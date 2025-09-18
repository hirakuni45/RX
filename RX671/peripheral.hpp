#pragma once
//=====================================================================//
/*!	@file
	@brief	Peripheral Type / ペリフェラル種別 (RX671)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023, 2025 Kunihito Hiramatsu @n
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

		VBATT,		///< Battery Backup Function / バッテリバックアップ機能

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

		RSCI10,		///< (R)Serial Communications Interface 0 / Ｒシリアルコミュニケーションインタフェース１０
		RSCI11,		///< (R)Serial Communications Interface 1 / Ｒシリアルコミュニケーションインタフェース１１

		RIIC0,		///< I2C-bus Interface 0 / I2C バスインタフェース０
		RIIC1,		///< I2C-bus Interface 1 / I2C バスインタフェース１
		RIIC2,		///< I2C-bus Interface 2 / I2C バスインタフェース２

		RIICHS0,	///< High-Speed I2C-bus Interface / ハイスピード I2C バスインタフェース

		CAN0,		///< CAN Module 0 / CAN インタフェース０
		CAN1,		///< CAN Module 1 / CAN インタフェース１

		RSPI0,		///< Serial Peripheral Interface 0 / シリアルペリフェラルインタフェース０
		RSPI1,		///< Serial Peripheral Interface 1 / シリアルペリフェラルインタフェース１
		RSPI2,		///< Serial Peripheral Interface 2 / シリアルペリフェラルインタフェース２

		RSPIA0,		///< Serial Peripheral Interface A / シリアルペリフェラルインタフェースＡ

		QSPIX,		///< Quad-SPI Memory Interface / クワッド SPI メモリインタフェース

		CRC,		///< CRC Calculator / CRC 演算器

		SDHI,		///< SD Host Interface / SD ホストインタフェース

		SSIE0,		///< Serial Sound Interface 0 / シリアルサウンドインタフェース０

		REMC0,		///< Remote Control Signal Receiver / リモコン信号受信機能

		CTSU,		///< Capacitive Touch Sensing Unit / 静電容量式タッチセンサ

		TSIP,		///< Trusted Secure IP / Trusted Secure IP

		S12AD,		///< 12-Bit A/D Converter / 12 ビット A/D コンバータ
		S12AD1,		///< 12-Bit A/D Converter 1 / 12 ビット A/D コンバータ１

		TEMPS,		///< Temperature Sensor / 温度センサ

		DOC,		///< Data Operation Circuit / データ演算回路

		STBRAM,		///< Standby RAM / スタンバイ RAM
	};
}
