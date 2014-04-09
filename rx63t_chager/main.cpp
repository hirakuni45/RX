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
#include "rx/rx63x/system.hpp"
#include "rx/rx63x/port.hpp"
#include "rx/rx63x/mpc.hpp"
#include "rx/cmt_io.hpp"
#include "rx/sci_io.hpp"
#include "rx/gpt_io.hpp"
#include "rx/adc_io.hpp"
#include "rx/format.hpp"
#include "chager.hpp"
#include "ssd1306z_io.hpp"
#include "monograph.hpp"

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

namespace root {
	device::cmt_io<device::CMT0>  cmt_;
	device::sci_io<device::SCI1, 256, 256> sci_;
	device::gpt_io<device::GPT0>  gpt_;
	device::adc_io<device::S12AD> adc_;
	device::ssd1306z_io oled_;
	utils::chager chager_;
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

static const int32_t low_limit_  = 10;  // 0.46V at 24V
static const int32_t high_limit_ = 320; // 15.0V at 24V
static int32_t loop_cpv_;
static int32_t adc_out_;
static int32_t adc_cur_;
static int32_t adc_inp_;
static int32_t adj_ref_;
static uint16_t timer_count_;
static volatile uint16_t timer_sync_;

static void timer_task_()
{
	using namespace root;

	adc_out_ = static_cast<int32_t>(adc_.get(0)); // 出力電圧 6:1 (Ref:2.5V, 4096:15V)
	adc_cur_ = static_cast<int32_t>(adc_.get(1)); // 出力電流 0 to 2.5A (4096:2.5A)
	adc_inp_ = static_cast<int32_t>(adc_.get(2)); // 入力電圧 10:1 (Ref:2.5V, 4096:25V)

	adc_.start(0b00000111);

	if(adj_ref_ < adc_out_) --loop_cpv_;
	else if(adj_ref_ > adc_out_) ++loop_cpv_;

	if(loop_cpv_ < low_limit_) loop_cpv_ = low_limit_;
	else if(loop_cpv_ > high_limit_) loop_cpv_ = high_limit_;

	gpt_.set_a(loop_cpv_);
	uint16_t ofs = (512 - loop_cpv_) / 4;
	gpt_.set_ad_a(loop_cpv_ + ofs);	// A/D 変換開始タイミング

	++timer_count_;
	if(timer_count_ >= 938) {
		timer_count_ = 0;
		++timer_sync_;
	}
}

static void timer_100hz()
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

	// GPT0 設定 (GTIOC0A: P71:38, PD7:12)(GTIOC0B: P74:35, PD6:13)
	device::PORT7::PDR.B1 = 1;			// output
	device::SYSTEM::MSTPCRA.MSTPA7 = 0; // GPT0..3 モジュール有効
	device::MPC::PWPR.B0WI = 0;			// PWPR 書き込み許可
	device::MPC::PWPR.PFSWE = 1;		// PxxPFS 書き込み許可
	device::MPC::P71PFS.PSEL = 0b0110;	// GTIOC0A 設定
	device::MPC::PWPR = device::MPC::PWPR.B0WI.b();	// MPC 書き込み禁止
	device::PORT7::PMR.B1 = 1;			// 周辺機能として使用
	gpt_.start();	// PWM start
	gpt_.set_r(512 - 1);
	gpt_.set_a(256);

	// S12AD 設定 P40(56), P41(55), P42(54)
	device::SYSTEM::MSTPCRA.MSTPA17 = 0; // S12AD モジュール有効
	device::MPC::PWPR.B0WI = 0;			 // PWPR 書き込み許可
	device::MPC::PWPR.PFSWE = 1;		 // PxxPFS 書き込み許可
	device::MPC::P40PFS.ASEL = 1;	     // アナログ入力設定
	device::MPC::P41PFS.ASEL = 1;	     // アナログ入力設定
	device::MPC::PWPR = device::MPC::PWPR.B0WI.b();	// MPC 書き込み禁止


	adj_ref_ = static_cast<int32_t>((4096.0f / 2.5f) * (5.0f / 6.0f)); // 指令電圧
	loop_cpv_ = low_limit_; // 初期電圧
	gpt_.set_a(loop_cpv_);
	uint16_t ofs = (512 - loop_cpv_) / 4;
	gpt_.set_ad_a(loop_cpv_ + ofs);	// A/D 変換開始タイミング
	adc_.start(0b00000111);
	adc_.sync();

	// タイマー設定
	cmt_.set_clock(F_PCKB);
	cmt_.set_task(timer_task_);
	uint8_t cmt_irq_level = 3;
	cmt_.initialize(93750, cmt_irq_level);

	cmt_.sync();

	chager_.initialize();

///	device::SYSTEM::PRCR = 0xa500;	///< クロック、低消費電力、関係書き込み禁止

	oled_.initialize();

#if 0
	uint16_t xx = 0;
	uint16_t yy = 0;
	int l = 0;
	uint16_t x = rand() & 127;
	uint16_t y = rand() & 63;
	monog_.line(xx, yy, x, y, 1);
	xx = x;
	yy = y;
	++l;
	if(l >= 20) {
		monog_.clear(0);
		l = 0;
	}
#endif

	cmt_.sync();
	int v = adc_inp_;
	format("Input Voltage: %2.4:8y\n") % ((v * 25) >> 4);

	uint32_t cnt = 0;
	uint32_t led = 0;

	int inp = 0;
	int out = 0;
	int cur = 0;

	while(1) {
		timer_100hz();

		chager_.service();

		++cnt;
		if(cnt >= 50) {
			inp = static_cast<int>(adc_inp_);
			out = static_cast<int>(adc_out_);
			cur = static_cast<int>(adc_cur_);
			cnt = 0;
		}

		monog_.at_font_posx() = 0;
		monog_.at_font_posy() = 0;
		gformat("Inp: %2.2:8y V") % ((inp * 25) >> 4);
		monog_.at_font_posx() = 0;
		monog_.at_font_posy() = 12;
		gformat("Out: %2.2:8y V") % ((out * 15) >> 4);
		monog_.at_font_posx() = 0;
		monog_.at_font_posy() = 12 * 2;
		gformat("Cur: %2.2:8y A") % ((cur * 5) >> (4 + 1));	// *2.5

		++led;
		if(led >= 50) led = 0;
		if(led < 25) {
			device::PORTB::PODR.B7 = 1; // LED Off
		} else {
			device::PORTB::PODR.B7 = 0; // LED On
		}

		oled_.copy(monog_.fb());
		monog_.clear(0);
	}
}
