#pragma once
//=========================================================================//
/*!	@file
	@brief	RX671 グループ・ポート・マッピング (QSPIX)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX671/peripheral.hpp"
#include "RX671/port.hpp"
#include "RX671/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  QSPIX ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_qspix : public port_map_order {

		static bool qspix_clk_(bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b01'1011 : 0;
			switch(odr) {  // QSPCLK:
			// P77 (LFQFP100: ---) (LFQFP144:  68)
			// PD5 (LFQFP100:  81) (LFQFP144: 121)
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
			default:
				ret = false;
				break;
			}
			return ret;
		}

		static bool qspix_ssl_(bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b01'1011 : 0;
			switch(odr) {  // QSSL:
			// P76 (LFQFP100: ---) (LFQFP144:  69)
			// PD4 (LFQFP100:  82) (LFQFP144: 122)
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
			default:
				ret = false;
				break;
			}
			return ret;
		}

		static bool qspix_io0_(bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b01'1011 : 0;
			switch(odr) {  // QIO0:
			// PC3 (LFQFP100:  49) (LFQFP144:  67)
			// PD6 (LFQFP100:  80) (LFQFP144: 120)
			// PE6 (LFQFP100:  72) (LFQFP144: 102)
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
				PORTE::PMR.B6 = 0;
				MPC::PE6PFS.PSEL = sel;
				PORTE::PMR.B6 = ena;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}

		static bool qspix_io1_(bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b01'1011 : 0;
			switch(odr) {  // QIO1:
			// PC4 (LFQFP100:  48) (LFQFP144:  66)
			// PD7 (LFQFP100:  79) (LFQFP144: 119)
			// PE7 (LFQFP100:  71) (LFQFP144: 101)
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
				PORTE::PMR.B7 = 0;
				MPC::PE7PFS.PSEL = sel;
				PORTE::PMR.B7 = ena;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}

		static bool qspix_io2_(bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b01'1011 : 0;
			switch(odr) {  // QIO2:
			// P80 (LFQFP100: ---) (LFQFP144:  65)
			// PD2 (LFQFP100:  84) (LFQFP144: 124)
			case ORDER::FIRST:
				PORT8::PMR.B0 = 0;
				MPC::P80PFS.PSEL = sel;
				PORT8::PMR.B0 = ena;
				break;
			case ORDER::SECOND:
				PORTD::PMR.B2 = 0;
				MPC::PD2PFS.PSEL = sel;
				PORTD::PMR.B2 = ena;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}

		static bool qspix_io3_(bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b01'1011 : 0;
			switch(odr) {  // QIO3:
			// P81 (LFQFP100: ---) (LFQFP144:  64)
			// PD3 (LFQFP100:  83) (LFQFP144: 123)
			case ORDER::FIRST:
				PORT8::PMR.B1 = 0;
				MPC::P81PFS.PSEL = sel;
				PORT8::PMR.B1 = ena;
				break;
			case ORDER::SECOND:
				PORTD::PMR.B3 = 0;
				MPC::PD3PFS.PSEL = sel;
				PORTD::PMR.B3 = ena;
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
			@brief  QSPIX、チャネル別ポート切り替え
			@param[in]	port	QSPIX チャネル型
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

			bool ret = false;
			switch(port) {
			case QSPI_PORT::CLK:
				ret = qspix_clk_(ena, odr);
				break;
			case QSPI_PORT::SSL:
				ret = qspix_ssl_(ena, odr);
				break;
			case QSPI_PORT::IO0:
				ret = qspix_io0_(ena, odr);
				break;
			case QSPI_PORT::IO1:
				ret = qspix_io1_(ena, odr);
				break;
			case QSPI_PORT::IO2:
				ret = qspix_io2_(ena, odr);
				break;
			case QSPI_PORT::IO3:
				ret = qspix_io3_(ena, odr);
				break;
			default:
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
