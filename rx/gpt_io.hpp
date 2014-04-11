#pragma once
//=====================================================================//
/*!	@file
	@brief	RX グループ・GPT I/O 制御 @n
			Copyright 2013 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "rx63x/gpt.hpp"
#include "rx63x/system.hpp"
#include "rx63x/icu.hpp"
#include "vect.h"

/// F_PCKA タイマーのクロックに必要なので定義が無い場合エラーにします。
#ifndef F_PCKA
#  error "gpt_io.hpp requires F_PCKA to be defined"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPT I/O 制御クラス
		@param[in]	GPT	GPTx定義クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class GPTX>
	class gpt_io {

		// ※必要なら、実装する
		void sleep_() { }

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		gpt_io() { }


		//-----------------------------------------------------------------//
		/*!
			@brief  機能を開始
			@param[in]	limit	PWM カウンターのリミット
		*/
		//-----------------------------------------------------------------//
		void start_pwm(uint16_t limit) {
			uint32_t ch = GPTX::get_chanel();

			// 書き込み保護を解除
			switch(ch) {
			case 0:
				GPT::GTWP.WP0 = 0;
				break;
			case 1:
				GPT::GTWP.WP1 = 0;
				break;
			case 2:
				GPT::GTWP.WP2 = 0;
				break;
			case 3:
				GPT::GTWP.WP3 = 0;
				break;
			case 4:
				GPTB::GTWP.WP4 = 0;
				break;
			case 5:
				GPTB::GTWP.WP5 = 0;
				break;
			case 6:
				GPTB::GTWP.WP6 = 0;
				break;
			case 7:
				GPTB::GTWP.WP7 = 0;
				break;
			}

			GPTX::GTIOR.GTIOA = 0b011001;
			GPTX::GTONCR = GPTX::GTONCR.OAE.b();
			GPTX::GTUDC = GPTX::GTUDC.UD.b() | GPTX::GTUDC.UDF.b(); // UP カウント設定

			// バッファ動作設定
			switch(ch) {
			case 0:
				GPT::GTBDR.BD0_0 = 1;  // GPT0 GTCCR バッファ動作禁止
				GPT::GTBDR.BD0_1 = 1;  // GPT0 GTPR バッファ動作禁止
				GPT::GTBDR.BD0_2 = 1;  // GPT0 GTADTR バッファ動作禁止
				GPT::GTBDR.BD0_3 = 1;  // GPT0 GTDV バッファ動作禁止 
				break;
			case 1:
				GPT::GTBDR.BD1_0 = 1;  // GPT1 GTCCR バッファ動作禁止
				GPT::GTBDR.BD1_1 = 1;  // GPT1 GTPR バッファ動作禁止
				GPT::GTBDR.BD1_2 = 1;  // GPT1 GTADTR バッファ動作禁止
				GPT::GTBDR.BD1_3 = 1;  // GPT1 GTDV バッファ動作禁止 
				break;
			case 2:
				GPT::GTBDR.BD2_0 = 1;  // GPT2 GTCCR バッファ動作禁止
				GPT::GTBDR.BD2_1 = 1;  // GPT2 GTPR バッファ動作禁止
				GPT::GTBDR.BD2_2 = 1;  // GPT2 GTADTR バッファ動作禁止
				GPT::GTBDR.BD2_3 = 1;  // GPT2 GTDV バッファ動作禁止 
				break;
			case 3:
				GPT::GTBDR.BD3_0 = 1;  // GPT3 GTCCR バッファ動作禁止
				GPT::GTBDR.BD3_1 = 1;  // GPT3 GTPR バッファ動作禁止
				GPT::GTBDR.BD3_2 = 1;  // GPT3 GTADTR バッファ動作禁止
				GPT::GTBDR.BD3_3 = 1;  // GPT3 GTDV バッファ動作禁止 
				break;
			case 4:
				GPTB::GTBDR.BD4_0 = 1; // GPT4 GTCCR バッファ動作禁止
				GPTB::GTBDR.BD4_1 = 1; // GPT4 GTPR バッファ動作禁止
				GPTB::GTBDR.BD4_2 = 1; // GPT4 GTADTR バッファ動作禁止
				GPTB::GTBDR.BD4_3 = 1; // GPT4 GTDV バッファ動作禁止 
				break;
			case 5:
				GPTB::GTBDR.BD5_0 = 1; // GPT5 GTCCR バッファ動作禁止
				GPTB::GTBDR.BD5_1 = 1; // GPT5 GTPR バッファ動作禁止
				GPTB::GTBDR.BD5_2 = 1; // GPT5 GTADTR バッファ動作禁止
				GPTB::GTBDR.BD5_3 = 1; // GPT5 GTDV バッファ動作禁止 
				break;
			case 6:
				GPTB::GTBDR.BD6_0 = 1; // GPT6 GTCCR バッファ動作禁止
				GPTB::GTBDR.BD6_1 = 1; // GPT6 GTPR バッファ動作禁止
				GPTB::GTBDR.BD6_2 = 1; // GPT6 GTADTR バッファ動作禁止
				GPTB::GTBDR.BD6_3 = 1; // GPT6 GTDV バッファ動作禁止 
				break;
			case 7:
				GPTB::GTBDR.BD7_0 = 1; // GPT7 GTCCR バッファ動作禁止
				GPTB::GTBDR.BD7_1 = 1; // GPT7 GTPR バッファ動作禁止
				GPTB::GTBDR.BD7_2 = 1; // GPT7 GTADTR バッファ動作禁止
				GPTB::GTBDR.BD7_3 = 1; // GPT7 GTDV バッファ動作禁止 
				break;
			}

			GPTX::GTPR = limit;
			GPTX::GTCCRA = 0;

			// カウント開始
			switch(ch) {
			case 0:
				GPT::GTSTR.CST0 = 1;
				break;
			case 1:
				GPT::GTSTR.CST1 = 1;
				break;
			case 2:
				GPT::GTSTR.CST2 = 1;
				break;
			case 3:
				GPT::GTSTR.CST3 = 1;
				break;
			case 4:
				GPTB::GTSTR.CST4 = 1;
				break;
			case 5:
				GPTB::GTSTR.CST5 = 1;
				break;
			case 6:
				GPTB::GTSTR.CST6 = 1;
				break;
			case 7:
				GPTB::GTSTR.CST7 = 1;
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  周期レジスター設定
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void set_r(uint16_t n) {
			GPTX::GTPR = n;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  コンペアキャプチャーＡレジスター設定
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void set_a(uint16_t n) { GPTX::GTCCRA = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief  コンペアキャプチャーＢレジスター設定
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void set_b(uint16_t n) { GPTX::GTCCRB = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief  コンペアキャプチャーＣレジスター設定
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void set_c(uint16_t n) { GPTX::GTCCRC = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief  コンペアキャプチャーＤレジスター設定
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void set_d(uint16_t n) { GPTX::GTCCRD = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief  コンペアキャプチャーＥレジスター設定
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void set_e(uint16_t n) { GPTX::GTCCRE = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief  コンペアキャプチャーＦレジスター設定
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void set_f(uint16_t n) { GPTX::GTCCRF = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換開始要求タイミングレジスターＡ設定
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void set_ad_a(uint16_t n) { GPTX::GTADTRA = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換開始要求タイミングレジスターＢ設定
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void set_ad_b(uint16_t n) { GPTX::GTADTRB = n; }

	};
}
