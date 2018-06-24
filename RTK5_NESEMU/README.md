Renesas Envision Kit RX65N ガジェット
=========
![R5F564ML](../RTK5RX65N.jpg)

## 概要
Envision Kit RX65N で実現する NES(ファミコン) エミュレーター
   
## プロジェクト・リスト
 - main.cpp
 - nesemu.hpp
 - emu/ NES Emulator ソースコード
 - Makefile
   
## ハードウェアーの準備
 - SD カードインターフェースの準備
 - ファミコン（互換）パッドの接続（main.cpp を参照）
 - オーディオの接続（DA0、DA1 から出力、GND レベルは、1.65V）
   
## リソースの準備
 - SD カードに、「xxx.nes」形式のファイルを書き込む。
 - nesemu.hpp の中で、*.nes ファイルを読み込む部分を修正。
   
## ビルド方法
 - make する。
 - nesemu.mot ファイルを書き込む。
   
-----
   
License
----

MIT
