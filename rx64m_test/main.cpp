//=====================================================================//
/*! @file
    @brief  SEEDA03 (RX64M) メイン @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "main.hpp"

namespace seeda {

	core core_;

}

extern "C" {

	extern void INT_Excep_ICU_GROUPAL1(void);
	extern void INT_Excep_CMT1_CMI1(void);

	void sci_putch(char ch)
	{
		seeda::core_.sci_.putch(ch);
	}

	void sci_puts(const char* s)
	{
		seeda::core_.sci_.puts(s);
	}

	char sci_getch(void)
	{
		return seeda::core_.sci_.getch();
	}

	uint16_t sci_length(void)
	{
		return seeda::core_.sci_.recv_length();
	}


	DSTATUS disk_initialize(BYTE drv) {
		return seeda::core_.tools_.disk_initialize(drv);
	}

	DSTATUS disk_status(BYTE drv) {
		return seeda::core_.tools_.disk_status(drv);
	}

	DRESULT disk_read(BYTE drv, BYTE* buff, DWORD sector, UINT count) {
		return seeda::core_.tools_.disk_read(drv, buff, sector, count);
	}

	DRESULT disk_write(BYTE drv, const BYTE* buff, DWORD sector, UINT count) {
		return seeda::core_.tools_.disk_write(drv, buff, sector, count);
	}

	DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void* buff) {
		return seeda::core_.tools_.disk_ioctl(drv, ctrl, buff);
	}


	DWORD get_fattime(void) {
		auto t = seeda::core_.tools_.get_time();
		return utils::str::get_fattime(t);
	}

	void utf8_to_sjis(const char* src, char* dst) {
		utils::str::utf8_to_sjis(src, dst);
	}

	unsigned long millis(void)
	{
		return seeda::core_.cmt0_.at_task().get_millis();
	}

	void delay(unsigned long ms)
	{
		seeda::core_.cmt0_.at_task().set_delay(ms);
		while(seeda::core_.cmt0_.at_task().get_delay() != 0) ;		
	}
}

namespace {

#ifdef SERVER_TASK
	void service_server()
	{
		EthernetClient& client = server_.available();
		if (client) {
			utils::format("new client\n");

			while (client.connected()) {
				if (client.available()) {
					char tmp[256];
					int len = client.read(tmp, 255);
					if(len > 0 && len < 256) {
						tmp[len] = 0;
	        			sci_puts(tmp);
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
							char tmp[128];
							time_t t = get_time_();
							disp_time_(t, tmp, sizeof(tmp));
							client.print(tmp);
							client.println("<br/ >");
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
///			delay(1);
			// close the connection:
			client.stop();
			utils::format("client disconnected\n");
		}
	}
#endif

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
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	using namespace seeda;

	device::PORT3::PCR.B5 = 1; // P35 pull-up

	device::SYSTEM::PRCR = 0xA50B;	// クロック、低消費電力、関係書き込み許可

	device::SYSTEM::MOSCWTCR = 9;	// 1ms wait
	// メインクロック強制発振とドライブ能力設定
	device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV2.b(0b10)
						  | device::SYSTEM::MOFCR.MOFXIN.b(1);
	device::SYSTEM::MOSCCR.MOSTP = 0;		// メインクロック発振器動作
	while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) asm("nop");

	// Base Clock 12.5MHz
	// PLLDIV: 1/1, STC: 16 倍(200MHz)
	device::SYSTEM::PLLCR = device::SYSTEM::PLLCR.PLIDIV.b(0) |
							device::SYSTEM::PLLCR.STC.b(0b011111);
	device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
	while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) asm("nop");

	device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(2)		// 1/2 (200/4=50)
						  | device::SYSTEM::SCKCR.ICK.b(1)		// 1/2 (200/2=100)
						  | device::SYSTEM::SCKCR.BCK.b(2)		// 1/2 (200/4=50)
						  | device::SYSTEM::SCKCR.PCKA.b(1)		// 1/2 (200/2=100)
						  | device::SYSTEM::SCKCR.PCKB.b(2)		// 1/4 (200/4=50)
						  | device::SYSTEM::SCKCR.PCKC.b(2)		// 1/4 (200/4=50)
						  | device::SYSTEM::SCKCR.PCKD.b(2);	// 1/4 (200/4=50)
	device::SYSTEM::SCKCR2 = device::SYSTEM::SCKCR2.UCK.b(0b0011) | 1;  // USB Clock: 1/4 (200/4=50)
	device::SYSTEM::SCKCR3.CKSEL = 0b100;	///< PLL 選択

	core_.init();

	core_.title();

#ifdef SERVER_TASK
	if(get_switch_() == 3) {  // Ethernet 起動
		device::power_cfg::turn(device::peripheral::ETHERCA);
		device::port_map::turn(device::peripheral::ETHERCA);
		set_interrupt_task(INT_Excep_ICU_GROUPAL1, static_cast<uint32_t>(device::icu_t::VECTOR::GROUPAL1));
		set_interrupt_task(INT_Excep_CMT1_CMI1, static_cast<uint32_t>(device::icu_t::VECTOR::CMI1));

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
#endif

	device::PORT4::PDR.B7 = 1; // output

	uint32_t cnt = 0;
	while(1) {

		core_.service();

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		device::PORT4::PODR.B7 = (cnt < 10) ? 0 : 1;
	}
}
