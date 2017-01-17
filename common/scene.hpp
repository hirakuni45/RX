#pragma once
//=====================================================================//
/*!	@file
	@brief	シーン・クラス
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>
#include <functional>

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	シーン・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class BASE>
	class scene {

		BASE&	base_;

		typedef std::function< void(BASE&) > func_type;

		func_type	init_;
		func_type	service_;	

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		scene(BASE& base) : base_(base) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	サービス
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			if(init_ != nullptr) {
				init_(base_);
				init_ = nullptr;
			}
			if(service_ != nullptr) {
				service_(base_);
			}
		}
	};
}
