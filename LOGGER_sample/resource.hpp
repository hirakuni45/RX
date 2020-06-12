#pragma once
//=====================================================================//
/*!	@file
    @brief  LOGGER リソース
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/format.hpp"
#include "graphics/bmp_in.hpp"

namespace app {

	extern const uint8_t* nmb24[];

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	リソース・クラス
		@param[in]	RENDER	描画クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class RENDER>
	class resource {

		RENDER&	render_;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	render	RENDER クラス（参照）
		*/
		//-------------------------------------------------------------//
		resource(RENDER& render) : render_(render) { }


		//-----------------------------------------------------------------//
		/*!
			@breif	２４ピクセルキャラクター表示
			@param[in]	pos	位置
			@param[in]	ch	キャラクター・コード
		*/
		//-----------------------------------------------------------------//
		void draw_nmb_24(const vtx::spos& pos, char ch) noexcept
		{
			if(ch >= '0' && ch <= '9') {
				render_.draw_mobj(pos, nmb24[ch - '0'], true);
			} else if(ch == ':') {
				render_.draw_mobj(pos, nmb24[10], true);
			} else if(ch == '.') {
				render_.draw_mobj(pos, nmb24[11], true);
			} else if(ch == 'X' || ch == 'x') {
				render_.draw_mobj(pos, nmb24[12], true);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	２４ピクセル文字列表示
			@param[in]	pos	位置
			@param[in]	str	文字列
			@return 描画後のＸ座標
		*/
		//-----------------------------------------------------------------//
		int16_t draw_nmb_24(const vtx::spos& pos, const char* str) noexcept
		{
			if(str == nullptr) return pos.x;

			char ch;
			auto loc = pos;
			while((ch = *str) != 0) {
				draw_nmb_24(loc, ch);
				loc.x += 20;
				++str;
			}
			return loc.x;
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	２４ピクセルカウント表示
			@param[in]	pos	位置
			@param[in]	cnt	カウント
			@return 描画後のＸ座標
		*/
		//-----------------------------------------------------------------//
		int16_t draw_count(const vtx::spos& pos, uint16_t cnt) noexcept
		{
			char tmp[4];
			utils::sformat("%03d ", tmp, sizeof(tmp)) % (cnt % 1000);
			return draw_nmb_24(pos, tmp);
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	２４ピクセル時間表示 (HH:MM:SS.LL)
			@param[in]	x	Ｘ軸位置
			@param[in]	y	Ｙ軸位置
			@param[in]	t	時間（1/100 秒単位）
			@return 描画後のＸ座標
		*/
		//-----------------------------------------------------------------//
		int16_t draw_hmsl(const vtx::spos& pos, uint32_t t) noexcept
		{
			auto mod = t % 100;
			t /= 100;
			auto sec = t % 60;
			t /= 60;
			auto min = t % 60;
			t /= 60;
			auto hur = t % 24;
			char tmp[16];
			utils::sformat("%02d:%02d:%02d.%02d", tmp, sizeof(tmp))
				% hur % min % sec % mod;
			return draw_nmb_24(pos, tmp);
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	２４ピクセル時間表示 (MM:SS.LL)
			@param[in]	pos	位置
			@param[in]	t	時間（1/100 秒単位）
			@return 描画後のＸ座標
		*/
		//-----------------------------------------------------------------//
		int16_t draw_msl(const vtx::spos& pos, uint32_t t) noexcept
		{
			auto mod = t % 100;
			t /= 100;
			auto sec = t % 60;
			t /= 60;
			auto min = t % 100;
			char tmp[12];
			utils::sformat("%02d:%02d.%02d", tmp, sizeof(tmp))
				% min % sec % mod;
			return draw_nmb_24(pos, tmp);
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	ラップステート表示 (NN HH::MM:SS HH::MM::SS)
			@param[in]	pos	位置
			@param[in]	n	回数
			@param[in]	t	現在時間（1/100 秒単位）
			@param[in]	d	経過時間（1/100 秒単位）
			@return 描画後のＸ座標
		*/
		//-----------------------------------------------------------------//
		int16_t draw_lap_state(const vtx::spos& pos, uint16_t n, uint32_t t, uint32_t d) noexcept
		{
			char tmp[16];
			utils::sformat("%03d", tmp, sizeof(tmp)) % (n % 1000);
			auto loc = pos;
			loc.x = draw_nmb_24(loc, tmp);
			loc.x += 20;
			// 現在時間の 1/100 は表示しない
			t /= 100;
			auto sec = t % 60;
			t /= 60;
			auto min = t % 60;
			t /= 60;
			auto hur = t % 24;
			utils::sformat("%02d:%02d:%02d", tmp, sizeof(tmp)) % hur % min % sec;
			loc.x = draw_nmb_24(loc, tmp);
			loc.x += 20;
			auto mod = d % 100;
			d /= 100;
			sec = d % 60;
			d /= 60;
			min = d % 60;
//			d /= 60;
//			hur = d % 24;
			utils::sformat("%02d:%02d.%02d", tmp, sizeof(tmp)) % min % sec % mod;
			return draw_nmb_24(loc, tmp);
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	２４ピクセルフルラップ表示 (NNN HH::MM:SS.LL)
			@param[in]	pos	位置
			@param[in]	n	回数
			@param[in]	t	時間（1/100 秒単位）
			@return 描画後のＸ座標
		*/
		//-----------------------------------------------------------------//
		int16_t draw_full_lap(const vtx::spos& pos, uint16_t n, uint32_t t) noexcept
		{
			auto mod = t % 100;
			t /= 100;
			auto sec = t % 60;
			t /= 60;
			auto min = t % 60;
			t /= 60;
			auto hur = t % 24;
			char tmp[16];
			utils::sformat("%03d %02d:%02d:%02d.%02d", tmp, sizeof(tmp))
				% n % hur % min % sec % mod;
			return draw_nmb_24(pos, tmp);
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	２４ピクセルショートラップ表示 (NNN M:SS.LL)
			@param[in]	pos	位置
			@param[in]	n	回数
			@param[in]	t	時間（1/100 秒単位）
			@return 描画後のＸ座標
		*/
		//-----------------------------------------------------------------//
		int16_t draw_short_lap(const vtx::spos& pos, uint16_t n, uint32_t t) noexcept
		{
			auto mod = t % 100;
			t /= 100;
			auto sec = t % 60;
			t /= 60;
			auto min = t;
			char mch = 'X';
			if(min < 10) mch = min + '0'; 
			char tmp[16];
			utils::sformat("%03d %c:%02d.%02d", tmp, sizeof(tmp))
				% n % mch % sec % mod;
			return draw_nmb_24(pos, tmp);
		}
	};
}
