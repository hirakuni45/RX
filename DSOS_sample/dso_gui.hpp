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

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  波形描画クラス
		@param[in]	RENDER	描画クラス
		@param[in]	TOUCH	タッチ・クラス
		@param[in]	CAPTURE	キャプチャー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class RENDER, class TOUCH, class CAPTURE>
	class dso_gui {

		static const int16_t BTN_GRID = 40;
		static const int16_t BTN_SIZE = 38;

		RENDER&		render_;
		TOUCH&		touch_;
		CAPTURE&	capture_;

		volatile uint32_t	capture_tic_;

		typedef gui::widget_director<RENDER, TOUCH, 32> WIDD;
		WIDD		widd_;

		typedef utils::render_wave<RENDER, TOUCH, CAPTURE> RENDER_WAVE;
		RENDER_WAVE	render_wave_;

		typedef gui::button BUTTON;
		BUTTON		ch0_;
		BUTTON		ch1_;
		BUTTON		trg_;
		BUTTON		smp_;
		BUTTON		mes_;
		BUTTON		opt_;

		typedef gui::menu MENU;
		MENU		trg_menu_;
		MENU		smp_unit_menu_;
		MENU		smp_fine_menu_;

		uint8_t		trg_type_;
		uint8_t		smp_unit_;
		uint8_t		smp_fine_;

		uint8_t		ch0_idx_;
		uint8_t		ch1_idx_;


		void setup_smp_fine_() noexcept
		{
			const char* p = nullptr;
			switch(smp_unit_) {
			case 0:  // 1us
				p = "1us,2us,5us";
				break;
			case 1:  // 10us
				p = "10us,20us,50us";
				break;
			case 2:  // 100us
				p = "100us,200us,500us";
				break;
			case 3:  // 1ms
				p = "1ms,2ms,5ms";
				break;
			case 4:  // 10ms
				p = "10ms,20ms,50ms";
				break;
			case 5:  // 100ms
				p = "100ms,200ms,500ms";
				break;
			default:
				break;
			}
			smp_fine_menu_.set_title(p);
			smp_fine_menu_.set_select_pos(0);
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
			ch0_(vtx::srect(442, 16+BTN_GRID*0, BTN_SIZE, BTN_SIZE), "GND"),
			ch1_(vtx::srect(442, 16+BTN_GRID*1, BTN_SIZE, BTN_SIZE), "GND"),
			trg_(vtx::srect(442, 16+BTN_GRID*2, BTN_SIZE, BTN_SIZE), "Trg"),
			smp_(vtx::srect(442, 16+BTN_GRID*3, BTN_SIZE, BTN_SIZE), "Smp"),
			mes_(vtx::srect(442, 16+BTN_GRID*4, BTN_SIZE, BTN_SIZE), "Mes"),
			opt_(vtx::srect(442, 16+BTN_GRID*5, BTN_SIZE, BTN_SIZE), "Opt"),
			trg_menu_(vtx::srect(442-100, 16, 90, 0), "Run,CH0-Pos,CH1-Pos,CH0-Neg,CH1-Neg"),
			smp_unit_menu_(vtx::srect(442-90-90, 16, 80, 0),
				"1us,10us,100us,1ms,10ms,100ms", false),
			smp_fine_menu_(vtx::srect(442-90, 16, 80, 0), ""),
			trg_type_(0), smp_unit_(0), smp_fine_(0),
			ch0_idx_(0), ch1_idx_(0)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
		*/
		//-----------------------------------------------------------------//
		void start() noexcept
		{
			static const char* ch_mode_tbl_[4] = { "GND", "DC", "GND", "AC" };

			ch0_.set_base_color(RENDER::DEF_COLOR::Lime);
			ch0_.enable();
			ch0_.at_select_func() = [=](uint32_t id) {
				++ch0_idx_;
				ch0_idx_ &= 3;
				ch0_.set_title(ch_mode_tbl_[ch0_idx_]);
			};

			ch1_.set_base_color(RENDER::DEF_COLOR::Fuchsi);
			ch1_.enable();
			ch1_.at_select_func() = [=](uint32_t id) {
				++ch1_idx_;
				ch1_idx_ &= 3;
				ch1_.set_title(ch_mode_tbl_[ch1_idx_]);
			};

			trg_.enable();
			trg_.at_select_func() = [=](uint32_t id) {
				bool ena = trg_menu_.get_state() == gui::widget::STATE::ENABLE;
				trg_menu_.enable(!ena);
			};

			smp_.enable();
			smp_.at_select_func() = [=](uint32_t id) {
				bool ena = smp_unit_menu_.get_state() == gui::widget::STATE::ENABLE;
				smp_unit_menu_.enable(!ena);
				setup_smp_fine_();
				smp_fine_menu_.enable(!ena);
			};

			mes_.enable();
			mes_.at_select_func() = [=](uint32_t id) {
			};

			opt_.enable();
			opt_.at_select_func() = [=](uint32_t id) {
			};

			trg_menu_.at_select_func() = [=](uint32_t pos, uint32_t num) {
				trg_menu_.enable(false);
				trg_type_ = pos;
			};

			smp_unit_menu_.at_select_func() = [=](uint32_t pos, uint32_t num) {
				smp_unit_ = pos;
				setup_smp_fine_();
			};
			smp_fine_menu_.at_select_func() = [=](uint32_t pos, uint32_t num) {
				smp_fine_ = pos;
			};

			capture_tic_ = capture_.get_capture_tic();
			capture_.set_trigger(CAPTURE::TRIGGER::FREE);
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

			if(trg_menu_.get_state() == gui::widget::STATE::ENABLE) {

			} else if(smp_unit_menu_.get_state() == gui::widget::STATE::ENABLE) {

			} else if(smp_fine_menu_.get_state() == gui::widget::STATE::ENABLE) {
	
			} else {
				// タッチ操作による画面更新が必要か？
				bool f = render_wave_.ui_service();

				// 波形をキャプチャーしたら描画
				if(f || capture_.get_capture_tic() != capture_tic_) {
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
