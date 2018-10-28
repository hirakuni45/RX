#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ、SDHI（SD カード）FatFS ドライバー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "ff12b/src/diskio.h"
#include "ff12b/src/ff.h"
#include "RX600/sdhi.hpp"
#include "RX600/port_map.hpp"
#include "common/delay.hpp"
#include "common/format.hpp"

/// F_PCLKB はクロック速度計算などで必要で、設定が無いとエラーにします。
#ifndef F_PCLKB
#  error "sdhi_io.hpp requires F_PCLKB to be defined"
#endif

namespace fatfs {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SDHI テンプレートクラス
		@param[in]	SDHI	SDHI クラス
		@param[in]	POW		電源制御ポート・クラス
		@param[in]	PSEL	ポート候補
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SDHI, class POW, device::port_map::option PSEL = device::port_map::option::FIRST>
	class sdhi_io {

		// 通常 PCLKB は 60MHz
		static const uint8_t CARD_DETECT_DIVIDE_ = 11;			///< CD 信号サンプリング周期
		// SD カード初期化時100～400KBPS(224KBPS）
		static const uint8_t CLOCK_SLOW_DIVIDE_  = 0b01000000;	///< 初期化時のクロック周期 (1/256)
		static const uint8_t CLOCK_FAST_DIVIDE_  = 0b00000100;	///< 通常クロック周期 (1/16)

		// MMC card type flags (MMC_GET_TYPE)
		static const BYTE CT_MMC   = 0x01;	///< MMC ver 3
		static const BYTE CT_SD1   = 0x02;	///< SD ver 1
		static const BYTE CT_SD2   = 0x04;	///< SD ver 2
		static const BYTE CT_SDC   = CT_SD1 | CT_SD2;   ///< SD
		static const BYTE CT_BLOCK = 0x08;	///< Block addressing

		FATFS		fatfs_;

		DSTATUS		stat_;			// Disk status
		BYTE		card_type_;		// b0:MMC, b1:SDv1, b2:SDv2, b3:Block addressing

		uint8_t		mount_delay_;
		bool		cd_;
		bool		mount_;
		bool		start_;
		bool		fast_;
		bool		onew_;

		// MMC/SD command (SPI mode)
		enum class command : uint32_t {
                                  // 引数　       応答　データ転送　説明
            CMD0   = 0x00000000,  // -            R1    -           ソフトウェア・リセット
			CMD1   = 0x00000001,  // -            R1    -           初期化開始
			CMD6   = 0x00000006,  // 
			CMD8   = 0x00000408,  // *3           R7    -           SDC V2 専用、動作電圧確認
			CMD9   = 0x00000009,  // -            R1    あり        CSD 読み出し
			CMD10  = 0x0000000A,  // -            R1    あり        CID 読み出し
			CMD12  = 0x0000000C,  // -            R1b   -           リード動作停止
			CMD16  = 0x00000010,  // BlockLen(32) R1    -           R/W ブロック長変更
			CMD17  = 0x00000011,  // Address(32)  R1    あり        シングル・ブロック・リード
			CMD18  = 0x00000012,  // Address(32)  R1    あり        マルチ・ブロック・リード
			CMD23  = 0x00000017,  // Block(16)    R1    -           MMC 専用次のマルチブロックブロック数設定
			CMD24  = 0x00000018,  // Address(32)  R1    あり        シングル・ブロック・ライト
			CMD25  = 0x00000019,  // Address(32)  R1    あり        マルチ・ブロック・ライト
			CMD55  = 0x00000037,  // -            R1    -           アプリケーション特化コマンド
			CMD58  = 0x0000003A,  // -            R3    -           OCR レジスタ取得    
			ACMD23 = 0x00000057,  // Block(23)    R1    -           SDC 専用次のマルチブロックブロック数設定
			ACMD41 = 0x00000069,  // *2           R1    -           SDC 専用、初期化開始
		};


		enum class state : uint8_t {
			no_error,
			cmd_error,
			timeout,
		};


