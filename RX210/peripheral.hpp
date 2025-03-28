#pragma once
//=====================================================================//
/*!	@file
	@brief	Peripheral Type / ペリフェラル種別 (RX210)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2025 Kunihito Hiramatsu @n
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

		DMAC0,	///< DMA コントローラー０
		DMAC1,	///< DMA コントローラー１
		DMAC2,	///< DMA コントローラー２
		DMAC3,	///< DMA コントローラー３
		DTC,	///< データトランスファコントローラ

		ELC,	///< イベントリンクコントローラ

		MTU0,	///< マルチファンクションタイマパルスユニット０
		MTU1,	///< マルチファンクションタイマパルスユニット１
		MTU2,	///< マルチファンクションタイマパルスユニット２
		MTU3,	///< マルチファンクションタイマパルスユニット３
		MTU4,	///< マルチファンクションタイマパルスユニット４
		MTU5,	///< マルチファンクションタイマパルスユニット５

		POE2,	///< ポートアウトプットイネーブル２

		TPU0,	///< 16 ビットタイマパルスユニット０
		TPU1,	///< 16 ビットタイマパルスユニット１
		TPU2,	///< 16 ビットタイマパルスユニット２
		TPU3,	///< 16 ビットタイマパルスユニット３
		TPU4,	///< 16 ビットタイマパルスユニット４
		TPU5,	///< 16 ビットタイマパルスユニット５

		TMR0,	///< 8 ビットタイマ０
		TMR1,	///< 8 ビットタイマ１
		TMR2,	///< 8 ビットタイマ２
		TMR3,	///< 8 ビットタイマ３

		CMT0,	///< コンペアマッチタイマー０
		CMT1,	///< コンペアマッチタイマー１
		CMT2,	///< コンペアマッチタイマー２
		CMT3,	///< コンペアマッチタイマー３

		RTC,	///< リアルタイムクロック

		IWDT,	///< 独立ウォッチドッグタイマ

		SCI0,	///< シリアルコミュニケーションインタフェース０
		SCI1,	///< シリアルコミュニケーションインタフェース１
		SCI2,	///< シリアルコミュニケーションインタフェース２
		SCI3,	///< シリアルコミュニケーションインタフェース３
		SCI4,	///< シリアルコミュニケーションインタフェース４
		SCI5,	///< シリアルコミュニケーションインタフェース５
		SCI6,	///< シリアルコミュニケーションインタフェース６
		SCI7,	///< シリアルコミュニケーションインタフェース７
		SCI8,	///< シリアルコミュニケーションインタフェース８
		SCI9,	///< シリアルコミュニケーションインタフェース９
		SCI10,	///< シリアルコミュニケーションインタフェース１０
		SCI11,	///< シリアルコミュニケーションインタフェース１１
		SCI12,	///< シリアルコミュニケーションインタフェース１２

		RIIC0,	///< I 2 C バスインタフェース０

		RSPI0,	///< シリアルペリフェラルインタフェース０

		CRC,	///< CRC 演算器（CRC）

		S12AD,	///< 12 ビット A/D コンバータ
		DA,		///< 10 ビット D/A コンバータ

		TEMPS,	///< 温度センサ

		CMPA,	///< コンパレータＡ
		CMPB,	///< コンパレータＢ

		DOC,	///< データ演算回路（DOC）
	};
}
