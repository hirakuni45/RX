#pragma once
//=====================================================================//
/*!	@file
	@brief	Peripheral Type / ペリフェラル種別 (RX110/RX111)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Peripheral Type / ペリフェラル型（種別）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class peripheral : uint8_t {

		CAC,	///< Clock Frequency Accuracy Measurement Circuit / クロック周波数精度測定回路

		DTC,	///< Data Transfer Controller / データトランスファコントローラ

		ELC,	///< Event Link Controller / イベントリンクコントローラ

		MTU0,	///< Multi-Function Timer Pulse Unit 0 / マルチファンクションタイマパルスユニット０
		MTU1,	///< Multi-Function Timer Pulse Unit 1 / マルチファンクションタイマパルスユニット１
		MTU2,	///< Multi-Function Timer Pulse Unit 2 / マルチファンクションタイマパルスユニット２
#if defined(SIG_RX111)
		MTU3,	///< Multi-Function Timer Pulse Unit 3 / マルチファンクションタイマパルスユニット３
		MTU4,	///< Multi-Function Timer Pulse Unit 4 / マルチファンクションタイマパルスユニット４
#endif
		MTU5,	///< Multi-Function Timer Pulse Unit 5 / マルチファンクションタイマパルスユニット５
#if defined(SIG_RX111)
		POE2,	///< Port Output Enable 2 / ポートアウトプットイネーブル２

		TMR0,	///< 8-Bit Timer 0 / 8 ビットタイマ０
		TMR1,	///< 8-Bit Timer 1 / 8 ビットタイマ１
		TMR2,	///< 8-Bit Timer 2 / 8 ビットタイマ２
		TMR3,	///< 8-Bit Timer 3 / 8 ビットタイマ３
#endif
		CMT0,	///< Compare Match Timer 0 / コンペアマッチタイマー０
		CMT1,	///< Compare Match Timer 1 / コンペアマッチタイマー１

		RTC,	///< Realtime Clock / リアルタイムクロック

		IWDT,	///< Independent Watchdog Timer / 独立ウォッチドッグタイマ
#if defined(SIG_RX111)
		USB0,	///< USB 2.0 Host/Function Module 0 / USB 2.0 ホスト/ファンクションモジュール
#endif
		SCI1,	///< Serial Communications Interface 1 / シリアルコミュニケーションインタフェース１
		SCI5,	///< Serial Communications Interface 5 / シリアルコミュニケーションインタフェース５
		SCI12,	///< Serial Communications Interface 12 / シリアルコミュニケーションインタフェース１２

		RIIC0,	///< I2C-bus Interface 0 / I2C バスインタフェース０

		RSPI0,	///< Serial Sound Interface 0 / シリアルペリフェラルインタフェース０

		CRC,	///< CRC Calculator / CRC 演算器

		S12AD,	///< 12-Bit A/D Converter / 12 ビット A/D コンバータ

		DA,		///< 8-Bit D/A Converter / 8 ビット D/A コンバータ

		DOC,	///< Data Operation Circuit / データ演算回路（DOC）
	};
}
