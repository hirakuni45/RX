#pragma once
//=====================================================================//
/*!	@file
	@brief	オーディオ出力クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/fixed_fifo.hpp"

namespace sound {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	オーディオ出力構造体
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct wave_t {
		uint16_t	l_ch;
		uint16_t	r_ch;

		wave_t() noexcept { }
		void zero() noexcept { l_ch = r_ch = 0x8000; }
	};
}


namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	サウンド出力クラス
		@param[in]	BFS		fifo バッファのサイズ
		@param[in]	OUTS	出力バッファのサイズ @n
							２のＮ乗サイズ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<uint32_t BFS, uint32_t OUTS>
	class sound_out {
	public:

		typedef sound::wave_t WAVE;
		typedef utils::fixed_fifo<WAVE, BFS> FIFO;		

	private:

		WAVE		wave_[OUTS];
		uint32_t	w_put_;

		FIFO		fifo_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		sound_out() noexcept : w_put_(0), fifo_()
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	ミュート
		*/
		//-----------------------------------------------------------------//
		void mute() noexcept
		{
			fifo_.clear();
			for(uint32_t i = 0; i < OUTS; ++i) {
				wave_[i].zero();
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	FIFO の参照
			@return FIFO
		*/
		//-----------------------------------------------------------------//
		FIFO& at_fifo() noexcept { return fifo_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	波形の取得
			@return 波形
		*/
		//-----------------------------------------------------------------//
		sound::wave_t* get_wave(uint32_t pos = 0) noexcept { return &wave_[pos]; }


		//-----------------------------------------------------------------//
		/*!
			@brief	波形サイズの取得
			@return 波形サイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t size() const noexcept { return OUTS; }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@param[in]	org	先頭位置
		*/
		//-----------------------------------------------------------------//
		void start(uint32_t org) noexcept
		{
			w_put_ = org & (OUTS - 1);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	サービス
			@param[in]	num	波形メモリに移動する数
		*/
		//-----------------------------------------------------------------//
		void service(uint32_t num) noexcept
		{
			if(fifo_.length() < num) return;

			for(uint32_t i = 0; i < num; ++i) {
				wave_[w_put_] = fifo_.get();
				wave_[w_put_].l_ch ^= 0x8000;
				wave_[w_put_].r_ch ^= 0x8000;
				++w_put_;
				w_put_ &= (OUTS - 1);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	波形メモリの位置を返す
			@return 波形メモリの位置
		*/
		//-----------------------------------------------------------------//
		auto get_wave_pos() const { return w_put_; }
	};
}
