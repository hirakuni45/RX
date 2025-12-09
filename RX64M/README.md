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

|R5F564MX----|Code Flash|RAM|ECCRAM|StanbyRAM|Data Flash|
|---|:-:|:-:|:-:|:-:|:-:|
|R5F564MLxxxx|4M|512K|32K|8K|64K|
|R5F564MJxxxx|3M|512K|32K|8K|64K|
|R5F564MGxxxx|2.5M|512K|32K|8K|64K|
|R5F564MFxxxx|2M|512K|32K|8K|64K|

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

## Peripheral / ペリフェラル

- [peripheral.hpp](peripheral.hpp?ts=4)

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

## Port map order (IRQ) / ポートマップ候補 (IRQ)

- [port_map_irq.hpp](../RX600/port_map_irq.hpp?ts=4)

### LFQFP100

|IRQ|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|IRQ0|P30 DS (20)|P10 (---)|PD0 (86)|-|-|
|IRQ1|P31 DS (19)|P11 (---)|PD1 (85)|-|-|
|IRQ2|P32 DS (18)|P12 (34)|PD2 (84)|-|-|
|IRQ3|P33 DS (17)|P13 (33)|PD3 (83)|-|-|
|IRQ4|PB1 DS (59)|P14 (32)|P34 (16)|PD4 (82)|PF5 (---)|
|IRQ5|PA4 DS (66)|P15 (31)|PD5 (81)|PE5 (73)|-|
|IRQ6|PA3 DS (67)|P16 (30)|PD6 (80)|PE6 (72)|-|
|IRQ7|PE2 DS (76)|P17 (29)|PD7 (79)|PE7 (71)|-|
|IRQ8|P40 DS (95)|P00 (---)|P20 (28)|-|-|
|IRQ9|P41 DS (93)|P01 (---)|P21 (27)|-|-|
|IRQ10|P42 DS (92)|P02 (---)|P55 (39)|-|-|
|IRQ11|P43 DS (91)|P03 (---)|PA1 (69)|-|-|
|IRQ12|P44 DS (90)|PB0 (61)|PC1 (51)|-|-|
|IRQ13|P45 DS (89)|P05 (100)|PC6 (46)|-|-|
|IRQ14|P46 DS (88)|PC0 (52)|PC7 (45)|-|-|
|IRQ15|P47 DS (87)|P07 (98)|P67 (---)|-|-|

### LFQFP144

|IRQ|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|IRQ0|P30 DS (29)|P10 (---)|PD0 (126)|-|-|
|IRQ1|P31 DS (28)|P11 (---)|PD1 (125)|-|-|
|IRQ2|P32 DS (27)|P12 (45)|PD2 (124)|-|-|
|IRQ3|P33 DS (26)|P13 (44)|PD3 (123)|-|-|
|IRQ4|PB1 DS (84)|P14 (43)|P34 (25)|PD4 (122)|PF5 (9)|
|IRQ5|PA4 DS (92)|P15 (42)|PD5 (121)|PE5 (106)|-|
|IRQ6|PA3 DS (94)|P16 (40)|PD6 (120)|PE6 (102)|-|
|IRQ7|PE2 DS (109)|P17 (38)|PD7 (119)|PE7 (101)|-|
|IRQ8|P40 DS (141)|P00 (8)|P20 (37)|-|-|
|IRQ9|P41 DS (139)|P01 (7)|P21 (36)|-|-|
|IRQ10|P42 DS (138)|P02 (6)|P55 (51)|-|-|
|IRQ11|P43 DS (137)|P03 (4)|PA1 (96)|-|-|
|IRQ12|P44 DS (136)|PB0 (87)|PC1 (73)|-|-|
|IRQ13|P45 DS (135)|P05 (2)|PC6 (61)|-|-|
|IRQ14|P46 DS (134)|PC0 (75)|PC7 (60)|-|-|
|IRQ15|P47 DS (133)|P07 (144)|P67 (98)|-|-|

### LFQFP176

