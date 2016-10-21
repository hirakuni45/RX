#pragma once
//=====================================================================//
/*!	@file
	@brief	I2C EEPROM ドライバー
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>
#include "common/iica_io.hpp"
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

		static const uint8_t	EEPROM_ADR_ = 0x50;

		I2C_IO&	i2c_;

		uint8_t	ds_;
		bool	exp_;
		bool	ad_mix_;
		uint8_t	pagen_;

		uint8_t i2c_adr_(uint32_t adr) const {
			uint8_t a = EEPROM_ADR_ | ds_;
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
			ID0,	///< A0=L(0), A1=L(0), A2=L(0)
			ID1,	///< A0=H(1), A1=L(0), A2=L(0)
			ID2,	///< A0=L(0), A1=H(1), A2=L(0)
			ID3,	///< A0=H(1), A1=H(1), A2=L(0)
			ID4,	///< A0=L(0), A1=L(0), A2=H(1)
			ID5,	///< A0=H(1), A1=L(0), A2=H(1)
			ID6,	///< A0=L(0), A1=H(1), A2=H(1)
			ID7,	///< A0=H(1), A1=H(1), A2=H(1)
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief 64K バイトまでの EEPROM の ID (0 to 7) @n
				   アドレス指定が２バイトのデバイス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class M64KB : uint8_t {
			ID0,	///< A0=L(0), A1=L(0), A2=L(0)
			ID1,	///< A0=H(1), A1=L(0), A2=L(0)
			ID2,	///< A0=L(0), A1=H(1), A2=L(0)
			ID3,	///< A0=H(1), A1=H(1), A2=L(0)
			ID4,	///< A0=L(0), A1=L(0), A2=H(1)
			ID5,	///< A0=H(1), A1=L(0), A2=H(1)
			ID6,	///< A0=L(0), A1=H(1), A2=H(1)
			ID7,	///< A0=H(1), A1=H(1), A2=H(1)
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief 128K バイトの EEPROM の ID (0 to 3) @n
				   アドレス指定が２バイトのデバイス @n
				   A2 端子が、バンクセレクトに使われるデバイス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class M128KB : uint8_t {
			ID0,	///< A0=L(0), A1=L(0)
			ID1,	///< A0=H(1), A1=L(0)
			ID2,	///< A0=L(0), A1=H(1)
			ID3,	///< A0=H(1), A1=H(1)
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	i2c	i2c_io クラスを参照で渡す
		 */
		//-----------------------------------------------------------------//
		EEPROM(I2C_IO& i2c) : i2c_(i2c), ds_(0),
			exp_(false), ad_mix_(false), pagen_(1) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	アドレス指定１バイトの EEPROM を開始
			@param[in]	type	デバイスのタイプとID
			@param[in]	pagen	ページサイズ（書き込み一時バッファのサイズ）	
		 */
		//-----------------------------------------------------------------//
		void start(M256B type_id, uint8_t pagen) {
			ds_ = static_cast<uint8_t>(type_id);
			exp_ = false;
			ad_mix_ = false;
			pagen_ = pagen;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	アドレス指定２バイトの EEPROM を開始
			@param[in]	type	デバイスのタイプとID
			@param[in]	pagen	ページサイズ（書き込み一時バッファのサイズ）	
		 */
		//-----------------------------------------------------------------//
		void start(M64KB type_id, uint8_t pagen) {
			ds_ = static_cast<uint8_t>(type_id);
			exp_ = true;
			ad_mix_ = false;
			pagen_ = pagen;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	アドレス指定２バイトで、「A2」がバンクの EEPROM を開始
			@param[in]	type	デバイスのタイプとID
			@param[in]	pagen	ページサイズ（書き込み一時バッファのサイズ）	
		 */
		//-----------------------------------------------------------------//
		void start(M128KB type_id, uint8_t pagen) {
			ds_ = static_cast<uint8_t>(type_id);
			exp_ = true;
			ad_mix_ = true;
			pagen_ = pagen;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	書き込み状態の検査
			@param[in]	adr	検査アドレス
			@return 「false」なら、書き込み中
		 */
		//-----------------------------------------------------------------//
		bool get_write_state(uint32_t adr) const {
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
		bool sync_write(uint32_t adr, uint16_t delay = 600) const {
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
			@brief	EEPROM 読み出し
			@param[in]	adr	読み出しアドレス
			@param[out]	dst	先
			@param[in]	len	長さ
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool read(uint32_t adr, uint8_t* dst, uint16_t len) const {
			uint8_t tmp[2];
			if(exp_) {
				tmp[0] = (adr >> 8) & 255;
				tmp[1] =  adr & 255;
				if(!i2c_.send(i2c_adr_(adr), tmp, 2)) {
					return false;
				}
			} else {
				tmp[0] = adr & 255;
				if(!i2c_.send(i2c_adr_(adr), tmp, 1)) {
					return false;
				}
			}
			if(!i2c_.recv(i2c_adr_(adr), dst, len)) {
				return false;
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	EEPROM 書き込み
			@param[in]	adr	書き込みアドレス
			@param[out]	src	元
			@param[in]	len	長さ
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool write(uint32_t adr, const uint8_t* src, uint16_t len) const {
			while(len > 0) {
				uint16_t l = pagen_ - (adr & (pagen_ - 1));
				if(len < l) l = len;
				if(exp_) {
					if(!i2c_.send(i2c_adr_(adr), adr >> 8, adr & 255, src, l)) {
						return false;
					}
				} else {
					if(!i2c_.send(i2c_adr_(adr), adr & 255, src, l)) {
						return false;
					}
				}
				src += l;
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
