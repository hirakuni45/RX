#pragma once
//=========================================================================//
/*!	@file
	@brief	RX110/RX111 グループ・電力制御クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX111/system.hpp"
#include "RX111/peripheral.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  電力制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct power_mgr {

		struct pad_t {

			uint8_t		mtu_;
			uint8_t		cmt_;

			pad_t() :
				mtu_(0),
				cmt_(0)
			{ }
		};
		static inline pad_t	pad_;

		static void sr_(bool f, uint8_t& pad, peripheral org, peripheral tgt)
		{
			if(f) {
				pad |= 1 << (static_cast<uint16_t>(tgt) - static_cast<uint16_t>(org));
			} else {
				pad &= ~(1 << (static_cast<uint16_t>(tgt) - static_cast<uint16_t>(org)));
			}
		}

		static void sr_(bool f, uint16_t& pad, peripheral org, peripheral tgt)
		{
			if(f) {
				pad |= 1 << (static_cast<uint16_t>(tgt) - static_cast<uint16_t>(org));
			} else {
				pad &= ~(1 << (static_cast<uint16_t>(tgt) - static_cast<uint16_t>(org)));
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  モジュール・ストップ機能を設定
			@param[in]	per	周辺機器タイプ
			@param[in]	ena	オフにする場合「false」
			@return ペリフェラルが見つからない場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn(peripheral per, bool ena = true)
		{
			device::SYSTEM::PRCR = 0xA500 | device::SYSTEM::PRCR.PRC1.b();

			bool ret = true;
			bool f = !ena;
			switch(per) {

			case peripheral::MTU0:
			case peripheral::MTU1:
			case peripheral::MTU2:
#if defined(SIG_RX111)
			case peripheral::MTU3:
			case peripheral::MTU4:
#endif
			case peripheral::MTU5:
				sr_(ena, pad_.mtu_, peripheral::MTU0, per);
				SYSTEM::MSTPCRA.MSTPA9 = (pad_.mtu_ == 0);
				break;

			case peripheral::CMT0:
			case peripheral::CMT1:
				sr_(ena, pad_.cmt_, peripheral::CMT0, per);
				SYSTEM::MSTPCRA.MSTPA15 = ((pad_.cmt_ & 0b0011) == 0);
				break;

			case peripheral::S12AD:
				SYSTEM::MSTPCRA.MSTPA17 = f;
				break;
#if defined(SIG_RX111)
			case peripheral::DA:
				SYSTEM::MSTPCRA.MSTPA19 = f;
				break;
#endif
			case peripheral::DTC:
				SYSTEM::MSTPCRA.MSTPA28 = f;
				break;

			case peripheral::SCI12:
				SYSTEM::MSTPCRB.MSTPB4 = f;
				break;

			case peripheral::DOC:
				SYSTEM::MSTPCRB.MSTPB6 = f;
				break;

			case peripheral::RSPI0:
				SYSTEM::MSTPCRB.MSTPB17 = f;
				break;
#if defined(SIG_RX111)
			case peripheral::USB0:
				SYSTEM::MSTPCRB.MSTPB19 = f;
				break;
#endif
			case peripheral::RIIC0:
				SYSTEM::MSTPCRB.MSTPB21 = f;
				break;

			case peripheral::CRC:
				SYSTEM::MSTPCRB.MSTPB23 = f;
				break;

			case peripheral::SCI5:
				SYSTEM::MSTPCRB.MSTPB26 = f;
				break;

			case peripheral::SCI1:
				SYSTEM::MSTPCRB.MSTPB30 = f;
				break;

			case peripheral::CAC:
				SYSTEM::MSTPCRC.MSTPC19 = f;
				break;

			default:
				ret = false;
				break;
			}
			device::SYSTEM::PRCR = 0xA500;
			return ret;
		}
	};
}
