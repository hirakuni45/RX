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
#include "common/command.hpp"
#include "common/rspi_io.hpp"
#include "common/spi_io.hpp"
#include "common/sdc_io.hpp"

#include <string>

#include <cstdlib>

#define SERVER_TASK

#ifdef SERVER_TASK
#include "GR/core/Ethernet.h"
#endif

namespace {

	class cmt_task {
		void (*task_10ms_)();

		volatile unsigned long millis_;
		volatile unsigned long delay_;
		volatile uint32_t millis10x_;
		volatile uint32_t cmtdiv_;

	public:
		cmt_task() : task_10ms_(nullptr),
			millis_(0), delay_(0), millis10x_(0), cmtdiv_(0) { }

		void operator() () {
			++millis_;
			++cmtdiv_;
			if(cmtdiv_ >= 10) {
				if(task_10ms_ != nullptr) (*task_10ms_)();
				cmtdiv_ = 0;
				++millis10x_;
			}
			if(delay_) {
				--delay_;
			}
		}

		void set_task_10ms(void (*task)(void)) {
			task_10ms_ = task;
		}

		void sync_100hz()
		{
			volatile uint32_t tmp = millis10x_;
			while(tmp == millis10x_) ;
		}

		unsigned long get_millis() const { return millis_; }
		unsigned long get_delay() const { return delay_; }
		void set_delay(unsigned long n) { delay_ = n; }
	};

	device::cmt_io<device::CMT0, cmt_task>  cmt_;

	typedef utils::fifo<uint8_t, 4096> buffer;
	device::sci_io<device::SCI7, buffer, buffer> sci_;

	utils::rtc_io rtc_;

#if 1
	// SDC 用　SPI 定義（RSPI）
	typedef device::rspi_io<device::RSPI> SPI;
#else
	// Soft SDC 用　SPI 定義（SPI）
	typedef device::PORT<device::PORTC, device::bitpos::B7> MISO;
	typedef device::PORT<device::PORTC, device::bitpos::B6> MOSI;
	typedef device::PORT<device::PORTC, device::bitpos::B5> SPCK;
	typedef device::spi_io<MISO, MOSI, SPCK> SPI;
#endif
	SPI spi_;

	typedef device::PORT<device::PORTC, device::bitpos::B4> sdc_select;	///< カード選択信号
	typedef device::NULL_PORT  sdc_power;	///< カード電源制御（常に電源ＯＮ）
	typedef device::PORT<device::PORTB, device::bitpos::B7> sdc_detect;	///< カード検出

	typedef utils::sdc_io<SPI, sdc_select, sdc_power, sdc_detect> SDC;
	SDC sdc_(spi_, 20000000);

	utils::command<256> cmd_;

#ifdef SERVER_TASK
	EthernetServer server_(80);
#endif

	// TelnetClient
//	EthernetServer telnet_(23);
}

