#pragma once
//=========================================================================//
/*!	@file
	@brief	RX63N/RX64M/RX65N グループ・ポート・マッピング （Ethernet) 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#if defined(SIG_RX63N)
#include "RX63N/peripheral.hpp"
#include "RX63N/port.hpp"
#include "RX63N/mpc.hpp"
#elif defined(SIG_RX64M) || defined(SIG_RX71M)
#include "RX64M/peripheral.hpp"
#include "RX64M/port.hpp"
#include "RX64M/mpc.hpp"
#elif defined(SIG_RX65N)
#include "RX65x/peripheral.hpp"
#include "RX64M/port.hpp"
#include "RX65x/mpc.hpp"
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
			default:
				++err;
				break;
			}

			switch(mdio) {
			// ET0_MDIO: P71
			// ET0_MDIO: PA3
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
			default:
				++err;
				break;
			}
		}

#if defined(SIG_RX64M) || defined(SIG_RX71M)
		static void ether1_mdc_mdio_(ORDER mdc, ORDER mdio, bool ena, uint8_t& err)
		{
			uint8_t mii = ena ? 0b01'0001 : 0;
			switch(mdc) {
			// ET1_MDC: P31
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT3::PMR.B1 = 0;
				MPC::P31PFS.PSEL = mii;
				PORT3::PMR.B1 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(mdio) {
			// ET1_MDIO: P30
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT3::PMR.B0 = 0;
				MPC::P30PFS.PSEL = mii;
				PORT3::PMR.B0 = ena;
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
			default:
				++err;
				break;
			}

			switch(port.crs_dv_) {
			// RMII0_CRS_DV: P83
			// RMII0_CRS_DV: PB7
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
			default:
				++err;
				break;
			}

			switch(port.txd0_) {
			// RMII0_TXD0: P81
			// RMII0_TXD0: PB5
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
			default:
				++err;
				break;
			}

			switch(port.txd1_) {
			// RMII0_TXD1: P82
			// RMII0_TXD1: PB6
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
			default:
				++err;
				break;
			}

			switch(port.rxd0_) {
			// RMII0_RXD0: P75
			// RMII0_RXD0: PB1
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
			default:
				++err;
				break;
			}

			switch(port.rxd1_) {
			// RMII0_RXD1: P74
			// RMII0_RXD1: PB0
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
			default:
				++err;
				break;
			}

			switch(port.txd_en_) {
			// RMII0_TXD_EN: P80
			// RMII0_TXD_EN: PA0
			// RMII0_TXD_EN: PB4
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
			default:
				++err;
				break;
			}

			switch(port.rx_er_) {
			// RMII0_RX_ER: P77
			// RMII0_RX_ER: PB3
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
			default:
				++err;
				break;
			}

			ether0_mdc_mdio_(port.mdc_, port.mdio_, ena, err);

			MPC::PFENET.PHYMODE0 = 0;  // RMII

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return err == 0;
		}

#if defined(SIG_RX64M) || defined(SIG_RX71M)
		static bool ether1_(const ether_rmii_t& port, bool ena)
		{
			uint8_t err = 0;
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			uint8_t rmii = ena ? 0b01'0010 : 0;

			switch(port.ref50ck_) {
			// REF50CK1: PG0
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTG::PMR.B0 = 0;
				MPC::PG0PFS.PSEL = rmii;
				PORTG::PMR.B0 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.crs_dv_) {
			// RMII1_CRS_DV: P92
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT9::PMR.B2 = 0;
				MPC::P92PFS.PSEL = rmii;
				PORT9::PMR.B2 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.txd0_) {
			// RMII1_TXD0: PG3
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTG::PMR.B3 = 0;
				MPC::PG3PFS.PSEL = rmii;
				PORTG::PMR.B3 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.txd1_) {
			// RMII1_TXD1: PG4
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTG::PMR.B4 = 0;
				MPC::PG4PFS.PSEL = rmii;
				PORTG::PMR.B4 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.rxd0_) {
			// RMII1_RXD0: P94
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT9::PMR.B4 = 0;
				MPC::P94PFS.PSEL = rmii;
				PORT9::PMR.B4 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.rxd1_) {
			// RMII1_RXD1: P95
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT9::PMR.B5 = 0;
				MPC::P95PFS.PSEL = rmii;
				PORT9::PMR.B5 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.txd_en_) {
			// RMII1_TXD_EN: P60
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT6::PMR.B0 = 0;
				MPC::P60PFS.PSEL = rmii;
				PORT6::PMR.B0 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.rx_er_) {
			// RMII1_RX_ER: PG1
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTG::PMR.B1 = 0;
				MPC::PG1PFS.PSEL = rmii;
				PORTG::PMR.B1 = ena;
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
			// ET0_CRS: P83
			// ET0_CRS: PB7
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
			default:
				++err;
				break;
			}

			switch(port.rx_dv_) {
			// ET0_RX_DV: PC2
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTC::PMR.B2 = 0;
				MPC::PC2PFS.PSEL = mii;
				PORTC::PMR.B2 = ena;
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
#if defined(SIG_RX63N)
#else
			case ORDER::THIRD:
				PORTJ::PMR.B3 = 0;
				MPC::PJ3PFS.PSEL = mii;
				PORTJ::PMR.B3 = ena;
				break;
#endif
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
#if defined(SIG_RX63N)
			case ORDER::FIRST:
				PORT5::PMR.B4 = 0;
				MPC::P54PFS.PSEL = mii;
				PORT5::PMR.B4 = ena;
				break;
			case ORDER::SECOND:
				PORTA::PMR.B5 = 0;
				MPC::PA5PFS.PSEL = mii;
				PORTA::PMR.B5 = ena;
				break;
#else
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
#endif
			default:
				++err;
				break;
			}

			switch(port.etxd0_) {
			// ET0_ETXD0: P81
			// ET0_ETXD0: PB5
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
			default:
				++err;
				break;
			}

			switch(port.etxd1_) {
			// ET0_ETXD1: P82
			// ET0_ETXD1: PB6
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
			default:
				++err;
				break;
			}

			switch(port.etxd2_) {
			// ET0_ETXD2: PC5
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTC::PMR.B5 = 0;
				MPC::PC5PFS.PSEL = mii;
				PORTC::PMR.B5 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.etxd3_) {
			// ET0_ETXD3: PC6
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTC::PMR.B6 = 0;
				MPC::PC6PFS.PSEL = mii;
				PORTC::PMR.B6 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.erxd0_) {
			// ET0_ERXD0: P75
			// ET0_ERXD0: PB1
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
			default:
				++err;
				break;
			}

			switch(port.erxd1_) {
			// ET0_ERXD1: P74
			// ET0_ERXD1: PB0
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
			default:
				++err;
				break;
			}

			switch(port.erxd2_) {
			// ET0_ERXD2: PC1
			// ET0_ERXD2: PE4
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
			default:
				++err;
				break;
			}

			switch(port.erxd3_) {
			// ET0_ERXD3: PC0
			// ET0_ERXD3: PE3
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
			default:
				++err;
				break;
			}

			switch(port.tx_en_) {
			// ET0_TX_EN: P80
			// ET0_TX_EN: PA0
			// ET0_TX_EN: PB4
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
			default:
				++err;
				break;
			}

			switch(port.tx_er_) {
			// ET0_TX_ER: PC3
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTC::PMR.B3 = 0;
				MPC::PC3PFS.PSEL = mii;
				PORTC::PMR.B3 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.rx_er_) {
			// ET0_RX_ER: P77
			// ET0_RX_ER: PB3
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
			default:
				++err;
				break;
			}

			switch(port.tx_clk_) {
			// ET0_TX_CLK: PC4
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTC::PMR.B4 = 0;
				MPC::PC4PFS.PSEL = mii;
				PORTC::PMR.B4 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.rx_clk_) {
			// ET0_RX_CLK: P76
			// ET0_RX_CLK: PB2
			// ET0_RX_CLK: PE5
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
			default:
				++err;
				break;
			}

			switch(port.col_) {
			// ET0_COL: PC7
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTC::PMR.B7 = 0;
				MPC::PC7PFS.PSEL = mii;
				PORTC::PMR.B7 = ena;
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

			MPC::PFENET.PHYMODE0 = 1;  // MII

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return err == 0;
		}

#if defined(SIG_RX64M) || defined(SIG_RX71M)
		static bool ether1_(const ether_mii_t& port, bool ena)
		{
			uint8_t err = 0;
			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			uint8_t mii = ena ? 0b01'0001 : 0;

			switch(port.crs_) {
			// ET1_CRS: P92
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT9::PMR.B2 = 0;
				MPC::P92PFS.PSEL = mii;
				PORT9::PMR.B2 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.rx_dv_) {
			// ET1_RX_DV: P90
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT9::PMR.B0 = 0;
				MPC::P90PFS.PSEL = mii;
				PORT9::PMR.B0 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.exout_) {
			// ET1_EX_OUT: P26
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT2::PMR.B6 = 0;
				MPC::P26PFS.PSEL = mii;
				PORT2::PMR.B6 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.linksta_) {
			// ET1_LINKSTA: P93
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT9::PMR.B3 = 0;
				MPC::P93PFS.PSEL = mii;
				PORT9::PMR.B3 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.etxd0_) {
			// ET1_ETXD0: PG3
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTG::PMR.B3 = 0;
				MPC::PG3PFS.PSEL = mii;
				PORTG::PMR.B3 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.etxd1_) {
			// ET1_ETXD1: PG4
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTG::PMR.B4 = 0;
				MPC::PG4PFS.PSEL = mii;
				PORTG::PMR.B4 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.etxd2_) {
			// ET1_ETXD2: PG5
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTG::PMR.B5 = 0;
				MPC::PG5PFS.PSEL = mii;
				PORTG::PMR.B5 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.etxd3_) {
			// ET1_ETXD3: PG6
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTG::PMR.B6 = 0;
				MPC::PG6PFS.PSEL = mii;
				PORTG::PMR.B6 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.erxd0_) {
			// ET1_ERXD0: P94
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT9::PMR.B4 = 0;
				MPC::P94PFS.PSEL = mii;
				PORT9::PMR.B4 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.erxd1_) {
			// ET1_ERXD1: P95
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT9::PMR.B5 = 0;
				MPC::P95PFS.PSEL = mii;
				PORT9::PMR.B5 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.erxd2_) {
			// ET1_ERXD2: P96
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT9::PMR.B6 = 0;
				MPC::P96PFS.PSEL = mii;
				PORT9::PMR.B6 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.erxd3_) {
			// ET1_ERXD3: P97
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT9::PMR.B7 = 0;
				MPC::P97PFS.PSEL = mii;
				PORT9::PMR.B7 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.tx_en_) {
			// ET1_TX_EN: P60
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT6::PMR.B0 = 0;
				MPC::P60PFS.PSEL = mii;
				PORT6::PMR.B0 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.tx_er_) {
			// ET1_TX_ER: PG7
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTG::PMR.B7 = 0;
				MPC::PG7PFS.PSEL = mii;
				PORTG::PMR.B7 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.rx_er_) {
			// ET1_RX_ER: PG1
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTG::PMR.B1 = 0;
				MPC::PG1PFS.PSEL = mii;
				PORTG::PMR.B1 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.tx_clk_) {
			// ET1_TX_CLK: PG2
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTG::PMR.B2 = 0;
				MPC::PG2PFS.PSEL = mii;
				PORTG::PMR.B2 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.rx_clk_) {
			// ET1_RX_CLK: PG0
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORTG::PMR.B0 = 0;
				MPC::PG0PFS.PSEL = mii;
				PORTG::PMR.B0 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.col_) {
			// ET1_COL: P91
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT9::PMR.B1 = 0;
				MPC::P91PFS.PSEL = mii;
				PORT9::PMR.B1 = ena;
				break;
			default:
				++err;
				break;
			}

			switch(port.wol_) {
			// ET1_WOL: P27
			case ORDER::BYPASS:
				break;
			case ORDER::FIRST:
				PORT2::PMR.B7 = 0;
				MPC::P27PFS.PSEL = mii;
				PORT2::PMR.B7 = ena;
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
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Ethernet ポートを切り替える RMII 型
			@param[in]	per		周辺機器タイプ
			@param[in]	port	ポート・マッピング・グループ
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn(peripheral per, const ether_rmii_t& port, bool ena = true) noexcept
		{
            bool ret = true;
            switch(per)
            {
			case peripheral::ETHERC0:
				ret = ether0_(port, ena);
				break;
#if defined(SIG_RX64M) || defined(SIG_RX71M)
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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Ethernet ポートを切り替える MII 型
			@param[in]	per		周辺機器タイプ
			@param[in]	port	ポート・マッピング・グループ
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn(peripheral per, const ether_mii_t& port, bool ena = true) noexcept
		{
            bool ret = true;
            switch(per)
            {
			case peripheral::ETHERC0:
				ret = ether0_(port, ena);
				break;
#if defined(SIG_RX64M) || defined(SIG_RX71M)
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
