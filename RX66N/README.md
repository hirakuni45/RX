## RX66N features / 特徴

- RXv3 core / RXv3 コア
- Maximum operating frequency 120MHz / 最大動作周波数 120MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- Double-precision 64-bit IEEE-754 floating point / 64 ビット倍精度浮動小数点
- 2.7V ～ 3.6V Operation / 動作
- IEEE1588 Ether-MAC (10/100 Mbps)
- USB2.0 Full Speed, Host, Function
- CAN (ISO11898-1)
- Serial Sound Interface (SSIE) / シリアルサウンドインタフェース (SSIE)
- SD Host Interface (SDHI) / SD ホストインタフェース (SDHI)
- Graphic LCD Controller (GLCDC) / グラフィック LCD コントローラ (GLCDC)
- 2D Drawing Engine (DRW2D) / 2D 描画エンジン (DRW2D)
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 12 Bits D/A / １２ビットＤ／Ａ変換器

### Package/パッケージ

|R5F566N---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F566NxxxBD|LFBGA|224|0.80|
|R5F566NxxxFC|LFQFP|176|0.50|
|R5F566NxxxBG|LFBGA|176|0.80|
|R5F566NxxxFB|LFQFP|144|0.50|
|R5F566NxxxLK|TFLGA|145|0.50|
|R5F566NxxxFP|LFQFP|100|0.50|

### Ambient operating temperature/動作周囲温度

|R5F566N--X--|degree Celsius|
|---|:-:|
|R5F566NxxDxx|-40 ～ +85℃|
|R5F566NxxGxx|-40 ～ +105℃|

### Crypt/暗号

|R5F566N-X---|Crypt|
|---|:-:|
|R5F566NxDxxx|-|
|R5F566NxHxxx|〇|

### Memoey size/メモリ容量

|R5F566NX----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F566NNxxxx|4M|1M|32K|
|R5F566NDxxxx|2M|1M|32K|

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|32K|64|4/64|4|0x??|4|

---

## RX66N Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F566NN|4096K|512K+512K+32K+8K|32K|[R5F566NN.ld](R5F566NN.ld?ts=4)|12288|4096|
|R5F566ND|2048K|512K+512K+32K+8K|32K|[R5F566ND.ld](R5F566ND.ld?ts=4)|12288|4096|

---

## RX66N Dedicated class / 専用クラス

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

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 100|LFQFP 144|LFQFP 176|
|---|---|---|---|
|VCL|VCL(5)|VCL(14)|VCL(14)|
|Reset Input/リセット入力|RES#(10)|RES#(19)|RES#(21)|
|Mode Controle/モード制御|MD/FINED(7)|MD/FINED(16)|MD/FINED(18)|
|UB|PC7/UB(45)|PC7/UB(60)|PC7/UB(76)|
|EMLE|EMLE(2)|EMLE(10)|EMLE(10)|
|RXD|P30/RXD1(20)|P30/RXD1(29)|PF2/RXD1(31)|
|TXD|P26/TXD1(22)|P26/TXD1(31)|PF0/RXD1(35)|
|UPSEL|P35/UPSEL(15)|P35/UPSEL(24)|P35/UPSEL(26)|
|USB_VCC|VCC_USB(35)|VCC_USB(46)|VCC_USB(54)|
|USB_VSS|VSS_USB(38)|VSS_USB(49)|VSS_USB(57)|
|USB+|USB_DP(37)|USB_DP(48)|USB_DP(56)|
|USB-|USB_DM(36)|USB_DM(47)|USB_DM(55)|
|Power/電源|VCC(14), VCC(60)|VCC(23), VCC(59), VCC(74), VCC(91)|VCC(25), VCC(39), VCC(75), VCC(90), VCC(103)|
|Power/電源||VCC(103), VCC(118), VCC(132)|VCC(115), VCC(127), VCC(142), VCC(153), VCC(164)|
|GND/接地|VSS(12), VSS(62)|VSS(12), VSS(21), VSS(57), VSS(76)|VSS(12), VSS(23), VSS(41), VSS(73), VSS(92)|
|GND/接地||VSS(93), VSS(105), VSS(116), VSS(130)|VSS(105), VSS(117), VSS(129), VSS(140), VSS(151), VSS(162)|     
|Analog Power/アナログ電源|AVCC0(97), AVCC1(1)|AVCC0(143), AVCC1(3)|AVCC0(175), AVCC1(3)|
|Analog GND/アナログ接地|AVSS0(99), AVSS1(3)|AVSS0(1), AVSS1(5)|AVSS0(1), AVSS1(5)|
|Analog Refarence L0/アナログ基準電源Ｌ0|VREFL0(94)|VREFL0(140)|VREFL0(172)|
|Analog Refarence H0/アナログ基準電源Ｈ0|VREFH0(96)|VREFH0(142)|VREFH0(174)|
|VBATT|VBATT(6)|VBATT(15)|VBATT(15)|
|OSC in|EXTAL(13)|EXTAL(22)|EXTAL(24)|
|OSC out|XTAL(11)|XTAL(20)|XTAL(22)|
|Sub OSC in|XCIN(8)|XCIN(17)|XCIN(19)|
|Sub OSC out|XCOUT(9)|XCOUT(18)|XCOUT(20)|

- VCL: 0.22uF/25V

|Mode/モード|UB|MD|UPSEL|
|---|:---:|:---:|:---:|
|Serial BOOT/シリアルブート|0|0|-|
|USB Boot/USB ブート|1|0|0/1|
|Single Chip/シングルチップ|-|1|-|

---

## peripheral / ペリフェラル

