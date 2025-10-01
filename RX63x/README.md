
## RX631/RX63N features / 特徴

- RXv1 core / RXv1 コア
- Maximum operating frequency 100MHz / 最大動作周波数 100MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 2.7V ～ 3.6V Operation / 動作
- IEEE802.3 Ether-MAC (10/100 Mbps) on board (for RX63N)
- USB2.0 Host, Function (Only FULL Speed 12Mbps, Can't select LOW Speed 1.5Mbps)
- CAN (ISO11898-1)
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 10 Bits A/D / １０ビットＡ／Ｄ変換器
- 10 Bits D/A / １０ビットＤ／Ａ変換器

### Package/パッケージ

|R5F563y---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F563yxxxFC|LFQFP|176|0.50|
|R5F563yxxxBG|LFBGA|176|0.80|
|R5F563yxxxLC|TFLGA|177|0.50|
|R5F563yxxxFB|LFQFP|144|0.50|
|R5F563yxxxLK|TFLGA|145|0.50|
|R5F563yxxxLJ|TFLGA|100|0.65|
|R5F563yxxxFP|LFQFP|100|0.50|
|R5F563yxxxLH|TFLGA|64|0.65|
|R5F563yxxxFM|LFQFP|64|0.50|
|R5F563yxxxFL|LFQFP|48|0.50|

### Ambient operating temperature/動作周囲温度

|R5F563y--X--|degree Celsius|
|---|:-:|
|R5F563yxxDxx|-40 ～ +85℃|
|R5F563yxxGxx|-40 ～ +105℃|

### CAN、DEU、PDC

|R5F563y-X---|CAN|DEU|PDC|
|---|:-:|:-:|:-:|
|R5F563yxHxxx|〇|〇|-|
|R5F563yxDxxx|〇|-|-|
|R5F563yxGxxx|-|〇|-|
|R5F563yxCxxx|-|-|-|
|R5F563yxSxxx|〇|-|〇|
|R5F563yxFxxx|〇|〇|-|

### Memoey size/メモリ容量

|R5F563yX----|Code Flash|RAM|Data Flash|
|---|:-:|:-:|:-:|
|R5F563yFxxxx|2M|256K|32K|
|R5F563yKxxxx|3M|192K|32K|
|R5F563yExxxx|2M|128K|32K|
|R5F563yJxxxx|1.5M|256K|32K|
|R5F563yGxxxx|1.5M|192K|32K|
|R5F563yDxxxx|1.5M|128K|32K|
|R5F563yYxxxx|1M|256K|32K|
|R5F563yWxxxx|1M|192K|32K|
|R5F563yBxxxx|1M|128K|32K|
|R5F563yAxxxx|768K|128K|32K|
|R5F563y8xxxx|512K|128K|32K|
|R5F563y7xxxx|384K|128K|32K|
|R5F563y6xxxx|256K|128K|32K|
|R5F563yPxxxx|512K|64K|32K|
|R5F563yNxxxx|384K|64K|32K|
|R5F563yMxxxx|256K|64K|32K|
|R5F563y0xxxx|0|128K|0|

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|32K|32|2/2048|2|0x??|0/4|

---

## RX631/RX63N Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F563NF|2048K|256K|32K|[R5F563NF.ld](R5F563NF.ld?ts=4)|7168|1024|
|R5F563NE|2048K|128K|32K|[R5F563NE.ld](R5F563NE.ld?ts=4)|7168|1024|

---

## RX631/RX63N Dedicated class / 専用クラス

|Function/機能|Source|Remarks/備考|
|---|---|:-:|
|Peripheral Name/ペリフェラル名|[peripheral.hpp](peripheral.hpp?ts=4)||
|Hardware-specific Definition/ハード固有定義|[board_profile.hpp](board_profile.hpp?ts=4)||
|Operating Frequency Definition/動作周波数定義|[clock_profile.hpp](clock_profile.hpp?ts=4)||
|Power Control/電力制御|[power_mgr.hpp](power_mgr.hpp?ts=4)||
|Port Definition/ポート定義|[port.hpp](port.hpp?ts=4)||
|Interrupt Definition/割り込み定義|[icu.hpp](icu.hpp?ts=4)||
|Interrupt Management/割り込み管理|[icu_mgr.hpp](icu_mgr.hpp?ts=4)||
|Port Mapping/ポートマッピング|[port_map.hpp](port_map.hpp?ts=4)||
|Port Mapping MTU/ポートマッピング MTU|[port_map_mtu.hpp](port_map_mtu.hpp?ts=4)||
|Port Mapping TMR/ポートマッピング TMR|[port_map_tmr.hpp](port_map_tmr.hpp?ts=4)||
|Port Mapping TPU/ポートマッピング TPU|[port_map_tpu.hpp](port_map_tpu.hpp?ts=4)||
|A/D Definition/A/D 定義|[ad.hpp](ad.hpp?ts=4)||
|D/A Definition/D/A 定義|[da.hpp](da.hpp?ts=4)||
|FLASH Definition/FLASH 定義|[flash.hpp](flash.hpp?ts=4)||
|IEB Definition/IEB 定義|[ieb.hpp](ieb.hpp?ts=4)||
|MCK Definition/MCK 定義|[mck.hpp](mck.hpp?ts=4)||
|POE2 Definition/POE2 定義|[poe2.hpp](poe2.hpp?ts=4)||
|RTC Definition/RTC 定義|[rtc.hpp](rtc.hpp?ts=4)||
|A/D Definition/A/D 定義|[s12ad.hpp](s12ad.hpp?ts=4)||
|System Definition/システム定義|[system.hpp](system.hpp?ts=4)||
|System I/O Definition/システム I/O 定義|[system_io.hpp](system_io.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LQFP 100|LQFP 176|
|---|---|---|
|VCL|VCL(5)|VCL(14)|
|Reset Input/リセット入力|RES#(10)|RES#(21)|
|Mode Controle/モード制御|MD/FINED(7)|MD/FINED(18)|
|B/UB|PC7(45)|PC7(76)|
|RXD|P30/RXD1(20)|PF2(31)|
|TXD|P26/TXD1(22)|PF0(35)|
|P35|P35(15)|P35(26)|
|USB_VCC|VCC_USB(35)|VCC_USB(57)|
|USB_VSS|VSS_USB(38)|VSS_USB(60)|
|USB+|USB_DP(37)|USB_DP(59)|
|USB-|USB_DM(36)|USB_DM(58)|
|Power/電源|VCC(14), VCC(60)|VCC(25), VCC(39), VCC(75), VCC(90), VCC(103)|
|Power/電源||VCC(115), VCC(127), VCC(142), VCC(153), VCC(164)|
|GND/接地|VSS(12), VSS(62)|VSS(12), VSS(23), VSS(41), VSS(73), VSS(92)|
|GND/接地||VSS(105), VSS(117), VSS(129), VSS(140), VSS(151), VSS(162)|     
|Analog Power/アナログ電源|AVCC0(97)|AVCC0(175)|
|Analog GND/アナログ接地|AVSS0(99)|AVSS0(1)|
|Analog Refarence L/アナログ基準電源Ｌ|VREFL(3)|VREFL(5)|
|Analog Refarence H/アナログ基準電源Ｈ|VREFH(1)|VREFH(3)|
|Analog Refarence L0/アナログ基準電源Ｌ0|VREFL0(94)|VREFL0(172)|
|Analog Refarence H0/アナログ基準電源Ｈ0|VREFH0(96)|VREFH0(174)|
|VBATT|VBATT(6)|VBATT(15)|
|OSC in|EXTAL(13)|EXTAL(24)|
|OSC out|XTAL(11)|XTAL(22)|
|Sub OSC in|XCIN(8)|XCIN(19)|
|Sub OSC out|XCOUT(9)|XCOUT(20)|

- VCL: 0.1uF/25V

|Mode/モード|B/UB|MD|P35(USB BUS Power Select)|
|---|:---:|:---:|:---:|
|Serial BOOT/シリアルブート|0|0|-|
|USB Boot/USB ブート|1|0|0/1|
|Single Chip/シングルチップ|-|1|-|

---

## peripheral / ペリフェラル

|Peripheral|Function|機能|
|---|---|---|
|LVDA|Voltage Detection Circuit|電圧検出回路|
|MCK|Frequency Measurement Circuit|周波数測定機能|
|MPU|Memory-Protection Unit|メモリプロテクションユニット|
|DMAC0|DMA Controller channel 0|DMA コントローラ・チャネル０|
|DMAC1|DMA Controller channel 1|DMA コントローラ・チャネル１|
|DMAC2|DMA Controller channel 2|DMA コントローラ・チャネル２|
|DMAC3|DMA Controller channel 3|DMA コントローラ・チャネル３|
|DTC|Data Transfer Controller|データトランスファコントローラ|
|EXDMAC0|EXDMA Controller channel 0|EXDMA コントローラ・チャネル０|
|EXDMAC1|EXDMA Controller channel 1|EXDMA コントローラ・チャネル１|
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
|TPU6|16-Bit Timer Pulse Unit 6|16 ビットタイマパルスユニット６|
|TPU7|16-Bit Timer Pulse Unit 7|16 ビットタイマパルスユニット７|
|TPU8|16-Bit Timer Pulse Unit 8|16 ビットタイマパルスユニット８|
|TPU9|16-Bit Timer Pulse Unit 9|16 ビットタイマパルスユニット９|
|TPU10|16-Bit Timer Pulse Unit 10|16 ビットタイマパルスユニット１０|
|TPU11|16-Bit Timer Pulse Unit 11|16 ビットタイマパルスユニット１１|
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
|RTC|Realtime Clock|リアルタイムクロック|
|WDTA|Watchdog Timer|ウォッチドッグタイマ|
|IWDT|Independent Watchdog Timer|独立ウォッチドッグタイマ|
|ETHERC|Ethernet Controller|イーサネットコントローラ|
|EDMAC|DMA Controller for the Ethernet Controller|イーサネットコントローラ用 DMA コントローラ|
|USB0|USB 2.0 FS Host/Function Module 0|USB 2.0 FS ホスト/ファンクションモジュール０|
|USB1|USB 2.0 FS Host/Function Module 1|USB 2.0 FS ホスト/ファンクションモジュール１|
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
|RIIC3|I2C-bus Interface 3|I2C バスインタフェース３|
|CAN0|CAN Module 0|CAN モジュール０|
|CAN1|CAN Module 1|CAN モジュール１|
|CAN2|CAN Module 2|CAN モジュール２|
|RSPI0|Serial Peripheral Interface 0|シリアルペリフェラルインタフェース０|
|RSPI1|Serial Peripheral Interface 1|シリアルペリフェラルインタフェース１|
|RSPI2|Serial Peripheral Interface 2|シリアルペリフェラルインタフェース２|
|IEB|IEBus Controller|IEBus™ コントローラ|
|CRC|CRC Calculator|CRC 演算器|
|PDC|Parallel Data Capture Unit|パラレルデータキャプチャユニット|
|S12AD|12-Bit A/D Converter|12 ビット A/D コンバータ|
|AD|10-Bit A/D Converter|10 ビット A/D コンバータ|
|DA|10-Bit D/A Converter|10 ビット D/A コンバータ|
|TEMPS|Temperature Sensor|温度センサ|

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
|SCI7 / RXD|P92 (---)|-|-|-|
|SCI7 / TXD|P90 (---)|-|-|-|
|SCI7 / SCK|P91 (---)|-|-|-|
|SCI8 / RXD|PC6 (46)|-|-|-|
|SCI8 / TXD|PC7 (45)|-|-|-|
|SCI8 / SCK|PC5 (47)|-|-|-|
|SCI9 / RXD|PB6 (54)|-|-|-|
|SCI9 / TXD|PB7 (53)|-|-|-|
|SCI9 / SCK|PB5 (55)|-|-|-|
|SCI10 / RXD|P81 (---)|-|-|-|
|SCI10 / TXD|P82 (---)|-|-|-|
|SCI10 / SCK|P80 (---)|-|-|-|
|SCI11 / RXD|P76 (---)|-|-|-|
|SCI11 / TXD|P77 (---)|-|-|-|
|SCI11 / SCK|P75 (---)|-|-|-|
|SCI12 / RXD|PE2 (76)|-|-|-|
|SCI12 / TXD|PE1 (77)|-|-|-|
|SCI12 / SCK|PE0 (78)|-|-|-|
|RIIC0 / SCL|P12 (34)|-|-|-|
|RIIC0 / SDA|P13 (33)|-|-|-|
|RIIC1 / SCL|P21 (27)|-|-|-|
|RIIC1 / SDA|P20 (28)|-|-|-|
|RIIC2 / SCL|P16 (30)|-|-|-|
|RIIC2 / SDA|P17 (29)|-|-|-|
|RIIC3 / SCL|PC0 (52)|-|-|-|
|RIIC3 / SDA|PC1 (51)|-|-|-|
|CAN0 / CRX|P33 (17)|PD2 (84)|-|-|
|CAN0 / CTX|P32 (18)|PD1 (85)|-|-|
|CAN1 / CRX|P15 (31)|P55 (39)|-|-|
|CAN1 / CTX|P14 (32)|P54 (40)|-|-|
|CAN2 / CRX|P67 (---)|-|-|-|
|CAN2 / CTX|P66 (---)|-|-|-|
|RSPI0 / RSPCK|PA5 (65)|PB0 (61)|PC5 (47)|-|
|RSPI0 / MOSI|PA6 (64)|P16 (30)|PC6 (46)|-|
|RSPI0 / MISO|PA7 (63)|P17 (29)|PC7 (45)|-|
|RSPI0 / SSL0|PA4 (66)|PC4 (48)|-|-|
|RSPI0 / SSL1|PA0 (70)|PC0 (52)|-|-|
|RSPI0 / SSL2|PA1 (60)|PC1 (51)|-|-|
|RSPI0 / SSL3|PA2 (68)|PC2 (50)|-|-|
|RSPI1 / RSPCK|P27 (21)|PE1 (77)|PE5 (73)|-|
|RSPI1 / MOSI|P26 (22)|PE2 (76)|PE6 (72)|-|
|RSPI1 / MISO|P30 (20)|PE3 (75)|PE7 (71)|-|
|RSPI1 / SSL0|P31 (19)|PE4 (74)|-|-|
|RSPI1 / SSL1|P50 (44)|PE0 (78)|-|-|
|RSPI1 / SSL2|P51 (43)|PE1 (77)|-|-|
|RSPI1 / SSL3|P52 (42)|PE2 (76)|-|-|
|RSPI2 / RSPCK|PD3 (83)|-|-|-|
|RSPI2 / MOSI|PD1 (85)|-|-|-|
|RSPI2 / MISO|PD2 (84)|-|-|-|
|RSPI2 / SSL0|PD4 (82)|-|-|-|
|RSPI2 / SSL1|PD5 (81)|-|-|-|
|RSPI2 / SSL2|PD6 (80)|-|-|-|
|RSPI2 / SSL3|PD7 (79)|-|-|-|

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
|SCI7 / RXD|P92 (128)|-|-|-|
|SCI7 / TXD|P90 (131)|-|-|-|
|SCI7 / SCK|P91 (129)|-|-|-|
|SCI8 / RXD|PC6 (61)|-|-|-|
|SCI8 / TXD|PC7 (60)|-|-|-|
|SCI8 / SCK|PC5 (62)|-|-|-|
|SCI9 / RXD|PB6 (79)|-|-|-|
|SCI9 / TXD|PB7 (78)|-|-|-|
|SCI9 / SCK|PB5 (80)|-|-|-|
|SCI10 / RXD|P81 (64)|-|-|-|
|SCI10 / TXD|P82 (63)|-|-|-|
|SCI10 / SCK|P80 (65)|-|-|-|
|SCI11 / RXD|P76 (69)|-|-|-|
|SCI11 / TXD|P77 (68)|-|-|-|
|SCI11 / SCK|P75 (71)|-|-|-|
|SCI12 / RXD|PE2 (109)|-|-|-|
|SCI12 / TXD|PE1 (110)|-|-|-|
|SCI12 / SCK|PE0 (111)|-|-|-|
|RIIC0 / SCL|P12 (45)|-|-|-|
|RIIC0 / SDA|P13 (44)|-|-|-|
|RIIC1 / SCL|P21 (36)|-|-|-|
|RIIC1 / SDA|P20 (37)|-|-|-|
|RIIC2 / SCL|P16 (40)|-|-|-|
|RIIC2 / SDA|P17 (38)|-|-|-|
|RIIC3 / SCL|PC0 (75)|-|-|-|
|RIIC3 / SDA|PC1 (73)|-|-|-|
|CAN0 / CRX|P33 (26)|PD2 (124)|-|-|
|CAN0 / CTX|P32 (27)|PD1 (125)|-|-|
|CAN1 / CRX|P15 (42)|P55 (51)|-|-|
|CAN1 / CTX|P14 (43)|P54 (52)|-|-|
|CAN2 / CRX|P67 (98)|-|-|-|
|CAN2 / CTX|P66 (99)|-|-|-|
|RSPI0 / RSPCK|PA5 (90)|PB0 (87)|PC5 (62)|-|
|RSPI0 / MOSI|PA6 (89)|P16 (40)|PC6 (61)|-|
|RSPI0 / MISO|PA7 (88)|P17 (38)|PC7 (60)|-|
|RSPI0 / SSL0|PA4 (92)|PC4 (66)|-|-|
|RSPI0 / SSL1|PA0 (97)|PC0 (75)|-|-|
|RSPI0 / SSL2|PA1 (96)|PC1 (73)|-|-|
|RSPI0 / SSL3|PA2 (95)|PC2 (70)|-|-|
|RSPI1 / RSPCK|P27 (30)|PE1 (110)|PE5 (106)|-|
|RSPI1 / MOSI|P26 (31)|PE2 (109)|PE6 (102)|-|
|RSPI1 / MISO|P30 (29)|PE3 (108)|PE7 (101)|-|
|RSPI1 / SSL0|P31 (28)|PE4 (107)|-|-|
|RSPI1 / SSL1|P50 (56)|PE0 (111)|-|-|
|RSPI1 / SSL2|P51 (55)|PE1 (110)|-|-|
|RSPI1 / SSL3|P52 (54)|PE2 (109)|-|-|
|RSPI2 / RSPCK|PD3 (123)|-|-|-|
|RSPI2 / MOSI|PD1 (125)|-|-|-|
|RSPI2 / MISO|PD2 (124)|-|-|-|
|RSPI2 / SSL0|PD4 (122)|-|-|-|
|RSPI2 / SSL1|PD5 (121)|-|-|-|
|RSPI2 / SSL2|PD6 (120)|-|-|-|
|RSPI2 / SSL3|PD7 (119)|-|-|-|

---

## port map order (MTU) / ポートマップ候補 (MTU)

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
|MTIOC3A|P14 (32)|P17 (29)|PC1 (51)|PC7 (45)|-|
|MTIOC3B|P17 (29)|P22 (26)|P80 (---)|PB7 (53)|PC5 (47)|
|MTIOC3C|P16 (30)|P56 (---)|PC0 (52)|PC6 (46)|PJ3 (4)|
|MTIOC3D|P16 (30)|P23 (25)|P81 (---)|PB6 (54)|PC4 (48)|
|MTIOC4A|P24 (24)|P82 (---)|PA0 (70)|PB3 (57)|PE2 (76)|
|MTIOC4B|P30 (20)|P54 (40)|PC2 (50)|PD1 (85)|PE3 (75)|
|MTIOC4C|P25 (23)|P83 (---)|PB1 (59)|PE1 (77)|PE5 (73)|
|MTIOC4D|P31 (19)|P55 (39)|PC3 (49)|PD2 (84)|PE4 (74)|
|MTIC5U|P12 (34)|PA4 (66)|PD7 (79)|-|-|
|MTIC5V|P11 (---)|PA6 (64)|PD6 (80)|-|-|
|MTIC5W|P10 (---)|PB0 (61)|PD5 (81)|-|-|
|MTCLKA|P14 (32)|P24 (24)|PA4 (66)|PC6 (46)|-|
|MTCLKB|P15 (31)|P25 (23)|PA6 (64)|PC7 (45)|-|
|MTCLKC|P22 (26)|PA1 (69)|PC4 (48)|-|-|
|MTCLKD|P23 (25)|PA3 (67)|PC5 (47)|-|-|

### LFQFP144

|MTU|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|MTIOC0A|P34 (25)|PB3 (82)|-|-|-|
|MTIOC0B|P13 (44)|P15 (42)|PA1 (96)|-|-|
|MTIOC0C|P32 (27)|PB1 (84)|-|-|-|
|MTIOC0D|P33 (26)|PA3 (94)|-|-|-|
|MTIOC1A|P20 (37)|PE4 (107)|-|-|-|
|MTIOC1B|P21 (36)|PB5 (80)|-|-|-|
|MTIOC2A|P26 (31)|PB5 (80)|-|-|-|
|MTIOC2B|P27 (30)|PE5 (106)|-|-|-|
|MTIOC3A|P14 (43)|P17 (38)|PC1 (73)|PC7 (60)|-|
|MTIOC3B|P17 (38)|P22 (35)|P80 (65)|PB7 (78)|PC5 (62)|
|MTIOC3C|P16 (40)|P56 (50)|PC0 (75)|PC6 (61)|PJ3 (13)|
|MTIOC3D|P16 (40)|P23 (34)|P81 (64)|PB6 (79)|PC4 (66)|
|MTIOC4A|P24 (33)|P82 (63)|PA0 (97)|PB3 (82)|PE2 (109)|
|MTIOC4B|P30 (29)|P54 (52)|PC2 (70)|PD1 (125)|PE3 (108)|
|MTIOC4C|P25 (32)|P83 (58)|PB1 (84)|PE1 (110)|PE5 (106)|
|MTIOC4D|P31 (28)|P55 (51)|PC3 (67)|PD2 (124)|PE4 (107)|
|MTIC5U|P12 (45)|PA4 (92)|PD7 (119)|-|-|
|MTIC5V|P11 (---)|PA6 (89)|PD6 (120)|-|-|
|MTIC5W|P10 (---)|PB0 (87)|PD5 (121)|-|-|
|MTCLKA|P14 (43)|P24 (33)|PA4 (92)|PC6 (61)|-|
|MTCLKB|P15 (42)|P25 (32)|PA6 (89)|PC7 (60)|-|
|MTCLKC|P22 (35)|PA1 (96)|PC4 (66)|-|-|
|MTCLKD|P23 (34)|PA3 (94)|PC5 (62)|-|-|

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
