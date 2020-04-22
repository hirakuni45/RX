#pragma once
//=====================================================================//
/*!	@file
	@brief	RX72M グループ・電力制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX72M/peripheral.hpp"
#include "RX600/system.hpp"
#include "RX600/bus.hpp"
#include "common/static_holder.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  電力制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class power_mgr {

		struct pad_t {

			uint16_t	cmt_;
			uint16_t	tpu_;
			uint16_t	tmr_;
			uint16_t	mtu_;
			uint16_t	dmac_;

			pad_t() : cmt_(0), tpu_(0), tmr_(0), mtu_(0), dmac_(0) { }
		};

		typedef utils::static_holder<pad_t> STH;

		static void set_(bool f, uint16_t& pad, peripheral org, peripheral tgt)
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
			case peripheral::CMTW0:
				SYSTEM::MSTPCRA.MSTPA0 = f;
				break;
			case peripheral::CMTW1:
				SYSTEM::MSTPCRA.MSTPA1 = f;
				break;

			case peripheral::TMR2:
			case peripheral::TMR3:
				set_(ena, STH::st.tmr_, peripheral::TMR0, t);
				SYSTEM::MSTPCRA.MSTPA4 = ((STH::st.tmr_ & 0b1100) == 0);

				break;
			case peripheral::TMR0:
			case peripheral::TMR1:
				set_(ena, STH::st.tmr_, peripheral::TMR0, t);
				SYSTEM::MSTPCRA.MSTPA5 = ((STH::st.tmr_ & 0b0011) == 0);
				break;

//			case peripheral::GPTW_POE:
//				SYSTEM::MSTPCRA.MSTPA7 = f;
//				break;

			case peripheral::MTU0:
			case peripheral::MTU1:
			case peripheral::MTU2:
			case peripheral::MTU3:
			case peripheral::MTU4:
			case peripheral::MTU5:
			case peripheral::MTU6:
			case peripheral::MTU7:
				set_(ena, STH::st.mtu_, peripheral::MTU0, t);
				SYSTEM::MSTPCRA.MSTPA9 = (STH::st.mtu_ == 0);
				break;

			case peripheral::PPG1:
				SYSTEM::MSTPCRA.MSTPA10 = f;
				break;
			case peripheral::PPG0:
				SYSTEM::MSTPCRA.MSTPA11 = f;
				break;

			// TPU0 to TPU5 のストップ状態設定
			case peripheral::TPU0:
			case peripheral::TPU1:
			case peripheral::TPU2:
			case peripheral::TPU3:
			case peripheral::TPU4:
			case peripheral::TPU5:
				set_(ena, STH::st.tpu_, peripheral::TPU0, t);
				SYSTEM::MSTPCRA.MSTPA13 = (STH::st.tpu_ == 0);
				break;

			// CMT2, CMT3 のストップ状態設定
			case peripheral::CMT2:
			case peripheral::CMT3:
				set_(ena, STH::st.cmt_, peripheral::CMT0, t);
				SYSTEM::MSTPCRA.MSTPA14 = ((STH::st.cmt_ & 0b1100) == 0);
				break;

			// CMT0, CMT1 のストップ状態設定
			case peripheral::CMT0:
			case peripheral::CMT1:
				set_(ena, STH::st.cmt_, peripheral::CMT0, t);
				SYSTEM::MSTPCRA.MSTPA15 = ((STH::st.cmt_ & 0b0011) == 0);
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

			// DMAC/DTC のストップ状態解除
			case peripheral::DMAC0:
			case peripheral::DMAC1:
			case peripheral::DMAC2:
			case peripheral::DMAC3:
			case peripheral::DMAC4:
			case peripheral::DMAC5:
			case peripheral::DMAC6:
			case peripheral::DMAC7:
			case peripheral::DTC:
				set_(ena, STH::st.dmac_, peripheral::DMAC0, t);
				SYSTEM::MSTPCRA.MSTPA28 = (STH::st.dmac_ == 0);
				break;

			// CAN モジュール
			case peripheral::CAN0:
				SYSTEM::MSTPCRB.MSTPB0 = f;
				break;
			case peripheral::CAN1:
				SYSTEM::MSTPCRB.MSTPB1 = f;
				break;
			case peripheral::CAN2:
				SYSTEM::MSTPCRB.MSTPB2 = f;
				break;

			case peripheral::SCI12:
				SYSTEM::MSTPCRB.MSTPB4 = f;		// B-B4 (SCI12)のストップ状態解除
				break;

			case peripheral::DOC:				// データ演算回路
				SYSTEM::MSTPCRB.MSTPB6 = f;
				break;

			case peripheral::TEMPS:				// 温度センサ
				SYSTEM::MSTPCRB.MSTPB8 = f;
				break;

			case peripheral::ELC:				// イベントリンク
				SYSTEM::MSTPCRB.MSTPB9 = f;
				break;

			case peripheral::DSMIF0:			// ΔΣインターフェース 0
			case peripheral::DSMIF1:			// ΔΣインターフェース 1
				SYSTEM::MSTPCRB.MSTPB11 = f;
				break;

			case peripheral::ETHERC1:
			case peripheral::EDMAC1:
			case peripheral::PMGI1:
				SYSTEM::MSTPCRB.MSTPB14 = f;	// ETHER1, EDMAC1 のストップ状態解除
				BUS::BEREN.TOEN = 1;
				break;
			case peripheral::ETHERC0:
			case peripheral::ETHERCA:
			case peripheral::EDMAC0:
			case peripheral::PMGI0:
				SYSTEM::MSTPCRB.MSTPB15 = f;	// ETHER0, EDMAC0 のストップ状態解除
				BUS::BEREN.TOEN = 1;
				break;

			case peripheral::RSPI1:
				SYSTEM::MSTPCRB.MSTPB16 = f;	// RSPI1 のストップ状態解除
				break;
			case peripheral::RSPI0:
				SYSTEM::MSTPCRB.MSTPB17 = f;	// RSPI0 のストップ状態解除
				break;

			case peripheral::USB0:
				SYSTEM::MSTPCRB.MSTPB19 = f;	// USB のストップ状態解除
				break;

			case peripheral::RIIC1:
				SYSTEM::MSTPCRB.MSTPB20 = f;	// RIIC1 のストップ状態解除
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

			case peripheral::RAM:
				SYSTEM::MSTPCRC.MSTPC0 = f;		// RAM のストップ状態解除
				break;
			case peripheral::EXTRAM:
				SYSTEM::MSTPCRC.MSTPC2 = f;		// RAM2 のストップ状態解除
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
				SYSTEM::MSTPCRC.MSTPC19 = f;	// CAC のストップ状態解除
				break;

			case peripheral::RSPI2:
				SYSTEM::MSTPCRC.MSTPC22 = f;	// RSPI2 のストップ状態解除
				break;

			case peripheral::QSPI:
				SYSTEM::MSTPCRC.MSTPC23 = f;	// QSPI のストップ状態解除
				break;

			case peripheral::SCI11:
				SYSTEM::MSTPCRC.MSTPC24 = f;	// SCI11 のストップ状態解除
				break;
			case peripheral::SCI10:
				SYSTEM::MSTPCRC.MSTPC25 = f;	// SCI10 のストップ状態解除
				break;
			case peripheral::SCI9:
				SYSTEM::MSTPCRC.MSTPC26 = f;	// SCI9 のストップ状態解除
				break;
			case peripheral::SCI8:
				SYSTEM::MSTPCRC.MSTPC27 = f;	// SCI8 のストップ状態解除
				break;

			case peripheral::DRW2D:
				SYSTEM::MSTPCRC.MSTPC28 = f;	// DRW2D のストップ状態解除
				break;
			case peripheral::GLCDC:
				SYSTEM::MSTPCRC.MSTPC29 = f;	// GLCDC のストップ状態解除
				break;


			case peripheral::ESC:
				SYSTEM::MSTPCRD.MSTPD11 = f;	// ESC(EtherCAT) のストップ状態解除
				break;

			case peripheral::SSIE1:
				SYSTEM::MSTPCRD.MSTPD14 = f;	// SSIE1 のストップ状態解除
				break;
			case peripheral::SSIE0:
				SYSTEM::MSTPCRD.MSTPD15 = f;	// SSIE0 のストップ状態解除
				break;

			case peripheral::SDHI:
				SYSTEM::MSTPCRD.MSTPD19 = f;	// SDHI のストップ状態解除
				break;

			default:
				break;
			}
			device::SYSTEM::PRCR = 0xA500;
		}
	};
}
