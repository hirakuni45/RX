Renesas RX24T, RX64M, RX71M, RX65N SCI (UART) サンプル
=========

## 概要
RX マイコンを使った SCI (UART) のサンプルプログラム
   
## プロジェクト・リスト
 - main.cpp
 - RX24T/Makefile
 - RX64M/Makefile
 - RX71M/Makefile
 - RX65N/Makefile
   
## ハードウェアーの準備
 - ベースクリスタルが異なる場合は、typedef のパラメーターを変更する。
 - Makefile で、各モジュール別の設定周波数を宣言している。
 - RX24T: 80MHz、RX64M: 120MHz、RX71M: 240MHz、RX65N: 120MHz
 - LED を指定のポートに接続する。
```
#if defined(SIG_RX64M) | defined(SIG_RX71M)
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
#elif defined(SIG_RX65N)
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
#elif defined(SIG_RX24T)
	typedef device::system_io<10000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
#endif
```
 - RX24T の場合「10MHz」、他 CPU は「12MHz」
 - Envision kit RX65N の場合は、ボード上の青色 LED を利用する。
   
## リソースの準備
 - SCI に指定されたポートに USB シリアルなどの変換器を接続する。
 - マイコン側の RXD 端子と、USB シリアルの TXD を接続。
 - マイコン側の TXD 端子と、USB シリアルの RXD を接続
   
## ビルド方法
 - 各プラットホームディレクトリーに移動、make する。
 - sci_sample.mot ファイルを書き込む。
   
## 動作
 - LED が 0.25 秒間隔で点滅する。
 - SCI に指定されたポートで、TX（送信）、RX（受信）を行う。
 - TeraTerm などで確認。
 - TeraTerm のシリアル設定：１１５２００ボー、８ビットデータ、１ストップ、パリティ無し。
    
## 備考
このプロジェクトが基本で最低限の設定などが含まれます、新しいプロジェクトを   
始める場合の参考にして下さい。   
   
-----
   
License
----

MIT
