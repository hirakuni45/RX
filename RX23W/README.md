
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

### Package/パッケージ

|R5F523W---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F523WxxxBL|BGA|85|0.5|
|R5F523WxxxLN|LGA|83|0.5|
|R5F523WxxxNG|QFN|56|0.4|

### Ambient operating temperature/動作周囲温度

|R5F523W--X--|degree Celsius|
|---|:-:|
|R5F523WxxDxx|-40 ～ +85℃|

### Crypt, Antena

|R5F523y-X---|Crypt|ANTENA|
|---|:-:|:-:|
|R5F523WxAxxx|-|-|
|R5F523WxBxxx|〇|-|
|R5F523WxCxxx|-|〇|
|R5F523WxDxxx|〇|〇|

### Memoey size/メモリ容量

|R5F523WX----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F523y8xxxx|512K|64K|8K|
|R5F523y7xxxx|384K|64K|8K|

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|8K|1024|1/1024|1|0xFF|4|

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
|-Port Function Definition/ポート機能定義|[mpc.hpp](mpc.hpp?ts=4)||
|-Port Mapping/ポートマッピング|[port_map.hpp](port_map.hpp?ts=4)||
|-Port Mapping IRQ/ポートマッピング IRQ|[port_map_irq.hpp](port_map_irq.hpp?ts=4)||
|-Port Mapping MTU/ポートマッピング MTU|[port_map_mtu.hpp](port_map_mtu.hpp?ts=4)||
|-Port Mapping TPU/ポートマッピング TPU|[port_map_tpu.hpp](port_map_tpu.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|QFN 56|LGA 83|
|---|---|---|
|VCL|VCL(1)|VCL(33)|
|Reset Input/リセット入力|RES#(5)|RES#(66)|
|Mode Controle/モード制御|MD/FINED(2)|MD/FINED(34)|
|B/UB|PC7(23)|PC7(44)|
|RXD|P30/RXD1(12)|P30/RXD1(12)|
|TXD|P26/TXD1(14)|P26/TXD1(14)|
|USB_VCC|VCC_USB(19)|VCC_USB(3)|
|USB_VSS|VSS_USB(22)|VSS_USB(6)|
|USB+|USB_DP(21)|USB_DP(5)|
|USB-|USB_DM(20)|USB_DM(4)|
|Power/電源|VCC(9), VCC(34)|VCC(31),VCC(60)|
|GND/接地|VSS(7), VSS(36)|VSS(30),VSS(62)|
|Analog Power/アナログ電源|AVCC0(54)|AVCC0(28)|
|Analog GND/アナログ接地|AVSS0(56)|AVSS0(29)|
|Analog Refarence L0/アナログ基準電源Ｌ0|VREFL0(52)|VREFL0(26)|
|Analog Refarence H0/アナログ基準電源Ｈ0|VREFH0(53)|VREFH0(27)|
|VBATT|VBATT(-)|VBATT(39)|
|OSC in|EXTAL(8)|EXTAL(38)|
|OSC out|XTAL(6)|XTAL(37)|
|Sub OSC in|XCIN(3)|XCIN(35)|
|Sub OSC out|XCOUT(4)|XCOUT(36)|

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
|[rxprog](../rxprog)|-|-|

rx_prog option:
- --write-page-wait=10000
- --erase-page-wait=5000

---

Translated with www.DeepL.com/Translator (free version)

---

## License

[MIT](../LICENSE)
