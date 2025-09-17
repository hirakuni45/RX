
## RX230/RX231 features / 特徴

- RXv2 core / RXv2 コア
- Maximum operating frequency 54MHz / 最大動作周波数 54MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 1.8V ～ 5.5V Operation / 動作
- USB2.0 Full Speed, Low Speed, Host, Function (RX231 Only)
- RSCAN (RX231 optional)
- SD Host Interface (SDHI) / SD ホストインタフェース (SDHI) (RX231 optional)
- Serial Sound Interface (SSI) / シリアルサウンドインタフェース (SSI)
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 12 Bits D/A / １２ビットＤ／Ａ変換器

### Package/パッケージ

|R5F523y---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F523yxxxFP|LFQFP|100|0.50|
|R5F523yxxxFM|LFQFP|64|0.50|
|R5F523yxxxFL|LFQFP|48|0.50|
|R5F523yxxxLA|TFLGA|100|0.50|
|R5F523yxxxLF|WFLGA|64|0.50|
|R5F523yxxxND|HWQFN|64|0.50|
|R5F523yxxxNE|HWQFN|48|0.50|

### Ambient operating temperature/動作周囲温度

|R5F523y--X--|degree Celsius|
|---|:-:|
|R5F523yxxDxx|-40 ～ +85℃|
|R5F523yxxGxx|-40 ～ +105℃|

### Crypt/暗号, SDHI, RSCAN, USB

|R5F523y-X---|Crypt|SDHI|RSCAN|USB|
|---|:-:|:-:|:-:|:-:|
|R5F5231xAxxx|-|-|〇|〇|
|R5F5231xBxxx|〇|〇|〇|〇|
|R5F5231xCxxx|-|-|-|〇|
|R5F5230xAxxx|-|-|-|-|

※R5F5231xBxxx: Excluding 48-pin version / ４８ピン版を除く

### Memoey size/メモリ容量

|R5F523yX----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F523y8xxxx|512K|64K|8K|
|R5F523y7xxxx|384K|64K|8K|
|R5F523y6xxxx|256K|32K|8K|
|R5F523y5xxxx|128K|32K|8K|

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|8K|1024|1/1024|1|0xFF|4|

---

## RX230/RX231 Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F52318|512K|64K|8K|[R5F52318.ld](R5F52318.ld?ts=4)|1536|512|
|R5F52317|384K|64K|8K|[R5F52317.ld](R5F52317.ld?ts=4)|1536|512|
|R5F52316|256K|32K|8K|[R5F52316.ld](R5F52316.ld?ts=4)|1536|512|
|R5F52315|128K|32K|8K|[R5F52315.ld](R5F52315.ld?ts=4)|1536|512|

---

