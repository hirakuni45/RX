#pragma once
//=====================================================================//
/*!	@file
	@brief	I2C EEPROM ドライバー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>
#include "common/delay.hpp"

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  EEPROM テンプレートクラス
		@param[in]	I2C_IO	i2c I/O クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class I2C_IO>
	class EEPROM {
	public:
		static const uint8_t	I2C_ADR = 0x50;

	private:

		I2C_IO&	i2c_io_;

		uint8_t	ds_;
		bool	exp_;
		bool	ad_mix_;
		uint8_t	pagen_;

		uint8_t i2c_adr_(uint32_t adr) const noexcept
		{
			uint8_t a = I2C_ADR | ds_;
			if(ad_mix_) {
				if(adr >> 16) a |= 4;
			}
			return a;
		}

	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief 256 バイトまでの EEPROM の ID (0 to 7) @n
				   アドレス指定が１バイトのデバイス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class M256B : uint8_t {
			ID0,	///< A2:A1:A0 = 000
			ID1,	///< A2:A1:A0 = 001
			ID2,	///< A2:A1:A0 = 010
			ID3,	///< A2:A1:A0 = 011
			ID4,	///< A2:A1:A0 = 100
			ID5,	///< A2:A1:A0 = 101
			ID6,	///< A2:A1:A0 = 110
			ID7,	///< A2:A1:A0 = 111
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief 64K バイトまでの EEPROM の ID (0 to 7) @n
				   アドレス指定が２バイトのデバイス @n
				   ・24C32 (32K/4096) pagen=32 @n
				   ・24C64 (64K/8192) pagen=32
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class M64KB : uint8_t {
			ID0,	///< A2:A1:A0 = 000
			ID1,	///< A2:A1:A0 = 001
			ID2,	///< A2:A1:A0 = 010
			ID3,	///< A2:A1:A0 = 011
			ID4,	///< A2:A1:A0 = 100
			ID5,	///< A2:A1:A0 = 101
			ID6,	///< A2:A1:A0 = 110
			ID7,	///< A2:A1:A0 = 111
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief 128K バイトの EEPROM の ID (0 to 3) @n
				   アドレス指定が２バイトのデバイス @n
				   A2 端子が、バンクセレクトに使われるデバイス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class M128KB : uint8_t {
			ID0,	///< A1:A0 = 00
			ID1,	///< A1:A0 = 01
			ID2,	///< A1:A0 = 10
			ID3,	///< A1:A0 = 11
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	i2c_io	i2c_io クラスを参照で渡す
		 */
		//-----------------------------------------------------------------//
		EEPROM(I2C_IO& i2c_io) noexcept : i2c_io_(i2c_io), ds_(0),
			exp_(false), ad_mix_(false), pagen_(1) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	アドレス指定１バイトの EEPROM を開始
			@param[in]	page_id	デバイスのページ ID
			@param[in]	page_n	ページサイズ（書き込み一時バッファのサイズ）	
		 */
		//-----------------------------------------------------------------//
		void start(M256B page_id, uint8_t page_n) noexcept
		{
			ds_ = static_cast<uint8_t>(page_id);
			exp_ = false;
			ad_mix_ = false;
			pagen_ = page_n;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	アドレス指定２バイトの EEPROM を開始
			@param[in]	page_id	デバイスのページ ID
			@param[in]	page_n	ページサイズ（書き込み一時バッファのサイズ）	
		 */
		//-----------------------------------------------------------------//
		void start(M64KB page_id, uint8_t page_n) noexcept
		{
			ds_ = static_cast<uint8_t>(page_id);
			exp_ = true;
			ad_mix_ = false;
			pagen_ = page_n;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	アドレス指定２バイトで、「A2」がバンクの EEPROM を開始
			@param[in]	page_id	デバイスのページ ID
			@param[in]	page_n	ページサイズ（書き込み一時バッファのサイズ）	
		 */
		//-----------------------------------------------------------------//
		void start(M128KB page_id, uint8_t page_n) noexcept
		{
			ds_ = static_cast<uint8_t>(page_id);
			exp_ = true;
			ad_mix_ = true;
			pagen_ = page_n;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	書き込み状態の検査
			@param[in]	adr	検査アドレス
			@return 「false」なら、書き込み中
		 */
		//-----------------------------------------------------------------//
		bool get_write_state(uint32_t adr) const noexcept {
			uint8_t tmp[1];
			return read(adr, tmp, 1);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	書き込み同期
			@param[in]	adr	検査アドレス
			@param[in]	delay 待ち時間（10us単位）
			@return デバイスエラーなら「false」
		 */
		//-----------------------------------------------------------------//
		bool sync_write(uint32_t adr, uint16_t delay = 600) const noexcept {
			bool ok = false;
			for(uint16_t i = 0; i < delay; ++i) {
				utils::delay::micro_second(10);
				uint8_t tmp[1];
				if(read(adr, tmp, 1)) {
					ok = true;
					break;
				}
			}
			return ok;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	EEPROM 読み出し @n
					※通常１バンク内のサイズを超えて読み出す事は出来ない。
			@param[in]	adr	読み出しアドレス
			@param[out]	dst	転送先
			@param[in]	len	長さ
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool read(uint32_t adr, void* dst, uint16_t len) const noexcept
		{
			if(exp_) {
				uint8_t tmp[2];
				tmp[0] = (adr >> 8) & 255;
				tmp[1] =  adr & 255;
				if(!i2c_io_.send(i2c_adr_(adr), tmp, 2)) {
					return false;
				}
			} else {
				uint8_t tmp[1];
				tmp[0] = adr & 255;
				if(!i2c_io_.send(i2c_adr_(adr), tmp, 1)) {
					return false;
				}
			}
			if(!i2c_io_.recv(i2c_adr_(adr), dst, len)) {
				return false;
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	EEPROM 書き込み
			@param[in]	adr	書き込みアドレス
			@param[in]	src	転送元
			@param[in]	len	長さ
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool write(uint32_t adr, const void* src, uint16_t len) const noexcept
		{
			const uint8_t* p = static_cast<const uint8_t*>(src);
			while(len > 0) {
				uint16_t l = pagen_ - (adr & (pagen_ - 1));
				if(len < l) l = len;
				if(exp_) {
					if(!i2c_io_.send(i2c_adr_(adr), adr >> 8, adr & 255, p, l)) {
						return false;
					}
				} else {
					if(!i2c_io_.send(i2c_adr_(adr), adr & 255, p, l)) {
						return false;
					}
				}
				p += l;
				len -= l;
				if(len) {  // 書き込み終了を待つポーリング
					if(!sync_write(adr)) {
						return false;
					}
				}
				adr += l;
			}
			return true;
		}
	};
}
