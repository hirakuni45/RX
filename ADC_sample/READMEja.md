Renesas RX マイコン A/D 変換サンプル
=========

[英語版](README.md)

---

## 概要

RX マイコンを使った A/D 変換を行うサンプルプログラム
   
---

## プロジェクト・リスト

- main.cpp
- RX140/Makefile
- RX220/Makefile
- RX231/Makefile
- RX24T/Makefile
- RX26T/Makefile
- RX631/Makefile
- RX63T/Makefile
- RX64M/Makefile
- RX72T/Makefile

---

## ハードウェアーの準備（全般）

|RXマイコン|A/D 定義クラス|A/D 制御クラス|AN000 ポート|
|:-:|:-:|:-:|:-:|
|RX140|[RX231/s12ade.hpp](../RX231/s12ade.hpp?ts=4)|[RX24T/adc_in.hpp](../RX24T/adc_in.hpp?ts=4)|P40|
|RX220|[RX220/s12ad.hpp](../RX220/s12ad.hpp?ts=4)|[RX24T/adc_in.hpp](../RX24T/adc_in.hpp?ts=4)|P40|
|RX231|[RX231/s12ade.hpp](../RX231/s12ade.hpp?ts=4)|[RX24T/adc_in.hpp](../RX24T/adc_in.hpp?ts=4)|P40|
|RX24T|[RX24T/s12ad.hpp](../RX24T/s12ad.hpp?ts=4)|[RX24T/adc_in.hpp](../RX24T/adc_in.hpp?ts=4)|P40|
|RX26T|[RX26T/s12adh.hpp](../RX26T/s12adh.hpp?ts=4)|[RX600/adc_in.hpp](../RX600/adc_in.hpp?ts=4)|P40|
|RX631|[RX63x/s12ad.hpp](../RX63x/s12ad.hpp?ts=4)|[RX600/adc_in.hpp](../RX600/adc_in.hpp?ts=4)|P40|
|RX63T|[RX63T/s12adb.hpp](../RX63T/s12adb.hpp?ts=4)|[RX600/adc_in.hpp](../RX600/adc_in.hpp?ts=4)|P40|
|RX64M|[RX64M/s12adc.hpp](../RX64M/s12adc.hpp?ts=4)|[RX600/adc_in.hpp](../RX600/adc_in.hpp?ts=4)|P40|
|RX72T|[RX72T/s12adh.hpp](../RX72T/s12adh.hpp?ts=4)|[RX600/adc_in.hpp](../RX600/adc_in.hpp?ts=4)|P40|

- A/D 変換ユニットは「device::S12AD」を利用します
- 変換モードは「シングル」を使います
- AN000 A/D 入力を変換するので、ボリュームなどを接続する

---

## ビルド方法

- 各プラットホームディレクトリーに移動、make する
- adc_sample.mot ファイルを書き込む
- 各マイコンディレクトリには「board_profile.hpp」があり、基板固有の設定を行う

---

## 動作

- LED 接続ポートは、各マイコンディレクトリの「board_profile.hpp」を参照
- シリアルポートは、各マイコンディレクトリの「board_profile.hpp」を参照
- LED が 0.25 秒間隔で点滅する
- シリアル設定：１１５２００ボー、８ビットデータ、１ストップ、パリティ無し
- １秒間隔で、AN000 アナログ入力の変換を行い、ターミナルに出力する

---
   
License
   
[MIT](../LICENSE)
