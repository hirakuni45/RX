
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

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|8K|1024|1/1024|1|0xFF|4|

---

## RX111 Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F51117|384K|64K|8K|[R5F51117.ld](R5F51117.ld?ts=4)|4096|1024|
|R5F51116|256K|32K|8K|[R5F51116.ld](R5F51116.ld?ts=4)|1536|512|
|R5F51115|128K|16K|8K|[R5F51115.ld](R5F51115.ld?ts=4)|768|256|

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

## peripheral / ペリフェラル

|Peripheral|Function|機能|
|---|---|---|
|CAC|Clock Frequency Accuracy Measurement Circuit|クロック周波数精度測定回路|
|DTC|Data Transfer Controller|データトランスファコントローラ|
|ELC|Event Link Controller|イベントリンクコントローラ|
|MTU0|Multi-Function Timer Pulse Unit 0|マルチファンクションタイマパルスユニット０|
|MTU1|Multi-Function Timer Pulse Unit 1|マルチファンクションタイマパルスユニット１|
|MTU2|Multi-Function Timer Pulse Unit 2|マルチファンクションタイマパルスユニット２|
|MTU3|Multi-Function Timer Pulse Unit 3|マルチファンクションタイマパルスユニット３|
|MTU4|Multi-Function Timer Pulse Unit 4|マルチファンクションタイマパルスユニット４|
|MTU5|Multi-Function Timer Pulse Unit 5|マルチファンクションタイマパルスユニット５|
|POE2|Port Output Enable 2|ポートアウトプットイネーブル２|
|TMR0|8-Bit Timer 0|8 ビットタイマ０|
|TMR1|8-Bit Timer 1|8 ビットタイマ１|
|TMR2|8-Bit Timer 2|8 ビットタイマ２|
|TMR3|8-Bit Timer 3|8 ビットタイマ３|
|CMT0|Compare Match Timer 0|コンペアマッチタイマ０|
|CMT1|Compare Match Timer 1|コンペアマッチタイマ１|
|RTC|Realtime Clock|リアルタイムクロック|
|IWDT|Independent Watchdog Timer|独立ウォッチドッグタイマ|
|USB0|USB 2.0 FS Host/Function Module 0|USB 2.0 FS ホスト/ファンクションモジュール０|
|SCI1|Serial Communications Interface 1|シリアルコミュニケーションインタフェース１|
|SCI5|Serial Communications Interface 5|シリアルコミュニケーションインタフェース５|
|SCI12|Serial Communications Interface 12|シリアルコミュニケーションインタフェース１２|
|RIIC0|I2C-bus Interface 0|I2C バスインタフェース０|
|RSPI0|Serial Peripheral Interface 0|シリアルペリフェラルインタフェース０|
|CRC|CRC Calculator|CRC 演算器|
|S12AD|12-Bit A/D Converter|12 ビット A/D コンバータ|
|DA|8-Bit D/A Converter|8 ビット D/A コンバータ|
|DOC|Data Operation Circuit|データ演算回路|

---

## port map order / ポートマップ候補

### LFQFP64

|Peripheral|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|SCI1 / RXD|P15 (19)|P30 (4)|PC6 (28)|-|
|SCI1 / TXD|P16 (18)|P26 (3)|PC7 (27)|-|
|SCI1 / SCK|P17 (17)|P27 (2)|PC5 (29)|-|
|SCI5 / RXD|PA3 (43)|PC2 (32)|-|-|
|SCI5 / TXD|PA4 (42)|PC3 (31)|-|-|
|SCI5 / SCK|PA1 (44)|PC4 (30)|-|-|
|SCI12 / RXD|PE2 (49)|P17 (17)|-|-|
|SCI12 / TXD|PE1 (50)|P14 (20)|-|-|
|SCI12 / SCK|PE0 (51)|P27 (2)|-|-|
|RIIC0 / SCL|P16 (18)|PB0 (39)|-|-|
|RIIC0 / SDA|P17 (17)|PA6 (41)|-|-|
|RSPI0 / RSPCK|P15 (19)|PB0 (39)|PC5 (29)|PE3 (48)|
|RSPI0 / MOSI|P16 (18)|PA6 (41)|PC6 (28)|PE4 (47)|
|RSPI0 / MISO|P17 (17)|PA3 (43)|PC7 (27)|PA3 (43)|
|RSPI0 / SSL0|P14 (20)|PA4 (42)|PC4 (30)|-|
|RSPI0 / SSL1|PA0 (45)|-|-|-|
|RSPI0 / SSL2|PA1 (44)|-|-|-|
|RSPI0 / SSL3|PC2 (32)|-|-|-|

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
