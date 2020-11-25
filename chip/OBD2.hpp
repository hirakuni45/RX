#pragma once
//=====================================================================//
/*!	@file
	@brief	OBD2 (On Board Diagnosis second generation) クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  OBD2 定義クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class OBD2_def {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief PID (Parameter Identification Data) コマンド
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class PID : uint8_t {
			ENGINE_LOAD  = 0x04,
			COOLANT_TEMP = 0x05,
			SHORT_TERM_FUEL_TRIM_1 = 0x06,
			LONG_TERM_FUEL_TRIM_1  = 0x07,
			SHORT_TERM_FUEL_TRIM_2 = 0x08,
			LONG_TERM_FUEL_TRIM_2  = 0x09,
			FUEL_PRESSURE = 0x0A,
			INTAKE_MAP = 0x0B,
			RPM = 0x0C,
			SPEED = 0x0D,
			TIMING_ADVANCE = 0x0E,
			INTAKE_TEMP = 0x0F,
			MAF_FLOW = 0x10,
			THROTTLE = 0x11,
			AUX_INPUT = 0x1E,
			RUNTIME = 0x1F,
			DISTANCE_WITH_MIL = 0x21,
			COMMANDED_EGR = 0x2C,
			EGR_ERROR = 0x2D,
			COMMANDED_EVAPORATIVE_PURGE = 0x2E,
			FUEL_LEVEL = 0x2F,
			WARMS_UPS = 0x30,
			DISTANCE = 0x31,
			EVAP_SYS_VAPOR_PRESSURE = 0x32,
			BAROMETRIC = 0x33,
			CATALYST_TEMP_B1S1 = 0x3C,
			CATALYST_TEMP_B2S1 = 0x3D,
			CATALYST_TEMP_B1S2 = 0x3E,
			CATALYST_TEMP_B2S2 = 0x3F,
			CONTROL_MODULE_VOLTAGE = 0x42,
			ABSOLUTE_ENGINE_LOAD = 0x43,
			AIR_FUEL_EQUIV_RATIO = 0x44,
			RELATIVE_THROTTLE_POS = 0x45,
			AMBIENT_TEMP = 0x46,
			ABSOLUTE_THROTTLE_POS_B = 0x47,
			ABSOLUTE_THROTTLE_POS_C = 0x48,
			ACC_PEDAL_POS_D = 0x49,
			ACC_PEDAL_POS_E = 0x4A,
			ACC_PEDAL_POS_F = 0x4B,
			COMMANDED_THROTTLE_ACTUATOR = 0x4C,
			TIME_WITH_MIL = 0x4D,
			TIME_SINCE_CODES_CLEARED = 0x4E,
			ETHANOL_FUEL = 0x52,
			FUEL_RAIL_PRESSURE = 0x59,
			HYBRID_BATTERY_PERCENTAGE = 0x5B,
			ENGINE_OIL_TEMP = 0x5C,
			FUEL_INJECTION_TIMING = 0x5D,
			ENGINE_FUEL_RATE = 0x5E,
			ENGINE_TORQUE_DEMANDED = 0x61,
			ENGINE_TORQUE_PERCENTAGE = 0x62,
			ENGINE_REF_TORQUE = 0x63,

// non-OBD/custom PIDs (no mode number)
			GPS_LATITUDE = 0xA,
			GPS_LONGITUDE = 0xB,
			GPS_ALTITUDE = 0xC,
			GPS_SPEED = 0xD,
			GPS_HEADING = 0xE,
			GPS_SAT_COUNT = 0xF,
			GPS_TIME = 0x10,
			GPS_DATE = 0x11,
			ACC = 0x20,
			GYRO = 0x21,
			COMPASS = 0x22,
			MEMS_TEMP = 0x23,
			BATTERY_VOLTAGE = 0x24,

// custom PIDs for calculated data
			TRIP_DISTANCE = 0x30,
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  OBD2 テンプレートクラス
		@param[in]	CAN_IO	can_io クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class CAN_IO>
	class OBD2 : public OBD2_def {

		CAN_IO&	can_io_;

		uint16_t hex2uint16_(const char* p) {
			char c = *p;
			uint16_t i = 0;
			for (char n = 0; c && n < 4; c = *(++p)) {
				if (c >= 'A' && c <= 'F') {
					c -= 7;
				} else if (c>='a' && c<='f') {
					c -= 39;
				} else if (c == ' ') {
					continue;
				} else if (c < '0' || c > '9') {
					break;
				}
				i = (i << 4) | (c & 0xF);
				n++;
			}
			return i;
		}

		uint8_t hex2uint8_(const char* p) {
			uint8_t c1 = *p;
			uint8_t c2 = *(p + 1);
			if (c1 >= 'A' && c1 <= 'F')
				c1 -= 7;
			else if (c1 >='a' && c1 <= 'f')
	    		c1 -= 39;
			else if (c1 < '0' || c1 > '9')
				return 0;

			if (c2 >= 'A' && c2 <= 'F')
				c2 -= 7;
			else if (c2 >= 'a' && c2 <= 'f')
	    		c2 -= 39;
			else if (c2 < '0' || c2 > '9')
				return 0;

			return c1 << 4 | (c2 & 0xf);
		}


		uint8_t getPercentageValue(const char* data)
		{
			return (uint16_t)hex2uint8_(data) * 100 / 255;
		}


		uint16_t getLargeValue(const char* data)
		{
			return hex2uint16_(data);
		}


		uint8_t getSmallValue(const char* data)
		{
			return hex2uint8_(data);
		}


		int16_t getTemperatureValue(const char* data)
		{
			return (int)hex2uint8_(data) - 40;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	can_io	can_io クラスを参照で渡す
		 */
		//-----------------------------------------------------------------//
		OBD2(CAN_IO& can_io) noexcept : can_io_(can_io)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	PID に対するデータ変換
			@param[in]	
		 */
		//-----------------------------------------------------------------//
		int normalize(PID pid, const char* data) noexcept
		{
			int result;
			switch (pid) {
			case PID::RPM:
			case PID::EVAP_SYS_VAPOR_PRESSURE: // kPa
				result = getLargeValue(data) >> 2;
				break;
			case PID::FUEL_PRESSURE: // kPa
				result = getSmallValue(data) * 3;
				break;
			case PID::COOLANT_TEMP:
			case PID::INTAKE_TEMP:
			case PID::AMBIENT_TEMP:
			case PID::ENGINE_OIL_TEMP:
				result = getTemperatureValue(data);
				break;
			case PID::THROTTLE:
			case PID::COMMANDED_EGR:
			case PID::COMMANDED_EVAPORATIVE_PURGE:
			case PID::FUEL_LEVEL:
			case PID::RELATIVE_THROTTLE_POS:
			case PID::ABSOLUTE_THROTTLE_POS_B:
			case PID::ABSOLUTE_THROTTLE_POS_C:
			case PID::ACC_PEDAL_POS_D:
			case PID::ACC_PEDAL_POS_E:
			case PID::ACC_PEDAL_POS_F:
			case PID::COMMANDED_THROTTLE_ACTUATOR:
			case PID::ENGINE_LOAD:
			case PID::ABSOLUTE_ENGINE_LOAD:
			case PID::ETHANOL_FUEL:
			case PID::HYBRID_BATTERY_PERCENTAGE:
				result = getPercentageValue(data);
				break;
			case PID::MAF_FLOW: // grams/sec
				result = getLargeValue(data) / 100;
				break;
			case PID::TIMING_ADVANCE:
				result = (int)(getSmallValue(data) / 2) - 64;
				break;
			case PID::DISTANCE: // km
			case PID::DISTANCE_WITH_MIL: // km
			case PID::TIME_WITH_MIL: // minute
			case PID::TIME_SINCE_CODES_CLEARED: // minute
			case PID::RUNTIME: // second
			case PID::FUEL_RAIL_PRESSURE: // kPa
			case PID::ENGINE_REF_TORQUE: // Nm
				result = getLargeValue(data);
				break;
			case PID::CONTROL_MODULE_VOLTAGE: // V
				result = getLargeValue(data) / 1000;
				break;
			case PID::ENGINE_FUEL_RATE: // L/h
				result = getLargeValue(data) / 20;
				break;
			case PID::ENGINE_TORQUE_DEMANDED: // %
			case PID::ENGINE_TORQUE_PERCENTAGE: // %
				result = (int)getSmallValue(data) - 125;
				break;
			case PID::SHORT_TERM_FUEL_TRIM_1:
			case PID::LONG_TERM_FUEL_TRIM_1:
			case PID::SHORT_TERM_FUEL_TRIM_2:
			case PID::LONG_TERM_FUEL_TRIM_2:
			case PID::EGR_ERROR:
				result = ((int)getSmallValue(data) - 128) * 100 / 128;
				break;
			case PID::FUEL_INJECTION_TIMING:
				result = ((int32_t)getLargeValue(data) - 26880) / 128;
				break;
			case PID::CATALYST_TEMP_B1S1:
			case PID::CATALYST_TEMP_B2S1:
			case PID::CATALYST_TEMP_B1S2:
			case PID::CATALYST_TEMP_B2S2:
				result = getLargeValue(data) / 10 - 40;
				break;
			case PID::AIR_FUEL_EQUIV_RATIO: // 0~200
				result = (long)getLargeValue(data) * 200 / 65536;
				break;
			default:
				result = getSmallValue(data);
			}
			return result;
		}
	};
}

