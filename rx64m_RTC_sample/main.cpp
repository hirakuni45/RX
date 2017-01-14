//=====================================================================//
/*! @file
    @brief  RX64M RTC サンプル @n
			・P07(176) ピンに赤色LED（VF:1.9V）を吸い込みで接続する
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/cmt_io.hpp"
#include "common/sci_io.hpp"
#include "rx64m/rtc_io.hpp"
#include "common/fifo.hpp"
#include "common/format.hpp"
#include "common/command.hpp"

namespace {

	class cmt_task {
	public:
		void operator() () {
		}
	};

	device::cmt_io<device::CMT0, cmt_task>  cmt_;

	typedef utils::fifo<uint16_t, 128> buffer;
	device::sci_io<device::SCI1, buffer, buffer> sci_;

	utils::rtc_io rtc_;

	utils::command<64> command_;

}

extern "C" {
	void sci_putch(char ch)
	{
		sci_.putch(ch);
	}

	void sci_puts(const char* str)
	{
		sci_.puts(str);
	}

	char sci_getch(void)
	{
		return sci_.getch();
	}

	uint16_t sci_length()
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


	void disp_time_(time_t t)
	{
		struct tm *m = localtime(&t);
		utils::format("%s %s %d %02d:%02d:%02d  %4d\n")
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
		if(command_.get_words() == 3) {
			char buff[12];
			if(command_.get_word(1, sizeof(buff), buff)) {
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

			if(command_.get_word(2, sizeof(buff), buff)) {
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

	device::SYSTEM::PLLCR.STC = 0b010011;		// PLL 10 倍(120MHz)
	device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
	while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) asm("nop");

	device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(1)		// 1/2 (120/2=60)
						  | device::SYSTEM::SCKCR.ICK.b(0)		// 1/1 (120/1=120)
						  | device::SYSTEM::SCKCR.BCK.b(1)		// 1/2 (120/2=60)
						  | device::SYSTEM::SCKCR.PCKA.b(0)		// 1/1 (120/1=120)
						  | device::SYSTEM::SCKCR.PCKB.b(1)		// 1/2 (120/2=60)
						  | device::SYSTEM::SCKCR.PCKC.b(1)		// 1/2 (120/2=60)
						  | device::SYSTEM::SCKCR.PCKD.b(1);	// 1/2 (120/2=60)
	device::SYSTEM::SCKCR2.UCK = 0b0100;  // USB Clock: 1/5 (120/5=24)
	device::SYSTEM::SCKCR3.CKSEL = 0b100;	///< PLL 選択


	// SDRAM 初期化 128M/32bits bus
	device::MPC::PFAOE0 = 0xff;  // A8 to A15
	device::MPC::PFBCR0 = device::MPC::PFBCR0.ADRLE.b(1) |
						  device::MPC::PFBCR0.DHE.b(1) |
						  device::MPC::PFBCR0.DH32E.b(1);
	device::MPC::PFBCR1 = device::MPC::PFBCR1.MDSDE.b(1) |
						  device::MPC::PFBCR1.DQM1E.b(1) |
						  device::MPC::PFBCR1.SDCLKE.b(1);
	device::SYSTEM::SYSCR0 = device::SYSTEM::SYSCR0.KEY.b(0x5A) |
							 device::SYSTEM::SYSCR0.ROME.b(1) |
							 device::SYSTEM::SYSCR0.EXBE.b(1);
	while(device::SYSTEM::SYSCR0.EXBE() == 0) asm("nop");
	device::BUS::SDIR = device::BUS::SDIR.ARFI.b(0) |
						device::BUS::SDIR.ARFC.b(1) |
						device::BUS::SDIR.PRC.b(0);
	device::BUS::SDICR = device::BUS::SDICR.INIRQ.b(1);  // 初期化シーケンス開始
	while(device::BUS::SDSR() != 0) asm("nop");
	// 動作許可、３２ビットアクセス
	device::BUS::SDCCR = device::BUS::SDCCR.BSIZE.b(1);
	// Burst read and burst write, CAS latency: 3, Burst type: Sequential, Burst length: 1
	device::BUS::SDMOD = 0b00000000110000;
	// CAS latency: 3, Write recovery: 1, ROW prechage: 4, RAS latency: 3, RAS active: 4
	device::BUS::SDTR = device::BUS::SDTR.CL.b(3) |
						device::BUS::SDTR.RP.b(3) |
						device::BUS::SDTR.RCD.b(2) |
						device::BUS::SDTR.RAS.b(3);
	// 128M/16 カラム９ビット、ロウ１２ビット
	device::BUS::SDADR = device::BUS::SDADR.MXC.b(1);
	// Refresh cycle
	device::BUS::SDRFCR = device::BUS::SDRFCR.RFC.b(2048) |
						  device::BUS::SDRFCR.REFW.b(7);
	device::BUS::SDRFEN = device::BUS::SDRFEN.RFEN.b(1);
	// SDRAM 動作開始
	device::BUS::SDCCR.EXENB = 1;

	{  // タイマー設定（６０Ｈｚ）
		uint8_t cmt_irq_level = 4;
		cmt_.start(60, cmt_irq_level);
	}

	{  // SCI 設定
		static const uint8_t sci_level = 2;
		sci_.start(115200, sci_level);
	}

	{  // RTC 設定
		rtc_.start();
	}

	utils::format("RX64M RTC sample\n");

	device::PORT0::PDR.B7 = 1; // output

	command_.set_prompt("# ");

	uint32_t cnt = 0;
	char buff[16];
	while(1) {
		cmt_.sync();

		// コマンド入力と、コマンド解析
		if(command_.service()) {
			uint8_t cmdn = command_.get_words();
			if(cmdn >= 1) {
				if(command_.cmp_word(0, "date")) {
					if(cmdn == 1) {
						time_t t = get_time_();
						if(t != 0) {
							disp_time_(t);
						}
					} else {
						set_time_date_();
					}
				} else if(command_.cmp_word(0, "help")) {
					sci_puts("date\n");
					sci_puts("date yyyy/mm/dd hh:mm[:ss]\n");
				} else {
					if(command_.get_word(0, sizeof(buff), buff)) {
						sci_puts("Command error: ");
						sci_puts(buff);
						sci_putch('\n');
					}
				}
			}
		}

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		device::PORT0::PODR.B7 = (cnt < 10) ? 0 : 1;
	}
}
