//=====================================================================//
/*! @file
    @brief  RX24T SDC サンプル @n
			・P00(4) ピンに赤色LED（VF:1.9V）を吸い込みで接続する
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/cmt_io.hpp"
#include "common/sci_io.hpp"
#include "common/fifo.hpp"
#include "common/format.hpp"
#include "common/command.hpp"
#include "common/rspi_io.hpp"
#include "common/spi_io.hpp"
#include "common/sdc_io.hpp"

#ifdef RTC
#include "common/iica_io.hpp"
#include "chip/DS3231.hpp"
#endif

namespace {

	class cmt_task {
	public:
		void operator() () {
		}
	};

	device::cmt_io<device::CMT0, cmt_task>  cmt_;

	typedef utils::fifo<uint8_t, 128> buffer;
	device::sci_io<device::SCI1, buffer, buffer> sci_;

#ifdef RTC
	typedef device::iica_io<device::RIIC0> I2C;
	I2C i2c_;

	chip::DS3231<I2C> rtc_(i2c_);
#endif

#if 0
	// RSPI SDC 用　SPI 定義（RSPI0）
	typedef device::rspi_io<device::RSPI0> SPI;
	SPI spi_;
#else
	// Soft SDC 用　SPI 定義（SPI）
	typedef device::PORT<device::PORT2, device::bitpos::B2> MISO;
	typedef device::PORT<device::PORT2, device::bitpos::B3> MOSI;
	typedef device::PORT<device::PORT2, device::bitpos::B4> SPCK;
	typedef device::spi_io<MISO, MOSI, SPCK> SPI;
	SPI spi_;
#endif
	typedef device::PORT<device::PORT6, device::bitpos::B5> sdc_select;	///< カード選択信号
	typedef device::PORT<device::PORT6, device::bitpos::B4> sdc_power;	///< カード電源制御
	typedef device::PORT<device::PORT6, device::bitpos::B3> sdc_detect;	///< カード検出

	utils::sdc_io<SPI, sdc_select, sdc_power, sdc_detect> sdc_(spi_, 20000000);

	utils::command<128> command_;

#ifdef RTC
	time_t get_time_()
	{
		time_t t = 0;
		if(!rtc_.get_time(t)) {
			utils::format("Stall RTC read (%d)\n") % static_cast<uint32_t>(i2c_.get_last_error());
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
			utils::format("Can't analize Time/Date input.\n");
			return;
		}

		time_t tt = mktime(m);
		if(!rtc_.set_time(tt)) {
			utils::format("Stall RTC write...\n");
		}
	}
#endif
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
#ifdef RTC
		time_t t = 0;
		if(!rtc_.get_time(t)) {
			utils::format("Stall RTC read (%d)\n") % static_cast<uint32_t>(iica_.get_last_error());
		}
		return utils::str::get_fattime(t);
#else
		return 0;
#endif
	}

	void utf8_to_sjis(const char* src, char* dst) {
		utils::str::utf8_to_sjis(src, dst);
	}

	uint8_t v_ = 91;
	uint8_t m_ = 123;
	uint8_t rand_()
	{
		v_ += v_ << 2;
		++v_;
		uint8_t n = 0;
		if(m_ & 0x02) n = 1;
		if(m_ & 0x40) n ^= 1;
		m_ += m_;
		if(n == 0) ++m_;
		return v_ ^ m_;
	}

	bool create_test_file_(const char* fname, uint32_t size)
	{
		uint8_t buff[512];
		FIL fp;

		utils::format("SD Write test...\n");

		for(uint16_t i = 0; i < sizeof(buff); ++i) {
			buff[i] = rand_();
		}

		auto st = cmt_.get_counter();
		if(!sdc_.open(&fp, fname, FA_WRITE | FA_CREATE_ALWAYS)) {
			utils::format("Can't create file: '%s'\n") % fname;
			return false;
		}
		auto rs = size;
		while(rs > 0) {
			UINT sz = sizeof(buff);
			if(sz > rs) sz = rs;
			UINT bw;
			f_write(&fp, buff, sz, &bw);
			rs -= bw;
		}
		f_close(&fp);

		auto ed = cmt_.get_counter();
		uint32_t len;
		if(ed > st) len = ed - st;
		else len = 65536 + ed - st;
		utils::format("Write frame: %d\n") % len;
		auto pbyte = size * 60 / len;
		utils::format("Write: %d Bytes/Sec\n") % pbyte;
		utils::format("Write: %d KBytes/Sec\n") % (pbyte / 1024);

		return true;
	}

	void test_all_()
	{
		utils::format("SD Speed test start...\n");

		const char* test_file = { "TEST.BIN" };
		uint32_t size = 1024L * 1024L;
		if(!create_test_file_(test_file, size)) {
			return;
		}

		auto st = cmt_.get_counter();

		utils::format("SD Read test...\n");
		FIL fp;
		if(!sdc_.open(&fp, test_file, FA_READ)) {
			utils::format("Can't read file: '%s'\n") % test_file;
		}
		auto rs = size;
		while(rs > 0) {
			uint8_t buff[512];
			UINT rb;
			UINT sz = sizeof(buff);
			if(sz > rs) sz = rs;
			f_read(&fp, buff, sz, &rb);
			rs -= rb;
		}
		f_close(&fp);

		auto ed = cmt_.get_counter();
		uint32_t len;
		if(ed > st) len = ed - st;
		else len = 65536 + ed - st;
		utils::format("Read frame: %d\n") % len;
		auto pbyte = size * 60 / len;
		utils::format("Read: %d Bytes/Sec\n") % pbyte;
		utils::format("Read: %d KBytes/Sec\n") % (pbyte / 1024);
	}

	bool check_mount_() {
		auto f = sdc_.get_mount();
		if(!f) {
			utils::format("SD card not mount.\n");
		}
		return f;
	}
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	device::SYSTEM::PRCR = 0xA50B;	// クロック、低消費電力、関係書き込み許可

	device::SYSTEM::MEMWAIT = 0b10; // 80MHz 動作 wait 設定

	while(device::SYSTEM::OPCCR.OPCMTSF() != 0) asm("nop");
	device::SYSTEM::OPCCR = 0;  // 高速モード選択
	while(device::SYSTEM::OPCCR.OPCMTSF() != 0) asm("nop");

	// clock osc 10MHz
	device::SYSTEM::MOSCWTCR = 9;	// 4ms wait
	// メインクロック・ドライブ能力設定、内部発信
	device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV21.b(1);
	device::SYSTEM::MOSCCR.MOSTP = 0;  // メインクロック発振器動作
	while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) asm("nop");

	device::SYSTEM::PLLCR.STC = 0b001111;		// PLL input: 1, PLL 8 倍(80MHz)
	device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
	while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) asm("nop");

	device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(2)		// 1/4 (80/4=20)
						  | device::SYSTEM::SCKCR.ICK.b(0)		// 1/1 (80/1=80)
						  | device::SYSTEM::SCKCR.PCKA.b(0)		// 1/1 (80/1=80)
						  | device::SYSTEM::SCKCR.PCKB.b(1)		// 1/2 (80/2=40)
						  | device::SYSTEM::SCKCR.PCKD.b(1);	// 1/2 (120/2=60)
	device::SYSTEM::SCKCR3.CKSEL = 0b100;	///< PLL 選択

	{  // タイマー設定（６０Ｈｚ）
		uint8_t intr_level = 4;
		cmt_.start(60, intr_level);
	}

	{  // SCI 設定
		uint8_t intr_level = 2;
		sci_.start(115200, intr_level);
	}

#ifdef RTC
	{  // IICA(I2C) の開始
		uint8_t intr_level = 0;
		if(!i2c_.start(I2C::speed::fast, intr_level)) {
			utils::format("IICA start error (%d)\n") % static_cast<uint32_t>(i2c_.get_last_error());
		}
	}
#endif

	// SD カード・クラスの初期化
	sdc_.start();

	utils::format("RX24T SD-CARD Access sample\n");

#ifdef RTC
	// DS3231(RTC) の開始
	if(!rtc_.start()) {
		utils::format("Stall RTC start (%d)\n") % static_cast<uint32_t>(i2c_.get_last_error());
	}
#endif

	command_.set_prompt("# ");

	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;

	LED::DIR = 1;

	uint32_t cnt = 0;
	while(1) {
		cmt_.sync();

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		LED::P = (cnt < 10) ? 0 : 1;

		sdc_.service();

		// コマンド入力と、コマンド解析
		if(command_.service()) {
			auto cmdn = command_.get_words();
			if(cmdn >= 1) {
				bool f = false;
				if(command_.cmp_word(0, "dir")) {  // dir [xxx]
					if(check_mount_()) {
						if(cmdn >= 2) {
							char tmp[128];
							command_.get_word(1, sizeof(tmp), tmp);
							sdc_.dir(tmp);
						} else {
							sdc_.dir("");
						}
					}
					f = true;
				} else if(command_.cmp_word(0, "cd")) {  // cd [xxx]
					if(check_mount_()) {
						if(cmdn >= 2) {
							char tmp[128];
							command_.get_word(1, sizeof(tmp), tmp);
							sdc_.cd(tmp);						
						} else {
							sdc_.cd("/");
						}
					}
					f = true;
				} else if(command_.cmp_word(0, "pwd")) { // pwd
					utils::format("%s\n") % sdc_.get_current();
					f = true;
				} else if(command_.cmp_word(0, "speed")) { // speed
					if(check_mount_()) {
						test_all_();
					}
					f = true;
				} else if(command_.cmp_word(0, "help")) { // help
					utils::format("dir [name]\n");
					utils::format("cd [directory-name]\n");
					utils::format("pwd\n");
					utils::format("speed\n");
#ifdef RTC
					utils::format("date\n");
#endif
					f = true;
#ifdef RTC
				} else if(command_.cmp_word(0, "date")) { // date
					date_();
					f = true;
				}
#else
				}
#endif
				if(!f) {
					char tmp[128];
					command_.get_word(0, sizeof(tmp), tmp);
					utils::format("Command error: '%s'\n") % tmp;
				}
			}
		}
	}
}
