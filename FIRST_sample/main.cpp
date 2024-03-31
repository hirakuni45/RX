//=============================================================================//
/*! @file
    @brief  ファースト・サンプル（LED 点滅） @n
			・動作周波数は、RXxxx/clock_profile.hpp を参照 @n
			・LED 接続ポートは、 RXxxx/board_profile.hpp を参照 @n
			  LED を「吸い込み：出力０で点灯させる場合」LED_ACTIVE = 0 @n
			  K（カソード）をポート側、A（アノード）を＋電源側に接続（制限抵抗を入れる） @n
			  LED を「吐き出し：出力１で点灯させる場合」LED_ACTIVE = 1 @n
			  K（カソード）を－電源側、A（アノード）をポート側に接続（制限抵抗を入れる） @n
			制限抵抗の計算方法： @n
			  LED の順方向電圧降下(Vf)を電源電圧から引いて、LED に流す電流により計算する。 @n
			  赤色 LED の例： @n
			  Vf：1.4V、電源電圧：3.3V、電流：1mA、R=E/I、1900 = (3.3 - 1.4) / 1E-3 @n
			  1.9K オームなので、1.5K～2K くらいが妥当な値。 @n
			Memo: @n
			  ポート出力は、電流を引いた（吸い込み）場合と、電流を掃き出した（吐き出し）場合で、能力が異なります。 @n
			  一般的に、「吸い込み」の方が電流を多く流せる場合が多く、その慣例に従って、「吸い込み」で接続する場合が通例です。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "common/renesas.hpp"

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::boost_master_clock();

	using namespace board_profile;

	LED::OUTPUT();  // LED ポートを出力に設定

	LED::P = 0;  // 消灯から開始

	while(1) {
#if 1
		utils::delay::milli_second(250);
		LED::P = 1;  // 点灯
		utils::delay::milli_second(250);
		LED::P = 0;  // 消灯
#else
		// 100KHz 出力
		utils::delay::micro_second(5);
		LED::P = 1;  // 点灯
		utils::delay::micro_second(5);
		LED::P = 0;  // 消灯
#endif
	}
}
