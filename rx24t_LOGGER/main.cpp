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

namespace {

	main_t main_;

	utils::scene<main_t> scene_(main_);

}

extern "C" {

	void sci_putch(char ch)
	{
		main_.sci1_.putch(ch);
	}

	void sci_puts(const char* str)
	{
		main_.sci1_.puts(str);
	}

	char sci_getch(void)
	{
		return main_.sci1_.getch();
	}

	uint16_t sci_length()
	{
		return main_.sci1_.recv_length();
	}

	DSTATUS disk_initialize(BYTE drv) {
		return main_.sdc_.at_mmc().disk_initialize(drv);
	}

	DSTATUS disk_status(BYTE drv) {
		return main_.sdc_.at_mmc().disk_status(drv);
	}

	DRESULT disk_read(BYTE drv, BYTE* buff, DWORD sector, UINT count) {
		return main_.sdc_.at_mmc().disk_read(drv, buff, sector, count);
	}

	DRESULT disk_write(BYTE drv, const BYTE* buff, DWORD sector, UINT count) {
		return main_.sdc_.at_mmc().disk_write(drv, buff, sector, count);
	}

	DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void* buff) {
		return main_.sdc_.at_mmc().disk_ioctl(drv, ctrl, buff);
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
	main_.init();

	main_.init_device();

	utils::format("RX24T Data Logger\n");

	main_.command_.set_prompt("# ");

	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;

	LED::DIR = 1;

	uint32_t cnt = 0;
	uint8_t nn = 0;
	while(1) {
		main_.cmt_.sync();

		main_.adc_io_.scan();
		main_.adc_io_.sync();

		// ４つのスイッチ判定（排他的）
		auto val = main_.adc_io_.get(main_t::ADC::analog::AIN000);
		val += 512;  // 閾値のオフセット（4096 / 4(SWITCH) / 2）
		val /= 1024;  // デコード（4096 / 4(SWITCH）

		main_t::switch_bits tmp;
		if(val < 4) {
			tmp.set(static_cast<main_t::SWITCH>(val));
		}
		main_.switch_man_.service(tmp);

		auto f = main_.nmea_.service();
		if(f) {
			utils::format("%s: ") % main_.nmea_.get_satellite();
			utils::format("D/T: %s %s, ") % main_.nmea_.get_date() % main_.nmea_.get_time();
			utils::format("Lat: %s, ") % main_.nmea_.get_lat();
			utils::format("Lon: %s, ") % main_.nmea_.get_lon();
			utils::format("Alt: %s [%s]\n") % main_.nmea_.get_altitude() % main_.nmea_.get_altitude_unit();
		};

		main_.sdc_.service();

		if(main_.switch_man_.get_positive().get(main_t::SWITCH::UP)) {
			main_.menu_.focus_prev();
		}
		if(main_.switch_man_.get_positive().get(main_t::SWITCH::DOWN)) {
			main_.menu_.focus_next();
		}
			

		// LCD 用サービス
		if(nn == 0) {  // フレームバッファ消去
			main_.bitmap_.clear(0);
			++nn;
		} else if(nn == 1) {  // 描画
			main_.bitmap_.frame(0, 0, 128, 64, 1);
			main_.menu_.render();
			++nn;
		} else if(nn >= 2) {  // 転送
			main_.spi_.start(8000000, main_t::SPI::PHASE::TYPE4);  // LCD 用速度と設定
			main_.lcd_.copy(main_.bitmap_.fb(), main_.bitmap_.page_num());
			main_.sdc_.setup_speed();  //  SDC 用速度と設定
			nn = 0;
		}

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		LED::P = (cnt < 10) ? 0 : 1;
	}
}
