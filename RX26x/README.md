
## RX260/RX261 features / 特徴

- RXv3 core / RXv3 コア
- Maximum operating frequency 64MHz / 最大動作周波数 64MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 1.6V ～ 5.5V Operation / 動作
- High-speed operation mode: 84 µA/MHz / 高速動作モード：84 µA/MHz
- CAN FD Module (CANFD) / CAN FD (CAN FD)
- Arithmetic Unit for Trigonometric Functions (TFUv2) / 三角関数演算器 (TFUv2)
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 8 Bits D/A / ８ビットＤ／Ａ変換器

---

## RX26T Linker file / リンカーファイル

|Type|Program|RAM|Data Flash|Source|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F526TF|512K|128K|8K|[R5F52618.ld](R5F52618.ld?ts=4)|2048|1024|

---

## RX26T Dedicated class / 専用クラス

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
|Port Mapping TMR/ポートマッピング TMR|[port_map_tmr.hpp](port_map_tmr.hpp?ts=4)||
|Port Mapping GPTW/ポートマッピング GPTW|[port_map_gptw.hpp](port_map_gptw.hpp?ts=4)||
|FLASH Definition/FLASH 定義|[flash.hpp](flash.hpp?ts=4)||
|A/D Definition/A/D 定義|[s12adh.hpp](s12adh.hpp?ts=4)||
|System Definition/システム定義|[system.hpp](system.hpp?ts=4)||
|System I/O Definition/システム I/O 定義|[system_io.hpp](system_io.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 100|
|---|---|
|VCL|VCL(5)|
|Reset Input/リセット入力|RES#(10)|
|Mode Controle/モード制御|MD/FINED(7)|
|B/UB|PC7(45)|
|RXD|P30/RXD1(20)|
|TXD|P26/TXD1(22)|
|USB+|USB_DP(37)|
|USB-|USB_DM(36)|
|UPSEL|P35/UPSEL(15)|
|Power/電源|VCC(14), VCC(60)|
|GND/接地|VSS(12), VSS(62)|
|Analog Power/アナログ電源|AVCC0(97)|
|Analog GND/アナログ接地|AVSS0(99)|
|Analog Refarence L0/アナログ基準電源Ｌ０|VREFL0(94)|
|Analog Refarence H0/アナログ基準電源Ｈ０|VREFH0(96)|
|OSC in|EXTAL(13)|
|OSC out|XTAL(11)|
|Sub OSC in|XCIN(8)|
|Sub OSC out|XCOUT(9)|

- VCL: 4.7uF/25V

|Mode/モード|B/UB|MD|
|---|:---:|:---:|
|Serial BOOT/シリアルブート|0|0|
|USB Boot/USB ブート|1|0|
|Single Chip/シングルチップ|-|1|

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
