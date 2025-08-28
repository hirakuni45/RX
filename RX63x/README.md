
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

## port map order / ポートマップ候補

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
|SCI2 / SCK|P11 (--)|P51 (55)|-|-|
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

## rx_prog Flash Programming / rx_prog フラッシュプログラム

||Support/サポート|operation verification/動作検証|
|-|:-:|:-:|
|[rxprog](../rxprog)|〇|〇|

---

Translated with www.DeepL.com/Translator (free version)

---

## License

[MIT](../LICENSE)
