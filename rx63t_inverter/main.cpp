//=====================================================================//
/*! @file
    @brief  RX メイン
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>
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
	device::sci_io<device::SCI1>  sci_;
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
	static const uint8_t sci_irq_level = 3;
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

	// S12AD 設定 (P40:56, P41:57)
	device::SYSTEM::MSTPCRA.MSTPA17 = 0; // S12AD モジュール有効
	device::MPC::PWPR.B0WI = 0;			 // PWPR 書き込み許可
	device::MPC::PWPR.PFSWE = 1;		 // PxxPFS 書き込み許可
	device::MPC::P40PFS.ASEL = 1;	     // アナログ入力設定
	device::MPC::P41PFS.ASEL = 1;	     // アナログ入力設定
	device::MPC::PWPR = device::MPC::PWPR.B0WI.b();	// MPC 書き込み禁止

	// 100Hz タイマー設定
	cmt_.set_clock(F_PCKA);
	static const uint8_t cmt_irq_level = 1;
	cmt_.initialize(100, cmt_irq_level);

	cmt_.sync();

	monitor_.initialize();

///	device::SYSTEM::PRCR = 0xa500;	///< クロック、低消費電力、関係書き込み禁止

	uint32_t cnt = 0;

	while(1) {
		cmt_.sync();

		// A/D 変換開始
		adc_.start(0b00000011);
		adc_.sync();
		uint16_t adv = adc_.get(0);
		uint16_t cpv = adv >> 3;
		if(cpv < 10) cpv = 10;
		else if(cpv > 500) cpv = 500;
		gpt_.set_a(cpv);

		monitor_.service();

        ++cnt;
        if(cnt >= 30) {
            cnt = 0;
			chout_ << "A/D(0): " << static_cast<int32_t>(adv) << utils::chout::endl;
        }
		if(cnt < 15) {
			device::PORTB::PODR.B7 = 1; // LED Off
		} else {
			device::PORTB::PODR.B7 = 0; // LED On
		}
	}

	return 0;
}
