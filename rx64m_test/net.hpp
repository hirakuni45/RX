#pragma once
//=====================================================================//
/*! @file
    @brief  SEEDA03 net クラス @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "main.hpp"

#include "GR/core/Ethernet.h"
#include <cstdlib>

extern "C" {
	extern void INT_Excep_ICU_GROUPAL1(void);
}

namespace seeda {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  net クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class net {

		typedef device::PORT<device::PORT7, device::bitpos::B0> LAN_RESN;
		typedef device::PORT<device::PORT7, device::bitpos::B3> LAN_PDN;

		EthernetServer server_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		net() : server_(80) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  初期化
		*/
		//-----------------------------------------------------------------//
		void init()
		{
			// LAN initialize (PHY reset, PHY POWER-DOWN
			LAN_PDN::DIR = 1;  // output;
			LAN_PDN::P = 1;    // Not Power Down Mode..
			LAN_RESN::DIR = 1; // output;
			LAN_RESN::P = 0;
			utils::delay::milli_second(200); /// reset rise time
			LAN_RESN::P = 1;

			device::power_cfg::turn(device::peripheral::ETHERCA);
			device::port_map::turn(device::peripheral::ETHERCA);
			set_interrupt_task(INT_Excep_ICU_GROUPAL1, static_cast<uint32_t>(device::icu_t::VECTOR::GROUPAL1));

			Ethernet.maininit();

			static const uint8_t mac[6] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
			if(Ethernet.begin(mac) == 0) {
				utils::format("Ethernet Fail: begin (DHCP)...\n");

				utils::format("SetIP: ");
				IPAddress ipa(192, 168, 3, 20);
				Ethernet.begin(mac, ipa);
			} else {
				utils::format("DHCP: ");
			}
			Ethernet.localIP().print();

			server_.begin();
			utils::format("Start server: ");
			Ethernet.localIP().print();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  タイトル表示（ネット関係）
		*/
		//-----------------------------------------------------------------//
		void title()
		{
		}


#if 0
		void telnet_service()
		{
			EthernetClient& client = telnet_.available();
			if(client) {
				char tmp[256];
				int len = client.read(tmp, 256);
				if(len > 0) {
					client.write(tmp, len);
				}
			}
		}
#endif

		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			Ethernet.mainloop();

			EthernetClient& client = server_.available();
			if (client) {
				utils::format("new client\n");

				while (client.connected()) {
					if (client.available()) {
						char tmp[256];
						int len = client.read(tmp, 255);
						if(len > 0 && len < 256) {
							tmp[len] = 0;
							utils::format("%s") % tmp;
						}

						// if you've gotten to the end of the line (received a newline
						// character) and the line is blank, the http request has ended,
						// so you can send a reply
						if (len > 0 && tmp[len - 1] == '\n') {
							// send a standard http response header
							client.println("HTTP/1.1 200 OK");
							client.println("Content-Type: text/html");
							// the connection will be closed after completion of the response
	          				client.println("Connection: close");
							client.println("Refresh: 5");  // refresh the page automatically every 5 sec
							client.println();
							client.println("<!DOCTYPE HTML>");
							client.println("<html>");
							client.println("<font size=\"5\">");
							{  // 時間表示
//								char tmp[128];
//								time_t t = get_time();
//								disp_time_(t, tmp, sizeof(tmp));
//								client.print(tmp);
//								client.println("<br/ >");
							}
							// アナログ入力の表示
							for (int ach = 0; ach < 4; ++ach) {
								char tmp[128];
								int v = rand() & (4096 - 1);
								utils::format("analog input(%d): %d", tmp, sizeof(tmp)) % ach % v;
								client.print(tmp);
								client.println("<br/ >");
							}
							client.println("</font>");
							client.println("</html>");
							break;
						}
					}
				}
				// give the web browser time to receive the data

				client.stop();
				utils::format("client disconnected\n");
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  PHY リセット信号制御
			@param[in]	cmd		コマンド入力インスタンス
		*/
		//-----------------------------------------------------------------//
		bool reset_signal(CMD cmd)
		{
			uint8_t cmdn = cmd.get_words();
			bool f = false;
			if(cmdn == 1) {
				bool v = LAN_RESN::P();
				utils::format("LAN-RESN: %d\n") % static_cast<int>(v);
				return true;
			} else if(cmdn > 1) {
				char tmp[16];
				if(cmd.get_word(1, sizeof(tmp), tmp)) {
					// Reset signal
					if(strcmp(tmp, "0") == 0) {
						device::PORT7::PODR.B0 = 0;
						f = true;
					} else if(strcmp(tmp, "1") == 0) {
						device::PORT7::PODR.B0 = 1;
						f = true;
					} else {
						utils::format("reset param error: '%s'\n") % tmp;
					}
				}
			}
			return f;
		}
	};
}
