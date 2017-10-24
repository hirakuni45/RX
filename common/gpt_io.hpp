#pragma once
//=====================================================================//
/*!	@file
	@brief	RX グループ・GPT I/O 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2013, 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

/// F_PCLKA タイマーのクロックに必要なので定義が無い場合エラーにします。
#ifndef F_PCLKA
#  error "gpt_io.hpp requires F_PCLKA to be defined"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GPT I/O 制御クラス
		@param[in]	GPT	GPTx定義クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class GPT>
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


#if 0
		//-----------------------------------------------------------------//
		/*!
			@brief  PWM を開始
			@param[in]	limit	PWM カウンターのリミット
		*/
		//-----------------------------------------------------------------//
		void start_pwm(uint16_t limit) {
			uint32_t ch = GPT::get_chanel();

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

			GPT::GTIOR.GTIOA = 0b011001;
			GPT::GTONCR = GPT::GTONCR.OAE.b();
			GPT::GTUDC = GPT::GTUDC.UD.b() | GPT::GTUDC.UDF.b(); // UP カウント設定

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

			GPT::GTPR = limit;
			GPT::GTCCRA = 0;

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
#endif

		//-----------------------------------------------------------------//
		/*!
			@brief  周期レジスター設定
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void set_r(uint16_t n) {
			GPT::GTPR = n;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  コンペアキャプチャーＡレジスター設定
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void set_a(uint16_t n) { GPT::GTCCRA = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief  コンペアキャプチャーＢレジスター設定
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void set_b(uint16_t n) { GPT::GTCCRB = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief  コンペアキャプチャーＣレジスター設定
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void set_c(uint16_t n) { GPT::GTCCRC = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief  コンペアキャプチャーＤレジスター設定
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void set_d(uint16_t n) { GPT::GTCCRD = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief  コンペアキャプチャーＥレジスター設定
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void set_e(uint16_t n) { GPT::GTCCRE = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief  コンペアキャプチャーＦレジスター設定
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void set_f(uint16_t n) { GPT::GTCCRF = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換開始要求タイミングレジスターＡ設定
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void set_ad_a(uint16_t n) { GPT::GTADTRA = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief  A/D 変換開始要求タイミングレジスターＢ設定
			@param[in]	n	値
		*/
		//-----------------------------------------------------------------//
		void set_ad_b(uint16_t n) { GPT::GTADTRB = n; }

	};
}
