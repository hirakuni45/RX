
## RX113 features / 特徴

- RXv1 core / RXv1 コア
- Maximum operating frequency 32MHz / 最大動作周波数 32MHz
- 1.8V ～ 3.6V Operation / 動作
- USB2.0 Full Speed, Low Speed, Host, Function
- LCD Controller, Driver / LCD コントローラ、ドライバ
- Capacitive touch sensor / 静電容量式タッチセンサ
- Low power timer / ローパワータイマー
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 12 Bits D/A / １２ビットＤ／Ａ変換器

### Package/パッケージ

|R5F5113---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F5113xxxFP|LFQFP|100|0.50|
|R5F5113xxxLJ|TFLGA|100|0.65|
|R5F5113xxxFM|LFQFP|64|0.50|

### Ambient operating temperature/動作周囲温度

|R5F5113--X--|degree Celsius|
|---|:-:|
|R5F5113xxDxx|-40 ～ +85℃|
|R5F5113xxGxx|-40 ～ +105℃|

### Memoey size/メモリ容量

|R5F5113X----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F51138xxxx|512K|64K|8K|
|R5F51137xxxx|384K|64K|8K|
|R5F51136xxxx|256K|32K|8K|
|R5F51135xxxx|128K|32K|8K|

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|8K|1024|1/1024|1|0xFF|4|

---

## RX113 Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F51138|512K|64K|8K|[R5F51138.ld](R5F51138.ld?ts=4)|3072|1024|
|R5F51136|256K|32K|8K|[R5F51136.ld](R5F51136.ld?ts=4)|1536|512|

---

