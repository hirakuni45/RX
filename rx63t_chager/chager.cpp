//=====================================================================//
/*!	@file
	@brief	Chager Monitor クラス
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdio>
#include "chager.hpp"
#include "main.hpp"

namespace utils {

#if 0
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  play コマンド
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	bool sd_monitor::cmd_play_(const utils::strings& ss)
	{
		if(ss[0] != "play") return false;

		if(ss.size() <= 1) return true;

		for(int i = 1; i < ss.size(); ++i) {
			vs1063a_.play(ss[i].c_str());
		}
		return true;
	}
#endif


	//-----------------------------------------------------------------//
	/*!
		@brief  初期化
	*/
	//-----------------------------------------------------------------//
	void chager::initialize()
	{
		sci_puts("RX63T start\n");
		sci_puts("Chager\n");
		sci_puts("\n");

		command_.set_prompt("% ");
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  サービス
	*/
	//-----------------------------------------------------------------//
	void chager::service()
	{
		if(!command_.service()) {
			return;
		}

		for(short i = 0; i < 8; ++i) {
			char word[16];
			if(command_.get_word(i, sizeof(word), word)) {
				sci_puts(word);
				sci_puts("\n");
			} else {
				break;
			}
		}
#if 0
//			if(cmd_play_(ss)) return;
//			if(cmd_volume_(ss)) return;
#endif
	}

}
