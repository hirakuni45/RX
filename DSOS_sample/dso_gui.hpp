#pragma once
//=====================================================================//
/*! @file
    @brief  DSO GUI クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
    @copyright  Copyright (C) 2020, 2022 Kunihito Hiramatsu @n
                Released under the MIT license @n
                https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "gui/widget_director.hpp"

#include "capture.hpp"
#include "render_wave.hpp"
#include "refclk.hpp"

namespace dsos {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  波形描画クラス
		@param[in]	RENDER	描画クラス
		@param[in]	TOUCH	タッチ・クラス
		@param[in]	CAPTURE	キャプチャー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class RENDER, class TOUCH, class CAPTURE>
	class dso_gui : public render_base {

		static constexpr int16_t BTN_GRID = 40;
		static constexpr int16_t BTN_SIZE = 38;

		RENDER&		render_;
		TOUCH&		touch_;
		CAPTURE&	capture_;

		uint16_t	capture_cycle_;

		typedef gui::widget_director<RENDER, TOUCH, 32> WIDD;
		WIDD		widd_;

		typedef render_wave<RENDER, TOUCH, CAPTURE> RENDER_WAVE;
		RENDER_WAVE	render_wave_;

		typedef gui::widget WIDGET;
		typedef gui::button BUTTON;
		BUTTON		ch0_btn_;
		BUTTON		ch1_btn_;
		BUTTON		smp_btn_;
		BUTTON		trg_btn_;
		BUTTON		mes_btn_;
		BUTTON		opt_btn_;

		typedef gui::menu MENU;
		MENU		ch0_mult_menu_;
		MENU		ch0_mode_menu_;
		MENU		ch0_volt_menu_;
		MENU		ch1_mult_menu_;
		MENU		ch1_mode_menu_;
		MENU		ch1_volt_menu_;
		MENU		trg_menu_;
		MENU		smp_unit_menu_;
		MENU		smp_fine_menu_;
		MENU		mes_menu_;
		MENU		opt_menu_;

		uint8_t		smp_unit_;
		uint8_t		smp_fine_;

		uint32_t	trg_update_;

		refclk		refclk_;

		bool		widd_last_;
		bool		wave_last_;

		WIDGET*		last_focus_;

		void side_button_stall_(BUTTON& mybtn, bool stall) noexcept
		{
			if(&mybtn != &ch0_btn_) {
				if(stall) ch0_btn_.set_state(BUTTON::STATE::STALL);
				else ch0_btn_.enable();
			}
			if(&mybtn != &ch1_btn_) {
				if(stall) ch1_btn_.set_state(BUTTON::STATE::STALL);
				else ch1_btn_.enable();
			}
			if(&mybtn != &trg_btn_) {
				if(stall) trg_btn_.set_state(BUTTON::STATE::STALL);
				else trg_btn_.enable();
			}
			if(&mybtn != &smp_btn_) {
				if(stall) smp_btn_.set_state(BUTTON::STATE::STALL);
				else smp_btn_.enable();
			}
			if(&mybtn != &mes_btn_) {
				if(stall) mes_btn_.set_state(BUTTON::STATE::STALL);
				else mes_btn_.enable();
			}
			if(&mybtn != &opt_btn_) {
				if(stall) opt_btn_.set_state(BUTTON::STATE::STALL);
				else opt_btn_.enable();
			}
		}


		void setup_smp_fine_() noexcept
		{
			const char* p = nullptr;
			switch(smp_unit_) {
			case 0:
				p = SMP_FINE0_STR;
				break;
			case 1:
				p = SMP_FINE1_STR;
				break;
			case 2:
				p = SMP_FINE2_STR;
				break;
			case 3:
				p = SMP_FINE3_STR;
				break;
			case 4:
				p = SMP_FINE4_STR;
				break;
			case 5:
				p = SMP_FINE5_STR;
				break;
			default:
				break;
			}
			smp_fine_menu_.set_title(p);
		}


		void setup_ch0_() noexcept
		{
			auto mult = static_cast<CH_MULT>(ch0_mult_menu_.get_select_pos());
			render_wave_.set_ch0_mult(mult);
			auto mode = static_cast<CH_MODE>(ch0_mode_menu_.get_select_pos());
			render_wave_.set_ch0_mode(mode);
			auto vol = static_cast<CH_VOLT>(ch0_volt_menu_.get_select_pos());
			render_wave_.set_ch0_volt(vol);
		}


		void setup_ch1_() noexcept
		{
			auto mult = static_cast<CH_MULT>(ch1_mult_menu_.get_select_pos());
			render_wave_.set_ch1_mult(mult);
			auto mode = static_cast<CH_MODE>(ch1_mode_menu_.get_select_pos());
			render_wave_.set_ch1_mode(mode);
			auto vol = static_cast<CH_VOLT>(ch1_volt_menu_.get_select_pos());
			render_wave_.set_ch1_volt(vol);
		}


		void exec_capture_() noexcept
		{
			auto trg = static_cast<TRG_MODE>(trg_menu_.get_select_pos());
			capture_.set_trg_mode(trg, render_wave_.get_trg_value());
		}


		void draw_focus_(WIDGET* w) noexcept
		{
			render_.set_fore_color(w->get_base_color());
			const auto& org = w->at_location().org;
			render_.line_h(org.y + BTN_SIZE - 9, org.x + 6, BTN_SIZE - 6 * 2);
			render_.line_h(org.y + BTN_SIZE - 8, org.x + 6, BTN_SIZE - 6 * 2);
			render_.line_h(org.y + BTN_SIZE - 7, org.x + 6, BTN_SIZE - 6 * 2);
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
			@param[in]	render	描画クラス
			@param[in]	touch	タッチ・クラス
			@param[in]	capture	キャプチャー・クラス
		*/
		//-----------------------------------------------------------------//
		dso_gui(RENDER& render, TOUCH& touch, CAPTURE& capture) noexcept :
			render_(render), touch_(touch), capture_(capture),
			capture_cycle_(0),
			widd_(render, touch),
			render_wave_(render_, touch_, capture_),
			ch0_btn_(vtx::srect(442, 16+BTN_GRID*0, BTN_SIZE, BTN_SIZE), "CH0"),
			ch1_btn_(vtx::srect(442, 16+BTN_GRID*1, BTN_SIZE, BTN_SIZE), "CH1"),
			smp_btn_(vtx::srect(442, 16+BTN_GRID*2, BTN_SIZE, BTN_SIZE), "Smp"),
			trg_btn_(vtx::srect(442, 16+BTN_GRID*3, BTN_SIZE, BTN_SIZE), "Trg"),
			mes_btn_(vtx::srect(442, 16+BTN_GRID*4, BTN_SIZE, BTN_SIZE), "Mes"),
			opt_btn_(vtx::srect(442, 16+BTN_GRID*5, BTN_SIZE, BTN_SIZE), "Opt"),
			ch0_mult_menu_(vtx::srect(442-90*3, 16, 80, 0), CAPTURE::CH_MULT_STR),
			ch0_mode_menu_(vtx::srect(442-90*2, 16, 80, 0), CAPTURE::CH_MODE_STR),
			ch0_volt_menu_(vtx::srect(442-90*1, 16, 80, 0), CAPTURE::CH_VOLT_STR),
			ch1_mult_menu_(vtx::srect(442-90*3, 16, 80, 0), CAPTURE::CH_MULT_STR),
			ch1_mode_menu_(vtx::srect(442-90*2, 16, 80, 0), CAPTURE::CH_MODE_STR),
			ch1_volt_menu_(vtx::srect(442-90*1, 16, 80, 0), CAPTURE::CH_VOLT_STR),
			trg_menu_(vtx::srect(442-100, 16, 90, 0), CAPTURE::TRG_MODE_STR),
			smp_unit_menu_(vtx::srect(442-90*2, 16, 80, 0), SMP_UNIT_STR, false),
			smp_fine_menu_(vtx::srect(442-90*1, 16, 80, 0), ""),
			mes_menu_(vtx::srect(442-100*1, 16, 90, 0), MES_MODE_STR),
			opt_menu_(vtx::srect(442-100*1, 16, 90, 0), OPTION_STR),
			smp_unit_(0), smp_fine_(0),
			trg_update_(0),
			refclk_(), widd_last_(false), wave_last_(false),
			last_focus_(nullptr)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
		*/
		//-----------------------------------------------------------------//
		void start() noexcept
		{
			ch0_btn_.set_layer(WIDGET::LAYER::_0);
			ch0_btn_.set_base_color(CH0_COLOR);
			ch0_btn_.enable();
			ch0_btn_.at_select_func() = [=](uint32_t id) {
				bool ena = ch0_mode_menu_.get_state() == WIDGET::STATE::ENABLE;
				ch0_mult_menu_.enable(!ena);
				ch0_mode_menu_.enable(!ena);
				ch0_volt_menu_.enable(!ena);
				side_button_stall_(ch0_btn_, !ena);
				if(ena) {  // メニューを閉じる瞬間
					setup_ch0_();
				}
			};

			ch1_btn_.set_layer(WIDGET::LAYER::_0);
			ch1_btn_.set_base_color(CH1_COLOR);
			ch1_btn_.enable();
			ch1_btn_.at_select_func() = [=](uint32_t id) {
				bool ena = ch1_mode_menu_.get_state() == WIDGET::STATE::ENABLE;
				ch1_mult_menu_.enable(!ena);
				ch1_mode_menu_.enable(!ena);
				ch1_volt_menu_.enable(!ena);
				side_button_stall_(ch1_btn_, !ena);
				if(ena) {  // メニューを閉じる瞬間
					setup_ch1_();
				}
			};

			smp_btn_.set_layer(WIDGET::LAYER::_0);
			smp_btn_.set_base_color(SMP_COLOR);
			smp_btn_.enable();
			smp_btn_.at_select_func() = [=](uint32_t id) {
				bool ena = smp_unit_menu_.get_state() == WIDGET::STATE::ENABLE;
				smp_unit_menu_.enable(!ena);
				setup_smp_fine_();
				smp_fine_menu_.enable(!ena);
				side_button_stall_(smp_btn_, !ena);
				if(ena) {
					auto smp = static_cast<SMP_MODE>(smp_fine_menu_.get_select_pos()
						+ smp_unit_menu_.get_select_pos() * SMP_FINE_NUM);
					render_wave_.set_smp_mode(smp);
				}
			};

			trg_btn_.set_layer(WIDGET::LAYER::_0);
			trg_btn_.set_base_color(TRG_COLOR);
			trg_btn_.enable();
			trg_btn_.at_select_func() = [=](uint32_t id) {
				bool ena = trg_menu_.get_state() == WIDGET::STATE::ENABLE;
				trg_menu_.enable(!ena);
				side_button_stall_(trg_btn_, !ena);
				if(ena) {  // メニューを閉じる瞬間
					exec_capture_();
				}
			};

			mes_btn_.set_layer(WIDGET::LAYER::_0);
			mes_btn_.set_base_color(MES_COLOR);
			mes_btn_.enable();
			mes_btn_.at_select_func() = [=](uint32_t id) {
				bool ena = mes_menu_.get_state() == WIDGET::STATE::ENABLE;
				mes_menu_.enable(!ena);
				side_button_stall_(mes_btn_, !ena);
				if(ena) {
					render_wave_.set_measere(static_cast<MEASERE>(mes_menu_.get_select_pos()));
				}
			};
			mes_menu_.set_layer(WIDGET::LAYER::_0);
			mes_menu_.set_base_color(MES_COLOR);

			opt_btn_.set_layer(WIDGET::LAYER::_0);
			opt_btn_.enable();
			opt_btn_.at_select_func() = [=](uint32_t id) {
				bool ena = opt_menu_.get_state() == WIDGET::STATE::ENABLE;
				side_button_stall_(opt_btn_, !ena);
			};
			opt_menu_.set_layer(WIDGET::LAYER::_0);

			ch0_mult_menu_.set_layer(WIDGET::LAYER::_0);
			ch0_mult_menu_.set_base_color(CH0_COLOR);
			ch0_mode_menu_.set_layer(WIDGET::LAYER::_0);
			ch0_mode_menu_.set_base_color(CH0_COLOR);
			ch0_volt_menu_.set_layer(WIDGET::LAYER::_0);
			ch0_volt_menu_.set_base_color(CH0_COLOR);
			ch1_mult_menu_.set_layer(WIDGET::LAYER::_0);
			ch1_mult_menu_.set_base_color(CH1_COLOR);
			ch1_mode_menu_.set_layer(WIDGET::LAYER::_0);
			ch1_mode_menu_.set_base_color(CH1_COLOR);
			ch1_volt_menu_.set_layer(WIDGET::LAYER::_0);
			ch1_volt_menu_.set_base_color(CH1_COLOR);
			trg_menu_.set_layer(WIDGET::LAYER::_0);
			trg_menu_.set_base_color(TRG_COLOR);

			smp_unit_menu_.set_layer(WIDGET::LAYER::_0);
			smp_unit_menu_.set_base_color(SMP_COLOR);
			smp_unit_menu_.at_select_func() = [=](uint32_t pos, uint32_t num) {
				smp_unit_ = pos;
				setup_smp_fine_();
			};
			smp_fine_menu_.set_layer(WIDGET::LAYER::_0);
			smp_fine_menu_.set_base_color(SMP_COLOR);
			smp_fine_menu_.at_select_func() = [=](uint32_t pos, uint32_t num) {
				smp_fine_ = pos;
			};

			capture_cycle_ = capture_.get_capture_cycle();
			capture_.set_trg_mode(TRG_MODE::SINGLE, 0);

			// 基準波出力開始
			refclk_.start();

			last_focus_ = &ch0_btn_;
			render_wave_.set_target(TARGET::CH0);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  更新 @n
					※毎フレーム呼ぶ
		*/
		//-----------------------------------------------------------------//
		void update() noexcept
		{
			widd_last_ = widd_.update();

			// ダブルバッファ時の widget 管理のケア
			if(render_.is_double_buffer()) {
				// GUI 操作が発生したら、ダブルバッファの両方に同じ絵を作る。
				if(!widd_last_) {
					widd_.refresh();
				}
			}

			// CH0, CH1, Smp(Time) ボタンのフォーカスを描画
			{
				auto w = widd_.get_current_widget();
				if(w == &ch0_btn_) {
					draw_focus_(w);
					last_focus_ = w;
					render_wave_.set_target(TARGET::CH0);
				} else if(w == &ch1_btn_) {
					draw_focus_(w);
					last_focus_ = w;
					render_wave_.set_target(TARGET::CH1);
				} else if(w == &smp_btn_) {
					draw_focus_(w);
					last_focus_ = w;
					render_wave_.set_target(TARGET::TIME);
				} else if(last_focus_ != nullptr) {
					draw_focus_(last_focus_);
				}
			}

			bool capture = false;
			if(!wave_last_ && trg_update_ != render_wave_.get_trg_update()) {  // トリガー電圧が変更になった！
				trg_update_ = render_wave_.get_trg_update();
				auto trg = static_cast<TRG_MODE>(trg_menu_.get_select_pos());
				if(trg == CAPTURE::TRG_MODE::CH0_POS || trg == CAPTURE::TRG_MODE::CH0_NEG
					|| trg == CAPTURE::TRG_MODE::CH1_POS || trg == CAPTURE::TRG_MODE::CH1_NEG) {
					capture = true;
				}
			}
			if(!wave_last_ && static_cast<TRG_MODE>(trg_menu_.get_select_pos()) == TRG_MODE::RUN) {  // トリガーモードが ’RUN' なら、キャプチャーを出し続ける。
				capture = true;
			}
			if(capture) {
				exec_capture_();
			}

			uint32_t n = 0;
			if(ch0_mode_menu_.get_state() == gui::widget::STATE::ENABLE) {
				++n;
			} else if(ch1_mode_menu_.get_state() == gui::widget::STATE::ENABLE) {
				++n;
			} else if(trg_menu_.get_state() == gui::widget::STATE::ENABLE) {
				++n;
			} else if(smp_unit_menu_.get_state() == gui::widget::STATE::ENABLE) {
				++n;
			} else if(mes_menu_.get_state() == gui::widget::STATE::ENABLE) {
				++n;
//			} else if(opt_menu_.get_state() == gui::widget::STATE::ENABLE) {
//				++n;
			}

			if(n == 0) {  // メニュー選択時はバイパスする。
				bool f = render_wave_.ui_service();  // タッチ操作による画面更新が必要な場合「true」が戻る。

				// 波形をキャプチャーしたら描画
				auto cycle = capture_.get_capture_cycle();
				if(cycle != capture_cycle_) {
					f = true;
				}
				if(f) {
					capture_cycle_ = cycle;
					render_wave_.update();
					wave_last_ = true;
				} else if(wave_last_) {  // ダブルバッファに書き込む為、同じ描画を行う
					render_wave_.update();
					wave_last_ = false;
				}

				render_wave_.update_info();
			}

			render_.flip();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  widget_director の参照
			@return widget_director
		*/
		//-----------------------------------------------------------------//
		auto& at_widd() noexcept { return widd_; }
	};
}
