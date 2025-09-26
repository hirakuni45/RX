
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

## peripheral / ペリフェラル

|Peripheral|Function|機能|
|---|---|---|
|CAC|Clock Frequency Accuracy Measurement Circuit|クロック周波数精度測定回路|
|DTC|Data Transfer Controller|データトランスファコントローラ|
|MTU0|Multi-Function Timer Pulse Unit 0|マルチファンクションタイマパルスユニット０|
|MTU1|Multi-Function Timer Pulse Unit 1|マルチファンクションタイマパルスユニット１|
|MTU2|Multi-Function Timer Pulse Unit 2|マルチファンクションタイマパルスユニット２|
|MTU3|Multi-Function Timer Pulse Unit 3|マルチファンクションタイマパルスユニット３|
|MTU4|Multi-Function Timer Pulse Unit 4|マルチファンクションタイマパルスユニット４|
|MTU5|Multi-Function Timer Pulse Unit 5|マルチファンクションタイマパルスユニット５|
|POE3|Port Output Enable 3|ポートアウトプットイネーブル３|
|TMR0|8-Bit Timer 0|8 ビットタイマ０|
|TMR1|8-Bit Timer 1|8 ビットタイマ１|
|TMR2|8-Bit Timer 2|8 ビットタイマ２|
|TMR3|8-Bit Timer 3|8 ビットタイマ３|
|TMR4|8-Bit Timer 4|8 ビットタイマ４|
|TMR5|8-Bit Timer 5|8 ビットタイマ５|
|TMR6|8-Bit Timer 6|8 ビットタイマ６|
|TMR7|8-Bit Timer 7|8 ビットタイマ７|
|CMT0|Compare Match Timer 0|コンペアマッチタイマ０|
|CMT1|Compare Match Timer 1|コンペアマッチタイマ１|
|CMT2|Compare Match Timer 2|コンペアマッチタイマ２|
|CMT3|Compare Match Timer 3|コンペアマッチタイマ３|
|IWDT|Independent Watchdog Timer|独立ウォッチドッグタイマ|
|SCI1|Serial Communications Interface 1|シリアルコミュニケーションインタフェース１|
|SCI5|Serial Communications Interface 5|シリアルコミュニケーションインタフェース５|
|SCI12|Serial Communications Interface 12|シリアルコミュニケーションインタフェース１２|
|RIIC0|I2C-bus Interface 0|I2C バスインタフェース０|
|CRC|CRC Calculator|CRC 演算器|
|S12AD|12-Bit A/D Converter|12 ビット A/D コンバータ|
|DA|8-Bit D/A Converter|8 ビット D/A コンバータ|
|CMPC0|Comparator C0|コンパレーターＣ０|
|CMPC1|Comparator C1|コンパレーターＣ１|
|CMPC2|Comparator C2|コンパレーターＣ２|
|DOC|Data Operation Circuit|データ演算回路|

---

## port map order / ポートマップ候補

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

## port map order (MTU) / ポートマップ候補 (MTU)

### LFQFP48

|Peripheral|FIRST|SECOND|THIRD|
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

## rx_prog Flash Programming / rx_prog フラッシュプログラム

||Support/サポート|operation verification/動作検証|
|-|:-:|:-:|
|[rxprog](../rxprog)|-|-|

---

Translated with www.DeepL.com/Translator (free version)

---

## License

[MIT](../LICENSE)
