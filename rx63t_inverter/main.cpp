//=====================================================================//
/*! @file
    @brief  RX メイン
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>
#include "main.hpp"
#include "system.hpp"
#include "port.hpp"
#include "cmt_io.hpp"
#include "sci_io.hpp"

namespace root {
	device::cmt_io<device::CMT0> cmt_;
	device::sci_io<device::SCI1> sci_;
}

#if 0
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
#endif

#if 0
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
#endif

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

	device::SYSTEM::SCKCR = device::SYSTEM::SCKCR.FCK.b(3)		// 1/8
						  | device::SYSTEM::SCKCR.ICK.b(1)		// 1/2
						  | device::SYSTEM::SCKCR.BCK.b(2)		// 1/4
						  | device::SYSTEM::SCKCR.PCKA.b(1)		// 1/2
						  | device::SYSTEM::SCKCR.PCKB.b(1)		// 1/4
						  | device::SYSTEM::SCKCR.PCKC.b(3)		// 1/8
						  | device::SYSTEM::SCKCR.PCKD.b(3);	// 1/8
	device::SYSTEM::SCKCR3.CKSEL = 4;	///< PLL 回路選択

///	device::SYSTEM::PRCR = 0xa500;	///< クロック、低消費電力、関係書き込み禁止

	// SCI の初期化（RXD0, TXD0）
//	device::PORT2::ICR.B1 = 1;		// PORT2:B1 input (RXD0)
//	sci_.initialize(256, 512, 3);
//	sci_.set_baud(115200);

	// 100Hz タイマー設定
	cmt_.set_clock(F_PCKA);
	static const uint8_t cmt_irq_level = 1;
	cmt_.initialize(100, cmt_irq_level);

	// 「FatFs のタイマー」コールバックを設定
//	cmt_.set_task(disk_timerproc);
//	syscalls_initialize();
	device::PORTB::PDR.B7 = 1; // PORTB:B7 output
	device::PORTB::PODR.B7 = 0; // LED On

	cmt_.sync();
	device::PORTB::PODR.B7 = 1; // LED Off

//	monitor_.initialize();

	uint32_t cnt = 0;

	while(1) {
		cmt_.sync();

///		syscalls_service();

///		monitor_.service();

        ++cnt;
        if(cnt >= 100) {
            cnt = 0;
        }

		if(cnt < 50) {
			device::PORTB::PODR.B7 = 1; // LED Off
		} else {
			device::PORTB::PODR.B7 = 0; // LED On
		}
	}

	return 0;
}