#if 0
/*************************************************************************
* Arduino Library for OBD-II UART/I2C Adapter
* Distributed under BSD License
* Visit http://freematics.com for more information
* (C)2012-2016 Stanley Huang <stanleyhuangyc@gmail.com>
*************************************************************************/

#include <Arduino.h>

#define OBD_MODEL_UART 0
#define OBD_MODEL_I2C 1

#define OBD_TIMEOUT_SHORT 1000 /* ms */
#define OBD_TIMEOUT_LONG 5000 /* ms */
#define OBD_TIMEOUT_GPS 200 /* ms */

#ifndef OBDUART
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168P__)
#define OBDUART Serial
#else
#define OBDUART Serial1
#endif
#endif


typedef enum {
    PROTO_AUTO = 0,
    PROTO_ISO_9141_2 = 3,
    PROTO_KWP2000_5KBPS = 4,
    PROTO_KWP2000_FAST = 5,
    PROTO_CAN_11B_500K = 6,
    PROTO_CAN_29B_500K = 7,
    PROTO_CAN_29B_250K = 8,
    PROTO_CAN_11B_250K = 9,
} OBD_PROTOCOLS;

// states
typedef enum {
    OBD_DISCONNECTED = 0,
    OBD_CONNECTING = 1,
    OBD_CONNECTED = 2,
	OBD_FAILED = 3
} OBD_STATES;

