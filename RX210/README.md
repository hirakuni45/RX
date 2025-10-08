
## RX210 features / 特徴

- RXv1 core / RXv1 コア
- Maximum operating frequency 50MHz / 最大動作周波数 50MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 1.62V ～ 5.5V Operation / 動作
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 10 Bits D/A / １０ビットＤ／Ａ変換器

### Package/パッケージ

|R5F5210---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F5210xxxFB|LQFP|144|0.50|
|R5F5210xxxFP|LQFP|100|0.50|
|R5F5210xxxFN|LQFP|80|0.50|
|R5F5210xxxFM|LQFP|64|0.50|
|R5F5210xxxFL|LQFP|48|0.50|
|R5F5210xxxFF|LQFP|80|0.65|
|R5F5210xxxFK|LQFP|64|0.80|
|R5F5210xxxLK|TFLGA|145|0.50|
|R5F5210xxxLA|TFLGA|100|0.50|
|R5F5210xxxLJ|TFLGA|100|0.65|
|R5F5210xxxLH|TFLGA|64|0.65|
|R5F5210xxxBM|WLBGA|69|0.40|

### Ambient operating temperature/動作周囲温度

|R5F5210--X--|degree Celsius|
|---|:-:|
|R5F5210xxDxx|-40 ～ +85℃|
|R5F5210xxGxx|-40 ～ +105℃|

### Chip version/チップバージョン

|R5F5210-X---|chip version|
|---|:-:|
|R5F5210xAxxx|A|
|R5F5210xBxxx|B|
|R5F5210xCxxx|C|

### Memoey size/メモリ容量

|R5F5210X----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F5210Bxxxx|1024K|96K|8K|
|R5F5210Axxxx|768K|96K|8K|
|R5F52108xxxx|512K|64K|8K|
|R5F52107xxxx|384K|64K|8K|
|R5F52106xxxx|256K|32K|8K|
|R5F52105xxxx|128K|20K|8K|
|R5F52104xxxx|96K|16K|8K|
|R5F52103xxxx|64K|12K|8K|

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|8K|128|2/2048|2|0x??|4|

---

## RX210 Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F5210B|1024K|96K|8K|[R5F5210B.ld](R5F5210B.ld?ts=4)|3072|1024|
|R5F52108|512K|64K|8K|[R5F52108.ld](R5F52108.ld?ts=4)|3072|1024|

---

