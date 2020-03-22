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
	public:

		//-----------------------------------------------------------------//
		/*!
			@brief  ARP リスト表示
		*/
		//-----------------------------------------------------------------//
		static void list_arp()
		{
			auto n = ether_arp_num();
			for(uint32_t i = 0; i < n; ++i) {
				const auto* p = ether_arp_get(i);
				if(p->ae_state == AS_FREE) continue;

				utils::format("(%d) %d.%d.%d.%d  --->  %02X:%02X:%02X:%02X:%02X:%02X\n")
					% i
					% static_cast<uint32_t>(p->ae_pra[0])
					% static_cast<uint32_t>(p->ae_pra[1])
					% static_cast<uint32_t>(p->ae_pra[2])
					% static_cast<uint32_t>(p->ae_pra[3])
					% static_cast<uint32_t>(p->ae_hwa[0])
					% static_cast<uint32_t>(p->ae_hwa[1])
					% static_cast<uint32_t>(p->ae_hwa[2])
					% static_cast<uint32_t>(p->ae_hwa[3])
					% static_cast<uint32_t>(p->ae_hwa[4])
					% static_cast<uint32_t>(p->ae_hwa[5]);
			}
		}


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
