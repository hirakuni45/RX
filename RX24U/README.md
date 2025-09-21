
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

## peripheral / ペリフェラル

|Peripheral|Function|機能|
|---|---|---|
|CAC|Clock Frequency Accuracy Measurement Circuit|クロック周波数精度測定回路|
|DTC|Data Transfer Controller|データトランスファコントローラ|
|MTU0|Multi-Function Timer Pulse Unit 0|マルチファンクションタイマパルスユニット０|
|MTU1|Multi-Function Timer Pulse Unit 1|マルチファンクションタイマパルスユニット１|
|MTU2|Multi-Function Timer Pulse Unit 2|マルチファンクションタイマパルスユニット２|
|MTU3|Multi-Function Timer Pulse Unit 3|マルチファンクションタイマパルスユニット３|
|MTU4|Multi-Function Timer Pulse Unit 4|マルチファンクションタイマパルスユニット４|
|MTU5|Multi-Function Timer Pulse Unit 5|マルチファンクションタイマパルスユニット５|
|MTU6|Multi-Function Timer Pulse Unit 6|マルチファンクションタイマパルスユニット６|
|MTU7|Multi-Function Timer Pulse Unit 7|マルチファンクションタイマパルスユニット７|
|MTU9|Multi-Function Timer Pulse Unit 9|マルチファンクションタイマパルスユニット９|
|POE3|Port Output Enable 3|ポートアウトプットイネーブル３|
|GPT0|General PWM Timer 0|汎用 PWM タイマ０|
|GPT1|General PWM Timer 1|汎用 PWM タイマ１|
|GPT2|General PWM Timer 2|汎用 PWM タイマ２|
|GPT3|General PWM Timer 3|汎用 PWM タイマ３|
|TMR0|8-Bit Timer 0|8 ビットタイマ０|
|TMR1|8-Bit Timer 1|8 ビットタイマ１|
|TMR2|8-Bit Timer 2|8 ビットタイマ２|
|TMR3|8-Bit Timer 3|8 ビットタイマ３|
|TMR4|8-Bit Timer 4|8 ビットタイマ４|
|TMR5|8-Bit Timer 5|8 ビットタイマ５|
|TMR6|8-Bit Timer 6|8 ビットタイマ６|
|TMR7|8-Bit Timer 7|8 ビットタイマ７|
|CMT0|Compare Match Timer 0|コンペアマッチタイマ０|
|CMT1|Compare Match Timer 1|コンペアマッチタイマ１|
|CMT2|Compare Match Timer 2|コンペアマッチタイマ２|
|CMT3|Compare Match Timer 3|コンペアマッチタイマ３|
|IWDT|Independent Watchdog Timer|独立ウォッチドッグタイマ|
|SCI1|Serial Communications Interface 1|シリアルコミュニケーションインタフェース１|
|SCI5|Serial Communications Interface 5|シリアルコミュニケーションインタフェース５|
|SCI6|Serial Communications Interface 6|シリアルコミュニケーションインタフェース６|
|SCI8|Serial Communications Interface 8|シリアルコミュニケーションインタフェース８|
|SCI9|Serial Communications Interface 9|シリアルコミュニケーションインタフェース９|
|SCI11|Serial Communications Interface 11|シリアルコミュニケーションインタフェース１１|
|RIIC0|I2C-bus Interface 0|I2C バスインタフェース０|
|RSCAN|RSCAN Module|RSCAN モジュール|
|RSPI0|Serial Peripheral Interface 0|シリアルペリフェラルインタフェース０|
|CRC|CRC Calculator|CRC 演算器|
|S12AD|12-Bit A/D Converter|12 ビット A/D コンバータ|
|S12AD1|12-Bit A/D Converter 1|12 ビット A/D コンバータ１|
|S12AD2|12-Bit A/D Converter 2|12 ビット A/D コンバータ２|
|DA|8-Bit D/A Converter|8 ビット D/A コンバータ|
|CMPC0|Comparator C0|コンパレーターＣ０|
|CMPC1|Comparator C1|コンパレーターＣ１|
|CMPC2|Comparator C2|コンパレーターＣ２|
|CMPC3|Comparator C3|コンパレーターＣ３|
|DOC|Data Operation Circuit|データ演算回路|

---

## port map order / ポートマップ候補

### LFQFP100

