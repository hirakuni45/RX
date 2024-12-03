
## RX621/RX62N features / 特徴

- RXv1 core / RXv1 コア
- Maximum operating frequency 100MHz / 最大動作周波数 100MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 2.7V ～ 3.6V Operation / 動作
- RMII/MII Ethernet MAC 10/100 Mbps (RX62N)
- USB2.0 Full Speed, Host, Function
- CAN (ISO11898-1)
- 12/10 Bits A/D / １２・１０ビットＡ／Ｄ変換器
- 10 Bits D/A / １０ビットＤ／Ａ変換器

### Package/パッケージ

|R5F562y---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F562yxxxBG|LFBGA|176|0.80|
|R5F562yxxxLE|TFLGA|145|0.65|
|R5F562yxxxFB|LQFP|144|0.50|
|R5F562yxxxFP|LQFP|100|0.50|
|R5F562yxxxLD|TFLGA|85|0.65|

### CAN

|R5F562y-X---|CAN|
|---|:-:|
|R5F563yxAxxx|-|
|R5F563yxBxxx|〇|

### Memoey size/メモリ容量

|R5F562yX----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F562y8xxxx|512K|96K|32K|
|R5F562y7xxxx|384K|64K|32K|
|R5F562y6xxxx|256K|64K|32K|

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|32K|2048|8/2048|8|0x??|0|

---

## RX621/RX62N Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F56218|512K|96K|32K|[R5F56218.ld](R5F56218.ld?ts=4)|1024|512|
|R5F562N8|512K|96K|32K|[R5F562N8.ld](R5F562N8.ld?ts=4)|1024|512|
|R5F562N7|384K|64K|32K|[R5F562N7.ld](R5F562N7.ld?ts=4)|1024|512|

---

## RX621/RX62N Dedicated class / 専用クラス

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
|BUS Definition/BUS 定義|[bus.hpp](bus.hpp?ts=4)||
|MTU2 Definition/MTU2 定義|[mtu2.hpp](mtu2.hpp?ts=4)||
|FLASH Definition/FLASH 定義|[flash.hpp](flash.hpp?ts=4)||
|FLASH I/O Definition/FLASH I/O 定義|[flash_io.hpp](flash_io.hpp?ts=4)||
|LVD Definition/LVD 定義|[lvd.hpp](lvd.hpp?ts=4)||
|POE2 Definition/POE2 定義|[poe2.hpp](poe2.hpp?ts=4)||
|RTC Definition/RTC 定義|[rtc.hpp](rtc.hpp?ts=4)||
|USB Definition/USB 定義|[usb.hpp](usb.hpp?ts=4)||
|WDT Definition/WDT 定義|[wdt.hpp](wdt.hpp?ts=4)||
|10 Bits A/D Definition/10 Bits A/D 定義|[ad.hpp](ad.hpp?ts=4)||
|12 Bits A/D Definition/12 Bits A/D 定義|[s12ad.hpp](s12ad.hpp?ts=4)||
|10 Bits D/A Definition/10 Bits D/A 定義|[da.hpp](da.hpp?ts=4)||
|System Definition/システム定義|[system.hpp](system.hpp?ts=4)||
|System I/O Definition/システム I/O 定義|[system_io.hpp](system_io.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LQFP 144|
|---|---|
|VCL|VCL(14)|
|Reset Input/リセット入力|RES#(19)|
|MD0|MD0(16)|
|MD1|MD1(15)|
|MDE|MDE(13)|
|EMLE|EMLE(10)|
|BSCANP|BSCANP(9)|
|RXD|P30/RXD1(29)|
|TXD|P26/TXD1(31)|
|USB_VCC|VCC_USB(46)|
|USB_VSS|VSS_USB(49)|
|USB+|USB_DP(48)|
|USB-|USB_DM(47)|
|Power/電源|VCC(  3), VCC( 23), VCC( 59), VCC( 74)|
|Power/電源|VCC( 91), VCC(103), VCC(118), VCC(132)|
|GND/接地|VSS(  5), VSS( 12), VSS( 21), VSS( 57)|
|GND/接地|VSS( 76), VSS( 93), VSS(105), VSS(116), VSS(130)|
|PLL Power/PLL 電源|PLLVCC(39)|
|PLL GND/PLL 接地|PLLVSS(41)|
|Analog Power/アナログ電源|AVCC(143)|
|Analog GND/アナログ接地|AVSS(  1)|
|Analog Refarence L/アナログ基準電源Ｌ|VREFL(140)|
|Analog Refarence H/アナログ基準電源Ｈ|VREFH(142)|
|OSC in|EXTAL(22)|
|OSC out|XTAL(20)|
|Sub OSC in|XCIN(17)|
|Sub OSC out|XCOUT(18)|

- VCL: 0.1uF/25V

|Mode/モード|MD0|MD1|
|---|:---:|:---:|
|Serial Boot/シリアルブート|1|0|
|USB Boot/USB ブート|0|1|
|Single Chip/シングルチップ|1|1|

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