uint16_t hex2uint16(const char *p);
uint8_t hex2uint8(const char *p);

class COBD
{
public:
	COBD():dataMode(1),errors(0),m_state(OBD_DISCONNECTED) {}
	// begin serial UART, return the version number on success and 0 on failure
	virtual byte begin();
	// initialize OBD-II connection
	virtual bool init(OBD_PROTOCOLS protocol = PROTO_AUTO);
	// un-initialize OBD-II connection
	virtual void end();
	// set serial baud rate
	virtual bool setBaudRate(unsigned long baudrate);
	// get connection state
	virtual OBD_STATES getState() { return m_state; }
	// read specified OBD-II PID value
	virtual bool readPID(byte pid, int& result);
	// read multiple (up to 8) OBD-II PID values, return number of values obtained
	virtual byte readPID(const byte pid[], byte count, int result[]);
	// set device into low power mode
	virtual void enterLowPowerMode();
	// wake up device from low power mode
	virtual void leaveLowPowerMode();
	// send AT command and receive response
	virtual byte sendCommand(const char* cmd, char* buf, byte bufsize, int timeout = OBD_TIMEOUT_LONG);
	// read diagnostic trouble codes (return number of DTCs read)
	virtual byte readDTC(uint16_t codes[], byte maxCodes = 1);
	// clear diagnostic trouble code
	virtual void clearDTC();
	// get battery voltage (works without ECU)
	virtual float getVoltage();
	// get VIN as a string, buffer length should be >= OBD_RECV_BUF_SIZE
	virtual bool getVIN(char* buffer, byte bufsize);
	// initialize MEMS sensor
	virtual bool memsInit();
	// read out MEMS data (acc for accelerometer, gyr for gyroscope, temp in 0.1 celcius degree)
	virtual bool memsRead(int16_t* acc, int16_t* gyr = 0, int16_t* mag = 0, int16_t* temp = 0);
	// send query for specified PID
	virtual void sendQuery(byte pid);
	// retrive and parse the response of specifie PID
	virtual bool getResult(byte& pid, int& result);
	// determine if the PID is supported
	virtual bool isValidPID(byte pid);
	// get adapter firmware version
	virtual byte getVersion();
	// set current PID mode
	byte dataMode;
	// number of subsequent errors
	byte errors;
	// bit map of supported PIDs
	byte pidmap[4 * 4];
protected:
	virtual char* getResponse(byte& pid, char* buffer, byte bufsize);
	virtual byte receive(char* buffer, byte bufsize, int timeout = OBD_TIMEOUT_SHORT);
	virtual void write(const char* s);
	virtual void dataIdleLoop() {}
	void recover();
	void debugOutput(const char* s);
	int normalizeData(byte pid, char* data);
	OBD_STATES m_state;
private:
	virtual uint8_t getPercentageValue(char* data)
	{
		return (uint16_t)hex2uint8(data) * 100 / 255;
	}
	virtual uint16_t getLargeValue(char* data)
	{
		return hex2uint16(data);
	}
	virtual uint8_t getSmallValue(char* data)
	{
		return hex2uint8(data);
	}
	virtual int16_t getTemperatureValue(char* data)
	{
		return (int)hex2uint8(data) - 40;
	}
	char* getResultValue(char* buf);
};

#define I2C_ADDR 0x62

#define MAX_PAYLOAD_SIZE 32
#define MAX_PIDS 8

#define CMD_QUERY_STATUS 0x10
#define CMD_SEND_AT_COMMAND 0x11
#define CMD_APPLY_OBD_PIDS 0x12
#define CMD_LOAD_OBD_DATA 0x13
#define CMD_GPS_SETUP 0x14
#define CMD_GPS_QUERY 0x15

typedef struct {
    uint16_t age;
    uint16_t value;
} PID_INFO;

typedef struct {
    uint16_t time;
    uint8_t message;
    uint8_t data;
} COMMAND_BLOCK;

