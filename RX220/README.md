
## RX220 features / 特徴

- RXv1 core / RXv1 コア
- Maximum operating frequency 32MHz / 最大動作周波数 32MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 1.62V ～ 5.5V Operation / 動作
- 12 Bits A/D / １２ビットＡ／Ｄ変換器

### Package/パッケージ

|R5F5220---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F5220xxxFP|LQFP|100|0.50|
|R5F5220xxxFM|LQFP|64|0.50|
|R5F5220xxxFK|LQFP|64|0.50|
|R5F5220xxxFL|LQFP|48|0.50|

### Ambient operating temperature/動作周囲温度

|R5F5220--X--|degree Celsius|
|---|:-:|
|R5F5220xxDxx|-40 ～ +85℃|
|R5F5220xxGxx|-40 ～ +105℃|

### Memoey size/メモリ容量

|R5F5220X----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F52206xxxx|256K|16K|8K|
|R5F52205xxxx|128K|8K|8K|
|R5F52203xxxx|64K|8K|8K|
|R5F52201xxxx|32K|4K|8K|

---

## RX220 Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F52206|256K|16K|8K|[R5F52206.ld](R5F52206.ld?ts=4)|768|256|

---

## RX220 Dedicated class / 専用クラス

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
|BUS Definition/BUS 定義|[bus.hpp](bus.hpp?ts=4)||
|CMPA Definition/CMPA 定義|[cmpa.hpp](cmpa.hpp?ts=4)||
|ELC Definition/ELC 定義|[elc.hpp](elc.hpp?ts=4)||
|IrDA Definition/IrDA 定義|[irda.hpp](irda.hpp?ts=4)||
|LVDA Definition/LVDA 定義|[lvda.hpp](lvda.hpp?ts=4)||
|MTU2 Definition/MTU2 定義|[mtu2.hpp](mtu2.hpp?ts=4)||
|POE2 Definition/POE2 定義|[poe2.hpp](poe2.hpp?ts=4)||
|RTC Definition/RTC 定義|[rtc.hpp](rtc.hpp?ts=4)||
|A/D Definition/A/D 定義|[s12ad.hpp](s12ad.hpp?ts=4)||
|FLASH Definition/FLASH 定義|[flash.hpp](flash.hpp?ts=4)||
|FLASH I/O Definition/FLASH I/O 定義|[flash_io.hpp](flash_io.hpp?ts=4)||
|System Definition/システム定義|[system.hpp](system.hpp?ts=4)||
|System I/O Definition/システム I/O 定義|[system_io.hpp](system_io.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 64|
|---|---|
|VCL|VCL(2)|
|Reset Input/リセット入力|RES#(6)|
|Mode Controle/モード制御|MD/FINED(3)|
|B/UB|PC7(27)|
|RXD|P30/RXD1(14)|
|TXD|P26/TXD1(16)|
|Power/電源|VCC(10), VCC(38)|
|GND/接地|VSS(8), VSS(40)|
|Analog Power/アナログ電源|AVCC0(62)|
|Analog GND/アナログ接地|AVSS0(64)|
|Analog Refarence L/アナログ基準電源Ｌ|VREFL0(59)|
|Analog Refarence H/アナログ基準電源Ｈ|VREFH0(61)|
|OSC out|XTAL(7)|
|OSC in|EXTAL(9)|
|Sub OSC out|XCOUT(5)|
|Sub OSC in|XCIN(4)|

- VCL: 0.1uF/25V

|Mode/モード|B/UB|MD|
|---|:---:|:---:|
|Serial BOOT/シリアルブート|0|0|
|User Boot/ユーザーブート|1|0|
|Single Chip/シングルチップ|-|1|

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
