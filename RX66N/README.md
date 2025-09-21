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
|CAN0|CAN Module 0|CAN インタフェース０|
|CAN1|CAN Module 1|CAN インタフェース１|
|CAN2|CAN Module 2|CAN インタフェース２|
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

## rx_prog Flash Programming / rx_prog フラッシュプログラム

||Support/サポート|operation verification/動作検証|
|-|:-:|:-:|
|[rxprog](../rxprog)|-|-|

---

Translated with www.DeepL.com/Translator (free version)

---

## License

[MIT](../LICENSE)
