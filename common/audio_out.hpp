#pragma once
//=====================================================================//
/*!	@file
	@brief	オーディオ出力クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/fixed_fifo.hpp"

namespace audio {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	オーディオ出力構造体
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct wave_t {
		uint16_t	l_ch;
		uint16_t	r_ch;

		wave_t() { }
		void zero() noexcept { l_ch = r_ch = 0x8000; }
	};

}

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	オーディオ出力クラス
		@param[in]	BFS		fifo バッファのサイズ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<uint32_t BFS>
	class audio_out {
	public:

		typedef utils::fixed_fifo<audio::wave_t, BFS> FIFO;		

	private:

		audio::wave_t	wave_[1024];
		uint32_t	w_put_;

		FIFO		fifo_;

	public:
		audio_out() noexcept : w_put_(0), fifo_() { }

		void mute() noexcept
		{
			for(uint32_t i = 0; i < 1024; ++i) {
				wave_[i].zero();
			}
		}

		FIFO& at_fifo() noexcept { return fifo_; }

		audio::wave_t* get_wave(uint32_t pos = 0) noexcept { return &wave_[pos]; }

		uint32_t size() const noexcept { return 1024; }

		void start(uint32_t org) noexcept
		{
			w_put_ = org & 1023;
		}

		void service(uint32_t num) noexcept
		{
			if(fifo_.length() < num) return;

			for(uint32_t i = 0; i < num; ++i) {
				wave_[w_put_] = fifo_.get();
				wave_[w_put_].l_ch ^= 0x8000;
				wave_[w_put_].r_ch ^= 0x8000;
				++w_put_;
				w_put_ &= 1023;
			}
		}
	};
}
