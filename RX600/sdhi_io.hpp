#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ、SDHI（SD ホストインターフェース）FatFS ドライバー @n
			SDHI インターフェースを使った SD カードアクセス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "ff13c/source/ff.h"
#include "ff13c/source/diskio.h"

#include "common/format.hpp"
// #include "common/memmgr.hpp"

/// F_PCLKB はクロック速度計算などで必要で、設定が無いとエラーにします。
#ifndef F_PCLKB
#  error "sdhi_io.hpp requires F_PCLKB to be defined"
#endif

/// byte_order.h のインクルードをしているかチェック
#if defined(LITTLE_ENDIAN)
#elif defined(BIG_ENDIAN)
#else
#  error "sdhi_io.hpp requires {LITTLE/BIG}_ENDIAN to be defined"
#endif

namespace fatfs {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SDHI テンプレートクラス
		@param[in]	SDHI	SDHI クラス
		@param[in]	POW		電源制御ポート・クラス
		@param[in]	WPRT	書き込み禁止ポート・クラス
		@param[in]	PSEL	ポート候補（port_map.hpp 参照）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SDHI, class POW, class WPRT = device::NULL_PORT,
		device::port_map::option PSEL = device::port_map::option::FIRST>
	class sdhi_io {

//		typedef utils::format debug_format;
		typedef utils::null_format debug_format;

		static const uint32_t MOUNT_DELAY_FRAME = 60;		///< 60 frame (1.0 sec)

		static const int DUMMY_LOOP_LIMIT = 1000;

		// 通常 PCLKB は 60MHz
		static const uint8_t CARD_DETECT_DIVIDE_ = 12;		///< CD 信号サンプリング周期
		static const uint8_t TIME_OUT_DIVIDE_    = 14;		///< タイムアウトカウント（０～１４）
		// SD カード初期化時100～400KBPS(60MHz / 256: 224KBPS）
		static const uint8_t CLOCK_SLOW_DIVIDE_  = 0b01000000;	///< 初期化時の分周比 (1/256)
		// RX65N Envision Kit では、30MHz までが安定動作。
		// RX72N Envision Kit では、60MHz まで動作確認したものの、マージンを取り、30MHz で運用。
///		static const uint8_t CLOCK_FAST_DIVIDE_  = 0b11111111;	///< ブースト時 (60MHz:1/1)
		static const uint8_t CLOCK_FAST_DIVIDE_  = 0b00000000;	///< ブースト時 (30MHz:1/2)
//		static const uint8_t CLOCK_FAST_DIVIDE_  = 0b00000001;	///< ブースト時 (15MHz:1/4)
//		static const uint8_t CLOCK_FAST_DIVIDE_  = 0b00000010;	///< ブースト時 (7.5MHz:1/8)
//		static const uint8_t CLOCK_FAST_DIVIDE_  = 0b00000100;	///< ブースト時 (3.75MHz:1/16)

		// MMC card type flags (MMC_GET_TYPE)
		static const uint8_t CT_MMC   = 0b00000001;	///< MMC ver 3
		static const uint8_t CT_SD1   = 0b00000010;	///< SD(SC) ,FAT12(16) (2G までのカード）
		static const uint8_t CT_SD2   = 0b00000100;	///< SDHC   ,FAT32 (32G までのカード）
//		static const uint8_t CT_SD3   = 0b00001000;	///< SDXC   ,exFAT (32G を超えるカード）
		static const uint8_t CT_BLOCK = 0b00010000;	///< Block addressing

		static const int BUSY_LOOP_LIMIT  = 1000;
		static const int ACEND_LOOP_LIMIT = 10000;
		static const int CMD0_LOOP_MAX   = 3;
		static const int ACMD41_LOOP_MAX = 1000;
		static const int CMD3_LOOP_MAX   = 3;
		static const int BRE_LOOP_LIMIT  = 1000;
		static const int BWE_LOOP_LIMIT  = 1000;

