Renesas RX マイコン・ハードウェアー定義（共通）テンプレート
=========

## 概要

ルネサス RX シリーズ用ハードウェアー定義 C++ フレームワーク   

- ルネサス社が提供する、ハードウェアー定義は、環境に強く依存します
- C 言語用に実装されており、C++ で利用するには、色々な弊害があります
- 言語規約に違反した実装も多くあり推奨できません
- 非常に冗長であり、可読性が悪いです
- 別ツールにより生成されるもので、一貫性に乏しいです
- 別ツールが無いと入手する事が出来ません
- 「#define」で一般的なキーワードを定義してあり、名前空間内、同名のキーワードを汚染します
- RX マイコンの違いにより部分的に異なる為、共有出来ません
   
C++ テンプレートを活用したハードウェアー定義は、C++17 以降のコンパイラならエラー   
無くコンパイルする事が可能で、ハードウェアー・マニュアルのレジスター解説に準拠し   
た正式な名称を使っています。   
「iodefine.h」では、ビットフィールド定義の構造上、ビットアクセス、ワードアクセス   
で異なった、インスタンスを付加する必要があり冗長です。   
   
ハードウェアーマニュアルに沿った、モジュール別にソースを分割しています。   
   
テンプレートクラスなので、最適化も最大限活用でき、必要なら、さらなる最適化に向けた実装の余地もあります。   
   
C++ の機能を使い、構造的なアクセス、参照アクセスなどにより、ハードウェアーが異なる微妙な違いを吸収します。
   
各デバイスモジュールは、このフレームワークでは「ペリフェラル」と呼んでいます
   
---

## ペリフェラル名

- 各デバイスモジュールを識別する為、ペリフェラル名を定義しています
- RXxxx/peripheral.hpp ファイルに定義されています
- 「ペリフェラル名」は、なるべく、ハードウェアーマニュアルで説明されているキーワードを使うようにしています
- この名称は、省電力切り替え、ポート制御、割り込み制御など、多様な場面で、識別子として使われています
- フレームワーク全体で必要な細かい設定を自動化する為に使われます
- ペリフェラル名は、そのベリフェラルを定義するクラス名と同一の場合もあり、注意が必要です
- ペリフェラル名はスコープを持つ列挙型として、「peripheral」空間に定義されています
   
## クロック・プロファイル定義

- 各マイコンで生成されるクロックは、複数あり、モジュールで異なっています
- BASE, PLL_BASE, PCLKA, PCLKB, PCLKC, PCLKD, FCLK, BCLK などです
- RXxxx/clock_profile.hpp ファイルで定義されています
- このクロック周波数は、必要なら、参照され、各モジュールクラスに定義があります
- 各モジュールは、それを制御するドライバーが、このクロック周波数を参照して周期を決定します
- 周波数は整数で定義されています（割り切れない場合、誤差の扱いに注意）
   
## 省電力制御

- RXxxx/power_mgr.hpp ファイルに定義されています
- ペリフェラル名をキーとして、電源制御を行います
   
## 割り込みベクター名

- RXxxx/icu.hpp ファイルに定義されています
- 各デバイスが扱う割り込みベクターも、抽象化の為定義されています
- 割り込みベクターは、通常ベクター、グループベクター、選択型ベクターなど特有の型を持っています
- 型の違いを利用して、設定方法が異なる場合でも、統一した設定方法になるように工夫してあります
   
## ポート・マッピング

- RX マイコンの各デバイスモジュールは、入出力として、I/O ポートを利用します
- このポートは、排他的に利用する為、どの入出力をどのポートに割り当てるかを設定しなければなりません
- ポートの割り当ては、制限があり、いくつかの候補があります
- ポートマップクラスでは、候補別、グループ別に指定が出来る仕組みを実装してあります
- RXxxx/port_map.hpp ファイルがあり、基本的なポートの候補が定義されています
- この仕組みを利用して、各ドライバークラスは、指定のポートを選択して切り替えるようにしています
- なるべく簡単な指定で、候補を選択出来るようにしています
- 「候補」は、ハードウェアマニュアルの MPC（マルチファンクションピンコントローラ）の「多機能端子の割り当て端子一覧」を元にしています
   
## コンビニエンス関数

- 各デバイスクラスは、ドライバーやサービスクラスからの操作をより抽象的に扱えるように色々な仕組みがあります
- 各デバイスクラスは、操作を簡潔に行えるような関数を用意している場合があります
   
## 名前空間

- デバイスの名前空間として「device」を使っています。
   
## ボード・プロファイル定義

