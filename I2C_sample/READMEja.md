Renesas RX24T, RX64M, RX71M, RX65N, RX66T, RX72N I2C サンプル
=========

## 概要

- RX マイコンを使った I2C のサンプルプログラム
- シリアル接続したターミナルとの間で、対話式に I2C デバイスとの通信の確認、操作を行う事が出来る。
- 「list」に示された、I2C デバイスとの通信では、専用コマンドが利用出来る。

## プロジェクト・リスト
 - main.cpp
 - exec_cmd.hap
 - BMP280_exec.hpp
 - DS3231_exec.hpp
 - EEPROM_exec.hpp
 - RX24T/Makefile
 - RX64M/Makefile
 - RX71M/Makefile
 - RX65N/Makefile
 - RX66T/Makefile
 - RX72N/Makefile
   
## ハードウェアーの準備

- 指定の I2C 信号を、I2C デバイスに接続する。

|I2C デバイス|機能|
|-----------|--------|
|BMP280     |温度、圧力センサ|
|DS3231     |リアルタイムクロック|
|EEPROM[0-7]|EEPROM|

## ビルド方法

 - 各プラットホームディレクトリーに移動、make する。
 - i2c_sample.mot ファイルを書き込む。
   
## 動作

- LED インジケーターの点滅
- シリアルターミナルで、対話形式の操作

## I2C マスターコマンド

## BMP280 コマンド

## DS3231 コマンド

## EEPROM コマンド
   
-----
   
License
----

MIT
