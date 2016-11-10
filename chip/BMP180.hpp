#pragma once
//=====================================================================//
/*!	@file
	@brief	BMP180 デジタル圧力センサー・ドライバー
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>
#include <cmath>
#include "common/iica_io.hpp"
#include "common/delay.hpp"

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  BMP180 テンプレートクラス
		@param[in]	I2C_IO	i2c I/O クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class I2C_IO>
	class BMP180 {

		// R/W ビットを含まない７ビット値
		static const uint8_t BMP180_ADR_ = 0x77;

		I2C_IO& i2c_;

		enum class MODE : uint8_t {
			ULTRALOWPOWER = 0,
			STANDARD      = 1,
			HIGHRES       = 2,
			ULTRAHIGHRES  = 3,
		};

		MODE	mode_;

		enum class REG : uint8_t {
			CAL_AC1       = 0xAA,  ///< Calibration data (16 bits)
			CAL_AC2       = 0xAC,  ///< Calibration data (16 bits)
			CAL_AC3       = 0xAE,  ///< Calibration data (16 bits)    
			CAL_AC4       = 0xB0,  ///< Calibration data (16 bits)
			CAL_AC5       = 0xB2,  ///< Calibration data (16 bits)
			CAL_AC6       = 0xB4,  ///< Calibration data (16 bits)
			CAL_B1        = 0xB6,  ///< Calibration data (16 bits)
			CAL_B2        = 0xB8,  ///< Calibration data (16 bits)
			CAL_MB        = 0xBA,  ///< Calibration data (16 bits)
			CAL_MC        = 0xBC,  ///< Calibration data (16 bits)
			CAL_MD        = 0xBE,  ///< Calibration data (16 bits)

			CONTROL       = 0xF4, 
			TEMPDATA      = 0xF6,
			PRESSUREDATA   = 0xF6,
			PRESSUREDATA_2 = 0xF8,
			READTEMPCMD   = 0x2E,
			READPRESSURECMD = 0x34,
		};

		int16_t		ac1_;
		int16_t		ac2_;
		int16_t		ac3_;
		int16_t		b1_;
		int16_t		b2_;
		int16_t		mb_;
		int16_t		mc_;
		int16_t		md_;
		uint16_t	ac4_;
		uint16_t	ac5_;
		uint16_t	ac6_;

		uint8_t read8_(REG adr) {
			uint8_t reg[1];
			reg[0] = static_cast<uint8_t>(adr);
			i2c_.send(BMP180_ADR_, reg, 1);
			i2c_.recv(BMP180_ADR_, reg, 1);
			return reg[0];
		}

		uint16_t read16_(REG adr) {
			uint8_t reg[2];
			reg[0] = static_cast<uint8_t>(adr);
			i2c_.send(BMP180_ADR_, reg, 1);
			i2c_.recv(BMP180_ADR_, reg, 2);
			return (reg[0] << 8) | reg[1];
		}

		void write8_(REG a, REG b) {
			uint8_t reg[2];
			reg[0] = static_cast<uint8_t>(a);
			reg[1] = static_cast<uint8_t>(b);
			i2c_.send(BMP180_ADR_, reg, 2);
		}

		int32_t computeB5_(int32_t UT) {
			int32_t X1 = (UT - static_cast<int32_t>(ac6_)) * (static_cast<int32_t>(ac5_)) >> 15;
			int32_t X2 = (static_cast<int32_t>(mc_) << 11) / (X1 + static_cast<int32_t>(md_));
			return X1 + X2;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	i2c	iica_io クラスを参照で渡す
		 */
		//-----------------------------------------------------------------//
		BMP180(I2C_IO& i2c) : i2c_(i2c), mode_(MODE::ULTRAHIGHRES),
			ac1_(0), ac2_(0), ac3_(0), b1_(0), b2_(0), mb_(0), mc_(0), md_(0),
			ac4_(0), ac5_(0), ac6_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@return エラーなら「false」を返す
		 */
		//-----------------------------------------------------------------//
		bool start() {

			if (read8_(static_cast<REG>(0xD0)) != 0x55) return false;

			// read calibration data
			ac1_ = read16_(REG::CAL_AC1);
			ac2_ = read16_(REG::CAL_AC2);
			ac3_ = read16_(REG::CAL_AC3);
			ac4_ = read16_(REG::CAL_AC4);
			ac5_ = read16_(REG::CAL_AC5);
			ac6_ = read16_(REG::CAL_AC6);

			b1_ = read16_(REG::CAL_B1);
			b2_ = read16_(REG::CAL_B2);

			mb_ = read16_(REG::CAL_MB);
			mc_ = read16_(REG::CAL_MC);
			md_ = read16_(REG::CAL_MD);

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	センサ温度値を返す
			@return センサ温度値
		 */
		//-----------------------------------------------------------------//
		uint16_t get_raw_temperature()
		{
  			write8_(REG::CONTROL, REG::READTEMPCMD);
			utils::delay::milli_second(5);
			return read16_(REG::TEMPDATA);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	センサ圧力値を返す
			@return センサ圧力値
		 */
		//-----------------------------------------------------------------//
		uint32_t get_raw_pressure()
		{
			write8_(REG::CONTROL, static_cast<REG>(
				static_cast<uint8_t>(REG::READPRESSURECMD) + (static_cast<uint8_t>(mode_) << 6)));

			switch(mode_) {
			case MODE::ULTRALOWPOWER: 
				utils::delay::milli_second(5);
				break;
  			case MODE::STANDARD: 
				utils::delay::milli_second(8);
				break;
			case MODE::HIGHRES:
				utils::delay::milli_second(14);
				break;
			default:
				utils::delay::milli_second(26);
				break;
			}

			uint32_t raw = read16_(REG::PRESSUREDATA);
			raw <<= 8;
			raw |= read8_(REG::PRESSUREDATA_2);
			raw >>= (8 - static_cast<uint8_t>(mode_));

			 /* this pull broke stuff, look at it later?
			  if (oversampling==0) {
			    raw <<= 8;
			    raw |= read8(BMP085_PRESSUREDATA+2);
			    raw >>= (8 - oversampling);
			  }
			 */
			return raw;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	温度を返す（℃ * 100）
			@return 温度
		 */
		//-----------------------------------------------------------------//
		int32_t get_temperature()
		{
			int32_t UT = get_raw_temperature();
			int32_t B5 = computeB5_(UT);
			int32_t temp = (B5 + 8) >> 3;
			return temp * 5;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	整数圧力を返す（hPa * 100）
			@return 圧力
		 */
		//-----------------------------------------------------------------//
		int32_t get_pressure_int100()
		{
  			int32_t UT = get_raw_temperature();
			int32_t UP = get_raw_pressure();
#if 0
			// use datasheet numbers!
			UT = 27898;
			UP = 23843;
			ac6_ = 23153;
			ac5_ = 32757;
			mc_ = -8711;
			md_ = 2868;
			b1_ = 6190;
			b2_ = 4;
			ac3_ = -14383;
			ac2_ = -72;
			ac1_ = 408;
			ac4_ = 32741;
			mode_ = MODE::ULTRALOWPOWER;
#endif

			int32_t B5 = computeB5_(UT);

			// do pressure calcs
			int32_t B6 = B5 - 4000;
			int32_t X1 = (static_cast<int32_t>(b2_) * ((B6 * B6) >> 12)) >> 11;
			int32_t X2 = (static_cast<int32_t>(ac2_) * B6) >> 11;
			int32_t X3 = X1 + X2;
			int32_t B3 = (((static_cast<int32_t>(ac1_) * 4 + X3) << static_cast<int8_t>(mode_)) + 2) / 4;

			X1 = (static_cast<int32_t>(ac3_) * B6) >> 13;
			X2 = (static_cast<int32_t>(b1_) * ((B6 * B6) >> 12)) >> 16;
			X3 = ((X1 + X2) + 2) >> 2;
			uint32_t B4 = (static_cast<uint32_t>(ac4_) * static_cast<uint32_t>(X3 + 32768)) >> 15;
			uint32_t B7 = (static_cast<uint32_t>(UP) - B3) * static_cast<uint32_t>(50000UL >> static_cast<uint8_t>(mode_));

  			int32_t p;
			if (B7 < 0x80000000) {
				p = (B7 * 2) / B4;
			} else {
				p = (B7 / B4) * 2;
			}
			X1 = (p >> 8) * (p >> 8);
			X1 = (X1 * 3038) >> 16;
			X2 = (-7357 * p) >> 16;

			p = p + ((X1 + X2 + static_cast<int32_t>(3791)) >> 4);
			return p;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	圧力を返す [hPa]
			@return 圧力 [hPa]
		 */
		//-----------------------------------------------------------------//
		float get_pressure() {
			return static_cast<float>(get_pressure_int100()) / 100.0f;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	高度を返す
			@param[in]	seaLevelhPa 海面ヘクトパスカル
			@return 高度
		 */
		//-----------------------------------------------------------------//
		float get_altitude(float seaLevelhPa = 1013.25f)
		{
			float pressure = get_pressure();
			float altitude = 44330.0f * (1.0f - std::pow(pressure / seaLevelhPa, 0.1903f));
			return altitude;
		}
	};
}
