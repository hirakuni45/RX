#pragma once
//=====================================================================//
/*!	@file
	@brief	Chager クラス
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>
#include "common/gpt_io.hpp"
// #include "common/adc_io.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  チャージャー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class chager {
		static const int32_t low_limit_  = 8;
		static const int32_t high_limit_ = 500;

		device::gpt_io<device::GPT0>  gpt0_;
		device::gpt_io<device::GPT1>  gpt1_;

		/// device::adc_io<device::S12AD> adc_;

		int16_t		inp_;
		int16_t		volt_[4];

		struct dcdc_t {
			int32_t	cpv_;
			int32_t	out_;
			int32_t	cur_;
			int32_t	vol_ref_;	///< 電圧基準
			int32_t	cur_ref_;	///< 電流基準
			int32_t vol_lim_;	///< 電圧リミット
			int32_t cur_lim_;	///< 電流リミット
			int32_t	thr_;		///< スレッショルド電圧
			int32_t	gain_;
			dcdc_t() : cpv_(0), out_(0), cur_(0),
				vol_ref_(0), cur_ref_(0),
				vol_lim_(0), cur_lim_(0),
				thr_(0), gain_(16) { }


			int32_t const_voltage() {
				if(vol_ref_ < out_) --cpv_;
				else if(vol_ref_ > out_) ++cpv_;
	
				int32_t cmpv = cpv_ / gain_;
				if(cmpv < low_limit_) cmpv = low_limit_;
				else if(cmpv > high_limit_) cmpv = high_limit_;
				return cmpv;
			}


			int32_t const_current() {
				if(vol_lim_ < out_) {
					--cpv_;
				} else {
					if(cur_ref_ < cur_) --cpv_;
					else if(cur_ref_ > cur_) ++cpv_;
				}

				int32_t cmpv = cpv_ / gain_;
				if(cmpv < low_limit_) cmpv = low_limit_;
				else if(cmpv > high_limit_) cmpv = high_limit_;
				return cmpv;
			}


			int32_t liion_chage() {
				int32_t cmpv;
				if(thr_ < out_) {
					cmpv = const_voltage();
				} else {
					cmpv = const_current();
				}
				return cmpv;
			}

		};

		dcdc_t	chanel0_;
		dcdc_t	chanel1_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		chager() : inp_(0), volt_(), chanel0_(), chanel1_() { }


		//-----------------------------------------------------------------//
		/*!
			@brief  初期化
		*/
		//-----------------------------------------------------------------//
		void initialize();


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
		*/
		//-----------------------------------------------------------------//
		void service();


		//-----------------------------------------------------------------//
		/*!
			@brief  電圧を取得
			@param[in]	chanel	チャネル(0, 1, 2, 3)
			@return 電圧
		*/
		//-----------------------------------------------------------------//
		int32_t get_voltage(int chanel) const {
			return volt_[chanel & 3];
		}
	};
}
