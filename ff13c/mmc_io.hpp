#pragma once
//=====================================================================//
/*!	@file
	@brief	MMC（SD カード）FatFS ドライバー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "ff13c/source/ff.h"
#include "ff13c/source/diskio.h"
#include "common/delay.hpp"
#include "common/format.hpp"

// #define DEBUG_MMC

namespace fatfs {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MMC テンプレートクラス
		@param[in]	SPI	SPI クラス
		@param[in]	SEL	デバイス選択クラス
		@param[in]	POW	電源操作クラス
		@param[in]	CDT	カード検出クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SPI, class SEL, class POW, class CDT>
	class mmc_io {

		// MMC card type flags (MMC_GET_TYPE)
		static const BYTE CT_MMC   = 0x01;	///< MMC ver 3
		static const BYTE CT_SD1   = 0x02;	///< SD ver 1
		static const BYTE CT_SD2   = 0x04;	///< SD ver 2
		static const BYTE CT_SDC   = CT_SD1 | CT_SD2;   ///< SD
		static const BYTE CT_BLOCK = 0x08;	///< Block addressing

		SPI&		spi_;

		FATFS		fatfs_;

		uint32_t	limitc_;

		DSTATUS		Stat_;		// Disk status
		BYTE		CardType_;	// b0:MMC, b1:SDv1, b2:SDv2, b3:Block addressing

		uint8_t		select_wait_;
		uint8_t		mount_delay_;
		bool		cd_;
		bool		mount_;
		bool		init_port_;

		// MMC/SD command (SPI mode)
		enum class command : uint8_t {
			CMD0 = 0,			/* GO_IDLE_STATE */
			CMD1 = 1,			/* SEND_OP_COND */
			ACMD41 = 0x80 + 41,	/* SEND_OP_COND (SDC) */
			CMD8 = 8,			/* SEND_IF_COND */
			CMD9 = 9,			/* SEND_CSD */
			CMD10 = 10,			/* SEND_CID */
			CMD12 = 12,			/* STOP_TRANSMISSION */
			CMD13 = 13,			/* SEND_STATUS */
			ACMD13 = 0x80 + 13,	/* SD_STATUS (SDC) */
			CMD16 = 16,			/* SET_BLOCKLEN */
			CMD17 = 17,			/* READ_SINGLE_BLOCK */
			CMD18 = 18,			/* READ_MULTIPLE_BLOCK */
			CMD23 = 23,			/* SET_BLOCK_COUNT */
			ACMD23 = 0x80 + 23,	/* SET_WR_BLK_ERASE_COUNT (SDC) */
			CMD24 = 24,			/* WRITE_BLOCK */
			CMD25 = 25,			/* WRITE_MULTIPLE_BLOCK */
			CMD32 = 32,			/* ERASE_ER_BLK_START */
			CMD33 = 33,			/* ERASE_ER_BLK_END */
			CMD38 = 38,			/* ERASE */
			CMD55 = 55,			/* APP_CMD */
			CMD58 = 58,			/* READ_OCR */
		};


		inline void lock_() {
#ifdef RTOS
			vTaskEnterCritical();
#endif
		}


		inline void unlock_() {
#ifdef RTOS
			vTaskExitCritical();
#endif
		}


		/* 1:OK, 0:Timeout */
		int wait_ready_() {
			UINT tmr;
			for (tmr = 5000; tmr; tmr--) {	/* Wait for ready in timeout of 500ms */
				BYTE d = spi_.xchg();
				if (d == 0xFF) break;
				utils::delay::micro_second(100);
			}
			return tmr ? 1 : 0;
		}


		void deselect_() {
			lock_();
			SEL::P = 1;
			unlock_();
			volatile BYTE d = spi_.xchg();	/* Dummy clock (force DO hi-z for multiple slave SPI) */
		}


		/* 1:OK, 0:Timeout */
		int select_() {
			lock_();
			SEL::P = 0;
			unlock_();
#ifdef DEBUG_MMC
			utils::format("Select port: %d\n") % static_cast<uint32_t>(SEL::P());
#endif
			volatile BYTE d = spi_.xchg();	/* Dummy clock (force DO enabled) */
#ifdef DEBUG_MMC
			utils::format("Select dummy: 0x%02X\n") % static_cast<uint32_t>(d);
#endif
			if (wait_ready_()) return 1;	/* Wait for card ready */
			deselect_();
			return 0;			/* Failed */
		}


		/* 1:OK, 0:Failed */
		/* Data buffer to store received data */
		/* Byte count */
		int rcvr_datablock_ (BYTE *buff, UINT btr)
		{
			BYTE d[2];
			UINT tmr;
			for (tmr = 1000; tmr; tmr--) {	/* Wait for data packet in timeout of 100ms */
				spi_.recv(d, 1);
				if (d[0] != 0xFF) break;
				utils::delay::micro_second(100);
			}
			if (d[0] != 0xFE) return 0;		/* If not valid data token, return with error */
#ifdef DEBUG_MMC
			utils::format("rcvr_datablock_: 0x%08X, %d\n") % (uint32_t)(buff)
				% static_cast<uint32_t>(btr);
			utils::delay::micro_second(100000);
#endif
			spi_.recv(buff, btr);			/* Receive the data block into buffer */
			spi_.recv(d, 2);				/* Discard CRC */

			return 1;						/* Return with success */
		}


		/* 1:OK, 0:Failed */
		/* 512 byte data block to be transmitted */
		/* Data/Stop token */
		int xmit_datablock_(const BYTE *buff, BYTE token) {
			BYTE d[2];

			if (!wait_ready_()) return 0;

			d[0] = token;
			spi_.send(d, 1);	/* Xmit a token */
			if (token != 0xFD) {		/* Is it data token? */
				spi_.send(buff, 512);	/* Xmit the 512 byte data block to MMC */
				spi_.recv(d, 2);		/* Xmit dummy CRC (0xFF,0xFF) */
				spi_.recv(d, 1);		/* Receive data response */
				if ((d[0] & 0x1F) != 0x05)	/* If not accepted, return with error */
				return 0;
			}

			return 1;
		}


		BYTE send_cmd_(command cmd, DWORD arg) {

#ifdef DEBUG_MMC
			utils::format("send_cmd_: 0x%02X, 0x%08X\n") % static_cast<uint32_t>(cmd) % static_cast<uint32_t>(arg);
#endif
			uint8_t c = static_cast<uint8_t>(cmd);
			if (c & 0x80) {	/* ACMD<n> is the command sequense of CMD55-CMD<n> */
				c &= 0x7F;
				auto n = send_cmd_(command::CMD55, 0);
				if (n > 1) return n;
			}

			/* Select the card and wait for ready except to stop multiple block read */
			if (c != static_cast<uint8_t>(command::CMD12)) {
///				utils::format("Deselect...\n");
				deselect_();
///				utils::format("Select...\n");
				if (!select_()) return 0xFF;
			}
#ifdef DEBUG_MMC
			utils::format("SEL: %d\n") % static_cast<int>(SEL::P());
			utils::format("CMD: 0x%02X\n") % static_cast<uint32_t>(cmd);
#endif
			/* Send a command packet */
			BYTE buf[6];
			buf[0] = 0x40 | c;						/* Start + Command index */
			buf[1] = static_cast<BYTE>(arg >> 24);	/* Argument[31..24] */
			buf[2] = static_cast<BYTE>(arg >> 16);	/* Argument[23..16] */
			buf[3] = static_cast<BYTE>(arg >> 8);	/* Argument[15..8] */
			buf[4] = static_cast<BYTE>(arg);		/* Argument[7..0] */
			BYTE n = 0x01;							/* Dummy CRC + Stop */
			if (c == static_cast<uint8_t>(command::CMD0)) n = 0x95;		/* (valid CRC for CMD0(0)) */
			if (c == static_cast<uint8_t>(command::CMD8)) n = 0x87;		/* (valid CRC for CMD8(0x1AA)) */
			buf[5] = n;
			spi_.send(buf, 6);

			/* Receive command response */
			BYTE d = 0;
			if (c == static_cast<uint8_t>(command::CMD12)) {  /* Skip a stuff byte when stop reading */
				d = spi_.xchg();
			}

			n = 10;		/* Wait for a valid response in timeout of 10 attempts */
			do {
				d = spi_.xchg();
			} while ((d & 0x80) && --n) ;

			return d;			/* Return with the response value */
		}

		void start_spi_(bool fast)
		{
			uint32_t speed;
			if(fast) {  // 最大速度制限
				speed = spi_.get_max_speed();
				if(speed > limitc_) speed = limitc_;
			} else {
				speed = 400000;  // 初期化時、400Kbits/s
			}
			if(!spi_.start_sdc(speed)) {
				utils::format("CSI Start fail ! (Clock spped over range)\n");
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	spi	SPI クラス
			@param[in]	limitc	SPI 最大速度
		 */
		//-----------------------------------------------------------------//
		mmc_io(SPI& spi, uint32_t limitc) noexcept :
			spi_(spi), limitc_(limitc), Stat_(STA_NOINIT), CardType_(0),
			select_wait_(0), mount_delay_(0), cd_(false), mount_(false),
			init_port_(false) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始（初期化）
		 */
		//-----------------------------------------------------------------//
		void start()
		{
			if(init_port_) return;

			lock_();

			if(POW::BIT_POS < 32) {
				POW::DIR = 1;
				POW::P = 1;  // power off
				POW::PU = 0;

				SEL::DIR = 1;
				SEL::PU = 0;
			  // ※電源 OFF 時は、SEL を「１」にすると、SEL から電流が流れるので、「０」にする
				SEL::P = 0;
			} else {
				SEL::DIR = 1;
				SEL::PU = 0;
				SEL::P = 1;
			}

			CDT::DIR = 0;
			CDT::PU  = 1;  // 内部プルアップは標準では有効にしておく

			unlock_();

			init_port_ = true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	カード・タイプの取得
			@return カード・タイプ
		 */
		//-----------------------------------------------------------------//
		BYTE card_type() const noexcept { return CardType_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ステータス
			@param[in]	drv		Physical drive nmuber (0)
		 */
		//-----------------------------------------------------------------//
		DSTATUS disk_status(BYTE drv) const noexcept
		{
			if (drv) return STA_NOINIT;
			return Stat_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	初期化
			@param[in]	drv		Physical drive nmuber (0)
			@return ステータス
		 */
		//-----------------------------------------------------------------//
		DSTATUS disk_initialize (BYTE drv) noexcept
		{
			if (drv) return RES_NOTRDY;

			SEL::P = 1;
			SEL::PU = 0;

			utils::delay::milli_second(100);  // 100ms

			// MISO: H (pull-up)
			start_spi_(false);
			/* Apply 80 dummy clocks and the card gets ready to receive command */
			BYTE buf[4];
			for (uint8_t n = 10; n; n--) spi_.recv(buf, 1);

			BYTE ty = 0;
			if (send_cmd_(command::CMD0, 0) == 1) {			/* Enter Idle state */
				if (send_cmd_(command::CMD8, 0x1AA) == 1) {	/* SDv2? */
					spi_.recv(buf, 4);						/* Get trailing return value of R7 resp */
					if (buf[2] == 0x01 && buf[3] == 0xAA) {	/* The card can work at vdd range of 2.7-3.6V */
						uint16_t tmr;
						for (tmr = 1000; tmr; tmr--) {	/* Wait for leaving idle state (ACMD41 with HCS bit) */
							if (send_cmd_(command::ACMD41, 1UL << 30) == 0) break;
							utils::delay::milli_second(1);
						}
						if (tmr && send_cmd_(command::CMD58, 0) == 0) {	/* Check CCS bit in the OCR */
							spi_.recv(buf, 4);
							ty = (buf[0] & 0x40) ? CT_SD2 | CT_BLOCK : CT_SD2;	/* SDv2 */
						}
					}
				} else {							/* SDv1 or MMCv3 */
					command cmd;
					if (send_cmd_(command::ACMD41, 0) <= 1) 	{
						ty = CT_SD1; cmd = command::ACMD41;	/* SDv1 */
					} else {
						ty = CT_MMC; cmd = command::CMD1;	/* MMCv3 */
					}
					uint16_t tmr;
					for (tmr = 1000; tmr; tmr--) {			/* Wait for leaving idle state */
						if (send_cmd_(cmd, 0) == 0) break;
						utils::delay::milli_second(1);
					}
					/* Set R/W block length to 512 */
					if (!tmr || send_cmd_(command::CMD16, 512) != 0) {
						ty = 0;
					}
				}
			} else {
#ifdef DEBUG_MMC
				utils::format("Idle state error...\n");
#endif
			}
			CardType_ = ty;
			DSTATUS s = ty ? 0 : STA_NOINIT;
			Stat_ = s;

			deselect_();

			start_spi_(true);

#ifdef DEBUG_MMC
			utils::format("init ret: cardtype: %d\n") % static_cast<uint32_t>(ty);
#endif
			return s;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	リード・セクター
			@param[in]	drv		Physical drive nmuber (0)
			@param[out]	buff	Pointer to the data buffer to store read data
			@param[in]	sector	Start sector number (LBA)
			@param[in]	count	Sector count (1..128)
			@return リザルト
		 */
		//-----------------------------------------------------------------//
		DRESULT disk_read(BYTE drv, BYTE* buff, DWORD sector, UINT count) noexcept
		{
			if (disk_status(drv) & STA_NOINIT) return RES_NOTRDY;
			if (!(CardType_ & CT_BLOCK)) sector *= 512;	/* Convert LBA to byte address if needed */

			/*  READ_MULTIPLE_BLOCK : READ_SINGLE_BLOCK */
			command cmd = count > 1 ? command::CMD18 : command::CMD17;
			if (send_cmd_(cmd, sector) == 0) {
				do {
					if (!rcvr_datablock_(buff, 512)) break;
					buff += 512;
				} while (--count) ;
				if (cmd == command::CMD18) send_cmd_(command::CMD12, 0);	/* STOP_TRANSMISSION */
			}
			deselect_();

			return count ? RES_ERROR : RES_OK;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ライト・セクター
			@param[in]	drv		Physical drive nmuber (0)
			@param[in]	buff	Pointer to the data to be written	
			@param[in]	sector	Start sector number (LBA)
			@param[in]	count	Sector count (1..128)
			@return リザルト
		 */
		//-----------------------------------------------------------------//
		DRESULT disk_write(BYTE drv, const BYTE* buff, DWORD sector, UINT count) noexcept
		{
			if (disk_status(drv) & STA_NOINIT) return RES_NOTRDY;
			if (!(CardType_ & CT_BLOCK)) sector *= 512;	/* Convert LBA to byte address if needed */

			if (count == 1) {	/* Single block write */
			if ((send_cmd_(command::CMD24, sector) == 0)	/* WRITE_BLOCK */
				&& xmit_datablock_(buff, 0xFE))
				count = 0;
			}
			else {				/* Multiple block write */
				if (CardType_ & CT_SDC) send_cmd_(command::ACMD23, count);
				if (send_cmd_(command::CMD25, sector) == 0) {	/* WRITE_MULTIPLE_BLOCK */
				do {
					if (!xmit_datablock_(buff, 0xFC)) break;
					buff += 512;
				} while (--count) ;
					if (!xmit_datablock_(0, 0xFD)) {  /* STOP_TRAN token */
						count = 1;
					}
				}
			}
			deselect_();

			return count ? RES_ERROR : RES_OK;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	I/O コントロール
			@param[in]	drv		Physical drive nmuber (0)
			@param[in]	ctrl	Control code
			@param[in]	buff	Buffer to send/receive control data
			@return リザルト
		 */
		//-----------------------------------------------------------------//
		DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void* buff) noexcept
		{
			if (disk_status(drv) & STA_NOINIT) return RES_NOTRDY;	/* Check if card is in the socket */

			DRESULT res = RES_ERROR;
			switch (ctrl) {
			case CTRL_SYNC :		/* Make sure that no pending write process */
				if (select_()) res = RES_OK;
				break;

			case GET_SECTOR_COUNT :	/* Get number of sectors on the disk (DWORD) */
				{
					BYTE csd[16];
					DWORD cs;
					if ((send_cmd_(command::CMD9, 0) == 0) && rcvr_datablock_(csd, 16)) {
						if ((csd[0] >> 6) == 1) {	/* SDC ver 2.00 */
							cs = csd[9] + ((WORD)csd[8] << 8) + ((DWORD)(csd[7] & 63) << 16) + 1;
							*(DWORD*)buff = cs << 10;
						} else {					/* SDC ver 1.XX or MMC */
							BYTE n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
							cs = (csd[8] >> 6) + ((WORD)csd[7] << 2) + ((WORD)(csd[6] & 3) << 10) + 1;
							*(DWORD*)buff = cs << (n - 9);
						}
						res = RES_OK;
					}
				}
				break;

			case GET_BLOCK_SIZE :	/* Get erase block size in unit of sector (DWORD) */
				*(DWORD*)buff = 128;
				res = RES_OK;
				break;

			default:
				res = RES_PARERR;
				break;
			}

			deselect_();

			return res;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	サービス @n
					※チャタリング除去を行う為、最大で、60Hz 間隔で呼び出す。
			@return カードがマウントされたら「true」
		 */
		//-----------------------------------------------------------------//
		bool service() noexcept
		{
			start();

			auto st = !CDT::P();
			if(st) {
				if(select_wait_ < 255) {
					++select_wait_;
				}
			} else {
				select_wait_ = 0;
			}
			if(!cd_ && select_wait_ >= 10) {
				mount_delay_ = 30;  // 30 フレーム後にマウントする
				if(POW::BIT_POS < 32) {
					lock_();
					POW::P = 0;
					SEL::P = 1;
					unlock_();
				} else {
					lock_();
					SEL::P = 1;
					unlock_();
				}
//				utils::format("Card ditect\n");
			} else if(cd_ && select_wait_ == 0) {
				f_mount(&fatfs_, "", 0);
				spi_.destroy();
				if(POW::BIT_POS < 32) {
					lock_();
					POW::P = 1;
					SEL::P = 0;
					unlock_();
				} else {
					lock_();
					SEL::P = 1;
					unlock_();
				}
				mount_ = false;
//				utils::format("Card unditect\n");
			}
			if(select_wait_ >= 10) cd_ = true;
			else cd_ = false;

			if(mount_delay_) {
				--mount_delay_;
				if(mount_delay_ == 0) {
					auto st = f_mount(&fatfs_, "", 1);
					if(st != FR_OK) {
						utils::format("f_mount NG: %d\n") % static_cast<uint32_t>(st);
						spi_.destroy();
						if(POW::BIT_POS < 32) {
							lock_();
							POW::P = 1;
							SEL::P = 0;
							unlock_();
						} else {
							lock_();
							SEL::P = 1;
							unlock_();
						}
						mount_ = false;
						init_port_ = false;  // 再マウント
					} else {
						mount_ = true;
					}
				}
			}
			return mount_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	カードのマウント状態取得
			@return カードがマウントされたら「true」
		 */
		//-----------------------------------------------------------------//
		bool get_mount() const noexcept { return mount_; }
	};
}
