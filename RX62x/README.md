
## RX621/RX62N features / 特徴

- RXv1 core / RXv1 コア
- Maximum operating frequency 100MHz / 最大動作周波数 100MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 2.7V ～ 3.6V Operation / 動作
- RMII/MII Ethernet MAC 10/100 Mbps (RX62N)
- USB2.0 Full Speed, Host, Function
- CAN (ISO11898-1)
- 12/10 Bits A/D / １２・１０ビットＡ／Ｄ変換器
- 10 Bits D/A / １０ビットＤ／Ａ変換器

### Package/パッケージ

|R5F562y---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F562yxxxBG|LFBGA|176|0.80|
|R5F562yxxxLE|TFLGA|145|0.65|
|R5F562yxxxFB|LQFP|144|0.50|
|R5F562yxxxFP|LQFP|100|0.50|
|R5F562yxxxLD|TFLGA|85|0.65|

### CAN

|R5F562y-X---|CAN|
|---|:-:|
|R5F563yxAxxx|-|
|R5F563yxBxxx|〇|

### Memoey size/メモリ容量

|R5F562yX----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F562y8xxxx|512K|96K|32K|
|R5F562y7xxxx|384K|64K|32K|
|R5F562y6xxxx|256K|64K|32K|

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|32K|2048|8/2048|8|0x??|0|

---

## RX621/RX62N Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F56218|512K|96K|32K|[R5F56218.ld](R5F56218.ld?ts=4)|1024|512|
|R5F562N8|512K|96K|32K|[R5F562N8.ld](R5F562N8.ld?ts=4)|1024|512|
|R5F562N7|384K|64K|32K|[R5F562N7.ld](R5F562N7.ld?ts=4)|1024|512|

---