		void set_clk_()
		{
			SDHI::SDSTS1 = 0;
			SDHI::SDSTS2 = 0;

			while(SDHI::SDSTS2.SDCLKCREN() == 0) ;

			if(fast_) {
///				SDHI::SDOPT = SDHI::SDOPT.CTOP.b(CARD_DETECT_DIVIDE_) | SDHI::SDOPT.WIDTH.b(1)
///					| SDHI::SDOPT.TOP.b(12);
//				SDHI::SDOPT = SDHI::SDOPT.CTOP.b(CARD_DETECT_DIVIDE_) | SDHI::SDOPT.WIDTH.b(onew_)
//					| SDHI::SDOPT.TOP.b(12);
				// F_PCLKB / 4 (15MHz)
				SDHI::SDCLKCR.CLKEN = 0;
				SDHI::SDCLKCR.CLKSEL = CLOCK_FAST_DIVIDE_;
				SDHI::SDCLKCR.CLKEN = 1;
			} else {
				// Card detect 50Hz(20ms) とする
				// ONEW: 1 bit: 1, 4 bits: 0
				// 開始時は、1 bit にしておく
///				SDHI::SDOPT = SDHI::SDOPT.CTOP.b(CARD_DETECT_DIVIDE_) | SDHI::SDOPT.WIDTH.b(1)
///					| SDHI::SDOPT.TOP.b(12);
				// F_PCLKB / 256
				SDHI::SDCLKCR.CLKEN = 0;
				SDHI::SDCLKCR.CLKSEL = CLOCK_SLOW_DIVIDE_;
				SDHI::SDCLKCR.CLKEN = 1;
			}
		}


