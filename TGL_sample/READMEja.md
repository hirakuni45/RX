Renesas RX72N Tiny GL サンプル
=========

<img src="../docs/TinyGLsample.jpg" width="50%">

[English](README.md)
   
---
   
## 概要
- RX72N Drw2d エンジンを使った、TinyGL(OpenGL の縮小版) のサンプル
- RX72N のセカンドメモリーが 512K バイトあるので、480x272 RGB565 でダブルバッファを利用
- ダブルバッファを活用したページフリッピングのサンプル
- TinyGL を使った、簡単な３Ｄグラフィックスの描画サンプル（API の仕様は OpenGL にある程度準拠）
- 内蔵メモリの関係で Z バッファは利用出来ない

## プロジェクト・リスト
- main.cpp
- RX72N/Makefile
      
## ビルド方法
- RX72N プラットホームディレクトリーに移動、make する。
- tgl_sample.mot ファイルを書き込む。
   
## 動作


---
      
License
---

MIT
