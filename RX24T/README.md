
## RX24T features / 特徴

- RXv2 core / RXv2 コア
- Maximum operating frequency 80MHz / 最大動作周波数 80MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 2.7V ～ 5.5V Operation / 動作
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 8 Bits D/A / ８ビットＤ／Ａ変換器

### Package/パッケージ

|R5F524T---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F524TxxxFP|LFQFP|100|0.50|
|R5F524TxxxFF|LQFP|80|0.65|
|R5F524TxxxFN|LFQFP|80|0.50|
|R5F524TxxxFM|LFQFP|64|0.50|

### Ambient operating temperature/動作周囲温度

|R5F524T--X--|degree Celsius|
|---|:-:|
|R5F524TxxDxx|-40 ～ +85℃|

### Memoey size/メモリ容量

|R5F524TX----|CodeFlash|RAM|DataFlash|ChipVersion|
|---|:-:|:-:|:-:|:-:|
|R5F524TExxxx|512K|32K|8K|B|
|R5F524TCxxxx|384K|32K|8K|B|
|R5F524TBxxxx|256K|32K|8K|B|
|R5F524TAxxxx|256K|16K|8K|A|
|R5F524T8xxxx|128K|16K|8K|A|

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|8K|1024|1/1024|1|0xFF|4|

---

## RX24T Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F524TA|256K|16K|8K|[R5F524TA.ld](R5F524TA.ld?ts=4)|1024|512|
|R5F524T8|128K|16K|8K|[R5F524T8.ld](R5F524T8.ld?ts=4)|1024|512|

---

