
## RX140 features / 特徴

- RXv2 core / RXv2 コア
- Maximum operating frequency 48MHz / 最大動作周波数 48MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 1.8V ～ 5.5V Operation / 動作
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 8 Bits D/A / ８ビットＤ／Ａ変換器

### Package/パッケージ

|R5F5140---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F5140xxxFN|LFQFP|80|0.50|
|R5F5140xxxFM|LFQFP|64|0.50|
|R5F5140xxxFK|LQFP|64|0.80|
|R5F5140xxxFL|LFQFP|48|0.50|
|R5F5140xxxNE|HWQFN|48|0.50|
|R5F5140xxxFJ|LFQFP|32|0.80|
|R5F5140xxxNH|HWQFN|32|0.50|

### Ambient operating temperature/動作周囲温度

|R5F5140--X--|degree Celsius|
|---|:-:|
|R5F5140xxDxx|-40 ～ +85℃|
|R5F5140xxGxx|-40 ～ +105℃|

### Crypt/暗号

|R5F5140-X---|Crypt|
|---|:-:|
|R5F5140xAxxx|-|
|R5F5140xBxxx|〇|

### Memoey size/メモリ容量

|R5F5140X----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F51406xxxx|256K|64K|8K|
|R5F51405xxxx|128K|32K|8K|
|R5F51403xxxx|64K|16K|4K|

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|4K/8K|256|1/256|1|0xFF|4|

---

## RX140 Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F51406|256K|64K|8K|[R5F51406.ld](R5F51406.ld?ts=4)|3072|1024|
|R5F51405|128K|32K|8K|[R5F51405.ld](R5F51405.ld?ts=4)|1536|512|
|R5F51403|64K|16K|4K|[R5F51403.ld](R5F51403.ld?ts=4)|768|256|

---

