
## RX63T features / 特徴

- RXv1 core / RXv1 コア
- Maximum operating frequency 100MHz / 最大動作周波数 100MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 3.3V ～ 5.0V Operation / 動作
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 10 Bits D/A / １０ビットＤ／Ａ変換器

### Package/パッケージ

|R5F563T---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F563TxxxFB|LFQFP|144|0.50|
|R5F563TxxxFP|LFQFP|100|0.50|
|R5F563TxxxFP|LFQFP|100|0.50|
|R5F563TxxxFP|LFQFP|100|0.50|
|R5F563TxxxFP|LFQFP|100|0.50|
|R5F563TxxxFP|LFQFP|100|0.50|

### Ambient operating temperature/動作周囲温度

|R5F563T--X--|degree Celsius|
|---|:-:|
|R5F563TxxDxx|-40 ～ +85℃|
|R5F563TxxGxx|-40 ～ +105℃|

### VCC, CAN

|R5F563T-X---|VCC|CAN|
|---|:-:|:-:|
|R5F563TxAxxx|5V|〇|
|R5F563TxBxxx|3V|〇|
|R5F563TxDxxx|5V|-|
|R5F563TxExxx|3V|-|

### Memoey size/メモリ容量

|R5F563TX----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F563TExxxx|512K|48K|32K|
|R5F563TCxxxx|384K|32K|32K|
|R5F563TBxxxx|256K|24K|32K|
|R5F563T6xxxx|64K|8K|8K|
|R5F563T5xxxx|48K|8K|8K|
|R5F563T4xxxx|32K|8K|8K|

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|8K/32K|32|2/32|2|0x??|0|

---

## RX63T Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F563T6|64K|8K|8K|[R5F563T6.ld](R5F563T6.ld?ts=4)|768|256|

---

## RX63T Dedicated class / 専用クラス

