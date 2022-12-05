#pragma once
//=====================================================================//
/*!	@file
	@brief	RX72N グループ・ポート・マッピング (QSPI)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX72N/peripheral.hpp"
#include "RX72N/port.hpp"
#include "RX72N/mpc.hpp"
#include "RX600/port_map_order.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  QSPI ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map_qspi : public port_map_order {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI ポート・チャネル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CHANNEL : uint8_t {
			CLK,		///< QSPCLK
			SSL,		///< QSSL
			IO0,		///< QMO/QIO0
			IO1,		///< GMI/QIO1
			IO2,		///< QIO2
			IO3,		///< QIO3
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI ポート・オーダー構造体
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct group_t {

			ORDER	clk;
			ORDER	ssl;
			ORDER	io0;
			ORDER	io1;
			ORDER	io2;
			ORDER	io3;

			group_t() noexcept :
				clk(ORDER::BYPASS),
				ssl(ORDER::BYPASS),
				io0(ORDER::BYPASS),
				io1(ORDER::BYPASS),
				io2(ORDER::BYPASS),
				io3(ORDER::BYPASS)
			{ }


			group_t(port_map_order::RENESAS renesas) noexcept
			{
				switch(renesas) {
				case port_map_order::RENESAS::RX72N_ENVISION_KIT:
					clk = ORDER::SECOND;	///< PD5
					ssl = ORDER::SECOND;	///< PD4
					io0 = ORDER::SECOND;	///< PD6
					io1 = ORDER::SECOND;	///< PD7
					io2 = ORDER::THIRD;		///< PD2
					io3 = ORDER::THIRD;		///< PD3
					break;
				default:
					break;
				}
			}
		};

	private:

		static bool qspi_clk_(bool ena, ORDER odr) noexcept
		{
			bool ret = true;
			uint8_t sel = ena ? 0b011011 : 0;
			switch(odr) {
			/// P77
			/// PD5
			/// PM0
			/// PN4
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
			uint8_t sel = ena ? 0b011011 : 0;
			switch(odr) {
			/// P76
			/// PD4
			/// PM1
			/// PN5
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
			uint8_t sel = ena ? 0b011011 : 0;
			switch(odr) {
			/// PC3
			/// PD6
			/// PJ3
			/// PM2
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
			uint8_t sel = ena ? 0b011011 : 0;
			switch(odr) {
			/// PC4
			/// PD7
			/// PJ5
			/// PM3
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
			uint8_t sel = ena ? 0b011011 : 0;
			switch(odr) {
			/// P00
			/// P80
			/// PD2
			/// PM4
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
			uint8_t sel = ena ? 0b011011 : 0;
			switch(odr) {
			/// P01
			/// P81
			/// PD3
			/// PM5
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
			@param[in]	per		周辺機器タイプ
			@param[in]	ch		QSPI チャネル型
			@param[in]	ena		無効にする場合場合「false」
			@param[in]	odr		候補を選択する場合
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn(peripheral per, CHANNEL ch, bool ena = true, ORDER odr = ORDER::FIRST) noexcept
		{
			if(odr == ORDER::BYPASS) return true;

			if(per != peripheral::QSPI) {
				return false;
			}

			MPC::PWPR.B0WI  = 0;	// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = true;
			switch(ch) {
			case CHANNEL::CLK:
				ret = qspi_clk_(ena, odr);
				break;
			case CHANNEL::SSL:
				ret = qspi_ssl_(ena, odr);
				break;
			case CHANNEL::IO0:
				ret = qspi_io0_(ena, odr);
				break;
			case CHANNEL::IO1:
				ret = qspi_io1_(ena, odr);
				break;
			case CHANNEL::IO2:
				ret = qspi_io2_(ena, odr);
				break;
			case CHANNEL::IO3:
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
			@brief  QSPI、チャネル別ポート切り替え
			@param[in]	group	チャネルオーダー
			@param[in]	ena		無効にする場合場合「false」
			@return 無効な周辺機器の場合「false」
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static bool turn(const group_t& group, bool ena) noexcept
		{
			if(!turn(peripheral::QSPI, CHANNEL::CLK, ena, group.clk)) {
				return false;
			}
			if(!turn(peripheral::QSPI, CHANNEL::SSL, ena, group.ssl)) {
				return false;
			}
			if(!turn(peripheral::QSPI, CHANNEL::IO0, ena, group.io0)) {
				return false;
			}
			if(!turn(peripheral::QSPI, CHANNEL::IO1, ena, group.io1)) {
				return false;
			}
			if(!turn(peripheral::QSPI, CHANNEL::IO2, ena, group.io2)) {
				return false;
			}
			if(!turn(peripheral::QSPI, CHANNEL::IO3, ena, group.io3)) {
				return false;
			}
			return false;
		}
	};
}
