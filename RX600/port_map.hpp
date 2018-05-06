#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・ポート・マッピング @n
			・ペリフェラル型に従って、ポートの設定をグループ化 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX600/port.hpp"
#include "RX600/mpc.hpp"
#include "RX600/peripheral.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・マッピング・ユーティリティー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class port_map {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ポート・マッピング・オプション型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class option : uint8_t {
			FIRST,		///< 第１候補
			SECOND,		///< 第２候補
			THIRD,		///< 第３候補
			FORCE,		///< 第４候補
		};

	private:

		static bool sub_1st_(peripheral t, bool enable)
		{
			bool ret = true;
			switch(t) {
			// ※シリアルポートの MPC 設定では、PDR を制御する必要は無いが、
			// 出力ポートのインピーダンス制御の一環として入れてある。
			case peripheral::SCI0:
				{
					uint8_t sel = enable ? 0b001010 : 0;
					MPC::P20PFS.PSEL = sel;  // TXD0 (P20 LQFP176: 45)
					MPC::P21PFS.PSEL = sel;  // RXD0 (P21 LQFP176: 44)
					PORT2::PMR.B0 = enable;
					PORT2::PMR.B1 = enable;
				}
				break;
			case peripheral::SCI1:
				{
					uint8_t sel = enable ? 0b001010 : 0;
					MPC::PF0PFS.PSEL = sel;  // TXD1 (PF0 LQFP176: 35)
					MPC::PF2PFS.PSEL = sel;  // RXD1 (PF2 LQFP176: 31)
					PORTF::PMR.B0 = enable;
					PORTF::PMR.B2 = enable;
				}
				break;
			case peripheral::SCI2:
				{
					uint8_t sel = enable ? 0b001010 : 0;
					MPC::P13PFS.PSEL = sel;  // TXD2 (P13 LQFP176: 52)
					MPC::P12PFS.PSEL = sel;  // RXD2 (P12 LQFP176: 53)
					PORT1::PMR.B3 = enable;
					PORT1::PMR.B2 = enable;
				}
				break;
			case peripheral::SCI3:
				{
					uint8_t sel = enable ? 0b001010 : 0;
					MPC::P23PFS.PSEL = sel;  // TXD3 (P23 LQFP176: 42)
					MPC::P25PFS.PSEL = sel;  // RXD3 (P25 LQFP176: 38)
					PORT2::PMR.B3 = enable;
					PORT2::PMR.B5 = enable;
				}
				break;
			case peripheral::SCI4:
				{
					uint8_t sel = enable ? 0b001010 : 0;
					MPC::PB1PFS.PSEL = sel;  // TXD4 (PB1 LQFP176: 100)
					MPC::PB0PFS.PSEL = sel;  // RXD4 (PB0 LQFP176: 104)
					PORTB::PMR.B1 = enable;
					PORTB::PMR.B0 = enable;
				}
				break;
			case peripheral::SCI5:
				{
					uint8_t sel = enable ? 0b001010 : 0;
					MPC::PA4PFS.PSEL = sel;  // TXD5 (PA4 LQFP176: 109)
					MPC::PA3PFS.PSEL = sel;  // RXD5 (PA3 LQFP176: 110)
					PORTA::PMR.B4 = enable;
					PORTA::PMR.B3 = enable;
				}
				break;
			case peripheral::SCI6:
				{
					uint8_t sel = enable ? 0b001010 : 0;
					MPC::P00PFS.PSEL = sel;  // TXD6 (P00 LQFP176: 8)
					MPC::P01PFS.PSEL = sel;  // RXD6 (P01 LQFP176: 7)
					PORT0::PMR.B0 = enable;
					PORT0::PMR.B1 = enable;
				}
				break;
			case peripheral::SCI7:
				{
					uint8_t sel = enable ? 0b001010 : 0;
					MPC::P90PFS.PSEL = sel;  // TXD7 (P90 LQFP176: 163)
					MPC::P92PFS.PSEL = sel;  // RXD7 (P92 LQFP176: 160)
					PORT9::PMR.B0 = enable;
					PORT9::PMR.B2 = enable;
				}
				break;
#if defined(SIG_RX64M) || defined(SIG_RX71M)
			case peripheral::SCIF8:
#elif defined(SIG_RX65N)
			case peripheral::SCI8:
#endif
				{
					uint8_t sel = enable ? 0b001010 : 0;
					MPC::PC7PFS.PSEL = sel;  // TXDF8 (PC7 LQFP176: 76)
					MPC::PC6PFS.PSEL = sel;  // RXDF8 (PC6 LQFP176: 77)
					PORTC::PMR.B7 = enable;
					PORTC::PMR.B6 = enable;
				}
				break;
#if defined(SIG_RX64M) || defined(SIG_RX71M)
			case peripheral::SCIF9:
#elif defined(SIG_RX65N)
			case peripheral::SCI9:
#endif
				{
					uint8_t sel = enable ? 0b001010 : 0;
					MPC::PB7PFS.PSEL = sel;  // TXDF9 (PB7 LQFP176: 94)
					MPC::PB6PFS.PSEL = sel;  // RXDF9 (PB6 LQFP176: 95)
					PORTB::PMR.B7 = enable;
					PORTB::PMR.B6 = enable;
				}
				break;
#if defined(SIG_RX64M) || defined(SIG_RX71M)
			case peripheral::SCIF10:
#elif defined(SIG_RX65N)
			case peripheral::SCI10:
#endif
				{
					uint8_t sel = enable ? 0b001010 : 0;
					MPC::P87PFS.PSEL = sel;  // TXDF10 (P86 LQFP176: 47)
					MPC::P86PFS.PSEL = sel;  // RXDF10 (P87 LQFP176: 49)
					PORT8::PMR.B7 = enable;
					PORT8::PMR.B6 = enable;
				}
				break;
#if defined(SIG_RX64M) || defined(SIG_RX71M)
			case peripheral::SCIF11:
#elif defined(SIG_RX65N)
			case peripheral::SCI11:
#endif
				{
					uint8_t sel = enable ? 0b001010 : 0;
					MPC::P77PFS.PSEL = sel;  // TXDF11 (P77 LQFP176: 84)
					MPC::P76PFS.PSEL = sel;  // RXDF11 (P76 LQFP176: 85)
					PORT7::PMR.B7 = enable;
					PORT7::PMR.B6 = enable;
				}
				break;

			case peripheral::SCI12:
				{
					uint8_t sel = enable ? 0b001100 : 0;
					MPC::PE2PFS.PSEL = sel;  // RXD12 (PE2 LQFP176: 133)
					MPC::PE1PFS.PSEL = sel;  // TXD12 (PE1 LQFP176: 134)
					PORTE::PMR.B2 = enable;
					PORTE::PMR.B1 = enable;
				}
				break;

			case peripheral::RSPI:
				{
					uint8_t sel = enable ? 0b001101 : 0;
					MPC::PC7PFS.PSEL = sel;  // MISOA-A  (PC7 LQFP176: 76)
					MPC::PC6PFS.PSEL = sel;  // MOSIA-A  (PC6 LQFP176: 77)
					MPC::PC5PFS.PSEL = sel;  // RSPCKA-A (PC5 LQFP176: 78)
					PORTC::PMR.B7 = enable;
					PORTC::PMR.B6 = enable;
					PORTC::PMR.B5 = enable;
				}
				break;

			case peripheral::QSPI:
				{
					uint8_t sel = enable ? 0b011011 : 0;
					MPC::P81PFS.PSEL = sel;  // QIO3-A   (P81 LQFP176: 80)
					MPC::P80PFS.PSEL = sel;  // QIO2-A   (P80 LQFP176: 81)
					MPC::PC4PFS.PSEL = sel;  // QIO1-A   (PC4 LQFP176: 82)
					MPC::PC3PFS.PSEL = sel;  // QIO0-A   (PC3 LQFP176: 83)
					MPC::P77PFS.PSEL = sel;  // QSPCLK-A (P77 LQFP176: 84)
					PORT8::PMR.B1 = enable;
					PORT8::PMR.B0 = enable;
					PORTC::PMR.B4 = enable;
					PORTC::PMR.B3 = enable;
					PORT7::PMR.B7 = enable;
				}
				break;

			case peripheral::SDHI:
				{
					uint8_t sel = enable ? 0b011010 : 0;
					MPC::P80PFS.PSEL = sel;  // SDHI_WP (81)
					PORT8::PMR.B0 = enable;
//					PORT8::PCR.B0 = 1;
					MPC::P81PFS.PSEL = sel;  // SDHI_CD (80)
					PORT8::PMR.B1 = enable;
//					PORT8::PCR.B1 = 1;
					MPC::PC2PFS.PSEL = sel;  // SDHI_D3 (86)
					PORTC::PMR.B2 = enable;
//					PORTC::PCR.B2 = 1;
					MPC::PC3PFS.PSEL = sel;  // SDHI_D0 (83)
					PORTC::PMR.B3 = enable;
//					PORTC::PCR.B3 = 1;
					MPC::PC4PFS.PSEL = sel;  // SDHI_D1 (82)
					PORTC::PMR.B4 = enable;
//					PORTC::PCR.B4 = 1;
   					MPC::P75PFS.PSEL = sel;  // SDHI_D2 (87)
					PORT7::PMR.B5 = enable;
//					PORT7::PCR.B5 = 1;
					MPC::P76PFS.PSEL = sel;  // SDHI_CMD (85)
					PORT7::PMR.B6 = enable;
//					PORT7::PCR.B6 = 1;
					MPC::P77PFS.PSEL = sel;  // SDHI_CLK (84)
					PORT7::PMR.B7 = enable;
//					PORT7::PCR.B7 = 1;
				}
				break;

			case peripheral::ETHERC0:  // only RMII mode, not use link status interrupt
				{
					uint8_t  mii = enable ? 0b010001 : 0;
					uint8_t rmii = enable ? 0b010010 : 0;
//					MPC::P34PFS.PSEL = mii;   // ET0_LINKSTA
//					PORT3::PMR.B4 = enable;
					MPC::P71PFS.PSEL = mii;   // ET0_MDIO
					MPC::P72PFS.PSEL = mii;   // ET0_MDC
//					MPC::P73PFS.PSEL = mii;   // ET0_WOL
					MPC::P74PFS.PSEL = rmii;  // RMII0_RXD1
					MPC::P75PFS.PSEL = rmii;  // RMII0_RXD0
					MPC::P76PFS.PSEL = rmii;  // REF50CK0
					MPC::P77PFS.PSEL = rmii;  // RMII0_RX_ER
					PORT7::PMR.B1 = enable;
					PORT7::PMR.B2 = enable;
//					PORT7::PMR.B3 = enable;
					PORT7::PMR.B4 = enable;
					PORT7::PMR.B5 = enable;
					PORT7::PMR.B6 = enable;
					PORT7::PMR.B7 = enable;
					MPC::P80PFS.PSEL = rmii;  // RMII0_TXD_EN
					MPC::P81PFS.PSEL = rmii;  // RMII0_TXD0
					MPC::P82PFS.PSEL = rmii;  // RMII0_TXD1
					MPC::P83PFS.PSEL = rmii;  // RMII0_CRS_DV
					PORT8::PMR.B0 = enable;
					PORT8::PMR.B1 = enable;
					PORT8::PMR.B2 = enable;
					PORT8::PMR.B3 = enable;
					MPC::PFENET.PHYMODE0 = 0;  // for RMII mode chanel 0
				}
				break;

			case peripheral::ETHERCA:  // only RMII mode, not use link status interrupt
				{
					uint8_t  mii = enable ? 0b010001 : 0;
					uint8_t rmii = enable ? 0b010010 : 0;
///					MPC::P73PFS.PSEL = mii;   // ET0_WOL  (144LQFP: 77)
					MPC::P72PFS.PSEL = mii;   // ET0_MDC  (144LQFP: 85)
					MPC::P71PFS.PSEL = mii;   // ET0_MDIO (144LQFP: 86)
///					PORT7::PMR.B3 = enable;
					PORT7::PMR.B2 = enable;
					PORT7::PMR.B1 = enable;
					MPC::PB7PFS.PSEL = rmii;  // RMII0_CRS_DV (144LQFP: 78)
					MPC::PB6PFS.PSEL = rmii;  // RMII0_TXD1   (144LQFP: 79)
					MPC::PB5PFS.PSEL = rmii;  // RMII0_TXD0   (144LQFP: 80)
					MPC::PB4PFS.PSEL = rmii;  // RMII0_TXD_EN (144LQFP: 81)
					MPC::PB3PFS.PSEL = rmii;  // RMII0_RX_ER  (144LQFP: 82)
					MPC::PB2PFS.PSEL = rmii;  // REF50CK0     (144LQFP: 83)
					MPC::PB1PFS.PSEL = rmii;  // RMII0_RXD0   (144LQFP: 84)
					MPC::PB0PFS.PSEL = rmii;  // RMII0_RXD1   (144LQFP: 87)
					PORTB::PMR.B7 = enable;
					PORTB::PMR.B6 = enable;
					PORTB::PMR.B5 = enable;
					PORTB::PMR.B4 = enable;
					PORTB::PMR.B3 = enable;
					PORTB::PMR.B2 = enable;
					PORTB::PMR.B1 = enable;
					PORTB::PMR.B0 = enable;
					MPC::PFENET.PHYMODE0 = 0;  // for RMII mode chanel 0
				}
				break;

			case peripheral::IRQ0:
				MPC::PD0PFS.ISEL = enable;  // PD0
				PORTD::PMR.B0 = 0;
				break;
			case peripheral::IRQ1:
				MPC::PD1PFS.ISEL = enable;  // PD1
				PORTD::PMR.B1 = 0;
				break;
			case peripheral::IRQ2:
				MPC::PD2PFS.ISEL = enable;  // PD2
				PORTD::PMR.B2 = 0;
				break;
			case peripheral::IRQ3:
				MPC::PD3PFS.ISEL = enable;  // PD3
				PORTD::PMR.B3 = 0;
				break;
			case peripheral::IRQ4:
				MPC::PD4PFS.ISEL = enable;  // PD4
				PORTD::PMR.B4 = 0;
				break;
			case peripheral::IRQ5:
				MPC::PD5PFS.ISEL = enable;  // PD5
				PORTD::PMR.B5 = 0;
				break;
			case peripheral::IRQ6:
				MPC::PD6PFS.ISEL = enable;  // PD6
				PORTD::PMR.B6 = 0;
				break;
			case peripheral::IRQ7:
				MPC::PD7PFS.ISEL = enable;  // PD7
				PORTD::PMR.B7 = 0;
				break;

			default:
				ret = false;
				break;
			}
			return ret;
		}


		static bool sub_2nd_(peripheral t, bool enable)
		{
			bool ret = true;
			switch(t) {

			case peripheral::SCI2:
				{
					uint8_t sel = enable ? 0b001010 : 0;
					MPC::P50PFS.PSEL = sel;  // TXD2/SMOSI2
					MPC::P51PFS.PSEL = sel;  // SCK2
					MPC::P52PFS.PSEL = sel;  // RXD2/SMISO2
					PORT5::PMR.B0 = enable;
					PORT5::PMR.B1 = enable;
					PORT5::PMR.B2 = enable;
				}
				break;

			case peripheral::RSPI:  // RSPI-B
				{
					uint8_t sel = enable ? 0b001101 : 0;
					MPC::PA7PFS.PSEL = sel;  // MISOA-B  (PA7 LQFP176: 106)
					PORTA::PMR.B7 = enable;
					MPC::PA6PFS.PSEL = sel;  // MOSIA-B  (PA6 LQFP176: 107)
					PORTA::PMR.B6 = enable;
					MPC::PA5PFS.PSEL = sel;  // RSPCKA-B (PA5 LQFP176: 108)
					PORTA::PMR.B5 = enable;
				}
				break;

			case peripheral::QSPI:  // QSPI-B
				{
					uint8_t sel = enable ? 0b011011 : 0;
					MPC::PD7PFS.PSEL = sel;  // QIO1-B   (PD7 LQFP176: 143)
					MPC::PD6PFS.PSEL = sel;  // QIO0-B   (PD6 LQFP176: 145)
					MPC::PD5PFS.PSEL = sel;  // QSPCLK-B (PD5 LQFP176: 147)
					MPC::PD3PFS.PSEL = sel;  // QIO3-B   (PD3 LQFP176: 150)
					MPC::PD2PFS.PSEL = sel;  // QIO2-B   (PD2 LQFP176: 154)
					PORTD::PMR.B7 = enable;
					PORTD::PMR.B6 = enable;
					PORTD::PMR.B5 = enable;
					PORTD::PMR.B3 = enable;
					PORTD::PMR.B2 = enable;
				}
				break;

			case peripheral::IRQ4:
				MPC::PF5PFS.ISEL = enable;  // PF5
				PORTF::PMR.B5 = 0;
				break;

			default:
				ret = false;
				break;
			}
			return ret;
		}


		static bool sub_3rd_(peripheral t, bool enable)
		{
			bool ret = true;
			switch(t) {

			case peripheral::SDHI:
				{
					uint8_t sel = enable ? 0b011010 : 0;
					MPC::P25PFS.PSEL = sel;  // SDHI_CD P25(32)
					PORT2::PMR.B5 = enable;
					MPC::P24PFS.PSEL = sel;  // SDHI_WP P24(33)
					PORT2::PMR.B4 = enable;
					MPC::P23PFS.PSEL = sel;  // SDHI_D1-C  P23(34)
					PORT2::PMR.B3 = enable;
					MPC::P22PFS.PSEL = sel;  // SDHI_D0-C  P22(35)
					PORT2::PMR.B2 = enable;
					MPC::P21PFS.PSEL = sel;  // SDHI_CLK-C P21(36)
					PORT2::PMR.B1 = enable;
					MPC::P20PFS.PSEL = sel;  // SDHI_CMD-C P20(37)
					PORT2::PMR.B0 = enable;
					MPC::P17PFS.PSEL = sel;  // SDHI_D3-C  P17(38)
					PORT1::PMR.B7 = enable;
   					MPC::P87PFS.PSEL = sel;  // SDHI_D2-C  P87(39)
					PORT8::PMR.B7 = enable;
				}
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}


	public:

		//-----------------------------------------------------------------//
		/*!
			@brief  周辺機器に切り替える
			@param[in]	t	周辺機器タイプ
			@param[in]	ena	無効にする場合「false」
			@param[in]	opt	ポート・マップ・オプション
		*/
		//-----------------------------------------------------------------//
		static bool turn(peripheral t, bool ena = true, option opt = option::FIRST) noexcept
		{
			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			if(opt == option::FIRST) {
				ret = sub_1st_(t, ena);
			} else if(opt == option::SECOND) {
				ret = sub_2nd_(t, ena);
			} else if(opt == option::THIRD) {
				ret = sub_3rd_(t, ena);
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  SDHI クロック端子のソフト制御
			@param[in]	t	周辺機器タイプ
			@param[in]	ena	SDHI のクロック端子にする場合「true」
			@param[in]	out	SDHI クロック出力設定
			@param[in]	opt	ポート・マップ・オプション
			@return 周辺機器型が異なる場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn_sdhi_clk(peripheral t, bool ena, bool out, option opt = option::FIRST) noexcept
		{
			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			bool ret = false;
			if(t == peripheral::SDHI) {
				if(opt == option::FIRST) {
					if(ena) {
						MPC::P77PFS.PSEL = 0b011010;  // enable SDHI_CLK
						PORT7::PMR.B7 = 1;
					} else {
						MPC::P77PFS.PSEL = 0;  		  // disable SDHI_CLK
						PORT7::PMR.B7 = 0;
						PORT7::PCR.B7 = 0;  // pullup offline
						PORT7::PDR.B7 = 1;  // output
						PORT7::PODR.B7 = out;
					}
					ret = true;
				} else if(opt == option::THIRD) {
					if(ena) {
						MPC::P21PFS.PSEL = 0b011010;  // enable SDHI_CLK
						PORT2::PMR.B1 = 1;
					} else {
						MPC::P21PFS.PSEL = 0;  		  // disable SDHI_CLK
						PORT2::PMR.B1 = 0;
						PORT2::PCR.B1 = 0;  // pullup offline
						PORT2::PDR.B1 = 1;  // output
						PORT2::PODR.B1 = out;
					}
					ret = true;
				}
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}


#if 0
		//-----------------------------------------------------------------//
		/*!
			@brief  アナログ入出力に切り替える
			@param[in]	t	周辺機器タイプ
			@param[in]	ena	無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		static bool turn_analog(bool ena = true) noexcept
		{
			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可



			MPC::PWPR = device::MPC::PWPR.B0WI.b();

			return ret;
		}
#endif
	};
}

