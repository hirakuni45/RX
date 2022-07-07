Renesas RX24T, RX64M, RX65N, RX71M, RX66T, RX72N, RX72T LED 点滅サンプル
=========
   
[英語版](README.md)
   
## 概要
RX マイコンを使った LED 点滅のサンプルプログラム
   
- マスタークロックのブースト
- LED の点滅
   
## プロジェクト・リスト
- main.cpp
- RX24T/Makefile
- RX64M/Makefile
- RX71M/Makefile
- RX65N/Makefile (for RX65N Envision Kit)
- RX66T/Makefile
- RX72N/Makefile (for RX72N Envision Kit)
- RX72T/Makefile
   
## ハードウェアーの準備（全般）
 - 各マイコンの、クリスタル周波数、各モジュールの周波数は、RXxxx/clock_profile.hpp を参照して下さい。
 - インジケーター LED を指定のポートに接続する。
   
```C++
#if defined(SIG_RX71M)
	static const char* system_str_ = { "RX71M" };
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
#elif defined(SIG_RX64M)
	static const char* system_str_ = { "RX64M" };
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
#elif defined(SIG_RX65N)
	static const char* system_str_ = { "RX65N" };
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
#elif defined(SIG_RX24T)
	static const char* system_str_ = { "RX24T" };
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
#elif defined(SIG_RX66T)
	static const char* system_str_ = { "RX66T" };
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
#elif defined(SIG_RX72N)
	static const char* system_str_ = { "RX72N" };
	typedef device::PORT<device::PORT4, device::bitpos::B0> LED;
#elif defined(SIG_RX72T)
	static const char* system_str_ = { "RX72T" };
	typedef device::PORT<device::PORT0, device::bitpos::B1> LED;
#endif
// クロックの定義は、「RXxxx/clock_profile.hpp」を参照。
	typedef device::system_io<> SYSTEM_IO;
// 内蔵、高速発信器の利用
//	typedef device::system_io<device::system_base::OSC_TYPE::HOCO> SYSTEM_IO;
```

 - Envision kit RX65N の場合、インジケーター LED はボード上の青色 LED を利用する。
 - Envision kit RX72N の場合、インジケーター LED はボード上の青色 LED を利用する。
   
## マスタークロックのブースト
- main 関数に動作が移行したら、内部インストラクションクロックを最大速度にブーストします。
- 内部デバイス用クロックも設定します。（RXxxx/clock_profile.hpp に設定があります）
   
```C++
    SYSTEM_IO::boost_master_clock();
```
   
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
