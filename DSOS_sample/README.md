Renesas RX65N/RX72N Envision Kit ガジェット
=========
![R5F564ML](../RTK5RX65N.jpg)

## 概要
 - RX65N/RX72N Envision Kit で実現するデジタルストレージオシロスコープ
 - 最大サンプリング速度 500 [ns] (2MHz)
 - 最大２チャネル同時
 - 内蔵１２ビット A/D コンバータ利用（４０９６段階）
 - タッチパネルを使った操作
   
## プロジェクト・リスト
 - main.cpp
 - capture.hpp
 - render_wave.hpp
 - dso_gui.hpp
 - Makefile
   
## ハードウェアーの準備
 - SD カードインターフェースの準備（キャプチャー波形を書き込む場合）
 - アナログ入力の接続
 - CH0: CN10 (1) P40_AN000_ARD_A0
 - CH1: CN10 (5) P90_AN114_SDA7_ARD_A4
 - GND: CN8  (4), (5)
 - 3.3V: CN8 (2)（A/D 変換基準電圧）
 - 5V: CN8 (3)（フロントエンド、プリアンプ電源用）
   
## リソースの準備
 - SD カード、ルートに「kfont.bin」ファイルを書き込む。（ファイラーでの漢字表示）   
 ※現在は、「kfont16.cpp」として、ソースコードに埋め込んでいる。   
   
## ビルド方法
 - make する。
 - dsos_sample.mot ファイルをターゲットに書き込む。

## 操作方法
    
-----
   
License
----

MIT
