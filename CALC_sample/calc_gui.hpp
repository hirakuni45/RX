#pragma once
//=====================================================================//
/*! @file
    @brief  GUI 関数電卓・クラス @n
			RX65N Envision Kit @n
			RX72N Envision Kit @n
			calc_gui
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#ifndef EMU
#include "common/renesas.hpp"

#include "common/fixed_fifo.hpp"
#include "common/sci_i2c_io.hpp"
#include "chip/FT5206.hpp"
#endif

#include "graphics/font8x16.hpp"
#include "graphics/kfont.hpp"
#include "graphics/graphics.hpp"
#include "graphics/simple_dialog.hpp"
#include "graphics/scaling.hpp"

#include "gui/widget_director.hpp"

#include "common/format.hpp"
#include "common/fixed_string.hpp"

#include "resource.hpp"

namespace app {

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    /*!
        @brief  CALC GUI クラス
		@param[in]	CALC_CMD	calc_cmd クラス型
    */
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class CALC_CMD>
    struct calc_gui {

		typedef typename CALC_CMD::NVAL NVAL;
		typedef typename CALC_CMD::SYMBOL SYMBOL;
		typedef typename CALC_CMD::FUNC FUNC;

		static constexpr int16_t  DISP_OFS_X = 4;
		static constexpr int16_t  DISP_OFS_Y = 6;

		static constexpr int16_t LCD_X = 480;
		static constexpr int16_t LCD_Y = 272;
		static constexpr auto PIX = graphics::pixel::TYPE::RGB565;

		CALC_CMD&	calc_cmd_;

#if defined(SIG_RX65N) || defined(SIG_RX72N)
		typedef utils::fixed_fifo<uint8_t, 64> RB64;
		typedef utils::fixed_fifo<uint8_t, 64> SB64;
		typedef device::sci_i2c_io<board_profile::FT5206_SCI_CH, RB64, SB64, board_profile::FT5206_SCI_ORDER> FT5206_I2C;
		typedef device::glcdc_mgr<device::GLCDC, LCD_X, LCD_Y, PIX> GLCDC;
#endif

#ifdef EMU
		template <uint32_t LCDX, uint32_t LCDY>
		class glcdc_emu {
		public:
			static constexpr uint32_t	width  = LCDX;
			static constexpr uint32_t	height = LCDY;
			static constexpr uint32_t	line_width = width;

		private:
			uint16_t fb_[LCDX * LCDY];

		public:
			void sync_vpos() { }

			void* get_fbp() { return fb_; }
		};
		typedef glcdc_emu<LCD_X, LCD_Y> GLCDC;
#endif

		typedef graphics::font8x16 AFONT;
		typedef graphics::kfont<16, 16> KFONT;
		typedef graphics::font<AFONT, KFONT> FONT;

		// ソフトウェアーレンダラー
//		typedef graphics::render<GLCDC, FONT> RENDER;
		// RX65N/RX72N DRW2D Engine
		typedef device::drw2d_mgr<GLCDC, FONT> RENDER;
		// 標準カラーインスタンス
		typedef graphics::def_color DEF_COLOR;

	private:

		GLCDC	glcdc_;
		AFONT	afont_;
		KFONT	kfont_;
		FONT	font_;
		RENDER	render_;
#ifndef EMU
		FT5206_I2C	ft5206_i2c_;
		typedef chip::FT5206<FT5206_I2C> TOUCH;
#else
		class touch_emu {
		public:

			struct touch_t {
				vtx::spos	pos;
			};

		private:
			touch_t	touch_[4];
			uint32_t	num_;

		public:
			touch_emu() : num_(0) { }

			uint32_t get_touch_num() const { return num_; }

			const auto& get_touch_pos(uint32_t idx) const {
				if(idx >= 4) idx = 0;
				return touch_[idx];
			}

			void update() { }

			void set_pos(const vtx::spos& pos)
			{
				touch_[0].pos = pos;
				num_ = 1;
			}

			void reset() { num_ = 0; }
		};
		typedef touch_emu TOUCH;
#endif
		TOUCH	touch_;
		// RX65N Envision Kit: INT to P02(IRQ10), not use
		// RX72N Envision Kit: INT to P34(IRQ4), not use

		typedef gui::simple_dialog<RENDER, TOUCH> DIALOG;
		DIALOG	dialog_;

		typedef gui::widget_director<RENDER, TOUCH, 60> WIDD;
		WIDD	widd_;

		static constexpr int16_t BTN_W = 41;
		static constexpr int16_t BTN_H = 38;
		static constexpr int16_t ORG_X = 8;
		static constexpr int16_t ORG_Y = 94;
		static constexpr int16_t SPC_X = 47;
		static constexpr int16_t SPC_Y = 44;

		constexpr int16_t LOC_X(int16_t x)
		{
			return ORG_X + SPC_X * x;
		}

		constexpr int16_t LOC_Y(int16_t y)
		{
			return ORG_Y + SPC_Y * y;
		}

		typedef gui::widget WIDGET;

		typedef gui::button BUTTON;
		BUTTON	no0_;
		BUTTON	no1_;
		BUTTON	no2_;
		BUTTON	no3_;
		BUTTON	no4_;
		BUTTON	no5_;
		BUTTON	no6_;
		BUTTON	no7_;
		BUTTON	no8_;
		BUTTON	no9_;

		BUTTON	del_;
		BUTTON	ac_;

		BUTTON	mul_;
		BUTTON	div_;
		BUTTON	add_;
		BUTTON	sub_;

		BUTTON	poi_;  // .
		BUTTON	x10_;
		BUTTON	ans_;
		BUTTON	equ_;  // =

		BUTTON	sin_;
		BUTTON	cos_;
		BUTTON	tan_;
		BUTTON	pai_;

		BUTTON	sqr_;   // x^2
		BUTTON	sqrt_;  // √
		BUTTON	pow_;	// x^y

		BUTTON	log_;
		BUTTON	ln_;
		BUTTON	inv_;	// 1/x

		BUTTON	fc_;
		BUTTON	angt_;

		BUTTON	left_;
		BUTTON	right_;
		BUTTON	pin_;  // (
		BUTTON	pot_;  // )

		BUTTON	setup_;
		BUTTON	sym_;
		BUTTON	sym_in_;
		BUTTON	sym_out_;

		typedef utils::fixed_string<256> STR;
		STR			cbackup_;
		STR			cbuff_;
		uint32_t	cbuff_pos_;
		uint32_t	del_len_;

		static constexpr int16_t limit_ = 3;
		vtx::spos	cur_pos_;

		bool		fc_mode_;

		int			nest_;

		uint32_t	symbol_idx_;

		int			shift_;

		void clear_win_()
		{
			cbackup_.clear();
			cbuff_.clear();
			cbuff_pos_ = 0;
			del_len_ = 0;
			cur_pos_.set(0);
			render_.set_fore_color(DEF_COLOR::Darkgray);
			render_.round_box(vtx::srect(0, 0, 480, 16 * 5 + 6), 8);
			nest_ = 0;
//			symbol_.set_value(SYMBOL::NAME::ANS, NVAL(0));
//			for(uint8_t i = static_cast<uint8_t>(SYMBOL::NAME::V0); i <= static_cast<uint8_t>(SYMBOL::NAME::V9); i++) {
//				symbol_.set_value(static_cast<SYMBOL::NAME>(i), NVAL(0));
//			}
			symbol_idx_ = 0;
			shift_ = 0;
		}

		typedef utils::fixed_string<512> OUTSTR;


		void conv_cha_(char ch, OUTSTR& out)
		{
			auto code = static_cast<uint8_t>(ch);
			if(code >= 0x80 && code < 0xc0) {
				out += calc_cmd_.at_symbol().get_name(static_cast<typename SYMBOL::NAME>(code));
				return;
			} else if(code >= 0xc0) {
				out += calc_cmd_.at_func().get_name(static_cast<typename FUNC::NAME>(code));
				return;
			}
			switch(code) {
			case '0': out += "０"; break;
			case '1': out += "１"; break;
			case '2': out += "２"; break;
			case '3': out += "３"; break;
			case '4': out += "４"; break;
			case '5': out += "５"; break;
			case '6': out += "６"; break;
			case '7': out += "７"; break;
			case '8': out += "８"; break;
			case '9': out += "９"; break;
			case 'A': out += "Ａ"; break;
			case 'B': out += "Ｂ"; break;
			case 'C': out += "Ｃ"; break;
			case 'D': out += "Ｄ"; break;
			case 'E': out += "Ｅ"; break;
			case 'F': out += "Ｆ"; break;
			case '+': out += "＋"; break;
			case '-': out += "－"; break;
			case '/': out += "÷"; break;
			case '*': out += "×"; break;
			case '?': out += "？"; break;
			default:
				if(ch >= 0) {
					out += ch;
				}
				break;
			}
		}


		uint32_t size_cha_(char ch)
		{
			auto code = static_cast<uint8_t>(ch);
			uint32_t l = 8;
			if(code >= 0x80 && code < 0xc0) {
				calc_cmd_.at_symbol().get_name(static_cast<typename SYMBOL::NAME>(code));
				l = 16;
			} else if(code >= 0xc0) {
				l = strlen(calc_cmd_.at_func().get_name(static_cast<typename FUNC::NAME>(code)));
				l *= 8;
			} else if(ch >= '0' && ch <= '9') {
				l = 16;
			} else if(ch == '+' || ch == '-' || ch == '/' || ch == '*') {
				l = 16;
			}
			return l;
		}


		OUTSTR conv_str_(const char* str)
		{
			OUTSTR out;
			char ch;
			while((ch = *str++) != 0) {
				conv_cha_(ch, out);
			}
			return out;
		}


		void update_calc_()
		{
			if(cbuff_pos_ == cbuff_.size()) return;

			if(cbuff_pos_ > cbuff_.size()) {
				if(del_len_ > 0) {
					auto x = cur_pos_.x - del_len_;
					render_.set_fore_color(DEF_COLOR::Darkgray);
					render_.fill_box(vtx::srect(DISP_OFS_X + x, DISP_OFS_Y + cur_pos_.y * 20, del_len_, 16));
					cur_pos_.x -= del_len_;
					del_len_ = 0;
				}
			} else {
				render_.set_fore_color(DEF_COLOR::White);
				auto i = cbuff_pos_;
				int x = cur_pos_.x + DISP_OFS_X;
				while(i < cbuff_.size()) {
					OUTSTR tmp;
					conv_cha_(cbuff_[i], tmp);
					x = render_.draw_text(vtx::spos(x, DISP_OFS_Y + cur_pos_.y * 20), tmp.c_str());
					++i;
				}
				cur_pos_.x = x - DISP_OFS_X;
			}
			cbuff_pos_ = cbuff_.size();
		}


		void parse_cbuff_(OUTSTR& out)
		{
			uint32_t i = 0;
			while(i < cbuff_.size()) {
				conv_cha_(cbuff_[i], out);
				++i;
			}
		}


		// 答え表示
#if 0
		void draw_ans_(const NVAL& in, bool ok)
		{
			char tmp[ANS_NUM+1];
			if(ok) {
				NVAL ans = in;
				if(shift_ != 0) {
					auto exp = NVAL::exp10(NVAL(shift_));
					ans *= exp;
				}
				ans(ANS_NUM, tmp, sizeof(tmp));
				// zero supless
				auto l = strlen(tmp);
				while(l > 0) {
					--l;
					if(tmp[l] != '0') break;
					else {
						tmp[l] = 0;
					}
				}
				if(l > 0) { if(tmp[l] == '.') tmp[l] = 0; }
			} else {
				utils::sformat("?", tmp, sizeof(tmp));
			}
			utils::format(" %s\n") % tmp;

			auto out = conv_str_(tmp);
			render_.set_fore_color(DEF_COLOR::Darkgray);
			render_.round_box(vtx::srect(0, DISP_OFS_Y + 20 * 3, 480, 20), 6, false, true);
			render_.set_fore_color(DEF_COLOR::White);
			render_.draw_text(vtx::spos(DISP_OFS_X, DISP_OFS_Y + 20 * 3), out.c_str());
			if(shift_ != 0) {  // exp 表示
				render_.set_fore_color(DEF_COLOR::Black);
				render_.fill_box(vtx::srect(480 - DISP_OFS_X - 24 - 2, DISP_OFS_Y + 20 * 3, 32, 20));
				char tmp[8];
				utils::sformat("%+d", tmp, sizeof(tmp)) % -shift_;
				render_.set_fore_color(DEF_COLOR::White);
				render_.draw_text(vtx::spos(480 - DISP_OFS_X - 24, DISP_OFS_Y + 20 * 3 + 1), tmp);
			}
		}
#endif

		// 答え表示
		void update_equ_()
		{
			if(cbuff_.empty()) {
				cbuff_ = cbackup_;
				return;
			}

			// 括弧が開いていたら自動で閉じる
			while(nest_ > 0) { cbuff_ += ')'; nest_--; }
			update_calc_();

			calc_cmd_(cbuff_.c_str());

//			auto ok = arith_.analize(cbuff_.c_str());
//			auto ans = arith_();
//			symbol_.set_value(SYMBOL::NAME::ANS, ans);
//			draw_ans_(ans, ok);

			OUTSTR cmd;
			parse_cbuff_(cmd);
			utils::format("%s\n") % cmd.c_str();

			cbackup_ = cbuff_;
			cbuff_.clear();
			cur_pos_.x = 0;
			cur_pos_.y++;
			if(cur_pos_.y >= limit_) {
				render_.move(vtx::srect(DISP_OFS_X, DISP_OFS_Y + 20, 480 - DISP_OFS_X * 2, 20 * 2), vtx::spos(DISP_OFS_X, DISP_OFS_Y));
				render_.set_fore_color(DEF_COLOR::Darkgray);
				render_.fill_box(vtx::srect(DISP_OFS_X, DISP_OFS_Y + 20 * 2, 480 - DISP_OFS_X * 2, 20));
				cur_pos_.y = limit_ - 1;
			}
			shift_ = 0;
		}


		void update_fc_()
		{
			if(fc_mode_) {
				sin_.set_title("asin");
				cos_.set_title("acos");
				tan_.set_title("atan");
				pai_.set_title("е");
			} else {
				sin_.set_title("sin");
				cos_.set_title("cos");
				tan_.set_title("tan");
				pai_.set_title("π");
			}
		}

	public:
		//-------------------------------------------------------------//
		/*!
			@brief  GUI コンストラクタ
			@param[in]	calc_cmd	calc_cmd クラスの参照
		*/
		//-------------------------------------------------------------//
		calc_gui(CALC_CMD& calc_cmd) noexcept :
			calc_cmd_(calc_cmd),
#ifndef EMU
			glcdc_(nullptr, reinterpret_cast<uint16_t*>(board_profile::LCD_ORG)),
#else
			glcdc_(),
#endif
			afont_(), kfont_(), font_(afont_, kfont_),
			render_(glcdc_, font_),
#ifndef EMU
			ft5206_i2c_(), touch_(ft5206_i2c_),
#else
			touch_(),
#endif
			dialog_(render_, touch_),
			widd_(render_, touch_),
			no0_(vtx::srect(LOC_X(5), LOC_Y(3), BTN_W, BTN_H), "０"),
			no1_(vtx::srect(LOC_X(5), LOC_Y(2), BTN_W, BTN_H), "１"),
			no2_(vtx::srect(LOC_X(6), LOC_Y(2), BTN_W, BTN_H), "２"),
			no3_(vtx::srect(LOC_X(7), LOC_Y(2), BTN_W, BTN_H), "３"),
			no4_(vtx::srect(LOC_X(5), LOC_Y(1), BTN_W, BTN_H), "４"),
			no5_(vtx::srect(LOC_X(6), LOC_Y(1), BTN_W, BTN_H), "５"),
			no6_(vtx::srect(LOC_X(7), LOC_Y(1), BTN_W, BTN_H), "６"),
			no7_(vtx::srect(LOC_X(5), LOC_Y(0), BTN_W, BTN_H), "７"),
			no8_(vtx::srect(LOC_X(6), LOC_Y(0), BTN_W, BTN_H), "８"),
			no9_(vtx::srect(LOC_X(7), LOC_Y(0), BTN_W, BTN_H), "９"),
			del_(vtx::srect(LOC_X(8), LOC_Y(0), BTN_W, BTN_H), "DEL"),
			ac_ (vtx::srect(LOC_X(9), LOC_Y(0), BTN_W, BTN_H), "AC"),
			mul_(vtx::srect(LOC_X(8), LOC_Y(1), BTN_W, BTN_H), "×"),
			div_(vtx::srect(LOC_X(9), LOC_Y(1), BTN_W, BTN_H), "÷"),
			add_(vtx::srect(LOC_X(8), LOC_Y(2), BTN_W, BTN_H), "＋"),
			sub_(vtx::srect(LOC_X(9), LOC_Y(2), BTN_W, BTN_H), "－"),
			poi_(vtx::srect(LOC_X(6), LOC_Y(3), BTN_W, BTN_H), "・"),
			x10_(vtx::srect(LOC_X(7), LOC_Y(3), BTN_W, BTN_H), "X10"),
			ans_(vtx::srect(LOC_X(8), LOC_Y(3), BTN_W, BTN_H), "Ans"),
			equ_(vtx::srect(LOC_X(9), LOC_Y(3), BTN_W, BTN_H), "＝"),

			sin_(vtx::srect(LOC_X(4), LOC_Y(0), BTN_W, BTN_H), "sin"),
			cos_(vtx::srect(LOC_X(4), LOC_Y(1), BTN_W, BTN_H), "cos"),
			tan_(vtx::srect(LOC_X(4), LOC_Y(2), BTN_W, BTN_H), "tan"),
			pai_(vtx::srect(LOC_X(4), LOC_Y(3), BTN_W, BTN_H), "π"),

			sqr_ (vtx::srect(LOC_X(3), LOC_Y(0), BTN_W, BTN_H)),
			sqrt_(vtx::srect(LOC_X(3), LOC_Y(1), BTN_W, BTN_H), "√"),
			pow_ (vtx::srect(LOC_X(3), LOC_Y(2), BTN_W, BTN_H)),

			log_(vtx::srect(LOC_X(2), LOC_Y(0), BTN_W, BTN_H), "log"),
			ln_ (vtx::srect(LOC_X(2), LOC_Y(1), BTN_W, BTN_H), "ln"),
			inv_(vtx::srect(LOC_X(2), LOC_Y(2), BTN_W, BTN_H)),

			fc_ (vtx::srect(LOC_X(0), LOC_Y(0), BTN_W, BTN_H), "FC"),
			angt_(vtx::srect(LOC_X(0), LOC_Y(1), BTN_W, BTN_H), "Deg"),

			left_ (vtx::srect(LOC_X(0), LOC_Y(3), BTN_W, BTN_H), "<--"),
			right_(vtx::srect(LOC_X(1), LOC_Y(3), BTN_W, BTN_H), "-->"),
			pin_(vtx::srect(LOC_X(2), LOC_Y(3), BTN_W, BTN_H), "（"),
			pot_(vtx::srect(LOC_X(3), LOC_Y(3), BTN_W, BTN_H), "）"),

			setup_   (vtx::srect(LOC_X(0), LOC_Y(2), BTN_W, BTN_H), "＠"),
			sym_     (vtx::srect(LOC_X(1), LOC_Y(0), BTN_W, BTN_H), "V0"),
			sym_in_  (vtx::srect(LOC_X(1), LOC_Y(1), BTN_W, BTN_H), "Min"),
			sym_out_ (vtx::srect(LOC_X(1), LOC_Y(2), BTN_W, BTN_H), "Rcl"),

			cbackup_(), cbuff_(), cbuff_pos_(0), del_len_(0), cur_pos_(0),
			fc_mode_(false), nest_(0), symbol_idx_(0), shift_(0)
		{ }


		//-------------------------------------------------------------//
		/*!
			@brief  widget 追加
			@param[in]	w	widget
			@return 正常なら「true」
		*/
		//-------------------------------------------------------------//
		bool insert_widget(gui::widget* w) noexcept {
			return widd_.insert(w);
		}


		//-------------------------------------------------------------//
		/*!
			@brief  widget 削除
			@param[in]	w	widget
			@return 正常なら「true」
		*/
		//-------------------------------------------------------------//
		void remove_widget(gui::widget* w) noexcept {
			widd_.remove(w);
		}


		//-------------------------------------------------------------//
		/*!
			@brief  GLCDC クラスの参照
			@return GLCDC クラス
		*/
		//-------------------------------------------------------------//
		auto& at_glcdc() noexcept { return glcdc_; }


		//-------------------------------------------------------------//
		/*!
			@brief  TOUCH クラスの参照
			@return TOUCH クラス
		*/
		//-------------------------------------------------------------//
		auto& at_touch() noexcept { return touch_; }


		//-------------------------------------------------------------//
		/*!
			@brief  レンダーの参照
			@return レンダー
		*/
		//-------------------------------------------------------------//
		RENDER& at_render() noexcept { return render_; }


		//-------------------------------------------------------------//
		/*!
			@brief  開始
		*/
		//-------------------------------------------------------------//
		void start() noexcept
		{
#ifndef EMU
			using namespace board_profile;
			{  // GLCDC の初期化
				LCD_DISP::DIR  = 1;
				LCD_LIGHT::DIR = 1;
				LCD_DISP::P  = 0;  // DISP Disable
				LCD_LIGHT::P = 0;  // BackLight Disable (No PWM)
				if(glcdc_.start(device::ICU::LEVEL::_2)) {
					utils::format("Start GLCDC\n");
					LCD_DISP::P  = 1;  // DISP Enable
					LCD_LIGHT::P = 1;  // BackLight Enable (No PWM)
					if(!glcdc_.control(GLCDC::CONTROL_CMD::START_DISPLAY)) {
						utils::format("GLCDC ctrl fail...\n");
					}
				} else {
					utils::format("GLCDC Fail\n");
				}
			}

			{  // FT5206 touch screen controller
				TOUCH::reset<FT5206_RESET>();
				auto intr_lvl = device::ICU::LEVEL::_1;
				if(!ft5206_i2c_.start(FT5206_I2C::MODE::MASTER, FT5206_I2C::SPEED::STANDARD, intr_lvl)) {
					utils::format("FT5206 I2C Start Fail...\n");
				}
				if(!touch_.start()) {
					utils::format("FT5206 Start Fail...\n");
				}
			}
			{  // render class の初期化
				render_.start(device::ICU::LEVEL::_2);
			}
#endif
		}


		//-------------------------------------------------------------//
		/*!
			@brief  タッチ・パネルの設定
		*/
		//-------------------------------------------------------------//
		void setup_touch_panel() noexcept
		{
			render_.sync_frame();
			dialog_.modal(vtx::spos(400, 60),
				"Touch panel device wait...\nPlease touch it with some screen.");
			uint8_t nnn = 0;
			while(1) {
				render_.sync_frame();
				touch_.update();
				auto num = touch_.get_touch_num();
				if(num == 0) {
					++nnn;
					if(nnn >= 60) break;
				} else {
					nnn = 0;
				}
			}
			render_.clear(DEF_COLOR::Black);
		}


		//-------------------------------------------------------------//
		/*!
			@brief  GUI のセットアップ
		*/
		//-------------------------------------------------------------//
		void setup() noexcept
		{

//			for(int y = 0; y < 80; ++y) {
//				render_.line_h(16*16+(y << 4), 16*16+4, 16*300);
//			}

//			render_.round_box(vtx::srect(16, 16, 300, 100), 16);

// return;
			no0_.set_layer(WIDGET::LAYER::_0);
			no0_.at_select_func() = [=](uint32_t id) { cbuff_ += '0'; };
			no1_.set_layer(WIDGET::LAYER::_0);
			no1_.at_select_func() = [=](uint32_t id) { cbuff_ += '1'; };
			no2_.set_layer(WIDGET::LAYER::_0);
			no2_.at_select_func() = [=](uint32_t id) { cbuff_ += '2'; };
			no3_.set_layer(WIDGET::LAYER::_0);
			no3_.at_select_func() = [=](uint32_t id) { cbuff_ += '3'; };
			no4_.set_layer(WIDGET::LAYER::_0);
			no4_.at_select_func() = [=](uint32_t id) { cbuff_ += '4'; };
			no5_.set_layer(WIDGET::LAYER::_0);
			no5_.at_select_func() = [=](uint32_t id) { cbuff_ += '5'; };
			no6_.set_layer(WIDGET::LAYER::_0);
			no6_.at_select_func() = [=](uint32_t id) { cbuff_ += '6'; };
			no7_.set_layer(WIDGET::LAYER::_0);
			no7_.at_select_func() = [=](uint32_t id) { cbuff_ += '7'; };
			no8_.set_layer(WIDGET::LAYER::_0);
			no8_.at_select_func() = [=](uint32_t id) { cbuff_ += '8'; };
			no9_.set_layer(WIDGET::LAYER::_0);
			no9_.at_select_func() = [=](uint32_t id) { cbuff_ += '9'; };

			del_.set_layer(WIDGET::LAYER::_0);
			del_.set_base_color(graphics::def_color::Orange);
			del_.at_select_func() = [=](uint32_t id) {
				if(cbuff_.empty()) return;

				auto code = static_cast<uint8_t>(cbuff_.back());
				cbuff_.pop_back();
				if(code == '(') {
					del_len_ = 8;
					nest_--;
					if(!cbuff_.empty()) {					
						auto code = static_cast<uint8_t>(cbuff_.back());
						if(code >= 0xc0) {
							auto p = calc_cmd_.at_func().get_name(static_cast<typename FUNC::NAME>(code));
							if(p != nullptr) {
								del_len_ += strlen(p);
							}
							cbuff_.pop_back();
						}
					}
				} else if(code == ')') {
					del_len_ = 8;
					nest_++;
				} else if(code == '.' || code == '^') {
					del_len_ = 8;
				} else if(code >= '0' && code <= '9') {
					del_len_ = 16;
				} else if(code == '+' || code == '-' || code == '*' || code == '/') {
					del_len_ = 16;
				} else if(code >= 0x80 && code < 0xc0) {
					auto p = calc_cmd_.at_symbol().get_name(static_cast<typename SYMBOL::NAME>(code));
					if(p != nullptr) {
						del_len_ = strlen(p);
					}
				} else if(code >= 0xc0) {
					auto p = calc_cmd_.at_func().get_name(static_cast<typename FUNC::NAME>(code));
					if(p != nullptr) {
						del_len_ = strlen(p);
					}
				}
			};
			ac_.set_layer(WIDGET::LAYER::_0);
			ac_.set_base_color(graphics::def_color::Orange);
			ac_.at_select_func() = [=](uint32_t id) { clear_win_(); };

			mul_.set_layer(WIDGET::LAYER::_0);
			mul_.at_select_func() = [=](uint32_t id) { cbuff_ += '*'; };
			div_.set_layer(WIDGET::LAYER::_0);
			div_.at_select_func() = [=](uint32_t id) { cbuff_ += '/'; };
			add_.set_layer(WIDGET::LAYER::_0);
			add_.at_select_func() = [=](uint32_t id) { cbuff_ += '+'; };
			sub_.set_layer(WIDGET::LAYER::_0);
			sub_.at_select_func() = [=](uint32_t id) { cbuff_ += '-'; };

			poi_.set_layer(WIDGET::LAYER::_0);
			poi_.at_select_func() = [=](uint32_t id) { cbuff_ += '.'; };

			left_.set_layer(WIDGET::LAYER::_0);
			left_.at_select_func()  = [=](uint32_t id) {
				shift_++;
				NVAL ans;
				calc_cmd_.at_symbol()(SYMBOL::NAME::ANS, ans);
//				draw_ans_(ans, true);
			};
			right_.set_layer(WIDGET::LAYER::_0);
			right_.at_select_func() = [=](uint32_t id) {
				shift_--;
				NVAL ans;
				calc_cmd_.at_symbol()(SYMBOL::NAME::ANS, ans);
//				draw_ans_(ans, true);
			};
			pin_.set_layer(WIDGET::LAYER::_0);
			pin_.at_select_func() = [=](uint32_t id) { cbuff_ += '('; nest_++; };
			pot_.set_layer(WIDGET::LAYER::_0);
			pot_.at_select_func() = [=](uint32_t id) { cbuff_ += ')'; nest_--; };

			x10_.set_layer(WIDGET::LAYER::_0);
			x10_.at_select_func() = [=](uint32_t id) {
				cbuff_ += '*';
				cbuff_ += static_cast<char>(FUNC::NAME::EXP10);
				cbuff_ += '(';
				nest_++;
			};
			ans_.set_layer(WIDGET::LAYER::_0);
			ans_.at_select_func() = [=](uint32_t id) {
//				NVAL tmp;
//				symbol_(SYMBOL::NAME::ANS, tmp);
//				if(tmp != 0) {
//					cbuff_ += static_cast<char>(SYMBOL::NAME::ANS);
//				}
			};

			equ_.set_layer(WIDGET::LAYER::_0);
			equ_.at_select_func() = [=](uint32_t id) { update_equ_(); };

			sin_.set_layer(WIDGET::LAYER::_0);
			sin_.set_base_color(graphics::def_color::EmeraldGreen);
			sin_.at_select_func() = [=](uint32_t id) {
				if(fc_mode_) {
					cbuff_ += static_cast<char>(FUNC::NAME::ASIN);
				} else {
					cbuff_ += static_cast<char>(FUNC::NAME::SIN);
				}
				cbuff_ += '('; nest_++;
			};
			cos_.set_layer(WIDGET::LAYER::_0);
			cos_.set_base_color(graphics::def_color::EmeraldGreen);
			cos_.at_select_func() = [=](uint32_t id) {
				if(fc_mode_) {
					cbuff_ += static_cast<char>(FUNC::NAME::ACOS);
				} else {
					cbuff_ += static_cast<char>(FUNC::NAME::COS);
				}
				cbuff_ += '('; nest_++;
			};
			tan_.set_layer(WIDGET::LAYER::_0);
			tan_.set_base_color(graphics::def_color::EmeraldGreen);
			tan_.at_select_func() = [=](uint32_t id) {
				if(fc_mode_) {
					cbuff_ += static_cast<char>(FUNC::NAME::ATAN);
				} else {
					cbuff_ += static_cast<char>(FUNC::NAME::TAN);
				}
				cbuff_ += '('; nest_++;
			};
			pai_.set_layer(WIDGET::LAYER::_0);
			pai_.set_base_color(graphics::def_color::LightPink);
			pai_.at_select_func() = [=](uint32_t id) {
				if(fc_mode_) {
					cbuff_ += static_cast<char>(SYMBOL::NAME::LOG2);
				} else {
					cbuff_ += static_cast<char>(SYMBOL::NAME::PI);
				}
			};

			sqr_.set_layer(WIDGET::LAYER::_0);
			sqr_.set_mobj(resource::bitmap::x_2);
			sqr_.at_select_func() = [=](uint32_t id) {
				cbuff_ += '^';
				cbuff_ += '2';
			};
			sqrt_.set_layer(WIDGET::LAYER::_0);
			sqrt_.at_select_func() = [=](uint32_t id) {
				cbuff_ += static_cast<char>(FUNC::NAME::SQRT);
				cbuff_ += '('; nest_++;
			};
			pow_.set_layer(WIDGET::LAYER::_0);
			pow_.set_mobj(resource::bitmap::x_y);
			pow_.at_select_func() = [=](uint32_t id) {
				cbuff_ += '^';
			};

			log_.set_layer(WIDGET::LAYER::_0);
			log_.at_select_func() = [=](uint32_t id) {
				cbuff_ += static_cast<char>(FUNC::NAME::LOG);
				cbuff_ += '('; nest_++;
			};
			ln_.set_layer(WIDGET::LAYER::_0);
			ln_.at_select_func() = [=](uint32_t id) {
				cbuff_ += static_cast<char>(FUNC::NAME::LN);
				cbuff_ += '('; nest_++;
			};
			inv_.set_layer(WIDGET::LAYER::_0);
			inv_.set_mobj(resource::bitmap::x_m1);
			inv_.at_select_func() = [=](uint32_t id) {
				cbuff_ += '^';
				cbuff_ += '-';
				cbuff_ += '1';
			};


			fc_.set_layer(WIDGET::LAYER::_0);  // 機能キー
			fc_.set_base_color(graphics::def_color::SafeColor);
			fc_.at_select_func() = [=](uint32_t id) {
				fc_mode_ = !fc_mode_;
				update_fc_();
			};

			angt_.set_layer(WIDGET::LAYER::_0);  // 角度タイプ
			angt_.set_base_color(graphics::def_color::SafeColor);
			angt_.at_select_func() = [=](uint32_t id) {
				switch(calc_cmd_.at_func().get_atype()) {
				case FUNC::ATYPE::Deg:
					calc_cmd_.at_func().set_atype(FUNC::ATYPE::Rad);
					angt_.set_title("Rad");
					break;
				case FUNC::ATYPE::Rad:
					calc_cmd_.at_func().set_atype(FUNC::ATYPE::Grad);
					angt_.set_title("Grad");
					break;
				case FUNC::ATYPE::Grad:
					calc_cmd_.at_func().set_atype(FUNC::ATYPE::Deg);
					angt_.set_title("Deg");
					break;
				}
			};

			setup_.set_layer(WIDGET::LAYER::_0);  // 設定
			setup_.set_base_color(graphics::def_color::SafeColor);
			setup_.at_select_func() = [=](uint32_t id) {
			};
			sym_.set_layer(WIDGET::LAYER::_0);  // シンボル変更
			sym_.set_base_color(graphics::def_color::SafeColor);
			sym_.at_select_func() = [=](uint32_t id) {
				symbol_idx_++;
				symbol_idx_ %= 10;
				auto i = static_cast<typename SYMBOL::NAME>(static_cast<uint32_t>(SYMBOL::NAME::V0) + symbol_idx_);
				sym_.set_title(calc_cmd_.at_symbol().get_name(i));
			};
			sym_in_.set_layer(WIDGET::LAYER::_0);  // シンボル(in)
			sym_in_.set_base_color(graphics::def_color::SafeColor);
			sym_in_.at_select_func() = [=](uint32_t id) {
				NVAL tmp;
				calc_cmd_.at_symbol()(SYMBOL::NAME::ANS, tmp);
				auto name = static_cast<typename SYMBOL::NAME>(
					static_cast<uint32_t>(SYMBOL::NAME::V0) + symbol_idx_);
				calc_cmd_.at_symbol().set_value(name, tmp);
			};
			sym_out_.set_layer(WIDGET::LAYER::_0);  // シンボル(out)
			sym_out_.set_base_color(graphics::def_color::SafeColor);
			sym_out_.at_select_func() = [=](uint32_t id) {
				cbuff_ += static_cast<char>(
					static_cast<uint32_t>(SYMBOL::NAME::V0) + symbol_idx_);
			};

			widd_.enable(WIDGET::LAYER::_0);

			clear_win_();
		}


		//-------------------------------------------------------------//
		/*!
			@brief  アップデート
		*/
		//-------------------------------------------------------------//
		void update() noexcept
		{
			render_.sync_frame();
			touch_.update();
			widd_.update();

			update_calc_();
		}
	};
}
