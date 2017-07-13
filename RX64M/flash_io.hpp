#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M グループ FLASH 制御
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

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  FLASH 制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class flash_io {

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  データ・フラッシュ構成（全体６４Ｋバイト、ブロック６４バイト）
		*/
		//-----------------------------------------------------------------//
		static const uint32_t data_flash_block = 64;     ///< データ・フラッシュのブロックサイズ
		static const uint32_t data_flash_size  = 65536;  ///< データ・フラッシュの容量
		static const uint32_t data_flash_bank  = 1024;   ///< データ・フラッシュのバンク数

	private:
		bool	trans_farm_;

		/// FACIコマンド発行領域 007E 0000h 4バイト
		static rw8_t<0x007E0000> FACI_CMD_AREA;		///< byte 書き込み

		static rw16_t<0x007E0000> FACI_CMD_AREA16;	///< word(16) 書き込み

		// return 「true」正常、「false」ロック状態
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
#ifndef NDEBUG
				utils::format("FACI 'turn_break_' timeout\n");
#endif
				return false;
			}

			if(device::FLASH::FASTAT.CMDLK() == 0) {
				return true;
			} else {
#ifndef NDEBUG
				utils::format("FACI 'turn_break_' fail\n");
#endif
				return false;
			}
		}


		void turn_rd_() const
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
#ifndef NDEBUG
				utils::format("FACI 'turn_rd_' fail\n"); 
#endif
			}
		}


		void turn_pe_() const
		{
			device::FLASH::FENTRYR = 0xAA80;

			if(device::FLASH::FENTRYR() != 0x0080) {
#ifndef NDEBUG
				utils::format("FACI 'turn_pe_' fail\n"); 
#endif
			}
		}


		/// FCUファームウェア格納領域 FEFF F000h～FEFF FFFFh 4Kバイト
		/// FCURAM領域 007F 8000h～007F 8FFFh 4Kバイト
		/// コンフィギュレーション設定領域 0012 0040h～0012 007Fh 64バイト
		void init_fcu_()
		{
			if(trans_farm_) return;

			if(device::FLASH::FENTRYR() != 0) {
				device::FLASH::FENTRYR = 0xAA00;
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
#ifndef NDEBUG
				utils::format("FACI Lock...\n");
#endif
			}
		}


		// 4 バイト書き込み
		// org: align 4 bytes
		bool write32_(const void* src, uint32_t org) const
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
#ifndef NDEBUG
				utils::format("FACI 'write32_' timeout\n");
#endif
				return false;
			}

			if(device::FLASH::FASTAT.CMDLK() != 0) {
#ifndef NDEBUG
				utils::format("FACI 'write32_' CMD Lock fail\n");
#endif
				return false;
			}
			return true;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		flash_io() : trans_farm_(false) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
		 */
		//-----------------------------------------------------------------//
		void start()
		{
			device::FLASH::FWEPROR.FLWE = 1;
			init_fcu_();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  読み出し
			@param[in]	org	開始アドレス
			@return データ
		*/
		//-----------------------------------------------------------------//
		uint8_t read(uint32_t org) const
		{
			if(org >= data_flash_size) return 0;
			turn_rd_();
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
		void read(uint32_t org, uint32_t len, void* dst) const
		{
			if(org >= data_flash_size) return;
			if((org + len) > data_flash_size) {
				len = data_flash_size - org;
			}
			turn_rd_();
			const void* src = reinterpret_cast<const void*>(0x00100000 + org);
			std::memcpy(dst, src, len);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  消去チェック
			@param[in]	bank	バンク
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool erase_check(uint32_t bank) const
		{
			if(bank >= data_flash_bank) return false;

			device::FLASH::FBCCNT = 0x00;  // address increment
			device::FLASH::FSADDR =  bank * data_flash_block;
			device::FLASH::FEADDR = ((bank + 1) * data_flash_block) - 1;

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
#ifndef NDEBUG
				utils::format("FACI 'erase_check' timeout\n");
#endif
				return false;
			}

			if(device::FLASH::FASTAT.CMDLK() == 0) {
				if(device::FLASH::FBCSTAT.BCST() != 0) {
					utils::format("FACI 'erase_check' blank check fail: %04X\n") % device::FLASH::FPSADDR();
					return false;
				}
			} else {
#ifndef NDEBUG
				utils::format("FACI 'erase_check' fail\n");
#endif
				return false;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  消去
			@param[in]	bank	バンク
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool erase(uint32_t bank) const
		{
			if(bank >= data_flash_bank) return false;

			turn_pe_();

			device::FLASH::FPROTR = 0x5501;
			device::FLASH::FCPSR  = 0x0000;  // サスペンド優先
			device::FLASH::FSADDR = bank * data_flash_block;

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
#ifndef NDEBUG
				utils::format("FACI 'erase' timeout\n");
#endif
				return false;
			}

			if(device::FLASH::FASTAT.CMDLK() == 0) {
				return true;
			} else {
#ifndef NDEBUG
				utils::format("FACI 'erase' fail\n");
#endif
				return false;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	src ソース
			@param[in]	org	開始オフセット
			@param[in]	len	バイト数（４の倍数）
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool write(const void* src, uint32_t org, uint32_t len) const
		{
///			if((len & 3) != 0 || (org & 3) != 0) return false;

			if(org >= data_flash_size) return false;

			if((org + len) > data_flash_size) {
				len = data_flash_size - org;
			}

			turn_pe_();

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


		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	org	開始オフセット
			@param[in]	data	書き込みデータ
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool write(uint32_t org, uint8_t data) const
		{
			uint8_t d = data;
			return write(&d, org, 1);
		}
	};
}
