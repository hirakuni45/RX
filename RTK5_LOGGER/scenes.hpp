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

namespace app {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	シーン総合クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class scenes {

		typedef utils::scene<title, root_menu> SCENE;

		SCENE		scene_;

		title		title_;
		root_menu	root_menu_;

		scenes_base	scenes_base_;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクタ
		*/
		//-------------------------------------------------------------//
		scenes() noexcept { scene_.change(title_); }


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
				scene_.change(title_);
				break;
			case scenes_id::root_menu:
				scene_.change(root_menu_);
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
			scene_.service();
		}
	};
}
