Renesas RX65N/RX72N Envision Kit Calculator Application
=========
<img src="../docs/calc_sample.jpg" width="50%">

[Japanese](READMEja.md)
   
## Overview
 - Generic Calculator Applications

## Project list
 - main.cpp
 - calc_gui.hpp
 - calc_symbol.hpp
 - calc_func.hpp
 - RX72N/Makefile

### 利用ライブラリ

 - libgmp.a
 - libmpfr.a

### 主なサポートクラス

 - common/basic_arith.hpp
 - common/mpfr.hpp
   
## ビルド方法
 - ターゲットディレクトリーに移動
 - make する。
 - calc_sample.mot ファイルをマイコンに書き込む。 

-----
   
License
----
   
MIT open source license   

libgmp:  GNU LGPL v3 and GNU GPL v2   
libfrmp: GNU LGPL v3   
