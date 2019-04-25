#pragma once
//=====================================================================//
/*!	@file
	@brief	シーン・クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>
#include <tuple>

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	シーン・インターフェース・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct scene {
		virtual ~scene() { }		///< デストラクタ
		virtual void init() = 0;	///< シーン開始前処理
		virtual void service() = 0;	///< シーン・サービス
		virtual void exit() = 0;	///< シーン終了処理
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	シーン・ディレクター・クラス
		@param[in]	Args	管理するシーンの全て
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class... Args>
	class scene_director {

		typedef std::tuple<Args...> SCENES;
		SCENES	scenes_;

		scene*	cur_scene_;
		scene*	new_scene_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		scene_director() noexcept : scenes_(), cur_scene_(nullptr), new_scene_(nullptr)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始（最初の型シーン）
		*/
		//-----------------------------------------------------------------//
		void start_first() noexcept
		{
			auto& t = std::get<0>(scenes_);
			new_scene_ = &t;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	シーンの切り替え
			@param[in]	news   シーン
		*/
		//-----------------------------------------------------------------//
		template <class T>
		void change() noexcept
		{
			auto& news = std::get<T>(scenes_);
			new_scene_ = &news;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	サービス
		*/
		//-----------------------------------------------------------------//
		void service() noexcept
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
