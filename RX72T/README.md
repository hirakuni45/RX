Renesas RX72T 専用ファイル
=========

## 概要

ルネサス RX72T 専用ハードウェアー定義 C++ テンプレート・クラス   
ルネサスが提供する、iodefine.h は C言語の規約に違反している為、特定の環境でしか正しくコンパイルする事が出来ません。   
※ビットフィールドの定義は、バイトサイズのみ準拠しますが、１６ビット、又はそれ以上は、エンディアンの関係などから、結果はコンパイラに依存します。   
   
また、非常に冗長であり、可読性が悪いです。   
※独自の方法を使い、プログラムで生成しているものと思います。   
   
---
   
C++ テンプレートを活用したハードウェアー定義（ＲＸマイコンフレームワーク）は、C++17 準拠のコンパイラならエラー無くコンパイルする事が可能で、ハードウェアー・マニュアルのレジスター説明に準拠した正式な名称を使っています。   

- 名前空間を利用してあり、名称の衝突を避ける事が出来ます。
- #define を使っていないので、名称がグローバル名と衝突しません。

```
    device::CMT0::CMCR.CKS = 2;  // CMT0 クロック選択
```
   
一報「iodefine.h」では、ビットフィールド定義の構造上、ビットアクセス、ワードアクセスで異なった、インスタンスを付加する必要があり冗長です。   

- #define を使用しており「CMT0」は他で利用する事が出来ません。
- アクセスに対する動作で、リード、ライトが明確ではありません。
   
```
    CMT0.CMCR.BIT.CKS = 2; // CMT0 クロック選択
```
   
ハードウェアーマニュアルに沿った、モジュール別にソースを分割しています。   
   
テンプレートクラスなので、最適化も最大限活用でき、必要なら、さらなる最適化に向けた実装の余地もあります。   
   
```
    uint8_t tmp = device::CMT0::CMCR.CKS();
```

レジスタの読出し動作と書き込み動作を明確にする為、上記のようにして、読出しを行います。   
   
専用のマネージャークラスを用意してあり、別プログラムを使って、コードを生成する必要がありません。   
この為、ソースコードの管理が統一的で、見通しが良く、全体を見渡す事が出来ます。   
※ほとんどのコードはヘッダーのみなので、リンクファイルを追加する必要がありません。   
   
---

## ペリフェラル名

 - 各デバイスモジュールを抽象化する為、ペリフェラル名（型）を定義しています。
 - デバイスモジュールクラス名とは異なる概念です。
 - 「ペリフェラル名」は、なるべく、ハードウェアーマニュアルで説明されているキーワード
を使うようにしています、詳しくは、[peripheral.hpp](peripheral.hpp?ts=4)を参照して下さい。
 - この名称は、省電力切り替え、専用ポート制御、割り込み制御など、多様な場面で、識別子として使われており、ペリフェラル全体で必要な細かい設定を自動化する為に使われます。
   
たとえば、コンペアマッチタイマー０は、「device::peripheral::CMT0」となります。   
この名称を使って、全体を参照する場合もあります。   
   
---

## ポート候補
   
このフレームワークでは、ポートの機能を選択する方法として、「ポート・マップ」と呼ばれる機構を使っています。   
この機能と、各ペリフェラル用に実装されたマネージャークラスにより、簡単に各機能を利用する事が出来ます。   
   
たとえば、SCI1 を使う場合、port_map.hpp を参照すると・・・   

