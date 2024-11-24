#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ FLASH データ 制御 @n
			RX110 (UID: extra area) (DataFlash: 0) @n
			RX111 (UID: extra area) @n
			RX130 (UID: extra area) @n
			RX13T (UID: extra area) (DataFlash: 0) @n
			RX140 @n
			RX231 @n
			RX24T/RX24U
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cstring>
#include "common/delay.hpp"

#include "common/format.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  FLASH 制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct flash_io {

		//-----------------------------------------------------------------//
		/*!
			@brief  データ・フラッシュ構成
		*/
		//-----------------------------------------------------------------//
		static constexpr auto DATA_SIZE       = FLASH::DATA_SIZE;  ///< データ容量
		static constexpr auto DATA_BLOCK_SIZE = FLASH::DATA_BLOCK_SIZE;	///< データブロックサイズ
		static constexpr auto DATA_BLOCK_NUM  = FLASH::DATA_SIZE / FLASH::DATA_BLOCK_SIZE;	///< データブロック数

		enum class ERROR : uint8_t {
			NONE,		///< エラー無し
			START,		///< 開始不良
			CLOCK,		///< クロック設定不良
			ADDRESS,	///< アドレス不良
			LENGTH,		///< 長さ不良
			BANK,		///< バンク数不良
			TIMEOUT,	///< タイムアウト
			WRITE,		///< 書き込みエラー
			ST_ILGL,	///< ILGL ステータス検出
			ST_ERS,		///< ERS ステータス検出
			ST_PRG,		///< PRG ステータス検出
		};

	private:

		ERROR		error_;

		static inline uint32_t	uid_[4];

		static void turn_rd_() noexcept
		{
			if(FLASH::FENTRYR.FENTRYD() == 0) return;
			FLASH::FENTRYR.FENTRYD = 0;  // read mode

			FLASH::FPR = 0xA5;
			FLASH::FPMCR =  0x08;
			FLASH::FPMCR = ~0x08;
			FLASH::FPMCR =  0x08;
			utils::delay::micro_second(3);  // tMS
			FLASH::FENTRYR = 0xAA00;
			while(FLASH::FENTRYR() != 0) ;
		}

		static void turn_pe_() noexcept
		{
			if(FLASH::FENTRYR.FENTRYD() != 0) return;
			FLASH::FENTRYR.FENTRYD = 1;  // P/E mode

			FLASH::FENTRYR = 0xAA80;
			utils::delay::micro_second(5);  // tDSTOP
			if(SYSTEM::OPCCR.OPCM() == 0) {
				FLASH::FPR = 0xA5;
				FLASH::FPMCR =  0x10;
				FLASH::FPMCR = ~0x10;
				FLASH::FPMCR =  0x10;
			} else {
				FLASH::FPR = 0xA5;
				FLASH::FPMCR =  0x50;
				FLASH::FPMCR = ~0x50;
				FLASH::FPMCR =  0x50;
			}
			uint8_t frq = clock_profile::FCLK / 1'000'000;
			if(frq > 32) frq = 32;
			FLASH::FISR.PCKA = frq - 1;
		}

#if defined(SIG_RX110) || defined(SIG_RX111) || defined(SIG_RX113) || defined(SIG_RX130)
		static void read_unique_id_() noexcept
		{
			// Entry P/E mode
			FLASH::FASR.EXS = 1;
			FLASH::FSARH = 0x00;
			FLASH::FSARL = 0x0850;
			FLASH::FEARH = 0x00;
			FLASH::FEARL = 0x086F;
			FLASH::FCR   = 0x85;
			while(1) {
				if(FLASH::FSTATR0.ILGLERR() != 0) break;
				if(FLASH::FSTATR1.DRRDY() != 0) break;
			}
			if(FLASH::FSTATR0.ILGLERR() == 0) {
				uint32_t i = 0;
				do {
					uint32_t tmp = FLASH::FRBH();
					tmp <<= 16;
					tmp |= FLASH::FRBL();
					uid_[i] = tmp;
					while(FLASH::FSTATR1.DRRDY() != 0) ;
					FLASH::FCR = 0x85;
					while(1) {
						if(FLASH::FSTATR1.DRRDY() != 0) break;
						if(FLASH::FSTATR1.FRDY() != 0) break;
					}
					++i;
				} while(FLASH::FSTATR1.DRRDY() != 0 && i < 4) ;
			}
			FLASH::FCR = 0x00;
			while(FLASH::FSTATR1.FRDY() != 0) ;
		}
