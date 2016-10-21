//=====================================================================//
/*! @file
    @brief  RX24T ファースト・サンプル @n
			・P00(4) ピンに赤色LED（VF:1.9V）を吸い込みで接続する
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/cmt_io.hpp"
#include "common/sci_io.hpp"
#include "common/fifo.hpp"
#include "common/format.hpp"
#include "common/iica_io.hpp"

#include "chip/DS3231.hpp"

namespace {

	class cmt_task {
	public:
		void operator() () {
		}
	};

	device::cmt_io<device::CMT0, cmt_task>  cmt_;

	typedef utils::fifo<uint8_t, 128> buffer;
	device::sci_io<device::SCI1, buffer, buffer> sci_;

	typedef device::iica_io<device::RIIC0> I2C;
	I2C i2c_;

	chip::DS3231<I2C> rtc_(i2c_);


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
}

extern "C" {
	void sci_putch(char ch)
	{
		sci_.putch(ch);
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

	// タイマー設定（６０Ｈｚ）
	cmt_.set_clock(F_PCKB);
	uint8_t cmt_irq_level = 4;
	cmt_.start(60, cmt_irq_level);

	// SCI 設定
	static const uint8_t sci_level = 2;
	sci_.start(115200, sci_level);

	// IICA(I2C) の開始
	{
		uint8_t intr_level = 0;
		if(!i2c_.start(I2C::speed::fast, intr_level)) {
//		if(!iica0_.start(IICA::speed::standard, intr_level)) {
			utils::format("IICA start error (%d)\n") % static_cast<uint32_t>(i2c_.get_last_error());
		}
	}

	utils::format("RX24T start\n");

	device::PORT0::PDR.B0 = 1; // output

	uint32_t cnt = 0;
	uint32_t n = 0;
	while(1) {
		cmt_.sync();

		if(sci_.length()) {
			auto ch = sci_.getch();
			sci_.putch(ch);
		}

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		device::PORT0::PODR.B0 = (cnt < 10) ? 0 : 1;

		if((n % 60) == 0) {
			time_t t = get_time_();
			if(t != 0) {
				disp_time_(t);
			}
//			utils::format("%d\n") % (n / 60);
		}
		++n;
	}
}
