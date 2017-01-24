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
			@brief  モジュール・ストップ機能を設定
			@param[in]	t	周辺機器タイプ
			@param[in]	ena	オフにする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void turn(peripheral t, bool ena = true)
		{
			bool f = !ena;
			switch(t) {
			case peripheral::DTC:
				SYSTEM::MSTPCRA.MSTPA28 = f;
				break;

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
			case peripheral::SCI1C:
				SYSTEM::MSTPCRB.MSTPB30 = f;
				break;
			case peripheral::SCI5:
			case peripheral::SCI5C:
				SYSTEM::MSTPCRB.MSTPB26 = f;
				break;
			case peripheral::SCI6:
			case peripheral::SCI6C:
				SYSTEM::MSTPCRB.MSTPB25 = f;
				break;

			case peripheral::TMR0:
			case peripheral::TMR1:
				SYSTEM::MSTPCRA.MSTPA5 = f;
				break;
			case peripheral::TMR2:
			case peripheral::TMR3:
				SYSTEM::MSTPCRA.MSTPA4 = f;
				break;
			case peripheral::TMR4:
			case peripheral::TMR5:
				SYSTEM::MSTPCRA.MSTPA3 = f;
				break;
			case peripheral::TMR6:
			case peripheral::TMR7:
				SYSTEM::MSTPCRA.MSTPA2 = f;
				break;

			case peripheral::MTU0:
			case peripheral::MTU1:
			case peripheral::MTU2:
			case peripheral::MTU3:
			case peripheral::MTU4:
			case peripheral::MTU5:
			case peripheral::MTU6:
			case peripheral::MTU7:
			case peripheral::MTU9:
				SYSTEM::MSTPCRA.MSTPA9 = f;
				break;

			case peripheral::S12AD:
				SYSTEM::MSTPCRA.MSTPA17 = f;
				break;
			case peripheral::S12AD1:
				SYSTEM::MSTPCRA.MSTPA16 = f;
				break;
			case peripheral::S12AD2:
				SYSTEM::MSTPCRA.MSTPA23 = f;
				break;

			default:
				break;
			}
		}
	};
}
