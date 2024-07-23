
## RX220 feature / 特徴

- RXv1 core / コア
- Maximum operating frequency / 最大動作周波数 32MHz
- 1.62V ～ 5.5V Operation / 動作
- 12 Bits A/D / １２ビットＡ／Ｄ変換器

---

## RX220 Linker file / リンカーファイル

|Type|Program|RAM|Data Flash|Source|
|---|:-:|:-:|:-:|---|
|R5F52206|256K|16K|8K|[R5F52206.ld](R5F52206.ld)|

---

## RX220 Dedicated class / 専用クラス

|Function/機能|Source|Remarks/備考|
|---|---|:-:|
|Peripheral Name/ペリフェラル名|[peripheral.hpp](peripheral.hpp)||
|Hardware-specific Definition/ハード固有定義|[board_profile.hpp](board_profile.hpp)||
|Operating Frequency Definition/動作周波数定義|[clock_profile.hpp](clock_profile.hpp)||
|Power Control/電力制御|[power_mgr.hpp](power_mgr.hpp)||
|Port Definition/ポート定義|[port.hpp](port.hpp)||
|Interrupt Definition/割り込み定義|[icu.hpp](icu.hpp)||
|Interrupt Management/割り込み管理|[icu_mgr.hpp](icu_mgr.hpp)||
|Port Function Definition/ポート機能定義|[mpc.hpp](mpc.hpp)||
|Port Mapping/ポートマッピング|[port_map.hpp](port_map.hpp)||
|Port Mapping IRQ/ポートマッピング IRQ|[port_map_irq.hpp](port_map_irq.hpp)||
|Port Mapping MTU/ポートマッピング MTU|[port_map_mtu.hpp](port_map_mtu.hpp)||
|Port Mapping MTU/ポートマッピング TMR|[port_map_tmr.hpp](port_map_tmr.hpp)||
|BUS Definition/BUS 定義|[bus.hpp](bus.hpp)||
|CMPA Definition/CMPA 定義|[cmpa.hpp](cmpa.hpp)||
|ELC Definition/ELC 定義|[elc.hpp](elc.hpp)||
|IrDA Definition/IrDA 定義|[irda.hpp](irda.hpp)||
|LVDA Definition/LVDA 定義|[lvda.hpp](lvda.hpp)||
|MTU2 Definition/MTU2 定義|[mtu2.hpp](mtu2.hpp)||
|POE2 Definition/POE2 定義|[poe2.hpp](poe2.hpp)||
|RTC Definition/RTC 定義|[rtc.hpp](rtc.hpp)||
|A/D Definition/A/D 定義|[s12ad.hpp](s12ad.hpp)||
|FLASH Definition/FLASH 定義|[flash.hpp](flash.hpp)||
|FLASH I/O Definition/FLASH I/O 定義|[flash_io.hpp](flash_io.hpp)||
|System Definition/システム定義|[system.hpp](system.hpp)||
|System I/O Definition/システム I/O 定義|[system_io.hpp](system_io.hpp)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 64|
|---|---|
|VCL|VCL(2)|
|Reset Input/リセット入力|RES#(6)|
|Mode Controle/モード制御|MD/FINED(3)|
|B/UB|PC7(27)|
|RXD|P30/RXD1(14)|
|TXD|P26/TXD1(16)|
|Power/電源|VCC(10), VCC(38)|
|GND/接地|VSS(8), VSS(40)|
|Analog Power/アナログ電源|AVCC0(62)|
|Analog GND/アナログ接地|AVSS0(64)|
|Analog Refarence L/アナログ基準電源Ｌ|VREFL0(59)|
|Analog Refarence H/アナログ基準電源Ｈ|VREFH0(61)|
|OSC out|XTAL(7)|
|OSC in|EXTAL(9)|
|Sub OSC out|XCOUT(5)|
|Sub OSC in|XCIN(4)|

- VCL: 0.1uF/25V

|Mode/モード|B/UB|MD|
|---|:---:|:---:|
|Serial BOOT/シリアルブート|0|0|
|User Boot/ユーザーブート|1|0|
|Single Chip/シングルチップ|-|1|

---

Translated with www.DeepL.com/Translator (free version)

---

## License

[MIT](../LICENSE)
