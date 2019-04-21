#pragma once
//=====================================================================//
/*!	@file
	@brief	シーン・クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	シーン・インターフェース・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct scene {
		virtual ~scene() { }
		virtual void init() = 0;
		virtual void service() = 0;
		virtual void exit() = 0;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	シーン・ディレクター・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class scene_director {

		scene*	cur_scene_;
		scene*	new_scene_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		scene_director() : cur_scene_(nullptr), new_scene_(nullptr) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	シーンの切り替え
			@param[in]	news   シーン
		*/
		//-----------------------------------------------------------------//
		template <class T>
		void change(T& news)
		{
			new_scene_ = &news;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	サービス
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			if(new_scene_ != nullptr) {
				if(cur_scene_ != nullptr) cur_scene_->exit();
				new_scene_->init();
				cur_scene_ = new_scene_;
				new_scene_ = nullptr;
			}

			if(cur_scene_ != nullptr) {
				cur_scene_->service();
			}
		}
	};
}
