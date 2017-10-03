#pragma once
//=====================================================================//
/*!	@file
	@brief	SDHI（SD カード）FatFS ドライバー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "ff12b/src/diskio.h"
#include "ff12b/src/ff.h"
#include "common/delay.hpp"
#include "common/format.hpp"

#if 0
/* MMC card type flags (MMC_GET_TYPE) */
#define CT_MMC		0x01		/* MMC ver 3 */
#define CT_SD1		0x02		/* SD ver 1 */
#define CT_SD2		0x04		/* SD ver 2 */
#define CT_SDC		(CT_SD1|CT_SD2)	/* SD */
#define CT_BLOCK	0x08		/* Block addressing */
#endif

/// F_PCLKB はクロック速度計算などで必要で、設定が無いとエラーにします。
#ifndef F_PCLKB
#  error "sdhi_io.hpp requires F_PCLKB to be defined"
#endif

namespace fatfs {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SDHI テンプレートクラス
		@param[in]	SDHI	SDHI クラス
		@param[in]	SPI		SPIの場合「true」	
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SDHI, bool SPI = true>
	class sdhi_io {

		DSTATUS stat_ = STA_NOINIT;	// Disk status
		BYTE card_type_ = 0;		// b0:MMC, b1:SDv1, b2:SDv2, b3:Block addressing

		// MMC/SD command (SPI mode)
		enum class command : uint8_t {
			CMD0 = 0,			///< GO_IDLE_STATE
			CMD1 = 1,			///< SEND_OP_COND
			ACMD41 = 0x80 + 41,	///< SEND_OP_COND (SDC)
			CMD8 = 8,			///< SEND_IF_COND
			CMD9 = 9,			///< SEND_CSD
			CMD10 = 10,			///< SEND_CID
			CMD12 = 12,			///< STOP_TRANSMISSION
			CMD13 = 13,			///< SEND_STATUS
			ACMD13 = 0x80 + 13,	///< SD_STATUS (SDC)
			CMD16 = 16,			///< SET_BLOCKLEN
			CMD17 = 17,			///< READ_SINGLE_BLOCK
			CMD18 = 18,			///< READ_MULTIPLE_BLOCK
			CMD23 = 23,			///< SET_BLOCK_COUNT
			ACMD23 = 0x80 + 23,	///< SET_WR_BLK_ERASE_COUNT (SDC)
			CMD24 = 24,			///< WRITE_BLOCK
			CMD25 = 25,			///< WRITE_MULTIPLE_BLOCK
			CMD32 = 32,			///< ERASE_ER_BLK_START
			CMD33 = 33,			///< ERASE_ER_BLK_END
			CMD38 = 38,			///< ERASE
			CMD55 = 55,			///< APP_CMD
			CMD58 = 58,			///< READ_OCR
		};


		void deselect_() {
//			SEL::P = 1;
//			BYTE d;
//			spi_.recv(&d, 1);	/* Dummy clock (force DO hi-z for multiple slave SPI) */
		}


		BYTE send_cmd_(command cmd, DWORD arg)
		{
			SDHI::SDSTS1 = 0;
			SDHI::SDSTS2 = 0;

			// クロック分周比、クロック許可、自動制御
			SDHI::SDCLKCR = SDHI::SDCLKCR.CLKSEL.b(1) | SDHI::SDCLKCR.CLKEN.b() | SDHI::SDCLKCR.CLKCTRLEN.b();

			SDHI::SDARG = arg;
			SDHI::SDCMD = SDHI::SDCMD.CMD.b(static_cast<uint8_t>(cmd));


#if 0
			auto c = static_cast<uint8_t>(cmd);
			if (c & 0x80) {	/* ACMD<n> is the command sequense of CMD55-CMD<n> */
				c &= 0x7F;
				auto n = send_cmd_(command::CMD55, 0);
				if (n > 1) return n;
			}

			/* Select the card and wait for ready except to stop multiple block read */
			if (c != static_cast<uint8_t>(command::CMD12)) {
				deselect_();
				if (!select_()) return 0xFF;
			}

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
			if (c == static_cast<uint8_t>(command::CMD12)) {  /* Skip a stuff byte when stop reading */
				BYTE d;
				spi_.recv(&d, 1);
			}

			n = 10;		/* Wait for a valid response in timeout of 10 attempts */
			BYTE d;
			do {
				spi_.recv(&d, 1);
			} while ((d & 0x80) && --n) ;

			return d;			/* Return with the response value */
#endif
			return 0;
		}


		/* 1:OK, 0:Failed */
		/* Data buffer to store received data */
		/* Byte count */
		int rcvr_datablock_(BYTE *buff, UINT btr)
		{
#if 0
			BYTE d[2];
			UINT tmr;
			for (tmr = 1000; tmr; tmr--) {	/* Wait for data packet in timeout of 100ms */
				spi_.recv(d, 1);
				if (d[0] != 0xFF) break;
				utils::delay::micro_second(100);
			}
			if (d[0] != 0xFE) return 0;		/* If not valid data token, return with error */

			spi_.recv(buff, btr);			/* Receive the data block into buffer */
			spi_.recv(d, 2);				/* Discard CRC */
#endif
			return 1;						/* Return with success */
		}

