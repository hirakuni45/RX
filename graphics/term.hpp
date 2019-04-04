#pragma once
//=====================================================================//
/*!	@file
	@brief	ターミナル・クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

namespace gui {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ターミナル・クラス
		@param[in]	RDR		基本描画クラス
		@param[in]	SZX		横幅
		@param[in]	SZY		高さ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class RDR, uint32_t SZX, uint32_t SZY>
	class term {

		char	code_[SZX * SZY];

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	rdr		描画クラス
		*/
		//-----------------------------------------------------------------//
		term() noexcept : code_{ 0x20 } { }


	};
}