|Peripheral|Function|機能|
|---|---|---|
|CAC|Clock Frequency Accuracy Measurement Circuit|クロック周波数精度測定回路|
|ELC|Event Link Controller|イベントリンクコントローラ|
|DMAC0|DMA Controller channel 0|DMA コントローラ・チャネル０|
|DMAC1|DMA Controller channel 1|DMA コントローラ・チャネル１|
|DMAC2|DMA Controller channel 2|DMA コントローラ・チャネル２|
|DMAC3|DMA Controller channel 3|DMA コントローラ・チャネル３|
|DMAC4|DMA Controller channel 4|DMA コントローラ・チャネル４|
|DMAC5|DMA Controller channel 5|DMA コントローラ・チャネル５|
|DMAC6|DMA Controller channel 6|DMA コントローラ・チャネル６|
|DMAC7|DMA Controller channel 7|DMA コントローラ・チャネル７|
|DTC|Data Transfer Controller|データトランスファコントローラ|
|EXDMAC0|EXDMA Controller channel 0|EXDMA コントローラ・チャネル０|
|EXDMAC1|EXDMA Controller channel 1|EXDMA コントローラ・チャネル１|
|MTU0|Multi-Function Timer Pulse Unit 0|マルチファンクションタイマパルスユニット０|
|MTU1|Multi-Function Timer Pulse Unit 1|マルチファンクションタイマパルスユニット１|
|MTU2|Multi-Function Timer Pulse Unit 2|マルチファンクションタイマパルスユニット２|
|MTU3|Multi-Function Timer Pulse Unit 3|マルチファンクションタイマパルスユニット３|
|MTU4|Multi-Function Timer Pulse Unit 4|マルチファンクションタイマパルスユニット４|
|MTU5|Multi-Function Timer Pulse Unit 5|マルチファンクションタイマパルスユニット５|
|MTU6|Multi-Function Timer Pulse Unit 6|マルチファンクションタイマパルスユニット６|
|MTU7|Multi-Function Timer Pulse Unit 7|マルチファンクションタイマパルスユニット７|
|MTU8|Multi-Function Timer Pulse Unit 8|マルチファンクションタイマパルスユニット８|
|POE3|Port Output Enable 3|ポートアウトプットイネーブル３|
|GPTW0|General PWM Timer 0|汎用 PWM タイマ０|
|GPTW1|General PWM Timer 1|汎用 PWM タイマ１|
|GPTW2|General PWM Timer 2|汎用 PWM タイマ２|
|GPTW3|General PWM Timer 3|汎用 PWM タイマ３|
|TPU0|16-Bit Timer Pulse Unit 0|16 ビットタイマパルスユニット０|
|TPU1|16-Bit Timer Pulse Unit 1|16 ビットタイマパルスユニット１|
|TPU2|16-Bit Timer Pulse Unit 2|16 ビットタイマパルスユニット２|
|TPU3|16-Bit Timer Pulse Unit 3|16 ビットタイマパルスユニット３|
|TPU4|16-Bit Timer Pulse Unit 4|16 ビットタイマパルスユニット４|
|TPU5|16-Bit Timer Pulse Unit 5|16 ビットタイマパルスユニット５|
|PPG0|Programmable Pulse Generator 0|プログラマブルパルスジェネレータ０|
|PPG1|Programmable Pulse Generator 1|プログラマブルパルスジェネレータ１|
|TMR0|8-Bit Timer 0|8 ビットタイマ０|
|TMR1|8-Bit Timer 1|8 ビットタイマ１|
|TMR2|8-Bit Timer 2|8 ビットタイマ２|
|TMR3|8-Bit Timer 3|8 ビットタイマ３|
|CMT0|Compare Match Timer 0|コンペアマッチタイマ０|
|CMT1|Compare Match Timer 1|コンペアマッチタイマ１|
|CMT2|Compare Match Timer 2|コンペアマッチタイマ２|
|CMT3|Compare Match Timer 3|コンペアマッチタイマ３|
|CMTW0|Compare Match Timer W0|コンペアマッチタイマＷ０|
|CMTW1|Compare Match Timer W1|コンペアマッチタイマＷ１|
|RTC|Realtime Clock|リアルタイムクロック|
|WDTA|Watchdog Timer|ウォッチドッグタイマ|
|IWDT|Independent Watchdog Timer|独立ウォッチドッグタイマ|
|ETHERC0|Ethernet Controller 0|イーサネットコントローラ０|
|EDMAC0|DMA Controller for the Ethernet Controller 0|イーサネットコントローラ用 DMA コントローラ０|
|PMGI0|PHY Management Interface 0|PHY マネジメントインタフェース０|
|USB0|USB 2.0 FS Host/Function Module 0|USB 2.0 FS ホスト/ファンクションモジュール０|
|SCI0|Serial Communications Interface 0|シリアルコミュニケーションインタフェース０|
|SCI1|Serial Communications Interface 1|シリアルコミュニケーションインタフェース１|
|SCI2|Serial Communications Interface 2|シリアルコミュニケーションインタフェース２|
|SCI3|Serial Communications Interface 3|シリアルコミュニケーションインタフェース３|
|SCI4|Serial Communications Interface 4|シリアルコミュニケーションインタフェース４|
|SCI5|Serial Communications Interface 5|シリアルコミュニケーションインタフェース５|
|SCI6|Serial Communications Interface 6|シリアルコミュニケーションインタフェース６|
|SCI7|Serial Communications Interface 7|シリアルコミュニケーションインタフェース７|
|SCI8|Serial Communications Interface 8|シリアルコミュニケーションインタフェース８|
|SCI9|Serial Communications Interface 9|シリアルコミュニケーションインタフェース９|
|SCI10|Serial Communications Interface 10|シリアルコミュニケーションインタフェース１０|
|SCI11|Serial Communications Interface 11|シリアルコミュニケーションインタフェース１１|
|SCI12|Serial Communications Interface 12|シリアルコミュニケーションインタフェース１２|
|RIIC0|I2C-bus Interface 0|I2C バスインタフェース０|
|RIIC1|I2C-bus Interface 1|I2C バスインタフェース１|
|RIIC2|I2C-bus Interface 2|I2C バスインタフェース２|
|CAN0|CAN Module 0|CAN モジュール０|
|CAN1|CAN Module 1|CAN モジュール１|
|CAN2|CAN Module 2|CAN モジュール２|
|RSPI0|Serial Peripheral Interface 0|シリアルペリフェラルインタフェース０|
|RSPI1|Serial Peripheral Interface 1|シリアルペリフェラルインタフェース１|
|RSPI2|Serial Peripheral Interface 2|シリアルペリフェラルインタフェース２|
|QSPI|Quad-SPI Memory Interface|クワッド SPI メモリインタフェース|
|CRC|CRC Calculator|CRC 演算器|
|SSIE0|Serial Sound Interface 0|シリアルサウンドインタフェース０|
|SSIE1|Serial Sound Interface 1|シリアルサウンドインタフェース１|
|SDHI|SD Host Interface|SD ホストインタフェース|
|MMCIF|MultiMediaCard Interface|マルチメディアカードインタフェース|
|PDC|Parallel Data Capture Unit|パラレルデータキャプチャユニット|
|GLCDC|Graphic LCD Controller|グラフィックスＬＣＤコントローラ|
|DRW2D|2D Drawing Engine|２Ｄ描画エンジン|
|S12AD|12-Bit A/D Converter|12 ビット A/D コンバータ|
|S12AD1|12-Bit A/D Converter 1|12 ビット A/D コンバータ１|
|R12DA|12-Bit D/A Converter|12 ビット D/A コンバータ|
|TEMPS|Temperature Sensor|温度センサ|
|DOC|Data Operation Circuit|データ演算回路|
|RAM|RAM (512K)|RAM (512K)|
|EXTRAM|Expansion RAM (512K)|拡張 RAM (512K)|
|ECCRAM|ECC RAM (32K)|ECC RAM (32K)|
|STBRAM|Standby RAM|スタンバイ RAM|

---

## port map order / ポートマップ候補

### LFQFP100

