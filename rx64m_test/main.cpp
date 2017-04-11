//=====================================================================//
/*! @file
    @brief  SEEDA03 (RX64M) メイン @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "main.hpp"
#include "core.hpp"
#include "tools.hpp"
#include "net.hpp"

namespace seeda {

	core 	core_;
	tools	tools_;
	net		net_;

	typedef utils::rtc_io RTC;
	RTC		rtc_;


	//-----------------------------------------------------------------//
	/*!
		@brief  GMT 時間の設定
		@param[in]	t	GMT 時間
	*/
	//-----------------------------------------------------------------//
	void set_time(time_t t)
	{
		if(!rtc_.set_time(t)) {
			utils::format("Stall RTC write...\n");
		}
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  GMT 時間の取得
		@return GMT 時間
	*/
	//-----------------------------------------------------------------//
	time_t get_time()
	{
		time_t t = 0;
		rtc_.get_time(t);
		return t;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  時間の表示
		@param[in]	t		時間
		@param[in]	dst		出力文字列
		@param[in]	size	文字列の大きさ
	*/
	//-----------------------------------------------------------------//
	void disp_time(time_t t, char* dst, uint32_t size)
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


	//-----------------------------------------------------------------//
	/*!
		@brief  A/D 変換値の取得
		@param[in]	ch	チャネル（０～７）
		@return A/D 変換値
	*/
	//-----------------------------------------------------------------//
	uint16_t get_analog(uint8_t ch)
	{
		return tools_.get_analog(ch);
	}
}

extern "C" {

	void sci_putch(char ch)
	{
		seeda::core_.sci_.putch(ch);
	}

	void sci_puts(const char* s)
	{
		seeda::core_.sci_.puts(s);
	}

	char sci_getch(void)
	{
		return seeda::core_.sci_.getch();
	}

	uint16_t sci_length(void)
	{
		return seeda::core_.sci_.recv_length();
	}


	DSTATUS disk_initialize(BYTE drv) {
		return seeda::tools_.disk_initialize(drv);
	}

	DSTATUS disk_status(BYTE drv) {
		return seeda::tools_.disk_status(drv);
	}

	DRESULT disk_read(BYTE drv, BYTE* buff, DWORD sector, UINT count) {
		return seeda::tools_.disk_read(drv, buff, sector, count);
	}

	DRESULT disk_write(BYTE drv, const BYTE* buff, DWORD sector, UINT count) {
		return seeda::tools_.disk_write(drv, buff, sector, count);
	}

	DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void* buff) {
		return seeda::tools_.disk_ioctl(drv, ctrl, buff);
	}


	DWORD get_fattime(void) {
		auto t = seeda::get_time();
		return utils::str::get_fattime(t);
	}

	void utf8_to_sjis(const char* src, char* dst) {
		utils::str::utf8_to_sjis(src, dst);
	}

	unsigned long millis(void)
	{
		return seeda::core_.cmt0_.at_task().get_millis();
	}

	void delay(unsigned long ms)
	{
		seeda::core_.cmt0_.at_task().set_delay(ms);
		while(seeda::core_.cmt0_.at_task().get_delay() != 0) ;		
	}

	void set_task_10ms(void (*task)(void)) {
		seeda::core_.cmt0_.at_task().set_task_10ms(task);
	}
}

namespace {

	void main_init_()
	{
		// RTC 設定
		seeda::rtc_.start();
	}
}


int main(int argc, char** argv);

int main(int argc, char** argv)
{
	using namespace seeda;

	device::PORT3::PCR.B5 = 1; // P35 pull-up

	device::SYSTEM::PRCR = 0xA50B;	// クロック、低消費電力、関係書き込み許可

	device::SYSTEM::MOSCWTCR = 9;	// 1ms wait
	// メインクロック強制発振とドライブ能力設定
	device::SYSTEM::MOFCR = device::SYSTEM::MOFCR.MODRV2.b(0b10)
						  | device::SYSTEM::MOFCR.MOFXIN.b(1);
	device::SYSTEM::MOSCCR.MOSTP = 0;		// メインクロック発振器動作
	while(device::SYSTEM::OSCOVFSR.MOOVF() == 0) asm("nop");

	// Base Clock 12.5MHz
	// PLLDIV: 1/1, STC: 16 倍(200MHz)
	device::SYSTEM::PLLCR = device::SYSTEM::PLLCR.PLIDIV.b(0) |
							device::SYSTEM::PLLCR.STC.b(0b011111);
	device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
	while(device::SYSTEM::OSCOVFSR.PLOVF() == 0) asm("nop");

	device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(2)		// 1/2 (200/4=50)
						  | device::SYSTEM::SCKCR.ICK.b(1)		// 1/2 (200/2=100)
						  | device::SYSTEM::SCKCR.BCK.b(2)		// 1/2 (200/4=50)
						  | device::SYSTEM::SCKCR.PCKA.b(1)		// 1/2 (200/2=100)
						  | device::SYSTEM::SCKCR.PCKB.b(2)		// 1/4 (200/4=50)
						  | device::SYSTEM::SCKCR.PCKC.b(2)		// 1/4 (200/4=50)
						  | device::SYSTEM::SCKCR.PCKD.b(2);	// 1/4 (200/4=50)
	device::SYSTEM::SCKCR2 = device::SYSTEM::SCKCR2.UCK.b(0b0011) | 1;  // USB Clock: 1/4 (200/4=50)
	device::SYSTEM::SCKCR3.CKSEL = 0b100;	///< PLL 選択

	main_init_();

	core_.init();
	tools_.init();

	core_.title();
	tools_.title();

	if(seeda::get_switch() == 3) {  // Ethernet 起動
		net_.init();
		net_.title();
	}

	device::PORT4::PDR.B7 = 1; // output

	uint32_t cnt = 0;
	while(1) {
		core_.sync();

		core_.service();
		tools_.service();

		if(seeda::get_switch() == 3) {  // Ethernet サービス
			net_.service();
		}

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		device::PORT4::PODR.B7 = (cnt < 10) ? 0 : 1;
	}
}
