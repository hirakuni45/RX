Renesas RX マイコン・フラッシュ・プログラミング・ツール (rx_prog)
=========
![R5F564ML](../RXchipS.jpg)

## 概要
シリアルインターフェースを使って、RX マイコンのフラッシュメモリーにプログラムを書き込む為のツール
   
## プロジェクト・リスト
 - main.cpp
 - area.hpp
 - conf_in.hpp
 - file_io.cpp
 - file_io.hpp
 - motsx_io.hpp
 - rs232c_io.hpp
 - rx_prog.hpp
 - rx_protocol.hpp
 - rx24t_protocol.hpp
 - rx63t_protocol.hpp
 - rx64m_protocol.hpp
 - rx65x_protocol.hpp
 - sjis_utf16.cpp
 - sjis_utf16.hpp
 - string_utils.cpp
 - string_utils.hpp
 - Makefile
 - rx_prog.conf
   
## ビルド（コンパイル）環境の準備（Windows）
 - MSYS2 のセットアップ
 - gcc 関係のインストール
 - boost のインストール（pacman を使って、mingw64 環境用をインストールする）
   
## ビルド方法、環境設定
 - make する
 - make install により、設定ファイルと実行ファイルをコピー
 - /usr/local/bin にパスを通す
   
## 接続準備（シリアル接続）
 - マイコン側の RXD1 端子と、USB シリアルの TXD を接続。
 - マイコン側の TXD1 端子と、USB シリアルの RXD を接続。
※ブート時のＳＣＩポート（通常 SCI1 です、要確認ハードウェアーマニュアル）   
 - CPU の MD 端子を「Ｌレベル」にして「リセット」信号を入れる。
   
## 操作方法
### rx_prog の起動確認
 - rx_prog を実行して、動作する事を確認（help がリストされる）
```
rx_prog
```
   
### rx_prog.conf 設定
 - 各デバイスの設定、ポート、ボーレートの設定などを記述する。
 - 各プラットホームで設定を共有出来るように、シリアルデバイスのポートパスを個別に指定できる。
 - 自分の環境に合わせてポート名、ボーレートなど設定しておく。
   
### コネクション検査
```
rx_prog -d RX71M --verbose
```
   
### 消去、書き込み、比較（プログレスバー付、「test_sample.mot」ファイルの場合）
```
rx_prog -d RX71M --progress --write --verify test_sample.mot
```
   
-----
   
License
----

MIT
