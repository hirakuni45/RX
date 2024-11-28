#pragma once
//=========================================================================//
/*!	@file
	@brief	flash_io ベース・クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cstdint>

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  flash_io ベース・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct flash_io_base {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  エラー型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ERROR : uint8_t {
			NONE,		///< エラー無し
			START,		///< 開始不良
			CLOCK,		///< クロック設定不良
			NOS,		///< 未サポート
			ADDRESS,	///< アドレス不良
			LENGTH,		///< 長さ不良
			BANK,		///< バンク数不良
			TIMEOUT,	///< タイムアウト
			WRITE,		///< 書き込みエラー
			LOCK,		///< Lock エラー
			ST_ILGL,	///< ILGL ステータス検出
			ST_ERS,		///< ERS ステータス検出
			ST_PRG,		///< PRG ステータス検出
		};
	};
}