|IRQ|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|IRQ0|P30 DS (33)|P10 (56)|PD0 (158)|-|-|
|IRQ1|P31 DS (32)|P11 (55)|PD1 (156)|-|-|
|IRQ2|P32 DS (29)|P12 (54)|PD2 (154)|-|-|
|IRQ3|P33 DS (28)|P13 (53)|PD3 (150)|-|-|
|IRQ4|PB1 DS (100)|P14 (51)|P34 (27)|PD4 (148)|PF5 (9)|
|IRQ5|PA4 DS (109)|P15 (50)|PD5 (147)|PE5 (130)|-|
|IRQ6|PA3 DS (110)|P16 (48)|PD6 (145)|PE6 (126)|-|
|IRQ7|PE2 DS (133)|P17 (46)|PD7 (143)|PE7 (125)|-|
|IRQ8|P40 DS (173)|P00 (8)|P20 (45)|-|-|
|IRQ9|P41 DS (171)|P01 (7)|P21 (44)|-|-|
|IRQ10|P42 DS (170)|P02 (6)|P55 (66)|-|-|
|IRQ11|P43 DS (169)|P03 (4)|PA1 (114)|-|-|
|IRQ12|P44 DS (168)|PB0 (104)|PC1 (89)|-|-|
|IRQ13|P45 DS (167)|P05 (2)|PC6 (77)|-|-|
|IRQ14|P46 DS (166)|PC0 (91)|PC7 (76)|-|-|
|IRQ15|P47 DS (165)|P07 (176)|P67 (120)|-|-|

---

## Port map order / ポートマップ候補

- [port_map.hpp](port_map.hpp?ts=4)

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
|USB0 / VBUS|P16 (30)|-|-|-|
|USB0 / EXICEN|P21 (27)|-|-|-|
|USB0 / VBUSEN|P16 (30)|P24 (24)|P32 (18)|-|
|USB0 / OVRCURA|P14 (32)|-|-|-|
|USB0 / OVRCURB|P16 (30)|P22 (26)|-|-|
|USB0 / ID|P20 (28)|-|-|-|

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
|USB0 / VBUS|P16 (40)|-|-|-|
|USB0 / EXICEN|P21 (36)|-|-|-|
|USB0 / VBUSEN|P16 (40)|P24 (33)|P32 (27)|-|
|USB0 / OVRCURA|P14 (43)|-|-|-|
|USB0 / OVRCURB|P16 (40)|P22 (35)|-|-|
|USB0 / ID|P20 (37)|-|-|-|

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
|USB0 / VBUS|P16 (48)|-|-|-|
|USB0 / EXICEN|P21 (44)|-|-|-|
|USB0 / VBUSEN|P16 (48)|P24 (40)|P32 (29)|-|
|USB0 / OVRCURA|P14 (51)|-|-|-|
|USB0 / OVRCURB|P16 (48)|P22 (43)|-|-|
|USB0 / ID|P20 (45)|-|-|-|

---

## Port map order (GPT) / ポートマップ候補 (GPT)

- [port_map_gpt.hpp](port_map_gpt.hpp?ts=4)

### LFQGFP100

|GPT|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|GTIOC0A|P23 (25)|P83 (---)|PA5 (65)|PD3 (83)|PE5 (73)|
|GTIOC0B|P17 (29)|P81 (---)|PA0 (70)|PD2 (84)|PE2 (76)|
|GTIOC1A|P22 (26)|PC5 (47)|PA2 (68)|PE4 (74)|PD1 (85)|
|GTIOC1B|P67 (---)|P87 (---)|PC3 (49)|PD0 (86)|PE1 (77)|
|GTIOC2A|P21 (27)|P82 (---)|PA1 (69)|PE3 (75)|-|
|GTIOC2B|P66 (---)|P86 (---)|PC2 (50)|PE0 (78)|-|
|GTIOC3A|PC7 (45)|PE7 (71)|-|-|-|
|GTIOC3B|PC6 (46)|PE6 (72)|-|-|-|
|GTETRG|P15 (31)|PA6 (64)|PC4 (48)|-|-|

### LFQGFP144

|GPT|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|GTIOC0A|P23 (34)|P83 (58)|PA5 (90)|PD3 (123)|PE5 (106)|
|GTIOC0B|P17 (38)|P81 (64)|PA0 (97)|PD2 (124)|PE2 (109)|
|GTIOC1A|P22 (35)|PC5 (62)|PA2 (95)|PE4 (107)|PD1 (125)|
|GTIOC1B|P67 (98)|P87 (39)|PC3 (67)|PD0 (126)|PE1 (110)|
|GTIOC2A|P21 (36)|P82 (63)|PA1 (96)|PE3 (108)|-|
|GTIOC2B|P66 (99)|P86 (41)|PC2 (70)|PE0 (111)|-|
|GTIOC3A|PC7 (60)|PE7 (101)|-|-|-|
|GTIOC3B|PC6 (61)|PE6 (102)|-|-|-|
|GTETRG|P15 (42)|PA6 (89)|PC4 (66)|-|-|

### LFQGFP176

