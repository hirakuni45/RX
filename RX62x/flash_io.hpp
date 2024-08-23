#pragma once
//=========================================================================//
/*!	@file
	@brief	RXv1 グループ FLASH 制御 @n
			・RX621/RX62N @n
			・RX631/RX63N @n
			このファイルは、「renesas.hpp」でインクルードされる前提なので、 @n
			個別にインクルードしない事。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cstring>
#include "common/delay.hpp"
#include "common/format.hpp"

#define FIO_DEBUG

namespace device {

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
		static constexpr uint32_t DATA_SIZE = FLASH::DATA_SIZE;	///< データ・フラッシュの容量
		static constexpr uint32_t DATA_BLOCK_SIZE = FLASH::DATA_BLOCK_SIZE;	///< データ・フラッシュのブロックサイズ
		static constexpr uint32_t DATA_BLOCK_NUM  = FLASH::DATA_SIZE / DATA_BLOCK_SIZE;	///< データ・フラッシュのバンク数

	private:
		enum class MODE : uint8_t {
			NONE,
			RD,
			PE,
		};

		MODE	mode_;

		bool	trans_farm_;

		enum class FCU_CMD : uint8_t {
			NORMAL,		///< ノーマルモード移行
			ST_READ,	///< ステータスリードモード移行
			LKB_READ,	///< ロックビットリードモード移行
			SET_CLOCK,	///< 周辺クロック通知
		};

		void step_frdy_(uint32_t timeout_ms) noexcept
		{
			while(FLASH::FSTATR0.FRDY() == 0) {
				utils::delay::micro_second(1);
				--timeout_ms;
				if(timeout_ms == 0) {
					debug_format("FRDY timeout. FCU initialize...\n");
					// FCU 初期化
					
				}
			}
		}


		void fcu_cmd_(FCU_CMD cmd) noexcept
		{
			switch(cmd) {
			case FCU_CMD::SET_CLOCK:
				FLASH::PCKAR = clock_profile::FCLK / 1'000'000;
				FLASH::FCU_DATA_CMD8 = 0xE9;
				FLASH::FCU_DATA_CMD8 = 0x03;
				FLASH::FCU_DATA_CMD16 = 0x0F0F;
				FLASH::FCU_DATA_CMD16 = 0x0F0F;
				FLASH::FCU_DATA_CMD16 = 0x0F0F;
				FLASH::FCU_DATA_CMD8 = 0xD0;
				step_frdy_(clock_profile::FCLK / 1'000'000 * 60);
				break;
			default:
				break;
			}
		}


		bool turn_break_() const noexcept
		{
#if 0
			faci_cmd_(FACI::BREAK);

			// break (4 bytes): FCLK 20MHz to 60MHz max 20us
			//                  FCLK 4MHz max 32us
			// * 1.1
			uint32_t cnt = 22;
			if(clock_profile::FCLK < 20000000) cnt = 36;
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
#endif
			return true;
		}

		void turn_rd_() noexcept
		{
			if(mode_ == MODE::RD) {
				return;
			}
#if 0
			if(FLASH::FENTRYR.FENTRYD() == 0) return;
			FLASH::FENTRYR.FENTRYD = 0;  // read mode

			FLASH::FPR = 0xA5;
			FLASH::FPMCR =  0x08;
			FLASH::FPMCR = ~0x08;
			FLASH::FPMCR =  0x08;
			utils::delay::micro_second(3);  // tMS
			device::FLASH::FENTRYR = 0xAA00;
			while(device::FLASH::FENTRYR() != 0) ;
#endif
			mode_ = MODE::RD;
		}

		void turn_pe_() noexcept
		{
			if(mode_ == MODE::PE) {
				return;
			}
#if 0
			if(device::FLASH::FENTRYR.FENTRYD() != 0) return;
			device::FLASH::FENTRYR.FENTRYD = 1;  // P/E mode

			device::FLASH::FENTRYR = 0xAA80;
			utils::delay::micro_second(5);  // tDSTOP
			if(device::SYSTEM::OPCCR.OPCM() == 0) {
				device::FLASH::FPR = 0xA5;
				device::FLASH::FPMCR =  0x10;
				device::FLASH::FPMCR = ~0x10;
				device::FLASH::FPMCR =  0x10;
			} else {
				device::FLASH::FPR = 0xA5;
				device::FLASH::FPMCR =  0x50;
				device::FLASH::FPMCR = ~0x50;
				device::FLASH::FPMCR =  0x50;
			}
			uint8_t frq = clock_profile::FCLK / 1000000;
			if(frq > 32) frq = 32;
			device::FLASH::FISR.PCKA = frq - 1;
#endif
			mode_ = MODE::PE;
		}

		bool init_fcu_() noexcept
		{
			if(trans_farm_) return true;

			uint8_t frq = clock_profile::FCLK / 500'000;
			++frq;
			frq >>= 1;
			FLASH::PCKAR.PCKA = frq;

#if 0
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
#endif
			return trans_farm_;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		flash_io() noexcept : mode_(MODE::NONE), trans_farm_(false)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
		 */
		//-----------------------------------------------------------------//
		void start() noexcept
		{
			fcu_cmd_(FCU_CMD::SET_CLOCK);

			init_fcu_();

			turn_rd_();
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
			if(org >= DATA_SIZE) return 0;
	
			turn_rd_();
	
			return rd8_(FLASH::DATA_ORG + org);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  読み出し
			@param[in]	org	開始アドレス
			@param[in]	len	バイト数
			@param[out]	dst	先
			@return 読出しサイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t read(uint32_t org, uint32_t len, void* dst) noexcept
		{
			if(org >= DATA_SIZE) return 0;
			if((org + len) > DATA_SIZE) {
				len = DATA_SIZE - org;
			}
			turn_rd_();
			const void* src = reinterpret_cast<const void*>(FLASH::DATA_ORG + org);
			std::memcpy(dst, src, len);
			return len;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  消去チェック
			@param[in]	bank	バンク
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool erase_check(uint32_t bank) noexcept
		{
			if(bank >= DATA_BLOCK_NUM) {
				return false;
			}

			turn_pe_();

			bool ret = true;






			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  消去
			@param[in]	bank	バンク
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool erase(uint32_t bank) noexcept
		{
			if(bank >= DATA_BLOCK_NUM) {
				return false;
			}

			turn_pe_();

			bool ret = true;






			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	src ソース
			@param[in]	org	開始オフセット
			@param[in]	len	バイト数
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool write(uint32_t org, const void* src, uint32_t len) noexcept
		{
			if(org >= DATA_SIZE) return false;

			if((org + len) > DATA_SIZE) {
				len = DATA_SIZE - org;
			}

			turn_pe_();

			bool ret = true;
#if 0
			device::FLASH::FASR.EXS = 0;

			const uint8_t*p = static_cast<const uint8_t*>(src);

			uint16_t page = DATA_FLASH_SIZE;
			for(uint16_t i = 0; i < len; ++i) {
				if(page != (org & ~(DATA_FLASH_BLOCK - 1))) {
					device::FLASH::FSARH = 0xFE00;
					device::FLASH::FSARL = org;
					page = org & ~(DATA_FLASH_BLOCK - 1);
				}
				device::FLASH::FWB0 = *p++;
				device::FLASH::FCR = 0x81;
				while(device::FLASH::FSTATR1.FRDY() == 0) ;
				device::FLASH::FCR = 0x00;
				while(device::FLASH::FSTATR1.FRDY() != 0) ;

				if(device::FLASH::FSTATR0.ILGLERR() != 0 || device::FLASH::FSTATR0.ERERR() != 0) {
					ret = false;
					break;
				}
				++org;
			}
			if(ret) { 
				device::FLASH::FRESETR.FRESET = 1;
				device::FLASH::FRESETR.FRESET = 0;
			}
#endif
			return ret;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ユニーク ID 数を取得 @n
					ユニーク ID をサポートしない場合は「０」が返る。
			@return ユニーク ID 数
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static uint32_t get_uid_num() noexcept
		{
			return FLASH::ID_NUM;
		} 


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ユニーク ID の取得 @n
					ユニーク ID をサポートしない場合、特定の ROM 領域を返す。 @n
					各マイコン「flash.hpp」を参照 
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
