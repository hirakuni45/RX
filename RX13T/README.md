
## RX13T features / 特徴

- RXv1 core / RXv1 コア
- Maximum operating frequency 32MHz / 最大動作周波数 32MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 2.7V ～ 5.5V Operation / 動作
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 8 Bits D/A / ８ビットＤ／Ａ変換器

### Package / パッケージ

|R5F513T---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F513TxxxFL|LFQFP|48|0.50|
|R5F513TxxxFJ|LQFP|32|0.80|
|R5F513TxxxNE|HWQFN|48|0.50|
|R5F513TxxxNH|HWQFN|32|0.50|

### Ambient operating temperature / 動作周囲温度

|R5F513T--X--|degree Celsius|
|---|:-:|
|R5F513TxxDxx|-40 ～ +85℃|
|R5F513TxxGxx|-40 ～ +105℃|

### Memoey size / メモリ容量

|R5F513TX----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F513T5xxxx|128K|12K|0K|
|R5F513T3xxxx|64K|12K|0K|

### Data Flash / データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|0K|-|-|-|-|0|

---

## RX13T Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Link File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F513T5|128K|12K|4K|[R5F513T5.ld](R5F513T5.ld?ts=4)|512|256|
|R5F513T3|64K|12K|4K|[R5F513T3.ld](R5F513T3.ld?ts=4)|512|256|

---

## RX13T Dedicated class / 専用クラス

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
|A/D Definition/A/D 定義|[s12ad.hpp](s12ad.hpp?ts=4)||
|D/A Definition/D/A 定義|[da.hpp](da.hpp?ts=4)||
|POE3 Definition/POE3 定義|[poe3.hpp](poe3.hpp?ts=4)||

```C++
namespace board_profile {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  基板プロファイル空間 @n
				DIY RX13T board
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

	// 基板シグネチュア
	static constexpr char system_str_[] = "RX13T DIY";

	/// LED インジケーター
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT1, device::bitpos::B0, LED_ACTIVE> LED;

	// SCI ポートの定義
	typedef device::SCI1 SCI_CH;
	static constexpr auto SCI_ORDER = device::port_map::ORDER::SECOND;

	// インターバル・タイマーの定義
	typedef device::CMT0 CMT_CH;

	// RIIC ポートの定義
	typedef device::RIIC0 RIIC_CH;
	// ソフト制御 I2C ポートの定義
	typedef device::PORT<device::PORTB, device::bitpos::B2> SDA;
	typedef device::PORT<device::PORTB, device::bitpos::B1> SCL;
}
```

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 48|
|---|---|
|VCL|VCL(1)|
|Reset Input/リセット入力|RES#(3)|
|Mode Controle/モード制御|MD/FINED(2)|
|RXD|PB7/RXD1(13)|
|TXD|PB6/TXD1(14)|
|Power/電源|VCC(7), VCC(32)|
|GND/接地|VSS(5), VSS(33)|
|Analog Power/アナログ電源|AVCC0(45)|
|Analog GND/アナログ接地|AVSS0(46)|
|OSC out|XTAL(4)|
|OSC in|EXTAL(6)|

- VCL: 4.7uF/25V

|Mode/モード|MD|
|---|:---:|
|Serial BOOT/シリアルブート|0|
|Single Chip/シングルチップ|1|

---

## Device, Renesas / デバイス、ルネサス

- [device.hpp (SIG_RX13T)](../common/device.hpp?ts=4)
- [renesas.hpp (SIG_RX13T)](../common/renesas.hpp?ts=4)

|name space|Device, Renesas|デバイス、ルネサス|
|---|---|---|
|[clock_profile](../RX13T/clock_profile?ts=4)|Clock Profile|クロック・プロファイル|
|[SYSTEM](../RX24T/system.hpp?ts=4)|Clock Generation Circuit|クロック発生回路|
|[power_mgr](../RX13T/power_mgr.hpp?ts=4)|Low Power Consumption|消費電力低減機能|
|[ICU](../RX13T/icu.hpp?ts=4)|Interrupt Controller|割り込みコントローラ|
|[icu_mgr](../RX24T/icu_mgr.hpp?ts=4)|ICU Manager|ICU マネージャー|
|[MPC](../RX13T/mpc.hpp?ts=4)|Multi-Function Pin Controller|マルチファンクションピンコントローラ|
|[PORTx](../RX13T/port.hpp?ts=4)|I/O Ports|I/O ポート|
|[port_map](../RX13T/port_map.hpp?ts=4)|Port Mapping|ポート・マッピング|
|[port_map_mtu](../RX13T/port_map_mtu.hpp?ts=4)|Port Mapping MTU|ポート・マッピング MTU|
|[port_map_irq](../RX13T/port_map_irq.hpp?ts=4)|Port Mapping IRQ|ポート・マッピング IRQ|
|[FLASH](../RX130/flash.hpp?ts=4)|Flash Memory|フラッシュメモリ|
|[SYSTEM_IO](../RX24T/system_io.hpp?ts=4)|System In/Out (Clock Setting)|システム In/Out (クロック設定)|
|[FLASH_IO](../RX24T/flash_io.hpp?ts=4)|Flash In/Out|フラッシュ In/Out|
|[adc_in](../RX24T/adc_in.hpp?ts=4)|A/D Converter Input|A/D 変換入力|
|[dac_out](../RX24T/dac_out.hpp?ts=4)|D/A Converter Output|D/A 変換出力|
|[board_profile](../RX13T/board_profile?ts=4)|Board Profile|ボード・プロファイル|