|GPT|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|GTIOC0A|P23 (42)|P83 (74)|PA5 (108)|PD3 (150)|PE5 (130)|
|GTIOC0B|P17 (46)|P81 (80)|PA0 (118)|PD2 (154)|PE2 (133)|
|GTIOC1A|P22 (43)|PC5 (78)|PA2 (112)|PE4 (131)|PD1 (156)|
|GTIOC1B|P67 (120)|P87 (47)|PC3 (83)|PD0 (158)|PE1 (134)|
|GTIOC2A|P21 (44)|P82 (79)|PA1 (114)|PE3 (132)|-|
|GTIOC2B|P66 (122)|P86 (49)|PC2 (86)|PE0 (135)|-|
|GTIOC3A|PC7 (76)|PE7 (125)|-|-|-|
|GTIOC3B|PC6 (77)|PE6 (126)|-|-|-|
|GTETRG|P15 (50)|PA6 (107)|PC4 (82)|-|-|

---

## Port map order (MTU) / ポートマップ候補 (MTU)

- [port_map_mtu.hpp](port_map_mtu.hpp?ts=4)

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
|MTIOC6A|PE7 (71)|-|-|-|-|-|
|MTIOC6B|PA5 (65)|-|-|-|-|-|
|MTIOC6C|PE6 (72)|-|-|-|-|-|
|MTIOC6D|PA0 (70)|-|-|-|-|-|
|MTIOC7A|PA2 (68)|-|-|-|-|-|
|MTIOC7B|PA1 (69)|-|-|-|-|-|
|MTIOC7C|P67 (---)|-|-|-|-|-|
|MTIOC7D|P66 (---)|-|-|-|-|-|
|MTIOC8A|PD6 (80)|-|-|-|-|-|
|MTIOC8B|PD4 (82)|-|-|-|-|-|
|MTIOC8C|PD5 (81)|-|-|-|-|-|
|MTIOC8D|PD3 (83)|-|-|-|-|-|
|MTCLKA|P14 (32)|P24 (24)|PA4 (66)|PC6 (46)|-|-|
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
|MTIOC6A|PE7 (101)|-|-|-|-|-|
|MTIOC6B|PA5 (90)|-|-|-|-|-|
|MTIOC6C|PE6 (102)|-|-|-|-|-|
|MTIOC6D|PA0 (97)|-|-|-|-|-|
|MTIOC7A|PA2 (95)|-|-|-|-|-|
|MTIOC7B|PA1 (96)|-|-|-|-|-|
|MTIOC7C|P67 (98)|-|-|-|-|-|
|MTIOC7D|P66 (99)|-|-|-|-|-|
|MTIOC8A|PD6 (120)|-|-|-|-|-|
|MTIOC8B|PD4 (122)|-|-|-|-|-|
|MTIOC8C|PD5 (121)|-|-|-|-|-|
|MTIOC8D|PD3 (123)|-|-|-|-|-|
|MTCLKA|P14 (43)|P24 (33)|PA4 (92)|PC6 (61)|-|-|
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
|MTIOC6A|PE7 (125)|-|-|-|-|-|
|MTIOC6B|PA5 (108)|-|-|-|-|-|
|MTIOC6C|PE6 (126)|-|-|-|-|-|
|MTIOC6D|PA0 (118)|-|-|-|-|-|
|MTIOC7A|PA2 (112)|-|-|-|-|-|
|MTIOC7B|PA1 (114)|-|-|-|-|-|
|MTIOC7C|P67 (120)|-|-|-|-|-|
|MTIOC7D|P66 (122)|-|-|-|-|-|
|MTIOC8A|PD6 (145)|-|-|-|-|-|
|MTIOC8B|PD4 (148)|-|-|-|-|-|
|MTIOC8C|PD5 (147)|-|-|-|-|-|
|MTIOC8D|PD3 (150)|-|-|-|-|-|
|MTCLKA|P14 (51)|P24 (40)|PA4 (109)|PC6 (77)|-|-|
|MTCLKB|P15 (50)|P25 (38)|PA6 (107)|PC7 (76)|-|-|
|MTCLKC|P22 (43)|PA1 (114)|PC4 (82)|-|-|-|
|MTCLKD|P23 (42)|PA3 (110)|PC5 (78)|-|-|-|

---

## Port map order (TPU) / ポートマップ候補 (TPU)

- [port_map_tpu.hpp](port_map_tpu.hpp?ts=4)

### LFQFP100

