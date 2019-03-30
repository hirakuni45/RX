Renesas RX24T, RX71M, RX64M, RX65N, RX66T LED 点滅サンプル
=========

## 概要
RX マイコンを使った LED 点滅のサンプルプログラム
   
## プロジェクト・リスト
- main.cpp
- RX24T/Makefile
- RX64M/Makefile
- RX71M/Makefile
- RX65N/Makefile
- RX66T/Makefile
   
## ハードウェアーの準備
- ベースクリスタルが異なる場合は、typedef のパラメーターを変更する。
- Makefile で、各モジュール別の設定周波数を宣言している。
- RX24T:  80MHz (10MHz)
- RX64M: 120MHz (12MHz)
- RX71M: 240MHz (12MHz)
- RX65N: 120MHz (12MHz)
- RX66T: 160MHz (10MHz)
- LED を指定のポートに接続する。
```
#if defined(SIG_RX71M)
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
#elif defined(SIG_RX64M)
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
#elif defined(SIG_RX65N)
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
#elif defined(SIG_RX24T)
	typedef device::system_io<10000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
#elif defined(SIG_RX66T)
	typedef device::system_io<10000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
#endif
```
- Envision kit RX65N の場合は、ボード上の青色 LED を利用する。
   
## リソースの準備
- 特に無し
   
## ビルド方法
- 各プラットホームディレクトリーに移動、make する。
- led_sample.mot ファイルを書き込む。
   
## 動作
- LED が 0.25 秒間隔で点滅する。
    
## 備考
- このプロジェクトが基本で最低限の設定などが含まれます、新しいプロジェクトを始める場合の参考にして下さい。   
   
-----
   
License
----

[MIT](../LICENSE)
