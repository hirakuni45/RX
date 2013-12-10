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
		*/
		//-----------------------------------------------------------------//
		void start() {
			GPT::GTWP.WP0 = 0;	// 書き込み保護を解除
			GPTX::GTIOR.GTIOA = 0b011001;
			GPTX::GTONCR = GPTX::GTONCR.OAE.b();
			GPTX::GTUDC = GPTX::GTUDC.UD.b() | GPTX::GTUDC.UDF.b(); // UP カウント設定
			GPT::GTBDR.BD0_0 = 1;  // GPT0 GTCCR バッファ動作禁止
			GPT::GTBDR.BD0_1 = 1;  // GPT0 GTPR バッファ動作禁止
			GPT::GTBDR.BD0_2 = 1;  // GPT0 GTADTR バッファ動作禁止
			GPT::GTBDR.BD0_3 = 1;  // GPT0 GTDV バッファ動作禁止 
			GPTX::GTPR = 512 - 1;
			GPTX::GTCCRA = 256;

			GPT::GTSTR.CST0 = 1;  // カウント開始
		}

		void set_r(uint16_t n) {
			GPTX::GTPR = n;
		}

		void set_a(uint16_t n) {
			GPTX::GTCCRA = n;
		}


	};
}