#endif
	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		flash_io() noexcept : error_(ERROR::NONE) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	最終エラー型を取得
			@return 最終エラー型
		 */
		//-----------------------------------------------------------------//
		auto get_last_error() const noexcept { return error_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@return エラー無ければ「true」
		 */
		//-----------------------------------------------------------------//
		bool start() noexcept
		{
			error_ = ERROR::NONE;

#if defined(SIG_RX110)
#else
			FLASH::DFLCTL.DFLEN = 1;
#endif
			utils::delay::micro_second(5);  // tDSTOP by high speed
			turn_rd_();

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  読み出し
			@param[in]	org	開始アドレス
			@return データ
		*/
		//-----------------------------------------------------------------//
		uint8_t read(uint16_t org) noexcept
		{
			error_ = ERROR::NONE;

			if(org >= DATA_SIZE) {
				error_ = ERROR::ADDRESS;
				return 0;
			}
			turn_rd_();
			return rd8_(0x0010'0000 + org);
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
		uint32_t read(uint16_t org, uint16_t len, void* dst) noexcept
		{
			error_ = ERROR::NONE;

			if(org >= DATA_SIZE) {
				error_ = ERROR::ADDRESS;
				return 0;
			}
			if((org + len) > DATA_SIZE) {
				len = DATA_SIZE - org;
			}
			turn_rd_();
			const void* src = reinterpret_cast<const void*>(0x0010'0000 + org);
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
			error_ = ERROR::NONE;

			if(bank >= DATA_BLOCK_NUM) {
				return false;
			}

			turn_pe_();

			FLASH::FASR.EXS = 0;

			uint32_t org = bank * DATA_BLOCK_SIZE;

			FLASH::FSARH = FLASH::DF_VA_H;
			FLASH::FSARL = FLASH::DF_VA_L + org;
			FLASH::FEARH = FLASH::DF_VA_H;
			FLASH::FEARL = FLASH::DF_VA_L + (org + DATA_BLOCK_SIZE - 1);

			FLASH::FCR = 0x83;
			while(FLASH::FSTATR1.FRDY() == 0) ;
			FLASH::FCR = 0x00;
			while(FLASH::FSTATR1.FRDY() != 0) ;

			if(FLASH::FSTATR0.ILGLERR() != 0 || FLASH::FSTATR0.ERERR() != 0) {
				FLASH::FRESETR.FRESET = 1;
				FLASH::FRESETR.FRESET = 0;
			}
			return FLASH::FSTATR0.BCERR() == 0;
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
			error_ = ERROR::NONE;

			if(bank >= DATA_BLOCK_NUM) {
				error_ = ERROR::BANK;
				return false;
			}

			turn_pe_();

			FLASH::FASR.EXS = 0;

			uint16_t org = bank * DATA_BLOCK_SIZE;
			FLASH::FSARH = FLASH::DF_VA_H;
			FLASH::FSARL = FLASH::DF_VA_L + org;
			FLASH::FEARH = FLASH::DF_VA_H;
			FLASH::FEARL = FLASH::DF_VA_L + org + DATA_BLOCK_SIZE - 1;

			FLASH::FCR = 0x84;
			while(FLASH::FSTATR1.FRDY() == 0) ;
			FLASH::FCR = 0x00;
			while(FLASH::FSTATR1.FRDY() != 0) ;

			bool ret = true;
			if(FLASH::FSTATR0.ILGLERR() != 0) {
				error_ = ERROR::ST_ILGL;
				ret = false;
			} else if(FLASH::FSTATR0.ERERR() != 0) {
				error_ = ERROR::ST_ERS;
				ret = false;
			} else {
				FLASH::FRESETR.FRESET = 1;
				FLASH::FRESETR.FRESET = 0;
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	org	開始オフセット
			@param[in]	src ソース
			@param[in]	len	バイト数
			@return エラーがあれば「false」
		*/
		//-----------------------------------------------------------------//
		bool write(uint32_t org, const void* src, uint32_t len) noexcept
		{
			error_ = ERROR::NONE;

			if(org >= DATA_SIZE) {
				error_ = ERROR::ADDRESS;
				return false;
			}

			if((org + len) > DATA_SIZE) {
				len = DATA_SIZE - org;
			}

			turn_pe_();

			FLASH::FASR.EXS = 0;

			const uint8_t* p = static_cast<const uint8_t*>(src);

			bool ret = true;
			FLASH::FSARH = FLASH::DF_VA_H;  // データ・フラッシュ仮想アドレスＨ
			FLASH::FSARL = FLASH::DF_VA_L + org;
			for(uint16_t i = 0; i < len; ++i) {
#if defined(SIG_RX110) || defined(SIG_RX111) || defined(SIG_RX113) || defined(SIG_RX130)
				FLASH::FWBL = *p++;
#else
				FLASH::FWB0 = *p++;
#endif
				FLASH::FCR = 0x81;
				while(FLASH::FSTATR1.FRDY() == 0) ;
				FLASH::FCR = 0x00;
				while(FLASH::FSTATR1.FRDY() != 0) ;
				if(FLASH::FSTATR0.ILGLERR() != 0) {
					error_ = ERROR::ST_ILGL;
					ret = false;
					break;
				} else if(FLASH::FSTATR0.ERERR() != 0) {
					error_ = ERROR::ST_ERS;
					ret = false;
					break;
				}
				++org;
			}
			if(!ret) {
				FLASH::FRESETR.FRESET = 1;
				FLASH::FRESETR.FRESET = 0;
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
#if defined(SIG_RX110) || defined(SIG_RX111) || defined(SIG_RX113) || defined(SIG_RX130)
			turn_pe_();
			read_unique_id_();
			return uid_[idx & 3];
#else
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
#endif
		}
	};
}
