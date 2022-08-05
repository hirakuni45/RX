Renesas TinyUSB/Host サンプル
=========

[Japanese](READMEja.md)
   
---
   
## 概要
- TinyUSB/Host を使ったサンプルプログラム

## プロジェクト・リスト
- main.cpp
- RX72N/Makefile（RX72N Envision Kit）
      
## ビルド方法
- 各プラットホームディレクトリーに移動、make する。
- tusb_host_sample.mot ファイルを書き込む。
   
## 動作
- (HID) USB/Keyboard を認識し、入力した文字をシリアル出力する。

## 不具合
- 認識しないキーボードがある。（原因を調査中）
- 色々な USB 機器を mount/umonut を繰り返すと、認識しなくなったり、動作が不安定になったりする。（調査中）

License
---

MIT
