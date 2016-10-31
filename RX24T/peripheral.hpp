#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・ペリフェラル @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ペリフェラル種別
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class peripheral {
		CMT0,	///< コンペアマッチタイマー０
		CMT1,	///< コンペアマッチタイマー１
		CMT2,	///< コンペアマッチタイマー２
		CMT3,	///< コンペアマッチタイマー３

		RIIC0,	///< I 2 C バスインタフェース０

		SCI1,	///< シリアルコミュニケーションインタフェース０
		SCI5,	///< シリアルコミュニケーションインタフェース５
		SCI6,	///< シリアルコミュニケーションインタフェース６

		RSPI0,	///< シリアルペリフェラルインタフェース０

		MTU0,	///< マルチファンクションタイマパルスユニット０
		MTU1,	///< マルチファンクションタイマパルスユニット１
		MTU2,	///< マルチファンクションタイマパルスユニット２
		MTU3,	///< マルチファンクションタイマパルスユニット３
		MTU4,	///< マルチファンクションタイマパルスユニット４
		MTU5,	///< マルチファンクションタイマパルスユニット５
		MTU6,	///< マルチファンクションタイマパルスユニット６
		MTU7,	///< マルチファンクションタイマパルスユニット７
		MTU9,	///< マルチファンクションタイマパルスユニット９
	};
}
