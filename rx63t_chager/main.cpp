//=====================================================================//
/*! @file
    @brief  RX63T メイン
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/cmt_io.hpp"
#include "common/fifo.hpp"
#include "common/sci_io.hpp"
#include "common/ssd1306z_io.hpp"
#include "common/monograph.hpp"
#include "monitor.hpp"
#include "chager.hpp"
#include "common/format.hpp"

namespace {

	volatile uint8_t dummy_;

	//-----------------------------------------------------------------//
	/*!
		@brief	無駄ループによる時間待ち
		@param[in]	n	無駄ループ回数
	 */
	//-----------------------------------------------------------------//
	void wait_delay_(uint32_t n)
	{
		// とりあえず無駄ループ
		for(uint32_t i = 0; i < n; ++i) {
			asm("nop");
		}
	}

	utils::chager chager_;
	uint16_t timer_count_;
	volatile uint16_t timer_sync_;

	class cmt_task {
	public:
		void operator() () {
			chager_.service();

			++timer_count_;
			// 60Hz
			if(timer_count_ >= 781) {
				timer_count_ = 0;
				++timer_sync_;
			}
		}
	};

	device::cmt_io<device::CMT0, cmt_task>  cmt_;

	typedef utils::fifo<uint8_t, 128> buffer;
	device::sci_io<device::SCI1, buffer, buffer> sci_;

	utils::monitor		monitor_;

#if 0
	device::ssd1306z_io oled_;
	graphics::monograph	monog_;

	struct grout {
		void operator() (char ch) {
			monog_.draw_font(ch);
		}
	};
	typedef utils::basic_format<grout> gformat;
#endif

	void delay_10ms_(uint32_t n)
	{
		while(n > 0) {
			cmt_.sync();
			--n;
		}
	}

	void timer_60hz()
	{
		volatile uint16_t cnt = timer_sync_;
		while(cnt == timer_sync_) ;
	}
}

extern "C" {

	void sci_putch(char ch)
	{
		sci_.putch(ch);
	}


	void sci_puts(const char *str)
	{
		sci_.puts(str);
	}


	char sci_getch(void)
	{
		return sci_.getch();
	}

	uint16_t sci_length(void)
	{
		return sci_.recv_length();
	}
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	device::SYSTEM::PRCR = 0xa503;	// クロック、低消費電力、関係書き込み許可

	device::SYSTEM::MOSCWTCR.MSTS = 0b01101;	// 131072 サイクル待ち
	device::SYSTEM::MOSCCR.MOSTP = 0;			// メインクロック発振器動作
	dummy_ = device::SYSTEM::MOSCCR.MOSTP();
	device::SYSTEM::MOFCR.MOFXIN = 1;			// メインクロック強制発振
	dummy_ = device::SYSTEM::MOFCR.MOFXIN();
	wait_delay_(5000);

	device::SYSTEM::PLLCR.STC = 0xf;			// PLL 16 倍(192MHz)
	device::SYSTEM::PLLWTCR.PSTS = 0b01010;		// 131072 サイクル待ち
	device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
	wait_delay_(5000);

	device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(3)		// 1/8 (192/8=24)
						  | device::SYSTEM::SCKCR.ICK.b(1)		// 1/2 (192/2=96)
						  | device::SYSTEM::SCKCR.BCK.b(2)		// 1/4 (192/4=48)
						  | device::SYSTEM::SCKCR.PCKA.b(1)		// 1/2 (192/2=96)
						  | device::SYSTEM::SCKCR.PCKB.b(2)		// 1/4 (192/4=48)
						  | device::SYSTEM::SCKCR.PCKC.b(2)		// 1/4 (192/8=48)
						  | device::SYSTEM::SCKCR.PCKD.b(2);	// 1/4 (192/8=48)
	device::SYSTEM::SCKCR3.CKSEL = 4;	///< PLL 回路選択

	// Signal LED 出力設定
	device::PORTB::PDR.B7 = 1;	// PORTB:B7 output
	device::PORTB::PODR.B7 = 1;	// LED Off

	// Phot device 制御 PB0, PB1, PB2
	device::PORTB::PDR.B0 = 1;	// PORTB:B0 output
	device::PORTB::PODR.B0 = 1;	// B0 off
	device::PORTB::PDR.B1 = 1;	// PORTB:B1 output
	device::PORTB::PODR.B1 = 1;	// B0 off
	device::PORTB::PDR.B2 = 1;	// PORTB:B2 output
	device::PORTB::PODR.B2 = 1;	// B0 off

	// SCI1 の初期化
	static const uint8_t sci_irq_level = 1;
	sci_.start(sci_irq_level);
	sci_.start(115200);

	// チャージャー本体
	chager_.initialize();

	// タイマー設定
	uint8_t cmt_irq_level = 3;
	cmt_.start(46875, cmt_irq_level);

	cmt_.sync();

	monitor_.initialize();

///	device::SYSTEM::PRCR = 0xa500;	///< クロック、低消費電力、関係書き込み禁止

///	oled_.initialize();

	cmt_.sync();
//	int v = adc_inp_;
//	format("Input Voltage: %2.4:8y\n") % ((v * 25) >> 4);

	uint32_t led = 0;
	uint32_t cnt = 0;

	while(1) {
		timer_60hz();

		monitor_.service();

#if 0
		++cnt;
		if(cnt >= 50) {
			inp = static_cast<int>(adc_inp_);
			out0 = static_cast<int>(adc_out0_);
			cur0 = static_cast<int>(adc_cur0_);
			out1 = static_cast<int>(adc_out1_);
			cur1 = static_cast<int>(adc_cur1_);
			cnt = 0;
		}
#endif

#if 0
		monog_.at_font_posx() = 0;
		monog_.at_font_posy() = 0;
		gformat("RX63T Hello");
		++cnt;
		if(cnt >= 60) {
			cnt = 0;
		}

//		gformat("Input: %2.2:8y V") % ((inp * 25) >> 4);
		monog_.at_font_posx() = 0;
		monog_.at_font_posy() = 12;
//		gformat("Out0:  %2.2:8y V") % ((out0 * 15) >> 4);
		monog_.at_font_posx() = 0;
		monog_.at_font_posy() = 12 * 2;
//		gformat("Cur0:  %2.2:8y A") % ((cur0 * 5) >> (4 + 1));	// *2.5
		monog_.at_font_posx() = 0;
		monog_.at_font_posy() = 12 * 3;
//		gformat("Out1:  %2.2:8y V") % ((out1 * 15) >> 4);
		monog_.at_font_posx() = 0;
		monog_.at_font_posy() = 12 * 4;
//		gformat("Cur1:  %2.2:8y A") % ((cur1 * 5) >> (4 + 1));	// *2.5
#endif

		++led;
		if(led >= 30) led = 0;
		if(led < 15) {
			device::PORTB::PODR.B7 = 1; // LED Off
		} else {
			device::PORTB::PODR.B7 = 0; // LED On
		}

//		oled_.copy(monog_.fb());
//		monog_.clear(0);
	}
}

