#pragma once
//=========================================================================//
/*!	@file
	@brief	RX66N/RX72N/RX72M グループ・ポート・マッピング （Ethernet) 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021, 2024 Kunihito Hiramatsu @n
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
			// ET0_MDC: P72
			// ET0_MDC: PA4
			// ET0_MDC: PK0
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
			// ET0_MDIO: P71
			// ET0_MDIO: PA3
			// ET0_MDIO: PL7
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

#if defined(SIG_RX66N)
#else
		static void ether1_mdc_mdio_(ORDER mdc, ORDER mdio, bool ena, uint8_t& err)
		{
			uint8_t mii = ena ? 0b01'0001 : 0;
			switch(mdc) {
			// ET1_MDC: P31
			// ET1_MDC: PD5
			// ET1_MDC: PN5
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
			// ET1_MDIO: P30
			// ET1_MDIO: PD4
			// ET1_MDIO: PN4
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
			// REF50CK0: P76
			// REF50CK0: PB2
			// REF50CK0: PE5
			// REF50CK0: PL3
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
			// RMII0_CRS_DV: P83
			// RMII0_CRS_DV: PB7
			// RMII0_CRS_DV: PM7
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
			// RMII0_TXD0: P81
			// RMII0_TXD0: PB5
			// RMII0_TXD0: PL4
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
			// RMII0_TXD1: P82
			// RMII0_TXD1: PB6
			// RMII0_TXD1: PL5
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
			// RMII0_RXD0: P75
			// RMII0_RXD0: PB1
			// RMII0_RXD0: PL0
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
			// RMII0_RXD1: P74
			// RMII0_RXD1: PB0
			// RMII0_RXD1: PL1
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
			// RMII0_TXD_EN: P80
			// RMII0_TXD_EN: PA0
			// RMII0_TXD_EN: PB4
			// RMII0_TXD_EN: PL6
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
			// RMII0_RX_ER: P77
			// RMII0_RX_ER: PB3
			// RMII0_RX_ER: PL2
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

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return err == 0;
		}

#if defined(SIG_RX66N)
#else
		static bool ether1_(const ether_rmii_t& port, bool ena)
		{
			uint8_t err = 0;
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			uint8_t rmii = ena ? 0b01'0010 : 0;

			switch(port.ref50ck_) {
			// REF50CK1: PD6
			// REF50CK1: PG0
			// REF50CK1: PQ4
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
			// RMII1_CRS_DV: P92
			// RMII1_CRS_DV: PQ0
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
			// RMII1_TXD0: P64
			// RMII1_TXD0: PG3
			// RMII1_TXD0: PQ5
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
			// RMII1_TXD1: P63
			// RMII1_TXD1: PG4
			// RMII1_TXD1: PQ6
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
			// RMII1_RXD0: P62
			// RMII1_RXD0: P94
			// RMII1_RXD0: PM0
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
			// RMII1_RXD1: P61
			// RMII1_RXD1: P95
			// RMII1_RXD1: PM1
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
			// RMII1_TXD_EN: P60
			// RMII1_TXD_EN: PQ7
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
			// RMII1_RX_ER: PD7
			// RMII1_RX_ER: PG1
			// RMII1_RX_ER: PN3
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
			// ET0_CRS: P83
			// ET0_CRS: PB7
			// ET0_CRS: PM7
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
			// ET0_RX_DV: PC2
			// ET0_RX_DV: PK2
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
			// ET0_EX_OUT: P55
			// ET0_EX_OUT: PA6
			// ET0_EX_OUT: PJ3
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
			// ET0_LINKSTA: P34
			// ET0_LINKSTA: P54
			// ET0_LINKSTA: PA5
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
			// ET0_ETXD0: P81
			// ET0_ETXD0: PB5
			// ET0_ETXD0: PL4
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
			// ET0_ETXD1: P82
			// ET0_ETXD1: PB6
			// ET0_ETXD1: PL5
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
			// ET0_ETXD2: PC5
			// ET0_ETXD2: PM4
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
			// ET0_ETXD3: PC6
			// ET0_ETXD3: PM5
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
			// ET0_ERXD0: P75
			// ET0_ERXD0: PB1
			// ET0_ERXD0: PL0
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
			// ET0_ERXD1: P74
			// ET0_ERXD1: PB0
			// ET0_ERXD1: PL1
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
			// ET0_ERXD2: PC1
			// ET0_ERXD2: PE4
			// ET0_ERXD2: PK4
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
			// ET0_ERXD3: PC0
			// ET0_ERXD3: PE3
			// ET0_ERXD3: PK5
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
			// ET0_TX_EN: P80
			// ET0_TX_EN: PA0
			// ET0_TX_EN: PB4
			// ET0_TX_EN: PL6
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
			// ET0_TX_ER: PC3
			// ET0_TX_ER: PK3
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
			// ET0_RX_ER: P77
			// ET0_RX_ER: PB3
			// ET0_RX_ER: PL2
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
			// ET0_TX_CLK: PC4
			// ET0_TX_CLK: PM6
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
			// ET0_RX_CLK: P76
			// ET0_RX_CLK: PB2
			// ET0_RX_CLK: PE5
			// ET0_RX_CLK: PL3
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
			// ET0_COL: PC7
			// ET0_COL: PK1
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
			// ET0_WOL: P73
			// ET0_WOL: PA1
			// ET0_WOL: PA7
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

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return err == 0;
		}

#if defined(SIG_RX66N)
#else
		static bool ether1_(const ether_mii_t& port, bool ena)
		{
			uint8_t err = 0;
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			uint8_t mii = ena ? 0b01'0001 : 0;

			switch(port.crs_) {
			// ET1_CRS: P92
			// ET1_CRS: PQ0
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
			// ET1_RX_DV: P90
			// ET1_RX_DV: PQ2
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
			// ET1_EX_OUT: P26
			// ET1_EX_OUT: PD2
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
			// ET1_LINKSTA: P84
			// ET1_LINKSTA: P93
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
			// ET1_ETXD0: P64
			// ET1_ETXD0: PG3
			// ET1_ETXD0: PQ5
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
			// ET1_ETXD1: P63
			// ET1_ETXD1: PG4
			// ET1_ETXD1: PQ6
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
			// ET1_ETXD2: PG5
			// ET1_ETXD2: PN0
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
			// ET1_ETXD3: PG6
			// ET1_ETXD3: PN1
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
			// ET1_ERXD0: P62
			// ET1_ERXD0: P94
			// ET1_ERXD0: PM0
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
			// ET1_ERXD1: P61
			// ET1_ERXD1: P95
			// ET1_ERXD1: PM1
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
			// ET1_ERXD2: P96
			// ET1_ERXD2: PM2
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
			// ET1_ERXD3: P97
			// ET1_ERXD3: PM3
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
			// ET1_TX_EN: P60
			// ET1_TX_EN: PQ7
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
			// ET1_TX_ER: PG7
			// ET1_TX_ER: PQ3
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
			// ET1_RX_ER: PD7
			// ET1_RX_ER: PG1
			// ET1_RX_ER: PN3
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
			// ET1_TX_CLK: PG2
			// ET1_TX_CLK: PN2
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
			// ET1_RX_CLK: PD6
			// ET1_RX_CLK: PG0
			// ET1_RX_CLK: PQ4
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
			// ET1_COL: P91
			// ET1_COL: PQ1
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
			// ET1_WOL: P27
			// ET1_WOL: PD3
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
#if defined(SIG_RX66N)
#else
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
#if defined(SIG_RX66N)
#else
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
