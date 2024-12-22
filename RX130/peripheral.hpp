#pragma once
//=====================================================================//
/*!	@file
	@brief	Peripheral Type / ペリフェラル種別 (RX130)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  peripheral enum class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class peripheral : uint8_t {

		CAC,	///< クロック周波数精度測定回路

		DTC,	///< データトランスファコントローラ

		ELC,	///< イベントリンクコントローラ

		MTU0,	///< マルチファンクションタイマパルスユニット０
		MTU1,	///< マルチファンクションタイマパルスユニット１
		MTU2,	///< マルチファンクションタイマパルスユニット２
		MTU3,	///< マルチファンクションタイマパルスユニット３
		MTU4,	///< マルチファンクションタイマパルスユニット４
		MTU5,	///< マルチファンクションタイマパルスユニット５

		POE2,	///< ポートアウトプットイネーブル２

		TMR0,	///< 8 ビットタイマ０
		TMR1,	///< 8 ビットタイマ１
		TMR2,	///< 8 ビットタイマ２
		TMR3,	///< 8 ビットタイマ３

		CMT0,	///< コンペアマッチタイマー０
		CMT1,	///< コンペアマッチタイマー１

		RTC,	///< リアルタイムクロック

		LPT,	///< ローパワータイマ

		IWDT,	///< 独立ウォッチドッグタイマ

		SCI0,	///< シリアルコミュニケーションインタフェース０
		SCI1,	///< シリアルコミュニケーションインタフェース１
		SCI5,	///< シリアルコミュニケーションインタフェース５
		SCI6,	///< シリアルコミュニケーションインタフェース６
		SCI8,	///< シリアルコミュニケーションインタフェース８
		SCI9,	///< シリアルコミュニケーションインタフェース９
		SCI11,	///< シリアルコミュニケーションインタフェース１１
		SCI12,	///< シリアルコミュニケーションインタフェース１２

		REMC0,	///< リモコン信号受信機能０
		REMC1,	///< リモコン信号受信機能１

		RIIC0,	///< I 2 C バスインタフェース０

		RSPI0,	///< シリアルペリフェラルインタフェース０

		CRC,	///< CRC 演算器（CRC）

		CTSU,	///< 静電容量式タッチセンサ

		S12AD,	///< 12 ビット A/D コンバータ０

		DA,		///< 10 ビット D/A コンバータ

		CMPB,	///< コンパレータＢ

		DOC,	///< データ演算回路（DOC）
	};
}
