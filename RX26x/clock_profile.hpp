#pragma once
#ifndef NO_CLOCK_PROFILE
//=========================================================================//
/*!	@file
	@brief	RX260/RX261 グループ・クロック。プロファイル @n
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
				・HOCO 周波数は、OFSM で設定する。（初期：32MHz） @n
				・詳細はハードウェアーマニュアル参照の事
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class clock_profile {
	public:

		static constexpr uint32_t	EXT_LIMIT   =  20'000'000;		///< 外部クロック入力最大値

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  発信器タイプ @n
					HOCO を使う場合、同時に、BASE に 16, 18, 20 MHz を設定 @n
					LOCO は、起動時のモードなので、設定する事はない。
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class OSC_TYPE : uint8_t {
			XTAL,	///< クリスタル接続（1～20MHz）
			CERA,	///< セラミック共振子リード品（16MHz ～ 20MHz）
			EXT,	///< 外部クロック入力（最大 20MHz）
			HOCO,	///< 内蔵高速オンチップオシレーター（BASE: 24MHz, 32MHz, 48MHz, 64MHz）
			LOCO,	///< 内蔵低速オンチップオシレーター (4MHz)
		};

		static constexpr bool		TURN_SBC	= false;			///< サブクロックを利用する場合「true」
		static constexpr bool       TURN_USB    = true;				///< USB を使う場合「true」
#if 1
		static constexpr auto       OSCT        = OSC_TYPE::XTAL;	///< オシレーターの選択
		static constexpr uint32_t   BASE		=  16'000'000;		///< 外部接続クリスタル（1MHz ～ 24MHz）
#else
		static constexpr auto       OSCT        = OSC_TYPE::HOCO;	///< オシレーターの選択
		static constexpr uint32_t   BASE		=  32'000'000;		///< HOCO 指定の固定値 (16, 18, 20MHz)
#endif

		static constexpr uint32_t   PLL_BASE	=  64'000'000;		///< PLL ベースクロック（最大 24 to 64MHz）

		static constexpr uint32_t   ICLK		=  64'000'000;		///< ICLK 周波数（最大 64MHz）
		static constexpr uint32_t   PCLKA		=  64'000'000;		///< PCLKA 周波数（最大 64MHz）
		static constexpr uint32_t   PCLKB		=  32'000'000;		///< PCLKB 周波数（最大 32MHz）
		static constexpr uint32_t   PCLKD		=  64'000'000;		///< PCLKD 周波数（最大 64MHz）
		static constexpr uint32_t   FCLK		=  64'000'000;		///< FCLK 周波数（最大 64MHz）
		static constexpr uint32_t   CANFDCLK	=  32'000'000;		///< CANFD 周波数（最大 32MHz）

		// RXv3 ノーウェイトの場合の調整値
		static constexpr uint32_t	DELAY_MS	= ICLK / 1'033'058 / 2;	///< ソフトウェアー遅延における定数（1マイクロ秒）
	};
}

#endif
