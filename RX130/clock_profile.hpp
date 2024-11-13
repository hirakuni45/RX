#pragma once
#ifndef NO_CLOCK_PROFILE
//=========================================================================//
/*!	@file
	@brief	RX130 グループ・クロック。プロファイル @n
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
			HOCO,	///< 内蔵高速オンチップオシレーター（BASE: 32MHz）
			LOCO,	///< 内蔵低速オンチップオシレーター (125KHz)
		};

		static constexpr auto       OSCT        = OSC_TYPE::XTAL;	///< オシレーターの選択
		static constexpr uint32_t   BASE		= 8'000'000;		///< 外部接続クリスタル（1MHz ～ 20MHz）

		static constexpr bool		TURN_SBC	= false;			///< サブクロックを利用する場合「true」

		static constexpr uint32_t   PLL_BASE	= 32'000'000;		///< PLL ベースクロック（最大 24MHz ～ 32MHz）

		static constexpr uint32_t   ICLK		= 32'000'000;		///< ICLK 周波数（最大 32MHz）
		static constexpr uint32_t   PCLKB		= 32'000'000;		///< PCLKB 周波数（最大 32MHz）
		static constexpr uint32_t   PCLKD		= 32'000'000;		///< PCLKD 周波数（最大 1MHz ～ 32MHz）
		static constexpr uint32_t   FCLK		= 32'000'000;		///< FCLK 周波数（最大 1 ～ 32MHz）

		static constexpr uint32_t	DELAY_MS	=  ICLK / ((ICLK > 32'000'000) ? 787'402 : 1'000'000) / 4;	///< ソフトウェアー遅延における定数（1マイクロ秒）
	};
}
#endif
