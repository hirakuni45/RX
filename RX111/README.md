
## RX111 features / 特徴

- RXv1 core / RXv1 コア
- Maximum operating frequency 32MHz / 最大動作周波数 32MHz
- 1.8V ～ 3.6V Operation / 動作
- USB2.0 Full Speed, Low Speed, Host, Function
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 8 Bits D/A / ８ビットＤ／Ａ変換器

### Package/パッケージ

|R5F5111---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F5111xxxFM|LFQFP|64|0.50|
|R5F5111xxxFK|LQFP|64|0.80|
|R5F5111xxxLF|WFLGA|64|0.50|
|R5F5111xxxFL|LFQFP|48|0.50|
|R5F5111xxxNE|HWQFN|48|0.50|
|R5F5111xxxNF|HWQFN|40|0.50|
|R5F5111xxxLM|WFLGA|36|0.50|

### Ambient operating temperature/動作周囲温度

|R5F5111--X--|degree Celsius|
|---|:-:|
|R5F5111xxDxx|-40 ～ +85℃|
|R5F5111xxGxx|-40 ～ +105℃|

### Memoey size/メモリ容量

|R5F5111X----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F51118xxxx|512K|64K|8K|
|R5F51117xxxx|384K|64K|8K|
|R5F51116xxxx|256K|32K|8K|
|R5F51115xxxx|128K|16K|8K|
|R5F51114xxxx|96K|16K|8K|
|R5F51113xxxx|64K|10K|8K|
|R5F51111xxxx|32K|10K|8K|
|R5F5111Jxxxx|16K|8K|8K|

---

## RX111 Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F51117|384K|64K|8K|[R5F51117.ld](R5F51117.ld?ts=4)|4096|1024|
|R5F51116|256K|32K|8K|[R5F51116.ld](R5F51116.ld?ts=4)|1536|512|
|R5F51115|128K|16K|8K|[R5F51115.ld](R5F51115.ld?ts=4)|1024|256|

---

## RX111 Dedicated class / 専用クラス

|Function/機能|Source|Remarks/備考|
|---|---|:-:|
|Peripheral Name/ペリフェラル名|[peripheral.hpp](peripheral.hpp?ts=4)||
|Hardware-specific Definition/ハード固有定義|[board_profile.hpp](board_profile.hpp?ts=4)||
|Operating Frequency Definition/動作周波数定義|[clock_profile.hpp](clock_profile.hpp?ts=4)||
|Power Control/電力制御|[power_mgr.hpp](power_mgr.hpp?ts=4)||
|Interrupt Definition/割り込み定義|[icu.hpp](icu.hpp?ts=4)||
|Port Function Definition/ポート機能定義|[mpc.hpp](mpc.hpp?ts=4)||
|Port Mapping/ポートマッピング|[port_map.hpp](port_map.hpp?ts=4)||
|Port Mapping IRQ/ポートマッピング IRQ|[port_map_irq.hpp](port_map_irq.hpp?ts=4)||
|Port Mapping MTU/ポートマッピング MTU|[port_map_mtu.hpp](port_map_mtu.hpp?ts=4)||
|FLASH Definition/FLASH 定義|[flash.hpp](flash.hpp?ts=4)||
|A/D Definition/A/D 定義|[s12adb.hpp](s12adb.hpp?ts=4)||
|System Definition/システム定義|[system.hpp](system.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 64|
|---|---|
|VCL|VCL(13)|
|Reset Input/リセット入力|RES#(7)|
|Mode Controle/モード制御|MD/FINED(6)|
|B/UB|P14(20)|
|RXD|P15/RXD1(19)|
|TXD|P16/TXD1(18)|
|USB_VCC|VCC_USB(21)|
|USB_VSS|VSS_USB(24)|
|USB+|USB_DP(23)|
|USB-|USB_DM(22)|
|Power/電源|VCC(15), VCC(38)|
|GND/接地|VSS(14), VSS(40)|
|Analog Power/アナログ電源|AVCC0(63)|
|Analog GND/アナログ接地|AVSS0(62)|
|Analog Refarence L/アナログ基準電源Ｌ|VREFL0(59)|
|Analog Refarence H/アナログ基準電源Ｈ|VREFH0(61)|
|OSC out|XTAL(11)|
|OSC in|EXTAL(12)|
|Sub OSC out|XCOUT(8)|
|Sub OSC in|XCIN(9)|

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
