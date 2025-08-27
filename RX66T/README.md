
## RX66T features / 特徴

- RXv3 core / RXv3 コア
- Maximum operating frequency 160MHz / 最大動作周波数 160MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 2.7V ～ 5.5V Operation / 動作
- USB2.0 Full Speed, Host, Function (Optional)
- CAN Module (CAN) / CAN モジュール (CAN)
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 12 Bits D/A / １２ビットＤ／Ａ変換器

### Package/パッケージ

|R5F566T---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F566TxxxFB|LFQFP|144|0.50|
|R5F566TxxxFH|LQFP|112|0.65|
|R5F566TxxxFP|LFQFP|100|0.50|
|R5F566TxxxFF|LQFP|80|0.65|
|R5F566TxxxFN|LFQFP|80|0.50|
|R5F566TxxxFM|LFQFP|64|0.50|

### Ambient operating temperature/動作周囲温度

|R5F566T--X--|degree Celsius|
|---|:-:|
|R5F566TxxDxx|-40 ～ +85℃|
|R5F566TxxGxx|-40 ～ +105℃|

### PGA, TSIP, USB

|R5F566T-X---|PGA|TSIP|USB|
|---|:-:|:-:|:-:|
|R5F566TxAxxx|〇|-|-|
|R5F566TxBxxx|-|-|-|
|R5F566TxCxxx|〇|-|〇|
|R5F566TxExxx|〇|〇|-|
|R5F566TxFxxx|-|〇|-|
|R5F566TxGxxx|〇|〇|〇|

### Memoey size/メモリ容量

|R5F566TX----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F566TKxxxx|1M|128K|32K|
|R5F566TFxxxx|512K|128K|32K|
|R5F566TExxxx|512K|64K|32K|
|R5F566TAxxxx|256K|64K|32K|

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|32K|64|4/64|4|0x??|3|

---

## RX66T Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F566TK|1024K|128K+16K|32K|[R5F566TK.ld](R5F566TK.ld?ts=4)|3584|512|
|R5F566TF|512K|128K+16K|32K|[R5F566TF.ld](R5F566TF.ld?ts=4)|3584|512|
|R5F566TE|512K|64K+16K|32K|[R5F566TE.ld](R5F566TE.ld?ts=4)|1792|256|
|R5F566TA|256K|64K+16K|32K|[R5F566TA.ld](R5F566TA.ld?ts=4)|1792|256|

RAM: 16K(With ECC)

---

## RX66T Dedicated class / 専用クラス

|Function/機能|Source|Remarks/備考|
|---|---|:-:|
|Hardware-specific Definition/ハード固有定義|[board_profile.hpp](board_profile.hpp?ts=4)||
|Operating Frequency Definition/動作周波数定義|[clock_profile.hpp](clock_profile.hpp?ts=4)||

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