|TPU|FIRST|SECOND|THIRD|
|---|---|---|---|
|TIOCA0|P86 (---)|PA0 (70)|-|
|TIOCB0|P17 (29)|PA1 (69)|-|
|TIOCC0|P32 (18)|-|-|
|TIOCD0|P33 (17)|PA3 (67)|-|
|TIOCA1|P56 (---)|PA4 (66)|-|
|TIOCB1|P16 (30)|PA5 (65)|-|
|TIOCA2|P87 (---)|PA6 (64)|-|
|TIOCB2|P15 (31)|PA7 (63)|-|
|TIOCA3|P21 (27)|PB0 (61)|-|
|TIOCB3|P20 (28)|PB1 (59)|-|
|TIOCC3|P22 (26)|PB2 (58)|-|
|TIOCD3|P23 (25)|PB3 (57)|-|
|TIOCA4|P25 (23)|PB4 (56)|-|
|TIOCB4|P24 (24)|PB5 (55)|-|
|TIOCA5|P13 (33)|PB6 (54)|-|
|TIOCB5|P14 (32)|PB7 (53)|-|
|TCLKA|P14 (32)|PC2 (50)|-|
|TCLKB|P15 (31)|PA3 (67)|PC3 (49)|
|TCLKC|P16 (30)|PB2 (58)|PC0 (52)|
|TCLKD|P17 (29)|PB3 (57)|PC1 (51)|

### LFQFP144

|TPU|FIRST|SECOND|THIRD|
|---|---|---|---|
|TIOCA0|P86 (41)|PA0 (97)|-|
|TIOCB0|P17 (38)|PA1 (96)|-|
|TIOCC0|P32 (27)|-|-|
|TIOCD0|P33 (26)|PA3 (94)|-|
|TIOCA1|P56 (50)|PA4 (92)|-|
|TIOCB1|P16 (40)|PA5 (90)|-|
|TIOCA2|P87 (39)|PA6 (89)|-|
|TIOCB2|P15 (41)|PA7 (88)|-|
|TIOCA3|P21 (36)|PB0 (87)|-|
|TIOCB3|P20 (37)|PB1 (84)|-|
|TIOCC3|P22 (35)|PB2 (83)|-|
|TIOCD3|P23 (34)|PB3 (82)|-|
|TIOCA4|P25 (32)|PB4 (81)|-|
|TIOCB4|P24 (33)|PB5 (80)|-|
|TIOCA5|P13 (44)|PB6 (79)|-|
|TIOCB5|P14 (43)|PB7 (78)|-|
|TCLKA|P14 (43)|PC2 (70)|-|
|TCLKB|P15 (42)|PA3 (94)|PC3 (67)|
|TCLKC|P16 (40)|PB2 (83)|PC0 (75)|
|TCLKD|P17 (38)|PB3 (82)|PC1 (73)|

### LFQFP176

|TPU|FIRST|SECOND|THIRD|
|---|---|---|---|
|TIOCA0|P86 (49)|PA0 (118)|-|
|TIOCB0|P17 (46)|PA1 (114)|-|
|TIOCC0|P32 (29)|-|-|
|TIOCD0|P33 (28)|PA3 (110)|-|
|TIOCA1|P56 (---)|PA4 (109)|-|
|TIOCB1|P16 (48)|PA5 (108)|-|
|TIOCA2|P87 (47)|PA6 (107)|-|
|TIOCB2|P15 (50)|PA7 (106)|-|
|TIOCA3|P21 (44)|PB0 (104)|-|
|TIOCB3|P20 (45)|PB1 (100)|-|
|TIOCC3|P22 (43)|PB2 (99)|-|
|TIOCD3|P23 (42)|PB3 (98)|-|
|TIOCA4|P25 (38)|PB4 (97)|-|
|TIOCB4|P24 (40)|PB5 (96)|-|
|TIOCA5|P13 (52)|PB6 (95)|-|
|TIOCB5|P14 (51)|PB7 (94)|-|
|TCLKA|P14 (51)|PC2 (86)|-|
|TCLKB|P15 (50)|PA3 (110)|PC3 (83)|
|TCLKC|P16 (48)|PB2 (99)|PC0 (91)|
|TCLKD|P17 (46)|PB3 (98)|PC1 (89)|

---

## Port map order (TMR) / ポートマップ候補 (TMR)

- [port_map_tmr.hpp](../RX63x/port_map_tmr.hpp?ts=4)

### LFQFP100

|TMR|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|TMO0|P22 (26)|PB3 (57)|-|-|
|TMCI0|P01 (---)|P21 (27)|PB1 (59)|-|
|TMRI0|P00 (---)|P20 (28)|PA4 (66)|-|
|TMO1|P17 (29)|P26 (22)|-|-|
|TMCI1|P02 (---)|P12 (34)|P54 (40)|PC4 (48)|
|TMRI1|P24 (24)|PB5 (55)|-|-|
|TMO2|P16 (30)|PC7 (45)|-|-|
|TMCI2|P15 (31)|P31 (19)|PC6 (46)|-|
|TMRI2|P14 (32)|PC5 (47)|-|-|
|TMO3|P13 (33)|P32 (18)|P55 (39)|-|
|TMCI3|P11 (---)|P27 (21)|P34 (16)|PA6 (64)|
|TMRI3|P10 (---)|P30 (20)|P33 (17)|-|

### LFQFP144

