Renesas RX24T, RX64M, RX71M, RX65N, RX66T, RX72N, RX72T I2C サンプル
=========

## 概要

- RX マイコンを使った I2C のサンプルプログラム
- シリアル接続したターミナルとの間で、対話式に I2C デバイスとの通信の確認、操作を行う事が出来る。
- 「list」に示された、I2C デバイスとの通信では、専用コマンドが利用出来る。
- IICA、SCI_I2C など複数のペリフェラルを切り替えて利用可能。

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
- プルアップ抵抗を適宜設定する。
- 利用する電圧には十分注意する事。

|I2C デバイス|メーカー|機能|
|-----------|-------|----|
|AS5600     |ams|12bits 磁気エンコーダ|
|BMP280     |Bosch Sensotec|温度、圧力センサ|
|DS3231     |Maxim Integrated|リアルタイムクロック|
|EEPROM[0-7]|Micro Chip|EEPROM|

## ビルド方法

 - 各プラットホームディレクトリーに移動、make する。
 - i2c_sample.mot ファイルを書き込む。
   
## 動作

- LED インジケーターの点滅。
- シリアルターミナルを接続して、対話形式の操作を行う事が出来る。

## I2C マスターコマンド

|コマンド|機能|
|-------|----|
|list|対応デバイスの表示|
|scan [start=0] [end=127]|接続I2Cされた I2C デバイスのスキャン|
|exec I2C-name|list 表示されたデバイス操作を起動|
|adr [X]|I2C アドレスを設定|
|r [num=1]|デバイスから num バイトを表示|
|s data...|デバイスにデータを書き込む|
   
※exec で起動した場合、exit で戻る。

## BMP280 コマンド

|コマンド|機能|
|-------|----|
|list|温度、圧力、標高を表示|

## DS3231 コマンド

|コマンド|機能|
|-------|----|
|date|日付、時間の表示|
|date yyyy/mm/dd hh:mm[:ss]|日付、時間の設定|

## EEPROM コマンド

|コマンド|機能|
|-------|----|
|read ORG [END=+16]|EEPROM からデータを読み込み表示|
|write ORG DATA...|EEPROM へデータ書き込み|

## AS5600 コマンド

|コマンド|機能|
|-------|----|
|list|磁気検出、回転位置表示|
|run|連続的に回転位置など表示（CTRL-Cで抜ける）|

-----
   
License
----

MIT
