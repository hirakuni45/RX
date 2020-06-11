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
#include "scenes_base.hpp"
#include "title.hpp"
#include "root_menu.hpp"
#include "laptime.hpp"
#include "recall.hpp"
#include "setup.hpp"
#include "gps.hpp"
#include "common/scene.hpp"

namespace app {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	シーン総合クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class scenes {

		scenes_base	scenes_base_;

		typedef utils::scene_director<title, root_menu, laptime, recall, setup, gps> SCDR;
		SCDR		scdr_;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクタ
		*/
		//-------------------------------------------------------------//
		scenes() noexcept : scenes_base_(), scdr_()
		{
			scdr_.change<title>();
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
		void change(scene_id id) noexcept
		{
			switch(id) {
			case scene_id::title:
				scdr_.change<title>();
				break;
			case scene_id::root_menu:
				scdr_.change<root_menu>();
				break;

			case scene_id::laptime:
				scdr_.change<laptime>();
				break;
			case scene_id::recall:
				scdr_.change<recall>();
				break;
			case scene_id::setup:
				scdr_.change<setup>();
				break;
			case scene_id::gps:
				scdr_.change<gps>();
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
