#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600 グループ QSPI I/O 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX600/qspi.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  QSPI 制御クラス
		@param[in]	QSPI	ハードウェアーリソース
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class QSPI>
	class qspi_io {

		typedef QSPI value_type;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		qspi_io() noexcept { }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]
		*/
		//-----------------------------------------------------------------//
		bool start() noexcept
		{

			return true;
		}


	};
}
