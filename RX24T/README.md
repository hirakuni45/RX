
## RX24T features / 特徴

- RXv2 core / RXv2 コア
- Maximum operating frequency 80MHz / 最大動作周波数 80MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 2.7V ～ 5.5V Operation / 動作
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 8 Bits D/A / ８ビットＤ／Ａ変換器

---

## RX24T Linker file / リンカーファイル

|Type|Program|RAM|Data Flash|Source|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F524T8|128K|16K|8K|[R5F524T8.ld](R5F524T8.ld)|1024|512|
|R5F524TA|256K|16K|8K|[R5F524TA.ld](R5F524TA.ld)|1024|512|

---

## RX24T Dedicated class / 専用クラス

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
|Port Mapping TMR/ポートマッピング TMR|[port_map_tmr.hpp](port_map_tmr.hpp)||
|Port Mapping GPT/ポートマッピング GPT|[port_map_gpt.hpp](port_map_gpt.hpp)||
|FLASH Definition/FLASH 定義|[flash.hpp](flash.hpp)||
|FLASH Definition/FLASH I/O 定義|[flash_io.hpp](flash_io.hpp)||
|LVDA Definition/LVDA 定義|[lvda.hpp](lvda.hpp)||
|POE3 Definition/POE3 定義|[poe2.hpp](poe3.hpp)||
|D/A Definition/D/A 定義|[da.hpp](da.hpp)||
|A/D Definition/A/D 定義|[s12ad.hpp](s12ad.hpp)||
|System Definition/システム定義|[system.hpp](system.hpp)||
|System I/O Definition/システム I/O 定義|[system_io.hpp](system_io.hpp)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 100|
|---|---|---|
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

## rx_prog Flash Programming / rx_prog フラッシュプログラム

||Support/サポート|operation verification/動作検証|
|-|:-:|:-:|
|[rxprog](../rxprog)|〇|〇|

---

Translated with www.DeepL.com/Translator (free version)

---

## License

[MIT](../LICENSE)
