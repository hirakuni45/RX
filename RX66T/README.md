
## RX66T features / 特徴

- RXv3 core / RXv3 コア
- Maximum operating frequency 160MHz / 最大動作周波数 160MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 2.7V ～ 5.5V Operation / 動作
- USB2.0 Full Speed, Host, Function (Optional)
- CAN Module (CAN) / CAN モジュール (CAN)
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 12 Bits D/A / １２ビットＤ／Ａ変換器

### Package/パッケージ

|R5F566T---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F566TxxxFB|LFQFP|144|0.50|
|R5F566TxxxFH|LQFP|112|0.65|
|R5F566TxxxFP|LFQFP|100|0.50|
|R5F566TxxxFF|LQFP|80|0.65|
|R5F566TxxxFN|LFQFP|80|0.50|
|R5F566TxxxFM|LFQFP|64|0.50|

### Ambient operating temperature/動作周囲温度

|R5F566T--X--|degree Celsius|
|---|:-:|
|R5F566TxxDxx|-40 ～ +85℃|
|R5F566TxxGxx|-40 ～ +105℃|

### PGA, TSIP, USB

|R5F566T-X---|PGA|TSIP|USB|
|---|:-:|:-:|:-:|
|R5F566TxAxxx|〇|-|-|
|R5F566TxBxxx|-|-|-|
|R5F566TxCxxx|〇|-|〇|
|R5F566TxExxx|〇|〇|-|
|R5F566TxFxxx|-|〇|-|
|R5F566TxGxxx|〇|〇|〇|

### Memoey size/メモリ容量

|R5F566TX----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F566TKxxxx|1M|128K|32K|
|R5F566TFxxxx|512K|128K|32K|
|R5F566TExxxx|512K|64K|32K|
|R5F566TAxxxx|256K|64K|32K|

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|32K|64|4/64|4|0x??|3|

---

## RX66T Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F566TK|1024K|128K+16K|32K|[R5F566TK.ld](R5F566TK.ld?ts=4)|3584|512|
|R5F566TF|512K|128K+16K|32K|[R5F566TF.ld](R5F566TF.ld?ts=4)|3584|512|
|R5F566TE|512K|64K+16K|32K|[R5F566TE.ld](R5F566TE.ld?ts=4)|1792|256|
|R5F566TA|256K|64K+16K|32K|[R5F566TA.ld](R5F566TA.ld?ts=4)|1792|256|

RAM: 16K(With ECC)

---

## RX66T Dedicated class / 専用クラス

