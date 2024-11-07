#pragma once
//=========================================================================//
/*!	@file
	@brief	RX66N/RX72N/RX72M グループ・ポート・マッピング (QSPI)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#if defined(SIG_RX66N)
#include "RX66N/peripheral.hpp"
#include "RX66N/port.hpp"
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
		@brief  QSPI ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_qspi : public port_map_order {

		static bool qspi_clk_(bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b01'1011 : 0;
			switch(odr) {
			/// QSPCLK:
			///   P77
			///   PD5
			///   PM0
			///   PN4
			case ORDER::FIRST:
				PORT7::PMR.B7 = 0;
				MPC::P77PFS.PSEL = sel;
				PORT7::PMR.B7 = ena;
				break;
			case ORDER::SECOND:
				PORTD::PMR.B5 = 0;
				MPC::PD5PFS.PSEL = sel;
				PORTD::PMR.B5 = ena;
				break;
			case ORDER::THIRD:
				PORTM::PMR.B0 = 0;
				MPC::PM0PFS.PSEL = sel;
				PORTM::PMR.B0 = ena;
				break;
			case ORDER::FOURTH:
				PORTN::PMR.B4 = 0;
				MPC::PN4PFS.PSEL = sel;
				PORTN::PMR.B4 = ena;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}


		static bool qspi_ssl_(bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b01'1011 : 0;
			switch(odr) {
			/// QSSL:
			///   P76
			///   PD4
			///   PM1
			///   PN5
			case ORDER::FIRST:
				PORT7::PMR.B6 = 0;
				MPC::P76PFS.PSEL = sel;
				PORT7::PMR.B6 = ena;
				break;
			case ORDER::SECOND:
				PORTD::PMR.B4 = 0;
				MPC::PD4PFS.PSEL = sel;
				PORTD::PMR.B4 = ena;
				break;
			case ORDER::THIRD:
				PORTM::PMR.B1 = 0;
				MPC::PM1PFS.PSEL = sel;
				PORTM::PMR.B1 = ena;
				break;
			case ORDER::FOURTH:
				PORTN::PMR.B5 = 0;
				MPC::PN5PFS.PSEL = sel;
				PORTN::PMR.B5 = ena;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}


		static bool qspi_io0_(bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b01'1011 : 0;
			switch(odr) {
			/// QIO0:
			///   PC3
			///   PD6
			///   PJ3
			///   PM2
			case ORDER::FIRST:
				PORTC::PMR.B3 = 0;
				MPC::PC3PFS.PSEL = sel;
				PORTC::PMR.B3 = ena;
				break;
			case ORDER::SECOND:
				PORTD::PMR.B6 = 0;
				MPC::PD6PFS.PSEL = sel;
				PORTD::PMR.B6 = ena;
				break;
			case ORDER::THIRD:
				PORTJ::PMR.B3 = 0;
				MPC::PJ3PFS.PSEL = sel;
				PORTJ::PMR.B3 = ena;
				break;
			case ORDER::FOURTH:
				PORTM::PMR.B2 = 0;
				MPC::PM2PFS.PSEL = sel;
				PORTM::PMR.B2 = ena;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}


		static bool qspi_io1_(bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b01'1011 : 0;
			switch(odr) {
			/// QIO1:
			///   PC4
			///   PD7
			///   PJ5
			///   PM3
			case ORDER::FIRST:
				PORTC::PMR.B4 = 0;
				MPC::PC4PFS.PSEL = sel;
				PORTC::PMR.B4 = ena;
				break;
			case ORDER::SECOND:
				PORTD::PMR.B7 = 0;
				MPC::PD7PFS.PSEL = sel;
				PORTD::PMR.B7 = ena;
				break;
			case ORDER::THIRD:
				PORTJ::PMR.B5 = 0;
				MPC::PJ5PFS.PSEL = sel;
				PORTJ::PMR.B5 = ena;
				break;
			case ORDER::FOURTH:
				PORTM::PMR.B3 = 0;
				MPC::PM3PFS.PSEL = sel;
				PORTM::PMR.B3 = ena;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}


		static bool qspi_io2_(bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b01'1011 : 0;
			switch(odr) {
			/// QIO2:
			///   P00
			///   P80
			///   PD2
			///   PM4
			case ORDER::FIRST:
				PORT0::PMR.B0 = 0;
				MPC::P00PFS.PSEL = sel;
				PORT0::PMR.B0 = ena;
				break;
			case ORDER::SECOND:
				PORT8::PMR.B0 = 0;
				MPC::P80PFS.PSEL = sel;
				PORT8::PMR.B0 = ena;
				break;
			case ORDER::THIRD:
				PORTD::PMR.B2 = 0;
				MPC::PD2PFS.PSEL = sel;
				PORTD::PMR.B2 = ena;
				break;
			case ORDER::FOURTH:
				PORTM::PMR.B4 = 0;
				MPC::PM4PFS.PSEL = sel;
				PORTM::PMR.B4 = ena;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}


		static bool qspi_io3_(bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b01'1011 : 0;
			switch(odr) {
			/// QIO3:
			///   P01
			///   P81
			///   PD3
			///   PM5
			case ORDER::FIRST:
				PORT0::PMR.B1 = 0;
				MPC::P01PFS.PSEL = sel;
				PORT0::PMR.B1 = ena;
				break;
			case ORDER::SECOND:
				PORT8::PMR.B1 = 0;
				MPC::P81PFS.PSEL = sel;
				PORT8::PMR.B1 = ena;
				break;
			case ORDER::THIRD:
				PORTD::PMR.B3 = 0;
				MPC::PD3PFS.PSEL = sel;
				PORTD::PMR.B3 = ena;
				break;
			case ORDER::FOURTH:
				PORTM::PMR.B5 = 0;
				MPC::PM5PFS.PSEL = sel;
				PORTM::PMR.B5 = ena;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}

	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI、チャネル別ポート切り替え
			@param[in]	port	QSPI チャネル型
			@param[in]	ena		無効にする場合場合「false」
			@param[in]	odr		候補を選択する場合
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn(QSPI_PORT port, bool ena = true, ORDER odr = ORDER::FIRST) noexcept
		{
			if(odr == ORDER::BYPASS) return true;

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = true;
			switch(port) {
			case QSPI_PORT::CLK:
				ret = qspi_clk_(ena, odr);
				break;
			case QSPI_PORT::SSL:
				ret = qspi_ssl_(ena, odr);
				break;
			case QSPI_PORT::IO0:
				ret = qspi_io0_(ena, odr);
				break;
			case QSPI_PORT::IO1:
				ret = qspi_io1_(ena, odr);
				break;
			case QSPI_PORT::IO2:
				ret = qspi_io2_(ena, odr);
				break;
			case QSPI_PORT::IO3:
				ret = qspi_io3_(ena, odr);
				break;
			default:
				ret = false;
				break;
			}

			MPC::PWPR = MPC::PWPR.B0WI.b();

			return ret;
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI、チャネル・グループ切り替え
			@param[in]	group	チャネル・グループ
			@param[in]	ena		無効にする場合場合「false」
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn(const qspi_port_t& group, bool ena = true) noexcept
		{
			uint32_t erc = 0;
			erc += turn(QSPI_PORT::CLK, ena, group.clk);
			erc += turn(QSPI_PORT::SSL, ena, group.ssl);
			erc += turn(QSPI_PORT::IO0, ena, group.io0);
			erc += turn(QSPI_PORT::IO1, ena, group.io1);
			erc += turn(QSPI_PORT::IO2, ena, group.io2);
			erc += turn(QSPI_PORT::IO3, ena, group.io3);
			return erc == 6;
		}
	};
}
