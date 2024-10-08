Renesas RX マイコン・フラッシュ・プログラミング・ツール (rx_prog)
=========
![R5F564ML](../docs/RX600_group.jpg)

## 概要
シリアルインターフェースを使って、RX マイコンのフラッシュメモリーにプログラムを書き込む為のツール
   
---
## プロジェクト・リスト
 - main.cpp
 - area.hpp
 - conf_in.hpp
 - file_io.cpp
 - file_io.hpp
 - motsx_io.hpp
 - rs232c_io.hpp
 - rx_prog.hpp
 - rx_protocol.hpp
 - rx220_protocol.hpp
 - rx23x_protocol.hpp
 - rx24t_protocol.hpp
 - rx26t_protocol.hpp
 - rx62x_protocol.hpp
 - rx63x_protocol.hpp
 - rx64m_protocol.hpp
 - rx65x_protocol.hpp
 - rx66t_protocol.hpp
 - rx72t_protocol.hpp
 - sjis_utf16.cpp
 - sjis_utf16.hpp
 - string_utils.cpp
 - string_utils.hpp
 - Makefile
 - rx_prog.conf
 - USB_CP2102N ---> KiCAD CP2102N USB シリアルボードプロジェクト（回路図、PCB トラック、ガーバー）
   
---
## ビルド（コンパイル）環境の準備（Windows）
 - MSYS2 のセットアップ
 - gcc 関係のインストール
 - boost は、1.74.0 を使いますので、事前にダウンロード（D:￥Download へ配置）して下さい。（boost_1_74_0.tar.gz）
 - C ドライブのルートに展開します
 - 以前は、MSYS2 pacman で mingw64 環境用をインストールしていましたが、最新バージョンで問題が発生する為

```bash
cd /c/
tar xfvz /d/Download/boost_1_74_0.tar.gz
```
   
- RX/READMEja.md の開発環境準備を参照
   
---
## ビルド方法、環境設定
 - make する
 - make install により、設定ファイルと実行ファイルをコピー (/usr/local/bin)
 - /usr/local/bin にパスを通す
   
---

## 接続準備（シリアル接続）

- マイコン側の VSS 端子と、USB シリアルの GND を接続。
- マイコン側の RXD1 端子と、USB シリアルの TXD を接続。
- マイコン側の TXD1 端子と、USB シリアルの RXD を接続。
※ブート時のＳＣＩポート（通常 SCI1 です、要確認ハードウェアーマニュアル）   
- UB 端子があるデバイス（USB I/F がある）の場合、プルダウンする。(4.7K)
- EMLE 端子がある場合プルダウンする。（4.7K）
- MD 端子を「Low レベル」にして「リセット」信号を入れる。
- 内臓プログラムを実行する場合は MD 端子を「High レベル」にして、リセット信号を入れる。
- MDE(13) は 0 (リトルエンディアンとする)

---
## 接続端子一覧

### RX140:

|端子|LFQFP 64|
|---|---|
|MD|MD(3)|
|RXD|P30/RXD1(14)|
|TXD|P26/TXD1(16)|

|モード|MD|
|---|:---:|
|シリアルブート|0|
|シングルチップ|1|

VCL: 4.7uF

### RX220:   
|端子|LFQFP 64|
|---|---|
|MD|MD(3)|
|B/UB|PC7(27)|
|RXD|P30/RXD1(14)|
|TXD|P26/TXD1(16)|

|モード|B/UB|MD|
|---|:---:|:---:|
|シリアルブート|0|0|
|User Boot|1|0|
|シングルチップ|-|1|

---
### RX231:   
|端子|LFQFP 64|LFQFP 100|
|---|---|---|
|MD|MD(3)|MD(7)|
|UB|PC7(27)|PC7(45)|
|RXD|P30/RXD1(14)|P30/RXD1(20)|
|TXD|P26/TXD1(16)|P25/TXD1(23)|

|モード|UB|MD|
|---|:---:|:---:|
|シリアルブート|0|0|
|USB ブート|1|0|
|シングルチップ|-|1|

VCL: 4.7uF   

---
### RX621/RX62N:   
|端子|RX62x (144)|
|---|---|
|MD0|MD0(16)|
|MD1|MD1(15)|
|EMLE|EMLE(10)|
|RXD|P30/RXD1(29)|
|TXD|P26/TXD1(31)|
   
