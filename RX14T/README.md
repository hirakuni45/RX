
## RX14T features / 特徴

- RXv2 core / RXv2 コア
- Maximum operating frequency 48MHz / 最大動作周波数 48MHz
- Single-precision 32-bit floating point / 32 ビット単精度浮動小数点
- 2.7V ～ 5.5V Operation / 動作
- Arithmetic Unit for Trigonometric Functions (TFUv1) / 三角関数演算器(TFUv1)
- 12 Bits A/D 2 Units / １２ビットＡ／Ｄ変換器２ユニット
- 8 Bits D/A 2 Channel / ８ビットＤ／Ａ変換器２チャンネル

### Package / パッケージ

|R5F514T---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F514TxxxFM|LFQFP|64|0.50|
|R5F514TxxxFK|LQFP|64|0.80|
|R5F514TxxxFD|LQFP|52|0.65|
|R5F514TxxxFL|LFQFP|48|0.50|
|R5F514TxxxFV|LQFP|44|0.80|
|R5F514TxxxFJ|LQFP|32|0.80|
|R5F514TxxxNE|HWQFN|48|0.50|
|R5F514TxxxNH|HWQFN|32|0.50|
|R5F514TxxxNK|HWQFN|24|0.50|

### Ambient operating temperature / 動作周囲温度

|R5F514T--X--|degree Celsius|
|---|:-:|
|R5F514TxxGxx|-40 ～ +105℃|
|R5F514TxxMxx|-40 ～ +125℃|

### Memoey size / メモリ容量

|R5F514TX----|CodeFlash|RAM|DataFlash|
|---|:-:|:-:|:-:|
|R5F514T5xxxx|128K|12K|4K|

### Data Flash / データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|4K|256|1/256|1|0xFF|4|

---

## RX14T Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Link File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F514T5|128K|12K|4K|[R5F514T5.ld](R5F514T5.ld?ts=4)|512|256|

---

## RX14T Dedicated class / 専用クラス

|Function/機能|Source|Remarks/備考|
|---|---|:-:|
|Hardware-specific Definition/ハード固有定義|[board_profile.hpp](board_profile.hpp?ts=4)||
|Operating Frequency Definition/動作周波数定義|[clock_profile.hpp](clock_profile.hpp?ts=4)||
|D/A Definition/D/A 定義|[da.hpp](da.hpp?ts=4)||
|Interrupt Definition/割り込み定義|[icu.hpp](icu.hpp?ts=4)||
|LVDA Definition/LVDA 定義|[lvda.hpp](lvda.hpp?ts=4)||
|Port Function Definition/ポート機能定義|[mpc.hpp](mpc.hpp?ts=4)||
|Peripheral Name/ペリフェラル名|[peripheral.hpp](peripheral.hpp?ts=4)||
|Programmable Gain Amplifier Definition/プログラマブルゲインアンプ定義|[pga.hpp](pga.hpp?ts=4)||
|Port Mapping GPTW/ポートマッピング GPTW|[port_map_gptw.hpp](port_map_gptw.hpp?ts=4)||
|Port Mapping IRQ/ポートマッピング IRQ|[port_map_irq.hpp](port_map_irq.hpp?ts=4)||
|Port Mapping MTU/ポートマッピング MTU|[port_map_mtu.hpp](port_map_mtu.hpp?ts=4)||
|Port Mapping TMR/ポートマッピング TMR|[port_map_tmr.hpp](port_map_tmr.hpp?ts=4)||
|Port Mapping/ポートマッピング|[port_map.hpp](port_map.hpp?ts=4)||
|Port Definition/ポート定義|[port.hpp](port.hpp?ts=4)||
|Power Control/電力制御|[power_mgr.hpp](power_mgr.hpp?ts=4)||
|A/D Definition/A/D 定義|[s12adf.hpp](s12adf.hpp?ts=4)||
|Temperature Sensor Definition/温度センサ定義|[temps.hpp](temps.hpp?ts=4)||

