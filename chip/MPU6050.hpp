#pragma once
//=====================================================================//
/*!	@file
	@brief	MPU6050 ジャイロ、加速度センサ・ドライバー
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>
#include "common/iica_io.hpp"
#include "common/delay.hpp"

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MPU6050 テンプレートクラス
		@param[in]	I2C_IO	i2c I/O クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class I2C_IO>
	class MPU6050 {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	int16_t 型ベクター
		 */
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct int16_vec {
			int16_t	x;
			int16_t y;
			int16_t z;
		};

	private:
		// R/W ビットを含まない７ビット値
		static const uint8_t MPU6050_ADR_ = 0x68;  // AD0 = 0; (GY-521 module default)
//		static const uint8_t MPU6050_ADR_ = 0x69;  // AD0 = 1;

		enum class REG : uint8_t {
			XG_OFFS_TC       = 0x00, //[7] PWR_MODE, [6:1] XG_OFFS_TC, [0] OTP_BNK_VLD
			YG_OFFS_TC       = 0x01, //[7] PWR_MODE, [6:1] YG_OFFS_TC, [0] OTP_BNK_VLD
			ZG_OFFS_TC       = 0x02, //[7] PWR_MODE, [6:1] ZG_OFFS_TC, [0] OTP_BNK_VLD
			X_FINE_GAIN      = 0x03, //[7:0] X_FINE_GAIN
			Y_FINE_GAIN      = 0x04, //[7:0] Y_FINE_GAIN
			Z_FINE_GAIN      = 0x05, //[7:0] Z_FINE_GAIN
			XA_OFFS_H        = 0x06, //[15:0] XA_OFFS
			XA_OFFS_L_TC     = 0x07,
			YA_OFFS_H        = 0x08, //[15:0] YA_OFFS
			YA_OFFS_L_TC     = 0x09,
			ZA_OFFS_H        = 0x0A, //[15:0] ZA_OFFS
			ZA_OFFS_L_TC     = 0x0B,
			XG_OFFS_USRH     = 0x13, //[15:0] XG_OFFS_USR
			XG_OFFS_USRL     = 0x14,
			YG_OFFS_USRH     = 0x15, //[15:0] YG_OFFS_USR
			YG_OFFS_USRL     = 0x16,
			ZG_OFFS_USRH     = 0x17, //[15:0] ZG_OFFS_USR
			ZG_OFFS_USRL     = 0x18,
			SMPLRT_DIV       = 0x19,
			CONFIG           = 0x1A,
			GYRO_CONFIG      = 0x1B,
			ACCEL_CONFIG     = 0x1C,
			FF_THR           = 0x1D,
			FF_DUR           = 0x1E,
			MOT_THR          = 0x1F,
			MOT_DUR          = 0x20,
			ZRMOT_THR        = 0x21,
			ZRMOT_DUR        = 0x22,
			FIFO_EN          = 0x23,
			I2C_MST_CTRL     = 0x24,
			I2C_SLV0_ADDR    = 0x25,
			I2C_SLV0_REG     = 0x26,
			I2C_SLV0_CTRL    = 0x27,
			I2C_SLV1_ADDR    = 0x28,
			I2C_SLV1_REG     = 0x29,
			I2C_SLV1_CTRL    = 0x2A,
			I2C_SLV2_ADDR    = 0x2B,
			I2C_SLV2_REG     = 0x2C,
			I2C_SLV2_CTRL    = 0x2D,
			I2C_SLV3_ADDR    = 0x2E,
			I2C_SLV3_REG     = 0x2F,
			I2C_SLV3_CTRL    = 0x30,
			I2C_SLV4_ADDR    = 0x31,
			I2C_SLV4_REG     = 0x32,
			I2C_SLV4_DO      = 0x33,
			I2C_SLV4_CTRL    = 0x34,
			I2C_SLV4_DI      = 0x35,
			I2C_MST_STATUS   = 0x36,
			INT_PIN_CFG      = 0x37,
			INT_ENABLE       = 0x38,
			DMP_INT_STATUS   = 0x39,
			INT_STATUS       = 0x3A,
			ACCEL_XOUT_H     = 0x3B,
			ACCEL_XOUT_L     = 0x3C,
			ACCEL_YOUT_H     = 0x3D,
			ACCEL_YOUT_L     = 0x3E,
			ACCEL_ZOUT_H     = 0x3F,
			ACCEL_ZOUT_L     = 0x40,
			TEMP_OUT_H       = 0x41,
			TEMP_OUT_L       = 0x42,
			GYRO_XOUT_H      = 0x43,
			GYRO_XOUT_L      = 0x44,
			GYRO_YOUT_H      = 0x45,
			GYRO_YOUT_L      = 0x46,
			GYRO_ZOUT_H      = 0x47,
			GYRO_ZOUT_L      = 0x48,
			EXT_SENS_DATA_00 = 0x49,
			EXT_SENS_DATA_01 = 0x4A,
			EXT_SENS_DATA_02 = 0x4B,
			EXT_SENS_DATA_03 = 0x4C,
			EXT_SENS_DATA_04 = 0x4D,
			EXT_SENS_DATA_05 = 0x4E,
			EXT_SENS_DATA_06 = 0x4F,
			EXT_SENS_DATA_07 = 0x50,
			EXT_SENS_DATA_08 = 0x51,
			EXT_SENS_DATA_09 = 0x52,
			EXT_SENS_DATA_10 = 0x53,
			EXT_SENS_DATA_11 = 0x54,
			EXT_SENS_DATA_12 = 0x55,
			EXT_SENS_DATA_13 = 0x56,
			EXT_SENS_DATA_14 = 0x57,
			EXT_SENS_DATA_15 = 0x58,
			EXT_SENS_DATA_16 = 0x59,
			EXT_SENS_DATA_17 = 0x5A,
			EXT_SENS_DATA_18 = 0x5B,
			EXT_SENS_DATA_19 = 0x5C,
			EXT_SENS_DATA_20 = 0x5D,
			EXT_SENS_DATA_21 = 0x5E,
			EXT_SENS_DATA_22 = 0x5F,
			EXT_SENS_DATA_23 = 0x60,
			MOT_DETECT_STATUS= 0x61,
			I2C_SLV0_DO      = 0x63,
			I2C_SLV1_DO      = 0x64,
			I2C_SLV2_DO      = 0x65,
			I2C_SLV3_DO      = 0x66,
			I2C_MST_DELAY_CTRL=0x67,
			SIGNAL_PATH_RESET= 0x68,
			MOT_DETECT_CTRL  = 0x69,
			USER_CTRL        = 0x6A,
			PWR_MGMT_1       = 0x6B,
			PWR_MGMT_2       = 0x6C,
			BANK_SEL         = 0x6D,
			MEM_START_ADDR   = 0x6E,
			MEM_R_W          = 0x6F,
			DMP_CFG_1        = 0x70,
			DMP_CFG_2        = 0x71,
			FIFO_COUNTH      = 0x72,
			FIFO_COUNTL      = 0x73,
			FIFO_R_W         = 0x74,
			WHO_AM_I         = 0x75,
		};

		struct CLOCK {
			enum {
				INTERNAL        = 0x00,
				PLL_XGYRO       = 0x01,
				PLL_YGYRO       = 0x02,
				PLL_ZGYRO       = 0x03,
				PLL_EXT32K      = 0x04,
				PLL_EXT19M      = 0x05,
				KEEP_RESET      = 0x07,
			};
		};

		struct PWR1 {
			enum {
				DEVICE_RESET_BIT = 7,
				SLEEP_BIT        = 6,
				CYCLE_BIT        = 5,
				TEMP_DIS_BIT     = 3,
				CLKSEL_LENGTH    = 3,
				CLKSEL_BIT       = 0,
			};
		};

		struct GYRO_CONFIG {
			enum {
				FS_SEL_BIT    = 2,
				FS_SEL_LENGTH = 2,
			};
			enum {
				FS_250       = 0x00,
				FS_500       = 0x01,
				FS_1000      = 0x02,
				FS_2000      = 0x03,
			};
		};

		struct ACCEL_CONFIG {
			enum {
				XA_ST_BIT         = 7,
				YA_ST_BIT         = 6,
				ZA_ST_BIT         = 5,
				AFS_SEL_BIT       = 3,
				AFS_SEL_LENGTH    = 2,
			};
			enum {
				AFS_2        = 0x00,
				AFS_4        = 0x01,
				AFS_8        = 0x02,
				AFS_16       = 0x03,
			};
		};