|Peripheral|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|SCI0 / RXD|P21 (27)|P33 (17)|-|-|
|SCI0 / TXD|P20 (28)|P32 (18)|-|-|
|SCI0 / SCK|P22 (26)|P34 (16)|-|-|
|SCI1 / RXD|P15 (31)|P30 (20)|PF2 (---)|-|
|SCI1 / TXD|P16 (30)|P26 (22)|PF0 (---)|-|
|SCI1 / SCK|P17 (29)|P27 (21)|PF1 (---)|-|
|SCI2 / RXD|P12 (34)|P52 (42)|-|-|
|SCI2 / TXD|P13 (33)|P50 (44)|-|-|
|SCI2 / SCK|P11 (---)|P51 (43)|-|-|
|SCI3 / RXD|P16 (30)|P25 (23)|-|-|
|SCI3 / TXD|P17 (29)|P23 (25)|-|-|
|SCI3 / SCK|P15 (31)|P24 (24)|-|-|
|SCI4 / RXD|PB0 (61)|-|-|-|
|SCI4 / TXD|PB1 (59)|-|-|-|
|SCI4 / SCK|PB3 (57)|-|-|-|
|SCI5 / RXD|PA2 (68)|PA3 (67)|PC2 (50)|PC2 (50)|
|SCI5 / TXD|PA4 (66)|PA4 (66)|PC3 (49)|PC3 (49)|
|SCI5 / SCK|PA1 (69)|PA1 (69)|PC1 (51)|PC4 (48)|
|SCI6 / RXD|P01 (---)|P33 (17)|PB0 (61)|-|
|SCI6 / TXD|P00 (---)|P32 (18)|PB1 (59)|-|
|SCI6 / SCK|P02 (---)|P34 (16)|PB3 (57)|-|
|SCI7 / RXD|P57 (---)|P92 (---)|PH1 (---)|-|
|SCI7 / TXD|P55 (39)|P90 (---)|PH2 (---)|-|
|SCI7 / SCK|P56 (---)|P91 (---)|PH0 (---)|-|
|SCI8 / RXD|PC6 (46)|PJ1 (---)|PK1 (---)|-|
|SCI8 / TXD|PC7 (45)|PJ2 (---)|PK2 (---)|-|
|SCI8 / SCK|PC5 (47)|PJ0 (---)|OK0 (---)|-|
|SCI9 / RXD|PB6 (54)|PL1 (---)|-|-|
|SCI9 / TXD|PB7 (53)|PL2 (---)|-|-|
|SCI9 / SCK|PB5 (55)|PL0 (---)|-|-|
|SCI10 / RXD|P81 (---)|P86 (---)|PC6 (46)|PM1 (---)|
|SCI10 / TXD|P82 (---)|P87 (---)|PC7 (45)|PM2 (---)|
|SCI10 / SCK|P80 (---)|P83 (---)|PC5 (47)|PM0 (---)|
|SCI11 / RXD|P76 (---)|PB6 (54)|PQ1 (---)|-|
|SCI11 / TXD|P77 (---)|PB7 (53)|PQ2 (---)|-|
|SCI11 / SCK|P75 (---)|PB5 (55)|PQ0 (---)|-|
|SCI12 / RXD|PE2 (76)|-|-|-|
|SCI12 / TXD|PE1 (77)|-|-|-|
|SCI12 / SCK|PE0 (78)|-|-|-|
|RIIC0 / SCL|P12 (34)|-|-|-|
|RIIC0 / SDA|P13 (33)|-|-|-|
|RIIC1 / SCL|P21 (27)|-|-|-|
|RIIC1 / SDA|P20 (28)|-|-|-|
|RIIC2 / SCL|P16 (30)|-|-|-|
|RIIC2 / SDA|P17 (29)|-|-|-|
|CAN0 / CRX|P33 (17)|PD2 (84)|-|-|
|CAN0 / CTX|P32 (18)|PD1 (85)|-|-|
|CAN1 / CRX|P15 (31)|P55 (39)|P15 (31)|P55 (39)|
|CAN1 / CTX|P14 (32)|P54 (40)|P23 (25)|P23 (25)|
|CAN2 / CRX|P67 (---)|-|-|-|
|CAN2 / CTX|P66 (---)|-|-|-|
|RSPI0 / RSPCK|PA5 (65)|PC5 (47)|PH0 (---)|-|
|RSPI0 / MOSI|PA6 (64)|PC6 (46)|PH1 (---)|-|
|RSPI0 / MISO|PA7 (63)|PC7 (45)|PH2 (---)|-|
|RSPI0 / SSL0|PA4 (66)|PC4 (48)|PH3 (---)|-|
|RSPI0 / SSL1|PA0 (70)|PC0 (52)|PH4 (---)|-|
|RSPI0 / SSL2|PA1 (69)|PC1 (51)|PH5 (---)|-|
|RSPI0 / SSL3|PA2 (68)|PC2 (50)|PH6 (---)|-|
|RSPI1 / RSPCK|P27 (21)|PE5 (73)|PK0 (---)|-|
|RSPI1 / MOSI|P26 (22)|PE6 (72)|PK1 (---)|-|
|RSPI1 / MISO|P30 (20)|PE7 (71)|PK2 (---)|-|
|RSPI1 / SSL0|P31 (19)|PE4 (74)|PK3 (---)|-|
|RSPI1 / SSL1|P50 (44)|PE0 (78)|PK4 (---)|-|
|RSPI1 / SSL2|P51 (43)|PE1 (77)|PK5 (---)|-|
|RSPI1 / SSL3|P52 (42)|PE2 (76)|PK6 (---)|-|
|RSPI2 / RSPCK|P56 (---)|PD3 (83)|PL0 (---)|-|
|RSPI2 / MOSI|P54 (40)|PD1 (85)|PL1 (---)|-|
|RSPI2 / MISO|P55 (39)|PD2 (84)|PL2 (---)|-|
|RSPI2 / SSL0|P57 (---)|PD4 (82)|PL3 (---)|-|
|RSPI2 / SSL1|PD5 (81)|PJ0 (---)|PL4 (---)|-|
|RSPI2 / SSL2|PD6 (80)|PJ1 (---)|PL5 (---)|-|
|RSPI2 / SSL3|PD7 (79)|PJ2 (---)|PL6 (---)|-|
|SSIE0 / AUDIO_CLK|P00 (---)|P22 (26)|P22 (26)|-|
|SSIE0 / SSIBCK0|P01 (---)|P23 (25)|P23 (25)|-|
|SSIE0 / SSILRCK0|P21 (27)|PF5 (---)|P21 (27)|-|
|SSIE0 / SSIRXD0|P20 (28)|PJ5 (---)|P20 (28)|-|
|SSIE0 / SSITXD0|P17 (29)|PJ3 (4)|P17 (29)|-|
|SSIE1 / AUDIO_CLK|P00 (---)|P22 (26)|-|-|
|SSIE1 / SSIBCK1|P02 (---)|P24 (24)|-|-|
|SSIE1 / SSILRCK1|P05 (100)|P15 (31)|-|-|
|SSIE1 / SSIDATA1|P03 (---)|P25 (23)|-|-|

### LFQFP144

