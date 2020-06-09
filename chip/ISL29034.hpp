#pragma once
//=========================================================================//
/*!	@file
	@brief	ISL29034 class @n
			Renesas (Intersil) @n
			Integrated Digital Light Sensor ドライバー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cstdint>
#include "common/delay.hpp"
#include "common/format.hpp"

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ISL29034 テンプレートクラス
		@param[in]	I2C	I2C 制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class I2C>
	class ISL29034 {

		static const uint8_t	I2C_ADR = 0x44;  ///< ISL29034 I2C Slave Address

		static const uint8_t	DEVICE_ID = 0x28 ///< ISL29034 Device ID(xx101xxx)

		enum class REG_ADR : uint8_t {
			CMD1 = 0x00,
			CMD2 = 0x01,
			DATA_L = 0x02,
			DATA_H = 0x03,
			REG_ID = 0x0F,
		};

		enum class OPR_MODE : uint8_t {  // Operation Mode
			PWR_DOWN = 0x00,	///< Power-down the device(Default)
			ALS_CONT = 0xA0,    ///< Measures ALS continuously
		};

		enum class LUX_RANGE : uint8_t {  // FULL SCALE LUX RANGE
			FS_0 = 0x00, ///< 1,000(Default)
			FS_1 = 0x01, ///< 4,000
			FS_2 = 0x02, ///< 16,000
			FS_3 = 0x03, ///< 64,000
		};

		enum class ADC_RESOLUTION : uint8_t {  // ADC RESOLUTION
			RES_16 = 0x00, ///< 16bit(Default)
			RES_12 = 0x04, ///< 12bit
			RES_8  = 0x08, ///< 8bit
			RES_4  = 0x0C, ///< 4bit
		};

		static const uint8_t ID_MASK = 0b00111000; ///< ISL29034 Device ID Mask

		I2C&	i2c_;

		LUX_RANGE		lux_range_;
		ADC_RESOLUTION	adc_resolution_;

#if 0


/**
 @brief Write I2C
 @param [in] address register address
 @param [in] data write data
*/
void FaBoAmbientLight::writeI2c(uint8_t address, uint8_t data) {
  Wire.beginTransmission(_i2caddr);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission();
}

/**
 @brief Read I2C
 @param [in] address register address
 @param [in] num read length
 @param [out] data read data
*/
void FaBoAmbientLight::readI2c(uint8_t address, uint8_t num, uint8_t * data) {
  Wire.beginTransmission(_i2caddr);
  Wire.write(address);
  Wire.endTransmission();
  uint8_t i = 0;
  Wire.requestFrom(_i2caddr, num);
  while( Wire.available() ) {
    data[i++] = Wire.read();
  }
}
#endif

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	i2c	i2c 制御クラスを参照で渡す
		 */
		//-----------------------------------------------------------------//
		ISL29034(I2C& i2c) noexcept : i2c_(i2c),
			lux_range_(LUX_RANGE::FS0),
			adc_resolution_(ADC_RESOLUTION::RES_16)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	デバイス ID を取得
			@return デバイス ID
		 */
		//-----------------------------------------------------------------//
//		uint16_t get_id() const noexcept { return id_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool start() noexcept
		{

#if 0
  if ( searchDevice() ) {
    setOperation(ISL29034_OP_ALS_CONT);
    setRange(ISL29034_FS_3);
    setResolution(ISL29034_RES_16);
    return true;
  } else {
    return false;
  }
#endif

			return true;
		}

#if 0
/**
 @brief Search Device
 @retval true device connected
 @retval false device error
*/
bool FaBoAmbientLight::searchDevice() {
  uint8_t data;
  readI2c(ISL29034_REG_ID, 1, &data);
//   Serial.println(data,HEX);
//   Serial.println(data&ISL29034_ID_MASK,HEX);
  if ( (data & ISL29034_ID_MASK) == ISL29034_DEVICE_ID ) {
    return true;
  } else {
    return false;
  }
}

/**
 @brief Set Operation Mode
 @param [in] config Operation Mode
*/
void FaBoAmbientLight::setOperation(uint8_t config) {
  writeI2c(ISL29034_REG_CMD1, config);
}

/**
 @brief Set FullScale Range
 @param [in] config FullScale Range
*/
void FaBoAmbientLight::setRange(uint8_t config) {
  uint8_t data;
  _range = config;
  readI2c(ISL29034_REG_CMD2, 1, &data);
  data &= 0xFC; // 11111100
  data |= config;
  writeI2c(ISL29034_REG_CMD2, data );
}

/**
 @brief Set ADC Resolution
 @param [in] config Resolution
*/
void FaBoAmbientLight::setResolution(uint8_t config) {
  uint8_t data;
  _resolution = config;
  readI2c(ISL29034_REG_CMD2, 1, &data);
  data &= 0xF3; // 11110011
  data |= config;
  writeI2c(ISL29034_REG_CMD2, data );
}


#endif


		//-----------------------------------------------------------------//
		/*!
			@brief	センサー値の取得（最大１６ビット）
			@return センサー値
		 */
		//-----------------------------------------------------------------//
		uint16_t get_value() noexcept
		{
			uint8_t tmp[2];

			switch(adc_resolution_) {
			case ADC_RESOLUTION::RES_16:
//				delay(90);
				break;
			case ADC_RESOLUTION::RES_12:
//				delay(6);
				break;
			case ADC_RESOLUTION::RES_8:
//				delayMicroseconds(352);
				break;
			case ADC_RESOLUTION::RES_4:
//				delayMicroseconds(22);
				break;
			}

//			read_(REG_DATA_L, 2, data);
			uint16_t adc = (static_cast<uint16_t>(tmp[1]) << 8) | static_cast<uint16_t>(tmp[0]);
			return adc;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	LUX の取得
			@return LUX 値
		 */
		//-----------------------------------------------------------------//
		float get_lux() noexcept
		{
			auto adc = get_value();
			if(adc == 0) return 0.0f;  // error ?

			uint16_t range = 0;
			switch(lux_range_) {
			case LUX_RANGE::FS_0:
				range = 1000;
				break;
			case LUX_RANGE::FS_1:
				range = 4000;
				break;
			case LUX_RANGE::FS_2:
				range = 16000;
				break;
			case LUX_RANGE::FS_3:
				range = 64000;
				break;
			}

			uint16_t count = 0;
			switch(adc_resolution_) {
			case ADC_RESOLUTION::RES_16:
				count = 65535;
				break;
			case ADC_RESOLUTION::RES_12:
				count = 4095;
				break;
			case ADC_RESOLUTION::RES_8:
				count = 255;
				break;
			case ADC_RESOLUTION::RES_4:
				count = 15;
				break;
			}

			return static_cast<float>(range) / static_cast<float>(count) * static_cast<float>(adc);
		}
	};
}
