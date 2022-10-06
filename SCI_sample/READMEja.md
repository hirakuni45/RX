Renesas RX62N, RX24T, RX64M, RX71M, RX65N, RX66T, RX72T, RX72N SCI (UART) サンプル
=========

[英語版](README.md)

---

## 概要

RX マイコンを使った SCI (UART) のサンプルプログラム
   
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
- RX62N の
- RX24T の SCI 標準ポートは、「RX24T/port_map.hpp」参照。
- RX64M/RX71M の SCI 標準ポートは、「RX600/port_map.hpp」参照。
- RX65x の SCI 標準ポートは、「RX65x/port_map.hpp」参照。
- RX72N の SCI 標準ポートは、「RX72N/port_map.hpp」参照。
- RX66T の SCI 標準ポートは、「RX66T/port_map.hpp」参照。
- RX72T の SCI 標準ポートは、「RX72T/port_map.hpp」参照。

```C++
#if defined(SIG_RX62N)
	static const char* system_str_ = { "RX62N BlueBoard-RX62N_100pin" };
	typedef device::PORT<device::PORT0, device::bitpos::B5, false> LED;
	typedef device::SCI0 SCI_CH;
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
 - sci_sample.mot ファイルを書き込む。

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

## 標準出力の対応
 - main.cpp には、標準出力（printf）に対応する事が出来る「枝」を出してあります。
 - 「sci_putch」などですが、これらの関数は、POSIX 関数、write などから、特定のディスクリプタ（stdout）で呼ばれるような仕組みが実装されています。 [common/syscalls.c](../common/syscalls.c)
 - なので、printf 関数は普通に使えるのですが、C++ では推奨しません。（使う理由が無い）
 - printf は、引数が可変引数になっていて、スタック経由なので、format 文と引数に反故がある場合、クラッシュする事もあります、コンパイラのチェックでは完全に「反故」を見つける事は困難です、従って、どんなに便利でも使ってはいけません。
 - 代わりに、utils::format クラスを利用して下さい、printf とほぼ同じように使えて、間違った引数でもクラッシュする事はありません。
 - C++ の標準出力機能「std::cout」は、メモリを大量に消費し、実質的に利用出来ない為非推奨としています。
 - std::string などの STL を使いたい場合、Makefile の USER_LIBS に、stdc++ などの STL ライブラリを追加します。
 - STL を使う場合、記憶割り当てを多用するので、十分な RAM が必要です。

 ---

 ## POSIX 関数と文字出力のしくみと考察
 - 通常、printf や、iostream の cout に文字出力を行った場合、内部では、POSIX 関数を経由して行います。   
 - これは、歴史的な背景や、シンプルな構造に対する考え方などがベースにあります。
 - アプリケーションが起動すると、３つの特別なファイルがオープンされた状態になっています。
 - これは、それぞれ、stdin(0)、stdout(1)、stderr(2) です。
 - アプリケーションは、この決められたファイルハンドルを使って、通常のファイルと同じようにアクセスする事で、文字の入出力を行います。
 - この C++ フレームワークでも、その仕組みを使います。
 - [common/syscalls.c](../common/syscalls.c) にその実装があります。（POSIX 関数郡）
 - その中で、write 関数では、stdout、stderr、宛に出力を行った場合、sci_putch 関数を呼び出します。
 - read 関数では、stdin から、sci_getch 関数からデータを受け取ります。(データが来るまでブロックされます)
 - [main.cpp](main.cpp) には、SCI の入出力と、POSIX 関数を繋ぐ為、sci_putch、sci_getch 関数を定義してあります。
 - 従って、文字の入出力を行うアプリケーションを実装する場合、syscalls.c を必ずリンクする必要があります。
 - ちなみに、SD カードアクセスを行う場合も POSIX 関数を実装する事で、標準関数を使ってファイルのやりとりが行えます。

syscalls.c 内、write 関数の sci_putch 呼び出し：   

```
_READ_WRITE_RETURN_TYPE write(int file, const void *ptr, size_t len)
{
	if(ptr == NULL) return 0;

	_READ_WRITE_RETURN_TYPE l = -1;
	if(file >= 0 && file <= 2) {
		if(file == 1 || file == 2) {
			const char *p = ptr;
			for(int i = 0; i < len; ++i) {
				char ch = *p++;
				sci_putch(ch);
			}
			l = len;
			errno = 0;
		}
	}
```
   
syscalls.c 内、read 関数の sci_getch 呼び出し：   

```
_READ_WRITE_RETURN_TYPE read(int file, void *ptr, size_t len)
{
	if(ptr == NULL) return 0;

	_READ_WRITE_RETURN_TYPE l = 0;
	if(file >= 0 && file <= 2) {
		// stdin
		if(file == STDIN_FILENO) {
			char *p = ptr;
			for(int i = 0; i < len; ++i) {
				char ch = sci_getch();
				sci_putch(ch);  // エコーバック
				// 改行コードを変換する
				if(ch == '\r') ch = '\n';
				*p++ = ch;
			}
			errno = 0;
			l = len;
		}
	}
```

main.cpp sci_putch、sci_getch の定義：   

```
extern "C" {

	// syscalls.c から呼ばれる、標準出力（stdout, stderr）
	void sci_putch(char ch)
	{
		sci_.putch(ch);
	}

	void sci_puts(const char* str)
	{
		sci_.puts(str);
	}

	// syscalls.c から呼ばれる、標準入力（stdin）
	char sci_getch(void)
	{
		return sci_.getch();
	}

	uint16_t sci_length()
	{
		return sci_.recv_length();
	}
}
```
---

## std::iostream が非推奨な理由と代替え方法
- C++ では、通常、文字の入出力は、iostream を使います。
- ですが、iostream はかなり巨大でメモリを大量に消費します。
- 組み込み系のマイコンでは、RAM、ROM 共に限られた容量なので、通常利用が困難です。
- その為、この C++ フレームワークでは、それらを利用しない方法を提案しています。
- これは、[common/format.hpp](../common/format.hpp) を利用する事で実現できるように配慮されています。
- [common/format.hpp](../common/format.hpp) は、iostream や、printf を置き換えるものです。
- 文字のフォーマットは、ほぼ、printf に準拠してあり、スタックを使わない方法で、パラメータの受け渡しを行います。

---

## サポートされている通信プロトコル

```
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	SCI 通信プロトコル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class PROTOCOL : uint8_t {
			B7_N_1S,	///< 7 ビット、No-Parity、1 Stop Bit
			B7_E_1S,	///< 7 ビット、Even(偶数)、1 Stop Bit
			B7_O_1S,	///< 7 ビット、Odd (奇数)、1 Stop Bit
			B7_N_2S,	///< 7 ビット、No-Parity、2 Stop Bits
			B7_E_2S,	///< 7 ビット、Even(偶数)、2 Stop Bits
			B7_O_2S,	///< 7 ビット、Odd (奇数)、2 Stop Bits
			B8_N_1S,	///< 8 ビット、No-Parity、1 Stop Bit
			B8_E_1S,	///< 8 ビット、Even(偶数)、1 Stop Bit
			B8_O_1S,	///< 8 ビット、Odd (奇数)、1 Stop Bit
			B8_N_2S,	///< 8 ビット、No-Parity、2 Stop Bits
			B8_E_2S,	///< 8 ビット、Even(偶数)、2 Stop Bits
			B8_O_2S,	///< 8 ビット、Odd (奇数)、2 Stop Bits
		};
```

- 何も設定しない場合、通信プロトコルは「B8_N_1S」が使われます。
   
他の指定をする場合：

```
		uint8_t intr = 2;        // 割り込みレベル（０を指定すると、ポーリング動作になる）
		uint32_t baud = 115200;  // ボーレート（任意の整数値を指定可能）
		auto protocol = SCI::PROTOCOL::B8_E_2S;  // 8 ビット、Even(偶数)、2 Stop Bits
		sci_.start(baud, intr, protocol);
```

---

## ボーレート

- ボーレートは、整数で指定しますが、良く使われるボーレートは設定がありますので利用する事があります。

```
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	SCI ボーレート型（シリアル通信で標準的に指定する定型値）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class BAUDRATE : uint32_t {
			B110    =    110,	///<    110 B.P.S.
			B150    =    150,	///<    150 B.P.S.
			B300    =    300,	///<    300 B.P.S.
			B600    =    600,	///<    600 B.P.S.
			B1200   =   1200,	///<   1200 B.P.S.
			B2400   =   2400,	///<   2400 B.P.S.
			B4800   =   4800,	///<   4800 B.P.S.
			B9600   =   9600,	///<   9600 B.P.S.
			B19200  =  19200,	///<  19200 B.P.S.
			B38400  =  38400,	///<  38400 B.P.S.
			B57600  =  57600,	///<  57600 B.P.S.
			B76800  =  76800,	///<  76800 B.P.S.
			B96000  =  96000,	///<  96000 B.P.S.
			B115200 = 115200,	///< 115200 B.P.S.
		};
```
   
```
		uint8_t intr = 2;        				 // 割り込みレベル（０を指定すると、ポーリング動作になる）
		auto protocol = SCI::PROTOCOL::B8_E_2S;  // 8 ビット、Even(偶数)、2 Stop Bits
		sci_.start(SCI::BAUDRATE::B115200, intr, protocol);  // 115200 B.P.S.
```

---
   
License
   
[MIT](../LICENSE)