class COBDI2C : public COBD {
public:
	byte begin();
	void end();
	void write(const char* s);
	// API not applicable
	bool setBaudRate(unsigned long baudrate) { return false; }
	// Asynchronized access API
	void setQueryPID(byte pid, byte obdPid[]);
	void applyQueryPIDs(byte obdPid[]);
	void loadQueryData(PID_INFO obdInfo[]);
	// initialize MEMS sensor
	bool memsInit();
	// read out MEMS sensor data (acc for accelerometer, gyr for gyroscope, temp in 0.1 celcius degree)
	bool memsRead(int* acc, int* gyr = 0, int* mag = 0, int* temp = 0);
protected:
	byte receive(char* buffer, byte bufsize, int timeout = OBD_TIMEOUT_SHORT);
	bool sendCommandBlock(byte cmd, uint8_t data = 0, byte* payload = 0, byte payloadBytes = 0);
private:
	bool MPU6050_read(int start, uint8_t* buffer, int size);
	bool MPU6050_write(int start, const uint8_t* pData, int size);
	bool MPU6050_write_reg(int reg, uint8_t data);
	void MPU6050_store(int* pData, uint8_t data_l, uint8_t data_h);
};
#endif

#if 0
/*************************************************************************
* Arduino Library for OBD-II UART/I2C Adapter
* Distributed under BSD License
* Visit http://freematics.com for more information
* (C)2012-2016 Stanley Huang <stanleyhuangyc@gmail.com>
*************************************************************************/

#include <Arduino.h>
#include <Wire.h>
#include "OBD.h"

//#define DEBUG Serial


/*************************************************************************
* OBD-II UART Adapter
*************************************************************************/

byte COBD::sendCommand(const char* cmd, char* buf, byte bufsize, int timeout)
{
	write(cmd);
	dataIdleLoop();
	return receive(buf, bufsize, timeout);
}

void COBD::sendQuery(byte pid)
{
	char cmd[8];
	sprintf(cmd, "%02X%02X\r", dataMode, pid);
#ifdef DEBUG
	debugOutput(cmd);
#endif
	write(cmd);
}

bool COBD::readPID(byte pid, int& result)
{
	// send a query command
	sendQuery(pid);
	// receive and parse the response
	return getResult(pid, result);
}

byte COBD::readPID(const byte pid[], byte count, int result[])
{
	byte results = 0; 
	for (byte n = 0; n < count; n++) {
		if (readPID(pid[n], result[n])) {
			results++;
		}
	}
	return results;
}

byte COBD::readDTC(uint16_t codes[], byte maxCodes)
{
	/*
	Response example:
	0: 43 04 01 08 01 09 
	1: 01 11 01 15 00 00 00
	*/ 
	byte codesRead = 0;
 	for (byte n = 0; n < 6; n++) {
		char buffer[128];
		sprintf_P(buffer, n == 0 ? PSTR("03\r") : PSTR("03%02X\r"), n);
		write(buffer);
		if (receive(buffer, sizeof(buffer)) > 0) {
			if (!strstr(buffer, "NO DATA")) {
				char *p = strstr(buffer, "43");
				if (p) {
					while (codesRead < maxCodes && *p) {
						p += 6;
						if (*p == '\r') {
							p = strchr(p, ':');
							if (!p) break;
							p += 2; 
						}
						uint16_t code = hex2uint16(p);
						if (code == 0) break;
						codes[codesRead++] = code;
					}
				}
				break;
			}
		}
	}
	return codesRead;
}

void COBD::clearDTC()
{
	char buffer[32];
	write("04\r");
	receive(buffer, sizeof(buffer));
}

void COBD::write(const char* s)
{
#ifdef DEBUG
	DEBUG.print("<<<");
	DEBUG.println(s);
#endif
	OBDUART.write(s);
}

