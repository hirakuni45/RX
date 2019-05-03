#pragma once
//=====================================================================//
/*!	@file
	@brief	グループ制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "graphics/widget.hpp"

namespace gui {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	グループ・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct group : public widget {

		typedef group value_type;

		static const uint32_t CNUM = 16;

	private:
		widget*		child_[CNUM];
		uint32_t	count_;

		void insert_(widget* w) {
			if(count_ < CNUM) {
				child_[count_] = w;
				++count_;
			}
		} 

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	loc		ロケーション
			@param[in]	str		フレーム・タイトル
		*/
		//-----------------------------------------------------------------//
		group(const vtx::srect& loc = vtx::srect(0), const char* str = "") noexcept :
			widget(loc, str), child_{ nullptr }, count_(0)
		{
			insert_widget(this);
		}


		group(const group& th) = delete;
		group& operator = (const group& th) = delete;


		//-----------------------------------------------------------------//
		/*!
			@brief	デストラクタ
		*/
		//-----------------------------------------------------------------//
		virtual ~group() noexcept { remove_widget(this); }


		//-----------------------------------------------------------------//
		/*!
			@brief	型整数を取得
			@return 型整数
		*/
		//-----------------------------------------------------------------//
		const char* get_name() const noexcept override { return "Group"; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ID を取得
			@return ID
		*/
		//-----------------------------------------------------------------//
		ID get_id() const noexcept override { return ID::GROUP; }


		//-----------------------------------------------------------------//
		/*!
			@brief	初期化
		*/
		//-----------------------------------------------------------------//
		void init() noexcept override { }

		//-----------------------------------------------------------------//
		/*!
			@brief	タッチ判定を更新
			@param[in]	pos		判定位置
			@param[in]	num		タッチ数
			@param[in]	slt		スライド・タイプの場合「true」
		*/
		//-----------------------------------------------------------------//
		void update_touch(const vtx::spos& pos, uint16_t num) noexcept override { }


		//-----------------------------------------------------------------//
		/*!
			@brief	選択推移
			@param[in]	inva	無効状態にする場合「true」
		*/
		//-----------------------------------------------------------------//
		void exec_select(bool inva) noexcept override { }


		//-----------------------------------------------------------------//
		/*!
			@brief	許可・不許可
			@param[in]	ena		不許可の場合「false」
		*/
		//-----------------------------------------------------------------//
		void enable(bool ena = true) override
		{
			auto st = STATE::DISABLE;
			if(ena) {
				st = STATE::ENABLE;
			}
			set_state(st);
			for(uint32_t i = 0; i < count_; ++i) {
				child_[i]->set_state(st);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	子供のリスト数取得
			@return 子供のリスト数
		*/
		//-----------------------------------------------------------------//
		uint32_t get_child_num() const noexcept { return count_; }
 

		//-----------------------------------------------------------------//
		/*!
			@brief	子供のリスト取得
			@return 子供のリスト
		*/
		//-----------------------------------------------------------------//
		widget** get_child() noexcept { return child_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	親の設定
			@param[in]	th	子のインスタンス	
		*/
		//-----------------------------------------------------------------//
		template <class T>
		group& operator + (T& th)
		{
			th.set_parents(this);
			insert_(&th);
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	親の設定
			@param[in]	th	子のインスタンス	
		*/
		//-----------------------------------------------------------------//
		template <class T>
		group& operator += (T& th)
		{
			th.set_parents(this);
			insert_(&th);
			return *this;
		}
	};
}
