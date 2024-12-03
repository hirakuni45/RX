
## RX23T features / 特徴

- RXv2 core / RXv2 コア
- Maximum operating frequency 40MHz / 最大動作周波数 40MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 2.7V ～ 5.5V Operation / 動作
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 8 Bits D/A (for Compalator) / ８ビットＤ／Ａ変換器（コンパレーター用）

### Package/パッケージ

|R5F523T---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F523TxxxFM|LFQFP|64|0.50|
|R5F523TxxxFD|LQFP|52|0.65|
|R5F523TxxxFL|LFQFP|48|0.50|

### Ambient operating temperature/動作周囲温度

|R5F523T--X--|degree Celsius|
|---|:-:|
|R5F523TxxDxx|-40 ～ +85℃|
|R5F523TxxGxx|-40 ～ +105℃|

### Memoey size/メモリ容量

|R5F523TX----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F523T5xxxx|128K|12K|0|
|R5F523T3xxxx|64K|12K|0|

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|0K|-|-|-|-|0|

---

## RX23T Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Source|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F523T5|128K|12K|-|[R5F523T5.ld](R5F523T5.ld?ts=4)|512|256|

---

## RX23T Dedicated class / 専用クラス

|Function/機能|Source|Remarks/備考|
|---|---|:-:|
|Peripheral Name/ペリフェラル名|[peripheral.hpp](peripheral.hpp?ts=4)||
|Hardware-specific Definition/ハード固有定義|[board_profile.hpp](board_profile.hpp?ts=4)||
|Operating Frequency Definition/動作周波数定義|[clock_profile.hpp](clock_profile.hpp?ts=4)||
|Power Control/電力制御|[power_mgr.hpp](power_mgr.hpp?ts=4)||
|Port Definition/ポート定義|[port.hpp](port.hpp?ts=4)||
|Interrupt Definition/割り込み定義|[icu.hpp](icu.hpp?ts=4)||
|Port Function Definition/ポート機能定義|[mpc.hpp](mpc.hpp?ts=4)||
|Port Mapping/ポートマッピング|[port_map.hpp](port_map.hpp?ts=4)||
|Port Mapping IRQ/ポートマッピング IRQ|[port_map_irq.hpp](port_map_irq.hpp?ts=4)||
|Port Mapping MTU/ポートマッピング MTU|[port_map_mtu.hpp](port_map_mtu.hpp?ts=4)||
|Port Mapping TMR/ポートマッピング TMR|[port_map_tmr.hpp](port_map_tmr.hpp?ts=4)||
|A/D Definition/A/D 定義|[s12ad.hpp](s12ad.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 64|
|---|---|
|VCL|VCL(3)|
|Reset Input/リセット入力|RES#(6)|
|Mode Controle/モード制御|MD/FINED(5)|
|RXD|PD5/RXD1(14)|
|TXD|PD3/TXD1(16)|
|Power/電源|VCC(10), VCC(42)|
|GND/接地|VSS(8), VSS(44)|
|Analog Power/アナログ電源|AVCC0(57)|
|Analog GND/アナログ接地|AVSS0(60)|
|Analog Refarence L0/アナログ基準電源Ｌ0|VREFL0(59)|
|Analog Refarence H0/アナログ基準電源Ｈ0|VREFH0(58)|
|OSC in|EXTAL(9)|
|OSC out|XTAL(7)|

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