|モード|MD0|MD1|
|---|:---:|:---:|
|シリアルブート|1|0|
|USB ブート|0|1|
|シングルチップ|1|1|

---
### RX631/RX63N:
|端子|LQFP 48|LQFP 64|TFLGA 64|LQFP 100|TFLGA 100|LQFP 144|TFLGA 145|LQFP 176|LFBGA 176|TFLGA 177|
|---|---|---|---|---|---|---|---|---|---|---|
|UB|PC7(21)|PC7(27)|PA6(D5)|PC7(45)|PC7(H7)|PC7(60)|PC7(N9)|PC7(76)|PC7(N10)|PC7(N10)|
|MD|MD/FINED(2)|MD/FINED(3)|MD/FINED(C2)|MD/FINED(7)|MD/FINED(D3)|MD/FINED(16)|MD/FINED(G3)|MD/FINED(18)|MD/FINED(G3)|MD/FINED(G3)|
|EMLE|ー|EMLE(1)|EMLE(C3)|EMLE(2)|EMLE(B1)|EMLE(10)|EMLE(E4)|EMLE(10)|EMLE(E2)|EMLE(E2)|
|RXD|P30/RXD1(10)|P30/RXD1(14)|P30/RXD1(E3)|P30/RXD1(20)|P30/RXD1(G3)|P30/RXD1(29)|P30/RXD1(J4)|PF2/RXD1(31)|PF2/RXD1(K3)|PF2/RXD1(K3)|
|TXD|P26/TXD1(12)|P26/TXD1(16)|P26/TXD1(G2)|P26/TXD1(22)|P26/RXD1(H1)|P26/RXD1(31)|P26/RXD1(K2)|PF0/RXD1(35)|PF0/RXD1(L3)|PF0/RXD1(L3)|

|モード|UB|MD|
|---|:---:|:---:|
|シリアルブート|0|0|
|USB ブート|1|0|
|シングルチップ|-|1|

---
### RX63T/RX24T/RX26T/RX66T/RX72T:
|端子|RX63T (64)|RX24T (100)|RX26T (100)|RX66T (100)|RX72T (144)|
|---|---|---|---|---|---|
|VCL|0.1uF|4.7uF|0.47uF|0.47uF|0.47uF|0.47uF|
|UB|P00(2)|ー|ー|UB/P00(4)|UB/P00(9)|
|MD|MD(5)|MD(6)|MD/FINED(6)|MD/FINED(6)|MD/FINED(11)|
|EMLE|EMLE(1)|ー|EMLE(2)|EMLE(2)|EMLE(7)|
|RXD|PD5/RXD1(14)|PD5/RXD1(20)|PD5/RXD1(20)|PD5/RXD1(20)|PD5/RXD1(25)|
|TXD|PD3/TXD1(16)|PD3/TXD1(22)|PD3/TXD1(22)|PD3/TXD1(22)|PD3/TXD1(27)|

|モード|UB|MD|
|---|:---:|:---:|
|シリアルブート|0|0|
|USB ブート|1|0|
|シングルチップ|-|1|

---
### RX64M/RX71M/RX651/RX65N/RX66N:
|端子|RX64M (176)|RX71M (176)|RX651/RX65N (176)|
|---|---|---|---|
|UB|PC7/UB(76)|PC7/UB(76)|PC7/UB(76)|
|MD|MD/FINED(18)|MD/FINED(18)|MD/FINED(18)|
|EMLE|EMLE(10)|EMLE(10)|EMLE(10)|
|RXD|PF2/RXD1(31)|PF2/RXD1(31)|PF2/RXD1(31)|
|TXD|PF0/TXD1(35)|PF0/TXD1(35)|PF0/TXD1(35)|

|モード|UB|MD|
|---|:---:|:---:|
|シリアルブート|0|0|
|USB ブート|1|0|
|シングルチップ|-|1|

---
### RX660/RX671:
|端子|RX660 (144)|RX671 (144)|
|---|---|---|
|UB|PC7/UB(60)|PC7/UB(60)|
|MD|MD/PN6(16)|MD(16)|
|RXD|P30/RXD1(29)|P30/RXD1(29)|
|TXD|P26/TXD1(31)|P26/TXD1(31)|

RX660:
|モード|UB|MD|
|---|:---:|:---:|
|シリアルブート|0|0|
|ユーザーブート|1|0|
|シングルチップ|-|1|

RX660: USB インターフェースが無い為、USB ブート不可

