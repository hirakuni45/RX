
## RX260/RX261 features / 特徴

- RXv3 core / RXv3 コア
- Maximum operating frequency 64MHz / 最大動作周波数 64MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 1.6V ～ 5.5V Operation / 動作
- High-speed operation mode: 84 µA/MHz / 高速動作モード：84 µA/MHz
- USB2.0 Full Speed, Host, Function
- CAN FD Module (CANFD) / CAN FD (CAN FD)
- Real time clock / リアルタイムクロック内蔵
- Capacitive touch sensor / 静電容量式タッチセンサ
- Renesas Secure IP (RSIP-E11A) / セキュリティ機能
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 8 Bits D/A / ８ビットＤ／Ａ変換器

### Package/パッケージ

|R5F526y---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F526yxxxFP|LFQFP|100|0.50|
|R5F526yxxxFN|LQFP|80|0.50|
|R5F526yxxxFM|LFQFP|64|0.50|
|R5F526yxxxFL|LQFP|48|0.50|
|R5F526yxxxNE|HWQFN|48|0.50|

### Ambient operating temperature/動作周囲温度

|R5F526y--X--|degree Celsius|
|---|:-:|
|R5F526yxxDxx|-40 ～ +85℃|
|R5F526yxxGxx|-40 ～ +105℃|

### Crypt/暗号, USB, CANFD

|R5F526y-X---|Crypt|USB|CANFD|
|---|:-:|:-:|:-:|
|R5F5261xAxxx|-|〇|〇|
|R5F5261xBxxx|〇|〇|〇|
|R5F5260xAxxx|-|-|-|

### Memoey size/メモリ容量

|R5F526yX----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F526y8xxxx|512K|128K|8K|
|R5F526y7xxxx|384K|128K|8K|
|R5F526y6xxxx|256K|128K|8K|

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|8K|256|1/256|1|0xFF|4|

---

## RX260/RX261 Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F526TF|512K|128K|8K|[R5F52618.ld](R5F52618.ld?ts=4)|2048|1024|

---

## RX260/RX261 Dedicated class / 専用クラス

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
