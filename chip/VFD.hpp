#pragma once
//=====================================================================//
/*!	@file
	@brief	VFD (Variable Frequency Drive) class @n
			中国製インバーター、RS-485 通信制御 @n
			8 bits No-Parity 1 Stop bit, 9600 baud
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/R8C/blob/master/LICENSE
*/
//=====================================================================//
#include "common/delay.hpp"

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  VFD テンプレートクラス
		@param[in]	SCI	sci クラス
		@param[in]	SEL	デバイス・セレクト
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SCI, class SEL>
	class VFD {

		VFD&	vfd_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクタ
			@param[in]	sci	SCI インターフェース・クラス
		 */
		//-----------------------------------------------------------------//
		VFD(SCI& sci) noexcept : sci_(sci) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
		 */
		//-----------------------------------------------------------------//
		void start() noexcept
		{
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	速度設定
			@param[in]	spd	速度
		 */
		//-----------------------------------------------------------------//
		void set_speed(uint32_t spd) noexcept
		{
		}
	};
}

#if 0
// RS485 connections
// D8 = DI (TX)
// D9 = DE
// D10 = RE
// D11 = RO (RX)
 
// adjust speed
String     speed=":010203030BB837\r\n";
  
char* read_speed=":01040300";
char* change_speed=":010203030BB8";
char* stop=":01030108";
char* start=":01030101";
 
 
SoftwareSerial myserial(11,8); // RX, TX
 
void setup() {
 Serial.begin(9600);
 pinMode(9,OUTPUT);
 pinMode(10,OUTPUT);
 myserial.begin(9600);
 digitalWrite(9,LOW); digitalWrite(9,LOW);
}
 
void setSpeed(int v) {
    Serial.print("Set new speed "); Serial.println(v,DEC);
    char* n=change_speed;
  //char n[13];
  //strcpy(n,change_speed);
  n[9]=toHexa((v/256)>>4);
  n[10]=toHexa((v/256)&0xf);
  n[11]=toHexa((v&0xff)>>4);
  n[12]=toHexa((v&0xff)&0xf);
Serial.println(n);
  query(n); // set new speed
}
 
void loop() {
 // while(myserial.available()) Serial.write(myserial.read());
  delay(1000);
 
  query(start);
  delay(10000);
 
  //delay(5000);
  for(long v=1000; v<16000; v+=1000) {setSpeed(v); delay(5000); }
 
  query(stop);
  delay(10000);
}
 
void transmit(String msg) {
  // activate driver
  digitalWrite(9,HIGH); digitalWrite(9,HIGH);
  delay(50);
  myserial.print(msg);
  delay(1);
  digitalWrite(9,LOW); digitalWrite(9,LOW);
}
 
char hexa(char byte) { // return hexa value of that ASCII char
  if(byte<='9') return byte & 0x0f;
  if(byte<='F') return (byte & 0x0f) + 9; // A=0x41 --> 0x0a
}
 
char toHexa(int i) {
 if(i<10) return 0x30 | i;
 return 0x41 + i - 10;
}
 
char crc(char* buffer) {
 int l=strlen(buffer);
 int i=1;
 int chk=0;
 while(i<l) { Serial.print(hexa(buffer[i])<<4|hexa(buffer[i+1]),HEX); chk+= ( hexa(buffer[i])<<4|hexa(buffer[i+1]) ); i+=2; Serial.print(" ");}
 Serial.print(":"); Serial.println(chk,HEX);
  Serial.println(0x100-chk,HEX);
 return (0x100-chk) & 0xff;
}
 
void query(char* cmd) {
  char lrc = crc(cmd);
  String msg = cmd;
  msg+=toHexa((lrc&0xf0)>>4);
  msg+=toHexa(lrc&0x0f);
  msg+="\r\n";
  Serial.print(msg);
  transmit(msg);
}
#endif
