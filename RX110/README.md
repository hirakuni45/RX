
## RX110 features / 特徴

- RXv1 core / RXv1 コア
- Maximum operating frequency 32MHz / 最大動作周波数 32MHz
- 1.8V ～ 3.6V Operation / 動作
- 12 Bits A/D / １２ビットＡ／Ｄ変換器

### Package/パッケージ

|R5F5110---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F5110xxxFM|LFQFP|64|0.50|
|R5F5110xxxFK|LQFP|64|0.80|
|R5F5110xxxLF|WFLGA|64|0.50|
|R5F5110xxxFL|LFQFP|48|0.50|
|R5F5110xxxNE|HWQFN|48|0.50|
|R5F5110xxxNF|HWQFN|40|0.50|
|R5F5110xxxLM|WFLGA|36|0.50|

### Ambient operating temperature/動作周囲温度

|R5F5110--X--|degree Celsius|
|---|:-:|
|R5F5110xxDxx|-40 ～ +85℃|
|R5F5110xxGxx|-40 ～ +105℃|

### Memoey size/メモリ容量

|R5F5110X----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F51105xxxx|128K|16K|0K|
|R5F51104xxxx|96K|16K|0K|
|R5F51103xxxx|64K|10K|0K|
|R5F51101xxxx|32K|10K|0K|
|R5F5110Jxxxx|16K|8K|0K|
|R5F5110Hxxxx|8K|8K|0K|

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|0K|-|-|-|-|4|

---

## RX110 Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F51105|128K|16K|0K|[R5F51105.ld](R5F51105.ld?ts=4)|768|256|
|R5F51104|96K|16K|0K|[R5F51104.ld](R5F51104.ld?ts=4)|768|256|
|R5F51103|64K|10K|0K|[R5F51113.ld](R5F51103.ld?ts=4)|256|128|

---

## RX110 Dedicated class / 専用クラス

|Function/機能|Source|Remarks/備考|
|---|---|:-:|
|Peripheral Name/ペリフェラル名|[peripheral.hpp](peripheral.hpp?ts=4)||
|Hardware-specific Definition/ハード固有定義|[board_profile.hpp](board_profile.hpp?ts=4)||
|Operating Frequency Definition/動作周波数定義|[clock_profile.hpp](clock_profile.hpp?ts=4)||
|Power Control/電力制御|[power_mgr.hpp](power_mgr.hpp?ts=4)||
|Interrupt Definition/割り込み定義|[icu.hpp](icu.hpp?ts=4)||
|Port Function Definition/ポート機能定義|[mpc.hpp](mpc.hpp?ts=4)||
|Port Mapping/ポートマッピング|[port_map.hpp](port_map.hpp?ts=4)||
|Port Mapping IRQ/ポートマッピング IRQ|[port_map_irq.hpp](port_map_irq.hpp?ts=4)||
|Port Mapping MTU/ポートマッピング MTU|[port_map_mtu.hpp](port_map_mtu.hpp?ts=4)||
|FLASH Definition/FLASH 定義|[flash.hpp](flash.hpp?ts=4)||
|A/D Definition/A/D 定義|[s12adb.hpp](s12adb.hpp?ts=4)||
|System Definition/システム定義|[system.hpp](system.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 64|
|---|---|
|VCL|VCL(13)|
|Reset Input/リセット入力|RES#(7)|
|Mode Controle/モード制御|MD/FINED(6)|
|B/UB|P14(20)|
|RXD|P15/RXD1(19)|
|TXD|P16/TXD1(18)|
|USB_VCC|VCC_USB(21)|
|USB_VSS|VSS_USB(24)|
|USB+|USB_DP(23)|
|USB-|USB_DM(22)|
|Power/電源|VCC(15), VCC(38)|
|GND/接地|VSS(14), VSS(40)|
|Analog Power/アナログ電源|AVCC0(63)|
|Analog GND/アナログ接地|AVSS0(62)|
|Analog Refarence L/アナログ基準電源Ｌ|VREFL0(59)|
|Analog Refarence H/アナログ基準電源Ｈ|VREFH0(61)|
|OSC out|XTAL(11)|
|OSC in|EXTAL(12)|
|Sub OSC out|XCOUT(8)|
|Sub OSC in|XCIN(9)|

- VCL: 4.7uF/25V

|Mode/モード|MD|
|---|:---:|
|Serial BOOT/シリアルブート|0|
|Single Chip/シングルチップ|1|

---

## port map order / ポートマップ候補

### LFQFP64

|Peripheral|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|SCI1 / RXD|P15 (19)|P30 (4)|PC6 (28)|-|
|SCI1 / TXD|P16 (18)|P26 (3)|PC7 (27)|-|
|SCI1 / SCK|P17 (17)|P27 (2)|PC5 (29)|-|
|SCI5 / RXD|PA3 (43)|PC2 (32)|-|-|
|SCI5 / TXD|PA4 (42)|PC3 (31)|-|-|
|SCI5 / SCK|PA1 (44)|PC4 (30)|-|-|
|SCI12 / RXD|PE2 (49)|P17 (17)|-|-|
|SCI12 / TXD|PE1 (50)|P14 (20)|-|-|
|SCI12 / SCK|PE0 (51)|P27 (2)|-|-|
|RIIC0 / SCL|P16 (18)|PB0 (39)|-|-|
|RIIC0 / SDA|P17 (17)|PA6 (41)|-|-|
|RSPI0 / RSPCK|P15 (19)|PB0 (39)|PC5 (29)|PE3 (48)|
|RSPI0 / MOSI|P16 (18)|PA6 (41)|PC6 (28)|PE4 (47)|
|RSPI0 / MISO|P17 (17)|PA3 (43)|PC7 (27)|PA3 (43)|
|RSPI0 / SSL0|P14 (20)|PA4 (42)|PC4 (30)|-|
|RSPI0 / SSL1|PA0 (45)|-|-|-|
|RSPI0 / SSL2|PA1 (44)|-|-|-|
|RSPI0 / SSL3|PC2 (32)|-|-|-|

---

## rx_prog Flash Programming / rx_prog フラッシュプログラム

||Support/サポート|operation verification/動作検証|
|-|:-:|:-:|
|[rxprog](../rxprog)|||

---

Translated with www.DeepL.com/Translator (free version)

---

## License

[MIT](../LICENSE)
