#pragma once
//=====================================================================//
/*!	@file
	@brief	オーディオ GUI クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/sci_i2c_io.hpp"

#include "graphics/font8x16.hpp"
#include "graphics/kfont.hpp"
#include "graphics/graphics.hpp"
#include "graphics/filer.hpp"
#include "graphics/simple_dialog.hpp"
#include "graphics/img_in.hpp"
#include "graphics/widget_director.hpp"
#include "graphics/scaling.hpp"
#include "graphics/img_in.hpp"

#include "sound/tag.hpp"
#include "sound/af_play.hpp"

#include "chip/FAMIPAD.hpp"
#include "chip/FT5206.hpp"

// ファミコン・パッドでの操作を有効にする場合
// #define USE_FAMIPAD

namespace app {

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    /*!
        @brief  AUDIO GUI クラス
    */
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    class audio_gui {
	public:
		static const int16_t LCD_X = 480;
		static const int16_t LCD_Y = 272;
		static const auto PIX = graphics::pixel::TYPE::RGB565;

		typedef utils::fixed_fifo<uint8_t, 64> RB64;
		typedef utils::fixed_fifo<uint8_t, 64> SB64;

#if defined(SIG_RX65N)
		typedef device::PORT<device::PORT6, device::bitpos::B3> LCD_DISP;
		typedef device::PORT<device::PORT6, device::bitpos::B6> LCD_LIGHT;
		static const uint32_t LCD_ORG = 0x0000'0100;
		typedef device::PORT<device::PORT0, device::bitpos::B7> FT5206_RESET;
		typedef device::sci_i2c_io<device::SCI6, RB64, SB64, device::port_map::option::FIRST_I2C> FT5206_I2C;
#ifdef USE_FAMIPAD
		// Famicon PAD (CMOS 4021B Shift Register)
		// 電源は、微小なので、接続を簡単に行う為、ポート出力を電源として利用
		typedef device::PORT<device::PORT6, device::bitpos::B0> PAD_VCC;
		typedef device::PORT<device::PORT6, device::bitpos::B1> PAD_GND;
		typedef device::PORT<device::PORT6, device::bitpos::B2> PAD_P_S;
		typedef device::PORT<device::PORT6, device::bitpos::B5> PAD_CLK;
		typedef device::PORT<device::PORT7, device::bitpos::B3> PAD_OUT;
		typedef chip::FAMIPAD<PAD_P_S, PAD_CLK, PAD_OUT> FAMIPAD;
#endif

#elif defined(SIG_RX72N)
		typedef device::PORT<device::PORTB, device::bitpos::B3> LCD_DISP;
		typedef device::PORT<device::PORT6, device::bitpos::B7> LCD_LIGHT;
		static const uint32_t LCD_ORG = 0x0080'0000;
		typedef device::PORT<device::PORT6, device::bitpos::B6> FT5206_RESET;
		typedef device::sci_i2c_io<device::SCI6, RB64, SB64, device::port_map::option::THIRD_I2C> FT5206_I2C;
#ifdef USE_FAMIPAD
		// Famicon PAD (CMOS 4021B Shift Register)
		// RX72N では、Pmod1 に接続する。
		// PMOD1                                                PAD_3V3:     Pmod1-6
		// PMOD1                                                PAD_GND:     Pmod1-5 
		typedef device::PORT<device::PORT5, device::bitpos::B1> PAD_P_S;  // Pmod1-4
		typedef device::PORT<device::PORT5, device::bitpos::B2> PAD_CLK;  // Pmod1-3
		typedef device::PORT<device::PORT5, device::bitpos::B0> PAD_OUT;  // Pmod1-2
		typedef chip::FAMIPAD<PAD_P_S, PAD_CLK, PAD_OUT, 40> FAMIPAD;
#endif
#endif
		typedef device::glcdc_mgr<device::GLCDC, LCD_X, LCD_Y, PIX> GLCDC;

		typedef graphics::font8x16 AFONT;
//  	for cash into SD card /kfont16.bin
//		typedef graphics::kfont<16, 16, 64> KFONT;
		typedef graphics::kfont<16, 16> KFONT;
		typedef graphics::font<AFONT, KFONT> FONT;

//	typedef device::drw2d_mgr<GLCDC, FONT> RENDER;
		// ソフトウェアーレンダラー
		typedef graphics::render<GLCDC, FONT> RENDER;
		// 標準カラーインスタンス
		typedef graphics::def_color DEF_COLOR;

	private:
#ifdef USE_FAMIPAD
		FAMIPAD		famipad_;
#endif

		GLCDC	glcdc_;
		AFONT	afont_;
		KFONT	kfont_;
		FONT	font_;
		RENDER	render_;

		FT5206_I2C	ft5206_i2c_;
		typedef chip::FT5206<FT5206_I2C> TOUCH;
		TOUCH	touch_;
		// RX65N Envision Kit: INT to P02(IRQ10), not use
		// RX72N Envision Kit: INT to P34(IRQ4), not use

		typedef gui::filer_base FILER_BASE;
		typedef gui::filer<RENDER> FILER;
		FILER	filer_;

		typedef gui::simple_dialog<RENDER, TOUCH> DIALOG;
		DIALOG	dialog_;

		typedef gui::widget_director<RENDER, TOUCH, 32> WIDD;
		WIDD	widd_;

		typedef gui::text TEXT;
		TEXT	album_;
		TEXT	title_;
		TEXT	artist_;
//		TEXT	year_;
//		TEXT	td_info_;

		typedef gui::slider SLIDER;
		SLIDER	slider_;
		typedef gui::button BUTTON;
		BUTTON	select_;
		BUTTON	rew_;
		BUTTON	play_;
		BUTTON	ff_;

		typedef img::scaling<RENDER> SCALING;
		SCALING		scaling_;

		typedef img::img_in<SCALING> IMG_IN;
		IMG_IN		img_in_;

		uint32_t	ctrl_;

		char		path_[256];

		utils::STR256	fin_artist_;

		struct th_sync_t {
			volatile uint8_t	put;
			volatile uint8_t	get;
			th_sync_t() : put(0), get(0) { }
			void send() { ++put; }
			bool sync() const { return put == get; }
			void recv() { get = put; }
			void clear() { get = put = 0; }
		};

		th_sync_t	play_stop_;
		th_sync_t	play_rew_;
		th_sync_t	play_pause_;
		th_sync_t	play_ff_;

		char			path_tag_[256];
		th_sync_t		req_tag_;
		sound::tag_t	play_tag_;

		bool		mount_state_;
		bool		filer_state_;


		int16_t render_text_(int16_t x, int16_t y, const char* text)
		{
			render_.swap_color();
			auto xx = render_.draw_text(vtx::spos(x, y), text);
			render_.swap_color();
			render_.draw_text(vtx::spos(x + 1, y + 1), text);
			return xx;
		}


		void render_tag_(utils::file_io& fin, const sound::tag_t& tag) noexcept
		{
			render_.set_fore_color(graphics::def_color::Black);
			render_.fill_box(vtx::srect(0, 0, LCD_X - LCD_Y, 20 * 6));
			render_.fill_box(vtx::srect(LCD_X - LCD_Y, 0, LCD_Y, LCD_Y));
			render_.sync_frame(false);

			scaling_.set_offset(vtx::spos(LCD_X - LCD_Y, 0));
			if(tag.get_apic().len_ > 0) {
				if(!img_in_.select_decoder(tag.get_apic().ext_)) {
					scaling_.set_scale();
					img_in_.load("/NoImage.jpg");
				} else {
					auto pos = fin.tell();
					fin.seek(utils::file_io::SEEK::SET, tag.get_apic().ofs_);
					img::img_info ifo;
					if(!img_in_.info(fin, ifo)) {

						auto st = img_in_.at_jpeg().get_status();
						utils::format("JPEG status: %d\n") % static_cast<int>(st);

						scaling_.set_scale();
						img_in_.load("/NoImage.jpg");
						render_.swap_color();
						render_.draw_text(vtx::spos(LCD_X - LCD_Y, 0), "image decode error.");
						render_.swap_color();
					} else {
						auto n = std::max(ifo.width, ifo.height);
						scaling_.set_scale(LCD_Y, n);
						img_in_.load(fin);
					}
					fin.seek(utils::file_io::SEEK::SET, pos);
				}
			} else {
				scaling_.set_scale();
				img_in_.load("/NoImage.jpg");
			}

			render_.set_fore_color(graphics::def_color::White);
			render_.set_back_color(graphics::def_color::Gray);
//			render_text_(0, 0 * 20, tag.get_album().c_str());
			album_.set_title(tag.get_album().c_str());
			album_.reset_scroll();
//			render_text_(0, 1 * 20, tag.get_title().c_str());
			title_.set_title(tag.get_title().c_str());
			title_.reset_scroll();
			{
				fin_artist_ = tag.get_artist().c_str();
///				auto x = render_text_(0, 2 * 20, tag.get_artist().c_str());
				if(!tag.get_artist2().empty()) {
					fin_artist_ += " / ";
					fin_artist_ += tag.get_artist2().c_str();
///					x = render_text_(x, 2 * 20, " / ");
///					render_text_(x, 2 * 20, tag.get_artist2().c_str());
				}
				artist_.set_title(fin_artist_.c_str());
				artist_.reset_scroll();
			}
			{
				auto x = render_text_(0, 3 * 20, tag.get_year().c_str());
				if(!tag.get_date().empty()) {
					x = render_text_(x, 3 * 20, "/");
					char tmp[8];
					utils::sformat("%c%c/%c%c", tmp, sizeof(tmp))
						% tag.get_date()[0] % tag.get_date()[1]
						% tag.get_date()[2] % tag.get_date()[3];
					render_text_(x, 3 * 20, tag.get_date().c_str());
				}
			}
			{
				char tmp[10];
				int16_t x = 0;
				if(!tag.get_disc().empty()) {
					utils::sformat("D:%s", tmp, sizeof(tmp)) % tag.get_disc().c_str();
					x = render_text_(0, 4 * 20, tmp);
				}
				if(!tag.get_track().empty()) {
					utils::sformat("T:%s", tmp, sizeof(tmp)) % tag.get_track().c_str();
					if(x > 0) x += 8;
					render_text_(x, 4 * 20, tmp);
				}
			}
			render_.sync_frame(false);
		}

	public:
		//-------------------------------------------------------------//
		/*!
			@brief  AUDIO GUI コンストラクタ
		*/
		//-------------------------------------------------------------//
		audio_gui() noexcept :
			glcdc_(nullptr, reinterpret_cast<void*>(LCD_ORG)),
			afont_(), kfont_(), font_(afont_, kfont_),
			render_(glcdc_, font_),
			ft5206_i2c_(), touch_(ft5206_i2c_),
			filer_(render_, false),
			dialog_(render_, touch_),
			widd_(render_, touch_),
			album_(  vtx::srect(   0, 20*0, 206, 20)),
		   	title_(  vtx::srect(   0, 20*1, 206, 20)),
		   	artist_( vtx::srect(   0, 20*2, 206, 20)),
//			year_(   vtx::srect(   0, 20*3, 206, 20)),
//			td_info_(vtx::srect(   0, 20*4, 206, 20)),
			slider_(vtx::srect(   0, 272-64*2-6-18, 206, 14)),
			select_(vtx::srect(   0, 272-64*2-6, 64, 64), "Sel"),
			rew_(   vtx::srect(70*0, 272-64, 64, 64), "<<"),
			play_(  vtx::srect(70*1, 272-64, 64, 64), "-"),
			ff_(    vtx::srect(70*2, 272-64, 64, 64), ">>"),
			scaling_(render_), img_in_(scaling_),
			ctrl_(0), path_{ 0 },
			fin_artist_(),
			play_stop_(), play_rew_(), play_pause_(), play_ff_(),
			path_tag_{ 0 }, req_tag_(), play_tag_(),
			mount_state_(false), filer_state_(false)
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
			{  // GLCDC の初期化
				LCD_DISP::DIR  = 1;
				LCD_LIGHT::DIR = 1;
				LCD_DISP::P  = 0;  // DISP Disable
				LCD_LIGHT::P = 0;  // BackLight Disable (No PWM)
				if(glcdc_.start()) {
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

			{  // DRW2D 初期化
				auto ver = render_.get_version();
				utils::format("DRW2D Version: %04X\n") % ver;
				if(render_.start()) {
					utils::format("Start DRW2D\n");
				} else {
					utils::format("DRW2D Fail\n");
				}
			}

#ifdef USE_FAMIPAD
			{  // ファミコンパッド初期化
#if defined(SIG_RX65N)
				PAD_VCC::DIR = 1;
				PAD_VCC::P = 1;
				PAD_GND::DIR = 1;
				PAD_GND::P = 0;
#endif
				famipad_.start();
			}
#endif

			{  // FT5206 touch screen controller
				TOUCH::reset<FT5206_RESET>();
				uint8_t intr_lvl = 1;
				if(!ft5206_i2c_.start(FT5206_I2C::SPEED::STANDARD, intr_lvl)) {
					utils::format("FT5206 I2C Start Fail...\n");
				}
				if(!touch_.start()) {
					utils::format("FT5206 Start Fail...\n");
				}
			}
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
			@brief  初期化
		*/
		//-------------------------------------------------------------//
		void open() noexcept
		{
			album_.enable();
			album_.set_base_color(DEF_COLOR::DarkSafeColor);
			title_.enable();
			title_.set_base_color(DEF_COLOR::LightSafeColor);
			artist_.enable();
			artist_.set_base_color(DEF_COLOR::DarkSafeColor);
//			year_.enable();
//			year_.set_base_color(DEF_COLOR::LightSafeColor);
//			td_info_.enable();
//			td_info_.set_base_color(DEF_COLOR::DarkSafeColor);

			slider_.enable_read_only();
			slider_.enable(false);

			select_.enable();
            select_.at_select_func() = [this](uint32_t id) {
				FILER_BASE::set(FILER_BASE::ctrl::OPEN, ctrl_);
			};

			rew_.enable();
			rew_.at_select_func() = [this](uint32_t id) {
				play_rew_.send();
			};
			play_.enable();
			play_.at_select_func() = [this](uint32_t id) {
				play_pause_.send();
			};
			ff_.enable();
			ff_.at_select_func() = [this](uint32_t id) {
				play_ff_.send();
			};
		}


		//-------------------------------------------------------------//
		/*!
			@brief  GUI 有効 / 無効
			@param[in]	ena	「false」の場合無効
		*/
		//-------------------------------------------------------------//
		void enable(bool ena = true) noexcept
		{
			ff_.enable(ena);
			play_.enable(ena);
			rew_.enable(ena);
			select_.enable(ena);
			slider_.enable(ena);
		}


		//-------------------------------------------------------------//
		/*!
			@brief  GUI 関係更新
			@param[in]	mount	SD カードマウント状態
			@param[in]	st		コーデックのステート
			@return ファイルが選択されたら「true」
		*/
		//-------------------------------------------------------------//
		bool update(bool mount, sound::af_play::STATE st) noexcept
		{
			render_.sync_frame();
			touch_.update();			

			if(st == sound::af_play::STATE::PLAY) {
				play_.set_title("Pause");
			} else if(st == sound::af_play::STATE::PAUSE) {
				play_.set_title("Play");
			} else {
				play_.set_title("-");
			}

			ctrl_ = 0;
			if(mount) {
				FILER_BASE::set(FILER_BASE::ctrl::MOUNT, ctrl_);
				if(!mount_state_ && mount) {  // SD がマウントされたら、画面を消して GUI 再描画
					render_.clear(DEF_COLOR::Black);
					widd_.redraw_all();
				}
			} else {
				dialog_.modal(vtx::spos(400, 60),
					"Insert the SD card.\n(The one with the music file.)");
				FILER_BASE::set(FILER_BASE::ctrl::CLOSE, ctrl_);
				if(st == sound::af_play::STATE::PLAY) {
					play_stop_.send();
				}
			}
			mount_state_ = mount;

			// ファイラーが有効なら、GUI を無効、ファイラーが無効なら GUI を有効にする。
			auto fs = filer_.get_state();
			enable(!fs);
			// ファイラーが閉じた時に GUI を再描画
			if(filer_state_ && !fs) {
				widd_.redraw_all();
			}
			filer_state_ = fs;

			widd_.update();

			bool ret = false;
			{  // ファイラーの操作
#ifdef ENABLE_FAMIPAD
				auto data = get_fami_pad();
				if(chip::on(data, chip::FAMIPAD_ST::SELECT)) {
					FILER_BASE::set(FILER_BASE::ctrl::OPEN, ctrl_);
				}
				if(chip::on(data, chip::FAMIPAD_ST::UP)) {
					FILER_BASE::set(FILER_BASE::ctrl::UP, ctrl_);
				}
				if(chip::on(data, chip::FAMIPAD_ST::DOWN)) {
					FILER_BASE::set(FILER_BASE::ctrl::DOWN, ctrl_);
				}
				if(chip::on(data, chip::FAMIPAD_ST::LEFT)) {
					FILER_BASE::set(FILER_BASE::ctrl::BACK, ctrl_);
				}
				if(chip::on(data, chip::FAMIPAD_ST::RIGHT)) {
					FILER_BASE::set(FILER_BASE::ctrl::SELECT, ctrl_);
				}
#endif
				auto tnum = touch_.get_touch_num();
				const auto& t = touch_.get_touch_pos(0);
				filer_.set_touch(tnum, t.pos); 
				path_[0] = 0;
				auto fst = filer_.update(ctrl_, path_, sizeof(path_));
				if(fst == FILER_BASE::status::FILE) {  // ファイル選択
//					utils::format("Play: '%s'\n") % path_;
					// プレイヤーが再生中なら停止を送る。
					if(st == sound::af_play::STATE::PLAY || st == sound::af_play::STATE::PAUSE) {
						play_stop_.send();
					}
					ret = true;
				} else if(fst == FILER_BASE::status::CANCEL) {  // ファイル選択キャンセル
					req_tag_.send();
				}
			}
			if(!req_tag_.sync()) {
				utils::file_io fin;
				if(fin.open(path_tag_, "rb")) {
					req_tag_.recv();
					render_tag_(fin, play_tag_);
					fin.close();
				}
			}
			return ret;
		}


		//-------------------------------------------------------------//
		/*!
			@brief  演奏ファイル名の登録
			@param[in]	fn	ファイル名
		*/
		//-------------------------------------------------------------//
		void set_file_name(const char* fn) noexcept
		{
			utils::file_io::make_full_path(fn, path_tag_, sizeof(path_tag_));
		}


		//-------------------------------------------------------------//
		/*!
			@brief  コーデック制御 @n
					※非同期、外部のタスクがこの API を呼ぶ
			@return コーデック制御ステート
		*/
		//-------------------------------------------------------------//
		sound::af_play::CTRL get_ctrl() noexcept
		{
			sound::af_play::CTRL c = sound::af_play::CTRL::NONE;
			if(!play_stop_.sync()) {
				play_stop_.recv();
				return sound::af_play::CTRL::STOP;
			}
			if(!play_pause_.sync()) {
				play_pause_.recv();
				return sound::af_play::CTRL::PAUSE;
			}
			if(!play_rew_.sync()) {
				play_rew_.recv();
				return sound::af_play::CTRL::REPLAY;
			}
			if(!play_ff_.sync()) {
				play_ff_.recv();
				return sound::af_play::CTRL::NEXT;
			}
			return c;
		}


		//-------------------------------------------------------------//
		/*!
			@brief  TAG のレンダリング @n
					※非同期、外部のタスクがこの API を呼ぶ
			@param[in]	fin		ファイル操作コンテキスト
			@param[in]	tag		タグ
		*/
		//-------------------------------------------------------------//
		void render_tag(utils::file_io& fin, const sound::tag_t& tag) noexcept
		{
			play_tag_ = tag;
			req_tag_.send();
		}


		//-------------------------------------------------------------//
		/*!
			@brief  時間のレンダリング @n
					※非同期、外部のタスクがこの API を呼ぶ
			@param[in]	t		時間
			@param[in]	all		全体時間
		*/
		//-------------------------------------------------------------//
		void render_time(uint32_t t, uint32_t all) noexcept
		{
			if(filer_.get_state()) return;

			uint16_t sec = t % 60;
			uint16_t min = (t / 60) % 60;
			uint16_t hor = (t / 3600) % 24;
			uint16_t asec = all % 60;
			uint16_t amin = (all / 60) % 60;
			uint16_t ahor = (all / 3600) % 24;
			char tmp[32];
			utils::sformat("%02d:%02d:%02d / %02d:%02d:%02d", tmp, sizeof(tmp))
				% hor % min % sec % ahor % amin % asec;
			render_.set_fore_color(graphics::def_color::Black);
			render_.fill_box(vtx::srect(0, 5 * 20, 8 * 8, 16));
			render_.set_fore_color(graphics::def_color::White);
			render_.draw_text(vtx::spos(0, 5 * 20), tmp);
			if(all > 0) {
				slider_.set_ratio(static_cast<float>(t) / static_cast<float>(all));
				slider_.set_update();
			}
			render_.sync_frame(false);
		}


		//-------------------------------------------------------------//
		/*!
			@brief  ファイル名の取得
			@return ファイル名
		*/
		//-------------------------------------------------------------//
		const char* get_filename() const noexcept { return path_; }
	};
}
