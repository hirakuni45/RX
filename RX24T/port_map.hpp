#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・ポート・マッピング @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "RX600/port.hpp"
#include "RX24T/mpc.hpp"
#include "RX24T/peripheral.hpp"

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
			@brief  アナログ入力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class analog : uint8_t {
			AIN000,
			AIN001,
			AIN002,
			AIN003,
			AIN016,

			AIN100,
			AIN101,
			AIN102,
			AIN103,
			AIN116,

			AIN200,
			AIN201,
			AIN202,
			AIN203,
			AIN204,
			AIN205,
			AIN206,
			AIN207,
			AIN208,
			AIN209,
			AIN210,
			AIN211,
		};


	private:
		static void sub_(peripheral t, bool enable) {
			switch(t) {
			case peripheral::RIIC0:
				{
					uint8_t sel = enable ? 0b01111 : 0;
					MPC::PB1PFS.PSEL = sel;  // SCL0
					MPC::PB2PFS.PSEL = sel;  // SDA0
					PORTB::PMR.B1 = enable;
					PORTB::PMR.B2 = enable;
				}
				break;

			case peripheral::RSPI0:
				{
					uint8_t sel = enable ? 0b01101 : 0;
					MPC::P22PFS.PSEL = sel;  // MISOA
					MPC::P23PFS.PSEL = sel;  // MOSIA
					MPC::P24PFS.PSEL = sel;  // RSPCKA
					PORT2::PMR.B2 = enable;
					PORT2::PMR.B3 = enable;
					PORT2::PMR.B4 = enable;
				}
				break;

			case peripheral::SCI1:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					MPC::PD3PFS.PSEL = sel;
					MPC::PD5PFS.PSEL = sel;
					PORTD::PMR.B3 = enable;
					PORTD::PMR.B5 = enable;
				}
				break;
			case peripheral::SCI5:
				{
					uint8_t sel = enable ? 0b01010 : 0;
					MPC::PB5PFS.PSEL = sel;
					MPC::PB6PFS.PSEL = sel;
					PORTB::PMR.B5 = enable;
					PORTB::PMR.B6 = enable;
				}
				break;
			case peripheral::SCI6:
				break;
			default:
				break;
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  周辺機器に切り替える
			@param[in]	t	周辺機器タイプ
			@param[in]	f	周辺機能を使わない場合「false」
		*/
		//-----------------------------------------------------------------//
		static void turn(peripheral t, bool f = true)
		{
			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			sub_(t, f);

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  アナログ入力に切り替える
			@param[in]	t	アナログ入力タイプ
			@param[in]	f	周辺機能を使わない場合「false」
		*/
		//-----------------------------------------------------------------//
		static void turn(analog t, bool f = true) {
			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			switch(t) {
			case analog::AIN000:
				PORT4::PDR.B0 = 0;
				MPC::P40PFS.ASEL = f;
				break;
			case analog::AIN001:
				PORT4::PDR.B1 = 0;
				MPC::P41PFS.ASEL = f;
				break;
			case analog::AIN002:
				PORT4::PDR.B2 = 0;
				MPC::P42PFS.ASEL = f;
				break;
			case analog::AIN003:
				PORT4::PDR.B3 = 0;
				MPC::P43PFS.ASEL = f;
				break;
			case analog::AIN016:
				PORT2::PDR.B0 = 0;
				MPC::P20PFS.ASEL = f;
				break;

			case analog::AIN100:
				PORT4::PDR.B4 = 0;
				MPC::P44PFS.ASEL = f;
				break;
			case analog::AIN101:
				PORT4::PDR.B5 = 0;
				MPC::P45PFS.ASEL = f;
				break;
			case analog::AIN102:
				PORT4::PDR.B6 = 0;
				MPC::P46PFS.ASEL = f;
				break;
			case analog::AIN103:
				PORT4::PDR.B7 = 0;
				MPC::P47PFS.ASEL = f;
				break;
			case analog::AIN116:
				PORT2::PDR.B1 = 0;
				MPC::P21PFS.ASEL = f;
				break;

			case analog::AIN200:
				PORT6::PDR.B0 = 0;
				MPC::P60PFS.ASEL = f;
				break;
			case analog::AIN201:
				PORT6::PDR.B1 = 0;
				MPC::P61PFS.ASEL = f;
				break;
			case analog::AIN202:
				PORT6::PDR.B2 = 0;
				MPC::P62PFS.ASEL = f;
				break;
			case analog::AIN203:
				PORT6::PDR.B3 = 0;
				MPC::P63PFS.ASEL = f;
				break;
			case analog::AIN204:
				PORT6::PDR.B4 = 0;
				MPC::P64PFS.ASEL = f;
				break;
			case analog::AIN205:
				PORT6::PDR.B5 = 0;
				MPC::P65PFS.ASEL = f;
				break;

			case analog::AIN206:
				PORT5::PDR.B0 = 0;
				MPC::P50PFS.ASEL = f;
				break;
			case analog::AIN207:
				PORT5::PDR.B1 = 0;
				MPC::P51PFS.ASEL = f;
				break;
			case analog::AIN208:
				PORT5::PDR.B2 = 0;
				MPC::P52PFS.ASEL = f;
				break;
			case analog::AIN209:
				PORT5::PDR.B3 = 0;
				MPC::P53PFS.ASEL = f;
				break;
			case analog::AIN210:
				PORT5::PDR.B4 = 0;
				MPC::P54PFS.ASEL = f;
				break;
			case analog::AIN211:
				PORT5::PDR.B5 = 0;
				MPC::P55PFS.ASEL = f;
				break;
			default:
				break;
			}
			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}

	};
}

