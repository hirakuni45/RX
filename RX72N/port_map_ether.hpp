#pragma once
//=========================================================================//
/*!	@file
	@brief	RX66N/RX72N/RX72M グループ・ポート・マッピング （Ethernet) 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#if defined(SIG_RX66N)
#include "RX66N/peripheral.hpp"
#include "RX72N/port.hpp"
#include "RX66N/mpc.hpp"
#elif defined(SIG_RX72N)
#include "RX72N/peripheral.hpp"
#include "RX72N/port.hpp"
#include "RX72N/mpc.hpp"
#elif defined(SIG_RX72M)
#include "RX72M/peripheral.hpp"
#include "RX72N/port.hpp"
#include "RX72M/mpc.hpp"
#endif
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Ethernet ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_ether : public port_map_order {

		static void ether0_mdc_mdio_(ORDER mdc, ORDER mdio, bool ena, uint8_t& err)
		{
			uint8_t mii = ena ? 0b01'0001 : 0;
			switch(mdc) {
			// ET0_MDC: P72 (LFQFP100: ---) (LFQFP144:  85) (LFQFP176: 101)
			// ET0_MDC: PA4 (LFQFP100:  66) (LFQFP144:  92) (LFQFP176: 109)
			// ET0_MDC: PK0 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT7::PMR.B2 = 0;
				MPC::P72PFS.PSEL = mii;
				PORT7::PMR.B2 = ena;
				break;
			case ORDER::SECOND:
				PORTA::PMR.B4 = 0;
				MPC::PA4PFS.PSEL = mii;
				PORTA::PMR.B4 = ena;
				break;
			case ORDER::THIRD:
				PORTK::PMR.B0 = 0;
				MPC::PK0PFS.PSEL = mii;
				PORTK::PMR.B0 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(mdio) {
			// ET0_MDIO: P71 (LFQFP100: ---) (LFQFP144:  86) (LFQFP176: 102)
			// ET0_MDIO: PA3 (LFQFP100:  67) (LFQFP144:  94) (LFQFP176: 110)
			// ET0_MDIO: PL7 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT7::PMR.B1 = 0;
				MPC::P71PFS.PSEL = mii;
				PORT7::PMR.B1 = ena;
				break;
			case ORDER::SECOND:
				PORTA::PMR.B3 = 0;
				MPC::PA3PFS.PSEL = mii;
				PORTA::PMR.B3 = ena;
				break;
			case ORDER::THIRD:
				PORTL::PMR.B7 = 0;
				MPC::PL7PFS.PSEL = mii;
				PORTL::PMR.B7 = ena;
				break;
			default:
				++err;
				break;
			}
		}

#if defined(SIG_RX72N) || defined(SIG_RX72M)
		static void ether1_mdc_mdio_(ORDER mdc, ORDER mdio, bool ena, uint8_t& err)
		{
			uint8_t mii = ena ? 0b01'0001 : 0;
			switch(mdc) {
			// ET1_MDC: P31 (LFQFP100:  19) (LFQFP144:  28) (LFQFP176:  32)
			// ET1_MDC: PD5 (LFQFP100:  81) (LFQFP144: 121) (LFQFP176: 147)
			// ET1_MDC: PN5 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT3::PMR.B1 = 0;
				MPC::P31PFS.PSEL = mii;
				PORT3::PMR.B1 = ena;
				break;
			case ORDER::SECOND:
				PORTD::PMR.B5 = 0;
				MPC::PD5PFS.PSEL = mii;
				PORTD::PMR.B5 = ena;
				break;
			case ORDER::THIRD:
				PORTN::PMR.B5 = 0;
				MPC::PN5PFS.PSEL = mii;
				PORTN::PMR.B5 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(mdio) {
			// ET1_MDIO: P30 (LFQFP100:  20) (LFQFP144:  29) (LFQFP176:  33)
			// ET1_MDIO: PD4 (LFQFP100:  82) (LFQFP144: 122) (LFQFP176: 148)
			// ET1_MDIO: PN4 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT3::PMR.B0 = 0;
				MPC::P30PFS.PSEL = mii;
				PORT3::PMR.B0 = ena;
				break;
			case ORDER::SECOND:
				PORTD::PMR.B4 = 0;
				MPC::PD4PFS.PSEL = mii;
				PORTD::PMR.B4 = ena;
				break;
			case ORDER::THIRD:
				PORTN::PMR.B4 = 0;
				MPC::PN4PFS.PSEL = mii;
				PORTN::PMR.B4 = ena;
				break;
			default:
				++err;
				break;
			}
		}
#endif

		static bool ether0_(const ether_rmii_t& port, bool ena)
		{
			uint8_t err = 0;
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			uint8_t rmii = ena ? 0b01'0010 : 0;

			switch(port.ref50ck_) {
			// REF50CK0: P76 (LFQFP100: ---) (LFQFP144:  69) (LFQFP176:  85)
			// REF50CK0: PB2 (LFQFP100:  58) (LFQFP144:  83) (LFQFP176:  99)
			// REF50CK0: PE5 (LFQFP100:  73) (LFQFP144: 106) (LFQFP176: 130)
			// REF50CK0: PL3 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT7::PMR.B6 = 0;
				MPC::P76PFS.PSEL = rmii;
				PORT7::PMR.B6 = ena;
				break;
			case ORDER::SECOND:
				PORTB::PMR.B2 = 0;
				MPC::PB2PFS.PSEL = rmii;
				PORTB::PMR.B2 = ena;
				break;
			case ORDER::THIRD:
				PORTE::PMR.B5 = 0;
				MPC::PE5PFS.PSEL = rmii;
				PORTE::PMR.B5 = ena;
				break;
			case ORDER::FOURTH:
				PORTL::PMR.B3 = 0;
				MPC::PL3PFS.PSEL = rmii;
				PORTL::PMR.B3 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.crs_dv_) {
			// RMII0_CRS_DV: P83 (LFQFP100: ---) (LFQFP144:  58) (LFQFP176:  74)
			// RMII0_CRS_DV: PB7 (LFQFP100:  53) (LFQFP144:  78) (LFQFP176:  94)
			// RMII0_CRS_DV: PM7 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT8::PMR.B3 = 0;
				MPC::P83PFS.PSEL = rmii;
				PORT8::PMR.B3 = ena;
				break;
			case ORDER::SECOND:
				PORTB::PMR.B7 = 0;
				MPC::PB7PFS.PSEL = rmii;
				PORTB::PMR.B7 = ena;
				break;
			case ORDER::THIRD:
				PORTM::PMR.B7 = 0;
				MPC::PM7PFS.PSEL = rmii;
				PORTM::PMR.B7 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.txd0_) {
			// RMII0_TXD0: P81 (LFQFP100: ---) (LFQFP144:  64) (LFQFP176:  80)
			// RMII0_TXD0: PB5 (LFQFP100:  55) (LFQFP144:  80) (LFQFP176:  96)
			// RMII0_TXD0: PL4 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT8::PMR.B1 = 0;
				MPC::P81PFS.PSEL = rmii;
				PORT8::PMR.B1 = ena;
				break;
			case ORDER::SECOND:
				PORTB::PMR.B5 = 0;
				MPC::PB5PFS.PSEL = rmii;
				PORTB::PMR.B5 = ena;
				break;
			case ORDER::THIRD:
				PORTL::PMR.B4 = 0;
				MPC::PL4PFS.PSEL = rmii;
				PORTL::PMR.B4 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.txd1_) {
			// RMII0_TXD1: P82 (LFQFP100: ---) (LFQFP144:  63) (LFQFP176:  79)
			// RMII0_TXD1: PB6 (LFQFP100:  54) (LFQFP144:  79) (LFQFP176:  95)
			// RMII0_TXD1: PL5 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT8::PMR.B2 = 0;
				MPC::P82PFS.PSEL = rmii;
				PORT8::PMR.B2 = ena;
				break;
			case ORDER::SECOND:
				PORTB::PMR.B6 = 0;
				MPC::PB6PFS.PSEL = rmii;
				PORTB::PMR.B6 = ena;
				break;
			case ORDER::THIRD:
				PORTL::PMR.B5 = 0;
				MPC::PL5PFS.PSEL = rmii;
				PORTL::PMR.B5 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.rxd0_) {
			// RMII0_RXD0: P75 (LFQFP100: ---) (LFQFP144:  71) (LFQFP176:  87)
			// RMII0_RXD0: PB1 (LFQFP100:  59) (LFQFP144:  84) (LFQFP176: 100)
			// RMII0_RXD0: PL0 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT7::PMR.B5 = 0;
				MPC::P75PFS.PSEL = rmii;
				PORT7::PMR.B5 = ena;
				break;
			case ORDER::SECOND:
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = rmii;
				PORTB::PMR.B1 = ena;
				break;
			case ORDER::THIRD:
				PORTL::PMR.B0 = 0;
				MPC::PL0PFS.PSEL = rmii;
				PORTL::PMR.B0 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.rxd1_) {
			// RMII0_RXD1: P74 (LFQFP100: ---) (LFQFP144:  72) (LFQFP176:  88)
			// RMII0_RXD1: PB0 (LFQFP100:  61) (LFQFP144:  87) (LFQFP176: 104)
			// RMII0_RXD1: PL1 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT7::PMR.B4 = 0;
				MPC::P74PFS.PSEL = rmii;
				PORT7::PMR.B4 = ena;
				break;
			case ORDER::SECOND:
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = rmii;
				PORTB::PMR.B0 = ena;
				break;
			case ORDER::THIRD:
				PORTL::PMR.B1 = 0;
				MPC::PL1PFS.PSEL = rmii;
				PORTL::PMR.B1 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.txd_en_) {
			// RMII0_TXD_EN: P80 (LFQFP100: ---) (LFQFP144:  65) (LFQFP176:  81)
			// RMII0_TXD_EN: PA0 (LFQFP100:  70) (LFQFP144:  97) (LFQFP176: 118)
			// RMII0_TXD_EN: PB4 (LFQFP100:  56) (LFQFP144:  81) (LFQFP176:  97)
			// RMII0_TXD_EN: PL6 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT8::PMR.B0 = 0;
				MPC::P80PFS.PSEL = rmii;
				PORT8::PMR.B0 = ena;
				break;
			case ORDER::SECOND:
				PORTA::PMR.B0 = 0;
				MPC::PA0PFS.PSEL = rmii;
				PORTA::PMR.B0 = ena;
				break;
			case ORDER::THIRD:
				PORTB::PMR.B4 = 0;
				MPC::PB4PFS.PSEL = rmii;
				PORTB::PMR.B4 = ena;
				break;
			case ORDER::FOURTH:
				PORTL::PMR.B6 = 0;
				MPC::PL6PFS.PSEL = rmii;
				PORTL::PMR.B6 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.rx_er_) {
			// RMII0_RX_ER: P77 (LFQFP100: ---) (LFQFP144:  68) (LFQFP176:  84)
			// RMII0_RX_ER: PB3 (LFQFP100:  57) (LFQFP144:  82) (LFQFP176:  98)
			// RMII0_RX_ER: PL2 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT7::PMR.B7 = 0;
				MPC::P77PFS.PSEL = rmii;
				PORT7::PMR.B7 = ena;
				break;
			case ORDER::SECOND:
				PORTB::PMR.B3 = 0;
				MPC::PB3PFS.PSEL = rmii;
				PORTB::PMR.B3 = ena;
				break;
			case ORDER::THIRD:
				PORTL::PMR.B2 = 0;
				MPC::PL2PFS.PSEL = rmii;
				PORTL::PMR.B2 = ena;
				break;
			default:
				++err;
				break;
			}

			ether0_mdc_mdio_(port.mdc_, port.mdio_, ena, err);

			MPC::PFENET.PHYMODE0 = 0;  // RMII

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return err == 0;
		}

#if defined(SIG_RX72N) || defined(SIG_RX72M)
		static bool ether1_(const ether_rmii_t& port, bool ena)
		{
			uint8_t err = 0;
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			uint8_t rmii = ena ? 0b01'0010 : 0;

			switch(port.ref50ck_) {
			// REF50CK1: PD6 (LFQFP100:  80) (LFQFP144: 120) (LFQFP176: 145)
			// REF50CK1: PG0 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: 146)
			// REF50CK1: PQ4 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTD::PMR.B6 = 0;
				MPC::PD6PFS.PSEL = rmii;
				PORTD::PMR.B6 = ena;
				break;
			case ORDER::SECOND:
				PORTG::PMR.B0 = 0;
				MPC::PG0PFS.PSEL = rmii;
				PORTG::PMR.B0 = ena;
				break;
			case ORDER::THIRD:
				PORTQ::PMR.B4 = 0;
				MPC::PQ4PFS.PSEL = rmii;
				PORTQ::PMR.B4 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.crs_dv_) {
			// RMII1_CRS_DV: P92 (LFQFP100: ---) (LFQFP144: 128) (LFQFP176: 160)
			// RMII1_CRS_DV: PQ0 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT9::PMR.B2 = 0;
				MPC::P92PFS.PSEL = rmii;
				PORT9::PMR.B2 = ena;
				break;
			case ORDER::SECOND:
				PORTQ::PMR.B0 = 0;
				MPC::PQ0PFS.PSEL = rmii;
				PORTQ::PMR.B0 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.txd0_) {
			// RMII1_TXD0: P64 (LFQFP100: ---) (LFQFP144: 112) (LFQFP176: 136)
			// RMII1_TXD0: PG3 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: 121)
			// RMII1_TXD0: PQ5 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT6::PMR.B4 = 0;
				MPC::P64PFS.PSEL = rmii;
				PORT6::PMR.B4 = ena;
				break;
			case ORDER::SECOND:
				PORTG::PMR.B3 = 0;
				MPC::PG3PFS.PSEL = rmii;
				PORTG::PMR.B3 = ena;
				break;
			case ORDER::THIRD:
				PORTQ::PMR.B5 = 0;
				MPC::PQ5PFS.PSEL = rmii;
				PORTQ::PMR.B5 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.txd1_) {
			// RMII1_TXD1: P63 (LFQFP100: ---) (LFQFP144: 113) (LFQFP176: 137)
			// RMII1_TXD1: PG4 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: 119)
			// RMII1_TXD1: PQ6 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT6::PMR.B3 = 0;
				MPC::P63PFS.PSEL = rmii;
				PORT6::PMR.B3 = ena;
				break;
			case ORDER::SECOND:
				PORTG::PMR.B4 = 0;
				MPC::PG4PFS.PSEL = rmii;
				PORTG::PMR.B4 = ena;
				break;
			case ORDER::THIRD:
				PORTQ::PMR.B6 = 0;
				MPC::PQ6PFS.PSEL = rmii;
				PORTQ::PMR.B6 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.rxd0_) {
			// RMII1_RXD0: P62 (LFQFP100: ---) (LFQFP144: 114) (LFQFP176: 138)
			// RMII1_RXD0: P94 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: 157)
			// RMII1_RXD0: PM0 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT6::PMR.B2 = 0;
				MPC::P62PFS.PSEL = rmii;
				PORT6::PMR.B2 = ena;
				break;
			case ORDER::SECOND:
				PORT9::PMR.B4 = 0;
				MPC::P94PFS.PSEL = rmii;
				PORT9::PMR.B4 = ena;
				break;
			case ORDER::THIRD:
				PORTM::PMR.B0 = 0;
				MPC::PM0PFS.PSEL = rmii;
				PORTM::PMR.B0 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.rxd1_) {
			// RMII1_RXD1: P61 (LFQFP100: ---) (LFQFP144: 115) (LFQFP176: 139)
			// RMII1_RXD1: P95 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: 155)
			// RMII1_RXD1: PM1 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT6::PMR.B1 = 0;
				MPC::P61PFS.PSEL = rmii;
				PORT6::PMR.B1 = ena;
				break;
			case ORDER::SECOND:
				PORT9::PMR.B5 = 0;
				MPC::P95PFS.PSEL = rmii;
				PORT9::PMR.B5 = ena;
				break;
			case ORDER::THIRD:
				PORTM::PMR.B1 = 0;
				MPC::PM1PFS.PSEL = rmii;
				PORTM::PMR.B1 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.txd_en_) {
			// RMII1_TXD_EN: P60 (LFQFP100: ---) (LFQFP144: 117) (LFQFP176: 141)
			// RMII1_TXD_EN: PQ7 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT6::PMR.B0 = 0;
				MPC::P60PFS.PSEL = rmii;
				PORT6::PMR.B0 = ena;
				break;
			case ORDER::SECOND:
				PORTQ::PMR.B7 = 0;
				MPC::PQ7PFS.PSEL = rmii;
				PORTQ::PMR.B7 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.rx_er_) {
			// RMII1_RX_ER: PD7 (LFQFP100:  79) (LFQFP144: 119) (LFQFP176: 143)
			// RMII1_RX_ER: PG1 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: 144)
			// RMII1_RX_ER: PN3 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTD::PMR.B7 = 0;
				MPC::PD7PFS.PSEL = rmii;
				PORTD::PMR.B7 = ena;
				break;
			case ORDER::SECOND:
				PORTG::PMR.B1 = 0;
				MPC::PG1PFS.PSEL = rmii;
				PORTG::PMR.B1 = ena;
				break;
			case ORDER::THIRD:
				PORTN::PMR.B3 = 0;
				MPC::PN3PFS.PSEL = rmii;
				PORTN::PMR.B3 = ena;
				break;
			default:
				++err;
				break;
			}

			ether1_mdc_mdio_(port.mdc_, port.mdio_, ena, err);

			MPC::PFENET.PHYMODE1 = 0;  // RMII

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return err == 0;
		}
#endif

		static bool ether0_(const ether_mii_t& port, bool ena)
		{
			uint8_t err = 0;
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			uint8_t mii = ena ? 0b01'0001 : 0;

			switch(port.crs_) {
			// ET0_CRS: P83 (LFQFP100: ---) (LFQFP144:  58) (LFQFP176:  74)
			// ET0_CRS: PB7 (LFQFP100:  53) (LFQFP144:  78) (LFQFP176:  94)
			// ET0_CRS: PM7 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT8::PMR.B3 = 0;
				MPC::P83PFS.PSEL = mii;
				PORT8::PMR.B3 = ena;
				break;
			case ORDER::SECOND:
				PORTB::PMR.B7 = 0;
				MPC::PB7PFS.PSEL = mii;
				PORTB::PMR.B7 = ena;
				break;
			case ORDER::THIRD:
				PORTM::PMR.B7 = 0;
				MPC::PM7PFS.PSEL = mii;
				PORTM::PMR.B7 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.rx_dv_) {
			// ET0_RX_DV: PC2 (LFQFP100:  50) (LFQFP144:  70) (LFQFP176:  86)
			// ET0_RX_DV: PK2 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTC::PMR.B2 = 0;
				MPC::PC2PFS.PSEL = mii;
				PORTC::PMR.B2 = ena;
				break;
			case ORDER::SECOND:
				PORTK::PMR.B2 = 0;
				MPC::PK2PFS.PSEL = mii;
				PORTK::PMR.B2 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.exout_) {
			// ET0_EX_OUT: P55 (LFQFP100:  39) (LFQFP144:  51) (LFQFP176:  65)
			// ET0_EX_OUT: PA6 (LFQFP100:  64) (LFQFP144:  89) (LFQFP176: 107)
			// ET0_EX_OUT: PJ3 (LFQFP100: ---) (LFQFP144:  13) (LFQFP176:  13)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT5::PMR.B5 = 0;
				MPC::P55PFS.PSEL = mii;
				PORT5::PMR.B5 = ena;
				break;
			case ORDER::SECOND:
				PORTA::PMR.B6 = 0;
				MPC::PA6PFS.PSEL = mii;
				PORTA::PMR.B6 = ena;
				break;
			case ORDER::THIRD:
				PORTJ::PMR.B3 = 0;
				MPC::PJ3PFS.PSEL = mii;
				PORTJ::PMR.B3 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.linksta_) {
			// ET0_LINKSTA: P34 (LFQFP100:  16) (LFQFP144:  25) (LFQFP176:  27)
			// ET0_LINKSTA: P54 (LFQFP100:  40) (LFQFP144:  52) (LFQFP176:  66)
			// ET0_LINKSTA: PA5 (LFQFP100:  65) (LFQFP144:  90) (LFQFP176: 108)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT3::PMR.B4 = 0;
				MPC::P34PFS.PSEL = mii;
				PORT3::PMR.B4 = ena;
				break;
			case ORDER::SECOND:
				PORT5::PMR.B4 = 0;
				MPC::P54PFS.PSEL = mii;
				PORT5::PMR.B4 = ena;
				break;
			case ORDER::THIRD:
				PORTA::PMR.B5 = 0;
				MPC::PA5PFS.PSEL = mii;
				PORTA::PMR.B5 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.etxd0_) {
			// ET0_ETXD0: P81 (LFQFP100: ---) (LFQFP144:  64) (LFQFP176:  80)
			// ET0_ETXD0: PB5 (LFQFP100:  55) (LFQFP144:  80) (LFQFP176:  96)
			// ET0_ETXD0: PL4 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT8::PMR.B1 = 0;
				MPC::P81PFS.PSEL = mii;
				PORT8::PMR.B1 = ena;
				break;
			case ORDER::SECOND:
				PORTB::PMR.B5 = 0;
				MPC::PB5PFS.PSEL = mii;
				PORTB::PMR.B5 = ena;
				break;
			case ORDER::THIRD:
				PORTL::PMR.B4 = 0;
				MPC::PL4PFS.PSEL = mii;
				PORTL::PMR.B4 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.etxd1_) {
			// ET0_ETXD1: P82 (LFQFP100: ---) (LFQFP144:  63) (LFQFP176:  79)
			// ET0_ETXD1: PB6 (LFQFP100:  54) (LFQFP144:  79) (LFQFP176:  95)
			// ET0_ETXD1: PL5 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT8::PMR.B2 = 0;
				MPC::P82PFS.PSEL = mii;
				PORT8::PMR.B2 = ena;
				break;
			case ORDER::SECOND:
				PORTB::PMR.B6 = 0;
				MPC::PB6PFS.PSEL = mii;
				PORTB::PMR.B6 = ena;
				break;
			case ORDER::THIRD:
				PORTL::PMR.B5 = 0;
				MPC::PL5PFS.PSEL = mii;
				PORTL::PMR.B5 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.etxd2_) {
			// ET0_ETXD2: PC5 (LFQFP100:  47) (LFQFP144:  62) (LFQFP176:  78)
			// ET0_ETXD2: PM4 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTC::PMR.B5 = 0;
				MPC::PC5PFS.PSEL = mii;
				PORTC::PMR.B5 = ena;
				break;
			case ORDER::SECOND:
				PORTM::PMR.B4 = 0;
				MPC::PM4PFS.PSEL = mii;
				PORTM::PMR.B4 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.etxd3_) {
			// ET0_ETXD3: PC6 (LFQFP100:  46) (LFQFP144:  61) (LFQFP176:  77)
			// ET0_ETXD3: PM5 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTC::PMR.B6 = 0;
				MPC::PC6PFS.PSEL = mii;
				PORTC::PMR.B6 = ena;
				break;
			case ORDER::SECOND:
				PORTM::PMR.B5 = 0;
				MPC::PM5PFS.PSEL = mii;
				PORTM::PMR.B5 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.erxd0_) {
			// ET0_ERXD0: P75 (LFQFP100: ---) (LFQFP144:  71) (LFQFP176:  87)
			// ET0_ERXD0: PB1 (LFQFP100:  59) (LFQFP144:  84) (LFQFP176: 100)
			// ET0_ERXD0: PL0 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT7::PMR.B5 = 0;
				MPC::P75PFS.PSEL = mii;
				PORT7::PMR.B5 = ena;
				break;
			case ORDER::SECOND:
				PORTB::PMR.B1 = 0;
				MPC::PB1PFS.PSEL = mii;
				PORTB::PMR.B1 = ena;
				break;
			case ORDER::THIRD:
				PORTL::PMR.B0 = 0;
				MPC::PL0PFS.PSEL = mii;
				PORTL::PMR.B0 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.erxd1_) {
			// ET0_ERXD1: P74 (LFQFP100: ---) (LFQFP144:  72) (LFQFP176:  88)
			// ET0_ERXD1: PB0 (LFQFP100:  61) (LFQFP144:  87) (LFQFP176: 104)
			// ET0_ERXD1: PL1 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT7::PMR.B4 = 0;
				MPC::P74PFS.PSEL = mii;
				PORT7::PMR.B4 = ena;
				break;
			case ORDER::SECOND:
				PORTB::PMR.B0 = 0;
				MPC::PB0PFS.PSEL = mii;
				PORTB::PMR.B0 = ena;
				break;
			case ORDER::THIRD:
				PORTL::PMR.B1 = 0;
				MPC::PL1PFS.PSEL = mii;
				PORTL::PMR.B1 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.erxd2_) {
			// ET0_ERXD2: PC1 (LFQFP100:  51) (LFQFP144:  73) (LFQFP176:  89)
			// ET0_ERXD2: PE4 (LFQFP100:  74) (LFQFP144: 107) (LFQFP176: 131)
			// ET0_ERXD2: PK4 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTC::PMR.B1 = 0;
				MPC::PC1PFS.PSEL = mii;
				PORTC::PMR.B1 = ena;
				break;
			case ORDER::SECOND:
				PORTE::PMR.B4 = 0;
				MPC::PE4PFS.PSEL = mii;
				PORTE::PMR.B4 = ena;
				break;
			case ORDER::THIRD:
				PORTK::PMR.B4 = 0;
				MPC::PK4PFS.PSEL = mii;
				PORTK::PMR.B4 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.erxd3_) {
			// ET0_ERXD3: PC0 (LFQFP100:  52) (LFQFP144:  75) (LFQFP176:  91)
			// ET0_ERXD3: PE3 (LFQFP100:  75) (LFQFP144: 108) (LFQFP176: 132)
			// ET0_ERXD3: PK5 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTC::PMR.B0 = 0;
				MPC::PC0PFS.PSEL = mii;
				PORTC::PMR.B0 = ena;
				break;
			case ORDER::SECOND:
				PORTE::PMR.B3 = 0;
				MPC::PE3PFS.PSEL = mii;
				PORTE::PMR.B3 = ena;
				break;
			case ORDER::THIRD:
				PORTK::PMR.B5 = 0;
				MPC::PK5PFS.PSEL = mii;
				PORTK::PMR.B5 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.tx_en_) {
			// ET0_TX_EN: P80 (LFQFP100: ---) (LFQFP144:  65) (LFQFP176:  81)
			// ET0_TX_EN: PA0 (LFQFP100:  70) (LFQFP144:  97) (LFQFP176: 118)
			// ET0_TX_EN: PB4 (LFQFP100:  56) (LFQFP144:  81) (LFQFP176:  97)
			// ET0_TX_EN: PL6 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT8::PMR.B0 = 0;
				MPC::P80PFS.PSEL = mii;
				PORT8::PMR.B0 = ena;
				break;
			case ORDER::SECOND:
				PORTA::PMR.B0 = 0;
				MPC::PA0PFS.PSEL = mii;
				PORTA::PMR.B0 = ena;
				break;
			case ORDER::THIRD:
				PORTB::PMR.B4 = 0;
				MPC::PB4PFS.PSEL = mii;
				PORTB::PMR.B4 = ena;
				break;
			case ORDER::FOURTH:
				PORTL::PMR.B6 = 0;
				MPC::PL6PFS.PSEL = mii;
				PORTL::PMR.B6 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.tx_er_) {
			// ET0_TX_ER: PC3 (LFQFP100:  49) (LFQFP144:  67) (LFQFP176:  83)
			// ET0_TX_ER: PK3 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTC::PMR.B3 = 0;
				MPC::PC3PFS.PSEL = mii;
				PORTC::PMR.B3 = ena;
				break;
			case ORDER::SECOND:
				PORTK::PMR.B3 = 0;
				MPC::PK3PFS.PSEL = mii;
				PORTK::PMR.B3 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.rx_er_) {
			// ET0_RX_ER: P77 (LFQFP100: ---) (LFQFP144:  68) (LFQFP176:  84)
			// ET0_RX_ER: PB3 (LFQFP100:  57) (LFQFP144:  82) (LFQFP176:  98)
			// ET0_RX_ER: PL2 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT7::PMR.B7 = 0;
				MPC::P77PFS.PSEL = mii;
				PORT7::PMR.B7 = ena;
				break;
			case ORDER::SECOND:
				PORTB::PMR.B3 = 0;
				MPC::PB3PFS.PSEL = mii;
				PORTB::PMR.B3 = ena;
				break;
			case ORDER::THIRD:
				PORTL::PMR.B2 = 0;
				MPC::PL2PFS.PSEL = mii;
				PORTL::PMR.B2 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.tx_clk_) {
			// ET0_TX_CLK: PC4 (LFQFP100:  48) (LFQFP144:  66) (LFQFP176:  82)
			// ET0_TX_CLK: PM6 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTC::PMR.B4 = 0;
				MPC::PC4PFS.PSEL = mii;
				PORTC::PMR.B4 = ena;
				break;
			case ORDER::SECOND:
				PORTM::PMR.B6 = 0;
				MPC::PM6PFS.PSEL = mii;
				PORTM::PMR.B6 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.rx_clk_) {
			// ET0_RX_CLK: P76 (LFQFP100: ---) (LFQFP144:  89) (LFQFP176:  85)
			// ET0_RX_CLK: PB2 (LFQFP100:  58) (LFQFP144:  83) (LFQFP176:  99)
			// ET0_RX_CLK: PE5 (LFQFP100:  73) (LFQFP144: 106) (LFQFP176: 130)
			// ET0_RX_CLK: PL3 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT7::PMR.B6 = 0;
				MPC::P76PFS.PSEL = mii;
				PORT7::PMR.B6 = ena;
				break;
			case ORDER::SECOND:
				PORTB::PMR.B2 = 0;
				MPC::PB2PFS.PSEL = mii;
				PORTB::PMR.B2 = ena;
				break;
			case ORDER::THIRD:
				PORTE::PMR.B5 = 0;
				MPC::PE5PFS.PSEL = mii;
				PORTE::PMR.B5 = ena;
				break;
			case ORDER::FOURTH:
				PORTL::PMR.B3 = 0;
				MPC::PL3PFS.PSEL = mii;
				PORTL::PMR.B3 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.col_) {
			// ET0_COL: PC7 (LFQFP100:  45) (LFQFP144:  60) (LFQFP176:  76)
			// ET0_COL: PK1 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTC::PMR.B7 = 0;
				MPC::PC7PFS.PSEL = mii;
				PORTC::PMR.B7 = ena;
				break;
			case ORDER::SECOND:
				PORTK::PMR.B1 = 0;
				MPC::PK1PFS.PSEL = mii;
				PORTK::PMR.B1 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.wol_) {
			// ET0_WOL: P73 (LFQFP100: ---) (LFQFP144:  77) (LFQFP176:  93)
			// ET0_WOL: PA1 (LFQFP100:  69) (LFQFP144:  96) (LFQFP176: 114)
			// ET0_WOL: PA7 (LFQFP100:  63) (LFQFP144:  88) (LFQFP176: 106)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT7::PMR.B3 = 0;
				MPC::P73PFS.PSEL = mii;
				PORT7::PMR.B3 = ena;
				break;
			case ORDER::SECOND:
				PORTA::PMR.B1 = 0;
				MPC::PA1PFS.PSEL = mii;
				PORTA::PMR.B1 = ena;
				break;
			case ORDER::THIRD:
				PORTA::PMR.B7 = 0;
				MPC::PA7PFS.PSEL = mii;
				PORTA::PMR.B7 = ena;
				break;
			default:
				++err;
				break;
			}

			ether0_mdc_mdio_(port.mdc_, port.mdio_, ena, err);

			MPC::PFENET.PHYMODE0 = 1;  // MII

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return err == 0;
		}

#if defined(SIG_RX72N) || defined(SIG_RX72M)
		static bool ether1_(const ether_mii_t& port, bool ena)
		{
			uint8_t err = 0;
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			uint8_t mii = ena ? 0b01'0001 : 0;

			switch(port.crs_) {
			// ET1_CRS: P92 (LFQFP100: ---) (LFQFP144: 128) (LFQFP176: 160)
			// ET1_CRS: PQ0 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT9::PMR.B2 = 0;
				MPC::P92PFS.PSEL = mii;
				PORT9::PMR.B2 = ena;
				break;
			case ORDER::SECOND:
				PORTQ::PMR.B0 = 0;
				MPC::PQ0PFS.PSEL = mii;
				PORTQ::PMR.B0 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.rx_dv_) {
			// ET1_RX_DV: P90 (LFQFP100: ---) (LFQFP144: 131) (LFQFP176: 163)
			// ET1_RX_DV: PQ2 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT9::PMR.B0 = 0;
				MPC::P90PFS.PSEL = mii;
				PORT9::PMR.B0 = ena;
				break;
			case ORDER::SECOND:
				PORTQ::PMR.B2 = 0;
				MPC::PQ2PFS.PSEL = mii;
				PORTQ::PMR.B2 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.exout_) {
			// ET1_EX_OUT: P26 (LFQFP100:  22) (LFQFP144:  31) (LFQFP176:  37)
			// ET1_EX_OUT: PD2 (LFQFP100:  84) (LFQFP144: 124) (LFQFP176: 154)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT2::PMR.B6 = 0;
				MPC::P26PFS.PSEL = mii;
				PORT2::PMR.B6 = ena;
				break;
			case ORDER::SECOND:
				PORTD::PMR.B2 = 0;
				MPC::PD2PFS.PSEL = mii;
				PORTD::PMR.B2 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.linksta_) {
			// ET1_LINKSTA: P84 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176:  62)
			// ET1_LINKSTA: P93 (LFQFP100: ---) (LFQFP144: 127) (LFQFP176: 159)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT8::PMR.B4 = 0;
				MPC::P84PFS.PSEL = mii;
				PORT8::PMR.B4 = ena;
				break;
			case ORDER::SECOND:
				PORT9::PMR.B3 = 0;
				MPC::P93PFS.PSEL = mii;
				PORT9::PMR.B3 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.etxd0_) {
			// ET1_ETXD0: P64 (LFQFP100: ---) (LFQFP144: 112) (LFQFP176: 136)
			// ET1_ETXD0: PG3 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: 121)
			// ET1_ETXD0: PQ5 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT6::PMR.B4 = 0;
				MPC::P64PFS.PSEL = mii;
				PORT6::PMR.B4 = ena;
				break;
			case ORDER::SECOND:
				PORTG::PMR.B3 = 0;
				MPC::PG3PFS.PSEL = mii;
				PORTG::PMR.B3 = ena;
				break;
			case ORDER::THIRD:
				PORTQ::PMR.B5 = 0;
				MPC::PQ5PFS.PSEL = mii;
				PORTQ::PMR.B5 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.etxd1_) {
			// ET1_ETXD1: P63 (LFQFP100: ---) (LFQFP144: 113) (LFQFP176: 137)
			// ET1_ETXD1: PG4 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: 119)
			// ET1_ETXD1: PQ6 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT6::PMR.B3 = 0;
				MPC::P63PFS.PSEL = mii;
				PORT6::PMR.B3 = ena;
				break;
			case ORDER::SECOND:
				PORTG::PMR.B4 = 0;
				MPC::PG4PFS.PSEL = mii;
				PORTG::PMR.B4 = ena;
				break;
			case ORDER::THIRD:
				PORTQ::PMR.B6 = 0;
				MPC::PQ6PFS.PSEL = mii;
				PORTQ::PMR.B6 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.etxd2_) {
			// ET1_ETXD2: PG5 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: 116)
			// ET1_ETXD2: PN0 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTG::PMR.B5 = 0;
				MPC::PG5PFS.PSEL = mii;
				PORTG::PMR.B5 = ena;
				break;
			case ORDER::SECOND:
				PORTN::PMR.B0 = 0;
				MPC::PN0PFS.PSEL = mii;
				PORTN::PMR.B0 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.etxd3_) {
			// ET1_ETXD3: PG6 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: 113)
			// ET1_ETXD3: PN1 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTG::PMR.B6 = 0;
				MPC::PG6PFS.PSEL = mii;
				PORTG::PMR.B6 = ena;
				break;
			case ORDER::SECOND:
				PORTN::PMR.B1 = 0;
				MPC::PN1PFS.PSEL = mii;
				PORTN::PMR.B1 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.erxd0_) {
			// ET1_ERXD0: P62 (LFQFP100: ---) (LFQFP144: 114) (LFQFP176: 138)
			// ET1_ERXD0: P94 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: 157)
			// ET1_ERXD0: PM0 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT6::PMR.B2 = 0;
				MPC::P62PFS.PSEL = mii;
				PORT6::PMR.B2 = ena;
				break;
			case ORDER::SECOND:
				PORT9::PMR.B4 = 0;
				MPC::P94PFS.PSEL = mii;
				PORT9::PMR.B4 = ena;
				break;
			case ORDER::THIRD:
				PORTM::PMR.B0 = 0;
				MPC::PM0PFS.PSEL = mii;
				PORTM::PMR.B0 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.erxd1_) {
			// ET1_ERXD1: P61 (LFQFP100: ---) (LFQFP144: 115) (LFQFP176: 139)
			// ET1_ERXD1: P95 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: 155)
			// ET1_ERXD1: PM1 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT6::PMR.B1 = 0;
				MPC::P61PFS.PSEL = mii;
				PORT6::PMR.B1 = ena;
				break;
			case ORDER::SECOND:
				PORT9::PMR.B5 = 0;
				MPC::P95PFS.PSEL = mii;
				PORT9::PMR.B5 = ena;
				break;
			case ORDER::THIRD:
				PORTM::PMR.B1 = 0;
				MPC::PM1PFS.PSEL = mii;
				PORTM::PMR.B1 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.erxd2_) {
			// ET1_ERXD2: P96 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: 152)
			// ET1_ERXD2: PM2 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT9::PMR.B6 = 0;
				MPC::P96PFS.PSEL = mii;
				PORT9::PMR.B6 = ena;
				break;
			case ORDER::SECOND:
				PORTM::PMR.B2 = 0;
				MPC::PM2PFS.PSEL = mii;
				PORTM::PMR.B2 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.erxd3_) {
			// ET1_ERXD3: P97 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: 149)
			// ET1_ERXD3: PM3 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT9::PMR.B7 = 0;
				MPC::P97PFS.PSEL = mii;
				PORT9::PMR.B7 = ena;
				break;
			case ORDER::SECOND:
				PORTM::PMR.B3 = 0;
				MPC::PM3PFS.PSEL = mii;
				PORTM::PMR.B3 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.tx_en_) {
			// ET1_TX_EN: P60 (LFQFP100: ---) (LFQFP144: 117) (LFQFP176: 141)
			// ET1_TX_EN: PQ7 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT6::PMR.B0 = 0;
				MPC::P60PFS.PSEL = mii;
				PORT6::PMR.B0 = ena;
				break;
			case ORDER::SECOND:
				PORTQ::PMR.B7 = 0;
				MPC::PQ7PFS.PSEL = mii;
				PORTQ::PMR.B7 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.tx_er_) {
			// ET1_TX_ER: PG7 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: 111)
			// ET1_TX_ER: PQ3 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTG::PMR.B7 = 0;
				MPC::PG7PFS.PSEL = mii;
				PORTG::PMR.B7 = ena;
				break;
			case ORDER::SECOND:
				PORTQ::PMR.B3 = 0;
				MPC::PQ3PFS.PSEL = mii;
				PORTQ::PMR.B3 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.rx_er_) {
			// ET1_RX_ER: PD7 (LFQFP100:  79) (LFQFP144: 119) (LFQFP176: 143)
			// ET1_RX_ER: PG1 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: 144)
			// ET1_RX_ER: PN3 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTD::PMR.B7 = 0;
				MPC::PD7PFS.PSEL = mii;
				PORTD::PMR.B7 = ena;
				break;
			case ORDER::SECOND:
				PORTG::PMR.B1 = 0;
				MPC::PG1PFS.PSEL = mii;
				PORTG::PMR.B1 = ena;
				break;
			case ORDER::THIRD:
				PORTN::PMR.B3 = 0;
				MPC::PN3PFS.PSEL = mii;
				PORTN::PMR.B3 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.tx_clk_) {
			// ET1_TX_CLK: PG2 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: 123)
			// ET1_TX_CLK: PN2 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTG::PMR.B2 = 0;
				MPC::PG2PFS.PSEL = mii;
				PORTG::PMR.B2 = ena;
				break;
			case ORDER::SECOND:
				PORTN::PMR.B2 = 0;
				MPC::PN2PFS.PSEL = mii;
				PORTN::PMR.B2 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.rx_clk_) {
			// ET1_RX_CLK: PD6 (LFQFP100:  80) (LFQFP144: 120) (LFQFP176: 145)
			// ET1_RX_CLK: PG0 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: 146)
			// ET1_RX_CLK: PQ4 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTD::PMR.B6 = 0;
				MPC::PD6PFS.PSEL = mii;
				PORTD::PMR.B6 = ena;
				break;
			case ORDER::SECOND:
				PORTG::PMR.B0 = 0;
				MPC::PG0PFS.PSEL = mii;
				PORTG::PMR.B0 = ena;
				break;
			case ORDER::THIRD:
				PORTQ::PMR.B4 = 0;
				MPC::PQ4PFS.PSEL = mii;
				PORTQ::PMR.B4 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.col_) {
			// ET1_COL: P91 (LFQFP100: ---) (LFQFP144: 129) (LFQFP176: 161)
			// ET1_COL: PQ1 (LFQFP100: ---) (LFQFP144: ---) (LFQFP176: ---)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT9::PMR.B1 = 0;
				MPC::P91PFS.PSEL = mii;
				PORT9::PMR.B1 = ena;
				break;
			case ORDER::SECOND:
				PORTQ::PMR.B1 = 0;
				MPC::PQ1PFS.PSEL = mii;
				PORTQ::PMR.B1 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.wol_) {
			// ET1_WOL: P27 (LFQFP100:  21) (LFQFP144:  30) (LFQFP176:  36)
			// ET1_WOL: PD3 (LFQFP100:  83) (LFQFP144: 123) (LFQFP176: 150)
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT2::PMR.B7 = 0;
				MPC::P27PFS.PSEL = mii;
				PORT2::PMR.B7 = ena;
				break;
			case ORDER::SECOND:
				PORTD::PMR.B3 = 0;
				MPC::PD3PFS.PSEL = mii;
				PORTD::PMR.B3 = ena;
				break;
			default:
				++err;
				break;
			}

			ether1_mdc_mdio_(port.mdc_, port.mdio_, ena, err);

			MPC::PFENET.PHYMODE1 = 1;  // MII

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return err == 0;
		}
#endif

	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Ethernet ポートを切り替える RMII 型
			@param[in]	per		周辺機器タイプ
			@param[in]	port	ポート・マッピング・グループ
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn(peripheral per, const ether_rmii_t& port, bool ena = true) noexcept
		{
            bool ret = true;
            switch(per)
            {
			case peripheral::ETHERC0:
				ret = ether0_(port, ena);
				break;
#if defined(SIG_RX72N) || defined(SIG_RX72M)
			case peripheral::ETHERC1:
				ret = ether1_(port, ena);
				break;
#endif
			default:
				ret = false;
				break;
			}
			return ret;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Ethernet ポートを切り替える MII 型
			@param[in]	per		周辺機器タイプ
			@param[in]	port	ポート・マッピング・グループ
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn(peripheral per, const ether_mii_t& port, bool ena = true) noexcept
		{
            bool ret = true;
            switch(per)
            {
			case peripheral::ETHERC0:
				ret = ether0_(port, ena);
				break;
#if defined(SIG_RX72N) || defined(SIG_RX72M)
			case peripheral::ETHERC1:
				ret = ether1_(port, ena);
				break;
#endif
			default:
				ret = false;
				break;
			}
			return ret;
		}
    };
}
