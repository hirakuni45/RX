#pragma once
//=========================================================================//
/*!	@file
	@brief	FT5206 class @n
			FocalTech @n
			Capacitive Touch Panel Controller ドライバー @n
			・I2C 割り込み対応 @n
			・２点同時までのタッチ位置を補足
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cstdint>
#include "common/delay.hpp"

namespace chip {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  FT5206 テンプレートクラス
		@param[in]	I2C	I2C 制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class I2C>
	class FT5206 {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Touch Event Type
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class EVENT : uint8_t {
			DOWN,		///< Touch Down
			UP,			///< Touch Up
			CONTACT,	///< Contact
			NONE
		};

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Touch Struct
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct xy {
			EVENT		before;	///< Touch Event (before)
			EVENT		event;	///< Touch Event
			uint8_t		id;		///< Touch ID
			int16_t		x;		///< Touch Position X
			int16_t		y;		///< Touch Position Y
			int16_t		org_x;	///< Touch Down Position X
			int16_t		org_y;	///< Touch Down Position Y
			int16_t		end_x;	///< Touch Up Position X
			int16_t		end_y;	///< Touch Up Position Y

			//-------------------------------------------------------------//
			/*!
				@brief	コンストラクター
			 */
			//-------------------------------------------------------------//
			xy() noexcept : before(EVENT::NONE), event(EVENT::NONE), id(0), x(0), y(0),
				   org_x(0), org_y(0), end_x(0), end_y(0) { }


			//-------------------------------------------------------------//
			/*!
				@brief	ドラッグされた距離の二乗を返す
				@return ドラッグされた距離の二乗
			 */
			//-------------------------------------------------------------//
			uint32_t length_sqr() const noexcept
			{
				auto dx = end_x - org_x;
				auto dy = end_y - org_y;
				return dx * dx + dy * dy;
			} 
		};

	private:

		static const uint8_t	FT5206_ADR = 0x38;

		I2C&	i2c_;

		enum class REG : uint8_t {
			DEVICE_MODE,		// R/W
			GEST_ID,			// R
			TD_STATUS,			// R
			TOUCH_XH,			// R
			TOUCH_XL,			// R
			TOUCH_YH,			// R
			TOUCH_YL,			// R

			TOUCH2_XH = 0x09,	// R
			TOUCH2_XL,			// R
			TOUCH2_YH,			// R
			TOUCH2_YL,			// R

			TOUCH3_XH = 0x0F,	// R
			TOUCH3_XL,			// R
			TOUCH3_YH,			// R
			TOUCH3_YL,			// R

			TOUCH4_XH = 0x15,	// R
			TOUCH4_XL,			// R
			TOUCH4_YH,			// R
			TOUCH4_YL,			// R

			TOUCH5_XH = 0x1B,	// R
			TOUCH5_XL,			// R
			TOUCH5_YH,			// R
			TOUCH5_YL,			// R

			ID_G_THGROUP = 0x80,		// R/W
			ID_G_THPEAK,				// R/W
			ID_G_THCAL,					// R/W
			ID_G_THWATER,				// R/W
			ID_G_THTEMP,				// R/W

			ID_G_CTRL = 0x86,			// R/W
			ID_G_TIME_ENTER_MONITOR,	// R/W
			ID_G_PERIODACTIVE,			// R/W
			ID_G_PERIODMONITOR,			// R/W

			ID_G_AUTO_CLB_MODE = 0xA0,	// R/W
			ID_G_LIB_VERSION_H,			// R
			ID_G_LIB_VERSION_L,			// R
			ID_G_CIPHER,				// R
			ID_G_MODE,					// R
			ID_G_PMODE,					// R
			ID_G_FIRMID,				// R
			ID_G_STATE,					// R
			ID_G_FT5201ID,				// R
			ID_G_ERR,					// R
			ID_G_CLB,					// R/W

			ID_G_B_AREA_TH = 0xAE,		// R/W

			LOG_MSG_CNT = 0xFE,			// R
			LOG_CUR_CHA					// R
		};

		uint8_t		touch_num_;
		bool		start_;
		uint16_t	version_;
		uint8_t		chip_;
		uint8_t		touch_tmp_[11];
		xy			xy_[2];


		void write_(REG reg, uint8_t data) noexcept
		{
			uint8_t tmp[2];
			tmp[0] = static_cast<uint8_t>(reg);
			tmp[1] = data;
			i2c_.send(FT5206_ADR, tmp, sizeof(tmp));
			i2c_.sync();
		}


		uint8_t read_(REG reg) noexcept
		{
			uint8_t tmp[1];
			tmp[0] = static_cast<uint8_t>(reg);
			i2c_.send(FT5206_ADR, tmp, sizeof(tmp));
			i2c_.recv(FT5206_ADR, tmp, sizeof(tmp));
			i2c_.sync();
			return tmp[0];
		}


		void convert_touch_() noexcept
		{
			touch_num_ = touch_tmp_[0] & 0x0f;

			xy_[0].before = xy_[0].event;
			xy_[0].event = static_cast<EVENT>(touch_tmp_[1] >> 6);
			xy_[0].id = touch_tmp_[3] >> 4;
			xy_[0].x = (static_cast<int16_t>(touch_tmp_[1] & 0x0F) << 8)
				| static_cast<int16_t>(touch_tmp_[2]);
			xy_[0].y = (static_cast<int16_t>(touch_tmp_[3] & 0x0F) << 8)
				| static_cast<int16_t>(touch_tmp_[4]);

			xy_[1].before = xy_[1].event;
			xy_[1].event = static_cast<EVENT>(touch_tmp_[7] >> 6);
			xy_[1].id = touch_tmp_[9] >> 4;
			xy_[1].x = (static_cast<int16_t>(touch_tmp_[7] & 0x0F) << 8)
				| static_cast<int16_t>(touch_tmp_[8]);
			xy_[1].y = (static_cast<int16_t>(touch_tmp_[9] & 0x0F) << 8)
				| static_cast<int16_t>(touch_tmp_[10]);
		}


		void request_touch_() noexcept
		{
			touch_tmp_[0] = static_cast<uint8_t>(REG::TD_STATUS);
			i2c_.send(FT5206_ADR, touch_tmp_, 1);
			i2c_.recv(FT5206_ADR, touch_tmp_, sizeof(touch_tmp_));
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	i2c	i2c 制御クラスを参照で渡す
		 */
		//-----------------------------------------------------------------//
		FT5206(I2C& i2c) noexcept : i2c_(i2c), touch_num_(0), start_(false),
			version_(0), chip_(0), touch_tmp_{ 0 }, xy_{ } { }


		//-----------------------------------------------------------------//
		/*!
			@brief	デバイスのバージョンを取得
			@return デバイスのバージョン
		 */
		//-----------------------------------------------------------------//
		uint16_t get_version() const noexcept { return version_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	チップ・コードを取得
			@return チップ・コード
		 */
		//-----------------------------------------------------------------//
		uint8_t get_chip() const noexcept { return chip_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	デバイス・リセット
			@param[in]	RES	リセット端子
		 */
		//-----------------------------------------------------------------//
		template <class RES>
		static void reset() noexcept {
			RES::DIR = 1;
			RES::P = 0;
			utils::delay::milli_second(5);
			RES::P = 1;
			utils::delay::milli_second(300);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@return 成功なら「true」
		 */
		//-----------------------------------------------------------------//
		bool start() noexcept
		{
			uint8_t tmp[3];
			tmp[0] = static_cast<uint8_t>(REG::ID_G_LIB_VERSION_H);
			if(!i2c_.send(FT5206_ADR, tmp, 1)) {
				utils::format("Send fail\n");
				return false;
			}
			i2c_.sync();

			tmp[0] = 0xff;
			tmp[1] = 0xff;
			tmp[2] = 0xff;
			if(!i2c_.recv(FT5206_ADR, tmp, sizeof(tmp))) {
				utils::format("Recv fail\n");
				return false;
			}
			i2c_.sync();
			version_ = (static_cast<uint16_t>(tmp[0]) << 8) | tmp[1];
			chip_ = tmp[2];

			write_(REG::DEVICE_MODE, 0x00);

			start_ = true;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	アップデート
		 */
		//-----------------------------------------------------------------//
		void update() noexcept
		{
			if(!start_) {
				touch_num_ = 0;
				return;
			}

			convert_touch_();
			request_touch_();

			for(uint8_t i = 0; i < 2; ++i) {
				if(xy_[i].event == EVENT::DOWN) {
					xy_[i].org_x = xy_[i].x;
					xy_[i].org_y = xy_[i].y;
				} else if(xy_[i].event == EVENT::UP) {
					xy_[i].end_x = xy_[i].x;
					xy_[i].end_y = xy_[i].y;
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	タッチ数を取得
			@return タッチ数
		 */
		//-----------------------------------------------------------------//
		uint8_t get_touch_num() const noexcept { return touch_num_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	タッチ位置を取得
			@param[in]	idx	タッチ・インデックス（０～１）
			@return タッチ位置
		 */
		//-----------------------------------------------------------------//
		const xy& get_touch_pos(uint8_t idx) const noexcept { return xy_[idx & 1]; }
	};
}