## RX113 Dedicated class / 専用クラス

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
|System Definition/システム定義|[system.hpp](system.hpp?ts=4)||
|System I/O Definition/システム I/O 定義|[system_io.hpp](system_io.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 64|LFQFP 100|
|---|---|---|
|VCL|VCL(13)|VCL(22)|
|Reset Input/リセット入力|RES#(7)|RES#(16)|
|Mode Controle/モード制御|MD/FINED(6)|MD/FINED(15)|
|B/UB|P14(20)|P14(29)|
|RXD|P15/RXD1(19)|P15/RXD1(28)|
|TXD|P16/TXD1(18)|P16/TXD1(27)|
|USB_VCC|VCC_USB(21)|VCC_USB(30)|
|USB_VSS|VSS_USB(24)|VSS_USB(33)|
|USB+|USB_DP(23)|USB_DP(32)|
|USB-|USB_DM(22)|USB_DM(31)|
|Power/電源|VCC(15), VCC(38)|VCC(24), VCC(60)|
|GND/接地|VSS(14), VSS(40)|VSS(23), VSS(62)|
|Analog Power/アナログ電源|AVCC0(63)|AVCC0(98)|
|Analog GND/アナログ接地|AVSS0(62)|AVSS0(97)|
|Analog Refarence L0/アナログ基準電源Ｌ０|VREFL0(59)|VREFL0(94)|
|Analog Refarence H0/アナログ基準電源Ｈ０|VREFH0(61)|VREFH0(96)|
|Analog Refarence L/アナログ基準電源Ｌ|-|VREFL(92)|
|Analog Refarence H/アナログ基準電源Ｈ|-|VREFH(93)|
|OSC out|XTAL(11)|XTAL(20)|
|OSC in|EXTAL(12)|EXTAL(21)|
|Sub OSC out|XCOUT(8)|XCOUT(17)|
|Sub OSC in|XCIN(9)|XCIN(18)|

- VCL: 4.7uF/25V

|Mode/モード|B/UB|MD|
|---|:---:|:---:|
|Serial BOOT/シリアルブート|0|0|
|USB Boot/USB ブート|1|0|
|Single Chip/シングルチップ|-|1|

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
|TMR0|8-Bit Timer 0|8 ビットタイマ０|
|TMR1|8-Bit Timer 1|8 ビットタイマ１|
|TMR2|8-Bit Timer 2|8 ビットタイマ２|
|TMR3|8-Bit Timer 3|8 ビットタイマ３|
|CMT0|Compare Match Timer 0|コンペアマッチタイマ０|
|CMT1|Compare Match Timer 1|コンペアマッチタイマ１|
|CMT2|Compare Match Timer 2|コンペアマッチタイマ２|
|CMT3|Compare Match Timer 3|コンペアマッチタイマ３|
|RTC|Realtime Clock|リアルタイムクロック|
|LPT|Low Power Timer|ローパワータイマ|
|IWDT|Independent Watchdog Timer|独立ウォッチドッグタイマ|
|USB0|USB 2.0 FS Host/Function Module 0|USB 2.0 FS ホスト/ファンクションモジュール０|
|SCI0|Serial Communications Interface 0|シリアルコミュニケーションインタフェース０|
|SCI1|Serial Communications Interface 1|シリアルコミュニケーションインタフェース１|
|SCI2|Serial Communications Interface 2|シリアルコミュニケーションインタフェース２|
|SCI5|Serial Communications Interface 5|シリアルコミュニケーションインタフェース５|
|SCI6|Serial Communications Interface 6|シリアルコミュニケーションインタフェース６|
|SCI8|Serial Communications Interface 8|シリアルコミュニケーションインタフェース８|
|SCI9|Serial Communications Interface 9|シリアルコミュニケーションインタフェース９|
|SCI12|Serial Communications Interface 12|シリアルコミュニケーションインタフェース１２|
|IrDA|IrDA Interface|IrDA インタフェース|
|RIIC0|I2C-bus Interface 0|I2C バスインタフェース０|
|SSI0|Serial Sound Interface 0|シリアルサウンドインタフェース０|
|RSPI0|Serial Peripheral Interface 0|シリアルペリフェラルインタフェース０|
|CRC|CRC Calculator|CRC 演算器|
|LCDC|LCD Controler, driver|LCD コントローラ、ドライバ|
|CTSU|Capacitive Touch Sensing Unit|静電容量式タッチセンサ|
|S12AD|12-Bit A/D Converter|12 ビット A/D コンバータ|
|R12DA|12-Bit D/A Converter|12 ビット D/A コンバータ|
|CMPB|Comparator B|コンパレータＢ|
|DOC|Data Operation Circuit|データ演算回路|

---

## port map order (IRQ) / ポートマップ候補 (IRQ)

- [port_map_irq.hpp](port_map_irq.hpp?ts=4)

### LFQFP64

|IRQ|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|IRQ0|P30 (4)|PE0 (51)|PD0 (56)|-|-|
|IRQ1|P31 (5)|PE1 (50)|PD1 (55)|-|-|
|IRQ2|P32 (16)|PB0 (39)|PC4 (30)|P12 (--)|PD2 (54)|
|IRQ3|P27 (2)|PE3 (48)|PA6 (41)|P13 (--)|PD3 (--)|
|IRQ4|P14 (20)|PB1 (37)|PE4 (47)|PD4 (--)|-|
|IRQ5|P15 (19)|PA4 (42)|PE5 (46)|P56 (--)|-|
|IRQ6|P16 (18)|PA3 (43)|PE6 (53)|P10 (--)|-|
|IRQ7|P17 (17)|PE2 (49)|PE7 (--)|P11 (--)|-|

### LFQFP100

|IRQ|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|IRQ0|P30 (13)|PE0 (78)|PD0 (85)|-|-|
|IRQ1|P31 (14)|PE1 (77)|PD1 (84)|-|-|
|IRQ2|P32 (25)|PB0 (61)|PC4 (48)|P12 (35)|PD2 (83)|
|IRQ3|P27 (11)|PE3 (75)|PA6 (63)|P13 (34)|PD3 (82)|
|IRQ4|P14 (29)|PB1 (59)|PE4 (74)|PD4 (81)|-|
|IRQ5|P15 (28)|PA4 (66)|PE5 (73)|P56 (38)|-|
|IRQ6|P16 (27)|PA3 (67)|PE6 (80)|P10 (37)|-|
|IRQ7|P17 (26)|PE2 (76)|PE7 (79)|P11 (36)|-|

---

## Port map order / ポートマップ候補

- [port_map.hpp](port_map.hpp?ts=4)

### LFQFP64

|Peripheral|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|SCI0 / RXD|P21 (--)|P11 (--)|-|-|-|
|SCI0 / TXD|P20 (--)|P10 (--)|-|-|-|
|SCI0 / SCK|P22 (--)|P12 (--)|-|-|-|
|SCI1 / RXD|P15 (19)|P30 (4)|PC6 (28)|-|-|
|SCI1 / TXD|P16 (18)|P26 (3)|PC7 (27)|-|-|
|SCI1 / SCK|P17 (17)|P27 (2)|PC5 (29)|-|-|
|SCI2 / RXD|P52 (--)|-|-|-|-|
|SCI2 / TXD|P50 (--)|-|-|-|-|
|SCI2 / SCK|P51 (--)|-|-|-|-|
|SCI5 / RXD|PA2 (--)|PA3 (43)|PC2 (32)|PC2 (32)|-|
|SCI5 / TXD|PA4 (42)|PA4 (42)|PC3 (31)|PC3 (31)|-|
|SCI5 / SCK|PA1 (44)|PA1 (44)|PC4 (30)|PC1 (33)|-|
|SCI6 / RXD|P02 (--)|P27 (2)|PB0 (39)|-|-|
|SCI6 / TXD|P07 (--)|P26 (3)|PB1 (37)|-|-|
|SCI6 / SCK|P04 (--)|P04 (--)|PB3 (36)|-|-|
|SCI8 / RXD|PC6 (28)|PA6 (41)|-|-|-|
|SCI8 / TXD|PC7 (27)|PA7 (--)|-|-|-|
|SCI8 / SCK|PC5 (29)|PA5 (--)|-|-|-|
|SCI9 / RXD|PB6 (34)|PE4 (47)|-|-|-|
|SCI9 / TXD|PB7 (33)|PE5 (46)|-|-|-|
|SCI9 / SCK|PB5 (35)|PE3 (48)|-|-|-|
|SCI12 / RXD|PE2 (49)|P17 (17)|P11 (--)|-|-|
|SCI12 / TXD|PE1 (50)|P14 (20)|P10 (--)|-|-|
|SCI12 / SCK|PE0 (51)|P27 (2)|P12 (--)|-|-|
|RIIC0 / SCL|P16 (18)|PB0 (39)|-|-|-|
|RIIC0 / SDA|P17 (17)|PA6 (41)|-|-|-|
|RSPI0 / RSPCK|P15 (19)|PB0 (39)|PC5 (29)|PE3 (48)|P51 (--)|
|RSPI0 / MOSI|P16 (18)|PA6 (41)|PC6 (28)|PE4 (47)|P50 (--)|
|RSPI0 / MISO|P17 (17)|PA3 (43)|PC7 (27)|PE5 (46)|P52 (--)|
|RSPI0 / SSL0|P14 (20)|PA4 (42)|PC4 (30)|P53 (--)|-|
|RSPI0 / SSL1|PA0 (45)|PC0 (34)|-|-|-|
|RSPI0 / SSL2|PA1 (44)|PC1 (33)|-|-|-|
|RSPI0 / SSL3|PA2 (--)|PC2 (32)|-|-|-|
|USB0 / VBUS|P16 (18)|PC4 (30)|-|-|-|
|USB0 / EXICEN|PC6 (28)|-|-|-|-|
|USB0 / VBUSEN|P16 (18)|PC4 (30)|P26 (3)|-|-|
|USB0 / OVRCURA|P14 (20)|PB3 (36)|-|-|-|
|USB0 / OVRCURB|P16 (18)|PC7 (27)|-|-|-|
|USB0 / ID|PC5 (29)|-|-|-|-|

### LFQFP100

|Peripheral|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|SCI0 / RXD|P21 (9)|P11 (36)|-|-|-|
|SCI0 / TXD|P20 (10)|P10 (37)|-|-|-|
|SCI0 / SCK|P22 (8)|P12 (35)|-|-|-|
|SCI1 / RXD|P15 (28)|P30 (13)|PC6 (46)|-|-|
|SCI1 / TXD|P16 (27)|P26 (12)|PC7 (45)|-|-|
|SCI1 / SCK|P17 (26)|P27 (11)|PC5 (47)|-|-|
|SCI2 / RXD|P52 (40)|-|-|-|-|
|SCI2 / TXD|P50 (42)|-|-|-|-|
|SCI2 / SCK|P51 (41)|-|-|-|-|
|SCI5 / RXD|PA2 (68)|PA3 (67)|PC2 (50)|PC2 (50)|-|
|SCI5 / TXD|PA4 (66)|PA4 (66)|PC3 (49)|PC3 (49)|-|
|SCI5 / SCK|PA1 (69)|PA1 (69)|PC4 (48)|PC1 (51)|-|
|SCI6 / RXD|P02 (3)|P27 (11)|PB0 (61)|-|-|
|SCI6 / TXD|P07 (99)|P26 (12)|PB1 (59)|-|-|
|SCI6 / SCK|P04 (1)|P04 (1)|PB3 (57)|-|-|
|SCI8 / RXD|PC6 (46)|PA6 (63)|-|-|-|
|SCI8 / TXD|PC7 (45)|PA7 (64)|-|-|-|
|SCI8 / SCK|PC5 (47)|PA5 (65)|-|-|-|
|SCI9 / RXD|PB6 (54)|PE4 (74)|-|-|-|
|SCI9 / TXD|PB7 (53)|PE5 (73)|-|-|-|
|SCI9 / SCK|PB5 (55)|PE3 (75)|-|-|-|
|SCI12 / RXD|PE2 (76)|P17 (26)|P11 (36)|-|-|
|SCI12 / TXD|PE1 (77)|P14 (29)|P10 (37)|-|-|
|SCI12 / SCK|PE0 (78)|P27 (11)|P12 (35)|-|-|
|RIIC0 / SCL|P16 (27)|PB0 (61)|-|-|-|
|RIIC0 / SDA|P17 (26)|PA6 (63)|-|-|-|
|RSPI0 / RSPCK|P15 (28)|PB0 (61)|PC5 (47)|PE3 (75)|P51 (41)|
|RSPI0 / MOSI|P16 (27)|PA6 (63)|PC6 (46)|PE4 (74)|P50 (42)|
|RSPI0 / MISO|P17 (26)|PA3 (67)|PC7 (45)|PE5 (73)|P52 (40)|
|RSPI0 / SSL0|P14 (29)|PA4 (66)|PC4 (48)|P53 (39)|-|
|RSPI0 / SSL1|PA0 (70)|PC0 (52)|-|-|-|
|RSPI0 / SSL2|PA1 (69)|PC1 (51)|-|-|-|
|RSPI0 / SSL3|PA2 (68)|PC2 (50)|-|-|-|
|USB0 / VBUS|P16 (27)|PC4 (48)|-|-|-|
|USB0 / EXICEN|PC6 (46)|-|-|-|-|
|USB0 / VBUSEN|P16 (27)|PC4 (48)|P26 (12)|-|-|
|USB0 / OVRCURA|P14 (29)|PB3 (57)|-|-|-|
|USB0 / OVRCURB|P16 (27)|PC7 (45)|-|-|-|
|USB0 / ID|PC5 (47)|-|-|-|-|

---

## Port map order (MTU) / ポートマップ候補 (MTU)

- [port_map_mtu.hpp](port_map_mtu.hpp?ts=4)

### LFQFP64

|MTU|FIRST|SECOND|THIRD|FOURTH|FIFTH|SIXTH|
|---|---|---|---|---|---|---|
|MTIOC0A|P14 (20)|PB3 (36)|PE3 (48)|P04 (--)|-|-|
|MTIOC0B|P15 (19)|PA1 (44)|P13 (--)|-|-|-|
|MTIOC0C|P17 (17)|P32 (16)|PB0 (39)|PB1 (37)|-|-|
|MTIOC0D|PA3 (43)|P02 (--)|-|-|-|-|
|MTIOC1A|PE4 (47)|P20 (--)|P56 (--)|-|-|-|
|MTIOC1B|PA3 (43)|PB5 (35)|PE3 (48)|P21 (--)|-|-|
|MTIOC2A|P26 (3)|PA6 (41)|PB5 (35)|PE0 (51)|P50 (--)|-|
|MTIOC2B|P27 (15)|PA4 (42)|PE5 (46)|P53 (--)|-|-|
|MTIOC3A|P14 (20)|P17 (17)|PC7 (27)|PE4 (47)|PC1 (33)|PF7 (--)|
|MTIOC3B|P17 (17)|PB3 (36)|PB7 (33)|PC5 (29)|P22 (--)|-|
|MTIOC3C|P16 (18)|PC6 (28)|PJ3 (--)|PC0 (34)|PF6 (--)|-|
|MTIOC3D|P16 (18)|PB6 (34)|PC4 (30)|P23 (--)|-|-|
|MTIOC4A|PA0 (45)|PB3 (36)|PE2 (49)|P24 (--)|-|-|
|MTIOC4B|P30 (4)|P54 (26)|PC2 (32)|PE3 (48)|PD1 (55)|-|
|MTIOC4C|PB1 (37)|PE1 (50)|PE5 (46)|P25 (--)|P51 (--)|-|
|MTIOC4D|P31 (5)|P55 (25)|PC3 (31)|PE4 (47)|PD2 (54)|-|
|MTIOC5U|PA4 (42)|P11 (--)|-|-|-|-|
|MTIOC5V|PA6 (41)|P10 (--)|-|-|-|-|
|MTIOC5W|PB0 (39)|P56 (--)|-|-|-|-|
|MTCLKA|P14 (20)|PA4 (42)|PC6 (28)|P24 (--)|-|-|
|MTCLKB|P15 (19)|PA6 (41)|PC7 (27)|P25 (--)|-|-|
|MTCLKC|PA1 (44)|PC4 (30)|P22 (--)|-|-|-|
|MTCLKD|PA3 (43)|PC5 (29)|P23 (--)|-|-|

### LFQFP100

|MTU|FIRST|SECOND|THIRD|FOURTH|FIFTH|SIXTH|
|---|---|---|---|---|---|---|
|MTIOC0A|P14 (29)|PB3 (57)|PE3 (75)|P04 (1)|-|-|
|MTIOC0B|P15 (28)|PA1 (69)|P13 (34)|-|-|-|
|MTIOC0C|P17 (26)|P32 (25)|PB0 (61)|PB1 (59)|-|-|
|MTIOC0D|PA3 (67)|P02 (3)|-|-|-|-|
|MTIOC1A|PE4 (74)|P20 (10)|P56 (38)|-|-|-|
|MTIOC1B|PA3 (67)|PB5 (55)|PE3 (75)|P21 (9)|-|-|
|MTIOC2A|P26 (12)|PA6 (63)|PB5 (55)|PE0 (78)|P50 (42)|-|
|MTIOC2B|P27 (11)|PA4 (68)|PE5 (73)|P53 (39)|-|-|
|MTIOC3A|P14 (29)|P17 (26)|PC7 (45)|PE4 (74)|PC1 (51)|PF7 (71)|
|MTIOC3B|P17 (26)|PB3 (57)|PB7 (53)|PC5 (47)|P22 (8)|-|
|MTIOC3C|P16 (27)|PC6 (46)|PJ3 (4)|PC0 (52)|PF6 (72)|-|
|MTIOC3D|P16 (27)|PB6 (54)|PC4 (48)|P23 (7)|-|-|
|MTIOC4A|PA0 (70)|PB3 (57)|PE2 (76)|P24 (6)|-|-|
|MTIOC4B|P30 (13)|P54 (44)|PC2 (50)|PE3 (75)|PD1 (84)|-|
|MTIOC4C|PB1 (59)|PE1 (77)|PE5 (73)|P25 (5)|P51 (41)|-|
|MTIOC4D|P31 (14)|P55 (43)|PC3 (49)|PE4 (74)|PD2 (83)|-|
|MTIOC5U|PA4 (66)|P11 (36)|-|-|-|-|
|MTIOC5V|PA6 (63)|P10 (37)|-|-|-|-|
|MTIOC5W|PB0 (61)|P56 (38)|-|-|-|-|
|MTCLKA|P14 (29)|PA4 (66)|PC6 (46)|P24 (6)|-|-|
|MTCLKB|P15 (28)|PA6 (63)|PC7 (45)|P25 (5)|-|-|
|MTCLKC|PA1 (69)|PC4 (48)|P22 (8)|-|-|-|
|MTCLKD|PA3 (67)|PC5 (47)|P23 (7)|-|-|-|

---

## Port map order (TMR) / ポートマップ候補 (TMR)

- [port_map_tmr.hpp](port_map_tmr.hpp?ts=4)

### LFQFP64

|TMR|FIRST|SECOND|THIRD|
|---|---|---|---|
|TMO0|P22 (--)|PB3 (36)|-|
|TMCI0|P21 (--)|PB1 (37)|-|
|TMRI0|P20 (--)|PA4 (42)|-|
|TMO1|P17 (17)|P26 (3)|-|
|TMCI1|P12 (--)|P54 (26)|PC4 (30)|
|TMRI1|P24 (--)|PB5 (35)|-|
|TMO2|P16 (18)|PC7 (27)|-|
|TMCI2|P15 (19)|P31 (5)|PC6 (28)|
|TMRI2|P14 (20)|PC5 (29)|-|
|TMO3|P13 (--)|P32 (16)|P55 (25)|
|TMCI3|P04 (--)|P27 (2)|PA6 (41)|
|TMRI3|P02 (--)|P30 (4)|-|

### LFQFP100

|TMR|FIRST|SECOND|THIRD|
|---|---|---|---|
|TMO0|P22 (8)|PB3 (57)|-|
|TMCI0|P21 (9)|PB1 (59)|-|
|TMRI0|P20 (10)|PA4 (66)|-|
|TMO1|P17 (26)|P26 (12)|-|
|TMCI1|P12 (35)|P54 (44)|PC4 (48)|
|TMRI1|P24 (6)|PB5 (55)|-|
|TMO2|P16 (27)|PC7 (45)|-|
|TMCI2|P15 (28)|P31 (14)|PC6 (46)|
|TMRI2|P14 (29)|PC5 (47)|-|
|TMO3|P13 (34)|P32 (25)|P55 (43)|
|TMCI3|P04 (1)|P27 (11)|PA6 (63)|
|TMRI3|P02 (3)|P30 (13)|-|

---

## 12 Bits A/D Converter input (S12AD) / 12 ビット A/D コンバーター入力 (S12AD)

- [s12adb.hpp](../RX111/s12adb.hpp?ts=4)

### LFQFP64

|S12AD/ANALOG|Port|
|---|---|
|AN000|P40 (60)|
|AN001|P41 (58)|
|AN002|P42 (57)|
|AN003|P43 (--)|
|AN004|P44 (--)|
|AN005|P90 (--)|
|AN006|P46 (--)|
|AN007|P91 (--)|
|AN008|PE0 (51)|
|AN009|PE1 (50)|
|AN010|PE2 (49)|
|AN011|PE3 (48)|
|AN012|PE4 (47)|
|AN013|PE5 (46)|
|AN014|PE6 (--)|
|AN015|PE7 (--)|
|||
|AN021|P92 (--)|

### LFQFP100

|S12AD/ANALOG|Port|
|---|---|
|AN000|P40 (95)|
|AN001|P41 (93)|
|AN002|P42 (92)|
|AN003|P43 (91)|
|AN004|P44 (90)|
|AN005|P90 (89)|
|AN006|P46 (88)|
|AN007|P91 (87)|
|AN008|PE0 (78)|
|AN009|PE1 (77)|
|AN010|PE2 (76)|
|AN011|PE3 (75)|
|AN012|PE4 (74)|
|AN013|PE5 (73)|
|AN014|PE6 (80)|
|AN015|PE7 (79)|
|||
|AN021|P92 (86)|

---

## 12 Bits D/A Converter output (R12DA) / 12 ビット D/A コンバーター出力 (R12DA)

- [r12da.hpp](../RX600/r12da.hpp?ts=4)

### LFQFP64

|R12DA/ANALOG|Port|
|---|---|
|DA0|PJ0 (1)|
|DA1|PJ2 (64)|

### LFQFP100

|R12DA/ANALOG|Port|
|---|---|
|DA0|PJ0 (2)|
|DA1|PJ2 (100)|

---

## rx_prog Flash Programming / rx_prog フラッシュプログラム

||Support/サポート|operation verification/動作検証|
|-|:-:|:-:|
|[rxprog](../rxprog)|||

---

Translated with www.DeepL.com/Translator (free version)

---

## License

[MIT](../LICENSE)
