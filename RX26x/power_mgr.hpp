#pragma once
//=========================================================================//
/*!	@file
	@brief	Low Power Consumption / 消費電力低減機能 (RX260/RX261)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX26x/peripheral.hpp"
#include "RX26x/system.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  省電力制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class power_mgr {

		static inline uint8_t	gptw_ = 0;
		static inline uint8_t	cmt_ = 0;
		static inline uint8_t	dma_dtc_ = 0;

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
			case peripheral::TMR3:
			case peripheral::TMR2:
				SYSTEM::MSTPCRA.MSTPA4 = f;
				break;
			case peripheral::TMR1:
			case peripheral::TMR0:
				SYSTEM::MSTPCRA.MSTPA5 = f;
				break;

			case peripheral::GPTW0:
			case peripheral::GPTW1:
			case peripheral::GPTW2:
			case peripheral::GPTW3:
			case peripheral::GPTW4:
			case peripheral::GPTW5:
			case peripheral::GPTW6:
			case peripheral::GPTW7:
				sr_(ena, gptw_, peripheral::GPTW0, per);
				SYSTEM::MSTPCRA.MSTPA7 = (gptw_ == 0);
				break;

			case peripheral::CMT2:
			case peripheral::CMT3:
				sr_(ena, cmt_, peripheral::CMT0, per);
				SYSTEM::MSTPCRA.MSTPA14 = ((cmt_ & 0b1100) == 0);
				break;
			case peripheral::CMT0:
			case peripheral::CMT1:
				sr_(ena, cmt_, peripheral::CMT0, per);
				SYSTEM::MSTPCRA.MSTPA15 = ((cmt_ & 0b0011) == 0);
				break;

			case peripheral::S12AD:
				SYSTEM::MSTPCRA.MSTPA17 = f;
				break;
			case peripheral::DA:
				SYSTEM::MSTPCRA.MSTPA19 = f;
				break;

			case peripheral::DMAC0:
			case peripheral::DMAC1:
			case peripheral::DMAC2:
			case peripheral::DMAC3:
			case peripheral::DTC:
				sr_(ena, dma_dtc_, peripheral::DMAC0, per);
				SYSTEM::MSTPCRA.MSTPA28 = ((dma_dtc_ & 0b1'1111) == 0);
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
#if defined(SIG_RX261)
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

			case peripheral::SCI6:
				SYSTEM::MSTPCRB.MSTPB25 = f;
				break;
			case peripheral::SCI5:
				SYSTEM::MSTPCRB.MSTPB26 = f;
				break;
			case peripheral::SCI1:
				SYSTEM::MSTPCRB.MSTPB30 = f;
				break;

			case peripheral::RSCI0:
				SYSTEM::MSTPCRB.MSTPB31 = f;
				break;

			case peripheral::CAC:
				SYSTEM::MSTPCRC.MSTPC19 = f;
				break;

			case peripheral::RSCI9:
				SYSTEM::MSTPCRC.MSTPC26 = f;
				break;
			case peripheral::RSCI8:
				SYSTEM::MSTPCRC.MSTPC27 = f;
				break;

			case peripheral::REMC0:
				SYSTEM::MSTPCRC.MSTPC29 = f;
				break;
#if defined(SIG_RX261)
			case peripheral::CANFD0:
				SYSTEM::MSTPCRD.MSTPD9 = f;
				break;
#endif
			case peripheral::CTSU:
				SYSTEM::MSTPCRD.MSTPD10 = f;
				break;

			case peripheral::RSIP:
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
