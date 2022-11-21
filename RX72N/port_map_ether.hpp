#pragma once
//=====================================================================//
/*!	@file
	@brief	RX72N グループ・ポート・マッピング （Ethernet) 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX72N/peripheral.hpp"
#include "RX600/port.hpp"
#include "RX72N/mpc.hpp"
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
			uint8_t mii = ena ? 0b010001 : 0;

			switch(mdc) {
			// P72
			// PA4
			// PK0
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
			// P71
			// PA3
			// PL7
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


		static void ether1_mdc_mdio_(ORDER mdc, ORDER mdio, bool ena, uint8_t& err)
		{
			uint8_t mii = ena ? 0b010001 : 0;

			switch(mdc) {
			// P31
			// PD5
			// PN5
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
			// P30
			// PD4
			// PN4
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


		static bool ether0_(const ether_rmii_t& port, bool ena)
		{
			uint8_t err = 0;
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			uint8_t rmii = ena ? 0b010010 : 0;

			switch(port.ref50ck_) {
			// P76
			// PB2
			// PE5
			// PL3
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
			// P83
			// PB7
			// PM7
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
			// P81
			// PB5
			// PL4
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
			// P82
			// PB6
			// PL5
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
			// P75
			// PB1
			// PL0
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
			// P74
			// PB0
			// PL1
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
			// P80
			// PA0
			// PB4
			// PL6
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
			// P77
			// PB3
			// PL2
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


		static bool ether0_(const ether_mii_t& port, bool ena)
		{
			uint8_t err = 0;
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			uint8_t mii = ena ? 0b010001 : 0;

			switch(port.crs_) {
			// P83
			// PB7
			// PM7
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
			// PC2
			// PK2
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
			// P55
			// PA6
			// PJ3
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
			// P34
			// P54
			// PA5
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
			// P81
			// PB5
			// PL4
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
			// P82
			// PB6
			// PL5
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
			// PC5
			// PM4
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
			// PC6
			// PM5
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
			// P75
			// PB1
			// PL0
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
			// P74
			// PB0
			// PL1
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
			// PC1
			// PE4
			// PK4
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
			// PC0
			// PE3
			// PK5
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
			// P80
			// PA0
			// PB4
			// PL6
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
			// PC3
			// PK3
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
			// P77
			// PB3
			// PL2
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
			// PC4
			// PM6
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
			// P76
			// PB2
			// PE5
			// PL3
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
			// PC7
			// PK1
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
			// P73
			// PA1
			// PA7
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


		static bool ether1_(const ether_rmii_t& port, bool ena)
		{
			uint8_t err = 0;
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			uint8_t rmii = ena ? 0b010010 : 0;

			switch(port.ref50ck_) {
			// PD6
			// PG0
			// PQ4
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
			// P92
			// PQ0
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
			// P64
			// PG3
			// PQ5
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
			// P63
			// PG4
			// PQ6
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
			// P62
			// P94
			// PM0
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
			// P61
			// P95
			// PM1
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
			// P60
			// PQ7
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
			// PD7
			// PG1
			// PN3
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


		static bool ether1_(const ether_mii_t& port, bool ena)
		{
			return true;
		}

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
			case peripheral::ETHERC1:
				ret = ether1_(port, ena);
				break;
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
			case peripheral::ETHERC1:
				ret = ether1_(port, ena);
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}
    };
}