		/* 1:OK, 0:Failed */
		/* 512 byte data block to be transmitted */
		/* Data/Stop token */
		int xmit_datablock_(const BYTE *buff, BYTE token)
		{
#if 0
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
#endif
			return 1;
		}


		/* 1:OK, 0:Timeout */
		int wait_ready_() {
#if 0
			BYTE d;
			UINT tmr;
			for (tmr = 5000; tmr; tmr--) {	/* Wait for ready in timeout of 500ms */
				spi_.recv(&d, 1);
				if (d == 0xFF) break;
				utils::delay::micro_second(100);
			}
			return tmr ? 1 : 0;
#endif
			return 1;
		}

		/* 1:OK, 0:Timeout */
		int select_() {
#if 0
			SEL::P = 0;
			BYTE d;
			spi_.recv(&d, 1);	/* Dummy clock (force DO enabled) */
			if (wait_ready_()) return 1;	/* Wait for card ready */
			deselect_();
#endif
			return 0;			/* Failed */
		}


#if 0
		void start_spi_(bool fast)
		{
			uint32_t speed;
			if(fast) speed = spi_.get_max_speed();
			else speed = 4000000;  // 初期化時、4MB/s
			if(!spi_.start_sdc(speed)) {
				utils::format("CSI Start fail ! (Clock spped over range)\n");
			}
		}
#endif

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		sdhi_io() { }


		//-----------------------------------------------------------------//
		/*!
			@brief	カード・タイプの取得
			@return カード・タイプ
		 */
		//-----------------------------------------------------------------//
		BYTE card_type() const { return card_type_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ステータス
			@param[in]	drv		Physical drive nmuber (0)
		 */
		//-----------------------------------------------------------------//
		DSTATUS disk_status(BYTE drv) const
		{
			if (drv) return STA_NOINIT;
			return stat_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	初期化
			@param[in]	drv		Physical drive nmuber (0)
		 */
		//-----------------------------------------------------------------//
		DSTATUS disk_initialize(BYTE drv)
		{
			if(drv) return RES_NOTRDY;

			device::power_cfg::turn(SDHI::get_peripheral());

			device::port_map::turn(SDHI::get_peripheral());

#if 0
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
							utils::delay::micro_second(1000);
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
						utils::delay::micro_second(1000);
					}
					/* Set R/W block length to 512 */
					if (!tmr || send_cmd_(command::CMD16, 512) != 0) {
						ty = 0;
					}
				}
			}
			CardType_ = ty;
			DSTATUS s = ty ? 0 : STA_NOINIT;
			Stat_ = s;

			deselect_();

			start_spi_(true);

			return s;
#endif
			return RES_NOTRDY;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	リード・セクター
			@param[in]	drv		Physical drive nmuber (0)
			@param[out]	buff	Pointer to the data buffer to store read data
			@param[in]	sector	Start sector number (LBA)
			@param[in]	count	Sector count (1..128)
		 */
		//-----------------------------------------------------------------//
		DRESULT disk_read(BYTE drv, BYTE* buff, DWORD sector, UINT count)
		{
			if(disk_status(drv) & STA_NOINIT) return RES_NOTRDY;
			if(!(card_type_ & CT_BLOCK)) sector *= 512;	/* Convert LBA to byte address if needed */

			//  READ_MULTIPLE_BLOCK : READ_SINGLE_BLOCK
			command cmd = count > 1 ? command::CMD18 : command::CMD17;
			if(send_cmd_(cmd, sector) == 0) {
				do {
					if(!rcvr_datablock_(buff, 512)) break;
					buff += 512;
				} while(--count) ;
				if(cmd == command::CMD18) send_cmd_(command::CMD12, 0);	/* STOP_TRANSMISSION */
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
		 */
		//-----------------------------------------------------------------//
		DRESULT disk_write(BYTE drv, const BYTE* buff, DWORD sector, UINT count)
		{
			if(disk_status(drv) & STA_NOINIT) return RES_NOTRDY;
			if(!(card_type_ & CT_BLOCK)) sector *= 512;	/* Convert LBA to byte address if needed */

			if(count == 1) {  // Single block write
			if((send_cmd_(command::CMD24, sector) == 0)	/* WRITE_BLOCK */
				&& xmit_datablock_(buff, 0xFE))
				count = 0;
			} else {           // Multiple block write
				if(card_type_ & CT_SDC) send_cmd_(command::ACMD23, count);
				if (send_cmd_(command::CMD25, sector) == 0) {	/* WRITE_MULTIPLE_BLOCK */
				do {
					if (!xmit_datablock_(buff, 0xFC)) break;
					buff += 512;
				} while(--count) ;
					if(!xmit_datablock_(0, 0xFD)) {  /* STOP_TRAN token */
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
		 */
		//-----------------------------------------------------------------//
		DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void* buff)
		{
			if(disk_status(drv) & STA_NOINIT) return RES_NOTRDY;	/* Check if card is in the socket */

			DRESULT res = RES_ERROR;
			switch (ctrl) {
			case CTRL_SYNC :		/* Make sure that no pending write process */
				if(select_()) res = RES_OK;
				break;

			case GET_SECTOR_COUNT :	/* Get number of sectors on the disk (DWORD) */
				{
					BYTE csd[16];
					DWORD cs;
					if((send_cmd_(command::CMD9, 0) == 0) && rcvr_datablock_(csd, 16)) {
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
	};
}
