#pragma once
#ifndef NO_CLOCK_PROFILE
//=========================================================================//
/*!	@file
	@brief	RX66N グループ・クロック。プロファイル @n
            クロックジェネレータで発生させる周波数の定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cstdint>

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  クロック・プロファイル・クラス @n
				・PLL_BASE は、BASE の 0.5 倍単位 @n
				・他は、PLL_BASE を基数とする整数除算値 @n
				・選択出来ない値を指定すると、コンパイルエラーとなる @n
				・詳細はハードウェアーマニュアル参照の事
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class clock_profile {
	public:

		static constexpr uint32_t	EXT_LIMIT   = 30'000'000;		///< 外部クロック入力最大値

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  発信器タイプ @n
					HOCO を使う場合、BASE に周波数（16,18,20 MHz）を設定します。 @n
					LOCO は、起動時のモードなので、設定する事は通常行わない。
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class OSC_TYPE : uint8_t {
			XTAL,		///< クリスタル接続
			EXT,		///< 外部クロック入力
			HOCO,		///< 内蔵高速オンチップオシレーター
			LOCO,		///< 内蔵低速オンチップオシレーター (240KHz)
		};

		static constexpr OSC_TYPE	OSCT        = OSC_TYPE::XTAL;	///< 発信器種別型

		static constexpr bool		TURN_SBC	= false;			///< サブクロックを利用する場合「true」
		static constexpr bool       TURN_USB    = true;				///< USB を使う場合「true」

		static constexpr uint32_t	BASE		=  16'000'000;		///< 外部接続クリスタル
		static constexpr uint32_t	PLL_BASE	= 240'000'000;		///< PLL ベースクロック（最大240MHz）

		static constexpr uint32_t	ICLK		= 120'000'000;		///< ICLK 周波数（最大120MHz）
		static constexpr uint32_t	PCLKA		= 120'000'000;		///< PCLKA 周波数（最大120MHz）
		static constexpr uint32_t	PCLKB		=  60'000'000;		///< PCLKB 周波数（最大60MHz）
		static constexpr uint32_t	PCLKC		=  60'000'000;		///< PCLKC 周波数（最大60MHz）
		static constexpr uint32_t	PCLKD		=  60'000'000;		///< PCLKD 周波数（最大60MHz）
		static constexpr uint32_t	FCLK		=  60'000'000;		///< FCLK 周波数（最大60MHz）
		static constexpr uint32_t	BCLK		= 120'000'000;		///< BCLK 周波数（最大120MHz）

//		static constexpr uint32_t	DELAY_MS	= ICLK / 1'000'000 / 4;	///< ソフトウェアー遅延における定数（1マイクロ秒）
		static constexpr uint32_t	DELAY_MS	= ICLK / 3'116'883;	///< ソフトウェアー遅延における定数（1マイクロ秒）
	};
}

#endif
