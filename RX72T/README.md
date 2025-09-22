## RX72T features / 特徴

- RXv3 core / RXv3 コア
- Maximum operating frequency 200MHz / 最大動作周波数 200MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 2.7V ～ 5.5V Operation / 動作
- USB2.0 Full Speed, Host, Function (Optional)
- CAN Module (CAN) / CAN モジュール (CAN)
- Arithmetic Unit for Trigonometric Functions (TFUv1) / 三角関数演算器 (TFUv1)
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 12 Bits D/A / １２ビットＤ／Ａ変換器

### Package/パッケージ

|R5F572T---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F572TxxxFB|LFQFP|144|0.50|
|R5F572TxxxFP|LFQFP|100|0.50|

### Ambient operating temperature/動作周囲温度

|R5F572T--X--|degree Celsius|
|---|:-:|
|R5F572TxxDxx|-40 ～ +85℃|
|R5F572TxxGxx|-40 ～ +105℃|

### PGA, TSIP, USB

|R5F572T-X---|PGA|TSIP|USB|
|---|:-:|:-:|:-:|
|R5F572TxAxxx|〇|-|-|
|R5F572TxBxxx|-|-|-|
|R5F572TxCxxx|〇|-|〇|
|R5F572TxExxx|〇|〇|-|
|R5F572TxFxxx|-|〇|-|
|R5F572TxGxxx|〇|〇|〇|

### Memoey size/メモリ容量

|R5F572TX----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F572TKxxxx|1M|128K|32K|
|R5F572TFxxxx|512K|128K|32K|

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|32K|64|4/64|4|0x??|3|

---

## RX72T Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F572TK|1024K|128K+16K|32K|[R5F572TK.ld](R5F572TK.ld?ts=4)|7168|1024|
|R5F572TF|512K|128K+16K|32K|[R5F572TF.ld](R5F572TF.ld?ts=4)|7168|1024|

RAM: 16K(With ECC)

---

## RX72T Dedicated class / 専用クラス

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
|POE3 Definition/POE3 定義|[poe3.hpp](poe3.hpp?ts=4)||
|A/D Definition/A/D 定義|[s12adh.hpp](s12adh.hpp?ts=4)||

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

## peripheral / ペリフェラル

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

## port map order / ポートマップ候補

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