## RX24T Dedicated class / 専用クラス

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
|Port Mapping TMR/ポートマッピング TMR|[port_map_tmr.hpp](port_map_tmr.hpp?ts=4)||
|Port Mapping GPT/ポートマッピング GPT|[port_map_gpt.hpp](port_map_gpt.hpp?ts=4)||
|FLASH Definition/FLASH 定義|[flash.hpp](flash.hpp?ts=4)||
|FLASH Definition/FLASH I/O 定義|[flash_io.hpp](flash_io.hpp?ts=4)||
|LVDA Definition/LVDA 定義|[lvda.hpp](lvda.hpp?ts=4)||
|POE3 Definition/POE3 定義|[poe2.hpp](poe3.hpp?ts=4)||
|D/A Definition/D/A 定義|[da.hpp](da.hpp?ts=4)||
|A/D Definition/A/D 定義|[s12ad.hpp](s12ad.hpp?ts=4)||
|System Definition/システム定義|[system.hpp](system.hpp?ts=4)||
|System I/O Definition/システム I/O 定義|[system_io.hpp](system_io.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 100|
|---|---|
|VCL|VCL(5)|
|Reset Input/リセット入力|RES#(10)|
|Mode Controle/モード制御|MD/FINED(6)|
|RXD|PD5/RXD1(20)|
|TXD|PD3/TXD1(22)|
|Power/電源|VCC(14), VCC(29), VCC(42), VCC(60)|
|GND/接地|VSS(3), VSS(12), VSS(31), VSS(44), VSS(62)|
|Analog Power/アナログ電源|AVCC0(93), AVCC1(92), AVCC2(71)|
|Analog GND/アナログ接地|AVSS0(94), AVSS1(95), AVSS2(73)|
|Analog Refarence/アナログ基準電源|VREF(72)|
|OSC in|EXTAL(13)|
|OSC out|XTAL(11)|

- VCL: 4.7uF/25V

|Mode/モード|MD|
|---|:---:|
|Serial BOOT/シリアルブート|0|
|Single Chip/シングルチップ|1|

---

## Peripheral / ペリフェラル

- [peripheral.hpp](peripheral.hpp?ts=4)

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

## Port map order (IRQ) / ポートマップ候補 (IRQ)

- [port_map_irq.hpp](port_map_irq.hpp?ts=4)

### LFQGFP100

|IRQ|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|IRQ0|P10 (100)|P52 (81)|PE5 (1)|-|-|
|IRQ1|P11 (99)|P53 (80)|PA5 (36)|PE4 (8)|-|
|IRQ2|P00 (4)|P54 (79)|PD4 (21)|PE3 (9)|-|
|IRQ3|P55 (78)|PB4 (30)|PD5 (20)|-|-|
|IRQ4|P01 (7)|P60 (77)|P96 (43)|-|-|
|IRQ5|P02 (2)|P61 (76)|P70 (57)|PB6 (27)|PD6 (19)|
|IRQ6|P21 (67)|P31 (61)|P62 (75)|-|-|
|IRQ7|P20 (68)|P30 (63)|P63 (74)|-|-|

---

## Port map order / ポートマップ候補

- [port_map.hpp](port_map.hpp?ts=4)

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

## Port map order (GPT) / ポートマップ候補 (GPT)

- [port_map_gpt.hpp](port_map_gpt.hpp?ts=4)

### LFQFP100

|GPT|FIRST|SECOND|THIRD|
|---|---|---|---|
|GTIOC0A|P71 (56)|PD7 (18)|-|
|GTIOC0B|P74 (53)|PD1 (24)|-|
|GTIOC1A|P72 (55)|PD0 (25)|-|
|GTIOC1B|P75 (52)|PB7 (26)|-|
|GTIOC2A|P73 (54)|PB6 (27)|-|
|GTIOC2B|P76 (51)|PB5 (28)|-|
|GTIOC3A|PD7 (18)|-|-|
|GTIOC3B|PD6 (19)|-|-|
|GTECLKA|PD5 (20)|-|-|
|GTECLKB|PD4 (21)|-|-|
|GTECLKC|PD3 (22)|-|-|
|GTECLKD|PB4 (30)|-|-|
|GTETRG|PB4 (30)|-|-|
|GTADSM0|PA3 (38)|-|-|
|GTADSM1|PA2 (39)|-|-|

---

## Port map order (MTU) / ポートマップ候補 (MTU)

[port_map_mtu.hpp](port_map_mtu.hpp?ts=4)

### LFQGFP100

|MTU|FIRST|SECOND|THIRD|
|---|---|---|---|
|MTIOC0A #|P31 (61)|PB3 (32)|-|
|MTIOC0B #|P30 (63)|PB2 (33)|-|
|MTIOC0C #|PB1 (34)|-|-|
|MTIOC0D #|PB0 (35)|-|-|
|MTIOC1A #|PA5 (36)|-|-|
|MTIOC1B #|PA4 (37)|-|-|
|MTIOC2A #|PA3 (38)|-|-|
|MTIOC2B #|PA2 (39)|-|-|
|MTIOC3A #|P11 (99)|P33 (58)|-|
|MTIOC3B #|P71 (56)|-|-|
|MTIOC3C #|P32 (59)|-|-|
|MTIOC3D #|P74 (53)|-|-|
|MTIOC4A #|P72 (55)|-|-|
|MTIOC4B #|P73 (54)|-|-|
|MTIOC4C #|P75 (52)|-|-|
|MTIOC4D #|P76 (51)|-|-|
|MTIC5U #|P24 (64)|P82 (96)|-|
|MTIC5V #|P23 (65)|P81 (97)|-|
|MTIC5W #|P22 (66)|P80 (98)|-|
|MTIOC6A #|PA1 (40)|-|-|
|MTIOC6B #|P95 (45)|-|-|
|MTIOC6C #|PA0 (41)|-|-|
|MTIOC6D #|P92 (48)|-|-|
|MTIOC7A #|P94 (46)|-|-|
|MTIOC7B #|P93 (47)|-|-|
|MTIOC7C #|P91 (49)|-|-|
|MTIOC7D #|P90 (50)|-|-|
|MTIOC9A #|P21 (67)|PD7 (18)|-|
|MTIOC9B #|P10 (100)|PE0 (17)|-|
|MTIOC9C #|P20 (68)|PD6 (19)|-|
|MTIOC9D #|P02 (2)|PE1 (16)|-|
|MTCLKA #|P21 (67)|P33 (58)|-|
|MTCLKB #|P20 (68)|P32 (59)|-|
|MTCLKC #|P11 (99)|P31 (61)|PE4 (8)|
|MTCLKD #|P10 (100)|P30 (63)|PE3 (9)|
|ADSM0|PB2 (33)|-|-|
|ADSM1|PB1 (34)|-|-|

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