---

## Peripheral / ペリフェラル

- [peripheral.hpp](peripheral.hpp?ts=4)

|Peripheral|Function|機能|
|---|---|---|
|[CAC](../RX600/cac.hpp?ts=4)|Clock Frequency Accuracy Measurement Circuit|クロック周波数精度測定回路|
|[DTC](../RX600/dtc.hpp?ts=4)|Data Transfer Controller|データトランスファコントローラ|
|[MTU0](../RX600/mtu3.hpp?ts=4)|Multi-Function Timer Pulse Unit 0|マルチファンクションタイマパルスユニット０|
|[MTU1](../RX600/mtu3.hpp?ts=4)|Multi-Function Timer Pulse Unit 1|マルチファンクションタイマパルスユニット１|
|[MTU2](../RX600/mtu3.hpp?ts=4)|Multi-Function Timer Pulse Unit 2|マルチファンクションタイマパルスユニット２|
|[MTU3](../RX600/mtu3.hpp?ts=4)|Multi-Function Timer Pulse Unit 3|マルチファンクションタイマパルスユニット３|
|[MTU4](../RX600/mtu3.hpp?ts=4)|Multi-Function Timer Pulse Unit 4|マルチファンクションタイマパルスユニット４|
|[MTU5](../RX600/mtu3.hpp?ts=4)|Multi-Function Timer Pulse Unit 5|マルチファンクションタイマパルスユニット５|
|[POE3](../RX13T/poe3.hpp?ts=4)|Port Output Enable 3|ポートアウトプットイネーブル３|
|[TMR0](../RX600/tmr.hpp?ts=4)|8-Bit Timer 0|8 ビットタイマ０|
|[TMR1](../RX600/tmr.hpp?ts=4)|8-Bit Timer 1|8 ビットタイマ１|
|[TMR2](../RX600/tmr.hpp?ts=4)|8-Bit Timer 2|8 ビットタイマ２|
|[TMR3](../RX600/tmr.hpp?ts=4)|8-Bit Timer 3|8 ビットタイマ３|
|[TMR4](../RX600/tmr.hpp?ts=4)|8-Bit Timer 4|8 ビットタイマ４|
|[TMR5](../RX600/tmr.hpp?ts=4)|8-Bit Timer 5|8 ビットタイマ５|
|[TMR6](../RX600/tmr.hpp?ts=4)|8-Bit Timer 6|8 ビットタイマ６|
|[TMR7](../RX600/tmr.hpp?ts=4)|8-Bit Timer 7|8 ビットタイマ７|
|[CMT0](../RX600/cmt.hpp?ts=4)|Compare Match Timer 0|コンペアマッチタイマ０|
|[CMT1](../RX600/cmt.hpp?ts=4)|Compare Match Timer 1|コンペアマッチタイマ１|
|[CMT2](../RX600/cmt.hpp?ts=4)|Compare Match Timer 2|コンペアマッチタイマ２|
|[CMT3](../RX600/cmt.hpp?ts=4)|Compare Match Timer 3|コンペアマッチタイマ３|
|[IWDT](../RX600/iwdt.hpp?ts=4)|Independent Watchdog Timer|独立ウォッチドッグタイマ|
|[SCI1](../RX600/sci_e.hpp?ts=4)|Serial Communications Interface 1|シリアルコミュニケーションインタフェース１|
|[SCI5](../RX600/sci_e.hpp?ts=4)|Serial Communications Interface 5|シリアルコミュニケーションインタフェース５|
|[SCI12](../RX600/sci_f.hpp?ts=4)|Serial Communications Interface 12|シリアルコミュニケーションインタフェース１２|
|[RIIC0](../RX600/riic.hpp?ts=4)|I2C-bus Interface 0|I2C バスインタフェース０|
|[CRC](../RX600/crc.hpp?ts=4)|CRC Calculator|CRC 演算器|
|[S12AD](../RX13T/s12ad.hpp?ts=4)|12-Bit A/D Converter|12 ビット A/D コンバータ|
|[DA](../RX13T/da.hpp?ts=4)|8-Bit D/A Converter|8 ビット D/A コンバータ|
|[CMPC0](../RX600/cmpc.hpp?ts=4)|Comparator C0|コンパレーターＣ０|
|[CMPC1](../RX600/cmpc.hpp?ts=4)|Comparator C1|コンパレーターＣ１|
|[CMPC2](../RX600/cmpc.hpp?ts=4)|Comparator C2|コンパレーターＣ２|
|[DOC](../RX600/doc.hpp?ts=4)|Data Operation Circuit|データ演算回路|

