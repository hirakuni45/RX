
## RX113 features / 特徴

- RXv1 core / RXv1 コア
- Maximum operating frequency 32MHz / 最大動作周波数 32MHz
- 1.8V ～ 3.6V Operation / 動作
- USB2.0 Full Speed, Low Speed, Host, Function
- LCD Controller, Driver / LCD コントローラ、ドライバ
- Capacitive touch sensor / 静電容量式タッチセンサ
- Low power timer / ローパワータイマー
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 12 Bits D/A / １２ビットＤ／Ａ変換器

### Package/パッケージ

|R5F5113---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F5113xxxFP|LFQFP|100|0.50|
|R5F5113xxxLJ|TFLGA|100|0.65|
|R5F5113xxxFM|LFQFP|64|0.50|

### Ambient operating temperature/動作周囲温度

|R5F5113--X--|degree Celsius|
|---|:-:|
|R5F5113xxDxx|-40 ～ +85℃|
|R5F5113xxGxx|-40 ～ +105℃|

### Memoey size/メモリ容量

|R5F5113X----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F51138xxxx|512K|64K|8K|
|R5F51137xxxx|384K|64K|8K|
|R5F51136xxxx|256K|32K|8K|
|R5F51135xxxx|128K|32K|8K|

---

## RX113 Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F51138|512K|64K|8K|[R5F51138.ld](R5F51138.ld?ts=4)|3072|1024|
|R5F51136|256K|32K|8K|[R5F51136.ld](R5F51136.ld?ts=4)|1536|512|

---

## RX113 Dedicated class / 専用クラス

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
|System Definition/システム定義|[system.hpp](system.hpp?ts=4)||
|System I/O Definition/システム I/O 定義|[system_io.hpp](system_io.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 64|LFQFP 100|
|---|---|---|
|VCL|VCL(13)|VCL(22)|
|Reset Input/リセット入力|RES#(7)|RES#(16)|
|Mode Controle/モード制御|MD/FINED(6)|MD/FINED(15)|
|B/UB|P14(20)|P14(29)|
|RXD|P15/RXD1(19)|P15/RXD1(28)|
|TXD|P16/TXD1(18)|P16/TXD1(27)|
|USB_VCC|VCC_USB(21)|VCC_USB(30)|
|USB_VSS|VSS_USB(24)|VSS_USB(33)|
|USB+|USB_DP(23)|USB_DP(32)|
|USB-|USB_DM(22)|USB_DM(31)|
|Power/電源|VCC(15), VCC(38)|VCC(24), VCC(60)|
|GND/接地|VSS(14), VSS(40)|VSS(23), VSS(62)|
|Analog Power/アナログ電源|AVCC0(63)|AVCC0(98)|
|Analog GND/アナログ接地|AVSS0(62)|AVSS0(97)|
|Analog Refarence L0/アナログ基準電源Ｌ０|VREFL0(59)|VREFL0(94)|
|Analog Refarence H0/アナログ基準電源Ｈ０|VREFH0(61)|VREFH0(96)|
|Analog Refarence L/アナログ基準電源Ｌ|-|VREFL(92)|
|Analog Refarence H/アナログ基準電源Ｈ|-|VREFH(93)|
|OSC out|XTAL(11)|XTAL(20)|
|OSC in|EXTAL(12)|EXTAL(21)|
|Sub OSC out|XCOUT(8)|XCOUT(17)|
|Sub OSC in|XCIN(9)|XCIN(18)|

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
|[rxprog](../rxprog)|||

---

Translated with www.DeepL.com/Translator (free version)

---

## License

[MIT](../LICENSE)
