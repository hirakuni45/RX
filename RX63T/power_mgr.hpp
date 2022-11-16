#pragma once
//=====================================================================//
/*!	@file
	@brief	RX63T グループ・電力制御 @n
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX63T/system.hpp"
#include "RX63T/peripheral.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX63T 電力制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class _>
	struct power_mgr_t {

		struct pad_t {

			uint8_t		gpta_;
			uint8_t		gptb_;

			uint8_t		mtu_;

			uint8_t		cmt_;

			uint8_t		dmac_;

			uint8_t		dpc_;

			pad_t() :
				gpta_(0), gptb_(0),
				mtu_(0),

				cmt_(0),

				dmac_(0),

				dpc_(0)
			{ }
		};
		static pad_t	pad_;

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
			case peripheral::GPT4:
			case peripheral::GPT5:
			case peripheral::GPT6:
			case peripheral::GPT7:
				sr_(ena, pad_.gptb_, peripheral::GPT4, per);
				SYSTEM::MSTPCRA.MSTPA6 = (pad_.gptb_ == 0);
				break;
			case peripheral::GPT0:
			case peripheral::GPT1:
			case peripheral::GPT2:
			case peripheral::GPT3:
				sr_(ena, pad_.gpta_, peripheral::GPT0, per);
				SYSTEM::MSTPCRA.MSTPA7 = (pad_.gpta_ == 0);
				break;

			case peripheral::MTU0:
			case peripheral::MTU1:
			case peripheral::MTU2:
			case peripheral::MTU3:
			case peripheral::MTU4:
			case peripheral::MTU5:
			case peripheral::MTU6:
			case peripheral::MTU7:
				sr_(ena, pad_.mtu_, peripheral::MTU0, per);
				SYSTEM::MSTPCRA.MSTPA9 = (pad_.mtu_ == 0);
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

			case peripheral::S12ADB1:
				SYSTEM::MSTPCRA.MSTPA16 = f;
				SYSTEM::MSTPCRA.MSTPA24 = f;
				break;
			case peripheral::S12ADB:
			case peripheral::S12ADB0:
				SYSTEM::MSTPCRA.MSTPA17 = f;
				SYSTEM::MSTPCRA.MSTPA24 = f;
				break;

			case peripheral::DA:
				SYSTEM::MSTPCRA.MSTPA19 = f;
				break;

			case peripheral::AD:
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

			case peripheral::CAN1:
				SYSTEM::MSTPCRB.MSTPB1 = f;
				break;

			case peripheral::SCI12:
				SYSTEM::MSTPCRB.MSTPB4 = f;
				break;

			case peripheral::DOC:
				SYSTEM::MSTPCRB.MSTPB6 = f;
				break;

			case peripheral::RSPI1:
				SYSTEM::MSTPCRB.MSTPB16 = f;
				break;
			case peripheral::RSPI0:
				SYSTEM::MSTPCRB.MSTPB17 = f;
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
				
			case peripheral::CAC:
				SYSTEM::MSTPCRC.MSTPC19 = f;
				break;

			case peripheral::DPC0:
			case peripheral::DPC1:
			case peripheral::DPC2:
			case peripheral::DPC3:
				sr_(ena, pad_.dpc_, peripheral::DPC0, per);
				SYSTEM::MSTPCRC.MSTPC31 = (pad_.dpc_ == 0);
				break;

			default:
				ret = false;
				break;
			}
			device::SYSTEM::PRCR = 0xA500;
			return ret;
		}
	};
	template <class _> typename power_mgr_t<_>::pad_t power_mgr_t<_>::pad_;

	typedef power_mgr_t<void> power_mgr;
}