|Peripheral|FIRST|SECOND|THIRD|
|---|---|---|---|
|SCI1 / RXD|PD5 (20)|PC3 (---)|-|
|SCI1 / TXD|PD3 (22)|PC4 (---)|-|
|SCI1 / SCK|PD4 (21)|P25 (---)|-|
|SCI5 / RXD|PB6 (27)|PE0 (17)|-|
|SCI5 / TXD|PB5 (28)|PD7 (18)|-|
|SCI5 / SCK|PB7 (26)|PD2 (23)|-|
|SCI6 / RXD|P80 (98)|PA5 (36)|PB1 (34)|
|SCI6 / TXD|P81 (97)|PB0 (35)|PB2 (33)|
|SCI6 / SCK|P82 (96)|PA4 (37)|PB3 (32)|
|SCI8 / RXD|P83 (---)|PC0 (---)|-|
|SCI8 / TXD|P84 (---)|PC1 (---)|-|
|SCI8 / SCK|PC2 (---)|PC2 (---)|-|
|SCI9 / RXD|PG0 (---)|-|-|
|SCI9 / TXD|PG1 (---)|-|-|
|SCI9 / SCK|PG2 (---)|-|-|
|SCI11 / RXD|PC6 (---)|PD5 (20)|PF1 (---)|
|SCI11 / TXD|PC5 (---)|PD3 (22)|PF0 (---)|
|SCI11 / SCK|PD4 (21)|PD4 (21)|PF2 (---)|
|RIIC0 / SCL|PB1 (34)|-|-|
|RIIC0 / SDA|PB2 (33)|-|-|
|RSCAN / CRX|PA0 (41)|PF2 (---)|-|
|RSCAN / CTX|PA1 (40)|PF3 (---)|-|
|RSPI0 / RSPCK|P24 (64)|PB3 (32)|PD0 (25)|
|RSPI0 / MOSI|P23 (65)|PB0 (35)|PD2 (23)|
|RSPI0 / MISO|P22 (66)|PA5 (36)|PD1 (24)|
|RSPI0 / SSL0|P30 (63)|PA3 (38)|PD6 (19)|
|RSPI0 / SSL1|P31 (61)|PA2 (39)|PD7 (18)|
|RSPI0 / SSL2|P32 (59)|PA1 (40)|PE0 (17)|
|RSPI0 / SSL3|P33 (58)|PA0 (41)|PE1 (16)|

### LFQFP144

|Peripheral|FIRST|SECOND|THIRD|
|---|---|---|---|
|SCI1 / RXD|PD5 (27)|PC3 (98)|-|
|SCI1 / TXD|PD3 (29)|PC4 (97)|-|
|SCI1 / SCK|PD4 (28)|P25 (93)|-|
|SCI5 / RXD|PB6 (38)|PE0 (24)|-|
|SCI5 / TXD|PB5 (39)|PD7 (25)|-|
|SCI5 / SCK|PB7 (37)|PD2 (30)|-|
|SCI6 / RXD|P80 (139)|PA5 (53)|PB1 (49)|
|SCI6 / TXD|P81 (138)|PB0 (50)|PB2 (48)|
|SCI6 / SCK|P82 (137)|PA4 (54)|PB3 (47)|
|SCI8 / RXD|P83 (136)|PC0 (46)|-|
|SCI8 / TXD|P84 (135)|PC1 (45)|-|
|SCI8 / SCK|PC2 (44)|PC2 (44)|-|
|SCI9 / RXD|PG0 (82)|-|-|
|SCI9 / TXD|PG1 (81)|-|-|
|SCI9 / SCK|PG2 (80)|-|-|
|SCI11 / RXD|PC6 (61)|PD5 (27)|PF1 (35)|
|SCI11 / TXD|PC5 (62)|PD3 (29)|PF0 (36)|
|SCI11 / SCK|PD4 (28)|PD4 (28)|PF2 (34)|
|RIIC0 / SCL|PB1 (34)|-|-|
|RIIC0 / SDA|PB2 (33)|-|-|
|RSCAN / CRX|PA0 (58)|PF2 (34)|-|
|RSCAN / CTX|PA1 (57)|PF3 (33)|-|
|RSPI0 / RSPCK|P24 (94)|PB3 (47)|PD0 (32)|
|RSPI0 / MOSI|P23 (95)|PB0 (50)|PD2 (30)|
|RSPI0 / MISO|P22 (96)|PA5 (53)|PD1 (31)|
|RSPI0 / SSL0|P30 (90)|PA3 (55)|PD6 (26)|
|RSPI0 / SSL1|P31 (87)|PA2 (56)|PD7 (25)|
|RSPI0 / SSL2|P32 (84)|PA1 (57)|PE0 (24)|
|RSPI0 / SSL3|P33 (83)|PA0 (58)|PE1 (23)|

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