|TMR|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|TMO0|P22 (35)|PB3 (82)|-|-|
|TMCI0|P01 (7)|P21 (36)|PB1 (84)|-|
|TMRI0|P00 (8)|P20 (37)|PA4 (92)|-|
|TMO1|P17 (38)|P26 (31)|-|-|
|TMCI1|P02 (6)|P12 (45)|P54 (52)|PC4 (66)|
|TMRI1|P24 (33)|PB5 (80)|-|-|
|TMO2|P16 (40)|PC7 (60)|-|-|
|TMCI2|P15 (42)|P31 (28)|PC6 (61)|-|
|TMRI2|P14 (43)|PC5 (62)|-|-|
|TMO3|P13 (44)|P32 (27)|P55 (51)|-|
|TMCI3|P11 (---)|P27 (30)|P34 (25)|PA6 (89)|
|TMRI3|P10 (---)|P30 (29)|P33 (26)|-|

### LFQFP176

|TMR|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|TMO0|P22 (43)|PB3 (98)|-|-|
|TMCI0|P01 (7)|P21 (44)|PB1 (100)|-|
|TMRI0|P00 (8)|P20 (45)|PA4 (109)|-|
|TMO1|P17 (46)|P26 (37)|-|-|
|TMCI1|P02 (6)|P12 (54)|P54 (67)|PC4 (82)|
|TMRI1|P24 (40)|PB5 (96)|-|-|
|TMO2|P16 (48)|PC7 (76)|-|-|
|TMCI2|P15 (50)|P31 (32)|PC6 (77)|-|
|TMRI2|P14 (51)|PC5 (78)|-|-|
|TMO3|P13 (53)|P32 (29)|P55 (66)|-|
|TMCI3|P11 (55)|P27 (36)|P34 (27)|PA6 (107)|
|TMRI3|P10 (56)|P30 (33)|P33 (28)|-|

---

## Port map order (QSPI) / ポートマップ候補 (QSPI)

- [port_map_qspi.hpp](port_map_qspi.hpp?ts=4)

### LFQFP100

|QSPI|FIRST|SECOND|
|---|---|---|
|QSPCLK|P77 (---)|PD5 (81)|
|QSSL|P76 (---)|PD4 (82)|
|QIO0|PC3 (49)|PD6 (80)|
|QIO1|PC4 (48)|PD7 (79)|
|QIO2|P80 (---)|PD2 (84)|
|QIO3|P81 (---)|PD3 (83)|

### LFQFP144

|QSPI|FIRST|SECOND|
|---|---|---|
|QSPCLK|P77 (68)|PD5 (121)|
|QSSL|P76 (69)|PD4 (122)|
|QIO0|PC3 (67)|PD6 (120)|
|QIO1|PC4 (66)|PD7 (119)|
|QIO2|P80 (65)|PD2 (124)|
|QIO3|P81 (64)|PD3 (123)|

### LFQFP176

|QSPI|FIRST|SECOND|
|---|---|---|
|QSPCLK|P77 (84)|PD5 (147)|
|QSSL|P76 (85)|PD4 (148)|
|QIO0|PC3 (83)|PD6 (145)|
|QIO1|PC4 (82)|PD7 (143)|
|QIO2|P80 (81)|PD2 (154)|
|QIO3|P81 (80)|PD3 (150)|

---

## Port map order (ETHERC0) / ポートマップ候補 (ETHERC0)

- [port_map_ether.hpp](port_map_ether.hpp?ts=4)

### LFQFP100

|ETHERC0|FIRST|SECOND|THIRD|
|---|---|---|---|
|ET0_MDC|P72 (---)|PA4 (66)|-|
|ET0_MDIO|P71 (---)|PA3 (67)|-|
|ET0_CRS|P83 (---)|PB7 (53)|-|
|ET0_RX_DV|PC2 (50)|-|-|
|ET0_EX_OUT|P55 (39)|PA6 (64)|PJ3 (---)|
|ET0_LINKSTA|P34 (16)|P54 (40)|PA5 (65)|
|ET0_ETXD0|P81 (---)|PB5 (55)|-|
|ET0_ETXD1|P82 (---)|PB6 (54)|-|
|ET0_ETXD2|PC5 (47)|-|-|
|ET0_ETXD3|PC6 (46)|-|-|
|ET0_ERXD0|P75 (---)|PB1 (59)|-|
|ET0_ERXD1|P74 (---)|PB0 (61)|-|
|ET0_ERXD2|PC1 (51)|PE4 (74)|-|
|ET0_ERXD3|PC0 (52)|PE3 (75)|-|
|ET0_TX_EN|P80 (---)|PA0 (70)|PB4 (56)|
|ET0_TX_ER|PC3 (49)|-|-|
|ET0_RX_ER|P77 (---)|PB3 (57)|-|
|ET0_TX_CLK|PC4 (48)|-|-|
|ET0_RX_CLK|P76 (---)|PB2 (58)|PE5 (73)|
|ET0_COL|PC7 (45)|-|-|
|ET0_WOL|P73 (---)|PA1 (69)|PA7 (63)|
|REF50CK0|P76 (---)|PB2 (58)|PE5 (73)|
|RMII0_CRS_DV|P83 (---)|PB7 (53)|-|
|RMII0_TXD0|P81 (---)|PB5 (55)|-|
|RMII0_TXD1|P82 (---)|PB6 (54)|-|
|RMII0_RXD0|P75 (---)|PB1 (59)|-|
|RMII0_RXD1|P74 (---)|PB0 (61)|-|
|RMII0_TXD_EN|P80 (---)|PA0 (70)|PB4 (56)|
|RMII0_RX_ER|P77 (---)|PB3 (57)|-|

