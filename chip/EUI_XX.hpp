#pragma once
//=====================================================================//
/*!	@file
	@brief	EUI-48/EUI-64 EEPROM クラス @n
			25AA02E48/25AA02E64 @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cmath>

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  EUI-48/EUI-64 テンプレートクラス
		@param[in]	SPI	SPI クラス
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

		bool get_write_busy_() const
		{
			utils::delay::loop(10);
			CS::P = 0;
			spi_.xchg(0x05);  // read state
			uint8_t v = spi_.xchg(0x00);
			CS::P = 1;
			return (v & 1) != 0;		
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
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
			CS::DIR = 1;
			CS::PU  = 0;

			CS::P = 0;
			spi_.xchg(0x01);  // write status
			spi_.xchg(static_cast<uint8_t>(bp) << 2);
			CS::P = 1;
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
		bool read(uint8_t org, void* dst, uint8_t len)
		{
			while(get_write_busy_()) ;

			utils::delay::loop(10);
			CS::P = 0;
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
		bool write(uint8_t org, const void* src, uint8_t len)
		{
			while(len > 0) {

				while(get_write_busy_()) ;

				utils::delay::loop(10);
				CS::P = 0;
				spi_.xchg(0x06);  // write enable
				CS::P = 1;

				uint8_t l = len;
				if(l > 16) l = 16;

				utils::delay::loop(10);
				CS::P = 0;
				spi_.xchg(0x02);
				spi_.xchg(org);
				spi_.send(src, l);
				CS::P = 1;

				len -= l;
				org += l;
			}
			return true;
		}
	};
}