int COBD::normalizeData(byte pid, char* data)
{
	int result;
	switch (pid) {
	case PID_RPM:
	case PID_EVAP_SYS_VAPOR_PRESSURE: // kPa
		result = getLargeValue(data) >> 2;
		break;
	case PID_FUEL_PRESSURE: // kPa
		result = getSmallValue(data) * 3;
		break;
	case PID_COOLANT_TEMP:
	case PID_INTAKE_TEMP:
	case PID_AMBIENT_TEMP:
	case PID_ENGINE_OIL_TEMP:
		result = getTemperatureValue(data);
		break;
	case PID_THROTTLE:
	case PID_COMMANDED_EGR:
	case PID_COMMANDED_EVAPORATIVE_PURGE:
	case PID_FUEL_LEVEL:
	case PID_RELATIVE_THROTTLE_POS:
	case PID_ABSOLUTE_THROTTLE_POS_B:
	case PID_ABSOLUTE_THROTTLE_POS_C:
	case PID_ACC_PEDAL_POS_D:
	case PID_ACC_PEDAL_POS_E:
	case PID_ACC_PEDAL_POS_F:
	case PID_COMMANDED_THROTTLE_ACTUATOR:
	case PID_ENGINE_LOAD:
	case PID_ABSOLUTE_ENGINE_LOAD:
	case PID_ETHANOL_FUEL:
	case PID_HYBRID_BATTERY_PERCENTAGE:
		result = getPercentageValue(data);
		break;
	case PID_MAF_FLOW: // grams/sec
		result = getLargeValue(data) / 100;
		break;
	case PID_TIMING_ADVANCE:
		result = (int)(getSmallValue(data) / 2) - 64;
		break;
	case PID_DISTANCE: // km
	case PID_DISTANCE_WITH_MIL: // km
	case PID_TIME_WITH_MIL: // minute
	case PID_TIME_SINCE_CODES_CLEARED: // minute
	case PID_RUNTIME: // second
	case PID_FUEL_RAIL_PRESSURE: // kPa
	case PID_ENGINE_REF_TORQUE: // Nm
		result = getLargeValue(data);
		break;
	case PID_CONTROL_MODULE_VOLTAGE: // V
		result = getLargeValue(data) / 1000;
		break;
	case PID_ENGINE_FUEL_RATE: // L/h
		result = getLargeValue(data) / 20;
		break;
	case PID_ENGINE_TORQUE_DEMANDED: // %
	case PID_ENGINE_TORQUE_PERCENTAGE: // %
		result = (int)getSmallValue(data) - 125;
		break;
	case PID_SHORT_TERM_FUEL_TRIM_1:
	case PID_LONG_TERM_FUEL_TRIM_1:
	case PID_SHORT_TERM_FUEL_TRIM_2:
	case PID_LONG_TERM_FUEL_TRIM_2:
	case PID_EGR_ERROR:
		result = ((int)getSmallValue(data) - 128) * 100 / 128;
		break;
	case PID_FUEL_INJECTION_TIMING:
		result = ((int32_t)getLargeValue(data) - 26880) / 128;
		break;
	case PID_CATALYST_TEMP_B1S1:
	case PID_CATALYST_TEMP_B2S1:
	case PID_CATALYST_TEMP_B1S2:
	case PID_CATALYST_TEMP_B2S2:
		result = getLargeValue(data) / 10 - 40;
		break;
	case PID_AIR_FUEL_EQUIV_RATIO: // 0~200
		result = (long)getLargeValue(data) * 200 / 65536;
		break;
	default:
		result = getSmallValue(data);
	}
	return result;
}

char* COBD::getResponse(byte& pid, char* buffer, byte bufsize)
{
	while (receive(buffer, bufsize) > 0) {
		char *p = buffer;
		while ((p = strstr(p, "41 "))) {
		    p += 3;
		    byte curpid = hex2uint8(p);
		    if (pid == 0) pid = curpid;
		    if (curpid == pid) {
		        errors = 0;
		        p += 2;
		        if (*p == ' ')
		            return p + 1;
		    }
		}
	}
	return 0;
}

bool COBD::getResult(byte& pid, int& result)
{
	char buffer[64];
	char* data = getResponse(pid, buffer, sizeof(buffer));
	if (!data) {
		recover();
		errors++;
		return false;
	}
	result = normalizeData(pid, data);
	return true;
}

void COBD::enterLowPowerMode()
{
  	char buf[32];
	sendCommand("ATLP\r", buf, sizeof(buf));
}

void COBD::leaveLowPowerMode()
{
	// simply send any command to wake the device up
	char buf[32];
	sendCommand("ATI\r", buf, sizeof(buf), 1000);
}

char* COBD::getResultValue(char* buf)
{
	char* p = buf;
	for (;;) {
		if (isdigit(*p) || *p == '-') {
			return p;
		}
		p = strchr(p, '\r');
		if (!p) break;
		if (*(++p) == '\n') p++;
	}
	return 0;
}

float COBD::getVoltage()
{
    char buf[32];
	if (sendCommand("ATRV\r", buf, sizeof(buf)) > 0) {
		char* p = getResultValue(buf);
		if (p) return (float)atof(p);
    }
    return 0;
}

bool COBD::getVIN(char* buffer, byte bufsize)
{
	for (byte n = 0; n < 5; n++) {
		if (sendCommand("0902\r", buffer, bufsize)) {
			int len = hex2uint16(buffer);
			char *p = strstr_P(buffer + 4, PSTR("0: 49 02 01"));
			if (p) {
				char *q = buffer;
				p += 11; // skip the header
				do {
					while (*(++p) == ' ');
					for (;;) {
						*(q++) = hex2uint8(p);
						while (*p && *p != ' ') p++;
						while (*p == ' ') p++;
						if (!*p || *p == '\r') break;
					}
					p = strchr(p, ':');
				} while(p);
				*q = 0;
				if (q - buffer == len - 3) {
					return true;
				}
			}
		}
		delay(100);
	}
    return false;
}

bool COBD::isValidPID(byte pid)
{
	if (pid >= 0x7f)
		return true;
	pid--;
	byte i = pid >> 3;
	byte b = 0x80 >> (pid & 0x7);
	return (pidmap[i] & b) != 0;
}