#if 0
TC_PWR_MODE_BIT     7
TC_OFFSET_BIT       6
TC_OFFSET_LENGTH    6
TC_OTP_BNK_VLD_BIT  0

VDDIO_LEVEL_VLOGIC  0
VDDIO_LEVEL_VDD     1

CFG_EXT_SYNC_SET_BIT    5
CFG_EXT_SYNC_SET_LENGTH 3
CFG_DLPF_CFG_BIT    2
CFG_DLPF_CFG_LENGTH 3

EXT_SYNC_DISABLED       0x0
EXT_SYNC_TEMP_OUT_L     0x1
EXT_SYNC_GYRO_XOUT_L    0x2
EXT_SYNC_GYRO_YOUT_L    0x3
EXT_SYNC_GYRO_ZOUT_L    0x4
EXT_SYNC_ACCEL_XOUT_L   0x5
EXT_SYNC_ACCEL_YOUT_L   0x6
EXT_SYNC_ACCEL_ZOUT_L   0x7

DLPF_BW_256         0x00
DLPF_BW_188         0x01
DLPF_BW_98          0x02
DLPF_BW_42          0x03
DLPF_BW_20          0x04
DLPF_BW_10          0x05
DLPF_BW_5           0x06

DHPF_RESET          0x00
DHPF_5              0x01
DHPF_2P5            0x02
DHPF_1P25           0x03
DHPF_0P63           0x04
DHPF_HOLD           0x07

