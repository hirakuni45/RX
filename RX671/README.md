## RX671 features / 特徴

- RXv3 core / RXv3 コア
- Maximum operating frequency 120MHz / 最大動作周波数 120MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 2.7V ～ 5.5V Operation / 動作
- USB2.0 Full Speed, Host, Function
- CAN (ISO11898-1)
- Serial Sound Interface (SSIE) / シリアルサウンドインタフェース (SSIE)
- SD Host Interface (SDHI) / SD ホストインタフェース (SDHI)
- 12 Bits A/D / １２ビットＡ／Ｄ変換器

### Package/パッケージ

|R5F5671---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F5671xxxLE|TFLGA|145|0.65|
|R5F5671xxxLK|TFLGA|145|0.50|
|R5F5671xxxFB|LFQFP|144|0.50|
|R5F5671xxxFP|LFQFP|100|0.50|
|R5F5671xxxLJ|TFLGA|100|0.65|
|R5F5671xxxFM|LFQFP|64|0.50|
|R5F5671xxxBP|TFBGA|64|0.50|
|R5F5671xxxNE|HWQFN|48|0.50|

### Ambient operating temperature/動作周囲温度

|R5F5671--X--|degree Celsius|
|---|:-:|
|R5F5671xxDxx|-40 ～ +85℃|
|R5F5671xxGxx|-40 ～ +105℃|

### Crypt/暗号

|R5F5671-X---|Crypt|
|---|:-:|
|R5F5671xDxxx|-|
|R5F5671xHxxx|〇|

### Memoey size/メモリ容量

|R5F5671X----|Code Flash|RAM|Data Flash|
|---|:-:|:-:|:-:|
|R5F56719xxxx|1M|384K|8K|
|R5F5671Cxxxx|1.5M|384K|8K|
|R5F5671Exxxx|2M|384K|8K|

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|8K|64|4/64|4|0x??|4|

---

## RX671 Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F5671C|1536K|384K+4K|32K|[R5F5671C.ld](R5F5671C.ld?ts=4)|14336|2048|
|R5F5671E|2048K|384K+4K|32K|[R5F5671E.ld](R5F5671E.ld?ts=4)|14336|2048|

---