- 各マイコン別に、ハードウェア依存の定義を集約したファイルを用意してあります
- RXxxx/board_profile.hpp ファイルに定義されています
- このファイルには、LED ポート、SCI ポート、CMT チャネルなど、良く使う定義があります
- サンプルアプリケーションプログラムの多くは、この定義を参照して利用しています
- その為、サンプルアプリケーションは、各マイコン特有の設定を意識する必要がありません
   
---

## iodefine.h との併用における解決策

 - ルネサス社が提供する、サンプルプログラムやドライバーを併用して使いたい場合があります
 - そのような場合 C++ のクラスと「iodefine.h」を併用する必要がある場合があります
 - その場合、一般的な名称が当たります（たとえば「USB」など）
 - これは、「iodefine.h」内で「#define」で定義されている場合がある為です
 - その場合、「iodefine.h」を当たらない名前に変更し、ルネサス社提供のソースコードを修正する必要があります
 - C++ テンプレートクラスは名前空間の中に押し込んであり、通常当たらないのですが、「#define」を使われるとどうしようもありません
 - C++ テンプレートクラス内の「当たる」名前を変更するとなると、大掛かりな修正になると思うので、推奨しません
 - 他の方法として、「iodefine.h」を利用するソースと、C++ フレームワークを利用するソースを完全に分離する方法があります
 - C ソースから、C++ の関数を呼ぶ場合、「extern "C"」を使って C++ 内の関数を定義します、その場合、C に準拠したプロトタイプとします

---

## サポートされた RX マイコン（ディレクトリ）

|RX マイコン|動作検証|
|:-:|:-:|
|[RX13T](../RX13T)|-|
|[RX23T](../RX23T)|-|
|[RX24T](../RX24T)|〇|
|[RX24U](../RX24U)|-|
|[RX26T](../RX26T)|〇|
|[RX26x (RX260/RX261)](../RX26x)|-|
|[RX62x (RX621/RX62N)](../RX62x)|〇|
|[RX63T](../RX63T)|〇|
|[RX63x (RX631/RX63N)](../RX63x)|〇|
|[RX64M](../RX64M)|〇|
|[RX65x (RX651/RX65N)](../RX65x)|〇|
|[RX66N](../RX66N)|-|
|[RX66T](../RX66T)|〇|
|[RX71M](../RX71M)|〇|
|[RX72M](../RX72M)|-|
|[RX72N](../RX72N)|〇|
|[RX72T](../RX72T)|〇|
|[RX110](../RX110)|-|
|[RX111](../RX111)|-|
|[RX113](../RX113)|-|
|[RX130](../RX130)|-|
|[RX140](../RX140)|〇|
|[RX220](../RX220)|〇|
|[RX231](../RX231)|〇|
|[RX660](../RX660)|-|
|[RX671](../RX671)|-|

---

## RX マイコン・デバイス・ファイル

