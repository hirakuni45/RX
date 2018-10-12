#pragma once
//=====================================================================//
/*!	@file
	@brief	サークル・クラス @n
			・XY プロッタ(CNC)用の円周位置を生成するクラス @n
			・XY 座標は、一般的数学的座標系を使う。 @n
			・入出力は整数で行い、桁落ちなどの対策を行う。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/glfw_app/blob/master/LICENSE
*/
//=====================================================================//
#include "common/vtx.hpp"

namespace imath {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	円クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class circle {

		vtx::ipos	start_;
		vtx::ipos	center_;
		vtx::ipos	term_;

		vtx::ipos	pos_;
		vtx::ipos	fin_;
		int32_t		rad_;
		int32_t		rad_sqr_;
		int32_t		oct_;

		bool		cw_;

		static int32_t octant_(const vtx::ipos& p) noexcept
		{
			uint32_t n = 0;
			if(std::abs(p.x) > std::abs(p.y)) n |= 0b001;
			if(p.x < 0) n |= 0b100;
			if(p.y < 0) n |= 0b010;
			static const int8_t map[8] = {
				0, 1, 3, 2, 7, 6, 4, 5
			};
			return map[n];
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクタ
		 */
		//-----------------------------------------------------------------//
		circle() noexcept :  start_(0), center_(0), term_(0),
			pos_(0), fin_(0), rad_(0), rad_sqr_(0), oct_(0), cw_(true)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	角度に対する座標
			@param[in]	an	角度（０～１．０）@n
							※０：３時、０．２５：６時、０．５：９時、０．７５：１２時
			@param[in]	rad	半径
		 */
		//-----------------------------------------------------------------//
		static vtx::ipos angle_to_position(float an, int32_t rad) noexcept
		{
			vtx::ipos pos;
			pos.x = cosf(an * vtx::radian_f_) * static_cast<float>(rad);
			pos.y = sinf(an * vtx::radian_f_) * static_cast<float>(rad);
			return pos;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	機能テスト用
		 */
		//-----------------------------------------------------------------//
		void func_test() noexcept
		{
			{
				float an = 0.0f;
				for(int32_t i = 0; i < 20; ++i) {
					auto pos = angle_to_position(an, 10 * 2);
					auto len = pos.len();
					++len;
					len /= 2;
					utils::format("%5.4f %d\n") % an % len;
					an += 0.05f;
				}
			}

			{
				float an = 1.0f / 4.0f;
				an -= 1.0f / 16.0f;
				for(uint32_t i = 0; i < 8; ++i) {
					auto pos = angle_to_position(an, 100);
					auto n = octant_(pos);
					utils::format("%d\n") % n;
					an -= 1.0f / 8.0f;
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	開始、終点を設定（１８０度以内である事）@n
					※円にする場合「開始」と「終点」を逆にしてもう一度呼ぶ
			@param[in]	sta	開始位置
			@param[in]	cen	中心位置
			@param[in]	fin	終端位置
			@param[in]	cw	反時計方向なら「false」
			@return 不整合なら「false」
		 */
		//-----------------------------------------------------------------//
		bool start(const vtx::ipos& sta, const vtx::ipos& cen, const vtx::ipos& fin, bool cw = true) noexcept
		{
			vtx::ipos d0 = sta - cen;
			vtx::ipos d1 = fin - cen;
			d0 *= 2;
			d1 *= 2;
			int32_t len0 = d0.len();
			++len0;
			len0 /= 2;
			int32_t len1 = d1.len();
			++len1;
			len1 /= 2;
			if(len0 != len1) {
				return false;
			}
			start_  = sta;
			center_ = cen;
			term_   = fin;
			cw_ = cw;
			oct_ = octant_(d1);

			rad_ = len0 * 2;
			rad_sqr_ = rad_ * rad_;
			pos_.x = d0.x;
			pos_.y = d0.y;
			fin_.x = d1.x;
			fin_.y = d1.y;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ステップ
			@return 終端なら「true」
		 */
		//-----------------------------------------------------------------//
		bool step() noexcept
		{
			bool limit = false;
			auto oct = octant_(pos_);
			switch(oct) {
			case 0:
			case 7:
				if(cw_) pos_.x += 2;
				else pos_.x -= 2;
				pos_.y = std::sqrt(rad_sqr_ - pos_.x * pos_.x);
				break;
			case 1:
			case 2:
				if(cw_) pos_.y -= 2;
				else pos_.y += 2;
				pos_.x = std::sqrt(rad_sqr_ - pos_.y * pos_.y);
				break;
			case 3:
			case 4:
				if(cw_) pos_.x -= 2;
				else pos_.x += 2;
				pos_.y = -std::sqrt(rad_sqr_ - pos_.x * pos_.x);
				break;
			case 5:
			case 6:
				if(cw_) pos_.y += 2;
				else pos_.y -= 2;
				pos_.x = -std::sqrt(rad_sqr_ - pos_.y * pos_.y);
				break;
			}
			if(oct != oct_) return false;

			switch(oct_) {
			case 0:
			case 1:
				if(cw_) {
					if(pos_.x >= fin_.x && pos_.y <= fin_.y) limit = true;
				} else {
					if(pos_.x <= fin_.x && pos_.y >= fin_.y) limit = true;
				}
				break;
			case 2:
			case 3:
				if(cw_) {
					if(pos_.x <= fin_.x && pos_.y <= fin_.y) limit = true;
				} else {
					if(pos_.x >= fin_.x && pos_.y >= fin_.y) limit = true;
				}
				break;
			case 4:
			case 5:
				if(cw_) {
					if(pos_.x <= fin_.x && pos_.y <= fin_.y) limit = true;
				} else {
					if(pos_.x >= fin_.x && pos_.y >= fin_.y) limit = true;
				}
				break;
			case 6:
			case 7:
				if(cw_) {
					if(pos_.x >= fin_.x && pos_.y >= fin_.y) limit = true;
				} else {
					if(pos_.x <= fin_.x && pos_.y <= fin_.y) limit = true;
				}
				break;
			}

			return limit;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	生成された位置を取得
			@return 生成された位置
		 */
		//-----------------------------------------------------------------//
		vtx::ipos get_position() const noexcept
		{
			vtx::ipos p;
			p.x = (pos_.x + 1) / 2 + center_.x;
			p.y = (pos_.y + 1) / 2 + center_.y;
			return p;
		}
	};
}