TEMP_FIFO_EN_BIT    7
XG_FIFO_EN_BIT      6
YG_FIFO_EN_BIT      5
ZG_FIFO_EN_BIT      4
ACCEL_FIFO_EN_BIT   3
SLV2_FIFO_EN_BIT    2
SLV1_FIFO_EN_BIT    1
SLV0_FIFO_EN_BIT    0

MULT_MST_EN_BIT     7
WAIT_FOR_ES_BIT     6
SLV_3_FIFO_EN_BIT   5
I2C_MST_P_NSR_BIT   4
I2C_MST_CLK_BIT     3
I2C_MST_CLK_LENGTH  4

CLOCK_DIV_348       0x0
CLOCK_DIV_333       0x1
CLOCK_DIV_320       0x2
CLOCK_DIV_308       0x3
CLOCK_DIV_296       0x4
CLOCK_DIV_286       0x5
CLOCK_DIV_276       0x6
CLOCK_DIV_267       0x7
CLOCK_DIV_258       0x8
CLOCK_DIV_500       0x9
CLOCK_DIV_471       0xA
CLOCK_DIV_444       0xB
CLOCK_DIV_421       0xC
CLOCK_DIV_400       0xD
CLOCK_DIV_381       0xE
CLOCK_DIV_364       0xF

I2C_SLV_RW_BIT      7
I2C_SLV_ADDR_BIT    6
I2C_SLV_ADDR_LENGTH 7
I2C_SLV_EN_BIT      7
I2C_SLV_BYTE_SW_BIT 6
I2C_SLV_REG_DIS_BIT 5
I2C_SLV_GRP_BIT     4
I2C_SLV_LEN_BIT     3
I2C_SLV_LEN_LENGTH  4

I2C_SLV4_RW_BIT         7
I2C_SLV4_ADDR_BIT       6
I2C_SLV4_ADDR_LENGTH    7
I2C_SLV4_EN_BIT         7
I2C_SLV4_INT_EN_BIT     6
I2C_SLV4_REG_DIS_BIT    5
I2C_SLV4_MST_DLY_BIT    4
I2C_SLV4_MST_DLY_LENGTH 5

MST_PASS_THROUGH_BIT    7
MST_I2C_SLV4_DONE_BIT   6
MST_I2C_LOST_ARB_BIT    5
MST_I2C_SLV4_NACK_BIT   4
MST_I2C_SLV3_NACK_BIT   3
MST_I2C_SLV2_NACK_BIT   2
MST_I2C_SLV1_NACK_BIT   1
MST_I2C_SLV0_NACK_BIT   0

INTCFG_INT_LEVEL_BIT        7
INTCFG_INT_OPEN_BIT         6
INTCFG_LATCH_INT_EN_BIT     5
INTCFG_INT_RD_CLEAR_BIT     4
INTCFG_FSYNC_INT_LEVEL_BIT  3
INTCFG_FSYNC_INT_EN_BIT     2
INTCFG_I2C_BYPASS_EN_BIT    1
INTCFG_CLKOUT_EN_BIT        0

INTMODE_ACTIVEHIGH  0x00
INTMODE_ACTIVELOW   0x01

INTDRV_PUSHPULL     0x00
INTDRV_OPENDRAIN    0x01

INTLATCH_50USPULSE  0x00
INTLATCH_WAITCLEAR  0x01

INTCLEAR_STATUSREAD 0x00
INTCLEAR_ANYREAD    0x01

