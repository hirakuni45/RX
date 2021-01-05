Renesas RX65N/RX72N Envision Kit GUI サンプル
=========

<img src="../docs/gui_sample.jpg" width="50%">

[English](README.md)
   
## 概要

 - C++ GUI フレームワークを利用したサンプル
 - GUI のレンダリングは、ソフトウェアーで行っているので、どんなプラットホームでも利用可能です。
 - 基本的な GUI フレームワークの利用方法や、操作に対する考え方が判ります。
    
## プロジェクト・リスト

 - main.cpp
 - RX65N/Makefile
 - RX72N/Makefile
   
### 主な widget クラス

 - graphics/widget.hpp
 - graphics/widget_director.hpp
 - graphics/button.hpp
 - graphics/check.hpp
 - graphics/radio.hpp
 - graphics/slider.hpp
 - graphics/menu.hpp
 - graphics/text.hpp
 - graphics/textbox.hpp
   
## ビルド方法

 - ターゲットディレクトリーに移動
 - make する。
 - GUI_sample.mot ファイルをマイコンに書き込む。

-----
   
License
----
   
MIT open source license   