```C++
namespace board_profile {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  基板プロファイル空間 @n
				DIY RX14T board
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

	// 基板シグネチュア
	static constexpr char system_str_[] = "RX14T DIY";

	/// LED インジケーター
	static constexpr bool LED_ACTIVE = 0;
	typedef device::PORT<device::PORT0, device::bitpos::B0, LED_ACTIVE> LED;

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

|Terminal/端子|LFQFP 48|LQFP 52|LFQFP 64|
|---|---|---|---|
|VCL|VCL (1)|VCL (2)|VCL (3)|
|Reset Input/リセット入力|RES# (3)|RES# (4)|RES# (6)|
|Mode Controle/モード制御|MD/FINED (2)|MD/FINED (3)|MD/FINED (5)|
|RXD|PB6/RXD1 (13)|PB6/RXD1 (15)|PB6/RXD1 (18)|
|TXD|PB5/TXD1 (14)|PB5/TXD1 (16)|PB5/TXD1 (19)|
|Power/電源|VCC (7)|VCC (8)|VCC (10)|
|GND/接地|VSS (5)|VSS (6)|VSS (8)|
|VREFH0|P14/VREFH0 (45)|P14/VREFH0 (48)|P14/VREFH0 (58)|
|VREFL0|P13/VREFL0 (46)|P13/VREFL0 (49)|P13/VREFL0 (59)|
|OSC out|P37/XTAL (4)|P37/XTAL (5)|P37/XTAL (7)|
|OSC in|P36/EXTAL (6)|P36/EXTAL (7)|P36/EXTAL (9)|

- VCL: 4.7uF/25V

|Mode/モード|MD|
|---|:---:|
|Serial BOOT/シリアルブート|0|
|Single Chip/シングルチップ|1|

---

## Device, Renesas / デバイス、ルネサス

- [device.hpp (SIG_RX14T)](../common/device.hpp?ts=4)
- [renesas.hpp (SIG_RX14T)](../common/renesas.hpp?ts=4)

|name space|Device, Renesas|デバイス、ルネサス|
|---|---|---|
|[clock_profile](../RX14T/clock_profile?ts=4)|Clock Profile|クロック・プロファイル|
|[SYSTEM](../RX24T/system.hpp?ts=4)|Clock Generation Circuit|クロック発生回路|
|[power_mgr](../RX14T/power_mgr.hpp?ts=4)|Low Power Consumption|消費電力低減機能|
|[ICU](../RX14T/icu.hpp?ts=4)|Interrupt Controller|割り込みコントローラ|
|[icu_mgr](../RX24T/icu_mgr.hpp?ts=4)|ICU Manager|ICU マネージャー|
|[MPC](../RX14T/mpc.hpp?ts=4)|Multi-Function Pin Controller|マルチファンクションピンコントローラ|
|[PORTx](../RX14T/port.hpp?ts=4)|I/O Ports|I/O ポート|
|[port_map](../RX14T/port_map.hpp?ts=4)|Port Mapping|ポート・マッピング|
|[port_map_mtu](../RX14T/port_map_mtu.hpp?ts=4)|Port Mapping MTU|ポート・マッピング MTU|
|[port_map_irq](../RX14T/port_map_irq.hpp?ts=4)|Port Mapping IRQ|ポート・マッピング IRQ|
|[FLASH](../RX130/flash.hpp?ts=4)|Flash Memory|フラッシュメモリ|
|[SYSTEM_IO](../RX24T/system_io.hpp?ts=4)|System In/Out (Clock Setting)|システム In/Out (クロック設定)|
|[FLASH_IO](../RX24T/flash_io.hpp?ts=4)|Flash In/Out|フラッシュ In/Out|
|[adc_in](../RX24T/adc_in.hpp?ts=4)|A/D Converter Input|A/D 変換入力|
|[dac_out](../RX24T/dac_out.hpp?ts=4)|D/A Converter Output|D/A 変換出力|
|[board_profile](../RX14T/board_profile?ts=4)|Board Profile|ボード・プロファイル|

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
|[POE3E](../RX13T/poe3.hpp?ts=4)|Port Output Enable 3|ポートアウトプットイネーブル３|
|[GPTW0](../RX600/gptw.hpp?ts=4)|General PWM Timer 0|汎用 PWM タイマ０|
|[GPTW1](../RX600/gptw.hpp?ts=4)|General PWM Timer 1|汎用 PWM タイマ１|
|[GPTW2](../RX600/gptw.hpp?ts=4)|General PWM Timer 2|汎用 PWM タイマ２|
|[POEG](../RX600/poeg.hpp?ts=4)|Port Output Enable GPTW|ポートアウトプットイネーブル GPTW|
|[TMR0](../RX600/tmr.hpp?ts=4)|8-Bit Timer 0|8 ビットタイマ０|
|[TMR1](../RX600/tmr.hpp?ts=4)|8-Bit Timer 1|8 ビットタイマ１|
|[TMR2](../RX600/tmr.hpp?ts=4)|8-Bit Timer 2|8 ビットタイマ２|
|[TMR3](../RX600/tmr.hpp?ts=4)|8-Bit Timer 3|8 ビットタイマ３|
|[CMT0](../RX600/cmt.hpp?ts=4)|Compare Match Timer 0|コンペアマッチタイマ０|
|[CMT1](../RX600/cmt.hpp?ts=4)|Compare Match Timer 1|コンペアマッチタイマ１|
|[IWDT](../RX600/iwdt.hpp?ts=4)|Independent Watchdog Timer|独立ウォッチドッグタイマ|
|[SCI1](../RX600/sci_g.hpp?ts=4)|Serial Communications Interface 1|シリアルコミュニケーションインタフェース１|
|[SCI5](../RX600/sci_g.hpp?ts=4)|Serial Communications Interface 5|シリアルコミュニケーションインタフェース５|
|[SCI6](../RX600/sci_g.hpp?ts=4)|Serial Communications Interface 6|シリアルコミュニケーションインタフェース６|
|[SCI12](../RX600/sci_h.hpp?ts=4)|Serial Communications Interface 12|シリアルコミュニケーションインタフェース１２|
|[RIIC0](../RX600/riic.hpp?ts=4)|I2C-bus Interface 0|I2C バスインタフェース０|
|[CRC](../RX600/crc.hpp?ts=4)|CRC Calculator|CRC 演算器|
|[S12AD](../RX14T/s12ad.hpp?ts=4)|12-Bit A/D Converter|12 ビット A/D コンバータ|
|[S12AD1](../RX14T/s12ad.hpp?ts=4)|12-Bit A/D Converter 1|12 ビット A/D コンバータ１|
|[DA](../RX14T/da.hpp?ts=4)|8-Bit D/A Converter|8 ビット D/A コンバータ|
|[TEMPS](../RX14T/temps.hpp?ts=4)|Temperature Sensor|温度センサ|
|[CMPC0](../RX600/cmpc.hpp?ts=4)|Comparator C0|コンパレーターＣ０|
|[CMPC1](../RX600/cmpc.hpp?ts=4)|Comparator C1|コンパレーターＣ１|
|[CMPC2](../RX600/cmpc.hpp?ts=4)|Comparator C2|コンパレーターＣ２|
|[DOC](../RX600/doc.hpp?ts=4)|Data Operation Circuit|データ演算回路|

---

## Port map order (IRQ) / ポートマップ候補 (IRQ)

- [port_map_irq.hpp](port_map_irq.hpp?ts=4)

### LFQFP48

|IRQ|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|IRQ0|P10 (48)|P37 (4)|P92 (24)|PE2 (8)|-|
|IRQ1|P11 (47)|P26 (33)|P93 (23)|-|-|
|IRQ2|P01 (--)|P22 (36)|P97 (19)|PB1 (17)|PD4 (11)|
|IRQ3|P24 (34)|P36 (6)|PB3 (16)|PD5 (10)|-|
|IRQ4|P00 (--)|P23 (35)|P13 (46)|P94 (22)|-|
|IRQ5|P02 (--)|P70 (31)|PB6 (13)|PD6 (9)|-|
|IRQ6|P14 (45)|P71 (30)|P90 (--)|-|-|
|IRQ7|P12 (--)|P72 (29)|PB5 (14)|-|-|

### LQFP52

|IRQ|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|IRQ0|P10 (51)|P37 (5)|P92 (26)|PE2 (9)|-|
|IRQ1|P11 (50)|P26 (36)|P93 (25)|-|-|
|IRQ2|P01 (--)|P22 (39)|P97 (21)|PB1 (19)|PD4 (12)|
|IRQ3|P24 (37)|P36 (7)|PB3 (18)|PD5 (11)|-|
|IRQ4|P00 (--)|P23 (38)|P13 (--)|P94 (24)|-|
|IRQ5|P02 (1)|P70 (33)|PB6 (15)|PD6 (10)|-|
|IRQ6|P14 (48)|P71 (32)|P90 (--)|-|-|
|IRQ7|P12 (--)|P72 (31)|PB5 (16)|-|-|

### LFQFP64

|IRQ|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|IRQ0|P10 (62)|P37 (7)|P92 (30)|PE2 (11)|-|
|IRQ1|P11 (61)|P26 (44)|P93 (29)|-|-|
|IRQ2|P01 (2)|P22 (48)|P97 (25)|PB1 (23)|PD4 (15)|
|IRQ3|P24 (46)|P36 (9)|PB3 (21)|PD5 (14)|-|
|IRQ4|P00 (4)|P23 (47)|P13 (59)|P94 (28)|-|
|IRQ5|P02 (1)|P70 (39)|PB6 (18)|PD6 (13)|-|
|IRQ6|P14 (58)|P71 (38)|P90 (32)|-|-|
|IRQ7|P12 (60)|P72 (37)|PB5 (19)|-|-|

---

## Port map order / ポートマップ候補

- [port_map.hpp](port_map.hpp?ts=4)

### LFQFP48

|Peripheral|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|SCI1 / RXD|P72 (37)|PB6 (18)|PD5 (14)|-|-|
|SCI1 / TXD|P71 (38)|PB5 (19)|PD3 (16)|-|-|
|SCI1 / SCK|P70 (39)|PB0 (24)|PD4 (15)|-|-|
|SCI5 / RXD|P24 (34)|P97 (19)|P97 (19)|PB6 (13)|PB6 (13)|
|SCI5 / TXD|P23 (35)|PB0 (18)|PB0 (18)|PB5 (14)|PB5 (14)|
|SCI5 / SCK|P22 (36)|P92 (24)|P96 (20)|PB1 (17)|PB7 (--)|
|SCI6 / RXD|P26 (33)|P36 (6)|P36 (6)|PB4 (15)|PB4 (15)|
|SCI6 / TXD|P11 (47)|P31 (32)|P37 (4)|PB3 (16)|PB3 (16)|
|SCI6 / SCK|P30 (--)|P30 (--)|P30 (--)|PB2 (--)|PG7 (2)|
|SCI12 / RXD|P36 (6)|P36 (6)|P76 (25)|P93 (23)|P93 (23)|
|SCI12 / TXD|P11 (47)|P37 (4)|P37 (4)|P94 (22)|P96 (20)|
|SCI12 / SCK|P75 (26)|P92 (24)|PB1 (17)|P92 (24)|PG7 (2)|
|RIIC0 / SCL|P97 (19)|P26 (33)|-|-|-|
|RIIC0 / SDA|PB0 (18)|P31 (32)|-|-|-|

### LQFP52

|Peripheral|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|SCI1 / RXD|P72 (31)|PB6 (15)|PD5 (11)|-|-|
|SCI1 / TXD|P71 (32)|PB5 (16)|PD3 (13)|-|-|
|SCI1 / SCK|P70 (33)|PB0 (20)|PD4 (12)|-|-|
|SCI5 / RXD|P24 (37)|P97 (21)|P97 (21)|PB6 (15)|PB6 (15)|
|SCI5 / TXD|P23 (38)|PB0 (20)|PB0 (20)|PB5 (16)|PB5 (19)|
|SCI5 / SCK|P22 (39)|P92 (26)|P96 (22)|PB1 (19)|PB7 (17)|
|SCI6 / RXD|P26 (36)|P36 (7)|P36 (7)|PB4 (17)|PB4 (17)|
|SCI6 / TXD|P11 (50)|P31 (35)|P37 (5)|PB3 (18)|PB3 (18)|
|SCI6 / SCK|P30 (--)|P30 (--)|P30 (--)|PB2 (--)|PG7 (3)|
|SCI12 / RXD|P36 (7)|P36 (7)|P76 (27)|P93 (25)|P93 (25)|
|SCI12 / TXD|P11 (50)|P37 (5)|P37 (5)|P94 (24)|P96 (22)|
|SCI12 / SCK|P75 (28)|P92 (26)|PB1 (19)|P92 (26)|PG7 (3)|
|RIIC0 / SCL|P97 (21)|P26 (36)|-|-|-|
|RIIC0 / SDA|PB0 (20)|P31 (35)|-|-|-|

### LFQFP64

|Peripheral|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|SCI1 / RXD|P72 (29)|PB6 (13)|PD5 (10)|-|-|
|SCI1 / TXD|P71 (30)|PB5 (14)|PD3 (12)|-|-|
|SCI1 / SCK|P70 (31)|PB0 (18)|PD4 (11)|-|-|
|SCI5 / RXD|P24 (46)|P97 (25)|P97 (25)|PB6 (18)|PB6 (18)|
|SCI5 / TXD|P23 (47)|PB0 (24)|PB0 (24)|PB5 (19)|PB5 (19)|
|SCI5 / SCK|P22 (48)|P92 (30)|P96 (26)|PB1 (23)|PB7 (17)|
|SCI6 / RXD|P26 (44)|P36 (9)|P36 (9)|PB4 (20)|PB4 (20)|
|SCI6 / TXD|P11 (61)|P31 (42)|P37 (7)|PB3 (21)|PB3 (21)|
|SCI6 / SCK|P30 (43)|P30 (43)|P30 (43)|PB2 (22)|PG7 (5)|
|SCI12 / RXD|P36 (9)|P36 (9)|P76 (33)|P93 (29)|P93 (29)|
|SCI12 / TXD|P11 (61)|P37 (7)|P37 (7)|P94 (28)|P96 (26)|
|SCI12 / SCK|P75 (34)|P92 (30)|PB1 (23)|P92 (30)|PG7 (5)|
|RIIC0 / SCL|P97 (25)|P26 (44)|-|-|-|
|RIIC0 / SDA|PB0 (24)|P31 (42)|-|-|-|

---

## Port map order (GPTW) / ポートマップ候補 (GPTW)

- [port_map_gptw.hpp](port_map_gptw.hpp?ts=4)

### LFQFP48

|GPTW|FIRST|SECOND|THIRD|FOURTH|FIFTH|SIXTH|
|---|---|---|---|---|---|---|
|GTIOC0A #|P26 (33)|P36 (6)|P71 (30)|P94 (22)|-|-|
|GTIOC0B #|P31 (32)|P74 (27)|P97 (19)|-|-|-|
|GTIOC1A #|P31 (32)|P72 (29)|P92 (24)|P95 (21)|PB5 (14)|PD3 (12)|
|GTIOC1B #|P75 (26)|P93 (23)|PB0 (18)|PD4 (11)|-|-|
|GTIOC2A #|P04 (--)|P23 (35)|P73 (28)|P96 (20)|PB5 (14)|PD5 (10)|
|GTIOC2B #|P03 (--)|P24 (34)|P76 (25)|PB1 (17)|PB6 (13)|PD6 (9)|
|GTETRGA|P25 (--)|P97 (19)|PE2 (8)|-|-|-|
|GTADSM0|P23 (35)|P46 (38)|PB0 (18)|-|-|-|
|GTADSM1|P22 (36)|P44 (40)|P97 (19)|-|-|-|
|GTCPPO0|P24 (34)|P36 (6)|P70 (31)|PB6 (13)|-|-|

### LQFP52

|GPTW|FIRST|SECOND|THIRD|FOURTH|FIFTH|SIXTH|
|---|---|---|---|---|---|---|
|GTIOC0A #|P26 (36)|P36 (7)|P71 (32)|P94 (24)|-|-|
|GTIOC0B #|P31 (35)|P74 (29)|P97 (21)|-|-|-|
|GTIOC1A #|P31 (35)|P72 (31)|P92 (26)|P95 (23)|PB5 (16)|PD3 (13)|
|GTIOC1B #|P75 (28)|P93 (25)|PB0 (20)|PD4 (12)|-|-|
|GTIOC2A #|P04 (52)|P23 (38)|P73 (30)|P96 (22)|PB5 (16)|PD5 (11)|
|GTIOC2B #|P03 (--)|P24 (37)|P76 (27)|PB1 (19)|PB6 (15)|PD6 (10)|
|GTETRGA|P25 (--)|P97 (21)|PE2 (9)|-|-|-|
|GTADSM0|P23 (38)|P46 (41)|PB0 (20)|-|-|-|
|GTADSM1|P22 (39)|P44 (43)|P97 (21)|-|-|-|
|GTCPPO0|P24 (37)|P36 (7)|P70 (33)|PB6 (15)|-|-|

### LFQFP64

|GPTW|FIRST|SECOND|THIRD|FOURTH|FIFTH|SIXTH|
|---|---|---|---|---|---|---|
|GTIOC0A #|P26 (44)|P36 (9)|P71 (38)|P94 (28)|-|-|
|GTIOC0B #|P31 (42)|P74 (35)|P97 (25)|-|-|-|
|GTIOC1A #|P31 (42)|P72 (37)|P92 (30)|P95 (27)|PB5 (19)|PD3 (16)|
|GTIOC1B #|P75 (34)|P93 (29)|PB0 (24)|PD4 (15)|-|-|
|GTIOC2A #|P04 (63)|P23 (47)|P73 (36)|P96 (26)|PB5 (19)|PD5 (14)|
|GTIOC2B #|P03 (64)|P24 (46)|P76 (33)|PB1 (23)|PB6 (18)|PD6 (13)|
|GTETRGA|P25 (45)|P97 (25)|PE2 (11)|-|-|-|
|GTADSM0|P23 (47)|P46 (50)|PB0 (24)|-|-|-|
|GTADSM1|P22 (48)|P44 (52)|P97 (25)|-|-|-|
|GTCPPO0|P24 (46)|P36 (9)|P70 (39)|PB6 (18)|-|-|

---

## Port map order (MTU) / ポートマップ候補 (MTU)

- [port_map_mtu.hpp](port_map_mtu.hpp?ts=4)

### LFQFP48

|MTU|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|MTIOC0A #|P30 (--)|P36 (6)|PB1 (17)|PD3 (12)|-|
|MTIOC0B #|P25 (--)|P92 (24)|PB0 (18)|PD4 (11)|-|
|MTIOC0C #|P33 (--)|P93 (23)|P97 (19)|PD5 (10)|-|
|MTIOC0D #|P32 (--)|P96 (20)|PD6 (9)|-|-|
|MTIOC1A #|P04 (--)|P36 (6)|P92 (24)|P94 (22)|-|
|MTIOC1B #|P03 (--)|P95 (21)|PB5 (14)|-|-|
|MTIOC2A #|P95 (21)|PB5 (14)|-|-|-|
|MTIOC2B #|P93 (23)|P94 (22)|PB6 (13)|-|-|
|MTIOC3A #|P11 (47)|P33 (--)|PB5 (14)|-|-|
|MTIOC3B #|P26 (33)|P71 (30)|P94 (22)|-|-|
|MTIOC3C #|P32 (--)|PB6 (13)|-|-|-|
|MTIOC3D #|P74 (27)|P97 (19)|-|-|-|
|MTIOC4A #|P31 (32)|P36 (6)|P72 (29)|P95 (21)|PD3 (12)|
|MTIOC4B #|P25 (--)|P73 (28)|P96 (20)|PD4 (11)|-|
|MTIOC4C #|P11 (47)|P75 (26)|PB0 (18)|PD5 (10)|-|
|MTIOC4D #|P76 (25)|PB1 (17)|PD6 (9)|-|-|
|MTIOC5U #|P24 (34)|P91 (--)|-|-|-|
|MTIOC5V #|P23 (35)|P90 (--)|-|-|-|
|MTIOC5W #|P22 (36)|PB2 (--)|-|-|-|
|MTCLKA #|P23 (35)|P33 (--)|P93 (23)|P97 (19)|-|
|MTCLKB #|P22 (36)|P32 (--)|P96 (20)|-|-|
|MTCLKC #|P11 (47)|P30 (--)|PB0 (18)|-|-|
|MTCLKD #|P10 (48)|P25 (--)|PB6 (13)|-|-|
|ADSM0|PB0 (18)|-|-|-|-|
|ADSM1|P97 (19)|-|-|-|-|

### LQFP52

|MTU|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|MTIOC0A #|P30 (--)|P36 (7)|PB1 (19)|PD3 (13)|-|
|MTIOC0B #|P25 (--)|P92 (26)|PB0 (20)|PD4 (12)|-|
|MTIOC0C #|P33 (34)|P93 (25)|P97 (21)|PD5 (11)|-|
|MTIOC0D #|P32 (--)|P96 (22)|PD6 (10)|-|-|
|MTIOC1A #|P04 (52)|P36 (7)|P92 (26)|P94 (24)|-|
|MTIOC1B #|P03 (--)|P95 (23)|PB5 (16)|-|-|
|MTIOC2A #|P95 (23)|PB5 (16)|-|-|-|
|MTIOC2B #|P93 (25)|P94 (24)|PB6 (15)|-|-|
|MTIOC3A #|P11 (50)|P33 (34)|PB5 (16)|-|-|
|MTIOC3B #|P26 (36)|P71 (32)|P94 (24)|-|-|
|MTIOC3C #|P32 (--)|PB6 (15)|-|-|-|
|MTIOC3D #|P74 (29)|P97 (21)|-|-|-|
|MTIOC4A #|P31 (35)|P36 (7)|P72 (31)|P95 (23)|PD3 (13)|
|MTIOC4B #|P25 (--)|P73 (30)|P96 (22)|PD4 (12)|-|
|MTIOC4C #|P11 (50)|P75 (28)|PB0 (20)|PD5 (11)|-|
|MTIOC4D #|P76 (27)|PB1 (19)|PD6 (10)|-|-|
|MTIOC5U #|P24 (37)|P91 (--)|-|-|-|
|MTIOC5V #|P23 (38)|P90 (--)|-|-|-|
|MTIOC5W #|P22 (39)|PB2 (--)|-|-|-|
|MTCLKA #|P23 (38)|P33 (34)|P93 (25)|P97 (21)|-|
|MTCLKB #|P22 (39)|P32 (--)|P96 (22)|-|-|
|MTCLKC #|P11 (50)|P30 (--)|PB0 (20)|-|-|
|MTCLKD #|P10 (51)|P25 (--)|PB6 (15)|-|-|
|ADSM0|PB0 (20)|-|-|-|-|
|ADSM1|P97 (21)|-|-|-|-|

### LFQFP64

|MTU|FIRST|SECOND|THIRD|FOURTH|FIFTH|
|---|---|---|---|---|---|
|MTIOC0A #|P30 (43)|P36 (9)|PB1 (23)|PD3 (16)|-|
|MTIOC0B #|P25 (45)|P92 (30)|PB0 (24)|PD4 (15)|-|
|MTIOC0C #|P33 (40)|P93 (29)|P97 (25)|PD5 (14)|-|
|MTIOC0D #|P32 (41)|P96 (26)|PD6 (13)|-|-|
|MTIOC1A #|P04 (63)|P36 (9)|P92 (30)|P94 (28)|-|
|MTIOC1B #|P03 (64)|P95 (27)|PB5 (19)|-|-|
|MTIOC2A #|P95 (27)|PB5 (19)|-|-|-|
|MTIOC2B #|P93 (29)|P94 (28)|PB6 (18)|-|-|
|MTIOC3A #|P11 (61)|P33 (40)|PB5 (19)|-|-|
|MTIOC3B #|P26 (44)|P71 (38)|P94 (28)|-|-|
|MTIOC3C #|P32 (41)|PB6 (18)|-|-|-|
|MTIOC3D #|P74 (35)|P97 (25)|-|-|-|
|MTIOC4A #|P31 (42)|P36 (9)|P72 (37)|P95 (27)|PD3 (16)|
|MTIOC4B #|P25 (45)|P73 (36)|P96 (26)|PD4 (15)|-|
|MTIOC4C #|P11 (61)|P75 (34)|PB0 (24)|PD5 (14)|-|
|MTIOC4D #|P76 (33)|PB1 (23)|PD6 (13)|-|-|
|MTIOC5U #|P24 (46)|P91 (31)|-|-|-|
|MTIOC5V #|P23 (47)|P90 (32)|-|-|-|
|MTIOC5W #|P22 (48)|PB2 (22)|-|-|-|
|MTCLKA #|P23 (47)|P33 (40)|P93 (29)|P97 (25)|-|
|MTCLKB #|P22 (48)|P32 (41)|P96 (26)|-|-|
|MTCLKC #|P11 (61)|P30 (43)|PB0 (24)|-|-|
|MTCLKD #|P10 (62)|P25 (45)|PB6 (18)|-|-|
|ADSM0|PB0 (24)|-|-|-|-|
|ADSM1|P97 (25)|-|-|-|-|

---

## Port map order (TMR) / ポートマップ候補 (TMR)

- [port_map_tmr.hpp](port_map_tmr.hpp?ts=4)

### LFQFP48

|TMR|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|TMO0|P04 (--)|PB5 (14)|PD3 (12)|-|
|TMCI0|PB6 (13)|PD4 (11)|-|-|
|TMRI0|PE2 (8)|PD5 (10)|-|-|
|TMO1|P10 (48)|P93 (23)|P96 (20)|PD6 (9)|
|TMCI1|P91 (--)|P97 (19)|PE2 (8)|-|
|TMRI1|P92 (24)|PB0 (18)|PD7 (--)|-|
|TMO2|P11 (47)|P23 (35)|P74 (27)|-|
|TMCI2|P24 (34)|P75 (26)|-|-|
|TMRI2|P22 (36)|P76 (25)|-|-|
|TMO3|P11 (47)|P26 (33)|-|-|
|TMCI3|P04 (--)|P31 (32)|-|-|
|TMRI3|P10 (48)|P25 (--)|P73 (28)|-|

### LQFP52

|TMR|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|TMO0|P04 (52)|PB5 (16)|PD3 (13)|-|
|TMCI0|PB6 (15)|PD4 (12)|-|-|
|TMRI0|PE2 (9)|PD5 (11)|-|-|
|TMO1|P10 (51)|P93 (25)|P96 (22)|PD6 (10)|
|TMCI1|P91 (--)|P97 (21)|PE2 (9)|-|
|TMRI1|P92 (26)|PB0 (20)|PD7 (--)|-|
|TMO2|P11 (50)|P23 (38)|P74 (29)|-|
|TMCI2|P24 (37)|P75 (28)|-|-|
|TMRI2|P22 (39)|P76 (27)|-|-|
|TMO3|P11 (50)|P26 (36)|-|-|
|TMCI3|P04 (52)|P31 (35)|-|-|
|TMRI3|P10 (51)|P25 (--)|P73 (30)|-|

### LFQFP64

|TMR|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|TMO0|P04 (63)|PB5 (19)|PD3 (16)|-|
|TMCI0|PB6 (18)|PD4 (15)|-|-|
|TMRI0|PE2 (11)|PD5 (14)|-|-|
|TMO1|P10 (62)|P93 (29)|P96 (26)|PD6 (13)|
|TMCI1|P91 (31)|P97 (25)|PE2 (11)|-|
|TMRI1|P92 (30)|PB0 (24)|PD7 (12)|-|
|TMO2|P11 (61)|P23 (47)|P74 (35)|-|
|TMCI2|P24 (46)|P75 (34)|-|-|
|TMRI2|P22 (48)|P76 (33)|-|-|
|TMO3|P11 (61)|P26 (44)|-|-|
|TMCI3|P04 (63)|P31 (42)|-|-|
|TMRI3|P10 (62)|P25 (45)|P73 (36)|-|

---

## 12 Bits A/D Converter input (S12AD) / 12 ビット A/D コンバーター入力 (S12AD)

- [s12adf.hpp](s12adf.hpp?ts=4)

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

### LQFP52

|ANALOG|Port|
|---|---|
|AN000|P40 (47)|
|AN001|P41 (46)|
|AN002|P42 (45)|
|AN003|P43 (44)|
|AN004|P44 (43)|
|AN005|P45 (32)|
|AN006|P46 (31)|
|AN007|P47 (40)|

### LFQFP64

|ANALOG|Port|
|---|---|
|AN000|P40 (56)|
|AN001|P41 (55)|
|AN002|P42 (54)|
|AN003|P43 (53)|
|AN004|P44 (52)|
|AN005|P45 (51)|
|AN006|P46 (50)|
|AN007|P47 (49)|

---

## 12 Bits A/D Converter input (S12AD1) / 12 ビット A/D コンバーター入力 (S12AD1)

- [s12adf.hpp](s12adf.hpp?ts=4)

### LFQFP48

|ANALOG|Port|
|---|---|
|AN102|P11 (47)|
|AN103|P10 (48)|
|AN104|P12 (--)|
|AN105|P13 (46)|
|AN106|P14 (45)|
|AN107|P15 (--)|

### LQFP52

|ANALOG|Port|
|---|---|
|AN102|P11 (50)|
|AN103|P10 (51)|
|AN104|P12 (--)|
|AN105|P13 (49)|
|AN106|P14 (48)|
|AN107|P15 (--)|

### LFQFP64

|ANALOG|Port|
|---|---|
|AN102|P11 (61)|
|AN103|P10 (62)|
|AN104|P12 (60)|
|AN105|P13 (59)|
|AN106|P14 (58)|
|AN107|P15 (57)|

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
