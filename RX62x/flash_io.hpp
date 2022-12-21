#pragma once
//=====================================================================//
/*!	@file
	@brief	RX621/RX62N グループ FLASH 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstring>
#include "common/delay.hpp"
#include "RX62x/flash.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  FLASH 制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class flash_io {
	public:
		static constexpr auto DATA_FLASH_SIZE  = FLASH::DATA_FLASH_SIZE;
		static constexpr auto DATA_FLASH_BLOCK = FLASH::DATA_FLASH_BLOCK;
		static constexpr auto DATA_FLASH_BANK  = FLASH::DATA_FLASH_SIZE / FLASH::DATA_FLASH_BLOCK;
		static constexpr auto DATA_WORD_SIZE   = FLASH::DATA_WORD_SIZE;

	private:
		enum class MODE : uint8_t {
			RD,
			PE,
		};

		MODE	mode_;

		void turn_rd_() noexcept
		{
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
		}

		void turn_pe_() noexcept
		{
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
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		flash_io() noexcept : mode_(MODE::RD)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
		 */
		//-----------------------------------------------------------------//
		void start() noexcept
		{

			FLASH::PCKAR = clock_profile::FCLK / 1'000'000;

//			FLASH::DFLCTL.DFLEN = 1;
			utils::delay::micro_second(5);  // tDSTOP by high speed
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
			if(org >= DATA_FLASH_SIZE) return 0;
	
			turn_rd_();
	
			return rd8_(FLASH::DATA_FLASH_ORG + org);
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
			if(org >= DATA_FLASH_SIZE) return 0;
			if((org + len) > DATA_FLASH_SIZE) {
				len = DATA_FLASH_SIZE - org;
			}
			turn_rd_();
			const void* src = reinterpret_cast<const void*>(FLASH::DATA_FLASH_ORG + org);
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
			if(bank >= DATA_FLASH_BLOCK) {
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
			if(bank >= DATA_FLASH_BLOCK) {
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
			if(org >= DATA_FLASH_SIZE) return false;

			if((org + len) > DATA_FLASH_SIZE) {
				len = DATA_FLASH_SIZE - org;
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