byte COBD::begin()
{
	long baudrates[] = {115200, 38400};
	byte version = 0;
	for (byte n = 0; n < sizeof(baudrates) / sizeof(baudrates[0]) && version == 0; n++) {
		OBDUART.begin(baudrates[n]);
		version = getVersion(); 
	}
	return version;	
}

byte COBD::getVersion()
{
	byte version = 0;
	for (byte n = 0; n < 3; n++) {
		char buffer[32];
		if (sendCommand("ATI\r", buffer, sizeof(buffer), 200)) {
			char *p = strchr(buffer, ' ');
			if (p) {
				p += 2;
				version = (*p - '0') * 10 + (*(p + 2) - '0');
				break;
			}
		}
	}
	return version;
}

byte COBD::receive(char* buffer, byte bufsize, int timeout)
{
	unsigned char n = 0;
	unsigned long startTime = millis();
	char c = 0;
	for (;;) {
		if (OBDUART.available()) {
			c = OBDUART.read();
			if (!buffer) {
			       n++;
			} else if (n < bufsize - 1) {
				if (c == '.' && n > 2 && buffer[n - 1] == '.' && buffer[n - 2] == '.') {
					// waiting siginal
					n = 0;
					timeout = OBD_TIMEOUT_LONG;
				} else {
					if (c == '\r' || c == '\n' || c == ' ') {
						if (n == 0 || buffer[n - 1] == '\r' || buffer[n - 1] == '\n') continue;
					}
					buffer[n++] = c;
				}
			}
		} else {
			if (c == '>') {
				// prompt char received
				break;
			}
			if ((int)(millis() - startTime) > timeout) {
			    // timeout
			    break;
			}
			dataIdleLoop();
		}
	}
	if (buffer) {
		buffer[n] = 0;
	}
#ifdef DEBUG
	DEBUG.print(">>>");
	DEBUG.println(buffer);
#endif
	return n;
}

void COBD::recover()
{
	sendCommand("\r", 0, 0);
}

bool COBD::init(OBD_PROTOCOLS protocol)
{
	const char *initcmd[] = {"ATZ\r", "ATE0\r", "ATH0\r"};
	char buffer[64];

	m_state = OBD_DISCONNECTED;
	for (unsigned char i = 0; i < sizeof(initcmd) / sizeof(initcmd[0]); i++) {
		write(initcmd[i]);
		if (receive(buffer, sizeof(buffer), OBD_TIMEOUT_LONG) == 0) {
			return false;
		}
	}
	if (protocol != PROTO_AUTO) {
		sprintf_P(buffer, PSTR("ATSP %u\r"), protocol);
		write(buffer);
		if (receive(buffer, sizeof(buffer), OBD_TIMEOUT_LONG) == 0 && !strstr(buffer, "OK")) {
			return false;
		}
	}

	// load pid map
	memset(pidmap, 0, sizeof(pidmap));
	bool success = false;
	for (byte i = 0; i < 4; i++) {
		byte pid = i * 0x20;
		sendQuery(pid);
		if (receive(buffer, sizeof(buffer), OBD_TIMEOUT_LONG) > 0) {
			char *p = buffer;
			while ((p = strstr(p, "41 "))) {
				p += 3;
				if (hex2uint8(p) == pid) {
					p += 2;
					for (byte n = 0; n < 4 && *(p + n * 3) == ' '; n++) {
						pidmap[i * 4 + n] = hex2uint8(p + n * 3 + 1);
					}
					success = true;
				}
			}
		}
	}

	if (success) {
		m_state = OBD_CONNECTED;
		errors = 0;
	}
	return success;
}

void COBD::end()
{
	m_state = OBD_DISCONNECTED;
	OBDUART.end();
}

bool COBD::setBaudRate(unsigned long baudrate)
{
    OBDUART.print("ATBR1 ");
    OBDUART.print(baudrate);
    OBDUART.print('\r');
    delay(50);
    OBDUART.end();
    OBDUART.begin(baudrate);
    recover();
    return true;
}

bool COBD::memsInit()
{
	char buf[16];
	return sendCommand("ATTEMP\r", buf, sizeof(buf)) > 0 && !strchr(buf, '?');
}

bool COBD::memsRead(int16_t* acc, int16_t* gyr, int16_t* mag, int16_t* temp)
{
	char buf[64];
	bool success;
	if (acc) {
		success = false;
		if (sendCommand("ATACL\r", buf, sizeof(buf)) > 0) do {
			char* p = getResultValue(buf);
			if (!p) break;
			acc[0] = atoi(p++);
			if (!(p = strchr(p, ','))) break;
			acc[1] = atoi(++p);
			if (!(p = strchr(p, ','))) break;
			acc[2] = atoi(++p);
			success = true;
		} while (0);
		if (!success) return false;
	}
	if (gyr) {
		success = false;
		if (sendCommand("ATGYRO\r", buf, sizeof(buf)) > 0) do {
			char* p = getResultValue(buf);
			if (!p) break;
			gyr[0] = atoi(p++);
			if (!(p = strchr(p, ','))) break;
			gyr[1] = atoi(++p);
			if (!(p = strchr(p, ','))) break;
			gyr[2] = atoi(++p);
			success = true;
		} while (0);
		if (!success) return false;
	}
	if (temp) {
		success = false;
		if (sendCommand("ATTEMP\r", buf, sizeof(buf)) > 0) {
			char* p = getResultValue(buf);
			if (p) {
				*temp = (atoi(p) + 12412) / 34;
				success = true;
			}
		}
		if (!success) return false;
	}
	return true;	
}

