
## RX23W features / 特徴

- RXv2 core / RXv2 コア
- Maximum operating frequency 54MHz / 最大動作周波数 54MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 1.8V ～ 3.6V Operation / 動作
- バッテリバックアップ専用電源で動作可能な RTC
- 8K バイト（プログラム / イレーズ回数 : 1,000,000 回（typ））
- Bluetooth Low Energy (1 チャネル )
- Bluetooth5.0 に準拠した RF トランシーバおよび Link Layer を内蔵
- LE 1M PHY、LE 2M PHY、LE Coded PHY(125kbps, 500kbps)、LE Advertising Extensions に対応
- Bluetooth 専用 AES-CCM (128 ビット ) 暗号回路を内蔵
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 12 Bits D/A / １２ビットＤ／Ａ変換器

---

## RX23W Linker file / リンカーファイル

|Type|Program|RAM|Data Flash|Source|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F523W8|512K|64K|8K|[R5F523W8.ld](R5F523W8.ld?ts=4)|3072|1024|
|R5F523W7|384K|64K|8K|[R5F523W7.ld](R5F523W7.ld?ts=4)|3072|1024|

---

## RX23W Dedicated class / 専用クラス

|Function/機能|Source|Remarks/備考|
|---|---|:-:|
|Peripheral Name/ペリフェラル名|[peripheral.hpp](peripheral.hpp?ts=4)||
|Hardware-specific Definition/ハード固有定義|[board_profile.hpp](board_profile.hpp?ts=4)||
|Operating Frequency Definition/動作周波数定義|[clock_profile.hpp](clock_profile.hpp?ts=4)||
|Power Control/電力制御|[power_mgr.hpp](power_mgr.hpp?ts=4)||
|-Port Definition/ポート定義|[port.hpp](port.hpp?ts=4)||
|-Interrupt Definition/割り込み定義|[icu.hpp](icu.hpp?ts=4)||
|-Interrupt Management/割り込み管理|[icu_mgr.hpp](icu_mgr.hpp?ts=4)||
|-Port Function Definition/ポート機能定義|[mpc.hpp](mpc.hpp?ts=4)||
|-Port Mapping/ポートマッピング|[port_map.hpp](port_map.hpp?ts=4)||
|-Port Mapping IRQ/ポートマッピング IRQ|[port_map_irq.hpp](port_map_irq.hpp?ts=4)||
|-Port Mapping MTU/ポートマッピング MTU|[port_map_mtu.hpp](port_map_mtu.hpp?ts=4)||
|-Port Mapping TPU/ポートマッピング TPU|[port_map_tpu.hpp](port_map_tpu.hpp?ts=4)||
|-BUS Definition/BUS 定義|[bus.hpp](bus.hpp?ts=4)||
|-CMPB Definition/CMPB 定義|[cmpb.hpp](cmpb.hpp?ts=4)||
|-ELC Definition/ELC 定義|[elc.hpp](elc.hpp?ts=4)||
|-FLASH Definition/FLASH 定義|[flash.hpp](flash.hpp?ts=4)||
|-LVDA Definition/LVDA 定義|[lvda.hpp](lvda.hpp?ts=4)||
|-POE2 Definition/POE2 定義|[poe2.hpp](poe2.hpp?ts=4)||
|-RTC Definition/RTC 定義|[rtc.hpp](rtc.hpp?ts=4)||
|-A/D Definition/A/D 定義|[s12ade.hpp](s12ade.hpp?ts=4)||
|-System Definition/システム定義|[system.hpp](system.hpp?ts=4)||
|-System I/O Definition/システム I/O 定義|[system_io.hpp](system_io.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 64|LFQFP 100|
|---|---|---|
|VCL|VCL(2)|VCL(5)|
|Reset Input/リセット入力|RES#(6)|RES#(10)|
|Mode Controle/モード制御|MD/FINED(3)|MD/FINED(7)|
|B/UB|PC7(27)|PC7(45)|
|RXD|P30/RXD1(14)|P30/RXD1(20)|
|TXD|P26/TXD1(16)|P26/TXD1(22)|
|USB_VCC|VCC_USB(21)|VCC_USB(35)|
|USB_VSS|VSS_USB(24)|VSS_USB(38)|
|USB+|USB_DP(23)|USB_DP(37)|
|USB-|USB_DM(22)|USB_DM(36)|
|Power/電源|VCC(10), VCC(38)|VCC(14),VCC(60)|
|GND/接地|VSS(8), VSS(40)|VSS(12),VSS(62)|
|Analog Power/アナログ電源|AVCC0(62)|AVCC0(97)|
|Analog GND/アナログ接地|AVSS0(64)|AVSS0(99)|
|Analog Refarence L/アナログ基準電源Ｌ|VREFL(52)|VREFL(3)|
|Analog Refarence H/アナログ基準電源Ｈ|VREFH(54)|VREFH(1)|
|Analog Refarence L0/アナログ基準電源Ｌ0|VREFL0(59)|VREFL0(94)|
|Analog Refarence H0/アナログ基準電源Ｈ0|VREFH0(61)|VREFH0(96)|
|VBATT|VBATT(12)|VBATT(6)|
|OSC in|EXTAL(9)|EXTAL(13)|
|OSC out|XTAL(7)|XTAL(11)|
|Sub OSC in|XCIN(4)|XCIN(8)|
|Sub OSC out|XCOUT(5)|XCOUT(9)|

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
|[rxprog](../rxprog)|〇|〇|

rx_prog option:
- --write-page-wait=10000
- --erase-page-wait=5000

---

Translated with www.DeepL.com/Translator (free version)

---

## License

[MIT](../LICENSE)
