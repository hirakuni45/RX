Renesas RX600 シリーズ・ハードウェアー定義テンプレート
=========

## 概要

ルネサス RX600 シリーズ用ハードウェアー定義 C++ テンプレート・クラス   
ルネサスが提供する、iodefine.h は C言語の規約に違反している為、特定の環境でしか   
正しくコンパイルする事が出来ません。(CC-RX)   
※ビットフィールドの定義は、バイトサイズのみ準拠しますが、１６ビット、又は   
それ以上は、エンディアンの関係などから、結果はコンパイラに依存します。（規約違反）
   
また、非常に冗長であり、可読性が悪いです。   
※独自の方法を使い、プログラムで生成しているものと思います。   
   
※RX600 シリーズ以外（RX24T）でも共有している場合があります。
   
C++ テンプレートを活用したハードウェアー定義は、C++17 以降のコンパイラならエラー   
無くコンパイルする事が可能で、ハードウェアー・マニュアルのレジスター説明に準拠し   
た正式な名称を使っています。   
「iodefine.h」では、ビットフィールド定義の構造上、ビットアクセス、ワードアクセス   
で異なった、インスタンスを付加する必要があり冗長です。
   
ハードウェアーマニュアルに沿った、モジュール別にソースを分割しています。   
   
テンプレートクラスなので、最適化も最大限活用でき、必要なら、さらなる最適化に向け
た実装の余地もあります。   
   
## ペリフェラル名

 - 各デバイスモジュールを抽象化する為、ペリフェラル名を定義しています。
 - 「ペリフェラル名」は、なるべく、ハードウェアーマニュアルで説明されているキーワード
を使うようにしています、詳しくは、[peripheral.hpp](peripheral.hpp?ts=4)を参照して下さい。
 - この名称は、省電力切り替え、専用ポート制御、割り込み制御など、多様な場面で、識別子    
として使われており、ペリフェラル全体で必要な細かい設定を自動化する為に使われます。
   
## 割り込みベクター名

 - 各デバイスが扱う割り込みベクターも、抽象化の為定義されています。
 - 割り込みベクターは、通常ベクター、グループベクター、選択型ベクターなど特有の型を   
持っており、型の違いを利用して、設定方法が異なる場合でも、統一した設定方法になるように
工夫してあります。   
   
## コンビニエンス関数

 - 各デバイスクラスには、ドライバーやサービスクラスからの操作をより抽象的に扱えるように、   
場合により、操作を簡潔に行えるような関数を用意している場合があります。
   
## 名前空間

 - デバイスの名前空間として「device」を使っています。
   
## iodefine.h との併用における解決策

 - ルネサス社が提供する、サンプルプログラムやドライバーを併用して使いたい場合があります。
 - そのような場合 C++ のクラスと「iodefine.h」を併用する必要がある場合があります。 
 - その場合、ペリフェラル名が当たります。
 - これは、「iodefine.h」内で「#define」で定義されている場合がある為です。
 - その場合、「iodefine.h」を当たらない名前に変更し、ルネサス社提供のソースコードを修正する必要があります。
 - C++ テンプレートクラスは名前空間の中に押し込んであり、通常当たらないのですが、「#define」を使われるとどうしようもありません。
 - C++ テンプレートクラス内の「当たる」名前を変更するとなると、大掛かりな修正になると思うので、推奨しません。
   
## プロジェクト・リスト

- [RX64M/RX71M ペリフェラル (peripheral.hpp)](peripheral.hpp?ts=4)
- [RX24T ペリフェラル (RX24T/peripheral.hpp)](../RX24T/peripheral.hpp?ts=4)
- [RX66T ペリフェラル (RX66T/peripheral.hpp)](../RX66T/peripheral.hpp?ts=4)
- [RX65N ペリフェラル (RX65x/peripheral.hpp)](../RX65x/peripheral.hpp?ts=4)
- [RX72N ペリフェラル (RX72N/peripheral.hpp)](../RX72N/peripheral.hpp?ts=4)
- [システム関係、設定クラス (system_io.hpp)](system_io.hpp?ts=4)
- [RX64M/RX71M 電力マネージャー (power_mgr.hpp)](power_mgr.hpp?ts=4)
- [RX24T 電力マネージャー (RX24T/power_mgr.hpp)](../RX24T/power_mgr.hpp?ts=4)
- [RX65N 電力マネージャー (RX65x/power_mgr.hpp)](../RX65x/power_mgr.hpp?ts=4)
- [RX66T 電力マネージャー (RX66T/power_mgr.hpp)](../RX66T/power_mgr.hpp?ts=4)
- [RX72N 電力マネージャー (RX72N/power_mgr.hpp)](../RX72N/power_mgr.hpp?ts=4)
- [RX64M/RX71M 割り込みコントローラ　ICU (icu.hpp)](icu.hpp?ts=4)
- [RX64M/RX71M 割り込みマネージャー・ヘッダー](icu_mgr.hpp?ts=4)
- [I/Oポート・マップ](port_map.hpp?ts=4)
- [SD ホストドライバークラス(sdhi_io)](sdhi_io.hpp?ts=4)
- [A/D 変換クラス](adc_in.hpp?ts=4)
- [D/A 変換クラス](dac_out.hpp?ts=4)
- [データーフラッシュメモリ入出力](flash_io.hpp?ts=4)

