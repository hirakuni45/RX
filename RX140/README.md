
## RX140 features / 特徴

- RXv2 core / RXv2 コア
- Maximum operating frequency 48MHz / 最大動作周波数 48MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 1.8V ～ 5.5V Operation / 動作
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 8 Bits D/A / ８ビットＤ／Ａ変換器

### Package/パッケージ

|R5F5140---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F5140xxxFN|LFQFP|80|0.50|
|R5F5140xxxFM|LFQFP|64|0.50|
|R5F5140xxxFK|LQFP|64|0.80|
|R5F5140xxxFL|LFQFP|48|0.50|
|R5F5140xxxNE|HWQFN|48|0.50|
|R5F5140xxxFJ|LFQFP|32|0.80|
|R5F5140xxxNH|HWQFN|32|0.50|

### Ambient operating temperature/動作周囲温度

|R5F5140--X--|degree Celsius|
|---|:-:|
|R5F5140xxDxx|-40 ～ +85℃|
|R5F5140xxGxx|-40 ～ +105℃|

### Crypt/暗号

|R5F5140-X---|Crypt|
|---|:-:|
|R5F5140xAxxx|-|
|R5F5140xBxxx|〇|

### Memoey size/メモリ容量

|R5F5140X----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F51406xxxx|256K|64K|8K|
|R5F51405xxxx|128K|32K|8K|
|R5F51403xxxx|64K|16K|4K|

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|4K/8K|256|1/256|1|0xFF|4|

---

## RX140 Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F51406|256K|64K|8K|[R5F51406.ld](R5F51406.ld?ts=4)|3072|1024|
|R5F51405|128K|32K|8K|[R5F51405.ld](R5F51405.ld?ts=4)|1536|512|
|R5F51403|64K|16K|4K|[R5F51403.ld](R5F51403.ld?ts=4)|768|256|

---

