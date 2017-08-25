#pragma once
//=====================================================================//
/*!	@file
	@brief	EUI-48/EUI-64 EEPROM クラス @n
			25AA02E48/25AA02E64
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

/// F_ICLK は速度パラメーター計算で必要で、設定が無いとエラーにします。
#ifndef F_ICLK
#  error "EUI_XX.hpp requires F_ICLK to be defined"
#endif

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  EUI-48/EUI-64 テンプレートクラス
		@param[in]	SPI	SPI 型
		@param[in]	CS	チップ・セレクト
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SPI, class CS>
	class EUI_XX {
	public:
		static const uint8_t eui48_org = 0xFA;
 		static const uint8_t eui64_org = 0xF8;

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Block Protection
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class BP : uint8_t {
			none,	///< none
			upq,	///< Upper 1/4 (0xC0 to 0xFF)
			uph,	///< Upper 1/2 (0x80 to 0xFF)
			all,	///< All (0x00 to 0xFF)
		};

	private:

		SPI&	spi_;

		inline void cs_setup_() const {
			uint32_t n = static_cast<uint32_t>(F_ICLK) * 20 / 100000000;
			utils::delay::loop(n);
		}


		bool get_write_busy_() const
		{
			utils::delay::loop(10);
			CS::P = 0;
			cs_setup_();
			spi_.xchg(0x05);  // read state
			uint8_t v = spi_.xchg(0x00);
			CS::P = 1;
			return (v & 1) != 0;		
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	spi	SPI クラス
		 */
		//-----------------------------------------------------------------//
		EUI_XX(SPI& spi) : spi_(spi) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@param	bp	ブロック・プロテクション
		 */
		//-----------------------------------------------------------------//
		void start(BP bp = BP::upq)
		{
			CS::DIR = 1;  // 出力指定
			CS::PU  = 0;  // プルアップ無効

			CS::P = 1;
			utils::delay::milli_second(10);

			CS::P = 0;
			cs_setup_();
			spi_.xchg(0x01);  // write status
			spi_.xchg(static_cast<uint8_t>(bp) << 2);
			CS::P = 1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ステートの取得
			@return ステート
		 */
		//-----------------------------------------------------------------//
		uint8_t get_state()
		{
			CS::P = 0;
			cs_setup_();
			spi_.xchg(0x05);  // read state
			uint8_t v = spi_.xchg(0x00);
			CS::P = 1;
			return v;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	読み込み
			@param[in]	org	開始アドレス
			@param[out]	dst	ディストネーション・アドレス
			@param[in]	len	長さ（最大１６）
			@return 正常なら「true」
		 */
		//-----------------------------------------------------------------//
		bool read(uint16_t org, void* dst, uint16_t len)
		{
			while(get_write_busy_()) ;

			CS::P = 0;
			cs_setup_();
			spi_.xchg(0x03);
			spi_.xchg(org);
			spi_.recv(dst, len);
			CS::P = 1;
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	書き込み
			@param[in]	org	開始アドレス
			@param[in]	src	ソースアドレス
			@param[in]	len	長さ（最大１６）
			@return 正常なら「true」
		 */
		//-----------------------------------------------------------------//
		bool write(uint16_t org, const void* src, uint16_t len)
		{
			while(get_write_busy_()) ;

			CS::P = 0;
			cs_setup_();
			spi_.xchg(0x06);  // write enable
			CS::P = 1;

			utils::delay::loop(10);

			CS::P = 0;
			cs_setup_();
			spi_.xchg(0x02);  // write
			spi_.xchg(org);
			spi_.send(src, len);
			CS::P = 1;

			return true;
		}
	};
}
