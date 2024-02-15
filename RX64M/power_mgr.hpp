#pragma once
//=========================================================================//
/*!	@file
	@brief	RX64M/RX71M グループ・電力制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX64M/peripheral.hpp"
#include "RX600/system.hpp"
#include "RX600/bus.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  電力制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class power_mgr {

		struct pad_t {

			uint8_t		tmr_;
			uint8_t		gpt_;
			uint16_t	mtu_;

			uint8_t		cmt_;
			uint8_t		tpu_;

			uint16_t	dmac_;
			uint8_t		exdmac_;

			pad_t() :
				tmr_(0),
				gpt_(0),
				mtu_(0),

				cmt_(0),
				tpu_(0),

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

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  周辺機器に切り替える
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

			case peripheral::CMTW0:
				SYSTEM::MSTPCRA.MSTPA0 = f;
				break;
			case peripheral::CMTW1:
				SYSTEM::MSTPCRA.MSTPA1 = f;
				break;

			case peripheral::TMR2:
			case peripheral::TMR3:
				sr_(ena, pad_.tmr_, peripheral::TMR0, per);
				SYSTEM::MSTPCRA.MSTPA4 = ((pad_.tmr_ & 0b1100) == 0);
				break;
			case peripheral::TMR0:
			case peripheral::TMR1:
				sr_(ena, pad_.tmr_, peripheral::TMR0, per);
				SYSTEM::MSTPCRA.MSTPA5 = ((pad_.tmr_ & 0b0011) == 0);
				break;

			case peripheral::GPT0:
			case peripheral::GPT1:
			case peripheral::GPT2:
			case peripheral::GPT3:
				sr_(ena, pad_.gpt_, peripheral::GPT0, per);
				SYSTEM::MSTPCRA.MSTPA7 = (pad_.gpt_ == 0);
				break;

			case peripheral::MTU0:
			case peripheral::MTU1:
			case peripheral::MTU2:
			case peripheral::MTU3:
			case peripheral::MTU4:
			case peripheral::MTU5:
			case peripheral::MTU6:
			case peripheral::MTU7:
			case peripheral::MTU8:
				sr_(ena, pad_.mtu_, peripheral::MTU0, per);
				SYSTEM::MSTPCRA.MSTPA9 = (pad_.mtu_ == 0);
				break;

			case peripheral::PPG0:
				SYSTEM::MSTPCRA.MSTPA11 = f;
				break;
			case peripheral::PPG1:
				SYSTEM::MSTPCRA.MSTPA10 = f;
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

			case peripheral::CMT0:
			case peripheral::CMT1:
				sr_(ena, pad_.cmt_, peripheral::CMT0, per);
				SYSTEM::MSTPCRA.MSTPA15 = ((pad_.cmt_ & 0b0011) == 0);
				break;
			case peripheral::CMT2:
			case peripheral::CMT3:
				sr_(ena, pad_.cmt_, peripheral::CMT0, per);
				SYSTEM::MSTPCRA.MSTPA14 = ((pad_.cmt_ & 0b1100) == 0);
				break;

			case peripheral::S12AD:
				SYSTEM::MSTPCRA.MSTPA17 = f;	// S12AD のストップ状態解除
				break;
			case peripheral::S12AD1:
				SYSTEM::MSTPCRA.MSTPA16 = f;	// S12AD1 のストップ状態解除
				break;

			case peripheral::R12DA:
				SYSTEM::MSTPCRA.MSTPA19 = f;	// R12DA のストップ状態解除
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
				sr_(ena, pad_.dmac_, peripheral::DMAC0, per);
				SYSTEM::MSTPCRA.MSTPA28 = (pad_.dmac_ == 0);
				break;

			case peripheral::EXDMAC0:
			case peripheral::EXDMAC1:
				sr_(ena, pad_.exdmac_, peripheral::EXDMAC0, per);
				SYSTEM::MSTPCRA.MSTPA29 = (pad_.exdmac_ == 0);
				break;

			case peripheral::CAN0:
				SYSTEM::MSTPCRB.MSTPB0 = f;	// CAN0 のストップ状態解除
				break;
			case peripheral::CAN1:
				SYSTEM::MSTPCRB.MSTPB1 = f;	// CAN1 のストップ状態解除
				break;
			case peripheral::CAN2:
				SYSTEM::MSTPCRB.MSTPB2 = f;	// CAN2 のストップ状態解除
				break;

			case peripheral::SCI12:
				SYSTEM::MSTPCRB.MSTPB4 = f;		// B-B4 (SCI12)のストップ状態解除
				break;

			case peripheral::DOC:
				SYSTEM::MSTPCRB.MSTPB6 = f;
				break;

			case peripheral::TEMPS:
				SYSTEM::MSTPCRB.MSTPB8 = f;
				break;

			case peripheral::ELC:
				SYSTEM::MSTPCRB.MSTPB9 = f;		// ELC のストップ状態解除
				break;

			case peripheral::USBA:
				SYSTEM::MSTPCRB.MSTPB12 = f;	// USBA のストップ状態解除
				break;

			case peripheral::ETHERC0:
			case peripheral::EDMAC0:
				SYSTEM::MSTPCRB.MSTPB15 = f;	// ETHER0, EDMAC0 のストップ状態解除
				BUS::BEREN.TOEN = 1;
				break;
			case peripheral::ETHERC1:
			case peripheral::EDMAC1:
				SYSTEM::MSTPCRB.MSTPB14 = f;	// ETHER1, EDMAC1 のストップ状態解除
				BUS::BEREN.TOEN = 1;
				break;
#if defined(SIG_RX71M)
			case peripheral::RSPI1:
				SYSTEM::MSTPCRB.MSTPB16 = f;	// RSPI1 のストップ状態解除
				break;
#endif
			case peripheral::RSPI0:
				SYSTEM::MSTPCRB.MSTPB17 = f;	// RSPI0 のストップ状態解除
				break;

			case peripheral::USB0:
				SYSTEM::MSTPCRB.MSTPB19 = f;	// USB のストップ状態解除
				break;

			case peripheral::RIIC0:
				SYSTEM::MSTPCRB.MSTPB21 = f;	// RIIC0 のストップ状態解除
				break;

			case peripheral::PDC:
				SYSTEM::MSTPCRB.MSTPB22 = f;
				break;
			case peripheral::CRC:
				SYSTEM::MSTPCRB.MSTPB23 = f;
				break;

			case peripheral::SCI7:
				SYSTEM::MSTPCRB.MSTPB24 = f;	// B24 (SCI7)のストップ状態解除
				break;
			case peripheral::SCI6:
				SYSTEM::MSTPCRB.MSTPB25 = f;	// B25 (SCI6)のストップ状態解除
				break;
			case peripheral::SCI5:
				SYSTEM::MSTPCRB.MSTPB26 = f;	// B26 (SCI5)のストップ状態解除
				break;
			case peripheral::SCI4:
				SYSTEM::MSTPCRB.MSTPB27 = f;	// B27 (SCI4)のストップ状態解除
				break;
			case peripheral::SCI3:
				SYSTEM::MSTPCRB.MSTPB28 = f;	// B28 (SCI3)のストップ状態解除
				break;
			case peripheral::SCI2:
				SYSTEM::MSTPCRB.MSTPB29 = f;	// B29 (SCI2)のストップ状態解除
				break;
			case peripheral::SCI1:
				SYSTEM::MSTPCRB.MSTPB30 = f;	// B30 (SCI1)のストップ状態解除
				break;
			case peripheral::SCI0:
				SYSTEM::MSTPCRB.MSTPB31 = f;	// B31 (SCI0)のストップ状態解除
				break;

			case peripheral::ECCRAM:
				SYSTEM::MSTPCRC.MSTPC6 = f;		// ECC RAM のストップ状態解除
				break;

			case peripheral::STBRAM:
				SYSTEM::MSTPCRC.MSTPC7 = f;		// STANDBY RAM のストップ状態解除
				break;

			case peripheral::RIIC2:
				SYSTEM::MSTPCRC.MSTPC17 = f;	// RIIC2 のストップ状態解除
				break;

			case peripheral::CAC:
				SYSTEM::MSTPCRC.MSTPC19 = f;
				break;

			case peripheral::QSPI:
				SYSTEM::MSTPCRC.MSTPC23 = f;
				break;

			case peripheral::SCIF11:
				SYSTEM::MSTPCRC.MSTPC24 = f;	// C-B24 (SCIF11のストップ状態解除
				break;
			case peripheral::SCIF10:
				SYSTEM::MSTPCRC.MSTPC25 = f;	// C-B25 (SCIF10のストップ状態解除
				break;
			case peripheral::SCIF9:
				SYSTEM::MSTPCRC.MSTPC26 = f;	// C-B26 (SCIF9)のストップ状態解除
				break;
			case peripheral::SCIF8:
				SYSTEM::MSTPCRC.MSTPC27 = f;	// C-B27 (SCIF8)のストップ状態解除
				break;

			case peripheral::SSI1:
				SYSTEM::MSTPCRD.MSTPD14 = f;	// SSI1 のストップ状態解除
				break;
			case peripheral::SSI0:
				SYSTEM::MSTPCRD.MSTPD15 = f;	// SSI0 のストップ状態解除
				break;

			case peripheral::SDHI:
				SYSTEM::MSTPCRD.MSTPD19 = f;	// SDHI のストップ状態解除
				break;

			case peripheral::MMCIF:
				SYSTEM::MSTPCRD.MSTPD21 = f;
				break;
	
			case peripheral::SRC:
				SYSTEM::MSTPCRD.MSTPD23 = f;
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