|ファイル|機能|クラス|
|---|---|---|
|[bus.hpp](bus.hpp?ts=4)|バス|BUS|
|[cac.hpp](cac.hpp?ts=4)|クロック周波数精度測定回路|CAC|
|[can.hpp](can.hpp?ts=4)|CAN モジュール|CAN|
|[canfd.hpp](canfd.hpp?ts=4)|CAN FD モジュール|CANFD|
|[cmpc.hpp](cmpc.hpp?ts=4)|コンパレータ C|CMPC|
|[cmt.hpp](cmt.hpp?ts=4)|コンペアマッチタイマ|CMT|
|[cmtw.hpp](cmtw.hpp?ts=4)|コンペアマッチタイマ W|CMTW|
|[crc.hpp](crc.hpp?ts=4)|CRC 演算|CRC|
|[crca.hpp](crca.hpp?ts=4)|CRC 演算 A|CRCA|
|[ctsu.hpp](ctsu.hpp?ts=4)|静電容量式タッチセンサ|CTSU|
|[ctsu2.hpp](ctsu2.hpp?ts=4)|静電容量式タッチセンサ 2|CTSU2|
|[dmac.hpp](dmac.hpp?ts=4)|DMA コントローラ|DMAC|
|[doc.hpp](doc.hpp?ts=4)|データ演算回路|DOC|
|[doca.hpp](doca.hpp?ts=4)|データ演算回路 A|DOCA|
|[drw2d.hpp](drw2d.hpp?ts=4)|2D 描画エンジン|DRW2D|
|[dsmif.hpp](dsmif.hpp?ts=4)|Δ-Σ モジュレータインタフェース|DSMIF|
|[dtc.hpp](dtc.hpp?ts=4)|データトランスファコントローラ|DTC|
|[edmac.hpp](edmac.hpp?ts=4)|イーサネットコントローラ用 DMA コントローラ|EDMAC|
|[elc.hpp](elc.hpp?ts=4)|イベントリンクコントローラ|ELC|
|[eptpc.hpp](eptpc.hpp?ts=4)|イーサネットコントローラ用 PTP コントローラ|EPTPC|
|[esc.hpp](esc.hpp?ts=4)|EtherCAT スレーブコントローラ|ESC|
|[etherc.hpp](etherc.hpp?ts=4)|イーサネットコントローラ|ETHERC|
|[exdmac.hpp](exdmac.hpp?ts=4)|EXDMA コントローラ|EXDMAC|
|[flash.hpp](flash.hpp?ts=4)|フラッシュメモリ|FLASH|
|[glcdc.hpp](glcdc.hpp?ts=4)|グラフィック LCD コントローラ|GLCDC|
|[gpt.hpp](gpt.hpp?ts=4)|汎用 PWM タイマ|GPT|
|[gptw.hpp](gptw.hpp?ts=4)|汎用 PWM タイマ W|GPTW|
|[hrpwm.hpp](hrpwm.hpp?ts=4)|高分解能 PWM 波形生成回路|HRPWM|
|[iwdt.hpp](iwdt.hpp?ts=4)|独立ウォッチドッグタイマ|IWDT|
|[lcdc.hpp](lcdc.hpp?ts=4)|LCD コントローラ / ドライバ|LCDC|
|[lpt.hpp](lpt.hpp?ts=4)|ローパワータイマ|LPT|
|[lvda.hpp](lvda.hpp?ts=4)|電圧検出回路|LVDA|
|[mmcif.hpp](mmcif.hpp?ts=4)|マルチメディアカードインタフェース|MMCIF|
|[mpu.hpp](mpu.hpp?ts=4)|メモリプロテクションユニット|MPU|
|[mtu3.hpp](mtu3.hpp?ts=4)|マルチファンクションタイマパルスユニット 3|MTU3|
|[pdc.hpp](pdc.hpp?ts=4)|パラレルデータキャプチャユニット|PDC|
|[pmgi.hpp](pmgi.hpp?ts=4)|PHY マネジメントインタフェース|PMGI|
|[poe3d.hpp](poe3d.hpp?ts=4)|ポートアウトプットイネーブル 3|POE3|
|[poeg.hpp](poeg.hpp?ts=4)|GPTW 用ポートアウトプットイネーブル|POEG|
|[ppg.hpp](ppg.hpp?ts=4)|プログラマブルパルスジェネレータ|PPG|
|[qspi.hpp](qspi.hpp?ts=4)|クワッドシリアルペリフェラルインタフェース|QSPI|
|[qspix.hpp](qspix.hpp?ts=4)|クワッドシリアルペリフェラルインタフェース X|QSPIX|
|[r12da.hpp](r12da.hpp?ts=4)|12 ビット D/A コンバータ|R12DA|
|[remc.hpp](remc.hpp?ts=4)|リモコン信号受信機能|REMC|
|[ri3c.hpp](ri3c.hpp?ts=4)|I3C バスインタフェース|RI3C|
|[riic.hpp](riic.hpp?ts=4)|I2C バスインタフェース|RIIC|
|[riichs.hpp](riichs.hpp?ts=4)|ハイスピード I2C バスインタフェース|RIICHS|
|[rscan.hpp](rscan.hpp?ts=4)|RSCAN モジュール|RSCAN|
|[rsci.hpp](rsci.hpp?ts=4)|シリアルコミュニケーションインタフェース|RSCI|
|[rspi.hpp](rspi.hpp?ts=4)|シリアルペリフェラルインタフェース|RSPI|
|[rspia.hpp](rspia.hpp?ts=4)|シリアルペリフェラルインタフェース A|RSPIA|
|[rtc.hpp](rtc.hpp?ts=4)|リアルタイムクロック|RTC|
|[s12adf.hpp](s12adf.hpp?ts=4)|12 ビット A/D コンバータ|S12ADC|
|[sci_a.hpp](sci_a.hpp?ts=4)|シリアルコミュニケーションインタフェース a|SCIa|
|[sci_c.hpp](sci_c.hpp?ts=4)|シリアルコミュニケーションインタフェース c|SCIc|
|[sci_d.hpp](sci_d.hpp?ts=4)|シリアルコミュニケーションインタフェース d|SCId|
|[sci_e.hpp](sci_e.hpp?ts=4)|シリアルコミュニケーションインタフェース e|SCIe|
|[sci_f.hpp](sci_f.hpp?ts=4)|シリアルコミュニケーションインタフェース f|SCIf|
|[sci_g.hpp](sci_g.hpp?ts=4)|シリアルコミュニケーションインタフェース g|SCIg|
|[sci_h.hpp](sci_h.hpp?ts=4)|シリアルコミュニケーションインタフェース h|SCIh|
|[sci_i.hpp](sci_i.hpp?ts=4)|シリアルコミュニケーションインタフェース i|SCIi|
|[sci_j.hpp](sci_j.hpp?ts=4)|シリアルコミュニケーションインタフェース j|SCIj|
|[sci_k.hpp](sci_k.hpp?ts=4)|シリアルコミュニケーションインタフェース k|SCIk|
|[sci_m.hpp](sci_m.hpp?ts=4)|シリアルコミュニケーションインタフェース m|SCIm|
|[scif.hpp](scif.hpp?ts=4)|FIFO 内蔵シリアルコミュニケーションインタフェース|SCIF|
|[sdhi.hpp](sdhi.hpp?ts=4)|SD ホストインタフェース|SDHI|
|[sdsi.hpp](sdsi.hpp?ts=4)|SD スレーブインタフェース|SDSI|
|[src.hpp](src.hpp?ts=4)|サンプリングレートコンバータ|SRC|
|[ssi.hpp](ssi.hpp?ts=4)|シリアルサウンドインタフェース|SSI|
|[ssie.hpp](ssie.hpp?ts=4)|拡張シリアルサウンドインタフェース|SSIE|
|[system.hpp](system.hpp?ts=4)|クロック発生回路/システム制御|SYSTEM|
|[tfu.hpp](tfu.hpp?ts=4)|三角関数演算器|TFU|
|[tmr.hpp](tmr.hpp?ts=4)|8 ビットタイマ|TMR|
|[tpu.hpp](tpu.hpp?ts=4)|16 ビットタイマパルスユニット|TPU|
|[usb.hpp](usb.hpp?ts=4)|USB2.0FS ホスト / ファンクションモジュール|USB|
|[usba.hpp](usba.hpp?ts=4)|USB 2.0 Full-Speed ホスト / ファンクションモジュール|USBA|
|[vbatt.hpp](vbatt.hpp?ts=4)|バッテリバックアップ機能|VBATT|
|[wdta.hpp](wdta.hpp?ts=4)|ウォッチドッグタイマ|WDT|


