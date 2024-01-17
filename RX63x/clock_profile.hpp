#pragma once
#ifndef NO_CLOCK_PROFILE
//=========================================================================//
/*!	@file
	@brief	RX631/RX63N グループ・クロック。プロファイル @n
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
				・PLL_BASE は、BASE の 8, 10, 12, 16, 20, 24, 25, 50 倍 @n
				・PLL_BASE は、104MHz ～ 200MHz の範囲 @n
				・他は、PLL_BASE を基数とする整数除算値 @n
				・選択出来ない値を指定すると、コンパイルエラーとなる @n
				・詳細はハードウェアーマニュアル参照の事
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class clock_profile {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  発信器タイプ @n
					HOCO を使う場合、BASE に周波数（50MHz）を設定します。 @n
					LOCO は、起動時のモードなので、設定する事は通常行わない。
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class OSC_TYPE : uint8_t {
			XTAL,		///< クリスタル接続（4MHz ～ 16MHz）
			EXT,		///< 外部クロック入力（最大 20MHz）
			HOCO,		///< 内蔵高速オンチップオシレーター（50MHz）
			LOCO,		///< 内蔵低速オンチップオシレーター (125KHz)
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  パッケージ型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class PACKAGE : uint8_t {
			MINI,	///< 64 pin package
			LARGE,	///< 100/112/129/144/167 pin package
		};


		static constexpr PACKAGE	PACK		= PACKAGE::LARGE;	///< パッケージの種別
#if 1
		static constexpr OSC_TYPE	OSCT        = OSC_TYPE::XTAL;	///< 発信器種別型

		static constexpr bool		TURN_SBC	= true;				///< サブクロックを利用する場合「true」
		static constexpr bool       TURN_USB    = true;				///< USB を使う場合「true」

		static constexpr uint32_t	BASE		=  12'000'000;		///< 外部接続クリスタル
#if 1 
		static constexpr uint32_t	PLL_BASE	= 192'000'000;		///< PLL ベースクロック（104MHz ～ 200MHz）

		static constexpr uint32_t	ICLK		=  96'000'000;		///< ICLK 周波数（最大100MHz）
		static constexpr uint32_t	PCLKA		=  96'000'000;		///< PCLKA 周波数（最大100MHz）
		static constexpr uint32_t	PCLKB		=  48'000'000;		///< PCLKB 周波数（最大50MHz）
		static constexpr uint32_t	FCLK		=  48'000'000;		///< FCLK 周波数（最大50MHz）
		static constexpr uint32_t	BCLK		=  48'000'000;		///< BCLK 周波数（最大100MHz）
#else
		// over clock: GR-CITRUS / RAYTRACER_sample で動作確認、問題無く動作する。
		static constexpr uint32_t	PLL_BASE	= 240'000'000;		///< PLL ベースクロック（104MHz ～ 200MHz）

		static constexpr uint32_t	ICLK		= 120'000'000;		///< ICLK 周波数（最大100MHz）
		static constexpr uint32_t	PCLKA		= 120'000'000;		///< PCLKA 周波数（最大100MHz）
		static constexpr uint32_t	PCLKB		=  60'000'000;		///< PCLKB 周波数（最大50MHz）
		static constexpr uint32_t	FCLK		=  60'000'000;		///< FCLK 周波数（最大50MHz）
		static constexpr uint32_t	BCLK		=  60'000'000;		///< BCLK 周波数（最大100MHz）
#endif

#else
		static constexpr OSC_TYPE	OSCT        = OSC_TYPE::HOCO;	///< 発信器種別型

		static constexpr bool		TURN_SBC	= false;			///< サブクロックを利用する場合「true」
		static constexpr bool       TURN_USB    = false;			///< USB を使う場合「true」

		static constexpr uint32_t	BASE		=  50'000'000;		///< 外部接続クリスタル
		static constexpr uint32_t	PLL_BASE	=  50'000'000;		///< PLL ベースクロック（104MHz ～ 200MHz）

		static constexpr uint32_t	ICLK		=  50'000'000;		///< ICLK 周波数（最大100MHz）
		static constexpr uint32_t	PCLKA		=  50'000'000;		///< PCLKA 周波数（最大100MHz）
		static constexpr uint32_t	PCLKB		=  50'000'000;		///< PCLKB 周波数（最大50MHz）
		static constexpr uint32_t	FCLK		=  50'000'000;		///< FCLK 周波数（最大50MHz）
		static constexpr uint32_t	BCLK		=  50'000'000;		///< BCLK 周波数（最大100MHz）
#endif
		static constexpr uint32_t	IECLK		=  50'000'000;		///< IECLK 周波数（最大50MHz）

		static constexpr uint32_t	DELAY_MS	= ICLK / 1'000'000 / 4;	///< ソフトウェアー遅延における定数（1マイクロ秒）
    };
}

#endif
