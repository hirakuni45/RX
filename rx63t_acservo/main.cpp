//=====================================================================//
/*! @file
    @brief  RX メイン
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>
#include <cmath>
#include "main.hpp"
#include "rx/rx63x/system.hpp"
#include "rx/rx63x/port.hpp"
#include "rx/rx63x/mpc.hpp"
#include "rx/cmt_io.hpp"
#include "rx/sci_io.hpp"
#include "rx/gpt_io.hpp"
#include "rx/adc_io.hpp"
#include "rx/chout.hpp"
#include "inv_monitor.hpp"


namespace root {
	device::cmt_io<device::CMT0>  cmt_;
	device::sci_io<device::SCI1, 256, 256>  sci_;
	device::gpt_io<device::GPT0>  gpt_;
	device::adc_io<device::S12AD> adc_;
	utils::chout chout_;
	utils::inv_monitor monitor_;
}


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


void prn_voltage_(const char* info, int32_t v)
{
	int32_t vv = v * 15 * 100 / 4096;
	int32_t mod = vv % 100;
	if(mod < 0) mod = -mod;
	root::chout_.suppress_char(' ');
	root::chout_.set_length(0);
	root::chout_ << info << (vv / 100) << '.';
	root::chout_.suppress_char('0');
	root::chout_.set_length(2);
	root::chout_ << mod << utils::chout::endl;
}

void prn_value_(const char* info, int32_t v)
{
	root::chout_.suppress_char(' ');
	root::chout_.set_length(0);
	root::chout_ << info << v << utils::chout::endl;
}

static volatile uint8_t dummy_;

static void wait_()
{
	// とりあえず無駄ループ
	for(uint32_t i = 0; i < 5000; ++i) {
		i += dummy_ & 0;
	}
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
	wait_();

	device::SYSTEM::PLLCR.STC = 0xf;			// PLL 16 倍(192MHz)
	device::SYSTEM::PLLWTCR.PSTS = 0b01010;		// 131072 サイクル待ち
	device::SYSTEM::PLLCR2.PLLEN = 0;			// PLL 動作
	wait_();

	device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(3)		// 1/8 (192/8=24)
						  | device::SYSTEM::SCKCR.ICK.b(1)		// 1/2 (192/2=96)
						  | device::SYSTEM::SCKCR.BCK.b(2)		// 1/4 (192/4=48)
						  | device::SYSTEM::SCKCR.PCKA.b(1)		// 1/2 (192/2=96)
						  | device::SYSTEM::SCKCR.PCKB.b(2)		// 1/4 (192/4=48)
						  | device::SYSTEM::SCKCR.PCKC.b(2)		// 1/4 (192/8=48)
						  | device::SYSTEM::SCKCR.PCKD.b(2);	// 1/4 (192/8=48)
	device::SYSTEM::SCKCR3.CKSEL = 4;	///< PLL 回路選択

	// Signal LED 出力設定
	device::PORTB::PDR.B7 = 1; // PORTB:B7 output
	device::PORTB::PODR.B7 = 1; // LED Off

	// SCI1 の初期化（PD5:RXD1:input, PD3:TXD1:output）
	device::PORTD::PDR.B3 = 1;
	device::MPC::PWPR.B0WI = 0;				// PWPR 書き込み許可
	device::MPC::PWPR.PFSWE = 1;			// PxxPFS 書き込み許可
	device::MPC::PD3PFS.PSEL = 0b01010;		// TXD1 設定
	device::MPC::PD5PFS.PSEL = 0b01010;		// RXD1 設定
	device::MPC::PWPR = device::MPC::PWPR.B0WI.b();	// MPC 書き込み禁止
	device::PORTD::PMR.B3 = 1;
	device::PORTD::PMR.B5 = 1;
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
	device::PORT7::PMR.B1 = 1;
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

	// タイマー設定
	cmt_.set_clock(F_PCKB);
	uint8_t cmt_irq_level = 3;
	cmt_.initialize(93750, cmt_irq_level);

	cmt_.sync();

	monitor_.initialize();

///	device::SYSTEM::PRCR = 0xa500;	///< クロック、低消費電力、関係書き込み禁止

	for(int i = 0; i < 10; ++i) {
		adc_.start(0b00000111);
		cmt_.sync();
		adc_.sync();
		int32_t v = static_cast<int32_t>(adc_.get(0));
		prn_value_("Ch0: ", v);
	}

	uint32_t cnt = 0;
	uint32_t led = 0;

	int32_t ds = 0;

	int32_t ref = 300;

	int32_t val = 0;

	int32_t low_limit = 10; // 0.23V at 12V input
	int32_t high_limit = 500; // 11.72V at 12V input
	int32_t cpv = low_limit;
	bool up = true;
	while(1) {
		adc_.start(0b00000111);

		cmt_.sync();

		// A/D 変換開始
		adc_.sync();

device::PORTB::PODR.B7 = 0; // LED On

		int32_t ref = static_cast<int32_t>(adc_.get(0)); // 指令電圧
		int32_t out = static_cast<int32_t>(adc_.get(1)); // 出力電圧
		int32_t inp = static_cast<int32_t>(adc_.get(2)); // 入力電圧

// int32_t gain = static_cast<int32_t>(adc_.get(0));
int32_t gain = 130;

		// 三角波
#if 0
		if(up) {
			ref += 1;
		} else {
			ref -= 1;
		}

		if(ref > 1700) {
			up = false;
			ref = 1700;
		} else if(ref < 200) {
			up = true;
			ref = 200;
		}
#endif

		int32_t dif = ref - out;  // 誤差
		// PWM の制御量に対するスレッショルド
		int32_t d = dif * gain / inp;
		val += d;
		cpv = val / 8;
		// 出力リミッター
		if(cpv < low_limit) cpv = low_limit;
		else if(cpv > high_limit) cpv = high_limit;

		gpt_.set_a(cpv);
		uint16_t ofs = (512 - cpv) / 4;
		gpt_.set_ad_a(cpv + ofs);	// A/D 変換開始タイミング

device::PORTB::PODR.B7 = 1; // LED Off

#if 0
		monitor_.service();

		++cnt;
		if(cnt >= 1000) {
			cnt = 0;
			prn_voltage_("Inp: ", inp);
			prn_voltage_("Ref: ", ref);
			prn_voltage_("Dif: ", dif);
			prn_voltage_("Out: ", out);
			prn_value_("PWM: ", cpv);
        }
#endif
#if 0
		++led;
		if(led >= 700) led = 0;
		if(led < 350) {
			device::PORTB::PODR.B7 = 1; // LED Off
		} else {
			device::PORTB::PODR.B7 = 0; // LED On
		}
#endif
	}
}