|Peripheral|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|SCI0 / RXD|P21 (36)|P33 (26)|-|-|
|SCI0 / TXD|P20 (37)|P32 (27)|-|-|
|SCI0 / SCK|P22 (35)|P34 (25)|-|-|
|SCI1 / RXD|P15 (42)|P30 (29)|PF2 (---)|-|
|SCI1 / TXD|P16 (40)|P26 (31)|PF0 (---)|-|
|SCI1 / SCK|P17 (38)|P27 (30)|PF1 (---)|-|
|SCI2 / RXD|P12 (45)|P52 (54)|-|-|
|SCI2 / TXD|P13 (44)|P50 (56)|-|-|
|SCI2 / SCK|P11 (---)|P51 (55)|-|-|
|SCI3 / RXD|P16 (40)|P25 (32)|-|-|
|SCI3 / TXD|P17 (38)|P23 (34)|-|-|
|SCI3 / SCK|P15 (42)|P24 (33)|-|-|
|SCI4 / RXD|PB0 (87)|-|-|-|
|SCI4 / TXD|PB1 (84)|-|-|-|
|SCI4 / SCK|PB3 (82)|-|-|-|
|SCI5 / RXD|PA2 (95)|PA3 (94)|PC2 (70)|PC2 (70)|
|SCI5 / TXD|PA4 (92)|PA4 (92)|PC3 (67)|PC3 (67)|
|SCI5 / SCK|PA1 (96)|PA1 (96)|PC1 (73)|PC4 (66)|
|SCI6 / RXD|P01 (7)|P33 (26)|PB0 (87)|-|
|SCI6 / TXD|P00 (8)|P32 (27)|PB1 (84)|-|
|SCI6 / SCK|P02 (6)|P34 (25)|PB3 (82)|-|
|SCI7 / RXD|P57 (---)|P92 (128)|PH1 (---)|-|
|SCI7 / TXD|P55 (51)|P90 (131)|PH2 (---)|-|
|SCI7 / SCK|P56 (50)|P91 (129)|PH0 (---)|-|
|SCI8 / RXD|PC6 (61)|PJ1 (---)|PK1 (---)|-|
|SCI8 / TXD|PC7 (60)|PJ2 (---)|PK2 (---)|-|
|SCI8 / SCK|PC5 (62)|PJ0 (---)|PK0 (---)|-|
|SCI9 / RXD|PB6 (79)|PL1 (---)|-|-|
|SCI9 / TXD|PB7 (78)|PL2 (---)|-|-|
|SCI9 / SCK|PB5 (80)|PL0 (---)|-|-|
|SCI10 / RXD|P81 (64)|P86 (41)|PC6 (61)|PM1 (---)|
|SCI10 / TXD|P82 (63)|P87 (39)|PC7 (60)|PM2 (---)|
|SCI10 / SCK|P80 (65)|P83 (58)|PC5 (62)|PM0 (---)|
|SCI11 / RXD|P76 (69)|PB6 (79)|PQ1 (---)|-|
|SCI11 / TXD|P77 (68)|PB7 (78)|PQ2 (---)|-|
|SCI11 / SCK|P75 (71)|PB5 (80)|PQ0 (---)|-|
|SCI12 / RXD|PE2 (109)|-|-|-|
|SCI12 / TXD|PE1 (110)|-|-|-|
|SCI12 / SCK|PE0 (111)|-|-|-|
|RIIC0 / SCL|P12 (45)|-|-|-|
|RIIC0 / SDA|P13 (44)|-|-|-|
|RIIC1 / SCL|P21 (36)|-|-|-|
|RIIC1 / SDA|P20 (37)|-|-|-|
|RIIC2 / SCL|P16 (40)|-|-|-|
|RIIC2 / SDA|P17 (38)|-|-|-|
|CAN0 / CRX|P33 (26)|PD2 (124)|-|-|
|CAN0 / CTX|P32 (27)|PD1 (125)|-|-|
|CAN1 / CRX|P15 (42)|P55 (51)|P15 (42)|P55 (51)|
|CAN1 / CTX|P14 (43)|P54 (52)|P23 (34)|P23 (34)|
|CAN2 / CRX|P67 (98)|-|-|-|
|CAN2 / CTX|P66 (99)|-|-|-|
|RSPI0 / RSPCK|PA5 (90)|PC5 (62)|PH0 (---)|-|
|RSPI0 / MOSI|PA6 (89)|PC6 (61)|PH1 (---)|-|
|RSPI0 / MISO|PA7 (88)|PC7 (60)|PH2 (---)|-|
|RSPI0 / SSL0|PA4 (92)|PC4 (66)|PH3 (---)|-|
|RSPI0 / SSL1|PA0 (97)|PC0 (75)|PH4 (---)|-|
|RSPI0 / SSL2|PA1 (96)|PC1 (73)|PH5 (---)|-|
|RSPI0 / SSL3|PA2 (95)|PC2 (70)|PH6 (---)|-|
|RSPI1 / RSPCK|P27 (30)|PE5 (106)|PK0 (---)|-|
|RSPI1 / MOSI|P26 (31)|PE6 (102)|PK1 (---)|-|
|RSPI1 / MISO|P30 (29)|PE7 (101)|PK2 (---)|-|
|RSPI1 / SSL0|P31 (28)|PE4 (107)|PK3 (---)|-|
|RSPI1 / SSL1|P50 (56)|PE0 (111)|PK4 (---)|-|
|RSPI1 / SSL2|P51 (55)|PE1 (110)|PK5 (---)|-|
|RSPI1 / SSL3|P52 (54)|PE2 (109)|PK6 (---)|-|
|RSPI2 / RSPCK|P56 (50)|PD3 (123)|PL0 (---)|-|
|RSPI2 / MOSI|P54 (52)|PD1 (125)|PL1 (---)|-|
|RSPI2 / MISO|P55 (51)|PD2 (124)|PL2 (---)|-|
|RSPI2 / SSL0|P57 (---)|PD4 (122)|PL3 (---)|-|
|RSPI2 / SSL1|PD5 (121)|PJ0 (---)|PL4 (---)|-|
|RSPI2 / SSL2|PD6 (120)|PJ1 (---)|PL5 (---)|-|
|RSPI2 / SSL3|PD7 (119)|PJ2 (---)|PL6 (---)|-|
|SSIE0 / AUDIO_CLK|P00 (8)|P22 (35)|P22 (35)|-|
|SSIE0 / SSIBCK0|P01 (7)|P23 (34)|P23 (34)|-|
|SSIE0 / SSILRCK0|P21 (36)|PF5 (9)|P21 (36)|-|
|SSIE0 / SSIRXD0|P20 (37)|PJ5 (11)|P20 (37)|-|
|SSIE0 / SSITXD0|P17 (38)|PJ3 (13)|P17 (38)|-|
|SSIE1 / AUDIO_CLK|P00 (8)|P22 (35)|-|-|
|SSIE1 / SSIBCK1|P02 (6)|P24 (33)|-|-|
|SSIE1 / SSILRCK1|P05 (2)|P15 (42)|-|-|
|SSIE1 / SSIDATA1|P03 (4)|P25 (32)|-|-|

