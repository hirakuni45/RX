//=====================================================================//
/*! @file
    @brief  RX65N ロガーメイン
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
// 漢字フォントをキャッシュする場合
#define CASH_KFONT

#include "common/renesas.hpp"
#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/format.hpp"
#include "common/command.hpp"
#include "common/spi_io2.hpp"
#include "common/sdc_man.hpp"
#include "common/qspi_io.hpp"

#include "scenes.hpp"

namespace {

	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
	typedef device::PORT<device::PORT0, device::bitpos::B5> SW2;

	typedef device::system_io<12000000> SYSTEM_IO;

	// debug serial port
	typedef utils::fixed_fifo<char, 512>  REB;
	typedef utils::fixed_fifo<char, 1024> SEB;
	typedef device::sci_io<device::SCI9, REB, SEB> SCI;
	SCI			sci_;

	// QSPI B グループ
//	typedef device::qspi_io<device::QSPI, device::port_map::option::SECOND> QSPI;
//	QSPI		qspi_;

	typedef utils::command<256> CMD;
	CMD			cmd_;

	typedef app::scenes	SCENES;
	SCENES		scenes_;


	bool check_mount_() {
		return scenes_.at_base().at_sdc().get_mount();
	}


	void command_()
	{
		if(!cmd_.service()) {
			return;
		}

		uint8_t cmdn = cmd_.get_words();
		if(cmdn >= 1) {
			bool f = false;
			if(cmd_.cmp_word(0, "dir")) {  // dir [xxx]
				if(check_mount_()) {
					if(cmdn >= 2) {
						char tmp[128];
						cmd_.get_word(1, tmp, sizeof(tmp));
						scenes_.at_base().at_sdc().dir(tmp);
					} else {
						scenes_.at_base().at_sdc().dir("");
					}
				}
				f = true;
			} else if(cmd_.cmp_word(0, "cd")) {  // cd [xxx]
				if(check_mount_()) {
					if(cmdn >= 2) {
						char tmp[128];
						cmd_.get_word(1, tmp, sizeof(tmp));
						scenes_.at_base().at_sdc().cd(tmp);						
					} else {
						scenes_.at_base().at_sdc().cd("/");
					}
				}
				f = true;
			} else if(cmd_.cmp_word(0, "pwd")) { // pwd
				utils::format("%s\n") % scenes_.at_base().at_sdc().get_current();
				f = true;
			} else if(cmd_.cmp_word(0, "gui")) {
				at_scenes_base().at_widget_director().list_all();
				f = true;
			} else if(cmd_.cmp_word(0, "help")) {
				utils::format("    dir [path]\n");
				utils::format("    cd [path]\n");
				utils::format("    pwd\n");
				f = true;
			}
			if(!f) {
				char tmp[128];
				if(cmd_.get_word(0, tmp, sizeof(tmp))) {
					utils::format("Command error: '%s'\n") % tmp;
				}
			}
		}
	}
}


void change_scene(app::scenes_id id)
{
	scenes_.change(id);
}


app::scenes_base& at_scenes_base()
{
	return scenes_.at_base();
}

/// widget の登録
bool insert_widget(gui::widget* w)
{
	return at_scenes_base().at_widget_director().insert(w);
}

/// widget の解除
void remove_widget(gui::widget* w)
{
	at_scenes_base().at_widget_director().remove(w);
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
		return scenes_.at_base().at_sdh().disk_initialize(drv);
	}


	DSTATUS disk_status(BYTE drv) {
		return scenes_.at_base().at_sdh().disk_status(drv);
	}


	DRESULT disk_read(BYTE drv, BYTE* buff, DWORD sector, UINT count) {
		return scenes_.at_base().at_sdh().disk_read(drv, buff, sector, count);
	}


	DRESULT disk_write(BYTE drv, const BYTE* buff, DWORD sector, UINT count) {
		return scenes_.at_base().at_sdh().disk_write(drv, buff, sector, count);
	}


	DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void* buff) {
		return scenes_.at_base().at_sdh().disk_ioctl(drv, ctrl, buff);
	}


	DWORD get_fattime(void) {
///		time_t t = 0;
///		rtc_.get_time(t);
		// GPS モジュールから GMT 時間を取得
		auto t = scenes_.at_base().at_nmea().get_gmtime();		
		return utils::str::get_fattime(t);
	}


	void utf8_to_sjis(const char* src, char* dst, uint32_t len) {
		utils::str::utf8_to_sjis(src, dst, len);
	}


	int fatfs_get_mount() {
		return check_mount_();
	}


	int make_full_path(const char* src, char* dst, uint16_t len)
	{
		return scenes_.at_base().at_sdc().make_full_path(src, dst, len);
	}
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::setup_system_clock();

	{  // SCI 設定
		uint8_t intr = 2;
		sci_.start(115200, intr);
	}

	utils::format("\rRTK5RX65N Start for Data Logger\n");

	cmd_.set_prompt("# ");

//	{  // QSPI の初期化（Flash Memory Read/Write Interface)
//		if(!qspi_.start(1000000, QSPI::PHASE::TYPE1, QSPI::DLEN::W8)) {
//			utils::format("QSPI not start.\n");
//		}
//	}

	// シーン初期化
	scenes_.at_base().init();

	LED::DIR = 1;


	


	uint8_t n = 0;
	while(1) {
		scenes_.at_base().sync();

		scenes_.at_base().update();

		scenes_.service();

		command_();

		++n;
		if(n >= 30) n = 0;
		if(n < 10) {
			LED::P = 0;
		} else {
			LED::P = 1;
		}
	}
}