|Function/機能|Source|Remarks/備考|
|---|---|:-:|
|Peripheral Name/ペリフェラル名|[peripheral.hpp](peripheral.hpp?ts=4)||
|Hardware-specific Definition/ハード固有定義|[board_profile.hpp](board_profile.hpp?ts=4)||
|Operating Frequency Definition/動作周波数定義|[clock_profile.hpp](clock_profile.hpp?ts=4)||
|Power Control/電力制御|[power_mgr.hpp](power_mgr.hpp?ts=4)||
|Port Definition/ポート定義|[port.hpp](port.hpp?ts=4)||
|Interrupt Definition/割り込み定義|[icu.hpp](icu.hpp?ts=4)||
|Interrupt Management/割り込み管理|[icu_mgr.hpp](icu_mgr.hpp?ts=4)||
|Port Function Definition/ポート機能定義|[mpc.hpp](mpc.hpp?ts=4)||
|Port Mapping/ポートマッピング|[port_map.hpp](port_map.hpp?ts=4)||
|Port Mapping IRQ/ポートマッピング IRQ|[port_map_irq.hpp](port_map_irq.hpp?ts=4)||
|Port Mapping MTU/ポートマッピング MTU|[port_map_mtu.hpp](port_map_mtu.hpp?ts=4)||
|Port Mapping GPT/ポートマッピング GPT|[port_map_gpt.hpp](port_map_gpt.hpp?ts=4)||
|A/D Definition/A/D 定義|[ad.hpp](ad.hpp?ts=4)||
|BUS Definition/BUS 定義|[bus.hpp](bus.hpp?ts=4)||
|D/A Definition/D/A 定義|[da.hpp](da.hpp?ts=4)||
|DPC Definition/DPC 定義|[dpc.hpp](dpc.hpp?ts=4)||
|FLASH Definition/FLASH 定義|[flash.hpp](flash.hpp?ts=4)||
|GPT Definition/GPT 定義|[gpt.hpp](gpt.hpp?ts=4)||
|LVDA Definition/LVDA 定義|[lvda.hpp](lvda.hpp?ts=4)||
|POE3 Definition/POE3 定義|[poe3.hpp](poe3.hpp?ts=4)||
|A/D Definition/A/D 定義|[s12adb.hpp](s12adb.hpp?ts=4)||
|System Definition/システム定義|[system.hpp](system.hpp?ts=4)||
|System I/O Definition/システム I/O 定義|[system_io.hpp](system_io.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LQFP 64|
|---|---|---|
|VCL|VCL(3)|
|Reset Input/リセット入力|RES#(6)|
|Mode Controle/モード制御|MD/FINED(5)|
|EMLE|EMLE(1)|
|RXD|PD5/RXD1(14)|
|TXD|PD3/TXD1(16)|
|Power/電源|VCC(10), VCC(20), VCC(42)|
|GND/接地|VSS(8), VSS(22), VSS(44)|
|Analog Power/アナログ電源|AVCC0(57)|
|Analog GND/アナログ接地|AVSS0(60)|
|Analog Refarence H/アナログ基準電源 H|VREFH0(58)|
|Analog Refarence L/アナログ基準電源 L|VREFL0(59)|
|OSC in|EXTAL(9)|
|OSC out|XTAL(7)|

- VCL: 0.1uF/25V

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
|DMAC0|DMA Controller channel 0|DMA コントローラ・チャネル０|
|DMAC1|DMA Controller channel 1|DMA コントローラ・チャネル１|
|DMAC2|DMA Controller channel 2|DMA コントローラ・チャネル２|
|DMAC3|DMA Controller channel 3|DMA コントローラ・チャネル３|
|DTC|Data Transfer Controller|データトランスファコントローラ|
|MTU0|Multi-Function Timer Pulse Unit 0|マルチファンクションタイマパルスユニット０|
|MTU1|Multi-Function Timer Pulse Unit 1|マルチファンクションタイマパルスユニット１|
|MTU2|Multi-Function Timer Pulse Unit 2|マルチファンクションタイマパルスユニット２|
|MTU3|Multi-Function Timer Pulse Unit 3|マルチファンクションタイマパルスユニット３|
|MTU4|Multi-Function Timer Pulse Unit 4|マルチファンクションタイマパルスユニット４|
|MTU5|Multi-Function Timer Pulse Unit 5|マルチファンクションタイマパルスユニット５|
|MTU6|Multi-Function Timer Pulse Unit 6|マルチファンクションタイマパルスユニット６|
|MTU7|Multi-Function Timer Pulse Unit 7|マルチファンクションタイマパルスユニット７|
|POE3|Port Output Enable 3|ポートアウトプットイネーブル３|
|GPT0|General PWM Timer 0|汎用 PWM タイマ０|
|GPT1|General PWM Timer 1|汎用 PWM タイマ１|
|GPT2|General PWM Timer 2|汎用 PWM タイマ２|
|GPT3|General PWM Timer 3|汎用 PWM タイマ３|
|GPT4|General PWM Timer 4|汎用 PWM タイマ４|
|GPT5|General PWM Timer 5|汎用 PWM タイマ５|
|GPT6|General PWM Timer 6|汎用 PWM タイマ６|
|GPT7|General PWM Timer 7|汎用 PWM タイマ７|
|CMT0|Compare Match Timer 0|コンペアマッチタイマ０|
|CMT1|Compare Match Timer 1|コンペアマッチタイマ１|
|CMT2|Compare Match Timer 2|コンペアマッチタイマ２|
|CMT3|Compare Match Timer 3|コンペアマッチタイマ３|
|WDTA|Watchdog Timer|ウォッチドッグタイマ|
|IWDT|Independent Watchdog Timer|独立ウォッチドッグタイマ|
|USB0|USB 2.0 Host/Function Module 0|USB 2.0 ホスト/ファンクションモジュール０|
|SCI0|Serial Communications Interface 0|シリアルコミュニケーションインタフェース０|
|SCI1|Serial Communications Interface 1|シリアルコミュニケーションインタフェース１|
|SCI2|Serial Communications Interface 2|シリアルコミュニケーションインタフェース２|
|SCI3|Serial Communications Interface 3|シリアルコミュニケーションインタフェース３|
|SCI12|Serial Communications Interface 12|シリアルコミュニケーションインタフェース１２|
|RIIC0|I2C-bus Interface 0|I2C バスインタフェース０|
|RIIC1|I2C-bus Interface 1|I2C バスインタフェース１|
|CAN1|CAN Module 1|CAN モジュール１|
|RSPI0|Serial Peripheral Interface 0|シリアルペリフェラルインタフェース０|
|RSPI1|Serial Peripheral Interface 1|シリアルペリフェラルインタフェース１|
|CRC|CRC Calculator|CRC 演算器|
|S12AD|12-Bit A/D Converter|12 ビット A/D コンバータ|
|S12AD1|12-Bit A/D Converter 1|12 ビット A/D コンバータ１|
|S12AD2|12-Bit A/D Converter 2|12 ビット A/D コンバータ２|
|AD|10-Bit A/D Converter|10 ビット A/D コンバータ|
|DA|10-Bit D/A Converter|10 ビット D/A コンバータ|
|DOC|Data Operation Circuit|データ演算回路|
|DPC0|Digital Power Supply Controller 0|デジタル電源制御演算器０|
|DPC1|Digital Power Supply Controller 1|デジタル電源制御演算器１|
|DPC2|Digital Power Supply Controller 2|デジタル電源制御演算器２|
|DPC3|Digital Power Supply Controller 3|デジタル電源制御演算器３|

---

## Port map order (IRQ) / ポートマップ候補 (IRQ)

- [port_map_irq.hpp](port_map_irq.hpp?ts=4)

### LFQFP64

|IRQ|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|IRQ0|P30[DS] (45)|PB5 (19)|PE5 (--)|PG0 (--)|
|IRQ1|P11[DS] (61)|P93 (30)|PE4 (--)|PG1 (--)|
|IRQ2|P00[DS] (2)|PE3[DS] (--)|PB6 (18)|PG2 (--)|
|IRQ3|PB4[DS] (21)|P34 (--)|P82 (--)|-|
|IRQ4|P01[DS] (4)|P96 [DS] (--)|P24 (46)|PB1 (25)|
|IRQ5|P70[DS] (39)|P80 (--)|PF2 (--)|-|
|IRQ6|P21[DS] (--)|PD5 (14)|PG4 (--)|-|
|IRQ7|P20[DS] (--)|P03 (--)|PE0 (--)|-|

---

## Port map order / ポートマップ候補

- [port_map.hpp](port_map.hpp?ts=4)

### LFQFP64

|Peripheral|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|SCI0 / RXD|P22 (48)|P24 (46)|PA5 (63)|PB1 (25)|
|SCI0 / TXD|P23 (47)|P30 (45)|PA4 (64)|PB2 (24)|
|SCI0 / SCK|P30 (45)|P23 (47)|PA3 (27)|PB3 (23)|
|SCI1 / RXD|P93 (30)|P96 (--)|PD5 (14)|PF2 (--)|
|SCI1 / TXD|P94 (29)|P95 (--)|PD3 (16)|PF3 (--)|
|SCI1 / SCK|P92 (31)|P92 (--)|PD4 (15)|PG6 (--)|
|SCI2 / RXD|P03 (--)|PA2 (28)|PG1 (--)|-|
|SCI2 / TXD|P02 (--)|PA1 (--)|PG0 (--)|-|
|SCI2 / SCK|P14 (--)|PA0 (--)|PG2 (--)|-|
|SCI3 / RXD|P34 (--)|PG4 (--)|-|-|
|SCI3 / TXD|P35 (--)|PG3 (--)|-|-|
|SCI3 / SCK|PG5 (--)|PG5 (--)|-|-|
|SCI12 / RXD|P80 (--)|PB6 (18)|-|-|
|SCI12 / TXD|P81 (--)|PB5 (19)|-|-|
|SCI12 / SCK|P82 (--)|PB7 (17)|-|-|
|RIIC0 / SCL|PB1 (25)|-|-|
|RIIC0 / SDA|PB2 (24)|-|-|
|RIIC1 / SCL|P25 (--)|-|-|
|RIIC1 / SDA|P26 (--)|-|-|
|CAN1 / CRX|P22 (48)|PB6 (18)|PE0 (--)|-|
|CAN1 / CTX|P23 (47)|PB5 (19)|PD7 (12)|-|
|RSPI0 / RSPCK|P24 (46)|PA4 (64)|PD0 (--)|-|
|RSPI0 / MOSI|P23 (47)|PB0 (26)|PD2 (--)|-|
|RSPI0 / MISO|P22 (48)|PA5 (63)|PD1 (--)|-|
|RSPI0 / SSL0|P30 (45)|PA3 (27)|PD6 (13)|
|RSPI0 / SSL1|P31 (43)|PA2 (28)|PD7 (12)|
|RSPI0 / SSL2|P32 (41)|PA1 (--)|PE0 (--)|
|RSPI0 / SSL3|P33 (40)|PA0 (--)|PE1 (--)|
|RSPI1 / RSPCK|P24 (46)|PA4 (64)|PD0 (--)|-|
|RSPI1 / MOSI|P23 (47)|PB0 (26)|PD2 (--)|-|
|RSPI1 / MISO|P22 (48)|PA5 (63)|PD1 (--)|-|
|RSPI1 / SSL0|P30 (45)|PA3 (27)|PD6 (13)|
|RSPI1 / SSL1|P31 (43)|PA2 (28)|PD7 (12)|
|RSPI1 / SSL2|P32 (41)|PA1 (--)|PE0 (--)|
|RSPI1 / SSL3|P33 (40)|PA0 (--)|PE1 (--)|

---

## Port map order (GPT) / ポートマップ候補 (GPT)

- [port_map_gpt.hpp](port_map_gpt.hpp?ts=4)

### LFQFP64

|GPT|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|GTIOC0A|P71 (38)|PD7 (12)|-|-|
|GTIOC0B|P74 (35)|PD6 (13)|-|-|
|GTIOC1A|P72 (37)|PD5 (14)|-|-|
|GTIOC1B|P75 (34)|PD4 (15)|-|-|
|GTIOC2A|P73 (36)|PD3 (16)|-|-|
|GTIOC2B|P76 (33)|PB6 (18)|PB7 (17)|PD2 (--)|
|GTIOC3A|P00 (2)|PD1 (--)|-|-|
|GTIOC3B|P01 (4)|PD0 (--)|-|-|
|GTIOC4A|P95 (--)|-|-|-|
|GTIOC4B|P92 (31)|-|-|-|
|GTIOC5A|P94 (29)|-|-|-|
|GTIOC5B|P91 (32)|-|-|-|
|GTIOC6A|P93 (30)|PG3 (--)|-|-|
|GTIOC6B|P90 (--)|PG4 (--)|-|-|
|GTIOC7A|PG0 (--)|-|-|-|
|GTIOC7B|PG1 (--)|-|-|-|
|GTETRG|PB4 (21)|-|-|-|
|GTETRG0|PB4 (21)|-|-|-|
|GTETRG1|P34 (--)|-|-|-|

---

## Port map order (MTU) / ポートマップ候補 (MTU)

- [port_map_mtu.hpp](port_map_mtu.hpp?ts=4)

### LFQFP64

|MTU|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|MTIOC0A|P31 (43)|PB3 (23)|-|-|
|MTIOC0B|P30 (45)|PB2 (24)|-|-|
|MTIOC0C|PB1 (25)|-|-|-|
|MTIOC0D|PB0 (26)|-|-|-|
|MTIOC1A|PA5 (63)|-|-|-|
|MTIOC1B|PA4 (64)|-|-|-|
|MTIOC2A|PA3 (27)|-|-|-|
|MTIOC2B|PA2 (28)|-|-|-|
|MTIOC3A|P33 (40)|-|-|-|
|MTIOC3B|P71 (38)|-|-|-|
|MTIOC3C|P32 (41)|-|-|-|
|MTIOC3D|P74 (35)|-|-|-|
|MTIOC4A|P72 (37)|-|-|-|
|MTIOC4B|P73 (36)|-|-|-|
|MTIOC4C|P75 (34)|-|-|-|
|MTIOC4D|P76 (33)|-|-|-|
|MTIOC5U|P24 (46)|P82 (--)|-|-|
|MTIOC5V|P23 (47)|P81 (--)|-|-|
|MTIOC5W|P22 (48)|P80 (--)|-|-|
|MTIOC6A|P33 (40)|PA1 (--)|-|-|
|MTIOC6B|P71 (38)|P95 (--)|-|-|
|MTIOC6C|P32 (41)|PA0 (--)|-|-|
|MTIOC6D|P74 (35)|P92 (31)|-|-|
|MTIOC7A|P72 (37)|P94 (29)|-|-|
|MTIOC7B|P73 (36)|P93 (30)|-|-|
|MTIOC7C|P75 (34)|P91 (32)|-|-|
|MTIOC7D|P76 (33)|P90 (--)|-|-|
|MTCLKA|P21 (--)|P22 (48)|P33 (40)|PB3 (23)|
|MTCLKB|P20 (--)|P23 (47)|P32 (41)|PB2 (24)|
|MTCLKC|P11 (61)|P24 (46)|P31 (43)|PE4 (--)|
|MTCLKD|P10 (62)|P30 (45)|PE3 (--)|-|

---

## rx_prog Flash Programming / rx_prog フラッシュプログラム

||Support/サポート|operation verification/動作検証|
|-|:-:|:-:|
|[rxprog](../rxprog)|〇|〇|

---

Translated with www.DeepL.com/Translator (free version)

---

## License

[MIT](../LICENSE)
