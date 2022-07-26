#pragma once
//=====================================================================//
/*!	@file
	@brief	ASCII ソフトキーボード
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "gui/widget.hpp"

namespace gui {

	namespace key_asc_base {

		struct location_t {
			vtx::srect	rect;
			char		code;  // normal-code
			char		shift; // shift-code
			constexpr location_t(const vtx::srect& r, char c, char s) :
				rect(r),
				code(c), shift(s)
			{ }
		};

	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ASCII ソフトキー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct key_asc : public widget {

		typedef key_asc value_type;

		//=============================================================//
		/*!
			@brief	キーマップ型
		*/
		//=============================================================//
		enum class KEY_MAP : uint8_t {
			ORG,	///< ` ~
			_1,		///< 1 !
			_2,		///< 2 @
			_3,		///< 3 #
			_4,		///< 4 $
			_5,		///< 5 %
			_6,		///< 6 ^
			_7,		///< 7 &
			_8,		///< 8 *
			_9,		///< 9 (
			_0,		///< 0 )
			MI_US,	///< - _
			EQ_PS,	///< = +
			BS,		///< BackSpace
			TAB,	///< TAB
			Q,		///< Q q
			W,		///< W w
			E,		///< E e
			R,		///< R r
			T,		///< T t
			Y,		///< Y y
			U,		///< U u
			I,		///< I i
			O,		///< O o
			P,		///< P p
			LEFT,	///< [ {
			RIGHT,	///< ] }
			BASL,	///< BackSlash |
			CA_LK,	///< CapsLock
			A,		///< A a
			S,		///< S s
			D,		///< D d
			F,		///< F f
			G,		///< G g
			H,		///< H h
			J,		///< J j
			K,		///< K k
			L,		///< L l
			COLN,	///< ; :
			AP_DQ,	///< ' "
			ENTER,	///< Enter
			SHIFT_L,	///< ShiftLeft
			Z,		///< Z Z
			X,		///< X x
			C,		///< C c
			V,		///< V v
			B,		///< B b
			N,		///< N n
			M,		///< M m
			KA_LI,	///< , <
			CO_LR,	///< . >
			SL_QS,	///< / ?
			SHIFT_R,	///< ShiftRight
			CTRL,	///< Ctrl
			ALT,	///< Alt
			SPACE,	///< Space
			FN,		///< Function
			A_LEFT,		///< Arrow Left
			A_DOWN,		///< Arrow Down
			A_RIGHT,	///< Arrow Right
			A_UP		///< Arrow Up
		};

		typedef std::function<void(char, KEY_MAP)> SELECT_FUNC_TYPE;

	private:
		static constexpr int16_t space = 2;

		static constexpr int16_t sz_x = 30;  // 通常幅
		static constexpr int16_t sz1x = 43;  // TAB 幅
		static constexpr int16_t sz2x = 56;  // バックスペース幅
		static constexpr int16_t sz3x = 52;  // CAPS LOCK 幅
		static constexpr int16_t sz4x = 68;  // LEFT-SHIFT 幅
		static constexpr int16_t sz5x = 82;  // RIGHT-SHIFT 幅
		static constexpr int16_t sz6x = 43;  // back slash 幅
		static constexpr int16_t sz7x = 66;  // ENTER 幅
		static constexpr int16_t sz8x = 56;  // CTRL, ALT, FN 幅
		static constexpr int16_t sz9x = 150; // SPACE 幅 
		static constexpr int16_t szax = 35;  // ARROW 幅

		static constexpr int16_t g0_x = 0;
		static constexpr int16_t g1_x = g0_x + sz1x + space;
		static constexpr int16_t g2_x = g0_x + sz3x + space;
		static constexpr int16_t g3_x = g0_x + sz4x + space;
		static constexpr int16_t g4_x = g0_x + sz8x * 2 + sz9x + space * 3;
		static constexpr int16_t g5_x = g4_x + sz8x + space;

		static constexpr int16_t sp_x = sz_x + space;
		static constexpr int16_t sp3x = sz8x + space;
		static constexpr int16_t sp5x = szax + space;

		static constexpr int16_t g0_y = 0;
		static constexpr int16_t sz_y = 30;
		static constexpr int16_t sp_y = sz_y + space;

		static constexpr char KEY_BACK_SPACE  = 0x08;
		static constexpr char KEY_TAB         = 0x09;
		static constexpr char KEY_ENTER       = 0x0D;

		static constexpr char KEY_CAPS_LOCK   = 0x80;
		static constexpr char KEY_SHIFT_LEFT  = 0x81;
		static constexpr char KEY_SHIFT_RIGHT = 0x82;
		static constexpr char KEY_CTRL        = 0x83;
		static constexpr char KEY_ALT         = 0x84;
		static constexpr char KEY_FN          = 0x85;
		static constexpr char KEY_ARROW_LEFT  = 0x86;
		static constexpr char KEY_ARROW_DOWN  = 0x87;
		static constexpr char KEY_ARROW_RIGHT = 0x88;
		static constexpr char KEY_ARROW_UP    = 0x89;

		static constexpr key_asc_base::location_t key_locations_[] = {
			{ { g0_x + sp_x *  0, g0_y + sp_y * 0, sz_x, sz_y }, '`', '~' },
			{ { g0_x + sp_x *  1, g0_y + sp_y * 0, sz_x, sz_y }, '1', '!' },
			{ { g0_x + sp_x *  2, g0_y + sp_y * 0, sz_x, sz_y }, '2', '@' },
			{ { g0_x + sp_x *  3, g0_y + sp_y * 0, sz_x, sz_y }, '3', '#' },
			{ { g0_x + sp_x *  4, g0_y + sp_y * 0, sz_x, sz_y }, '4', '$' },
			{ { g0_x + sp_x *  5, g0_y + sp_y * 0, sz_x, sz_y }, '5', '%' },
			{ { g0_x + sp_x *  6, g0_y + sp_y * 0, sz_x, sz_y }, '6', '^' },
			{ { g0_x + sp_x *  7, g0_y + sp_y * 0, sz_x, sz_y }, '7', '&' },
			{ { g0_x + sp_x *  8, g0_y + sp_y * 0, sz_x, sz_y }, '8', '*' },
			{ { g0_x + sp_x *  9, g0_y + sp_y * 0, sz_x, sz_y }, '9', '(' },
			{ { g0_x + sp_x * 10, g0_y + sp_y * 0, sz_x, sz_y }, '0', ')' },
			{ { g0_x + sp_x * 11, g0_y + sp_y * 0, sz_x, sz_y }, '-', '_' },
			{ { g0_x + sp_x * 12, g0_y + sp_y * 0, sz_x, sz_y }, '=', '+' },
			{ { g0_x + sp_x * 13, g0_y + sp_y * 0, sz2x, sz_y }, KEY_BACK_SPACE, KEY_BACK_SPACE },

			{ { g0_x,             g0_y + sp_y * 1, sz1x, sz_y }, KEY_TAB, KEY_TAB },
			{ { g1_x + sp_x *  0, g0_y + sp_y * 1, sz_x, sz_y }, 'Q', 'q' },
			{ { g1_x + sp_x *  1, g0_y + sp_y * 1, sz_x, sz_y }, 'W', 'w' },
			{ { g1_x + sp_x *  2, g0_y + sp_y * 1, sz_x, sz_y }, 'E', 'e' },
			{ { g1_x + sp_x *  3, g0_y + sp_y * 1, sz_x, sz_y }, 'R', 'r' },
			{ { g1_x + sp_x *  4, g0_y + sp_y * 1, sz_x, sz_y }, 'T', 't' },
			{ { g1_x + sp_x *  5, g0_y + sp_y * 1, sz_x, sz_y }, 'Y', 'y' },
			{ { g1_x + sp_x *  6, g0_y + sp_y * 1, sz_x, sz_y }, 'U', 'u' },
			{ { g1_x + sp_x *  7, g0_y + sp_y * 1, sz_x, sz_y }, 'I', 'i' },
			{ { g1_x + sp_x *  8, g0_y + sp_y * 1, sz_x, sz_y }, 'O', 'o' },
			{ { g1_x + sp_x *  9, g0_y + sp_y * 1, sz_x, sz_y }, 'P', 'p' },
			{ { g1_x + sp_x * 10, g0_y + sp_y * 1, sz_x, sz_y }, '[', '{' },
			{ { g1_x + sp_x * 11, g0_y + sp_y * 1, sz_x, sz_y }, ']', '}' },
			{ { g1_x + sp_x * 12, g0_y + sp_y * 1, sz6x, sz_y }, '\\', '|' },

			{ { g0_x,             g0_y + sp_y * 2, sz3x, sz_y }, KEY_CAPS_LOCK, KEY_CAPS_LOCK },
			{ { g2_x + sp_x *  0, g0_y + sp_y * 2, sz_x, sz_y }, 'A', 'a' },
			{ { g2_x + sp_x *  1, g0_y + sp_y * 2, sz_x, sz_y }, 'S', 's' },
			{ { g2_x + sp_x *  2, g0_y + sp_y * 2, sz_x, sz_y }, 'D', 'd' },
			{ { g2_x + sp_x *  3, g0_y + sp_y * 2, sz_x, sz_y }, 'F', 'f' },
			{ { g2_x + sp_x *  4, g0_y + sp_y * 2, sz_x, sz_y }, 'G', 'g' },
			{ { g2_x + sp_x *  5, g0_y + sp_y * 2, sz_x, sz_y }, 'H', 'h' },
			{ { g2_x + sp_x *  6, g0_y + sp_y * 2, sz_x, sz_y }, 'J', 'j' },
			{ { g2_x + sp_x *  7, g0_y + sp_y * 2, sz_x, sz_y }, 'K', 'k' },
			{ { g2_x + sp_x *  8, g0_y + sp_y * 2, sz_x, sz_y }, 'L', 'l' },
			{ { g2_x + sp_x *  9, g0_y + sp_y * 2, sz_x, sz_y }, ';', ':' },
			{ { g2_x + sp_x * 10, g0_y + sp_y * 2, sz_x, sz_y }, '\'', '"' },
			{ { g2_x + sp_x * 11, g0_y + sp_y * 2, sz7x, sz_y }, KEY_ENTER, KEY_ENTER },

			{ { g0_x,             g0_y + sp_y * 3, sz4x, sz_y }, KEY_SHIFT_LEFT, KEY_SHIFT_LEFT },
			{ { g3_x + sp_x *  0, g0_y + sp_y * 3, sz_x, sz_y }, 'Z', 'z' },
			{ { g3_x + sp_x *  1, g0_y + sp_y * 3, sz_x, sz_y }, 'X', 'x' },
			{ { g3_x + sp_x *  2, g0_y + sp_y * 3, sz_x, sz_y }, 'C', 'c' },
			{ { g3_x + sp_x *  3, g0_y + sp_y * 3, sz_x, sz_y }, 'V', 'v' },
			{ { g3_x + sp_x *  4, g0_y + sp_y * 3, sz_x, sz_y }, 'B', 'b' },
			{ { g3_x + sp_x *  5, g0_y + sp_y * 3, sz_x, sz_y }, 'N', 'n' },
			{ { g3_x + sp_x *  6, g0_y + sp_y * 3, sz_x, sz_y }, 'M', 'm' },
			{ { g3_x + sp_x *  7, g0_y + sp_y * 3, sz_x, sz_y }, ',', '<' },
			{ { g3_x + sp_x *  8, g0_y + sp_y * 3, sz_x, sz_y }, '.', '>' },
			{ { g3_x + sp_x *  9, g0_y + sp_y * 3, sz_x, sz_y }, '/', '?' },
			{ { g3_x + sp_x * 10, g0_y + sp_y * 3, sz5x, sz_y }, KEY_SHIFT_RIGHT, KEY_SHIFT_RIGHT },
	
			{ { g0_x + sp3x *  0, g0_y + sp_y * 4, sz8x, sz_y }, KEY_CTRL, KEY_CTRL },
			{ { g0_x + sp3x *  1, g0_y + sp_y * 4, sz8x, sz_y }, KEY_ALT,  KEY_ALT },
			{ { g0_x + sp3x *  2, g0_y + sp_y * 4, sz9x, sz_y }, ' ', ' ' },
			{ { g4_x            , g0_y + sp_y * 4, sz8x, sz_y }, KEY_FN, KEY_FN },
			{ { g5_x + sp5x *  0, g0_y + sp_y * 4, szax, sz_y }, KEY_ARROW_LEFT,  KEY_ARROW_LEFT  },
			{ { g5_x + sp5x *  1, g0_y + sp_y * 4, szax, sz_y }, KEY_ARROW_DOWN,  KEY_ARROW_DOWN  },
			{ { g5_x + sp5x *  2, g0_y + sp_y * 4, szax, sz_y }, KEY_ARROW_RIGHT, KEY_ARROW_RIGHT },
			{ { g5_x + sp5x *  3, g0_y + sp_y * 4, szax, sz_y }, KEY_ARROW_UP,    KEY_ARROW_UP    }
		};

		struct key_t {
			bool	level;
			bool	positive;
			bool	negative;
			bool	draw;
			key_t() noexcept : level(false), positive(false), negative(true), draw(true) { }
		};
		key_t	key_[14 + 14 + 13 + 12 + 8];

		SELECT_FUNC_TYPE	select_func_;
		char	code_;
		uint8_t	key_map_;
		bool	shift_;
		bool	ctrl_;
		bool	alt_;
		bool	lock_;
		bool	fn_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	loc		ロケーション
		*/
		//-----------------------------------------------------------------//
		key_asc(const vtx::srect& loc = vtx::srect(0), const char* str = nullptr) noexcept :
			widget(loc, str), key_{ },
			select_func_(), code_(0xff), key_map_(0),
			shift_(false), ctrl_(false), alt_(false), lock_(false), fn_(false)
		{
			at_location().size.x = 13 * sp_x + sz2x + space;
			at_location().size.y = sp_y * 5;
			insert_widget(this);
		}


		key_asc(const key_asc& th) = delete;
		key_asc& operator = (const key_asc& th) = delete;


		//-----------------------------------------------------------------//
		/*!
			@brief	デストラクタ
		*/
		//-----------------------------------------------------------------//
		virtual ~key_asc() noexcept { remove_widget(this); }


		//-----------------------------------------------------------------//
		/*!
			@brief	型整数を取得
			@return 型整数
		*/
		//-----------------------------------------------------------------//
		const char* get_name() const noexcept override { return "KeyAsc"; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ID を取得
			@return ID
		*/
		//-----------------------------------------------------------------//
		ID get_id() const noexcept override { return ID::KEY_ASC; }


		//-----------------------------------------------------------------//
		/*!
			@brief	初期化
		*/
		//-----------------------------------------------------------------//
		void init() noexcept override { }


		//-----------------------------------------------------------------//
		/*!
			@brief	タッチ判定を更新
			@param[in]	pos		判定位置
			@param[in]	num		タッチ数
		*/
		//-----------------------------------------------------------------//
		void update_touch(const vtx::spos& pos, uint16_t num) noexcept override
		{
			update_touch_def(pos, num);

			auto loc = vtx::srect(get_final_position(), widget::get_location().size);
			uint32_t i = 0;
			bool all = false;
			for(auto& k : key_) {
				vtx::srect r(loc.org + key_locations_[i].rect.org, key_locations_[i].rect.size);
				auto level = false;
				if(r.is_focus(pos)) {
					level = num > 0;
				}
				k.positive = ( level && !k.level);
				k.negative = (!level &&  k.level);
				k.level = level;
				if(k.positive) {
					key_map_ = i;
					auto code = key_locations_[i].code;
					if(code == KEY_SHIFT_RIGHT || code == KEY_SHIFT_LEFT) {
						shift_ = !shift_;
						all = true;
					} else if(code == KEY_CAPS_LOCK) {
						lock_ = !lock_;
						all = true;
					} else if(code == KEY_CTRL) {
						ctrl_ = !ctrl_;
					} else if(code == KEY_ALT) {
						alt_ = !alt_;
					} else if(code == KEY_FN) {
						fn_ = !fn_;
					} else {
						if(ctrl_) {
							if(code >= 'A') {
								code_ = code - 0x40;
							} else {
								code_ = code;
							}
						} else if(shift_) {
							code_ = key_locations_[i].shift;
						} else {
							code_ = key_locations_[i].code;
						}
					}
					k.draw = true;
				}
				if(k.negative) {
					k.draw = true;
				}
				++i;
			}
			if(all) {
				uint32_t i = 0;
				for(auto& k : key_) {
					auto code = key_locations_[i].code;
					if(code > 0x20 && code < 0x80) {
						k.draw = true;
					}
					++i;
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	選択推移
		*/
		//-----------------------------------------------------------------//
		void exec_select() noexcept override
		{
			if(code_ != 0xff) {
				if(select_func_) {
					select_func_(code_, static_cast<KEY_MAP>(key_map_));
				}
				code_ = 0xff;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	許可・不許可
			@param[in]	ena		不許可の場合「false」
		*/
		//-----------------------------------------------------------------//
		void enable(bool ena = true) override
		{
			if(ena) {
				set_state(STATE::ENABLE);
			} else {
				set_state(STATE::DISABLE);
				reset_touch_state();
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	セレクト関数への参照
			@return	セレクト関数
		*/
		//-----------------------------------------------------------------//
		SELECT_FUNC_TYPE& at_select_func() noexcept { return select_func_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	描画
		*/
		//-----------------------------------------------------------------//
		template<class RDR>
		void draw(RDR& rdr) noexcept
		{
			auto r = vtx::srect(get_final_position(), get_location().size);

			uint32_t i = 0;
			for(auto& k : key_) {
				uint8_t inten = 64;
				if(k.level) {
					inten = 192;
				}
				if(k.draw) {
					k.draw = false;
					graphics::share_color sc;
					sc.set_color(get_base_color().rgba8, inten);
					rdr.set_fore_color(sc);
					auto rr = key_locations_[i].rect;
					rr.org += r.org;
					if(k.level) {
						rr.org += 1;
						rr.size -= 2;
					}
					rdr.round_box(rr, 3);

					rdr.set_fore_color(get_font_color());
					char cha;
					if(shift_) {
						cha = key_locations_[i].shift;
					} else {
						cha = key_locations_[i].code;
					}
					switch(cha) {
					case KEY_BACK_SPACE: {
						vtx::spos sz(8 * 2, 16);
						rdr.draw_text(rr.org + (rr.size - sz) / 2, "BS");
						}
						break;
					case KEY_TAB: {
						vtx::spos sz(8 * 3, 16);
						rdr.draw_text(rr.org + (rr.size - sz) / 2, "TAB");
						}
						break;
					case KEY_CAPS_LOCK: {
						vtx::spos sz(8 * 3, 16);
						rdr.draw_text(rr.org + (rr.size - sz) / 2, "[A]");
						}
						break;
					case KEY_ENTER: {
						vtx::spos sz(8 * 5, 16);
						rdr.draw_text(rr.org + (rr.size - sz) / 2, "Enter");
						}
						break;
					case KEY_SHIFT_LEFT:
					case KEY_SHIFT_RIGHT: {
						vtx::spos sz(8 * 5, 16);
						rdr.draw_text(rr.org + (rr.size - sz) / 2, "Shift");
						}
						break;
					case KEY_CTRL: {
						vtx::spos sz(8 * 4, 16);
						rdr.draw_text(rr.org + (rr.size - sz) / 2, "CTRL");
						}
						break;
					case KEY_ALT: {
						vtx::spos sz(8 * 3, 16);
						rdr.draw_text(rr.org + (rr.size - sz) / 2, "ALT");
						}
						break;
					case KEY_FN: {
						vtx::spos sz(8 * 2, 16);
						rdr.draw_text(rr.org + (rr.size - sz) / 2, "Fn");
						}
						break;
					case KEY_ARROW_LEFT: {
						vtx::spos sz(8 * 2, 16);
						rdr.draw_text(rr.org + (rr.size - sz) / 2, "Lt");
						}
						break;
					case KEY_ARROW_DOWN: {
						vtx::spos sz(8 * 2, 16);
						rdr.draw_text(rr.org + (rr.size - sz) / 2, "Dn");
						}
						break;
					case KEY_ARROW_RIGHT: {
						vtx::spos sz(8 * 2, 16);
						rdr.draw_text(rr.org + (rr.size - sz) / 2, "Ri");
						}
						break;
					case KEY_ARROW_UP: {
						vtx::spos sz(8 * 2, 16);
						rdr.draw_text(rr.org + (rr.size - sz) / 2, "Up");
						}
						break;
					default: {
						vtx::spos sz(8, 16);					
						rdr.draw_font(rr.org + (rr.size - sz) / 2, cha); 
						}
						break;
					}
				}
				++i;
			}
		}
	};
}
