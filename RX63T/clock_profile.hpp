#pragma once
#ifndef NO_CLOCK_PROFILE
//=========================================================================//
/*!	@file
	@brief	RX63T グループ・クロック。プロファイル @n
            クロックジェネレータで発生させる周波数の定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cstdint>

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  クロック・プロファイル・クラス @n
				・選択出来ない値を指定すると、コンパイルエラーとなる @n
				・詳細はハードウェアーマニュアル参照の事
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class clock_profile {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  発信器型 @n
					XTAL: @n
						144/120/112/100 pin: 8 ~ 12.5MHz @n
						64/48 pin: 4 ~ 16MHz @n
					EXT: @n
						144/120/112/100 pin: 14MHz (max) @n
						64/48 pin: 20MHz (max) @n
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class OSC_TYPE : uint8_t {
			XTAL,		///< クリスタル接続
			EXT,		///< 外部クロック入力
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  パッケージ型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class PACKAGE : uint8_t {
			MINI,	///< 48/64 pin package
			LARGE,	///< 100/112/129/144 pin package
		};

		static constexpr auto		PACK        = PACKAGE::MINI;	///< パッケージの設定 

		static constexpr auto       OSCT        = OSC_TYPE::XTAL;	///< オシレーターの選択
		static constexpr bool       TURN_USB    = true;				///< USB を使う場合「true」

		static constexpr uint32_t   BASE		=  12'000'000;		///< 外部接続クリスタル（8MHz ～ 12.5MHz）

		static constexpr uint32_t   PLL_BASE	= 192'000'000;		///< PLL ベースクロック（最大104 ～ 200MHz）

		static constexpr uint32_t   ICLK		=  96'000'000;		///< ICLK 周波数（最大100MHz）
		static constexpr uint32_t   PCLKA		=  96'000'000;		///< PCLKA 周波数（最大100MHz）
		static constexpr uint32_t   PCLKB		=  48'000'000;		///< PCLKB 周波数（最大50MHz）
		static constexpr uint32_t	PCLKC		=  96'000'000;		///< PCLKC 周波数（最大100MHz）
		static constexpr uint32_t   PCLKD		=  48'000'000;		///< PCLKD 周波数（最大50MHz）
		static constexpr uint32_t   FCLK		=  48'000'000;		///< FCLK 周波数（最大50MHz）
		static constexpr uint32_t	BCLK		=  48'000'000;		///< BCLK 周波数（最大50MHz）

		static constexpr uint32_t	DELAY_MS	= ICLK / 1'000'000 / 4;	///< ソフトウェアー遅延における定数（1マイクロ秒）
	};
}

#endif
