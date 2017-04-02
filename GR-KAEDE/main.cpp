//=====================================================================//
/*! @file
    @brief  GR-KAEDE(RX64M) サンプル @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/cmt_io.hpp"
#include "common/fifo.hpp"
#include "common/sci_io.hpp"
#include "common/format.hpp"
#include "rx64m/rtc_io.hpp"
#include "common/command.hpp"

#include "common/vect.h"
#include "GR/core/Ethernet.h"

#include <cstdlib>

#define SERVER_TASK

namespace {

	volatile unsigned long millis_ = 0;
	volatile unsigned long delay_ = 0;
	volatile uint32_t millis10x_ = 0;
	volatile uint32_t cmtdiv_ = 0;

	class cmt_task {
	public:
		void operator() () {
			++millis_;
			++cmtdiv_;
			if(cmtdiv_ >= 10) {
				cmtdiv_ = 0;
				++millis10x_;
			}
			if(delay_) {
				--delay_;
			}
		}
	};

	static void sync_100hz()
	{
		volatile uint32_t tmp = millis10x_;
		while(tmp == millis10x_) ;
	}

	device::cmt_io<device::CMT0, cmt_task>  cmt_;

	typedef utils::fifo<uint8_t, 256> buffer;
	device::sci_io<device::SCI7, buffer, buffer> sci_;

	utils::rtc_io rtc_;

	utils::command<256> cmd_;

	// EthernetClient client_;
#ifdef SERVER_TASK
	EthernetServer server_(80);
#endif
}

extern "C" {

	void INT_Excep_ICU_GROUPAL1(void);
	void INT_Excep_CMT1_CMI1(void);

	void sci_putch(char ch)
	{
		sci_.putch(ch);
	}

	void sci_puts(const char* s)
	{
		sci_.puts(s);
	}

	char sci_getch(void)
	{
		return sci_.getch();
	}

	uint16_t sci_length(void)
	{
		return sci_.recv_length();
	}

	time_t get_time_()
	{
		time_t t = 0;
		if(!rtc_.get_time(t)) {
			utils::format("Stall RTC read\n");
		}
		return t;
	}

	unsigned long millis(void)
	{
		return millis_;
	}

	void delay(unsigned long ms)
	{
		delay_ = ms;
		while(delay_ != 0) ;		
	}
}

namespace {

	void disp_time_(time_t t, char* dst = nullptr, uint32_t size = 0)
	{
		struct tm *m = localtime(&t);
		utils::format("%s %s %d %02d:%02d:%02d  %4d\n", dst, size)
			% get_wday(m->tm_wday)
			% get_mon(m->tm_mon)
			% static_cast<uint32_t>(m->tm_mday)
			% static_cast<uint32_t>(m->tm_hour)
			% static_cast<uint32_t>(m->tm_min)
			% static_cast<uint32_t>(m->tm_sec)
			% static_cast<uint32_t>(m->tm_year + 1900);
	}

	const char* get_dec_(const char* p, char tmch, int& value) {
		int v = 0;
		char ch;
		while((ch = *p) != 0) {
			++p;
			if(ch == tmch) {
				break;
			} else if(ch >= '0' && ch <= '9') {
				v *= 10;
				v += ch - '0';
			} else {
				return nullptr;
			}
		}
		value = v;
		return p;
	}

	void set_time_date_()
	{
		time_t t = get_time_();
		if(t == 0) return;

		struct tm *m = localtime(&t);
		bool err = false;
		if(cmd_.get_words() == 3) {
			char buff[12];
			if(cmd_.get_word(1, sizeof(buff), buff)) {
				const char* p = buff;
				int vs[3];
				uint8_t i;
				for(i = 0; i < 3; ++i) {
					p = get_dec_(p, '/', vs[i]);
					if(p == nullptr) {
						break;
					}
				}
				if(p != nullptr && p[0] == 0 && i == 3) {
					if(vs[0] >= 1900 && vs[0] < 2100) m->tm_year = vs[0] - 1900;
					if(vs[1] >= 1 && vs[1] <= 12) m->tm_mon = vs[1] - 1;
					if(vs[2] >= 1 && vs[2] <= 31) m->tm_mday = vs[2];		
				} else {
					err = true;
				}
			}

			if(cmd_.get_word(2, sizeof(buff), buff)) {
				const char* p = buff;
				int vs[3];
				uint8_t i;
				for(i = 0; i < 3; ++i) {
					p = get_dec_(p, ':', vs[i]);
					if(p == nullptr) {
						break;
					}
				}
				if(p != nullptr && p[0] == 0 && (i == 2 || i == 3)) {
					if(vs[0] >= 0 && vs[0] < 24) m->tm_hour = vs[0];
					if(vs[1] >= 0 && vs[1] < 60) m->tm_min = vs[1];
					if(i == 3 && vs[2] >= 0 && vs[2] < 60) m->tm_sec = vs[2];
					else m->tm_sec = 0;
				} else {
					err = true;
				}
			}
		}

		if(err) {
			sci_puts("Can't analize Time/Date input.\n");
			return;
		}

		time_t tt = mktime(m);
		if(!rtc_.set_time(tt)) {
			sci_puts("Stall RTC write...\n");
		}
	}


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
							utils::format("analog input(%d): %d", tmp, sizeof(tmp)) % ach % rand();
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
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	device::SYSTEM::PRCR = 0xA50B;	// クロック、低消費電力、関係書き込み許可

	device::SYSTEM::MOSCWTCR = 9;	// 1ms wait
	// メインクロック強制発振とドライブ能力設定
	device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV2.b(0b10)
						  | device::SYSTEM::MOFCR.MOFXIN.b(1);
	device::SYSTEM::MOSCCR.MOSTP = 0;		// メインクロック発振器動作
	while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) asm("nop");

	// Base Clock 12MHz
	// PLLDIV: 1/1, STC: 16 倍(192MHz)
	device::SYSTEM::PLLCR = device::SYSTEM::PLLCR.PLIDIV.b(0) |
							device::SYSTEM::PLLCR.STC.b(0b011111);
	device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
	while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) asm("nop");

	device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(2)		// 1/2 (192/4=48)
						  | device::SYSTEM::SCKCR.ICK.b(1)		// 1/2 (192/2=96)
						  | device::SYSTEM::SCKCR.BCK.b(2)		// 1/2 (192/4=48)
						  | device::SYSTEM::SCKCR.PCKA.b(1)		// 1/2 (192/2=96)
						  | device::SYSTEM::SCKCR.PCKB.b(2)		// 1/4 (192/4=48)
						  | device::SYSTEM::SCKCR.PCKC.b(2)		// 1/4 (192/4=48)
						  | device::SYSTEM::SCKCR.PCKD.b(2);	// 1/4 (192/4=48)
	device::SYSTEM::SCKCR2 = device::SYSTEM::SCKCR2.UCK.b(0b0011) | 1;  // USB Clock: 1/4 (192/4=48)
	device::SYSTEM::SCKCR3.CKSEL = 0b100;	///< PLL 選択

	{  // タイマー設定、１０００Ｈｚ（１ｍｓ）
		uint8_t int_level = 4;
		cmt_.start(1000, int_level);
	}

	{  // SCI 設定
		uint8_t int_level = 2;
		sci_.start(115200, int_level);
	}

	{  // RTC 設定
		rtc_.start();
	}

	// タイトル・コール
	utils::format("\nStart GR-KAEDE, ");
	utils::format("Endian: %3b") % static_cast<uint32_t>(device::SYSTEM::MDE.MDE());
	utils::format(", PCKA: %u [Hz]") % static_cast<uint32_t>(F_PCKA);
	utils::format(", PCKB: %u [Hz]\n") % static_cast<uint32_t>(F_PCKB);
	{
		time_t t = get_time_();
		if(t != 0) {
			disp_time_(t);
		}
	}

	{  // Ethernet 起動
		device::power_cfg::turn(device::peripheral::ETHERC0);
		device::port_map::turn(device::peripheral::ETHERC0);
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

#ifdef SERVER_TASK
		server_.begin();
		utils::format("Start server: ");
		Ethernet.localIP().print();
#endif
	}

	cmd_.set_prompt("# ");

	device::PORTC::PDR.B0 = 1; // output

	uint32_t cnt = 0;

	while(1) {
///		cmt_.sync();
		sync_100hz();
		Ethernet.mainloop();

		// コマンド入力と、コマンド解析
		if(cmd_.service()) {
			uint8_t cmdn = cmd_.get_words();
			if(cmdn >= 1) {
				if(cmd_.cmp_word(0, "date")) {
					if(cmdn == 1) {
						time_t t = get_time_();
						if(t != 0) {
							disp_time_(t);
						}
					} else {
						set_time_date_();
					}
				} else if(cmd_.cmp_word(0, "help") || cmd_.cmp_word(0, "?")) {
					sci_puts("date\n");
					sci_puts("date yyyy/mm/dd hh:mm[:ss]\n");
				} else {
					char buff[32];
					if(cmd_.get_word(0, sizeof(buff), buff)) {
						sci_puts("Command error: ");
						sci_puts(buff);
						sci_putch('\n');
					}
				}
			}
		}

#ifdef SERVER_TASK
		service_server();
#endif

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		device::PORTC::PODR.B0 = (cnt < 10) ? 0 : 1;
	}
}
