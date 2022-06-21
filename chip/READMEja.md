各種デバイス（ IC ）ドライバー
=========

[英語版](./README.md)

---

## 概要

I2C、SPI、BUS、CAN、等のインターフェースで通信を行うデバイス制御クラス

---

## デバイス・リスト

|デバイス名|機能|メーカー|I/F|電源電圧|URL|
|---------|----|--------|---|--------|---|
|BMP180|digital barometric pressure sensor|BOSCH|I2C|3.3|[秋月電子](http://akizukidenshi.com/catalog/g/gI-06585/)|
|BMP280|digital barometric pressure sensor|BOSCH|I2C|3.3|[秋月電子](http://akizukidenshi.com/catalog/g/gI-06585/)|   
|DS1371|内部バイナリー、I²Cリアルタイムクロック|Maxim Integrated|I2C|1.7 to 5.5|[MAXIM](https://www.maximintegrated.com/jp/products/digital/real-time-clocks/DS1371.html)|
|DS3231|超高精度I²Cリアルタイムクロック|Maxim Integrated|I2C|3.3|[MAXIM](https://www.maximintegrated.com/jp/products/digital/real-time-clocks/DS3231.html)|
|EEPROM|I2C EEPROM|各社|I2C|3.3 to 5.5|-|
|EUI_XX (25AA02E48/25AA02E64)|2K SPI Bus Serial EEPROMs with EUI-48 or EUI-64 Node Identity|Microchip|SPI|3.3|-|
|LTC2348_16|Octal, 16-Bit, 200ksps Differential +-10.24V Input SoftSpan ADC|LINEAR TECHNOLOGY|SPI|3.3|-|
|MAX7219|8 Digits LED Driver|Maxim Integrated|SPI|3.3|-|
|MPU6050|Digital Motion Processor|InvenSense|I2C|3.3|[InvenSense](https://www.invensense.com/products/motion-tracking/6-axis/mpu-6050/)|
|NTCTH|NTC サーミスタ|muRata|アナログ|-|-|   
|SH1106|132x64 Dot Matrix OLED/PLED Segment/Common Driver with Controller|SINO WEALTH|SPI|3.3|[Other](http://www.rhydolabz.com/documents/sh1106_datasheet.pdf)|
|SSD1306|128 x 64 Dot Matrix OLED/PLED Segment/Common Driver with Controller|SOLOMON SYSTECH|SPI|3.3|-|
|ST7565/ST7565R/ST7567|65 x 132 Dot Matrix LCD Controller/Driver|Sitronix|SPI|3.3|[Other](http://www.hpinfotech.ro/)|
|UC1701|Single-Chip, Ultra-Low Power 65COM by 132SEG Passive Matrix LCD Controller-Driver|ULTRA CHIP|SPI|3.3|[Other](http://www.hpinfotech.ro/UC1701.pdf)|   
|VS1063|MP3 / OGG VORBIS ENCODER AND AUDIO CODEC|VLSI Solution|SPI|3.3|[VLSI](http://www.vlsi.fi/fileadmin/VS1063.pdf)|
|phy_base(LAN8720/DP83822/KSZ8041NL)|Ethernet default PHY device|Microchip/Texas Instruments/MICREL|-|3.3|-|
|VL53L0X|World smallest Time-of-Flight (ToF) ranging sensor|STMicroelectronics|I2C|3.3|[ST](http://www.st.com/ja/imaging-and-photonics-solutions/vl53l0x.html)|
|AD9833|Programmable Waveform Generator|ANALOG DEVICES|SPI|3.3|[AD](http://www.analog.com/media/jp/technical-documentation/data-sheets/AD9833_JP.pdf)|
|AD985X (AD9850, AD9851)|Programmable Waveform Generator|ANALOG DEVICES|3-Wire|3.3|[AD](http://www.analog.com/media/jp/technical-documentation/data-sheets/AD9851_JP.pdf)|
|FT5206|Capacitive Touch Panel Controller|FocalTech|I2C|3.3|[Other](https://www.buydisplay.com/download/ic/FT5206.pdf)|
|R61505V/W|TFT Display Controller Driver|Renesas SP|BUS-8/BUS-16/SPI|[Other](https://datasheetspdf.com/pdf-down/R/6/1/R61505-Renesas.pdf)|
|FAMIPAD|Family Computer Joy-Pad P/S Conversion (C-MOS Logic IC 4021)|Nintendo|serial(P/S, CLK, OUT)|3.0 to 5.5|-|
|MAX6675|冷接点補償K熱電対デジタルコンバータ(0℃～+1024℃)|Maxim Integrated|SPI|3.0 to 5.5|[MAXIM](https://www.maximintegrated.com/jp/products/sensors/MAX6675.html)| 
|ISL29034|Integrated Digital Light Sensor|Renesas (intersil)|I2C|2.25 to 3.63|[Renesas](https://www.renesas.com/jp/ja/products/sensors/ambient-light-sensors/light-to-digital-sensors/device/ISL29034.html)|
|OBD2|On Board Diagnosis second generation|SAE|CAN|3.3 to 5.0|[Wikipedia](https://en.wikipedia.org/wiki/OBD-II_PIDs)|
|AS5600|12-bit Programmable Contactless Potentiometer|ams|I2C|3.3V or 5.0V|[ams](https://ams.com/ja/as5600)|

---

## デバイス・テンプレート・クラスの特徴

- デバイスクラスは、C++ テンプレート活用したクラスで、通常ヘッダーをインクルードするだけで使えるように設計されています。
- 物理的な定義（どのピンを使うか、どのインターフェースを使うかなど）を極限まで排除して、純粋に IC の仕様を網羅した制御コードのみ実装されています。
- その為、非常に汎用性が高く、色々な異なったマイコンに最小限の定義で適合します。
- 例えば、RX マイコンの場合、I2C は、IICA、SCI-I2C、ソフト I2C、など色々なインターフェースが考えられますが、同じように扱えます。
- オーサリングツールに頼って、別プログラムで設定を生成したりする事が必要ありません。（生成したコードと自分のコードをマージする必要性が無い）
- コードは読みやすく、間違いが少なく、保守が簡単になるように工夫しています。

I2C 接続、タッチパネルコントローラー FT5206 の例：

```C++
#include "common/sci_i2c_io.hpp"
#include "chip/FT5206.hpp"

	//SCI-I2C で利用する FIFO バッファの定義
	typedef utils::fixed_fifo<uint8_t, 64> RB64;  // 受信バッファ
	typedef utils::fixed_fifo<uint8_t, 64> SB64;  // 送信バッファ

	// Ft5206 の RESET 信号の型
	typedef device::PORT<device::PORT6, device::bitpos::B6> FT5206_RESET;
	// SCI-I2C インターフェースの型（SCI6、３番目候補のポートを利用）
	typedef device::sci_i2c_io<device::SCI6, RB64, SB64, device::port_map::ORDER::THIRD_I2C> FT5206_I2C;


	// SCI-I2C インターフェースの定義（実態）
	FT5206_I2C	ft5206_i2c_;
	// FT5206 チップの型
	typedef chip::FT5206<FT5206_I2C> TOUCH;
	// FT5206 チップの定義（実態）
	TOUCH	touch_;


	{  // FT5206 の初期化
		TOUCH::reset<FT5206_RESET>();  // FT5206 のリセット
		uint8_t intr_lvl = 1;
		// I2C マスター、標準速度で初期化
		if(!ft5206_i2c_.start(FT5206_I2C::MODE::MASTER, FT5206_I2C::SPEED::STANDARD, intr_lvl)) {
			utils::format("FT5206 I2C Start Fail...\n");
		}
		// FT5206 を開始
		if(!touch_.start()) {
			utils::format("FT5206 Start Fail...\n");
		}
	}


	// メインループ
	while(1) {
		touch_.update();


		auto tnum = touch_.get_touch_num();  // タッチ数の取得
		if(tnum > 0) {
			const auto& t = touch_.get_touch_pos(0);  // タッチ位置の取得
		}
	}
```


## I2C インターフェース・クラスに要求される機能

---

## SPI インターフェース・クラスに要求される機能

---

## CAN インターフェース・クラスに要求される機能

---

License
----

MIT
