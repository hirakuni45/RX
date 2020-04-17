#pragma once
//=====================================================================//
/*!	@file
	@brief	オーディオ出力クラス @n
			アップサンプリング変換
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
		@param[in]	T	基本型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <typename T>
	struct wave_t {
		T	l_ch;
		T	r_ch;

		wave_t() noexcept { }
		wave_t(const wave_t& t) noexcept : l_ch(t.l_ch), r_ch(t.r_ch) { }
		void zero() noexcept { l_ch = 0; r_ch = 0; }
		wave_t linear(int32_t base, int32_t mod, const wave_t& back) const noexcept
		{
			wave_t tmp;
			tmp.l_ch = back.l_ch + (static_cast<int32_t>(l_ch - back.l_ch) * mod / base);
			tmp.r_ch = back.r_ch + (static_cast<int32_t>(r_ch - back.r_ch) * mod / base);
			return tmp;
		} 
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	サウンド出力クラス
		@param[in]	T		基本型
		@param[in]	BFS		fifo バッファのサイズ
		@param[in]	OUTS	出力バッファのサイズ（外部ハードウェアの仕様による）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<typename T, uint32_t BFS, uint32_t OUTS>
	class sound_out {
	public:
		typedef T value_type;
		typedef wave_t<T> WAVE;
		typedef utils::fixed_fifo<WAVE, BFS> FIFO;		

	private:

		WAVE		wave_[OUTS];
		uint32_t	w_put_;

		FIFO		fifo_;

		uint32_t	out_rate_;
		uint32_t	inp_rate_;
		uint32_t	timebase_;
		WAVE		wbase_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		sound_out() noexcept : w_put_(0), fifo_(),
			out_rate_(48'000), inp_rate_(48'000), timebase_(0), wbase_()
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	出力レート設定
			@param[in]	rate	出力レート（Hz）
			@return 正常なら「true」
		*/
		//-----------------------------------------------------------------//
		bool set_output_rate(uint32_t rate) noexcept
		{
			if(rate == 0) return false;

			out_rate_ = rate;
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レート設定 @n
					アップサンプリングのみ対応なので、出力レートより高い周波数は設定エラー
			@param[in]	rate	入力レート（Hz）
			@return 正常なら「true」
		*/
		//-----------------------------------------------------------------//
		bool set_input_rate(uint32_t rate) noexcept
		{
			if(rate == 0 || out_rate_ < rate) return false;
			if(inp_rate_ != rate) {
				timebase_ = 0;
			}
			inp_rate_ = rate;
			return true;
		}


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
			@brief	出力波形メモリアドレスのを取得
			@return 出力波形メモリのアドレス
		*/
		//-----------------------------------------------------------------//
		const WAVE* get_wave(uint32_t pos = 0) const noexcept { return &wave_[pos]; }


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
			@param[in]	num		波形メモリに移動する数（出力周期に沿った数）
			@param[in]	ofs		波形オフセット
		*/
		//-----------------------------------------------------------------//
		void service(uint32_t num, uint16_t ofs) noexcept
		{
			volatile auto len = fifo_.length();
			if(inp_rate_ == out_rate_) {
				for(uint32_t i = 0; i < num; ++i) {
					WAVE t;
					if(len > 0) {
						t = fifo_.get();
						--len;
					} else {
						t.zero();
					}
					t.l_ch += ofs;
					t.r_ch += ofs;
					wave_[w_put_] = t;
					++w_put_;
					w_put_ &= (OUTS - 1);
				}
			} else {
				uint32_t i = 0;
				auto back = wbase_;
				while(i < num) {
					if(timebase_ >= out_rate_) {
						timebase_ -= out_rate_;
						back = wbase_;
						if(len > 0) {
							wbase_ = fifo_.get();
							--len;
						} else {
							wbase_.zero();
						}
						wbase_.l_ch += ofs;
						wbase_.r_ch += ofs;
					}
					timebase_ += inp_rate_;
					wave_[w_put_] = wbase_;
///					wave_[w_put_] = back.linear(
///						static_cast<int32_t>(out_rate_), static_cast<int32_t>(timebase_), wbase_);
					++w_put_;
					w_put_ &= (OUTS - 1);
					++i;
				}
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