		FATFS		fatfs_;
		DSTATUS		stat_;			// Disk status
		uint8_t		card_type_;

		uint8_t		mount_delay_;
		uint8_t		intr_lvl_;
		bool		cd_;
		bool		mount_;
		bool		start_;
		bool		onew_;

		uint32_t	rca_id_;
		uint32_t	cid_[4];

		// SD command
		enum class command : uint32_t {
                              // 引数　       応答　転送　説明
            CMD0   = 0,       // -            R1    -     ソフトウェア・リセット
			CMD2   = 2,       // -            R2    -	  CID の読み出し
			CMD3   = 3,       // -            R3    -	  RCA の読み出し
			CMD4   = 4,       // -            R3    -	  DSR

			CMD6   = 6,       // 
			CMD7   = 7,       // RCA-ID       R1b         SD カードセレクト 
			CMD8   = 8,       // *3           R7    -     SDC V2 専用、動作電圧確認
			CMD9   = 9,       // -            R1    あり  CSD 読み出し
			CMD10  = 10,      // -            R1    あり  CID 読み出し
			CMD12  = 12,      // -            R1b   -     リード動作停止
			CMD16  = 16,      // BlockLen(32) R1    -     R/W ブロック長変更
			CMD17  = 17,      // Address(32)  R1    あり  シングル・ブロック・リード
			CMD18  = 18,      // Address(32)  R1    あり  マルチ・ブロック・リード
			CMD23  = 23,      // Block(16)    R1    -     MMC 専用次のマルチブロックブロック数設定
			CMD24  = 24,      // Address(32)  R1    あり  シングル・ブロック・ライト
			CMD25  = 25,      // Address(32)  R1    あり  マルチ・ブロック・ライト
			CMD41  = 41,
			CMD55  = 55,      // -            R1    -     アプリケーション特化コマンド
			CMD58  = 58,      // -            R3    -     OCR レジスタ取得

			ACMD6  = 0x40+6,  //                    -     Set Bus Width
			ACMD23 = 0x40+23, // Block(23)    R1    -     SDC 専用次のマルチブロックブロック数設定
			ACMD41 = 0x40+41, // *2           R3    -     SDC 専用、初期化開始
		};


		enum class state : uint8_t {
			no_error,
			cmd_error,
			timeout,
			busy,
		};


		bool wait_busy_() noexcept {
			int loop = 0;
///			while(SDHI::SDSTS2.CBSY() != 0) {
			while(SDHI::SDSTS2.SDCLKCREN() == 0) {
				++loop;
				if(loop >= BUSY_LOOP_LIMIT) {
					return false;
				}
				utils::delay::micro_second(10);
			}
			return true;
		}


		bool wait_acend_() noexcept {
			int loop = 0;
			while(SDHI::SDSTS1.ACEND() == 0) {
				++loop;
				if(loop >= ACEND_LOOP_LIMIT) {
					return false;
				}
				utils::delay::micro_second(10);
			}
			return true;
		}


		bool set_bus_(bool single) noexcept {
			if(!wait_busy_()) {
				return false;
			}

			SDHI::SDOPT =
				  SDHI::SDOPT.CTOP.b(CARD_DETECT_DIVIDE_)
				| SDHI::SDOPT.TOP.b(TIME_OUT_DIVIDE_)
				| SDHI::SDOPT.WIDTH.b(single);
			return true;
		}


		void set_clk_(bool fast) noexcept {
			SDHI::SDSTS1 = 0;
			SDHI::SDSTS2 = 0;

			while(SDHI::SDSTS2.SDCLKCREN() == 0) ;

			SDHI::SDCLKCR.CLKEN = 0;
			if(fast) {
				SDHI::SDCLKCR.CLKSEL = CLOCK_FAST_DIVIDE_;
			} else {
				SDHI::SDCLKCR.CLKSEL = CLOCK_SLOW_DIVIDE_;
			}
			SDHI::SDCLKCR.CLKEN = 1;
			uint32_t div = SDHI::SDCLKCR.CLKSEL();
			if(div == 0) div = 2;
			else if(div == 0xff) div = 1; 
			else div <<= 2;
			auto frq = F_PCLKB / div / 1000;
			char ch = 'K';
			if(frq >= 1000) {
				ch = 'M';
				frq /= 1000;
			}
			debug_format("SD CLK: %d %cHz\n") % frq % ch;
		}