### LFQFP144

|ETHERC0|FIRST|SECOND|THIRD|
|---|---|---|---|
|ET0_MDC|P72 (85)|PA4 (92)|-|
|ET0_MDIO|P71 (86)|PA3 (94)|-|
|ET0_CRS|P83 (58)|PB7 (78)|-|
|ET0_RX_DV|PC2 (70)|-|-|
|ET0_EX_OUT|P55 (51)|PA6 (89)|PJ3 (13)|
|ET0_LINKSTA|P34 (25)|P54 (52)|PA5 (90)|
|ET0_ETXD0|P81 (64)|PB5 (80)|-|
|ET0_ETXD1|P82 (63)|PB6 (79)|-|
|ET0_ETXD2|PC5 (62)|-|-|
|ET0_ETXD3|PC6 (61)|-|-|
|ET0_ERXD0|P75 (71)|PB1 (84)|-|
|ET0_ERXD1|P74 (72)|PB0 (87)|-|
|ET0_ERXD2|PC1 (73)|PE4 (107)|-|
|ET0_ERXD3|PC0 (75)|PE3 (108)|-|
|ET0_TX_EN|P80 (65)|PA0 (97)|PB4 (81)|
|ET0_TX_ER|PC3 (67)|-|-|
|ET0_RX_ER|P77 (68)|PB3 (82)|-|
|ET0_TX_CLK|PC4 (66)|-|-|
|ET0_RX_CLK|P76 (89)|PB2 (83)|PE5 (106)|
|ET0_COL|PC7 (60)|-|-|
|ET0_WOL|P73 (77)|PA1 (96)|PA7 (88)|
|REF50CK0|P76 (69)|PB2 (83)|PE5 (106)|
|RMII0_CRS_DV|P83 (58)|PB7 (78)|-|
|RMII0_TXD0|P81 (64)|PB5 (80)|-|
|RMII0_TXD1|P82 (63)|PB6 (79)|-|
|RMII0_RXD0|P75 (71)|PB1 (84)|-|
|RMII0_RXD1|P74 (72)|PB0 (87)|-|
|RMII0_TXD_EN|P80 (65)|PA0 (97)|PB4 (81)|
|RMII0_RX_ER|P77 (68)|PB3 (82)|-|

### LFQFP176

|ETHERC0|FIRST|SECOND|THIRD|
|---|---|---|---|
|ET0_MDC|P72 (101)|PA4 (109)|-|
|ET0_MDIO|P71 (102)|PA3 (110)|-|
|ET0_CRS|P83 (74)|PB7 (94)|-|
|ET0_RX_DV|PC2 (86)|-|-|
|ET0_EX_OUT|P55 (65)|PA6 (107)|PJ3 (13)|
|ET0_LINKSTA|P34 (27)|P54 (66)|PA5 (108)|
|ET0_ETXD0|P81 (80)|PB5 (96)|-|
|ET0_ETXD1|P82 (79)|PB6 (95)|-|
|ET0_ETXD2|PC5 (78)|-|-|
|ET0_ETXD3|PC6 (77)|-|-|
|ET0_ERXD0|P75 (87)|PB1 (100)|-|
|ET0_ERXD1|P74 (88)|PB0 (104)|-|
|ET0_ERXD2|PC1 (89)|PE4 (131)|-|
|ET0_ERXD3|PC0 (91)|PE3 (132)|-|
|ET0_TX_EN|P80 (81)|PA0 (118)|PB4 (97)|
|ET0_TX_ER|PC3 (83)|-|-|
|ET0_RX_ER|P77 (84)|PB3 (98)|-|
|ET0_TX_CLK|PC4 (82)|-|-|
|ET0_RX_CLK|P76 (85)|PB2 (99)|PE5 (130)|
|ET0_COL|PC7 (76)|-|-|
|ET0_WOL|P73 (93)|PA1 (114)|PA7 (106)|
|REF50CK0|P76 (85)|PB2 (99)|PE5 (130)|
|RMII0_CRS_DV|P83 (74)|PB7 (94)|-|
|RMII0_TXD0|P81 (80)|PB5 (96)|-|
|RMII0_TXD1|P82 (79)|PB6 (95)|-|
|RMII0_RXD0|P75 (87)|PB1 (100)|-|
|RMII0_RXD1|P74 (88)|PB0 (104)|-|
|RMII0_TXD_EN|P80 (81)|PA0 (118)|PB4 (97)|
|RMII0_RX_ER|P77 (84)|PB3 (98)|-|