### LFQFP176

|Peripheral|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|SCI0 / RXD|P21 (44)|P33 (28)|-|-|
|SCI0 / TXD|P20 (45)|P32 (29)|-|-|
|SCI0 / SCK|P22 (43)|P34 (27)|-|-|
|SCI1 / RXD|P15 (50)|P30 (33)|PF2 (31)|-|
|SCI1 / TXD|P16 (48)|P26 (37)|PF0 (35)|-|
|SCI1 / SCK|P17 (46)|P27 (36)|PF1 (34)|-|
|SCI2 / RXD|P12 (53)|P52 (70)|-|-|
|SCI2 / TXD|P13 (52)|P50 (72)|-|-|
|SCI2 / SCK|P11 (67)|P51 (71)|-|-|
|SCI3 / RXD|P16 (48)|P25 (38)|-|-|
|SCI3 / TXD|P17 (46)|P23 (42)|-|-|
|SCI3 / SCK|P15 (50)|P24 (40)|-|-|
|SCI4 / RXD|PB0 (104)|-|-|-|
|SCI4 / TXD|PB1 (100)|-|-|-|
|SCI4 / SCK|PB3 (98)|-|-|-|
|SCI5 / RXD|PA2 (112)|PA3 (110)|PC2 (86)|PC2 (86)|
|SCI5 / TXD|PA4 (109)|PA4 (109)|PC3 (83)|PC3 (83)|
|SCI5 / SCK|PA1 (114)|PA1 (114)|PC1 (89)|PC4 (82)|
|SCI6 / RXD|P01 (7)|P33 (28)|PB0 (104)|-|
|SCI6 / TXD|P00 (8)|P32 (29)|PB1 (100)|-|
|SCI6 / SCK|P02 (6)|P34 (27)|PB3 (98)|-|
|SCI7 / RXD|P57 (160)|P92 (160)|PH1 (---)|-|
|SCI7 / TXD|P55 (163)|P90 (163)|PH2 (---)|-|
|SCI7 / SCK|P56 (161)|P91 (161)|PH0 (---)|-|
|SCI8 / RXD|PC6 (77)|PJ1 (59)|PK1 (---)|-|
|SCI8 / TXD|PC7 (76)|PJ2 (58)|PK2 (---)|-|
|SCI8 / SCK|PC5 (78)|PJ0 (60)|PK0 (---)|-|
|SCI9 / RXD|PB6 (95)|PL1 (---)|-|-|
|SCI9 / TXD|PB7 (94)|PL2 (---)|-|-|
|SCI9 / SCK|PB5 (96)|PL0 (---)|-|-|
|SCI10 / RXD|P81 (80)|P86 (49)|PC6 (77)|PM1 (---)|
|SCI10 / TXD|P82 (79)|P87 (47)|PC7 (76)|PM2 (---)|
|SCI10 / SCK|P80 (81)|P83 (74)|PC5 (78)|PM0 (---)|
|SCI11 / RXD|P76 (85)|PB6 (95)|PQ1 (---)|-|
|SCI11 / TXD|P77 (84)|PB7 (94)|PQ2 (---)|-|
|SCI11 / SCK|P75 (87)|PB5 (96)|PQ0 (---)|-|
|SCI12 / RXD|PE2 (133)|-|-|-|
|SCI12 / TXD|PE1 (134)|-|-|-|
|SCI12 / SCK|PE0 (135)|-|-|-|
|RIIC0 / SCL|P12 (53)|-|-|-|
|RIIC0 / SDA|P13 (52)|-|-|-|
|RIIC1 / SCL|P21 (44)|-|-|-|
|RIIC1 / SDA|P20 (45)|-|-|-|
|RIIC2 / SCL|P16 (48)|-|-|-|
|RIIC2 / SDA|P17 (46)|-|-|-|
|CAN0 / CRX|P33 (28)|PD2 (154)|-|-|
|CAN0 / CTX|P32 (29)|PD1 (156)|-|-|
|CAN1 / CRX|P15 (50)|P55 (65)|P15 (50)|P55 (65)|
|CAN1 / CTX|P14 (51)|P54 (66)|P23 (42)|P23 (42)|
|CAN2 / CRX|P67 (120)|-|-|-|
|CAN2 / CTX|P66 (122)|-|-|-|
|RSPI0 / RSPCK|PA5 (108)|PC5 (78)|PH0 (---)|-|
|RSPI0 / MOSI|PA6 (107)|PC6 (77)|PH1 (---)|-|
|RSPI0 / MISO|PA7 (106)|PC7 (76)|PH2 (---)|-|
|RSPI0 / SSL0|PA4 (109)|PC4 (82)|PH3 (---)|-|
|RSPI0 / SSL1|PA0 (118)|PC0 (91)|PH4 (---)|-|
|RSPI0 / SSL2|PA1 (114)|PC1 (89)|PH5 (---)|-|
|RSPI0 / SSL3|PA2 (112)|PC2 (86)|PH6 (---)|-|
|RSPI1 / RSPCK|P27 (36)|PE5 (130)|PK0 (---)|-|
|RSPI1 / MOSI|P26 (37)|PE6 (126)|PK1 (---)|-|
|RSPI1 / MISO|P30 (33)|PE7 (125)|PK2 (---)|-|
|RSPI1 / SSL0|P31 (32)|PE4 (131)|PK3 (---)|-|
|RSPI1 / SSL1|P50 (72)|PE0 (135)|PK4 (---)|-|
|RSPI1 / SSL2|P51 (71)|PE1 (134)|PK5 (---)|-|
|RSPI1 / SSL3|P52 (70)|PE2 (133)|PK6 (---)|-|
|RSPI2 / RSPCK|P56 (64)|PD3 (150)|PL0 (---)|-|
|RSPI2 / MOSI|P54 (66)|PD1 (156)|PL1 (---)|-|
|RSPI2 / MISO|P55 (65)|PD2 (154)|PL2 (---)|-|
|RSPI2 / SSL0|P57 (63)|PD4 (148)|PL3 (---)|-|
|RSPI2 / SSL1|PD5 (147)|PJ0 (60)|PL4 (---)|-|
|RSPI2 / SSL2|PD6 (145)|PJ1 (59)|PL5 (---)|-|
|RSPI2 / SSL3|PD7 (143)|PJ2 (58)|PL6 (---)|-|

---

## port map order (GPTW) / ポートマップ候補 (GPTW)

### LFQGFP100

