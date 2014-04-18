//=====================================================================//
/*!	@file
	@brief	Chager Monitor クラス
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdio>
#include "rx/rx63x/system.hpp"
#include "rx/rx63x/port.hpp"
#include "rx/rx63x/mpc.hpp"
#include "chager.hpp"
#include "main.hpp"

namespace utils {

	//-----------------------------------------------------------------//
	/*!
		@brief  初期化
	*/
	//-----------------------------------------------------------------//
	void chager::initialize()
	{
		// Phot device LED 制御 PB0, PB1, PB2
		device::PORTB::PDR.B0 = 1;	// PORTB:B0 output
		device::PORTB::PODR.B0 = 1;	// B0 off
		device::PORTB::PDR.B1 = 1;	// PORTB:B1 output
		device::PORTB::PODR.B1 = 1;	// B0 off
		device::PORTB::PDR.B2 = 1;	// PORTB:B2 output
		device::PORTB::PODR.B2 = 1;	// B0 off

		// GPT0 設定 (GTIOC0A: P71:38, PD7:12)(GTIOC0B: P74:35, PD6:13)
		// GPT1 設定 (GTIOC1A: P72:37, PD5:14)(GTIOC1B: P75:34, PD4:15)
		device::PORT7::PDR.B1 = 1;			// output
		device::PORT7::PDR.B2 = 1;			// output
		device::SYSTEM::MSTPCRA.MSTPA7 = 0; // GPT0..3 モジュール有効
		device::MPC::PWPR.B0WI = 0;			// PWPR 書き込み許可
		device::MPC::PWPR.PFSWE = 1;		// PxxPFS 書き込み許可
		device::MPC::P71PFS.PSEL = 0b0110;	// GTIOC0A 設定
		device::MPC::P72PFS.PSEL = 0b0110;	// GTIOC1A 設定
		device::MPC::PWPR = device::MPC::PWPR.B0WI.b();	// MPC 書き込み禁止
		device::PORT7::PMR.B1 = 1;			// 周辺機能として使用
		device::PORT7::PMR.B2 = 1;			// 周辺機能として使用
		gpt0_.start_pwm(512 - 1);	// GPT0 PWM start
		gpt0_.set_r(512 - 1);
		gpt0_.set_a(low_limit_);
		gpt1_.start_pwm(512 - 1);	// GPT1 PWM start
		gpt1_.set_r(512 - 1);
		gpt1_.set_a(low_limit_);

		// S12AD 設定 P40(56), P41(55), P42(54), P43(53), P44(52),
		device::SYSTEM::MSTPCRA.MSTPA17 = 0; // S12AD モジュール有効
		device::MPC::PWPR.B0WI = 0;			 // PWPR 書き込み許可
		device::MPC::PWPR.PFSWE = 1;		 // PxxPFS 書き込み許可
		device::MPC::P40PFS.ASEL = 1;	     // アナログ入力設定
		device::MPC::P41PFS.ASEL = 1;	     // アナログ入力設定
		device::MPC::P42PFS.ASEL = 1;	     // アナログ入力設定
		device::MPC::P43PFS.ASEL = 1;	     // アナログ入力設定
		device::MPC::P44PFS.ASEL = 1;	     // アナログ入力設定
		device::MPC::PWPR = device::MPC::PWPR.B0WI.b();	// MPC 書き込み禁止

		adc_.start(0b00011111);
		adc_.sync();

//		チャネル０
		chanel0_.vol_ref_ = static_cast<int32_t>((4096.0f / 2.5f) * (1.0f / 6.0f) * 5.0f); // Ch0 指令電圧
		chanel0_.cur_lim_ = static_cast<int32_t>((4096.0f / 2.5f) * 1.2f); // Ch0 リミット電流

//		チャネル１

	}


	//-----------------------------------------------------------------//
	/*!
		@brief  サービス
	*/
	//-----------------------------------------------------------------//
	void chager::service()
	{
		inp_  = static_cast<int32_t>(adc_.get(2)); // 入力電圧 10:1 (Ref:2.5V, 4096:25V)

		chanel0_.out_ = static_cast<int32_t>(adc_.get(0)); // 出力電圧 6:1 (Ref:2.5V, 4096:15V)
		chanel0_.cur_ = static_cast<int32_t>(adc_.get(1)); // 出力電流 0 to 2.5A (4096:2.5A)
		chanel1_.out_ = static_cast<int32_t>(adc_.get(4)); // 出力電圧 6:1 (Ref:2.5V, 4096:15V)
		chanel1_.cur_ = static_cast<int32_t>(adc_.get(3)); // 出力電流 0 to 2.5A (4096:2.5A)	

		adc_.start(0b00011111);

		gpt0_.set_a(chanel0_.const_voltage());






	}
}