## RX140 Dedicated class / 専用クラス

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
|Port Mapping MTU/ポートマッピング TMR|[port_map_tmr.hpp](port_map_tmr.hpp?ts=4)||
|A/D Definition/A/D 定義|[RX231/s12ade.hpp](../RX231/s12ade.hpp?ts=4)||
|D/A Definition/D/A 定義|[da.hpp](da.hpp?ts=4)||
|BUS Definition/BUS 定義|[bus.hpp](bus.hpp?ts=4)||
|ELC Definition/ELC 定義|[elc.hpp](elc.hpp?ts=4)||
|RTC Definition/RTC 定義|[rtc.hpp](rtc.hpp?ts=4)||
|FLASH Definition/FLASH 定義|[flash.hpp](flash.hpp?ts=4)||
|FLASH I/O Definition/FLASH I/O 定義|[RX24T/flash_io.hpp](../RX24T/flash.hpp?ts=4)||
|System Definition/システム定義|[system.hpp](system.hpp?ts=4)||
|System I/O Definition/システム I/O 定義|[system_io.hpp](system_io.hpp?ts=4)||
|A/D I/O Definition/A/D I/O 定義|[RX24T/adc_io.hpp](../RX24T/adc_io.hpp?ts=4)||
|D/A out Definition/D/A out 定義|[RX600/dac_out.hpp](../RX600/adc_io.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 64|LFQFP 80|
|---|---|---|
|VCL|VCL(2)|VCL(4)|
|Reset Input/リセット入力|RES#(6)|RES#(9)|
|Mode Controle/モード制御|MD/FINED(3)|MD/FINED(6)|
|RXD|P30/RXD1(14)|P30/RXD1(18)|
|TXD|P26/TXD1(16)|P26/TXD1(20)|
|Power/電源|VCC(10), VCC(38)|VCC(13), VCC(48)|
|GND/接地|VSS(8), VSS(40)|VSS(11), VSS(50)|
|Analog Power/アナログ電源|AVCC0(62)|AVCC0(77)|
|Analog GND/アナログ接地|AVSS0(64)|AVSS0(79)|
|Analog Refarence L/アナログ基準電源Ｌ|VREFL0(59)|VREFL0(74)|
|Analog Refarence H/アナログ基準電源Ｈ|VREFH0(61)|VREFH0(76)|
|OSC out|XTAL(7)|XTAL(10)|
|OSC in|EXTAL(9)|EXTAL(12)|
|Sub OSC out|XCOUT(5)|XCOUT(8)|
|Sub OSC in|XCIN(4)|XCIN(7)|

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
|ELC|Event Link Controller|イベントリンクコントローラ|
|MTU0|Multi-Function Timer Pulse Unit 0|マルチファンクションタイマパルスユニット０|
|MTU1|Multi-Function Timer Pulse Unit 1|マルチファンクションタイマパルスユニット１|
|MTU2|Multi-Function Timer Pulse Unit 2|マルチファンクションタイマパルスユニット２|
|MTU3|Multi-Function Timer Pulse Unit 3|マルチファンクションタイマパルスユニット３|
|MTU4|Multi-Function Timer Pulse Unit 4|マルチファンクションタイマパルスユニット４|
|MTU5|Multi-Function Timer Pulse Unit 5|マルチファンクションタイマパルスユニット５|
|POE2|Port Output Enable 2|ポートアウトプットイネーブル２|
|TPU0|16-Bit Timer Pulse Unit 0|16 ビットタイマパルスユニット０|
|TPU1|16-Bit Timer Pulse Unit 1|16 ビットタイマパルスユニット１|
|TPU2|16-Bit Timer Pulse Unit 2|16 ビットタイマパルスユニット２|
|TPU3|16-Bit Timer Pulse Unit 3|16 ビットタイマパルスユニット３|
|TPU4|16-Bit Timer Pulse Unit 4|16 ビットタイマパルスユニット４|
|TPU5|16-Bit Timer Pulse Unit 5|16 ビットタイマパルスユニット５|
|TMR0|8-Bit Timer 0|8 ビットタイマ０|
|TMR1|8-Bit Timer 1|8 ビットタイマ１|
|TMR2|8-Bit Timer 2|8 ビットタイマ２|
|TMR3|8-Bit Timer 3|8 ビットタイマ３|
|CMT0|Compare Match Timer 0|コンペアマッチタイマ０|
|CMT1|Compare Match Timer 1|コンペアマッチタイマ１|
|RTC|Realtime Clock|リアルタイムクロック|
|LPT|Low Power Timer|ローパワータイマ|
|IWDT|Independent Watchdog Timer|独立ウォッチドッグタイマ|
|SCI1|Serial Communications Interface 1|シリアルコミュニケーションインタフェース１|
|SCI5|Serial Communications Interface 5|シリアルコミュニケーションインタフェース５|
|SCI6|Serial Communications Interface 6|シリアルコミュニケーションインタフェース６|
|SCI8|Serial Communications Interface 8|シリアルコミュニケーションインタフェース８|
|SCI9|Serial Communications Interface 9|シリアルコミュニケーションインタフェース９|
|SCI11|Serial Communications Interface 11|シリアルコミュニケーションインタフェース１１|
|SCI12|Serial Communications Interface 12|シリアルコミュニケーションインタフェース１２|
|RIIC0|I2C-bus Interface 0|I2C バスインタフェース０|
|RSCAN|RSCAN Module|RSCAN インタフェース|
|RSPI0|Serial Peripheral Interface 0|シリアルペリフェラルインタフェース０|
|CRC|CRC Calculator|CRC 演算器|
|CTSU|Capacitive Touch Sensing Unit|静電容量式タッチセンサ|
|S12AD|12-Bit A/D Converter|12 ビット A/D コンバータ|
|DA|8-Bit D/A Converter|8 ビット D/A コンバータ|
|CMPB|Comparator B|コンパレータＢ|
|DOC|Data Operation Circuit|データ演算回路|

---

## port map order / ポートマップ候補

### LFQFP64

|Peripheral|FIRST|SECOND|THIRD|
|---|---|---|---|
|SCI1 / RXD|P15 (19)|P30 (14)|-|
|SCI1 / TXD|P16 (18)|P26 (16)|-|
|SCI1 / SCK|P17 (17)|P27 (15)|-|
|SCI5 / RXD|PA2 (--)|PA3 (43)|PC2 (32)|
|SCI5 / TXD|PA4 (42)|PA4 (42)|PC3 (31)|
|SCI5 / SCK|PA1 (44)|PA1 (44)|PC4 (30)|
|SCI6 / RXD|PB0 (39)|PD1 (--)|-|
|SCI6 / TXD|PB1 (37)|PD0 (--)|-|
|SCI6 / SCK|PB3 (36)|PD2 (--)|-|
|SCI8 / RXD|PC6 (28)|-|-|
|SCI8 / TXD|PC7 (27)|-|-|
|SCI8 / SCK|PC5 (29)|-|-|
|SCI9 / RXD|PB6 (34)|-|-|
|SCI9 / TXD|PB7 (33)|-|-|
|SCI9 / SCK|PB5 (35)|-|-|
|SCI12 / RXD|PE2 (49)|-|-|
|SCI12 / TXD|PE1 (50)|-|-|
|SCI12 / SCK|PE0 (51)|-|-|
|RIIC0 / SCL|P16 (18)|P12 (--)|-|
|RIIC0 / SDA|P17 (17)|P13 (--)|-|
|RSCAN / CRX|P15 (19)|P55 (--)|-|
|RSCAN / CTX|P14 (20)|P54 (--)|-|
|RSPI0 / RSPCK|PA5 (--)|PB0 (39)|PC5 (29)|
|RSPI0 / MOSI|PA6 (41)|P16 (18)|PC6 (28)|
|RSPI0 / MISO|PA7 (--)|P17 (17)|PC7 (27)|
|RSPI0 / SSL0|PA4 (42)|PC4 (30)|-|
|RSPI0 / SSL1|PA0 (45)|PC0 (--)|-|
|RSPI0 / SSL2|PA1 (44)|PC1 (--)|-|
|RSPI0 / SSL3|PA2 (--)|PC2 (32)|-|

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