|GPTW|FIRST|SECOND|THIRD|FOURTH|FIFTH|SIXTH|
|---|---|---|---|---|---|---|
|GTIOC0A|P23 (25)|P83 (---)|PA5 (65)|PD3 (83)|PE5 (73)|PH6 (---)|
|GTIOC0B|P17 (29)|P81 (---)|PA0 (70)|PD2 (84)|PE2 (76)|PH7 (---)|
|GTIOC1A|P22 (26)|PA2 (68)|PC5 (47)|PD1 (85)|PE4 (74)|PK6 (---)|
|GTIOC1B|P67 (---)|P87 (---)|PC3 (49)|PD0 (86)|PE1 (77)|PK7 (---)|
|GTIOC2A|P21 (27)|P82 (---)|PA1 (69)|PE3 (75)|PL6 (---)|-|
|GTIOC2B|P66 (---)|P86 (---)|PC2 (50)|PE0 (78)|PL7 (---)|-|
|GTIOC3A|PC7 (45)|PE7 (71)|PM6 (---)|-|-|-|
|GTIOC3B|PC6 (46)|PE6 (72)|PM7 (---)|-|-|-|
|GTADSM0|P12 (34)|PH4 (---)|PK4 (---)|PL4 (---)|PM4 (---)|-|
|GTADSM1|P13 (33)|PH5 (---)|PK5 (---)|PL5 (---)|PM5 (---)|-|
|GTETRGA|P15 (31)|PH0 (---)|PK0 (---)|PL0 (---)|PM0 (---)|-|
|GTETRGB|PA6 (64)|PH1 (---)|PK1 (---)|PL1 (---)|PM1 (---)|-|
|GTETRGC|PC4 (48)|PH2 (---)|PK2 (---)|PL2 (---)|PM2 (---)|-|
|GTETRGD|P14 (32)|PH3 (---)|PK3 (---)|PL3 (---)|PM3 (---)|-|

### LFQGFP144

|GPTW|FIRST|SECOND|THIRD|FOURTH|FIFTH|SIXTH|
|---|---|---|---|---|---|---|
|GTIOC0A|P23 (34)|P83 (58)|PA5 (90)|PD3 (123)|PE5 (106)|PH6 (---)|
|GTIOC0B|P17 (38)|P81 (64)|PA0 (97)|PD2 (124)|PE2 (109)|PH7 (---)|
|GTIOC1A|P22 (35)|PA2 (95)|PC5 (62)|PD1 (125)|PE4 (107)|PK6 (---)|
|GTIOC1B|P67 (98)|P87 (39)|PC3 (67)|PD0 (126)|PE1 (110)|PK7 (---)|
|GTIOC2A|P21 (36)|P82 (63)|PA1 (96)|PE3 (108)|PL6 (---)|-|
|GTIOC2B|P66 (99)|P86 (41)|PC2 (70)|PE0 (111)|PL7 (---)|-|
|GTIOC3A|PC7 (60)|PE7 (101)|PM6 (---)|-|-|-|
|GTIOC3B|PC6 (61)|PE6 (102)|PM7 (---)|-|-|-|
|GTADSM0|P12 (45)|PH4 (---)|PK4 (---)|PL4 (---)|PM4 (---)|-|
|GTADSM1|P13 (44)|PH5 (---)|PK5 (---)|PL5 (---)|PM5 (---)|-|
|GTETRGA|P15 (42)|PH0 (---)|PK0 (---)|PL0 (---)|PM0 (---)|-|
|GTETRGB|PA6 (89)|PH1 (---)|PK1 (---)|PL1 (---)|PM1 (---)|-|
|GTETRGC|PC4 (66)|PH2 (---)|PK2 (---)|PL2 (---)|PM2 (---)|-|
|GTETRGD|P14 (43)|PH3 (---)|PK3 (---)|PL3 (---)|PM3 (---)|-|

### LFQGFP176

|GPTW|FIRST|SECOND|THIRD|FOURTH|FIFTH|SIXTH|
|---|---|---|---|---|---|---|
|GTIOC0A|P23 (42)|P83 (74)|PA5 (108)|PD3 (150)|PE5 (130)|PH6 (---)|
|GTIOC0B|P17 (46)|P81 (80)|PA0 (118)|PD2 (154)|PE2 (133)|PH7 (---)|
|GTIOC1A|P22 (43)|PA2 (112)|PC5 (78)|PD1 (156)|PE4 (131)|PK6 (---)|
|GTIOC1B|P67 (120)|P87 (47)|PC3 (83)|PD0 (158)|PE1 (134)|PK7 (---)|
|GTIOC2A|P21 (44)|P82 (79)|PA1 (114)|PE3 (132)|PL6 (---)|-|
|GTIOC2B|P66 (122)|P86 (49)|PC2 (86)|PE0 (135)|PL7 (---)|-|
|GTIOC3A|PC7 (76)|PE7 (125)|PM6 (---)|-|-|-|
|GTIOC3B|PC6 (77)|PE6 (126)|PM7 (---)|-|-|-|
|GTADSM0|P12 (53)|PH4 (---)|PK4 (---)|PL4 (---)|PM4 (---)|-|
|GTADSM1|P13 (52)|PH5 (---)|PK5 (---)|PL5 (---)|PM5 (---)|-|
|GTETRGA|P15 (50)|PH0 (---)|PK0 (---)|PL0 (---)|PM0 (---)|-|
|GTETRGB|PA6 (107)|PH1 (---)|PK1 (---)|PL1 (---)|PM1 (---)|-|
|GTETRGC|PC4 (82)|PH2 (---)|PK2 (---)|PL2 (---)|PM2 (---)|-|
|GTETRGD|P14 (51)|PH3 (---)|PK3 (---)|PL3 (---)|PM3 (---)|-|

---

## port map order (MTU) / ポートマップ候補 (MTU)

### LFQFP100