		state send_cmd_sub_(command cmd, uint32_t arg, bool check_err = true) noexcept
		{
			SDHI::SDARG = arg;

			if(!wait_busy_()) {
				return state::busy;
			}

			SDHI::SDCMD = static_cast<uint32_t>(cmd);
			state st = state::no_error;
			while(SDHI::SDSTS1.RSPEND() == 0) {
				if(check_err) {
					auto sts = SDHI::SDSTS2();
					if(sts & SDHI::SDSTS2.CMDE.b()) {
						SDHI::SDSTS2.CMDE = 0;
						debug_format("send_cmd_: CMDE...\n");
						st = state::cmd_error;
						break;
					}
					if(sts & SDHI::SDSTS2.CRCE.b()) {
						SDHI::SDSTS2.CRCE = 0;
						debug_format("send_cmd_: CRCE...\n");
						st = state::cmd_error;
						break;
					}
					if(sts & SDHI::SDSTS2.RSPTO.b()) {
						SDHI::SDSTS2.RSPTO = 0;
						debug_format("send_cmd_: RSPTO... (timeout)\n");
						st = state::timeout;
						break;
					}
					if(sts & SDHI::SDSTS2.ENDE.b()) {
						SDHI::SDSTS2.ENDE = 0;
						debug_format("send_cmd_: ENDE...\n");
						st = state::cmd_error;
						break;
					}
				}
			}
			SDHI::SDSTS1 = 0x0000FFFE;
			return st;
		}


		state send_cmd_(command cmd, uint32_t arg, bool check_err = true) noexcept
		{
			if((static_cast<uint32_t>(cmd) & 0x40) != 0) {
				auto res = send_cmd_sub_(command::CMD55, rca_id_);
				if(res != state::no_error) {
					return res;
				}
			}
			return send_cmd_sub_(cmd, arg, check_err);
		}


		bool send_cmd_data_(command cmd, uint32_t arg) noexcept
		{
			SDHI::SDARG = arg;
			SDHI::SDCMD = static_cast<uint32_t>(cmd);
			while(SDHI::SDSTS1.RSPEND() == 0) {
				if(SDHI::SDSTS2.CRCE()) {
					debug_format("CRC Error (CRCE)\n");
					return false;
				}
				if(SDHI::SDSTS2.CMDE()) {
					debug_format("Command error (CMDE)\n");
					return false;
				}
				if(SDHI::SDSTS2.RSPTO()) {
					debug_format("Response Timeout (RSPTO)\n");
					return false;
				}
			}
			SDHI::SDSTS1 = 0x0000FFFE;
			auto sp10 = SDHI::SDRSP10();
///			utils::format("%s: Response: %08X\n") % cmdstr % sp10;
			int loop = 0;
			while(SDHI::SDSTS2.BRE() == 0) {
				if(loop >= BRE_LOOP_LIMIT) {
					debug_format("Data Time out\n");
					return false;
				}
				auto st = SDHI::SDSTS2();
				if(st & SDHI::SDSTS2.DTO.b()) {
					debug_format("Data DTO error\n");
					return false;
				}
				if(st & SDHI::SDSTS2.CRCE.b()) {
					debug_format("Data CRC error\n");
					return false;
				}
				++loop;
				utils::delay::micro_second(100);
			}
			SDHI::SDSTS2 = 0x0000FEFF;
			return true;
		}


		static void cdeti_task_() noexcept {
		}

