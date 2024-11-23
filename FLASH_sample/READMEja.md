Renesas RX マイコン Data Flash 操作サンプル
=========

[English](README.md)

## 概要
- RX マイコンを使った内臓データフラッシュへのアクセス、サンプルプログラム。
- ターミナルを使い、対話形式で、データフラッシュメモリーの操作を行う。
- マイコン内蔵ユニークＩＤの表示
---
   
## プロジェクト・リスト
|File|flash_io|動作確認|
|---|---|:-:|
|[main.cpp](main.cpp)|-|-|
|[RX140/Makefile](RX140/Makefile)|[RX24T/flash_io.hpp](../RX24T/flash_io.hpp)|〇|
|[RX220/Makefile](RX220/Makefile)|[RX62x/flash_io.hpp](../RX62x/flash_io.hpp)||
|[RX231/Makefile](RX231/Makefile)|[RX24T/flash_io.hpp](../RX24T/flash_io.hpp)|〇|
|[RX24T/Makefile](RX24T/Makefile)|[RX24T/flash_io.hpp](../RX24T/flash_io.hpp)|〇|
|[RX26T/Makefile](RX26T/Makefile)|[RX62x/flash_io.hpp](../RX62x/flash_io.hpp)||
|[RX62N/Makefile](RX62N/Makefile)|[RX62x/flash_io.hpp](../RX62x/flash_io.hpp)|〇|
|[RX631/Makefile](RX631/Makefile)|[RX62x/flash_io.hpp](../RX62x/flash_io.hpp)|〇|
|[RX64M/Makefile](RX64M/Makefile)|[RX600/flash_io.hpp](../RX600/flash_io.hpp)|〇|
|[RX71M/Makefile](RX71M/Makefile)|[RX600/flash_io.hpp](../RX600/flash_io.hpp)|〇|
|[RX65N/Makefile](RX65N/Makefile)|[RX600/flash_io.hpp](../RX600/flash_io.hpp)|〇|
|[RX72N/Makefile](RX72N/Makefile)|[RX600/flash_io.hpp](../RX600/flash_io.hpp)|〇|
|[RX66T/Makefile](RX66T/Makefile)|[RX600/flash_io.hpp](../RX600/flash_io.hpp)|〇|
|[RX72T/Makefile](RX72T/Makefile)|[RX600/flash_io.hpp](../RX600/flash_io.hpp)|〇|
 
 ---
    
---

## ビルド方法
 - 各プラットホームディレクトリーに移動、make する。
 - flash_sample.mot ファイルを書き込む。
---
   
## 動作
 - LED が 0.25 秒間隔で点滅する。
 - SCI に指定されたポートで、TX（送信）、RX（受信）を行う。
 - TeraTerm などで確認。
 - TeraTerm のシリアル設定：１１５２００ボー、８ビットデータ、１ストップ、パリティ無し。
 - main.cpp の中、SCI の初期化でボーレートは自由に設定できる。
 - 設定出来ない「値」の場合、初期化が失敗する。（極端に遅い、早い）
 - 対話形式で、データフラッシュの操作を行う。
---

## データフラッシュ操作コマンド

### erase [bank] 
- データフラッシュの消去（バンク毎）。
- バンク数は、「容量」を「バンクサイズ」で割ったもの。

### check [bank]
- データフラッシュの消去確認（バンク毎）。

### r org [len] (read)
- 読出し

### write org data... (write)
- 書き込み
- RX231, RX24T では、１バイト毎、他は４バイト毎

### uid (unique ID lists)
- ユニークＩＤの表示

---

## 備考

各マイコンにおけるデータフラッシュの仕様など：

|CPU|容量|バンクサイズ|書き込み単位|ユニークＩＤ数|
|---|:--:|:-:|:-:|:-:|
|RX140|4K|256|1|4|
|RX220|8K|128|2|4|
|RX231|8K|1024|1|4|
|RX24T|8K|1024|1|4|
|RX26T|16K|64|4|3|
|RX62N|32K|2048|8|0|
|RX631|32K|2048|4|4|
|RX64M|64K|64|4|3|
|RX71M|64K|64|4|3|
|RX65N|32K|64|4|4|
|RX72N|32K|64|4|4|
|RX66T|32K|64|4|3|
|RX72T|32K|64|4|3|

-----
   
License
----

MIT