INTERRUPT_FF_BIT            7
INTERRUPT_MOT_BIT           6
INTERRUPT_ZMOT_BIT          5
INTERRUPT_FIFO_OFLOW_BIT    4
INTERRUPT_I2C_MST_INT_BIT   3
INTERRUPT_PLL_RDY_INT_BIT   2
INTERRUPT_DMP_INT_BIT       1
INTERRUPT_DATA_RDY_BIT      0

// TODO: figure out what these actually do
// UMPL source code is not very obivous
DMPINT_5_BIT            5
DMPINT_4_BIT            4
DMPINT_3_BIT            3
DMPINT_2_BIT            2
DMPINT_1_BIT            1
DMPINT_0_BIT            0

MOTION_MOT_XNEG_BIT     7
MOTION_MOT_XPOS_BIT     6
MOTION_MOT_YNEG_BIT     5
MOTION_MOT_YPOS_BIT     4
MOTION_MOT_ZNEG_BIT     3
MOTION_MOT_ZPOS_BIT     2
MOTION_MOT_ZRMOT_BIT    0

DELAYCTRL_DELAY_ES_SHADOW_BIT   7
DELAYCTRL_I2C_SLV4_DLY_EN_BIT   4
DELAYCTRL_I2C_SLV3_DLY_EN_BIT   3
DELAYCTRL_I2C_SLV2_DLY_EN_BIT   2
DELAYCTRL_I2C_SLV1_DLY_EN_BIT   1
DELAYCTRL_I2C_SLV0_DLY_EN_BIT   0

PATHRESET_GYRO_RESET_BIT    2
PATHRESET_ACCEL_RESET_BIT   1
PATHRESET_TEMP_RESET_BIT    0

DETECT_ACCEL_ON_DELAY_BIT       5
DETECT_ACCEL_ON_DELAY_LENGTH    2
DETECT_FF_COUNT_BIT             3
DETECT_FF_COUNT_LENGTH          2
DETECT_MOT_COUNT_BIT            1
DETECT_MOT_COUNT_LENGTH         2

DETECT_DECREMENT_RESET  0x0
DETECT_DECREMENT_1      0x1
DETECT_DECREMENT_2      0x2
DETECT_DECREMENT_4      0x3

USERCTRL_DMP_EN_BIT             7
USERCTRL_FIFO_EN_BIT            6
USERCTRL_I2C_MST_EN_BIT         5
USERCTRL_I2C_IF_DIS_BIT         4
USERCTRL_DMP_RESET_BIT          3
USERCTRL_FIFO_RESET_BIT         2
USERCTRL_I2C_MST_RESET_BIT      1
USERCTRL_SIG_COND_RESET_BIT     0

PWR2_LP_WAKE_CTRL_BIT       7
PWR2_LP_WAKE_CTRL_LENGTH    2
PWR2_STBY_XA_BIT            5
PWR2_STBY_YA_BIT            4
PWR2_STBY_ZA_BIT            3
PWR2_STBY_XG_BIT            2
PWR2_STBY_YG_BIT            1
PWR2_STBY_ZG_BIT            0

WAKE_FREQ_1P25      0x0
WAKE_FREQ_2P5       0x1
WAKE_FREQ_5         0x2
WAKE_FREQ_10        0x3

BANKSEL_PRFTCH_EN_BIT       6
BANKSEL_CFG_USER_BANK_BIT   5
BANKSEL_MEM_SEL_BIT         4
BANKSEL_MEM_SEL_LENGTH      5

WHO_AM_I_BIT        6
WHO_AM_I_LENGTH     6

