各種デバイスドライバー
=========

[English](README.md)

## 概要
I2C、SPI、BUS、等のインターフェースで通信を行うデバイス制御クラス
   
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
   
---

## I2C インターフェース・クラスに要求される機能

---

## SPI インターフェース・クラスに要求される機能

---

License
----

MIT
