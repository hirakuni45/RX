Renesas Envision Kit RX65N/RX72N ガジェット
=========
![R5F564ML](../docs/RTK5_side.jpg)

## 概要
Envision Kit RX65N/RX72N で実現する Space Invaders エミュレーター
   
## プロジェクト・リスト
 - main.cpp
 - spinv.hpp
 - Makefile
 - wavs/ 効果音ファイル
   
## ハードウェアーの準備 RX65N
 - SD カードインターフェースの準備
 - ファミコン（互換）パッドの接続（main.cpp を参照）
 - オーディオの接続（DA0、DA1 から出力、GND レベルは、1.65V）
 - P03_JOY_RIGHT_IRQ11 (DA0) Left 出力
 - P05_IRQ13_SW (DA1) Right 出力
 ※ SE はモノラル
 - Pmod (10) PB6_RXD9_PMOD_10 ---> RXD として使用
 - Pmod ( 9) PB7_TXD9_PMOD_9  ---> TXD として使用
 - RXD/TXD は 115200 Baud, 8-bits, 1-Stop, No-Parity 内部動作表示等

## ハードウェアーの準備 RX72N
 - ファミコン（互換）パッドの接続（main.cpp を参照）Pmod1 に接続する
 - 効果音は D2 オーディオジャックから出力
   
## リソースの準備
 - ROM の準備（invaders.h、invaders.g、invaders.f、invaders.e）invaders.zip
 - サウンドデータの準備（BaseHit.wav, InvHit.Wav, Shot.wav, Ufo.wav, UfoHit.wav, Walk1.wav, Walk2.wav, Walk3.wav, Walk4.wav）
 - SD カードに上記ファイルを、それぞれディレクトリを作成して配置しておく（/inv_roms, /inv_wavs）

## ビルド方法
 - make する。
 - side.mot ファイルを書き込む。
   
## 参考動画
<https://www.youtube.com/watch?v=AkgoFYMugng>
   
-----
   
License
----

MIT
SIDE for GPLv2
