#pragma once
//=========================================================================//
/*!	@file
	@brief	RX220 グループ FLASH 制御 @n
			このファイルは、「renesas.hpp」にインクルードされる前提なので、個別にインクルードしない。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cstring>
#include "common/delay.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  FLASH 制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class flash_io {

		void turn_rd_() const
		{
			if(FLASH::FENTRYR.FENTRYD() == 0) return;
			FLASH::FENTRYR.FENTRYD = 0;  // read mode

			FLASH::FPR = 0xA5;
			FLASH::FPMCR =  0x08;
			FLASH::FPMCR = ~0x08;
			FLASH::FPMCR =  0x08;
			utils::delay::micro_second(3);  // tMS
			device::FLASH::FENTRYR = 0xAA00;
			while(device::FLASH::FENTRYR() != 0) ;
		}

		void turn_pe_() const
		{
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

		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		flash_io() { }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
		 */
		//-----------------------------------------------------------------//
		void start() const
		{
			uint8_t frq = clock_profile::FCLK / 500'000;
			++frq;
			frq >>= 1;
			device::FLASH::PCKAR.PCKA = frq;

			device::FLASH::DFLCTL.DFLEN = 1;
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
		uint8_t read(uint16_t org) const
		{
			if(org >= FLASH::DATA_FLASH_SIZE) return 0;
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
		void read(uint16_t org, uint16_t len, void* dst) const
		{
			if(org >= FLASH::DATA_FLASH_SIZE) return;
			if((org + len) > FLASH::DATA_FLASH_SIZE) {
				len = FLASH::DATA_FLASH_SIZE - org;
			}
			turn_rd_();
			const void* src = reinterpret_cast<const void*>(0x0010'0000 + org);
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
			if(bank >= FLASH::DATA_FLASH_BANK) {
				return false;
			}

			turn_pe_();

			device::FLASH::FASR.EXS = 0;

			uint32_t org = bank * DATA_FLASH_BLOCK;
			device::FLASH::FSARH = 0xFE00;
			device::FLASH::FSARL = org;
			device::FLASH::FEARH = 0xFE00;
			device::FLASH::FEARL = org + DATA_FLASH_BLOCK - 1;

			device::FLASH::FCR = 0x83;
			while(device::FLASH::FSTATR1.FRDY() == 0) ;
			device::FLASH::FCR = 0x00;
			while(device::FLASH::FSTATR1.FRDY() != 0) ;

			bool ret = true;
			if(device::FLASH::FSTATR0.ILGLERR() != 0 || device::FLASH::FSTATR0.ERERR() != 0) {
				ret = false;
			} else {
				device::FLASH::FRESETR.FRESET = 1;
				device::FLASH::FRESETR.FRESET = 0;
			}
			return ret;
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
			if(bank >= FLASH::DATA_FLASH_BANK) {
				return false;
			}

			turn_pe_();

			device::FLASH::FASR.EXS = 0;

			uint16_t org = bank * DATA_FLASH_BLOCK;
			device::FLASH::FSARH = 0xFE00;
			device::FLASH::FSARL = org;
			device::FLASH::FEARH = 0xFE00;
			device::FLASH::FEARL = org + DATA_FLASH_BLOCK - 1;

			device::FLASH::FCR = 0x84;
			while(device::FLASH::FSTATR1.FRDY() == 0) ;
			device::FLASH::FCR = 0x00;
			while(device::FLASH::FSTATR1.FRDY() != 0) ;

			bool ret = true;
			if(device::FLASH::FSTATR0.ILGLERR() != 0 || device::FLASH::FSTATR0.ERERR() != 0) {
				ret = false;
			} else {
				device::FLASH::FRESETR.FRESET = 1;
				device::FLASH::FRESETR.FRESET = 0;
			}
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
		bool write(uint32_t org, const void* src, uint32_t len) const
		{
			if(org >= FLASH::DATA_FLASH_SIZE) return false;

			if((org + len) > DATA_FLASH_SIZE) {
				len = DATA_FLASH_SIZE - org;
			}

			turn_pe_();

			device::FLASH::FASR.EXS = 0;

			const uint8_t*p = static_cast<const uint8_t*>(src);

			bool ret = true;
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
