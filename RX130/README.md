
## RX130 features / 特徴

- RXv1 core / RXv1 コア
- Maximum operating frequency 32MHz / 最大動作周波数 32MHz
- 1.8V ～ 5.5V Operation / 動作
- Capacitive touch sensor / 静電容量式タッチセンサ
- Low power timer / ローパワータイマー
- Remote control signal reception function / リモコン信号受信機能
- 12 Bits A/D / １２ビットＡ／Ｄ変換器
- 8 Bits D/A / ８ビットＤ／Ａ変換器

### Package/パッケージ

|R5F5130---XX|Package/パッケージ|Pin/ピン数|Pitch/ピッチ|
|---|:-:|:-:|:-:|
|R5F5130xxxFP|LFQFP|100|0.50|
|R5F5130xxxFN|LFQFP|80|0.50|
|R5F5130xxxFM|LFQFP|64|0.50|
|R5F5130xxxFK|LQFP|64|0.80|
|R5F5130xxxFL|LFQFP|48|0.50|
|R5F5130xxxNE|HWQFN|48|0.50|

### Ambient operating temperature/動作周囲温度

|R5F5130--X--|degree Celsius|
|---|:-:|
|R5F5130xxDxx|-40 ～ +85℃|
|R5F5130xxGxx|-40 ～ +105℃|

### Version

|R5F5130-X---|Version|
|---|:-:|
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

### Data Flash/データ・フラッシュ

|Capacity|Erase Size|Blank Check Size|Write Size|Erase Value|ID|
|:-:|:-:|:-:|:-:|:-:|:-:|
|8K|1024|1/1024|1|0xFF|4|

---

## RX130 Linker file / リンカーファイル

|Type|Code Flash|RAM|Data Flash|Linker File|Ustack|Istack|
|---|:-:|:-:|:-:|---|:-:|:-:|
|R5F51306|256K|32K|8K|[R5F51306.ld](R5F51306.ld?ts=4)|1536|512|
|R5F51305|128K|16K|8K|[R5F51305.ld](R5F51305.ld?ts=4)|1024|256|

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
|FLASH Definition/FLASH 定義|[flash.hpp](flash.hpp?ts=4)||
|System Definition/システム定義|[system.hpp](system.hpp?ts=4)||

---

## Basic Pin Assignments / 基本ピンアサイン

|Terminal/端子|LFQFP 64|LFQFP 80|LFQFP100|
|---|---|---|---|
|VCL|VCL(2)|VCL(4)|VCL(5)|
|Reset Input/リセット入力|RES#(6)|RES#(9)|RES#(10)|
|Mode Controle/モード制御|MD/FINED(3)|MD/FINED(6)|MD/FINED(7)|
|RXD|P30/RXD1(14)|P30/RXD1(18)|P30/RXD1(20)|
|TXD|P26/TXD1(16)|P26/TXD1(20)|P26/TXD1(22)|
|Power/電源|VCC(10), VCC(38)|VCC(13), VCC(48)|VCC(14), VCC(60)|
|GND/接地|VSS(8), VSS(40)|VSS(11), VSS(50)|VSS(12), VSS(62)|
|Analog Power/アナログ電源|AVCC0(62)|AVCC0(77)|AVCC0(97)|
|Analog GND/アナログ接地|AVSS0(64)|AVSS0(79)|AVSS0(99)|
|Analog Refarence L/アナログ基準電源Ｌ|VREFL0(59)|VREFL0(74)|VREFL0(94)|
|Analog Refarence H/アナログ基準電源Ｈ|VREFH0(61)|VREFH0(76)|VREFH0(96)|
|OSC out|XTAL(7)|XTAL(10)|XTAL(11)|
|OSC in|EXTAL(9)|EXTAL(12)|EXTAL(13)|
|Sub OSC out|XCOUT(5)|XCOUT(8)|XCOUT(9)|
|Sub OSC in|XCIN(4)|XCIN(7)|XCIN(8)|

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
|LPT|Low Power Timer|ローパワータイマ|
|IWDT|Independent Watchdog Timer|独立ウォッチドッグタイマ|
|SCI0|Serial Communications Interface 0|シリアルコミュニケーションインタフェース０|
|SCI1|Serial Communications Interface 1|シリアルコミュニケーションインタフェース１|
|SCI5|Serial Communications Interface 5|シリアルコミュニケーションインタフェース５|
|SCI6|Serial Communications Interface 6|シリアルコミュニケーションインタフェース６|
|SCI8|Serial Communications Interface 8|シリアルコミュニケーションインタフェース８|
|SCI9|Serial Communications Interface 9|シリアルコミュニケーションインタフェース９|
|SCI11|Serial Communications Interface 11|シリアルコミュニケーションインタフェース１１|
|SCI12|Serial Communications Interface 12|シリアルコミュニケーションインタフェース１２|
|REMC0|Remote Control Signal Receiver 0|リモコン信号受信機能０|
|REMC1|Remote Control Signal Receiver 1|リモコン信号受信機能１|
|RIIC0|I2C-bus Interface 0|I2C バスインタフェース０|
|RSCAN|RSCAN Module|RSCAN インタフェース|
|RSPI0|Serial Peripheral Interface 0|シリアルペリフェラルインタフェース０|
|CRC|CRC Calculator|CRC 演算器|
|CTSU|Capacitive Touch Sensing Unit|静電容量式タッチセンサ|
|S12AD|12-Bit A/D Converter|12 ビット A/D コンバータ|
|DA|8-Bit D/A Converter|8 ビット D/A コンバータ|
|CMPB|Comparator B|コンパレータＢ|
|DOC|Data Operation Circuit|データ演算回路|

