#pragma once
//=====================================================================//
/*!	@file
	@brief	サウンド・マネージャー @n
			登録した PCM 波形データの発音制御 @n
			非常にシンプルな構成で、基本的な動作のみ実装
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <memory>
#include "sound/wav_in.hpp"

namespace sound {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  サウンド・マネージャー・クラス
		@param[in]	CTXMAX	最大登録数
		@param[in]	SNDMAX	同時発音数
		@param[in]	RDRLEN	レンダリング・バッファ長さ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t CTXMAX, uint32_t SNDMAX, uint32_t RDRLEN>
	class snd_mgr {

		typedef std::shared_ptr<const int8_t> WAV_PTR;

		struct ctx_t {
			WAV_PTR		org_;
			uint32_t	len_;
			ctx_t() : org_(), len_(0) { }
		};
		ctx_t	ctx_[CTXMAX];

		struct snd_t {
			uint32_t	ctx_;
			uint32_t	pos_;
			bool		loop_;
			snd_t() : ctx_(CTXMAX), pos_(0), loop_(false) { }
		};
		snd_t	snd_[SNDMAX];

		int16_t	final_[RDRLEN];

		uint32_t	dec_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		snd_mgr() noexcept : dec_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  最大登録数を取得
			@return	最大登録数
		*/
		//-----------------------------------------------------------------//
		uint32_t context_max() const noexcept { return CTXMAX; }


		//-----------------------------------------------------------------//
		/*!
			@brief  最大発音数を取得
			@return	最大発音数
		*/
		//-----------------------------------------------------------------//
		uint32_t sound_max() const noexcept { return SNDMAX; }


		//-----------------------------------------------------------------//
		/*!
			@brief  サウンド・コンテキストの登録（８ビット）
			@param[in]	org	サウンド・データ先頭
			@param[in]	len	サウンド・データ長さ（バイト）
			@return	コンテキストのハンドル
		*/
		//-----------------------------------------------------------------//
		uint32_t set_sound(const int8_t* org, uint32_t len)
		{
			for(uint32_t i = 0; i < CTXMAX; ++i) {
				if(ctx_[i].len_ == 0) {
					ctx_[i].org_ = WAV_PTR(org);
					ctx_[i].len_ = len;
					return i;
				}
			}
			return CTXMAX;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サウンド・コンテキストの登録
			@param[in]	filename	ファイル名
			@return	コンテキストハンドル
		*/
		//-----------------------------------------------------------------//
		uint32_t set_sound(const char* filename)
		{
			utils::file_io in;
			if(!in.open(filename, "rb")) {
				return CTXMAX;
			}

			wav_in wav;
			tag_t tag;
			if(!wav.load_header(in, tag)) {
				in.close();
				return false;
			}

			utils::format("Rate: %d, Bits: %d\n") % wav.get_rate() % wav.get_bits();

			if(!in.seek(utils::file_io::SEEK::SET, wav.get_top())) {
				in.close();
				return false;
			}

			uint32_t len = wav.get_size();
			int8_t* org = new int8_t[len];
			if(in.read(org, len) != len) {
				in.close();
				return CTXMAX;
			}
			in.close();
			for(uint32_t i = 0; i < len; ++i) {
				org[i] ^= 0x80;
			}

			return set_sound(org, len);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サウンド・リクエスト
			@param[in]	ctxhnd	コンテキスト・ハンドル
			@param[in]	loop	ループの場合「true」
			@return	発音ハンドル
		*/
		//-----------------------------------------------------------------//
		uint32_t request(uint32_t ctxhnd, bool loop = false) noexcept
		{
			if(ctxhnd >= CTXMAX) return SNDMAX;

			for(uint32_t i = 0; i < SNDMAX; ++i) {
				if(snd_[i].ctx_ < CTXMAX) {
					continue;
				}
				snd_[i].ctx_  = ctxhnd;
				snd_[i].pos_  = 0;
				snd_[i].loop_ = loop;
				return i;
			}
			return SNDMAX;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サウンド停止
			@param[in]	sndhnd	発音ハンドル
			@return	成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool stop(uint32_t sndhnd) noexcept
		{
			if(sndhnd >= SNDMAX) return false;

			snd_t& snd = snd_[sndhnd];
			if(snd.ctx_ < CTXMAX) {
				snd.ctx_ = CTXMAX;
				return true;
			} else {
				return false;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サウンド・ステータス
			@param[in]	sndhnd	発音ハンドル
			@return	発音中なら「true」
		*/
		//-----------------------------------------------------------------//
		bool status(uint32_t sndhnd) const noexcept
		{
			if(sndhnd >= SNDMAX) return false;

			const snd_t& snd = snd_[sndhnd];
			return snd.ctx_ < CTXMAX;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サウンドバッファを更新
			@param[in]	dec	レンダリング数のマイナス調整
		*/
		//-----------------------------------------------------------------//
		void update(uint32_t dec = 0) noexcept
		{
			dec_ = dec;

			for(uint32_t i = 0; i < (RDRLEN - dec); ++i) {
				final_[i] = 0;
			}

			for(uint32_t i = 0; i < (SNDMAX - dec); ++i) {
				snd_t& snd = snd_[i];
				if(snd.ctx_ >= CTXMAX) {
					continue;
				}
				ctx_t& ctx = ctx_[snd.ctx_];
				const int8_t* org = ctx.org_.get();
				for(uint32_t j = 0; j < RDRLEN; ++j) {
					if(snd.pos_ >= ctx.len_) {
						if(snd.loop_) {
							snd.pos_ = 0;
						} else {
							snd.ctx_ = CTXMAX;
						}
						break;
					}
					final_[j] += org[snd.pos_];
					++snd.pos_;
				}
			}

			// 最終ゲイン調整
			for(uint32_t i = 0; i < (RDRLEN - dec); ++i) {
				final_[i] *= 256 / SNDMAX;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サウンドバッファ・サイズの取得
			@return	サウンドバッファ・サイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t get_length() const noexcept {
			return RDRLEN - dec_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サウンドバッファの取得（最終）
			@return	サウンドバッファ
		*/
		//-----------------------------------------------------------------//
		const int16_t* get_buffer() const noexcept {
			return final_;
		}
	};
}
