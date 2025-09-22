## RX64M features / 特徴

- RXv2 core / RXv2 コア
- Maximum operating frequency 120MHz / 最大動作周波数 120MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 2.7V ～ 3.6V Operation / 動作
- IEEE1588 Ether-MAC (10/100 Mbps)
- USB2.0 Full Speed, Host, Function
- CAN (ISO11898-1)
- Serial Sound Interface (SSI) / シリアルサウンドインタフェース (SSI)
- SD Host Interface/Optional (SDHI) / SD ホストインタフェース/オプション (SDHI)
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 12 Bits D/A / １２ビットＤ／Ａ変換器

### Package/パッケージ

|R5F564M---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F564MxxxFC|LFQFP|176|0.50|
|R5F564MxxxBG|LFBGA|176|0.80|
|R5F564MxxxLC|TFLGA|177|0.50|
|R5F564MxxxFB|LFQFP|144|0.50|
|R5F564MxxxLK|TFLGA|145|0.50|
|R5F564MxxxFP|LFQFP|100|0.50|
|R5F564MxxxLJ|TFLGA|100|0.65|

### Ambient operating temperature/動作周囲温度

|R5F564M--X--|degree Celsius|
|---|:-:|
|R5F564MxxDxx|-40 ～ +85℃|
|R5F564MxxGxx|-40 ～ +105℃|

### Crypt/暗号、SDHI

|R5F564M-X---|Crypt|SDHI|
|---|:-:|:-:|
|R5F564MxDxxx|-|〇|
|R5F564MxHxxx|〇|〇|
|R5F564MxCxxx|-|-|
|R5F564MxGxxx|〇|-|

### Memoey size/メモリ容量

|R5F564MX----|Code Flash|RAM|Data Flash|
|---|:-:|:-:|:-:|
|R5F564MLxxxx|4M|512K+32K|64K|
|R5F564MJxxxx|3M|512K+32K|64K|
|R5F564MGxxxx|2.5M|512K+32K|64K|
|R5F564MFxxxx|2M|512K+32K|64K|

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|64K|64|4/64|4|0x??|4|

---

## RX64M Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F564MLxxxx|4096K|512K+32K|64K|[R5F564ML.ld](R5F564ML.ld?ts=4)|6144|2048|
|R5F564MJxxxx|3072K|512K+32K|64K|[R5F564MJ.ld](R5F564MJ.ld?ts=4)|6144|2048|
|R5F564MGxxxx|2560K|512K+32K|64K|[R5F564MG.ld](R5F564MG.ld?ts=4)|6144|2048|
|R5F564MFxxxx|2048K|512K+32K|64K|[R5F564MF.ld](R5F564MF.ld?ts=4)|6144|2048|

---

## RX64M Dedicated class / 専用クラス

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
|Port Mapping ETHER/ポートマッピング ETHER|[port_map_ether.hpp](port_map_ether.hpp?ts=4)||
|Port Mapping GPT/ポートマッピング GPT|[port_map_gpt.hpp](port_map_gpt.hpp?ts=4)||
|Port Mapping MTU/ポートマッピング MTU|[port_map_mtu.hpp](port_map_mtu.hpp?ts=4)||
|Port Mapping QSPI/ポートマッピング QSPI|[port_map_qspi.hpp](port_map_qspi.hpp?ts=4)||
|Port Mapping TPU/ポートマッピング TPU|[port_map_tpu.hpp](port_map_tpu.hpp?ts=4)||
|POE3 Definition/POE3 定義|[poe3.hpp](poe3.hpp?ts=4)||
|A/D Definition/A/D 定義|[s12adc.hpp](s12adc.hpp?ts=4)||

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