---

## port map order / ポートマップ候補

### LFQFP64

|Peripheral|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|SCI0 / RXD|P21 (--)|-|-|-|
|SCI0 / TXD|P20 (--)|-|-|-|
|SCI0 / SCK|P22 (--)|-|-|-|
|SCI1 / RXD|P15 (19)|P30 (14)|-|-|
|SCI1 / TXD|P16 (18)|P26 (16)|-|-|
|SCI1 / SCK|P17 (17)|P27 (15)|-|-|
|SCI5 / RXD|PA2 (--)|PA3 (43)|PC2 (32)|PC2 (32)|
|SCI5 / TXD|PA4 (42)|PA4 (42)|PC3 (31)|PC3 (31)|
|SCI5 / SCK|PA1 (44)|PA1 (44)|PC4 (30)|PC1 (--)|
|SCI6 / RXD|P33 (--)|PB0 (39)|PD1 (--)|-|
|SCI6 / TXD|P32 (12)|PB1 (37)|PD0 (--)|-|
|SCI6 / SCK|P34 (--)|PB3 (36)|PD2 (--)|-|
|SCI8 / RXD|PC6 (28)|-|-|-|
|SCI8 / TXD|PC7 (27)|-|-|-|
|SCI8 / SCK|PC5 (29)|-|-|-|
|SCI9 / RXD|PB6 (34)|-|-|-|
|SCI9 / TXD|PB7 (33)|-|-|-|
|SCI9 / SCK|PB5 (35)|-|-|-|
|SCI12 / RXD|PE2 (49)|-|-|-|
|SCI12 / TXD|PE1 (50)|-|-|-|
|SCI12 / SCK|PE0 (51)|-|-|-|
|RIIC0 / SCL|P16 (18)|P12 (--)|-|-|
|RIIC0 / SDA|P17 (17)|P13 (--)|-|-|
|RSPI0 / RSPCK|PA5 (--)|PB0 (39)|PC5 (29)|-|
|RSPI0 / MOSI|PA6 (41)|P16 (18)|PC6 (28)|-|
|RSPI0 / MISO|PA7 (--)|P17 (17)|PC7 (27)|-|
|RSPI0 / SSL0|PA4 (42)|PC4 (30)|-|-|
|RSPI0 / SSL1|PA0 (45)|PC0 (--)|-|-|
|RSPI0 / SSL2|PA1 (44)|PC1 (--)|-|-|
|RSPI0 / SSL3|PA2 (--)|PC2 (32)|-|-|

### LFQFP100

|Peripheral|FIRST|SECOND|THIRD|FOURTH|
|---|---|---|---|---|
|SCI0 / RXD|P21 (27)|-|-|-|
|SCI0 / TXD|P20 (28)|-|-|-|
|SCI0 / SCK|P22 (26)|-|-|-|
|SCI1 / RXD|P15 (31)|P30 (20)|-|-|
|SCI1 / TXD|P16 (30)|P26 (22)|-|-|
|SCI1 / SCK|P17 (29)|P27 (21)|-|-|
|SCI5 / RXD|PA2 (68)|PA3 (67)|PC2 (50)|PC2 (50)|
|SCI5 / TXD|PA4 (66)|PA4 (66)|PC3 (49)|PC3 (49)|
|SCI5 / SCK|PA1 (69)|PA1 (69)|PC4 (48)|PC1 (51)|
|SCI6 / RXD|P33 (17)|PB0 (61)|PD1 (85)|-|
|SCI6 / TXD|P32 (18)|PB1 (59)|PD0 (86)|-|
|SCI6 / SCK|P34 (16)|PB3 (57)|PD2 (84)|-|
|SCI8 / RXD|PC6 (46)|-|-|-|
|SCI8 / TXD|PC7 (45)|-|-|-|
|SCI8 / SCK|PC5 (47)|-|-|-|
|SCI9 / RXD|PB6 (54)|-|-|-|
|SCI9 / TXD|PB7 (53)|-|-|-|
|SCI9 / SCK|PB5 (55)|-|-|-|
|SCI12 / RXD|PE2 (76)|-|-|-|
|SCI12 / TXD|PE1 (77)|-|-|-|
|SCI12 / SCK|PE0 (78)|-|-|-|
|RIIC0 / SCL|P16 (30)|P12 (34)|-|-|
|RIIC0 / SDA|P17 (29)|P13 (33)|-|-|
|RSPI0 / RSPCK|PA5 (65)|PB0 (61)|PC5 (47)|-|
|RSPI0 / MOSI|PA6 (64)|P16 (30)|PC6 (46)|-|
|RSPI0 / MISO|PA7 (63)|P17 (29)|PC7 (45)|-|
|RSPI0 / SSL0|PA4 (66)|PC4 (48)|-|-|
|RSPI0 / SSL1|PA0 (70)|PC0 (52)|-|-|
|RSPI0 / SSL2|PA1 (69)|PC1 (51)|-|-|
|RSPI0 / SSL3|PA2 (68)|PC2 (50)|-|-|

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
