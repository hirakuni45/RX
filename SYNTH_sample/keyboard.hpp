#pragma once
//=====================================================================//
/*! @file
    @brief  鍵盤 クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
    @copyright  Copyright (C) 2021 Kunihito Hiramatsu @n
                Released under the MIT license @n
                https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <array>

#include "graphics/graphics.hpp"

namespace synth {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SYNTH 描画クラス
		@param[in]	RENDER	描画クラス
		@param[in]	TOUCH	タッチ・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class RENDER, class TOUCH>
	class keyboard {
    public:
        enum class key : uint8_t {
            C1,
            C1s,
            D1,
            D1s,
            E1,
            F1,
            F1s,
            G1,
            G1s,
            A1,
            A1s,
            B1,
            C2,
            C2s,
            D2,
            D2s,
            E2,
            F2,
            F2s,
            G2,
            G2s,
            A2,
            A2s,
            B2,
        };


        struct key_t {

            vtx::srect  rect_;
            key         key_;
            bool        sharp_;

            bool        draw_;

            bool        back_;
            bool        level_;
            bool        positive_;
            bool        negative_;

            constexpr key_t(const vtx::srect& rect = vtx::srect(0), key k = key::C) noexcept :
                rect_(rect), key_(k),
                draw_(false),
                back_(false), level_(false), positive_(false), negative_(false)
            { }


            bool is_sharp() const noexcept
            {
                auto n = static_cast<uint8_t>(key_);
                auto m = n % 12;
                if(m == 1 || m == 3 || m == 6 || m == 8 || m == 10) {
                    return true;
                } else {
                    return false;
                }
            }
        };

    private:

		RENDER&		render_;
		TOUCH&		touch_;

        typedef graphics::def_color DEF_COLOR;

        static const int16_t    KEY_W_WIDTH  = 40;
        static const int16_t    KEY_W_HEIGHT = 180;
        static const int16_t    KEY_B_WIDTH  = 32;
        static const int16_t    KEY_B_HEIGHT = 110;
        static const int16_t    KEY_POS_X = 0;
        static const int16_t    KEY_POS_Y = 272 - KEY_W_HEIGHT;
        static const int16_t    KEY_SPACE = 3;

        typedef std::array<key_t, 21> KEYS;
        KEYS        keys_;

        bool        enable_;


        void draw_key_(const key_t& t)
        {
            auto r = t.rect_;
            r.size.x -= KEY_SPACE;
            if(t.level_) {
                if(t.is_sharp()) {
                    render_.set_fore_color(DEF_COLOR::Gray);
                } else {
                    render_.set_fore_color(DEF_COLOR::Silver);
                }
            } else {
                if(t.is_sharp()) {
                    render_.set_fore_color(DEF_COLOR::Black);
                } else {
                    render_.set_fore_color(DEF_COLOR::White);
                }
            }
            render_.fill_box(r);
        }

    public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
			@param[in]	render	描画クラス
			@param[in]	touch	タッチ・クラス
		*/
		//-----------------------------------------------------------------//
		keyboard(RENDER& render, TOUCH& touch) noexcept :
			render_(render), touch_(touch),
            keys_{
                key_t(vtx::srect(KEY_POS_X + (KEY_W_WIDTH *  0),      KEY_POS_Y, KEY_W_WIDTH, KEY_W_HEIGHT), key::C1),
                key_t(vtx::srect(KEY_POS_X + (KEY_W_WIDTH *  0) + 20, KEY_POS_Y, KEY_B_WIDTH, KEY_B_HEIGHT), key::C1s),
                key_t(vtx::srect(KEY_POS_X + (KEY_W_WIDTH *  1),      KEY_POS_Y, KEY_W_WIDTH, KEY_W_HEIGHT), key::D1),
                key_t(vtx::srect(KEY_POS_X + (KEY_W_WIDTH *  1) + 20, KEY_POS_Y, KEY_B_WIDTH, KEY_B_HEIGHT), key::D1s),
                key_t(vtx::srect(KEY_POS_X + (KEY_W_WIDTH *  2),      KEY_POS_Y, KEY_W_WIDTH, KEY_W_HEIGHT), key::E1),
                key_t(vtx::srect(KEY_POS_X + (KEY_W_WIDTH *  3),      KEY_POS_Y, KEY_W_WIDTH, KEY_W_HEIGHT), key::F1),
                key_t(vtx::srect(KEY_POS_X + (KEY_W_WIDTH *  3) + 20, KEY_POS_Y, KEY_B_WIDTH, KEY_B_HEIGHT), key::F1s),
                key_t(vtx::srect(KEY_POS_X + (KEY_W_WIDTH *  4),      KEY_POS_Y, KEY_W_WIDTH, KEY_W_HEIGHT), key::G1),
                key_t(vtx::srect(KEY_POS_X + (KEY_W_WIDTH *  4) + 20, KEY_POS_Y, KEY_B_WIDTH, KEY_B_HEIGHT), key::G1s),
                key_t(vtx::srect(KEY_POS_X + (KEY_W_WIDTH *  5),      KEY_POS_Y, KEY_W_WIDTH, KEY_W_HEIGHT), key::A1),
                key_t(vtx::srect(KEY_POS_X + (KEY_W_WIDTH *  5) + 20, KEY_POS_Y, KEY_B_WIDTH, KEY_B_HEIGHT), key::A1s),
                key_t(vtx::srect(KEY_POS_X + (KEY_W_WIDTH *  6),      KEY_POS_Y, KEY_W_WIDTH, KEY_W_HEIGHT), key::B1),
                key_t(vtx::srect(KEY_POS_X + (KEY_W_WIDTH *  7),      KEY_POS_Y, KEY_W_WIDTH, KEY_W_HEIGHT), key::C2),
                key_t(vtx::srect(KEY_POS_X + (KEY_W_WIDTH *  7) + 20, KEY_POS_Y, KEY_B_WIDTH, KEY_B_HEIGHT), key::C2s),
                key_t(vtx::srect(KEY_POS_X + (KEY_W_WIDTH *  8),      KEY_POS_Y, KEY_W_WIDTH, KEY_W_HEIGHT), key::D2),
                key_t(vtx::srect(KEY_POS_X + (KEY_W_WIDTH *  8) + 20, KEY_POS_Y, KEY_B_WIDTH, KEY_B_HEIGHT), key::D2s),
                key_t(vtx::srect(KEY_POS_X + (KEY_W_WIDTH *  9),      KEY_POS_Y, KEY_W_WIDTH, KEY_W_HEIGHT), key::E2),
                key_t(vtx::srect(KEY_POS_X + (KEY_W_WIDTH * 10),      KEY_POS_Y, KEY_W_WIDTH, KEY_W_HEIGHT), key::F2),
                key_t(vtx::srect(KEY_POS_X + (KEY_W_WIDTH * 10) + 20, KEY_POS_Y, KEY_B_WIDTH, KEY_B_HEIGHT), key::F2s),
                key_t(vtx::srect(KEY_POS_X + (KEY_W_WIDTH * 11),      KEY_POS_Y, KEY_W_WIDTH, KEY_W_HEIGHT), key::G2),
                key_t(vtx::srect(KEY_POS_X + (KEY_W_WIDTH * 11) + 20, KEY_POS_Y, KEY_B_WIDTH, KEY_B_HEIGHT), key::G2s),
            },
            enable_(true)
        { }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
		*/
		//-----------------------------------------------------------------//
		void start() noexcept
        {
            for(auto& t : keys_) {
                t.draw_ = true;
            }
        }


		//-----------------------------------------------------------------//
		/*!
			@brief  表示許可
            @param[in]    ena		不許可の場合「false」
		*/
		//-----------------------------------------------------------------//
		void enable(bool ena = true) noexcept
        {
            if(!enable_ && ena) {
                for(auto& t : keys_) {
                    t.draw_ = true;
                }
            }
            enable_ = ena;
        }


		//-----------------------------------------------------------------//
		/*!
			@brief  更新 @n
					※毎フレーム呼ぶ
		*/
		//-----------------------------------------------------------------//
		void update() noexcept
        {
            if(!enable_) {
                return;
            }

            for(auto& t : keys_) {
                t.back_ = t.level_;
                t.level_ = false;
            }

            auto num = touch_.get_touch_num();
            for(uint32_t i = 0; i < num; ++i) {
                const auto& ts = touch_.get_touch_pos(i);
                bool on = false;
                for(auto& t : keys_) {
                    auto rect = t.rect_;
                    rect.size.x -= KEY_SPACE;
                    if(t.is_sharp()) {
                        if(rect.is_focus(ts.pos)) {
                            t.level_ = true;
                            on = true;
                            break;
                        }
                    }
                }
                if(on) continue;
                for(auto& t : keys_) {
                    auto rect = t.rect_;
                    rect.size.x -= KEY_SPACE;
                    if(!t.is_sharp()) {
                        if(rect.is_focus(ts.pos)) {
                            t.level_ = true;
                        }
                    }
                }
            }

            for(auto& t : keys_) {
                t.positive_ = (!t.back_ &&  t.level_);
                t.negative_ = ( t.back_ && !t.level_);
                if(t.positive_ || t.negative_) {
                    t.draw_ = true;
                }
                if(t.draw_) {
                    draw_key_(t);
                }
            }

            for(auto& t : keys_) {
                if(t.draw_) {
                    auto n = static_cast<uint32_t>(t.key_);
                    switch(n % 12) {
                    case 0:
                        draw_key_(keys_[n + 1]);
                        break;
                    case 2:
                        draw_key_(keys_[n - 1]);
                        draw_key_(keys_[n + 1]);
                        break;
                    case 4:
                        draw_key_(keys_[n - 1]);
                        break;
                    case 5:
                        draw_key_(keys_[n + 1]);
                        break;
                    case 7:
                        draw_key_(keys_[n - 1]);
                        draw_key_(keys_[n + 1]);
                        break;
                    case 9:
                        draw_key_(keys_[n - 1]);
                        draw_key_(keys_[n + 1]);
                        break;
                    case 11:
                        draw_key_(keys_[n - 1]);
                        break;
                    default:
                        break;
                    }
                    t.draw_ = false;
                }
            }
        }


		//-----------------------------------------------------------------//
		/*!
			@brief  キーボードの状態を返す
            @param[in] key  キーコード
            @return キーボードの状態
		*/
		//-----------------------------------------------------------------//
        const auto& get(key k) const noexcept { return keys_[static_cast<uint8_t>(k)]; }
    };
}
