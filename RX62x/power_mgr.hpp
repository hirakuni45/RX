#pragma once
//=====================================================================//
/*!	@file
	@brief	Low Power Consumption / 消費電力低減機能 (RX621/RX62N)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX62x/system.hpp"
#include "RX62x/peripheral.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  電力制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct power_mgr {

		struct pad_t {

			uint8_t		tmr_;
			uint8_t		mtu0_;
			uint8_t		mtu1_;

			uint8_t		cmt_;

			uint16_t	dmac_;
			uint8_t		exdmac_;

			pad_t() :
				tmr_(0),
				mtu0_(0), mtu1_(0),

				cmt_(0),

				dmac_(0),
				exdmac_(0)
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
			case peripheral::MTU5:
				sr_(ena, pad_.mtu0_, peripheral::MTU0, per);
				SYSTEM::MSTPCRA.MSTPA9 = (pad_.mtu0_ == 0);
				break;
			case peripheral::MTU6:
			case peripheral::MTU7:
			case peripheral::MTU8:
			case peripheral::MTU9:
			case peripheral::MTU10:
			case peripheral::MTU11:
				sr_(ena, pad_.mtu1_, peripheral::MTU6, per);
				SYSTEM::MSTPCRA.MSTPA8 = (pad_.mtu1_ == 0);
				break;

			case peripheral::PPG1:
				SYSTEM::MSTPCRA.MSTPA10 = f;
				break;
			case peripheral::PPG0:
				SYSTEM::MSTPCRA.MSTPA11 = f;
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

			case peripheral::DA:
				SYSTEM::MSTPCRA.MSTPA19 = f;
				break;

			case peripheral::AD1:
				SYSTEM::MSTPCRA.MSTPA22 = f;
				break;
			case peripheral::AD0:
				SYSTEM::MSTPCRA.MSTPA23 = f;
				break;

			case peripheral::DTC:
			case peripheral::DMAC0:
			case peripheral::DMAC1:
			case peripheral::DMAC2:
			case peripheral::DMAC3:
				sr_(ena, pad_.dmac_, peripheral::DTC, per);
				SYSTEM::MSTPCRA.MSTPA28 = (pad_.dmac_ == 0);
				break;
			case peripheral::EXDMAC0:
			case peripheral::EXDMAC1:
				sr_(ena, pad_.exdmac_, peripheral::EXDMAC0, per);
				SYSTEM::MSTPCRA.MSTPA29 = (pad_.exdmac_ == 0);
				break;

			case peripheral::CAN:
				SYSTEM::MSTPCRB.MSTPB0 = f;
				break;

			case peripheral::EDMAC:
				SYSTEM::MSTPCRB.MSTPB15 = f;
				break;

			case peripheral::RSPI1:
				SYSTEM::MSTPCRB.MSTPB16 = f;
				break;
			case peripheral::RSPI0:
				SYSTEM::MSTPCRB.MSTPB17 = f;
				break;

			case peripheral::USB1:
				SYSTEM::MSTPCRB.MSTPB18 = f;
				break;
			case peripheral::USB0:
				SYSTEM::MSTPCRB.MSTPB19 = f;
				break;

			case peripheral::RIIC1:
				SYSTEM::MSTPCRB.MSTPB20 = f;
				break;
			case peripheral::RIIC0:
				SYSTEM::MSTPCRB.MSTPB21 = f;
				break;

			case peripheral::CRC:
				SYSTEM::MSTPCRB.MSTPB23 = f;
				break;

			case peripheral::SCI6:
				SYSTEM::MSTPCRB.MSTPB25 = f;
				break;
			case peripheral::SCI5:
				SYSTEM::MSTPCRB.MSTPB26 = f;
				break;
			case peripheral::SCI3:
				SYSTEM::MSTPCRB.MSTPB28 = f;
				break;
			case peripheral::SCI2:
				SYSTEM::MSTPCRB.MSTPB29 = f;
				break;
			case peripheral::SCI1:
				SYSTEM::MSTPCRB.MSTPB30 = f;
				break;
			case peripheral::SCI0:
				SYSTEM::MSTPCRB.MSTPB31 = f;
				break;

			default:
				ret = false;
				break;
			}
			return ret;
		}
	};
}