---

## Port map order (ETHERC1) / ポートマップ候補 (ETHERC1)

- [port_map_ether.hpp](port_map_ether.hpp?ts=4)

### LFQFP100

|ETHERC0|FIRST|
|---|---|
|ET1_MDC|P31 (19)|
|ET1_MDIO|P30 (20)|
|ET1_CRS|P92 (---)|
|ET1_RX_DV|P90 (---)|
|ET1_EX_OUT|P26 (22)|
|ET1_LINKSTA|P93 (---)|
|ET1_ETXD0|PG3 (---)|
|ET1_ETXD1|PG4 (---)|
|ET1_ETXD2|PG5 (---)|
|ET1_ETXD3|PG6 (---)|
|ET1_ERXD0|P94 (---)|
|ET1_ERXD1|P95 (---)|
|ET1_ERXD2|P96 (---)|
|ET1_ERXD3|P97 (---)|
|ET1_TX_EN|P60 (---)|
|ET1_TX_ER|PG7 (---)|
|ET1_RX_ER|PG1 (---)|
|ET1_TX_CLK|PG2 (---)|
|ET1_RX_CLK|PG0 (---)|
|ET1_COL|P91 (---)|
|ET1_WOL|P27 (21)|
|REF50CK1|PG0 (---)|
|RMII1_CRS_DV|P92 (---)|
|RMII1_TXD0|PG3 (---)|
|RMII1_TXD1|PG4 (---)|
|RMII1_RXD0|P94 (---)|
|RMII1_RXD1|P95 (---)|
|RMII1_TXD_EN|P60 (---)|
|RMII1_RX_ER|PG1 (---)|

### LFQFP144

|ETHERC0|FIRST|
|---|---|
|ET1_MDC|P31 (28)|
|ET1_MDIO|P30 (29)|
|ET1_CRS|P92 (128)|
|ET1_RX_DV|P90 (131)|
|ET1_EX_OUT|P26 (31)|
|ET1_LINKSTA|P93 (127)|
|ET1_ETXD0|PG3 (---)|
|ET1_ETXD1|PG4 (---)|
|ET1_ETXD2|PG5 (---)|
|ET1_ETXD3|PG6 (---)|
|ET1_ERXD0|P94 (---)|
|ET1_ERXD1|P95 (---)|
|ET1_ERXD2|P96 (---)|
|ET1_ERXD3|P97 (---)|
|ET1_TX_EN|P60 (117)|
|ET1_TX_ER|PG7 (---)|
|ET1_RX_ER|PG1 (---)|
|ET1_TX_CLK|PG2 (---)|
|ET1_RX_CLK|PG0 (---)|
|ET1_COL|P91 (129)|
|ET1_WOL|P27 (30)|
|REF50CK1|PG0 (---)|
|RMII1_CRS_DV|P92 (128)|
|RMII1_TXD0|PG3 (---)|
|RMII1_TXD1|PG4 (---)|
|RMII1_RXD0|P94 (---)|
|RMII1_RXD1|P95 (---)|
|RMII1_TXD_EN|P60 (117)|
|RMII1_RX_ER|PG1 (---)|

### LFQFP176

|ETHERC0|FIRST|
|---|---|
|ET1_MDC|P31 (32)|
|ET1_MDIO|P30 (33)|
|ET1_CRS|P92 (160)|
|ET1_RX_DV|P90 (163)|
|ET1_EX_OUT|P26 (37)|
|ET1_LINKSTA|P93 (159)|
|ET1_ETXD0|PG3 (121)|
|ET1_ETXD1|PG4 (119)|
|ET1_ETXD2|PG5 (116)|
|ET1_ETXD3|PG6 (113)|
|ET1_ERXD0|P94 (157)|
|ET1_ERXD1|P95 (155)|
|ET1_ERXD2|P96 (152)|
|ET1_ERXD3|P97 (149)|
|ET1_TX_EN|P60 (141)|
|ET1_TX_ER|PG7 (111)|
|ET1_RX_ER|PG1 (144)|
|ET1_TX_CLK|PG2 (123)|
|ET1_RX_CLK|PG0 (146)|
|ET1_COL|P91 (161)|
|ET1_WOL|P27 (36)|
|REF50CK1|PG0 (146)|
|RMII1_CRS_DV|P92 (160)|
|RMII1_TXD0|PG3 (121)|
|RMII1_TXD1|PG4 (119)|
|RMII1_RXD0|P94 (157)|
|RMII1_RXD1|P95 (155)|
|RMII1_TXD_EN|P60 (141)|
|RMII1_RX_ER|PG1 (144)|

