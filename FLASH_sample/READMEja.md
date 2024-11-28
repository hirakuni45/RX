Renesas RX マイコン Data Flash 操作サンプル
=========

[English](README.md)

## 概要
- RX マイコンを使った内臓データフラッシュへのアクセス、サンプルプログラム。
- ターミナルを使い、対話形式で、データフラッシュメモリーの操作を行う。
- マイコン内蔵ユニークＩＤの表示
---
   
## プロジェクト・リスト
|File/Group|flash_io|動作確認|
|---|---|:-:|
|[main.cpp](main.cpp)|-|-|
|RX111|[RX24T/flash_io.hpp](../RX24T/flash_io.hpp)||
|RX113|[RX24T/flash_io.hpp](../RX24T/flash_io.hpp)||
|RX130|[RX24T/flash_io.hpp](../RX24T/flash_io.hpp)||
|[RX140/Makefile](RX140/Makefile)|[RX24T/flash_io.hpp](../RX24T/flash_io.hpp)|〇|
|[RX220/Makefile](RX220/Makefile)|[RX62x/flash_io.hpp](../RX62x/flash_io.hpp)|〇|
|[RX231/Makefile](RX231/Makefile)|[RX24T/flash_io.hpp](../RX24T/flash_io.hpp)|〇|
|[RX24T/Makefile](RX24T/Makefile)|[RX24T/flash_io.hpp](../RX24T/flash_io.hpp)|〇|
|RX261|[RX24T/flash_io.hpp](../RX24T/flash_io.hpp)||
|[RX26T/Makefile](RX26T/Makefile)|[RX62x/flash_io.hpp](../RX62x/flash_io.hpp)|〇|
|[RX62N/Makefile](RX62N/Makefile)|[RX62x/flash_io.hpp](../RX62x/flash_io.hpp)|〇|
|[RX631/Makefile](RX631/Makefile)|[RX62x/flash_io.hpp](../RX62x/flash_io.hpp)|〇|
|RX63T|[RX62x/flash_io.hpp](../RX62x/flash_io.hpp)||
|[RX64M/Makefile](RX64M/Makefile)|[RX600/flash_io.hpp](../RX600/flash_io.hpp)|〇|
|[RX71M/Makefile](RX71M/Makefile)|[RX600/flash_io.hpp](../RX600/flash_io.hpp)|〇|
|[RX65N/Makefile](RX65N/Makefile)|[RX600/flash_io.hpp](../RX600/flash_io.hpp)|〇|
|RX660|[RX600/flash_io.hpp](../RX600/flash_io.hpp)||
|RX66N|[RX600/flash_io.hpp](../RX600/flash_io.hpp)||
|RX671|[RX600/flash_io.hpp](../RX600/flash_io.hpp)||
|[RX72N/Makefile](RX72N/Makefile)|[RX600/flash_io.hpp](../RX600/flash_io.hpp)|〇|
|RX72M|[RX600/flash_io.hpp](../RX600/flash_io.hpp)||
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

|CPU|容量|バンクサイズ|書き込み単位|消去後の値|ユニークＩＤ数 (32bits)|
|---|:--:|:-:|:-:|:-:|:-:|
|RX110|0K|-|-|-|4|
|RX111|8K|1024|1|0xFF|4|
|RX113|8K|1024|1|0xFF|4|
|RX130|8K|1024|1|0xFF|4|
|RX13T|0K|-|-|-|4|
|RX140|4K|256|1|0xFF|4|
|RX220|8K|2048|2|0x??|4|
|RX23[01]|8K|1024|1|0xFF|4|
|RX23T|0K|-|-|-|4|
|RX24T|8K|1024|1|0xFF|4|
|RX26[01]|8K|256|1|0xFF|4|
|RX26T|16K|64|4|0x??|3|
|RX62[1N]|32K|2048|8|0x??|0|
|RX63[1N]|32K|2048|4|0x??|4|
|RX63T|8K/32K|32|2|0x??|0|
|RX64M|64K|64|4|0x??|3|
|RX71M|64K|64|4|0x??|3|
|RX65[1N]|32K|64|4|0x??|4|
|RX660|32K|64|4|0x??|4|
|RX66N|32K|64|4|0x??|4|
|RX671|8K|64|4|0x??|4|
|RX72N|32K|64|4|0x??|4|
|RX66T|32K|64|4|0x??|3|
|RX72T|32K|64|4|0x??|3|

-----
   
License
----

MIT
