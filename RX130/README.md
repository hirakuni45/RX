
## RX130 features / 特徴

- RXv1 core / RXv1 コア
- Maximum operating frequency 32MHz / 最大動作周波数 32MHz
- 1.8V ～ 5.5V Operation / 動作
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 8 Bits D/A / ８ビットＤ／Ａ変換器

### Package/パッケージ

|R5F5130---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F5130xxxFP|LFQFP|100|0.50|
|R5F5130xxxFN|LFQFP|80|0.50|
|R5F5130xxxFM|LQFP|64|0.50|
|R5F5130xxxFK|LQFP|64|0.80|
|R5F5130xxxFL|LFQFP|48|0.50|
|R5F5130xxxNE|HWQFN|48|0.50|

### Version

|R5F5130-X---|Version|
|---|:-:|:-:|:-:|
|R5F5130xAxxx|A|
|R5F5130xBxxx|B|

### Memoey size/メモリ容量

|R5F5130X----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F51308xxxx|512K|48K|8K|
|R5F51307xxxx|384K|48K|8K|
|R5F51306xxxx|256K|32K|8K|
|R5F51305xxxx|128K|16K|8K|
|R5F51303xxxx|64K|10K|8K|

---

## RX130 Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F51306|256K|32K|8K|[R5F51306.ld](R5F51405.ld?ts=4)|1536|512|
|R5F51305|128K|16K|8K|[R5F51305.ld](R5F51406.ld?ts=4)|1024|256|

---

## RX130 Dedicated class / 専用クラス

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
|A/D Definition/A/D 定義|[s12ad.hpp](s12ad.hpp?ts=4)||
|D/A Definition/D/A 定義|[da.hpp](da.hpp?ts=4)||
|BUS Definition/BUS 定義|[bus.hpp](bus.hpp?ts=4)||
|ELC Definition/ELC 定義|[elc.hpp](elc.hpp?ts=4)||
|RTC Definition/RTC 定義|[rtc.hpp](rtc.hpp?ts=4)||
|FLASH Definition/FLASH 定義|[flash.hpp](flash.hpp?ts=4)||
|System Definition/システム定義|[system.hpp](system.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 64|LFQFP 80|
|---|---|---|
|VCL|VCL(2)|VCL(4)|
|Reset Input/リセット入力|RES#(6)|RES#(9)|
|Mode Controle/モード制御|MD/FINED(3)|MD/FINED(6)|
|RXD|P30/RXD1(14)|P30/RXD1(18)|
|TXD|P26/TXD1(16)|P26/TXD1(20)|
|Power/電源|VCC(10), VCC(38)|VCC(13), VCC(48)|
|GND/接地|VSS(8), VSS(40)|VSS(11), VSS(50)|
|Analog Power/アナログ電源|AVCC0(62)|AVCC0(77)|
|Analog GND/アナログ接地|AVSS0(64)|AVSS0(79)|
|Analog Refarence L/アナログ基準電源Ｌ|VREFL0(59)|VREFL0(74)|
|Analog Refarence H/アナログ基準電源Ｈ|VREFH0(61)|VREFH0(76)|
|OSC out|XTAL(7)|XTAL(10)|
|OSC in|EXTAL(9)|EXTAL(12)|
|Sub OSC out|XCOUT(5)|XCOUT(8)|
|Sub OSC in|XCIN(4)|XCIN(7)|

- VCL: 4.7uF/25V

|Mode/モード|MD|
|---|:---:|
|Serial BOOT/シリアルブート|0|
|Single Chip/シングルチップ|1|

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
