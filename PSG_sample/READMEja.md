Renesas RX231, RX26T, RX62N, RX631, RX64M, RX65N, RX71M, RX66T, RX72N, RX72T 疑似 PSG 演奏サンプル
=========
   
<iframe width="560" height="315" src="https://www.youtube.com/watch?v=4ZHuMYcSQko" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

[English](README.md)
   
## 概要

RX マイコンを使った 疑似 PSG 音楽演奏サンプルです。 
   
- RX72N では、SSIE からデジタルデータ出力されます。
- 通常、DA0/DA1 からアナログ出力されます。
- 元は、R8C 用に作られた物ですが、RX マイコン内蔵の D/A 出力では、かなり高品質な音が出ます。
- 疑似 PSG クラスでは、主に矩形波を使った（ファミコン並）音楽演奏を行う為の実装がされています。
- サンプリングは 48KHz で行っています。
   
## プロジェクト・リスト

- main.cpp
- RX231/Makefile
- RX26T/Makefile
- RX62N/Makefile
- RX631/Makefile (for GR-CITRUS)
- RX64M/Makefile
- RX71M/Makefile
- RX65N/Makefile (for RX65N Envision Kit)
- RX66T/Makefile
- RX72N/Makefile (for RX72N Envision Kit)
- RX72T/Makefile
   
## ハードウェアーの準備

 - インジケーター LED を指定のポートに接続する。
 - DA0/DA1 にアンプを接続して下さい。
 - RX72N Envision Kit では、付属のアナログ出力端子から出力されます。
 - DA0/DA1 アナログ出力では、無音レベルは、電源電圧の中間電位となっている為、ラインアンプに接続する際には、電圧変換を行う必要があります。
 - アナログからライン出力への参考回路は、(AUDIO_sample)[../AUDIO_sample] と同等なので参照して下さい。
   
## リソースの準備

- 得に必要ありません。
- ドラゴンクエスト１、ラダトーム城のピアノバージョンのスコアが入力されています。（途中までです）
- 自分でスコアを作る事も出来ます。
   
## ビルド方法

- 各プラットホームディレクトリーに移動、make する。
- psg_sample.mot ファイルをマイコンに書き込む。
   
## 動作

- LED が 0.25 秒間隔で点滅する。
- 音楽の演奏が開始され、DA0/DA1 からアナログ出力（モノラル）
- RX72N では、SSIE 出力
- GR-CITRUS（RX631）の D/A 出力は、DA1 のみ。（DA0 は端子がありません）
    
-----
   
License
----

[MIT](../LICENSE)
