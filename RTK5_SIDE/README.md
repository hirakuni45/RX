Renesas Envision Kit RX65N ガジェット
=========
![R5F564ML](../RTK5_side.jpg)

## 概要
Envision Kit RX65N で実現する Space Invaders エミュレーター
   
## プロジェクト・リスト
 - main.cpp
 - spinv.hpp
 - Makefile
 - wavs/ 効果音ファイル
   
## ハードウェアーの準備
 - SD カードインターフェースの準備
 - ファミコン（互換）パッドの接続（main.cpp を参照）
 - オーディオの接続（DA0、DA1 から出力、GND レベルは、1.65V）
   
## リソースの準備
 - ROM の準備（invaders.h、invaders.g、invaders.f、invaders.e）
 - サウンドデータの準備（BaseHit.wav, InvHit.Wav, Shot.wav, Ufo.wav, UfoHit.wav, Walk1.wav, Walk2.wav, Walk3.wav, Walk4.wav）
 - SD カードに上記ファイルを、それぞれディレクトリを作成して配置（/inv_roms, /inv_wavs）

## ビルド方法
 - make する。
 - side.mot ファイルを書き込む。
   
## 参考動画
<https://www.youtube.com/watch?v=AkgoFYMugng>
   
-----
   
License
----

MIT