## RX140 Dedicated class / 専用クラス

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
|Port Mapping MTU/ポートマッピング TMR|[port_map_tmr.hpp](port_map_tmr.hpp?ts=4)||
|A/D Definition/A/D 定義|[RX231/s12ade.hpp](../RX231/s12ade.hpp?ts=4)||
|D/A Definition/D/A 定義|[da.hpp](da.hpp?ts=4)||
|BUS Definition/BUS 定義|[bus.hpp](bus.hpp?ts=4)||
|ELC Definition/ELC 定義|[elc.hpp](elc.hpp?ts=4)||
|RTC Definition/RTC 定義|[rtc.hpp](rtc.hpp?ts=4)||
|FLASH Definition/FLASH 定義|[flash.hpp](flash.hpp?ts=4)||
|FLASH I/O Definition/FLASH I/O 定義|[RX24T/flash_io.hpp](../RX24T/flash.hpp?ts=4)||
|System Definition/システム定義|[system.hpp](system.hpp?ts=4)||
|System I/O Definition/システム I/O 定義|[system_io.hpp](system_io.hpp?ts=4)||
|A/D I/O Definition/A/D I/O 定義|[RX24T/adc_io.hpp](../RX24T/adc_io.hpp?ts=4)||
|D/A out Definition/D/A out 定義|[RX600/dac_out.hpp](../RX600/adc_io.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 64|LFQFP 80|
|---|---|---|
|VCL|VCL(2)|VCL(4)|
|Reset Input/リセット入力|RES#(6)|RES#(9)|
|Mode Controle/モード制御|MD/FINED(3)|MD/FINED(6)|
|RXD|P30/RXD1(14)|P30/RXD1(18)|
|TXD|P26/TXD1(16)|P26/TXD1(20)|
|Power/電源|VCC(10), VCC(38)|VCC(13), VCC(48)|
|GND/接地|VSS(8), VSS(40)|VSS(11), VSS(50)|
|Analog Power/アナログ電源|AVCC0(62)|AVCC0(77)|
|Analog GND/アナログ接地|AVSS0(64)|AVSS0(79)|
|Analog Refarence L/アナログ基準電源Ｌ|VREFL0(59)|VREFL0(74)|
|Analog Refarence H/アナログ基準電源Ｈ|VREFH0(61)|VREFH0(76)|
|OSC out|XTAL(7)|XTAL(10)|
|OSC in|EXTAL(9)|EXTAL(12)|
|Sub OSC out|XCOUT(5)|XCOUT(8)|
|Sub OSC in|XCIN(4)|XCIN(7)|

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
|RTC|Realtime Clock|リアルタイムクロック|
|LPT|Low Power Timer|ローパワータイマ|
|IWDT|Independent Watchdog Timer|独立ウォッチドッグタイマ|
|SCI1|Serial Communications Interface 1|シリアルコミュニケーションインタフェース１|
|SCI5|Serial Communications Interface 5|シリアルコミュニケーションインタフェース５|
|SCI6|Serial Communications Interface 6|シリアルコミュニケーションインタフェース６|
|SCI8|Serial Communications Interface 8|シリアルコミュニケーションインタフェース８|
|SCI9|Serial Communications Interface 9|シリアルコミュニケーションインタフェース９|
|SCI11|Serial Communications Interface 11|シリアルコミュニケーションインタフェース１１|
|SCI12|Serial Communications Interface 12|シリアルコミュニケーションインタフェース１２|
|RIIC0|I2C-bus Interface 0|I2C バスインタフェース０|
|RSCAN|RSCAN Module|RSCAN インタフェース|
|RSPI0|Serial Peripheral Interface 0|シリアルペリフェラルインタフェース０|
|CRC|CRC Calculator|CRC 演算器|
|CTSU|Capacitive Touch Sensing Unit|静電容量式タッチセンサ|
|S12AD|12-Bit A/D Converter|12 ビット A/D コンバータ|
|DA|8-Bit D/A Converter|8 ビット D/A コンバータ|
|CMPB|Comparator B|コンパレータＢ|
|DOC|Data Operation Circuit|データ演算回路|

---

## Port map order (IRQ) / ポートマップ候補 (IRQ)

- [port_map_irq.hpp](port_map_irq.hpp?ts=4)

### LFQFP48

|IRQ|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|IRQ0|P30 (10)|PD0 (--)|PH1 (19)|-|
|IRQ1|P31 (9)|PD1 (--)|PH2 (18)|-|
|IRQ2|P12 (--)|P32 (--)|P36 (6)|PD2 (--)|
|IRQ3|P13 (--)|-|-|-|
|IRQ4|P14 (16)|P34 (--)|P37 (4)|PB1 (27)|
|IRQ5|P15 (15)|PA4 (32)|PE5 (--)|-|
|IRQ6|P16 (14)|PA3 (33)|-|-|
|IRQ7|P17 (13)|PE2 (37)|-|-|

### LFQFP64

|IRQ|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|IRQ0|P30 (14)|PD0 (--)|PH1 (23)|-|
|IRQ1|P31 (13)|PD1 (--)|PH2 (22)|-|
|IRQ2|P12 (--)|P32 (12)|P36 (9)|PD2 (--)|
|IRQ3|P13 (--)|-|-|-|
|IRQ4|P14 (20)|P34 (--)|P37 (7)|PB1 (37)|
|IRQ5|P15 (19)|PA4 (42)|PE5 (46)|-|
|IRQ6|P16 (18)|PA3 (43)|-|-|
|IRQ7|P17 (17)|PE2 (49)|-|-|

### LFQFP80

|IRQ|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|IRQ0|P30 (18)|PD0 (66)|PH1 (31)|-|
|IRQ1|P31 (17)|PD1 (65)|PH2 (30)|-|
|IRQ2|P12 (28)|P32 (16)|P36 (12)|PD2 (64)|
|IRQ3|P13 (27)|-|-|-|
|IRQ4|P14 (26)|P34 (15)|P37 (10)|PB1 (47)|
|IRQ5|P15 (25)|PA4 (53)|PE5 (58)|-|
|IRQ6|P16 (24)|PA3 (54)|-|-|
|IRQ7|P17 (23)|PE2 (61)|-|-|

---

## Port map order / ポートマップ候補

- [port_map.hpp](port_map.hpp?ts=4)

### LFQFP48

|Peripheral|FIRST|SECOND|THIRD|
|---|---|---|---|
|SCI1 / RXD|P15 (15)|P30 (10)|-|
|SCI1 / TXD|P16 (14)|P26 (12)|-|
|SCI1 / SCK|P17 (13)|P27 (11)|-|
|SCI5 / RXD|PA2 (--)|PA3 (33)|PC2 (26)|
|SCI5 / TXD|PA4 (32)|PA4 (32)|PC3 (25)|
|SCI5 / SCK|PA1 (34)|PA1 (34)|PC4 (24)|
|SCI6 / RXD|PB0 (29)|PD1 (--)|-|
|SCI6 / TXD|PB1 (27)|PD0 (--)|-|
|SCI6 / SCK|PB3 (26)|PD2 (--)|-|
|SCI8 / RXD|PC6 (22)|-|-|
|SCI8 / TXD|PC7 (21)|-|-|
|SCI8 / SCK|PC5 (23)|-|-|
|SCI9 / RXD|PB6 (--)|-|-|
|SCI9 / TXD|PB7 (--)|-|-|
|SCI9 / SCK|PB5 (25)|-|-|
|SCI12 / RXD|PE2 (37)|-|-|
|SCI12 / TXD|PE1 (38)|-|-|
|SCI12 / SCK|PE0 (--)|-|-|
|RIIC0 / SCL|P16 (14)|P12 (--)|-|
|RIIC0 / SDA|P17 (13)|P13 (--)|-|
|RSCAN / CRX|P15 (15)|P55 (--)|-|
|RSCAN / CTX|P14 (16)|P54 (--)|-|
|RSPI0 / RSPCK|PA5 (--)|PB0 (29)|PC5 (23)|
|RSPI0 / MOSI|PA6 (31)|P16 (14)|PC6 (22)|
|RSPI0 / MISO|PA7 (21)|P17 (13)|PC7 (21)|
|RSPI0 / SSL0|PA4 (32)|PC4 (24)|-|
|RSPI0 / SSL1|PA0 (--)|-|-|
|RSPI0 / SSL2|PA1 (34)|-|-|
|RSPI0 / SSL3|PA2 (--)|PC2 (26)|-|

### LFQFP64

|Peripheral|FIRST|SECOND|THIRD|
|---|---|---|---|
|SCI1 / RXD|P15 (19)|P30 (14)|-|
|SCI1 / TXD|P16 (18)|P26 (16)|-|
|SCI1 / SCK|P17 (17)|P27 (15)|-|
|SCI5 / RXD|PA2 (--)|PA3 (43)|PC2 (32)|
|SCI5 / TXD|PA4 (42)|PA4 (42)|PC3 (31)|
|SCI5 / SCK|PA1 (44)|PA1 (44)|PC4 (30)|
|SCI6 / RXD|PB0 (39)|PD1 (--)|-|
|SCI6 / TXD|PB1 (37)|PD0 (--)|-|
|SCI6 / SCK|PB3 (36)|PD2 (--)|-|
|SCI8 / RXD|PC6 (28)|-|-|
|SCI8 / TXD|PC7 (27)|-|-|
|SCI8 / SCK|PC5 (29)|-|-|
|SCI9 / RXD|PB6 (34)|-|-|
|SCI9 / TXD|PB7 (33)|-|-|
|SCI9 / SCK|PB5 (35)|-|-|
|SCI12 / RXD|PE2 (49)|-|-|
|SCI12 / TXD|PE1 (50)|-|-|
|SCI12 / SCK|PE0 (51)|-|-|
|RIIC0 / SCL|P16 (18)|P12 (--)|-|
|RIIC0 / SDA|P17 (17)|P13 (--)|-|
|RSCAN / CRX|P15 (19)|P55 (--)|-|
|RSCAN / CTX|P14 (20)|P54 (--)|-|
|RSPI0 / RSPCK|PA5 (--)|PB0 (39)|PC5 (29)|
|RSPI0 / MOSI|PA6 (41)|P16 (18)|PC6 (28)|
|RSPI0 / MISO|PA7 (--)|P17 (17)|PC7 (27)|
|RSPI0 / SSL0|PA4 (42)|PC4 (30)|-|
|RSPI0 / SSL1|PA0 (45)|-|-|
|RSPI0 / SSL2|PA1 (44)|-|-|
|RSPI0 / SSL3|PA2 (--)|PC2 (32)|-|

### LFQFP80

|Peripheral|FIRST|SECOND|THIRD|
|---|---|---|---|
|SCI1 / RXD|P15 (25)|P30 (18)|-|
|SCI1 / TXD|P16 (24)|P26 (20)|-|
|SCI1 / SCK|P17 (23)|P27 (19)|-|
|SCI5 / RXD|PA2 (55)|PA3 (54)|PC2 (40)|
|SCI5 / TXD|PA4 (53)|PA4 (53)|PC3 (39)|
|SCI5 / SCK|PA1 (56)|PA1 (56)|PC4 (38)|
|SCI6 / RXD|PB0 (49)|PD1 (65)|-|
|SCI6 / TXD|PB1 (47)|PD0 (66)|-|
|SCI6 / SCK|PB3 (45)|PD2 (64)|-|
|SCI8 / RXD|PC6 (36)|-|-|
|SCI8 / TXD|PC7 (35)|-|-|
|SCI8 / SCK|PC5 (37)|-|-|
|SCI9 / RXD|PB6 (42)|-|-|
|SCI9 / TXD|PB7 (41)|-|-|
|SCI9 / SCK|PB5 (43)|-|-|
|SCI12 / RXD|PE2 (61)|-|-|
|SCI12 / TXD|PE1 (62)|-|-|
|SCI12 / SCK|PE0 (63)|-|-|
|RIIC0 / SCL|P16 (24)|P12 (28)|-|
|RIIC0 / SDA|P17 (23)|P13 (27)|-|
|RSCAN / CRX|P15 (25)|P55 (33)|-|
|RSCAN / CTX|P14 (26)|P54 (34)|-|
|RSPI0 / RSPCK|PA5 (52)|PB0 (49)|PC5 (37)|
|RSPI0 / MOSI|PA6 (51)|P16 (24)|PC6 (36)|
|RSPI0 / MISO|PA7 (35)|P17 (23)|PC7 (35)|
|RSPI0 / SSL0|PA4 (53)|PC4 (38)|-|
|RSPI0 / SSL1|PA0 (57)|-|-|
|RSPI0 / SSL2|PA1 (56)|-|-|
|RSPI0 / SSL3|PA2 (55)|PC2 (40)|-|

---

## Port map order (MTU) / ポートマップ候補 (MTU)

- [port_map_mtu.hpp](port_map_mtu.hpp?ts=4)

### LFQFP48

|MTU|FIRST|SECOND|THIRD|FOURTH|FIFTH|SIXTH|SEVENTH|
|---|---|---|---|---|---|---|---|
|MTIOC0A|P34 (--)|PB3 (26)|PC4 (24)|-|-|-|-|
|MTIOC0B|P13 (--)|P15 (15)|PA1 (34)|-|-|-|-|
|MTIOC0C|P32 (--)|PB1 (27)|PC5 (23)|-|-|-|-|
|MTIOC0D|PA3 (33)|-|-|-|-|-|-|
|MTIOC1A|P20 (--)|PE4 (35)|-|-|-|-|-|
|MTIOC1B|P21 (--)|PB5 (25)|PE3 (36)|-|-|-|-|
|MTIOC2A|P26 (12)|PB5 (25)|-|-|-|-|-|
|MTIOC2B|P27 (11)|PE5 (--)|-|-|-|-|-|
|MTIOC3A|P14 (16)|P17 (13)|PC7 (21)|PJ1 (--)|-|-|-|
|MTIOC3B|P17 (13)|PA1 (34)|PB7 (--)|PC5 (23)|PH0 (20)|-|-|
|MTIOC3C|P16 (14)|PC6 (22)|-|-|-|-|-|
|MTIOC3D|P16 (14)|PA6 (31)|PB0 (29)|PB6 (--)|PC4 (24)|PH1 (19)|-|
|MTIOC4A|P55 (--)|PA0 (--)|PB3 (26)|PE2 (37)|PE4 (35)|-|-|
|MTIOC4B|P30 (10)|P54 (--)|PC2 (26)|PD1 (--)|PE3 (36)|-|-|
|MTIOC4C|PA4 (32)|PB1 (27)|PE1 (38)|PE5 (--)|PH2 (18)|-|-|
|MTIOC4D|P31 (9)|P55 (--)|PA3 (33)|PC3 (25)|PD2 (--)|PE4 (35)|PH3 (17)|
|MTIOC5U|PA4 (32)|-|-|-|-|-|-|
|MTIOC5V|PA3 (33)|PA6 (31)|-|-|-|-|-|
|MTIOC5W|PB0 (29)|-|-|-|-|-|-|
|MTCLKA|P14 (16)|PA4 (32)|PC6 (22)|-|-|-|-|
|MTCLKB|P15 (15)|PA6 (31)|PC7 (21)|-|-|-|-|
|MTCLKC|PA1 (34)|PC4 (24)|-|-|-|-|-|
|MTCLKD|PA3 (33)|PC5 (23)|-|-|-|-|-|

### LFQFP64

|MTU|FIRST|SECOND|THIRD|FOURTH|FIFTH|SIXTH|SEVENTH|
|---|---|---|---|---|---|---|---|
|MTIOC0A|P34 (--)|PB3 (36)|PC4 (30)|-|-|-|-|
|MTIOC0B|P13 (--)|P15 (19)|PA1 (44)|-|-|-|-|
|MTIOC0C|P32 (12)|PB1 (37)|PC5 (29)|-|-|-|-|
|MTIOC0D|PA3 (43)|-|-|-|-|-|-|
|MTIOC1A|P20 (--)|PE4 (47)|-|-|-|-|-|
|MTIOC1B|P21 (--)|PB5 (35)|PE3 (48)|-|-|-|-|
|MTIOC2A|P26 (16)|PB5 (35)|-|-|-|-|-|
|MTIOC2B|P27 (15)|PE5 (46)|-|-|-|-|-|
|MTIOC3A|P14 (20)|P17 (17)|PC7 (27)|PJ1 (--)|-|-|-|
|MTIOC3B|P17 (17)|PA1 (44)|PB7 (33)|PC5 (29)|PH0 (24)|-|-|
|MTIOC3C|P16 (18)|PC6 (28)|-|-|-|-|-|
|MTIOC3D|P16 (18)|PA6 (41)|PB0 (39)|PB6 (34)|PC4 (30)|PH1 (23)|-|
|MTIOC4A|P55 (25)|PA0 (45)|PB3 (36)|PE2 (49)|PE4 (47)|-|-|
|MTIOC4B|P30 (14)|P54 (26)|PC2 (32)|PD1 (--)|PE3 (48)|-|-|
|MTIOC4C|PA4 (42)|PB1 (37)|PE1 (50)|PE5 (46)|PH2 (22)|-|-|
|MTIOC4D|P31 (13)|P55 (25)|PA3 (43)|PC3 (31)|PD2 (--)|PE4 (47)|PH3 (21)|
|MTIOC5U|PA4 (42)|-|-|-|-|-|-|
|MTIOC5V|PA3 (43)|PA6 (41)|-|-|-|-|-|
|MTIOC5W|PB0 (39)|-|-|-|-|-|-|
|MTCLKA|P14 (20)|PA4 (42)|PC6 (28)|-|-|-|-|
|MTCLKB|P15 (19)|PA6 (41)|PC7 (27)|-|-|-|-|
|MTCLKC|PA1 (44)|PC4 (30)|-|-|-|-|-|
|MTCLKD|PA3 (43)|PC5 (29)|-|-|-|-|-|

### LFQFP80

|MTU|FIRST|SECOND|THIRD|FOURTH|FIFTH|SIXTH|SEVENTH|
|---|---|---|---|---|---|---|---|
|MTIOC0A|P34 (15)|PB3 (45)|PC4 (38)|-|-|-|-|
|MTIOC0B|P13 (27)|P15 (25)|PA1 (56)|-|-|-|-|
|MTIOC0C|P32 (16)|PB1 (47)|PC5 (37)|-|-|-|-|
|MTIOC0D|PA3 (54)|-|-|-|-|-|-|
|MTIOC1A|P20 (22)|PE4 (59)|-|-|-|-|-|
|MTIOC1B|P21 (21)|PB5 (43)|PE3 (60)|-|-|-|-|
|MTIOC2A|P26 (20)|PB5 (43)|-|-|-|-|-|
|MTIOC2B|P27 (19)|PE5 (58)|-|-|-|-|-|
|MTIOC3A|P14 (26)|P17 (23)|PC7 (35)|PJ1 (5)|-|-|-|
|MTIOC3B|P17 (23)|PA1 (56)|PB7 (41)|PC5 (37)|PH0 (32)|-|-|
|MTIOC3C|P16 (24)|PC6 (36)|-|-|-|-|-|
|MTIOC3D|P16 (24)|PA6 (51)|PB0 (49)|PB6 (42)|PC4 (38)|PH1 (31)|-|
|MTIOC4A|P55 (33)|PA0 (57)|PB3 (45)|PE2 (61)|PE4 (59)|-|-|
|MTIOC4B|P30 (18)|P54 (34)|PC2 (40)|PD1 (65)|PE3 (60)|-|-|
|MTIOC4C|PA4 (53)|PB1 (47)|PE1 (62)|PE5 (58)|PH2 (30)|-|-|
|MTIOC4D|P31 (17)|P55 (33)|PA3 (54)|PC3 (39)|PD2 (64)|PE4 (59)|PH3 (29)|
|MTIOC5U|PA4 (53)|-|-|-|-|-|-|
|MTIOC5V|PA3 (54)|PA6 (51)|-|-|-|-|-|
|MTIOC5W|PB0 (49)|-|-|-|-|-|-|
|MTCLKA|P14 (26)|PA4 (53)|PC6 (36)|-|-|-|-|
|MTCLKB|P15 (25)|PA6 (51)|PC7 (35)|-|-|-|-|
|MTCLKC|PA1 (56)|PC4 (38)|-|-|-|-|-|
|MTCLKD|PA3 (54)|PC5 (37)|-|-|-|-|-|

---

## Port map order (TMR) / ポートマップ候補 (TMR)

- [port_map_tmr.hpp](port_map_tmr.hpp?ts=4)

### LFQFP48

|TMR|FIRST|SECOND|THIRD|
|---|---|---|---|
|TMO0|PB3 (26)|PH1 (19)|-|
|TMCI0|P21 (--)|PB1 (27)|PH3 (17)|
|TMRI0|P20 (--)|PA4 (32)|PH2 (18)|
|TMO1|P17 (13)|P26 (12)|-|
|TMCI1|P12 (--)|P54 (--)|PC4 (24)|
|TMRI1|PB5 (25)|-|-|
|TMO2|P16 (14)|PC7 (21)|-|
|TMCI2|P15 (15)|P31 (9)|PC6 (22)|
|TMRI2|P14 (16)|PC5 (23)|-|
|TMO3|P13 (--)|P32 (--)|P55 (--)|
|TMCI3|P27 (11)|P34 (--)|PA6 (31)|
|TMRI3|P30 (10)|-|-|

### LFQFP64

|TMR|FIRST|SECOND|THIRD|
|---|---|---|---|
|TMO0|PB3 (36)|PH1 (23)|-|
|TMCI0|P21 (--)|PB1 (37)|PH3 (21)|
|TMRI0|P20 (--)|PA4 (42)|PH2 (22)|
|TMO1|P17 (17)|P26 (16)|-|
|TMCI1|P12 (--)|P54 (26)|PC4 (30)|
|TMRI1|PB5 (35)|-|-|
|TMO2|P16 (18)|PC7 (27)|-|
|TMCI2|P15 (19)|P31 (13)|PC6 (28)|
|TMRI2|P14 (20)|PC5 (29)|-|
|TMO3|P13 (--)|P32 (12)|P55 (25)|
|TMCI3|P27 (--)|P34 (--)|PA6 (41)|
|TMRI3|P30 (14)|-|-|

### LFQFP80

|TMR|FIRST|SECOND|THIRD|
|---|---|---|---|
|TMO0|PB3 (45)|PH1 (31)|-|
|TMCI0|P21 (21)|PB1 (47)|PH3 (29)|
|TMRI0|P20 (22)|PA4 (53)|PH2 (30)|
|TMO1|P17 (23)|P26 (20)|-|
|TMCI1|P12 (28)|P54 (34)|PC4 (38)|
|TMRI1|PB5 (43)|-|-|
|TMO2|P16 (24)|PC7 (35)|-|
|TMCI2|P15 (25)|P31 (17)|PC6 (36)|
|TMRI2|P14 (26)|PC5 (37)|-|
|TMO3|P13 (27)|P32 (16)|P55 (33)|
|TMCI3|P27 (19)|P34 (15)|PA6 (51)|
|TMRI3|P30 (18)|-|-|

---

## 12 Bits A/D Converter input (S12AD) / 12 ビット A/D コンバーター入力 (S12AD)

- [s12ade.hpp](../RX231/s12ade.hpp?ts=4)

### LFQFP48

|S12AD/ANALOG|Port|
|---|---|
|AN000|P40 (45)|
|AN001|P41 (43)|
|AN002|P42 (42)|
|AN003|P43 (--)|
|AN004|P44 (--)|
|AN005|P45 (41)|
|AN006|P46 (40)|
|AN007|P47 (39)|
|||
|AN016|PE0 (--)|
|AN017|PE1 (38)|
|AN018|PE2 (37)|
|AN019|PE3 (36)|
|AN020|PE4 (35)|
|AN021|PE5 (--)|
|||
|AN024|PD0 (--)|
|AN025|PD1 (--)|
|AN026|PD2 (--)|

### LFQFP64

|S12AD/ANALOG|Port|
|---|---|
|AN000|P40 (45)|
|AN001|P41 (43)|
|AN002|P42 (42)|
|AN003|P43 (--)|
|AN004|P44 (--)|
|AN005|P45 (41)|
|AN006|P46 (40)|
|AN007|P47 (39)|
|||
|AN016|PE0 (--)|
|AN017|PE1 (38)|
|AN018|PE2 (37)|
|AN019|PE3 (36)|
|AN020|PE4 (35)|
|AN021|PE5 (--)|
|||
|AN024|PD0 (--)|
|AN025|PD1 (--)|
|AN026|PD2 (--)|

### LFQFP80

|S12AD/ANALOG|Port|
|---|---|
|AN000|P40 (75)|
|AN001|P41 (73)|
|AN002|P42 (72)|
|AN003|P43 (71)|
|AN004|P44 (70)|
|AN005|P45 (69)|
|AN006|P46 (68)|
|AN007|P47 (67)|
|||
|AN016|PE0 (63)|
|AN017|PE1 (62)|
|AN018|PE2 (61)|
|AN019|PE3 (60)|
|AN020|PE4 (59)|
|AN021|PE5 (58)|
|||
|AN024|PD0 (66)|
|AN025|PD1 (65)|
|AN026|PD2 (64)|

---

## 8 Bits D/A Converter output (DA) / 8 ビット D/A コンバーター出力 (DA)

- [da.hpp](../RX140/da.hpp?ts=4)

### LFQFP48

|DA/ANALOG|Port|
|---|---|
|DA0|P03 (--)|
|DA1|P05 (--)|

### LFQFP64

|DA/ANALOG|Port|
|---|---|
|DA0|P03 (1)|
|DA1|P05 (63)|

### LFQFP80

|DA/ANALOG|Port|
|---|---|
|DA0|P03 (2)|
|DA1|P05 (80)|

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