## RX マイコン・サポート・ファイル

|ファイル|機能|
|---|---|
|[ad_utils.hpp](ad_utils.hpp?ts=4)|A/D 変換ユーティリティ|
|[adc_in.hpp](adc_in.hpp?ts=4)|A/D 入力|
|[adc_in_base.hpp](adc_in_base.hpp?ts=4)|A/D 変換ベース|
|[bus_mgr.hpp](bus_mgr.hpp?ts=4)|バス・マネージャー|
|[can_frame.hpp](can_frame.hpp?ts=4)|CAN フレーム定義|
|[canfd_frame.hpp](canfd_frame.hpp?ts=4)|CAN FD フレーム定義|
|[dac_out.hpp](dac_out.hpp?ts=4)|D/A 出力|
|[dmac_mgr.hpp](dmac_mgr.hpp?ts=4)|DMAC マネージャー|
|[drw2d_mgr.hpp](drw2d_mgr.hpp?ts=4)|DRW2D マネージャー|
|[ether_io.hpp](ether_io.hpp?ts=4)|イーサーネット入出力|
|[flash_io.hpp](flash_io.hpp?ts=4)|フラッシュメモリ入出力|
|[flash_io_base.hpp](flash_io_base.hpp?ts=4)|フラッシュメモリ入出力ベース|
|[glcdc_def.hpp](glcdc_def.hpp?ts=4)|GLCDC 基本定義|
|[glcdc_mgr.hpp](glcdc_mgr.hpp?ts=4)|GLCDC マネージャー|
|[icu_base.hpp](icu_base.hpp?ts=4)|割り込み制御ベース|
|[icu_utils.hpp](icu_utils.hpp?ts=4)|割り込み制御ユーティリティ|
|[mtu_base.hpp](mtu_base.hpp?ts=4)|MTU ベース|
|[port_base.hpp](port_base.hpp?ts=4)|ポート・ベース|
|[port_map_irq.hpp](port_map_irq.hpp?ts=4)|IRQ ポート・マップ|
|[port_map_order.hpp](port_map_order.hpp?ts=4)|ポート・マップ・オーダー|
|[rtc_io.hpp](rtc_io.hpp?ts=4)|RTC 入出力|
|[sci_base.hpp](sci_base.hpp?ts=4)|SCI ベース|
|[sdram.hpp](sdram.hpp?ts=4)|SDRAM 設定|
|[ssi_io.hpp](ssi_io.hpp?ts=4)|SSI 入出力|
|[ssie_io.hpp](ssie_io.hpp?ts=4)|SSIE 入出力|
|[standby_ram.hpp](standby_ram.hpp?ts=4)|スタンバイ RAM 制御|
|[system_io.hpp](system_io.hpp?ts=4)|クロック制御など|

-----
   
License

MIT