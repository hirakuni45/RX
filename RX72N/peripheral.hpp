#pragma once
//=====================================================================//
/*!	@file
	@brief	Peripheral Type / ペリフェラル種別 (RX72N)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020, 2024 Kunihito Hiramatsu @n
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
	enum class peripheral : uint16_t {

		CAC,		///< クロック周波数精度測定回路

		ELC,		///< イベントリンクコントローラ

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

		MTU0,		///< マルチファンクションタイマパルスユニット０
		MTU1,		///< マルチファンクションタイマパルスユニット１
		MTU2,		///< マルチファンクションタイマパルスユニット２
		MTU3,		///< マルチファンクションタイマパルスユニット３
		MTU4,		///< マルチファンクションタイマパルスユニット４
		MTU5,		///< マルチファンクションタイマパルスユニット５
		MTU6,		///< マルチファンクションタイマパルスユニット６
		MTU7,		///< マルチファンクションタイマパルスユニット７
		MTU8,		///< マルチファンクションタイマパルスユニット８

		POE3,		///< ポートアウトプットイネーブル（省電源制御がGPTWと共通）
		GPTW0,		///< 汎用 PWM タイマ０
		GPTW1,		///< 汎用 PWM タイマ１
		GPTW2,		///< 汎用 PWM タイマ２
		GPTW3,		///< 汎用 PWM タイマ３

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

		ETHERC0,	///< イーサネットコントローラ 0
		ETHERC1,	///< イーサネットコントローラ 1
		EPTPC,		///< イーサネットコントローラ用 PTP コントローラ
		EPTPC0,		///< イーサネットコントローラ用 PTP コントローラ 0
		EPTPC1,		///< イーサネットコントローラ用 PTP コントローラ 1

		ETHERCA,	///< Ethernet 0 (PHY RMII)カスタムポート接続

		EDMAC0,		///< Ethernet DMA 0
		EDMAC1,		///< Ethernet DMA 1
		PTPEDMAC,	///< PTP Ethernet DMA

		PMGI0,		///< PHY マネジメントインタフェース 0
		PMGI1,		///< PHY マネジメントインタフェース 1

		USB0,		///< USB2.0FSホスト/ファンクションモジュール（USBb）

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

		RIIC0,		///< I 2 C バスインタフェース０（RIICa）
		RIIC1,		///< I 2 C バスインタフェース１（RIICa）
		RIIC2,		///< I 2 C バスインタフェース２（RIICa）

		CAN0,		///< CAN インタフェース（CAN0）
		CAN1,		///< CAN インタフェース（CAN1）
		CAN2,		///< CAN インタフェース（CAN2）

		RSPI0,		///< シリアルペリフェラルインタフェース（RSPIc）
		RSPI1,		///< シリアルペリフェラルインタフェース（RSPIc）
		RSPI2,		///< シリアルペリフェラルインタフェース（RSPIc）

		QSPI,		///< クワッドシリアルペリフェラルインタフェース（QSPI）

		CRC,		///< CRC 演算器

		SSIE0,		///< シリアルサウンドインタフェース（SSIE）
		SSIE1,		///< シリアルサウンドインタフェース（SSIE）

		SDHI,		///< SD ホストインタフェース（SDHI）

		MMCIF,		///< マルチメディアカードインタフェース（MMCIF）

		PDC,		///< パラレルデータキャプチャユニット

		GLCDC,		///< グラフィックスＬＣＤコントローラ
		DRW2D,		///< ２Ｄ描画エンジン

		S12AD,		///< 12 ビット A/D コンバータ（S12ADC）
		S12AD1,		///< 12 ビット A/D コンバータ（S12ADC）

		R12DA,		///< 12 ビット D/A コンバータ（R12DA）

		TEMPS,		///< 温度センサ

		DOC,		///< データ演算回路

		RAM,		///< RAM (512K)
		EXTRAM,		///< 拡張 RAM (512K)
		ECCRAM,		///< ECC RAM (32K)
		STBRAM,		///< Standby RAM (8K)
	};
}
