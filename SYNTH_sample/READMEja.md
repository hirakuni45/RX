Renesas RX65N/RX72N SYNTH (Yamaha DX7 エミュレータ) サンプル
=========

<img src="../docs/SYNTH_sample.jpg" width="50%">

## 概要
RX マイコンを使った Yamaha DX7 のサンプルプログラム
   
## プロジェクト・リスト
 - main.cpp
 - synth_gui.hpp
 - keyboard.hpp
 - RX65N/Makefile
 - RX72N/Makefile
 - DX7_0628.SYX

## DX7 エミュレータ（ソース）

 - RX/sound/synth/

## ハードウェアーの準備（全般）
      
## ビルド方法
 - 各プラットホームディレクトリーに移動、make する。
 - SYNTH_sample.mot ファイルを書き込む。
   
## 動作

 - DX7_0628.SYX を SD カードのルートに置いておく。
 - 起動して、鍵盤を押せば、音色の音が鳴る。
 - 「<」、「>」音色変更ボタンで、音色を変更出来る。
    
## 備考


-----
   
License
----

MIT
