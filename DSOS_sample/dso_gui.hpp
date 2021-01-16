#pragma once
//=====================================================================//
/*! @file
    @brief  DSO GUI クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
    @copyright  Copyright (C) 2020 Kunihito Hiramatsu @n
                Released under the MIT license @n
                https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "graphics/widget_director.hpp"

#include "capture.hpp"
#include "render_wave.hpp"

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

		static const int16_t BTN_GRID = 40;
		static const int16_t BTN_SIZE = 38;

		RENDER&		render_;
		TOUCH&		touch_;
		CAPTURE&	capture_;

		volatile uint32_t	capture_tic_;

		typedef gui::widget_director<RENDER, TOUCH, 32> WIDD;
		WIDD		widd_;

		typedef render_wave<RENDER, TOUCH, CAPTURE> RENDER_WAVE;
		RENDER_WAVE	render_wave_;

		typedef gui::widget WIDGET;
		typedef gui::button BUTTON;
		BUTTON		ch0_btn_;
		BUTTON		ch1_btn_;
		BUTTON		trg_btn_;
		BUTTON		smp_btn_;
		BUTTON		mes_btn_;
		BUTTON		opt_btn_;

		typedef gui::menu MENU;
		MENU		ch0_mode_menu_;
		MENU		ch0_volt_menu_;
		MENU		ch1_mode_menu_;
		MENU		ch1_volt_menu_;
		MENU		trg_menu_;
		MENU		smp_unit_menu_;
		MENU		smp_fine_menu_;
		MENU		mes_menu_;

		uint8_t		smp_unit_;
		uint8_t		smp_fine_;


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
				p = SMP_FINE4_STR;
				break;
			default:
				break;
			}
			smp_fine_menu_.set_title(p);
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
			capture_tic_(0),
			widd_(render, touch),
			render_wave_(render_, touch_, capture_),
			ch0_btn_(vtx::srect(442, 16+BTN_GRID*0, BTN_SIZE, BTN_SIZE), "CH0"),
			ch1_btn_(vtx::srect(442, 16+BTN_GRID*1, BTN_SIZE, BTN_SIZE), "CH1"),
			trg_btn_(vtx::srect(442, 16+BTN_GRID*2, BTN_SIZE, BTN_SIZE), "Trg"),
			smp_btn_(vtx::srect(442, 16+BTN_GRID*3, BTN_SIZE, BTN_SIZE), "Smp"),
			mes_btn_(vtx::srect(442, 16+BTN_GRID*4, BTN_SIZE, BTN_SIZE), "Mes"),
			opt_btn_(vtx::srect(442, 16+BTN_GRID*5, BTN_SIZE, BTN_SIZE), "Opt"),
			ch0_mode_menu_(vtx::srect(442-90*2, 16, 80, 0), CAPTURE::CH_MODE_STR),
			ch0_volt_menu_(vtx::srect(442-90*1, 16, 80, 0), CAPTURE::CH_VOLT_STR),
			ch1_mode_menu_(vtx::srect(442-90*2, 16, 80, 0), CAPTURE::CH_MODE_STR),
			ch1_volt_menu_(vtx::srect(442-90*1, 16, 80, 0), CAPTURE::CH_VOLT_STR),
			trg_menu_(vtx::srect(442-100, 16, 90, 0), CAPTURE::TRG_MODE_STR),
			smp_unit_menu_(vtx::srect(442-90*2, 16, 80, 0), SMP_UNIT_STR, false),
			smp_fine_menu_(vtx::srect(442-90*1, 16, 80, 0), ""),
			mes_menu_(vtx::srect(442-90*1, 16, 80, 0), MES_MODE_STR),
			smp_unit_(0), smp_fine_(0)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
		*/
		//-----------------------------------------------------------------//
		void start() noexcept
		{
			ch0_btn_.set_base_color(CH0_COLOR);
			ch0_btn_.enable();
			ch0_btn_.at_select_func() = [=](uint32_t id) {
				bool ena = ch0_mode_menu_.get_state() == WIDGET::STATE::ENABLE;
				ch0_mode_menu_.enable(!ena);
				ch0_volt_menu_.enable(!ena);
				side_button_stall_(ch0_btn_, !ena);
			};

			ch1_btn_.set_base_color(CH1_COLOR);
			ch1_btn_.enable();
			ch1_btn_.at_select_func() = [=](uint32_t id) {
				bool ena = ch1_mode_menu_.get_state() == WIDGET::STATE::ENABLE;
				ch1_mode_menu_.enable(!ena);
				ch1_volt_menu_.enable(!ena);
				side_button_stall_(ch1_btn_, !ena);
			};

			trg_btn_.set_base_color(TRG_COLOR);
			trg_btn_.enable();
			trg_btn_.at_select_func() = [=](uint32_t id) {
				bool ena = trg_menu_.get_state() == WIDGET::STATE::ENABLE;
				trg_menu_.enable(!ena);
				side_button_stall_(trg_btn_, !ena);
				if(ena) {  // メニューを閉じる瞬間
					capture_.set_trigger(static_cast<typename CAPTURE::TRG_MODE>(trg_menu_.get_select_pos()));
				}
			};

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
			mes_menu_.set_base_color(MES_COLOR);

			opt_btn_.enable();
			opt_btn_.at_select_func() = [=](uint32_t id) {
//				bool ena = opt_menu_.get_state() == WIDGET::STATE::ENABLE;
//				side_button_stall_(opt_btn_, !ena);
			};

			ch0_mode_menu_.set_base_color(CH0_COLOR);
			ch0_volt_menu_.set_base_color(CH0_COLOR);
			ch1_mode_menu_.set_base_color(CH1_COLOR);
			ch1_volt_menu_.set_base_color(CH1_COLOR);
			trg_menu_.set_base_color(TRG_COLOR);

			smp_unit_menu_.set_base_color(SMP_COLOR);
			smp_unit_menu_.at_select_func() = [=](uint32_t pos, uint32_t num) {
				smp_unit_ = pos;
				setup_smp_fine_();
			};
			smp_fine_menu_.set_base_color(SMP_COLOR);
			smp_fine_menu_.at_select_func() = [=](uint32_t pos, uint32_t num) {
				smp_fine_ = pos;
			};

			capture_tic_ = capture_.get_capture_tic();
			capture_.set_trigger(CAPTURE::TRG_MODE::ONE);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  更新 @n
					※毎フレーム呼ぶ
		*/
		//-----------------------------------------------------------------//
		void update() noexcept
		{
			widd_.update();

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
			}

			if(n == 0) {  // メニュー選択時はバイパスする。
				// タッチ操作による画面更新が必要か？
				bool f = render_wave_.ui_service();

				// 波形をキャプチャーしたら描画
				auto tic = capture_.get_capture_tic();
				if(f || tic != capture_tic_) {
					capture_tic_ = tic;
					render_wave_.update();
				}
			}
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
