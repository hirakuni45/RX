#pragma once
//=========================================================================//
/*!	@file
	@brief	FT5206 class @n
			FocalTech @n
			Capacitive Touch Panel Controller ドライバー @n
			・I2C 割り込み対応 @n
			・２点同時までのタッチ位置を補足
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cstdint>
#include "common/delay.hpp"
#include "common/vtx.hpp"

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
		struct touch_t {
			EVENT		before;	///< Touch Event (before)
			EVENT		event;	///< Touch Event
			uint8_t		id;		///< Touch ID
			vtx::spos	pos;	///< Touch Position
			vtx::spos	org;	///< Touch Down Position
			vtx::spos	end;	///< Touch Up Position

			//-------------------------------------------------------------//
			/*!
				@brief	コンストラクター
			 */
			//-------------------------------------------------------------//
			touch_t() noexcept : before(EVENT::NONE), event(EVENT::NONE), id(0),
				pos(0), org(0), end(0) { }


			//-------------------------------------------------------------//
			/*!
				@brief	ドラッグされた距離の二乗を返す
				@return ドラッグされた距離の二乗
			 */
			//-------------------------------------------------------------//
			uint32_t length_sqr() const noexcept
			{
				auto d = end - org;
				return d.x * d.x + d.y * d.y;
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

		uint8_t		touch_id_;
		uint8_t		touch_num_;
		bool		start_;
		bool		startup_;
		uint16_t	version_;
		uint8_t		chip_;
		uint8_t		touch_tmp_[12];
		touch_t		t_[2];


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
			touch_id_  = touch_tmp_[0];  // GEST_ID
			touch_num_ = touch_tmp_[1] & 0x0f;  // TD_STATUS

			t_[0].before = t_[0].event;
			t_[0].event = static_cast<EVENT>(touch_tmp_[2] >> 6);
			t_[0].id = touch_tmp_[4] >> 4;
			t_[0].pos.x = (static_cast<int16_t>(touch_tmp_[2] & 0x0F) << 8)
				| static_cast<int16_t>(touch_tmp_[3]);
			t_[0].pos.y = (static_cast<int16_t>(touch_tmp_[4] & 0x0F) << 8)
				| static_cast<int16_t>(touch_tmp_[5]);

			t_[1].before = t_[1].event;
			t_[1].event = static_cast<EVENT>(touch_tmp_[8] >> 6);
			t_[1].id = touch_tmp_[10] >> 4;
			t_[1].pos.x = (static_cast<int16_t>(touch_tmp_[8] & 0x0F) << 8)
				| static_cast<int16_t>(touch_tmp_[9]);
			t_[1].pos.y = (static_cast<int16_t>(touch_tmp_[10] & 0x0F) << 8)
				| static_cast<int16_t>(touch_tmp_[11]);

			// イベントが不正なら、無効にする。
//			if(t_[0].event == EVENT::NONE || t_[1].event == EVENT::NONE) {
//				touch_num_ = 0;
//			}
#if 1
			if(t_[0].event == EVENT::DOWN || t_[1].event == EVENT::DOWN) {
				startup_ = true;
			}
			if(!startup_) {
				touch_num_ = 0;
			}
#endif
		}


		void request_touch_() noexcept
		{
			touch_tmp_[0] = static_cast<uint8_t>(REG::GEST_ID);
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
		FT5206(I2C& i2c) noexcept : i2c_(i2c), touch_id_(0), touch_num_(0),
			start_(false), startup_(false),
			version_(0), chip_(0), touch_tmp_{ 0 }, t_{ } { }


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

			touch_num_ = 0;

			start_ = true;
			startup_ = false;

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
				return;
			}

			convert_touch_();
			request_touch_();

			for(uint8_t i = 0; i < 2; ++i) {
				if(t_[i].event == EVENT::DOWN) {
					t_[i].org = t_[i].pos;
				} else if(t_[i].event == EVENT::UP) {
					t_[i].end = t_[i].pos;
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
		const touch_t& get_touch_pos(uint8_t idx) const noexcept { return t_[idx & 1]; }
	};
}
