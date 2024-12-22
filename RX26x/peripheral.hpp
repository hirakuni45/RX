#pragma once
//=====================================================================//
/*!	@file
	@brief	Peripheral Type / ペリフェラル種別 (RX260/RX261)
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

		CAC,		///< クロック周波数精度測定回路

		DMAC0,		///< DMA コントローラ・チャネル０
		DMAC1,		///< DMA コントローラ・チャネル１
		DMAC2,		///< DMA コントローラ・チャネル２
		DMAC3,		///< DMA コントローラ・チャネル３
		DTC,		///< データトランスファコントローラ (DTCb)

		ELC,		///< イベントリンクコントローラ (ELC)

		GPTW0,		///< 汎用 PWM タイマ (GPTWa) 0
		GPTW1,		///< 汎用 PWM タイマ (GPTWa) 1
		GPTW2,		///< 汎用 PWM タイマ (GPTWa) 2
		GPTW3,		///< 汎用 PWM タイマ (GPTWa) 3
		GPTW4,		///< 汎用 PWM タイマ (GPTWa) 4
		GPTW5,		///< 汎用 PWM タイマ (GPTWa) 5
		GPTW6,		///< 汎用 PWM タイマ (GPTWa) 6
		GPTW7,		///< 汎用 PWM タイマ (GPTWa) 7

		POEG,		///< GPTW 用ポートアウトプットイネーブル (POEG)

		TMR0,		///< 8 ビットタイマ０
		TMR1,		///< 8 ビットタイマ１
		TMR2,		///< 8 ビットタイマ２
		TMR3,		///< 8 ビットタイマ３

		CMT0,		///< コンペアマッチタイマ０（CMT）
		CMT1,		///< コンペアマッチタイマ１（CMT）
		CMT2,		///< コンペアマッチタイマ２（CMT）
		CMT3,		///< コンペアマッチタイマ３（CMT）

		RTC,		///< リアルタイムクロック (RTCBa)

		LPT,		///< ローパワータイマ (LPTa)

		WDTA,		///< ウォッチドッグタイマ (WDTA)
		IWDT,		///< 独立ウォッチドッグタイマ (IWDTa)

		USB0,		///< USB2.0FS ホスト / ファンクションモジュール (USBe)

		SCI1,		///< シリアルコミュニケーションインタフェース (SCIk) 1
		SCI5,		///< シリアルコミュニケーションインタフェース (SCIk) 5
		SCI6,		///< シリアルコミュニケーションインタフェース (SCIk) 6
		RSCI0,		///< シリアルコミュニケーションインタフェース (RSCI) 0
		RSCI8,		///< シリアルコミュニケーションインタフェース (RSCI) 8
		RSCI9,		///< シリアルコミュニケーションインタフェース (RSCI) 9
		SCI12,		///< シリアルコミュニケーションインタフェース (SCIh) 12

		RIIC0,		///< I2C バスインタフェース (RIICa)

		CANFD0,		///< CAN FD モジュール (CANFD)

		RSPI0,		///< シリアルペリフェラルインタフェース (RSPId)

		CRC,		///< CRC 演算器 (CRCA)

		REMC0,		///< リモコン信号受信機能 (REMCa)

		RSIP,		///< Renesas Secure IP (RSIP-E11A)

		CTSU,		///< 静電容量式タッチセンサ (CTSU2SLa)

		S12AD,		///< 12 ビット A/D コンバータ（S12ADC）

		DA,			///< 8 ビット D/A コンバータ（DAa）

		TEMPS,		///< 温度センサ（TEMPS）

		CMPB,		///< コンパレーターＢ

		DOC,		///< データ演算回路 (DOC)
	};
}
