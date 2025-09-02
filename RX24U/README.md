
## RX24U features / 特徴

- RXv2 core / RXv2 コア
- Maximum operating frequency 80MHz / 最大動作周波数 80MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 2.7V ～ 5.5V Operation / 動作
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 8 Bits D/A / ８ビットＤ／Ａ変換器

### Package/パッケージ

|R5F524U---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F524UxxxFB|LFQFP|144|0.50|
|R5F524UxxxFP|LFQFP|100|0.50|

### Ambient operating temperature/動作周囲温度

|R5F524U--X--|degree Celsius|
|---|:-:|
|R5F524UxxDxx|-40 ～ +85℃|

### Memoey size/メモリ容量

|R5F524UX----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F524UExxxx|512K|32K|8K|
|R5F524UCxxxx|384K|32K|8K|
|R5F524UBxxxx|256K|32K|8K|

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|8K|1024|1/1024|1|0xFF|4|

---

## RX24U Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F524UE|512K|32K|8K|[R5F524UE.ld](R5F524UE.ld?ts=4)|1536|512|
|R5F524UB|256K|32K|8K|[R5F524UB.ld](R5F524UB.ld?ts=4)|1536|512|

---

## RX24U Dedicated class / 専用クラス

|Function/機能|Source|Remarks/備考|
|---|---|:-:|
|Peripheral Name/ペリフェラル名|[peripheral.hpp](peripheral.hpp?ts=4)||
|Hardware-specific Definition/ハード固有定義|[board_profile.hpp](board_profile.hpp?ts=4)||
|Operating Frequency Definition/動作周波数定義|[clock_profile.hpp](clock_profile.hpp?ts=4)||
|Power Control/電力制御|[power_mgr.hpp](power_mgr.hpp?ts=4)||
|Interrupt Definition/割り込み定義|[icu.hpp](icu.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 100|LFQFP 144|
|---|---|---|
|VCL|VCL(5)|VCL(5)|
|Reset Input/リセット入力|RES#(10)|RES#(10)|
|Mode Controle/モード制御|MD/FINED(6)|MD/FINED(6)|
|RXD|PD5/RXD1(20)|PD5/RXD1(27)|
|TXD|PD3/TXD1(22)|PD3/TXD1(29)|
|Power/電源|VCC(14), VCC(29), VCC(42), VCC(60)|VCC(6), VCC(20), VCC(21), VCC(40)|
|Power/電源|-|VCC(63), VCC(85), VCC(86)|
|GND/接地|VSS(3), VSS(12), VSS(31), VSS(44)|VSS(8), VSS(9), VSS(18), VSS(42)|
|GND/接地|VSS(62)|VSS(65), VSS(66), VSS(88), VSS(89)|
|Analog Power/アナログ電源|AVCC0(93), AVCC1(92), AVCC2(72)|AVCC0(129), AVCC1(127), AVCC2(104)|
|Analog GND/アナログ接地|AVSS0(94), AVSS1(95), AVSS2(73)|AVSS0(131), AVSS1(133), AVSS2(105)|
|Programable Gain AMP GND0|PGAVSS0(91)|PGAVSS0(126)|
|Programable Gain AMP GND1|PGAVSS1(86)|PGAVSS1(121)|
|Analog Refarence L0/アナログ基準電源Ｌ0|-|VREFL0(132)|
|Analog Refarence H0/アナログ基準電源Ｈ0|-|VREFH0(130)|
|Analog Refarence L1/アナログ基準電源Ｌ0|-|VREFL1(134)|
|Analog Refarence H1/アナログ基準電源Ｈ0|-|VREFH1(128)|
|Analog Refarence L2/アナログ基準電源Ｌ0|-|VREFL2(106)|
|Analog Refarence H2/アナログ基準電源Ｈ0|-|VREFH2(103)|
|OSC in|EXTAL(13)|EXTAL(19)|
|OSC out|XTAL(11)|XTAL(17)|

- VCL: 4.7uF/25V

|Mode/モード|MD|
|---|:---:|
|Serial BOOT/シリアルブート|0|
|Single Chip/シングルチップ|1|

---

## port map order / ポートマップ候補

### LFQFP100

|Peripheral|FIRST|SECOND|THIRD|
|---|---|---|---|
|SCI1 / RXD|PD5 (20)|-|-|
|SCI1 / TXD|PD3 (22)|-|-|
|SCI1 / SCK|PD4 (21)|-|-|
|SCI5 / RXD|PB6 (27)|PE0 (17)|-|
|SCI5 / TXD|PB5 (28)|PD7 (18)|-|
|SCI5 / SCK|PB7 (26)|PD2 (23)|-|
|SCI6 / RXD|P80 (98)|PA5 (36)|PB1 (34)|
|SCI6 / TXD|P81 (97)|PB0 (35)|PB2 (33)|
|SCI6 / SCK|P82 (96)|PA4 (37)|PB3 (32)|
|RIIC0 / SCL|PB1 (34)|-|-|
|RIIC0 / SDA|PB2 (33)|-|-|
|RSCAN / CRX|PA0 (41)|-|-|
|RSCAN / CTX|PA1 (40)|-|-|
|RSPI0 / RSPCK|P24 (64)|PB3 (32)|PD0 (25)|
|RSPI0 / MOSI|P23 (65)|PB0 (35)|PD2 (23)|
|RSPI0 / MISO|P22 (66)|PA5 (36)|PD1 (24)|
|RSPI0 / SSL0|P30 (63)|PA3 (38)|PD6 (19)|
|RSPI0 / SSL1|P31 (61)|PA2 (39)|PD7 (18)|
|RSPI0 / SSL2|P32 (59)|PA1 (40)|PE0 (17)|
|RSPI0 / SSL3|P33 (58)|PA0 (41)|PE1 (16)|

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
