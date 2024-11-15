
## RX13T features / 特徴

- RXv1 core / RXv1 コア
- Maximum operating frequency 32MHz / 最大動作周波数 32MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 2.7V ～ 5.5V Operation / 動作
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 8 Bits D/A / ８ビットＤ／Ａ変換器

### Package/パッケージ

|R5F513T---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F513TxxxFL|LFQFP|48|0.50|
|R5F513TxxxFJ|LQFP|32|0.80|
|R5F513TxxxNE|HWQFN|48|0.50|
|R5F513TxxxNH|HWQFN|32|0.50|

### Ambient operating temperature/動作周囲温度

|R5F513T--X--|degree Celsius|
|---|:-:|
|R5F513TxxDxx|-40 ～ +85℃|
|R5F513TxxGxx|-40 ～ +105℃|

### Memoey size/メモリ容量

|R5F513TX----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F513T5xxxx|128K|12K|0|
|R5F513T3xxxx|64K|12K|0|

---

## RX13T Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Link File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F513T5|128K|12K|4K|[R5F513T5.ld](R5F513T5.ld?ts=4)|512|256|
|R5F513T3|64K|12K|4K|[R5F513T3.ld](R5F513T3.ld?ts=4)|512|256|

---

## RX13T Dedicated class / 専用クラス

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
|A/D Definition/A/D 定義|[s12ad.hpp](s12ad.hpp?ts=4)||
|D/A Definition/D/A 定義|[da.hpp](da.hpp?ts=4)||
|POE3 Definition/POE3 定義|[poe3.hpp](poe3.hpp?ts=4)||

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

## rx_prog Flash Programming / rx_prog フラッシュプログラム

||Support/サポート|operation verification/動作検証|
|-|:-:|:-:|
|[rxprog](../rxprog)|-|-|

---

Translated with www.DeepL.com/Translator (free version)

---

## License

[MIT](../LICENSE)
