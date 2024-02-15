//=====================================================================//
/*! @file
    @brief  SD-CARD サンプル @n
			RX64M, RX71M: @n
					12MHz のベースクロックを使用する @n
			　　　　P07 ピンにLEDを接続する @n
			RX64M GR-KAEDE: @n
					内蔵 SD カードインターフェースの RSPI は、デバッガー E1 @n
					と共有されており、ポートがプルダウンされています。@n
					SD カードの初期化時、プルアップが必要なので、そ対策が必要。@n
					※ main 関数の始めで、その対策をしています。@n
			RX65N (Renesas Envision kit RX65N): @n
					12MHz のベースクロックを使用する @n
			　　　　P70 に接続された LED を利用する @n
			RX24T: @n
					10MHz のベースクロックを使用する @n
			　　　　P00 ピンにLEDを接続する @n
			RX72N (Renesas Envision kit RX72N): @n
					16MHz のベースクロックを使用する @n
					P40 に接続された LED を利用する
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/fixed_fifo.hpp"
#include "common/sci_io.hpp"
#include "common/cmt_mgr.hpp"

#include "common/format.hpp"
#include "common/input.hpp"
#include "common/string_utils.hpp"

#include "common/spi_io2.hpp"
#include "common/rspi_io.hpp"
#include "common/command.hpp"
#include "common/shell.hpp"

#include "common/iica_io.hpp"
#include "chip/DS3231.hpp"

#include "graphics/font8x16.hpp"
#include "graphics/kfont.hpp"
#include "graphics/graphics.hpp"
#include "graphics/simple_filer.hpp"

#include "common/sci_i2c_io.hpp"
#include "chip/FT5206.hpp"

namespace {

#if defined(SIG_RX24T)
	static const char* system_str_ = { "RX24T" };
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::SCI1 SCI_CH;
	// SDCARD 制御リソース
#if 1
	// RSPI0 定義
	typedef device::rspi_io<device::RSPI0> SDC_SPI;
#else
	// Soft SPI 定義
	typedef device::PORT<device::PORT2, device::bitpos::B2> MISO;
	typedef device::PORT<device::PORT2, device::bitpos::B3> MOSI;
	typedef device::PORT<device::PORT2, device::bitpos::B4> SPCK;
	typedef device::spi_io2<MISO, MOSI, SPCK> SDC_SPI;
#endif
	SDC_SPI	sdc_spi_;
	typedef device::PORT<device::PORT6, device::bitpos::B5> SDC_SELECT;	///< カード選択信号
	typedef device::PORT<device::PORT6, device::bitpos::B4, 0> SDC_POWER;	///< カード電源制御
	typedef device::PORT<device::PORT6, device::bitpos::B3> SDC_DETECT;	///< カード検出
	typedef device::NULL_PORT SDC_WPRT;  ///< カード書き込み禁止ポート設定
	typedef fatfs::mmc_io<SDC_SPI, SDC_SELECT, SDC_POWER, SDC_DETECT, SDC_WPRT> SDC;
	SDC		sdc_(sdc_spi_, 20'000'000);

	typedef device::iica_io<device::RIIC0> I2C;
	typedef chip::DS3231<I2C> RTC;
	#define ENABLE_I2C_RTC

#elif defined(SIG_RX64M)
	// GR-KAEDE の場合有効にする。
//	#define GR_KAEDE

	#ifdef GR_KAEDE
	static const char* system_str_ = { "RX64M GR-KAEDE" };
	typedef device::PORT<device::PORT0, device::bitpos::B3> LED;
//	typedef device::PORT<device::PORT0, device::bitpos::B2> LED1;
//	typedef device::PORT<device::PORTC, device::bitpos::B0> LED2;
//	typedef device::PORT<device::PORTC, device::bitpos::B1> LED3;
	typedef device::SCI7 SCI_CH;

    typedef device::rspi_io<device::RSPI> SDC_SPI;
    typedef device::PORT<device::PORTC, device::bitpos::B4> SDC_SELECT; ///< カード選択信号
    typedef device::NULL_PORT  SDC_POWER;   ///< カード電源制御（常に電源ＯＮ）
    typedef device::PORT<device::PORTB, device::bitpos::B7> SDC_DETECT; ///< カード検出
	typedef device::NULL_PORT SDC_WPRT;  ///< カード書き込み禁止

	#else
	static const char* system_str_ = { "RX64M DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;

	// SDCARD 制御リソース（ソフト SPI）
	typedef device::PORT<device::PORTC, device::bitpos::B3> MISO;
	typedef device::PORT<device::PORT7, device::bitpos::B6> MOSI;
	typedef device::PORT<device::PORT7, device::bitpos::B7> SPCK;
	typedef device::spi_io2<MISO, MOSI, SPCK> SDC_SPI;  ///< Soft SPI 定義

	typedef device::PORT<device::PORTC, device::bitpos::B2> SDC_SELECT;	///< カード選択信号
	typedef device::PORT<device::PORT8, device::bitpos::B2, 0> SDC_POWER;	///< カード電源制御
	typedef device::PORT<device::PORT8, device::bitpos::B1> SDC_DETECT;	///< カード検出
	typedef device::NULL_PORT SDC_WPRT;  ///< カード書き込み禁止
	#endif

	#define USE_SPI

	SDC_SPI	sdc_spi_;
	typedef fatfs::mmc_io<SDC_SPI, SDC_SELECT, SDC_POWER, SDC_DETECT, SDC_WPRT> SDC;
	SDC		sdc_(sdc_spi_, 20'000'000);

	// 内臓 RTC を有効
	#define ENABLE_RTC
	typedef utils::rtc_io RTC;

#elif defined(SIG_RX71M)

	static const char* system_str_ = { "RX71M" };
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;

#elif defined(SIG_RX65N)

	static const char* system_str_ = { "RX65N Envision Kit" };
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
	typedef device::SCI9 SCI_CH;
	typedef device::PORT<device::PORT6, device::bitpos::B4, 0> SDC_POWER;  ///< 「０」でＯＮ
	typedef device::NULL_PORT SDC_WPRT;  ///< カード書き込み禁止ポート設定
	typedef fatfs::sdhi_io<device::SDHI, SDC_POWER, SDC_WPRT, device::port_map::ORDER::THIRD> SDC;
	SDC		sdc_;

	#define TOUCH_FILER
	static const int16_t LCD_X = 480;
	static const int16_t LCD_Y = 272;
	static const auto PIX = graphics::pixel::TYPE::RGB565;
	typedef device::PORT<device::PORT6, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B6> LCD_LIGHT;
	static const uint32_t LCD_ORG = 0x0000'0100;

	typedef utils::fixed_fifo<uint8_t, 64> RB64;
	typedef utils::fixed_fifo<uint8_t, 64> SB64;
	typedef device::PORT<device::PORT0, device::bitpos::B7> FT5206_RESET;
	typedef device::sci_i2c_io<device::SCI6, RB64, SB64, device::port_map::ORDER::FIRST> FT5206_I2C;

#elif defined(SIG_RX72N)

	static const char* system_str_ = { "RX72N Envision Kit" };
	typedef device::PORT<device::PORT4, device::bitpos::B0> LED;
	typedef device::SCI2 SCI_CH;
	typedef device::PORT<device::PORT4, device::bitpos::B2> SDC_POWER;
	typedef device::NULL_PORT SDC_WPRT;  ///< カード書き込み禁止ポート設定
	typedef fatfs::sdhi_io<device::SDHI, SDC_POWER, SDC_WPRT, device::port_map::ORDER::THIRD> SDC;
	SDC		sdc_;

	#define TOUCH_FILER
	static const int16_t LCD_X = 480;
	static const int16_t LCD_Y = 272;
	static const auto PIX = graphics::pixel::TYPE::RGB565;
	typedef device::PORT<device::PORTB, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B7> LCD_LIGHT;
	static const uint32_t LCD_ORG = 0x0080'0000;

	typedef utils::fixed_fifo<uint8_t, 64> RB64;
	typedef utils::fixed_fifo<uint8_t, 64> SB64;
	typedef device::PORT<device::PORT6, device::bitpos::B6> FT5206_RESET;
	typedef device::sci_i2c_io<device::SCI6, RB64, SB64, device::port_map::ORDER::SECOND> FT5206_I2C;

#elif defined(SIG_RX72T)
	// RSPI I/F
	static const char* system_str_ = { "RX72T" };
	typedef device::PORT<device::PORT0, device::bitpos::B1> LED;
	typedef device::SCI1 SCI_CH;

#if 0
	// SDCARD 制御リソース（ソフト SPI）
	typedef device::PORT<device::PORT2, device::bitpos::B2> MISO;
	typedef device::PORT<device::PORT2, device::bitpos::B1> MOSI;
	typedef device::PORT<device::PORT2, device::bitpos::B0> SPCK;
	typedef device::spi_io2<MISO, MOSI, SPCK> SDC_SPI;  ///< Soft SPI 定義
#else
	// RSPI 定義、FIRST: P20:RSPCK, P21:MOSI, P22:MISO
	typedef device::rspi_io<device::RSPI0> SDC_SPI;
#endif

	SDC_SPI	sdc_spi_;
	typedef device::PORT<device::PORT3, device::bitpos::B0> SDC_SELECT;			///< カード選択信号
	typedef device::PORT<device::PORTA, device::bitpos::B2> SDC_POWER;			///< カード電源制御 MIC2076-1YM (ACTIVE-HIGH)
	typedef device::PORT<device::PORTB, device::bitpos::B4, 0> SDC_DETECT;		///< カード検出（ACTIVE-LOW）
	typedef device::NULL_PORT SDC_WPRT;											///< カード書き込み禁止ポート設定（無効）
	typedef fatfs::mmc_io<SDC_SPI, SDC_SELECT, SDC_POWER, SDC_DETECT, SDC_WPRT> SDC;
	SDC		sdc_(sdc_spi_, 20'000'000);

	#define USE_SPI

	#define ENABLE_I2C_RTC
	typedef device::iica_io<device::RIIC0> I2C;
	typedef chip::DS3231<I2C> RTC;
#endif

	typedef utils::fixed_fifo<char, 512> RXB;  // RX (RECV) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (SEND) バッファの定義

	typedef device::sci_io<SCI_CH, RXB, TXB> SCI;
	SCI		sci_;

	static const uint32_t CMT_FREQ = 1000;  ///< 計測用タイマー分解能

	class cmt_task {
		volatile uint32_t	cnt_;
		volatile uint32_t	div_;
		volatile uint32_t	tdiv_;
		volatile uint32_t	time_;

	public:
		cmt_task() : cnt_(0), div_(0), tdiv_(0), time_(0) { }

		void sync_100hz() noexcept {
			auto tmp = div_;
			while(tmp == div_) ;
		}

		void set_time(uint32_t time) { time_ = time; }
		auto get_time() const noexcept { return time_; }

		void operator() () noexcept {
			++cnt_;
			if(cnt_ >= 10) {
				cnt_ = 0;
				++div_;
			}
			++tdiv_;
			if(tdiv_ > CMT_FREQ) {
				++time_;
				tdiv_ = 0;
			}
		}
	};

	typedef device::cmt_mgr<device::CMT0, cmt_task> CMT;
	CMT		cmt_;

	typedef utils::command<256> CMD;
	CMD		cmd_;

	typedef utils::shell<CMD> SHELL;
	SHELL	shell_(cmd_);

#ifdef ENABLE_RTC
	RTC		rtc_;
#else
#ifndef ENABLE_I2C_RTC
	class MYRTC {
	public:
		bool start() noexcept { return true; }
		bool set_time(time_t t) { cmt_.at_func().set_time(t); return true; }
		bool get_time(time_t& t) {
			t = cmt_.at_func().get_time();
			return true;
		}
	};
	MYRTC	rtc_;
#endif
#endif

#ifdef ENABLE_I2C_RTC
	I2C		i2c_;
	RTC		rtc_(i2c_);
#endif

// Renesas Envision Kit Touch Screen 定義 (RX65N/RX72N Envision Kit)
#ifdef TOUCH_FILER
	typedef device::glcdc_mgr<device::GLCDC, LCD_X, LCD_Y, PIX> GLCDC;

	typedef graphics::font8x16 AFONT;
// 	for cash into SD card /kfont16.bin
//	typedef graphics::kfont<16, 16, 64> KFONT;
	typedef graphics::kfont<16, 16> KFONT;
	typedef graphics::font<AFONT, KFONT> FONT;

	// ハードウェアレンダラー
//	typedef device::drw2d_mgr<GLCDC, FONT> RENDER;
	// ソフトウェアーレンダラー
	typedef graphics::render<GLCDC, FONT> RENDER;
	// 標準カラーインスタンス
	typedef graphics::def_color DEF_COLOR;

	GLCDC	glcdc_(nullptr, reinterpret_cast<void*>(LCD_ORG));
	AFONT	afont_;
	KFONT	kfont_;
	FONT	font_(afont_, kfont_);
	RENDER	render_(glcdc_, font_);

	// ファイラー定義
	typedef gui::simple_filer_base FILER_BASE;
	typedef gui::simple_filer<RENDER> FILER;
	FILER	filer_(render_, true);  // ３本タッチオープンを有効にする場合第二引数「true」

	// タッチパネル定義
	FT5206_I2C	ft5206_i2c_;
	typedef chip::FT5206<FT5206_I2C> TOUCH;
	TOUCH	touch_(ft5206_i2c_);
#endif

	// ファイル書き込みテスト
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
			LED::P = !LED::P();
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


	// ファイル読出しテスト
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
			LED::P = !LED::P();
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

	// syscalls.c から呼ばれる、標準出力（stdout, stderr）
	void sci_putch(char ch)
	{
		sci_.putch(ch);
	}

	void sci_puts(const char* str)
	{
		sci_.puts(str);
	}

	// syscalls.c から呼ばれる、標準入力（stdin）
	char sci_getch(void)
	{
		return sci_.getch();
	}

	uint16_t sci_length()
	{
		return sci_.recv_length();
	}

	// FatFs から呼ばれるファイル操作関数
	DSTATUS disk_initialize(BYTE drv) {
		return sdc_.disk_initialize(drv);
	}

	DSTATUS disk_status(BYTE drv) {
		return sdc_.disk_status(drv);
	}

	DRESULT disk_read(BYTE drv, BYTE* buff, DWORD sector, UINT count) {
		return sdc_.disk_read(drv, buff, sector, count);
	}

	DRESULT disk_write(BYTE drv, const BYTE* buff, DWORD sector, UINT count) {
		return sdc_.disk_write(drv, buff, sector, count);
	}

	DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void* buff) {
		return sdc_.disk_ioctl(drv, ctrl, buff);
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
}


int main(int argc, char** argv);

int main(int argc, char** argv)
{
#ifdef GR_KAEDE
    // GR-KAEDE の RSPI 端子のプルダウン問題回避
    // ※PC3 から、PC7 へ １K オームの抵抗を接続しておきます。
	// それを利用して、プルアップの状態にします。
    device::PORTC::PDR.B3 = 1; // output
    device::PORTC::PODR.B3 = 1;
#endif

	SYSTEM_IO::boost_master_clock();

	{  // タイマー設定
		auto intr = device::ICU::LEVEL::_4;
		cmt_.start(CMT_FREQ, intr);
	}

	{  // SCI の開始
		auto intr = device::ICU::LEVEL::_2;
		uint32_t baud = 115200;  // ボーレート
		sci_.start(baud, intr);
	}

	auto clk = device::clock_profile::ICLK / 1'000'000;
	utils::format("Start SD-CARD Access sample for '%s' %d[MHz]\n") % system_str_ % clk;

#ifdef USE_SPI
	utils::format("SPI Set  Speed: %u [Hz]\n") % sdc_spi_.get_speed();
	utils::format("SPI Real Speed: %u [Hz]\n") % sdc_spi_.get_speed(true);
#endif

#ifdef TOUCH_FILER
	{  // GLCDC の初期化
		LCD_DISP::DIR  = 1;
		LCD_LIGHT::DIR = 1;
		LCD_DISP::P  = 0;  // DISP Disable
		LCD_LIGHT::P = 0;  // BackLight Disable (No PWM)
		if(glcdc_.start(device::ICU::LEVEL::_2)) {
			utils::format("Start GLCDC\n");
			LCD_DISP::P  = 1;  // DISP Enable
			LCD_LIGHT::P = 1;  // BackLight Enable (No PWM)
			if(!glcdc_.control(GLCDC::CONTROL_CMD::START_DISPLAY)) {
				utils::format("GLCDC ctrl fail...\n");
			}
		} else {
			utils::format("GLCDC Fail\n");
		}
	}

	{  // レンダラー初期化
		auto ver = render_.get_version();
		utils::format("DRW2D Version: %04X\n") % ver;
//		if(render_.start(device::ICU::LEVEL::_2)) {
		if(render_.start()) {
			utils::format("Start DRW2D\n");
		} else {
			utils::format("DRW2D Fail\n");
		}
	}

	{  // FT5206 touch screen controller
		TOUCH::reset<FT5206_RESET>();
		auto intr_lvl = device::ICU::LEVEL::_1;
		if(!ft5206_i2c_.start(FT5206_I2C::MODE::MASTER, FT5206_I2C::SPEED::STANDARD, intr_lvl)) {
			utils::format("FT5206 I2C Start Fail...\n");
		}
		if(!touch_.start()) {
			utils::format("FT5206 Start Fail...\n");
		}
	}
#endif

#ifdef ENABLE_RTC
	{  // RTC の開始
		rtc_.start();
	}
#endif

#ifdef ENABLE_I2C_RTC
	{  // I2C-RTC の開始
		auto intr_level = device::ICU::LEVEL::NONE;
		if(!i2c_.start(I2C::MODE::MASTER, I2C::SPEED::FAST, intr_level)) {
			utils::format("IICA start error (%d)\n") % static_cast<uint32_t>(i2c_.get_last_error());
		}
		// DS3231(RTC) の開始
		if(!rtc_.start()) {
			utils::format("Stall RTC start (%d)\n") % static_cast<uint32_t>(i2c_.get_last_error());
		}
	}
#endif

	cmd_.set_prompt("# ");

	LED::DIR = 1;

	uint8_t cnt = 0;
	while(1) {

		bool mount = sdc_.service();

#ifdef TOUCH_FILER
		render_.sync_frame();
		touch_.update();
		{
			uint32_t ctrl = 0;
			if(mount) {
				FILER_BASE::set(FILER_BASE::ctrl::MOUNT, ctrl);
			}
			auto tnum = touch_.get_touch_num();
			const auto& t = touch_.get_touch_pos(0);
			filer_.set_touch(tnum, t.pos); 
			char tmp[256];
			tmp[0] = 0;
			auto fst = filer_.update(ctrl, tmp, sizeof(tmp));
			if(fst == FILER_BASE::status::FILE) {
				utils::format("Select file: '%s'\n") % tmp;
			}
		}
#else
		cmt_.at_func().sync_100hz();
#endif
		command_();

		++cnt;
		if(cnt >= 50) {
			cnt = 0;
		}
		if(cnt < 25) {
			LED::P = 0;
		} else {
			LED::P = 1;
		}
	}
}
