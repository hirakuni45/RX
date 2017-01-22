#pragma once
//=====================================================================//
/*!	@file
	@brief	ラップ・タイマー・クラス
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "main.hpp"

namespace app {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ラップ・タイマー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class laptimer {

		static const uint16_t TRIGGER_LOOP_DELAY   = 60;   ///< // ラップタイム時の点滅時間
		static const uint16_t TRIGGER_LOOP_PITOUT  = 60;   ///< // ピットアウト時の点滅時間
		static const uint16_t LAP_COUNT_LIMIT      = 300;  ///< // ラップ数の限度

		time_t				start_time_;
		uint32_t			lap_total_;
		volatile uint32_t	lap_time_ref_;
		volatile uint32_t	lap_best_;
		volatile uint16_t 	lap_count_;
		volatile uint8_t	trg_loop_;		// ラップトリガーで起動されるタイマー
		volatile bool		lap_enable_;
		char 				lap_step_;
		char	  			lap_exit_;
		uint8_t				cancel_count_;
		uint8_t				lap_exit_active_;
		uint8_t				pit_out_count_;

		short				recall_pos_;

		uint32_t			lap_buff_[LAP_COUNT_LIMIT];

		char				save_enable_ = 1;

		enum class task {
			menu,
			main,
		};
		task	task_;

		uint32_t get_laptimer_() const
		{
			auto& core = at_core();
			return core.cmt_.get_counter();
		}

		// ラップ・タイマー・メイン
		void laptimer_main_()
		{
			auto& core = at_core();
			// 経過時間
			lap_total_ = get_laptimer_() - lap_time_ref_;
			core.resource_.draw_time_hms_12(0, 0, lap_total_ / 100);

			if(lap_best_) {
				core.resource_.draw_time_mst_12(128 - 51, 0, lap_best_);
			}
	
			core.bitmap_.line(0, 13, 127, 13, 1);
			core.bitmap_.line(0, 14, 127, 14, 1);

			uint8_t trg = 0;
			time_t v;
			if(trg_loop_) {
				trg_loop_--;
				if((trg_loop_ & 7) > 2) trg = 1;
				if(lap_count_ == 0) {
					v = 0;
				} else {
					v = (lap_buff_[lap_count_] >> 1) - (lap_buff_[lap_count_ - 1] >> 1);
				}
			} else {
				if(lap_count_ == 0) {
					v = get_laptimer_() - lap_time_ref_;
				} else {
					v = get_laptimer_() - lap_time_ref_ - (lap_buff_[lap_count_] >> 1);
				}
				trg = 1;
			}

			if(lap_exit_) {
				core.bitmap_.draw_text((128 - (6 * 18)) / 2, (64 - 12) / 2, "'UP + DOWN' to End");
///				if((g_switch_level & (SWITCH_BIT_UP | SWITCH_BIT_DOWN)) == (SWITCH_BIT_UP | SWITCH_BIT_DOWN)) {
///					lap_enable_ = false;		// ラップタイマーのサービス（割り込み内処理）を停止
///					finsh_logging();
///					install_task(laptimer_save);
///				}
			} else {
				if(trg) {
					core.resource_.draw_time_32(8, 16, v);
				}
			}
	
			core.bitmap_.line(0, 49, 127, 49, 1);
			core.bitmap_.line(0, 50, 127, 50, 1);

			core.resource_.draw_number3_12(100, 52, lap_count_);



#if 0
	unsigned long a, b, l;

	if(g_lap_step == 0) {
		// ピットイン中はプログレスバー表示をしない
		if((g_switch_level & SWITCH_BIT_PIT)) {
			if(g_switch_level & SWITCH_BIT_PIT) {
				monograph_draw_string_P(0, (64 - 12), PSTR("- Pit IN -"));
			}
		} else if(g_pit_out_count) {
			monograph_draw_string_P(0, (64 - 12), PSTR("- Pit OUT -"));
			--g_pit_out_count;
		} else {
			// プログレスバー表示
			if(g_lap_count) {
				// ピット・アウトした周は表示しない
				if((g_lap_buff[g_lap_count - 1] & 1) == 0) {
					b = get_laptimer() - g_lap_time_ref - (g_lap_buff[g_lap_count] >> 1);
					a = (g_lap_buff[g_lap_count] >> 1) - (g_lap_buff[g_lap_count - 1] >> 1);	// 1周前のタイム
					if(a > 0) {
						l = b * 90 / a;
						if(l >= 90) l = 90;
						trg = 1;
						if(l >= 70) {
							if((g_loop_count & 15) < 6) trg = 0;
						}
						if(trg) {
							monograph_line(0, 56,  l, 56, 1);
							monograph_line(0, 57,  l, 57, 1);
						}
					}
				}
				monograph_line(0, 58, 90, 58, 1);
			}
		}
	} else if(g_lap_exit == 0) {
		g_lap_exit_active--;
		if(g_lap_exit_active == 0) g_lap_step = 0;

	}

	// ピットアウトの検出
	if(g_switch_negative & SWITCH_BIT_PIT) {
		g_pit_out_count = TRIGGER_LOOP_PITOUT;
	}

	// キャンセルボタンのホールド
	if(g_switch_level & SWITCH_BIT_CANCEL) {
		++g_cancel_count;
		if(g_cancel_count >= 50) {
			g_lap_exit = 1;
		}
	} else {
		g_cancel_count = 0;
	}
#endif
		}

		void recall_init_()
		{
		}

		// ラップ・タイマー・メニュー
		void menu_()
		{
			auto& core = at_core();

			auto t = core.get_time();
			const struct tm* tt = localtime(&t); 
			int16_t x = 0;
			int16_t y = 0;
			core.draw_date(x, y, tt);
			core.bitmap_.draw_text(x + (6 * 11), y, get_wday(tt->tm_wday));

			y += 12;
			core.draw_time(x, y, tt);
			core.bitmap_.line(0, 24, 127, 24, 1);

			int n = core.menu_run_;
			switch(n) {
			case 0:
//				start_logging();
				lap_count_ = 0;
				lap_buff_[0] = 0;
				lap_best_ = 0;
				lap_time_ref_ = get_laptimer_();
				trg_loop_ = TRIGGER_LOOP_DELAY;
				lap_enable_ = true;
				lap_step_ = 0;
				lap_exit_active_ = 0;
				lap_exit_ = 0;
				lap_total_ = 0;
				cancel_count_ = 0;
				pit_out_count_ = 0;
				start_time_ = t;
				task_ = task::main;
				break;
			case 1:
////				task_ = [this]{ recall_init_(); };
				break;
			case 2:
//				install_task(setup_init);
				break;
			default:
				break;
			}

//			if(util_get_cancel()) {
//				install_task(menu_init);
//			}

			core.menu_.render(0, 24);
		}

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	初期化
		*/
		//-------------------------------------------------------------//
		void init()
		{
			auto& core = at_core();

			core.menu_.set_space(0);
			core.menu_.add(core_t::MENU::type::PROP, "Start");
			core.menu_.add(core_t::MENU::type::PROP, "Recall");
			core.menu_.add(core_t::MENU::type::PROP, "Setup");
			core.menu_run_ = -1;
			task_ = task::menu;
		}


		//-------------------------------------------------------------//
		/*!
			@brief	サービス
		*/
		//-------------------------------------------------------------//
		void service()
		{
			switch(task_) {
			case task::menu:
				menu_();
				break;
			case task::main:
				laptimer_main_();
				break;
			default:
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@breif	ラップタイマー・サービス（サーバー）@n
					・1/100 秒間隔の割り込みから呼ばれる。@n
					・ラップタイム記録
			@param[in]	pit	ピットフラグ
		 */
		//-----------------------------------------------------------------//
		void laptimer_service(uint8_t pit)
		{
			if(!lap_enable_) return;

			if(lap_count_ < LAP_COUNT_LIMIT) {
				auto t = get_laptimer_() - lap_time_ref_;
				lap_count_++;
				lap_buff_[lap_count_] = (t << 1) | pit;
				t = (lap_buff_[lap_count_] >> 1) - (lap_buff_[lap_count_ - 1] >> 1);
				if(pit == 0) {
					if(lap_best_ == 0) lap_best_ = t;
					else if(lap_best_ > t) lap_best_ = t;
				}
				trg_loop_ = TRIGGER_LOOP_DELAY;
			}
		}
	};
}
