
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
|[rxprog](../rxprog)|〇|〇|

---

Translated with www.DeepL.com/Translator (free version)

---

## License

[MIT](../LICENSE)
