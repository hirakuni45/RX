#pragma once
//=====================================================================//
/*!	@file
	@brief	Peripheral Type / ペリフェラル種別 (RX26T)
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
		@brief  peripheral enum class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class peripheral : uint8_t {

		CAC,		///< クロック周波数精度測定回路

		DMAC0,		///< DMA コントローラ・チャネル０
		DMAC1,		///< DMA コントローラ・チャネル１
		DMAC2,		///< DMA コントローラ・チャネル２
		DMAC3,		///< DMA コントローラ・チャネル３
		DMAC4,		///< DMA コントローラ・チャネル４
		DMAC5,		///< DMA コントローラ・チャネル５
		DMAC6,		///< DMA コントローラ・チャネル６
		DMAC7,		///< DMA コントローラ・チャネル７
		DTC,		///< データトランスファコントローラ (DTCb)

		ELC,		///< イベントリンクコントローラ (ELC)

		MTU0,		///< マルチファンクションタイマパルスユニット 3 (MTU3d) 0
		MTU1,		///< マルチファンクションタイマパルスユニット 3 (MTU3d) 1
		MTU2,		///< マルチファンクションタイマパルスユニット 3 (MTU3d) 2
		MTU3,		///< マルチファンクションタイマパルスユニット 3 (MTU3d) 3
		MTU4,		///< マルチファンクションタイマパルスユニット 3 (MTU3d) 4
		MTU5,		///< マルチファンクションタイマパルスユニット 3 (MTU3d) 5
		MTU6,		///< マルチファンクションタイマパルスユニット 3 (MTU3d) 6
		MTU7,		///< マルチファンクションタイマパルスユニット 3 (MTU3d) 7
		MTU9,		///< マルチファンクションタイマパルスユニット 3 (MTU3d) 9

		POE3D,		///< ポートアウトプットイネーブル 3 (POE3D)

		GPTW0,		///< 汎用 PWM タイマ (GPTWa) 0
		GPTW1,		///< 汎用 PWM タイマ (GPTWa) 1
		GPTW2,		///< 汎用 PWM タイマ (GPTWa) 2
		GPTW3,		///< 汎用 PWM タイマ (GPTWa) 3
		GPTW4,		///< 汎用 PWM タイマ (GPTWa) 4
		GPTW5,		///< 汎用 PWM タイマ (GPTWa) 5
		GPTW6,		///< 汎用 PWM タイマ (GPTWa) 6
		GPTW7,		///< 汎用 PWM タイマ (GPTWa) 7
		GPTW8,		///< 汎用 PWM タイマ (GPTWa) 8

		HRPWM,		///< 高分解能 PWM 波形生成回路 (HRPWM)

		POEG,		///< GPTW 用ポートアウトプットイネーブル (POEG)

		TMR0,		///< 8 ビットタイマ０
		TMR1,		///< 8 ビットタイマ１
		TMR2,		///< 8 ビットタイマ２
		TMR3,		///< 8 ビットタイマ３
		TMR4,		///< 8 ビットタイマ４
		TMR5,		///< 8 ビットタイマ５
		TMR6,		///< 8 ビットタイマ６
		TMR7,		///< 8 ビットタイマ７

		CMT0,		///< コンペアマッチタイマ０（CMT）
		CMT1,		///< コンペアマッチタイマ１（CMT）
		CMT2,		///< コンペアマッチタイマ２（CMT）
		CMT3,		///< コンペアマッチタイマ３（CMT）

		CMTW0,		///< コンペアマッチタイマ W (CMTW)
		CMTW1,		///< コンペアマッチタイマ W (CMTW)

		WDTA,		///< ウォッチドッグタイマ
		IWDT,		///< 独立ウォッチドッグタイマ

		SCI1,		///< シリアルコミュニケーションインタフェース (SCIk) 1
		SCI5,		///< シリアルコミュニケーションインタフェース (SCIk) 5
		SCI6,		///< シリアルコミュニケーションインタフェース (SCIk) 6
		RSCI8,		///< シリアルコミュニケーションインタフェース (RSCI) 8
		RSCI9,		///< シリアルコミュニケーションインタフェース (RSCI) 9
		RSCI11,		///< シリアルコミュニケーションインタフェース (RSCI) 11	
		SCI12,		///< シリアルコミュニケーションインタフェース (SCIh) 12

		RIIC0,		///< I2C バスインタフェース (RIICa)

		RI3C0,		///< I3C バスインタフェース (RI3C)

		CANFD0,		///< CAN FD モジュール (CANFD)

		RSPI0,		///< シリアルペリフェラルインタフェース (RSPId)

		RSPIA0,		///< シリアルペリフェラルインタフェース (RSPIA)

		CRC,		///< CRC 演算器 (CRCA)

		TSIP_L,		///< Trusted Secure IP (TSIP-Lite)

		S12AD,		///< 12 ビット A/D コンバータ（S12ADC）
		S12AD1,		///< 12 ビット A/D コンバータ（S12ADC）
		S12AD2,		///< 12 ビット A/D コンバータ（S12ADC）

		R12DA,		///< 12 ビット D/A コンバータ（R12DA）

		TEMPS,		///< 温度センサ（TEMPS）

		CMPC0,		///< コンパレーター０
		CMPC1,		///< コンパレーター１
		CMPC2,		///< コンパレーター２
		CMPC3,		///< コンパレーター３
		CMPC4,		///< コンパレーター４
		CMPC5,		///< コンパレーター５

		DOC,		///< データ演算回路 (DOC)
	};
}
