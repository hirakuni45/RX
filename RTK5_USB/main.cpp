//=====================================================================//
/*! @file
    @brief  USB 操作サンプル @n
			RX64M, RX71M, RX72M: @n
					12MHz のベースクロックを使用する @n
			　　　　P07 ピンにLEDを接続する @n
			RX65N (Renesas Envision kit RX65N): @n
					12MHz のベースクロックを使用する @n
			　　　　P70 に接続された LED を利用する @n
			RX66T: @n
					10MHz のベースクロックを使用する @n
			　　　　P00 ピンにLEDを接続する
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/cmt_io.hpp"
#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/format.hpp"
#include "common/input.hpp"
#include "common/vt100.hpp"

#include "common/command.hpp"
#include "common/shell.hpp"

#include "platform.h"
#include "r_usb_basic_config.h"
#include "usb/usb_io.hpp"
#include "usb/usb_hmsc.hpp"

#include "usb/usb_host.hpp"

namespace {

	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;

	typedef utils::fixed_fifo<char, 1024> RECV_BUFF;
	typedef utils::fixed_fifo<char, 512> SEND_BUFF;
	typedef device::sci_io<device::SCI9, RECV_BUFF, SEND_BUFF> SCI_IO;
	SCI_IO		sci_io_;

	typedef utils::VT100<SCI_IO> VT100;
	VT100		vt100_(sci_io_);

	typedef device::usb_io<device::USB0> USB_IO;

	USB_IO		usb_io_;

	typedef fatfs::usb_hmsc<USB_IO> HMSC;
	HMSC		hmsc_(usb_io_);

	static const uint32_t CMT_FREQ = 1000;  ///< 計測用タイマー分解能

	class cmt_task {
		volatile uint32_t	cnt_;
		volatile uint32_t	div_;

	public:
		cmt_task() : cnt_(0), div_(0) { }

		void sync_100hz() noexcept {
			auto tmp = div_;
			while(tmp == div_) ;
		}

		void operator() () noexcept {
			++cnt_;
			if(cnt_ >= 10) {
				cnt_ = 0;
				++div_;
			}
		}
	};

	typedef device::cmt_io<device::CMT0, cmt_task> CMT;
	CMT			cmt_;

	typedef utils::command<256> CMD;
	CMD			cmd_;

	typedef utils::shell<CMD> SHELL;
	SHELL		shell_(cmd_);


	bool write_test_(const char* fname, uint32_t size)
	{
		utils::format("Write: '%s'\n") % fname;

		uint8_t buff[512];
		utils::file_io fio;

		for(uint16_t i = 0; i < sizeof(buff); ++i) {
			buff[i] = rand();
		}

		auto st = cmt_.get_counter();
		if(!fio.open(fname, "wb")) {
			utils::format("Can't create file: '%s'\n") % fname;
			return false;
		}
		auto ed = cmt_.get_counter();
		uint32_t topen = ed - st;
		st = ed;

		auto rs = size;
		while(rs > 0) {
			UINT sz = sizeof(buff);
			if(sz > rs) sz = rs;
			auto bw = fio.write(buff, sz);
			rs -= bw;
		}
		ed = cmt_.get_counter();
		uint32_t twrite = ed - st;
		st = ed;

		fio.close();
		ed = cmt_.get_counter();
		uint32_t tclose = ed - st;

		utils::format("Write Open:  %d [ms]\n") % (topen * 1000 / CMT_FREQ);
		auto pbyte = size * CMT_FREQ / twrite;
//		utils::format("Write: %d Bytes/Sec\n") % pbyte;
		utils::format("Write: %d KBytes/Sec\n") % (pbyte / 1024);
		utils::format("Write Close: %d [ms]\n") % (tclose * 1000 / CMT_FREQ);

		return true;
	}


	void read_test_(const char* fname, uint32_t size)
	{
		utils::format("Read: '%s'\n") % fname;

		auto st = cmt_.get_counter();
		utils::file_io fin;
		if(!fin.open(fname, "rb")) {
			utils::format("Can't read file: '%s'\n") % fname;
			return;
		}
		auto ed = cmt_.get_counter();
		uint32_t topen = ed - st;
		st = ed;

		auto rs = size;
		while(rs > 0) {
			uint8_t buff[512];
			uint32_t sz = sizeof(buff);
			if(sz > rs) sz = rs;
			auto s = fin.read(buff, sz);
			if(s == 0) break;
			rs -= s;
		}
		ed = cmt_.get_counter();
		uint32_t tread = ed - st;
		st = ed;

		fin.close();
		ed = cmt_.get_counter();
		uint32_t tclose = ed - st;

		utils::format("Read Open:  %d [ms]\n") % (topen * 1000 / CMT_FREQ);
		auto pbyte = size * CMT_FREQ / tread;
//		utils::format("Read: %d Bytes/Sec\n") % pbyte;
		utils::format("Read: %d KBytes/Sec\n") % (pbyte / 1024);
		utils::format("Read Close: %d [ms]\n") % (tclose * 1000 / CMT_FREQ);
	}


	void command_()
	{
		if(!cmd_.service()) {
			return;
		}
		if(shell_.analize()) {
			return;
		}

		auto cmdn = cmd_.get_words();

		if(cmd_.cmp_word(0, "write")) { // test file (read/write)
			if(cmdn >= 2) {
				char tmp[128];
				cmd_.get_word(1, tmp, sizeof(tmp));
				write_test_(tmp, 1024 * 1024);
			}
		} else if(cmd_.cmp_word(0, "read")) { // speed test
			if(cmdn >= 2) {
				char tmp[128];
				cmd_.get_word(1, tmp, sizeof(tmp));
				read_test_(tmp, 1024 * 1024);
			}
		} else if(cmd_.cmp_word(0, "time")) { // 日付・時間設定
#if defined( ENABLE_RTC) || defined(ENABLE_I2C_RTC)
			if(cmdn >= 3) {
				char date[64];
				cmd_.get_word(1, date, sizeof(date));
				char time[64];
				cmd_.get_word(2, time, sizeof(time));
				auto t = utils::str::make_time(date, time);
				rtc_.set_time(t);
			} else {
				time_t t = 0;
				if(rtc_.get_time(t)) {
					utils::str::print_date_time(t);
				}
			}
#else
			utils::format("RTC Disabled...\n");
#endif
		} else if(cmd_.cmp_word(0, "help")) {
			shell_.help();
			utils::format("    write filename      test for write\n");
			utils::format("    read filename       test for read\n");
			utils::format("    time [yyyy/mm/dd hh:mm[:ss]]   set date/time\n");
		} else {
			utils::format("Command error: '%s'\n") % cmd_.get_command();
		}
	}
}

extern "C" {

	void sci_putch(char ch)
	{
		sci_io_.putch(ch);
	}


	void sci_puts(const char* str)
	{
		sci_io_.puts(str);
	}


	char sci_getch(void)
	{
		return sci_io_.getch();
	}


	uint16_t sci_length()
	{
		return sci_io_.recv_length();
	}

	usb_err_t usb_module_start (uint8_t ip_type)
	{
		usb_io_.enable_mod();
		return USB_SUCCESS;
	}

	usb_err_t usb_module_stop (uint8_t ip_type)
	{
		usb_io_.enable_mod(false);
		return USB_SUCCESS;
	}

	void usb_cpu_usbint_init (uint8_t ip_type)
	{
		usb_io_.init_intr();
	}

	void usb_cpu_int_enable (void)
	{
		usb_io_.enable_intr();
	}

	void usb_cpu_int_disable (void)
	{
		usb_io_.enable_intr(false);
	}

	void usb_cpu_delay_1us (uint16_t time)
	{
		utils::delay::micro_second(time);
	}

	void usb_cpu_delay_xms (uint16_t time)
	{
		utils::delay::milli_second(time);
	}


	DSTATUS disk_initialize(BYTE drv) {
		return hmsc_.disk_initialize(drv);
	}


	DSTATUS disk_status(BYTE drv) {
		return hmsc_.disk_status(drv);
	}


	DRESULT disk_read(BYTE drv, BYTE* buff, DWORD sector, UINT count) {
		return hmsc_.disk_read(drv, buff, sector, count);
	}


	DRESULT disk_write(BYTE drv, const BYTE* buff, DWORD sector, UINT count) {
		return hmsc_.disk_write(drv, buff, sector, count);
	}


	DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void* buff) {
		return hmsc_.disk_ioctl(drv, ctrl, buff);
	}


	DWORD get_fattime(void) {
		time_t t = 0;
#if defined( ENABLE_RTC) || defined(ENABLE_I2C_RTC)
		rtc_.get_time(t);
#else
		t = utils::str::make_time(nullptr, nullptr);
#endif
		return utils::str::get_fattime(t);
	}
};


int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::setup_system_clock();

	{  // タイマー設定
		uint8_t intr = 4;
		cmt_.start(CMT_FREQ, intr);
	}

	{  // SCI 設定
		uint8_t sci_level = 2;
		sci_io_.start(115200, sci_level);
		vt100_.start();
	}

#ifdef ENABLE_RTC
	{  // RTC の開始
		rtc_.start();
	}
#endif

	LED::OUTPUT();  // LED ポートを出力に設定

	utils::format("RTK5_USB sample start\n");

	{  // USB ホスト開始
		uint8_t lvl = USB_CFG_INTERRUPT_PRIORITY;
		if(!usb_io_.start(lvl)) {
			utils::format("USB Host not start...\n");
		} else {
			utils::format("USB Host start...\n");
		}
	}

	cmd_.set_prompt("# ");

	uint8_t cnt = 0;
	while(1) {
		cmt_.at_task().sync_100hz();

		hmsc_.service();

		command_();

		++cnt;
		if(cnt >= 40) cnt = 0;
		if(cnt < 12) { 
			LED::P = 0;
		} else {
			LED::P = 1;
		}
	}
}
