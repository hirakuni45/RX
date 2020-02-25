各種デバイスドライバー
=========

[English](README.md)

## 概要
I2C、SPI、BUS、等のインターフェースで通信を行うデバイス制御クラス
   
## デバイス・リスト
 - BMP180   
BOSCH   
digital barometric pressure sensor   
<http://akizukidenshi.com/catalog/g/gI-06585/>   
Interface: I2C   
   
 - BMP280   
BOSCH   
digital barometric pressure sensor   
<http://akizukidenshi.com/catalog/g/gI-06585/>   
Interface: I2C   
   
 - DS1371   
Maxim Integrated   
内部バイナリー、I²Cリアルタイムクロック(RTC)    
<https://www.maximintegrated.com/jp/products/digital/real-time-clocks/DS1371.html>   
Interface: I2C   
   
 - DS3231   
Maxim Integrated   
超高精度I²Cリアルタイムクロック(RTC)    
超高精度I²C内蔵RTC/TCXO/水晶    
<https://www.maximintegrated.com/jp/products/digital/real-time-clocks/DS3231.html>   
Interface: I2C   
   
 - EEPROM   
各社   
I2C EEPROM   
I2C EEPROM（１byte、２byte address）   
Interface: I2C   
   
 - EUI_XX   
Microchip   
2K SPI Bus Serial EEPROMs with EUI-48 or EUI-64 Node Identity   
25AA02E48/25AA02E64   
Interface: SPI   
   
 - LTC2348_16   
LINEAR TECHNOLOGY   
Octal, 16-Bit, 200ksps Differential +-10.24V Input SoftSpan ADC   
Interface: wide SPI   
   
 - MAX7219   
Maxim Integrated   
SPI, 8 Digits LED Driver   
Interface: SPI   
   
 - MPU6050   
InvenSense   
Digital Motion Processor   
<https://www.invensense.com/products/motion-tracking/6-axis/mpu-6050/>   
Interface: I2C   
   
 - NTCTH   
muRata   
NTC サーミスタ   
Interface: Analog   
   
 - SH1106   
SINO WEALTH   
132x64 Dot Matrix OLED/PLED Segment/Common Driver with Controller   
<http://www.rhydolabz.com/documents/sh1106_datasheet.pdf>   
Interface: SPI   
   
 - SSD1306   
SOLOMON SYSTECH   
128 x 64 Dot Matrix OLED/PLED Segment/Common Driver with Controller   
Interface: SPI   
   
 - ST7565：（ST7565R）、（ST7567）   
Sitronix   
65 x 132 Dot Matrix LCD Controller/Driver   
RAM capacity : 65 x 132 = 8580 bits   
<http://www.hpinfotech.ro/ST7565.pdf>   
<http://www.aitendo.com/product/13327>   
<http://www.aitendo.com/product/12866>   
Interface: SPI   
   
 - UC1701   
ULTRA CHIP   
Single-Chip, Ultra-Low Power 65COM by 132SEG Passive Matrix LCD Controller-Driver   
<http://www.hpinfotech.ro/UC1701.pdf>   
Interface: SPI   
   
 - VS1063   
VLSI Solution   
MP3 / OGG VORBIS ENCODER AND AUDIO CODEC   
<http://www.vlsi.fi/fileadmin/datasheets/vs1063ds.pdf>   
Interface: SPI   
   
 - phy_base   
Ethernet default PHY device   
LAN8720(A) 10/100M (Microchip)   
DP83822 10/100M (Texas Instruments) for option   
KSZ8041NL 10/100M (MICREL) for option   
Interface: PHY   
   
 - VL53L0X   
STMicroelectronics   
World smallest Time-of-Flight (ToF) ranging sensor   
<http://www.st.com/ja/imaging-and-photonics-solutions/vl53l0x.html>   
Interface: I2C   
   
 - AD9833   
ANALOG DEVICES   
Programmable Waveform Generator   
<http://www.analog.com/media/jp/technical-documentation/data-sheets/AD9833_JP.pdf>   
Interface: SPI   

 - AD985X (AD9850, AD9851)   
ANALOG DEVICES   
Programmable Waveform Generator   
<http://www.analog.com/media/jp/technical-documentation/data-sheets/AD9851_JP.pdf>   
Interface: 3 Wire Serial (W_CLK, D7, UD)   
   
 - FT5206
FocalTech   
Capacitive Touch Panel Controller   
<https://www.buydisplay.com/download/ic/FT5206.pdf>   
Interface: I2C   
   
 - VFD
?
Variable Frequency Drive
?
Interface: RS-485 (8 Bits 1 Stop No-Parity, 9600 Baud)
   
 - R61505V/W
Renesas SP
TFT Display Controller Driver (262,144-color, 240RGB x 320-dot)
<https://datasheetspdf.com/pdf-down/R/6/1/R61505-Renesas.pdf>
Interface: BUS-8(/CS,/RD,/WR), BUS-16(/CS,/RD,/WR),SPI(/CS,MOSI,MISO,CLK)

 - FAMIPAD
Nintendo
Family Computer Joy-Pad P/S Conversion
Interface: 8 bits serial(P/S, CLK, OUT)

 - MAX6675
Maxim Integrated   
冷接点補償K熱電対デジタルコンバータ(0℃～+1024℃)   
https://www.maximintegrated.com/jp/products/sensors/MAX6675.html   
Interface: SPI (/CS, SCK, SO)   

-----
   
License
----

MIT
