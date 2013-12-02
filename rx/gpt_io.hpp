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

/// F_PCKA はボーレートパラメーター計算で必要で、設定が無いとエラーにします。
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
	template <class GPT>
	class gpt_io {

		GPT		gpt_;



		// ※必要なら、実装する
		void sleep_() { }

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		gpt_io() { }






	};
}