RX671:
|モード|UB|MD|
|---|:---:|:---:|
|シリアルブート|0|0|
|USB ブート|1|0|
|シングルチップ|-|1|

---

- MD0、MD1、UB、MD、EMLE、B/UB 端子は、抵抗（4.7K 程度）でプルアップ、又はプルダウン。（直接 Vss や Vcc に接続しない事）
- XTAL、EXTAL に適切なクリスタルを接続。
- VCL に規定のコンデンサを接続。
- VSS、VCC、AVSS、AVCC 等電源を全て接続、バイパスコンデンサを入れる。
- VREFL, VREFH などのアナログ電圧リファレンスの適切な処理。
- USB_VSS、USB_VCC などの USB 電源を適切に接続する。
   
※詳しくは、各デバイスのハードウェアーマニュアル「概要、ピン配置図」、「フラッシュメモル、ブートモード」を参照して下さい。   
※ルネサス製リファレンスボードの回路図などが公開されていますので参考にして下さい。   
   
---
## 操作方法
![R5F564ML](../docs/USB_Serial.jpg)
### rx_prog の起動確認
 - rx_prog を実行して、動作する事を確認（help がリストされる）
```
% rx_prog
Renesas RX Series Programmer Version 1.65
Copyright (C) 2016, 2023 Hiramatsu Kunihito (hira@rvf-rc45.net)
usage:
rx_prog [options] [mot file] ...

Options :
    -P PORT,   --port=PORT     Specify serial port
    -s SPEED,  --speed=SPEED   Specify serial speed
    -d DEVICE, --device=DEVICE Specify device name
    -e, --erase                Perform a device erase to a minimum
    -v, --verify               Perform data verify
    -w, --write                Perform data write
    --progress                 display Progress output
    --erase-page-wait=WAIT     Delay per read page  (2000) [uS]
    --write-page-wait=WAIT     Delay per write page (5000) [uS]
    --device-list              Display device list
    --verbose                  Verbose output
    -h, --help                 Display this
```

### -P PORT (--port=PORT)

- 通信ポートを指定する場合
- rx_prog.conf ファイルでも指定可能
- rx_prog.conf では、異なった環境で共有出来るようにする為、Windows、OS-X、Linux で異なるポートを指定可能

conf ファイルで指定する場合：
```
#port = /dev/ttyS10
#port = COM12
```

環境毎の異なった設定：
```
port_win   = COM7
port_osx   = /dev/tty.usbserial-DA00X2QP
port_linux = /dev/ttyUSB0
```

### -s SPEED (--speed=SPEED)

- シリアル通信の最大速度を指定
- RX デバイスにより、最大速度が制限される場合がある
- 環境によって、設定可能な最大速度が異なる
- rx_prog.conf ファイルでも指定可能
- rx_prog.conf では、異なった環境で共有出来るようにする為、Windows、OS-X、Linux で異なるポートを指定可能

設定可能な通信速度：
- 19200
- 38400
- 57600
- 115200
- 230400 (RX220, RX621, RX62N では設定しても、115200 に制限される)

### -d DEVICE (--device==DEVICE)

- RX マイコン名の設定（RX24T, RX621, RX62N, RX631, RX63N, RX63T, RX64M, RX71M, RX651, RX65N, RX66T, RX72T, RX220）
- RX621, RX62N, RX220 RX631, RX63N, RX63T では、conf ファイル中で、分周器定数を指定する必要がある

RX621 の場合（divide_sys, divide_ext）:
```
R5F56217 {
	group = "RX621"
	clock = 1200
	divide_sys = 8
	divide_ext = 4
	rom = 384K
	ram = 64K
	data = 32K
	comment = "; RX621 Flash:384K DataFlash:32K RAM:64K"
	rom-area  = FFFA0000,FFFFFFFF
	data-area = 00100000,00107FFF
	ram-area  = 00000000,0000FFFF
}
```

clock:   
- 接続クリスタルの値、12MHz の場合 1200 とする。

divide_sys:
- 命令クロックに相当する倍率

divide_ext:
- 周辺機器に相当するクロックの倍率

---

### --progress

- プログレス表示（キャラクターによる進捗状況表示）を行う

```
 % rx_prog -d RX71M --progress --write --verify test_sample.mot
Erase:  ################################################# 100 %
Write:  ################################################# 100 %
Verify: ################################################# 100 %
```

### --erase-page-wait

