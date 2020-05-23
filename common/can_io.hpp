#pragma once
//=====================================================================//
/*!	@file
	@brief	RX グループ・CAN I/O 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/vect.h"

#ifndef F_PCLKB
#  error "can_io.hpp requires F_PCLKB to be defined"
#endif

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CAN 制御ベースクラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class can_io_base {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CAN スピード型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class SPEED {
			_125K =   125'000,	///< 125 Kbps
			_250K =   250'000,	///< 250 Kbps
			_500K =   500'000,	///< 500 Kbps
			_1M   = 1'000'000	///< 1 Mbps
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CAN 制御クラス
		@param[in]	CAN		CAN 定義クラス
		@param[in]	PSEL	ポート候補
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class CAN, port_map::option PSEL = port_map::option::FIRST>
	class can_io : public can_io_base {
	public:

	private:

		uint8_t		level_;

		// 便宜上のスリープ
		void sleep_() { asm("nop"); }

		static void recv_task_() {
		}

		static void send_task_() {
		}

		static void err_task_() {
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		can_io() noexcept : level_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  通信速度を設定して、CSI を有効にする
			@param[in]	speed	通信速度
			@param[in]	level	割り込みレベル、０の場合はポーリング
			@return エラー（速度設定範囲外）なら「false」
		*/
		//-----------------------------------------------------------------//
		bool start(SPEED speed, uint8_t level = 0) noexcept
		{
			level_ = level;

			power_mgr::turn(CAN::get_peripheral());
			port_map::turn(CAN::get_peripheral(), true, PSEL);

			uint32_t tq = 10;  // TSEG2: 6-1, TSEG1: 4-1
			uint32_t brp = F_PCLKB / static_cast<uint32_t>(speed);
			brp /= tq;
			--brp;

			CAN::BCR = CAN::BCR.TSEG1.b(0b0101) | CAN::BCR.BRP.b(brp)
				CAN::BCR.TSEG2.b(0b011);




			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアル送信
			@param[in]	src	送信ソース
			@param[in]	cnt	送信サイズ
		*/
		//-----------------------------------------------------------------//
		void send(const void* src, uint32_t size) noexcept
		{
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアル受信
			@param[out]	dst	受信先
			@param[in]	cnt	受信サイズ
		*/
		//-----------------------------------------------------------------//
		void recv(void* dst, uint32_t size) noexcept
		{
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  RSPIを無効にして、パワーダウンする
			@param[in]	power パワーダウンをしない場合「false」
		*/
		//-----------------------------------------------------------------//
		void destroy(bool power = true) noexcept
		{
		}
	};
}
