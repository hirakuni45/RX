//=====================================================================//
/*! @file
    @brief  ファースト・サンプル（LED 点滅） @n
			RX64M, RX71M, RX72M: @n
					12MHz のベースクロックを使用する @n
			　　　　P07 ピンにLEDを接続する @n
			RX65N (Renesas Envision kit RX65N): @n
					12MHz のベースクロックを使用する @n
			　　　　P70 に接続された LED を利用する @n
			RX63T @n
					12MHz のベースクロックを使用する @n
					PB7 に接続された LED を利用する @n
			RX24T: @n
					10MHz のベースクロックを使用する @n
			　　　　P00 ピンにLEDを接続する @n
			RX66T: @n
					10MHz のベースクロックを使用する @n
			　　　　P00 ピンにLEDを接続する
			RX72N: @n
					16MHz のベースクロックを使用する @n
					P40 ピンにLEDを接続する @n
			RX72T: @n
					16MHz のベースクロックを使用する @n
					P01 ピンにLEDを接続する
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

namespace {

/// LED 接続ポートの定義
#if defined(SIG_RX71M)
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
#elif defined(SIG_RX72M)
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
#elif defined(SIG_RX72N)
	typedef device::PORT<device::PORT4, device::bitpos::B0> LED;
#elif defined(SIG_RX64M)
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
#elif defined(SIG_RX65N)
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
#elif defined(SIG_RX24T)
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
#elif defined(SIG_RX66T)
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
#elif defined(SIG_RX72T)
	typedef device::PORT<device::PORT0, device::bitpos::B1> LED;
#endif
// クロックの定義は、「RXxxx/clock_profile.hpp」を参照。
	typedef device::system_io<> SYSTEM_IO;
// 内蔵、高速発信器の利用
//	typedef device::system_io<device::system_base::OSC_TYPE::HOCO> SYSTEM_IO;
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::boost_master_clock();

	LED::OUTPUT();  // LED ポートを出力に設定

	while(1) {
		utils::delay::milli_second(250);
		LED::P = 0;
		utils::delay::milli_second(250);
		LED::P = 1;
	}
}
