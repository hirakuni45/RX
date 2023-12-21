//=========================================================================//
/*! @file
    @brief  ファースト・サンプル（LED 点滅） @n
			※動作周波数は、RXxxx/clock_profile.hpp を参照。 @n
			LED 接続ポートの定義： @n
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
	@copyright	Copyright (C) 2018, 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"

namespace {

#if defined(SIG_RX220)
	// 秋月 AE-RX220 ボード
	// P03 に LED を吸い込みで接続する事を想定している。
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B3, LED_ACTIVE> LED;
#elif defined(SIG_RX231)
	// DIY RX231 board
	static constexpr bool LED_ACTIVE = 1;
	typedef device::PORT<device::PORT0, device::bitpos::B1, LED_ACTIVE> LED;
#elif defined(SIG_RX62N)
	static constexpr bool LED_ACTIVE = 0;
  #if defined(CQ_FRK)
    // FRK-RX62N(CQ 出版社)
	typedef device::PORT<device::PORT1, device::bitpos::B5, LED_ACTIVE> LED;
  #else
    // BlueBoard-RX62N_100pin
	typedef device::PORT<device::PORT0, device::bitpos::B5, LED_ACTIVE> LED;
  #endif
#elif defined(SIG_RX631)
	// RX631 GR-CITRUS
	static constexpr bool LED_ACTIVE = 1;
	typedef device::PORT<device::PORTA, device::bitpos::B0, LED_ACTIVE> LED;
#elif defined(SIG_RX63T)
	// DIY RX63T board
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORTB, device::bitpos::B7, LED_ACTIVE> LED;
#elif defined(SIG_RX24T)
	// DIY RX24T board
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B0, LED_ACTIVE> LED;
#elif defined(SIG_RX26T)
	// DIY RX26T board
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B0, LED_ACTIVE> LED;
#elif defined(SIG_RX71M)
	// DIY RX72M board
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B7, LED_ACTIVE> LED;
#elif defined(SIG_RX72M)
	// 工事中
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B7, LED_ACTIVE> LED;
#elif defined(SIG_RX72N)
	// Renesas RX72N Envision Kit
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT4, device::bitpos::B0, LED_ACTIVE> LED;
#elif defined(SIG_RX64M)
	// DIY RX64M board
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B7, LED_ACTIVE> LED;
#elif defined(SIG_RX65N)
	// Renesas RX65N Envision Kit
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT7, device::bitpos::B0, LED_ACTIVE> LED;
#elif defined(SIG_RX66T)
	// DIY RX66T board
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B0, LED_ACTIVE> LED;
#elif defined(SIG_RX72T)
	// DIY RX72T board
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B1, LED_ACTIVE> LED;
#endif
}

int main(int argc, char** argv);

int main(int argc, char** argv)
{
	SYSTEM_IO::boost_master_clock();

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