- イレース・ページ発行後の遅延時間（マイクロ秒）
- CP2102N など、FTDI より高速な USB シリアル変換器を利用する場合に必要。
- イレースページなどのコマンド発効後、次にコマンドを発行する遅延を儲ける必要がある。
- 標準では、２ミリ秒（２０００マイクロ秒）が設定

### --write-page-wait

- ライト・ページ発行語の遅延時間（マイクロ秒）
- CP2102N など、FTDI より高速な USB シリアル変換器を利用する場合に必要。
- ライトページなどのコマンド発効後、次にコマンドを発行する遅延を儲ける必要がある。
- 標準では、５ミリ秒（５０００マイクロ秒）が設定

### --erase コマンドの有無

- RX62x, RX63T などでは、ID 検査が行われない場合、内部フラッシュは、自動的に消去される為、「--erase」を必要としません。
- 現在のバージョンでは、ID 検査、ID 設定コマンドを実装していません。

### --verify コマンドの有無

- RX63T では、verify を書き込み後、自動で行うので、--verify コマンドを必要としません。

---

### rx_prog.conf 設定

- 各デバイスの設定、ポート、ボーレートの設定などを記述します。
- 各プラットホームで設定を共有出来るように、シリアルデバイスのポートパスを個別に指定できます。
- 自分の環境に合わせてポート名、ボーレートなど設定しておきます。
- RX220, RX62x では、高ボーレートの場合に誤差が大きくなる為、115200 に制限されます。
   
rx_prog.conf 設定例：
```
# 標準のシリアルポート、プラットホーム依存ポート名
# port_win, port_osx, port_linux は、プラットホーム別に認識し、port より優先されます。
#port = /dev/ttyS10
#port = COM12
port_win   = COM3
port_osx   = /dev/tty.usbserial-DA00X2QP
port_linux = /dev/ttyUSB0

# 標準のシリアル・スピード、プラットホーム依存スピード
# speed_win, speed_osx, speed_linux は、プラットホーム別に認識し、speed より優先されます。
# ※設定できる最大速度は、プラットホームにより異なります。
#speed = 230400
speed_win = 230400
speed_osx = 230400
speed_linux = 230400

# erase-page command wait [uS]
erase_page_wait = 2000
# write-page command wait [uS]
write_page_wait = 5000
```
rx_prog.conf は、以下の順番にスキャンされ、ロードされます。   
- カレント・ディレクトリ
- コマンド・ディレクトリ（通常、/usr/local/bin）
- シリアルスピードは、19200, 38400, 57600, 115200, 230400 の中から選択します。
- RX621/RX62N では、高いボーレートで誤差が大きく、シリアル速度を内部で 115200 に制限しています。
- RX621/RX62N, RX631/RX63N, RX63T などのデバイスでは、接続時、外部接続クリスタル周波数、倍率設定が必要です。
- RX63T では、高いボーレートで誤差が大きく、シリアル速度を内部で 115200 に制限しています。
- 以下のように、設定ファイルで行います。
- group 名が同一の設定が複数ある場合、最初に見つけたグループ内設定が有効になります。

```
R5F56217 {
	group = "RX621"
	clock = 1200
	divide_sys = 8
	divide_ext = 4

...

}
```

---

### 対応デバイス・リスト表示