```
		static bool sci1_(ORDER opt, bool enable, bool clock)
		{
			uint8_t sel = enable ? 0b001010 : 0;
			switch(opt) {
			case ORDER::FIRST:
			// PD5/RXD1 (20/100) (25/144)
			// PD4/SCK1 (21/100) (26/144)
			// PD3/TXD1 (22/100) (27/144)
				if(clock) {
					PORTD::PMR.B4 = 0;
					MPC::PD4PFS.PSEL = sel;
					PORTD::PMR.B4 = enable;
				}
				PORTD::PMR.B3 = 0;
				PORTD::PMR.B5 = 0;
				MPC::PD3PFS.PSEL = sel;
				MPC::PD5PFS.PSEL = sel;
				PORTD::PMR.B3 = enable;
				PORTD::PMR.B5 = enable;
				break;
			case ORDER::SECOND:
			// P25/SCK1 (94/144)
			// PC4/TXD1 (98/144)
			// PC3/RXD1 (99/144)
				if(clock) {
					PORT2::PMR.B5 = 0;
					MPC::P25PFS.PSEL = sel;
					PORT2::PMR.B5 = enable;
				}
				PORTC::PMR.B4 = 0;
				PORTC::PMR.B3 = 0;
				MPC::PC4PFS.PSEL = sel;
				MPC::PC3PFS.PSEL = sel;
				PORTC::PMR.B4 = enable;
				PORTC::PMR.B3 = enable;
				break;
			default:
				return false;
			}
			return true;
		}
```

となっており、以下のように「typedef」する事で、簡単にポートの機能を選択する事が出来ます。   

```
	typedef utils::fixed_fifo<char, 512> RXB;  // RX (受信) バッファの定義
	typedef utils::fixed_fifo<char, 256> TXB;  // TX (送信) バッファの定義
    typedef device::sci_io<device::SCI1, RXB, TXB, device::port_map::ORDER::SECOND> SCI1_IO;
    SCI1_IO sci_io_;
```
   
同じように、port_map_mtu.hpp、port_map_gptw.hpp なども用意されています。   
   
---

## 割り込みベクター名

 - 各デバイスが扱う割り込みベクターも、抽象化の為定義されています。
 - 割り込みベクターは、通常ベクター、グループベクター、選択型ベクターなど特有の型を持っており、型の違いを利用して、設定方法が異なる場合でも、統一した設定方法になるように工夫してあります。   

IRQ0, IPR レジスタのアクセス例：

 ```
    device::ICU::IPR.IRQ0 = 1;

又は・

    device::ICU::IPR[device::ICU::VECTOR::IRQ0] = 1;
 ```

---

## RX72T 専用ファイル・リスト

|ファイル名|内容|
|------|------|
|[R5F572TK.ld](R5F572TK.ld?ts=4)|R5F572TK リンカースクリプト (RAM:128K, ROM:1M)|
|[R5F572TE.ld](R5F572TE.ld?ts=4)|R5F572TE リンカースクリプト (RAM:128K, ROM:512K)|
|[clock_profile.hpp](clock_profile.hpp?ts=4)|クロックプロファイル|
|[peripheral.hpp](peripheral.hpp?ts=4)|ペリフェラル定義|
|[system.hpp](system.hpp?ts=4)|システム関係の定義|
|[icu.hpp](icu.hpp?ts=4)|割り込みコントローラ（ICUA）定義|
|[icu_mgr.hpp](icu_mgr.hpp?ts=4)|割り込みマネージャー|
|[port_map.hpp](port_map.hpp?ts=4)|I/Oポート・マップ定義|
|[port_map_gptw.hpp](port_map_gptw.hpp?ts=4)|GPTW マップ定義|
|[port_map_mtu.hpp](port_map_mtu.hpp?ts=4)|MTU マップ定義|
|[power_mgr.hpp](power_mgr.hpp?ts=4)|電源マネージャー|
   
---

## 標準的なクロックソース

- RX72T の最大周波数は 200MHz ですが、USB を使う前提だと、192MHz (8MHzx24) で動作させる事になります。
- 上記二種類の場合に都合が良いクリスタルは 16MHz となります。
- 標準的なクロックプロファイルは、200MHz となります。
- USB を使う場合、Makefile 「USER_DEFS」に、「USE_USB」を追加して下さい。（192MHz のクロックプロファイルが選択）
- main 関数の先頭で、「device::boost_master_clock()」を呼び出す事で、最大速度になります。
   
```
    typedef device::system_io<> SYSTEM_IO;
    SYSTEM_IO::boost_master_clock();
```

-----
   
License
----

MIT

