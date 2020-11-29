#pragma once
//=====================================================================//
/*!	@file
	@brief	ＧＰＳファイル操作
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/format.hpp"
#include "common/file_io.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ＧＰＳファイル・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class gps_file {

		enum class MODE : uint8_t {
			NONE,	///< 何もしない
			OPEN,	///< ファイルオープン
			WRITE,	///< 書き込み
			CLOSE,	///< クローズ
		};
		MODE			mode_;

		utils::file_io	file_;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		gps_file() :
			mode_(MODE::NONE), file_()
		{ }


		//-------------------------------------------------------------//
		/*!
			@brief	サービス
		*/
		//-------------------------------------------------------------//
		void service()
		{
			switch(mode_) {
			case MODE::NONE:
				break;
			case MODE::OPEN:
				if(n > 0) {
					if(!file_.is_open()) {
						auto t = nmea.get_gmtime();
						char tmp[32];
						make_file_name_(t, tmp, sizeof(tmp));
						file_.open(tmp, "wb");
					} else {
						gps_mode_ = GPS_MODE::WRITE;
						gps_fifo_.clear();
					}
				}
				break;
			case MODE::WRITE:
				break;
			case MODE::CLOSE:
				break;
			}
		}
	};
}
