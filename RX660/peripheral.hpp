#pragma once
//=====================================================================//
/*!	@file
	@brief	Peripheral Type / ペリフェラル種別 (RX660)
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
		@brief  ペリフェラル型（種別）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class peripheral : uint16_t {

		CAC,		///< Clock Frequency Accuracy Measurement Circuit / クロック周波数精度測定回路

		DMAC0,		///< DMA Controller channel 0 / DMA コントローラ・チャネル０
		DMAC1,		///< DMA Controller channel 1 / DMA コントローラ・チャネル１
		DMAC2,		///< DMA Controller channel 2 / DMA コントローラ・チャネル２
		DMAC3,		///< DMA Controller channel 3 / DMA コントローラ・チャネル３
		DMAC4,		///< DMA Controller channel 4 / DMA コントローラ・チャネル４
		DMAC5,		///< DMA Controller channel 5 / DMA コントローラ・チャネル５
		DMAC6,		///< DMA Controller channel 6 / DMA コントローラ・チャネル６
		DMAC7,		///< DMA Controller channel 7 / DMA コントローラ・チャネル７
		DTC,		///< Data Transfer Controller / データトランスファコントローラ

		ELC,		///< Event Link Controller / イベントリンクコントローラ

		MTU0,		///< Multi-Function Timer Pulse Unit 0 / マルチファンクションタイマパルスユニット０
		MTU1,		///< Multi-Function Timer Pulse Unit 1 / マルチファンクションタイマパルスユニット１
		MTU2,		///< Multi-Function Timer Pulse Unit 2 / マルチファンクションタイマパルスユニット２
		MTU3,		///< Multi-Function Timer Pulse Unit 3 / マルチファンクションタイマパルスユニット３
		MTU4,		///< Multi-Function Timer Pulse Unit 4 / マルチファンクションタイマパルスユニット４
		MTU5,		///< Multi-Function Timer Pulse Unit 5 / マルチファンクションタイマパルスユニット５
		MTU6,		///< Multi-Function Timer Pulse Unit 6 / マルチファンクションタイマパルスユニット６
		MTU7,		///< Multi-Function Timer Pulse Unit 7 / マルチファンクションタイマパルスユニット７
		MTU8,		///< Multi-Function Timer Pulse Unit 8 / マルチファンクションタイマパルスユニット８

		POE3,		///< Port Output Enable 3 / ポートアウトプットイネーブル３

		TMR0,		///< 8-Bit Timer 0 / 8 ビットタイマ０
		TMR1,		///< 8-Bit Timer 1 / 8 ビットタイマ１
		TMR2,		///< 8-Bit Timer 2 / 8 ビットタイマ２
		TMR3,		///< 8-Bit Timer 3 / 8 ビットタイマ３

		CMT0,		///< Compare Match Timer 0 / コンペアマッチタイマ０
		CMT1,		///< Compare Match Timer 1 / コンペアマッチタイマ１
		CMT2,		///< Compare Match Timer 2 / コンペアマッチタイマ２
		CMT3,		///< Compare Match Timer 3 / コンペアマッチタイマ３

		CMTW0,		///< Compare Match Timer W0 / コンペアマッチタイマＷ０
		CMTW1,		///< Compare Match Timer W1 / コンペアマッチタイマＷ１

		RTC,		///< Realtime Clock / リアルタイムクロック

		WDTA,		///< Watchdog Timer / ウォッチドッグタイマ
		IWDT,		///< Independent Watchdog Timer / 独立ウォッチドッグタイマ

		SCI0,		///< Serial Communications Interface 0 / シリアルコミュニケーションインタフェース０
		SCI1,		///< Serial Communications Interface 1 / シリアルコミュニケーションインタフェース１
		SCI2,		///< Serial Communications Interface 2 / シリアルコミュニケーションインタフェース２
		SCI3,		///< Serial Communications Interface 3 / シリアルコミュニケーションインタフェース３
		SCI4,		///< Serial Communications Interface 4 / シリアルコミュニケーションインタフェース４
		SCI5,		///< Serial Communications Interface 5 / シリアルコミュニケーションインタフェース５
		SCI6,		///< Serial Communications Interface 6 / シリアルコミュニケーションインタフェース６
		SCI7,		///< Serial Communications Interface 7 / シリアルコミュニケーションインタフェース７
		SCI8,		///< Serial Communications Interface 8 / シリアルコミュニケーションインタフェース８
		SCI9,		///< Serial Communications Interface 9 / シリアルコミュニケーションインタフェース９
		SCI10,		///< Serial Communications Interface 10 / シリアルコミュニケーションインタフェース１０
		SCI11,		///< Serial Communications Interface 11 / シリアルコミュニケーションインタフェース１１
		SCI12,		///< Serial Communications Interface 12 / シリアルコミュニケーションインタフェース１２

		RSCI10,		///< (R)Serial Communications Interface 0 / Ｒシリアルコミュニケーションインタフェース１０
		RSCI11,		///< (R)Serial Communications Interface 1 / Ｒシリアルコミュニケーションインタフェース１１

		RIIC0,		///< I2C-bus Interface 0 / I2C バスインタフェース０
		RIIC2,		///< I2C-bus Interface 2 / I2C バスインタフェース２

		CANFD0,		///< CANFD-Lite Module 0 / CANFD-Lite モジュール０

		RSPI0,		///< Serial Peripheral Interface 0 / シリアルペリフェラルインタフェース０

		CRC,		///< CRC Calculator / CRC 演算器

		REMC0,		///< Remote Control Signal Receiver / リモコン信号受信機能

		S12AD,		///< 12-Bit A/D Converter / 12 ビット A/D コンバータ

		R12DA,		///< 12-Bit D/A Converter / 12 ビット D/A コンバータ

		TEMPS,		///< Temperature Sensor / 温度センサ

		CMPC0,		///< Comparator C0 / コンパレータＣ０
		CMPC1,		///< Comparator C1 / コンパレータＣ１
		CMPC2,		///< Comparator C2 / コンパレータＣ２
		CMPC3,		///< Comparator C3 / コンパレータＣ３

		DOC,		///< Data Operation Circuit / データ演算回路
	};
}
