#pragma once
//=========================================================================//
/*!	@file
	@brief	RX26T グループ・省電力制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX26T/peripheral.hpp"
#include "RX26T/system.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  省電力制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class power_mgr {

		struct pad_t {

			uint8_t		cmt_;
			uint8_t		cmpc_;
			uint16_t	mtu3_;
			uint16_t	dma_dtc_;

			pad_t() : cmt_(0), cmpc_(0),
			mtu3_(0), dma_dtc_(0)
			{ }
		};
		static inline pad_t	pad_;

		static void sr_(bool f, uint8_t& pad, peripheral org, peripheral tgt)
		{
			if(f) {
				pad |=   1 << (static_cast<uint16_t>(tgt) - static_cast<uint16_t>(org));
			} else {
				pad &= ~(1 << (static_cast<uint16_t>(tgt) - static_cast<uint16_t>(org)));
			}
		}

		static void sr_(bool f, uint16_t& pad, peripheral org, peripheral tgt)
		{
			if(f) {
				pad |=   1 << (static_cast<uint16_t>(tgt) - static_cast<uint16_t>(org));
			} else {
				pad &= ~(1 << (static_cast<uint16_t>(tgt) - static_cast<uint16_t>(org)));
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  周辺機器の電力制御を切り替える
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
			case peripheral::CMTW1:
				SYSTEM::MSTPCRA.MSTPA0 = f;
				break;
			case peripheral::CMTW0:
				SYSTEM::MSTPCRA.MSTPA1 = f;
				break;
			case peripheral::TMR6:
			case peripheral::TMR7:
				SYSTEM::MSTPCRA.MSTPA2 = f;
				break;
			case peripheral::TMR4:
			case peripheral::TMR5:
				SYSTEM::MSTPCRA.MSTPA3 = f;
				break;
			case peripheral::TMR3:
			case peripheral::TMR2:
				SYSTEM::MSTPCRA.MSTPA4 = f;
				break;
			case peripheral::TMR1:
			case peripheral::TMR0:
				SYSTEM::MSTPCRA.MSTPA5 = f;
				break;

			case peripheral::HRPWM:
				SYSTEM::MSTPCRA.MSTPA7 = f;
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
				sr_(ena, pad_.mtu3_, peripheral::MTU0, per);
				SYSTEM::MSTPCRA.MSTPA9 = ((pad_.mtu3_ & 0b1'1111'1111) == 0);
				break;

			case peripheral::CMT0:
			case peripheral::CMT1:
				// CMT0, CMT1 のストップ状態設定
				sr_(ena, pad_.cmt_, peripheral::CMT0, per);
				SYSTEM::MSTPCRA.MSTPA15 = ((pad_.cmt_ & 0b0011) == 0);
				break;
			case peripheral::CMT2:
			case peripheral::CMT3:
				sr_(ena, pad_.cmt_, peripheral::CMT0, per);
				SYSTEM::MSTPCRA.MSTPA14 = ((pad_.cmt_ & 0b1100) == 0);
				break;

			case peripheral::S12AD1:
				SYSTEM::MSTPCRA.MSTPA16 = f;	// S12AD1 のストップ状態解除
				break;
			case peripheral::S12AD:
				SYSTEM::MSTPCRA.MSTPA17 = f;	// S12AD のストップ状態解除
				break;

			case peripheral::R12DA:
				SYSTEM::MSTPCRA.MSTPA19 = f;	// R12DA のストップ状態解除
				break;
			case peripheral::S12AD2:
				SYSTEM::MSTPCRA.MSTPA23 = f;	// S12AD2 のストップ状態解除
				break;

			case peripheral::DMAC0:
			case peripheral::DMAC1:
			case peripheral::DMAC2:
			case peripheral::DMAC3:
			case peripheral::DMAC4:
			case peripheral::DMAC5:
			case peripheral::DMAC6:
			case peripheral::DMAC7:
			case peripheral::DTC:
				sr_(ena, pad_.dma_dtc_, peripheral::DMAC0, per);
				SYSTEM::MSTPCRA.MSTPA28 = ((pad_.dma_dtc_ & 0b1'1111'1111) == 0);
				break;

			case peripheral::SCI12:
				SYSTEM::MSTPCRB.MSTPB4 = f;		// SCI12 のストップ状態解除
				break;

			case peripheral::DOC:
				SYSTEM::MSTPCRB.MSTPB6 = f;		// DOC のストップ状態解除
				break;

			case peripheral::ELC:
				SYSTEM::MSTPCRB.MSTPB9 = f;		// ELC のストップ状態解除
				break;

			case peripheral::CMPC0:
			case peripheral::CMPC1:
			case peripheral::CMPC2:
			case peripheral::CMPC3:
			case peripheral::CMPC4:
			case peripheral::CMPC5:
				sr_(ena, pad_.cmpc_, peripheral::CMPC0, per);
				SYSTEM::MSTPCRB.MSTPB10 = ((pad_.cmpc_ & 0b11'1111) == 0);
				break;

			case peripheral::RSPI0:
				SYSTEM::MSTPCRB.MSTPB17 = f;
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
			case peripheral::SCI1:
				SYSTEM::MSTPCRB.MSTPB30 = f;
				break;

			case peripheral::CAC:
				SYSTEM::MSTPCRC.MSTPC19 = f;
				break;

			case peripheral::RSCI11:
				SYSTEM::MSTPCRC.MSTPC24 = f;
				break;

			case peripheral::RSCI9:
				SYSTEM::MSTPCRC.MSTPC26 = f;
				break;
			case peripheral::RSCI8:
				SYSTEM::MSTPCRC.MSTPC27 = f;
				break;

			case peripheral::RI3C0:
				SYSTEM::MSTPCRD.MSTPD5 = f;
				break;

			case peripheral::CANFD0:
				SYSTEM::MSTPCRD.MSTPD10 = f;
				break;

			case peripheral::RSPIA0:
				SYSTEM::MSTPCRD.MSTPD26 = f;
				break;

			case peripheral::TSIP_L:
				SYSTEM::MSTPCRD.MSTPD27 = f;
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
