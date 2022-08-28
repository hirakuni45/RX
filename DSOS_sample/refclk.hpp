#pragma once
//=====================================================================//
/*! @file
    @brief  リファレンス・クロック制御クラス @n
			※「GLFW_SIM」を有効にする事で、各種動作をシュミレートする。
    @author 平松邦仁 (hira@rvf-rc45.net)
    @copyright  Copyright (C) 2020 Kunihito Hiramatsu @n
                Released under the MIT license @n
                https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
// GLFW_SIM for simulate MTU conversion
#ifndef GLFW_SIM
#include "common/renesas.hpp"
#include "common/mtu_io.hpp"
#endif

namespace dsos {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  リファレンス・クロック・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class refclk {

#ifndef GLFW_SIM
#if defined(SIG_RX65N)
	// CN13 (1): PD1_AN109_IRQ1 (MTIOC4B)
	typedef device::MTU4 MTU;
	static constexpr auto PSEL = device::port_map_mtu::ORDER::FIFTH;
#elif defined(SIG_RX72N)
	// Pmod2 (8): PD1_RESET (MTIOC4B)
	typedef device::MTU4 MTU;
	static constexpr auto PSEL = device::port_map_mtu::ORDER::FIFTH;
#endif
	typedef device::mtu_io<MTU, utils::null_task, utils::null_task, PSEL> MTU_IO;
#else
	class MTU_IO {
	public:
	};
#endif

	MTU_IO	mtu_io_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-----------------------------------------------------------------//
		refclk() noexcept : mtu_io_()
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始（1KHz の出力）
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start() noexcept
		{
#ifndef GLFW_SIM
			uint32_t freq = 1'000;
			auto ret = mtu_io_.start_normal(MTU::CHANNEL::B, MTU_IO::OUTPUT::TOGGLE, freq);
			return ret;
#else
			return true;
#endif
		}
	};
}
