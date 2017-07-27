#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M グループ FLASH 制御 @n
			・データフラッシュ消去サイズ（６４バイト単位）
			・データフラッシュ書き込みサイズ（４バイト単位）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstring>
#include "common/delay.hpp"
#include "common/format.hpp"

namespace device {

/// F_FCLK は変換パラメーター計算で必要で、設定が無いとエラーにします。
#ifndef F_FCLK
#  error "flash_io.hpp requires F_FCLK to be defined"
#endif

#define FIO_DEBUG

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  FLASH 制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class flash_io {

#ifdef FIO_DEBUG
		typedef utils::format debug_format;
#else
		typedef utils::null_format debug_format;
#endif

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  データ・フラッシュ構成 @n
					（全体６４Ｋバイト、ブロック６４個、バンク１０２４個）
		*/
		//-----------------------------------------------------------------//
		static const uint32_t data_flash_block = 64;     ///< データ・フラッシュのブロックサイズ
		static const uint32_t data_flash_size  = 65536;  ///< データ・フラッシュの容量
		static const uint32_t data_flash_bank  = 1024;   ///< データ・フラッシュのバンク数


		//-----------------------------------------------------------------//
		/*!
			@brief  エラー型
		*/
		//-----------------------------------------------------------------//
		enum class error : uint8_t {
			NONE,		///< エラー無し
			ADDRESS,	///< アドレス・エラー
			TIMEOUT,	///< タイム・アウト・エラー
			LOCK,		///< ロック・エラー
		};

	private:

		enum class mode : uint8_t {
			NONE,
			RD,
			PE
		};

		error	error_;
		mode	mode_;

		bool	trans_farm_;

		/// FACIコマンド発行領域 007E 0000h 4バイト
		static rw8_t<0x007E0000> FACI_CMD_AREA;		///< byte 書き込み

		static rw16_t<0x007E0000> FACI_CMD_AREA16;	///< word(16) 書き込み

		// return 「true」正常、「false」ロック状態
		// 強制終了コマンド
		bool turn_break_() const
		{
			FACI_CMD_AREA = 0xB3;

			// break (4 bytes): FCLK 20MHz to 60MHz max 20us
			//                  FCLK 4MHz max 32us
			// * 1.1
			uint32_t cnt = 22;
			if(F_FCLK < 20000000) cnt = 36;
			while(device::FLASH::FSTATR.FRDY() == 0) {
				utils::delay::micro_second(1);
				--cnt;
				if(cnt == 0) break;
			}
			if(cnt == 0) {
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


		void turn_rd_()
		{
			uint32_t n = 5;
			while(device::FLASH::FSTATR.FRDY() == 0) {
				utils::delay::micro_second(1);
				--n;
				if(n == 0) break;
			} 
			if(n == 0 || device::FLASH::FASTAT.CMDLK() != 0) {
				turn_break_();
			}
		
			device::FLASH::FENTRYR = 0xAA00;

			if(device::FLASH::FENTRYR() != 0x0000) {
				debug_format("FACI 'turn_rd_' fail\n"); 
			}
			mode_ = mode::RD;
		}


		void turn_pe_()
		{
			device::FLASH::FENTRYR = 0xAA80;

			if(device::FLASH::FENTRYR() != 0x0080) {
				debug_format("FACI 'turn_pe_' fail\n");
			}
			mode_ = mode::PE;
		}


		/// FCUファームウェア格納領域 FEFF F000h～FEFF FFFFh 4Kバイト
		/// FCURAM領域 007F 8000h～007F 8FFFh 4Kバイト
		/// コンフィギュレーション設定領域 0012 0040h～0012 007Fh 64バイト
		bool init_fcu_()
		{
			if(trans_farm_) return true;

			if(device::FLASH::FENTRYR() != 0) {
				device::FLASH::FENTRYR = 0xAA00;

				uint32_t wait = 4;
				while(device::FLASH::FENTRYR() != 0) {
					if(wait > 0) {
						--wait;
					} else {
						debug_format("FACI Tras FARM timeout\n");
						return false;
					}
				}
			}

			device::FLASH::FCURAME = 0xC403;  // Write only

			const uint32_t* src = reinterpret_cast<const uint32_t*>(0xFEFFF000);  // Farm master
			uint32_t* dst = reinterpret_cast<uint32_t*>(0x007F8000);  // Farm section
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
			return trans_farm_;
		}


		// 4 バイト書き込み
		// org: align 4 bytes
		bool write32_(const void* src, uint32_t org)
		{
			device::FLASH::FPROTR = 0x5501;
			device::FLASH::FSADDR = org;

			FACI_CMD_AREA = 0xE8;
			FACI_CMD_AREA = 0x02;

			const uint8_t* p = static_cast<const uint8_t*>(src);
			FACI_CMD_AREA16 = (static_cast<uint16_t>(p[1]) << 8) | static_cast<uint16_t>(p[0]);

			while(device::FLASH::FSTATR.DBFULL() != 0) {
				asm("nop");
			}

			FACI_CMD_AREA16 = (static_cast<uint16_t>(p[3]) << 8) | static_cast<uint16_t>(p[2]);

			while(device::FLASH::FSTATR.DBFULL() != 0) {
				asm("nop");
			}

			FACI_CMD_AREA = 0xD0;


			// write (4 bytes): FCLK 20MHz to 60MHz max 1.7ms
			//                  FCLK 4MHz max 3.8ms
			// * 1.1
			uint32_t cnt = 1870;
			if(F_FCLK < 20000000) cnt = 4180;
			while(device::FLASH::FSTATR.FRDY() == 0) {
				utils::delay::micro_second(1);
				--cnt;
				if(cnt == 0) break;
			}
			if(cnt == 0) {  // time out
				turn_break_();
				error_ = error::TIMEOUT;
				debug_format("FACI 'write32_' timeout\n");
				return false;
			}

			if(device::FLASH::FASTAT.CMDLK() != 0) {
				error_ = error::LOCK;
				debug_format("FACI 'write32_' CMD Lock fail\n");
				return false;
			}

			error_ = error::NONE;
			return true;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		flash_io() noexcept : error_(error::NONE), mode_(mode::NONE), trans_farm_(false) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	エラー・ステータスを取得
			@return エラー・ステータス
		 */
		//-----------------------------------------------------------------//
		error get_last_error() const { return error_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@return エラーが無ければ「true」
		 */
		//-----------------------------------------------------------------//
		bool start() noexcept
		{
			if(trans_farm_) return false;  // ファームが既に転送済み

			device::FLASH::FWEPROR.FLWE = 1;

			uint32_t clk = static_cast<uint32_t>(F_FCLK) / 500000;
			if(clk & 1) { clk >>= 1; ++clk; }
			else { clk >>= 1; }
			if(clk > 60) {
				clk = 60;
			}
			device::FLASH::FPCKAR = 0x1E00 | clk;

			init_fcu_();

			error_ = error::NONE;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  読み出し
			@param[in]	org	開始アドレス
			@return データ
		*/
		//-----------------------------------------------------------------//
		uint8_t read(uint32_t org) noexcept
		{
			if(org >= data_flash_size) {
				error_ = error::ADDRESS;
				return 0;
			}

			if(mode_ != mode::RD) {
				turn_rd_();
			}

			error_ = error::NONE;

			return device::rd8_(0x00100000 + org);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  読み出し
			@param[in]	org	開始アドレス
			@param[in]	len	バイト数
			@param[out]	dst	先
		*/
		//-----------------------------------------------------------------//
		bool read(uint32_t org, uint32_t len, void* dst) noexcept
		{
			if(org >= data_flash_size) {
				error_ = error::ADDRESS;
				return false;
			}
			if((org + len) > data_flash_size) {
				len = data_flash_size - org;
			}
			if(mode_ != mode::RD) {
				turn_rd_();
			}

			const void* src = reinterpret_cast<const void*>(0x00100000 + org);
			std::memcpy(dst, src, len);

			error_ = error::NONE;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  消去チェック
			@param[in]	org		開始アドレス
			@param[in]	len		検査長（バイト単位）
			@return 消去されていれば「true」（エラーは「false」）
		*/
		//-----------------------------------------------------------------//
		bool erase_check(uint32_t org, uint32_t len = data_flash_block) noexcept
		{
			if(org >= data_flash_size) {
				error_ = error::ADDRESS;
				return false;
			}

			if(mode_ != mode::PE) {
				turn_pe_();
			}

			device::FLASH::FBCCNT = 0x00;  // address increment
			device::FLASH::FSADDR = org;
			device::FLASH::FEADDR = org + len - 1;

			FACI_CMD_AREA = 0x71;
			FACI_CMD_AREA = 0xD0;

			// erase cheak (4 bytes): FCLK 20MHz to 60MHz max 30us
			//                        FCLK 4MHz max 84us
			// * 1.1
			uint32_t cnt = 33 * 64 / 4;
			if(F_FCLK < 20000000) cnt = 93 * 64 / 4;
			while(device::FLASH::FSTATR.FRDY() == 0) {
				utils::delay::micro_second(1);
				--cnt;
				if(cnt == 0) break;
			}
			if(cnt == 0) {  // time out
				turn_break_();
				error_ = error::TIMEOUT;
				debug_format("FACI 'erase_check' timeout\n");
				return false;
			}

			if(device::FLASH::FASTAT.CMDLK() == 0) {
				return device::FLASH::FBCSTAT.BCST() == 0;
			} else {
				error_ = error::LOCK;
				debug_format("FACI 'erase_check' lock fail\n");
				return false;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  消去
			@param[in]	org		開始アドレス
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool erase(uint32_t org) noexcept
		{
			if(org >= data_flash_size) {
				error_ = error::ADDRESS;
				return false;
			}

			if(mode_ != mode::PE) {
				turn_pe_();
			}

			device::FLASH::FPROTR = 0x5501;  // ロックビットプロテクト無効
			device::FLASH::FCPSR  = 0x0000;  // サスペンド優先
			device::FLASH::FSADDR = org;

			FACI_CMD_AREA = 0x20;
			FACI_CMD_AREA = 0xD0;

			// 64 bytes erase: FCLK 20MHz to 60MHz max 10ms
			//                 FCLK 4MHz max 18ms
			// * 1.1
			uint32_t cnt = 1100;
			if(F_FCLK < 20000000) cnt = 1980;
			while(device::FLASH::FSTATR.FRDY() == 0) {
				utils::delay::micro_second(10);
				--cnt;
				if(cnt == 0) break;
			}

			if(cnt == 0) {  // time out
				turn_break_();
				error_ = error::TIMEOUT;
				debug_format("FACI 'erase' timeout\n");
				return false;
			}

			if(device::FLASH::FASTAT.CMDLK() == 0) {
				error_ = error::NONE;
				return true;
			} else {
				error_ = error::LOCK;
				debug_format("FACI 'erase' lock fail\n");
				return false;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み @n
					※仕様上、４バイト単位で書き込まれる。@n
					※４バイト未満の場合は、０ｘＦＦが書き込まれる
			@param[in]	org	開始オフセット
			@param[in]	src ソース
			@param[in]	len	バイト数
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool write(uint32_t org, const void* src, uint32_t len) noexcept
		{
			if(org >= data_flash_size) {
				error_ = error::ADDRESS;
				return false;
			}

			if((org + len) > data_flash_size) {
				len = data_flash_size - org;
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

			if(f) {
				error_ = error::NONE;
			}

			return f;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	org	開始オフセット
			@param[in]	data	書き込みデータ
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool write(uint32_t org, uint8_t data) noexcept
		{
			uint8_t d = data;
			return write(org, &d, 1);
		}
	};
}
