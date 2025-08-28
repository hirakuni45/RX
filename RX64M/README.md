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
