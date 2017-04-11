#pragma once
//=====================================================================//
/*! @file
    @brief  SEEDA03 (RX64M) メイン @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/renesas.hpp"

#include "common/command.hpp"
#include "common/format.hpp"
#include "common/input.hpp"
#include "common/time.h"

namespace seeda {

	typedef utils::command<256> CMD;

	typedef device::PORT<device::PORT6, device::bitpos::B7> SW1;
	typedef device::PORT<device::PORT6, device::bitpos::B6> SW2;


	//-----------------------------------------------------------------//
	/*!
		@brief  GMT 時間の設定
		@param[in]	t	GMT 時間
	*/
	//-----------------------------------------------------------------//
	void set_time(time_t t);


	//-----------------------------------------------------------------//
	/*!
		@brief  GMT 時間の取得
		@return GMT 時間
	*/
	//-----------------------------------------------------------------//
	time_t get_time();


	//-----------------------------------------------------------------//
	/*!
		@brief  時間の表示
		@param[in]	t		時間
		@param[in]	dst		出力文字列
		@param[in]	size	文字列の大きさ
	*/
	//-----------------------------------------------------------------//
	void disp_time(time_t t, char* dst = nullptr, uint32_t size = 0);


	//-----------------------------------------------------------------//
	/*!
		@brief  設定スイッチの状態を取得
		@return 設定スイッチの状態
	*/
	//-----------------------------------------------------------------//
	uint8_t get_switch()
	{
		return static_cast<uint8_t>(!SW1::P()) | (static_cast<uint8_t>(!SW2::P()) << 1);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  A/D 変換値の取得
		@param[in]	ch	チャネル（０～７）
		@return A/D 変換値
	*/
	//-----------------------------------------------------------------//
	uint16_t get_analog(uint8_t ch);
}
