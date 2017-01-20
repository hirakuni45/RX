#pragma once
//=====================================================================//
/*!	@file
	@brief	シーン・クラス
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <boost/variant.hpp>

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	シーン・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class... Args>
	class scene {

		static const int argc_ = sizeof...(Args);

		using scene_type = boost::variant<Args...>;
		scene_type cur_scene_;
		scene_type new_scene_;

		struct init_visitor {
			using result_type = void;

    		template <class T>
    		void operator()(T& x) {
				return x.init();
			}
		};

		struct service_visitor {
			using result_type = void;

    		template <class T>
    		void operator()(T& x) {
				return x.service();
			}
		};

		bool	change_;
		bool	current_;

		void init_()
		{
			init_visitor vis;
           	boost::apply_visitor(vis, new_scene_);
			cur_scene_ = new_scene_;
			current_ = true;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	start	開始時クラスのインデックス
		*/
		//-----------------------------------------------------------------//
		scene() : change_(false), current_(false) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	チェンジ・シーン
			@param[in]	T	型
			@param[in]	new_scene	新規シーンのインスタンス
		*/
		//-----------------------------------------------------------------//
		template <class T>
		void change(T scene)
		{
			new_scene_ = scene;
			change_ = true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	サービス
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			if(change_) {
				init_();
				change_ = false;
			}

			if(current_) {
				service_visitor vis;
    	       	boost::apply_visitor(vis, cur_scene_);
			}
		}
	};
}
