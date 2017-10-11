#pragma once
//=========================================================================//
/*!	@file
	@brief	SD カード・マネージャー @n
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cstring>
#include "common/format.hpp"
#include "common/string_utils.hpp"
#include "ff12b/mmc_io.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SD カード・マネージャー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class sdc_man {

		FATFS	fatfs_;  ///< FatFS コンテキスト

		char	current_[_MAX_LFN + 1];

		bool	mount_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		sdc_man() : current_{ 0 }, mount_(false) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始（初期化）
		 */
		//-----------------------------------------------------------------//
		void start()
		{
			mount_ = false;

			strcpy(current_, "/");
			select_wait_ = 0;
			mount_delay_ = 0;

			memset(&fatfs_, 0, sizeof(FATFS));
		}

	};
}