## RX621/RX62N Dedicated class / 専用クラス

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
|BUS Definition/BUS 定義|[bus.hpp](bus.hpp?ts=4)||
|MTU2 Definition/MTU2 定義|[mtu2.hpp](mtu2.hpp?ts=4)||
|FLASH Definition/FLASH 定義|[flash.hpp](flash.hpp?ts=4)||
|FLASH I/O Definition/FLASH I/O 定義|[flash_io.hpp](flash_io.hpp?ts=4)||
|LVD Definition/LVD 定義|[lvd.hpp](lvd.hpp?ts=4)||
|POE2 Definition/POE2 定義|[poe2.hpp](poe2.hpp?ts=4)||
|RTC Definition/RTC 定義|[rtc.hpp](rtc.hpp?ts=4)||
|USB Definition/USB 定義|[usb.hpp](usb.hpp?ts=4)||
|WDT Definition/WDT 定義|[wdt.hpp](wdt.hpp?ts=4)||
|10 Bits A/D Definition/10 Bits A/D 定義|[ad.hpp](ad.hpp?ts=4)||
|12 Bits A/D Definition/12 Bits A/D 定義|[s12ad.hpp](s12ad.hpp?ts=4)||
|10 Bits D/A Definition/10 Bits D/A 定義|[da.hpp](da.hpp?ts=4)||
|System Definition/システム定義|[system.hpp](system.hpp?ts=4)||
|System I/O Definition/システム I/O 定義|[system_io.hpp](system_io.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LQFP 144|
|---|---|
|VCL|VCL(14)|
|Reset Input/リセット入力|RES#(19)|
|MD0|MD0(16)|
|MD1|MD1(15)|
|MDE|MDE(13)|
|EMLE|EMLE(10)|
|BSCANP|BSCANP(9)|
|RXD|P30/RXD1(29)|
|TXD|P26/TXD1(31)|
|USB_VCC|VCC_USB(46)|
|USB_VSS|VSS_USB(49)|
|USB+|USB_DP(48)|
|USB-|USB_DM(47)|
|Power/電源|VCC(  3), VCC( 23), VCC( 59), VCC( 74)|
|Power/電源|VCC( 91), VCC(103), VCC(118), VCC(132)|
|GND/接地|VSS(  5), VSS( 12), VSS( 21), VSS( 57)|
|GND/接地|VSS( 76), VSS( 93), VSS(105), VSS(116), VSS(130)|
|PLL Power/PLL 電源|PLLVCC(39)|
|PLL GND/PLL 接地|PLLVSS(41)|
|Analog Power/アナログ電源|AVCC(143)|
|Analog GND/アナログ接地|AVSS(  1)|
|Analog Refarence L/アナログ基準電源Ｌ|VREFL(140)|
|Analog Refarence H/アナログ基準電源Ｈ|VREFH(142)|
|OSC in|EXTAL(22)|
|OSC out|XTAL(20)|
|Sub OSC in|XCIN(17)|
|Sub OSC out|XCOUT(18)|

- VCL: 0.1uF/25V

|Mode/モード|MD0|MD1|
|---|:---:|:---:|
|Serial Boot/シリアルブート|1|0|
|USB Boot/USB ブート|0|1|
|Single Chip/シングルチップ|1|1|

---

## peripheral / ペリフェラル

|Peripheral|Function|機能|
|---|---|---|
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
|MTU6|Multi-Function Timer Pulse Unit 6|マルチファンクションタイマパルスユニット６|
|MTU7|Multi-Function Timer Pulse Unit 7|マルチファンクションタイマパルスユニット７|
|MTU8|Multi-Function Timer Pulse Unit 8|マルチファンクションタイマパルスユニット８|
|MTU9|Multi-Function Timer Pulse Unit 9|マルチファンクションタイマパルスユニット９|
|MTU10|Multi-Function Timer Pulse Unit 10|マルチファンクションタイマパルスユニット１０|
|MTU11|Multi-Function Timer Pulse Unit 11|マルチファンクションタイマパルスユニット１１|
|POE2|Port Output Enable 2|ポートアウトプットイネーブル２|
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
|SCI5|Serial Communications Interface 5|シリアルコミュニケーションインタフェース５|
|SCI6|Serial Communications Interface 6|シリアルコミュニケーションインタフェース６|
|RIIC0|I2C-bus Interface 0|I2C バスインタフェース０|
|RIIC1|I2C-bus Interface 1|I2C バスインタフェース１|
|CAN0|CAN Module 0|CAN モジュール０|
|RSPI0|Serial Peripheral Interface 0|シリアルペリフェラルインタフェース０|
|RSPI1|Serial Peripheral Interface 1|シリアルペリフェラルインタフェース１|
|CRC|CRC Calculator|CRC 演算器|
|S12AD|12-Bit A/D Converter|12 ビット A/D コンバータ|
|AD0|10-Bit A/D Converter 0|10 ビット A/D コンバータ０|
|AD1|10-Bit A/D Converter 1|10 ビット A/D コンバータ１|
|DA|10-Bit D/A Converter|10 ビット D/A コンバータ|

---

## port map order / ポートマップ候補

### LFQFP100

|Peripheral|FIRST|SECOND|
|---|---|---|
|SCI0 / RXD|P21 (27)|-|
|SCI0 / TXD|P20 (28)|-|
|SCI0 / SCK|P22 (26)|-|
|SCI1 / RXD|P30 (20)|PF2 (---)|
|SCI1 / TXD|P26 (22)|PF0 (---)|
|SCI1 / SCK|P27 (21)|PF1 (---)|
|SCI2 / RXD|P12 (34)|P52 (42)|
|SCI2 / TXD|P13 (33)|P50 (44)|
|SCI2 / SCK|P11 (---)|P51 (43)|
|SCI3 / RXD|P16 (30)|P25 (32)|
|SCI3 / TXD|P17 (---)|P23 (34)|
|SCI3 / SCK|P15 (---)|P24 (33)|
|SCI5 / RXD|PC2 (50)|-|
|SCI5 / TXD|PC3 (49)|-|
|SCI5 / SCK|PC1 (51)|-|
|SCI6 / RXD|P01 (---)|P33 (17)|
|SCI6 / TXD|P00 (---)|P32 (18)|
|SCI6 / SCK|P02 (---)|P34 (16)|
|RIIC0 / SCL|P12 (34)|-|
|RIIC0 / SDA|P13 (33)|-|
|RIIC1 / SCL|P21 (27)|-|
|RIIC1 / SDA|P20 (28)|-|
|CAN0 / CRX|P33 (17)|-|
|CAN0 / CTX|P32 (18)|-|
|RSPI0 / RSPCK|PC5 (47)|PA5 (65)|
|RSPI0 / MOSI|PC6 (46)|PA6 (64)|
|RSPI0 / MISO|PC7 (45)|PA7 (63)|
|RSPI0 / SSL0|PC4 (48)|PA4 (66)|
|RSPI0 / SSL1|PC0 (52)|PA0 (70)|
|RSPI0 / SSL2|PC1 (51)|PA1 (69)|
|RSPI0 / SSL3|PC2 (50)|PA2 (68)|
|RSPI1 / RSPCK|P27 (21)|PE5 (73)|
|RSPI1 / MOSI|P26 (22)|PE6 (72)|
|RSPI1 / MISO|P30 (20)|PE7 (71)|
|RSPI1 / SSL0|P31 (19)|PE4 (74)|
|RSPI1 / SSL1|P50 (44)|PE0 (78)|
|RSPI1 / SSL2|P51 (43)|PE1 (77)|
|RSPI1 / SSL3|P52 (42)|PE2 (76)|

### LFQFP144

|Peripheral|FIRST|SECOND|
|---|---|---|
|SCI0 / RXD|P21 (36)|-|
|SCI0 / TXD|P20 (37)|-|
|SCI0 / SCK|P22 (35)|-|
|SCI1 / RXD|P30 (29)|PF2 (---)|
|SCI1 / TXD|P26 (31)|PF0 (---)|
|SCI1 / SCK|P27 (30)|PF1 (---)|
|SCI2 / RXD|P12 (45)|P52 (54)|
|SCI2 / TXD|P13 (44)|P50 (56)|
|SCI2 / SCK|P11 (---)|P51 (55)|
|SCI3 / RXD|P16 (40)|P25 (32)|
|SCI3 / TXD|P17 (38)|P23 (34)|
|SCI3 / SCK|P15 (42)|P24 (33)|
|SCI5 / RXD|PC2 (70)|-|
|SCI5 / TXD|PC3 (67)|-|
|SCI5 / SCK|PC1 (73)|-|
|SCI6 / RXD|P01 (7)|P33 (26)|
|SCI6 / TXD|P00 (8)|P32 (27)|
|SCI6 / SCK|P02 (6)|P34 (25)|
|RIIC0 / SCL|P12 (45)|-|
|RIIC0 / SDA|P13 (44)|-|
|RIIC1 / SCL|P21 (36)|-|
|RIIC1 / SDA|P20 (37)|-|
|CAN0 / CRX|P33 (26)|-|
|CAN0 / CTX|P32 (27)|-|
|RSPI0 / RSPCK|PC5 (62)|PA5 (90)|
|RSPI0 / MOSI|PC6 (61)|PA6 (89)|
|RSPI0 / MISO|PC7 (60)|PA7 (88)|
|RSPI0 / SSL0|PC4 (66)|PA4 (92)|
|RSPI0 / SSL1|PC0 (75)|PA0 (97)|
|RSPI0 / SSL2|PC1 (73)|PA1 (96)|
|RSPI0 / SSL3|PC2 (70)|PA2 (95)|
|RSPI1 / RSPCK|P27 (30)|PE5 (106)|
|RSPI1 / MOSI|P26 (31)|PE6 (102)|
|RSPI1 / MISO|P30 (29)|PE7 (101)|
|RSPI1 / SSL0|P31 (28)|PE4 (107)|
|RSPI1 / SSL1|P50 (56)|PE0 (111)|
|RSPI1 / SSL2|P51 (55)|PE1 (110)|
|RSPI1 / SSL3|P52 (54)|PE2 (109)|

---

## port map order (MTU) / ポートマップ候補 (MTU)

### LFQGFP100

|MTU|FIRST|SECOND|
|---|---|---|
|MTIOC0A|P34 (16)|-|
|MTIOC0B|P15 (---)|-|
|MTIOC0C|P32 (18)|-|
|MTIOC0D|P33 (17)|-|
|MTIOC1A|P20 (28)|-|
|MTIOC1B|P21 (27)|-|
|MTIOC2A|P26 (22)|-|
|MTIOC2B|P27 (21)|-|
|MTIOC3A|P17 (---)|-|
|MTIOC3B|P22 (26)|P80 (---)|
|MTIOC3C|P16 (30)|P56 (---)|
|MTIOC3D|P23 (25)|P81 (---)|
|MTIOC4A|P24 (24)|P82 (---)|
|MTIOC4B|P30 (20)|P54 (40)|
|MTIOC4C|P25 (23)|P83 (---)|
|MTIOC4D|P31 (19)|P55 (39)|
|MTIOC5U|P12 (34)|PD7 (79)|
|MTIOC5V|P11 (---)|PD6 (80)|
|MTIOC5W|P10 (---)|PD5 (81)|
|MTIOC6A|PA0 (70)|-|
|MTIOC6B|PA1 (69)|-|
|MTIOC6C|PA2 (68)|-|
|MTIOC6D|PA3 (67)|-|
|MTIOC7A|PA4 (66)|-|
|MTIOC7B|PA5 (65)|-|
|MTIOC8A|PA6 (64)|-|
|MTIOC8B|PA7 (63)|-|
|MTIOC9A|PB0 (61)|-|
|MTIOC9B|PB2 (58)|-|
|MTIOC9C|PB1 (59)|-|
|MTIOC9D|PB3 (57)|-|
|MTIOC10A|PB4 (56)|-|
|MTIOC10B|PB6 (54)|-|
|MTIOC10C|PB5 (55)|-|
|MTIOC10D|PB7 (53)|-|
|MTIOC11U|PC7 (45)|PD4 (82)|
|MTIOC11V|PC6 (46)|PD3 (83)|
|MTIOC11W|PC5 (47)|PD2 (84)|
|MTCLKA|P24 (24)|PC6 (46)|
|MTCLKB|P25 (23)|PC7 (45)|
|MTCLKC|P22 (26)|PC4 (48)|
|MTCLKD|P23 (25)|PC5 (47)|
|MTCLKE|PC2 (50)|PB4 (56)|
|MTCLKF|PC3 (49)|PB5 (55)|
|MTCLKG|PC0 (52)|PB2 (58)|
|MTCLKH|PC1 (51)|PB3 (57)|

### LFQGFP144

|MTU|FIRST|SECOND|
|---|---|---|
|MTIOC0A|P34 (25)|-|
|MTIOC0B|P15 (42)|-|
|MTIOC0C|P32 (27)|-|
|MTIOC0D|P33 (26)|-|
|MTIOC1A|P20 (37)|-|
|MTIOC1B|P21 (36)|-|
|MTIOC2A|P26 (31)|-|
|MTIOC2B|P27 (30)|-|
|MTIOC3A|P17 (38)|-|
|MTIOC3B|P22 (35)|P80 (65)|
|MTIOC3C|P16 (40)|P56 (50)|
|MTIOC3D|P23 (34)|P81 (64)|
|MTIOC4A|P24 (33)|P82 (63)|
|MTIOC4B|P30 (29)|P54 (52)|
|MTIOC4C|P25 (32)|P83 (58)|
|MTIOC4D|P31 (28)|P55 (51)|
|MTIOC5U|P12 (45)|PD7 (119)|
|MTIOC5V|P11 (---)|PD6 (120)|
|MTIOC5W|P10 (---)|PD5 (121)|
|MTIOC6A|PA0 (97)|-|
|MTIOC6B|PA1 (96)|-|
|MTIOC6C|PA2 (95)|-|
|MTIOC6D|PA3 (94)|-|
|MTIOC7A|PA4 (92)|-|
|MTIOC7B|PA5 (90)|-|
|MTIOC8A|PA6 (89)|-|
|MTIOC8B|PA7 (88)|-|
|MTIOC9A|PB0 (87)|-|
|MTIOC9B|PB2 (83)|-|
|MTIOC9C|PB1 (84)|-|
|MTIOC9D|PB3 (82)|-|
|MTIOC10A|PB4 (81)|-|
|MTIOC10B|PB6 (79)|-|
|MTIOC10C|PB5 (80)|-|
|MTIOC10D|PB7 (78)|-|
|MTIOC11U|PC7 (60)|PD4 (122)|
|MTIOC11V|PC6 (61)|PD3 (123)|
|MTIOC11W|PC5 (62)|PD2 (124)|
|MTCLKA|P24 (33)|PC6 (61)|
|MTCLKB|P25 (32)|PC7 (60)|
|MTCLKC|P22 (35)|PC4 (66)|
|MTCLKD|P23 (34)|PC5 (62)|
|MTCLKE|PC2 (70)|PB4 (81)|
|MTCLKF|PC3 (67)|PB5 (80)|
|MTCLKG|PC0 (75)|PB2 (83)|
|MTCLKH|PC1 (73)|PB3 (82)|

---

## port map order (IRQ) / ポートマップ候補 (IRQ)

### LFQGFP100

|IRQ|FIRST|SECOND|
|---|---|---|
|IRQ0|P30 (20)|P10 (---)|
|IRQ1|P31 (19)|P11 (---)|
|IRQ2|P32 (18)|P12 (34)|
|IRQ3|P33 (17)|P13 (33)|
|IRQ4|P34 (16)|P14 (32)|
|IRQ5|PE5 (73)|P15 (---)|
|IRQ6|PE6 (72)|P16 (30)|
|IRQ7|PE7 (71)|P17 (---)|
|IRQ8|P00 (---)|P40 (95)|
|IRQ9|P01 (---)|P41 (93)|
|IRQ10|P02 (---)|P42 (92)|
|IRQ11|P03 (---)|P43 (91)|
|IRQ13|P05 (100)|P45 (89)|
|IRQ15|P07 (98)|P47 (87)|

### LFQGFP144

|IRQ|FIRST|SECOND|
|---|---|---|
|IRQ0|P30 (29)|P10 (---)|
|IRQ1|P31 (28)|P11 (---)|
|IRQ2|P32 (27)|P12 (45)|
|IRQ3|P33 (26)|P13 (44)|
|IRQ4|P34 (25)|P14 (43)|
|IRQ5|PE5 (106)|P15 (42)|
|IRQ6|PE6 (102)|P16 (40)|
|IRQ7|PE7 (101)|P17 (38)|
|IRQ8|P00 (8)|P40 (141)|
|IRQ9|P01 (7)|P41 (139)|
|IRQ10|P02 (6)|P42 (138)|
|IRQ11|P03 (4)|P43 (137)|
|IRQ13|P05 (2)|P45 (135)|
|IRQ15|P07 (144)|P47 (133)|

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
