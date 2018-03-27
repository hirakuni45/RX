//=====================================================================//
/*! @file
    @brief  RX56N ファースト・サンプル
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/cmt_io.hpp"

// #include "common/format.hpp"

namespace {

	typedef device::system_io<12000000> SYSTEM_IO;

	device::cmt_io<device::CMT0, utils::null_task>  cmt_;

	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;

	typedef device::PORT<device::PORT6, device::bitpos::B3> LCD_DISP;
	typedef device::PORT<device::PORT6, device::bitpos::B6> LCD_LIGHT;
	typedef device::glcdc_io<device::GLCDC> GLCDC_IO;
	GLCDC_IO	glcdc_io_;
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::setup_system_clock();

	{  // タイマー設定（６０Ｈｚ）
		uint8_t cmt_irq_level = 4;
		cmt_.start(60, cmt_irq_level);
	}

	if(0) {  // GLCDC 初期化
		LCD_DISP::DIR  = 1;
		LCD_LIGHT::DIR = 1;
		LCD_DISP::P  = 1;  // DISP Enable
		LCD_LIGHT::P = 1;  // BackLight Enable (No PWM)
		glcdc_io_.start();
	}

#if 0
	device::GLCDC::GR1CLUT0[0].R = 0xcc;
	device::GLCDC::GR1CLUT0[1] = 0x123456;
	uint32_t rgba = device::GLCDC::GR1CLUT0[2];
	utils::format("%08X\n") % rgba;
#endif


	LED::DIR = 1;
	uint8_t n = 0;
	while(1) {
		cmt_.sync();

		++n;
		if(n >= 30) {
			n = 0;
		}
		if(n < 10) {
			LED::P = 0;
		} else {
			LED::P = 1;
		}
	}
}
