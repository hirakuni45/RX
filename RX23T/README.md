
## RX23T feature / 特徴

- RXv2 core / コア
- Maximum operating frequency / 最大動作周波数 40MHz
- IEEE754 FPU on board (single precision floating point) / FPU 搭載（単精度浮動小数点）
- 2.7V ～ 5.5V Operation / 動作
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 8 Bits D/A (for Compalator) / ８ビットＤ／Ａ変換器（コンパレーター用）

---

## RX23T Linker file / リンカーファイル

|Type|Program|RAM|Data Flash|Source|
|---|:-:|:-:|:-:|---|
|R5F523T5|128K|12K|-|[R5F523T5.ld](R5F523T5.ld)|

---

## RX23T Dedicated class / 専用クラス

|Function/機能|Source|Remarks/備考|
|---|---|:-:|
|Peripheral Name/ペリフェラル名|[peripheral.hpp](peripheral.hpp)||
|Hardware-specific Definition/ハード固有定義|[board_profile.hpp](board_profile.hpp)||
|Operating Frequency Definition/動作周波数定義|[clock_profile.hpp](clock_profile.hpp)||
|Power Control/電力制御|[power_mgr.hpp](power_mgr.hpp)||
|Port Definition/ポート定義|[port.hpp](port.hpp)||
|Interrupt Definition/割り込み定義|[icu.hpp](icu.hpp)||
|Port Function Definition/ポート機能定義|[mpc.hpp](mpc.hpp)||
|Port Mapping/ポートマッピング|[port_map.hpp](port_map.hpp)||
|Port Mapping IRQ/ポートマッピング IRQ|[port_map_irq.hpp](port_map_irq.hpp)||
|Port Mapping MTU/ポートマッピング MTU|[port_map_mtu.hpp](port_map_mtu.hpp)||
|Port Mapping TMR/ポートマッピング TMR|[port_map_tmr.hpp](port_map_tmr.hpp)||
|A/D Definition/A/D 定義|[s12ad.hpp](s12ad.hpp)||

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

Translated with www.DeepL.com/Translator (free version)

---

## License

[MIT](../LICENSE)
