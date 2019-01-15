#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ FLASH 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstring>
#include "common/delay.hpp"

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
			@brief  データ・フラッシュ構成 @n
					（全体８Ｋバイト、ブロック１０２４バイト、バンク８個）
		*/
		//-----------------------------------------------------------------//
		static const uint32_t data_flash_block = 1024;	///< データ・フラッシュのブロックサイズ
		static const uint32_t data_flash_size  = 8192;  ///< データ・フラッシュの容量
		static const uint32_t data_flash_bank  = 8;		///< データ・フラッシュのバンク数
		static const uint32_t data_flash_word  = 1;		///< データ・フラッシュ書き込みワードサイズ

	private:

		void turn_rd_() const
		{
			if(device::FLASH::FENTRYR.FENTRYD() == 0) return;
			device::FLASH::FENTRYR.FENTRYD = 0;  // read mode

			device::FLASH::FPR = 0xA5;
			device::FLASH::FPMCR =  0x08;
			device::FLASH::FPMCR = ~0x08;
			device::FLASH::FPMCR =  0x08;
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
			uint8_t frq = F_FCLK / 1000000;
			if(frq > 32) frq = 32;
			device::FLASH::FISR.PCKA = frq - 1;
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
		void read(uint16_t org, uint16_t len, void* dst) const
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
			if(bank >= data_flash_bank) {
				return false;
			}

			turn_pe_();

			device::FLASH::FASR.EXS = 0;

			uint32_t org = bank * data_flash_block;
			device::FLASH::FSARH = 0xFE00;
			device::FLASH::FSARL = org;
			device::FLASH::FEARH = 0xFE00;
			device::FLASH::FEARL = org + data_flash_block - 1;

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
			if(bank >= data_flash_bank) {
				return false;
			}

			turn_pe_();

			device::FLASH::FASR.EXS = 0;

			uint16_t org = bank * data_flash_block;
			device::FLASH::FSARH = 0xFE00;
			device::FLASH::FSARL = org;
			device::FLASH::FEARH = 0xFE00;
			device::FLASH::FEARL = org + data_flash_block - 1;

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
		bool write(uint32_t org, const uint8_t* src, uint32_t len) const
		{
			if(org >= data_flash_size) return false;

			if((org + len) > data_flash_size) {
				len = data_flash_size - org;
			}

			turn_pe_();

			device::FLASH::FASR.EXS = 0;

			const uint8_t*p = src;

			bool ret = true;
			uint16_t page = data_flash_size;
			for(uint16_t i = 0; i < len; ++i) {
				if(page != (org & ~(data_flash_block - 1))) {
					device::FLASH::FSARH = 0xFE00;
					device::FLASH::FSARL = org;
					page = org & ~(data_flash_block - 1);
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


		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	org	開始オフセット
			@param[in]	data	書き込みデータ
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool write(uint16_t org, uint8_t data) const
		{
			uint8_t d = data;
			return write(&d, org, 1);
		}

	};
}
