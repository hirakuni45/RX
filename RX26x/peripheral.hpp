#pragma once
//=====================================================================//
/*!	@file
	@brief	Peripheral Type / ペリフェラル種別 (RX260/RX261)
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
		@brief  Peripheral Type / ペリフェラル型（種別）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class peripheral : uint8_t {

		CAC,		///< Clock Frequency Accuracy Measurement Circuit / クロック周波数精度測定回路

		DMAC0,		///< DMA Controller channel 0 / DMA コントローラ・チャネル０
		DMAC1,		///< DMA Controller channel 1 / DMA コントローラ・チャネル１
		DMAC2,		///< DMA Controller channel 2 / DMA コントローラ・チャネル２
		DMAC3,		///< DMA Controller channel 3 / DMA コントローラ・チャネル３
		DTC,		///< Data Transfer Controller / データトランスファコントローラ

		ELC,		///< Event Link Controller / イベントリンクコントローラ (ELC)

		GPTW0,		///< General PWM Timer 0 / 汎用 PWM タイマ０
		GPTW1,		///< General PWM Timer 1 / 汎用 PWM タイマ１
		GPTW2,		///< General PWM Timer 2 / 汎用 PWM タイマ２
		GPTW3,		///< General PWM Timer 3 / 汎用 PWM タイマ３
		GPTW4,		///< General PWM Timer 4 / 汎用 PWM タイマ４
		GPTW5,		///< General PWM Timer 5 / 汎用 PWM タイマ５
		GPTW6,		///< General PWM Timer 6 / 汎用 PWM タイマ６
		GPTW7,		///< General PWM Timer 7 / 汎用 PWM タイマ７

		POEG,		///< GPTW Port Output Enable / GPTW 用ポートアウトプットイネーブル

		TMR0,		///< 8-Bit Timer 0 / 8 ビットタイマ０
		TMR1,		///< 8-Bit Timer 1 / 8 ビットタイマ１
		TMR2,		///< 8-Bit Timer 2 / 8 ビットタイマ２
		TMR3,		///< 8-Bit Timer 3 / 8 ビットタイマ３

		CMT0,		///< Compare Match Timer 0 / コンペアマッチタイマ０
		CMT1,		///< Compare Match Timer 1 / コンペアマッチタイマ１
		CMT2,		///< Compare Match Timer 2 / コンペアマッチタイマ２
		CMT3,		///< Compare Match Timer 3 / コンペアマッチタイマ３

		RTC,		///< Realtime Clock / リアルタイムクロック

		LPT,		///< Low Power Timer / ローパワータイマ

		WDTA,		///< Watchdog Timer / ウォッチドッグタイマ
		IWDT,		///< Independent Watchdog Timer / 独立ウォッチドッグタイマ
#if defined(SIG_RX261)
		USB0,		///< USB 2.0 Host/Function Module 0 / USB 2.0 FS ホスト/ファンクションモジュール
#endif
		SCI1,		///< Serial Communications Interface 1 / シリアルコミュニケーションインタフェース１
		SCI5,		///< Serial Communications Interface 5 / シリアルコミュニケーションインタフェース５
		SCI6,		///< Serial Communications Interface 6 / シリアルコミュニケーションインタフェース６
		SCI12,		///< Serial Communications Interface 12 / シリアルコミュニケーションインタフェース１２
		RSCI0,		///< (R)Serial Communications Interface 0 / Ｒシリアルコミュニケーションインタフェース０
		RSCI8,		///< (R)Serial Communications Interface 8 / Ｒシリアルコミュニケーションインタフェース８
		RSCI9,		///< (R)Serial Communications Interface 9 / Ｒシリアルコミュニケーションインタフェース９

		RIIC0,		///< I2C-bus Interface 0 / I2C バスインタフェース０
#if defined(SIG_RX261)
		CANFD0,		///< CANFD Module 0 / CANFD モジュール０
#endif
		RSPI0,		///< Serial Peripheral Interface 0 / シリアルペリフェラルインタフェース０

		CRC,		///< CRC Calculator / CRC 演算器

		REMC0,		///< Remote Control Signal Receiver / リモコン信号受信機能

		RSIP,		///< Renesas Secure IP (RSIP-E11A) / Renesas Secure IP (RSIP-E11A)

		CTSU,		///< Capacitive Touch Sensing Unit / 静電容量式タッチセンサ

		S12AD,		///< 12-Bit A/D Converter / 12 ビット A/D コンバータ

		DA,			///< 8-Bit D/A Converter / 8 ビット D/A コンバータ

		TEMPS,		///< Temperature Sensor / 温度センサ

		CMPB,		///< Comparator B / コンパレーターＢ

		DOC,		///< Data Operation Circuit / データ演算回路
	};
}
