
## RX210 features / 特徴

- RXv1 core / RXv1 コア
- Maximum operating frequency 50MHz / 最大動作周波数 50MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 1.62V ～ 5.5V Operation / 動作
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 10 Bits D/A / １０ビットＤ／Ａ変換器

### Package/パッケージ

|R5F5210---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F5210xxxFB|LQFP|144|0.50|
|R5F5210xxxFP|LQFP|100|0.50|
|R5F5210xxxFN|LQFP|80|0.50|
|R5F5210xxxFM|LQFP|64|0.50|
|R5F5210xxxFL|LQFP|48|0.50|
|R5F5210xxxFF|LQFP|80|0.65|
|R5F5210xxxFK|LQFP|64|0.80|
|R5F5210xxxLK|TFLGA|145|0.50|
|R5F5210xxxLA|TFLGA|100|0.50|
|R5F5210xxxLJ|TFLGA|100|0.65|
|R5F5210xxxLH|TFLGA|64|0.65|
|R5F5210xxxBM|WLBGA|69|0.40|

### Ambient operating temperature/動作周囲温度

|R5F5210--X--|degree Celsius|
|---|:-:|
|R5F5210xxDxx|-40 ～ +85℃|
|R5F5210xxGxx|-40 ～ +105℃|

### Chip version/チップバージョン

|R5F5210-X---|chip version|
|---|:-:|
|R5F5210xAxxx|A|
|R5F5210xBxxx|B|
|R5F5210xCxxx|C|

### Memoey size/メモリ容量

|R5F5210X----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F5210Bxxxx|1024K|96K|8K|
|R5F5210Axxxx|768K|96K|8K|
|R5F52108xxxx|512K|64K|8K|
|R5F52107xxxx|384K|64K|8K|
|R5F52106xxxx|256K|32K|8K|
|R5F52105xxxx|128K|20K|8K|
|R5F52104xxxx|96K|16K|8K|
|R5F52103xxxx|64K|12K|8K|

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|8K|128|2/2048|2|0x??|4|

---

## RX210 Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F5210B|1024K|96K|8K|[R5F5210B.ld](R5F5210B.ld?ts=4)|3072|1024|

---

## RX210 Dedicated class / 専用クラス

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
|Port Mapping TPU/ポートマッピング TPU|[port_map_tpu.hpp](port_map_tpu.hpp?ts=4)||
|Port Mapping MTU/ポートマッピング TMR|[port_map_tmr.hpp](port_map_tmr.hpp?ts=4)||
|CMPA Definition/CMPA 定義|[cmpb.hpp](cmpa.hpp?ts=4)||
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
|Power/電源|VCC(14), VCC(60)|
|GND/接地|VSS(12), VSS(62)|
|Analog Power/アナログ電源|AVCC0(97)|
|Analog GND/アナログ接地|AVSS0(99)|
|Analog Refarence L/アナログ基準電源Ｌ|VREFL0(94)|
|Analog Refarence H/アナログ基準電源Ｈ|VREFH0(96)|
|OSC out|XTAL(11)|
|OSC in|EXTAL(13)|
|Sub OSC out|XCOUT(9)|
|Sub OSC in|XCIN(8)|

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
|[rxprog](../rxprog)|-|-|

---

Translated with www.DeepL.com/Translator (free version)

---

## License

[MIT](../LICENSE)