|Function/機能|Source|Remarks/備考|
|---|---|:-:|
|Hardware-specific Definition/ハード固有定義|[board_profile.hpp](board_profile.hpp?ts=4)||
|Operating Frequency Definition/動作周波数定義|[clock_profile.hpp](clock_profile.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 100|LFQFP 144|
|---|---|---|
|VCL|VCL(5)|VCL(10)|
|Reset Input/リセット入力|RES#(10)|RES#(15)|
|Mode Controle/モード制御|MD/FINED(6)|MD/FINED(11)|
|UB|P00/UB(4)|P00/UB(9)|
|EMLE|EMLE(2)|EMLE(7)|
|RXD|PD5/RXD1(20)|PD5/RXD1(25)|
|TXD|PD3/TXD1(22)|PD3/TXD1(27)|
|UPSEL|PE2/UPSEL(15)|PE2/UPSEL(20)|
|USB_VCC|VCC_USB(26)|VCC_USB(38)|
|USB_VSS|VSS_USB(31)|VSS_USB(37)|
|USB+|USB_DP(25)|USB_DP(36)|
|USB-|USB_DM(24)|USB_DM(35)|
|Power/電源|VCC(14), VCC(29), VCC(42), VCC(60)|VCC(6), VCC(19), VCC(42), VCC(64), VCC(88)|
|GND/接地|VSS(3), VSS(12), VSS(31), VSS(44), VSS(62)|VSS(8), VSS(17), VSS(44), VSS(66), VSS(90)|
|Analog Power/アナログ電源|AVCC0(93), AVCC1(92), AVCC2(72)|AVCC0(134), AVCC1(133), AVCC2(104), AVCC2(105)|
|Analog GND/アナログ接地|AVSS0(94), AVSS1(95), AVSS2(73)|AVSS0(135), AVSS1(136), AVSS2(106)|
|Gain GND/ゲイン接地|PGAVSS0(91), PGAVSS1(86)|PGAVSS0(132), PGAVSS1(124)|
|OSC in|EXTAL(13)|EXTAL(18)|
|OSC out|XTAL(11)|XTAL(16)|

- VCL: 0.47uF/25V

|Mode/モード|UB|MD|UPSEL|
|---|:---:|:---:|:---:|
|Serial BOOT/シリアルブート|0|0|-|
|USB Boot/USB ブート|1|0|0/1|
|Single Chip/シングルチップ|-|1|-|

- EMLE: 0

---

## Peripheral / ペリフェラル

- [peripheral.hpp](../RX72T/peripheral.hpp?ts=4)

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
|POE3|Port Output Enable 3|ポートアウトプットイネーブル３|
|GPTW0|General PWM Timer 0|汎用 PWM タイマ０|
|GPTW1|General PWM Timer 1|汎用 PWM タイマ１|
|GPTW2|General PWM Timer 2|汎用 PWM タイマ２|
|GPTW3|General PWM Timer 3|汎用 PWM タイマ３|
|GPTW4|General PWM Timer 4|汎用 PWM タイマ４|
|GPTW5|General PWM Timer 5|汎用 PWM タイマ５|
|GPTW6|General PWM Timer 6|汎用 PWM タイマ６|
|GPTW7|General PWM Timer 7|汎用 PWM タイマ７|
|GPTW8|General PWM Timer 8|汎用 PWM タイマ８|
|GPTW9|General PWM Timer 9|汎用 PWM タイマ９|
|HRPWM|High Resolution PWM Waveform Generation Circuit|高分解能 PWM 波形生成回路|
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
|WDTA|Watchdog Timer|ウォッチドッグタイマ|
|IWDT|Independent Watchdog Timer|独立ウォッチドッグタイマ|
|USB0|USB 2.0 FS Host/Function Module 0|USB 2.0 FS ホスト/ファンクションモジュール０|
|SCI1|Serial Communications Interface 1|シリアルコミュニケーションインタフェース１|
|SCI5|Serial Communications Interface 5|シリアルコミュニケーションインタフェース５|
|SCI6|Serial Communications Interface 6|シリアルコミュニケーションインタフェース６|
|SCI8|Serial Communications Interface 8|シリアルコミュニケーションインタフェース８|
|SCI9|Serial Communications Interface 9|シリアルコミュニケーションインタフェース９|
|SCI11|Serial Communications Interface 11|シリアルコミュニケーションインタフェース１１|
|SCI12|Serial Communications Interface 12|シリアルコミュニケーションインタフェース１２|
|RIIC0|I2C-bus Interface 0|I2C バスインタフェース０|
|CAN0|CAN Module 0|CAN モジュール０|
|RSPI0|Serial Peripheral Interface 0|シリアルペリフェラルインタフェース０|
|S12AD|12-Bit A/D Converter|12 ビット A/D コンバータ|
|S12AD1|12-Bit A/D Converter 1|12 ビット A/D コンバータ１|
|S12AD2|12-Bit A/D Converter 2|12 ビット A/D コンバータ２|
|R12DA|12-Bit D/A Converter|12 ビット D/A コンバータ|
|CMPC0|Comparator C0|コンパレーターＣ０|
|CMPC1|Comparator C1|コンパレーターＣ１|
|CMPC2|Comparator C2|コンパレーターＣ２|
|CMPC3|Comparator C3|コンパレーターＣ３|
|CMPC4|Comparator C4|コンパレーターＣ４|
|CMPC5|Comparator C5|コンパレーターＣ５|
|CRC|CRC Calculator|CRC 演算器|
|DOC|Data Operation Circuit|データ演算回路|
|ECCRAM|ECC RAM (32K)|ECC RAM (32K)|
|TSIP|Trusted Secure IP (TSIP-Lite)|Trusted Secure IP (TSIP-Lite)|

---

## Port map order (IRQ) / ポートマップ候補 (IRQ)

- [port_map_irq.hpp](../RX72T/port_map_irq.hpp?ts=4)

### LFQGFP100

|IRQ|FIRST|SECOND|THIRD|FOURTH|FIFTH|SIXTH|
|---|---|---|---|---|---|---|
|IRQ0|P10 DS (100)|P52 (81)|PE5 (1)|PG0 (---)|-|-|
|IRQ1|P11 DS (99)|P53 (80)|PA5 (36)|PE4 (8)|PG1 (---)|-|
|IRQ2|PE3 DS (9)|P00 (4)|P54 (79)|PB6 (27)|PD4 (21)|PG2 (---)|
|IRQ3|PB4 DS (30)|P34 (---)|P55 (78)|P82 (96)|PE6 (---)|-|
|IRQ4|P96 DS (43)|P01 (7)|P24 (65)|P60 (77)|PB1 (34)|-|
|IRQ5|P70 DS (57)|P61 (76)|P80 (98)|PD6 (19)|PF2 (---)|-|
|IRQ6|P21 DS (68)|P31 (61)|P35 (---)|P62 (75)|PD5 (20)|-|
|IRQ7|P20 DS (69)|P30 (63)|P63 (74)|PA6 (---)|PE0 (17)|-|
|IRQ8|PK1 DS (---)|P64 (71)|PB0 (35)|PD7 (18)|-|-|
|IRQ9|PK2 DS (---)|P12 (---)|P65 (70)|PB3 (32)|-|-|
|IRQ10|PC5 DS (---)|P13 (---)|P22 (67)|P25 (---)|-|-|
|IRQ11|PC6 DS (---)|P14 (---)|P23 (66)|P26 (---)|-|-|
|IRQ12|P32 DS (59)|P15 (---)|PC0 (---)|PF0 (---)|-|-|
|IRQ13|P33 DS (58)|P16 (---)|PC1 (---)|PF1 (---)|-|-|
|IRQ14|PA1 DS (40)|P17 (---)|PC3 (---)|PF3 (---)|-|-|
|IRQ15|PK0 DS (---)|P27 (64)|PC2 (---)|PE1 (16)|-|-|

### LFQGFP144

|IRQ|FIRST|SECOND|THIRD|FOURTH|FIFTH|SIXTH|
|---|---|---|---|---|---|---|
|IRQ0|P10 DS (141)|P52 (114)|PE5 (5)|PG0 (82)|-|-|
|IRQ1|P11 DS (140)|P53 (113)|PA5 (54)|PE4 (13)|PG1 (81)|-|
|IRQ2|PE3 DS (14)|P00 (9)|P54 (112)|PB6 (40)|PD4 (26)|PG2 (80)|
|IRQ3|PB4 DS (43)|P34 (61)|P55 (111)|P82 (137)|PE6 (4)|-|
|IRQ4|P96 DS (65)|P01 (12)|P24 (95)|P60 (110)|PB1 (50)|-|
|IRQ5|P70 DS (79)|P61 (109)|P80 (139)|PD6 (24)|PF2 (32)|-|
|IRQ6|P21 DS (100)|P31 (89)|P35 (60)|P62 (108)|PD5 (25)|-|
|IRQ7|P20 DS (101)|P30 (91)|P63 (107)|PA6 (53)|PE0 (22)|-|
|IRQ8|PK1 DS (84)|P64 (103)|PB0 (51)|PD7 (23)|-|-|
|IRQ9|PK2 DS (83)|P12 (3)|P65 (102)|PB3 (48)|-|-|
|IRQ10|PC5 DS (63)|P13 (2)|P22 (97)|P25 (94)|-|-|
|IRQ11|PC6 DS (62)|P14 (1)|P23 (96)|P26 (93)|-|-|
|IRQ12|P32 DS (87)|P15 (144)|PC0 (47)|PF0 (34)|-|-|
|IRQ13|P33 DS (86)|P16 (143)|PC1 (46)|PF1 (33)|-|-|
|IRQ14|PA1 DS (58)|P17 (142)|PC3 (99)|PF3 (31)|-|-|
|IRQ15|PK0 DS (85)|P27 (92)|PC2 (45)|PE1 (21)|-|-|

---

## Port map order / ポートマップ候補

- [port_map.hpp](../RX72T/port_map.hpp?ts=4)

### LFQFP100

|Peripheral|FIRST|SECOND|THIRD|FOURTH|FIFTH|SIXTH|SEVENTH|
|---|---|---|---|---|---|---|---|
|SCI1 / RXD|P34 (---)|PC3 (---)|PD5 (20)|-|-|-|-|
|SCI1 / TXD|P35 (---)|PC4 (---)|PD3 (22)|-|-|-|-|
|SCI1 / SCK|P25 (---)|P25 (---)|PD4 (21)|-|-|-|-|
|SCI5 / RXD|PB6 (27)|PE0 (17)|PK0 (---)|-|-|-|-|
|SCI5 / TXD|PB5 (28)|PD7 (18)|PK1 (---)|-|-|-|-|
|SCI5 / SCK|PB7 (26)|PD2 (23)|PK2 (---)|-|-|-|-|
|SCI6 / RXD|P80 (98)|PA5 (36)|PB1 (34)|-|-|-|-|
|SCI6 / TXD|P81 (97)|PB0 (35)|PB2 (33)|-|-|-|-|
|SCI6 / SCK|P82 (96)|PA4 (37)|PB3 (32)|-|-|-|-|
|SCI8 / RXD|P22 (67)|PA5 (36)|PC0 (---)|PD1 (24)|P22 (67)|-|-|
|SCI8 / TXD|P21 (68)|PA4 (37)|PC1 (---)|PD0 (25)|P23 (66)|-|-|
|SCI8 / SCK|P20 (69)|PA3 (38)|PC2 (---)|PD2 (23)|P24 (65)|-|-|
|SCI9 / RXD|P00 (4)|PA2 (39)|PG0 (---)|-|-|-|-|
|SCI9 / TXD|P01 (7)|PA1 (40)|PG1 (---)|-|-|-|-|
|SCI9 / SCK|PE4 (8)|PA0 (41)|PG2 (---)|-|-|-|-|
|SCI11 / RXD|PA1 (40)|PA7 (---)|PB6 (27)|PC6 (---)|PD5 (20)|PF1 (---)|-|
|SCI11 / TXD|PA0 (41)|PA6 (---)|PB5 (28)|PC5 (---)|PD3 (22)|PF0 (---)|-|
|SCI11 / SCK|PA2 (39)|PA2 (---)|PB4 (30)|PB7 (---)|PD4 (21)|PF2 (---)|-|
|SCI12 / RXD|P00 (4)|P22 (67)|P80 (98)|PA7 (---)|PB6 (27)|PC3 (---)|-|
|SCI12 / TXD|P01 (7)|P21 (68)|P81 (97)|PA6 (---)|PB5 (28)|PC4 (---)|-|
|SCI12 / SCK|P82 (96)|P82 (96)|P82 (96)|P82 (96)|PB7 (26)|PB7 (---)|-|
|RIIC0 / SCL|PB1 (34)|-|-|-|-|-|-|
|RIIC0 / SDA|PB2 (33)|-|-|-|-|-|-|
|CAN0 / CRX|P22 (67)|PA1 (40)|PA7 (---)|PB6 (27)|PC6 (---)|PE0 (17)|PF3 (---)|
|CAN0 / CTX|P23 (66)|PA0 (41)|PA6 (---)|PB5 (28)|PC5 (---)|PD7 (18)|PF2 (---)|
|RSPI0 / RSPCK|P20 (69)|P24 (65)|PA4 (37)|PB3 (32)|PD0 (25)|-|-|
|RSPI0 / MOSI|P21 (68)|P23 (66)|PB0 (35)|PB0 (35)|PD2 (23)|-|-|
|RSPI0 / MISO|P22 (67)|P22 (67)|PA5 (36)|PA5 (36)|PD1 (24)|-|-|
|RSPI0 / SSL0|P30 (63)|PA3 (38)|PD6 (19)|-|-|-|-|
|RSPI0 / SSL1|P31 (61)|PA2 (39)|PD7 (18)|-|-|-|-|
|RSPI0 / SSL2|P32 (59)|PA1 (40)|PE0 (17)|-|-|-|-|
|RSPI0 / SSL3|P33 (58)|PA0 (41)|PE1 (16)|-|-|-|-|
|USB0 / VBUS|PC0 (---)|PD2 (23)|-|-|-|-|-|
|USB0 / EXICEN|PA0 (41)|PC1 (---)|-|-|-|-|-|
|USB0 / VBUSEN|PA0 (41)|PC1 (---)|PB5 (28)|-|-|-|-|
|USB0 / OVRCURA|PA1 (40)|PB6 (27)|PC2 (---)|-|-|-|-|
|USB0 / OVRCURB|P34 (---)|PB4 (30)|PB7 (---)|PE0 (17)|-|-|-|
|USB0 / ID|PA1 (40)|PC2 (---)|-|-|-|-|-|

### LFQFP144

|Peripheral|FIRST|SECOND|THIRD|FOURTH|FIFTH|SIXTH|SEVENTH|
|---|---|---|---|---|---|---|---|
|SCI1 / RXD|P34 (61)|PC3 (99)|PD5 (25)|-|-|-|-|
|SCI1 / TXD|P35 (60)|PC4 (98)|PD3 (27)|-|-|-|-|
|SCI1 / SCK|P25 (94)|P25 (94)|PD4 (26)|-|-|-|-|
|SCI5 / RXD|PB6 (40)|PE0 (22)|PK0 (85)|-|-|-|-|
|SCI5 / TXD|PB5 (41)|PD7 (23)|PK1 (84)|-|-|-|-|
|SCI5 / SCK|PB7 (39)|PD2 (28)|PK2 (83)|-|-|-|-|
|SCI6 / RXD|P80 (139)|PA5 (54)|PB1 (50)|-|-|-|-|
|SCI6 / TXD|P81 (138)|PB0 (51)|PB2 (49)|-|-|-|-|
|SCI6 / SCK|P82 (137)|PA4 (55)|PB3 (48)|-|-|-|-|
|SCI8 / RXD|P22 ( 97)|PA5 (54)|PC0 (47)|PD1 (29)|P22 (97)|-|-|
|SCI8 / TXD|P21 (100)|PA4 (55)|PC1 (46)|PD0 (30)|P23 (96)|-|-|
|SCI8 / SCK|P20 (101)|PA3 (56)|PC2 (45)|PD2 (28)|P24 (95)|-|-|
|SCI9 / RXD|P00 ( 9)|PA2 (57)|PG0 (82)|-|-|-|-|
|SCI9 / TXD|P01 (12)|PA1 (58)|PG1 (81)|-|-|-|-|
|SCI9 / SCK|PE4 (13)|PA0 (59)|PG2 (80)|-|-|-|-|
|SCI11 / RXD|PA1 (58)|PA7 (52)|PB6 (40)|PC6 (62)|PD5 (25)|PF1 (33)|-|
|SCI11 / TXD|PA0 (59)|PA6 (53)|PB5 (41)|PC5 (63)|PD3 (27)|PF0 (34)|-|
|SCI11 / SCK|PA2 (57)|PA2 (57)|PB4 (43)|PB7 (39)|PD4 (26)|PF2 (32)|-|
|SCI12 / RXD|P00 (  9)|P22 ( 97)|P80 (139)|PA7 ( 52)|PB6 (40)|PC3 (99)|-|
|SCI12 / TXD|P01 ( 12)|P21 (100)|P81 (138)|PA6 ( 53)|PB5 (41)|PC4 (98)|-|
|SCI12 / SCK|P82 (137)|P82 (137)|P82 (137)|P82 (137)|PB7 (39)|PB7 (39)|-|
|RIIC0 / SCL|PB1 (50)|-|-|-|-|-|-|
|RIIC0 / SDA|PB2 (49)|-|-|-|-|-|-|
|CAN0 / CRX|P22 (97)|PA1 (58)|PA7 (52)|PB6 (40)|PC6 (62)|PE0 (22)|PF3 (31)|
|CAN0 / CTX|P23 (96)|PA0 (59)|PA6 (53)|PB5 (41)|PC5 (63)|PD7 (23)|PF2 (32)|
|RSPI0 / RSPCK|P20 (101)|P24 (95)|PA4 (55)|PB3 (48)|PD0 (30)|-|-|
|RSPI0 / MOSI|P21 (100)|P23 (96)|PB0 (51)|PB0 (51)|PD2 (28)|-|-|
|RSPI0 / MISO|P22 ( 97)|P22 (97)|PA5 (54)|PA5 (54)|PD1 (29)|-|-|
|RSPI0 / SSL0|P30 (91)|PA3 (56)|PD6 (24)|-|-|-|-|
|RSPI0 / SSL1|P31 (89)|PA2 (57)|PD7 (23)|-|-|-|-|
|RSPI0 / SSL2|P32 (87)|PA1 (58)|PE0 (22)|-|-|-|-|
|RSPI0 / SSL3|P33 (86)|PA0 (59)|PE1 (21)|-|-|-|-|
|USB0 / VBUS|PC0 (47)|PD2 (28)|-|-|-|-|-|
|USB0 / EXICEN|PA0 (59)|PC1 (46)|-|-|-|-|-|
|USB0 / VBUSEN|PA0 (59)|PC1 (46)|PB5 (41)|-|-|-|-|
|USB0 / OVRCURA|PA1 (58)|PB6 (40)|PC2 (45)|-|-|-|-|
|USB0 / OVRCURB|P34 (61)|PB4 (43)|PB7 (39)|PE0 (22)|-|-|-|
|USB0 / ID|PA1 (58)|PC2 (45)|-|-|-|-|-|

---

## Port map order (GPTW) / ポートマップ候補 (GPTW)

- [port_map_gptw.hpp](../RX72T/port_map_gptw.hpp?ts=4)

### LFQGFP100

|GPTW|FIRST|SECOND|THIRD|FOURTH|FIFTH|SIXTH|SEVENTH|EIGHTH|NINTH|TENTH|ELEVENTH|TWELVETH|
|---|---|---|---|---|---|---|---|---|---|---|---|---|
|GTIOC0A|P12 (---)|P71 (56)|PD2 (23)|PD7 (18)|PG1 (---)|-|-|-|-|-|-|-|
|GTIOC0B|P15 (---)|P74 (53)|PD1 (24)|PD6 (19)|PG2 (---)|-|-|-|-|-|-|-|
|GTIOC1A|P13 (---)|P72 (55)|PD0 (25)|PD5 (20)|PK2 (---)|-|-|-|-|-|-|-|
|GTIOC1B|P16 (---)|P75 (52)|PB7 (---)|PD4 (21)|PG0 (---)|-|-|-|-|-|-|-|
|GTIOC2A|P14 (---)|P73 (54)|PB6 (27)|PD3 (22)|PK0 (---)|-|-|-|-|-|-|-|
|GTIOC2B|P17 (---)|P76 (51)|PB5 (28)|PD2 (23)|PK1 (---)|-|-|-|-|-|-|-|
|GTIOC3A|P32 (59)|PD1 (---)|PD7 (18)|PE5 (1)|-|-|-|-|-|-|-|-|
|GTIOC3B|P11 (99)|P33 (58)|PD0 (---)|PD6 (19)|-|-|-|-|-|-|-|-|
|GTIOC4A|P71 (56)|P95 (45)|-|-|-|-|-|-|-|-|-|-|
|GTIOC4B|P74 (53)|P92 (48)|-|-|-|-|-|-|-|-|-|-|
|GTIOC5A|P72 (55)|P94 (46)|-|-|-|-|-|-|-|-|-|-|
|GTIOC5B|P75 (52)|P91 (49)|-|-|-|-|-|-|-|-|-|-|
|GTIOC6A|P73 (54)|P93 (47)|-|-|-|-|-|-|-|-|-|-|
|GTIOC6B|P76 (51)|P90 (50)|-|-|-|-|-|-|-|-|-|-|
|GTIOC7A|P12 (---)|P95 (45)|-|-|-|-|-|-|-|-|-|-|
|GTIOC7B|P15 (---)|P92 (48)|-|-|-|-|-|-|-|-|-|-|
|GTIOC8A|P13 (---)|P94 (46)|-|-|-|-|-|-|-|-|-|-|
|GTIOC8B|P16 (---)|P91 (49)|-|-|-|-|-|-|-|-|-|-|
|GTIOC9A|P14 (---)|P93 (47)|-|-|-|-|-|-|-|-|-|-|
|GTIOC9B|P17 (---)|P90 (50)|-|-|-|-|-|-|-|-|-|-|
|GTETRGA|P01 (7)|P11 (99)|P70 (57)|P96 (43)|PB4 (30)|PD5 (20)|PE3 (9)|PE4 (8)|PE6 (---)|PF3 (---)|PG2 (---)|-|
|GTETRGB|P01 (7)|P10 (100)|P34 (---)|P70 (57)|P96 (43)|PB4 (30)|PD4 (21)|PE3 (9)|PE4 (8)|PE5 (1)|PE6 (---)|PF2 (---)|
|GTETRGC|P01 (7)|P11 (99)|P70 (57)|P96 (43)|PB4 (30)|PD3 (22)|PE3 (9)|PE4 (8)|PE6 (---)|PF1 (---)|-|-|
|GTETRGD|P01 (7)|P10 (100)|P70 (57)|P96 (43)|PB4 (30)|PE3 (9)|PE4 (8)|PE5 (1)|PE6 (---)|PF0 (---)|-|-|
|GTADSM0|P35 (---)|PA3 (38)|PA7 (---)|PB2 (33)|PC2 (---)|-|-|-|-|-|-|-|
|GTADSM1|P34 (---)|PA2 (39)|PA6 (---)|PB1 (34)|PC1 (---)|-|-|-|-|-|-|-|

### LFQGFP144

|GPTW|FIRST|SECOND|THIRD|FOURTH|FIFTH|SIXTH|SEVENTH|EIGHTH|NINTH|TENTH|ELEVENTH|TWELVETH|
|---|---|---|---|---|---|---|---|---|---|---|---|---|
|GTIOC0A|P12 (3)|P71 (78)|PD2 (28)|PD7 (23)|PG1 (81)|-|-|-|-|-|-|-|
|GTIOC0B|P15 (144)|P74 (75)|PD1 (29)|PD6 (24)|PG2 (80)|-|-|-|-|-|-|-|
|GTIOC1A|P13 (2)|P72 (77)|PD0 (30)|PD5 (25)|PK2 (83)|-|-|-|-|-|-|-|
|GTIOC1B|P16 (143)|P75 (74)|PB7 (39)|PD4 (26)|PG0 (82)|-|-|-|-|-|-|-|
|GTIOC2A|P14 (1)|P73 (76)|PB6 (40)|PD3 (27)|PK0 (85)|-|-|-|-|-|-|-|
|GTIOC2B|P17 (142)|P76 (73)|PB5 (41)|PD2 (28)|PK1 (84)|-|-|-|-|-|-|-|
|GTIOC3A|P32 (87)|PD1 (29)|PD7 (23)|PE5 (5)|-|-|-|-|-|-|-|-|
|GTIOC3B|P11 (140)|P33 (86)|PD0 (30)|PD6 (24)|-|-|-|-|-|-|-|-|
|GTIOC4A|P71 (78)|P95 (67)|-|-|-|-|-|-|-|-|-|-|
|GTIOC4B|P74 (75)|P92 (70)|-|-|-|-|-|-|-|-|-|-|
|GTIOC5A|P72 (77)|P94 (68)|-|-|-|-|-|-|-|-|-|-|
|GTIOC5B|P75 (74)|P91 (71)|-|-|-|-|-|-|-|-|-|-|
|GTIOC6A|P73 (76)|P93 (69)|-|-|-|-|-|-|-|-|-|-|
|GTIOC6B|P76 (73)|P90 (72)|-|-|-|-|-|-|-|-|-|-|
|GTIOC7A|P12 (3)|P95 (67)|-|-|-|-|-|-|-|-|-|-|
|GTIOC7B|P15 (144)|P92 (70)|-|-|-|-|-|-|-|-|-|-|
|GTIOC8A|P13 (2)|P94 (68)|-|-|-|-|-|-|-|-|-|-|
|GTIOC8B|P16 (143)|P91 (71)|-|-|-|-|-|-|-|-|-|-|
|GTIOC9A|P14 (1)|P93 (69)|-|-|-|-|-|-|-|-|-|-|
|GTIOC9B|P17 (142)|P90 (72)|-|-|-|-|-|-|-|-|-|-|
|GTETRGA|P01 (12)|P11 (140)|P70 (79)|P96 (65)|PB4 (43)|PD5 (25)|PE3 (14)|PE4 (13)|PE6 (4)|PF3 (31)|PG2 (80)|-|
|GTETRGB|P01 (12)|P10 (141)|P34 (61)|P70 (79)|P96 (65)|PB4 (43)|PD4 (26)|PE3 (14)|PE4 (13)|PE5 (5)|PE6 (4)|PF2 (32)|
|GTETRGC|P01 (12)|P11 (140)|P70 (79)|P96 (65)|PB4 (43)|PD3 (27)|PE3 (14)|PE4 (13)|PE6 (4)|PF1 (33)|-|-|
|GTETRGD|P01 (12)|P10 (141)|P70 (79)|P96 (65)|PB4 (43)|PE3 (14)|PE4 (13)|PE5 (5)|PE6 (4)|PF0 (34)|-|-|
|GTADSM0|P35 (60)|PA3 (56)|PA7 (42)|PB2 (49)|PC2 (45)|-|-|-|-|-|-|-|
|GTADSM1|P34 (61)|PA2 (57)|PA6 (53)|PB1 (50)|PC1 (46)|-|-|-|-|-|-|-|

---

## port map order (MTU) / ポートマップ候補 (MTU)

- [port_map_mtu.hpp](../RX72T/port_map_mtu.hpp?ts=4)

### LFQGFP100

|MTU|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|MTIOC0A #|P31 (61)|PB3 (32)|-|-|-|
|MTIOC0B #|P30 (63)|PB2 (33)|PC0 (---)|-|-|
|MTIOC0C #|P27 (64)|PB1 (34)|PC1 (---)|-|-|
|MTIOC0D #|PB0 (35)|PC2 (---)|-|-|-|
|MTIOC1A #|P27 (64)|PA5 (36)|PC6 (---)|-|-|
|MTIOC1B #|PA4 (37)|PC5 (---)|-|-|-|
|MTIOC2A #|P35 (---)|PA3 (38)|-|-|-|
|MTIOC2B #|P34 (---)|PA2 (39)|-|-|-|
|MTIOC3A #|P11 (99)|P33 (58)|-|-|-|
|MTIOC3B #|P12 (---)|P71 (56)|-|-|-|
|MTIOC3C #|P32 (59)|-|-|-|-|
|MTIOC3D #|P15 (---)|P74 (53)|-|-|-|
|MTIOC4A #|P13 (---)|P72 (55)|-|-|-|
|MTIOC4B #|P14 (---)|P73 (54)|-|-|-|
|MTIOC4C #|P16 (---)|P75 (52)|-|-|-|
|MTIOC4D #|P17 (---)|P76 (51)|-|-|-|
|MTIC5U #|P24 (65)|P82 (96)|-|-|-|
|MTIC5V #|P23 (66)|P81 (97)|-|-|-|
|MTIC5W #|P22 (67)|P80 (98)|-|-|-|
|MTIOC6A #|PA1 (40)|-|-|-|-|
|MTIOC6B #|P95 (45)|-|-|-|-|
|MTIOC6C #|PA0 (41)|-|-|-|-|
|MTIOC6D #|P92 (48)|-|-|-|-|
|MTIOC7A #|P94 (46)|-|-|-|-|
|MTIOC7B #|P93 (47)|-|-|-|-|
|MTIOC7C #|P91 (49)|-|-|-|-|
|MTIOC7D #|P90 (50)|-|-|-|-|
|MTIOC9A #|P00 (4)|P21 (68)|P26 (---)|P35 (---)|PD7 (18)|
|MTIOC9B #|P22 ~# (67)|P10 (100)|P34 (---)|PC4 (---)|PE0 (17)|
|MTIOC9C #|P01 (7)|P20 (69)|P25 (---)|PC6 (---)|PD6 (19)|
|MTIOC9D #|P11 ~# (99)|PC3 (---)|PC5 (---)|PE1 (16)|PE5 (1)|
|MTCLKA #|P21 (68)|P33 (58)|PA7 (---)|-|-|
|MTCLKB #|P20 (69)|P32 (59)|PA6 (---)|-|-|
|MTCLKC #|P11 (99)|P31 (61)|PA7 (---)|PE4 (8)|-|
|MTCLKD #|P10 (100)|P22 (67)|P30 (63)|PA6 (---)|PE3 (9)|
|ADSM0|PA7 (---)|PB2 (33)|PC2 (---)|-|-|
|ADSM1|PA6 (---)|PB1 (34)|PC1 (---)|-|-|

### LFQGFP144

|MTU|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|MTIOC0A #|P31 (89)|PB3 (48)|-|-|-|
|MTIOC0B #|P30 (91)|PB2 (49)|PC0 (47)|-|-|
|MTIOC0C #|P27 (92)|PB1 (50)|PC1 (46)|-|-|
|MTIOC0D #|PB0 (51)|PC2 (45)|-|-|-|
|MTIOC1A #|P27 (92)|PA5 (54)|PC6 (62)|-|-|
|MTIOC1B #|PA4 (55)|PC5 (63)|-|-|-|
|MTIOC2A #|P35 (60)|PA3 (56)|-|-|-|
|MTIOC2B #|P34 (61)|PA2 (57)|-|-|-|
|MTIOC3A #|P11 (140)|P33 (86)|-|-|-|
|MTIOC3B #|P12 (3)|P71 (78)|-|-|-|
|MTIOC3C #|P32 (87)|-|-|-|-|
|MTIOC3D #|P15 (144)|P74 (75)|-|-|-|
|MTIOC4A #|P13 (2)|P72 (77)|-|-|-|
|MTIOC4B #|P14 (1)|P73 (76)|-|-|-|
|MTIOC4C #|P16 (143)|P75 (74)|-|-|-|
|MTIOC4D #|P17 (142)|P76 (73)|-|-|-|
|MTIC5U #|P24 (95)|P82 (137)|-|-|-|
|MTIC5V #|P23 (96)|P81 (138)|-|-|-|
|MTIC5W #|P22 (97)|P80 (139)|-|-|-|
|MTIOC6A #|PA1 (58)|-|-|-|-|
|MTIOC6B #|P95 (67)|-|-|-|-|
|MTIOC6C #|PA0 (59)|-|-|-|-|
|MTIOC6D #|P92 (70)|-|-|-|-|
|MTIOC7A #|P94 (68)|-|-|-|-|
|MTIOC7B #|P93 (69)|-|-|-|-|
|MTIOC7C #|P91 (71)|-|-|-|-|
|MTIOC7D #|P90 (72)|-|-|-|-|
|MTIOC9A #|P00 (9)|P21 (100)|P26 (93)|P35 (60)|PD7 (23)|
|MTIOC9B #|P22 ~# (97)|P10 (141)|P34 (61)|PC4 (98)|PE0 (22)|
|MTIOC9C #|P01 (12)|P20 (101)|P25 (94)|PC6 (62)|PD6 (24)|
|MTIOC9D #|P11 ~# (140)|PC3 (99)|PC5 (63)|PE1 (21)|PE5 (5)|
|MTCLKA #|P21 (100)|P33 (86)|PA7 (52)|-|-|
|MTCLKB #|P20 (101)|P32 (87)|PA6 (53)|-|-|
|MTCLKC #|P11 (140)|P31 (89)|PA7 (52)|PE4 (13)|-|
|MTCLKD #|P10 (141)|P22 (97)|P30 (91)|PA6 (53)|PE3 (14)|
|ADSM0|PA7 (52)|PB2 (49)|PC2 (45)|-|-|
|ADSM1|PA6 (53)|PB1 (50)|PC1 (46)|-|-|

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