|MTU|FIRST|SECOND|THIRD|FOURTH|FIFTH|SIXTH|
|---|---|---|---|---|---|---|
|MTIOC0A|P34 (16)|PB3 (57)|-|-|-|-|
|MTIOC0B|P13 (33)|P15 (31)|PA1 (69)|-|-|-|
|MTIOC0C|P32 (18)|PB1 (59)|-|-|-|-|
|MTIOC0D|P33 (17)|PA3 (67)|-|-|-|-|
|MTIOC1A|P20 (28)|PE4 (74)|-|-|-|-|
|MTIOC1B|P21 (27)|PB5 (55)|-|-|-|-|
|MTIOC2A|P26 (22)|PB5 (55)|-|-|-|-|
|MTIOC2B|P27 (21)|PE5 (73)|-|-|-|-|
|MTIOC3A|P14 (32)|P17 (29)|PC1 (51)|PC7 (45)|-|-|
|MTIOC3B|P17 (29)|P22 (26)|P80 (---)|PB7 (53)|PC5 (47)|PE1 (77)|
|MTIOC3C|P16 (30)|P56 (---)|PC0 (52)|PC6 (46)|PJ3 (4)|-|
|MTIOC3D|P16 (30)|P23 (25)|P81 (---)|PC4 (48)|PB6 (54)|PE0 (78)|
|MTIOC4A|P21 (27)|P24 (24)|P82 (---)|PA0 (70)|PB3 (57)|PE2 (76)|
|MTIOC4B|P17 (29)|P30 (20)|P54 (40)|PC2 (50)|PD1 (85)|PE3 (75)|
|MTIOC4C|P25 (23)|P83 (---)|P87 (---)|PB1 (59)|PE1 (77)|PE5 (73)|
|MTIOC4D|P31 (19)|P55 (39)|P86 (---)|PC3 (49)|PD2 (84)|PE4 (74)|
|MTIC5U|P12 (34)|PA4 (66)|PD7 (79)|-|-|-|
|MTIC5V|P11 (---)|PA6 (64)|PD6 (80)|-|-|-|
|MTIC5W|P10 (---)|PB0 (61)|PD5 (81)|-|-|-|
|MTIOC6A|PE7 (71)|PJ1 (---)|-|-|-|-|
|MTIOC6B|PA5 (65)|PJ0 (---)|-|-|-|-|
|MTIOC6C|PE6 (72)|P85 (---)|-|-|-|-|
|MTIOC6D|PA0 (70)|P84 (---)|-|-|-|-|
|MTIOC7A|PA2 (68)|-|-|-|-|-|
|MTIOC7B|PA1 (69)|-|-|-|-|-|
|MTIOC7C|P67 (---)|-|-|-|-|-|
|MTIOC7D|P66 (---)|-|-|-|-|-|
|MTIOC8A|PD6 (80)|-|-|-|-|-|
|MTIOC8B|PD4 (82)|-|-|-|-|-|
|MTIOC8C|PD5 (81)|-|-|-|-|-|
|MTIOC8D|PD3 (83)|-|-|-|-|-|
|MTCLKA|P14 (32)|P24 (24)|PA4 (66)|PC6 (46)|PD5 (81)|-|
|MTCLKB|P15 (31)|P25 (23)|PA6 (64)|PC7 (45)|-|-|
|MTCLKC|P22 (26)|PA1 (69)|PC4 (48)|-|-|-|
|MTCLKD|P23 (25)|PA3 (67)|PC5 (47)|-|-|-|

### LFQFP144

|MTU|FIRST|SECOND|THIRD|FOURTH|FIFTH|SIXTH|
|---|---|---|---|---|---|---|
|MTIOC0A|P34 (25)|PB3 (82)|-|-|-|-|
|MTIOC0B|P13 (44)|P15 (42)|PA1 (96)|-|-|-|
|MTIOC0C|P32 (27)|PB1 (84)|-|-|-|-|
|MTIOC0D|P33 (26)|PA3 (94)|-|-|-|-|
|MTIOC1A|P20 (37)|PE4 (107)|-|-|-|-|
|MTIOC1B|P21 (36)|PB5 (80)|-|-|-|-|
|MTIOC2A|P26 (31)|PB5 (80)|-|-|-|-|
|MTIOC2B|P27 (30)|PE5 (106)|-|-|-|-|
|MTIOC3A|P14 (43)|P17 (38)|PC1 (73)|PC7 (60)|-|-|
|MTIOC3B|P17 (38)|P22 (35)|P80 (65)|PB7 (78)|PC5 (62)|PE1 (110)|
|MTIOC3C|P16 (40)|P56 (50)|PC0 (75)|PC6 (61)|PJ3 (13)|-|
|MTIOC3D|P16 (40)|P23 (34)|P81 (64)|PC4 (66)|PB6 (79)|PE0 (111)|
|MTIOC4A|P21 (36)|P24 (33)|P82 (63)|PA0 (97)|PB3 (82)|PE2 (109)|
|MTIOC4B|P17 (38)|P30 (29)|P54 (52)|PC2 (70)|PD1 (125)|PE3 (108)|
|MTIOC4C|P25 (32)|P83 (58)|P87 (39)|PB1 (84)|PE1 (110)|PE5 (106)|
|MTIOC4D|P31 (28)|P55 (51)|P86 (41)|PC3 (67)|PD2 (124)|PE4 (107)|
|MTIC5U|P12 (45)|PA4 (92)|PD7 (119)|-|-|-|
|MTIC5V|P11 (---)|PA6 (89)|PD6 (120)|-|-|-|
|MTIC5W|P10 (---)|PB0 (87)|PD5 (121)|-|-|-|
|MTIOC6A|PE7 (101)|PJ1 (---)|-|-|-|-|
|MTIOC6B|PA5 (90)|PJ0 (---)|-|-|-|-|
|MTIOC6C|PE6 (102)|P85 (---)|-|-|-|-|
|MTIOC6D|PA0 (97)|P84 (---)|-|-|-|-|
|MTIOC7A|PA2 (95)|-|-|-|-|-|
|MTIOC7B|PA1 (96)|-|-|-|-|-|
|MTIOC7C|P67 (98)|-|-|-|-|-|
|MTIOC7D|P66 (99)|-|-|-|-|-|
|MTIOC8A|PD6 (120)|-|-|-|-|-|
|MTIOC8B|PD4 (122)|-|-|-|-|-|
|MTIOC8C|PD5 (121)|-|-|-|-|-|
|MTIOC8D|PD3 (123)|-|-|-|-|-|
|MTCLKA|P14 (43)|P24 (33)|PA4 (92)|PC6 (61)|PD5 (121)|-|
|MTCLKB|P15 (42)|P25 (32)|PA6 (89)|PC7 (60)|-|-|
|MTCLKC|P22 (35)|PA1 (96)|PC4 (66)|-|-|-|
|MTCLKD|P23 (34)|PA3 (94)|PC5 (62)|-|-|-|

### LFQFP176

