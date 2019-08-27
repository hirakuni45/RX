Renesas Envision Kit RX65N ガジェット
=========
![R5F564ML](../RTK5RX65N.jpg)

## 概要
Envision Kit RX65N で実現する NES(ファミコン) エミュレーター
   
## プロジェクト・リスト
 - main.cpp
 - nesemu.hpp
 - emu/* [NES Emulator ソースコード]
 - Makefile
   
## ハードウェアーの準備
 - SD カードインターフェースの準備
 - ファミコン（互換）パッドの接続（main.cpp を参照）
 - オーディオの接続（DA0、DA1 から出力、GND レベルは、1.65V）
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
 - ファイラーが開くので、上下ボタンで、ファイル名にフォーカスを移動。
 -「xxx.nes」ファイルで、右方向ボタンを押す。
 - ディレクトリーの場合は、そのディレクトリーへ移動する。
 - ディレクトリーを戻る場合は、左方向ボタンを押す。
 - 上記で選択したゲームが起動する。
   
## 制限
 - エミュレーションは、おおよそ、2MBits(256Kバイト)の場合まで可能。
 - メモリーの余裕が殆どありませんから、同じような構成でも起動出来ない場合があります。
   
## 参考動画
<https://www.youtube.com/watch?v=frRI-cbzGus>
   
-----
   
License
----

MIT

and

NES Emulator for G.P.L.
