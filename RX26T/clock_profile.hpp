#pragma once
#ifndef NO_CLOCK_PROFILE
//=========================================================================//
/*!	@file
	@brief	RX26T グループ・クロック。プロファイル @n
            クロックジェネレータで発生させる周波数の定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023 Kunihito Hiramatsu @n
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

		static constexpr uint32_t	EXT_LIMIT   = 24'000'000;		///< 外部クロック入力最大値

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  発信器タイプ @n
					HOCO を使う場合、同時に、BASE に 16, 18, 20 MHz を設定 @n
					LOCO は、起動時のモードなので、設定する事はない。
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class OSC_TYPE : uint8_t {
			XTAL,		///< クリスタル接続（8 ～ 24MHz）
			EXT,		///< 外部クロック入力（最大 24MHz）
			HOCO,		///< 内蔵高速オンチップオシレーター（BASE には 16, 18, 20MHz を設定）
			LOCO,		///< 内蔵低速オンチップオシレーター (240KHz)
		};
#if 1
		static constexpr auto       OSCT        = OSC_TYPE::XTAL;	///< オシレーターの選択
		static constexpr uint32_t   BASE		=  12'000'000;		///< 外部接続クリスタル（8MHz ～ 24MHz）
#else
		static constexpr auto       OSCT        = OSC_TYPE::HOCO;	///< オシレーターの選択
		static constexpr uint32_t   BASE		=  20'000'000;		///< HOCO 指定の固定値 (16, 18, 20MHz)
#endif
		static constexpr uint32_t   PLL_BASE	=  240'000'000;		///< PLL ベースクロック（最大 120 to 240MHz）

		static constexpr uint32_t   ICLK		=  120'000'000;		///< ICLK 周波数（最大 120MHz）
		static constexpr uint32_t   PCLKA		=  120'000'000;		///< PCLKA 周波数（最大 120MHz）
		static constexpr uint32_t   PCLKB		=   60'000'000;		///< PCLKB 周波数（最大 60MHz）
		static constexpr uint32_t   PCLKC		=  120'000'000;		///< PCLKB 周波数（最大 120MHz）
		static constexpr uint32_t   PCLKD		=   60'000'000;		///< PCLKD 周波数（最大 60MHz）
		static constexpr uint32_t   FCLK		=   60'000'000;		///< FCLK 周波数（最大 60MHz）

		static constexpr uint32_t	DELAY_MS	= ICLK / 4444444;	///< ソフトウェアー遅延における定数（1マイクロ秒）
		static constexpr bool		DELAY_T1	= false;			///< 微調整として、「nop」を１つ追加
	};
}

#endif
