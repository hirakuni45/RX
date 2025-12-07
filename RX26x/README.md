
## RX260/RX261 features / 特徴

- RXv3 core / RXv3 コア
- Maximum operating frequency 64MHz / 最大動作周波数 64MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 1.6V ～ 5.5V Operation / 動作
- High-speed operation mode: 84 µA/MHz / 高速動作モード：84 µA/MHz
- USB2.0 Full Speed, Host, Function
- CAN FD Module (CANFD) / CAN FD (CAN FD)
- Real time clock / リアルタイムクロック内蔵
- Capacitive touch sensor / 静電容量式タッチセンサ
- Renesas Secure IP (RSIP-E11A) / セキュリティ機能
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 8 Bits D/A / ８ビットＤ／Ａ変換器

### Package/パッケージ

|R5F526y---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F526yxxxFP|LFQFP|100|0.50|
|R5F526yxxxFN|LQFP|80|0.50|
|R5F526yxxxFM|LFQFP|64|0.50|
|R5F526yxxxFL|LQFP|48|0.50|
|R5F526yxxxNE|HWQFN|48|0.50|

### Ambient operating temperature/動作周囲温度

|R5F526y--X--|degree Celsius|
|---|:-:|
|R5F526yxxDxx|-40 ～ +85℃|
|R5F526yxxGxx|-40 ～ +105℃|

### Crypt/暗号, USB, CANFD

|R5F526y-X---|Crypt|USB|CANFD|
|---|:-:|:-:|:-:|
|R5F5261xAxxx|-|〇|〇|
|R5F5261xBxxx|〇|〇|〇|
|R5F5260xAxxx|-|-|-|

### Memoey size/メモリ容量

|R5F526yX----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F526y8xxxx|512K|128K|8K|
|R5F526y7xxxx|384K|128K|8K|
|R5F526y6xxxx|256K|128K|8K|

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|8K|256|1/256|1|0xFF|4|

---

## RX260/RX261 Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F526TF|512K|128K|8K|[R5F52618.ld](R5F52618.ld?ts=4)|2048|1024|

---

## RX260/RX261 Dedicated class / 専用クラス

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
|Port Mapping TMR/ポートマッピング TMR|[port_map_tmr.hpp](port_map_tmr.hpp?ts=4)||
|Port Mapping GPTW/ポートマッピング GPTW|[port_map_gptw.hpp](port_map_gptw.hpp?ts=4)||
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
|USB+|USB_DP(37)|
|USB-|USB_DM(36)|
|UPSEL|P35/UPSEL(15)|
|Power/電源|VCC(14), VCC(60)|
|GND/接地|VSS(12), VSS(62)|
|Analog Power/アナログ電源|AVCC0(97)|
|Analog GND/アナログ接地|AVSS0(99)|
|Analog Refarence L0/アナログ基準電源Ｌ０|VREFL0(94)|
|Analog Refarence H0/アナログ基準電源Ｈ０|VREFH0(96)|
|OSC in|EXTAL(13)|
|OSC out|XTAL(11)|
|Sub OSC in|XCIN(8)|
|Sub OSC out|XCOUT(9)|

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
|DMAC0|DMA Controller channel 0|DMA コントローラ・チャネル０|
|DMAC1|DMA Controller channel 1|DMA コントローラ・チャネル１|
|DMAC2|DMA Controller channel 2|DMA コントローラ・チャネル２|
|DMAC3|DMA Controller channel 3|DMA コントローラ・チャネル３|
|DTC|Data Transfer Controller|データトランスファコントローラ|
|ELC|Event Link Controller|イベントリンクコントローラ|
|GPTW0|General PWM Timer 0|汎用 PWM タイマ０|
|GPTW1|General PWM Timer 1|汎用 PWM タイマ１|
|GPTW2|General PWM Timer 2|汎用 PWM タイマ２|
|GPTW3|General PWM Timer 3|汎用 PWM タイマ３|
|GPTW4|General PWM Timer 4|汎用 PWM タイマ４|
|GPTW5|General PWM Timer 5|汎用 PWM タイマ５|
|GPTW6|General PWM Timer 6|汎用 PWM タイマ６|
|GPTW7|General PWM Timer 7|汎用 PWM タイマ７|
|POEG|GPTW Port Output Enable|GPTW 用ポートアウトプットイネーブル|
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
|WDTA|Watchdog Timer|ウォッチドッグタイマ|
|IWDT|Independent Watchdog Timer|独立ウォッチドッグタイマ|
|USB0|USB 2.0 Host/Function Module 0|USB 2.0 ホスト/ファンクションモジュール０|
|SCI1|Serial Communications Interface 1|シリアルコミュニケーションインタフェース１|
|SCI5|Serial Communications Interface 5|シリアルコミュニケーションインタフェース５|
|SCI6|Serial Communications Interface 6|シリアルコミュニケーションインタフェース６|
|SCI12|Serial Communications Interface 12|シリアルコミュニケーションインタフェース１２|
|RSCI0|(R)Serial Communications Interface 0|Ｒシリアルコミュニケーションインタフェース０|
|RSCI8|(R)Serial Communications Interface 8|Ｒシリアルコミュニケーションインタフェース８|
|RSCI9|(R)Serial Communications Interface 9|Ｒシリアルコミュニケーションインタフェース９|
|RIIC0|I2C-bus Interface 0|I2C バスインタフェース０|
|CANFD0|CANFD Module 0|CANFD モジュール０|
|RSPI0|Serial Peripheral Interface 0|シリアルペリフェラルインタフェース０|
|CRC|CRC Calculator|CRC 演算器|
|REMC0|Remote Control Signal Receiver|リモコン信号受信機能|
|RSIP|Renesas Secure IP (RSIP-E11A)|Renesas Secure IP (RSIP-E11A)|
|CTSU|Capacitive Touch Sensing Unit|静電容量式タッチセンサ|
|S12AD|12-Bit A/D Converter|12 ビット A/D コンバータ|
|DA|8-Bit D/A Converter|8 ビット D/A コンバータ|
|TEMPS|Temperature Sensor|温度センサ|
|CMPB|Comparator B|コンパレーターＢ|
|DOC|Data Operation Circuit|データ演算回路|

