
## RX13T feature / 特徴

- RXv1 core / コア
- Maximum operating frequency / 最大動作周波数 32MHz
- FPU on board (single precision floating point) / FPU 搭載（単精度浮動小数点）
- 2.7V ～ 5.5V Operation / 動作
- 12 Bits A/D, 8 Channels (Sample hold: 3 Channels) / ８チャネル１２ビットＡ／Ｄ変換器（サンプルホールド３チャネル）
- 8 Bits D/A, 1 Channel (for Compalator) / コンパレーター専用 8 ビットＤ／Ａ変換器

---

## RX13T Linker file / リンカーファイル

|Type|Program|RAM|Data Flash|Source|
|---|:-:|:-:|:-:|---|
|R5F513T3|64K|12K|4K|[R5F513T3.ld](R5F513T3.ld)|
|R5F513T5|128K|12K|4K|[R5F513T5.ld](R5F513T5.ld)|

---

## RX13T Dedicated class / 専用クラス

|Function/機能|Source|Remarks/備考|
|---|---|:-:|
|Peripheral Name/ペリフェラル名|[peripheral.hpp](peripheral.hpp)||
|Hardware-specific Definition/ハード固有定義|[board_profile.hpp](board_profile.hpp)||
|Operating Frequency Definition/動作周波数定義|[clock_profile.hpp](clock_profile.hpp)||
|Power Control/電力制御|[power_mgr.hpp](power_mgr.hpp)||
|Port Definition/ポート定義|[port.hpp](port.hpp)||
|Interrupt Definition/割り込み定義|[icu.hpp](icu.hpp)||
|Interrupt Management/割り込み管理|[icu_mgr.hpp](icu_mgr.hpp)||
|Port Function Definition/ポート機能定義|[mpc.hpp](mpc.hpp)||
|Port Mapping/ポートマッピング|[port_map.hpp](port_map.hpp)||
|Port Mapping IRQ/ポートマッピング IRQ|[port_map_irq.hpp](port_map_irq.hpp)||
|Port Mapping MTU/ポートマッピング MTU|[port_map_mtu.hpp](port_map_mtu.hpp)||
|A/D Definition/A/D 定義|[s12ad.hpp](s12ad.hpp)||
|D/A Definition/D/A 定義|[da.hpp](da.hpp)||
|POE3 Definition/POE3 定義|[poe3.hpp](poe3.hpp)||
|System Definition/システム定義|[RX24T/system.hpp](../RX24T/system.hpp)|RX24T と共有|
|System I/O Definition/システム I/O 定義|[RX24T/system_io.hpp](../RX24T/system_io.hpp)|RX24T と共有|

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 48|
|---|---|
|VCL|VCL(1)|
|Reset Input/リセット入力|RES#(3)|
|Mode Controle/モード制御|MD/FINED(2)|
|RXD|PB7/RXD1(13)|
|TXD|PB6/TXD1(14)|
|Power/電源|VCC(7), VCC(32)|
|GND/接地|VSS(5), VSS(33)|
|Analog Power/アナログ電源|AVCC0(45)|
|Analog GND/アナログ接地|AVSS0(46)|
|OSC out|XTAL(4)|
|OSC in|EXTAL(6)|

- VCL: 4.7uF/25V

|Mode/モード|MD|
|---|:---:|
|Serial BOOT/シリアルブート|0|
|Single Chip/シングルチップ|1|

---

Translated with www.DeepL.com/Translator (free version)

---

## License

[MIT](../LICENSE)
