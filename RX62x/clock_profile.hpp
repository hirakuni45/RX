#pragma once
//=========================================================================//
/*!	@file
	@brief	RX621/RX62N グループ・クロック。プロファイル @n
            クロックジェネレータで発生させる周波数の定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
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
			@brief  発信器タイプ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class OSC_TYPE : uint8_t {
			XTAL,		///< クリスタル接続（8MHz ～ 14MHz）
			EXT,		///< 外部クロック入力（8MHz ～ 14MHz）
		};

		static constexpr auto       OSCT        = OSC_TYPE::XTAL;	///< オシレーターの選択
		static constexpr uint32_t   BASE		= 12'000'000;		///< 外部接続クリスタル

		static constexpr bool       TURN_USB    = true;				///< USB を使う場合「true」

		static constexpr uint32_t   ICLK		= 96'000'000;		///< ICLK 周波数（最大 8~100MHz）
		static constexpr uint32_t   PCLK		= 48'000'000;		///< PCLK 周波数（最大 8~50MHz）
		static constexpr uint32_t   BCLK		= 48'000'000;		///< BCLK 周波数（最大 8~50MHz）
	};
}
