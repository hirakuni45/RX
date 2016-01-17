//=====================================================================//
/*! @file
    @brief  RX メイン
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>
// #include <cmath>
#include <cstdlib>
#include "main.hpp"
#include "RX63T/system.hpp"
#include "RX63T/port.hpp"
#include "RX63T/mpc.hpp"
#include "common/cmt_io.hpp"
#include "common/sci_io.hpp"
#include "common/format.hpp"
#include "monitor.hpp"
#include "ssd1306z_io.hpp"
#include "monograph.hpp"
#include "chager.hpp"

static volatile uint8_t dummy_;
//-----------------------------------------------------------------//
/*!
	@brief	無駄ループによる時間待ち
	@param[in]	n	無駄ループ回数
 */
//-----------------------------------------------------------------//
void wait_delay(uint32_t n)
{
	// とりあえず無駄ループ
	for(uint32_t i = 0; i < n; ++i) {
		dummy_ += i & 255;
	}
}

static utils::chager	chager_;
static uint16_t timer_count_;
static volatile uint16_t timer_sync_ = 0x0001;

static uint32_t count_ = 1230;

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

namespace root {
	device::cmt_io<device::CMT0, cmt_task>  cmt_;
	device::sci_io<device::SCI1, 256, 256> sci_;
	device::ssd1306z_io oled_;
	utils::monitor		monitor_;
	graphics::monograph	monog_;
}

struct chout {
	void operator() (char ch) {
		root::sci_.putch(ch);
	}
};
typedef utils::format<chout>	format;

struct grout {
	void operator() (char ch) {
		root::monog_.draw_font(ch);
	}
};
typedef utils::format<grout>	gformat;


//-----------------------------------------------------------------//
/*!
	@brief	SCI 文字出力
	@param[in]	ch	文字コード
 */
//-----------------------------------------------------------------//
void sci_putch(char ch)
{
	root::sci_.putch(ch);
}


//-----------------------------------------------------------------//
/*!
	@brief	SCI 文字列出力
	@param[in]	str	文字列
 */
//-----------------------------------------------------------------//
void sci_puts(const char *str)
{
	root::sci_.puts(str);
}


//-----------------------------------------------------------------//
/*!
	@brief	SCI 文字入力
	@return 文字コード
 */
//-----------------------------------------------------------------//
char sci_getch(void)
{
	return root::sci_.getch();
}


//-----------------------------------------------------------------//
/*!
	@brief	SCI 文字入力数を取得
	@return 入力文字数
 */
//-----------------------------------------------------------------//
uint32_t sci_length(void)
{
	return root::sci_.length();
}


//-----------------------------------------------------------------//
/*!
	@brief	10ms 単位タイマー
 */
//-----------------------------------------------------------------//
void delay_10ms(uint32_t n)
{
	while(n > 0) {
		root::cmt_.sync();
		--n;
	}
}


static void timer_60hz()
{
	volatile uint16_t cnt = timer_sync_;
	while(cnt == timer_sync_) ;
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	using namespace root;

	device::SYSTEM::PRCR = 0xa503;	// クロック、低消費電力、関係書き込み許可

	device::SYSTEM::MOSCWTCR.MSTS = 0b01101;	// 131072 サイクル待ち
	device::SYSTEM::MOSCCR.MOSTP = 0;			// メインクロック発振器動作
	dummy_ = device::SYSTEM::MOSCCR.MOSTP();
	device::SYSTEM::MOFCR.MOFXIN = 1;			// メインクロック強制発振
	dummy_ = device::SYSTEM::MOFCR.MOFXIN();
	wait_delay(5000);

	device::SYSTEM::PLLCR.STC = 0xf;			// PLL 16 倍(192MHz)
	device::SYSTEM::PLLWTCR.PSTS = 0b01010;		// 131072 サイクル待ち
	device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
	wait_delay(5000);

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

	// SCI1 の初期化（PD5:RXD1:input, PD3:TXD1:output）
	device::PORTD::PDR.B3 = 1;
	device::PORTD::PDR.B5 = 0;
	device::MPC::PWPR.B0WI = 0;				// PWPR 書き込み許可
	device::MPC::PWPR.PFSWE = 1;			// PxxPFS 書き込み許可
	device::MPC::PD3PFS.PSEL = 0b01010;		// TXD1 設定
	device::MPC::PD5PFS.PSEL = 0b01010;		// RXD1 設定
	device::MPC::PWPR = device::MPC::PWPR.B0WI.b();	// MPC 書き込み禁止
	device::PORTD::PMR.B3 = 1;				// 周辺機能として使用
	device::PORTD::PMR.B5 = 1;				// 周辺機能として使用
	static const uint8_t sci_irq_level = 1;
	sci_.initialize(sci_irq_level);
	sci_.start(115200);

	// チャージャー本体
	chager_.initialize();

	// タイマー設定
	cmt_.set_clock(F_PCKB);
	uint8_t cmt_irq_level = 3;
	cmt_.initialize(46875, cmt_irq_level);

	cmt_.sync();

	monitor_.initialize();

///	device::SYSTEM::PRCR = 0xa500;	///< クロック、低消費電力、関係書き込み禁止

	oled_.initialize();

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

		monog_.at_font_posx() = 0;
		monog_.at_font_posy() = 0;
		gformat("RX63T Hello %u") % static_cast<unsigned int>(count_);
		++cnt;
		if(cnt >= 60) {
			cnt = 0;
			++count_;
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

		++led;
		if(led >= 30) led = 0;
		if(led < 15) {
			device::PORTB::PODR.B7 = 1; // LED Off
		} else {
			device::PORTB::PODR.B7 = 0; // LED On
		}

		oled_.copy(monog_.fb());
		monog_.clear(0);
	}
}