---

## 12 Bits A/D Converter input (S12AD) / 12 ビット A/D コンバーター入力 (S12AD)

- [s12adf.hpp](../RX600/s12adf.hpp?ts=4)

### LFQFP100

|S12AD/ANALOG|Port|
|---|---|
|AN000|P40 (91)|
|AN001|P41 (93)|
|AN002|P42 (92)|
|AN003|P43 (91)|
|AN004|P44 (90)|
|AN005|P45 (89)|
|AN006|P46 (88)|
|AN007|P47 (87)|

|S12AD1/ANALOG|Port|
|---|---|
|AN100|PE2 (76)|
|AN101|PE3 (75)|
|AN102|PE4 (74)|
|AN103|PE5 (73)|
|AN104|PE6 (72)|
|AN105|PE7 (71)|
|AN106|PD6 (80)|
|AN107|PD7 (79)|
|AN108|PD0 (86)|
|AN109|PD1 (85)|
|AN110|PD2 (84)|
|AN111|PD3 (83)|
|AN112|PD4 (82)|
|AN113|PD5 (81)|
|AN114|P90 (---)|
|AN115|P91 (---)|
|AN116|P92 (---)|
|AN117|P93 (---)|
|AN118|P00 (---)|
|AN119|P01 (---)|
|AN120|P02 (---)|

### LFQFP144

|S12AD/ANALOG|Port|
|---|---|
|AN000|P40 (141)|
|AN001|P41 (139)|
|AN002|P42 (138)|
|AN003|P43 (137)|
|AN004|P44 (136)|
|AN005|P45 (135)|
|AN006|P46 (134)|
|AN007|P47 (133)|

|S12AD1/ANALOG|Port|
|---|---|
|AN100|PE2 (109)|
|AN101|PE3 (108)|
|AN102|PE4 (107)|
|AN103|PE5 (106)|
|AN104|PE6 (102)|
|AN105|PE7 (101)|
|AN106|PD6 (120)|
|AN107|PD7 (119)|
|AN108|PD0 (126)|
|AN109|PD1 (125)|
|AN110|PD2 (124)|
|AN111|PD3 (123)|
|AN112|PD4 (122)|
|AN113|PD5 (121)|
|AN114|P90 (131)|
|AN115|P91 (129)|
|AN116|P92 (128)|
|AN117|P93 (127)|
|AN118|P00 (8)|
|AN119|P01 (7)|
|AN120|P02 (6)|

### LFQFP176

|S12AD/ANALOG|Port|
|---|---|
|AN000|P40 (173)|
|AN001|P41 (171)|
|AN002|P42 (170)|
|AN003|P43 (169)|
|AN004|P44 (168)|
|AN005|P45 (167)|
|AN006|P46 (166)|
|AN007|P47 (165)|

|S12AD1/ANALOG|Port|
|---|---|
|AN100|PE2 (133)|
|AN101|PE3 (132)|
|AN102|PE4 (131)|
|AN103|PE5 (130)|
|AN104|PE6 (126)|
|AN105|PE7 (125)|
|AN106|PD6 (145)|
|AN107|PD7 (143)|
|AN108|PD0 (158)|
|AN109|PD1 (156)|
|AN110|PD2 (154)|
|AN111|PD3 (150)|
|AN112|PD4 (148)|
|AN113|PD5 (147)|
|AN114|P90 (163)|
|AN115|P91 (161)|
|AN116|P92 (160)|
|AN117|P93 (159)|
|AN118|P00 (8)|
|AN119|P01 (7)|
|AN120|P02 (6)|

---

## 12 Bits D/A Converter output (R12DA) / 12 ビット D/A コンバーター出力 (R12DA)

- [r12da.hpp](../RX600/r12da.hpp?ts=4)

### LFQFP100

|R12DA/ANALOG|Port|
|---|---|
|DA0|P03 (---)|
|DA1|P05 (100)|

### LFQFP144

|R12DA/ANALOG|Port|
|---|---|
|DA0|P03 (4)|
|DA1|P05 (2)|

### LFQFP176

|R12DA/ANALOG|Port|
|---|---|
|DA0|P03 (4)|
|DA1|P05 (2)|

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
