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

		static const uint8_t DIR_X_BIT     = 0b00000001;
		static const uint8_t DIR_Y_BIT     = 0b00000010;
		static const uint8_t DIR_Z_BIT     = 0b00000100;
		static const uint8_t DIR_W_BIT     = 0b00001000;
		static const uint8_t DIR_ALL_BITS  = 0b00001111;
		static const uint8_t STEP_X_BIT    = 0b00010000;
		static const uint8_t STEP_Y_BIT    = 0b00100000;
		static const uint8_t STEP_Z_BIT    = 0b01000000;
		static const uint8_t STEP_W_BIT    = 0b10000000;
		static const uint8_t STEP_ALL_BITS = 0b11110000;
		static const uint8_t LIM_X_BIT     = 0b00010000;
		static const uint8_t LIM_Y_BIT     = 0b00100000;
		static const uint8_t LIM_Z_BIT     = 0b01000000;
		static const uint8_t LIM_W_BIT     = 0b10000000;

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
			uint8_t		mask_;

			int32_t		frq_;
			int32_t		acc_;
			int32_t		acc_step_;
			int32_t		lin_step_;

		public:
			mtu_task() noexcept : count_(0), pos_(0), mask_(0),
				frq_(0), acc_(0), acc_step_(0), lin_step_(0) { }

			void operator() () noexcept {
				if(count_ & 1) {
					if(step_.length() > 0) {
						auto bits = step_.get();
						PULSE_OUT::PODR = bits & (mask_ | DIR_ALL_BITS);
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
					if(acc_step_ > 0) {
						frq_ += acc_;
						--acc_step_;
						MTU::set_frq(device::MTU0::channel::A, frq_);
					} else if(lin_step_ > 0) {
						--lin_step_;
					} else {
						frq_ -= acc_;
						if(frq_ < 100) {
							frq_ = 100;
						}
						MTU::set_frq(device::MTU0::channel::A, frq_);
					}
				}
				++count_;
			}

			STEP_PAD& at_step() noexcept { return step_; }

			vtx::ivtx4& at_pos() noexcept { return pos_; }

			void set_mask(uint8_t mask) noexcept {
				mask_ = (mask ^ STEP_ALL_BITS) | DIR_ALL_BITS;
			}

			void set_frq(int32_t frq, int32_t acc) noexcept {
				frq_ = frq;
				acc_ = acc;
			}

			void set_step(int32_t acc_step, int32_t lin_step) noexcept {
				acc_step_ = acc_step;
				lin_step_ = lin_step;
			}
		};

		typedef device::mtu_io<device::MTU0, mtu_task> MTU;
		MTU			mtu_;

		int32_t		speed_limit_;    // 最大速度 [Hz]
		int32_t		speed_current_;  // 現在速度 [Hz]
		int32_t		accel_;
		int32_t		frq_;

		vtx::ivtx4	min_;   // 可動領域（最小）
		vtx::ivtx4	max_;   // 可動領域（最大）
		vtx::ivtx4	org_;   // 基点
		vtx::ivtx4	pos_;   // 現在位置
		vtx::ivtx4	fin_;   // 最終位置
		vtx::ivtx4	pulse_;	// 回転辺りのパルス数
		vtx::ivtx4	lead_;  // ボールネジのリード（回転辺りの移動量）単位「ｍｍ」

		uint32_t	sqr_len_;
		uint32_t	length_;

		typedef imath::fraction<uint32_t> FRACTION;
		FRACTION	frac_x_;
		FRACTION	frac_y_;
		FRACTION	frac_z_;
		FRACTION	frac_w_;

		uint8_t		dir_;

		uint8_t		limit_lvl_;
		uint8_t		limit_pos_;
		uint8_t		limit_neg_;

		enum class CMD {
			ERR,	///< error

			HELP,	///< command help

			SPEED,	///< speed
			MOVE,	///< move
			POS,	///< position
			ACCEL,	///< acceleration/deceleration
			LEAD,	///< lead per rad
			PULSE,	///< pulse per rad
			STOP,	///< stop
			PAUSE,	///< pause
			START,	///< start
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
				else if(cmdl_.cmp_word(0, "accel")) return CMD::ACCEL;
				else if(cmdl_.cmp_word(0, "lead")) return CMD::LEAD;
				else if(cmdl_.cmp_word(0, "pulse")) return CMD::PULSE;
				else if(cmdl_.cmp_word(0, "stop")) return CMD::STOP;
				else if(cmdl_.cmp_word(0, "pause")) return CMD::PAUSE;
				else if(cmdl_.cmp_word(0, "start")) return CMD::START;
				else if(cmdl_.cmp_word(0, "help")) return CMD::HELP;
			}
			return CMD::ERR;
		}

		void help_cmd_() noexcept
		{
			utils::format("s[peed] [new speed]  Setup speed limit (Hz)\n");
			utils::format("m[ove] [new position]\n");
			utils::format("p[os]            Indication of the position\n");
			utils::format("accel [freq]     Acceleration and deceleration (Hz)\n");
			utils::format("lead [x y z w]   Quantity of movement per turn of the ball screw (um/rad)\n");
			utils::format("pulse [x y z w]  The number of the pulses per turn (pulse/rad)\n");
//			utils::format("stop\n");
//			utils::format("pause\n");
//			utils::format("start\n");
			utils::format("help\n");
		}


		bool get_int_(int32_t& val) noexcept
		{
			if(!cmdl_.get_integer(1, val)) {
				return false;
			}
			return true;
		}


		bool get_xyzw_(vtx::ivtx4& val) noexcept
		{
			if(!cmdl_.get_integer(1, val.x)) {
				return false;
			}
			if(!cmdl_.get_integer(2, val.y)) {
				return false;
			}
			if(!cmdl_.get_integer(3, val.z)) {
				return false;
			}
			if(!cmdl_.get_integer(4, val.w)) {
				return false;
			}
			return true;
		}

 	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	CMDL	コマンド・ライン・クラス			
		*/
		//-----------------------------------------------------------------//
		pulse(CMDL& cmdl) noexcept : cmdl_(cmdl),
			speed_limit_(50000), speed_current_(0), accel_(100), frq_(0),
			min_(0), max_(0), org_(0), pos_(0), fin_(0),
			pulse_(6400), lead_(5000), sqr_len_(0), length_(0),
			dir_(0), limit_lvl_(0), limit_pos_(0), limit_neg_(0)
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

			limit_lvl_ = 0;
			limit_pos_ = 0;
			limit_neg_ = 0;

			// MTU3 をノーマルモードで起動、初期 100Hz
			uint8_t intr = 4;
			auto f = mtu_.start_normal(device::MTU0::channel::A, MTU::OUTPUT_TYPE::NONE,
				100, intr);

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
			auto bot = d.max();  // 差分が最大の値を分母とする
			frac_x_.set(d.x, bot);
			frac_y_.set(d.y, bot);
			frac_z_.set(d.z, bot);
			frac_w_.set(d.w, bot);

			dir_ = 0;
			if(sub.x < 0) dir_ |= DIR_X_BIT;
			if(sub.y < 0) dir_ |= DIR_Y_BIT;
			if(sub.z < 0) dir_ |= DIR_Z_BIT;
			if(sub.w < 0) dir_ |= DIR_W_BIT;

			// 距離に対する、加減速の算出
			sqr_len_ = d.sqr();
			length_ = d.len();  // 全体距離
			// 加速距離＋減速距離
			auto n = speed_limit_ / accel_;  // 加速に必要なパルス数
			if(bot > (n * 2)) {
				mtu_.at_main_task().set_step(n, bot - (n * 2));
			} else {
				mtu_.at_main_task().set_step(bot / 2, 0);
			}
			speed_current_ = 100;
			mtu_.at_main_task().set_frq(speed_current_, accel_);
			mtu_.set_frq(speed_current_);  // 初期周期
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  アップデート（１／１００秒、１０ｍｓ）
		*/
		//-----------------------------------------------------------------//
		void update() noexcept
		{
			uint8_t lvl = 0;
			if(!LIM_X::P()) lvl |= LIM_X_BIT;
			if(!LIM_Y::P()) lvl |= LIM_Y_BIT;
			if(!LIM_Z::P()) lvl |= LIM_Z_BIT;
			if(!LIM_W::P()) lvl |= LIM_W_BIT;
			limit_pos_ = ~limit_lvl_ &  lvl;
			limit_neg_ =  limit_lvl_ & ~lvl;
			limit_lvl_ =  lvl;
			mtu_.at_main_task().set_mask(lvl);

			if(limit_pos_ & LIM_X_BIT) {
				utils::format("Limit X ON\n");
			}
			if(limit_pos_ & LIM_Y_BIT) {
				utils::format("Limit Y ON\n");
			}
			if(limit_pos_ & LIM_Z_BIT) {
				utils::format("Limit Z ON\n");
			}
			if(limit_pos_ & LIM_W_BIT) {
				utils::format("Limit W ON\n");
			}
			if(limit_neg_ & LIM_X_BIT) {
				utils::format("Limit X OFF\n");
			}
			if(limit_neg_ & LIM_Y_BIT) {
				utils::format("Limit Y OFF\n");
			}
			if(limit_neg_ & LIM_Z_BIT) {
				utils::format("Limit Z OFF\n");
			}
			if(limit_neg_ & LIM_W_BIT) {
				utils::format("Limit W OFF\n");
			}

			//　速度の計算（１／１００秒毎の更新）


			// パルス生成
			auto& step = mtu_.at_main_task().at_step();
			while((step.size() - step.length()) >= (step.size() / 32)) {
				if(fin_ == pos_) break;

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
					step.put(bits);
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
			if(n == 0) return true;

			switch(cmd) {
			case CMD::HELP:
				help_cmd_();
				break;
			case CMD::SPEED:
				if(n > 1) {
					int32_t a = speed_limit_;
					if(!get_int_(a)) {
						if(a > 0) {
							speed_limit_ = a;
						}
					}
				} else {
					utils::format("Speed limit: %d [Hz]\n") % speed_limit_;
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
			case CMD::ACCEL:
				if(n == 1) {
					utils::format("Acceleration/Deceleration: %u[Hz]\n") % accel_;
				} else if(n == 2) {
					int32_t a = accel_;
					if(get_int_(a)) {
						accel_ = a;
					} else {
						utils::format("decimal input error:\n");
					}
				}
				break;
			case CMD::LEAD:
				if(n == 1) {
					utils::format("Lead/Rad: %d, %d, %d, %d [um/rad]\n")
						% lead_.x % lead_.y % lead_.z % lead_.w;
				} else if(n == 5) {
					if(!get_xyzw_(lead_)) {
						utils::format("decimal input error:\n");
					}
				}
				break;
			case CMD::PULSE:
				if(n == 1) {
					utils::format("Pulse/Rad: %d, %d, %d, %d\n")
						% pulse_.x % pulse_.y % pulse_.z % pulse_.w;
				} else if(n == 5) {
					get_xyzw_(pulse_);
				} else {
//					utils::format("
				}
				break;
			case CMD::STOP:
				fin_ = pos_;  // 最終位置を現在の位置とする。
				mtu_.at_main_task().at_step().clear();
				break;
			case CMD::PAUSE:
				break;
			case CMD::START:
				break;
			default:
				return false;
				break;
			}
			return true;
		}
	};
}
