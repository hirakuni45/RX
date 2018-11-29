#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・省電力制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX600/peripheral.hpp"
#include "RX600/system.hpp"
#include "RX600/bus.hpp"
#include "common/static_holder.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  省電力制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class power_cfg {

		struct pad_t {

			uint8_t		cmt_;
			uint8_t		tpu_;

			pad_t() : cmt_(0), tpu_(0) { }
		};

		typedef utils::static_holder<pad_t> STH;

		static void set_(bool f, uint8_t& pad, peripheral org, peripheral tgt)
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
			@param[in]	t	周辺機器タイプ
			@param[in]	ena	オフにする場合「false」
		*/
		//-----------------------------------------------------------------//
		static void turn(peripheral t, bool ena = true)
		{
			device::SYSTEM::PRCR = 0xA500 | device::SYSTEM::PRCR.PRC1.b();

			bool f = !ena;
			switch(t) {
			case peripheral::CMT0:
			case peripheral::CMT1:
				// CMT0, CMT1 のストップ状態設定
				set_(ena, STH::st.cmt_, peripheral::CMT0, t);
				SYSTEM::MSTPCRA.MSTPA15 = ((STH::st.cmt_ & 0b0011) == 0);
				break;
			case peripheral::CMT2:
			case peripheral::CMT3:
				// CMT2, CMT3 のストップ状態設定
				set_(ena, STH::st.cmt_, peripheral::CMT0, t);
				SYSTEM::MSTPCRA.MSTPA14 = ((STH::st.cmt_ & 0b1100) == 0);
				break;

			case peripheral::CMTW0:
				SYSTEM::MSTPCRA.MSTPA0 = f;
				break;
			case peripheral::CMTW1:
				SYSTEM::MSTPCRA.MSTPA1 = f;
				break;

			case peripheral::TPU0:
			case peripheral::TPU1:
			case peripheral::TPU2:
			case peripheral::TPU3:
			case peripheral::TPU4:
			case peripheral::TPU5:
				// TPU0 to TPU5 のストップ状態設定
				set_(ena, STH::st.tpu_, peripheral::TPU0, t);
				SYSTEM::MSTPCRA.MSTPA13 = (STH::st.tpu_ == 0);
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
				SYSTEM::MSTPCRA.MSTPA28 = f;	// DMAC/DTC のストップ状態解除
				break;

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

			case peripheral::SCI12:
				SYSTEM::MSTPCRB.MSTPB4 = f;		// B-B4 (SCI12)のストップ状態解除
				break;
			case peripheral::SCIF8:
				SYSTEM::MSTPCRC.MSTPC27 = f;	// C-B27 (SCIF8)のストップ状態解除
				break;
			case peripheral::SCIF9:
				SYSTEM::MSTPCRC.MSTPC26 = f;	// C-B26 (SCIF9)のストップ状態解除
				break;
			case peripheral::SCIF10:
				SYSTEM::MSTPCRC.MSTPC25 = f;	// C-B25 (SCIF10のストップ状態解除
				break;
			case peripheral::SCIF11:
				SYSTEM::MSTPCRC.MSTPC24 = f;	// C-B24 (SCIF11のストップ状態解除
				break;

			case peripheral::RIIC0:
				SYSTEM::MSTPCRB.MSTPB21 = f;	// RIIC0 のストップ状態解除
				break;
			case peripheral::RIIC2:
				SYSTEM::MSTPCRC.MSTPC17 = f;	// RIIC2 のストップ状態解除
				break;

			case peripheral::RSPI:
				SYSTEM::MSTPCRB.MSTPB17 = f;	// RSPI のストップ状態解除
				break;

			case peripheral::SDHI:
				SYSTEM::MSTPCRD.MSTPD19 = f;	// SDHI のストップ状態解除
				break;

			case peripheral::ETHERC0:
			case peripheral::ETHERCA:
			case peripheral::EDMAC0:
				SYSTEM::MSTPCRB.MSTPB15 = f;	// ETHER0, EDMAC0 のストップ状態解除
				BUS::BEREN.TOEN = 1;
				break;
			case peripheral::ETHERC1:
			case peripheral::EDMAC1:
				SYSTEM::MSTPCRB.MSTPB14 = f;	// ETHER1, EDMAC1 のストップ状態解除
				BUS::BEREN.TOEN = 1;
				break;

			case peripheral::USB0:
				SYSTEM::MSTPCRB.MSTPB19 = f;	// USB のストップ状態解除
				break;
			case peripheral::USBA:
				SYSTEM::MSTPCRB.MSTPB12 = f;	// USBA のストップ状態解除
				break;

			case peripheral::ECCRAM:
				SYSTEM::MSTPCRC.MSTPC6 = f;		// ECC RAM のストップ状態解除
				break;

			case peripheral::STBRAM:
				SYSTEM::MSTPCRC.MSTPC7 = f;		// STANDBY RAM のストップ状態解除
				break;

			default:
				break;
			}
			device::SYSTEM::PRCR = 0xA500;
		}
	};
}