## RX230/RX231 Dedicated class / 専用クラス

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
|Port Mapping TPU/ポートマッピング TPU|[port_map_tpu.hpp](port_map_tpu.hpp?ts=4)||
|BUS Definition/BUS 定義|[bus.hpp](bus.hpp?ts=4)||
|CMPB Definition/CMPB 定義|[cmpb.hpp](cmpb.hpp?ts=4)||
|ELC Definition/ELC 定義|[elc.hpp](elc.hpp?ts=4)||
|FLASH Definition/FLASH 定義|[flash.hpp](flash.hpp?ts=4)||
|LVDA Definition/LVDA 定義|[lvda.hpp](lvda.hpp?ts=4)||
|POE2 Definition/POE2 定義|[poe2.hpp](poe2.hpp?ts=4)||
|RTC Definition/RTC 定義|[rtc.hpp](rtc.hpp?ts=4)||
|A/D Definition/A/D 定義|[s12ade.hpp](s12ade.hpp?ts=4)||
|System Definition/システム定義|[system.hpp](system.hpp?ts=4)||
|System I/O Definition/システム I/O 定義|[system_io.hpp](system_io.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 64|LFQFP 100|
|---|---|---|
|VCL|VCL(2)|VCL(5)|
|Reset Input/リセット入力|RES#(6)|RES#(10)|
|Mode Controle/モード制御|MD/FINED(3)|MD/FINED(7)|
|B/UB|PC7(27)|PC7(45)|
|RXD|P30/RXD1(14)|P30/RXD1(20)|
|TXD|P26/TXD1(16)|P26/TXD1(22)|
|USB_VCC|VCC_USB(21)|VCC_USB(35)|
|USB_VSS|VSS_USB(24)|VSS_USB(38)|
|USB+|USB_DP(23)|USB_DP(37)|
|USB-|USB_DM(22)|USB_DM(36)|
|Power/電源|VCC(10), VCC(38)|VCC(14),VCC(60)|
|GND/接地|VSS(8), VSS(40)|VSS(12),VSS(62)|
|Analog Power/アナログ電源|AVCC0(62)|AVCC0(97)|
|Analog GND/アナログ接地|AVSS0(64)|AVSS0(99)|
|Analog Refarence L/アナログ基準電源Ｌ|VREFL(52)|VREFL(3)|
|Analog Refarence H/アナログ基準電源Ｈ|VREFH(54)|VREFH(1)|
|Analog Refarence L0/アナログ基準電源Ｌ0|VREFL0(59)|VREFL0(94)|
|Analog Refarence H0/アナログ基準電源Ｈ0|VREFH0(61)|VREFH0(96)|
|VBATT|VBATT(12)|VBATT(6)|
|OSC in|EXTAL(9)|EXTAL(13)|
|OSC out|XTAL(7)|XTAL(11)|
|Sub OSC in|XCIN(4)|XCIN(8)|
|Sub OSC out|XCOUT(5)|XCOUT(9)|

- VCL: 4.7uF/25V

|Mode/モード|B/UB|MD|
|---|:---:|:---:|
|Serial BOOT/シリアルブート|0|0|
|USB Boot/USB ブート|1|0|
|Single Chip/シングルチップ|-|1|

---

## port map order / ポートマップ候補

### LFQFP64

|Peripheral|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|SCI0 / RXD|P21 (--)|-|-|-|
|SCI0 / TXD|P20 (--)|-|-|-|
|SCI0 / SCK|P22 (--)|-|-|-|
|SCI1 / RXD|P15 (19)|P30 (14)|-|-|
|SCI1 / TXD|P16 (18)|P26 (16)|-|-|
|SCI1 / SCK|P17 (17)|P27 (15)|-|-|
|SCI5 / RXD|PA2 (--)|PA3 (43)|PC2 (32)|PC2 (32)|
|SCI5 / TXD|PA4 (42)|PA4 (42)|PC3 (31)|PC3 (31)|
|SCI5 / SCK|PA1 (44)|PA1 (44)|PC4 (30)|PC1 (--)|
|SCI6 / RXD|P33 (--)|PB0 (39)|-|-|
|SCI6 / TXD|P32 (--)|PB1 (37)|-|-|
|SCI6 / SCK|P34 (17)|PB3 (36)|-|-|
|SCI8 / RXD|PC6 (28)|-|-|-|
|SCI8 / TXD|PC7 (27)|-|-|-|
|SCI8 / SCK|PC5 (29)|-|-|-|
|SCI9 / RXD|PB6 (34)|-|-|-|
|SCI9 / TXD|PB7 (33)|-|-|-|
|SCI9 / SCK|PB5 (35)|-|-|-|
|SCI12 / RXD|PE2 (49)|-|-|-|
|SCI12 / TXD|PE1 (50)|-|-|-|
|SCI12 / SCK|PE0 (51)|-|-|-|
|RIIC0 / SCL|P16 (18)|P12 (--)|-|-|
|RIIC0 / SDA|P17 (17)|P13 (--)|-|-|
|RSPI0 / RSPCK|PA5 (--)|PB0 (39)|PC5 (29)|-|
|RSPI0 / MOSI|PA6 (41)|P16 (18)|PC6 (28)|-|
|RSPI0 / MISO|PA7 (--)|P17 (17)|PC7 (27)|-|
|RSPI0 / SSL0|PA4 (42)|PC4 (30)|-|-|
|RSPI0 / SSL1|PA0 (45)|PC0 (--)|-|-|
|RSPI0 / SSL2|PA1 (44)|PC1 (--)|-|-|
|RSPI0 / SSL3|PA2 (--)|PC2 (32)|-|-|
|SSI0 / AUDIO_MCLK|P22 (--)|P30 (14)|PE3 (48)|-|
|SSI0 / SSISCK0|P23 (--)|P31 (13)|PA1 (44)|-|
|SSI0 / SSIWS0|P21 (--)|P27 (15)|PA6 (41)|-|
|SSI0 / SSIRXD0|P20 (--)|P26 (16)|PA3 (43)|-|
|SSI0 / SSITXD0|P17 (17)|P17 (17)|PA4 (42)|-|

### LFQFP100

|Peripheral|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|SCI0 / RXD|P21 (27)|-|-|-|
|SCI0 / TXD|P20 (28)|-|-|-|
|SCI0 / SCK|P22 (26)|-|-|-|
|SCI1 / RXD|P15 (31)|P30 (20)|-|-|
|SCI1 / TXD|P16 (30)|P26 (22)|-|-|
|SCI1 / SCK|P17 (29)|P27 (21)|-|-|
|SCI5 / RXD|PA2 (68)|PA3 (67)|PC2 (50)|PC2 (50)|
|SCI5 / TXD|PA4 (66)|PA4 (66)|PC3 (49)|PC3 (49)|
|SCI5 / SCK|PA1 (69)|PA1 (69)|PC4 (48)|PC1 (51)|
|SCI6 / RXD|P33 (17)|PB0 (61)|-|-|
|SCI6 / TXD|P32 (18)|PB1 (59)|-|-|
|SCI6 / SCK|P34 (16)|PB3 (57)|-|-|
|SCI8 / RXD|PC6 (46)|-|-|-|
|SCI8 / TXD|PC7 (45)|-|-|-|
|SCI8 / SCK|PC5 (47)|-|-|-|
|SCI9 / RXD|PB6 (54)|-|-|-|
|SCI9 / TXD|PB7 (53)|-|-|-|
|SCI9 / SCK|PB5 (55)|-|-|-|
|SCI12 / RXD|PE2 (76)|-|-|-|
|SCI12 / TXD|PE1 (77)|-|-|-|
|SCI12 / SCK|PE0 (78)|-|-|-|
|RIIC0 / SCL|P16 (30)|P12 (34)|-|-|
|RIIC0 / SDA|P17 (29)|P13 (33)|-|-|
|RSPI0 / RSPCK|PA5 (65)|PB0 (61)|PC5 (47)|-|
|RSPI0 / MOSI|PA6 (64)|P16 (30)|PC6 (46)|-|
|RSPI0 / MISO|PA7 (63)|P17 (29)|PC7 (45)|-|
|RSPI0 / SSL0|PA4 (66)|PC4 (48)|-|-|
|RSPI0 / SSL1|PA0 (70)|PC0 (52)|-|-|
|RSPI0 / SSL2|PA1 (69)|PC1 (51)|-|-|
|RSPI0 / SSL3|PA2 (68)|PC2 (50)|-|-|
|SSI0 / AUDIO_MCLK|P22 (26)|P30 (20)|PE3 (75)|-|
|SSI0 / SSISCK0|P23 (25)|P31 (19)|PA1 (69)|-|
|SSI0 / SSIWS0|P21 (27)|P27 (21)|PA6 (64)|-|
|SSI0 / SSIRXD0|P20 (28)|P26 (22)|PA3 (67)|-|
|SSI0 / SSITXD0|P17 (29)|P17 (29)|PA4 (66)|-|

---

## rx_prog Flash Programming / rx_prog フラッシュプログラム

||Support/サポート|operation verification/動作検証|
|-|:-:|:-:|
|[rxprog](../rxprog)|〇|〇|

rx_prog option:
- --write-page-wait=10000
- --erase-page-wait=5000

---

Translated with www.DeepL.com/Translator (free version)

---

## License

[MIT](../LICENSE)
