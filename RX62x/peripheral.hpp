#pragma once
//=====================================================================//
/*!	@file
	@brief	Peripheral Type / ペリフェラル種別 (RX621/RX62N)
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

		DMAC0,	///< DMA Controller channel 0 / DMA コントローラ０
		DMAC1,	///< DMA Controller channel 1 / DMA コントローラ１
		DMAC2,	///< DMA Controller channel 2 / DMA コントローラ２
		DMAC3,	///< DMA Controller channel 3 / DMA コントローラ３
		DTC,	///< Data Transfer Controller / データトランスファコントローラ

		EXDMAC0,	///< EXDMA Controller channel 0 / EXDMA コントローラ０
		EXDMAC1,	///< EXDMA Controller channel 1 / EXDMA コントローラ１

		MTU0,	///< Multi-Function Timer Pulse Unit 0 / マルチファンクションタイマパルスユニット０
		MTU1,	///< Multi-Function Timer Pulse Unit 1 / マルチファンクションタイマパルスユニット１
		MTU2,	///< Multi-Function Timer Pulse Unit 2 / マルチファンクションタイマパルスユニット２
		MTU3,	///< Multi-Function Timer Pulse Unit 3 / マルチファンクションタイマパルスユニット３
		MTU4,	///< Multi-Function Timer Pulse Unit 4 / マルチファンクションタイマパルスユニット４
		MTU5,	///< Multi-Function Timer Pulse Unit 5 / マルチファンクションタイマパルスユニット５
		MTU6,	///< Multi-Function Timer Pulse Unit 6 / マルチファンクションタイマパルスユニット６
		MTU7,	///< Multi-Function Timer Pulse Unit 7 / マルチファンクションタイマパルスユニット７
		MTU8,	///< Multi-Function Timer Pulse Unit 8 / マルチファンクションタイマパルスユニット８
		MTU9,	///< Multi-Function Timer Pulse Unit 9 / マルチファンクションタイマパルスユニット９
		MTU10,	///< Multi-Function Timer Pulse Unit 10 / マルチファンクションタイマパルスユニット１０
		MTU11,	///< Multi-Function Timer Pulse Unit 11 / マルチファンクションタイマパルスユニット１１

		POE2,	///< ポートアウトプットイネーブル２

		PPG0,	///< プログラマブルパルスジェネレータ０
		PPG1,	///< プログラマブルパルスジェネレータ１

		TMR0,	///< 8 ビットタイマ０
		TMR1,	///< 8 ビットタイマ１
		TMR2,	///< 8 ビットタイマ２
		TMR3,	///< 8 ビットタイマ３

		CMT0,	///< Compare Match Timer 0 / コンペアマッチタイマー０
		CMT1,	///< Compare Match Timer 1 / コンペアマッチタイマー１
		CMT2,	///< Compare Match Timer 2 / コンペアマッチタイマー２
		CMT3,	///< Compare Match Timer 3 / コンペアマッチタイマー３

		RTC,	///< Realtime Clock / リアルタイムクロック

		WDT,	///< Watchdog Timer / ウォッチドッグタイマ
		IWDT,	///< Independent Watchdog Timer / 独立ウォッチドッグタイマ

		ETHERC,	///< Ethernet Controller / イーサネットコントローラ
		EDMAC,	///< DMA Controller for the Ethernet Controller / イーサネットコントローラ用 DMA コントローラ

		USB0,	///< USB 2.0 Host/Function Module 0 / USB 2.0 ホスト／ファンクションモジュール０
		USB1,	///< USB 2.0 Host/Function Module 1 / USB 2.0 ホスト／ファンクションモジュール１

		SCI0,	///< Serial Communications Interface 0 / シリアルコミュニケーションインタフェース０
		SCI1,	///< Serial Communications Interface 1 / シリアルコミュニケーションインタフェース１
		SCI2,	///< Serial Communications Interface 2 / シリアルコミュニケーションインタフェース２
		SCI3,	///< Serial Communications Interface 3 / シリアルコミュニケーションインタフェース３
		SCI5,	///< Serial Communications Interface 5 / シリアルコミュニケーションインタフェース５
		SCI6,	///< Serial Communications Interface 6 / シリアルコミュニケーションインタフェース６

		RIIC0,	///< I2C-bus Interface 0 / I2C バスインタフェース０
		RIIC1,	///< I2C-bus Interface 1 / I2C バスインタフェース１

		CAN0,	///< CAN Module 0 / CAN モジュール０

		RSPI0,	///< Serial Peripheral Interface 0 / シリアルペリフェラルインタフェース０
		RSPI1,	///< Serial Peripheral Interface 1 / シリアルペリフェラルインタフェース１

		CRC,	///< CRC Calculator / CRC 演算器

		S12AD,	///< 12-Bit A/D Converter / 12 ビット A/D コンバータ

		AD0,	///< 10-Bit A/D Converter 0 / 10 ビット A/D コンバータ０
		AD1,	///< 10-Bit A/D Converter 1 / 10 ビット A/D コンバータ１

		DA,		///< 10-Bit D/A Converter / 10 ビット D/A コンバータ
	};
}