---

## Port map order (IRQ) / ポートマップ候補 (IRQ)

- [port_map_irq.hpp](port_map_irq.hpp?ts=4)

### LFQFP100

|IRQ|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|IRQ0|P30 (20)|PD0 (86)|PH1 (37)|-|-|
|IRQ1|P31 (19)|PD1 (85)|PH2 (36)|-|-|
|IRQ2|P12 (34)|P32 (18)|P36 (13)|PD2 (84)|-|
|IRQ3|P13 (33)|P33 (17)|PD3 (83)|-|-|
|IRQ4|P14 (32)|P34 (16)|P37 (11)|PB1 (59)|PD4 (82)|
|IRQ5|P15 (31)|PA4 (66)|PD5 (81)|PE5 (73)|-|
|IRQ6|P16 (30)|PA3 (67)|PD6 (80)|PE6 (72)|-|
|IRQ7|P17 (29)|PD7 (79)|PE2 (76)|PE7 (71)|-|

---

## Port map order / ポートマップ候補

- [port_map.hpp](port_map.hpp?ts=4)

### LFQFP100

|Peripheral|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|SCI1 / RXD|P15 (31)|P30 (20)|-|-|-|
|SCI1 / TXD|P16 (30)|P26 (22)|-|-|-|
|SCI1 / SCK|P17 (29)|P27 (21)|-|-|-|
|SCI5 / RXD|PA2 (68)|PA3 (67)|PC2 (50)|PC2 (50)|-|
|SCI5 / TXD|PA4 (66)|PA4 (66)|PC3 (49)|PC3 (49)|-|
|SCI5 / SCK|PA1 (69)|PA1 (69)|PC1 (51)|PC4 (48)|-|
|SCI6 / RXD|P33 (17)|PB0 (61)|PD1 (85)|-|-|
|SCI6 / TXD|P32 (18)|PB1 (59)|PD0 (86)|-|-|
|SCI6 / SCK|P34 (16)|PB3 (57)|PD2 (84)|-|-|
|RSCI0 / RXD|P21 (27)|-|-|-|-|
|RSCI0 / TXD|P20 (28)|-|-|-|-|
|RSCI0 / SCK|P22 (26)|-|-|-|-|
|RSCI0 / DE|P23 (25)|-|-|-|-|
|RSCI8 / RXD|PC6 (46)|-|-|-|-|
|RSCI8 / TXD|PC7 (45)|-|-|-|-|
|RSCI8 / SCK|PC5 (47)|-|-|-|-|
|RSCI8 / DE|PC4 (48)|-|-|-|-|
|RSCI9 / RXD|PB6 (54)|-|-|-|-|
|RSCI9 / TXD|PB7 (53)|-|-|-|-|
|RSCI9 / SCK|PB5 (55)|-|-|-|-|
|RSCI9 / DE|PB4 (56)|-|-|-|-|
|SCI12 / RXD|PE2 (76)|-|-|-|-|
|SCI12 / TXD|PE1 (77)|-|-|-|-|
|SCI12 / SCK|PE0 (78)|-|-|-|-|
|RIIC0 / SCL|P12 (34)|P16 (30)|-|-|-|
|RIIC0 / SDA|P13 (33)|P17 (29)|-|-|-|
|CANFD0 / CRX|P14 (32)|P32 (18)|P54 (40)|PD1 (85)|-|
|CANFD0 / CTX|P15 (31)|P33 (17)|P55 (39)|PD2 (84)|-|
|RSPI0 / RSPCK|PA5 (65)|PA5 (65)|PB0 (61)|PB0 (61)|PC5 (47)|
|RSPI0 / MOSI|P16 (31)|PA6 (64)|P16 (30)|PA6 (64)|PC6 (46)|
|RSPI0 / MISO|P17 (29)|PA7 (63)|P17 (29)|PA7 (63)|PC7 (45)|
|RSPI0 / SSL0|PA4 (66)|PC4 (48)|-|-|-|
|RSPI0 / SSL1|PA0 (70)|PC0 (52)|-|-|-|
|RSPI0 / SSL2|PA1 (69)|PC1 (51)|-|-|-|
|RSPI0 / SSL3|PA2 (68)|PC2 (50)|-|-|-|
|LPT / LPTO|P26 (22)|PB3 (57)|PC7 (45)|-|-|
|USB0 / VBUS|P16 (30)|PB5 (55)|-|-|-|
|USB0 / EXICEN|P21 (27)|PC6 (46)|-|-|-|
|USB0 / VBUSEN|P16 (30)|P24 (24)|P26 (22)|P32 (18)|-|
|USB0 / OVRCURA|P14 (32)|-|-|-|-|
|USB0 / OVRCURB|P16 (30)|P22 (26)|-|-|-|
|USB0 / ID|P20 (28)|PC5 (47)|-|-|-|

