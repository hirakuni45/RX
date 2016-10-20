#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M グループ・省電力制御 @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "RX64M/system.hpp"
#include "RX64M/peripheral.hpp"

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
			case peripheral::SCI0:
				SYSTEM::MSTPCRB.MSTPB31 = f;	// B31 (SCI0)のストップ状態解除
				break;
			case peripheral::SCI1:
				SYSTEM::MSTPCRB.MSTPB30 = f;	// B30 (SCI1)のストップ状態解除
				break;
			case peripheral::SCI2:
				SYSTEM::MSTPCRB.MSTPB29 = f;	// B29 (SCI2)のストップ状態解除
				break;
			case peripheral::SCI3:
				SYSTEM::MSTPCRB.MSTPB28 = f;	// B28 (SCI3)のストップ状態解除
				break;
			case peripheral::SCI4:
				SYSTEM::MSTPCRB.MSTPB27 = f;	// B27 (SCI4)のストップ状態解除
				break;
			case peripheral::SCI5:
				SYSTEM::MSTPCRB.MSTPB26 = f;	// B26 (SCI5)のストップ状態解除
				break;
			case peripheral::SCI6:
				SYSTEM::MSTPCRB.MSTPB25 = f;	// B25 (SCI6)のストップ状態解除
				break;
			case peripheral::SCI7:
				SYSTEM::MSTPCRB.MSTPB24 = f;	// B24 (SCI7)のストップ状態解除
				break;
			case peripheral::CMT0:
			case peripheral::CMT1:
				SYSTEM::MSTPCRA.MSTPA15 = f;
				break;
			default:
				break;
			}
		}
	};
}
