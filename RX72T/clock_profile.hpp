#pragma once
//=====================================================================//
/*!	@file
	@brief	RX72T グループ・クロック。プロファイル @n
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
		@brief  クロック・プロファイル・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class clock_profile {
    public:
        static const uint32_t   BASE        =  16'000'000;      ///< 外部接続クリスタル
        static const uint32_t   PLL_BASE    = 192'000'000;      ///< PLL ベースクロック

        static const uint32_t   ICLK        = 192'000'000;      ///< ICLK 周波数
		static const uint32_t   PCLKA       =  96'000'000;      ///< PCLKA 周波数
        static const uint32_t   PCLKB       =  48'000'000;      ///< PCLKB 周波数
        static const uint32_t   PCLKC       = 192'000'000;      ///< PCLKC 周波数
        static const uint32_t   PCLKD       =  48'000'000;      ///< PCLKD 周波数
        static const uint32_t   FCLK        =  48'000'000;      ///< FCLK 周波数
        static const uint32_t   BCLK        =  48'000'000;      ///< BCLK 周波数
    };
}
