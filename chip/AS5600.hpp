#pragma once
//=========================================================================//
/*!	@file
	@brief	AS5600 I2C 12-bit Programmable Contactless Potentiometer @n
			ams @n
			https://ams.com/ja/as5600
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=========================================================================//
#include <cstdint>

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  AS5600 テンプレートクラス
		@param[in]	I2C_IO	I2C I/O クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class I2C_IO>
	class AS5600 {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  パワーモード型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class POWER_MODE : uint8_t {
			NORMAL,		///< Normal / 6.5mA
			LPM1,		///< Polling time:   5ms / 3.4mA
			LPM2,		///< Polling time:  20ms / 1.8mA
			LPM3		///< Polling time: 100ms / 1.5mA
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ヒステリシス型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class HYSTERESIS : uint8_t {
			OFF,
			LSB1,
			LSB2,
			LSB3
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  出力ステージ型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class OUTPUT_STAGE : uint8_t {
			ANALOG_FULL,
			ANALOG_REDUCED,
			DIGITAL_PWM
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PWM 周波数型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class PWM : uint8_t {
			F115,	///< 115 Hz
			F230,	///< 230 Hz
			F460,	///< 460 Hz
			F920,	///< 920 Hz
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  スローフィルター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class SLOW_FILTER : uint8_t {
			X16,	///< 16x
			X8,		///< 8x
			X4,		///< 4x
			X2		///< 2x
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ファースト・フィルター・スレッショルド型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class FAST_FILTER_THRESHOLD : uint8_t {
			SLOW,
    		LSB6,
      		LSB7,
    		LSB9,
    		LSB18,
    		LSB21,
    		LSB24,
    		LSB10
		};

	private:

		static constexpr uint8_t I2C_ADR = 0b011'0110;		///< (0x36) with out R/W bit

		I2C_IO&		i2c_io_;

		enum class CMD : uint8_t {
    		ZMCO        = 0x00,
			ZPOS_H      = 0x01,
    		ZPOS_L      = 0x02,
    		MPOS_H      = 0x03,
    		MPOS_L      = 0x04,
      		MANG_H      = 0x05,
    		MANG_L      = 0x06,
    		CONF_H      = 0x07,
    		CONF_L      = 0x08,
    		RAWANGLE_H  = 0x0C,
    		RAWANGLE_L  = 0x0D,
    		ANGLE_H     = 0x0E,
    		ANGLE_L     = 0x0F,
    		STATUS      = 0x0B,
    		AGC         = 0x1A,
    		MAGNITUDE_H = 0x1B,
    		MAGNITUDE_L = 0x1C,
    		BURN        = 0xFF
		};

		void write_(CMD cmd, uint8_t value) noexcept
		{
			uint8_t tmp[2];
			tmp[0] = static_cast<uint8_t>(cmd);
			tmp[1] = value;
			i2c_io_.send(I2C_ADR, tmp, sizeof(tmp));
		}


		void write16_(CMD cmd, uint16_t value) noexcept
		{
			uint8_t tmp[3];
			tmp[0] = static_cast<uint8_t>(cmd);
			tmp[1] = value >> 8;
			tmp[2] = value;
			i2c_io_.send(I2C_ADR, tmp, sizeof(tmp));
		}


		uint8_t read_(CMD cmd) noexcept
		{
			uint8_t tmp[1];
			tmp[0] = static_cast<uint8_t>(cmd);
			i2c_io_.send(I2C_ADR, tmp, 1);
			i2c_io_.recv(I2C_ADR, tmp, 1);
			return tmp[0];
		}


		uint16_t read16_(CMD cmd) noexcept
		{
			uint8_t tmp[2];
			tmp[0] = static_cast<uint8_t>(cmd);
			i2c_io_.send(I2C_ADR, tmp, 1);
			i2c_io_.recv(I2C_ADR, tmp, 2);
			return (static_cast<uint16_t>(tmp[0]) << 8) | tmp[1];
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクタ
		 */
		//-----------------------------------------------------------------//
		AS5600(I2C_IO& i2c_io) noexcept : i2c_io_(i2c_io)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@return エラーがあれば「false」を返す。
		 */
		//-----------------------------------------------------------------//
		bool start() noexcept
		{
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	RAW 角度の取得
			@return RAW 角度
		 */
		//-----------------------------------------------------------------//
		uint16_t get_raw_angle() noexcept
		{
			return read16_(CMD::RAWANGLE_H);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ステータスの取得 @n
					X X MD ML MH X X X @n
					MH: AGC minimum gain overflow, magnet too strong @n
 					ML: AGC maximum gain overflow, magnet too weak @n
 					MD: Magnet was detected
			@return ステータス
		 */
		//-----------------------------------------------------------------//
		uint8_t get_status() noexcept
		{
			return read_(CMD::STATUS);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	磁力が強すぎるか？
			@return 強すぎる場合「true」
		 */
		//-----------------------------------------------------------------//
		bool is_magnet_too_strong() noexcept
		{
			return (get_status() & 0b0000'1000) != 0 ? true : false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	磁力が弱すぎるか？
			@return 弱すぎる場合「true」
		 */
		//-----------------------------------------------------------------//
		bool is_magnet_too_weak() noexcept
		{
			return (get_status() & 0b0001'0000) != 0 ? true : false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	磁力を検出したか？
			@return 検出した場合「true」
		 */
		//-----------------------------------------------------------------//
		bool is_magnet_detected() noexcept
		{
			return (get_status() & 0b0010'0000) != 0 ? true : false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	AGC (Automatic Gain Control) の取得 @n
					3.3V: 0 to 128 @n
					5.0V: 0 to 255
			@return AGC
		 */
		//-----------------------------------------------------------------//
		uint8_t get_agc() noexcept
		{
			return read_(CMD::AGC);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	MAGNITUDE の取得
			@return MAGNITUDE
		 */
		//-----------------------------------------------------------------//
		uint16_t get_magnitude() noexcept
		{
			return read16_(CMD::MAGNITUDE_H);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	パワーモードの設定
			@param[in] mode	パワーモード型
		 */
		//-----------------------------------------------------------------//
		void set_power_mode(POWER_MODE mode) noexcept
		{
			auto tmp = read_(CMD::CONF_L);
			tmp &= 0b1111'1100;
			tmp |= static_cast<uint8_t>(mode);
			write_(CMD::CONF_L, tmp);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ヒステリシスの設定
			@param[in] hyst	ヒステリシス型
		 */
		//-----------------------------------------------------------------//
		void set_hysteresis(HYSTERESIS hyst) noexcept
		{
			auto tmp = read_(CMD::CONF_L);
			tmp &= 0b1111'0011;
			tmp |= static_cast<uint8_t>(hyst) << 2;
			write_(CMD::CONF_L, tmp);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	出力ステージの設定
			@param[in] ost	出力ステージ型
		 */
		//-----------------------------------------------------------------//
		void set_output_stage(OUTPUT_STAGE ost) noexcept
		{
			auto tmp = read_(CMD::CONF_L);
			tmp &= 0b1100'1111;
			tmp |= static_cast<uint8_t>(ost) << 4;
			write_(CMD::CONF_L, tmp);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	PWM 周波数の設定
			@param[in] pwm	PWM 周波数型
		 */
		//-----------------------------------------------------------------//
		void set_pwm_frequency(PWM pwm) noexcept
		{
			auto tmp = read_(CMD::CONF_L);
			tmp &= 0b0011'1111;
			tmp |= static_cast<uint8_t>(pwm) << 6;
			write_(CMD::CONF_L, tmp);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	スローフィルターの設定
			@param[in]	slf		スローフィルター型
		 */
		//-----------------------------------------------------------------//
		void set_slow_filter(SLOW_FILTER slf) noexcept
		{
			auto tmp = read_(CMD::CONF_H);
			tmp &= 0b1111'1100;
			tmp |= static_cast<uint8_t>(slf);
			write_(CMD::CONF_H, tmp);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	CONF の取得
			@return CONF
		 */
		//-----------------------------------------------------------------//
		uint16_t get_conf() noexcept
		{
			return read16_(CMD::CONF_H);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ファースト・フィルター・スレッショルドの設定
			@param[in]	fft		ファースト・フィルター・スレッショルド型
		 */
		//-----------------------------------------------------------------//
		void set_fast_filter_threshold(FAST_FILTER_THRESHOLD fft) noexcept
		{
			auto tmp = read_(CMD::CONF_H);
			tmp &= 0b1110'0011;
			tmp |= static_cast<uint8_t>(fft) << 2;
			write_(CMD::CONF_H, tmp);
		}
	};
}
