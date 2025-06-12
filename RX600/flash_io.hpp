#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600/RX700 グループ FLASH 制御 @n
			RX64M/RX71M/RX65[1N]/RX66N/RX66T/RX72T/RX72M/RX72N @n
			・データフラッシュ消去サイズ（６４バイト単位） @n
			・データフラッシュ書き込みサイズ（４バイト単位） @n
			このファイルは、「renesas.hpp」にインクルードされる前提なので、個別にインクルードしない。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cstring>
#include "RX600/flash_io_base.hpp"
#include "common/delay.hpp"

// デバッグ・メッセージを表示する場合有効にする
#define FIO_DEBUG

#ifdef FIO_DEBUG
#include "common/format.hpp"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  FLASH 制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class flash_io : public flash_io_base {

#ifdef FIO_DEBUG
		typedef utils::format debug_format;
#else
		typedef utils::null_format debug_format;
#endif

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  データ・フラッシュ構成
		*/
		//-----------------------------------------------------------------//
		static constexpr uint32_t DATA_SIZE  = FLASH::DATA_SIZE;	///< データ・フラッシュの容量
		static constexpr uint32_t DATA_BLANK_SIZE = FLASH::DATA_BLANK_SIZE;	///< データ・フラッシュのブロックサイズ
		static constexpr uint32_t DATA_BLANK_NUM  = FLASH::DATA_SIZE / DATA_BLANK_SIZE;	///< データ・フラッシュのバンク数
		static constexpr uint32_t DATA_ERASE_SIZE = FLASH::DATA_ERASE_SIZE;	///< データ・フラッシュのブロックサイズ
		static constexpr uint32_t DATA_ERASE_NUM  = FLASH::DATA_SIZE / DATA_ERASE_SIZE;	///< データ・フラッシュのバンク数
	
	private:

		static constexpr uint32_t MODE_CHANGE_DELAY = 10;	///< モード変更における遅延

		enum class mode : uint8_t {
			NONE,
			RD,
			PE
		};

		/// FACI シーケンサ・コマンド
		enum class FACI : uint8_t {
			WRITE_TOP = 0xE8,		///< プログラム(データフラッシュメモリ) 4バイトプログラム
			WRITE_FIN = 0xD0,		///< プログラム(データフラッシュメモリ) 4バイトプログラム 最終コマンド
			ERASE1 = 0x20,			///< 1st ブロックイレーズ (データフラッシュメモリ 64バイト)
			ERASE2 = 0xD0,			///< 2nd ブロックイレーズ (データフラッシュメモリ 64バイト)
			CLEAR_STATUS = 0x50,	///< ステータスクリア
			BREAK = 0xB3,			///< 強制終了
			CHECK_BLANK1 = 0x71,	///< 1st ブランクチェック
			CHECK_BLANK2 = 0xD0,	///< 2nd ブランクチェック
		};

		ERROR	error_;
		mode	mode_;
		bool	trans_farm_;

		inline void faci_cmd_(FACI cmd) const noexcept
		{
			FLASH::FACI_CMD_AREA = static_cast<uint8_t>(cmd);
		}

		inline void faci_cmd_(FACI cmd1, FACI cmd2) noexcept
		{
			FLASH::FACI_CMD_AREA = static_cast<uint8_t>(cmd1);
			FLASH::FACI_CMD_AREA = static_cast<uint8_t>(cmd2);
		}

		// return 「true」正常、「false」ロック状態
		// 強制終了コマンド
		bool turn_break_() const noexcept
		{
			faci_cmd_(FACI::BREAK);

			// break (4 bytes): FCLK 20MHz to 60MHz max 20us
			//                  FCLK 4MHz max 32us
			// * 1.1
			uint32_t loop = 22;
			if(clock_profile::FCLK < 20'000'000) {
				loop += loop;
			}
			while(device::FLASH::FSTATR.FRDY() == 0) {
				utils::delay::micro_second(1);
				--loop;
				if(loop == 0) break;
			}
			if(loop == 0) {
				debug_format("FACI 'turn_break_' timeout\n");
				return false;
			}

			if(device::FLASH::FASTAT.CMDLK() == 0) {
				return true;
			} else {
				debug_format("FACI 'turn_break_' fail\n");
				return false;
			}
		}

		void turn_rd_() noexcept
		{
			uint32_t loop = 15;
			while(device::FLASH::FSTATR.FRDY() == 0) {
				utils::delay::micro_second(1);
				--loop;
				if(loop == 0) break;
			} 
			if(loop == 0 || device::FLASH::FASTAT.CMDLK() != 0) {
				turn_break_();
			}
		
			device::FLASH::FENTRYR = 0xAA00;
			utils::delay::micro_second(MODE_CHANGE_DELAY);
			if(device::FLASH::FENTRYR() != 0x0000) {
				debug_format("FACI 'RD' not ready: 'turn_rd_'\n"); 
			}
			mode_ = mode::RD;
		}

		bool turn_pe_() noexcept
		{
			uint32_t n = 100;  // 最大１００マイクロ秒待つ
			while(device::FLASH::FSTATR.FRDY() == 0) {
				utils::delay::micro_second(1);
				--n;
				if(n == 0) {
					debug_format("FACI not ready: 'turn_pe_'\n");
					return false;
				}
			}

			device::FLASH::FENTRYR = 0xAA80;
			utils::delay::micro_second(MODE_CHANGE_DELAY);
			if(device::FLASH::FENTRYR() == 0x0080) {
				mode_ = mode::PE;
				return true;
			} else {
				debug_format("FACI 'P/E' not ready: 'turn_pe_'\n");
				return false;
			}
		}

		bool init_fcu_() noexcept
		{
			if(trans_farm_) return true;

#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX651)
			/// RX64M, RX71M, RX65x では、ファームを転送する必要がある。
			/// FCUファームウェア格納領域 FEFF F000h～FEFF FFFFh 4Kバイト
			/// FCURAM領域 007F 8000h～007F 8FFFh 4Kバイト
			/// コンフィギュレーション設定領域 0012 0040h～0012 007Fh 64バイト
			if(device::FLASH::FENTRYR() != 0) {
				device::FLASH::FENTRYR = 0xAA00;

				uint32_t wait = 4;
				while(device::FLASH::FENTRYR() != 0) {
					utils::delay::micro_second(1);
					if(wait > 0) {
						--wait;
					} else {
						debug_format("FACI Tras FARM timeout\n");
						return false;
					}
				}
			}

			device::FLASH::FCURAME = 0xC403;  // Write only

			const uint32_t* src = reinterpret_cast<const uint32_t*>(0xFEFF'F000);  // Farm master
			uint32_t* dst = reinterpret_cast<uint32_t*>(0x007F'8000);  // Farm section
			for(uint32_t i = 0; i < (4096 / 4); ++i) {
				*dst++ = *src++;
			}
			device::FLASH::FCURAME = 0xC400;

			turn_pe_();

			auto f = turn_break_();			
			if(f) {
				turn_rd_();
				trans_farm_ = true;
			} else {
				turn_break_();
				debug_format("FACI Tras FARM lock\n");
			}
#else
			trans_farm_ = turn_pe_();
#endif
			return trans_farm_;
		}

		// 4 バイト書き込み
		// org: align 4 bytes
		bool write32_(const void* src, uint32_t org) noexcept
		{
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX66T) || defined(SIG_RX72T)
			device::FLASH::FPROTR = 0x5501;
#endif
			device::FLASH::FSADDR = org;

			faci_cmd_(FACI::WRITE_TOP);
			FLASH::FACI_CMD_AREA = 0x02;  // 書き込み数

			const uint8_t* p = static_cast<const uint8_t*>(src);
			FLASH::FACI_CMD_AREA16 = (static_cast<uint16_t>(p[1]) << 8) | static_cast<uint16_t>(p[0]);

			while(device::FLASH::FSTATR.DBFULL() != 0) {
				asm("nop");
			}

			FLASH::FACI_CMD_AREA16 = (static_cast<uint16_t>(p[3]) << 8) | static_cast<uint16_t>(p[2]);

			while(device::FLASH::FSTATR.DBFULL() != 0) {
				asm("nop");
			}
			faci_cmd_(FACI::WRITE_FIN);

			auto loop = FLASH::WRITE_WORD_TIME;
			if(clock_profile::FCLK < 20'000'000) {
				loop += loop;
			}
			loop += loop / 10;  // x 1.1
			while(device::FLASH::FSTATR.FRDY() == 0) {
				utils::delay::micro_second(1);
				--loop;
				if(loop == 0) break;
			}
			if(loop == 0) {  // time out
				turn_break_();
				error_ = ERROR::TIMEOUT;
				debug_format("FACI 'write32_' timeout\n");
				return false;
			}

			if(device::FLASH::FASTAT.CMDLK() != 0) {
				turn_break_();
				error_ = ERROR::LOCK;
				debug_format("FACI 'write32_' write error: 0x%04X\n") % org;
				return false;
			}

			error_ = ERROR::NONE;
			return true;
		}

		bool erase_check_(uint32_t ofs, uint32_t len) noexcept
		{
			if(mode_ != mode::PE) {
				turn_pe_();
			}

			device::FLASH::FBCCNT = 0x00;  // address increment
			device::FLASH::FSADDR = ofs;
			device::FLASH::FEADDR = ofs + len - FLASH::DATA_WORD_SIZE;

			faci_cmd_(FACI::CHECK_BLANK1, FACI::CHECK_BLANK2);

			auto loop = FLASH::CHECK_WORD_TIME * len / FLASH::DATA_WORD_SIZE;
			if(clock_profile::FCLK < 20'000'000) {
				loop += loop;
			}
			loop += loop / 10;  // x 1.1
			while(device::FLASH::FSTATR.FRDY() == 0) {
				utils::delay::micro_second(1);
				--loop;
				if(loop == 0) break;
			}
			if(loop == 0) {  // time out
				turn_break_();
				error_ = ERROR::TIMEOUT;
				debug_format("FACI 'erase_check' timeout\n");
				return false;
			}

			if(device::FLASH::FASTAT.CMDLK() != 0) {
				turn_break_();
				error_ = ERROR::LOCK;
				debug_format("FACI 'erase_check' lock fail\n");
				return false;
			}

			return device::FLASH::FBCSTAT.BCST() == 0;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		flash_io() noexcept : error_(ERROR::NONE), mode_(mode::NONE), trans_farm_(false) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	エラー・ステータスを取得
			@return エラー・ステータス
		 */
		//-----------------------------------------------------------------//
		auto get_last_error() const noexcept { return error_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@return エラーが無ければ「true」
		 */
		//-----------------------------------------------------------------//
		bool start() noexcept
		{
			error_ = ERROR::NONE;

			if(trans_farm_) return false;  // ファームが既に転送済み

			device::FLASH::FWEPROR = 0b01;  // プロテクトを解除

			// クロック速度の最適化
			auto clk = ((static_cast<uint32_t>(clock_profile::FCLK) / 500'000) + 1) >> 1;
			if(clk > 60) {
				clk = 60;
			}
			debug_format("FCLK base: %d MHz\n") % clk;
			device::FLASH::FPCKAR = 0x1E00 | clk;

			auto state = init_fcu_();
			if(!state) {
				error_ = ERROR::START;
				debug_format("'init_fcu_' fail\n");
			}

			return state;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  １バイトの読み出し
			@param[in]	org	開始アドレス
			@return データ
		*/
		//-----------------------------------------------------------------//
		uint8_t read(uint32_t org) noexcept
		{
			error_ = ERROR::NONE;

			if(org >= DATA_SIZE) {
				error_ = ERROR::ADDRESS;
				return 0;
			}

			if(mode_ != mode::RD) {
				turn_rd_();
			}

			return device::rd8_(0x00100000 + org);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  読み出し
			@param[in]	org	開始アドレス
			@param[out]	dst	先
			@param[in]	len	バイト数
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool read(uint32_t org, void* dst, uint32_t len) noexcept
		{
			error_ = ERROR::NONE;

			if(org >= DATA_SIZE) {
				error_ = ERROR::ADDRESS;
				return false;
			}
			if((org + len) > DATA_SIZE) {
				len = DATA_SIZE - org;
			}
			if(mode_ != mode::RD) {
				turn_rd_();
			}

			const void* src = reinterpret_cast<const void*>(0x00100000 + org);
			std::memcpy(dst, src, len);

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  消去チェック（ワード単位） @n
					ワード単位は、各マイコンにより異なる。 @n
					FLASH::DATA_WORD_SIZE を参照
			@param[in]	adrs	アドレス
			@return 消去されていれば「true」（エラーは「false」）
		*/
		//-----------------------------------------------------------------//
		bool erase_check_w(uint32_t adrs) noexcept
		{
			error_ = ERROR::NONE;

			if(adrs >= DATA_SIZE) {
				error_ = ERROR::ADDRESS;
				return false;
			}

			return erase_check_(adrs, FLASH::DATA_WORD_SIZE);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  消去チェック（バンク単位）
			@param[in]	bank	バンク
			@return 消去されていれば「true」（エラーは「false」）
		*/
		//-----------------------------------------------------------------//
		bool erase_check(uint32_t bank) noexcept
		{
			error_ = ERROR::NONE;

			if(bank >= DATA_BLANK_NUM) {
				error_ = ERROR::BANK;
				return false;
			}

			return erase_check_(bank * DATA_BLANK_SIZE, DATA_BLANK_SIZE);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  消去
			@param[in]	bank	開始アドレス
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool erase(uint32_t bank) noexcept
		{
			error_ = ERROR::NONE;

			if(bank >= DATA_ERASE_NUM) {
				error_ = ERROR::BANK;
				return false;
			}

			if(mode_ != mode::PE) {
				turn_pe_();
			}

#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX66T) || defined(SIG_RX72T)
			device::FLASH::FPROTR = 0x5501;  // ロックビットプロテクト無効
#endif
			device::FLASH::FCPSR  = 0x0000;  // サスペンド優先
			device::FLASH::FSADDR = bank * DATA_ERASE_SIZE;

			faci_cmd_(FACI::ERASE1, FACI::ERASE2);

			auto loop = FLASH::ERASE_BLOCK_TIME;
			if(device::clock_profile::FCLK < 20'000'000) {
				loop += loop;
			}
			loop += loop / 10;  // x 1.1
			while(device::FLASH::FSTATR.FRDY() == 0) {
				utils::delay::micro_second(1);
				--loop;
				if(loop == 0) break;
			}

			if(loop == 0) {  // time out
				turn_break_();
				error_ = ERROR::TIMEOUT;
				debug_format("FACI 'erase' timeout\n");
				return false;
			}

			if(device::FLASH::FASTAT.CMDLK() == 0) {
				return true;
			} else {
				turn_break_();
				error_ = ERROR::LOCK;
				debug_format("FACI 'erase' lock fail\n");
				return false;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  全消去
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool erase_all() noexcept
		{
			for(uint32_t pos = 0; pos < DATA_SIZE; pos += DATA_BLANK_SIZE) {
				if(!erase_check(pos)) {
					auto ret = erase(pos);
					if(!ret) {
						return false;
					}
				}
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み @n
					※仕様上、４バイト単位で書き込まれる。@n
					※４バイト未満の場合は、０ｘＦＦが書き込まれる
			@param[in]	org	開始アドレス
			@param[in]	src ソース
			@param[in]	len	バイト数
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool write(uint32_t org, const void* src, uint32_t len) noexcept
		{
			error_ = ERROR::NONE;

			if(org >= DATA_SIZE || (org & 0x03) != 0) {
				error_ = ERROR::ADDRESS;
				return false;
			}

			if((org + len) > DATA_SIZE) {
				len = DATA_SIZE - org;
			}

			if(mode_ != mode::PE) {
				turn_pe_();
			}

			const uint8_t* p = static_cast<const uint8_t*>(src);
			bool f = false;
			int32_t l = static_cast<int32_t>(len);
			while(l > 0) {
				uint32_t mod = org & 3;
				if(mod != 0) {
					uint8_t tmp[4];
					tmp[0] = 0xFF;
					tmp[1] = 0xFF;
					tmp[2] = 0xFF;
					tmp[3] = 0xFF;
					l -= 4 - mod;
					while(mod < 3) {
						tmp[mod] = *p++;
						++mod;
					}
					org &= 0xFFFFFFFC;
					f = write32_(tmp, org);
				} else {
					f = write32_(p, org);
					p += 4;
					l -= 4;
				}
				if(!f) break;
				org += 4;
			}

			return f;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ユニーク ID 数を取得 @n
					RX64M などユニーク ID をサポートしない場合は「０」が返る。
			@return ユニーク ID 数
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static uint32_t get_uid_num() noexcept
		{
			return FLASH::ID_NUM;
		} 


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ユニーク ID の取得 @no
					RX64M などユニーク ID をサポートしない場合、特定の ROM 領域を返す。 
			@param[in]	idx		ID 番号（０～３）
			@return ID 値
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static uint32_t get_uid(uint32_t idx) noexcept
		{
			switch(idx) {
			case 0:
				return FLASH::UIDR0();
			case 1:
				return FLASH::UIDR1();
			case 2:
				return FLASH::UIDR2();
			case 3:
				return FLASH::UIDR3();
			default:
				return 0;
			}
		}
	};
}
