#pragma once
//=========================================================================//
/*!	@file
	@brief	Low Power Consumption / 消費電力低減機能 (RX23W)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX231/system.hpp"
#include "RX23W/peripheral.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  電力制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct power_mgr {

		struct pad_t {

			uint8_t		tmr_;
			uint8_t		mtu_;
			uint8_t		tpu_;
			uint8_t		cmt_;
			uint16_t	dmac_;

			pad_t() :
				tmr_(0),
				mtu_(0),
				tpu_(0),
				cmt_(0),
				dmac_(0)
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
			case peripheral::TMR3:
			case peripheral::TMR2:
				sr_(ena, pad_.tmr_, peripheral::TMR0, per);
				SYSTEM::MSTPCRA.MSTPA4 = ((pad_.tmr_ & 0b00'00'11'00) == 0);
				break;
			case peripheral::TMR1:
			case peripheral::TMR0:
				sr_(ena, pad_.tmr_, peripheral::TMR0, per);
				SYSTEM::MSTPCRA.MSTPA5 = ((pad_.tmr_ & 0b00'00'00'11) == 0);
				break;

			case peripheral::MTU0:
			case peripheral::MTU1:
			case peripheral::MTU2:
			case peripheral::MTU3:
			case peripheral::MTU4:
				sr_(ena, pad_.mtu_, peripheral::MTU0, per);
				SYSTEM::MSTPCRA.MSTPA9 = (pad_.mtu_ == 0);
				break;

			case peripheral::TPU0:
			case peripheral::TPU1:
			case peripheral::TPU2:
			case peripheral::TPU3:
			case peripheral::TPU4:
			case peripheral::TPU5:
				sr_(ena, pad_.tpu_, peripheral::TPU0, per);
				SYSTEM::MSTPCRA.MSTPA13 = (pad_.tpu_ == 0);
				break;

			case peripheral::CMT2:
			case peripheral::CMT3:
				// CMT2, CMT3 のストップ状態設定
				sr_(ena, pad_.cmt_, peripheral::CMT0, per);
				SYSTEM::MSTPCRA.MSTPA14 = ((pad_.cmt_ & 0b1100) == 0);
				break;
			case peripheral::CMT0:
			case peripheral::CMT1:
				// CMT0, CMT1 のストップ状態設定
				sr_(ena, pad_.cmt_, peripheral::CMT0, per);
				SYSTEM::MSTPCRA.MSTPA15 = ((pad_.cmt_ & 0b0011) == 0);
				break;

			case peripheral::S12AD:
				SYSTEM::MSTPCRA.MSTPA17 = f;
				break;

			case peripheral::R12DA:
				SYSTEM::MSTPCRA.MSTPA19 = f;
				break;

			case peripheral::DMAC0:
			case peripheral::DMAC1:
			case peripheral::DMAC2:
			case peripheral::DMAC3:
			case peripheral::DTC:
				sr_(ena, pad_.dmac_, peripheral::DMAC0, per);
				SYSTEM::MSTPCRA.MSTPA28 = (pad_.dmac_ == 0);
				break;

			case peripheral::RSCAN:
				SYSTEM::MSTPCRB.MSTPB0 = f;
				break;

			case peripheral::SCI12:
				SYSTEM::MSTPCRB.MSTPB4 = f;
				break;

			case peripheral::DOC:
				SYSTEM::MSTPCRB.MSTPB6 = f;
				break;

			case peripheral::ELC:
				SYSTEM::MSTPCRB.MSTPB9 = f;
				break;

			case peripheral::CMPB:
				SYSTEM::MSTPCRB.MSTPB10 = f;
				break;

			case peripheral::RSPI0:
				SYSTEM::MSTPCRB.MSTPB17 = f;
				break;

			case peripheral::USB0:
				SYSTEM::MSTPCRB.MSTPB19 = f;
				break;

			case peripheral::RIIC0:
				SYSTEM::MSTPCRB.MSTPB21 = f;
				break;

			case peripheral::CRC:
				SYSTEM::MSTPCRB.MSTPB23 = f;
				break;

			case peripheral::BLE:
				SYSTEM::MSTPCRB.MSTPB25 = f;
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

			case peripheral::IrDA:
				SYSTEM::MSTPCRC.MSTPC20 = f;
				break;

			case peripheral::SCI8:
				SYSTEM::MSTPCRC.MSTPC27 = f;
				break;

			case peripheral::CTSU:
				SYSTEM::MSTPCRD.MSTPD10 = f;
				break;

			case peripheral::SSI0:
				SYSTEM::MSTPCRD.MSTPD15 = f;
				break;

			case peripheral::SDHI:
				SYSTEM::MSTPCRD.MSTPD19 = f;
				break;

			case peripheral::TSIP_L:
				SYSTEM::MSTPCRD.MSTPD31 = f;
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
