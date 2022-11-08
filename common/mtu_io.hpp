#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ MTU2/MTU3x 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "renesas.hpp"
#include "common/intr_utils.hpp"
#include "common/vect.h"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU 基本クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class mtu_base {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アウトプット型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class OUTPUT : uint8_t {
			NONE,					///< 出力しない
			LOW_TO_HIGH = 0b0010,	///< 初期０で、マッチで１
			HIGH_TO_LOW = 0b0101,	///< 初期１で、マッチで０
			TOGGLE = 0b0011,		///< トグル出力
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  キャプチャー型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CAPTURE : uint8_t {
			POSITIVE,	///< 立ち上がり
			NEGATIVE,	///< 立下り
			DUAL,		///< 両エッジ
			
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  キャプチャー構造体
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct capture_t {
			volatile uint32_t	all_count_;
			volatile uint16_t	ovfw_limit_;	///< オーバーフローの最大値
			volatile uint16_t	ovfw_count_;

			capture_t() : all_count_(0),
				ovfw_limit_(0),   // タイムアウト１秒
				ovfw_count_(0)
			{ }

			void clear() {
				all_count_ = 0;
				ovfw_count_ = 0;
			}
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MTU 制御クラス
		@param[in]	MTUX	MTU ユニット
		@param[in]	MTASK	メイン割り込みタスク
		@param[in]	OTASK	オーバーフロー割り込みタスク
		@param[in]	PSEL	入出力ポートオーダー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class MTUX, class MTASK = utils::null_task, class OTASK = utils::null_task,
		port_map_mtu::ORDER PSEL = port_map_mtu::ORDER::FIRST>
	class mtu_io : public mtu_base {
	public:

		typedef MTUX mtu_type;
		typedef typename MTUX::CHANNEL CHANNEL;

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PWM 出力設定構造体
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct pwm_port_t {
			CHANNEL		pwm;
			OUTPUT		out;
			port_map_mtu::ORDER	order;
			pwm_port_t() noexcept :
				pwm(), out(OUTPUT::NONE), order(port_map_mtu::ORDER::FIRST)
			{ }
			constexpr pwm_port_t(CHANNEL ch, OUTPUT o, port_map_mtu::ORDER odr = port_map_mtu::ORDER::FIRST) noexcept :
				pwm(ch), out(o), order(odr) { }
		};

	private:

		enum class MODE : uint8_t {
			NORMAL = 0b0000,
			PWM2   = 0b0011,
		};

		uint32_t	clk_base_;

		struct task_t {
			volatile uint32_t	tgr_adr_;		// TGR の実アドレス
			volatile uint32_t	ovfw_tick_;

			uint32_t	rate_;
			uint32_t	tgr_;
			uint8_t		shift_;
			OUTPUT		out_;

			capture_t	cap_;

			task_t() : tgr_adr_(MTUX::TGRA.address),
				ovfw_tick_(0),
				rate_(0), tgr_(0), shift_(0), out_(OUTPUT::NONE),
				cap_()
			{ }
		};

		static task_t	tt_;

		static MTASK	mtask_;
		static OTASK	otask_;

		CHANNEL			channel_;

		ICU::VECTOR		intr_vec_;

		uint8_t			intr_level_;


		static INTERRUPT_FUNC void cap_task_()
		{
			tt_.cap_.all_count_ = (tt_.ovfw_tick_ << 16) | rd16_(tt_.tgr_adr_);
			mtask_();
			tt_.ovfw_tick_ = 0;
		}

		static INTERRUPT_FUNC void ovf_task_()
		{
			++tt_.ovfw_tick_;
			if(tt_.ovfw_tick_ >= tt_.cap_.ovfw_limit_) {
				tt_.ovfw_tick_ = 0;
				MTUX::TCNT = 0;
				++tt_.cap_.ovfw_count_;
			}
			otask_();
		}

		static INTERRUPT_FUNC void match_task_()
		{
			mtask_();
		}

		// ch: A, B, C, D (0 to 3)
		// dv: 0 to 10
		static bool set_TCR_(typename MTUX::CHANNEL ch) noexcept
		{
			uint8_t tpsc = 0b1111;
			if(MTUX::DIVIDE_AVILITY == MTUX::CLOCK_DIVIDER::MTU3) {
				static constexpr uint8_t ckt[] = {
					0b000000,  // (0)  1/1
					0b001000,  // (1)  1/2
					0b000001,  // (2)  1/4
					0b010000,  // (3)  1/8
					0b000010,  // (4)  1/16
					0b011000,  // (5)  1/32
					0b000011,  // (6)  1/64
					0b100000,  // (7)  1/128(NG: 1/256)
					0b100000,  // (8)  1/256
					0b101000,  // (9)  1/512(NG: 1/1024)
					0b101000,  // (10) 1/1024
				};
				tpsc = ckt[tt_.shift_] & 0b111;
				MTUX::TCR2.TPSC2 = ckt[tt_.shift_] >> 3;
			} else {
				if(tt_.shift_ == 0) tpsc = 0b000;  // 1/1
				else if(tt_.shift_ == 2) tpsc = 0b001;  // 1/4
				else if(tt_.shift_ == 4) tpsc = 0b010;  // 1/16
				else if(tt_.shift_ == 6) tpsc = 0b011;  // 1/64
				if(MTUX::DIVIDE_AVILITY == MTUX::CLOCK_DIVIDER::MTU2_EXT1) {
					if(tt_.shift_ == 8) tpsc = 0b110;
				} else if(MTUX::DIVIDE_AVILITY == MTUX::CLOCK_DIVIDER::MTU2_EXT2) {
					if(tt_.shift_ == 10) tpsc = 0b111;
				} else if(MTUX::DIVIDE_AVILITY == MTUX::CLOCK_DIVIDER::MTU2_EXT3) {
					if(tt_.shift_ == 8) tpsc = 0b100;
					else if(tt_.shift_ == 10) tpsc = 0b101;
				}
			}
			if(tpsc == 0b1111) {
				return false;
			}
			static constexpr uint8_t cclr[4] = { 0b001, 0b010, 0b101, 0b110 };  // A, B, C, D
			MTUX::TCR  = MTUX::TCR.TPSC.b(tpsc)
					   | MTUX::TCR.CKEG.b(0b00)
					   | MTUX::TCR.CCLR.b(cclr[static_cast<uint8_t>(ch)]);
			return true;
		}


		static bool make_clock2_(uint32_t freq, uint32_t& match) noexcept
		{
			tt_.rate_ = freq;
			tt_.shift_ = 0;
			match = MTUX::PCLK / freq;
			while(match > 65535) {
				++tt_.shift_;
				match /= 2;
				if(tt_.shift_ > 6) {  // 1/64 まで
					return false;
				}
			}
			while(tt_.shift_ == 1 || tt_.shift_ == 3 || tt_.shift_ == 5) {  // 1/2, 1/8, 1/32 を除外
				++tt_.shift_;
				match /= 2;
			}
			return true;
		}

		static bool make_clock2e1_(uint32_t freq, uint32_t& match) noexcept
		{
			tt_.rate_ = freq;
			tt_.shift_ = 0;
			match = MTUX::PCLK / freq;
			while(match > 65535) {
				++tt_.shift_;
				match /= 2;
				if(tt_.shift_ > 8) {  // 1/256 まで
					return false;
				}
			}
			while(tt_.shift_ == 1 || tt_.shift_ == 3 || tt_.shift_ == 5 || tt_.shift_ == 7) {  // 1/2, 1/8, 1/32, 1/128 を除外
				++tt_.shift_;
				match /= 2;
			}
			return true;
		}

		static bool make_clock2e2_(uint32_t freq, uint32_t& match) noexcept
		{
			tt_.rate_ = freq;
			tt_.shift_ = 0;
			match = MTUX::PCLK / freq;
			while(match > 65535) {
				++tt_.shift_;
				match /= 2;
				if(tt_.shift_ > 10) {  // 1/1024 まで
					return false;
				}
			}
			while(tt_.shift_ == 1 || tt_.shift_ == 3 || tt_.shift_ == 5 || tt_.shift_ == 7 || tt_.shift_ == 8 ||  tt_.shift_ == 9) {  // 1/2, 1/8, 1/32, 1/128、1/256, 1/512 を除外
				++tt_.shift_;
				match /= 2;
			}
			return true;
		}

		static bool make_clock2e3_(uint32_t freq, uint32_t& match) noexcept
		{
			tt_.rate_ = freq;
			tt_.shift_ = 0;
			match = MTUX::PCLK / freq;
			while(match > 65535) {
				++tt_.shift_;
				match /= 2;
				if(tt_.shift_ > 10) {  // 1/1024 まで
					return false;
				}
			}
			while(tt_.shift_ == 1 || tt_.shift_ == 3 || tt_.shift_ == 5 || tt_.shift_ == 7 || tt_.shift_ == 9) {  // 1/2, 1/8, 1/32, 1/128、1/512 を除外
				++tt_.shift_;
				match /= 2;
			}
			return true;
		}

		static bool make_clock3_(uint32_t freq, uint32_t& match) noexcept
		{
			tt_.rate_ = freq;
			tt_.shift_ = 0;
			match = MTUX::PCLK / freq;
			if(MTUX::TGR32) {
				return true;
			}

			while(match > 65535) {
				++tt_.shift_;
				match /= 2;
				if(tt_.shift_ > 10) {  // 1/1024 まで
					return false;
				}
			}
			while(tt_.shift_ == 7 || tt_.shift_ == 9) {  // 1/128, 1/512 を除外
				++tt_.shift_;
				match /= 2;
			}
			return true;
		}


		static bool make_clock_(uint32_t freq, uint32_t& match) noexcept
		{
			bool ret = false;
			switch(MTUX::DIVIDE_AVILITY) {
			case MTUX::CLOCK_DIVIDER::MTU2:
				ret = make_clock2_(freq, match);
				break;
			case MTUX::CLOCK_DIVIDER::MTU2_EXT1:
				ret = make_clock2e1_(freq, match);
				break;
			case MTUX::CLOCK_DIVIDER::MTU2_EXT2:
				ret = make_clock2e2_(freq, match);
				break;
			case MTUX::CLOCK_DIVIDER::MTU2_EXT3:
				ret = make_clock2e3_(freq, match);
				break;
			case MTUX::CLOCK_DIVIDER::MTU3:
				ret = make_clock3_(freq, match);
				break;
			}
			return ret;
		}


		bool set_output_type_(typename MTUX::CHANNEL ch, OUTPUT out) noexcept
		{
			MTUX::TIOR.set(ch, static_cast<uint8_t>(out));
			return out == OUTPUT::TOGGLE;
		}


		void set_interruptABCD_(typename MTUX::CHANNEL ch) noexcept // ABCD の割り込み
		{
			auto cvec = MTUX::get_vector(ch);
			intr_vec_ = icu_mgr::set_interrupt(cvec, match_task_, intr_level_);
			if(intr_vec_ != ICU::VECTOR::NONE) {
				MTUX::TIER |= 1 << static_cast<uint8_t>(ch);  // ABCD の割り込み
			}
		}


		bool start_(CHANNEL ch, uint32_t freq, OUTPUT out, uint8_t lvl, MODE md) noexcept
		{
			if(!power_mgr::turn(MTUX::PERIPHERAL)) {
				return false;
			}

			MTUX::enable(false);
			MTUX::TIER = 0;
			MTUX::TIOR.disable();

			intr_level_ = lvl;
			channel_ = ch;
			tt_.out_ = out;

			if(out != OUTPUT::NONE) {
				bool pena = true;
				port_map_mtu::turn(MTUX::PERIPHERAL, MTUX::get_port_map_channel(ch), pena, PSEL);
			}

			uint32_t match;
			if(!make_clock_(freq, match)) {
				power_mgr::turn(MTUX::PERIPHERAL, false);
				return false;
			}

			if(set_output_type_(ch, out)) {
				bool mod = match & 1;
				match /= 2;
				if(mod) ++match;
			}
			if(!set_TCR_(ch)) {
				power_mgr::turn(MTUX::PERIPHERAL, false);
				return false;
			}

			// MTU2 系では、TMDR、MTU3 系では TMDR1 となっている。
			// これを回避する為、MTU2 系では、TMDR と同一の機能を TMDR1 にも与えている。
			MTUX::TMDR1 = static_cast<uint8_t>(md);

			if(intr_level_ > 0) {
				set_interruptABCD_(ch);
			}

			tt_.tgr_ = match;
			MTUX::TGR[ch] = match - 1;

			MTUX::TCNT = 0;

			return true;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		mtu_io() noexcept : clk_base_(MTUX::PCLK), channel_(CHANNEL::A),
			intr_vec_(ICU::VECTOR::NONE), intr_level_(0)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  ノーマル・モード（コンペア・マッチ・タイマー）
			@param[in]	ch		出力チャネル
			@param[in]	freq	出力周波数
			@param[in]	out		出力タイプ
			@param[in]	lvl		割り込みレベル
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start_normal(CHANNEL ch, uint32_t freq, OUTPUT out, uint8_t lvl = 0) noexcept
		{
			static_assert(MTUX::PERIPHERAL != peripheral::MTU5, "Normal mode cannot select MTU5");

			auto ret = start_(ch, freq, out, lvl, MODE::NORMAL);
			if(ret) {
				MTUX::enable();
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  インターバルタイマー（ポート出力無し）
			@param[in]	freq	周波数
			@param[in]	lvl		割り込みレベル
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t freq, uint8_t lvl = 0) noexcept
		{
			return start_normal(CHANNEL::A, freq, OUTPUT::NONE, lvl);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  コンペア・マッチ・タイマー周期の再設定
			@param[in]	ch		設定チャネル
			@param[in]	freq	周波数
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		static bool set_freq(CHANNEL ch, uint32_t freq) noexcept
		{
			uint32_t match;
			if(!make_clock_(freq, match)) {
				return false;
			}

			set_TCR_(ch);

			if(tt_.out_ == OUTPUT::TOGGLE) {
				bool mod = match & 1;
				match /= 2;
				if(mod) ++match;
			}

			if((match - 1) < MTUX::TCNT()) {
				MTUX::TCNT = 0;
			}
			MTUX::TGR[ch] = match - 1;
			tt_.tgr_ = match;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  PWM2 開始（１出力）
			@param[in]	mch		PWM 周期チャネル
			@param[in]	freq	PWM 周波数
			@param[in]	po		PWM 出力設定
			@param[in]	lvl		割り込みレベル
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start_pwm2(CHANNEL mch, uint32_t freq, const pwm_port_t& po, uint8_t lvl = 0) noexcept
		{
			auto ret = start_(mch, freq, OUTPUT::NONE, lvl, MODE::PWM2);
			if(ret) {
				if(po.out != OUTPUT::NONE) {
					bool pena = true;
					port_map_mtu::turn(MTUX::PERIPHERAL, MTUX::get_port_map_channel(po.pwm), pena, po.order);
				}
				MTUX::TIOR.set(po.pwm, static_cast<uint8_t>(po.out));
				set_pwm_duty(po.pwm, 0);
				MTUX::enable();
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  PWM2 開始（２出力）
			@param[in]	mch		PWM 周期チャネル
			@param[in]	freq	PWM 周波数
			@param[in]	po1		PWM1 出力設定
			@param[in]	po2		PWM2 出力設定
			@param[in]	lvl		割り込みレベル
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start_pwm2(CHANNEL mch, uint32_t freq, const pwm_port_t& po1, const pwm_port_t& po2, uint8_t lvl = 0) noexcept
		{
			auto ret = start_(mch, freq, OUTPUT::NONE, lvl, MODE::PWM2);  // PWM2 mode
			if(ret) {
				bool pena = true;
				if(po1.out != OUTPUT::NONE) {
					port_map_mtu::turn(MTUX::PERIPHERAL, MTUX::get_port_map_channel(po1.pwm), pena, po1.order);
				}
				MTUX::TIOR.set(po1.pwm, static_cast<uint8_t>(po1.out));
				set_pwm_duty(po1.pwm, 0);

				if(po2.out != OUTPUT::NONE) {
					port_map_mtu::turn(MTUX::PERIPHERAL, MTUX::get_port_map_channel(po2.pwm), pena, po2.order);
				}
				MTUX::TIOR.set(po2.pwm, static_cast<uint8_t>(po2.out));
				set_pwm_duty(po2.pwm, 0);
				MTUX::enable();
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  PWM2 開始（３出力）
			@param[in]	mch		PWM 周期チャネル
			@param[in]	freq	PWM 周波数
			@param[in]	po		PWM 出力設定
			@param[in]	lvl		割り込みレベル
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start_pwm2(CHANNEL mch, uint32_t freq, const pwm_port_t po[3], uint8_t lvl = 0) noexcept
		{
			auto ret = start_(mch, freq, OUTPUT::NONE, lvl, MODE::PWM2);
			if(ret) {
				for(uint32_t i = 0; i < 3; ++i) {
					if(po[i].out != OUTPUT::NONE) {
						bool pena = true;
						port_map_mtu::turn(MTUX::PERIPHERAL, MTUX::get_port_map_channel(po[i].pwm), pena, po[i].order);
					}
					MTUX::TIOR.set(po[i].pwm, static_cast<uint8_t>(po[i].out));
					set_pwm_duty(po[i].pwm, 0);
				}
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  PWM デューティー設定
			@param[in]	ch		出力チャネル
			@param[in]	duty	デューティー（duty / 65535）
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool set_pwm_duty(CHANNEL ch, uint16_t duty) noexcept
		{
			if(channel_ == ch) return false;

			MTUX::TGR[ch] = (static_cast<uint32_t>(MTUX::TGR[channel_]) * duty) >> 16;

			return true;
		}





		//-----------------------------------------------------------------//
		/*!
			@brief  ベース・クロック（インプット・キャプチャ）の設定 @n
					※MTU モジュールへの供給クロックのＮ分の１を設定
			@param[in]	clk	ベース・クロック
		*/
		//-----------------------------------------------------------------//
		void set_base_clock(uint32_t clk) noexcept {
			uint32_t a = MTUX::PCLK;
			while(a < clk) {
				a <<= 1;
			}
			clk_base_ = a;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ベース・クロックの取得
			@return ベース・クロック
		*/
		//-----------------------------------------------------------------//
		uint32_t get_base_clock() const noexcept { return clk_base_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  インプットキャプチャ開始 @n
					※カウントクロックは「set_limit_clock」により @n
					変更が可能。
			@param[in]	ch		入力チャネル
			@param[in]	ct		キャプチャ型
			@param[in]	lvl		割り込みレベル（割り込みを使わない場合エラー）
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start_capture(CHANNEL ch, CAPTURE cap, uint8_t lvl) noexcept
		{
			if(lvl == 0) return false;

			// MTU5 はインプットキャプチャとして利用不可
			if(MTUX::PERIPHERAL == peripheral::MTU5) {
				return false;
			}

			power_mgr::turn(MTUX::PERIPHERAL);

			intr_level_ = lvl;
			bool pena = true;
			bool neg = false;
			bool inp = true;
			port_map_mtu::turn(MTUX::PERIPHERAL, MTUX::get_port_map_channel(ch), pena, PSEL, neg, inp);

			uint8_t ctd = 0;
			switch(cap) {
			case CAPTURE::POSITIVE: ctd = 0b1000; break;
			case CAPTURE::NEGATIVE: ctd = 0b1001; break;
			case CAPTURE::DUAL:     ctd = 0b1011; break;
			default: break;
			}
			MTUX::TIOR.set(ch, ctd);

			uint32_t dv = MTUX::PCLK / clk_base_;
			--dv;
			if(dv >= 10) dv = 10;
			tt_.shift_ = dv;

			set_TCR_(ch);
			MTUX::TMDR1 = 0x00;  // 通常動作

			if(lvl > 0) {
				icu_mgr::set_interrupt(MTUX::TCIV, ovf_task_, lvl);
				auto cvec = MTUX::get_vector(ch);
				icu_mgr::set_interrupt(cvec, cap_task_, lvl);
				MTUX::TIER = (1 << static_cast<uint8_t>(ch)) | MTUX::TIER.TCIEV.b();
			}

			tt_.cap_.clear();

			// 各チャネルに相当するジャネラルレジスタ
			MTUX::TGR[ch] = 0x0000;

			MTUX::TCNT = 0;
			MTUX::enable();

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  位相係数モード開始（モード１）@n
					・MTCLKA, MTCLKB に入力された位相の異なる信号でカウンター更新
			@param[in]	ch		出力チャネル
			@param[in]	level	割り込みレベル
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start_count_phase(typename MTUX::CHANNEL ch, uint8_t level = 0) noexcept
		{
			// 工事中
			if(peripheral::MTU1 == MTUX::PERIPHERAL || peripheral::MTU2 == MTUX::PERIPHERAL) {
			} else {
				return false;
			}

			power_mgr::turn(MTUX::PERIPHERAL);

			intr_level_ = level;
#if 0
			bool pena = (ot != OUTPUT_TYPE::NONE);
			port_map_mtu::turn(MTUX::PERIPHERAL, MTUX::get_port_map_channel(ch), pena, PSEL);

			set_output_type_(ch, ot, match);

			set_TCR_(ch, dv);
			MTUX::TMDR1.MD = 0b0100;  // 位相係数 mode 1

			// 各チャネルに相当するジャネラルレジスタ
			tt_.tgr_adr_ = MTUX::TGRA.address + static_cast<uint32_t>(ch) * 2;
			wr16_(tt_.tgr_adr_, match - 1);
#endif
			MTUX::TCNT = 0;
			MTUX::enable();

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  同期 @n
					※主にインターバルタイマーとして使う場合の同期
		*/
		//-----------------------------------------------------------------//
		void sync() noexcept
		{
			if(intr_level_ > 0) {
				auto tmp = tt_.main_tick_;
				while(tmp == tt_.main_tick_) { }
			} else {  // インターバルの周期が CPU ループに対して、短い場合は、正確に機能しないので注意！
				auto tmp = MTUX::TCNT();
				while(1) {
					auto tmp2 = MTUX::TCNT();
					if(tmp2 < tmp) break;
					tmp = tmp2;
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  停止
		*/
		//-----------------------------------------------------------------//
		void stop() noexcept
		{
			MTUX::TIER = 0x00;
			MTUX::enable(false);
//			icu_mgr::set_level(MTUX::get_vec(MTUX::interrupt::OVF), 0);
//			port_map::turn(MTUX::PERIPHERAL, static_cast<port_map::channel>(ch), false);
			power_mgr::turn(MTUX::PERIPHERAL, false);
			intr_level_ = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	周期を取得
			@param[in]	real	「true」にした場合、実際に設定された周波数
			@return 周期
		 */
		//-----------------------------------------------------------------//
		static uint32_t get_rate(bool real = false) noexcept
		{
			if(real) {
				uint32_t rate = (MTUX::PCLK >> tt_.shift_) / tt_.tgr_;
				if(tt_.out_ == OUTPUT::TOGGLE) {
					rate >>= 1;
				}
				return rate;
			} else {
				return tt_.rate_;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターの取得
			@return 割り込みベクター
		*/
		//-----------------------------------------------------------------//
		auto get_intr_vec() const noexcept { return intr_vec_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  キャプチャ構造体の参照（RO）
			@return	キャプチャ構造体
		*/
		//-----------------------------------------------------------------//
		static const capture_t& get_capture() noexcept { return tt_.cap_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  キャプチャ構造体の参照
			@return	キャプチャ構造体
		*/
		//-----------------------------------------------------------------//
		static capture_t& at_capture() noexcept { return tt_.cap_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  MAIN tick の取得
			@return	MAIN tick
		*/
		//-----------------------------------------------------------------//
		static uint32_t get_main_tick() noexcept { return tt_.main_tick_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  MTASK クラスの参照
			@return MTASK クラス
		*/
		//-----------------------------------------------------------------//
		static MTASK& at_main_task() noexcept { return mtask_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  MTASK クラスの参照
			@return MTASK クラス
		*/
		//-----------------------------------------------------------------//
		static MTASK& at_task() noexcept { return mtask_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  OTASK クラスの参照
			@return OTASK クラス
		*/
		//-----------------------------------------------------------------//
		static OTASK& at_ovfl_task() noexcept { return otask_; }
	};

	template <class MTUX, class MTASK, class OTASK, port_map_mtu::ORDER PSEL>
		typename mtu_io<MTUX, MTASK, OTASK, PSEL>::task_t mtu_io<MTUX, MTASK, OTASK, PSEL>::tt_;
	template <class MTUX, class MTASK, class OTASK, port_map_mtu::ORDER PSEL>
		MTASK mtu_io<MTUX, MTASK, OTASK, PSEL>::mtask_;
	template <class MTUX, class MTASK, class OTASK, port_map_mtu::ORDER PSEL>
		OTASK mtu_io<MTUX, MTASK, OTASK, PSEL>::otask_;
}
