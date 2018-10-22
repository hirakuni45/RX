//=====================================================================//
/*! @file
    @brief  RX24T / BMP180/BMP280 サンプル @n
			・P00(4) ピンに赤色LED（VF:1.9V）を吸い込みで接続する
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/cmt_io.hpp"
#include "common/sci_io.hpp"
#include "common/fixed_fifo.hpp"
#include "common/format.hpp"
#include "common/iica_io.hpp"
#include "common/si2c_io.hpp"
#include "chip/VL53L0X.hpp"

/// #define SOFT_I2C

namespace {

	device::cmt_io<device::CMT0, utils::null_task>  cmt_;

	typedef utils::fixed_fifo<char, 128> buffer;
	device::sci_io<device::SCI1, buffer, buffer> sci_;

#ifdef SOFT_I2C
	typedef device::PORT<device::PORTB, device::bitpos::B2> SDA;
	typedef device::PORT<device::PORTB, device::bitpos::B1> SCL;
	typedef device::si2c_io<SDA, SCL> I2C;
#else
	typedef device::iica_io<device::RIIC0> I2C;
#endif
	I2C i2c_;

	typedef chip::VL53L0X<I2C> VLX;
	VLX vlx_(i2c_);
}

extern "C" {

	void sci_putch(char ch)
	{
		sci_.putch(ch);
	}

	void sci_puts(const char* str)
	{
		sci_.puts(str);
	}

	char sci_getch(void)
	{
		return sci_.getch();
	}

	uint16_t sci_length()
	{
		return sci_.recv_length();
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

	{  // タイマー設定（６０Ｈｚ）
		uint8_t intr_level = 4;
		cmt_.start(60, intr_level);
	}

	{  // SCI 設定
		uint8_t intr_level = 2;
		sci_.start(115200, intr_level);
	}

	{  // IICA(I2C) の開始
#ifdef SOFT_I2C
		if(!i2c_.start(I2C::speed::fast)) {
#else
		uint8_t intr_level = 0;
		if(!i2c_.start(I2C::speed::fast, intr_level)) {
#endif
			utils::format("IICA start fail: (%d)\n") % static_cast<uint32_t>(i2c_.get_last_error());
		}
	}

	utils::format("RX24T VL53L0X sample\n");

	// VL53L0X の開始
	if(!vlx_.start()) {
		utils::format("VL53L0X start NG\n");
	} else {
		utils::format("VL53L0X start OK\n");
		// 20ms
		vlx_.set_measurement_timing_budget(200000);
	}

	device::PORT0::PDR.B0 = 1; // output

	uint32_t cnt = 0;
	uint32_t n = 0;
	while(1) {
		cmt_.sync();

		++cnt;
		if(cnt >= 30) {
			cnt = 0;
		}
		device::PORT0::PODR.B0 = (cnt < 10) ? 0 : 1;

		++n;
		if(n >= 30) {
			auto len = vlx_.read_range_single_millimeters();
			if(vlx_.timeout_occurred()) {
				utils::format("Length: timeout\n");
			} else {
				utils::format("Length: %d [mm]\n") % (len - 50);
			}
			n = 0;
		}
	}
}
