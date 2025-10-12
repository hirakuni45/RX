
## RX23T features / 特徴

- RXv2 core / RXv2 コア
- Maximum operating frequency 40MHz / 最大動作周波数 40MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 2.7V ～ 5.5V Operation / 動作
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 8 Bits D/A (for Compalator) / ８ビットＤ／Ａ変換器（コンパレーター用）

### Package/パッケージ

|R5F523T---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F523TxxxFM|LFQFP|64|0.50|
|R5F523TxxxFD|LQFP|52|0.65|
|R5F523TxxxFL|LFQFP|48|0.50|

### Ambient operating temperature/動作周囲温度

|R5F523T--X--|degree Celsius|
|---|:-:|
|R5F523TxxDxx|-40 ～ +85℃|
|R5F523TxxGxx|-40 ～ +105℃|

### Memoey size/メモリ容量

|R5F523TX----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F523T5xxxx|128K|12K|0|
|R5F523T3xxxx|64K|12K|0|

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|0K|-|-|-|-|0|

---

## RX23T Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Source|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F523T5|128K|12K|-|[R5F523T5.ld](R5F523T5.ld?ts=4)|512|256|

---

## RX23T Dedicated class / 専用クラス

|Function/機能|Source|Remarks/備考|
|---|---|:-:|
|Peripheral Name/ペリフェラル名|[peripheral.hpp](peripheral.hpp?ts=4)||
|Hardware-specific Definition/ハード固有定義|[board_profile.hpp](board_profile.hpp?ts=4)||
|Operating Frequency Definition/動作周波数定義|[clock_profile.hpp](clock_profile.hpp?ts=4)||
|Power Control/電力制御|[power_mgr.hpp](power_mgr.hpp?ts=4)||
|Port Definition/ポート定義|[port.hpp](port.hpp?ts=4)||
|Interrupt Definition/割り込み定義|[icu.hpp](icu.hpp?ts=4)||
|Port Function Definition/ポート機能定義|[mpc.hpp](mpc.hpp?ts=4)||
|Port Mapping/ポートマッピング|[port_map.hpp](port_map.hpp?ts=4)||
|Port Mapping IRQ/ポートマッピング IRQ|[port_map_irq.hpp](port_map_irq.hpp?ts=4)||
|Port Mapping MTU/ポートマッピング MTU|[port_map_mtu.hpp](port_map_mtu.hpp?ts=4)||
|Port Mapping TMR/ポートマッピング TMR|[port_map_tmr.hpp](port_map_tmr.hpp?ts=4)||
|A/D Definition/A/D 定義|[s12ad.hpp](s12ad.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 64|
|---|---|
|VCL|VCL(3)|
|Reset Input/リセット入力|RES#(6)|
|Mode Controle/モード制御|MD/FINED(5)|
|RXD|PD5/RXD1(14)|
|TXD|PD3/TXD1(16)|
|Power/電源|VCC(10), VCC(42)|
|GND/接地|VSS(8), VSS(44)|
|Analog Power/アナログ電源|AVCC0(57)|
|Analog GND/アナログ接地|AVSS0(60)|
|Analog Refarence L0/アナログ基準電源Ｌ0|VREFL0(59)|
|Analog Refarence H0/アナログ基準電源Ｈ0|VREFH0(58)|
|OSC in|EXTAL(9)|
|OSC out|XTAL(7)|

- VCL: 4.7uF/25V

|Mode/モード|MD|
|---|:---:|
|Serial BOOT/シリアルブート|0|
|Single Chip/シングルチップ|1|

---

## Peripheral / ペリフェラル

- [peripheral.hpp](peripheral.hpp?ts=4)

|Peripheral|Function|機能|
|---|---|---|
|CAC|Clock Frequency Accuracy Measurement Circuit|クロック周波数精度測定回路|
|DTC|Data Transfer Controller|データトランスファコントローラ|
|MTU0|Multi-Function Timer Pulse Unit 0|マルチファンクションタイマパルスユニット０|
|MTU1|Multi-Function Timer Pulse Unit 1|マルチファンクションタイマパルスユニット１|
|MTU2|Multi-Function Timer Pulse Unit 2|マルチファンクションタイマパルスユニット２|
|MTU3|Multi-Function Timer Pulse Unit 3|マルチファンクションタイマパルスユニット３|
|MTU4|Multi-Function Timer Pulse Unit 4|マルチファンクションタイマパルスユニット４|
|MTU5|Multi-Function Timer Pulse Unit 5|マルチファンクションタイマパルスユニット５|
|POE3|Port Output Enable 3|ポートアウトプットイネーブル３|
|TMR0|8-Bit Timer 0|8 ビットタイマ０|
|TMR1|8-Bit Timer 1|8 ビットタイマ１|
|TMR2|8-Bit Timer 2|8 ビットタイマ２|
|TMR3|8-Bit Timer 3|8 ビットタイマ３|
|CMT0|Compare Match Timer 0|コンペアマッチタイマ０|
|CMT1|Compare Match Timer 1|コンペアマッチタイマ１|
|CMT2|Compare Match Timer 2|コンペアマッチタイマ２|
|CMT3|Compare Match Timer 3|コンペアマッチタイマ３|
|IWDT|Independent Watchdog Timer|独立ウォッチドッグタイマ|
|SCI1|Serial Communications Interface 1|シリアルコミュニケーションインタフェース１|
|SCI5|Serial Communications Interface 5|シリアルコミュニケーションインタフェース５|
|RIIC0|I2C-bus Interface 0|I2C バスインタフェース０|
|RSPI0|Serial Peripheral Interface 0|シリアルペリフェラルインタフェース０|
|CRC|CRC Calculator|CRC 演算器|
|S12AD|12-Bit A/D Converter|12 ビット A/D コンバータ|
|DA|8-Bit D/A Converter|8 ビット D/A コンバータ|
|CMPC0|Comparator C0|コンパレーターＣ０|
|CMPC1|Comparator C1|コンパレーターＣ１|
|CMPC2|Comparator C2|コンパレーターＣ２|
|DOC|Data Operation Circuit|データ演算回路|

---

## Port map order (IRQ) / ポートマップ候補 (IRQ)

- [port_map_irq.hpp](port_map_irq.hpp?ts=4)

### LFQFP64

|[IRQ]|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|IRQ0|P10 (62)|P93 (30)|-|-|
|IRQ1|P11 (61)|P94 (29)|-|-|
|IRQ2|P00 (2)|P22 (48)|PB1 (25)|PD4 (15)|
|IRQ3|P24 (46)|PB4 (21)|PD5 (14)|-|
|IRQ4|P01 (4)|P23 (47)|PA2 (28)|-|
|IRQ5|P02 (1)|P70 (39)|PB6 (18)|PD6 (13)|

---

## Port map order / ポートマップ候補

- [port_map.hpp](port_map.hpp?ts=4)

### LFQFP64

|Peripheral|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|SCI1 / RXD|PD5 (14)|-|-|-|
|SCI1 / TXD|PD3 (16)|-|-|-|
|SCI1 / SCK|PD4 (15)|-|-|-|
|SCI5 / RXD|PB1 (25)|PB6 (18)|PB6 (18)|-|
|SCI5 / TXD|PB2 (24)|PB5 (19)|PB5 (19)|-|
|SCI5 / SCK|PB3 (23)|PB3 (23)|PB7 (17)|-|
|RIIC0 / SCL|PB1 (25)|-|-|-|
|RIIC0 / SDA|PB2 (24)|-|-|-|
|RSPI0 / RSPCK|P24 (46)|P93 (30)|PA4 (64)|PB3 (23)|
|RSPI0 / MOSI|P23 (47)|P23 (47)|PB0 (26)|PB0 (26)|
|RSPI0 / MISO|P22 (48)|P94 (29)|PA5 (63)|PA5 (63)|
|RSPI0 / SSL0|P30 (45)|PA3 (27)|PD6 (13)|-|
|RSPI0 / SSL1|P31 (43)|PA2 (28)|PD7 (12)|-|
|RSPI0 / SSL2|P32 (41)|P92 (31)|-|-|
|RSPI0 / SSL3|P33 (40)|P91 (32)|-|-|

---

## Port map order (MTU) / ポートマップ候補 (MTU)

- [port_map_mtu.hpp](port_map_mtu.hpp?ts=4)

### LFQFP64

|MTU|FIRST|SECOND|THIRD|
|---|---|---|---|
|MTIOC0A|P31 (43)|PB3 (23)|-|
|MTIOC0B|P30 (45)|P93 (30)|PB2 (24)|
|MTIOC0C|P94 (29)|PB1 (25)|-|
|MTIOC0D|PB0 (26)|-|-|
|MTIOC1A|PA5 (63)|-|-|
|MTIOC1B|PA4 (64)|-|-|
|MTIOC2A|PA3 (27)|-|-|
|MTIOC2B|PA2 (28)|-|-|
|MTIOC3A|P11 (61)|P33 (40)|-|
|MTIOC3B|P71 (38)|-|-|
|MTIOC3C|P32 (41)|-|-|
|MTIOC3D|P74 (35)|-|-|
|MTIOC4A|P72 (37)|-|-|
|MTIOC4B|P73 (36)|-|-|
|MTIOC4C|P75 (34)|-|-|
|MTIOC4D|P76 (33)|-|-|
|MTIOC5U|P24 (46)|-|-|
|MTIOC5V|P23 (47)|-|-|
|MTIOC5W|P22 (48)|-|-|
|MTCLKA|P33 (40)|-|-|
|MTCLKB|P32 (41)|-|-|
|MTCLKC|P11 (61)|P31 (43)|-|
|MTCLKD|P10 (62)|P30 (45)|-|
|ADSM0|PB2 (24)|-|-|

---

## Port map order (TMR) / ポートマップ候補 (TMR)

- [port_map_tmr.hpp](port_map_tmr.hpp?ts=4)

### LFQFP64

|TMR|FIRST|SECOND|
|---|---|---|
|TMO0|PD3 (16)|-|
|TMCI0|PD4 (15)|-|
|TMRI0|PD5 (14)|-|
|TMO1|P94 (29)|PD6 (13)|
|TMCI1|P92 (31)|-|
|TMRI1|P93 (30)|PD7 (12)|
|TMO2|P23 (47)|-|
|TMCI2|P24 (46)|-|
|TMRI2|P22 (48)|-|
|TMO3|P11 (61)|-|
|TMCI3|PA5 (63)|-|
|TMRI3|P10 (62)|-|

---

## rx_prog Flash Programming / rx_prog フラッシュプログラム

||Support/サポート|operation verification/動作検証|
|-|:-:|:-:|
|[rxprog](../rxprog)|-|-|

---

Translated with www.DeepL.com/Translator (free version)

---

## License

[MIT](../LICENSE)