## RX671 Dedicated class / 専用クラス

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
|Port Mapping MTU/ポートマッピング MTU|[port_map_mtu.hpp](port_map_mtu.hpp?ts=4)||
|Port Mapping QSPI/ポートマッピング QSPI|[port_map_qspi.hpp](port_map_qspi.hpp?ts=4)||
|Port Mapping TMR/ポートマッピング TMR|[port_map_tmr.hpp](port_map_tmr.hpp?ts=4)||
|Port Mapping TPU/ポートマッピング TPU|[port_map_tpu.hpp](port_map_tpu.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 100|LFQFP 144|
|---|---|---|
|VCL|VCL(5)|VCL(14)|
|Reset Input/リセット入力|RES#(10)|RES#(19)|
|Mode Controle/モード制御|MD/FINED(7)|MD/FINED(16)|
|UB|PC7/UB(45)|PC7/UB(60)|
|EMLE|EMLE(2)|EMLE(10)|
|RXD|P30/RXD1(20)|P30/RXD1(29)|
|TXD|P26/TXD1(22)|P26/TXD1(31)|
|UPSEL|P35/UPSEL(15)|P35/UPSEL(24)|
|USB_VCC|VCC_USB(35)|VCC_USB(46)|
|USB_VSS|VSS_USB(38)|VSS_USB(49)|
|USB+|USB_DP(37)|USB_DP(48)|
|USB-|USB_DM(36)|USB_DM(47)|
|Power/電源|VCC(14), VCC(60)|VCC(23), VCC(59), VCC(74), VCC(91)|
|Power/電源||VCC(103), VCC(118), VCC(132)|
|GND/接地|VSS(12), VSS(62)|VSS(12), VSS(21), VSS(57), VSS(76)|
|GND/接地||VSS(93), VSS(105), VSS(116), VSS(130)|
|Analog Power/アナログ電源|AVCC0(97), AVCC1(1)|AVCC0(143), AVCC1(3)|
|Analog GND/アナログ接地|AVSS0(99), AVSS1(3)|AVSS0(1), AVSS1(5)|
|Analog Refarence L0/アナログ基準電源Ｌ0|VREFL0(94)|VREFL0(140)|
|Analog Refarence H0/アナログ基準電源Ｈ0|VREFH0(96)|VREFH0(142)|
|VBATT|VBATT(6)|VBATT(15)|
|OSC in|EXTAL(13)|EXTAL(22)|
|OSC out|XTAL(11)|XTAL(20)|
|Sub OSC in|XCIN(8)|XCIN(17)|
|Sub OSC out|XCOUT(9)|XCOUT(18)|

- VCL: 0.22uF/25V

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
|VBATT|Battery Backup Function|バッテリバックアップ機能|
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
|ELC|Event Link Controller|イベントリンクコントローラ|
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
|RSCI10|(R)Serial Communications Interface 10|Ｒシリアルコミュニケーションインタフェース１０|
|RSCI11|(R)Serial Communications Interface 11|Ｒシリアルコミュニケーションインタフェース１１|
|RIIC0|I2C-bus Interface 0|I2C バスインタフェース０|
|RIIC1|I2C-bus Interface 1|I2C バスインタフェース１|
|RIIC2|I2C-bus Interface 2|I2C バスインタフェース２|
|RIICHS0|High-Speed I2C-bus Interface|ハイスピード I2C バスインタフェース|
|CAN0|CAN Module 0|CAN モジュール０|
|CAN1|CAN Module 1|CAN モジュール１|
|RSPI0|Serial Peripheral Interface 0|シリアルペリフェラルインタフェース０|
|RSPI1|Serial Peripheral Interface 1|シリアルペリフェラルインタフェース１|
|RSPI2|Serial Peripheral Interface 2|シリアルペリフェラルインタフェース２|
|RSPIA0|Serial Peripheral Interface A|シリアルペリフェラルインタフェースＡ|
|QSPIX|Quad-SPI Memory Interface|クワッド SPI メモリインタフェース|
|CRC|CRC Calculator|CRC 演算器|
|SDHI|SD Host Interface|SD ホストインタフェース|
|SSIE0|Serial Sound Interface|シリアルサウンドインタフェース|
|REMC0|Remote Control Signal Receiver|リモコン信号受信機能|
|CTSU|Capacitive Touch Sensing Unit|静電容量式タッチセンサ|
|TSIP|Trusted Secure IP|Trusted Secure IP|
|S12AD|12-Bit A/D Converter|12 ビット A/D コンバータ|
|S12AD1|12-Bit A/D Converter 1|12 ビット A/D コンバータ１|
|TEMPS|Temperature Sensor|温度センサ|
|DOC|Data Operation Circuit|データ演算回路|
|STBRAM|Standby RAM|スタンバイ RAM|

---

## port map order / ポートマップ候補

### LFQFP100

|Peripheral|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|SCI0 / RXD|P21 (27)|P33 (17)|-|-|
|SCI0 / TXD|P20 (28)|P32 (18)|-|-|
|SCI0 / SCK|P22 (26)|P34 (16)|-|-|
|SCI1 / RXD|P15 (31)|P30 (20)|-|-|
|SCI1 / TXD|P16 (30)|P26 (22)|-|-|
|SCI1 / SCK|P17 (29)|P27 (21)|-|-|
|SCI2 / RXD|P12 (34)|P52 (42)|-|-|
|SCI2 / TXD|P13 (33)|P50 (44)|-|-|
|SCI2 / SCK|P51 (43)|P51 (43)|-|-|
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
|SCI7 / RXD|P92 (---)|P92 (---)|-|-|
|SCI7 / TXD|P90 (---)|P55 (39)|-|-|
|SCI7 / SCK|P91 (---)|P56 (---)|-|-|
|SCI8 / RXD|PC6 (46)|-|-|-|
|SCI8 / TXD|PC7 (45)|-|-|-|
|SCI8 / SCK|PC5 (47)|-|-|-|
|SCI9 / RXD|PB6 (54)|-|-|-|
|SCI9 / TXD|PB7 (53)|-|-|-|
|SCI9 / SCK|PB5 (55)|-|-|-|
|SCI10 / RXD|P81 (---)|P86 (---)|PC6 (46)|-|
|SCI10 / TXD|P82 (---)|P87 (---)|PC7 (45)|-|
|SCI10 / SCK|P80 (---)|P83 (---)|PC5 (47)|-|
|SCI11 / RXD|P76 (---)|PB6 (54)|-|-|
|SCI11 / TXD|P77 (---)|PB7 (53)|-|-|
|SCI11 / SCK|P75 (---)|PB5 (55)|-|-|
|SCI12 / RXD|PE2 (76)|PA2 (68)|-|-|
|SCI12 / TXD|PE1 (77)|PA4 (66)|-|-|
|SCI12 / SCK|PE0 (78)|PA1 (69)|-|-|
|RSCI10 / RXD|P81 (---)|P86 (---)|PC6 (46)|-|
|RSCI10 / TXD|P82 (---)|P87 (---)|PC7 (45)|-|
|RSCI10 / SCK|P80 (---)|P83 (---)|PC5 (47)|-|
|RSCI10 / DE|P80 (---)|PC4 (48)|-|-|
|RSCI11 / RXD|P76 (---)|PB6 (54)|PC0 (52)|-|
|RSCI11 / TXD|P77 (---)|PB7 (53)|PC1 (51)|-|
|RSCI11 / SCK|P75 (---)|PB5 (55)|PB5 (55)|-|
|RSCI11 / DE|P75 (---)|PB4 (56)|-|-|
|RIIC0 / SCL|P12 (34)|-|-|-|
|RIIC0 / SDA|P13 (33)|-|-|-|
|RIIC1 / SCL|P21 (27)|-|-|-|
|RIIC1 / SDA|P20 (28)|-|-|-|
|RIIC2 / SCL|P16 (30)|-|-|-|
|RIIC2 / SDA|P17 (29)|-|-|-|
|RICHS0 / SCLHS|P12 (34)|-|-|-|
|RICHS0 / SDAHS|P13 (33)|-|-|-|
|CAN0 / CRX|P33 (17)|PD2 (84)|-|-|
|CAN0 / CTX|P32 (18)|PD1 (85)|-|-|
|CAN1 / CRX|P15 (31)|P55 (39)|-|-|
|CAN1 / CTX|P14 (32)|P54 (40)|-|-|
|RSPI0 / RSPCK|PA5 (65)|PC5 (47)|-|-|
|RSPI0 / MOSI|PA6 (64)|PC6 (46)|-|-|
|RSPI0 / MISO|PA7 (63)|PC7 (45)|-|-|
|RSPI0 / SSL0|PA4 (66)|PC4 (48)|-|-|
|RSPI0 / SSL1|PA0 (70)|PC0 (52)|-|-|
|RSPI0 / SSL2|PA1 (69)|PC1 (51)|-|-|
|RSPI0 / SSL3|PA2 (68)|PC2 (50)|-|-|
|RSPI1 / RSPCK|P27 (21)|PE5 (73)|-|-|
|RSPI1 / MOSI|P26 (22)|PE6 (72)|-|-|
|RSPI1 / MISO|P30 (20)|PE7 (71)|-|-|
|RSPI1 / SSL0|P31 (19)|PE4 (74)|-|-|
|RSPI1 / SSL1|P50 (44)|PE0 (78)|-|-|
|RSPI1 / SSL2|P51 (43)|PE1 (77)|-|-|
|RSPI1 / SSL3|P52 (42)|PE2 (76)|-|-|
|RSPI2 / RSPCK|P56 (---)|PD3 (83)|-|-|
|RSPI2 / MOSI|P54 (40)|PD1 (85)|-|-|
|RSPI2 / MISO|P55 (39)|PD2 (84)|-|-|
|RSPI2 / SSL0|PD4 (82)|-|-|-|
|RSPI2 / SSL1|PD5 (81)|-|-|-|
|RSPI2 / SSL2|PD6 (80)|-|-|-|
|RSPI2 / SSL3|PD7 (79)|-|-|-|
|RSPIA0 / RSPCK|PA5 (65)|PC5 (47)|-|-|
|RSPIA0 / MOSI|PA6 (64)|PC6 (46)|-|-|
|RSPIA0 / MISO|PA7 (63)|PC7 (45)|-|-|
|RSPIA0 / SSL0|PA4 (66)|PC4 (48)|-|-|
|RSPIA0 / SSL1|PA0 (70)|PC0 (52)|-|-|
|RSPIA0 / SSL2|PA1 (69)|PC1 (51)|-|-|
|RSPIA0 / SSL3|PA2 (68)|PC2 (50)|-|-|
|SSIE0 / AUDIO_CLK|P22 (26)|PC4 (48)|-|-|
|SSIE0 / SSIBCK0|P23 (25)|PC5 (47)|-|-|
|SSIE0 / SSILRCK0|P21 (27)|PC6 (46)|-|-|
|SSIE0 / SSIRXD0|P20 (28)|P53 (41)|-|-|
|SSIE0 / SSITXD0|P17 (29)|PC7 (45)|-|-|

### LFQFP144

|Peripheral|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|SCI0 / RXD|P21 (36)|P33 (26)|-|-|
|SCI0 / TXD|P20 (37)|P32 (27)|-|-|
|SCI0 / SCK|P22 (35)|P34 (25)|-|-|
|SCI1 / RXD|P15 (42)|P30 (29)|-|-|
|SCI1 / TXD|P16 (40)|P26 (31)|-|-|
|SCI1 / SCK|P17 (38)|P27 (30)|-|-|
|SCI2 / RXD|P12 (45)|P52 (54)|-|-|
|SCI2 / TXD|P13 (44)|P50 (56)|-|-|
|SCI2 / SCK|P51 (55)|P51 (55)|-|-|
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
|SCI7 / RXD|P92 (128)|P92 (128)|-|-|
|SCI7 / TXD|P90 (131)|P55 ( 51)|-|-|
|SCI7 / SCK|P91 (129)|P56 ( 50)|-|-|
|SCI8 / RXD|PC6 (61)|-|-|-|
|SCI8 / TXD|PC7 (60)|-|-|-|
|SCI8 / SCK|PC5 (62)|-|-|-|
|SCI9 / RXD|PB6 (79)|-|-|-|
|SCI9 / TXD|PB7 (78)|-|-|-|
|SCI9 / SCK|PB5 (80)|-|-|-|
|SCI10 / RXD|P81 (64)|P86 (41)|PC6 (61)|-|
|SCI10 / TXD|P82 (63)|P87 (39)|PC7 (60)|-|
|SCI10 / SCK|P80 (65)|P83 (58)|PC5 (62)|-|
|SCI11 / RXD|P76 (69)|PB6 (79)|-|-|
|SCI11 / TXD|P77 (68)|PB7 (78)|-|-|
|SCI11 / SCK|P75 (71)|PB5 (80)|-|-|
|SCI12 / RXD|PE2 (109)|PA2 (95)|-|-|
|SCI12 / TXD|PE1 (110)|PA4 (92)|-|-|
|SCI12 / SCK|PE0 (111)|PA1 (96)|-|-|
|RSCI10 / RXD|P81 (64)|P86 (41)|PC6 (61)|-|
|RSCI10 / TXD|P82 (63)|P87 (39)|PC7 (60)|-|
|RSCI10 / SCK|P80 (65)|P83 (58)|PC5 (62)|-|
|RSCI10 / DE|P80 (65)|PC4 (66)|-|-|
|RSCI11 / RXD|P76 (69)|PB6 (79)|PC0 (75)|-|
|RSCI11 / TXD|P77 (68)|PB7 (78)|PC1 (73)|-|
|RSCI11 / SCK|P75 (71)|PB5 (80)|PB5 (80)|-|
|RSCI11 / DE|P75 (71)|PB4 (81)|-|-|
|RIIC0 / SCL|P12 (45)|-|-|-|
|RIIC0 / SDA|P13 (44)|-|-|-|
|RIIC1 / SCL|P21 (36)|-|-|-|
|RIIC1 / SDA|P20 (37)|-|-|-|
|RIIC2 / SCL|P16 (40)|-|-|-|
|RIIC2 / SDA|P17 (38)|-|-|-|
|RICHS0 / SCLHS|P12 (45)|-|-|-|
|RICHS0 / SDAHS|P13 (44)|-|-|-|
|CAN0 / CRX|P33 (26)|PD2 (124)|-|-|
|CAN0 / CTX|P32 (27)|PD1 (125)|-|-|
|CAN1 / CRX|P15 (42)|P55 (51)|-|-|
|CAN1 / CTX|P14 (43)|P54 (52)|-|-|
|RSPI0 / RSPCK|PA5 (90)|PC5 (62)|-|-|
|RSPI0 / MOSI|PA6 (89)|PC6 (61)|-|-|
|RSPI0 / MISO|PA7 (88)|PC7 (60)|-|-|
|RSPI0 / SSL0|PA4 (92)|PC4 (66)|-|-|
|RSPI0 / SSL1|PA0 (97)|PC0 (75)|-|-|
|RSPI0 / SSL2|PA1 (96)|PC1 (73)|-|-|
|RSPI0 / SSL3|PA2 (95)|PC2 (70)|-|-|
|RSPI1 / RSPCK|P27 (30)|PE5 (106)|-|-|
|RSPI1 / MOSI|P26 (31)|PE6 (102)|-|-|
|RSPI1 / MISO|P30 (29)|PE7 (101)|-|-|
|RSPI1 / SSL0|P31 (28)|PE4 (107)|-|-|
|RSPI1 / SSL1|P50 (56)|PE0 (111)|-|-|
|RSPI1 / SSL2|P51 (55)|PE1 (110)|-|-|
|RSPI1 / SSL3|P52 (54)|PE2 (109)|-|-|
|RSPI2 / RSPCK|P56 (50)|PD3 (123)|-|-|
|RSPI2 / MOSI|P54 (52)|PD1 (125)|-|-|
|RSPI2 / MISO|P55 (51)|PD2 (124)|-|-|
|RSPI2 / SSL0|PD4 (122)|-|-|-|
|RSPI2 / SSL1|PD5 (121)|-|-|-|
|RSPI2 / SSL2|PD6 (120)|-|-|-|
|RSPI2 / SSL3|PD7 (119)|-|-|-|
|RSPIA0 / RSPCK|PA5 (90)|PC5 (62)|-|-|
|RSPIA0 / MOSI|PA6 (89)|PC6 (61)|-|-|
|RSPIA0 / MISO|PA7 (88)|PC7 (60)|-|-|
|RSPIA0 / SSL0|PA4 (92)|PC4 (66)|-|-|
|RSPIA0 / SSL1|PA0 (97)|PC0 (75)|-|-|
|RSPIA0 / SSL2|PA1 (96)|PC1 (73)|-|-|
|RSPIA0 / SSL3|PA2 (95)|PC2 (70)|-|-|
|SSIE0 / AUDIO_CLK|P22 (35)|PC4 (66)|-|-|
|SSIE0 / SSIBCK0|P23 (34)|PC5 (62)|-|-|
|SSIE0 / SSILRCK0|P21 (36)|PC6 (61)|-|-|
|SSIE0 / SSIRXD0|P20 (37)|P53 (53)|-|-|
|SSIE0 / SSITXD0|P17 (38)|PC7 (60)|-|-|

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
|MTIOC3D|P16 (30)|P23 (25)|P81 (---)|PB6 (54)|PC4 (48)|PE0 (78)|
|MTIOC4A|P21 (27)|P24 (24)|P82 (---)|PA0 (70)|PB3 (57)|PE2 (76)|
|MTIOC4B|P17 (29)|P30 (20)|P54 (40)|PC2 (50)|PD1 (85)|PE3 (75)|
|MTIOC4C|P25 (23)|P83 (---)|P87 (---)|PB1 (59)|PE1 (77)|PE5 (73)|
|MTIOC4D|P31 (19)|P55 (39)|P86 (---)|PC3 (49)|PD2 (84)|PE4 (74)|
|MTIC5U|P12 (34)|PA4 (66)|PD7 (79)|-|-|-|
|MTIC5V|PA6 (64)|PD6 (80)|-|-|-|-|
|MTIC5W|PB0 (61)|PD5 (81)|-|-|-|-|
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
|MTIOC3D|P16 (40)|P23 (34)|P81 (64)|PB6 (79)|PC4 (66)|PE0 (111)|
|MTIOC4A|P21 (36)|P24 (33)|P82 (63)|PA0 (97)|PB3 (82)|PE2 (109)|
|MTIOC4B|P17 (38)|P30 (29)|P54 (52)|PC2 (70)|PD1 (125)|PE3 (108)|
|MTIOC4C|P25 (32)|P83 (58)|P87 (39)|PB1 (84)|PE1 (110)|PE5 (106)|
|MTIOC4D|P31 (28)|P55 (51)|P86 (41)|PC3 (67)|PD2 (124)|PE4 (107)|
|MTIC5U|P12 (45)|PA4 (92)|PD7 (119)|-|-|-|
|MTIC5V|PA6 (89)|PD6 (120)|-|-|-|-|
|MTIC5W|PB0 (87)|PD5 (121)|-|-|-|-|
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
