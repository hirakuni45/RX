Renesas TinyUSB/Host サンプル
=========

[英語版](README.md)
   
---
   
## 概要

- TinyUSB/Host を使ったサンプルプログラム

---

## プロジェクト・リスト

- main.cpp
- RX65N/Makefile（RX65N Envision Kit）
- RX72N/Makefile（RX72N Envision Kit）
- RX72T/Makefile (RX72T HiraKuni45 PGA-100 Board)

---

## ビルド方法

- 各プラットホームディレクトリーに移動、make する。
- tusb_host_sample.mot ファイルを書き込む。

---

## 動作

- (HID) USB/Keyboard を認識し、入力した文字をシリアル出力する。
- 現在、英語キーボードのみ対応。

---

### 動作確認機器

|機器|サプライヤー|型番|USBタイプ|VID|PID|
|---|---|---|---|---|---|
|US キーボード|サンワサプライ（株）|SKB-E3U|HID|1C4F|0027|

---

## 不具合

- 認識しないキーボードがある。（調査中）
- 色々な USB 機器を mount/umonut を繰り返すと、認識しなくなったり、動作が不安定になったりする。（調査中）
- キーボード LED の点灯をサービスしていますが、API が「false」を返して失敗する。（調査中）

---
## License

[TinyUSB: MIT](../tinyusb/LICENCE)

[MyProject: MIT](../LICENSE)
