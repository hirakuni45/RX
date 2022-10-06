Renesas RX62N、RX24T, RX64M, RX65N, RX71M, RX66T, RX72N, RX72T LED 点滅サンプル
=========
   
[英語版](README.md)
   
## 概要
RX マイコンを使った LED 点滅のサンプルプログラム
   
- マスタークロックのブースト
- LED の点滅

---

## プロジェクト・リスト
- main.cpp
- RX62N/Makefile (BlueBoard-RX62N_100pin)
- RX24T/Makefile
- RX64M/Makefile
- RX71M/Makefile
- RX65N/Makefile (for RX65N Envision Kit)
- RX66T/Makefile
- RX72N/Makefile (for RX72N Envision Kit)
- RX72T/Makefile

---

## ハードウェアーの準備（全般）
 - 各マイコンの、クリスタル周波数、各モジュールの周波数は、RXxxx/clock_profile.hpp を参照して下さい。
 - インジケーター LED を指定のポートに接続する。
 - LED の接続は標準では、LOW レベル出力で点灯するように接続します。
 - LED の typedef を変更する事で、HIGH レベルで点灯するようにする事も出来ます。
   
```C++
/// LED 接続ポートの定義
/// LED を「吸い込み：出力０で点灯させる場合」LED_ASSERT = 0
/// LED を「吐き出し：出力１で点灯させる場合」LED_ASSERT = 1
// Memo:
//    ポート出力は、電流を引いた（吸い込み）場合と、電流を掃き出した（吐き出し）場合で、能力が異なります。
//    一般的に、「吸い込み」の方が電流を多く流せる場合が多く、その慣例に従って、「吸い込み」で接続する場合が通例です。
#if defined(SIG_RX62N)
	// BlueBoard-RX62N_100pin
	static constexpr bool LED_ASSERT = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B5, LED_ASSERT> LED;
#elif defined(SIG_RX24T)
	// DIY RX24T board
	static constexpr bool LED_ASSERT = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B0, LED_ASSERT> LED;
#elif defined(SIG_RX71M)
	// DIY RX72M board
	static constexpr bool LED_ASSERT = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B7, LED_ASSERT> LED;
#elif defined(SIG_RX72M)
	// 工事中
	static constexpr bool LED_ASSERT = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B7, LED_ASSERT> LED;
#elif defined(SIG_RX72N)
	// RX72N Envision Kit
	static constexpr bool LED_ASSERT = 0;
	typedef device::PORT<device::PORT4, device::bitpos::B0, LED_ASSERT> LED;
#elif defined(SIG_RX64M)
	// DIY RX64M board
	static constexpr bool LED_ASSERT = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B7, LED_ASSERT> LED;
#elif defined(SIG_RX65N)
	// RX65N Envision Kit
	static constexpr bool LED_ASSERT = 0;
	typedef device::PORT<device::PORT7, device::bitpos::B0, LED_ASSERT> LED;
#elif defined(SIG_RX66T)
	// DIY RX66T board
	static constexpr bool LED_ASSERT = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B0, LED_ASSERT> LED;
#elif defined(SIG_RX72T)
	// DIY RX72T board
	static constexpr bool LED_ASSERT = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B1, LED_ASSERT> LED;
#endif
```

 - BlueBoard-RX62N_100pin の場合、ボード上の D2 赤色 LED を利用する。 
 - Envision kit RX65N の場合、インジケーター LED はボード上の青色 LED を利用する。
 - Envision kit RX72N の場合、インジケーター LED はボード上の青色 LED を利用する。

---

## マスタークロックのブースト
- main 関数に動作が移行したら、内部インストラクションクロックを最大速度にブーストします。
- 内部デバイス用クロックも設定します。（RXxxx/clock_profile.hpp に設定があります）
   
```C++
    SYSTEM_IO::boost_master_clock();
```

---

## リソースの準備
- 特に無し
   
## ビルド方法
- 各プラットホームディレクトリーに移動、make する。
- led_sample.mot ファイルをマイコンに書き込む。
   
## 動作
- LED が 0.25 秒間隔で点滅する。（ソフトウェアーによる遅延ループなので正確ではありません）
    
## 備考
- このプロジェクトが基本で最低限の設定などが含まれます、新しいプロジェクトを始める場合の参考にして下さい。   
   
-----
   
License
----

[MIT](../LICENSE)
