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
#include "common/vtx.hpp"
#include "common/fraction.hpp"
#include "common/fixed_fifo.hpp"

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

		static const uint8_t DIR_X_BIT  = 0b00000001;
		static const uint8_t DIR_Y_BIT  = 0b00000010;
		static const uint8_t DIR_Z_BIT  = 0b00000100;
		static const uint8_t DIR_W_BIT  = 0b00001000;
		static const uint8_t STEP_X_BIT = 0b00010000;
		static const uint8_t STEP_Y_BIT = 0b00100000;
		static const uint8_t STEP_Z_BIT = 0b01000000;
		static const uint8_t STEP_W_BIT = 0b10000000;

		typedef device::PORTB PULSE_OUT;
		typedef device::PORT<device::PORTB, device::bitpos::B0> DIR_X;
		typedef device::PORT<device::PORTB, device::bitpos::B1> DIR_Y;
		typedef device::PORT<device::PORTB, device::bitpos::B2> DIR_Z;
		typedef device::PORT<device::PORTB, device::bitpos::B3> DIR_W;
		typedef device::PORT<device::PORTB, device::bitpos::B4> PULSE_X;
		typedef device::PORT<device::PORTB, device::bitpos::B5> PULSE_Y;
		typedef device::PORT<device::PORTB, device::bitpos::B6> PULSE_Z;
		typedef device::PORT<device::PORTB, device::bitpos::B7> PULSE_W;

		typedef device::PORT<device::PORT6, device::bitpos::B0> LIM_X;
		typedef device::PORT<device::PORT6, device::bitpos::B1> LIM_Y;
		typedef device::PORT<device::PORT6, device::bitpos::B2> LIM_Z;
		typedef device::PORT<device::PORT6, device::bitpos::B3> LIM_W;

		typedef utils::fixed_fifo<uint8_t, 2048> STEP_PAD;

		class mtu_task {
			uint32_t	count_;

			vtx::ivtx4	pos_;

			STEP_PAD	step_;

		public:
			mtu_task() noexcept : count_(0), pos_(0) { }

			void operator() () noexcept {
				if(count_ & 1) {
					if(step_.length() > 0) {
						auto bits = step_.get();
						PULSE_OUT::PODR = bits;
						if(bits & STEP_X_BIT) pos_.x += (bits & DIR_X_BIT) ? -1 : 1;
						if(bits & STEP_Y_BIT) pos_.y += (bits & DIR_Y_BIT) ? -1 : 1;
						if(bits & STEP_Z_BIT) pos_.z += (bits & DIR_Z_BIT) ? -1 : 1;
						if(bits & STEP_W_BIT) pos_.w += (bits & DIR_W_BIT) ? -1 : 1;
					}
				} else {
					PULSE_X::P = 0;
					PULSE_Y::P = 0;
					PULSE_Z::P = 0;
					PULSE_W::P = 0;
				}
				++count_;
			}

			STEP_PAD& at_step() noexcept { return step_; }

			vtx::ivtx4& at_pos() noexcept { return pos_; }
		};

		typedef device::mtu_io<device::MTU0, mtu_task> MTU;
		MTU			mtu_;

		uint32_t	speed_;

		vtx::ivtx4	min_;
		vtx::ivtx4	max_;
		vtx::ivtx4	org_;  // 基点
		vtx::ivtx4	pos_;  // 現在位置
		vtx::ivtx4	fin_;  // 最終位置

		typedef imath::fraction<uint32_t> FRACTION;
		FRACTION	frac_x_;
		FRACTION	frac_y_;
		FRACTION	frac_z_;
		FRACTION	frac_w_;

		uint8_t		dir_;

		enum class CMD {
			ERR,	///< error
			HELP,	///< command help
			SPEED,	///< speed
			MOVE,	///< move
			POS,	///< position
		};

		CMD scan_cmd_(uint32_t& n) const
		{
			n = cmdl_.get_words();
			if(n >= 1) {
				if(cmdl_.cmp_word(0, "s")) return CMD::SPEED;
				else if(cmdl_.cmp_word(0, "m")) return CMD::MOVE;
				else if(cmdl_.cmp_word(0, "p")) return CMD::POS;
				else if(cmdl_.cmp_word(0, "speed")) return CMD::SPEED;
				else if(cmdl_.cmp_word(0, "move")) return CMD::MOVE;
				else if(cmdl_.cmp_word(0, "pos")) return CMD::POS;
				else if(cmdl_.cmp_word(0, "position")) return CMD::POS;
				else if(cmdl_.cmp_word(0, "help")) return CMD::HELP;
			}
			return CMD::ERR;
		}

		void help_cmd_() noexcept
		{
			utils::format("s[peed] [new speed]\n");
			utils::format("m[ove] [new position]\n");
			utils::format("p[os]\n");
			utils::format("help\n");
		}

 	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	CMDL	コマンド・ライン・クラス			
		*/
		//-----------------------------------------------------------------//
		pulse(CMDL& cmdl) noexcept : cmdl_(cmdl), speed_(100),
			min_(0), max_(0), org_(0), pos_(0), dir_(0)
		{ }


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
			DIR_W::DIR = 1;
			PULSE_X::DIR = 1;
			PULSE_Y::DIR = 1;
			PULSE_Z::DIR = 1;
			PULSE_W::DIR = 1;

			DIR_X::P = 1;
			DIR_Y::P = 1;
			DIR_Z::P = 1;
			DIR_W::P = 1;
			PULSE_X::P = 1;
			PULSE_Y::P = 1;
			PULSE_Z::P = 1;
			PULSE_W::P = 1;

			LIM_X::DIR = 0;
			LIM_X::PU  = 1;
			LIM_Y::DIR = 0;
			LIM_Y::PU  = 1;
			LIM_Z::DIR = 0;
			LIM_Z::PU  = 1;
			LIM_W::DIR = 0;
			LIM_W::PU  = 1;

			// MTU3 をノーマルモードで起動
			uint8_t intr = 4;
			auto f = mtu_.start_normal(device::MTU0::channel::A, MTU::OUTPUT_TYPE::NONE,
				speed_, intr);

			return f;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  直線移動
			@param[in]	target
		*/
		//-----------------------------------------------------------------//
		void move(const vtx::ivtx4& target) noexcept
		{
			fin_ = target;

			auto sub = target - pos_;
			vtx::ivtx4 d;
			d.x = std::abs(sub.x);
			d.y = std::abs(sub.y);
			d.z = std::abs(sub.z);
			d.w = std::abs(sub.w);
			auto max = std::abs(d.max());

			dir_ = 0;
			if(sub.x < 0) dir_ |= DIR_X_BIT;
			if(sub.y < 0) dir_ |= DIR_Y_BIT;
			if(sub.z < 0) dir_ |= DIR_Z_BIT;
			if(sub.w < 0) dir_ |= DIR_W_BIT;

			frac_x_.set(d.x, max);
			frac_y_.set(d.y, max);
			frac_z_.set(d.z, max);
			frac_w_.set(d.w, max);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
		*/
		//-----------------------------------------------------------------//
		void update() noexcept
		{
			if(fin_ != pos_) {
				auto bits = dir_;
				if(frac_x_.add()) {
					bits |= STEP_X_BIT;
					if(dir_ & DIR_X_BIT) pos_.x--;
					else ++pos_.x;
				}
				if(frac_y_.add()) {
					bits |= STEP_Y_BIT;
					if(dir_ & DIR_Y_BIT) pos_.y--;
					else ++pos_.y;
				}
				if(frac_z_.add()) {
					bits |= STEP_Z_BIT;
					if(dir_ & DIR_Z_BIT) pos_.z--;
					else ++pos_.z;
				}
				if(frac_w_.add()) {
					bits |= STEP_W_BIT;
					if(dir_ & DIR_W_BIT) pos_.w--;
					else ++pos_.w;
				}
				if(bits != dir_) {
					mtu_.at_main_task().at_step().put(bits);
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  コマンド・サービス
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool service_command()
		{
			uint32_t n;
			auto cmd = scan_cmd_(n);
			switch(cmd) {
			case CMD::HELP:
				help_cmd_();
				break;
			case CMD::SPEED:
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
				break;
			case CMD::POS:
				if(n == 1) {
					auto p = pos_ - org_;
					utils::format("Pos: %d, %d, %d, %d\n") % p.x % p.y % p.z % p.w;
				}
				break;
			case CMD::MOVE:
				if(n == 1) {
					utils::format("Param error: '%s'\n") % cmdl_.get_command();
					return false;
				} else {
					vtx::ivtx4 target = pos_;
					if(n >= 2) {  // X
						if(!cmdl_.get_integer(1, target.x)) {
							char tmp[16];
							cmdl_.get_word(1, tmp, sizeof(tmp));
							utils::format("Illegual position X: %s\n") % tmp;
							return false;
						}
					}
					if(n >= 3) {  // Y
						if(!cmdl_.get_integer(2, target.y)) {
							char tmp[16];
							cmdl_.get_word(2, tmp, sizeof(tmp));
							utils::format("Illegual position Y: %s\n") % tmp;
							return false;
						}
					}
					if(n >= 4) {  // Z
						if(!cmdl_.get_integer(3, target.z)) {
							char tmp[16];
							cmdl_.get_word(3, tmp, sizeof(tmp));
							utils::format("Illegual position Z: %s\n") % tmp;
							return false;
						}
					}
					if(n >= 5) {  // W
						if(!cmdl_.get_integer(4, target.w)) {
							char tmp[16];
							cmdl_.get_word(4, tmp, sizeof(tmp));
							utils::format("Illegual position W: %s\n") % tmp;
							return false;
						}
					}
					move(target);
				}
				break;
			default:
				return false;
				break;
			}
			return true;
		}
	};
}
