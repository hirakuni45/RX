#pragma once
//=====================================================================//
/*! @file
    @brief  CNC PULSE class
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/mtu_io.hpp"

namespace cnc {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CNC PULSE class
		@param[in]	CMDL	コマンド・ライン・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class CMDL>
	class pulse {

		CMDL&	cmdl_;

	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アウトプット・タイプ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

	private:
		typedef device::PORTB CTRL_PORT;
		typedef device::PORT<device::PORTB, device::bitpos::B0> DIR_X;
		typedef device::PORT<device::PORTB, device::bitpos::B1> DIR_Y;
		typedef device::PORT<device::PORTB, device::bitpos::B2> DIR_Z;
		typedef device::PORT<device::PORTB, device::bitpos::B3> DIR_A;
		typedef device::PORT<device::PORTB, device::bitpos::B4> PULSE_X;
		typedef device::PORT<device::PORTB, device::bitpos::B5> PULSE_Y;
		typedef device::PORT<device::PORTB, device::bitpos::B6> PULSE_Z;
		typedef device::PORT<device::PORTB, device::bitpos::B7> PULSE_A;


		class mtu_task;

		typedef device::mtu_io<device::MTU0, mtu_task> MTU;
		MTU			mtu_;

		class mtu_task {
			uint32_t	count_;

		public:
			mtu_task() : count_(0) { }

			void operator() () {
				PULSE_X::P = !PULSE_X::P();
			}
		};

		uint32_t	speed_;

 	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	CMDL	コマンド・ライン・クラス			
		*/
		//-----------------------------------------------------------------//
		pulse(CMDL& cmdl) : cmdl_(cmdl), speed_(1000) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  初期化
		*/
		//-----------------------------------------------------------------//
		bool start() noexcept
		{
			DIR_X::DIR = 1;
			DIR_Y::DIR = 1;
			DIR_Z::DIR = 1;
			DIR_A::DIR = 1;
			PULSE_X::DIR = 1;
			PULSE_Y::DIR = 1;
			PULSE_Z::DIR = 1;
			PULSE_A::DIR = 1;

			DIR_X::P = 1;
			DIR_Y::P = 1;
			DIR_Z::P = 1;
			DIR_A::P = 1;
			PULSE_X::P = 1;
			PULSE_Y::P = 1;
			PULSE_Z::P = 1;
			PULSE_A::P = 1;

			uint8_t intr = 4;
			auto f = mtu_.start_normal(device::MTU0::channel::A, MTU::OUTPUT_TYPE::NONE,
				speed_, intr);
			return f;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  コマンド・サービス
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool service_command()
		{
			auto n = cmdl_.get_words();

			if(n >= 1) {
				if(cmdl_.cmp_word(0, "speed")) {
					if(n > 1) {
						int32_t a = speed_;
						if(cmdl_.get_integer(1, a)) {
							if(a > 0) {
								speed_ = a;
								mtu_.set_frq(speed_);
							}
						}
					} else {
						utils::format("Speed: %d\n") % speed_;
					}
				} else {
					return false;
				}
			}

			return true;
		}
	};
}
