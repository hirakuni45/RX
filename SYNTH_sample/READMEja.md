Renesas RX65N/RX72N SYNTH (Yamaha DX7 エミュレータ) サンプル
=========

<img src="../docs/SYNTH_sample.jpg" width="50%">

[English](README.md)

## 概要

RX マイコンを使った Yamaha DX7 FM シンセサイザの発音サンプルプログラム
   
## プロジェクト・リスト
 - main.cpp
 - synth_gui.hpp
 - keyboard.hpp
 - RX65N/Makefile
 - RX72N/Makefile
 - DX7_0628.SYX

## FM シンセサイザ、DX7 エミュレータ（ソース）

 - RX/sound/synth/

## スタンダード MIDI ファイルプレイヤー（ソース）

- RX/sound/smf

※元のソースコードは「Arduino」環境用の物なので、このフレームワーク用に修正を加えている。

## ハードウェアーの準備（全般）

- RX72N Envision Kit では、オーディオジャックにアンプを接続する。
- RX65N Envision Kit では、DA0,DA1 からアナログ出力するので、適切なアンプを接続する。
- RX65N Envision Kit の改造方法は、AUDIO_sample などを参考にする。
      
## ビルド方法

 - 各プラットホームディレクトリーに移動、make する。
 - SYNTH_sample.mot ファイルを書き込む。
   
## 動作

 - DX7_0628.SYX を SD カードのルートに置いておく。
 - 音色の読み込みは、遅延がある（約３秒）
 - 起動して、鍵盤を押せば、音色の音が鳴る。（全部で３２音色）
 - 「<」、「>」音色変更ボタンで、音色を変更出来る。
 - 音色変更ボタンがある中央には、音色名が表示されている。
 - 「<<」、「>>」ボタンで、オクターブ域を変更出来る。（５オクターブ）
 - 鍵盤は、同時に４つまで認識し、音が鳴る。（FM シンセサイザーの能力的には同時８音）
 - 「@」ボタンを押すと「ファイラー」が開くので、MID ファイルを選択すると、演奏を行う。
    
## 備考

RX65N の場合、処理能力に制限があり、同時発音数は４つに設定されている。
   
MID ファイルは、スタンダード MIDI 形式、現在導入しているパーサーの制限、シンセサイザーの制限などで、演奏可能ファイルとそうでないファイルがある。
MID ファイルはネットを探すと色々あるので、探して、自動演奏を楽しんでもらいたい。

-----
   
License
----

MIT

FM Synthsizer License:

  http://www.apache.org/licenses/LICENSE-2.0

smf:

```
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
```