- VCL: 0.1uF/25V

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
|GPT0|General PWM Timer 0|汎用 PWM タイマ０|
|GPT1|General PWM Timer 1|汎用 PWM タイマ１|
|GPT2|General PWM Timer 2|汎用 PWM タイマ２|
|GPT3|General PWM Timer 3|汎用 PWM タイマ３|
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
|ETHERC1|Ethernet Controller 1|イーサネットコントローラ１|
|EPTPC|PTP Module for the Ethernet Controller|イーサネットコントローラ用 PTP コントローラ|
|EPTPC0|PTP Module for the Ethernet Controller 0|イーサネットコントローラ用 PTP コントローラ０|
|EPTPC1|PTP Module for the Ethernet Controller 1|イーサネットコントローラ用 PTP コントローラ１|
|EDMAC0|DMA Controller for the Ethernet Controller 0|イーサネットコントローラ用 DMA コントローラ０|
|EDMAC1|DMA Controller for the Ethernet Controller 1|イーサネットコントローラ用 DMA コントローラ１|
|PTPEDMAC|PTP Ethernet DMA|PTP イーサネット DMA|
|USB0|USB 2.0 FS Host/Function Module 0|USB 2.0 FS ホスト/ファンクションモジュール０|
|USBA|USB 2.0 High-Speed Host/Function Module|USB 2.0 High-Speed ホスト/ファンクションモジュール|
|SCI0|Serial Communications Interface 0|シリアルコミュニケーションインタフェース０|
|SCI1|Serial Communications Interface 1|シリアルコミュニケーションインタフェース１|
|SCI2|Serial Communications Interface 2|シリアルコミュニケーションインタフェース２|
|SCI3|Serial Communications Interface 3|シリアルコミュニケーションインタフェース３|
|SCI4|Serial Communications Interface 4|シリアルコミュニケーションインタフェース４|
|SCI5|Serial Communications Interface 5|シリアルコミュニケーションインタフェース５|
|SCI6|Serial Communications Interface 6|シリアルコミュニケーションインタフェース６|
|SCI7|Serial Communications Interface 7|シリアルコミュニケーションインタフェース７|
|SCIF8|FIFO Embedded Serial Communications Interface 8|FIFO 内臓シリアルコミュニケーションインターフェース８|
|SCIF9|FIFO Embedded Serial Communications Interface 9|FIFO 内臓シリアルコミュニケーションインターフェース９|
|SCIF10|FIFO Embedded Serial Communications Interface 10|FIFO 内臓シリアルコミュニケーションインターフェース１０|
|SCIF11|FIFO Embedded Serial Communications Interface 11|FIFO 内臓シリアルコミュニケーションインターフェース１１|
|SCI12|Serial Communications Interface 12|シリアルコミュニケーションインタフェース１２|
|RIIC0|I2C-bus Interface 0|I2C バスインタフェース０|
|RIIC2|I2C-bus Interface 2|I2C バスインタフェース２|
|CAN0|CAN Module 0|CAN モジュール０|
|CAN1|CAN Module 1|CAN モジュール１|
|CAN2|CAN Module 2|CAN モジュール２|
|RSPI0|Serial Peripheral Interface 0|シリアルペリフェラルインタフェース０|
|QSPI|Quad-SPI Memory Interface|クワッド SPI メモリインタフェース|
|CRC|CRC Calculator|CRC 演算器|
|SSI0|Serial Sound Interface 0|シリアルサウンドインタフェース０|
|SSI1|Serial Sound Interface 1|シリアルサウンドインタフェース１|
|SDHI|SD Host Interface|SD ホストインタフェース|
|MMCIF|MultiMediaCard Interface|マルチメディアカードインタフェース|
|PDC|Parallel Data Capture Unit|パラレルデータキャプチャユニット|
|S12AD|12-Bit A/D Converter|12 ビット A/D コンバータ|
|S12AD1|12-Bit A/D Converter 1|12 ビット A/D コンバータ１|
|R12DA|12-Bit D/A Converter|12 ビット D/A コンバータ|
|TEMPS|Temperature Sensor|温度センサ|
|DOC|Data Operation Circuit|データ演算回路|
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
|SCI7 / RXD|P92 (---)|-|-|-|
|SCI7 / TXD|P90 (---)|-|-|-|
|SCI7 / SCK|P91 (---)|-|-|-|
|SCIF8 / RXD|PC6 (46)|-|-|-|
|SCIF8 / TXD|PC7 (45)|-|-|-|
|SCIF8 / SCK|PC5 (47)|-|-|-|
|SCIF9 / RXD|PB6 (54)|-|-|-|
|SCIF9 / TXD|PB7 (53)|-|-|-|
|SCIF9 / SCK|PB5 (55)|-|-|-|
|SCIF10 / RXD|P81 (---)|P86 (---)|-|-|
|SCIF10 / TXD|P82 (---)|P87 (---)|-|-|
|SCIF10 / SCK|P80 (---)|P83 (---)|-|-|
|SCIF11 / RXD|P76 (---)|-|-|-|
|SCIF11 / TXD|P77 (---)|-|-|-|
|SCIF11 / SCK|P75 (---)|-|-|-|
|SCI12 / RXD|PE2 (76)|-|-|-|
|SCI12 / TXD|PE1 (77)|-|-|-|
|SCI12 / SCK|PE0 (78)|-|-|-|
|RIIC0 / SCL|P12 (34)|-|-|-|
|RIIC0 / SDA|P13 (33)|-|-|-|
|RIIC2 / SCL|P16 (30)|-|-|-|
|RIIC2 / SDA|P17 (29)|-|-|-|
|CAN0 / CRX|P33 (17)|PD2 (84)|-|-|
|CAN0 / CTX|P32 (18)|PD1 (85)|-|-|
|CAN1 / CRX|P15 (31)|P55 (39)|-|-|
|CAN1 / CTX|P14 (32)|P54 (40)|-|-|
|CAN2 / CRX|P67 (---)|--|-|-|
|CAN2 / CTX|P66 (---)|--|-|-|
|RSPI0 / RSPCK|PA5 (65)|PC5 (47)|-|-|
|RSPI0 / MOSI|PA6 (64)|PC6 (46)|-|-|
|RSPI0 / MISO|PA7 (63)|PC7 (45)|-|-|
|RSPI0 / SSL0|PA4 (66)|PC4 (48)|-|-|
|RSPI0 / SSL1|PA0 (70)|PC0 (52)|-|-|
|RSPI0 / SSL2|PA1 (69)|PC1 (51)|-|-|
|RSPI0 / SSL3|PA2 (68)|PC2 (50)|-|-|
|SSI0 / AUDIO_CLK|P22 (26)|-|-|-|
|SSI0 / SSISCK0|P23 (25)|-|-|-|
|SSI0 / SSIWS0|P21 (27)|-|-|-|
|SSI0 / SSIRXD0|P20 (28)|-|-|-|
|SSI0 / SSITXD0|P17 (29)|-|-|-|
|SSI1 / AUDIO_CLK|P22 (26)|-|-|-|
|SSI1 / SSISCK1|P24 (25)|-|-|-|
|SSI1 / SSIWS1|P15 (31)|-|-|-|
|SSI1 / SSIDATA1|P25 (23)|-|-|-|

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
|SCIF7 / RXD|P92 (128)|-|-|-|
|SCIF7 / TXD|P90 (131)|-|-|-|
|SCIF7 / SCK|P91 (129)|-|-|-|
|SCIF8 / RXD|PC6 (61)|-|-|-|
|SCIF8 / TXD|PC7 (60)|-|-|-|
|SCIF8 / SCK|PC5 (62)|-|-|-|
|SCIF9 / RXD|PB6 (79)|-|-|-|
|SCIF9 / TXD|PB7 (78)|-|-|-|
|SCIF9 / SCK|PB5 (80)|-|-|-|
|SCIF10 / RXD|P81 (64)|P86 (41)|-|-|
|SCIF10 / TXD|P82 (63)|P87 (39)|-|-|
|SCIF10 / SCK|P80 (65)|P83 (58)|-|-|
|SCIF11 / RXD|P76 (69)|-|-|-|
|SCIF11 / TXD|P77 (68)|-|-|-|
|SCIF11 / SCK|P75 (71)|-|-|-|
|SCI12 / RXD|PE2 (109)|-|-|-|
|SCI12 / TXD|PE1 (110)|-|-|-|
|SCI12 / SCK|PE0 (111)|-|-|-|
|RIIC0 / SCL|P12 (45)|-|-|-|
|RIIC0 / SDA|P13 (44)|-|-|-|
|RIIC2 / SCL|P16 (40)|-|-|-|
|RIIC2 / SDA|P17 (38)|-|-|-|
|CAN0 / CRX|P33 (26)|PD2 (124)|-|-|
|CAN0 / CTX|P32 (27)|PD1 (125)|-|-|
|CAN1 / CRX|P15 (42)|P55 (51)|-|-|
|CAN1 / CTX|P14 (43)|P54 (52)|-|-|
|CAN2 / CRX|P67 (98)|-|-|-|
|CAN2 / CTX|P66 (99)|-|-|-|
|RSPI0 / RSPCK|PA5 (90)|PC5 (62)|-|-|
|RSPI0 / MOSI|PA6 (89)|PC6 (61)|-|-|
|RSPI0 / MISO|PA7 (88)|PC7 (60)|-|-|
|RSPI0 / SSL0|PA4 (92)|PC4 (66)|-|-|
|RSPI0 / SSL1|PA0 (97)|PC0 (75)|-|-|
|RSPI0 / SSL2|PA1 (96)|PC1 (73)|-|-|
|RSPI0 / SSL3|PA2 (95)|PC2 (70)|-|-|
|SSI0 / AUDIO_CLK|P22 (35)|-|-|-|
|SSI0 / SSISCK0|P23 (34)|-|-|-|
|SSI0 / SSIWS0|P21 (36)|-|-|-|
|SSI0 / SSIRXD0|P20 (37)|-|-|-|
|SSI0 / SSITXD0|P17 (38)|-|-|-|
|SSI1 / AUDIO_CLK|P22 (35)|-|-|-|
|SSI1 / SSISCK1|P24 (33)|-|-|-|
|SSI1 / SSIWS1|P15 (42)|-|-|-|
|SSI1 / SSIDATA1|P25 (32)|-|-|-|

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
|SCI7 / RXD|P92 (160)|-|-|-|
|SCI7 / TXD|P90 (163)|-|-|-|
|SCI7 / SCK|P91 (161)|-|-|-|
|SCIF8 / RXD|PC6 (77)|-|-|-|
|SCIF8 / TXD|PC7 (76)|-|-|-|
|SCIF8 / SCK|PC5 (78)|-|-|-|
|SCIF9 / RXD|PB6 (95)|-|-|-|
|SCIF9 / TXD|PB7 (94)|-|-|-|
|SCIF9 / SCK|PB5 (96)|-|-|-|
|SCIF10 / RXD|P81 (80)|P86 (49)|-|-|
|SCIF10 / TXD|P82 (79)|P87 (47)|-|-|
|SCIF10 / SCK|P80 (81)|P83 (74)|-|-|
|SCIF11 / RXD|P76 (85)|-|-|-|
|SCIF11 / TXD|P77 (84)|-|-|-|
|SCIF11 / SCK|P75 (87)|-|-|-|
|SCI12 / RXD|PE2 (133)|-|-|-|
|SCI12 / TXD|PE1 (134)|-|-|-|
|SCI12 / SCK|PE0 (135)|-|-|-|
|RIIC0 / SCL|P12 (53)|-|-|-|
|RIIC0 / SDA|P13 (52)|-|-|-|
|RIIC2 / SCL|P16 (48)|-|-|-|
|RIIC2 / SDA|P17 (46)|-|-|-|
|CAN0 / CRX|P33 (28)|PD2 (154)|-|-|
|CAN0 / CTX|P32 (29)|PD1 (156)|-|-|
|CAN1 / CRX|P15 (50)|P55 (65)|-|-|
|CAN1 / CTX|P14 (51)|P54 (66)|-|-|
|CAN2 / CRX|P67 (120)|-|-|-|
|CAN2 / CTX|P66 (122)|-|-|-|
|RSPI0 / RSPCK|PA5 (108)|PC5 (78)|-|-|
|RSPI0 / MOSI|PA6 (107)|PC6 (77)|-|-|
|RSPI0 / MISO|PA7 (106)|PC7 (76)|-|-|
|RSPI0 / SSL0|PA4 (109)|PC4 (82)|-|-|
|RSPI0 / SSL1|PA0 (118)|PC0 (91)|-|-|
|RSPI0 / SSL2|PA1 (114)|PC1 (89)|-|-|
|RSPI0 / SSL3|PA2 (112)|PC2 (86)|-|-|
|SSI0 / AUDIO_CLK|P22 (43)|-|-|-|
|SSI0 / SSISCK0|P23 (42)|-|-|-|
|SSI0 / SSIWS0|P21 (44)|-|-|-|
|SSI0 / SSIRXD0|P20 (45)|-|-|-|
|SSI0 / SSITXD0|P17 (46)|-|-|-|
|SSI1 / AUDIO_CLK|P22 (43)|-|-|-|
|SSI1 / SSISCK1|P24 (40)|-|-|-|
|SSI1 / SSIWS1|P15 (50)|-|-|-|
|SSI1 / SSIDATA1|P25 (38)|-|-|-|

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