---

## Port map order (GPTW) / ポートマップ候補 (GPTW)

- [port_map_gptw.hpp](port_map_gptw.hpp?ts=4)

### LFQFP100

|GPTW|FIRST|SECOND|THIRD|FOURTH|FIFTH|SIXTH|SEVENTH|EIGHTH|NINTH|
|---|---|---|---|---|---|---|---|---|---|
|GTIOC0A|P17 (29)|P22 (26)|PA0 (70)|PA1 (69)|PB7 (53)|PC5 (47)|PH0 (38)|-|-|
|GTIOC0B|P16 (30)|P17 (29)|P23 (25)|PA1 (69)|PA6 (64)|PB0 (61)|PB6 (54)|PC4 (48)|PH1 (37)|
|GTIOC1A|P24 (24)|P32 (18)|P55 (39)|PA0 (70)|PB3 (57)|PE2 (76)|PE4 (74)|-|-|
|GTIOC1B|P25 (23)|P33 (17)|PA3 (67)|PA4 (66)|PB1 (59)|PE1 (77)|PE5 (73)|PH2 (36)|-|
|GTIOC2A|P21 (27)|P30 (20)|P54 (40)|PB0 (61)|PC2 (50)|PD1 (85)|PE3 (75)|-|-|
|GTIOC2B|P20 (28)|P31 (19)|P55 (39)|PA3 (67)|PB1 (59)|PC3 (49)|PD2 (84)|PE4 (74)|PH3 (35)|
|GTIOC3A|P22 (26)|P34 (16)|PB2 (58)|PB3 (57)|PC4 (48)|-|-|-|-|
|GTIOC3B|P13 (33)|P15 (31)|P23 (25)|PA1 (69)|PB3 (57)|-|-|-|-|
|GTIOC4A|P20 (28)|PA4 (66)|PE4 (74)|-|-|-|-|-|-|
|GTIOC4B|P16 (30)|P21 (27)|PA5 (65)|PB5 (55)|PE3 (75)|-|-|-|-|
|GTIOC5A|P26 (22)|PA6 (64)|PB5 (55)|-|-|-|-|-|-|
|GTIOC5B|P15 (31)|P27 (21)|PA7 (63)|PE5 (73)|-|-|-|-|-|
|GTIOC6A|P14 (32)|P17 (29)|P25 (23)|PB4 (56)|PC1 (51)|PC7 (45)|PJ1 (6)|-|-|
|GTIOC6B|P16 (30)|P24 (24)|PB5 (55)|PC0 (52)|PC6 (46)|PJ3 (4)|-|-|-|
|GTIOC7A|P13 (33)|P32 (18)|PB1 (59)|PB6 (54)|PC5 (47)|-|-|-|-|
|GTIOC7B|P14 (32)|P33 (17)|PA3 (67)|PB7 (53)|-|-|-|-|-|
|GTETRGA|P14 (32)|P24 (24)|PA4 (66)|PC2 (50)|PC6 (46)|-|-|-|-|
|GTETRGB|P15 (31)|P25 (23)|PA3 (67)|PA6 (64)|PC3 (49)|PC7 (45)|-|-|-|
|GTETRGC|P16 (30)|P22 (26)|PA1 (69)|PB2 (58)|PC0 (52)|PC4 (48)|-|-|-|
|GTETRGD|P17 (29)|P23 (25)|PA3 (67)|PB3 (57)|PC1 (51)|PC5 (47)|-|-|-|
|GTCPPO0|P14 (32)|P17 (29)|PC1 (51)|PC7 (45)|PJ1 (6)|-|-|-|-|
|GTIU|P34 (16)|PB3 (57)|PC4 (48)|-|-|-|-|-|-|
|GTIV|P13 (33)|P15 (31)|PA1 (69)|-|-|-|-|-|-|
|GTIW|P32 (18)|PB1 (59)|PC5 (47)|-|-|-|-|-|-|
|GTOULO|P16 (30)|PA6 (64)|PC4 (48)|PH1 (37)|-|-|-|-|-|
|GTOUUP|P17 (29)|PA1 (69)|PC5 (47)|PH0 (38)|-|-|-|-|-|
|GTOVLO|PA3 (67)|PA4 (66)|PB1 (59)|PE1 (77)|-|-|-|-|-|
|GTOVUP|PA0 (70)|PB3 (57)|PE2 (76)|PE4 (74)|-|-|-|-|-|
|GTOWLO|P31 (19)|PA3 (67)|PB1 (59)|PE4 (74)|-|-|-|-|-|
|GTOWUP|P30 (20)|PB0 (61)|PC2 (50)|PE3 (75)|-|-|-|-|-|

