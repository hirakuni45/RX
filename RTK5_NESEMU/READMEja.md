Renesas Envision Kit RX65N NES Emulator
=========

[Japanese](READMEja.md)

## 概要

<img src="../docs/NES_001.jpg" width="50%"><img src="../docs/NES_002.jpg" width="50%">

Envision Kit RX65N で実現する NES(ファミコン) エミュレーター
   
## プロジェクト・リスト
 - main.cpp
 - nesemu.hpp
 - emu/* [NES Emulator ソースコード]
 - Makefile
   
## ハードウェアーの準備
 - SD カードインターフェースの準備

 <img src="../docs/SD_MOUNT.jpg" width="50%">
 
 - ファミコン（互換）パッドの接続

<img src="../docs/JoyPad.jpg" width="50%"><img src="../docs/JoyPadCon.jpg" width="50%">

 - オーディオの接続（DA0、DA1 から出力、GND レベルは、1.65V）

<img src="../docs/AudioLead.jpg" width="50%">

 - P03_JOY_RIGHT_IRQ11 (DA0) Left 出力
 - P05_IRQ13_SW (DA1) Right 出力
 ※ ファミコンの仕様でモノラル
 - Pmod (10) PB6_RXD9_PMOD_10 ---> RXD として使用
 - Pmod ( 9) PB7_TXD9_PMOD_9  ---> TXD として使用
 - RXD/TXD は 115200 Baud, 8-bits, 1-Stop, No-Parity 内部動作表示等
   
## リソースの準備
 - SD カードのルートに「kfont16.bin」ファイルを書き込む。（ファイラーでの漢字表示）
 RX/graphics/kfont16.bin   
 ※現在は、「kfont16.cpp」として、ソースコードに埋め込んでいる。
 - SD カードに、「xxx.nes」形式のファイルを書き込む。
   
## ビルド方法
 - make する。
 - nesemu.mot ファイルを書き込む。
   
## 操作方法
 - 「SELECT」、「START」ボタンを２秒程度同時押しする。
 - メニューが表示され、上下ボタンで選択し、Ａボタンで決定。
 - 「Select NES File」、ファイラーが開く。
 - 「Load State x」NES ステートをロード（左右ボタンでスロットを変更 0 ～ 9）
 - 「Save State x」NES ステートをセーブ（左右ボタンでスロットを変更 0 ～ 9）
 - 「Reset」NES をリセット
 - 「Close Menu」メニューを終了
   
### ファイラーの操作
 - 上下ボタンで、ファイル名フォーカスを移動。
 - 「xxx.nes」ファイルで、右方向ボタンを押して選択（ゲームが起動する）。   
 - ディレクトリーの場合は、そのディレクトリーへ移動する。
 - ディレクトリーを戻る場合は、左方向ボタンを押す。
 - Ａボタンを押すとファイル情報の表示。（もう一度押すと戻る）
 - Ｂボタンを押すとファイラーを閉じる。
   
## シリアルターミナル接続によるモニター機能
SCI9 に USB シリアルなどを接続して、ターミナルソフトにより、簡単な操作が出来る。
対応しているコマンドは以下

```
# help
    dir [xxx]       list current directory
    pwd             current directory path
    cd [xxx]        change current directory
    nes filename    Emulations for NES
    pause           Pause Emulation (toggle)
    reset           Reset NES Machine
    save [slot-no]  Save NES State (slot-no:0 to 9)
    load [slot-no]  Load NES State (slot-no:0 to 9)
    info            Cartrige Infomations
    call-151        Goto Monitor
```
   
call-151 でモニター機能に移り、ファミコン内部のメモリダンプなど行える。

```
#call-151
$fff8.ffff
FFF8- FF FF 0C E2 20 E0 20 E0
$e020l
E020- 78       SEI
E021- D8       CLD
E022- A2 4D    LDX  #$4D
E024- 9A       TXS
E025- A9 10    LDA  #$10
E027- 8D 00 20 STA  $2000
E02A- AD 02 20 LDA  $2002
E02D- 10 FB    BPL  $E02A
E02F- A2 00    LDX  #$00
E031- 8A       TXA
E032- 95 00    STA  $00,X
E034- 9D 00 02 STA  $0200,X
E037- 9D 00 06 STA  $0600,X
E03A- 9D 00 07 STA  $0700,X
E03D- E8       INX
E03E- D0 F2    BNE  $E032
E040- A2 00    LDX  #$00
E042- BD 05 01 LDA  $0105,X
E045- DD 10 E0 CMP  $E010,X
E048- D0 0B    BNE  $E055
$0.
0000- 00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
$0:1 2 3 4
$0.
0000- 01 02 03 04 00 00 00 00  00 00 00 00 00 00 00 00
$exit
#
```

## 制限
 - エミュレーションは、プログラム、ビットマップの合計が、2MBits(256Kバイト)の場合まで可能。
 - 同じような構成でも、マッパー（バンク切り替えデバイス）など、起動出来ない場合があります。
 - NES ステートによる機能は、マッパーによっては（マッパーの状態がセーブ出来ない）正しく機能しないようです。
   
## 参考動画
<https://www.youtube.com/watch?v=frRI-cbzGus>
   
-----
   
License
----

MIT

and

NES Emulator for G.P.L.
