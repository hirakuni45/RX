#pragma once
#ifndef NO_CLOCK_PROFILE
//=========================================================================//
/*!	@file
	@brief	RX140 グループ・クロック。プロファイル @n
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
				・選択出来ない値を指定すると、コンパイルエラーとなる @n
				・このプロセッサは、ICLK の違いで、動作モードを切り替える @n
				・詳細はハードウェアーマニュアル参照の事 
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class clock_profile {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  発信器タイプ @n
					HOCO 発振周波数は、OFSM 領域で予め ROM 上に設定しておく。 @n
					LOCO は、起動時のモードなので、設定する事はない。
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class OSC_TYPE : uint8_t {
			XTAL,	///< クリスタル接続（1～20MHz）
			CERA,	///< セラミック発振子リード品（16MHz ～ 20MHz）
			EXT,	///< 外部クロック入力（最大 20MHz）
			HOCO,	///< 内蔵高速オンチップオシレーター（BASE: 24MHz, 32MHz, 48MHz）
			LOCO,	///< 内蔵低速オンチップオシレーター (125KHz)
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サブクロック発信器ドライブ能力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class SUB_OSC_MODE : uint8_t {
			DEFAULT,	///< 標準 CL 用ドライブ能力
			L_HIGH,		///< 低 CL 用ドライブ能力高
			L_MID,		///< 低 CL 用ドライブ能力中
			L_LOW,		///< 低 CL 用ドライブ能力低
		};

		static constexpr auto       OSCT        = OSC_TYPE::XTAL;	///< オシレーターの選択
		static constexpr uint32_t   BASE		= 12'000'000;		///< 外部接続クリスタル（1MHz ～ 20MHz）

		static constexpr auto		SOMCR		= SUB_OSC_MODE::DEFAULT;	///< サブクロック発信器モード選択
		static constexpr bool		TURN_SBC	= false;			///< サブクロックを利用する場合「true」
#if 1
		static constexpr uint32_t   PLL_BASE	= 48'000'000;		///< PLL ベースクロック（最大 24MHz ～ 48MHz）

		static constexpr uint32_t   ICLK		= 48'000'000;		///< ICLK 周波数（最大 48MHz）
		static constexpr uint32_t   PCLKB		= 24'000'000;		///< PCLKB 周波数（最大 32MHz）
		static constexpr uint32_t   PCLKD		= 48'000'000;		///< PCLKD 周波数（最大 1MHz ～ 48MHz）
		static constexpr uint32_t   FCLK		= 24'000'000;		///< FCLK 周波数（最大 1 ～ 32MHz）
#else
		static constexpr uint32_t   PLL_BASE	= 54'000'000;		///< PLL ベースクロック（最大 24MHz ～ 48MHz）

		static constexpr uint32_t   ICLK		= 54'000'000;		///< ICLK 周波数（最大 48MHz）
		static constexpr uint32_t   PCLKB		= 27'000'000;		///< PCLKB 周波数（最大 32MHz）
		static constexpr uint32_t   PCLKD		= 54'000'000;		///< PCLKD 周波数（最大 1MHz ～ 48MHz）
		static constexpr uint32_t   FCLK		= 27'000'000;		///< FCLK 周波数（最大 1 ～ 32MHz）
#endif

		// 32MHz より高い周波数で動作させる場合、MEMWAIT を設けるので、ソフト遅延を微調整する。
		static constexpr uint32_t	DELAY_MS	=  ICLK / ((ICLK > 32'000'000) ? 787'402 : 1'000'000) / 4;	///< ソフトウェアー遅延における定数（1マイクロ秒）
	};
}
#endif