```
 % rx_prog --device-list
R5F52206 (RX220): Program-Flash:  256K, RAM:   16K, Data-Flash:  8K
R5F52315 (RX231): Program-Flash:  128K, RAM:   64K, Data-Flash:  8K
R5F52316 (RX231): Program-Flash:  256K, RAM:   32K, Data-Flash:  8K
R5F52317 (RX231): Program-Flash:  384K, RAM:   64K, Data-Flash:  8K
R5F52318 (RX231): Program-Flash:  512K, RAM:   64K, Data-Flash:  8K
R5F56217 (RX621): Program-Flash:  384K, RAM:   64K, Data-Flash: 32K
R5F56218 (RX621): Program-Flash:  512K, RAM:   96K, Data-Flash: 32K
R5F562N7 (RX62N): Program-Flash:  384K, RAM:   64K, Data-Flash: 32K
R5F562N8 (RX62N): Program-Flash:  512K, RAM:   96K, Data-Flash: 32K
R5F5631F (RX631): Program-Flash: 2048K, RAM:  256K, Data-Flash: 32K
R5F563NE (RX63N): Program-Flash: 2048K, RAM:  128K, Data-Flash: 32K
R5F564MF (RX64M): Program-Flash: 2048K, RAM:  512K, Data-Flash: 64K
R5F571MF (RX71M): Program-Flash: 2048K, RAM:  512K, Data-Flash: 64K
R5F564MG (RX64M): Program-Flash: 2560K, RAM:  512K, Data-Flash: 64K
R5F571MG (RX71M): Program-Flash: 2560K, RAM:  512K, Data-Flash: 64K
R5F564MJ (RX64M): Program-Flash: 3072K, RAM:  512K, Data-Flash: 64K
R5F571MJ (RX71M): Program-Flash: 3072K, RAM:  512K, Data-Flash: 64K
R5F564ML (RX64M): Program-Flash: 4096K, RAM:  512K, Data-Flash: 64K
R5F571ML (RX71M): Program-Flash: 4096K, RAM:  512K, Data-Flash: 64K
R5F5651E (RX651): Program-Flash: 2048K, RAM:  640K, Data-Flash: 32K
R5F565NE (RX65N): Program-Flash: 2048K, RAM:  640K, Data-Flash: 32K
R5F5671C (RX671): Program-Flash: 1536K, RAM:  384K, Data-Flash:  8K
R5F5671E (RX671): Program-Flash: 2048K, RAM:  384K, Data-Flash:  8K
R5F572ND (RX72N): Program-Flash: 2048K, RAM: 1024K, Data-Flash: 32K
R5F572NN (RX72N): Program-Flash: 4096K, RAM: 1024K, Data-Flash: 32K
R5F572MD (RX72M): Program-Flash: 2048K, RAM: 1024K, Data-Flash: 32K
R5F572MN (RX72M): Program-Flash: 4096K, RAM: 1024K, Data-Flash: 32K
R5F563T6 (RX63T): Program-Flash:   64K, RAM:    8K, Data-Flash:  8K
R5F524T8 (RX24T): Program-Flash:  128K, RAM:   16K, Data-Flash:  8K
R5F524TA (RX24T): Program-Flash:  256K, RAM:   16K, Data-Flash:  8K
R5F526TF (RX26T): Program-Flash:  512K, RAM:   64K, Data-Flash: 16K
R5F566TA (RX66T): Program-Flash:  256K, RAM:   64K, Data-Flash: 32K
R5F566TE (RX66T): Program-Flash:  512K, RAM:   64K, Data-Flash: 32K
R5F566TF (RX66T): Program-Flash:  512K, RAM:  128K, Data-Flash: 32K
R5F566TK (RX66T): Program-Flash: 1024K, RAM:  128K, Data-Flash: 32K
R5F572TF (RX72T): Program-Flash:  512K, RAM:  128K, Data-Flash: 32K
R5F572TK (RX72T): Program-Flash: 1024K, RAM:  128K, Data-Flash: 32K
```

---

### 現在の実装依存

- 現在の実装では、rx_prog.conf に定義された、デバイス情報プロファイルは、フラッシュプログラム時に参照されたり、評価される仕組みを実装していません。
- 将来の拡張用です。
- 「clock、divide_sys、divide_ext」など、接続に必要な情報は、最初にマッチしたグループデバイスのプロファイルが利用されます。
- 本来、接続時に取得した、デバイス TYP に沿ったデバイスプロファイルを利用すべきですが、その実装がされていません。
- これは、TYP と、デバイスプロファイルの資料が公開されていない為です。
- 同じグループで、ハードウェアー仕様が異なるデバイスがあり、rx_prog.conf に異なる定義を行っても、反映されませんので注意が必要です。
- OFS オプション設定メモリの書き換えに対応していません。

---

### コネクション検査
![R5F564ML](../docs/RX_boards.jpg)
```
 % rx_prog -d RX71M --verbose
# Platform: 'Cygwin'
# Configuration file path: '/usr/local/bin/rx_prog.conf'
# Device: 'RX71M'
# Serial port path: 'COM3'
# Serial port speed: 230400
# Serial port alias: COM3 ---> /dev/ttyS2
# Serial port path: '/dev/ttyS2'
# Connection OK.
#01/01: Device Type TYP: 20 02 FD 09 01 48 40 00
#01/01: Device Type OSA: 16000000
#01/01: Device Type OSI: 16000000
#01/01: Device Type CPA: 120000000
#01/01: Device Type CPI: 120000000
#01/01: Endian is little.
#01/01: System clock: 120000000
#01/01: Device clock: 60000000
#01/01: Change baud rate: 230400
#01/01: ID: Disable
```
   
