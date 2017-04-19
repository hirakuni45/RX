#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ FLASH 制御 @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstring>
#include "common/delay.hpp"

namespace device {

/// F_CLK は変換パラメーター計算で必要で、設定が無いとエラーにします。
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
		static const uint16_t data_flash_block_ = 1024;
		static const uint16_t data_flash_size_  = 8192;

		//-----------------------------------------------------------------//
		/*!
			@brief  データ・バンク定義（全体８Ｋバイト、ブロック１Ｋバイト）
		*/
		//-----------------------------------------------------------------//
		enum class data_area {
			bank0,	///< 0x00100000 to 0x001003FF (1024)
			bank1,	///< 0x00100400 to 0x001007FF (1024)
			bank2,	///< 0x00100800 to 0x00100BFF (1024)
			bank3,	///< 0x00100C00 to 0x00100FFF (1024)
			bank4,	///< 0x00101000 to 0x001013FF (1024)
			bank5,	///< 0x00101400 to 0x001017FF (1024)
			bank6,	///< 0x00101800 to 0x00101BFF (1024)
			bank7,	///< 0x00101C00 to 0x00101FFF (1024)
		};

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
			if(org >= data_flash_size_) return 0;
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
			if(org >= data_flash_size_) return;
			if((org + len) > data_flash_size_) {
				len = data_flash_size_ - org;
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
		bool erase_check(data_area bank) const
		{
			turn_pe_();

			device::FLASH::FASR.EXS = 0;

			uint16_t org = static_cast<uint16_t>(bank) * data_flash_block_;
			device::FLASH::FSARH = 0xFE00;
			device::FLASH::FSARL = org;
			device::FLASH::FEARH = 0xFE00;
			device::FLASH::FEARL = org + data_flash_block_ - 1;

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
		bool erase(data_area bank) const
		{
			turn_pe_();

			device::FLASH::FASR.EXS = 0;

			uint16_t org = static_cast<uint16_t>(bank) * data_flash_block_;
			device::FLASH::FSARH = 0xFE00;
			device::FLASH::FSARL = org;
			device::FLASH::FEARH = 0xFE00;
			device::FLASH::FEARL = org + data_flash_block_ - 1;

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
		bool write(const void* src, uint16_t org, uint16_t len) const
		{
			if(org >= data_flash_size_) return false;

			if((org + len) > data_flash_size_) {
				len = data_flash_size_ - org;
			}

			turn_pe_();

			device::FLASH::FASR.EXS = 0;

			const uint8_t*p = static_cast<const uint8_t*>(src);

			bool ret = true;
			uint16_t page = data_flash_size_;
			for(uint16_t i = 0; i < len; ++i) {
				if(page != (org & ~(data_flash_block_ - 1))) {
					device::FLASH::FSARH = 0xFE00;
					device::FLASH::FSARL = org;
					page = org & ~(data_flash_block_ - 1);
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
