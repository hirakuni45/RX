#pragma once
//=====================================================================//
/*! @file
    @brief  SEEDA03 net_tools クラス @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "main.hpp"

namespace seeda {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  net_tools クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class net_tools {

		typedef HTTP::http_format http_format;

	public:

		//-----------------------------------------------------------------//
		/*!
			@brief  render date/time
		*/
		//-----------------------------------------------------------------//
		static void render_date_time()
		{
			char tmp[128];
			time_t t = get_time();
			disp_time(t, tmp, sizeof(tmp));
			http_format("%s<br>\n") % tmp;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ビルドバージョン表示
		*/
		//-----------------------------------------------------------------//
		static void render_version()
		{
			http_format("Seeda03 Build: %u Version %d.%02d<br>\n") % build_id_
				% (seeda_version_ / 100) % (seeda_version_ % 100);
		}

	};
}