---

## Port map order (IRQ) / ポートマップ候補 (IRQ)

- [port_map_irq.hpp](port_map_irq.hpp?ts=4)

### LFQFP48

|IRQ|FIRST|SECOND|THIRD|
|---|---|---|---|
|IRQ0|P10 (48)|P93 (24)|PE2 (8)|
|IRQ1|P11 (47)|P94 (23)|-|
|IRQ2|P22 (36)|PB1 (19)|PD4 (11)|
|IRQ3|P24 (34)|PB4 (16)|PD5 (10)|
|IRQ4|P23 (35)|PA2 (22)|-|
|IRQ5|P70 (31)|PB7 (13)|PD6 (9)|

---

## Port map order / ポートマップ候補

- [port_map.hpp](port_map.hpp?ts=4)

### LFQFP48

|Peripheral|FIRST|SECOND|THIRD|
|---|---|---|---|
|SCI1 / RXD|PD5 (10)|PB7 (13)|-|
|SCI1 / TXD|PD3 (12)|PB6 (14)|-|
|SCI1 / SCK|PD4 (11)|PD4 (11)|-|
|SCI5 / RXD|PB1 (19)|PB7 (13)|P24 (34)|
|SCI5 / TXD|PB2 (18)|PB6 (14)|P23 (35)|
|SCI5 / SCK|PB3 (17)|PB3 (27)|PB3 (17)|
|SCI12 / RXD|P94 (23)|P94 (23)|-|
|SCI12 / TXD|PB0 (20)|PB0 (20)|-|
|SCI12 / SCK|PB3 (17)|P93 (24)|-|
|RIIC0 / SCL|PB1 (19)|-|-|
|RIIC0 / SDA|PB2 (18)|-|-|

---

## Port map order (MTU) / ポートマップ候補 (MTU)

- [port_map_mtu.hpp](port_map_mtu.hpp?ts=4)

### LFQFP48

|MTU|FIRST|SECOND|THIRD|
|---|---|---|---|
|MTIOC0A|PB3 (17)|PD3 (12)|-|
|MTIOC0B|PB2 (18)|PD4 (11)|-|
|MTIOC0C|PB1 (19)|PD5 (10)|-|
|MTIOC0D|PB0 (20)|PD6 (9)|-|
|MTIOC1A|P93 (24)|PA2 (22)|-|
|MTIOC1B|PA3 (21)|PB6 (14)|-|
|MTIOC2A|PA3 (21)|PB0 (20)|-|
|MTIOC2B|PA2 (22)|P94 (23)|-|
|MTIOC3A|P11 (47)|PB6 (14)|-|
|MTIOC3B|P71 (30)|-|-|
|MTIOC3C|PB7 (13)|-|-|
|MTIOC3D|P74 (27)|-|-|
|MTIOC4A|P72 (29)|-|-|
|MTIOC4B|P73 (28)|-|-|
|MTIOC4C|P75 (26)|-|-|
|MTIOC4D|P76 (25)|-|-|
|MTIOC5U|P24 (34)|P94 (23)|-|
|MTIOC5V|P23 (35)|P93 (24)|-|
|MTIOC5W|P22 (36)|PB1 (19)|-|
|MTCLKA|P11 (47)|P94 (23)|PB1 (19)|
|MTCLKB|P10 (48)|PB0 (20)|-|
|MTCLKC|PB2 (18)|-|-|
|MTCLKD|PB7 (13)|-|-|
|ADSM0|PB2 (18)|-|-|

---

## 12 Bits A/D Converter input (S12AD) / 12 ビット A/D コンバーター入力 (S12AD)

- [s12ad.hpp](s12ad.hpp?ts=4)

### LFQFP48

|ANALOG|Port|
|---|---|
|AN000|P40 (44)|
|AN001|P41 (43)|
|AN002|P42 (42)|
|AN003|P43 (41)|
|AN004|P44 (40)|
|AN005|P45 (39)|
|AN006|P46 (38)|
|AN007|P47 (37)|

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