---

## Port map order (TMR) / ポートマップ候補 (TMR)

- [port_map_tmr.hpp](port_map_tmr.hpp?ts=4)

### LFQFP100

|TMR|FIRST|SECOND|THIRD|
|---|---|---|---|
|TMO0|P22 (26)|PB3 (57)|PH1 (37)|
|TMCI0|P21 (27)|PB1 (59)|PH3 (35)|
|TMRI0|P20 (28)|PA4 (66)|PH2 (36)|
|TMO1|P17 (29)|P26 (22)|-|
|TMCI1|P12 (34)|P54 (40)|PC4 (48)|
|TMRI1|P24 (24)|PB5 (55)|-|
|TMO2|P16 (30)|PC7 (45)|-|
|TMCI2|P15 (31)|P31 (19)|PC6 (46)|
|TMRI2|P14 (32)|PC5 (47)|-|
|TMO3|P13 (33)|P32 (18)|P55 (39)|
|TMCI3|P27 (21)|P34 (16)|PA6 (64)|
|TMRI3|P30 (20)|P33 (17)|-|

---

## 12 Bits A/D Converter input (S12AD) / 12 ビット A/D コンバーター入力 (S12AD)

- [s12ade.hpp](../RX231/s12ade.hpp?ts=4)

### LFQFP100

|S12AD/ANALOG|Port|
|---|---|
|AN000|P40 (95)|
|AN001|P41 (93)|
|AN002|P42 (92)|
|AN003|P43 (91)|
|AN004|P44 (90)|
|AN005|P45 (89)|
|AN006|P46 (88)|
|AN007|P47 (87)|
|||
|AN016|PE0 (78)|
|AN017|PE1 (77)|
|AN018|PE2 (76)|
|AN019|PE3 (75)|
|AN020|PE4 (74)|
|AN021|PE5 (73)|
|AN022|PE6 (72)|
|AN023|PE7 (71)|
|AN024|PD0 (86)|
|AN025|PD1 (85)|
|AN026|PD2 (84)|
|AN027|PD3 (83)|
|AN028|PD4 (82)|
|AN029|PD5 (81)|
|AN030|PD6 (80)|
|AN031|PD7 (79)|

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