#ifdef DEBUG
void COBD::debugOutput(const char *s)
{
	DEBUG.print('[');
	DEBUG.print(millis());
	DEBUG.print(']');
	DEBUG.print(s);
}
#endif

/*************************************************************************
* OBD-II I2C Adapter
*************************************************************************/

byte COBDI2C::begin()
{
	Wire.begin();
#ifdef DEBUG
	DEBUG.begin(115200);
#endif
	recover();
	return getVersion();
}

void COBDI2C::end()
{
	m_state = OBD_DISCONNECTED;
}

void COBDI2C::write(const char* s)
{
	COMMAND_BLOCK cmdblock = {millis(), CMD_SEND_AT_COMMAND};
	Wire.beginTransmission(I2C_ADDR);
	Wire.write((byte*)&cmdblock, sizeof(cmdblock));
	Wire.write(s);
	Wire.endTransmission();
}

bool COBDI2C::sendCommandBlock(byte cmd, uint8_t data, byte* payload, byte payloadBytes)
{
	COMMAND_BLOCK cmdblock = {millis(), cmd, data};
	Wire.beginTransmission(I2C_ADDR);
	bool success = Wire.write((byte*)&cmdblock, sizeof(COMMAND_BLOCK)) == sizeof(COMMAND_BLOCK);
	if (payload) Wire.write(payload, payloadBytes);
	Wire.endTransmission();
	return success;
}

byte COBDI2C::receive(char* buffer, byte bufsize, int timeout)
{
	uint32_t start = millis();
	byte offset = 0;
	do {
		Wire.requestFrom((byte)I2C_ADDR, (byte)MAX_PAYLOAD_SIZE, (byte)1);
		int c = Wire.read();
		if (offset == 0 && c < 0xa) {
			 // data not ready
			dataIdleLoop();
			continue; 
		}
		if (buffer) buffer[offset++] = c;
		for (byte i = 1; i < MAX_PAYLOAD_SIZE && Wire.available(); i++) {
			char c = Wire.read();
			if (c == '.' && offset > 2 && buffer[offset - 1] == '.' && buffer[offset - 2] == '.') {
				// waiting signal
				offset = 0;
				timeout = OBD_TIMEOUT_LONG;
			} else if (c == 0 || offset == bufsize - 1) {
				// string terminator encountered or buffer full
				if (buffer) buffer[offset] = 0;
				// discard the remaining data
				while (Wire.available()) Wire.read();
				return offset;
			} else {
				if (buffer) buffer[offset++] = c;
			}
		}
	} while(millis() - start < timeout);
	if (buffer) buffer[offset] = 0;
	return 0;
}

void COBDI2C::setQueryPID(byte pid, byte obdPid[])
{
	byte n = 0;
	for (; n < MAX_PIDS && obdPid[n]; n++) {
		if (obdPid[n] == pid)
			return;
	}
	if (n == MAX_PIDS) {
		memmove(obdPid, obdPid + 1, sizeof(obdPid[0]) * (MAX_PIDS - 1));
		n = MAX_PIDS - 1;
	}
	obdPid[n] = pid;
}

void COBDI2C::applyQueryPIDs(byte obdPid[])
{
	sendCommandBlock(CMD_APPLY_OBD_PIDS, 0, (byte*)obdPid, sizeof(obdPid[0])* MAX_PIDS);
	delay(200);
}

void COBDI2C::loadQueryData(PID_INFO obdInfo[])
{
	sendCommandBlock(CMD_LOAD_OBD_DATA);
	dataIdleLoop();
	Wire.requestFrom((byte)I2C_ADDR, (byte)MAX_PAYLOAD_SIZE, (byte)0);
	Wire.readBytes((char*)obdInfo, sizeof(obdInfo[0]) * MAX_PIDS);
}

#define MPU6050_I2C_ADDRESS 0x68
#define MPU6050_ACCEL_XOUT_H       0x3B   // R
#define MPU6050_ACCEL_XOUT_L       0x3C   // R
#define MPU6050_ACCEL_YOUT_H       0x3D   // R
#define MPU6050_ACCEL_YOUT_L       0x3E   // R
#define MPU6050_ACCEL_ZOUT_H       0x3F   // R
#define MPU6050_ACCEL_ZOUT_L       0x40   // R
#define MPU6050_TEMP_OUT_H         0x41   // R
#define MPU6050_TEMP_OUT_L         0x42   // R
#define MPU6050_GYRO_XOUT_H        0x43   // R
#define MPU6050_GYRO_XOUT_L        0x44   // R
#define MPU6050_GYRO_YOUT_H        0x45   // R
#define MPU6050_GYRO_YOUT_L        0x46   // R
#define MPU6050_GYRO_ZOUT_H        0x47   // R
#define MPU6050_GYRO_ZOUT_L        0x48   // R
#define MPU6050_PWR_MGMT_1         0x6B   // R/W
#define MPU6050_PWR_MGMT_2         0x6C   // R/W
#define MPU6050_WHO_AM_I           0x75   // R

