
## RX26T features / 特徴

- RXv3 core / RXv3 コア
- Maximum operating frequency 120MHz / 最大動作周波数 120MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 2.7V ～ 5.5V Operation / 動作
- CAN FD Module (CANFD) / CAN FD (CAN FD)
- Arithmetic Unit for Trigonometric Functions (TFUv2) / 三角関数演算器 (TFUv2)
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 12 Bits D/A / １２ビットＤ／Ａ変換器

### Package/パッケージ

|R5F526T---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F526TxxxFP|LFQFP|100|0.50|
|R5F526TxxxFN|LQFP|80|0.50|
|R5F526TxxxFM|LFQFP|64|0.50|
|R5F526TxxxFL|LQFP|48|0.50|
|R5F526TxxxND|HWQFN|64|0.50|
|R5F526TxxxNE|HWQFN|48|0.50|

### Ambient operating temperature/動作周囲温度

|R5F526T--X--|degree Celsius|
|---|:-:|
|R5F526TxxDxx|-40 ～ +85℃|
|R5F526TxxGxx|-40 ～ +105℃|

### CAN 2.0/CAN FD, TSIP-Lite

|R5F526T-X---|CAN|TSIP-Lite|
|---|:-:|:-:|
|R5F526TxAxxx|2.0|-|
|R5F526TxBxxx|2.0|〇|
|R5F526TxCxxx|FD|-|
|R5F526TxDxxx|FD|〇|

### Memoey size/メモリ容量

|R5F526TX----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F526TFxxxx|512K|64K|16K|
|R5F526TBxxxx|256K|64K|16K|
|R5F526TAxxxx|256K|48K|16K|
|R5F526T9xxxx|128K|64K|16K|
|R5F526T8xxxx|128K|48K|16K|

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|16K|64|4/64|4|0x??|3|

---

## RX26T Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F526T8|128K|48K|16K|[R5F526T8.ld](R5F526T8.ld?ts=4)|1536|512|
|R5F526TF|512K|64K|16K|[R5F526TF.ld](R5F526TF.ld?ts=4)|2048|1024|

---

