
## RX63T features / 特徴

- RXv1 core / RXv1 コア
- Maximum operating frequency 100MHz / 最大動作周波数 100MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 3.3V ～ 5.0V Operation / 動作
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 10 Bits D/A / １０ビットＤ／Ａ変換器

### Package/パッケージ

|R5F563T---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F563TxxxFB|LFQFP|144|0.50|
|R5F563TxxxFP|LFQFP|100|0.50|
|R5F563TxxxFP|LFQFP|100|0.50|
|R5F563TxxxFP|LFQFP|100|0.50|
|R5F563TxxxFP|LFQFP|100|0.50|
|R5F563TxxxFP|LFQFP|100|0.50|

### Ambient operating temperature/動作周囲温度

|R5F563T--X--|degree Celsius|
|---|:-:|
|R5F563TxxDxx|-40 ～ +85℃|
|R5F563TxxGxx|-40 ～ +105℃|

### VCC, CAN

|R5F563T-X---|VCC|CAN|
|---|:-:|:-:|
|R5F563TxAxxx|5V|〇|
|R5F563TxBxxx|3V|〇|
|R5F563TxDxxx|5V|-|
|R5F563TxExxx|3V|-|

### Memoey size/メモリ容量

|R5F563TX----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F563TExxxx|512K|48K|32K|
|R5F563TCxxxx|384K|32K|32K|
|R5F563TBxxxx|256K|24K|32K|
|R5F563T6xxxx|64K|8K|8K|
|R5F563T5xxxx|48K|8K|8K|
|R5F563T4xxxx|32K|8K|8K|

---

## RX63T Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F563T6|64K|8K|8K|[R5F563T6.ld](R5F563T6.ld?ts=4)|768|256|

---

## RX63T Dedicated class / 専用クラス

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
|Port Mapping GPT/ポートマッピング GPT|[port_map_gpt.hpp](port_map_gpt.hpp?ts=4)||
|A/D Definition/A/D 定義|[ad.hpp](ad.hpp?ts=4)||
|BUS Definition/BUS 定義|[bus.hpp](bus.hpp?ts=4)||
|D/A Definition/D/A 定義|[da.hpp](da.hpp?ts=4)||
|DPC Definition/DPC 定義|[dpc.hpp](dpc.hpp?ts=4)||
|FLASH Definition/FLASH 定義|[flash.hpp](flash.hpp?ts=4)||
|GPT Definition/GPT 定義|[gpt.hpp](gpt.hpp?ts=4)||
|LVDA Definition/LVDA 定義|[lvda.hpp](lvda.hpp?ts=4)||
|POE3 Definition/POE3 定義|[poe3.hpp](poe3.hpp?ts=4)||
|A/D Definition/A/D 定義|[s12adb.hpp](s12adb.hpp?ts=4)||
|System Definition/システム定義|[system.hpp](system.hpp?ts=4)||
|System I/O Definition/システム I/O 定義|[system_io.hpp](system_io.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LQFP 64|
|---|---|---|
|VCL|VCL(3)|
|Reset Input/リセット入力|RES#(6)|
|Mode Controle/モード制御|MD/FINED(5)|
|EMLE|EMLE(1)|
|RXD|PD5/RXD1(14)|
|TXD|PD3/TXD1(16)|
|Power/電源|VCC(10), VCC(20), VCC(42)|
|GND/接地|VSS(8), VSS(22), VSS(44)|
|Analog Power/アナログ電源|AVCC0(57)|
|Analog GND/アナログ接地|AVSS0(60)|
|Analog Refarence H/アナログ基準電源 H|VREFH0(58)|
|Analog Refarence L/アナログ基準電源 L|VREFL0(59)|
|OSC in|EXTAL(9)|
|OSC out|XTAL(7)|

- VCL: 0.1uF/25V

|Mode/モード|MD|
|---|:---:|
|Serial BOOT/シリアルブート|0|
|Single Chip/シングルチップ|1|

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
