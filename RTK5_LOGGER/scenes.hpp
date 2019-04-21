#pragma once
//=====================================================================//
/*!	@file
	@brief	シーン総合
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/scene.hpp"

#include "scenes_base.hpp"
#include "title.hpp"
#include "root_menu.hpp"
#include "laptime.hpp"
#include "recall.hpp"
#include "setup.hpp"
#include "gps.hpp"

namespace app {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	シーン総合クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class scenes {

		typedef utils::scene_director SCDR;
		SCDR		scdr_;

		scenes_base	scenes_base_;

		title		title_;
		root_menu	root_menu_;

		laptime		laptime_;
		recall		recall_;
		setup		setup_;
		gps			gps_;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクタ
		*/
		//-------------------------------------------------------------//
		scenes() noexcept : scdr_(), scenes_base_(),
			title_(),
			root_menu_(),
			laptime_(),
			recall_(),
			setup_(),
			gps_()
		{
			scdr_.change(title_);
		}


		//-------------------------------------------------------------//
		/*!
			@brief	シーン・ベースの参照
			@return シーン・ベース
		*/
		//-------------------------------------------------------------//
		scenes_base& at_base() noexcept { return scenes_base_; }


		//-------------------------------------------------------------//
		/*!
			@brief	シーン切り替え
			@param[in]	id	新規シーン番号
		*/
		//-------------------------------------------------------------//
		void change(scenes_id id) noexcept
		{
			switch(id) {
			case scenes_id::title:
				scdr_.change(title_);
				break;
			case scenes_id::root_menu:
				scdr_.change(root_menu_);
				break;

			case scenes_id::laptime:
				scdr_.change(laptime_);
				break;
			case scenes_id::recall:
				scdr_.change(recall_);
				break;
			case scenes_id::setup:
				scdr_.change(setup_);
				break;
			case scenes_id::gps:
				scdr_.change(gps_);
				break;

			default:
				break;
			}
		}


		//-------------------------------------------------------------//
		/*!
			@brief	サービス
		*/
		//-------------------------------------------------------------//
		void service() noexcept
		{
			scdr_.service();
		}
	};
}
