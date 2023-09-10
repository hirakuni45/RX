Renesas RX62N, RX24T, RX64M, RX71M, RX65N, RX66T, RX72T, RX72N MTU サンプル
=========

[英語版](README.md)

---

## 概要

RX マイコンを使った MTU のサンプルプログラム
   
---

## プロジェクト・リスト

- main.cpp
- RX62N/Makefile
- RX24T/Makefile
- RX64M/Makefile
- RX71M/Makefile
- RX65N/Makefile
- RX66T/Makefile
- RX72T/Makefile
- RX72N/Makefile

---

## ハードウェアーの準備（全般）

- 各マイコンの、クリスタル周波数、各モジュールの周波数は、RXxxx/clock_profile.hpp を参照して下さい。
- インジケーター LED を指定のポートに接続する。
-  USB シリアルとSCI ポートを接続する。
- RX62N の SCI 標準ポートは、「RX62x/port_map.hpp」参照。
- RX24T の SCI 標準ポートは、「RX24T/port_map.hpp」参照。
- RX64M/RX71M の SCI 標準ポートは、「RX64M/port_map.hpp」参照。
- RX65x の SCI 標準ポートは、「RX65x/port_map.hpp」参照。
- RX72N の SCI 標準ポートは、「RX72N/port_map.hpp」参照。
- RX66T の SCI 標準ポートは、「RX66T/port_map.hpp」参照。
- RX72T の SCI 標準ポートは、「RX72T/port_map.hpp」参照。

```C++
#if defined(SIG_RX62N)
  #if defined(CQ_FRK)
    // FRK-RX62N(CQ 出版社)
	static const char* system_str_ = { "RX62N FRK-RX62N" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT1, device::bitpos::B5, LED_ACTIVE> LED;
	typedef device::SCI0 SCI_CH;
  #else
    // BlueBoard-RX62N_100pin
	static const char* system_str_ = { "RX62N BlueBoard-RX62N_100pin" };
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B5, LED_ACTIVE> LED;
	typedef device::SCI0 SCI_CH;
  #endif
#elif defined(SIG_RX24T)
	static const char* system_str_ = { "RX24T DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B0, false> LED;
	typedef device::SCI1 SCI_CH;
#elif defined(SIG_RX71M)
	static const char* system_str_ = { "RX71M DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B7, false> LED;
	typedef device::SCI1 SCI_CH;
#elif defined(SIG_RX64M)
	static const char* system_str_ = { "RX64M DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B7, false> LED;
	typedef device::SCI1 SCI_CH;
#elif defined(SIG_RX65N)
	static const char* system_str_ = { "RX65N Envision Kit" };
	typedef device::PORT<device::PORT7, device::bitpos::B0, false> LED;
	typedef device::SCI9 SCI_CH;
#elif defined(SIG_RX66T)
	static const char* system_str_ = { "RX66T DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B0, false> LED;
	typedef device::SCI1 SCI_CH;
#elif defined(SIG_RX72N)
	static const char* system_str_ = { "RX72N Envision Kit" };
	typedef device::PORT<device::PORT4, device::bitpos::B0, false> LED;
	typedef device::SCI2 SCI_CH;
#elif defined(SIG_RX72T)
	static const char* system_str_ = { "RX72T DIY" };
	typedef device::PORT<device::PORT0, device::bitpos::B1, false> LED;
	typedef device::SCI1 SCI_CH;
#endif
```

- BlueBoard-RX62N_100pin の場合、ボード上の D2 LED を利用する。（赤色） 
- FRK-RX62N の場合、ボード上の LED1 を利用する。（黄色） 
- RX65N Envision kit の場合、インジケーター LED はボード上の青色を利用する。
- RX72N Envision kit の場合、インジケーター LED はボード上の青色を利用する。

---

## ハードウェアーリソースの準備

- SCI に指定されたポートに USB シリアルなどの変換器を使い PC と接続する。
- マイコン側の RXD 端子と、USB シリアルの TXD を接続。
- マイコン側の TXD 端子と、USB シリアルの RXD を接続。
- RX72N Envision kit は、ボード上の CN8 マイクロ USB と PC を接続。

---

## ビルド方法

- 各プラットホームディレクトリーに移動、make する。
- mtu_sample.mot ファイルを書き込む。
- FRK-RX62N は、R5F562N7(FlashRom: 374KB) の為、Makefile のデバイスを変更する。
- CQ_FRK 変数（コンパイル時定数）を有効にする事で、基板依存の切り替えを行う。

```
# BlueBoard-RX62N_100pin
#DEVICE		=	R5F562N8
# FRK-RX62N (CQ出版)
DEVICE		=	R5F562N7
USER_DEFS	=	CQ_FRK
```

---

## 動作
- LED が 0.25 秒間隔で点滅する。
- SCI に指定されたポートで、TX（送信）、RX（受信）を行う。
- TeraTerm などで確認。
- TeraTerm のシリアル設定：１１５２００ボー、８ビットデータ、１ストップ、パリティ無し。
- main.cpp の中、SCI の初期化でボーレートは自由に設定できる。
- ボーレート設定出来ない「値」の場合、初期化が失敗する。（極端に遅い、速い）
- utils::command クラスにより、１行入力機能をサービス。
- 受け取った文字をパースして表示。
    
---

## 備考
- FIFO バッファは、受信側 256 バイト、送信側 512 バイトとなっています。
- ボーレート、受信頻度、送信頻度などを考慮して、適切な値に調整します。
- 最小は 16 バイト程度が必要です。
- FIFO バッファより大きい文字列を送る場合、バッファが空くまで待機する事になります。
- 受信時、バッファからの取り出し速度が、受信速度を下回ると、オーバーフローして、文字を紛失します。
- SCI のチャネルを変更する場合「main.cpp」で「typedef」してある定義を変更します。
- SCIx とポート接続の関係性は、RXxxx/port_map.hpp を参照して下さい。
- ピン番号以外は、144ピン、100ピン、デバイスでも同じように機能する。
- 第二候補を選択する場合は、sci_io の typedef で、「device::port_map::ORDER::SECOND」を追加する。
- 別プログラムによって、雑多な設定を自動化してソースコードを生成する試みを行っているアプリケーションがありますが、それは、基本的に間違った方法だと思えます、設定の修正が必要な場合、必ず生成プログラムに戻って、生成からやり直す必要があります。
- C++ テンプレートは、チャネルの違いや、ポートの違い、デバイスの違いをうまく吸収して、柔軟で、判りやすい方法で実装できます。

---
   
License
   
[MIT](../LICENSE)
