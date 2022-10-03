#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・クロック。プロファイル @n
            クロックジェネレータで発生させる周波数の定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021, 2022 Kunihito Hiramatsu @n
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
				・HOCO を選択する場合、BASE を 8 とする事 @n
				・詳細はハードウェアーマニュアル参照の事
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class clock_profile {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  発信器タイプ @n
					HOCO を使う場合、同時に、clock_profile::PLL_BASE に周波数（8 MHz）を設定します。 @n
					LOCO は、起動時のモードなので、設定する事はない。
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class OSC_TYPE : uint8_t {
			XTAL,		///< クリスタル接続
			EXT,		///< 外部クロック入力
			HOCO,		///< 内蔵高速オンチップオシレーター（BASE には 8MHz を設定）
			LOCO,		///< 内蔵低速オンチップオシレーター (240KHz)
		};

		static constexpr auto       OSCT        = OSC_TYPE::XTAL;	///< オシレーターの選択
		static constexpr uint32_t   BASE		= 10'000'000;		///< 外部接続クリスタル（1MHz ～ 20MHz）

//		static constexpr auto       OSCT        = OSC_TYPE::HOCO;	///< オシレーターの選択
//		static constexpr uint32_t   BASE		=  8'000'000;		///< 外部接続クリスタル（1MHz ～ 20MHz）

		static constexpr uint32_t   PLL_BASE	= 80'000'000;		///< PLL ベースクロック（最大80MHz）

		static constexpr uint32_t   ICLK		= 80'000'000;		///< ICLK 周波数（最大80MHz）
		static constexpr uint32_t   PCLKA		= 80'000'000;		///< PCLKA 周波数（最大80MHz）
		static constexpr uint32_t   PCLKB		= 40'000'000;		///< PCLKB 周波数（最大40MHz）
		static constexpr uint32_t   PCLKD		= 40'000'000;		///< PCLKD 周波数（最大40MHz）
		static constexpr uint32_t   FCLK		= 20'000'000;		///< FCLK 周波数（最大32MHz）
	};
}
