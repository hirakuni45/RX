#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ SDRAM 設定
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX600/system.hpp"
#include "common/renesas.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SDRAM 種別
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class sdram_type {
		M128,	///< 128 Mbits (16 Mbytes)
		M256,	///< 256 Mbits (32 Mbytes)
		M512,	///< 512 Mbits (64 Mbytes)
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  バス幅
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class sdram_width {
		W16,	///< 16 bits
		W32,	///< 32 bits
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SDRAM 制御クラス
		@param[in]	mtype	メモリータイプ
		@param[in]	busw	バス幅
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <sdram_type mtype, sdram_width busw>
	class sdram {

	public:
		void operator() ()
		{
			// SDRAM 初期化 128M/32bits bus
			device::MPC::PFAOE0 = 0xff;  // A8 to A15
			device::MPC::PFBCR0 = device::MPC::PFBCR0.ADRLE.b(1) |
								  device::MPC::PFBCR0.DHE.b(1) |
								  device::MPC::PFBCR0.DH32E.b(1);
			device::MPC::PFBCR1 = device::MPC::PFBCR1.MDSDE.b(1) |
								  device::MPC::PFBCR1.DQM1E.b(1) |
								  device::MPC::PFBCR1.SDCLKE.b(1);
			device::SYSTEM::SYSCR0 = device::SYSTEM::SYSCR0.KEY.b(0x5A) |
									 device::SYSTEM::SYSCR0.ROME.b(1) |
									 device::SYSTEM::SYSCR0.EXBE.b(1);
			while(device::SYSTEM::SYSCR0.EXBE() == 0) asm("nop");
			device::BUS::SDIR = device::BUS::SDIR.ARFI.b(0) |
								device::BUS::SDIR.ARFC.b(1) |
								device::BUS::SDIR.PRC.b(0);
			device::BUS::SDICR = device::BUS::SDICR.INIRQ.b(1);  // 初期化シーケンス開始
			while(device::BUS::SDSR() != 0) asm("nop");
			// 動作許可、３２ビットアクセス
			device::BUS::SDCCR = device::BUS::SDCCR.BSIZE.b(1);
			// Burst read and burst write, CAS latency: 3, Burst type: Sequential, Burst length: 1
			device::BUS::SDMOD = 0b00000000110000;
			// CAS latency: 3, Write recovery: 1, ROW prechage: 4, RAS latency: 3, RAS active: 4
			device::BUS::SDTR = device::BUS::SDTR.CL.b(3) |
								device::BUS::SDTR.RP.b(3) |
								device::BUS::SDTR.RCD.b(2) |
								device::BUS::SDTR.RAS.b(3);
			// 128M/16 カラム９ビット、ロウ１２ビット
			device::BUS::SDADR = device::BUS::SDADR.MXC.b(1);
			// Refresh cycle
			device::BUS::SDRFCR = device::BUS::SDRFCR.RFC.b(2048) |
								  device::BUS::SDRFCR.REFW.b(7);
			device::BUS::SDRFEN = device::BUS::SDRFEN.RFEN.b(1);
			// SDRAM 動作開始
			device::BUS::SDCCR.EXENB = 1;
		}
	};

	typedef sdram<sdram_type::M128, sdram_width::W16> SDRAM_128M_16W;
	typedef sdram<sdram_type::M128, sdram_width::W32> SDRAM_128M_32W;

	typedef sdram<sdram_type::M256, sdram_width::W16> SDRAM_256M_16W;
	typedef sdram<sdram_type::M256, sdram_width::W32> SDRAM_256M_32W;

	typedef sdram<sdram_type::M512, sdram_width::W16> SDRAM_512M_16W;
	typedef sdram<sdram_type::M512, sdram_width::W32> SDRAM_512M_32W;
}
