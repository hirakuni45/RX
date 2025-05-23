## RX671 features / 特徴

- RXv3 core / RXv3 コア
- Maximum operating frequency 120MHz / 最大動作周波数 120MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 2.7V ～ 5.5V Operation / 動作
- USB2.0 Full Speed, Host, Function
- CAN (ISO11898-1)
- Serial Sound Interface (SSIE) / シリアルサウンドインタフェース (SSIE)
- SD Host Interface (SDHI) / SD ホストインタフェース (SDHI)
- 12 Bits A/D / １２ビットＡ／Ｄ変換器

### Package/パッケージ

|R5F5671---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F5671xxxLE|TFLGA|145|0.65|
|R5F5671xxxLK|TFLGA|145|0.50|
|R5F5671xxxFB|LFQFP|144|0.50|
|R5F5671xxxFP|LFQFP|100|0.50|
|R5F5671xxxLJ|TFLGA|100|0.65|
|R5F5671xxxFM|LFQFP|64|0.50|
|R5F5671xxxBP|TFBGA|64|0.50|
|R5F5671xxxNE|HWQFN|48|0.50|

### Ambient operating temperature/動作周囲温度

|R5F5671--X--|degree Celsius|
|---|:-:|
|R5F5671xxDxx|-40 ～ +85℃|
|R5F5671xxGxx|-40 ～ +105℃|

### Crypt/暗号

|R5F5671-X---|Crypt|
|---|:-:|
|R5F5671xDxxx|-|
|R5F5671xHxxx|〇|

### Memoey size/メモリ容量

|R5F5671X----|Code Flash|RAM|Data Flash|
|---|:-:|:-:|:-:|
|R5F56719xxxx|1M|384K|8K|
|R5F5671Cxxxx|1.5M|384K|8K|
|R5F5671Exxxx|2M|384K|8K|

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|8K|64|4/64|4|0x??|4|

---

## RX671 Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F5671C|1536K|384K+4K|32K|[R5F5671C.ld](R5F5671C.ld?ts=4)|14336|2048|
|R5F5671E|2048K|384K+4K|32K|[R5F5671E.ld](R5F5671E.ld?ts=4)|14336|2048|

---

## RX671 Dedicated class / 専用クラス

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
|Port Mapping MTU/ポートマッピング MTU|[port_map_mtu.hpp](port_map_mtu.hpp?ts=4)||
|Port Mapping QSPI/ポートマッピング QSPI|[port_map_qspi.hpp](port_map_qspi.hpp?ts=4)||
|Port Mapping TMR/ポートマッピング TMR|[port_map_tmr.hpp](port_map_tmr.hpp?ts=4)||
|Port Mapping TPU/ポートマッピング TPU|[port_map_tpu.hpp](port_map_tpu.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 100|LFQFP 144|
|---|---|---|
|VCL|VCL(5)|VCL(14)|
|Reset Input/リセット入力|RES#(10)|RES#(19)|
|Mode Controle/モード制御|MD/FINED(7)|MD/FINED(16)|
|UB|PC7/UB(45)|PC7/UB(60)|
|EMLE|EMLE(2)|EMLE(10)|
|RXD|P30/RXD1(20)|P30/RXD1(29)|
|TXD|P26/TXD1(22)|P26/TXD1(31)|
|UPSEL|P35/UPSEL(15)|P35/UPSEL(24)|
|USB_VCC|VCC_USB(35)|VCC_USB(46)|
|USB_VSS|VSS_USB(38)|VSS_USB(49)|
|USB+|USB_DP(37)|USB_DP(48)|
|USB-|USB_DM(36)|USB_DM(47)|
|Power/電源|VCC(14), VCC(60)|VCC(23), VCC(59), VCC(74), VCC(91)|
|Power/電源||VCC(103), VCC(118), VCC(132)|
|GND/接地|VSS(12), VSS(62)|VSS(12), VSS(21), VSS(57), VSS(76)|
|GND/接地||VSS(93), VSS(105), VSS(116), VSS(130)|
|Analog Power/アナログ電源|AVCC0(97), AVCC1(1)|AVCC0(143), AVCC1(3)|
|Analog GND/アナログ接地|AVSS0(99), AVSS1(3)|AVSS0(1), AVSS1(5)|
|Analog Refarence L0/アナログ基準電源Ｌ0|VREFL0(94)|VREFL0(140)|
|Analog Refarence H0/アナログ基準電源Ｈ0|VREFH0(96)|VREFH0(142)|
|VBATT|VBATT(6)|VBATT(15)|
|OSC in|EXTAL(13)|EXTAL(22)|
|OSC out|XTAL(11)|XTAL(20)|
|Sub OSC in|XCIN(8)|XCIN(17)|
|Sub OSC out|XCOUT(9)|XCOUT(18)|

- VCL: 0.22uF/25V

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
|[rxprog](../rxprog)|-|-|

---

Translated with www.DeepL.com/Translator (free version)

---

## License

[MIT](../LICENSE)
