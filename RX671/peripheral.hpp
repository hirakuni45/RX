#pragma once
//=====================================================================//
/*!	@file
	@brief	RX671 グループ・ペリフェラル
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ペリフェラル種別
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class peripheral : uint16_t {

		CAC,		///< クロック周波数精度測定回路

		DMAC0,		///< DMA コントローラ・チャネル０
		DMAC1,		///< DMA コントローラ・チャネル１
		DMAC2,		///< DMA コントローラ・チャネル２
		DMAC3,		///< DMA コントローラ・チャネル３
		DMAC4,		///< DMA コントローラ・チャネル４
		DMAC5,		///< DMA コントローラ・チャネル５
		DMAC6,		///< DMA コントローラ・チャネル６
		DMAC7,		///< DMA コントローラ・チャネル７
		DTC,		///< データトランスファコントローラ

		EXDMAC0,	///< EXDMA コントローラ・チャネル０
		EXDMAC1,	///< EXDMA コントローラ・チャネル１

		ELC,		///< イベントリンクコントローラ

		MTU0,		///< マルチファンクションタイマパルスユニット０
		MTU1,		///< マルチファンクションタイマパルスユニット１
		MTU2,		///< マルチファンクションタイマパルスユニット２
		MTU3,		///< マルチファンクションタイマパルスユニット３
		MTU4,		///< マルチファンクションタイマパルスユニット４
		MTU5,		///< マルチファンクションタイマパルスユニット５
		MTU6,		///< マルチファンクションタイマパルスユニット６
		MTU7,		///< マルチファンクションタイマパルスユニット７
		MTU8,		///< マルチファンクションタイマパルスユニット８

		POE3,		///< ポートアウトプットイネーブル

		TPU0,		///< 16 ビットタイマパルスユニット０
		TPU1,		///< 16 ビットタイマパルスユニット１
		TPU2,		///< 16 ビットタイマパルスユニット２
		TPU3,		///< 16 ビットタイマパルスユニット３
		TPU4,		///< 16 ビットタイマパルスユニット４
		TPU5,		///< 16 ビットタイマパルスユニット５

		PPG0,		///< プログラマブルパルスジェネレータ０
		PPG1,		///< プログラマブルパルスジェネレータ１

		TMR0,		///< 8 ビットタイマ０
		TMR1,		///< 8 ビットタイマ１
		TMR2,		///< 8 ビットタイマ２
		TMR3,		///< 8 ビットタイマ３

		CMT0,		///< コンペアマッチタイマ０（CMT）
		CMT1,		///< コンペアマッチタイマ１（CMT）
		CMT2,		///< コンペアマッチタイマ２（CMT）
		CMT3,		///< コンペアマッチタイマ３（CMT）

		CMTW0,		///< コンペアマッチタイマＷ０（CMTW）
		CMTW1,		///< コンペアマッチタイマＷ１（CMTW）

		RTC,		///< リアルタイムクロック

		WDTA,		///< ウォッチドッグタイマ
		IWDT,		///< 独立ウォッチドッグタイマ

		USB0,		///< USB2.0FSホスト/ファンクションモジュール（USBb）
		USB1,		///< USB2.0FSホスト/ファンクションモジュール（USBb）

		SCI0,		///< シリアルコミュニケーションインタフェース (P20:TXD0, P21:RXD0)
		SCI1,		///< シリアルコミュニケーションインタフェース (PF0:TXD1, PF2:RXD1)
		SCI2,		///< シリアルコミュニケーションインタフェース (P13:TXD2, P12:RXD2)
		SCI3,		///< シリアルコミュニケーションインタフェース (P23:TXD3, P25:RXD3)
		SCI4,		///< シリアルコミュニケーションインタフェース (PB1:TXD4, PB0:RXD4)
		SCI5,		///< シリアルコミュニケーションインタフェース (PA4:TXD5, PA2:RXD5)
		SCI6,		///< シリアルコミュニケーションインタフェース (P00:TXD6, P01:RXD6)
		SCI7,		///< シリアルコミュニケーションインタフェース (P90:TXD7, P92:RXD7)
		SCI8,		///< シリアルコミュニケーションインタフェース
		SCI9,		///< シリアルコミュニケーションインタフェース
		SCI10,		///< シリアルコミュニケーションインタフェース
		SCI11,		///< シリアルコミュニケーションインタフェース
		SCI12,		///< シリアルコミュニケーションインタフェース

		RSCI10,		///< シリアルコミュニケーションインタフェース (RSCI10)
		RSCI11,		///< シリアルコミュニケーションインタフェース (RSCI11)

		RIIC0,		///< I 2 C バスインタフェース０（RIIC0a）
		RIIC1,		///< I 2 C バスインタフェース１（RIIC1a）
		RIIC2,		///< I 2 C バスインタフェース２（RIIC2a）

		RIICHS0,	///< ハイスピード I2C バスインタフェース

		CAN0,		///< CAN インタフェース（CAN0）
		CAN1,		///< CAN インタフェース（CAN1）

		RSPI0,		///< シリアルペリフェラルインタフェース（RSPI0）
		RSPI1,		///< シリアルペリフェラルインタフェース（RSPI1）
		RSPI2,		///< シリアルペリフェラルインタフェース（RSPI2）

		RSPIA0,		///< シリアルペリフェラルインタフェース (RSPIA)

		QSPIX,		///< クワッド SPI メモリインタフェース (QSPIX)

		CRC,		///< CRC 演算器（CRCA）

		SDHI,		///< SD ホストインタフェース（SDHI）

		SSIE0,		///< シリアルサウンドインタフェース (SSIE)

		REMC0,		///< リモコン信号受信機能 (REMCa)

		CTSU,		///< 静電容量式タッチセンサ (CTSUa)

		TSIP,		///< Trusted Secure IP (TSIP)

		S12AD,		///< 12 ビット A/D コンバータ（S12ADFa）
		S12AD1,		///< 12 ビット A/D コンバータ（S12ADFa）

		R12DA,		///< 12 ビット D/A コンバータ（R12DA）

		TEMPS,		///< 温度センサ（TEMPS）

		DOC,		///< データ演算回路 (DOCA)

		STBRAM,		///< スタンバイ RAM
	};
}
