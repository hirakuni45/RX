//=====================================================================//
/*!	@file
	@brief	SSD1306Z 制御クラス @n
			4 wire SPI
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "RX63T/system.hpp"
#include "RX63T/port.hpp"
#include "RX63T/mpc.hpp"
#include "RX63T/sci.hpp"
#include "common/delay.hpp"
#include "common/ssd1306z_io.hpp"

namespace device {

	static void put_(uint8_t ch)
	{
		for(uint8_t i = 0; i < 8; ++i) {
			if(ch & 0x80) {
				device::PORT3::PODR.B0 = 1;	// data
			} else {
				device::PORT3::PODR.B0 = 0;	// data
			}
			ch <<= 1;
			device::PORT2::PODR.B3 = 0;	// clk
			asm("nop");
			device::PORT2::PODR.B3 = 1;	// clk
			asm("nop");
		}
	}

#if 0
	static void put2_(uint8_t ch)
	{
		while(device::SCI0::SSR.TEND() == 0) ;
		utils::wait_delay(1);
		device::SCI0::TDR = ch;
	}
#endif

	static inline void select_(bool sel) {
		device::PORT2::PODR.B2 = sel;
	}

	static inline void cmd_data_(bool sel) {
		device::PORT2::PODR.B4 = sel;
	}

#if 0
	static bool setup_spi_(uint32_t bps)
	{
		uint32_t brr = F_PCKB / bps / 4;
		uint8_t cks = 0;
		while(brr > 256) {
			brr >>= 2;
			++cks;
		}
		if(cks > 3 || brr > 256) return false;

		SYSTEM::MSTPCRB.MSTPB31 = 0;	// B31 (SCI0)のストップ状態解除
		device::SCI0::SCR = 0x00;				// TE, RE disable.
		device::SCI0::SSR = 0xc0;				// reset error

//		ICU::IER.TEI0 = false;
//		ICU::IER.RXI0 = false;
//		uint32_t chanel = SCIx::get_chanel();
//		if(!set_intr_(chanel)) {
//			return false;
//		}

		device::SCI0::SMR = cks | device::SCI0::SMR.CM.b();
///		format("SMR: %02X\n") % static_cast<unsigned int>(SCI0::SMR());
///		device::SCI0::SIMR1.IICM = 0;

		// LSB(0), MSB(1) first
		device::SCI0::SCMR.SDIR = 1;

		// クロックタイミング種別選択
		device::SCI0::SPMR = device::SCI0::SPMR.CKPH.b(0) | device::SCI0::SPMR.CKPOL.b(0) | device::SCI0::SPMR.MSS.b(0);

		if(brr) --brr;
		device::SCI0::BRR = static_cast<uint8_t>(brr);

		uint8_t scr = SCI0::SCR.CKE.b(0b00);

//		if(polling_) {
///			SCIx::SCR = SCIx::SCR.TE.b() | SCIx::SCR.RE.b() | scr;
			device::SCI0::SCR = device::SCI0::SCR.TE.b() | scr;
			device::SCI0::TDR = 0;	// dummy write
//		} else {
//			SCIx::SCR = SCIx::SCR.RIE.b() | SCIx::SCR.TE.b() | SCIx::SCR.RE.b() | scr;
//		}
	}
#endif

	//-----------------------------------------------------------------//
	/*!
		@brief  初期化
	*/
	//-----------------------------------------------------------------//
	void ssd1306z_io::initialize()
	{
		// SCI0(簡易 SPI) の初期化
		// P30:SMOSI0(45) ---> OLED:SDA
		// P23:SCK0(47)   ---> OLED:SCK
		// P22:(48)       ---> OLED:CS
		// P24:(46)       ---> OLED:A0
		device::PORT3::PDR.B0 = 1;
		device::PORT2::PDR.B2 = 1;
		device::PORT2::PDR.B3 = 1;
		device::PORT2::PDR.B4 = 1;

		device::PORT3::PODR.B0 = 0;	// シリアル・データ
		device::PORT2::PODR.B3 = 1;	// シリアル・クロック

		select_(1);
		utils::delay::micro_second(500);

		cmd_data_(0);
		select_(0);
		put_(0xAE);	// Set Display Off
		put_(0xd5);	// display divide ratio/osc. freq. mode
		put_(0x80);
		put_(0xA8);	// multiplex ration mode:63
		put_(0x3F);
		put_(0xD3);	// Set Display Offset
		put_(0x00);
		put_(0x40);	// Set Display Start Line
		put_(0x8D);	// Set Display Offset
		// put_(0x10);
		put_(0x14);
		put_(0xA1);	// Segment Remap
		put_(0xC8);	// Sst COM Output Scan Direction
		// put_(0xC8);
		put_(0xDA);	// common pads hardware: alternative
		put_(0x12);
		put_(0x81);	// contrast control 
//		put_(0x9F);
		put_(0x66);
		put_(0xD9);	// set pre-charge period
//		put_(0x22);	// set period 1:1;period 2:15
		put_(0xF1);
		put_(0xDB);	// VCOM deselect level mode
		put_(0x40);	// set Vvcomh=0.83*Vcc
		put_(0xA4);	// Set Entire Display On/Off
		put_(0xA6);	// Set Normal Display
		put_(0xAF);	// Set Display On
		select_(1);
		utils::delay::micro_second(100);  // 重要！

#if 0
		device::MPC::PWPR.B0WI = 0;				// PWPR 書き込み許可
		device::MPC::PWPR.PFSWE = 1;			// PxxPFS 書き込み許可
		device::MPC::P30PFS.PSEL = 0b1010;		// SMOSI0設定
		device::MPC::P23PFS.PSEL = 0b01010;		// SCK0設定
		device::MPC::PWPR = device::MPC::PWPR.B0WI.b();	// MPC 書き込み禁止
		device::PORT3::PMR.B0 = 1;				// 周辺機能として使用
		device::PORT2::PMR.B3 = 1;				// 周辺機能として使用

		// 48MHz で、10Mbps 以下の設定では、6Mbps が最大値
		// ※12Mbps では、許容範囲を超えてしまう・・
		setup_spi_(6000000);	// 6Mbps
#endif
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  フレームバッファコピー
		@param[in]	buff	バッファ
	*/
	//-----------------------------------------------------------------//
	void ssd1306z_io::copy(const uint8_t* buff)
	{
		cmd_data_(0);
		utils::delay::micro_second(1);
		select_(0);
		utils::delay::micro_second(1);
		for(uint8_t j = 0; j < 8; ++j) {
			put_(0xb0 + j);		// set page address 0 to 7
			put_(0x00);			// lower collum start address
			put_(0x10);			// higher collum start address
			utils::delay::micro_second(1);
			cmd_data_(1);
			utils::delay::micro_second(1);
			for(uint16_t i = 0; i < 128; ++i) {
				put_(*buff++);
			}
			utils::delay::micro_second(1);
			cmd_data_(0);
		}
		select_(1);
	}
}
