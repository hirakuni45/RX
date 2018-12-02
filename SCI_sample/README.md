Renesas RX24T, RX64M, RX71M, RX65N, RX66T SCI (UART) サンプル
=========

## 概要
RX マイコンを使った SCI (UART) のサンプルプログラム
   
## プロジェクト・リスト
 - main.cpp
 - RX24T/Makefile
 - RX64M/Makefile
 - RX71M/Makefile
 - RX65N/Makefile
 - RX66T/Makefile
   
## ハードウェアーの準備（全般）
 - ベースクリスタルが異なる場合は、typedef のパラメーターを変更する。
 - Makefile で、各モジュール別の設定周波数を宣言している。
 - RX24T:  80MHz (10MHz)
 - RX64M: 120MHz (12MHz)
 - RX71M: 240MHz (12MHz)
 - RX65N: 120MHz (12MHz)
 - RX66T: 160MHz (10MHz)
 - インジケーター LED を指定のポートに接続する。
 - USB シリアルの信号と設定の SCI ポートを接続する。
 - RX6x, RX71M, SCI の標準ポートは、「RX600/port_map.hpp」参照。
 - RX24T, SCI の標準ポートは、「RX24T/port_map.hpp」参照。
```
#if defined(SIG_RX64M)
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX64M" };
#elif defined(SIG_RX71M)
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX71M" };
#elif defined(SIG_RX65N)
	typedef device::system_io<12000000> SYSTEM_IO;
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
	typedef device::SCI9 SCI_CH;
	static const char* system_str_ = { "RX65N" };
#elif defined(SIG_RX24T)
	typedef device::system_io<10000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX24T" };
#elif defined(SIG_RX66T)
	typedef device::system_io<10000000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX66T" };
#endif
```
 - 標準的には、RX24T, RX66T の場合「10MHz」、他 CPU は「12MHz」のクリスタル。
 - Envision kit RX65N の場合、インジケーター LED はボード上の青色を利用する。
   
## ハードウェアーリソースの準備
 - SCI に指定されたポートに USB シリアルなどの変換器を接続する。
 - マイコン側の RXD 端子と、USB シリアルの TXD を接続。
 - マイコン側の TXD 端子と、USB シリアルの RXD を接続。
   
## ビルド方法
 - 各プラットホームディレクトリーに移動、make する。
 - sci_sample.mot ファイルを書き込む。
   
## 動作
 - LED が 0.25 秒間隔で点滅する。
 - SCI に指定されたポートで、TX（送信）、RX（受信）を行う。
 - TeraTerm などで確認。
 - TeraTerm のシリアル設定：１１５２００ボー、８ビットデータ、１ストップ、パリティ無し。
 - main.cpp の中、SCI の初期化でボーレートは自由に設定できる。
 - 設定出来ない「値」の場合、初期化が失敗する。（極端に遅い、早い）
    
## 備考
 - FIFO バッファは、受信側 256 バイト、送信側 512 バイトとなっている。
 - ボーレート、受信頻度、送信頻度などを考慮して、適切な値に調整する。
 - 最小は 16 バイト程度。
 - FIFO バッファより大きい文字列を送る場合、バッファが空くまで待機する事になる。
 - 受信時、バッファからの取り出し速度が、受信速度を下回ると、オーバーフローして、文字を紛失する。
 - SCI のチャネルを変更する場合「main.cpp」で「typedef」してある定義を変更する。
 - SCIx とポート接続の関係性は、RX600/port_map.hpp を参照する。
 - port_map クラスは、169 ピンデバイスのポートを基準にしたアサインになっている。
 - ピン番号以外は、144ピン、100ピン、デバイスでも同じように機能する。
 - 第二候補を選択する場合は、sci_io の typedef で、「device::port_map::option::SECOND」を追加する。
 - 別プログラムによって、雑多な設定を自動化してソースコードを生成する試みを行っている場合がありますが、それは、基本的に間違った方法だと思えます、設定の修正が必要な場合、必ず生成プログラムに戻って、生成からやり直す必要があります。
 - C++ テンプレートは、チャネルの違いや、ポートの違い、デバイスの違いをうまく吸収して、柔軟で、判りやすい方法で実装できます。
   
## 標準出力の対応
 - main.cpp には、標準出力（printf）に対応する事が出来る「枝」を出してあります。
 - 「sci_putch」などですが、これらの関数は、POSIX 関数、write などから、特定のディスクリプタ（stdout）で呼ばれるような仕組みが実装されています。（common/syscalls.c）
 - なので、printf 関数は普通に使えるのですが、C++ では推奨しません。（使う理由が無い）
 - printf は、引数が可変引数になっていて、スタック経由なので、format 文と引数に反故がある場合、クラッシュする事もあります、コンパイラのチェックでは完全に「反故」を見つける事は困難です、従って、どんなに便利でも使ってはいけません。
 - 代わりに、utils::format クラスを利用して下さい、printf とほぼ同じように使えて、間違った引数でもクラッシュする事はありません。
 - C++ の標準出力機能「std::cout」は、メモリを大量に消費し、実質的に利用出来ない為非推奨としています。
   
-----
   
License
----

MIT