|MTU|FIRST|SECOND|THIRD|FOURTH|FIFTH|SIXTH|
|---|---|---|---|---|---|---|
|MTIOC0A|P34 (27)|PB3 (98)|-|-|-|-|
|MTIOC0B|P13 (52)|P15 (50)|PA1 (114)|-|-|-|
|MTIOC0C|P32 (29)|PB1 (100)|-|-|-|-|
|MTIOC0D|P33 (28)|PA3 (110)|-|-|-|-|
|MTIOC1A|P20 (45)|PE4 (131)|-|-|-|-|
|MTIOC1B|P21 (44)|PB5 (96)|-|-|-|-|
|MTIOC2A|P26 (37)|PB5 (96)|-|-|-|-|
|MTIOC2B|P27 (36)|PE5 (130)|-|-|-|-|
|MTIOC3A|P14 (51)|P17 (46)|PC1 (89)|PC7 (76)|-|-|
|MTIOC3B|P17 (46)|P22 (43)|P80 (81)|PB7 (94)|PC5 (78)|PE1 (134)|
|MTIOC3C|P16 (48)|P56 (64)|PC0 (91)|PC6 (77)|PJ3 (13)|-|
|MTIOC3D|P16 (48)|P23 (42)|P81 (80)|PC4 (82)|PB6 (95)|PE0 (135)|
|MTIOC4A|P21 (44)|P24 (40)|P82 (79)|PA0 (118)|PB3 (98)|PE2 (133)|
|MTIOC4B|P17 (46)|P30 (33)|P54 (66)|PC2 (86)|PD1 (156)|PE3 (132)|
|MTIOC4C|P25 (38)|P83 (74)|P87 (47)|PB1 (100)|PE1 (134)|PE5 (130)|
|MTIOC4D|P31 (32)|P55 (65)|P86 (49)|PC3 (83)|PD2 (154)|PE4 (131)|
|MTIC5U|P12 (53)|PA4 (109)|PD7 (143)|-|-|-|
|MTIC5V|P11 (67)|PA6 (107)|PD6 (145)|-|-|-|
|MTIC5W|P10 (68)|PB0 (104)|PD5 (147)|-|-|-|
|MTIOC6A|PE7 (125)|PJ1 (59)|-|-|-|-|
|MTIOC6B|PA5 (108)|PJ0 (69)|-|-|-|-|
|MTIOC6C|PE6 (126)|P85 (61)|-|-|-|-|
|MTIOC6D|PA0 (118)|P84 (62)|-|-|-|-|
|MTIOC7A|PA2 (112)|-|-|-|-|-|
|MTIOC7B|PA1 (114)|-|-|-|-|-|
|MTIOC7C|P67 (120)|-|-|-|-|-|
|MTIOC7D|P66 (122)|-|-|-|-|-|
|MTIOC8A|PD6 (145)|-|-|-|-|-|
|MTIOC8B|PD4 (148)|-|-|-|-|-|
|MTIOC8C|PD5 (147)|-|-|-|-|-|
|MTIOC8D|PD3 (150)|-|-|-|-|-|
|MTCLKA|P14 (51)|P24 (40)|PA4 (109)|PC6 (77)|PD5 (147)|-|
|MTCLKB|P15 (50)|P25 (38)|PA6 (107)|PC7 (76)|-|-|
|MTCLKC|P22 (43)|PA1 (114)|PC4 (82)|-|-|-|
|MTCLKD|P23 (42)|PA3 (110)|PC5 (78)|-|-|-|

---

## port map order (IRQ) / ポートマップ候補 (IRQ)

### LFQFP100

|IRQ|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|IRQ0|P30[DS] (20)|P10 (---)|PD0 (86)|-|-|
|IRQ1|P31[DS] (19)|P11 (---)|PD1 (85)|-|-|
|IRQ2|P32[DS] (18)|P12 (34)|PD2 (84)|-|-|
|IRQ3|P33[DS] (17)|P13 (33)|PD3 (83)|-|-|
|IRQ4|PB1[DS] (59)|P14 (32)|P34 (16)|PD4 (82)|PF5 (---)|
|IRQ5|PA4[DS] (66)|P15 (31)|PD5 (81)|PE5 (73)|-|
|IRQ6|PA3[DS] (67)|P16 (30)|PD6 (80)|PE6 (72)|-|
|IRQ7|PE2[DS] (76)|P17 (29)|PD7 (79)|PE7 (71)|-|
|IRQ8|P40[DS] (95)|P00 (---)|P20 (28)|-|-|
|IRQ9|P41[DS] (93)|P01 (---)|P21 (27)|-|-|
|IRQ10|P42[DS] (92)|P02 (---)|P55 (39)|-|-|
|IRQ11|P43[DS] (91)|P03 (---)|PA1 (69)|-|-|
|IRQ12|P44[DS] (90)|PB0 (61)|PC1 (51)|-|-|
|IRQ13|P45[DS] (89)|P05 (100)|PC6 (46)|-|-|
|IRQ14|P46[DS] (88)|PC0 (52)|PC7 (45)|-|-|
|IRQ15|P47[DS] (87)|P07 (98)|P67 (---)|-|-|

### LFQFP144

|IRQ|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|IRQ0|P30[DS] (29)|P10 (---)|PD0 (126)|-|-|
|IRQ1|P31[DS] (28)|P11 (---)|PD1 (125)|-|-|
|IRQ2|P32[DS] (27)|P12 (45)|PD2 (124)|-|-|
|IRQ3|P33[DS] (26)|P13 (44)|PD3 (123)|-|-|
|IRQ4|PB1[DS] (84)|P14 (43)|P34 (25)|PD4 (122)|PF5 (9)|
|IRQ5|PA4[DS] (92)|P15 (42)|PD5 (121)|PE5 (106)|-|
|IRQ6|PA3[DS] (94)|P16 (40)|PD6 (120)|PE6 (102)|-|
|IRQ7|PE2[DS] (109)|P17 (38)|PD7 (119)|PE7 (101)|-|
|IRQ8|P40[DS] (141)|P00 (8)|P20 (37)|-|-|
|IRQ9|P41[DS] (139)|P01 (7)|P21 (36)|-|-|
|IRQ10|P42[DS] (138)|P02 (6)|P55 (51)|-|-|
|IRQ11|P43[DS] (137)|P03 (4)|PA1 (96)|-|-|
|IRQ12|P44[DS] (136)|PB0 (87)|PC1 (73)|-|-|
|IRQ13|P45[DS] (135)|P05 (2)|PC6 (61)|-|-|
|IRQ14|P46[DS] (134)|PC0 (75)|PC7 (60)|-|-|
|IRQ15|P47[DS] (133)|P07 (144)|P67 (98)|-|-|

### LFQFP176

|IRQ|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|IRQ0|P30[DS] (33)|P10 (56)|PD0 (158)|-|-|
|IRQ1|P31[DS] (32)|P11 (55)|PD1 (156)|-|-|
|IRQ2|P32[DS] (29)|P12 (54)|PD2 (154)|-|-|
|IRQ3|P33[DS] (28)|P13 (53)|PD3 (150)|-|-|
|IRQ4|PB1[DS] (100)|P14 (51)|P34 (27)|PD4 (148)|PF5 (9)|
|IRQ5|PA4[DS] (109)|P15 (50)|PD5 (147)|PE5 (130)|-|
|IRQ6|PA3[DS] (110)|P16 (48)|PD6 (145)|PE6 (126)|-|
|IRQ7|PE2[DS] (133)|P17 (46)|PD7 (143)|PE7 (125)|-|
|IRQ8|P40[DS] (173)|P00 (8)|P20 (45)|-|-|
|IRQ9|P41[DS] (171)|P01 (7)|P21 (44)|-|-|
|IRQ10|P42[DS] (170)|P02 (6)|P55 (66)|-|-|
|IRQ11|P43[DS] (169)|P03 (4)|PA1 (114)|-|-|
|IRQ12|P44[DS] (168)|PB0 (104)|PC1 (89)|-|-|
|IRQ13|P45[DS] (167)|P05 (2)|PC6 (77)|-|-|
|IRQ14|P46[DS] (166)|PC0 (91)|PC7 (76)|-|-|
|IRQ15|P47[DS] (165)|P07 (176)|P67 (120)|-|-|

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
