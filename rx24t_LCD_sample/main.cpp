//=====================================================================//
/*! @file
    @brief  RX24T LCD サンプル @n
			・（インジケーター）P00(4) ピンに赤色LED（VF:1.9V）を吸い込みで接続する
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/cmt_io.hpp"
#include "common/sci_io.hpp"
#include "common/fifo.hpp"
#include "common/format.hpp"
#include "common/rspi_io.hpp"
#include "chip/ST7565.hpp"
#include "chip/UC1701.hpp"
#include "common/monograph.hpp"

// LCD を選択する
// #define LCD_ST7565
#define LCD_UC1701

namespace {

	class cmt_task {
	public:
		void operator() () {
		}
	};

	device::cmt_io<device::CMT0, cmt_task>  cmt_;

	typedef utils::fifo<uint8_t, 128> buffer;
	device::sci_io<device::SCI1, buffer, buffer> sci_;

	// SPI 定義（RSPI0）
	typedef device::rspi_io<device::RSPI0> SPI;
	SPI spi_;

	typedef device::PORT<device::PORT6, device::bitpos::B1> LCD_SEL;	///< LCD 選択信号
	typedef device::PORT<device::PORT6, device::bitpos::B2> LCD_A0;	    ///< LCD レジスター選択

#ifdef LCD_ST7565
	// ST7565 drive
	chip::ST7565<SPI, LCD_SEL, LCD_A0> lcd_(spi_);
#endif
#ifdef LCD_UC1701
	// UC1701 drive
	chip::UC1701<SPI, LCD_SEL, LCD_A0> lcd_(spi_);
#endif

	// モノクロ・グラフィックス
	graphics::kfont_null kfont_;
	graphics::monograph<128, 64> bitmap_(kfont_);

	uint8_t v_ = 91;
	uint8_t m_ = 123;
	uint8_t rand_()
	{
		v_ += v_ << 2;
		++v_;
		uint8_t n = 0;
		if(m_ & 0x02) n = 1;
		if(m_ & 0x40) n ^= 1;
		m_ += m_;
		if(n == 0) ++m_;
		return v_ ^ m_;
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
	uint8_t cmt_irq_level = 4;
	cmt_.start(60, cmt_irq_level);

	// SCI 設定
	static const uint8_t sci_level = 2;
	sci_.start(115200, sci_level);

#ifdef LCD_ST7565
	utils::format("RX24T LCD ST7565 sample\n");
#endif
#ifdef LCD_UC1701
	utils::format("RX24T LCD UC1701 sample\n");
#endif

	// RSPI 開始
	{
#ifdef LCD_ST7565
		uint32_t clk = 8000000;
#endif
#ifdef LCD_UC1701
///		uint32_t clk = 4000000;
		uint32_t clk = 1000000;
#endif
		if(!spi_.start(clk, SPI::PHASE::TYPE4)) {
			utils::format("RSPI speed fail...\n");
		}
	}

	// LCD 開始
	{
		lcd_.start(0x00);
		bitmap_.clear(0);
	}

	device::PORT0::PDR.B0 = 1; // output

	uint16_t x = rand_() & 127;
	uint16_t y = rand_() & 63;
	uint16_t xx;
	uint16_t yy;
	uint8_t	nn = 0;
	uint8_t loop = 0;

	uint32_t cnt = 0;
	while(1) {
		cmt_.sync();

		if(nn >= 4) {
			lcd_.copy(bitmap_.fb(), bitmap_.page_num());
			nn = 0;
		}
		++nn;

		if(loop >= 20) {
			loop = 0;
			bitmap_.clear(0);
			bitmap_.frame(0, 0, 128, 64, 1);
		}
		xx = rand_() & 127;
		yy = rand_() & 63;
		bitmap_.line(x, y, xx, yy, 1);
		x = xx;
		y = yy;
		++loop;

		if(sci_.recv_length()) {
			auto ch = sci_.getch();
			sci_.putch(ch);
		}

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		device::PORT0::PODR.B0 = (cnt < 10) ? 0 : 1;
	}
}
