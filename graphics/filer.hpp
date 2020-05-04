#pragma once
//=====================================================================//
/*!	@file
	@brief	ファイル選択ユーティリティー @n
			ファイルを選択を行う GUI を提供する。@n
			スイッチによる操作と、タッチパネルによる操作をサポートする。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/file_io.hpp"
#include "common/fixed_stack.hpp"

namespace gui {


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ファイラー・ベース・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class filer_base {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ファイラー制御型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ctrl : uint8_t {
			MOUNT,		///< ＳＤカードのマウント状態
			OPEN,		///< ファイラーを起動
			UP,			///< スクロール上
			DOWN,		///< スクロール下
			BACK,		///< ディレクトリーを戻る
			SELECT,		///< 選択
			INFO,		///< ファイルの情報を表示
			CLOSE,		///< ファイラーを閉じる
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	制御データ構築
			@param[in]	pos		ファイラー制御型
			@param[in]	ctrl	制御データ（参照）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static void set(ctrl pos, uint32_t& ctrl) noexcept
		{
			ctrl |= 1 << static_cast<uint8_t>(pos);
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ステータス型 @n
					ファイラーが閉じた時の状態
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class status : uint8_t {
			NONE,	///< 未定義動作
			FILE,	///< ファイルが選択された
			CANCEL,	///< 操作がキャンセルされた
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ファイラー・クラス
		@param[in]	RDR	描画クラス型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class RDR>
	class filer : public filer_base {

		using GLC = typename RDR::glc_type;

		static const int32_t FRAME_PER_FILES = 10;  ///< ディレクトリー取得で処理するフレーム辺りのファイル数
		static const int16_t MODAL_RADIUS = 10;  ///< modal round radius

		static const int16_t SPC = 2;									///< 文字間隙間
		static const int16_t FLN = RDR::font_type::height + SPC;		///< 行幅
		static const int16_t SCN = (RDR::glc_type::height - SPC) / FLN;	///< 行数

		static const uint16_t REPEAT_DELAY = 40;	///< リピートまでの時間（フレーム数）
		static const uint16_t REPEAT_CYCLE = 8;		///< リピート間隔（フレーム数）

		typedef graphics::def_color DEF_COLOR;

		RDR&		rdr_;

		typedef utils::dir_list DLIST;
		DLIST		dlist_;

		uint32_t	ctrl_;

		struct rdr_st {
			int16_t		vofs_;
			int16_t		vpos_;
			int16_t		hmax_;
			int16_t		sel_pos_;
			uint16_t	num_;
			int16_t		match_;

			rdr_st() noexcept : vofs_(0), vpos_(0), hmax_(0),
				sel_pos_(0), num_(0), match_(-1)
			{ }
		};
		rdr_st		rdr_st_;

		bool		open_;
		bool		info_;

		struct pos_t {
			int16_t		vofs_;
			int16_t		sel_pos_;
			pos_t(int16_t vofs = 0, int16_t sel_pos = 0) noexcept :
				vofs_(vofs), sel_pos_(sel_pos) { }
		};
		typedef utils::fixed_stack<pos_t, 16> POS_STACK;
		POS_STACK	pos_stack_;

		bool		touch_lvl_;
		bool		touch_pos_;
		bool		touch_neg_;
		uint8_t		touch_num_;
		vtx::spos	touch_;
		vtx::spos	touch_org_;
		vtx::spos	touch_end_;

		uint8_t		back_num_;
		bool		tto_;
		uint16_t	repeat_;


		static uint32_t ctrl_mask_(ctrl ctrl) noexcept
		{
			return 1 << static_cast<uint8_t>(ctrl);
		}


		void dir_draw_func_(const char* name, const FILINFO* fi, bool dir, void* opt) noexcept
		{
			rdr_st& t = *static_cast<rdr_st*>(opt);
			bool draw = false;
			if(t.match_ < 0) {
				draw = true;
			} else if(t.num_ == static_cast<uint16_t>(t.match_)) {
				draw = true;
			}
			if(draw && t.vpos_ >= 0 && t.vpos_ < RDR::glc_type::height) {
				rdr_.set_fore_color(DEF_COLOR::Black);
				rdr_.fill_box(vtx::srect(SPC, t.vpos_,
					RDR::glc_type::width - SPC * 2, RDR::font_type::height));
				rdr_.set_fore_color(DEF_COLOR::White);
				if(dir) rdr_.draw_font(vtx::spos(SPC, t.vpos_), '/');
				if(dir) {
					rdr_.set_fore_color(DEF_COLOR::Blue);
				} else {
					rdr_.set_fore_color(DEF_COLOR::White);
				}
				auto w = rdr_.draw_text(vtx::spos(SPC + 8, t.vpos_), name);
				if(t.hmax_ < w) t.hmax_ = w;
			}
			t.vpos_ += FLN;
			++t.num_;
		}


		void start_dir_draw_(int16_t match = -1) noexcept
		{
			rdr_st_.vpos_ = rdr_st_.vofs_ + 2;
			rdr_st_.num_ = 0;
			rdr_st_.match_ = match;
			char tmp[FF_MAX_LFN + 1];
			if(utils::file_io::pwd(tmp, sizeof(tmp))) {
				dlist_.start(tmp);
			}
		}


		void draw_sel_frame_(int16_t pos)
		{
			int16_t h = RDR::font_type::height + 2;
			int16_t y = pos * h;
			rdr_.frame(vtx::srect(0, y, rdr_st_.hmax_ + 3, h + 1));
		}


		void scan_dir_(bool back)
		{
			if(back) {
				if(pos_stack_.empty()) {
					rdr_st_.vofs_ = 0;
					rdr_st_.sel_pos_ = 0;
				} else {
					const auto& t = pos_stack_.pop();
					rdr_st_.vofs_ = t.vofs_;
					rdr_st_.sel_pos_ = t.sel_pos_;
				}
			} else {
				rdr_st_.vofs_ = 0;
				rdr_st_.sel_pos_ = 0;
			}
			start_dir_draw_();
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	rdr		レンダリング・インスタンス
			@param[in]	tto		３本指タッチオープンを無効にする場合「false」
		*/
		//-----------------------------------------------------------------//
		filer(RDR& rdr, bool tto = true) noexcept : rdr_(rdr), dlist_(),
			ctrl_(0), rdr_st_(), open_(false), info_(false), 
			touch_lvl_(false), touch_pos_(false), touch_neg_(false), touch_num_(0),
			touch_(0), touch_org_(0), touch_end_(0),
			back_num_(0), tto_(tto), repeat_(0)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	モーダルウィンドウ描画（画面の中心に表示される）
			@param[in]	size	大きさ
			@param[in]	text	テキスト
		*/
		//-----------------------------------------------------------------//
		void modal(const vtx::spos& size, const char* text) noexcept
		{
			vtx::spos pos((GLC::width  - size.x) / 2, (GLC::height - size.y) / 2);
			rdr_.set_fore_color(DEF_COLOR::White);
			rdr_.set_back_color(DEF_COLOR::Darkgray);
			vtx::srect r(pos, size);
			rdr_.round_box(r, MODAL_RADIUS);
			r.org += 2;
			r.size -= 2 * 2;
			rdr_.swap_color();
			rdr_.round_box(r, MODAL_RADIUS - 2);

			auto sz = rdr_.at_font().get_text_size(text);
			rdr_.swap_color();
			rdr_.draw_text(pos + (size - sz) / 2, text);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ファイラーの状態を返す。
			@return ファイラーの状態、「true」ならファイラーが有効
		*/
		//-----------------------------------------------------------------//
		bool get_state() const noexcept { return open_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	スクリーン・タッチ位置設定 @n
					※タッチ情報は毎フレーム設定する事。
			@param[in]	num		タッチ数
			@param[in]	pos		タッチ位置
		*/
		//-----------------------------------------------------------------//
		void set_touch(uint8_t num, const vtx::spos& pos) noexcept
		{
			touch_num_ = num;
			bool lvl = num > 0;
			touch_pos_ = !touch_lvl_ &  lvl;
			touch_neg_ =  touch_lvl_ & !lvl;
			touch_lvl_ = lvl;
			touch_ = pos;
			if(touch_pos_) {
				touch_org_ = touch_;
			}
			if(touch_neg_) {
				touch_end_ = touch_;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	アップデート（毎フレーム呼ぶ）
			@param[in]	ctrl	ファイラー制御
			@param[in]	dst		選択パス受け取り先
			@param[in]	dstlen	選択パス最大サイズ
			@return ステータス型による状態の返却
		*/
		//-----------------------------------------------------------------//
		status update(uint32_t ctrl, char* dst, uint32_t dstlen) noexcept
		{
			uint32_t ptrg = ~ctrl_ &  ctrl;
			uint32_t ntrg =  ctrl_ & ~ctrl;
			ctrl_ = ctrl;

			dlist_.service(FRAME_PER_FILES,
				[&](const char* name, const FILINFO* fi, bool dir, void* opt) {
				dir_draw_func_(name, fi, dir, opt); }, true, &rdr_st_);

			if((ntrg & ctrl_mask_(ctrl::MOUNT))) {  // SD カードのマウント状態
				open_ = false;
				pos_stack_.clear();
				rdr_.clear(DEF_COLOR::Black);
			}
			if((ctrl & ctrl_mask_(ctrl::MOUNT)) == 0) {
				return status::NONE;
			}

			bool opt = false;
			if(back_num_ == 3 && touch_num_ < 3) {
				if(!tto_ && !open_) ;  // 3 touch open が無効な場合 
				else {
					opt = true;
				}
			}
			bool open = open_;
			if((ptrg & ctrl_mask_(ctrl::OPEN)) != 0 || opt) {
				open_ = !open_;
				rdr_.clear(DEF_COLOR::Black);
				if(open_) {
					rdr_.at_font().at_kfont().flush_cash();
					scan_dir_(false);
				}
			}
			if((ptrg & ctrl_mask_(ctrl::CLOSE)) != 0) {
				rdr_.clear(DEF_COLOR::Black);
				open_ = false;
			}
			back_num_ = touch_num_;

			if(!open_) {
				if(open && !open_) {
					return status::CANCEL;
				} else {
					return status::NONE;
				}
			}

			{  // ドラッグでフォーカス移動
				if(touch_neg_) {
					auto dx = touch_.x - touch_org_.x;
					if(dx >= FLN * 2) {
						ptrg |= ctrl_mask_(ctrl::SELECT);
						touch_org_.x = touch_.x;
					} else if(dx <= -FLN * 2) {
						ptrg |= ctrl_mask_(ctrl::BACK);
						touch_org_.x = touch_.x;
					}
				}
				if(touch_lvl_) {
					auto dy = touch_.y - touch_org_.y;
					if(dy >= FLN) {
						ptrg |= ctrl_mask_(ctrl::DOWN);
						touch_org_.y = touch_.y;
					} else if(dy <= -FLN) {
						ptrg |= ctrl_mask_(ctrl::UP);
						touch_org_.y = touch_.y;
					}
				}
			}

			{
				auto t = ctrl_ & (ctrl_mask_(ctrl::DOWN) | ctrl_mask_(ctrl::UP));
				if(t != 0) {
					++repeat_;
					if(repeat_ >= REPEAT_DELAY) {
						ptrg |= t; 
						repeat_ -= REPEAT_CYCLE;
					}
				} else {
					repeat_ = 0;
				}
			}

			{
				if(dlist_.probe()) return status::NONE;
				if(rdr_st_.num_ < static_cast<int16_t>(dlist_.get_total())) {
					return status::NONE;
				}
			}

			if(ptrg & ctrl_mask_(ctrl::INFO)) {
				if(info_) {
					pos_stack_.push(pos_t(rdr_st_.vofs_, rdr_st_.sel_pos_));
					info_ = false;
					rdr_.clear(DEF_COLOR::Black);
					scan_dir_(true);
					return status::NONE;
				} else {
					info_ = true;
					uint32_t idx = rdr_st_.sel_pos_ - rdr_st_.vofs_ / FLN;
					char tmp[FF_MAX_LFN + 1];
					if(!utils::file_io::pwd(tmp, sizeof(tmp))) {
						return status::NONE;
					}
					if(!utils::file_io::get_dir_path(tmp, idx, dst, dstlen)) {
						return status::NONE;
					}
					bool dir = false;
					uint32_t l = strlen(dst);
					if(dst[l - 1] == '/') {
						dir = true;
						dst[l - 1] = 0;
					}
					auto t = utils::file_io::get_time(dst);
					struct tm *m = localtime(&t);
					utils::sformat("%s %2d %4d %02d:%02d\n", tmp, sizeof(tmp))
						% get_mon(m->tm_mon)
						% static_cast<int>(m->tm_mday)
						% static_cast<int>(m->tm_year + 1900)
						% static_cast<int>(m->tm_hour)
						% static_cast<int>(m->tm_min);
					if(!dir) {
						auto n = utils::file_io::get_file_size(dst);
						l = strlen(tmp);
						utils::sformat("%u bytes", &tmp[l], sizeof(tmp) - l) % n;
					}
					modal(vtx::spos(300, 80), tmp);
				}
			}
			if(info_) {
				return status::NONE;
			}

			// 選択フレームの描画
			rdr_.set_fore_color(DEF_COLOR::White);
			draw_sel_frame_(rdr_st_.sel_pos_);
			int16_t pos = rdr_st_.sel_pos_;
			if(ptrg & ctrl_mask_(ctrl::UP)) {
				pos--;
			}
			if(ptrg & ctrl_mask_(ctrl::DOWN)) {
				++pos;
			}
			int16_t vofs = rdr_st_.vofs_;
			int16_t scn = SCN;
			if(rdr_st_.num_ < scn) scn = rdr_st_.num_; 
			if(pos < 0) {
				pos = 0;
				vofs += FLN;
			} else if(pos >= scn) {
				pos = scn - 1;
				vofs -= FLN;
			}
			int16_t lim = 0;
			if(rdr_st_.num_ > scn) {
				lim = -(rdr_st_.num_ - scn) * FLN;
			}
			if(vofs > 0) {
				vofs = 0;
			} else if(vofs < lim) {
				vofs = lim;
			}
			if(vofs != rdr_st_.vofs_) {
				rdr_.set_fore_color(DEF_COLOR::Black);
				draw_sel_frame_(rdr_st_.sel_pos_);  // delete frame
				int16_t match = -1;
				if(vofs < rdr_st_.vofs_) {  // down
					rdr_.scroll(FLN);
					match = -vofs / FLN + (RDR::glc_type::height / FLN) - 1;
				} else if(vofs > rdr_st_.vofs_) {  // up
					rdr_.scroll(-FLN);
					match = -vofs / FLN;
				}
				rdr_st_.vofs_ = vofs;
				start_dir_draw_(match);
			}
			
			if(pos != rdr_st_.sel_pos_) {
				rdr_.set_fore_color(DEF_COLOR::Black);
				draw_sel_frame_(rdr_st_.sel_pos_);
				rdr_st_.sel_pos_ = pos;
			}

			if(ptrg & ctrl_mask_(ctrl::SELECT)) {
				uint32_t idx = rdr_st_.sel_pos_ - rdr_st_.vofs_ / FLN;
				char root[FF_MAX_LFN + 1];
				if(!utils::file_io::pwd(root, sizeof(root))) {
					return status::NONE;
				}
				if(!utils::file_io::get_dir_path(root, idx, dst, dstlen)) {
					return status::NONE;
				}
				uint32_t l = strlen(dst);
				if(dst[l - 1] == '/') {  // directory ?
					pos_stack_.push(pos_t(rdr_st_.vofs_, rdr_st_.sel_pos_));
					dst[l - 1] = 0;
					utils::file_io::cd(dst);
					rdr_.clear(DEF_COLOR::Black);
					scan_dir_(false);
				} else {
					rdr_.clear(DEF_COLOR::Black);
					open_ = false;
					return status::FILE;
				}
			}

			if(ptrg & ctrl_mask_(ctrl::BACK)) {
				if(!pos_stack_.empty()) {
					utils::file_io::cd("..");
					rdr_.clear(DEF_COLOR::Black);
					scan_dir_(true);
				}
			}

			return status::NONE;
		}
	};
}
