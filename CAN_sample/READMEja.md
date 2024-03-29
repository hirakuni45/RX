Renesas RX62N, RX631, RX64M, RX65N, RX72N, RX71M, RX66T, RX72T CAN 通信サンプル
=========
   
[英語版](README.md)
   
## 概要

RX マイコンを使った CAN 通信サンプルプログラム   
CAN ポートに CAN バス・トランシーバーを接続する必要があります。   
CAN が複数チャネルある場合、チャネルを切り替えて通信する事が出来ます。   
※「main.cpp」で、環境変数「MULTI」を有効にします。
   
## プロジェクト・リスト

- main.cpp
- RX62N/Makefile
- RX631/Makefile
- RX64M/Makefile
- RX65N/Makefile
- RX71M/Makefile
- RX72N/Makefile
- RX66T/Makefile
- RX72T/Makefile
- README.md
- READMEja.md
   
## ハードウェアーの準備

- RXxxx/clock_profile.h で、各モジュール別の設定周波数を宣言している。
- LED を指定のポートに接続する。
- RX72N Envision kit の場合は、ボード上の青色 LED を利用する。
- CAN ポートに、CAN バス・トランシーバーを接続します。(CTX0, CRX0)
- CAN バス・トランシーバーには適切なターミネーター抵抗を接続します。
- CAN バス・トランシーバーは、3.3V で動作する品種が必要です。
   
### CAN ポート設定

CAN バス・トランシーバーを接続するポートは、以下のソースを参照して下さい。   
**実際に接続する場合、ハードウェアーマニュアルを参照して確認して下さい。**    

|マイコン|ファイル|CAN0 候補|CAN1 候補|
|-------|--------|:---:|:---:|
|RX62N  |[RX62x/port_map.hpp](../RX62x/port_map.hpp)|FIRST|X|
|RX631  |[RX63x/port_map.hpp](../RX63x/port_map.hpp)|FIRST|-|
|RX64M  |[RX64M/port_map.hpp](../RX64M/port_map.hpp)|FIRST|FIRST|
|RX65N  |[RX65x/port_map.hpp](../RX65x/port_map.hpp)|FIRST|X|
|RX71M  |[RX64M/port_map.hpp](../RX64M/port_map.hpp)|FIRST|FIRST|
|RX72N  |[RX72N/port_map.hpp](../RX72N/port_map.hpp)|X|SECOND|
|RX66T  |[RX66T/port_map.hpp](../RX66T/port_map.hpp)|FIRST|X|
|RX72T  |[RX72T/port_map.hpp](../RX72T/port_map.hpp)|FIRST|X|
RX65N: RX65N Envision Kit
RX72N: RX72N Envision Kit

CAN0:      
|マイコン|FIRST/CRX0|FIRST/CTX0|\||SECOND/CRX0|SECOND/CTX0|
|-------|:---:|:---:|-|:---:|:---:|
|RX62N  |P33|P32|\||-|-|
|RX631  |P33|P32|\||PD2|PD1|
|RX64M  |P33|P32|\||PD2|PD1|
|RX65N  |P33|P32|\||PD2|PD1|
|RX71M  |P33|P32|\||PD2|PD1|
|RX72N  |P33|P32|\||PD2|PD1|
|RX66T  |P22|P23|\||PA1|PA0|
|RX72T  |P22|P23|\||PA1|PA0|

RX64M の場合 (port_map.hpp FIRST 候補)
```C++
            case peripheral::CAN0:
                {
                    uint8_t sel = enable ? 0b010000 : 0;
                    PORT3::PMR.B2 = 0;
                    PORT3::PMR.B3 = 0;
                    MPC::P32PFS.PSEL = sel;  // CTX0 (P32 LQFP176: 29)
                    MPC::P33PFS.PSEL = sel;  // CRX0 (P33 LQFP176: 28)
                    PORT3::PMR.B2 = enable;
                    PORT3::PMR.B3 = enable;
                }
                break;
```

- main.cpp で、CAN ポート候補を変更する事で、アサインするポートを変更出来ます。
- port_map.hpp には基本的なポート設定が用意されています。

