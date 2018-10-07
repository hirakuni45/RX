#pragma once
//=====================================================================//
/*!	@file
	@brief	サークル・クラス
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

		vtx::ipos	center_;
		vtx::ipos	start_;
		vtx::ipos	term_;

		int32_t		x_;
		int32_t		y_;
		int32_t		p_;
		int32_t		radius_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクタ
		 */
		//-----------------------------------------------------------------//
		circle() noexcept :  center_(0), start_(0), term_(0),
			x_(0), y_(0), p_(0), radius_(0)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	中心を設定
			@param[in]	center	中心座標
		 */
		//-----------------------------------------------------------------//
		void set_center(const vtx::ipos& center) noexcept
		{
			center_ = center;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	開始、終点を設定（１８０度以内である事）@n
					※円にする場合「開始」と「終点」を逆にしてもう一度呼ぶ
			@param[in]	start	開始位置
			@param[in]	term	終端位置
			@return 不整合なら「false」
		 */
		//-----------------------------------------------------------------//
		bool set_start(const vtx::ipos& start, const vtx::ipos& term) noexcept
		{
			start_ = start;
			term_ = term;
			int32_t len0 = (start - center_).len();
			int32_t len1 = (term - center_).len();
			int32_t d = len0 - len1;
			if(-1 <= d && d <= 1) {
				radius_ = (len0 + len1) / 2;
				x_ = start.x;
				y_ = start.y;
//				p = (5 - radius_ * 4) / 4;
				return true;
			}
			else return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ステップ
			@return 終端なら「true」
		 */
		//-----------------------------------------------------------------//
		bool step() noexcept
		{
			int32_t x = 0;
			int32_t y = radius_;
			int32_t p = (5 - radius_ * 4) / 4;
			// circlePoints(xCenter, yCenter, x, y, pix);
			while(x < y) {
				x++;
				if(p < 0) {
					p += 2 * x + 1;
				} else {
					y--;
					p += 2 * (x - y) + 1;
				}
				// circlePoints(xCenter, yCenter, x, y, pix);
			}
			return true;
		}
	};
}