		state send_cmd_(command cmd, uint32_t arg, bool check_err = true)
		{
			set_clk_();
			SDHI::SDARG = arg;
			while(SDHI::SDSTS2.CBSY() != 0) ;
			SDHI::SDCMD = static_cast<uint32_t>(cmd);
			state st = state::no_error;
			while(SDHI::SDSTS1.RSPEND() == 0) {
				if(check_err) {
					auto sts = SDHI::SDSTS2();
					if(sts & SDHI::SDSTS2.CMDE.b()) {
						SDHI::SDSTS2.CMDE = 0;
///						utils::format("send_cmd_: CMDE...\n");
						st = state::cmd_error;
						break;
					}
					if(sts & SDHI::SDSTS2.RSPTO.b()) {
						SDHI::SDSTS2.RSPTO = 0;
///						utils::format("send_cmd_: RSPTO... (timeout)\n");
						st = state::timeout;
						break;
					}
				}
			}
			SDHI::SDSTS1 = 0x0000FFFE;
			return st;
		}


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	onew	１ビットモードの場合「true」
		 */
		//-----------------------------------------------------------------//
		sdhi_io(bool onew = false) noexcept : stat_(STA_NOINIT), card_type_(0),
			mount_delay_(0), cd_(false), mount_(false), start_(false), fast_(false),
			onew_(onew) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
		 */
		//-----------------------------------------------------------------//
		void start()
		{
			if(!start_) {
				POW::DIR = 1;
				POW::P   = 1;  // offline power
				POW::PU  = 0;
				POW::OD  = 1;  // Open Drain

				device::power_cfg::turn(SDHI::get_peripheral());
				device::port_map::turn(SDHI::get_peripheral(), true, PSEL);

				while(SDHI::SDSTS2.CBSY() != 0) ;
				SDHI::SDOPT = SDHI::SDOPT.CTOP.b(CARD_DETECT_DIVIDE_) | SDHI::SDOPT.WIDTH.b()
					| SDHI::SDOPT.TOP.b(12);

#ifdef LITTLE_ENDIAN
				// データ読み出し、書き込み時のエンディアン変換を有効にする
//				SDHI::SDSWAP = SDHI::SDSWAP.BWSWP.b(1) | SDHI::SDSWAP.BRSWP.b(1);
#endif
				fast_ = false;
				start_ = true;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	カード・タイプの取得
			@return カード・タイプ
		 */
		//-----------------------------------------------------------------//
		BYTE card_type() const noexcept { return card_type_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ステータス
			@param[in]	drv		Physical drive nmuber (0)
		 */
		//-----------------------------------------------------------------//
		DSTATUS disk_status(BYTE drv) const noexcept
		{
			if (drv) return STA_NOINIT;
			return stat_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	エラー・ステータスの詳細レポート
			@param[in]	opt		表示に付け加える文字列
		 */
		//-----------------------------------------------------------------//
		void list_error_state1(const char* opt = "") const noexcept
		{
			utils::format("%s") % opt;
			utils::format("CMDE0:    %d\n") % static_cast<uint16_t>(SDHI::SDERSTS1.CMDE0());
			utils::format("%s") % opt;
			utils::format("CMDE1:    %d\n") % static_cast<uint16_t>(SDHI::SDERSTS1.CMDE1());
			utils::format("%s") % opt;
			utils::format("RSPLENE0: %d\n") % static_cast<uint16_t>(SDHI::SDERSTS1.RSPLENE0());
			utils::format("%s") % opt;
			utils::format("RSPLENE1: %d\n") % static_cast<uint16_t>(SDHI::SDERSTS1.RSPLENE1());
			utils::format("%s") % opt;
			utils::format("RDLENE:   %d\n") % static_cast<uint16_t>(SDHI::SDERSTS1.RDLENE());
			utils::format("%s") % opt;
			utils::format("CRCLENE:  %d\n") % static_cast<uint16_t>(SDHI::SDERSTS1.CRCLENE());
			utils::format("%s") % opt;
			utils::format("RSPCRCE0: %d\n") % static_cast<uint16_t>(SDHI::SDERSTS1.RSPCRCE0());
			utils::format("%s") % opt;
			utils::format("RSPCRCE1: %d\n") % static_cast<uint16_t>(SDHI::SDERSTS1.RSPCRCE1());
			utils::format("%s") % opt;
			utils::format("RDCRCE:   %d\n") % static_cast<uint16_t>(SDHI::SDERSTS1.RDCRCE());
			utils::format("%s") % opt;
			utils::format("CRCTKE:   %d\n") % static_cast<uint16_t>(SDHI::SDERSTS1.CRCTKE());
			utils::format("%s") % opt;
			utils::format("CRCTK:    %d\n") % static_cast<uint16_t>(SDHI::SDERSTS1.CRCTK());
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	初期化
			@param[in]	drv		Physical drive nmuber (0)
		 */
		//-----------------------------------------------------------------//
		DSTATUS disk_initialize(BYTE drv) noexcept
		{
			if(drv) return RES_NOTRDY;

			utils::format("Start: disk_initialize\n");
#if 0
			utils::format("  Version IP1: 0x%02X, IP2: 0x%1X, CLKRAT: %d, CPRM: %d\n")
				% static_cast<uint16_t>(SDHI::SDVER.IP1())
				% static_cast<uint16_t>(SDHI::SDVER.IP2())
				% static_cast<uint16_t>(SDHI::SDVER.CLKRAT())
				% static_cast<uint16_t>(SDHI::SDVER.CPRM());
			utils::format("  SDSIZE: %d\n") % SDHI::SDSIZE();
#endif
			// ダミークロックを７４個以上入った事を確認する。
			// ※CS(D3) = 1, DI = 1 が「１」の状態である事。
			SDHI::SDCLKCR.CLKCTRLEN = 1;
			set_clk_();
			SDHI::SDCLKCR.CLKCTRLEN = 0;
			for(uint32_t i = 0; i < 75; ++i) {
				while(device::port_map::probe_sdhi_clock(PSEL) == 0) ;
				while(device::port_map::probe_sdhi_clock(PSEL) == 1) ;
			}
			SDHI::SDCLKCR.CLKCTRLEN = 1;

			if(send_cmd_(command::CMD0, 0) != state::no_error) {  // soft reset
				utils::format("CMD0: Error\n");
				stat_ = STA_NOINIT;
				return stat_;
			}
			utils::format("CMD0: OK!\n");

			BYTE ty = 0;
			if(send_cmd_(command::CMD8, 0x01AA) == state::no_error) {
				uint32_t res = SDHI::SDRSP10() & 0xFFF;
				if(res != 0x1AA) {  // No Match for SD-V1
					utils::format("CMD8: State Miss Match (%03X)\n") % res;
					stat_ = STA_NOINIT;
					return stat_;
				} else {
					utils::format("CMD8: OK! for 'SD-V2'\n");
					ty = CT_SD2;  // for SD Ver 2.x
				}
			} else {  // Error, No Response for SD-V1, MMC-V3, Error
				ty = CT_SD1;
				utils::format("CMD8: NG! for 'SD-V1, MMC-V3 or Fail'\n");
			}

///////////////////////////////////////////////////////////////

			// 初期化コマンド(CMD55/ACMD41)
			// retray loop count: 1 turn 640 clock for 234KHz(60MHz / 256) 2.735ms
			// 750 ms: 
			static const uint32_t init_limit = 300;
			uint32_t init_loop = 0;
			while(init_loop < init_limit) {
				auto st = send_cmd_(command::CMD55, 0);
				if(st != state::no_error) {
					utils::format("CMD55: Error\n");
				}
				uint32_t send = (ty == CT_SD2) ? 0x40000000 : 0x00000000;
				st = send_cmd_(command::ACMD41, send);
				uint32_t res = SDHI::SDRSP10();
// utils::format("ACM41: %08X\n") % res;
				if(st == state::no_error && res == 0) {
					break;
				} else {
					++init_loop;
				}
			}
			if(init_loop >= init_limit) {  // timeout
				utils::format("ACMD41: Time Out\n");
				stat_ = STA_NOINIT;
				return stat_;
			}

			if(ty == CT_SD2) {
				utils::format("ACMD41: OK! (SD-V2), %d loops\n") % init_loop;

				// Block for 512 bytes
				if(send_cmd_(command::CMD16, 512) == state::no_error) {
					utils::format("CMD16: OK!\n");
				} else {
					utils::format("CMD16: NG!\n");
				}
			} else { // SD-V1
				utils::format("ACMD41: OK! (SD-V1), %d loops\n") % init_loop;
			}

//	ty |= CT_BLOCK;

			card_type_ = ty;
			stat_ = ty ? 0 : STA_NOINIT;

			// boost for CLK
			fast_ = true;

			if(card_type_ & CT_BLOCK) {
				utils::format("SD: Block mode\n"); 
			}

			return stat_;
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
		DRESULT disk_read(BYTE drv, void* buff, DWORD sector, UINT count) noexcept
		{
			if(disk_status(drv) & STA_NOINIT) return RES_NOTRDY;

			// Convert LBA to byte address if needed
			if(!(card_type_ & CT_BLOCK)) sector *= 512;

			utils::format("disk_read: sector: %d, count: %d\n") % sector % count;

			set_clk_();
			SDHI::SDSIZE   = 512;
//			SDHI::SDIMSK1  = 0x0000FFFE;
//			SDHI::SDIMSK2  = 0x00007F80;
			SDHI::SDSTOP   = 0x00000100;  // for multi block
			SDHI::SDBLKCNT = count;  // for multi block read
			SDHI::SDARG    = sector;
			command cmd = count > 1 ? command::CMD18 : command::CMD17;
			const char* cmdstr = cmd == command::CMD17 ? "CMD17" : "CMD18";
			SDHI::SDCMD = static_cast<uint32_t>(cmd);
			while(SDHI::SDSTS1.RSPEND() == 0) {
				if(SDHI::SDSTS2.CRCE()) {
					utils::format("%s CRC Error (CRCE)\n") % cmdstr;
					return RES_ERROR;
				}
				if(SDHI::SDSTS2.CMDE()) {
					utils::format("%s Command error (CMDE)\n") % cmdstr;
					return RES_ERROR;
				}
				if(SDHI::SDSTS2.RSPTO()) {
					utils::format("%s Response Timeout (RSPTO)\n") % cmdstr;
					return RES_ERROR;
				}
			}
			SDHI::SDSTS1 = 0x0000FFFE;
			auto sp10 = SDHI::SDRSP10();
			utils::format("%s: Response: %08X\n") % cmdstr % sp10;
			uint32_t loop = 0;
			while(SDHI::SDSTS2.BRE() == 0) {				
				if(loop >= 1000000) {
					utils::format("%s time out\n") % cmdstr;
					return RES_ERROR;
				}
				auto st = SDHI::SDSTS2();
				if(st & SDHI::SDSTS2.DTO.b()) {
					utils::format("%s DTO error\n") % cmdstr;
					return RES_ERROR;
				}
				if(st & SDHI::SDSTS2.CRCE.b()) {
					utils::format("%s CRC error\n") % cmdstr;
					return RES_ERROR;
				}
				++loop;
				utils::delay::micro_second(100);
			}

			SDHI::SDSTS2 = 0x0000FEFF;
			utils::format("%s BRE: OK\n") % cmdstr;

			if((reinterpret_cast<uint32_t>(buff) & 0x3) == 0) {
				uint32_t* p = static_cast<uint32_t*>(buff);
				for(uint32_t n = 0; n < (512 / 4); ++n) {
					*p++ = SDHI::SDBUFR(); 
				}
			} else {
				uint8_t* p = static_cast<uint8_t*>(buff);
				for(uint32_t n = 0; n < 128; ++n) {
					uint32_t tmp = SDHI::SDBUFR();
					std::memcpy(p, &tmp, 4);
					p += 4;
				}
			}

			utils::format("Data trans: OK\n");

			while(SDHI::SDSTS1.ACEND() == 0) {

			}
			SDHI::SDSTS1 = 0x0000FFFB;
			{
				auto sp10 = SDHI::SDRSP10();
				utils::format("Data end: 0x%08X\n") % sp10;
			}
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
		DRESULT disk_write(BYTE drv, const void* buff, DWORD sector, UINT count) noexcept
		{
			if(disk_status(drv) & STA_NOINIT) return RES_NOTRDY;
			if(!(card_type_ & CT_BLOCK)) sector *= 512;	/* Convert LBA to byte address if needed */

			SDHI::SDSTS1 = 0;
			SDHI::SDSTS2 = 0;
			SDHI::SDSIZE = 512;

			if(count == 1) {  // Single block write
				SDHI::SDARG = sector;
				SDHI::SDCMD = static_cast<uint32_t>(command::CMD24);

				while(SDHI::SDSTS1.RSPEND() == 0) {
					if(SDHI::SDSTS2() & (SDHI::SDSTS2.CMDE.b() | SDHI::SDSTS2.RSPTO.b())) {
						return RES_ERROR;
					}
				}
				SDHI::SDSTS1 = 0x0000FFFE;
//				auto sp10 = SDHI::SDRSP10();
				if((reinterpret_cast<uint32_t>(buff) & 0x3) == 0) {
					const uint32_t* p = static_cast<const uint32_t*>(buff);
					for(uint32_t n = 0; n < 128; ++n) {
						SDHI::SDBUFR = *p++;
					}
				} else {
					const uint8_t* p = static_cast<const uint8_t*>(buff);
					for(uint32_t n = 0; n < 128; ++n) {
						uint32_t tmp;
						std::memcpy(&tmp, p, 4);
						p += 4;
						SDHI::SDBUFR = tmp;
					}
				}
				while(SDHI::SDSTS1.ACEND() == 0) {

				}
				SDHI::SDSTS1 = 0x0000FFFB;
				count = 0;
			} else {  // Multiple block write
#if 0
				if(card_type_ & CT_SDC) send_cmd_(command::ACMD23, count);
				if(send_cmd_(command::CMD25, sector) == 0) {	/* WRITE_MULTIPLE_BLOCK */
				do {
					if (!xmit_datablock_(buff, 0xFC)) break;
					buff += 512;
				} while(--count) ;
					if(!xmit_datablock_(0, 0xFD)) {  /* STOP_TRAN token */
						count = 1;
					}
				}
#endif
			}

			return count != 0 ? RES_ERROR : RES_OK;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	I/O コントロール
			@param[in]	drv		Physical drive nmuber (0)
			@param[in]	ctrl	Control code
			@param[in]	buff	Buffer to send/receive control data
		 */
		//-----------------------------------------------------------------//
		DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void* buff) noexcept
		{
			if(disk_status(drv) & STA_NOINIT) return RES_NOTRDY;  // Check if card is in the socket

			utils::format("disk_ioctl: %02X\n") % static_cast<uint16_t>(ctrl);

			DRESULT res = RES_ERROR;
			switch (ctrl) {
			case CTRL_SYNC :		/* Make sure that no pending write process */
///				if(select_()) res = RES_OK;
				break;

			case GET_SECTOR_COUNT :	/* Get number of sectors on the disk (DWORD) */
				{
#if 0
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
#endif
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

			bool cd = SDHI::SDSTS1.SDCDMON();
			if(cd && !cd_) {
				utils::format("Card Detect\n");
				POW::P = 0;  // power ON!
				mount_delay_ = 30;  // 30 フレーム後にマウントする
			} else if(!cd && cd_) {
				utils::format("Card Eject\n");
				f_mount(&fatfs_, "", 0);
				POW::P = 1;
				mount_ = false;
			}
			cd_ = cd;

			if(mount_delay_) {
				--mount_delay_;
				if(mount_delay_ == 0) {
					auto st = f_mount(&fatfs_, "", 1);
					if(st != FR_OK) {
						utils::format("f_mount NG: %d\n") % static_cast<uint32_t>(st);
						POW::P = 1;
						mount_ = false;
					} else {
						utils::format("f_mount OK\n");
						mount_ = true;
					}
				}
			}

			return mount_;
		}
	};
}
