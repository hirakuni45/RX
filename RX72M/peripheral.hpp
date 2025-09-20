#pragma once
//=====================================================================//
/*!	@file
	@brief	Peripheral Type / ペリフェラル種別 (RX72M)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2025 Kunihito Hiramatsu @n
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
	enum class peripheral : uint16_t {

		CAC,		///< Clock Frequency Accuracy Measurement Circuit / クロック周波数精度測定回路

		ELC,		///< Event Link Controller / イベントリンクコントローラ

		DMAC0,		///< DMA Controller channel 0 / DMA コントローラ・チャネル０
		DMAC1,		///< DMA Controller channel 1 / DMA コントローラ・チャネル１
		DMAC2,		///< DMA Controller channel 2 / DMA コントローラ・チャネル２
		DMAC3,		///< DMA Controller channel 3 / DMA コントローラ・チャネル３
		DMAC4,		///< DMA Controller channel 4 / DMA コントローラ・チャネル４
		DMAC5,		///< DMA Controller channel 5 / DMA コントローラ・チャネル５
		DMAC6,		///< DMA Controller channel 6 / DMA コントローラ・チャネル６
		DMAC7,		///< DMA Controller channel 7 / DMA コントローラ・チャネル７
		DTC,		///< Data Transfer Controller / データトランスファコントローラ

		EXDMAC0,	///< EXDMA Controller channel 0 / EXDMA コントローラ・チャネル０
		EXDMAC1,	///< EXDMA Controller channel 1 / EXDMA コントローラ・チャネル１

		MTU0,		///< Multi-Function Timer Pulse Unit 0 / マルチファンクションタイマパルスユニット０
		MTU1,		///< Multi-Function Timer Pulse Unit 1 / マルチファンクションタイマパルスユニット１
		MTU2,		///< Multi-Function Timer Pulse Unit 2 / マルチファンクションタイマパルスユニット２
		MTU3,		///< Multi-Function Timer Pulse Unit 3 / マルチファンクションタイマパルスユニット３
		MTU4,		///< Multi-Function Timer Pulse Unit 4 / マルチファンクションタイマパルスユニット４
		MTU5,		///< Multi-Function Timer Pulse Unit 5 / マルチファンクションタイマパルスユニット５
		MTU6,		///< Multi-Function Timer Pulse Unit 6 / マルチファンクションタイマパルスユニット６
		MTU7,		///< Multi-Function Timer Pulse Unit 7 / マルチファンクションタイマパルスユニット７
		MTU8,		///< Multi-Function Timer Pulse Unit 8 / マルチファンクションタイマパルスユニット８

		POE3,		///< Port Output Enable 3 / ポートアウトプットイネーブル
		GPTW0,		///< General PWM Timer 0 / 汎用 PWM タイマ０
		GPTW1,		///< General PWM Timer 1 / 汎用 PWM タイマ１
		GPTW2,		///< General PWM Timer 2 / 汎用 PWM タイマ２
		GPTW3,		///< General PWM Timer 3 / 汎用 PWM タイマ３

		TPU0,		///< 16-Bit Timer Pulse Unit 0 / 16 ビットタイマパルスユニット０
		TPU1,		///< 16-Bit Timer Pulse Unit 1 / 16 ビットタイマパルスユニット１
		TPU2,		///< 16-Bit Timer Pulse Unit 2 / 16 ビットタイマパルスユニット２
		TPU3,		///< 16-Bit Timer Pulse Unit 3 / 16 ビットタイマパルスユニット３
		TPU4,		///< 16-Bit Timer Pulse Unit 4 / 16 ビットタイマパルスユニット４
		TPU5,		///< 16-Bit Timer Pulse Unit 5 / 16 ビットタイマパルスユニット５

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

		CMTW0,		///< Compare Match Timer W 0 / コンペアマッチタイマＷ０
		CMTW1,		///< Compare Match Timer W 1 / コンペアマッチタイマＷ１

		RTC,		///< Realtime Clock / リアルタイムクロック

		WDTA,		///< Watchdog Timer / ウォッチドッグタイマ
		IWDT,		///< Independent Watchdog Timer / 独立ウォッチドッグタイマ

		ETHERC0,	///< Ethernet Controller 0 / イーサネットコントローラ０
		ETHERC1,	///< Ethernet Controller 1 / イーサネットコントローラ１
		EPTPC,		///< PTP Module for the Ethernet Controller / イーサネットコントローラ用 PTP コントローラ
		EPTPC0,		///< PTP Module for the Ethernet Controller 0 / イーサネットコントローラ用 PTP コントローラ０
		EPTPC1,		///< PTP Module for the Ethernet Controller 1 / イーサネットコントローラ用 PTP コントローラ１

		EDMAC0,		///< DMA Controller for the Ethernet Controller 0 / イーサネットコントローラ用 DMA コントローラ０
		EDMAC1,		///< DMA Controller for the Ethernet Controller 1 / イーサネットコントローラ用 DMA コントローラ１
		PTPEDMAC,	///< PTP Ethernet DMA / PTP イーサネット DMA

		PMGI0,		///< PHY Management Interface 0 / PHY マネジメントインタフェース０
		PMGI1,		///< PHY Management Interface 1 / PHY マネジメントインタフェース１

		ESC,		///< EtherCAT Slave Controller / EtherCAT スレーブコントローラ

		USB0,		///< USB 2.0 FS Host/Function Module 0 / USB 2.0 FS ホスト/ファンクションモジュール

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

		CAN0,		///< CAN Module 0 / CAN インタフェース０
		CAN1,		///< CAN Module 1 / CAN インタフェース１
		CAN2,		///< CAN Module 2 / CAN インタフェース２

		RSPI0,		///< Serial Peripheral Interface 0 / シリアルペリフェラルインタフェース０
		RSPI1,		///< Serial Peripheral Interface 1 / シリアルペリフェラルインタフェース１
		RSPI2,		///< Serial Peripheral Interface 2 / シリアルペリフェラルインタフェース２

		QSPI,		///< Quad-SPI Memory Interface / クワッドシリアルペリフェラルインタフェース

		CRC,		///< CRC Calculator / CRC 演算器

		SSIE0,		///< Serial Sound Interface 0 / シリアルサウンドインタフェース０
		SSIE1,		///< Serial Sound Interface 1 / シリアルサウンドインタフェース１

		SDHI,		///< SD Host Interface / SD ホストインタフェース

		MMCIF,		///< MultiMediaCard Interface / マルチメディアカードインタフェース

		PDC,		///< Parallel Data Capture Unit / パラレルデータキャプチャユニット

		GLCDC,		///< Graphic LCD Controller / グラフィックスＬＣＤコントローラ
		DRW2D,		///< 2D Drawing Engine / ２Ｄ描画エンジン

		TSIP,		///< Trusted Secure IP / Trusted Secure IP

		DSMIF0,		///< ΔΣ Modulator Interface 0 / ΔΣモジュレータインターフェース０
		DSMIF1,		///< ΔΣ Modulator Interface 1 / ΔΣモジュレータインターフェース１

		S12AD,		///< 12-Bit A/D Converter / 12 ビット A/D コンバータ
		S12AD1,		///< 12-Bit A/D Converter 1 / 12 ビット A/D コンバータ１

		R12DA,		///< 12-Bit D/A Converter / 12 ビット D/A コンバータ

		TEMPS,		///< Temperature Sensor / 温度センサ

		DOC,		///< Data Operation Circuit / データ演算回路

		RAM,		///< RAM (512K) / RAM (512K)
		EXTRAM,		///< Expansion RAM (512K) / 拡張 RAM (512K)
		ECCRAM,		///< ECC RAM (32K) / ECC RAM (32K)
		STBRAM,		///< Standby RAM (8K) / スタンバイ RAM (8K)
	};
}
