Renesas RX マイコン LED 点滅サンプル
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
- RX140/Makefile
- RX220/Makefile (AE-RX220)
- RX231/Makefile
- RX62N/Makefile (BlueBoard-RX62N_100pin / FRK-RX62N)
- RX631/Makefile (GR-CITRUS)
- RX63T/Makefile
- RX24T/Makefile
- RX26T/Makefile
- RX66T/Makefile
- RX72T/Makefile
- RX64M/Makefile
- RX71M/Makefile
- RX65N/Makefile (RX65N Envision Kit)
- RX72N/Makefile (RX72N Envision Kit)

---

## ハードウェアーの準備（全般）
 - 各マイコンの、クリスタル周波数、各モジュールの周波数は、RXxxx/clock_profile.hpp を参照して下さい。
 - 各マイコンの、LED 接続ポートは、RXxxx/board_profile.hpp を参照して下さい。
 - インジケーター LED を指定のポートに接続する。
 - LED の接続は標準では、LOW レベル出力で点灯するように接続します。
 - LED の typedef を変更する事で、HIGH レベルで点灯するようにする事も出来ます。
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
	using namespace board_profile;

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
