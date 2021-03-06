Renesas RX65N/RX72N Envision Kit ガジェット
=========

[English](README.md)

<img src="../docs/DSOS_SQUARE.jpg" width="50%"><img src="../docs/DSOS_SIN.jpg" width="50%">

**RX65N Envision Kit の場合、ダブルバッファが物理的に出来ない為、操作性に難があります。**   
**RX72N Envision Kit で利用下さい。**

## 概要
 - RX72N Envision Kit で実現するデジタルストレージオシロスコープ
 - 最大サンプリング速度 500 [ns] (2MHz)
 - 最大２チャネル同時
 - 内蔵１２ビット A/D コンバータ利用（４０９６段階）
 - タッチパネルを使った操作
 - 1:1 プローブ専用（1Mオーム）

---

## プロジェクト・リスト
 - main.cpp
 - capture.hpp
 - render_base.hpp
 - render_wave.hpp
 - dso_gui.hpp
 - resource.hpp resource.cpp
 - resource/cnv.sh  gui_parts.png  res_dir_0.h  res_dir_1.h  res_dir_2.h  res_dir_3.h
 - Makefile
   
リソースの画像を変換するには、bmc.exe が必要です。
[ビットマップコンバーター](https://github.com/hirakuni45/glfw3_app/tree/master/glfw3_app/bmc)

---

## ハードウェアーの準備
 - SD カードインターフェースの準備（キャプチャー波形を書き込む場合）
 - アナログ入力の接続

|ターゲット        | CH0  | CH1  |
|------------------|------|------|
|RX65N Envision Kit|AIN000|AIN114|
|RX72N Envision Kit|AIN007|AIN108|

---

## アナログフロントエンド


## 機能

チャネル電圧レンジ切替:
10V,5V,2V,1V,500mV,200mV,100mV,50mV,10mV

チャネル動作切り替：
AC,GND,DC,OFF

サンプリング周期（グリッド）：
1us,2us,5us
10us,20us,50us
100us,200us,500us
1ms,2ms,5ms
10ms,20ms,50ms
100ms,200ms,500ms

トリガー条件：
None
One
Run
CH0-Pos
CH1-Pos
CH0-Neg
CH1-Neg

計測：
Off
Time Sub
CH0 Sub
CH1 Sub
Time Abs
CH0 Abs
CH1 Abs

基準波の出力：
10KHz の矩形波

---

## ビルド方法
 - make する。
 - dsos_sample.mot ファイルをターゲットに書き込む。

## 操作方法
    
-----
   
License
----

MIT