		static void caci_task_() noexcept {
		}

		static void sdaci_task_() noexcept {
		}

		static volatile uint32_t i_count_;

		static INTERRUPT_FUNC void sbfai_task_() noexcept {
			++i_count_;
		}

		static void sync_data_end_() noexcept {
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	onew	１ビットモードの場合「true」
		 */
		//-----------------------------------------------------------------//
		sdhi_io(bool onew = false) noexcept :
			stat_(STA_NOINIT), card_type_(0),
			mount_delay_(0), intr_lvl_(0),
			cd_(false), mount_(false), start_(false),
			onew_(onew), rca_id_(0)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@param[in]	lvl		割り込みレベル（０の場合、ポーリング）
		 */
		//-----------------------------------------------------------------//
		void start(uint8_t lvl = 0)
		{
			if(start_) {
				return;
			}

			POW::DIR = 1;
			POW::P   = 0;  // offline power
			POW::PU  = 0;

			WPRT::DIR = 0;

			device::power_mgr::turn(SDHI::PERIPHERAL);
			using port_map = device::port_map;
			port_map::turn_sdhi(port_map::sdhi_situation::START, PSEL);

			intr_lvl_ = lvl;
			if(intr_lvl_) {
//				cdeti_task_
//				caci_task_
//				sdaci_task_
				set_interrupt_task(sbfai_task_, static_cast<uint32_t>(SDHI::SBFA_VEC));
			} else {
				set_interrupt_task(nullptr, static_cast<uint32_t>(SDHI::SBFA_VEC));
			}
			device::icu_mgr::set_level(SDHI::PERIPHERAL, intr_lvl_);

			start_ = true;
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
			if(!SDHI::SDSTS1.SDCDMON()) return RES_NOTRDY;
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
			@return SD のステータスを返す。
		 */
		//-----------------------------------------------------------------//
		DSTATUS disk_initialize(BYTE drv) noexcept
		{
			if(drv) {
				return RES_NOTRDY;
			}

			if(!SDHI::SDSTS1.SDCDMON()) {
				return RES_NOTRDY;
			}
#if 0
			debug_format("Start SDHI: disk_initialize\n");
			debug_format("  Version IP1: 0x%02X, IP2: 0x%1X, CLKRAT: %d, CPRM: %d\n")
				% static_cast<uint16_t>(SDHI::SDVER.IP1())
				% static_cast<uint16_t>(SDHI::SDVER.IP2())
				% static_cast<uint16_t>(SDHI::SDVER.CLKRAT())
				% static_cast<uint16_t>(SDHI::SDVER.CPRM());
			debug_format("  SDSIZE: %d\n") % SDHI::SDSIZE();
#endif
			SDHI::SDRST.SDRST = 0;
			using port_map = device::port_map;
			port_map::turn_sdhi(port_map::sdhi_situation::INSERT, PSEL);
			SDHI::SDRST.SDRST = 1;

			if(!set_bus_(true)) {
				return RES_NOTRDY;
			}

			// ダミークロックをが７４個以上入った事を確認する。
			// ※CS(D3) = 1, DI = 1 が「１」の状態である事。
			set_clk_(false);

			SDHI::SDCLKCR.CLKCTRLEN = 0;
			for(uint32_t i = 0; i < 75; ++i) {
				int loop = 0;
				while(device::port_map::probe_sdhi_clock(PSEL) == 0) {
					++loop;
					if(loop >= DUMMY_LOOP_LIMIT) {
						return RES_NOTRDY;
					}
				}
				loop = 0;
				while(device::port_map::probe_sdhi_clock(PSEL) == 1) {
					++loop;
					if(loop >= DUMMY_LOOP_LIMIT) {
						return RES_NOTRDY;
					}
				}
			}
			debug_format("Assert 74 dummy clocks.\n");
			SDHI::SDCLKCR.CLKCTRLEN = 1;

			{
				// CMD0 soft reset
				int loop;
				state ret;
				for(loop = 0; loop < CMD0_LOOP_MAX; ++loop) {
					ret = send_cmd_(command::CMD0, 0);
					if(ret == state::no_error && loop > 0) {
						break;
					}
					utils::delay::milli_second(1);
				}
				if(ret != state::no_error) {
					debug_format("CMD0: Error\n");
					stat_ = STA_NOINIT;
					return stat_;
				}
				debug_format("CMD0: OK (%d)\n") % loop;
			}

			BYTE ty = 0;
			// 0x100: 2.7V to 3.6V condition
			// 0x200: Low range
			// 0x0AA: Check Pattern
			if(send_cmd_(command::CMD8, 0x01AA) == state::no_error) {
				uint32_t res = SDHI::SDRSP10();
				rca_id_ = res & 0xfffff000;
				if((res & 0xfff) != 0x1AA) {  // No Match for SD-V1
					debug_format("CMD8: State Miss Match (%03X)\n") % res;
					stat_ = STA_NOINIT;
					return stat_;
				} else {
					debug_format("CMD8: OK 'SD-V2' RCA: 0x%08X\n") % rca_id_;
					ty = CT_SD2;  // for SD Ver 2.x
				}
			} else {  // Error, No Response for SD-V1, MMC-V3, Error
				// Clear the illegal command error for CMD8
				for(int loop = 0; loop < CMD0_LOOP_MAX; ++loop) {
					if(send_cmd_(command::CMD0, 0) == state::no_error) {
						break;
					} 
				}
				ty = CT_SD1;
				debug_format("CMD8: NG 'SD-V1, MMC-V3 or Fail'\n");
			}

			{  // ACMD41
				int loop;
				uint32_t st = 0;
				uint32_t res = 0;
				uint32_t msd = 1;  // delay for command
				for(loop = 0; loop < ACMD41_LOOP_MAX; ++loop) {
					// HCS: 0x40000000
					uint32_t arg = 0;
					arg |= 0xFF8000;  // 電圧範囲の指定: 2.7～3.6V
					if((ty & CT_SD2) != 0) arg |= 0x40000000;
					// arg |= 0x01000000;  // S18R(B24) 電圧切り替え要求
					// SDHI は 3.3V のみサポート
					if(send_cmd_(command::ACMD41, arg) != state::no_error) {
						debug_format("ACMD41: State Error\n");
						stat_ = STA_NOINIT;
						return stat_;
					} else {
						res = SDHI::SDRSP10();
						if(st != res) {
							st = res;
							debug_format("ACMD41(%d ms): State(0x%08X)\n")
								% static_cast<int>(loop * msd) % res;
						}
						if((res & 0x80000000) != 0) {
							break;
						} else {
							utils::delay::milli_second(msd);
						}
					}
				}
				if(loop < ACMD41_LOOP_MAX) {
					debug_format("ACMD41: OK for %d [ms]\n")
						% static_cast<int>(loop * msd);
				} else {
					debug_format("ACMD41(%d ms): Busy Error: State(0x%08X)\n")
						% static_cast<int>(loop * msd) % res;
					stat_ = STA_NOINIT;
					return stat_;
				}
				if(res & 0x40000000) {
					ty |= CT_BLOCK;
				}
			}

			// 電圧切り替え可能なインターフェースなら、（CMD11）を送って電圧を切り替える。

			// CMD2 (CID) カード識別レジスタ (R2)
			if(send_cmd_(command::CMD2, 0x0) != state::no_error) {
				debug_format("CMD2: Error\n");
				stat_ = STA_NOINIT;
				return stat_;
			} else {
				uint32_t st[4];
				st[3] = SDHI::SDRSP76();
				st[2] = SDHI::SDRSP54();
				st[1] = SDHI::SDRSP32();
				st[0] = SDHI::SDRSP10();

				cid_[0] = (st[3] << 8) | (st[2] >> 24);
				cid_[1] = (st[2] << 8) | (st[1] >> 24);
				cid_[2] = (st[1] << 8) | (st[0] >> 24);
				cid_[3] =  st[0] << 8;
				debug_format("CMD2: OK (%08X, %08X, %08X, %08X)\n")
					% cid_[0] % cid_[1] % cid_[2] % cid_[3];
			}

			{  // CMD3 RCA 読み出し
				int loop;
				for(loop = 0; loop < CMD3_LOOP_MAX; ++loop) {
					if(send_cmd_(command::CMD3, 0) == state::no_error) {
						rca_id_ = SDHI::SDRSP10() & 0xffff0000;
						if(rca_id_ != 0) {
							break;
						}
					}
				}
				if(loop >= CMD3_LOOP_MAX) {
					debug_format("CMD3: Error\n");
					stat_ = STA_NOINIT;
					return stat_;
				}
				debug_format("CMD3: OK (RCA: %08X)\n") % rca_id_;
			}

			bool lock = false;
			{  // CMD7 RCA を使ってカード選択
				if(send_cmd_(command::CMD7, rca_id_) != state::no_error) {
					debug_format("CMD7: Error\n");
					stat_ = STA_NOINIT;
					return stat_;
				} else {
					if((SDHI::SDRSP10() & 0xfdffe008) != 0) {
						lock = true;
					}
					debug_format("CMD7: OK\n");
				}
			}

			if(send_cmd_(command::CMD16, 512) != state::no_error) {
				debug_format("CMD16: Error\n");
				stat_ = STA_NOINIT;
				return stat_;
			}

			if(lock) {
				// カードのロックを外すには、CMD42 が必要
				// その後で ACMD6 を使いバス幅を４ビットと同時にロック解除する。
				// とりあえず、エラーで終了
				debug_format("Card Locked...\n");
				stat_ = STA_NOINIT;
				return stat_;
			}

			{  // change bus width
				uint32_t busarg = onew_ ? 0x00000000 : 0x00000002;
				if(send_cmd_(command::ACMD6, busarg) != state::no_error) {
					debug_format("ACMD6: Error\n");
					stat_ = STA_NOINIT;
					return stat_;
				} else {
					if(busarg) {
						if(!set_bus_(false)) {
							stat_ = STA_NOINIT;
							return stat_;
						}
					}
					debug_format("ACMD6: OK bus = %d bit\n") %
						static_cast<int>(busarg != 0 ? 4 : 1);
				}
			}

			port_map::turn_sdhi(port_map::sdhi_situation::BUS, PSEL);

			card_type_ = ty;
			stat_ = ty ? 0 : STA_NOINIT;

			// Select FAST_CLK
			set_clk_(true);

			if(card_type_ & CT_BLOCK) {
				debug_format("SD: Block mode\n"); 
			}

			// データ読み出し、書き込み時のエンディアン変換を有効にする
#ifdef BIG_ENDIAN
			debug_format("Turn SWAP mode for Big Endian\n");
			SDHI::SDSWAP = SDHI::SDSWAP.BWSWP.b(1) | SDHI::SDSWAP.BRSWP.b(1);
#endif

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
			if(!SDHI::SDSTS1.SDCDMON()) return RES_NOTRDY;
			if(disk_status(drv) & STA_NOINIT) return RES_NOTRDY;

			// Convert LBA to byte address if needed
			if(!(card_type_ & CT_BLOCK)) sector *= 512;

///			utils::format("disk_read: sector: %d, count: %d\n") % sector % count;

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
					debug_format("%s CRC Error (CRCE)\n") % cmdstr;
					return RES_ERROR;
				}
				if(SDHI::SDSTS2.CMDE()) {
					debug_format("%s Command error (CMDE)\n") % cmdstr;
					return RES_ERROR;
				}
				if(SDHI::SDSTS2.RSPTO()) {
					debug_format("%s Response Timeout (RSPTO)\n") % cmdstr;
					return RES_ERROR;
				}
			}
			SDHI::SDSTS1 = 0x0000FFFE;
			auto sp10 = SDHI::SDRSP10();
///			utils::format("%s: Response: %08X\n") % cmdstr % sp10;

			while(count > 0) {

				uint32_t loop = 0;
				while(SDHI::SDSTS2.BRE() == 0) {
					if(loop >= 10000) {
						debug_format("%s time out\n") % cmdstr;
						return RES_ERROR;
					}
					auto st = SDHI::SDSTS2();
					if(st & SDHI::SDSTS2.DTO.b()) {
						debug_format("%s DTO error\n") % cmdstr;
						return RES_ERROR;
					}
					if(st & SDHI::SDSTS2.CRCE.b()) {
						debug_format("%s CRC error\n") % cmdstr;
						return RES_ERROR;
					}
					++loop;
					utils::delay::micro_second(100);
				}

				SDHI::SDSTS2 = 0x0000FEFF;
///				utils::format("%s BRE: OK\n") % cmdstr;

				if((reinterpret_cast<uint32_t>(buff) & 0x3) == 0) {
					uint32_t* p = static_cast<uint32_t*>(buff);
					for(uint32_t n = 0; n < (512 / 4); ++n) {
						*p++ = SDHI::SDBUFR(); 
					}
					buff = static_cast<void*>(p);
				} else {
					uint8_t* p = static_cast<uint8_t*>(buff);
					for(uint32_t n = 0; n < (512 / 4); ++n) {
						uint32_t tmp = SDHI::SDBUFR();
						std::memcpy(p, &tmp, 4);
						p += 4;
					}
					buff = static_cast<void*>(p);
				}
				--count;
			}

///			utils::format("Data trans: OK\n");

			if(!wait_acend_()) {
				debug_format("Read: ACEND time out\n");
				return RES_ERROR;				
			}

			SDHI::SDSTS1 = 0x0000FFFB;
			{
///				auto sp10 = SDHI::SDRSP10();
///				utils::format("Data end: 0x%08X\n") % sp10;
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
			if(!SDHI::SDSTS1.SDCDMON()) return RES_NOTRDY;
			if(disk_status(drv) & STA_NOINIT) return RES_NOTRDY;
			if(WPRT::BIT_POS < 8) {
				if(WPRT::P()) return RES_WRPRT;
			}

			if(!(card_type_ & CT_BLOCK)) sector *= 512;	/* Convert LBA to byte address if needed */

			SDHI::SDSTS1 = 0;
			SDHI::SDSTS2 = 0;
			SDHI::SDSIZE = 512;

			SDHI::SDSTOP   = 0x00000100;  // for multi block
			SDHI::SDBLKCNT = count;  // for multi block read
			SDHI::SDARG    = sector;
			command cmd = count > 1 ? command::CMD25 : command::CMD24;
			const char* cmdstr = cmd == command::CMD25 ? "CMD25" : "CMD24";
			SDHI::SDCMD = static_cast<uint32_t>(cmd);

			while(SDHI::SDSTS1.RSPEND() == 0) {
				if(SDHI::SDSTS2() & (SDHI::SDSTS2.CMDE.b() | SDHI::SDSTS2.RSPTO.b())) {
					return RES_ERROR;
				}
			}
			SDHI::SDSTS1 = 0x0000FFFE;
//			auto sp54 = SDHI::SDRSP54();

			while(count > 0) {

				uint32_t loop = 0;
				while(SDHI::SDSTS2.BWE() == 0) {
					if(loop >= BWE_LOOP_LIMIT) {
						debug_format("%s time out\n") % cmdstr;
						return RES_ERROR;
					}
					auto st = SDHI::SDSTS2();
					if(st & SDHI::SDSTS2.DTO.b()) {
						debug_format("%s DTO error\n") % cmdstr;
						return RES_ERROR;
					}
					if(st & SDHI::SDSTS2.CRCE.b()) {
						debug_format("%s CRC error\n") % cmdstr;
						return RES_ERROR;
					}
					++loop;
					utils::delay::micro_second(100);
				}

				SDHI::SDSTS2 = 0xFDFF;

				if((reinterpret_cast<uint32_t>(buff) & 0x3) == 0) {
					const uint32_t* p = static_cast<const uint32_t*>(buff);
					for(uint32_t n = 0; n < 128; ++n) {
						SDHI::SDBUFR = *p++;
					}
					buff = static_cast<const void*>(p);
				} else {
					const uint8_t* p = static_cast<const uint8_t*>(buff);
					for(uint32_t n = 0; n < 128; ++n) {
						uint32_t tmp;
						std::memcpy(&tmp, p, 4);
						p += 4;
						SDHI::SDBUFR = tmp;
					}
					buff = static_cast<const void*>(p);
				}
				--count;
			}

			if(!wait_acend_()) {
				debug_format("Write: ACEND time out\n");
				return RES_ERROR;				
			}

			SDHI::SDSTS1 = 0x0000FFFB;

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

			debug_format("disk_ioctl: %02X\n") % static_cast<uint16_t>(ctrl);

			DRESULT res = RES_ERROR;
			switch (ctrl) {
			case CTRL_SYNC :		/* Make sure that no pending write process */
///				if(select_()) res = RES_OK;
				break;

			case GET_SECTOR_COUNT:	/* Get number of sectors on the disk (DWORD) */
				if(send_cmd_data_(command::CMD9, 0)) {
					uint8_t csd[16];
					uint32_t* p = reinterpret_cast<uint32_t*>(csd);
					*p++ = SDHI::SDBUFR();
					*p++ = SDHI::SDBUFR();
					*p++ = SDHI::SDBUFR();
					*p++ = SDHI::SDBUFR();
					DWORD cs;
					if((csd[0] >> 6) == 1) {	/* SDC ver 2.00 */
						cs = csd[9] + ((WORD)csd[8] << 8) + ((DWORD)(csd[7] & 63) << 16) + 1;
						*(DWORD*)buff = cs << 10;
					} else {					/* SDC ver 1.XX or MMC */
						BYTE n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
						cs = (csd[8] >> 6) + ((WORD)csd[7] << 2) + ((WORD)(csd[6] & 3) << 10) + 1;
						*(DWORD*)buff = cs << (n - 9);
					}
					res = RES_OK;
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
///				utils::format("Card Detect\n");
				POW::P = 1;  // power ON!
				mount_delay_ = MOUNT_DELAY_FRAME;  // n フレーム後にマウントする
			} else if(!cd && cd_) {
///				utils::format("Card Eject\n");
				f_mount(nullptr, "", 0);
				device::port_map::turn_sdhi(device::port_map::sdhi_situation::EJECT, PSEL);
				POW::P = 0;

				stat_ = STA_NOINIT;
				mount_ = false;
			}
			cd_ = cd;

			if(mount_delay_) {
				--mount_delay_;
				if(mount_delay_ == 0) {
					auto st = f_mount(&fatfs_, "", 0);
					if(st != FR_OK) {
						debug_format("f_mount NG: %d\n") % static_cast<uint32_t>(st);
						POW::P = 0;
						mount_ = false;
					} else {
						debug_format("f_mount OK\n");
						mount_ = true;
					}
				}
			}

			return mount_;
		}


        //-----------------------------------------------------------------//
        /*!
            @brief  カードのマウント状態取得
            @return カードがマウントされたら「true」
         */
        //-----------------------------------------------------------------//
        bool get_mount() const noexcept { return mount_; }
	};

	// テンプレート関数、実態の定義
	template <class SDHI, class POW, class WPRT, device::port_map::option PSEL>
		volatile uint32_t sdhi_io<SDHI, POW, WPRT, PSEL>::i_count_ = 0;
}
