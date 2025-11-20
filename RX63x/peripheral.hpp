#pragma once
//=====================================================================//
/*!	@file
	@brief	Peripheral Type / ペリフェラル種別 (RX631/RX63N)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2025 Kunihito Hiramatsu @n
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

		LVDA,		///< Voltage Detection Circuit / 電圧検出回路

		MCK,		///< Frequency Measurement Circuit / 周波数測定機能

		MPU,		///< Memory-Protection Unit / メモリプロテクションユニット

		DMAC0,		///< DMA Controller channel 0 / DMA コントローラ・チャネル０
		DMAC1,		///< DMA Controller channel 1 / DMA コントローラ・チャネル１
		DMAC2,		///< DMA Controller channel 2 / DMA コントローラ・チャネル２
		DMAC3,		///< DMA Controller channel 3 / DMA コントローラ・チャネル３
		DTC,		///< Data Transfer Controller / データトランスファコントローラ

		EXDMAC0,	///< EXDMA Controller channel 0 / EXDMA コントローラ・チャネル０
		EXDMAC1,	///< EXDMA Controller channel 1 / EXDMA コントローラ・チャネル１

		MTU0,		///< Multi-Function Timer Pulse Unit 0 / マルチファンクションタイマパルスユニット０
		MTU1,		///< Multi-Function Timer Pulse Unit 1 / マルチファンクションタイマパルスユニット１
		MTU2,		///< Multi-Function Timer Pulse Unit 2 / マルチファンクションタイマパルスユニット２
		MTU3,		///< Multi-Function Timer Pulse Unit 3 / マルチファンクションタイマパルスユニット３
		MTU4,		///< Multi-Function Timer Pulse Unit 4 / マルチファンクションタイマパルスユニット４
		MTU5,		///< Multi-Function Timer Pulse Unit 5 / マルチファンクションタイマパルスユニット５

		POE2,		///< Port Output Enable 2 / ポートアウトプットイネーブル

		TPU0,		///< 16-Bit Timer Pulse Unit 0 / 16 ビットタイマパルスユニット０
		TPU1,		///< 16-Bit Timer Pulse Unit 1 / 16 ビットタイマパルスユニット１
		TPU2,		///< 16-Bit Timer Pulse Unit 2 / 16 ビットタイマパルスユニット２
		TPU3,		///< 16-Bit Timer Pulse Unit 3 / 16 ビットタイマパルスユニット３
		TPU4,		///< 16-Bit Timer Pulse Unit 4 / 16 ビットタイマパルスユニット４
		TPU5,		///< 16-Bit Timer Pulse Unit 5 / 16 ビットタイマパルスユニット５
		TPU6,		///< 16-Bit Timer Pulse Unit 6 / 16 ビットタイマパルスユニット６
		TPU7,		///< 16-Bit Timer Pulse Unit 7 / 16 ビットタイマパルスユニット７
		TPU8,		///< 16-Bit Timer Pulse Unit 8 / 16 ビットタイマパルスユニット８
		TPU9,		///< 16-Bit Timer Pulse Unit 9 / 16 ビットタイマパルスユニット９
		TPU10,		///< 16-Bit Timer Pulse Unit 10 / 16 ビットタイマパルスユニット１０
		TPU11,		///< 16-Bit Timer Pulse Unit 11 / 16 ビットタイマパルスユニット１１

		PPG0,		///< Programmable Pulse Generator 0 / プログラマブルパルスジェネレータ０
		PPG1,		///< Programmable Pulse Generator 1 / プログラマブルパルスジェネレータ１

		TMR0,		///< 8-Bit Timer 0 / 8 ビットタイマ０
		TMR1,		///< 8-Bit Timer 1 / 8 ビットタイマ１
		TMR2,		///< 8-Bit Timer 2 / 8 ビットタイマ２
		TMR3,		///< 8-Bit Timer 3 / 8 ビットタイマ３

		CMT0,		///< Compare Match Timer 0 / コンペアマッチタイマ０
		CMT1,		///< Compare Match Timer 1 / コンペアマッチタイマ１
		CMT2,		///< Compare Match Timer 2 / コンペアマッチタイマ２
		CMT3,		///< Compare Match Timer 3 / コンペアマッチタイマ３

		RTC,		///< Realtime Clock / リアルタイムクロック

		WDTA,		///< Watchdog Timer / ウォッチドッグタイマ
		IWDT,		///< Independent Watchdog Timer / 独立ウォッチドッグタイマ
#if defined(SIG_RX63N)
		ETHERC0,	///< Ethernet Controller 0 / イーサネットコントローラ０
		EDMAC0,		///< DMA Controller for the Ethernet Controller 0 / イーサネットコントローラ用 DMA コントローラ０
#endif
		USB0,		///< USB 2.0 FS Host/Function Module 0 / USB 2.0 FS ホスト/ファンクションモジュール０
		USB1,		///< USB 2.0 FS Host/Function Module 1 / USB 2.0 FS ホスト/ファンクションモジュール１

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

		RIIC0,		///< I2C-bus Interface 0 / I2C バスインタフェース０
		RIIC1,		///< I2C-bus Interface 1 / I2C バスインタフェース１
		RIIC2,		///< I2C-bus Interface 2 / I2C バスインタフェース２
		RIIC3,		///< I2C-bus Interface 3 / I2C バスインタフェース３

		CAN0,		///< CAN Module 0 / CAN モジュール０
		CAN1,		///< CAN Module 1 / CAN モジュール１
		CAN2,		///< CAN Module 2 / CAN モジュール２

		RSPI0,		///< Serial Peripheral Interface 0 / シリアルペリフェラルインタフェース０
		RSPI1,		///< Serial Peripheral Interface 1 / シリアルペリフェラルインタフェース１
		RSPI2,		///< Serial Peripheral Interface 2 / シリアルペリフェラルインタフェース２

		IEB,		///< IEBus Controller / IEBus™ コントローラ

		CRC,		///< CRC Calculator / CRC 演算器

		PDC,		///< Parallel Data Capture Unit / パラレルデータキャプチャユニット

		S12AD,		///< 12-Bit A/D Converter / 12 ビット A/D コンバータ

		AD,			///< 10-Bit A/D Converter / 10 ビット A/D コンバータ

		DA,			///< 10-Bit D/A Converter / 10 ビット D/A コンバータ

		TEMPS,		///< Temperature Sensor / 温度センサ
	};
}