## RX26T Dedicated class / 専用クラス

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
|Port Mapping TMR/ポートマッピング TMR|[port_map_tmr.hpp](port_map_tmr.hpp?ts=4)||
|Port Mapping GPTW/ポートマッピング GPTW|[port_map_gptw.hpp](port_map_gptw.hpp?ts=4)||
|FLASH Definition/FLASH 定義|[flash.hpp](flash.hpp?ts=4)||
|A/D Definition/A/D 定義|[s12adh.hpp](s12adh.hpp?ts=4)||
|System Definition/システム定義|[system.hpp](system.hpp?ts=4)||
|System I/O Definition/システム I/O 定義|[system_io.hpp](system_io.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 100|
|---|---|
|VCL|VCL(5)|
|Reset Input/リセット入力|RES#(10)|
|Mode Controle/モード制御|MD/FINED(6)|
|RXD|PD5/RXD1(20)|
|TXD|PD3/TXD1(22)|
|Power/電源|VCC(14), VCC(29), VCC(42), VCC(60)|
|GND/接地|VSS(3), VSS(12), VSS(31), VSS(44), VSS(62)|
|Analog Power/アナログ電源|AVCC0(93), AVCC1(92), AVCC2(72)|
|Analog GND/アナログ接地|AVSS0(94), AVSS1(95), AVSS2(73)|
|OSC in|EXTAL(13)|
|OSC out|XTAL(11)|

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
|DMAC0|DMA Controller channel 0|DMA コントローラ・チャネル０|
|DMAC1|DMA Controller channel 1|DMA コントローラ・チャネル１|
|DMAC2|DMA Controller channel 2|DMA コントローラ・チャネル２|
|DMAC3|DMA Controller channel 3|DMA コントローラ・チャネル３|
|DMAC4|DMA Controller channel 4|DMA コントローラ・チャネル４|
|DMAC5|DMA Controller channel 5|DMA コントローラ・チャネル５|
|DMAC6|DMA Controller channel 6|DMA コントローラ・チャネル６|
|DMAC7|DMA Controller channel 7|DMA コントローラ・チャネル７|
|DTC|Data Transfer Controller|データトランスファコントローラ|
|ELC|Event Link Controller|イベントリンクコントローラ|
|MTU0|Multi-Function Timer Pulse Unit 0|マルチファンクションタイマパルスユニット０|
|MTU1|Multi-Function Timer Pulse Unit 1|マルチファンクションタイマパルスユニット１|
|MTU2|Multi-Function Timer Pulse Unit 2|マルチファンクションタイマパルスユニット２|
|MTU3|Multi-Function Timer Pulse Unit 3|マルチファンクションタイマパルスユニット３|
|MTU4|Multi-Function Timer Pulse Unit 4|マルチファンクションタイマパルスユニット４|
|MTU5|Multi-Function Timer Pulse Unit 5|マルチファンクションタイマパルスユニット５|
|MTU6|Multi-Function Timer Pulse Unit 6|マルチファンクションタイマパルスユニット６|
|MTU7|Multi-Function Timer Pulse Unit 7|マルチファンクションタイマパルスユニット７|
|MTU9|Multi-Function Timer Pulse Unit 9|マルチファンクションタイマパルスユニット９|
|POE3D|Port Output Enable 3D|ポートアウトプットイネーブル３Ｄ|
|GPTW0|General PWM Timer 0|汎用 PWM タイマ０|
|GPTW1|General PWM Timer 1|汎用 PWM タイマ１|
|GPTW2|General PWM Timer 2|汎用 PWM タイマ２|
|GPTW3|General PWM Timer 3|汎用 PWM タイマ３|
|GPTW4|General PWM Timer 4|汎用 PWM タイマ４|
|GPTW5|General PWM Timer 5|汎用 PWM タイマ５|
|GPTW6|General PWM Timer 6|汎用 PWM タイマ６|
|GPTW7|General PWM Timer 7|汎用 PWM タイマ７|
|GPTW8|General PWM Timer 8|汎用 PWM タイマ８|
|HRPWM|High Resolution PWM Waveform Generation Circuit|高分解能 PWM 波形生成回路|
|POEG|GPTW Port Output Enable|GPTW 用ポートアウトプットイネーブル|
|TMR0|8-Bit Timer 0|8 ビットタイマ０|
|TMR1|8-Bit Timer 1|8 ビットタイマ１|
|TMR2|8-Bit Timer 2|8 ビットタイマ２|
|TMR3|8-Bit Timer 3|8 ビットタイマ３|
|TMR4|8-Bit Timer 4|8 ビットタイマ４|
|TMR5|8-Bit Timer 5|8 ビットタイマ５|
|TMR6|8-Bit Timer 6|8 ビットタイマ６|
|TMR7|8-Bit Timer 7|8 ビットタイマ７|
|CMT0|Compare Match Timer 0|コンペアマッチタイマ０|
|CMT1|Compare Match Timer 1|コンペアマッチタイマ１|
|CMT2|Compare Match Timer 2|コンペアマッチタイマ２|
|CMT3|Compare Match Timer 3|コンペアマッチタイマ３|
|CMTW0|Compare Match Timer W0|コンペアマッチタイマＷ０|
|CMTW1|Compare Match Timer W1|コンペアマッチタイマＷ１|
|WDTA|Watchdog Timer|ウォッチドッグタイマ|
|IWDT|Independent Watchdog Timer|独立ウォッチドッグタイマ|
|SCI1|Serial Communications Interface 1|シリアルコミュニケーションインタフェース１|
|SCI5|Serial Communications Interface 5|シリアルコミュニケーションインタフェース５|
|SCI6|Serial Communications Interface 6|シリアルコミュニケーションインタフェース６|
|SCI12|Serial Communications Interface 12|シリアルコミュニケーションインタフェース１２|
|RSCI8|(R)Serial Communications Interface 8|Ｒシリアルコミュニケーションインタフェース８|
|RSCI9|(R)Serial Communications Interface 9|Ｒシリアルコミュニケーションインタフェース９|
|RIIC0|I2C-bus Interface 0|I2C バスインタフェース０|
|RI3C0|I3C-bus Interface 0|I3C バスインタフェース０|
|CANFD0|CANFD Module 0|CANFD モジュール０|
|RSPI0|Serial Peripheral Interface 0|シリアルペリフェラルインタフェース０|
|RSPIA0|Serial Peripheral Interface A0|シリアルペリフェラルインタフェースＡ０|
|CRC|CRC Calculator|CRC 演算器|
|TSIP_L|Trusted Secure IP (TSIP-Lite)|Trusted Secure IP (TSIP-Lite)|
|S12AD|12-Bit A/D Converter|12 ビット A/D コンバータ|
|S12AD1|12-Bit A/D Converter 1|12 ビット A/D コンバータ１|
|S12AD2|12-Bit A/D Converter 2|12 ビット A/D コンバータ２|
|R12DA|12-Bit D/A Converter|12 ビット D/A コンバータ|
|TEMPS|Temperature Sensor|温度センサ|
|CMPC0|Comparator C0|コンパレーターＣ０|
|CMPC1|Comparator C1|コンパレーターＣ１|
|CMPC2|Comparator C2|コンパレーターＣ２|
|CMPC3|Comparator C3|コンパレーターＣ３|
|CMPC4|Comparator C4|コンパレーターＣ４|
|CMPC5|Comparator C5|コンパレーターＣ５|
|DOC|Data Operation Circuit|データ演算回路|

---

## Port map order (IRQ) / ポートマップ候補 (IRQ)

- [port_map_irq.hpp](port_map_irq.hpp?ts=4)

### LFQGFP100

|IRQ|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|IRQ0|P10 DS (100)|P52 (81)|PE2 (15)|PE5 (1)|-|
|IRQ1|P11 DS (99)|P53 (80)|P95 (45)|PA5 (36)|PE4 (8)|
|IRQ2|P00 (4)|P54 (79)|PB6 (27)|PD4 (21)|PE3 (9)|
|IRQ3|P55 (78)|P82 (96)|PB4 (30)|-|-|
|IRQ4|P01 (7)|P24 (65)|P60 (77)|P96 (43)|PB1 (34)|
|IRQ5|P61 (76)|P70 (57)|P80 (98)|PD6 (19)|PN7 (2)|
|IRQ6|P21 (68)|P31 (61)|P62 (75)|PD5 (20)|-|
|IRQ7|P20 (69)|P30 (63)|P63 (74)|PE0 (17)|-|
|IRQ8|P64 (71)|PB0 (35)|PD7 (18)|-|-|
|IRQ9|P65 (70)|PB3 (32)|-|-|-|
|IRQ10|P22 (67)|-|-|-|-|
|IRQ11|P23 (66)|-|-|-|-|
|IRQ12|P32 (59)|-|-|-|-|
|IRQ13|P33 (58)|-|-|-|-|
|IRQ14|P93 (47)|PA1 (40)|-|-|-|
|IRQ15|P27 (64)|PE1 (16)|-|-|-|

---

## Port map order / ポートマップ候補

- [port_map.hpp](port_map.hpp?ts=4)

### LFQFP100

|Peripheral|FIRST|SECOND|THIRD|FOURTH|FIFTH|SIXTH|SEVENTH|EIGHTH|NINTH|TENTH|
|---|---|---|---|---|---|---|---|---|---|---|
|SCI0 / RXD|PD5 (20)|-|-|-|-|-|-|-|-|-|
|SCI0 / TXD|PD3 (22)|-|-|-|-|-|-|-|-|-|
|SCI0 / SCK|PD4 (21)|-|-|-|-|-|-|-|-|-|
|SCI5 / RXD|P37 (11)|P91 (49)|PB6 (27)|PE0 (17)|-|-|-|-|-|-|
|SCI5 / TXD|P36 (13)|P90 (50)|PB5 (28)|PD7 (18)|-|-|-|-|-|-|
|SCI5 / SCK|P70 (57)|P70 (57)|PB7 (26)|PD2 (23)|-|-|-|-|-|-|
|SCI6 / RXD|P80 (98)|P95 (45)|PB1 (34)|-|-|-|-|-|-|-|
|SCI6 / TXD|P81 (97)|PB0 (35)|PB2 (33)|-|-|-|-|-|-|-|
|SCI6 / SCK|P82 (96)|PA4 (37)|PB3 (32)|-|-|-|-|-|-|-|
|RSCI8 / RXD|P20 (69)|-|-|-|-|-|-|-|-|-|
|RSCI8 / TXD|P21 (68)|-|-|-|-|-|-|-|-|-|
|RSCI8 / SCK|P11 (99)|-|-|-|-|-|-|-|-|-|
|RSCI8 / DE|P20 (69)|P24 (65)|P30 (63)|P96 (43)|-|-|-|-|-|-|
|RSCI9 / RXD|P00 (4)|-|-|-|-|-|-|-|-|-|
|RSCI9 / TXD|P01 (7)|-|-|-|-|-|-|-|-|-|
|RSCI9 / SCK|P11 (99)|-|-|-|-|-|-|-|-|-|
|RSCI9 / DE|P70 (57)|PB3 (32)|PE3 (9)|-|-|-|-|-|-|-|
|RSCI11 / RXD|P93 (47)|-|-|-|-|-|-|-|-|-|
|RSCI11 / TXD|P92 (48)|-|-|-|-|-|-|-|-|-|
|RSCI11 / SCK|PB4 (30)|-|-|-|-|-|-|-|-|-|
|RSCI11 / DE|PB0 (35)|PD6 (19)|-|-|-|-|-|-|-|-|
|SCI12 / RXD|P00 (4)|-|-|-|-|-|-|-|-|-|
|SCI12 / TXD|P01 (7)|-|-|-|-|-|-|-|-|-|
|SCI12 / SCK|P82 (96)|-|-|-|-|-|-|-|-|-|
|RIIC0 / SCL|PB1 (34)|-|-|-|-|-|-|-|-|-|
|RIIC0 / SDA|PB2 (33)|-|-|-|-|-|-|-|-|-|
|RI3C0 / SCL|PB1 (34)|-|-|-|-|-|-|-|-|-|
|RI3C0 / SDA|PB2 (33)|-|-|-|-|-|-|-|-|-|
|CANFD0 / CRX|P22 (67)|P93 (47)|PA1 (40)|PB4 (30)|PB6 (27)|PE0 (17)|-|-|-|-|
|CANFD0 / CTX|P23 (66)|P92 (48)|PA0 (41)|PB3 (32)|PB5 (28)|PD7 (18)|-|-|-|-|
|RSPI0 / RSPCK|P20 (69)|P24 (65)|P27 (64)|PA4 (37)|PB3 (32)|PD0 (25)|-|-|-|-|
|RSPI0 / MOSI|P21 (68)|P23 (66)|P23 (66)|PB0 (35)|PB0 (35)|PD2 (23)|-|-|-|-|
|RSPI0 / MISO|P22 (67)|P22 (67)|P22 (67)|PA5 (36)|PA5 (36)|PD1 (24)|-|-|-|-|
|RSPI0 / SSL0|P30 (63)|P70 (57)|P94 (46)|PA3 (38)|PD6 (19)|-|-|-|-|-|
|RSPI0 / SSL1|P31 (61)|PA2 (39)|PD7 (18)|-|-|-|-|-|-|-|
|RSPI0 / SSL2|P32 (59)|P93 (47)|PA1 (40)|PE0 (17)|-|-|-|-|-|-|
|RSPI0 / SSL3|P33 (58)|P92 (48)|PA0 (41)|PE1 (16)|-|-|-|-|-|-|
|RSPIA0 / RSPCK|P20 (69)|P24 (65)|P27 (64)|P70 (57)|P91 (49)|P96 (43)|PA4 (37)|PB5 (28)|PD0 (25)|PD0 (25)|
|RSPIA0 / MOSI|P21 (68)|P23 (66)|P23 (66)|P72 (55)|P93 (47)|P93 (47)|PB0 (35)|PB0 (35)|PD2 (23)|PD3 (22)|
|RSPIA0 / MISO|P22 (67)|P22 (67)|P22 (67)|P71 (56)|P92 (48)|P95 (45)|PA5 (36)|PB6 (27)|PD1 (24)|PD1 (24)|
|RSPIA0 / SSL0|P30 (63)|P73 (54)|P94 (46)|PA3 (38)|PD5 (20)|PD6 (19)|-|-|-|-|
|RSPIA0 / SSL1|P31 (61)|P74 (53)|P90 (50)|PA2 (39)|PB4 (30)|PD7 (18)|-|-|-|-|
|RSPIA0 / SSL2|P32 (59)|P75 (52)|P93 (47)|P95 (45)|PA1 (40)|PD4 (21)|PE0 (17)|-|-|-|
|RSPIA0 / SSL3|P33 (58)|P76 (51)|P92 (48)|P96 (43)|PA0 (41)|PB7 (26)|PE1 (16)|-|-|-|

---

## Port map order (GPTW) / ポートマップ候補 (GPTW)

- [port_map_gptw.hpp](port_map_gptw.hpp?ts=4)

### LFQGFP100

|GPTW|FIRST|SECOND|THIRD|FOURTH|FIFTH|SIXTH|SEVENTH|EIGHTH|NINTH|
|---|---|---|---|---|---|---|---|---|---|
|GTIOC0A|P71 (56)|PD2 (23)|PD7 (18)|-|-|-|-|-|-|
|GTIOC0B|P74 (53)|PD1 (24)|PD6 (19)|-|-|-|-|-|-|
|GTIOC1A|P72 (55)|PD0 (25)|PD5 (20)|-|-|-|-|-|-|
|GTIOC1B|P75 (52)|PB7 (26)|PD4 (21)|-|-|-|-|-|-|
|GTIOC2A|P73 (54)|PB6 (27)|PD3 (22)|-|-|-|-|-|-|
|GTIOC2B|P76 (51)|PB5 (28)|PD2 (23)|-|-|-|-|-|-|
|GTIOC3A|P10 (100)|P32 (59)|PB6 (27)|PD1 (24)|PD7 (18)|PE5 (1)|-|-|-|
|GTIOC3B|P11 (99)|P33 (58)|PB5 (28)|PD0 (25)|PD6 (19)|-|-|-|-|
|GTIOC4A|P71 (56)|P95 (45)|-|-|-|-|-|-|-|
|GTIOC4B|P74 (53)|P92 (48)|-|-|-|-|-|-|-|
|GTIOC5A|P72 (55)|P94 (46)|-|-|-|-|-|-|-|
|GTIOC5B|P75 (52)|P91 (49)|-|-|-|-|-|-|-|
|GTIOC6A|P73 (54)|P93 (47)|-|-|-|-|-|-|-|
|GTIOC6B|P76 (51)|P90 (50)|-|-|-|-|-|-|-|
|GTIOC7A|P32 (59)|P95 (45)|PB2 (33)|PD5 (20)|-|-|-|-|-|
|GTIOC7B|P33 (58)|P92 (48)|PB1 (34)|PD3 (22)|-|-|-|-|-|
|GTETRGA|P01 (7)|P11 (99)|P70 (57)|P96 (43)|PB4 (30)|PD5 (20)|PE3 (9)|PE4 (8)|-|
|GTETRGB|P01 (7)|P10 (100)|P70 (57)|P96 (43)|PB4 (30)|PD4 (21)|PE3 (9)|PE4 (8)|PE5 (1)|
|GTETRGC|P01 (7)|P11 (99)|P70 (57)|P96 (43)|PB4 (30)|PD3 (22)|PE3 (9)|PE4 (8)|-|
|GTETRGD|P01 (7)|P10 (100)|P70 (57)|P96 (43)|PB4 (30)|PE3 (9)|PE4 (8)|PE5 (1)|-|
|GTADSM0|P94 (46)|PA3 (38)|PB2 (33)|-|-|-|-|-|-|
|GTADSM1|PA2 (39)|PB1 (34)|-|-|-|-|-|-|-|
|GTIU|P00 (4)|P21 (68)|P31 (61)|PB3 (32)|PD7 (18)|-|-|-|-|
|GTIV|P10 (100)|P22 (67)|P30 (63)|PB2 (33)|PE0 (17)|-|-|-|-|
|GTIW|P01 (7)|P20 (69)|PB1 (34)|PD6 (19)|-|-|-|-|-|
|GTOULO|P74 (53)|P92 (48)|-|-|-|-|-|-|-|
|GTOUUP|P71 (56)|P95 (45)|-|-|-|-|-|-|-|
|GTOVLO|P75 (52)|P91 (49)|-|-|-|-|-|-|-|
|GTOVUP|P72 (55)|P94 (46)|-|-|-|-|-|-|-|
|GTOWLO|P76 (51)|P90 (50)|-|-|-|-|-|-|-|
|GTOWUP|P73 (54)|P93 (47)|-|-|-|-|-|-|-|

---

## Port map order (MTU) / ポートマップ候補 (MTU)

- [port_map_mtu.hpp](port_map_mtu.hpp?ts=4)

### LFQGFP100

|MTU|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|MTIOC0A #|P31 (61)|P70 (57)|PB3 (32)|-|
|MTIOC0B #|P30 (63)|PB2 (33)|-|-|
|MTIOC0C #|P27 (64)|PB1 (34)|-|-|
|MTIOC0D #|PB0 (35)|-|-|-|
|MTIOC1A #|P27 (64)|P95 (45)|PA5 (36)|-|
|MTIOC1B #|PA4 (37)|-|-|-|
|MTIOC2A #|P94 (46)|PA3 (38)|-|-|
|MTIOC2B #|PA2 (39)|-|-|-|
|MTIOC3A #|P11 (99)|P33 (58)|-|-|
|MTIOC3B #|P71 (56)|-|-|-|
|MTIOC3C #|P32 (59)|-|-|-|
|MTIOC3D #|P74 (53)|-|-|-|
|MTIOC4A #|P72 (55)|-|-|-|
|MTIOC4B #|P73 (54)|-|-|-|
|MTIOC4C #|P75 (52)|-|-|-|
|MTIOC4D #|P76 (51)|-|-|-|
|MTIC5U #|P24 (65)|P82 (96)|-|-|
|MTIC5V #|P23 (66)|P81 (97)|-|-|
|MTIC5W #|P22 (67)|P80 (98)|-|-|
|MTIOC6A #|P93 (47)|PA1 (40)|-|-|
|MTIOC6B #|P95 (45)|-|-|-|
|MTIOC6C #|P92 (48)|PA0 (41)|-|-|
|MTIOC6D #|P92 (48)|-|-|-|
|MTIOC7A #|P94 (46)|-|-|-|
|MTIOC7B #|P93 (47)|-|-|-|
|MTIOC7C #|P91 (49)|-|-|-|
|MTIOC7D #|P90 (50)|-|-|-|
|MTIOC9A #|P00 (4)|P21 (68)|PD7 (18)|-|
|MTIOC9B #|P22 ~# (67)|P10 (100)|PE0 (17)|-|
|MTIOC9C #|P01 (7)|P20 (69)|PD6 (19)|-|
|MTIOC9D #|P11 ~# (99)|PE1 (16)|PE5 (1)|PN7 (2)|
|MTCLKA #|P21 (67)|P33 (58)|-|-|
|MTCLKB #|P20 (69)|P32 (59)|-|-|
|MTCLKC #|P11 (99)|P31 (61)|P70 (57)|PE4 (8)|
|MTCLKD #|P10 (100)|P22 (67)|P30 (63)|PE3 (9)|
|ADSM0|PB2 (33)|-|-|-|
|ADSM1|PB1 (34)|-|-|-|

---

## Port map order (TMR) / ポートマップ候補 (TMR)

- [port_map_tmr.hpp](port_map_tmr.hpp?ts=4)

### LFQGFP100

|TMR|FIRST|SECOND|THIRD|FOURTH|FIFTH|SIXTH|
|---|---|---|---|---|---|---|
|TMO0|P33 (58)|PB0 (35)|PD3 (22)|-|-|-|
|TMCI0|PB1 (34)|PD4 (21)|-|-|-|-|
|TMRI0|PB2 (33)|PD5 (20)|-|-|-|-|
|TMO1|PD6 (19)|-|-|-|-|-|
|TMCI1|PD2 (23)|PE0 (17)|-|-|-|-|
|TMRI1|PD7 (18)|-|-|-|-|-|
|TMO2|P20 (69)|P23 (66)|P27 (64)|P92 (48)|PA0 (41)|PD1 (24)|
|TMCI2|P24 (65)|-|-|-|-|-|
|TMRI2|P22 (67)|-|-|-|-|-|
|TMO3|P11 (99)|-|-|-|-|-|
|TMCI3|P95 (45)|PA5 (36)|-|-|-|-|
|TMRI3|P10 (100)|-|-|-|-|-|
|TMO4|P22 (67)|P82 (96)|P93 (47)|PA1 (40)|PD2 (23)|-|
|TMCI4|P21 (68)|P81 (97)|-|-|-|-|
|TMRI4|P20 (69)|P80 (98)|-|-|-|-|
|TMO5|PE1 (16)|-|-|-|-|-|
|TMCI5|PE0 (17)|-|-|-|-|-|
|TMRI5|PD7 (18)|-|-|-|-|-|
|TMO6|P21 (68)|P24 (65)|P27 (64)|P32 (59)|PD0 (25)|-|
|TMCI6|P30 (63)|PD4 (21)|-|-|-|-|
|TMRI6|P31 (61)|P70 (57)|PD5 (20)|-|-|-|
|TMO7|PA2 (39)|-|-|-|-|-|
|TMCI7|PA4 (37)|-|-|-|-|-|
|TMRI7|P94 (46)|PA3 (38)|-|-|-|-|

---

## 12 Bits A/D Converter input (S12AD) / 12 ビット A/D コンバーター入力 (S12AD)

- [s12adh.hpp](s12adh.hpp?ts=4)

### LFQFP100

|S12AD/ANALOG|Port|
|---|---|
|AN000|P40 (91)|
|AN001|P41 (90)|
|AN002|P42 (89)|
|AN003|P43 (88)|
|AN004|P44 (87)|
|AN005|P45 (86)|
|AN006|P46 (85)|

|S12AD1/ANALOG|Port|
|---|---|
|AN100|P44 (87)|
|AN101|P45 (86)|
|AN102|P46 (85)|
|AN103|P47 (84)|

|S12AD2/ANALOG|Port|
|---|---|
|AN200|P52 (81)|
|AN201|P53 (80)|
|AN202|P54 (79)|
|AN203|P55 (78)|
|AN204|P50 (83)|
|AN205|P51 (82)|
|AN206|P60 (77)|
|AN207|P61 (76)|
|AN208|P62 (75)|
|AN209|P63 (74)|
|AN210|P64 (71)|
|AN211|P65 (70)|
|AN216|P20 (69)|
|AN217|P21 (68)|

---

## 12 Bits D/A Converter output (R12DA) / 12 ビット D/A コンバーター出力 (R12DA)

- [r12da.hpp](../RX600/r12da.hpp?ts=4)

### LFQFP100

|R12DA/ANALOG|Port|
|---|---|
|DA0|P64 (71)|
|DA1|P65 (70)|

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