|機能|名称|ファイル|RX24T|RX64M/RX71M|RX65N|RX66T|RX72N|
|----|----|--------|-----|-----------|-----|-----|-----|-----|-----|
|システム関係定義|-|[system.hpp](system.hpp?ts=4)|O|O|O|O|O|
|電圧検出回路|LVDA|[lvda.hpp](lvda.hpp?ts=4)|O|O|O|O|O|
|クロック周波数精度測定回路|CAC|[cac.hpp](cac.hpp?ts=4)|O|O|O|O|O|
|メモリプロテクションユニット|MPU|[mpu.hpp](mpu.hpp?ts=4)|O|O|O|O|O|
|DMAコントローラ|DMAC0-7|[dmac.hpp](dmac.hpp?ts=4)|O|O|O|O|O|
|EXDMAコントローラ|EXDMAC0-1|[exdmac.hpp](exdmac.hpp?ts=4)|O|O|O|O|O|
|データトランスファコントローラ|DTC|[dtc.hpp](dtc.hpp?ts=4)|O|O|O|O|O|
|イベントリンクコントローラ|ELC|[elc.hpp](elc.hpp?ts=4)|O|O|O|O|O|
|I/Oポート|-|[port.hpp](port.hpp?ts=4)|O|O|O|O|O|
|マルチファンクションピンコントローラ|MPC|[mpc.hpp](mpc.hpp?ts=4)|O|O|O|O|O|
|マルチファンクションタイマパルスユニット 3|MTU0-n|[mtu3.hpp](mtu3.hpp?ts=4)|O|O|O|O|*|
|ポートアウトプットイネーブル 3|POE3|[poe3.hpp](poe3.hpp?ts=4)|O|O|O|O|*|
|汎用 PWM タイマ|GPTxx|[gpt.hpp](gpt.hpp?ts=4)|O|O|O|O|*|
|16 ビットタイマパルスユニット|TPU0-5|[tpu.hpp](tpu.hpp?ts=4)|O|O|O|O|O|
|プログラマブルパルスジェネレータ|PPG|[ppg.hpp](ppg.hpp?ts=4)|O|O|O|O|O|
|8 ビットタイマ|TMR0-n|[tmr.hpp](tmr.hpp?ts=4)|O|O|O|O|O|
|コンペアマッチタイマ|CMT0-3|[cmt.hpp](cmt.hpp?ts=4)|O|O|O|O|O|
|コンペアマッチタイマ W|CMTW0-1|[cmtw.hpp](cmtw.hpp?ts=4)|O|O|O|O|O|
|リアルタイムクロック|RTC|[rtc.hpp](rtc.hpp?ts=4)|O|O|O|O|O|
|ウォッチドッグタイマ|-|[wdta.hpp](wdta.hpp?ts=4)|O|O|O|O|O|
|独立ウォッチドッグタイマ|-|[iwdt.hpp](iwdt.hpp?ts=4)|O|O|O|O|O|
|機能|名称|ファイル|RX24T|RX64M/RX71M|RX65N|RX66T|RX72N|
|イーサネットコントローラ|ETHERC0-1|[etherc.hpp](etherc.hpp?ts=4)|X|O|O|X|O|
|イーサネットコントローラ用 PTP コントローラ|EPTPC|[eptpc.hpp](eptpc.hpp?ts=4)|X|O|X|X|*|
|イーサネットコントローラ用 DMA コントローラ|EDMAC|[edmac.hpp](edmac.hpp?ts=4)|X|O|O|X|O|
|USB2.0FS ホスト / ファンクションモジュール|USB|[usb.hpp](usb.hpp?ts=4)|X|O|O|O|O|
|USB 2.0 High-Speed ホスト / ファンクションモジュール|USBA|[usba.hpp](usba.hpp?ts=4)|X|O|X|X|X|
|シリアルコミュニケーションインタフェース|SCIn|[sci.hpp](sci.hpp?ts=4)|O|O|O|O|O|
|FIFO 内蔵シリアルコミュニケーションインタフェース|SCIF|[scif.hpp](scif.hpp?ts=4)|X|O|X|X|X|
|I2C バスインタフェース|RIICn|[riic.hpp](riic.hpp?ts=4)|O|O|O|O|O|
|CAN モジュール|CANn|[can.hpp](can.hpp?ts=4)|O|O|O|O|*|
|シリアルペリフェラルインタフェース|RSPIn|[rspi.hpp](rspi.hpp?ts=4)|O|O|O|O|O|
|クワッドシリアルペリフェラルインタフェース|QSPI|[qspi.hpp](qspi.hpp?ts=4)|X|O|O|X|O|
|CRC 演算器|CRC|[crc.hpp](crc.hpp?ts=4)|O|O|O|O|O|
|シリアルサウンドインタフェース|SSI0-1|[ssi.hpp](ssi.hpp?ts=4)|X|O|X|X|X|
|拡張シリアルサウンドインタフェース|SSIE0-1|[ssie.hpp](ssie.hpp?ts=4)|X|X|X|X|O|
|サンプリングレートコンバータ|SRC|[src.hpp](src.hpp?ts=4)|X|O|X|X|X|
|SD ホストインタフェース|(SDHI|[sdhi.hpp](sdhi.hpp?ts=4)|X|O|O|X|O|
|パラレルデータキャプチャユニット|PDC|[pdc.hpp](pdc.hpp?ts=4)|X|O|O|X|O|
|12 ビット A/D コンバータ|S12AD-1|[s12adc.hpp](s12adc.hpp?ts=4)|O|O|O|O|O|
|12 ビット D/A コンバータ|R12DA|[r12da.hpp](r12da.hpp?ts=4)|X|O|O|O|O|
|フラッシュメモリ|-|[flash.hpp](flash.hpp?ts=4)|O|O|O|O|O|
   
-----
   
License

MIT