## RX210 Dedicated class / 専用クラス

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
|Port Mapping TPU/ポートマッピング TPU|[port_map_tpu.hpp](port_map_tpu.hpp?ts=4)||
|Port Mapping MTU/ポートマッピング TMR|[port_map_tmr.hpp](port_map_tmr.hpp?ts=4)||
|CMPA Definition/CMPA 定義|[cmpb.hpp](cmpa.hpp?ts=4)||
|System Definition/システム定義|[system.hpp](system.hpp?ts=4)||
|System I/O Definition/システム I/O 定義|[system_io.hpp](system_io.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 100|
|---|---|
|VCL|VCL(5)|
|Reset Input/リセット入力|RES#(10)|
|Mode Controle/モード制御|MD/FINED(7)|
|B/UB|PC7(45)|
|RXD|P30/RXD1(20)|
|TXD|P26/TXD1(22)|
|Power/電源|VCC(14), VCC(60)|
|GND/接地|VSS(12), VSS(62)|
|Analog Power/アナログ電源|AVCC0(97)|
|Analog GND/アナログ接地|AVSS0(99)|
|Analog Refarence L/アナログ基準電源Ｌ|VREFL0(94)|
|Analog Refarence H/アナログ基準電源Ｈ|VREFH0(96)|
|OSC out|XTAL(11)|
|OSC in|EXTAL(13)|
|Sub OSC out|XCOUT(9)|
|Sub OSC in|XCIN(8)|

- VCL: 0.1uF/25V

|Mode/モード|B/UB|MD|
|---|:---:|:---:|
|Serial BOOT/シリアルブート|0|0|
|User Boot/ユーザーブート|1|0|
|Single Chip/シングルチップ|-|1|

---

## peripheral / ペリフェラル

|Peripheral|Function|機能|
|---|---|---|
|CAC|Clock Frequency Accuracy Measurement Circuit|クロック周波数精度測定回路|
|DMAC0|DMA Controller channel 0|DMA コントローラ・チャネル０|
|DMAC1|DMA Controller channel 1|DMA コントローラ・チャネル１|
|DMAC2|DMA Controller channel 2|DMA コントローラ・チャネル２|
|DMAC3|DMA Controller channel 3|DMA コントローラ・チャネル３|
|DTC|Data Transfer Controller|データトランスファコントローラ|
|ELC|Event Link Controller|イベントリンクコントローラ|
|MTU0|Multi-Function Timer Pulse Unit 0|マルチファンクションタイマパルスユニット０|
|MTU1|Multi-Function Timer Pulse Unit 1|マルチファンクションタイマパルスユニット１|
|MTU2|Multi-Function Timer Pulse Unit 2|マルチファンクションタイマパルスユニット２|
|MTU3|Multi-Function Timer Pulse Unit 3|マルチファンクションタイマパルスユニット３|
|MTU4|Multi-Function Timer Pulse Unit 4|マルチファンクションタイマパルスユニット４|
|MTU5|Multi-Function Timer Pulse Unit 5|マルチファンクションタイマパルスユニット５|
|POE2|Port Output Enable 2|ポートアウトプットイネーブル２|
|TPU0|16-Bit Timer Pulse Unit 0|16 ビットタイマパルスユニット０|
|TPU1|16-Bit Timer Pulse Unit 1|16 ビットタイマパルスユニット１|
|TPU2|16-Bit Timer Pulse Unit 2|16 ビットタイマパルスユニット２|
|TPU3|16-Bit Timer Pulse Unit 3|16 ビットタイマパルスユニット３|
|TPU4|16-Bit Timer Pulse Unit 4|16 ビットタイマパルスユニット４|
|TPU5|16-Bit Timer Pulse Unit 5|16 ビットタイマパルスユニット５|
|TMR0|8-Bit Timer 0|8 ビットタイマ０|
|TMR1|8-Bit Timer 1|8 ビットタイマ１|
|TMR2|8-Bit Timer 2|8 ビットタイマ２|
|TMR3|8-Bit Timer 3|8 ビットタイマ３|
|CMT0|Compare Match Timer 0|コンペアマッチタイマ０|
|CMT1|Compare Match Timer 1|コンペアマッチタイマ１|
|CMT2|Compare Match Timer 2|コンペアマッチタイマ２|
|CMT3|Compare Match Timer 3|コンペアマッチタイマ３|
|RTC|Realtime Clock|リアルタイムクロック|
|IWDT|Independent Watchdog Timer|独立ウォッチドッグタイマ|
|SCI0|Serial Communications Interface 0|シリアルコミュニケーションインタフェース０|
|SCI1|Serial Communications Interface 1|シリアルコミュニケーションインタフェース１|
|SCI1|Serial Communications Interface 2|シリアルコミュニケーションインタフェース２|
|SCI1|Serial Communications Interface 3|シリアルコミュニケーションインタフェース３|
|SCI1|Serial Communications Interface 4|シリアルコミュニケーションインタフェース４|
|SCI5|Serial Communications Interface 5|シリアルコミュニケーションインタフェース５|
|SCI6|Serial Communications Interface 6|シリアルコミュニケーションインタフェース６|
|SCI1|Serial Communications Interface 7|シリアルコミュニケーションインタフェース７|
|SCI8|Serial Communications Interface 8|シリアルコミュニケーションインタフェース８|
|SCI9|Serial Communications Interface 9|シリアルコミュニケーションインタフェース９|
|SCI10|Serial Communications Interface 10|シリアルコミュニケーションインタフェース１０|
|SCI11|Serial Communications Interface 11|シリアルコミュニケーションインタフェース１１|
|SCI12|Serial Communications Interface 12|シリアルコミュニケーションインタフェース１２|
|RIIC0|I2C-bus Interface 0|I2C バスインタフェース０|
|RSPI0|Serial Peripheral Interface 0|シリアルペリフェラルインタフェース０|
|CRC|CRC Calculator|CRC 演算器|
|S12AD|12-Bit A/D Converter|12 ビット A/D コンバータ|
|DA|10-Bit D/A Converter|10 ビット D/A コンバータ|
|CMPA|Comparator A|コンパレータＡ|
|CMPB|Comparator B|コンパレータＢ|
|DOC|Data Operation Circuit|データ演算回路|

---

## port map order / ポートマップ候補

### LQFP64

|Peripheral|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|SCI0 / RXD|P21 (--)|P33 (--)|-|-|
|SCI0 / TXD|P20 (--)|P32 (12)|-|-|
|SCI0 / SCK|P22 (--)|P34 (--)|-|-|
|SCI1 / RXD|P15 (19)|P30 (14)|-|-|
|SCI1 / TXD|P16 (18)|P26 (16)|-|-|
|SCI1 / SCK|P17 (17)|P27 (15)|-|-|
|SCI2 / RXD|P12 (--)|P52 (--)|-|-|
|SCI2 / TXD|P13 (--)|P50 (--)|-|-|
|SCI2 / SCK|P51 (--)|P51 (--)|-|-|
|SCI3 / RXD|P16 (18)|P25 (--)|-|-|
|SCI3 / TXD|P17 (17)|P23 (--)|-|-|
|SCI3 / SCK|P55 (19)|P24 (--)|-|-|
|SCI4 / RXD|PB0 (39)|PK4 (--)|-|-|
|SCI4 / TXD|PB1 (37)|PK5 (--)|-|-|
|SCI4 / SCK|PB3 (36)|P70 (--)|-|-|
|SCI5 / RXD|PA2 (--)|PA3 (43)|PC2 (32)|PC2 (32)|
|SCI5 / TXD|PA4 (42)|PA4 (42)|PC3 (31)|PC3 (31)|
|SCI5 / SCK|PA1 (44)|PA1 (44)|PC4 (30)|PC1 (--)|
|SCI6 / RXD|P01 (--)|P33 (--)|PB0 (39)|-|
|SCI6 / TXD|P00 (--)|P32 (12)|PB1 (37)|-|
|SCI6 / SCK|P02 (--)|P34 (--)|PB3 (36)|-|
|SCI7 / RXD|P92 (--)|-|-|-|
|SCI7 / TXD|P90 (--)|-|-|-|
|SCI7 / SCK|P91 (--)|-|-|-|
|SCI8 / RXD|PC6 (28)|-|-|-|
|SCI8 / TXD|PC7 (27)|-|-|-|
|SCI8 / SCK|PC5 (29)|-|-|-|
|SCI9 / RXD|PB6 (34)|PK3 (--)|-|-|
|SCI9 / TXD|PB7 (33)|PK2 (--)|-|-|
|SCI9 / SCK|PB5 (35)|P60 (--)|-|-|
|SCI10 / RXD|P81 (--)|-|-|-|
|SCI10 / TXD|P82 (--)|-|-|-|
|SCI10 / SCK|P80 (--)|-|-|-|
|SCI11 / RXD|P76 (--)|-|-|-|
|SCI11 / TXD|P77 (--)|-|-|-|
|SCI11 / SCK|P75 (--)|-|-|-|
|SCI12 / RXD|PE2 (49)|-|-|-|
|SCI12 / TXD|PE1 (50)|-|-|-|
|SCI12 / SCK|PE0 (51)|-|-|-|
|RIIC0 / SCL|P16 (18)|P12 (--)|-|-|
|RIIC0 / SDA|P17 (17)|P13 (--)|-|-|
|RSPI0 / RSPCK|PA5 (--)|PB0 (39)|PC5 (29)|-|
|RSPI0 / MOSI|PA6 (41)|P16 (18)|PC6 (28)|-|
|RSPI0 / MISO|PA7 (--)|P17 (17)|PC7 (27)|-|
|RSPI0 / SSL0|PA4 (42)|PC4 (30)|-|-|
|RSPI0 / SSL1|PA0 (45)|PC0 (--)|-|-|
|RSPI0 / SSL2|PA1 (44)|PC1 (--)|-|-|
|RSPI0 / SSL3|PA2 (--)|PC2 (32)|-|-|

### LQFP100

|Peripheral|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|SCI0 / RXD|P21 (27)|P33 (17)|-|-|
|SCI0 / TXD|P20 (28)|P32 (18)|-|-|
|SCI0 / SCK|P22 (26)|P34 (16)|-|-|
|SCI1 / RXD|P15 (31)|P30 (20)|-|-|
|SCI1 / TXD|P16 (30)|P26 (22)|-|-|
|SCI1 / SCK|P17 (29)|P27 (21)|-|-|
|SCI2 / RXD|P12 (34)|P52 (42)|-|-|
|SCI2 / TXD|P13 (33)|P50 (44)|-|-|
|SCI2 / SCK|P51 (43)|P51 (43)|-|-|
|SCI3 / RXD|P16 (30)|P25 (23)|-|-|
|SCI3 / TXD|P17 (29)|P23 (25)|-|-|
|SCI3 / SCK|P55 (31)|P24 (24)|-|-|
|SCI4 / RXD|PB0 (61)|PK4 (--)|-|-|
|SCI4 / TXD|PB1 (59)|PK5 (--)|-|-|
|SCI4 / SCK|PB3 (57)|P70 (--)|-|-|
|SCI5 / RXD|PA2 (68)|PA3 (67)|PC2 (50)|PC2 (50)|
|SCI5 / TXD|PA4 (66)|PA4 (66)|PC3 (49)|PC3 (49)|
|SCI5 / SCK|PA1 (69)|PA1 (69)|PC4 (48)|PC1 (51)|
|SCI6 / RXD|P01 (--)|P33 (17)|PB0 (61)|-|
|SCI6 / TXD|P00 (--)|P32 (18)|PB1 (59)|-|
|SCI6 / SCK|P02 (--)|P34 (16)|PB3 (57)|-|
|SCI7 / RXD|P92 (--)|-|-|-|
|SCI7 / TXD|P90 (--)|-|-|-|
|SCI7 / SCK|P91 (--)|-|-|-|
|SCI8 / RXD|PC6 (46)|-|-|-|
|SCI8 / TXD|PC7 (45)|-|-|-|
|SCI8 / SCK|PC5 (47)|-|-|-|
|SCI9 / RXD|PB6 (54)|PK3 (--)|-|-|
|SCI9 / TXD|PB7 (53)|PK2 (--)|-|-|
|SCI9 / SCK|PB5 (55)|P60 (--)|-|-|
|SCI10 / RXD|P81 (--)|-|-|-|
|SCI10 / TXD|P82 (--)|-|-|-|
|SCI10 / SCK|P80 (--)|-|-|-|
|SCI11 / RXD|P76 (--)|-|-|-|
|SCI11 / TXD|P77 (--)|-|-|-|
|SCI11 / SCK|P75 (--)|-|-|-|
|SCI12 / RXD|PE2 (76)|-|-|-|
|SCI12 / TXD|PE1 (77)|-|-|-|
|SCI12 / SCK|PE0 (78)|-|-|-|
|RIIC0 / SCL|P16 (30)|P12 (34)|-|-|
|RIIC0 / SDA|P17 (29)|P13 (33)|-|-|
|RSPI0 / RSPCK|PA5 (65)|PB0 (61)|PC5 (47)|-|
|RSPI0 / MOSI|PA6 (64)|P16 (30)|PC6 (46)|-|
|RSPI0 / MISO|PA7 (63)|P17 (29)|PC7 (45)|-|
|RSPI0 / SSL0|PA4 (66)|PC4 (48)|-|-|
|RSPI0 / SSL1|PA0 (70)|PC0 (52)|-|-|
|RSPI0 / SSL2|PA1 (69)|PC1 (51)|-|-|
|RSPI0 / SSL3|PA2 (68)|PC2 (50)|-|-|

---

## port map order (MTU) / ポートマップ候補 (MTU)

### LFQFP64

|MTU|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|MTIOC0A|P34 (--)|PB3 (36)|-|-|-|
|MTIOC0B|P13 (--)|P15 (19)|PA1 (44)|-|-|
|MTIOC0C|P32 (12)|PB1 (37)|-|-|-|
|MTIOC0D|P33 (--)|PA3 (43)|-|-|-|
|MTIOC1A|P20 (--)|PE4 (47)|-|-|-|
|MTIOC1B|P21 (--)|PB5 (35)|-|-|-|
|MTIOC2A|P26 (16)|PB5 (35)|-|-|-|
|MTIOC2B|P27 (15)|PE5 (46)|-|-|-|
|MTIOC3A|P14 (20)|P17 (17)|PC1 (--)|PC7 (27)|PJ1 (--)|
|MTIOC3B|P17 (17)|P22 (--)|PB7 (33)|PC5 (29)|-|
|MTIOC3C|P16 (18)|P56 (--)|PC0 (--)|PC6 (28)|PJ3 (--)|
|MTIOC3D|P16 (18)|P23 (--)|P81 ()|PB6 (34)|PC4 (30)|
|MTIOC4A|P24 (--)|P82 (--)|PA0 (45)|PB3 (36)|PE2 (49)|
|MTIOC4B|P30 (14)|P54 (26)|PC2 (32)|PD1 (--)|PE3 (48)|
|MTIOC4C|P25 (--)|P83 (--)|PB1 (37)|PE1 (50)|PE5 (46)|
|MTIOC4D|P31 (13)|P55 (25)|PC3 (31)|PD2 (--)|PE4 (47)|
|MTIOC5U|PA4 (42)|PD7 (--)|-|-|-|
|MTIOC5V|PA6 (41)|PD6 (--)|-|-|-|
|MTIOC5W|PB0 (39)|PD5 (--)|-|-|-|
|MTCLKA|P14 (20)|P24 (--)|PA4 (42)|PC6 (28)|-|
|MTCLKB|P15 (19)|P25 (--)|PA6 (41)|PC7 (27)|-|
|MTCLKC|P22 (--)|PA1 (44)|PC4 (30)|-|-|
|MTCLKD|P23 (--)|PA3 (43)|PC5 (29)|-|-|

### LFQFP100

|MTU|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|MTIOC0A|P34 (16)|PB3 (57)|-|-|-|
|MTIOC0B|P13 (33)|P15 (31)|PA1 (69)|-|-|
|MTIOC0C|P32 (18)|PB1 (59)|-|-|-|
|MTIOC0D|P33 (17)|PA3 (67)|-|-|-|
|MTIOC1A|P20 (28)|PE4 (74)|-|-|-|
|MTIOC1B|P21 (27)|PB5 (55)|-|-|-|
|MTIOC2A|P26 (22)|PB5 (55)|-|-|-|
|MTIOC2B|P27 (21)|PE5 (73)|-|-|-|
|MTIOC3A|P14 (32)|P17 (29)|PC1 (51)|PC7 (45)|PJ1 (6)|
|MTIOC3B|P17 (29)|P22 (26)|PB7 (53)|PC5 (47)|-|
|MTIOC3C|P16 (30)|P56 (--)|PC0 (52)|PC6 (46)|PJ3 (4)|
|MTIOC3D|P16 (30)|P23 (25)|P81 (--)|PB6 (54)|PC4 (48)|
|MTIOC4A|P24 (24)|P82 (--)|PA0 (70)|PB3 (57)|PE2 (76)|
|MTIOC4B|P30 (20)|P54 (40)|PC2 (50)|PD1 (85)|PE3 (75)|
|MTIOC4C|P25 (23)|P83 (--)|PB1 (59)|PE1 (77)|PE5 (73)|
|MTIOC4D|P31 (19)|P55 (39)|PC3 (49)|PD2 (84)|PE4 (74)|
|MTIOC5U|PA4 (66)|PD7 (79)|-|-|-|
|MTIOC5V|PA6 (64)|PD6 (80)|-|-|-|
|MTIOC5W|PB0 (61)|PD5 (81)|-|-|-|
|MTCLKA|P14 (32)|P24 (24)|PA4 (66)|PC6 (46)|-|
|MTCLKB|P15 (31)|P25 (23)|PA6 (64)|PC7 (45)|-|
|MTCLKC|P22 (26)|PA1 (69)|PC4 (48)|-|-|
|MTCLKD|P23 (25)|PA3 (67)|PC5 (47)|-|-|

---

## port map order (IRQ) / ポートマップ候補 (IRQ)

### LFQFP64

|IRQ|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|IRQ0|P30[DS] (14)|PD0 (--)|PH1 (23)|-|-|
|IRQ1|P31[DS] (13)|PD1 (--)|PH2 (22)|-|-|
|IRQ2|P32[DS] (12)|P12 (--)|PD2 (--)|-|-|
|IRQ3|P33[DS] (--)|P13 (--)|PD3 (--)|-|-|
|IRQ4|PB1[DS] (37)|P14 (20)|P34 (--)|PD4 (--)|PF5 (--)|
|IRQ5|PA4[DS] (42)|P15 (19)|PD5 (--)|PE5 (46)|-|
|IRQ6|PA3[DS] (43)|P16 (18)|PD6 (--)|PE6 (--)|-|
|IRQ7|PE2[DS] (49)|P17 (17)|PD7 (--)|PE7 (--)|-|

### LFQFP100

|IRQ|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|IRQ0|P30[DS] (20)|PD0 (86)|PH1 (37)|-|-|
|IRQ1|P31[DS] (19)|PD1 (85)|PH2 (36)|-|-|
|IRQ2|P32[DS] (18)|P12 (34)|PD2 (84)|-|-|
|IRQ3|P33[DS] (17)|P13 (33)|PD3 (83)|-|-|
|IRQ4|PB1[DS] (59)|P14 (32)|P34 (18)|PD4 (82)|PF5 (--)|
|IRQ5|PA4[DS] (66)|P15 (31)|PD5 (81)|PE5 (73)|-|
|IRQ6|PA3[DS] (67)|P16 (30)|PD6 (80)|PE6 (72)|-|
|IRQ7|PE2[DS] (76)|P17 (29)|PD7 (79)|PE7 (71)|-|

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
