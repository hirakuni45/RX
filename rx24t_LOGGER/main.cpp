//=====================================================================//
/*! @file
    @brief  RX24T データ・ロガー @n
			・P00(4) ピンに赤色LED（VF:1.9V）を吸い込みで接続する @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/cmt_io.hpp"
#include "common/fifo.hpp"
#include "common/sci_io.hpp"
#include "common/rspi_io.hpp"
#include "common/sdc_io.hpp"
#include "chip/ST7565.hpp"
#include "common/monograph.hpp"
#include "common/font6x12.hpp"

#define RTC

#ifdef RTC
#include "common/iica_io.hpp"
#include "chip/DS3231.hpp"
#endif

#include "common/format.hpp"
#include "common/command.hpp"

#include "common/menu.hpp"
#include "common/scene.hpp"

#include "common/adc_io.hpp"
#include "common/bitset.hpp"
#include "common/switch_man.hpp"


namespace {

	class cmt_task {
	public:
		void operator() () {
		}
	};

	device::cmt_io<device::CMT0, cmt_task>  cmt_;

	typedef utils::fifo<uint8_t, 256> buffer;
	device::sci_io<device::SCI1, buffer, buffer> sci1_;

#ifdef RTC
	typedef device::iica_io<device::RIIC0> I2C;
	I2C i2c_;

	chip::DS3231<I2C> rtc_(i2c_);
#endif

	// SPI 定義（RSPI0）
	typedef device::rspi_io<device::RSPI0> SPI;
	SPI spi_;

	typedef device::PORT<device::PORT6, device::bitpos::B5> SDC_SELECT;	///< カード選択信号
	typedef device::PORT<device::PORT6, device::bitpos::B4> SDC_POWER;	///< カード電源制御
	typedef device::PORT<device::PORT6, device::bitpos::B3> SDC_DETECT;	///< カード検出

	utils::sdc_io<SPI, SDC_SELECT, SDC_POWER, SDC_DETECT> sdc_(spi_);

	typedef device::PORT<device::PORT6, device::bitpos::B1> LCD_SEL;	///< LCD 選択信号
	typedef device::PORT<device::PORT6, device::bitpos::B2> LCD_A0;	    ///< LCD レジスター選択

	chip::ST7565<SPI, LCD_SEL, LCD_A0> lcd_(spi_);

	// モノクロ・グラフィックス
	graphics::kfont_null kfont_;
	typedef graphics::font6x12 AFONT;
	typedef graphics::monograph<128, 64, AFONT> BITMAP;
	BITMAP bitmap_(kfont_);

	typedef graphics::menu<BITMAP, 5> MENU;
	MENU menu_(bitmap_);

	utils::scene<MENU> scene_(menu_);

	uint32_t adc_cnt_;

	class adc_task {
	public:
		void operator() () {
			++adc_cnt_;
		}
	};

	typedef device::S12AD adc;
	typedef device::adc_io<adc, adc_task> adc_io;
	adc_io adc_io_;

	enum class SWITCH : uint8_t {
		RIGHT,
		UP,
		DOWN,
		LEFT,
		A,
		B
	};

	typedef utils::bitset<uint32_t, SWITCH> switch_bits;
	utils::switch_man<switch_bits> switch_man_;

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

	void date_()
	{
		time_t t = 0;

		if(!rtc_.get_time(t)) {
			utils::format("Stall RTC read (%d)\n") % static_cast<uint32_t>(i2c_.get_last_error());
		}
		disp_time_(t);
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
		sci1_.putch(ch);
	}

	void sci_puts(const char* str)
	{
		sci1_.puts(str);
	}

	char sci_getch(void)
	{
		return sci1_.getch();
	}

	uint16_t sci_length()
	{
		return sci1_.recv_length();
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
			utils::format("Stall RTC read (%d)\n") % static_cast<uint32_t>(i2c_.get_last_error());
		}
		return utils::str::get_fattime(t);
#else
		return 0;
#endif
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

	{  // タイマー設定（１００Ｈｚ）
		uint8_t intr_level = 4;
		cmt_.start(100, intr_level);
	}

	{  // SCI1 設定
		uint8_t intr_level = 2;
		sci1_.start(115200, intr_level);
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
	sdc_.initialize();

	utils::format("RX24T Data Logger\n");

#ifdef RTC
	// DS3231(RTC) の開始
	if(!rtc_.start()) {
		utils::format("Stall RTC start (%d)\n") % static_cast<uint32_t>(i2c_.get_last_error());
	}
#endif

	// LCD 開始
	{
		spi_.start(8000000, SPI::PHASE::TYPE4);  // LCD 用設定、速度
		bool comrvs = true;
		lcd_.start(0x10, comrvs);
		bitmap_.clear(0);

		menu_.set_space(4);
		menu_.add(MENU::type::PROP, "Logging");
		menu_.add(MENU::type::PROP, "Recall");
		menu_.add(MENU::type::PROP, "Setup");
	}

	// A/D 設定
	{
		uint8_t intr_level = 1;
		if(!adc_io_.start(adc::analog::AIN000, intr_level)) {
			utils::format("A/D start fail AIN000\n");
		}
		if(!adc_io_.start(adc::analog::AIN001, intr_level)) {
			utils::format("A/D start fail AIN001\n");
		}
	}

	command_.set_prompt("# ");

	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;

	LED::DIR = 1;

	uint32_t cnt = 0;
	uint8_t nn = 0;
	while(1) {
		cmt_.sync();

		adc_io_.scan();
		adc_io_.sync();

		// ４つのスイッチ判定（排他的）
		auto val = adc_io_.get(adc::analog::AIN000);
		val += 512;  // 閾値のオフセット（4096 / 4(SWITCH) / 2）
		val /= 1024;  // デコード（4096 / 4(SWITCH）

		switch_bits tmp;
		if(val < 4) {
			tmp.set(static_cast<SWITCH>(val));
		}
		switch_man_.service(tmp);

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
				} else if(command_.cmp_word(0, "next")) {
					menu_.focus_next();
					f = true;
				} else if(command_.cmp_word(0, "prev")) {
					menu_.focus_prev();
					f = true;
				} else if(command_.cmp_word(0, "help")) { // help
					utils::format("dir [name]\n");
					utils::format("cd [directory-name]\n");
					utils::format("pwd\n");
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


		if(switch_man_.get_positive().get(SWITCH::UP)) {
			menu_.focus_prev();
		}
		if(switch_man_.get_positive().get(SWITCH::DOWN)) {
			menu_.focus_next();
		}
			

		// LCD 用サービス
		if(nn == 0) {  // フレームバッファ消去
			bitmap_.clear(0);
			++nn;
		} else if(nn == 1) {  // 描画
			bitmap_.frame(0, 0, 128, 64, 1);
			menu_.render();
			++nn;
		} else if(nn >= 2) {  // 転送
			spi_.start(8000000, SPI::PHASE::TYPE4);  // LCD 用速度と設定
			lcd_.copy(bitmap_.fb(), bitmap_.page_num());
			sdc_.setup_speed();  //  SDC 用速度と設定
			nn = 0;
		}

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		LED::P = (cnt < 10) ? 0 : 1;
	}
}
