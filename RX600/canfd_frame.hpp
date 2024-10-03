#pragma once
//=========================================================================//
/*!	@file
	@brief	CANFD フレーム・クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	CANFD フレーム構造・クラス @n
				・RX CANFD のメッセージバッファ構造を表現したもの @n
				・内部は、32 ビット x 4 ワードの単純な構造 @n
				pad[0]::B31 = IDE @n
				pad[0]::B30 = RTR @n
				pad[0]::B28-B18 = SID @n
				pad[0]::B17-B0  = EID @n
				pad[1]::B20-B16 = DLC @n
				pad[1]::B15-B8  = DATA0 @n
				pad[1]::B7-B0   = DATA1 @n
				pad[2]::B31-B24 = DATA2 @n
				pad[2]::B23-B16 = DATA3 @n
				pad[2]::B15-B8  = DATA4 @n
				pad[2]::B7-B0   = DATA5 @n
				pad[3]::B31-B24 = DATA6 @n
				pad[3]::B23-B16 = DATA7 @n
				pad[3]::B15-B0  = TS
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class canfd_frame {
		uint32_t	hf0_;
		uint32_t	hf1_;
		uint32_t	hf2_;
		uint32_t	df_[16];



	};
}
