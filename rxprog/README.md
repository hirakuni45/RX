Renesas RX マイコン・フラッシュ・プログラミング・ツール (rx_prog)
=========
![R5F564ML](RXchipS.jpg)

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
   
## 接続ハードウェアー（シリアル接続）
 - 所定のＳＣＩポート（通常 SCI1 です、要確認ハードウェアーマニュアル）と接続する。
 - CPU の MD 端子を「Ｌレベル」にして「リセット」信号を入れる。
   
## 操作方法
 - rx_prog を実行して、動作する事を確認（help がリストされる）
   
-----
   
License
----

MIT
