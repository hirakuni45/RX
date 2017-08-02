#pragma once
//=====================================================================//
/*! @file
    @brief  サンプリング・クラス
	@copyright Copyright 2017 Kunihito Hiramatsu All Right Reserved.
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <map>
#include <complex>
#include "common/format.hpp"
#include "common/time.h"

namespace seeda {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  サンプリング・ホルダー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct sample_t {

		enum class mode : uint8_t {
			none,	///< 無変換
			real,	///< 係数変換
			abs,	///< 絶対値変換
		};

		float		gain_;				///< 係数変換ゲイン
///		float		offset_;			///< 係数オフセット

		uint32_t	limit_lo_count_;	///< lo を超えた数
		uint32_t	limit_hi_count_;	///< hi を超えた数
		uint16_t	limit_lo_level_;	///< lo レベル
		uint16_t	limit_hi_level_;	///< hi レベル
		uint16_t	center_;

		uint16_t	ch_;
		mode		mode_;
		bool		signal_;
		uint16_t	min_;
		uint16_t	max_;
		uint16_t	average_;
		uint16_t	median_;

		sample_t() :
			gain_(1024.0f),
			limit_lo_count_(0), limit_hi_count_(0), limit_lo_level_(30000), limit_hi_level_(40000),
			center_(0),
			ch_(0), mode_(mode::none), signal_(false),
			min_(0), max_(0), average_(0), median_(0) { }


		void value_convert(uint16_t value, char* dst, uint32_t size) const
		{
			switch(mode_) {
			case mode::real:
				{
					int32_t v = static_cast<int32_t>(value) - static_cast<int32_t>(center_);
					float a = static_cast<float>(v) / 65535.0f * gain_;
					utils::sformat("%3.2f", dst, size, true) % a;
				}
				break;
			case mode::abs:
				{
					float a = static_cast<float>(value) / 65535.0f * gain_;
					utils::sformat("%3.2f", dst, size, true) % a;
				}
				break;
			default:
				utils::sformat("%d", dst, size, true) % value;
				break;
			}
		}


		void make_csv(char* dst, uint32_t size, bool append) const
		{
			static const char* modes[] = { "value", "real", "abs" };

			utils::sformat("%d,%s", dst, size, append) % ch_ % modes[static_cast<uint32_t>(mode_)];
			utils::sformat(",",     dst, size, true);
			value_convert(min_,     dst, size);
			utils::sformat(",",     dst, size, true);
			value_convert(max_,     dst, size);
			utils::sformat(",",     dst, size, true);
			value_convert(average_, dst, size);
			utils::sformat("%d,",   dst, size, true) % static_cast<uint32_t>(limit_lo_level_);
			utils::sformat("%d,",   dst, size, true) % static_cast<uint32_t>(limit_lo_count_);
			utils::sformat("%d,",   dst, size, true) % static_cast<uint32_t>(limit_hi_level_);
			utils::sformat("%d,",   dst, size, true) % static_cast<uint32_t>(limit_hi_count_);
			value_convert(median_,  dst, size);
		}


		void make_csv2(char* dst, uint32_t size, bool append) const
		{
			uint32_t count = limit_lo_count_ + limit_hi_count_;

			utils::sformat("%d,",   dst, size, append) % ch_;
			value_convert(max_,     dst, size);
			utils::sformat(",",     dst, size, true);
			value_convert(min_,     dst, size);
			utils::sformat(",",     dst, size, true);
			value_convert(average_, dst, size);
			utils::sformat(",",     dst, size, true);
			value_convert(median_,  dst, size);
			utils::sformat(",%u",   dst, size, true) % count;
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  サンプル・データ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct sample_data {
		time_t		time_;
		sample_t	smp_[8];
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  サンプリング・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class sample {

		sample_t	t_;

		uint32_t	sum_;
		uint32_t	count_;

		typedef std::map<uint16_t, uint16_t> MAP;
		MAP		map_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		sample() : t_(), sum_(0), count_(0), map_() { }


		//-----------------------------------------------------------------//
		/*!
			@brief  クリア
		*/
		//-----------------------------------------------------------------//
		void clear()
		{
			sum_ = 0;
			count_ = 0;

			t_.min_ = 65535;
			t_.max_ = 0;
			t_.average_ = 0;
			t_.median_ = 0;
			t_.limit_lo_count_ = 0;
			t_.limit_hi_count_ = 0;

			map_.clear();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  追加
			@param[in]	data	データ
		*/
		//-----------------------------------------------------------------//
		void add(uint16_t data)
		{
			if(t_.mode_ == sample_t::mode::abs) {
				if(data >= t_.center_) data -= t_.center_;
				else data = t_.center_ - data;
			}

			sum_ += data;
			++count_;
			if(t_.min_ > data) t_.min_ = data;
			if(t_.max_ < data) t_.max_ = data;

			if(t_.limit_hi_level_ < data) ++t_.limit_hi_count_;
			if(t_.limit_lo_level_ > data) ++t_.limit_lo_count_;

			auto ret = map_.emplace(data, 1);
			if(!ret.second) {
				auto& v = ret.first;
				++v->second;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  主に median の計算
		*/
		//-----------------------------------------------------------------//
		void collect()
		{
			uint32_t med = 0;
			uint32_t sum = 0;

			for(MAP::iterator it = map_.begin(); it != map_.end(); ++it) {
				uint32_t cnt = it->second;
				sum += cnt;
				if(sum >= (count_ / 2)) {
					med = it->first;
					if((count_ & 1) == 0) {
						++it;
						if(it == map_.end()) {  // 要素数が１個の場合は、平均しない
							break;
						}
						med += static_cast<uint32_t>(it->first);
						med /= 2;
					}
					break;
				}
			}

			t_.median_ = med;

			t_.average_ = sum_ / count_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  結果取得
			@return 結果
		*/
		//-----------------------------------------------------------------//
		const sample_t& get() const { return t_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  結果参照
			@return 結果
		*/
		//-----------------------------------------------------------------//
		sample_t& at() { return t_; }
	};
}
