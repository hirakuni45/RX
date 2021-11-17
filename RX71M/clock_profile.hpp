#pragma once
//=====================================================================//
/*!	@file
	@brief	RX71M グループ・クロック。プロファイル @n
            クロックジェネレータで発生させる周波数の定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  クロック・プロファイル・クラス @n
				・分周器の仕様を超える値を指定しない事 @n
				・PLL_BASE は、0.5 倍単位 @n
				・他は、PLL_BASE を基数とする整数除算値 @n
				・詳細はハードウェアーマニュアル参照の事
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class clock_profile {
	public:
		static constexpr uint32_t	BASE		=  12'000'000;		///< 外部接続クリスタル
		static constexpr uint32_t	PLL_BASE	= 240'000'000;		///< PLL ベースクロック（最大240MHz）

		static constexpr uint32_t	ICLK		= 240'000'000;		///< ICLK 周波数（最大240MHz）
		static constexpr uint32_t	PCLKA		= 120'000'000;		///< PCLKA 周波数（最大120MHz）
		static constexpr uint32_t	PCLKB		=  60'000'000;		///< PCLKB 周波数（最大60MHz）
		static constexpr uint32_t	PCLKC		=  60'000'000;		///< PCLKC 周波数（最大60MHz）
		static constexpr uint32_t	PCLKD		=  60'000'000;		///< PCLKD 周波数（最大60MHz）
		static constexpr uint32_t	FCLK		=  60'000'000;		///< FCLK 周波数（最大60MHz）
		static constexpr uint32_t	BCLK		= 120'000'000;		///< BCLK 周波数（最大120MHz）
    };
}