typedef struct
{
    uint8_t x_accel_h;
    uint8_t x_accel_l;
    uint8_t y_accel_h;
    uint8_t y_accel_l;
    uint8_t z_accel_h;
    uint8_t z_accel_l;
    uint8_t t_h;
    uint8_t t_l;
    uint8_t x_gyro_h;
    uint8_t x_gyro_l;
    uint8_t y_gyro_h;
    uint8_t y_gyro_l;
    uint8_t z_gyro_h;
    uint8_t z_gyro_l;
} MPU6050_READOUT_DATA;

bool COBDI2C::memsInit()
{
	// default at power-up:
	//    Gyro at 250 degrees second
	//    Acceleration at 2g
	//    Clock source at internal 8MHz
	//    The device is in sleep mode.
	//
	uint8_t c;
	bool success;
	success = MPU6050_read (MPU6050_WHO_AM_I, &c, 1);
	if (!success) return false;

	// According to the datasheet, the 'sleep' bit
	// should read a '1'. But I read a '0'.
	// That bit has to be cleared, since the sensor
	// is in sleep mode at power-up. Even if the
	// bit reads '0'.
	success = MPU6050_read (MPU6050_PWR_MGMT_2, &c, 1);
	if (!success) return false;

	// Clear the 'sleep' bit to start the sensor.
	MPU6050_write_reg (MPU6050_PWR_MGMT_1, 0);
	return true;
}

bool COBDI2C::memsRead(int* acc, int* gyr, int* mag, int* temp)
{
	bool success;

	// Read the raw values.
	// Read 14 bytes at once,
	// containing acceleration, temperature and gyro.
	// With the default settings of the MPU-6050,
	// there is no filter enabled, and the values
	// are not very stable.
	
	MPU6050_READOUT_DATA accel_t_gyro;
	success = MPU6050_read (MPU6050_ACCEL_XOUT_H, (uint8_t *)&accel_t_gyro, sizeof(MPU6050_READOUT_DATA));
	if (!success) return false;
	
	if (temp) {
		// 340 per degrees Celsius, -512 at 35 degrees.
		*temp = ((int)(((uint16_t)accel_t_gyro.t_h << 8) | accel_t_gyro.t_l) + 512) / 34 + 350; 
	}

	if (acc) {
		MPU6050_store(acc, accel_t_gyro.x_accel_l, accel_t_gyro.x_accel_h);
		MPU6050_store(acc + 1, accel_t_gyro.y_accel_l, accel_t_gyro.y_accel_h);
		MPU6050_store(acc + 2, accel_t_gyro.z_accel_l, accel_t_gyro.z_accel_h);
	}

	if (gyr) {
		MPU6050_store(gyr, accel_t_gyro.x_gyro_l, accel_t_gyro.x_gyro_h);
		MPU6050_store(gyr + 1, accel_t_gyro.y_gyro_l, accel_t_gyro.y_gyro_h);
		MPU6050_store(gyr + 2, accel_t_gyro.z_gyro_l, accel_t_gyro.z_gyro_h);
	}
	
	if (mag) {
		// no magnetometer
		mag[0] = 0;
		mag[1] = 0;
		mag[2] = 0;
	}
	
	return true;
}

void COBDI2C::MPU6050_store(int* pData, uint8_t data_l, uint8_t data_h)
{
	uint8_t* ptr = (uint8_t*)pData;
	*ptr = data_l;
	*(ptr + 1) = data_h;
}

bool COBDI2C::MPU6050_read(int start, uint8_t* buffer, int size)
{
	int i, n;

	Wire.beginTransmission(MPU6050_I2C_ADDRESS);
	Wire.write(start);
	Wire.endTransmission(false);    // hold the I2C-bus

	// Third parameter is true: relase I2C-bus after data is read.
	Wire.requestFrom(MPU6050_I2C_ADDRESS, size, true);
	while(Wire.available() && i<size)
	{
		buffer[i++]=Wire.read();
	}
	return i == size;
}


bool COBDI2C::MPU6050_write(int start, const uint8_t* pData, int size)
{
	int n;

	Wire.beginTransmission(MPU6050_I2C_ADDRESS);
	Wire.write(start);        // write the start address
	n = Wire.write(pData, size);  // write data bytes
	if (n != size) return false;
	Wire.endTransmission(true); // release the I2C-bus
	return true;
}

bool COBDI2C::MPU6050_write_reg(int reg, uint8_t data)
{
	return MPU6050_write(reg, &data, 1);
}
#endif
