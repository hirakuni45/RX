//=====================================================================//
/*! @file
    @brief  RX24T データ・ロガー @n
			・P00(4) ピンに赤色LED（VF:1.9V）を吸い込みで接続する @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "main.hpp"

#include "common/scene.hpp"
#include "root_menu.hpp"

namespace {

	core_t core_;

	typedef utils::scene<app::root_menu> SCENE;
	SCENE scene_;

	app::root_menu	root_menu_;
}

core_t& get_core()
{
	return core_;
}

void select_scene(uint32_t idx)
{
	switch(idx) {
	case 0:
		scene_.change(root_menu_);
		break;
	default:
		break;
	}
}

extern "C" {

	void sci_putch(char ch)
	{
		core_.sci1_.putch(ch);
	}

	void sci_puts(const char* str)
	{
		core_.sci1_.puts(str);
	}

	char sci_getch(void)
	{
		return core_.sci1_.getch();
	}

	uint16_t sci_length()
	{
		return core_.sci1_.recv_length();
	}

	DSTATUS disk_initialize(BYTE drv) {
		return core_.sdc_.at_mmc().disk_initialize(drv);
	}

	DSTATUS disk_status(BYTE drv) {
		return core_.sdc_.at_mmc().disk_status(drv);
	}

	DRESULT disk_read(BYTE drv, BYTE* buff, DWORD sector, UINT count) {
		return core_.sdc_.at_mmc().disk_read(drv, buff, sector, count);
	}

	DRESULT disk_write(BYTE drv, const BYTE* buff, DWORD sector, UINT count) {
		return core_.sdc_.at_mmc().disk_write(drv, buff, sector, count);
	}

	DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void* buff) {
		return core_.sdc_.at_mmc().disk_ioctl(drv, ctrl, buff);
	}

	DWORD get_fattime(void) {
		time_t t = 0;
#if 0
		if(!rtc_.get_time(t)) {
			utils::format("Stall RTC read (%d)\n") % static_cast<uint32_t>(i2c_.get_last_error());
		}
#endif
		return utils::str::get_fattime(t);
	}
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	core_.init();

	core_.init_device();

	utils::format("RX24T Data Logger\n");
	core_.command_.set_prompt("# ");

	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	LED::DIR = 1;

	select_scene(0);

	uint32_t cnt = 0;
	uint8_t nn = 0;
	while(1) {
		core_.cmt_.sync();

		core_.adc_io_.scan();
		core_.adc_io_.sync();

		// ４つのスイッチ判定（排他的）
		auto val = core_.adc_io_.get(core_t::ADC::analog::AIN000);
		val += 512;  // 閾値のオフセット（4096 / 4(SWITCH) / 2）
		val /= 1024;  // デコード（4096 / 4(SWITCH）

		core_t::switch_bits tmp;
		if(val < 4) {
			tmp.set(static_cast<core_t::SWITCH>(val));
		}
		core_.switch_man_.service(tmp);

		auto f = core_.nmea_.service();
		if(f) {
			utils::format("%s: ") % core_.nmea_.get_satellite();
			utils::format("D/T: %s %s, ") % core_.nmea_.get_date() % core_.nmea_.get_time();
			utils::format("Lat: %s, ") % core_.nmea_.get_lat();
			utils::format("Lon: %s, ") % core_.nmea_.get_lon();
			utils::format("Alt: %s [%s]\n") % core_.nmea_.get_altitude() % core_.nmea_.get_altitude_unit();
		};

		core_.sdc_.service();


		if(core_.switch_man_.get_positive().get(core_t::SWITCH::UP)) {
			core_.menu_.focus_prev();
		}
		if(core_.switch_man_.get_positive().get(core_t::SWITCH::DOWN)) {
			core_.menu_.focus_next();
		}

		// LCD 用サービス
		if(nn == 0) {  // フレームバッファ消去
			core_.bitmap_.clear(0);
			++nn;
		} else if(nn == 1) {  // 描画
			// シーン・タスク
			scene_.service();

			++nn;
		} else if(nn >= 2) {  // 転送
			core_.spi_.start(8000000, core_t::SPI::PHASE::TYPE4);  // LCD 用速度と設定
			core_.lcd_.copy(core_.bitmap_.fb(), core_.bitmap_.page_num());
			core_.sdc_.setup_speed();  //  SDC 用速度と設定
			nn = 0;
		}

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		LED::P = (cnt < 10) ? 0 : 1;
	}
}
