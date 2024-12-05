#pragma once
//=========================================================================//
/*!	@file
	@brief	RX マイコングループ A/D 変換制御・ベース @n
			・RX13T (Group: A, B, C) @n
			・RX140 (Group: A, B) @n
			・RX220 (Group: A, B) @n
			・RX231 (Group: A, B) @n
			・RX23T (Group: A, B) @n
			・RX24T/RX24U (Group: A, B) @n
			・RX260/RX261 (Group: A, B) @n
			・RX631/RX63N (Group: A) @n
			・RX63T (Group: A, B, C) @n
			・RX64M/RX71M (Group: A, B, C) @n
			・RX66T/RX72T (Group: A, B, C)
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
		@brief  A/D 制御ベース・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct adc_in_base {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D 変換モード型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class SCAN_MODE : uint8_t {
			SINGLE     = 0b00,	///< シングルスキャンモード
			GROUP      = 0b01,	///< グループスキャンモード
			CONTINUOUS = 0b10,	///< 連続スキャンモード
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  A/D 変換グループ型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class GROUP : uint8_t {
#if defined(SIG_RX140) || defined(SIG_RX220) || defined(SIG_RX231) || defined(SIG_RX23T) || defined(SIG_RX24T) || defined(SIG_RX24U) || defined(SIG_RX260) || defined(SIG_RX261)
			A,		///< グループＡ
			B,		///< グループＢ
#elif defined(SIG_RX621) || defined(SIG_RX62N) || defined(SIG_RX631) || defined(SIG_RX63N)
			A,		///< グループＡ
#else
			A,		///< グループＡ
			B,		///< グループＢ
			C,		///< グループＣ
#endif
		};
	};
}
