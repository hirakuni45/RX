#pragma once
//=====================================================================//
/*!	@file
	@brief	VT100 ユーティリティー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/vtx.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  VT100 ユーティリティー
		@param[in]	SCI_IO	シリアル通信制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SCI_IO>
	class VT100 {
	public:

	private:

		SCI_IO&		sci_io_;

		vtx::spos	pos_;
		vtx::spos	limit_;

		void decimal_(uint16_t val) noexcept
		{
			char tmp[5];
			uint16_t i = 0;
			while(val > 0) {
				tmp[i] = (val % 10) + '0';
				val /= 10;
				++i;
			}
			if(i == 0) {
				tmp[i] = '0';
				++i;
			}
			while(i > 0) {
				--i;
				sci_io_.putch(tmp[i]);
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクタ
			@param[in]	sci_io	シリアル通信制御クラス
		*/
		//-----------------------------------------------------------------//
		VT100(SCI_IO& sci_io) : sci_io_(sci_io), pos_(0), limit_(80, 24)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	カーソル位置を取得
			@return カーソル位置
		*/
		//-----------------------------------------------------------------//
		const vtx::spos& get_cursor() const noexcept { return pos_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	カーソル位置を設定
			@param[in]	pos		カーソル位置
			@return 正常なら「true」
		*/
		//-----------------------------------------------------------------//
		bool set_cursor(const vtx::spos& pos) noexcept
		{
			if(pos.x < 0 || pos.y < 0 || pos.x >= limit_.x || pos.y > limit_.y) {
				return false;
			}

			sci_io_.putch(0x1b);
			sci_io_.putch('[');
			decimal_(pos.x);
			sci_io_.putch(';');
			decimal_(pos.y);
			sci_io_.putch('H');

			pos_ = pos;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
		*/
		//-----------------------------------------------------------------//
		void start() noexcept
		{
			sci_io_.putch(0x1b);
			sci_io_.putch('[');
			sci_io_.putch('2');
			sci_io_.putch('J');

			set_cursor(vtx::spos(0));
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	画面クリア
			@param[in]	begin	開始から
			@param[in]	end		終端まで
		*/
		//-----------------------------------------------------------------//
		void clear(bool begin = true, bool end = true) noexcept
		{
			char ch = '0';

			sci_io_.putch(0x1b);
			sci_io_.putch('[');
			sci_io_.putch(ch);
			sci_io_.putch('J');
		}
	};
};