```C++
    static const auto CAN0_PORT = device::port_map::option::FIRST;
    static const auto CAN1_PORT = device::port_map::option::FIRST;
```

---

### CAN バス・トランシーバーの代表的な品種

[Texas Instruments: SN65HVD23x](https://www.ti.com/jp/lit/ds/symlink/sn65hvd230.pdf?ts=1604189973572&ref_url=https%253A%252F%252Fwww.google.com%252F)
- 3.3V 動作
- 5V 不可
- 最大 1 Mbit/s

[NXP Semiconductors: TJA1441](https://www.nxp.com/docs/en/data-sheet/TJA1441.pdf)
- 電源 5V
- I/O 3.3V、5V 選択可
- 最大 5 Mbit/s
   
---

### RX62N の場合

- CAN0 を利用
- FRK-RX62N(CQ 出版社) で動作確認

### RX631 の場合

- CAN0 を利用
- GR-CITRUS で動作確認

### RX64M/RX71M の場合

- CAN0/CAN1 複数チャネル対応
- DIY ボードで動作確認
   
### RX66T/RX72T の場合

- CAN0 を利用
- DIY ボードで動作確認

### RX65N Envision Kit の場合

- プログラムは複数チャネルに対応していますが、CAN ポートにアクセス出来ない為、シングルチャネルです。
- CAN0 を使います。
- CN13 (2) P32 (CTX0)
- CN13 (3) P33 (CRX0)
- CN8  (2) 3.3V
- CN8  (4) GND
- CN8  (5) GND

### RX72N Envision Kit の場合

- プログラムは複数チャネルに対応していますが、CAN ポートにアクセス出来ない為、シングルチャネルです。
- CAN1 を使います。
- Pmod1  (1) P54_SS    (CTX1)
- Pmod1  (7) P55/IRQ10 (CRX1)
- Pmod1  (6) 3.3V
- Pmod1 (12) 3.3V
- Pmod1  (5) GND
- Pmod1 (11) GND

---

## can_analize クラスによるパケット情報収集

CAN0 に対応するインスタンスは「[can_analize](../common/can_analize.hpp?ts=4)」クラスによるパケットの収集を行っています。

- 任意の ID、それに関する情報収集。
- データ列の収集。（最後に取得した８バイトのみ）
- 受信した回数。
- std::map による、ID の違いによるマッピング。（表示順番が整列されて表示）
- boost::unordered_map を使う事も出来ます。（その場合、CAN-ID の表示順番は不定です）
- boost::unordered_map を使うと実行バイナリが若干小さくなります。（記憶割り当ても小さくなります） 
   
|プロジェクト|RX62N|RX631|RX64M|RX65N|RX71M|RX72N|RX66T|RX72T|
|---|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|動作確認|〇|〇|〇|－|－|－|－|〇|
   
動作確認：   
実際に CAN バスを接続し、相互の通信を行って通信を確認した。   
ハードに依存する port_map クラスの実装が適切で、コンパイルが通れば、問題無いと思います。   

---

## 対話コマンド

対話形式で、CAN データ送信、受信の確認等が出来ます。

- プログラムを起動すると、常に全ての ID を受信します。
- ID の収集は「can_analizer」クラスで行っており、boost::unoderd_map を使っています。
- ID の収集がメモリの限界を超えると、メモリ不足でエクセプションがスローされてクラッシュすると思われます。
- send_loop コマンドにより、乱数で生成した ID、データを連続で送信します。
- ID を補足する機能（map）は、チャネル０番のみに備わっています。
- RX64M/RX71M では、２チャネルの CAN を有効にします。
- CAN1 の受信では、受信したデータを常に表示します。
- MB-no はメールボックスの番号です。
- メールボックス関係のコマンドは、デバッグ用です。
- 受信した CAN フレームは、メモリに格納され、「dump」コマンドで確認出来ます。
- 同じ ID に新しいデータフレームが来ると、上書きされ、カウンタが進みます。

```
CAN command version: 1.00
    ext                    set ext-id mode
    std                    set std-id mode
    send CAN-ID [data...]  send data frame
    stat MB-no             stat MCTLx register (MB-no: 0 to 31)
    list MB-no             list MBx register (MB-no: 0 to 31)
    status                 list recv/send error count
    clear [CAN-ID]         clear map
    map [CAN-ID]           Display all collected IDs
    dump CAN-ID            dump frame data
    send_loop NUM [-rtr]   random ID, random DATA, send loop (RTR)
    help                   command list (this)

  Input number: nnn decimal, xnnn hexa-decimal, bnnn binary
```

### ch コマンド

- 「#define MULTI」を有効にした場合で、CAN1 のインスタンスがある場合に、カレントチャネルを変更する。

### valid コマンド

- VALID フィルターを有効にする、無効にする。

### valist コマンド

- 有効な ID リストを表示。

### std コマンド

- 標準 ID モードにする。（11 ビット）

### ext コマンド

- 拡張 ID モードにする。（29 ビット）

### send CAN-ID [data...] コマンド

- ID を指定して、データ列を送信。
- ID のみの場合、リモートフレームの送信。
- 最大８バイトのデータ列送信。
- 数値は、１０進数、１６進数（先頭に x を付ける）、２進数（先頭に b を付ける）を入力可能。
   
### stat MB-no コマンド（デバッグ用）

- CAN MCTLx レジスターの表示。
- MB-no は、０～３１

### list MB-no コマンド（デバッグ用）

- CAN MBx レジスターの表示。
- MB-no は、０～３１

### clear [CAN-ID] コマンド

- can_analizer クラスの個別 ID 情報のクリア。
- can_analizer クラスの収集履歴を全てクリア。

### map [CAN-ID] コマンド

- can_analizer クラスが収集した ID の表示。
- 個別 ID の詳細表示。

### dump [CAN-ID] コマンド

- can_analizer クラスの個別 ID に関するフレームデータ表示。
- フレームデータは、その ID が最後に取得したものになります。

### send_loop [num] コマンド

- ID を乱数で生成して、データ送信を行う。
- データ送信を繰り返す数を指定する。

### help コマンド

- コマンドの簡単な説明を表示。

---

## CAN/ID フィルター

main.cpp には、通過する事が出来る ID リストを使った、フィルターのサンプルコードが含まれます。   

- この機能は、「MULTI」チャネルを有効にした場合に利用されます。
- 複数チャネルで、CAN1 のインスタンスに対して適用されます。    
- フィルターには、「boost/unordered_set」を利用しています。 
- main.cpp の先頭で、「#define VALID_FILTER」をコメントアウトすると、フィルターを無効にします。 
- 有効な ID テーブルは、以下のようになっています。
- boost::unordered_set を使っています。
- ID の追加、削除など、動的に行えます。

```C++
#include <boost/unordered_set.hpp>

	// 有効な ID だけ通すフィルター
	typedef boost::unordered_set<uint32_t> VALID;
//	typedef const boost::unordered_set<uint32_t> VALID;
	VALID	valid_{ 0x123, 0x200, 0x300, 0xaaa, 15, 21, 33 };
```
   
メインループで、CAN1 の受信フレームをディスパッチする際に、ID が有効か確認し、無効な ID を無視します。
   
```C++
		while(can1_.get_recv_num() > 0) {
			auto frm = can1_.get_recv_frame();
#ifdef VALID_FILTER
			if(valid_.find(frm.get_id()) != valid_.end()) {
#else
			{
#endif
				utils::format("\nCAN1:\n");
				CAN::list(frm, "  ");
			}
		}
```

---

## リソースの準備

- CAN バスに適切な CAN バストランシーバーを接続する。
- CAN バスにターミネーター抵抗を接続する。

CAN-BUS トランシーバー SN65HVD230 の参考回路：   
<img src="../docs/CAN_IF.png" width="75%">

---

## ビルド方法

- 各プラットホームディレクトリーに移動、make する。
- can_sample.mot ファイルを書き込む。

---

## 動作

- LED が 0.25 秒間隔で点滅する。
- ターミナルでシリアル接続を行い、対話式コマンドで通信を行う。
   
---
   
## License

boost:
  [Boost Software License](https://www.boost.org/users/license.html)

[MIT](../LICENSE)
