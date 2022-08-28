#pragma once
//=====================================================================//
/*!	@file
	@brief	Widget クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/vtx.hpp"
#include "graphics/color.hpp"
#include "common/file_io.hpp"

namespace gui {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	Widget クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct widget {

		typedef graphics::def_color DEF_COLOR;	///< 標準カラー

		static constexpr int16_t DEF_FRAME_ROUND_RADIUS   = 6;	///< 標準、フレーム、コーナーの半径
		static constexpr int16_t DEF_FRAME_FRAME_WIDTH    = 2;	///< 標準、フレーム、外周のフレーム幅

		static constexpr int16_t DEF_DIALOG_ROUND_RADIUS  = 6;	///< 標準、ダイアログ、コーナーの半径
		static constexpr int16_t DEF_DIALOG_FRAME_WIDTH   = 2;	///< 標準、ダイアログ、外周のフレーム幅

		static constexpr int16_t DEF_BUTTON_ROUND_RADIUS  = 6;	///< 標準、ボタン、コーナーの半径
		static constexpr int16_t DEF_BUTTON_FRAME_WIDTH   = 3;	///< 標準、ボタン、外周のフレーム幅
		static constexpr int16_t DEF_BUTTON_HEIGHT        = 30;	///< 標準、ボタン、サイズが省略された場合の高さ
		static constexpr int16_t DEF_BUTTON_TO_STR        = 4;	///< 標準、ボタン、フレームからタイトルまでの距離

		static constexpr int16_t DEF_SLIDER_ROUND_RADIUS  = 10;	///< 標準、スライダー、コーナーの半径
		static constexpr int16_t DEF_SLIDER_FRAME_WIDTH   = 3;	///< 標準、スライダー、外周のフレーム幅
		static constexpr int16_t DEF_SLIDER_HANDLE_SIZE   = 20;	///< 標準、スライダー、ハンドルの大きさ

		static constexpr int16_t DEF_MENU_ROUND_RADIUS    = 6;	///< 標準、メニュー、コーナー半径
		static constexpr int16_t DEF_MENU_HEIGHT          = 28;	///< 標準、メニュー、アイテムの高さ
		static constexpr int16_t DEF_MENU_SIGN_SPACE      = 5;	///< 標準、メニュー、サインまでの隙間
		static constexpr int16_t DEF_MENU_SIGN_SIZE       = 6;	///< 標準、メニュー、サインの大きさ

		static constexpr int16_t DEF_CHECK_ROUND_RADIUS   = 2;	///< 標準、チェックボックス、コーナー半径
		static constexpr int16_t DEF_CHECK_FRAME_WIDTH    = 3;	///< 標準、チェックボックス、外周フレーム幅
		static constexpr int16_t DEF_CHECK_BOX_SIZE       = 22;	///< 標準、チェックボックス、大きさ
		static constexpr int16_t DEF_CHECK_SPACE          = 4;	///< 標準、チェックボックス、有効アイテムの隙間
		static constexpr int16_t DEF_CHECK_TO_STR         = 5;	///< 標準、チェックボックス、文字までの隙間

		static constexpr int16_t DEF_RADIO_FRAME_WIDTH    = 3;	///< 標準、ラジオボタン、外周フレーム幅
		static constexpr int16_t DEF_RADIO_BOX            = 22;	///< 標準、ラジオボタン、大きさ
		static constexpr int16_t DEF_RADIO_SPACE          = 4;	///< 標準、ラジオボタン、有効アイテムの隙間
		static constexpr int16_t DEF_RADIO_TO_STR         = 5;	///< 標準、ラジオボタン、文字までの隙間

		static constexpr int16_t DEF_SPINBOX_ROUND_RADIUS = 6;	///< 標準、スピンボックス、コーナー半径
		static constexpr int16_t DEF_SPINBOX_FRAME_WIDTH  = 2;	///< 標準、スピンボックス、外周フレーム幅
		static constexpr int16_t DEF_SPINBOX_HEIGHT       = 30;	///< 標準、スピンボックス、サイズが省略された場合の高さ
		static constexpr int16_t DEF_SPINBOX_ARROW_SPACE  = 2;	///< 標準、スピンボックス、矢印までの隙間
		static constexpr int16_t DEF_SPINBOX_ARROW_W      = 5;	///< 標準、スピンボックス、矢印の幅
		static constexpr int16_t DEF_SPINBOX_ARROW_H      = 8;	///< 標準、スピンボックス、矢印の高さ

		static constexpr int16_t DEF_TOGGLE_WIDTH         = 58;	///< 標準、トグルスイッチ、横幅
		static constexpr int16_t DEF_TOGGLE_HEIGHT        = 29;	///< 標準、トグルスイッチ、サイズが省略された場合の高さ
		static constexpr int16_t DEF_TOGGLE_FRAME_WIDTH   = 2;	///< 標準、トグルスイッチ、外周フレーム幅

		static constexpr int16_t DEF_PROGRESS_HEIGHT      = 24;	///< 標準、プログレスバー、サイズが省略された場合の高さ
		static constexpr int16_t DEF_PROGRESS_FRAME_WIDTH = 2;	///< 標準、プログレスバー、フレーム幅

		static constexpr int16_t DEF_FILER_HEIGHT         = 20;	///< 標準、ファイラー、アイテムの高さ
		static constexpr int16_t DEF_FILER_DRAG_TH        = 10; ///< 標準、ファイラー、ドラッグ開始のスレッショルド幅
		static constexpr uint16_t DEF_FILER_LOOP		  = 2;	///< 標準、１フレームに取得するファイル情報数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	レイヤー型（最大８つ）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class LAYER : uint8_t {
			_0,		///< レイヤー０
			_1,		///< レイヤー１
			_2,		///< レイヤー２
			_3,		///< レイヤー３
			_4,		///< レイヤー４
			_5,		///< レイヤー５
			_6,		///< レイヤー６
			_7		///< レイヤー７
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	widget ID
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ID : uint8_t {
			GROUP,		///< グループ
			FRAME,		///< フレーム
			BOX,		///< ボックス（シンプルな単型）
			TEXT,		///< テキスト
			TEXTBOX,	///< テキスト・ボックス
			DIALOG,		///< ダイアログ
			BUTTON,		///< ボタン
			CHECK,		///< チェック・ボタン
			RADIO,		///< ラジオ・ボタン
			SLIDER,		///< スライダー
			MENU,		///< メニュー
			TERM,		///< ターミナル
			SPINBOX,	///< スピンボックス
			TOGGLE,		///< トグルスイッチ
			PROGRESS,	///< プログレスバー
			CLOSEBOX,	///< クローズボックス
			FILER,		///< ファイラー
			KEY_ASC,	///< ASCII ソフトキーボード
			KEY_10,		///< １０ソフトキーボード
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ステート
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class STATE : uint8_t {
			DISABLE,	///< 無効状態（表示されない）
			ENABLE,		///< 有効
			STALL,		///< 表示されているが、ストール状態
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タッチ・ステート
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct touch_state {
			vtx::spos	position_;	///< タッチしている絶対位置
			vtx::spos	relative_;	///< タッチしている相対位置
			vtx::spos	expand_;	///< フォーカス拡張領域
			bool		positive_;	///< タッチした瞬間「true」になる
			bool		level_;		///< タッチしている間「true」になる
			bool		negative_;	///< 離した瞬間「true」になる
			touch_state(const vtx::spos& fexp = vtx::spos(4)) noexcept :
				position_(-1), expand_(fexp),
				positive_(false), level_(false), negative_(false) { }
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	水平配置型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class H_ALIGNMENT : uint8_t {
			LEFT,	///< 左寄せ
			CENTER,	///< 中央
			RIGHT,	///< 右寄せ
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	垂直配置型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class V_ALIGNMENT : uint8_t {
			TOP,	///< 上寄せ
			CENTER,	///< 中央
			BOTTOM,	///< 下寄せ
		};

		static constexpr int16_t SIZE_AUTO = 0;		///< 自動で最適なサイズをロードする。

	private:

		widget*		parents_;	///< 親
		widget*		next_;		///< リンク

		vtx::srect	location_;	///< 位置とサイズ

		const char*	title_;		///< タイトル
		const void*	mobj_;		///< モーションオブジェクト（ビットマップ表示）

		graphics::share_color	base_color_;	///< GUI 基本色
		graphics::share_color	font_color_;	///< フォント基本色

		STATE		state_;
		bool		focus_;
		bool		touch_;

		touch_state	touch_state_;

		bool		update_;

		uint8_t		exec_request_;

		uint8_t		layer_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	loc		ロケーション
			@param[in]	title	タイトル
			@param[in]	fexp	フォーカス拡張領域
		*/
		//-----------------------------------------------------------------//
		widget(const vtx::srect& loc = vtx::srect(0), const char* title = nullptr, const vtx::spos& fexp = vtx::spos(0)) noexcept :
			parents_(nullptr), next_(nullptr),
			location_(loc), title_(title), mobj_(nullptr),
			base_color_(graphics::def_color::White), font_color_(graphics::def_color::White),
			state_(STATE::DISABLE), focus_(false), touch_(false),
			touch_state_(fexp), update_(false),
			exec_request_(0), layer_(0)
		{ } 


		//-----------------------------------------------------------------//
		/*!
			@brief	widget 名称の取得
			@return widget 名称
		*/
		//-----------------------------------------------------------------//
		virtual const char* get_name() const = 0;


		//-----------------------------------------------------------------//
		/*!
			@brief	ID を取得
			@return ID
		*/
		//-----------------------------------------------------------------//
		virtual ID get_id() const = 0; 


		//-----------------------------------------------------------------//
		/*!
			@brief	ハイブリッド・タイプか検査
			@return ハイブリッドの場合「true」
		*/
		//-----------------------------------------------------------------//
		virtual bool hybrid() const noexcept { return false; } 


		//-----------------------------------------------------------------//
		/*!
			@brief	初期化 @n
					GUI が有効になった場合に実行される
		*/
		//-----------------------------------------------------------------//
		virtual void init() = 0;


		//-----------------------------------------------------------------//
		/*!
			@brief	タッチ判定を更新（通常毎フレーム呼ばれる）
			@param[in]	pos		判定位置
			@param[in]	num		タッチ数
		*/
		//-----------------------------------------------------------------//
		virtual void update_touch(const vtx::spos& pos, uint16_t num) = 0;


		//-----------------------------------------------------------------//
		/*!
			@brief	選択推移 @n
					状態の変化が起きた場合に呼び出される。
		*/
		//-----------------------------------------------------------------//
		virtual void exec_select() = 0;


		//-----------------------------------------------------------------//
		/*!
			@brief	許可・不許可
			@param[in]	ena		不許可の場合「false」
		*/
		//-----------------------------------------------------------------//
		virtual void enable(bool ena = true) = 0;


		//-----------------------------------------------------------------//
		/*!
			@brief	プロパティのセーブ
			@param[in]	fio		ファイル I/O コンテキスト
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		virtual bool save(utils::file_io& fio) { return false; }


		//-----------------------------------------------------------------//
		/*!
			@brief	プロパティのロード
			@param[in]	fio		ファイル I/O コンテキスト
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		virtual bool load(utils::file_io& fio) { return false; }


		//-----------------------------------------------------------------//
		/*!
			@brief	親を設定
			@param[in]	w	親 widget
		*/
		//-----------------------------------------------------------------//
		void set_parents(widget* w) noexcept { parents_ = w; }


		//-----------------------------------------------------------------//
		/*!
			@brief	親 widget を返す
			@return	親 widget
		*/
		//-----------------------------------------------------------------//
		widget* get_parents() const noexcept { return parents_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	次接続設定
			@param[in]	w	親 widget
		*/
		//-----------------------------------------------------------------//
		void set_next(widget* w) noexcept { next_ = w; }


		//-----------------------------------------------------------------//
		/*!
			@brief	次接続 widget を返す
			@return	次接続 widget
		*/
		//-----------------------------------------------------------------//
		widget* get_next() const noexcept { return next_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ロケーションの取得
			@return ロケーション
		*/
		//-----------------------------------------------------------------//
		const vtx::srect& get_location() const noexcept { return location_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ロケーションの参照
			@return ロケーション
		*/
		//-----------------------------------------------------------------//
		vtx::srect& at_location() noexcept { return location_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	タイトルの設定
			@param[in]	title	タイトル
		*/
		//-----------------------------------------------------------------//
		void set_title(const char* title) noexcept { title_ = title; }


		//-----------------------------------------------------------------//
		/*!
			@brief	タイトルの取得
			@return タイトル
		*/
		//-----------------------------------------------------------------//
		const char* get_title() const noexcept { return title_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	タイトル更新前処理
		*/
		//-----------------------------------------------------------------//
		virtual void update_title() noexcept { }


		//-----------------------------------------------------------------//
		/*!
			@brief	モーションオブジェクトの設定
			@param[in]	mobj	モーションオブジェクト
		*/
		//-----------------------------------------------------------------//
		void set_mobj(const void* mobj) noexcept {
			mobj_ = mobj;
			set_update();			
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	モーションオブジェクトの取得
			@return モーションオブジェクト
		*/
		//-----------------------------------------------------------------//
		const void* get_mobj() const noexcept { return mobj_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ベースカラーの設定
			@param[in]	color	カラー
		*/
		//-----------------------------------------------------------------//
		void set_base_color(const graphics::share_color& color) noexcept {
			base_color_ = color;
			set_update();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ベースカラーの取得
			@return ベースカラー
		*/
		//-----------------------------------------------------------------//
		auto get_base_color() const noexcept {
			if(state_ == STATE::STALL) {
				graphics::share_color sh(0, 0, 0);
				sh.set_color(base_color_.rgba8, 96);
				return sh;
			} else {
				return base_color_;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	フォントカラーの設定
			@param[in]	color	カラー
		*/
		//-----------------------------------------------------------------//
		void set_font_color(const graphics::share_color& color) noexcept {
			font_color_ = color;
			set_update();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	フォントカラーの取得
			@return フォントカラー
		*/
		//-----------------------------------------------------------------//
		auto get_font_color() const noexcept
		{
			if(state_ == STATE::STALL) {
				graphics::share_color sh(0, 0, 0);
				sh.set_color(font_color_.rgba8, 96);
				return sh;
			} else {
				return font_color_;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	「更新」の設定
			@param[in]	update	更新をしない場合「false」
		*/
		//-----------------------------------------------------------------//
		void set_update(bool update = true) noexcept { update_ = update; }


		//-----------------------------------------------------------------//
		/*!
			@brief	「更新」の取得
			@return	「更新」
		*/
		//-----------------------------------------------------------------//
		auto get_update() const noexcept { return update_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	レイヤーの設定
			@param[in]	layer	レイヤー
		*/
		//-----------------------------------------------------------------//
		void set_layer(LAYER layer) noexcept { layer_ = 1 << static_cast<uint8_t>(layer); }


		//-----------------------------------------------------------------//
		/*!
			@brief	レイヤービットの取得
			@return レイヤー
		*/
		//-----------------------------------------------------------------//
		auto get_layer_bits() const noexcept { return layer_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ステートの設定
			@param[in]	state	ステート
		*/
		//-----------------------------------------------------------------//
		void set_state(STATE state) noexcept { state_ = state; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ステートの取得
			@return	ステート
		*/
		//-----------------------------------------------------------------//
		auto get_state() const noexcept { return state_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	フォーカスを取得
			@return フォーカス
		*/
		//-----------------------------------------------------------------//
		bool get_focus() const noexcept { return focus_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	タッチ・ステートを取得
			@return タッチ・ステート
		*/
		//-----------------------------------------------------------------//
		const auto& get_touch_state() const noexcept { return touch_state_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	タッチステートをリセット
		*/
		//-----------------------------------------------------------------//
		void reset_touch_state() noexcept
		{
			touch_state_.positive_ = false;
			touch_state_.negative_ = false;
			touch_state_.level_    = false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	標準的なタッチ判定更新
			@param[in]	pos		判定位置
			@param[in]	num		タッチ数
			@param[in]	exp		タッチ領域拡張を行わない場合「false」
		*/
		//-----------------------------------------------------------------//
		void update_touch_def(const vtx::spos& pos, uint16_t num, bool exp = true) noexcept
		{
			auto loc = vtx::srect(get_final_position(), location_.size);
			if(exp) {
				loc.org  -= touch_state_.expand_;
				loc.size += touch_state_.expand_;
			}
			focus_ = loc.is_focus(pos);
			if(focus_) {
				if(num > 0) {
					touch_ = true;
					touch_state_.position_ = pos;
					touch_state_.relative_ = pos - loc.org;
				} else {
					touch_ = false;
					touch_state_.position_.set(-1);
				}
				auto level = touch_;
				touch_state_.positive_ = ( level && !touch_state_.level_);
				touch_state_.negative_ = (!level &&  touch_state_.level_);
				touch_state_.level_    =   level;
			} else {
				touch_state_.positive_ = false;
				touch_state_.negative_ = false;
				touch_state_.level_    = false;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	タッチ判定を更新（スライダー用）@n
					・スライダーの操作性を良くする為の工夫をする。@n
					・タッチしたまま、左右、上下にドラッグして、スライダー @n
					のフォーカスを外れた場合、操作が中断してしまうのを改善する。
			@param[in]	pos		判定位置
			@param[in]	num		タッチ数
		*/
		//-----------------------------------------------------------------//
		void update_touch_slider(const vtx::spos& pos, uint16_t num) noexcept
		{
			if(num == 0) {
				focus_ = false;
				touch_ = false;
				touch_state_.position_.set(-1);
				touch_state_.positive_ = false;
				touch_state_.negative_ = touch_state_.level_;
				touch_state_.level_    = false;
				return;
			}

			auto loc = vtx::srect(get_final_position(), location_.size);
			loc.org  -= touch_state_.expand_;
			loc.size += touch_state_.expand_;
			bool focus = loc.is_focus(pos);
			if(!focus_ && focus) {
				touch_ = true;
			}
			focus_ = focus;
			touch_state_.position_ = pos;

			auto level = touch_;
			touch_state_.positive_ = ( level && !touch_state_.level_);
			touch_state_.negative_ = (!level &&  touch_state_.level_);
			touch_state_.level_    =   level;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	最終位置を取得
			@return 最終位置
		*/
		//-----------------------------------------------------------------//
		vtx::spos get_final_position() const noexcept
		{
			auto pos = location_.org;
			widget* w = parents_;
			while(w != nullptr) {
				pos += w->get_location().org;
				w = w->get_parents();
			}
			return pos;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	動作リクエストを取得
			@return 動作リクエスト
		*/
		//-----------------------------------------------------------------//
		auto get_exec_request() const noexcept { return exec_request_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	動作リクエストを発行
		*/
		//-----------------------------------------------------------------//
		void set_exec_request() noexcept { ++exec_request_; }
	};
}

extern bool insert_widget(gui::widget* w);	///< widget インサートのグローバル関数型
extern void remove_widget(gui::widget* w);	///< widget リムーブのグローバル関数型
