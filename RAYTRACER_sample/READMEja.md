Renesas RX24T, RX64M, RX71M, RX65N, RX66T, RX72N レイトレーサーサンプル
=========
   
[Japanese](READMEja.md)
   
<img src="../docs/RX65N_raytrace1.jpg" width="40%"> <img src="../docs/RX65N_raytrace2.jpg" width="40%">   
Raytracer 320x240/480x272, for RX65N Envision kit   
※少し前のバージョンによるレンダリング（最新のコードでは最適化により若干高速）
   
---
   
## 概要
RX マイコンを使ったレイトレーシングのレンダリングプログラム
   
## プロジェクト・リスト
- main.cpp
- raytracer.hpp
- RX24T/Makefile
- RX64M/Makefile
- RX71M/Makefile
- RX65N/Makefile
- RX66T/Makefile
- RX72N/Makefile
   
## ハードウェアーの準備（全般）
- ベースクリスタルが異なる場合は、typedef のパラメーターを変更する。
- Makefile で、各モジュール別の設定周波数を宣言している。
- RX24T:  80MHz (10MHz)
- RX64M: 120MHz (12MHz)
- RX71M: 240MHz (12MHz)
- RX65N: 120MHz (12MHz)
- RX66T: 160MHz (10MHz)
- RX72N: 240MHz (16MHz)
- インジケーター LED を指定のポートに接続する。
- USB シリアルの信号と設定の SCI1(RX24T, RX66T, RX64M, RX71M) ポートを接続する。
- RX65N Envision kit は付属の LCD (480x272) を使う。
- RX24T, RX66T は８ビット接続 (R61505W LCD Controller)
- RX64M, RX71M は１６ビット接続 (R61505W LCD Controller)
- R61505W LCD との接続ポートは、「main.cpp」を参照
- RX72N Envision kit は付属の LCD (480x272) を使う。
   
## ハードウェアーリソースの準備
- SCI に指定されたポートに USB シリアルなどの変換器を接続する。
- マイコン側の RXD 端子と、USB シリアルの TXD を接続。
- マイコン側の TXD 端子と、USB シリアルの RXD を接続。
- RX72N Envision Kit では、CN8 コネクタが USB シリアル接続となっている。
   
## ビルド方法
- 各プラットホームディレクトリーに移動、make する。
- raytracer_sample.mot ファイルを書き込む。
   
## 動作
- 320x240 の解像度でレイトレーシングを行い描画する（描画ハードウェアーがあれば）。
- レンダリング時間を、液晶とコンソールに表示（ミリ秒）
- LED が 0.25 秒間隔で点滅する。
- SCI に指定されたポートで、TX（送信）、RX（受信）を行う。
- TeraTerm などで確認。
- TeraTerm のシリアル設定：１１５２００ボー、８ビットデータ、１ストップ、パリティ無し。
- RX65N Envision kit では、裏側の SW2 を押す事で、サンプリング数、解像度を変えてレンダリング
- RX72N Envision kit では、裏側の SW2 を押す事で、サンプリング数、解像度を変えてレンダリング
   
## 備考
   
- ポートバスによる、フォントの描画を LCD に送る処理は、かなり大きい。
- オリジナルコードでは、ライン毎にレンダリング時間を LCD に表示しているが、コメントアウトしてある。
   
## レンダリング時間３２０ｘ２４０、サンプリング数：１
   
|マイコン  |core|周波数 [MHz]|描画方式         |時間 [ms]   |
|----------|----|------------|-----------------|------------|
|RX24T     |RXv2|80          |8 bits, port-bus |1224        |
|RX65N     |RXv2|120         |Frame Memory     |784         |
|RX64M     |RXv2|120         |16 bits, port-bus|751         |
|RX66T     |RXv3|160         |8 bits, port-bus |602         |
|RX71M     |RXv2|240         |16 bits, port-bus|439         |
|RX72N     |RXv3|240         |Frame Memory     |361         |
---
   
License
---

参照（レイトレーサー）： http://www.cs.cmu.edu/~ph/

他： MIT