---

### 消去、書き込み、比較（プログレスバー付、「test_sample.mot」ファイルの場合）
```
 % rx_prog -d RX71M --progress --write --verify test_sample.mot
Erase:  ################################################# 100 %
Write:  ################################################# 100 %
Verify: ################################################# 100 %
```

---

### 不必要なシリアルポートの削除（Windows）
```
set devmgr_show_nonpresent_devices=1
start devmgmt.msc
```
   
- 全ての USB シリアルデバイスをコンピューターから取り外す。
- 上記で BAT ファイルを作成して、右クリックにて、「管理者権限」で実行する。
- 「表示」-「非表示のデバイスの表示」にチェックを入れる。
- 使っていない COM ポートを削除する。
- 改めて、USB シリアルデバイスを順番にコンピューターに接続していく。
   
※同メーカーデバイスの場合、二個目以降、COM ポート番号の移り変わりなどが発生するので状況に応じてメーカー専用ツールなどで内部シリアル ID 番号を変更するなどの対処を行う必要がある。
※専用ツールの利用に関して、デバイスメーカーのＨＰで確認下さい。
   
---

### FT232RL, FT231XS と CP2102 の違い
FT231XS, FT232RL:
```
Neptune./d/Git/RX/RAYTRACER_sample/RX66T % time rx_prog -d RX66T --progress --erase --write --verify raytracer_sample.mot
Erase:  ################################################# 100 %
Write:  ################################################# 100 %
Verify: ################################################# 100 %

real    0m16.617s
user    0m0.202s
sys     0m0.421s
```
   
CP2102:
```
Neptune./d/Git/RX/RAYTRACER_sample/RX66T % time rx_prog -P COM12 -d RX66T --progress --erase --write --verify raytracer_sample.mot
Erase:  ################################################# 100 %
Write:  ################################################# 100 %
Verify: ################################################# 100 %

real    0m6.616s
user    0m0.078s
sys     0m0.187s
```
   
※FTDI のデバイスはシリコンラボ製デバイスに比べて低速なようです。
   
---

## RX62N の刻印と容量

- FRK-RX62N 搭載の「R5F562N7」は、カタログ上は、FlashROM:384K、RAM:64K 品となっています。
- しかし、接続テストを行うと、下記のように、通常存在しない FlashROM エリアを報告します。

```
 % rx_prog -d RX62N --verbose
# Platform: 'Cygwin'
# Configuration file path: 'rx_prog.conf'
# Device: 'RX62N'
# Serial port path: 'COM7'
# Serial port speed: 230400
# Erase Page Wait: 2000 [uS]
# Write Page Wait: 5000 [uS]
# Serial port alias: COM7 ---> /dev/ttyS6
# Serial port path: '/dev/ttyS6'
Connection OK. (RX62x)
#01/01: Device: RX600 Series
#01/01: Device ID: 0x35307936
#01/01: Clock Mode: 0x00
#01/02: Multiplier: 1, 2, 4, 8
#02/02: Multiplier: 1, 2, 4, 8
#01/02: Frequency Min: 8 MHz, Max: 100 MHz
#02/02: Frequency Min: 8 MHz, Max: 50 MHz
#01/01: Change baud rate: 115200
#01/01: Boot Area: FF7FC000, FF7FFFFF
#01/01: Area: FFF80000, FFFFFFFF
#01/54: Area: FFFFF000, FFFFFFFF
#02/54: Area: FFFFE000, FFFFEFFF
#03/54: Area: FFFFD000, FFFFDFFF
#04/54: Area: FFFFC000, FFFFCFFF
#05/54: Area: FFFFB000, FFFFBFFF
#06/54: Area: FFFFA000, FFFFAFFF
#07/54: Area: FFFF9000, FFFF9FFF
#08/54: Area: FFFF8000, FFFF8FFF

...

#50/54: Area: 00102000, 001027FF
#51/54: Area: 00101800, 00101FFF
#52/54: Area: 00101000, 001017FF
#53/54: Area: 00100800, 00100FFF
#54/54: Area: 00100000, 001007FF
#01/01: Program size: 256 Bytes
#01/01: ID Protect: false
```

- R5F562N8 と同じく、FlashROM は、FFF80000 から 512K バイト、RAM は、96K バイト利用可能なようです。
- 実際にプログラムが出来、動作も確認しました。

---
   
License
----

MIT
