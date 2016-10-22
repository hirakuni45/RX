#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・省電力制御 @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "RX24T/system.hpp"
#include "RX24T/peripheral.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  省電力制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct power_cfg {

		//-----------------------------------------------------------------//
		/*!
			@brief  周辺機器に切り替える
			@param[in]	t	周辺機器タイプ
			@param[in]	ena	オフにする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void turn(peripheral t, bool ena = true)
		{
			bool f = !ena;
			switch(t) {
			case peripheral::CMT0:
			case peripheral::CMT1:
				SYSTEM::MSTPCRA.MSTPA15 = f;
				break;
			case peripheral::CMT2:
			case peripheral::CMT3:
				SYSTEM::MSTPCRA.MSTPA14 = f;
				break;

			case peripheral::RSPI0:
				SYSTEM::MSTPCRB.MSTPB17 = f;
				break;

			case peripheral::RIIC0:
				SYSTEM::MSTPCRB.MSTPB21 = f;
				break;

			case peripheral::SCI1:
				SYSTEM::MSTPCRB.MSTPB30 = f;
				break;
			case peripheral::SCI5:
				SYSTEM::MSTPCRB.MSTPB26 = f;
				break;
			case peripheral::SCI6:
				SYSTEM::MSTPCRB.MSTPB25 = f;
				break;
			default:
				break;
			}
		}
	};
}
