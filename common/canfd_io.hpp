#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ・CANFD I/O 制御 @n
			・CANFD クロックは、正確に一致しない場合、エラーとする。 @n
			・CANFD ポートに、CAN バス・トランシーバーを接続する。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"
#include "common/vect.h"
#include "common/delay.hpp"
#include "common/format.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CANFD 制御定義クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class canfd_io_def {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CAN スピード型（CAN FD 公称ビットレート）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class SPEED {
			_50K  =    50'000,	///<  50 Kbps（標準ではない）
			_100K =   100'000,	///< 100 Kbps（標準ではない）
			_125K =   125'000,	///< 125 Kbps
			_250K =   250'000,	///< 250 Kbps
			_500K =   500'000,	///< 500 Kbps
			_750K =   750'000,	///< 750 Kbps（標準ではない）
			_1M   = 1'000'000	///< 1 Mbps
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CAN FD フレーム・データ ビット レート
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class DATA {
			_2M = 2'000'000,	///< 2Mbps
			_4M = 4'000'000,	///< 4Mbps
			_5M = 5'000'000,	///< 5Mbps
			_8M = 8'000'000		///< 8Mbps
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CANFD 制御クラス
		@param[in]	CANFD	CANFD 定義クラス
		@param[in]	RBF		受信バッファクラス (utils::fixed_fifo<can_frame, N>)
		@param[in]	TBF		送信バッファクラス (utils::fixed_fifo<can_frame, N>)
		@param[in]	PSEL	ポート候補
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class CANFD, class RBF, class TBF, port_map::ORDER PSEL = port_map::ORDER::FIRST>
	struct canfd_io : public canfd_io_def {

		static_assert(RBF::size() > 16, "Receive buffer is too small.");
		static_assert(TBF::size() > 16, "Transmission buffer is too small.");

#ifndef NDEBUG
		typedef utils::null_format	format;
#else
		typedef utils::format		format;
#endif

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		canfd_io() noexcept { }


		//-----------------------------------------------------------------//
		/*!
			@brief  通信速度が設定可能か検査
			@param[in]	speed	公称通信速度型
			@param[in]	data	データ通信速度型
			@return 可能なら「true」を返す。
		*/
		//-----------------------------------------------------------------//
		static constexpr bool probe_speed(SPEED speed, DATA data) noexcept
		{
#if 0
			if(get_tq_(false, speed) >= 8) return true;  // PCLKB 選択
			else if(get_tq_(true, speed) >= 8) return true;  // XTAL(EXTAL) 選択
			else return false;
#endif
			return false;
		}






	};
}