extern "C" {

	void INT_Excep_ICU_GROUPAL1(void);
///	void INT_Excep_CMT1_CMI1(void);

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

	DSTATUS disk_initialize(BYTE drv) {
		return sdc_.at_mmc().disk_initialize(drv);
	}

	DSTATUS disk_status(BYTE drv) {
		return sdc_.at_mmc().disk_status(drv);
	}

	DRESULT disk_read(BYTE drv, BYTE* buff, DWORD sector, UINT count) {
		return sdc_.at_mmc().disk_read(drv, buff, sector, count);
	}

	DRESULT disk_write(BYTE drv, const BYTE* buff, DWORD sector, UINT count) {
		return sdc_.at_mmc().disk_write(drv, buff, sector, count);
	}

	DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void* buff) {
		return sdc_.at_mmc().disk_ioctl(drv, ctrl, buff);
	}

	DWORD get_fattime(void) {
		time_t t = 0;
		rtc_.get_time(t);
		return utils::str::get_fattime(t);
	}

	void utf8_to_sjis(const char* src, char* dst) {
		utils::str::utf8_to_sjis(src, dst);
	}

	unsigned long millis(void)
	{
		return cmt_.at_task().get_millis();
	}

	void delay(unsigned long ms)
	{
		cmt_.at_task().set_delay(ms);
		while(cmt_.at_task().get_delay() != 0) ;
	}

	void set_task_10ms(void (*task)(void)) {
		cmt_.at_task().set_task_10ms(task);
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

	bool check_mount_() {
		auto f = sdc_.get_mount();
		if(!f) {
			utils::format("SD card not mount.\n");
		}
		return f;
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
		uint8_t int_level = 2;
		cmt_.start(1000, int_level);
	}

	{  // SCI 設定
		uint8_t int_level = 1;
		sci_.start(115200, int_level);
	}

	{  // RTC 設定
		rtc_.start();
	}

	{  // SD カード・クラスの初期化
		device::PORTC::PDR.B3 = 1; // output
		device::PORTC::PODR.B3 = 1; // MISO: pull-up		
		sdc_.start();
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

#ifdef SERVER_TASK
	{  // Ethernet 起動
		device::power_cfg::turn(device::peripheral::ETHERC0);
		device::port_map::turn(device::peripheral::ETHERC0);
		set_interrupt_task(INT_Excep_ICU_GROUPAL1, static_cast<uint32_t>(device::icu_t::VECTOR::GROUPAL1));
///		set_interrupt_task(INT_Excep_CMT1_CMI1, static_cast<uint32_t>(device::icu_t::VECTOR::CMI1));

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

///		telnet_.begin();
	}
#endif

	cmd_.set_prompt("# ");

	device::PORTC::PDR.B0 = 1; // output

	uint32_t cnt = 0;

	while(1) {
		cmt_.at_task().sync_100hz();

#ifdef SERVER_TASK
		Ethernet.mainloop();
#endif
		sdc_.service();

		// コマンド入力と、コマンド解析
		if(cmd_.service()) {
			uint8_t cmdn = cmd_.get_words();
			if(cmdn >= 1) {
				bool f = false;
				if(cmd_.cmp_word(0, "dir")) {  // dir [xxx]
					if(check_mount_()) {
						if(cmdn >= 2) {
							char tmp[128];
							cmd_.get_word(1, sizeof(tmp), tmp);
							sdc_.dir(tmp);
						} else {
							sdc_.dir("");
						}
					}
					f = true;
				} else if(cmd_.cmp_word(0, "cd")) {  // cd [xxx]
					if(check_mount_()) {
						if(cmdn >= 2) {
							char tmp[128];
							cmd_.get_word(1, sizeof(tmp), tmp);
							sdc_.cd(tmp);						
						} else {
							sdc_.cd("/");
						}
					}
					f = true;
				} else if(cmd_.cmp_word(0, "pwd")) { // pwd
					utils::format("%s\n") % sdc_.get_current();
					f = true;
				} else if(cmd_.cmp_word(0, "date")) {
					if(cmdn == 1) {
						time_t t = get_time_();
						if(t != 0) {
							disp_time_(t);
						}
					} else {
						set_time_date_();
					}
					f = true;
				} else if(cmd_.cmp_word(0, "help") || cmd_.cmp_word(0, "?")) {
					utils::format("date\n");
					utils::format("date yyyy/mm/dd hh:mm[:ss]\n");
					utils::format("dir [name]\n");
					utils::format("cd [directory-name]\n");
					utils::format("pwd\n");
					f = true;
				}
				if(!f) {
					char tmp[128];
					if(cmd_.get_word(0, sizeof(tmp), tmp)) {
						utils::format("Command error: '%s'\n") % tmp;
					}
				}
			}
		}

#ifdef SERVER_TASK
		service_server();
#endif
///		telnet_service();

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		device::PORTC::PODR.B0 = (cnt < 10) ? 0 : 1;
	}
}
