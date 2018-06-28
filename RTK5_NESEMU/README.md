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
   
## ビルド方法
 - make する。
 - nesemu.mot ファイルを書き込む。
   
## 操作方法
 - 「SELECT」、「START」ボタンを２秒程度同時押しする。
 - ファイラーが開くので、「xxx.nes」ファイルを選択（右方向ボタン）
 - 上記で選択したゲームが起動する。
   
## 制限
 - エミュレーションは、おおよそ、1MBitsROM １個の場合まで可能。
 - ファイラーは、31文字より大きいファイルを選択出来ない。
   
-----
   
License
----

MIT
