#pragma once
//=========================================================================//
/*!	@file
	@brief	RX700 グループ・SSIE I/O 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX600/ssie.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SSIE（シリアルサウンドインターフェース）制御クラス
		@param[in]	SSIE	ハードウェアーリソース
		@param[in]	MASTER	スレーブの場合「false」
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SSIE, bool MASTER = true>
	class ssie_io {

		typedef SSIE value_type;

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  オーディオ・フォーマット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class FORM {
			I2S_LEFT,	///< I2S 左詰め
			I2S_RIGHT,	///< I2S 右詰め
			TDM,		///< TDM フォーマット
			MONO,		///< モノラル・フォーマット
		};

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	
		*/
		//-----------------------------------------------------------------//
		ssie_io() noexcept { }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	form	オーディオ・フォーマット
		*/
		//-----------------------------------------------------------------//
		bool start(FORM form) noexcept
		{
			power_mgr::turn(SSIE::get_peripheral());

			port_map::turn(SSIE::get_peripheral(), true);




			return true;
		}
	};
}