DMP_MEMORY_BANKS        8
DMP_MEMORY_BANK_SIZE    256
DMP_MEMORY_CHUNK_SIZE   16
#endif

		I2C_IO& i2c_;

		uint8_t recv_(REG reg) const {
			uint8_t tmp[1];
			tmp[0] = static_cast<uint8_t>(reg);
			i2c_.send(MPU6050_ADR_, tmp, 1);
			i2c_.recv(MPU6050_ADR_, tmp, 1);
			return tmp[0];
		}

		void send_(REG reg, uint8_t data) {
			uint8_t tmp[2];
			tmp[0] = static_cast<uint8_t>(reg);
			tmp[1] = data;
			i2c_.send(MPU6050_ADR_, tmp, 2);
		}

		void set_bit_(REG reg, uint8_t bpos, bool f) {
			uint8_t tmp[2];
			tmp[0] = static_cast<uint8_t>(reg);
			i2c_.send(MPU6050_ADR_, tmp, 1);
			i2c_.recv(MPU6050_ADR_, &tmp[1], 1);
			if(f) tmp[1] |= 1 << bpos;
			else tmp[1] &= ~(1 << bpos);
 			i2c_.send(MPU6050_ADR_, tmp, 2);
		}

		void set_bits_(REG reg, uint8_t bpos, uint8_t len, uint8_t v) {
			uint8_t tmp[2];
			tmp[0] = static_cast<uint8_t>(reg);
			i2c_.send(MPU6050_ADR_, tmp, 1);
			i2c_.recv(MPU6050_ADR_, &tmp[1], 1);
			tmp[1] &= ((1 << len) - 1) << bpos;
			tmp[1] |= v << bpos;
 			i2c_.send(MPU6050_ADR_, tmp, 2);
		}

		void get_8_(REG reg, uint8_t& v) const {
			uint8_t tmp[1];
			tmp[0] = static_cast<uint8_t>(reg);
			i2c_.send(MPU6050_ADR_, tmp, 1);
			i2c_.recv(MPU6050_ADR_, tmp, 1);
			v = tmp[0];
		}

		void get_16_(REG reg, uint16_t& v) const {
			uint8_t tmp[2];
			tmp[0] = static_cast<uint8_t>(reg);
			i2c_.send(MPU6050_ADR_, tmp, 1);
			i2c_.recv(MPU6050_ADR_, tmp, 2);
		    v = static_cast<uint16_t>((tmp[0] << 8) | tmp[1]);
		}

		void get_vec_(REG reg, int16_vec& vec) const {
			uint8_t tmp[6];
			tmp[0] = static_cast<uint8_t>(reg);
			i2c_.send(MPU6050_ADR_, tmp, 1);
			i2c_.recv(MPU6050_ADR_, tmp, 6);
		    vec.x = static_cast<int16_t>((tmp[0] << 8) | tmp[1]);
		    vec.y = static_cast<int16_t>((tmp[2] << 8) | tmp[3]);
		    vec.z = static_cast<int16_t>((tmp[4] << 8) | tmp[5]);
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	i2c	iica_io クラスを参照で渡す
		 */
		//-----------------------------------------------------------------//
		MPU6050(I2C_IO& i2c) : i2c_(i2c) { }

		void set_sleep_enable(bool f) { set_bit_(REG::PWR_MGMT_1, PWR1::SLEEP_BIT, f); }

		void set_clock_source(uint8_t source) {
			set_bits_(REG::PWR_MGMT_1, PWR1::CLKSEL_BIT, PWR1::CLKSEL_LENGTH, source);
		}

		void set_full_scale_gyro_range(uint8_t range) {
    		set_bits_(REG::GYRO_CONFIG, GYRO_CONFIG::FS_SEL_BIT, GYRO_CONFIG::FS_SEL_LENGTH, range);
		}

		void set_full_scale_accel_range(uint8_t range) {
			set_bits_(REG::ACCEL_CONFIG, ACCEL_CONFIG::AFS_SEL_BIT, ACCEL_CONFIG::AFS_SEL_LENGTH, range);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@return エラーなら「false」を返す
		 */
		//-----------------------------------------------------------------//
		bool start() {
			uint8_t sig;
			get_8_(REG::WHO_AM_I, sig);
			sig &= 0x7e;
			if(sig != (MPU6050_ADR_ & 0x7e)) return false;

			set_clock_source(CLOCK::INTERNAL);

			set_full_scale_gyro_range(GYRO_CONFIG::FS_250);

			set_full_scale_accel_range(ACCEL_CONFIG::AFS_2);

			set_sleep_enable(false);

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	加速度値を取得
			@return 加速度値
		 */
		//-----------------------------------------------------------------//
		int16_vec get_accel() const {
			int16_vec vec;
			get_vec_(REG::ACCEL_XOUT_H, vec);
			return vec;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	温度を取得（*10）
			@return 温度
		 */
		//-----------------------------------------------------------------//
		int16_t get_temp() const {
			uint16_t v;
			get_16_(REG::TEMP_OUT_H, v);
			// Temperature in degrees C = (TEMP_OUT Register Value as a signed quantity)/340 + 36.53
			return (static_cast<int16_t>(v) / 34) + 365; 
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ジャイロ値を取得
			@return ジャイロ値
		 */
		//-----------------------------------------------------------------//
		int16_vec get_gyro() const {
			int16_vec vec;
			get_vec_(REG::GYRO_XOUT_H, vec);
			return vec;
		}
	};
}


