## RX72T features / 特徴

- RXv3 core / RXv3 コア
- Maximum operating frequency 200MHz / 最大動作周波数 200MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 2.7V ～ 5.5V Operation / 動作
- USB2.0 Full Speed, Host, Function (Optional)
- CAN Module (CAN) / CAN モジュール (CAN)
- Arithmetic Unit for Trigonometric Functions (TFUv1) / 三角関数演算器 (TFUv1)
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 12 Bits D/A / １２ビットＤ／Ａ変換器

### Package/パッケージ

|R5F572T---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F572TxxxFB|LFQFP|144|0.50|
|R5F572TxxxFP|LFQFP|100|0.50|

### Ambient operating temperature/動作周囲温度

|R5F572T--X--|degree Celsius|
|---|:-:|
|R5F572TxxDxx|-40 ～ +85℃|
|R5F572TxxGxx|-40 ～ +105℃|

### PGA, TSIP, USB

|R5F572T-X---|PGA|TSIP|USB|
|---|:-:|:-:|:-:|
|R5F572TxAxxx|〇|-|-|
|R5F572TxBxxx|-|-|-|
|R5F572TxCxxx|〇|-|〇|
|R5F572TxExxx|〇|〇|-|
|R5F572TxFxxx|-|〇|-|
|R5F572TxGxxx|〇|〇|〇|

### Memoey size/メモリ容量

|R5F572TX----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F572TKxxxx|1M|128K|32K|
|R5F572TFxxxx|512K|128K|32K|

---

## RX72T Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F572TK|1024K|128K+16K|32K|[R5F572TK.ld](R5F572TK.ld?ts=4)|7168|1024|
|R5F572TF|512K|128K+16K|32K|[R5F572TF.ld](R5F572TF.ld?ts=4)|7168|1024|

RAM: 16K(With ECC)

---

## RX72T Dedicated class / 専用クラス

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
|Port Mapping TMR/ポートマッピング TMR|[port_map_tmr.hpp](port_map_tmr.hpp?ts=4)||
|Port Mapping GPTW/ポートマッピング GPTW|[port_map_gptw.hpp](port_map_gptw.hpp?ts=4)||
|POE3 Definition/POE3 定義|[poe3.hpp](poe3.hpp?ts=4)||
|A/D Definition/A/D 定義|[s12adh.hpp](s12adh.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 100|LFQFP 144|
|---|---|---|
|VCL|VCL(5)|VCL(10)|
|Reset Input/リセット入力|RES#(10)|RES#(15)|
|Mode Controle/モード制御|MD/FINED(6)|MD/FINED(11)|
|UB|P00/UB(4)|P00/UB(9)|
|EMLE|EMLE(2)|EMLE(7)|
|RXD|PD5/RXD1(20)|PD5/RXD1(25)|
|TXD|PD3/TXD1(22)|PD3/TXD1(27)|
|UPSEL|PE2/UPSEL(15)|PE2/UPSEL(20)|
|USB_VCC|VCC_USB(26)|VCC_USB(38)|
|USB_VSS|VSS_USB(31)|VSS_USB(37)|
|USB+|USB_DP(25)|USB_DP(36)|
|USB-|USB_DM(24)|USB_DM(35)|
|Power/電源|VCC(14), VCC(29), VCC(42), VCC(60)|VCC(6), VCC(19), VCC(42), VCC(64), VCC(88)|
|GND/接地|VSS(3), VSS(12), VSS(31), VSS(44), VSS(62)|VSS(8), VSS(17), VSS(44), VSS(66), VSS(90)|
|Analog Power/アナログ電源|AVCC0(93), AVCC1(92), AVCC2(72)|AVCC0(134), AVCC1(133), AVCC2(104), AVCC2(105)|
|Analog GND/アナログ接地|AVSS0(94), AVSS1(95), AVSS2(73)|AVSS0(135), AVSS1(136), AVSS2(106)|
|Gain GND/ゲイン接地|PGAVSS0(91), PGAVSS1(86)|PGAVSS0(132), PGAVSS1(124)|
|OSC in|EXTAL(13)|EXTAL(18)|
|OSC out|XTAL(11)|XTAL(16)|

- VCL: 0.47uF/25V

|Mode/モード|UB|MD|UPSEL|
|---|:---:|:---:|:---:|
|Serial BOOT/シリアルブート|0|0|-|
|USB Boot/USB ブート|1|0|0/1|
|Single Chip/シングルチップ|-|1|-|

- EMLE: 0

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
