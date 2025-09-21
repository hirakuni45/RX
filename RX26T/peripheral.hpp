#pragma once
//=====================================================================//
/*!	@file
	@brief	Peripheral Type / ペリフェラル種別 (RX26T)
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
		@brief  Peripheral Type / ペリフェラル型（種別）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class peripheral : uint8_t {

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

		ELC,		///< Event Link Controller / イベントリンクコントローラ (ELC)

		MTU0,		///< Multi-Function Timer Pulse Unit 0 / マルチファンクションタイマパルスユニット０
		MTU1,		///< Multi-Function Timer Pulse Unit 1 / マルチファンクションタイマパルスユニット１
		MTU2,		///< Multi-Function Timer Pulse Unit 2 / マルチファンクションタイマパルスユニット２
		MTU3,		///< Multi-Function Timer Pulse Unit 3 / マルチファンクションタイマパルスユニット３
		MTU4,		///< Multi-Function Timer Pulse Unit 4 / マルチファンクションタイマパルスユニット４
		MTU5,		///< Multi-Function Timer Pulse Unit 5 / マルチファンクションタイマパルスユニット５
		MTU6,		///< Multi-Function Timer Pulse Unit 6 / マルチファンクションタイマパルスユニット６
		MTU7,		///< Multi-Function Timer Pulse Unit 7 / マルチファンクションタイマパルスユニット７
		MTU9,		///< Multi-Function Timer Pulse Unit 9 / マルチファンクションタイマパルスユニット９

		POE3D,		///< Port Output Enable 3D / ポートアウトプットイネーブル３Ｄ

		GPTW0,		///< General PWM Timer 0 / 汎用 PWM タイマ０
		GPTW1,		///< General PWM Timer 1 / 汎用 PWM タイマ１
		GPTW2,		///< General PWM Timer 2 / 汎用 PWM タイマ２
		GPTW3,		///< General PWM Timer 3 / 汎用 PWM タイマ３
		GPTW4,		///< General PWM Timer 4 / 汎用 PWM タイマ４
		GPTW5,		///< General PWM Timer 5 / 汎用 PWM タイマ５
		GPTW6,		///< General PWM Timer 6 / 汎用 PWM タイマ６
		GPTW7,		///< General PWM Timer 7 / 汎用 PWM タイマ７
		GPTW8,		///< General PWM Timer 8 / 汎用 PWM タイマ８

		HRPWM,		///< High Resolution PWM Waveform Generation Circuit / 高分解能 PWM 波形生成回路

		POEG,		///< GPTW Port Output Enable / GPTW 用ポートアウトプットイネーブル

		TMR0,		///< 8-Bit Timer 0 / 8 ビットタイマ０
		TMR1,		///< 8-Bit Timer 1 / 8 ビットタイマ１
		TMR2,		///< 8-Bit Timer 2 / 8 ビットタイマ２
		TMR3,		///< 8-Bit Timer 3 / 8 ビットタイマ３
		TMR4,		///< 8-Bit Timer 4 / 8 ビットタイマ４
		TMR5,		///< 8-Bit Timer 5 / 8 ビットタイマ５
		TMR6,		///< 8-Bit Timer 6 / 8 ビットタイマ６
		TMR7,		///< 8-Bit Timer 7 / 8 ビットタイマ７

		CMT0,		///< Compare Match Timer 0 / コンペアマッチタイマ０
		CMT1,		///< Compare Match Timer 1 / コンペアマッチタイマ１
		CMT2,		///< Compare Match Timer 2 / コンペアマッチタイマ２
		CMT3,		///< Compare Match Timer 3 / コンペアマッチタイマ３

		CMTW0,		///< Compare Match Timer W0 / コンペアマッチタイマＷ０
		CMTW1,		///< Compare Match Timer W1 / コンペアマッチタイマＷ１

		WDTA,		///< Watchdog Timer / ウォッチドッグタイマ
		IWDT,		///< Independent Watchdog Timer / 独立ウォッチドッグタイマ

		SCI1,		///< Serial Communications Interface 1 / シリアルコミュニケーションインタフェース１
		SCI5,		///< Serial Communications Interface 5 / シリアルコミュニケーションインタフェース５
		SCI6,		///< Serial Communications Interface 6 / シリアルコミュニケーションインタフェース６
		SCI12,		///< Serial Communications Interface 12 / シリアルコミュニケーションインタフェース１２
		RSCI8,		///< (R)Serial Communications Interface 8 / Ｒシリアルコミュニケーションインタフェース８
		RSCI9,		///< (R)Serial Communications Interface 9 / Ｒシリアルコミュニケーションインタフェース９
		RSCI11,		///< (R)Serial Communications Interface 11 / Ｒシリアルコミュニケーションインタフェース１１

		RIIC0,		///< I2C-bus Interface 0 / I2C バスインタフェース０

		RI3C0,		///< I3C-bus Interface 0 / I3C バスインタフェース０

		CANFD0,		///< CANFD Module 0 / CANFD モジュール０

		RSPI0,		///< Serial Peripheral Interface 0 / シリアルペリフェラルインタフェース０

		RSPIA0,		///< Serial Peripheral Interface A0 / シリアルペリフェラルインタフェースＡ０

		CRC,		///< CRC Calculator / CRC 演算器

		TSIP_L,		///< Trusted Secure IP (TSIP-Lite) / Trusted Secure IP (TSIP-Lite)

		S12AD,		///< 12-Bit A/D Converter / 12 ビット A/D コンバータ
		S12AD1,		///< 12-Bit A/D Converter 1 / 12 ビット A/D コンバータ１
		S12AD2,		///< 12-Bit A/D Converter 2 / 12 ビット A/D コンバータ２

		R12DA,		///< 12-Bit D/A Converter / 12 ビット D/A コンバータ

		TEMPS,		///< Temperature Sensor / 温度センサ

		CMPC0,		///< Comparator C0 / コンパレーターＣ０
		CMPC1,		///< Comparator C1 / コンパレーターＣ１
		CMPC2,		///< Comparator C2 / コンパレーターＣ２
		CMPC3,		///< Comparator C3 / コンパレーターＣ３
		CMPC4,		///< Comparator C4 / コンパレーターＣ４
		CMPC5,		///< Comparator C5 / コンパレーターＣ５

		DOC,		///< Data Operation Circuit / データ演算回路
	};
}
