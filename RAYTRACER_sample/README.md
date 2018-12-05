Renesas RX24T, RX64M, RX71M, RX65N, RX66T レイトレーサーサンプル
=========

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
   
## ハードウェアーの準備（全般）
 - ベースクリスタルが異なる場合は、typedef のパラメーターを変更する。
 - Makefile で、各モジュール別の設定周波数を宣言している。
 - RX24T:  80MHz (10MHz)
 - RX64M: 120MHz (12MHz)
 - RX71M: 240MHz (12MHz)
 - RX65N: 120MHz (12MHz)
 - RX66T: 160MHz (10MHz)
 - インジケーター LED を指定のポートに接続する。
 - USB シリアルの信号と設定の SCI ポートを接続する。
 - RX64M, RX71M, SCI の標準ポートは、「RX600/port_map.hpp」参照。
 - RX24T, SCI の標準ポートは、「RX24T/port_map.hpp」参照。
 - RX66T SCI の標準ポートは、「RX66T/port_map.hpp」参照。
   
## ハードウェアーリソースの準備
 - SCI に指定されたポートに USB シリアルなどの変換器を接続する。
 - マイコン側の RXD 端子と、USB シリアルの TXD を接続。
 - マイコン側の TXD 端子と、USB シリアルの RXD を接続。
   
## ビルド方法
 - 各プラットホームディレクトリーに移動、make する。
 - raytracer_sample.mot ファイルを書き込む。
   
## 動作
 - 320x240 の解像度でレイトレーシングを行い描画する（描画ハードウェアーがあれば）。
 - LED が 0.25 秒間隔で点滅する。
 - SCI に指定されたポートで、TX（送信）、RX（受信）を行う。
 - TeraTerm などで確認。
 - TeraTerm のシリアル設定：１１５２００ボー、８ビットデータ、１ストップ、パリティ無し。
 - main.cpp の中、SCI の初期化でボーレートは自由に設定できる。
 - 設定出来ない「値」の場合、初期化が失敗する。（極端に遅い、早い）
    
## 備考
 - SCI_sample を参照の事。
   
-----
   
License
----

MIT
