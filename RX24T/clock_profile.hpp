#pragma once
#ifndef NO_CLOCK_PROFILE
//=========================================================================//
/*!	@file
	@brief	RX24T グループ・クロック。プロファイル @n
            クロックジェネレータで発生させる周波数の定義 @n
			※簡単な実験では、120MHz は、普通に動作する、それ以上は、怪しい・・
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cstdint>

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  クロック・プロファイル・クラス @n
				・PLL_BASE は、BASE の 0.5 倍単位（4 ～ 15.5 倍） @n
				・他は、PLL_BASE を基数とする整数除算値 @n
				・選択出来ない値を指定すると、コンパイルエラーとなる @n
				・詳細はハードウェアーマニュアル参照の事
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct clock_profile {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  発信器タイプ @n
					HOCO を使う場合、同時に、BASE に 8 MHz（8'000'000）を設定 @n
					LOCO は、起動時のモードなので、設定する事はない。
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class OSC_TYPE : uint8_t {
			XTAL,		///< クリスタル接続
			EXT,		///< 外部クロック入力
			HOCO,		///< 内蔵高速オンチップオシレーター（BASE には 8MHz を設定）
			LOCO,		///< 内蔵低速オンチップオシレーター (240KHz)
		};
#if 1
		static constexpr auto       OSCT        = OSC_TYPE::XTAL;	///< オシレーターの選択
		static constexpr uint32_t   BASE		= 10'000'000;		///< 外部接続クリスタル（1MHz ～ 20MHz）
#else
		static constexpr auto       OSCT        = OSC_TYPE::HOCO;	///< オシレーターの選択
		static constexpr uint32_t   BASE		=  8'000'000;		///< HOCO 指定の固定値
#endif
		static constexpr uint32_t   PLL_BASE	=  80'000'000;		///< PLL ベースクロック（最大80MHz）

		static constexpr uint32_t   ICLK		=  80'000'000;		///< ICLK 周波数（最大80MHz）
		static constexpr uint32_t   PCLKA		=  80'000'000;		///< PCLKA 周波数（最大80MHz）
		static constexpr uint32_t   PCLKB		=  40'000'000;		///< PCLKB 周波数（最大40MHz）
		static constexpr uint32_t   PCLKD		=  40'000'000;		///< PCLKD 周波数（最大40MHz）
		static constexpr uint32_t   FCLK		=  20'000'000;		///< FCLK 周波数（最大32MHz）
#else
		// オーバークロックプロファイル 120MHz
		static constexpr uint32_t   PLL_BASE	= 120'000'000;		///< PLL ベースクロック

		static constexpr uint32_t   ICLK		= 120'000'000;		///< ICLK 周波数（最大80MHz）
		static constexpr uint32_t   PCLKA		= 120'000'000;		///< PCLKA 周波数（最大80MHz）
		static constexpr uint32_t   PCLKB		=  60'000'000;		///< PCLKB 周波数（最大40MHz）
		static constexpr uint32_t   PCLKD		=  60'000'000;		///< PCLKD 周波数（最大40MHz）
		static constexpr uint32_t   FCLK		=  30'000'000;		///< FCLK 周波数（最大32MHz）
#endif
//		static constexpr uint32_t	DELAY_MS	= ICLK / 1'000'000 / 4;	///< ソフトウェアー遅延における定数（1マイクロ秒）
		static constexpr uint32_t	DELAY_MS	= ICLK / 3'200'000;	///< ソフトウェアー遅延における定数（1マイクロ秒）
	};
}

#endif
