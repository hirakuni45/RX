Renesas RX220, RX62N、RX63T, RX24T, RX64M, RX65N, RX71M, RX66T, RX72N, RX72T LED 点滅サンプル
=========
   
[英語版](README.md)
   
## 概要
RX マイコンを使った LED 点滅のサンプルプログラム
   
- マスタークロックのブースト
- LED の点滅
- ソフトウェアーディレーによる遅延

---

## プロジェクト・リスト
- main.cpp
- RX220/Makefile (AE-RX220)
- RX62N/Makefile (BlueBoard-RX62N_100pin / FRK-RX62N)
- RX631/Makefile (GR-CITRUS)
- RX63T/Makefile
- RX24T/Makefile
- RX66T/Makefile
- RX72T/Makefile
- RX64M/Makefile
- RX71M/Makefile
- RX65N/Makefile (for RX65N Envision Kit)
- RX72N/Makefile (for RX72N Envision Kit)

---

## ハードウェアーの準備（全般）
 - 各マイコンの、クリスタル周波数、各モジュールの周波数は、RXxxx/clock_profile.hpp を参照して下さい。
 - インジケーター LED を指定のポートに接続する。
 - LED の接続は標準では、LOW レベル出力で点灯するように接続します。
 - LED の typedef を変更する事で、HIGH レベルで点灯するようにする事も出来ます。
   
```C++
/// LED 接続ポートの定義
/// LED を「吸い込み：出力０で点灯させる場合」LED_ACTIVE = 0
/// LED を「吐き出し：出力１で点灯させる場合」LED_ACTIVE = 1
// Memo:
//    ポート出力は、電流を引いた（吸い込み）場合と、電流を掃き出した（吐き出し）場合で、能力が異なります。
//    一般的に、「吸い込み」の方が電流を多く流せる場合が多く、その慣例に従って、「吸い込み」で接続する場合が通例です。
#if defined(SIG_RX220)
	// 秋月 AE-RX220 ボード
	// P03 に LED を吸い込みで接続する事を想定している。
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B3, LED_ACTIVE> LED;
#elif defined(SIG_RX62N)
	// BlueBoard-RX62N_100pin
	static constexpr bool LED_ACTIVE = 0;
  #if defined(CQ_FRK)
	typedef device::PORT<device::PORT1, device::bitpos::B5, LED_ACTIVE> LED;
  #else
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
#elif defined(SIG_RX71M)
	// DIY RX72M board
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B7, LED_ACTIVE> LED;
#elif defined(SIG_RX72M)
	// 工事中
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B7, LED_ACTIVE> LED;
#elif defined(SIG_RX72N)
	// RX72N Envision Kit
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT4, device::bitpos::B0, LED_ACTIVE> LED;
#elif defined(SIG_RX64M)
	// DIY RX64M board
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B7, LED_ACTIVE> LED;
#elif defined(SIG_RX65N)
	// RX65N Envision Kit
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
```

 - BlueBoard-RX62N_100pin の場合、ボード上の D2 LED を利用する。（赤色） 
 - FRK-RX62N の場合、ボード上の LED1 を利用する。（黄色） 
 - GR-CITRUS の場合、ボード上 LED1 を利用する。（赤色）
 - Envision kit RX65N の場合、インジケーター LED はボード上の青色 LED を利用する。
 - Envision kit RX72N の場合、インジケーター LED はボード上の青色 LED を利用する。
 - 他ボードでは、'LED' の 'typedef' で示されたポートに LED を接続するか、LED が接続されたポートを 'typedef' する。

---

## マスタークロックのブースト
- main 関数に動作が移行したら、内部インストラクションクロック（ICLK ）を最大速度にブーストします。
- 内部デバイス用クロックも設定しています。（RXxxx/clock_profile.hpp に設定があります）
   
```C++
    SYSTEM_IO::boost_master_clock();
```
---

## LED 接続ポートを「出力」に設定

```C++
	LED::OUTPUT();  // LED ポートを出力に設定
```

## 点滅

```C++
	while(1) {
		utils::delay::milli_second(250);
		LED::P = 1;  // 点灯
		utils::delay::milli_second(250);
		LED::P = 0;  // 消灯
	}
```

---

## LED の制限抵抗

- LED に直列に入れる制限抵抗値の目安は以下の表を参照の事。
- 制限抵抗は、Vcc 側でも、Vss(GND) 側、どちらでも良いです。

1mA 程度の電流を流す場合：
|電源電圧|赤色(Vf)|黄色(Vf)|青色(Vf)|
|:---:|:---:|:---:|:---:|
|3.3V|2K (1.4V)|1.2K (2.1V)|300 (3.0V)|
|5V|3.6K (1.4V)|3K (2.1V)|2K (3.0V)|

計算式：   
   （「電源電圧」－「LED の Vf」）／ 「LED に流す電流」   

- 表の LED の Vf は目安です、流す電流や、LED により異なります。
- Vf が大きい場合、制限抵抗はより小さくなるので、ポートに流れる電流が制限を超えないように配慮して下さい。
- ポートに流す事が出来る最大電流は、ハードウェアーマニュアルの「電気的特性」「出力許容電流」を参照して下さい。

---

## ビルド方法

- 各プラットホームディレクトリーに移動、make する。
- led_sample.mot ファイルをマイコンに書き込む。
- FRK-RX62N は、R5F562N7(FlashRom: 374KB) の為、Makefile のデバイスを変更する。
- CQ_FRK 変数（コンパイル時定数）を有効にする事で、基板依存の切り替えを行う。

```
# BlueBoard-RX62N_100pin
#DEVICE		=	R5F562N8
# FRK-RX62N (CQ出版)
DEVICE		=	R5F562N7
USER_DEFS	=	CQ_FRK
```
   
## 動作
- LED が 0.25 秒間隔で点滅する。（ソフトウェアーによる遅延ループなので正確ではありません）
    
## 備考
- このプロジェクトが基本で最低限の設定などが含まれます、新しいプロジェクトを始める場合のテンプレートにして下さい。   
   
-----
   
License
----

[MIT](../LICENSE)
