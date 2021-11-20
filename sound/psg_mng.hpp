#pragma once
//=====================================================================//
/*!	@file
	@brief	PSG Emulations Manager @n
			ファミコン内蔵音源と同じような機能を持った波形生成 @n
			波形をレンダリングして波形バッファに生成する。 @n
			生成した波形メモリを PWM 変調などで出力する事を前提にしている。 @n
			分解能は８ビット
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/R8C/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>

extern "C" {
	void sci_putch(char ch);
}

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  PSG ベース・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class psg_base {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  波形タイプ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class WTYPE : uint8_t {
			SQ25,	///< 矩形波 Duty25%
			SQ50,	///< 矩形波 Duty50%
			SQ75,	///< 矩形波 Duty75%
			TRI,	///< 三角波
			NOISE,	///< ノイズ（現在未サポート）
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  １２平均音階率によるキーテーブル @n
					(0)27.5, (1)55, (2)110, (3)220, (4)440, (5)880, (6)1760, (7)3520
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class KEY : uint8_t {
			A_0,		///< A  ラ  27.5Hz (0)
			As0,		///< A#
			Bb0 = As0,	///< Bb
			B_0,		///< B  シ
			C_1,		///< C  ド
			Cs1,		///< C#
			Db1 = Cs1,	///< Db
			D_1,		///< D  レ
			Ds1,		///< D#
			Eb1 = Ds1,	///< Eb
			E_1,		///< E  ミ
			F_1,		///< F  ファ
			Fs1,		///< F#
			Gb1 = Fs1,	///< Gb
			G_1,		///< G  ソ
			Gs1,		///< G#

			Ab1 = Gs1,	///< Ab
			A_1,		///< A  ラ  55Hz (1)
			As1,		///< A#
			Bb1 = As1,	///< Bb
			B_1,		///< B  シ
			C_2,		///< C  ド
			Cs2,		///< C#
			Db2 = Cs2,	///< Db
			D_2,		///< D  レ
			Ds2,		///< D#
			Eb2 = Ds2,	///< Eb
			E_2,		///< E  ミ
			F_2,		///< F  ファ
			Fs2,		///< F#
			Gb2 = Fs2,	///< Gb
			G_2,		///< G  ソ
			Gs2,		///< G#

			Ab2 = Gs2,	///< Ab
			A_2,		///< A  ラ  110Hz (2)
			As2,		///< A#
			Bb2 = As2,	///< Bb
			B_2,		///< B  シ
			C_3,		///< C  ド
			Cs3,		///< C#
			Db3 = Cs3,	///< Db
			D_3,		///< D  レ
			Ds3,		///< D#
			Eb3 = Ds3,	///< Eb
			E_3,		///< E  ミ
			F_3,		///< F  ファ
			Fs3,		///< F#
			Gb3 = Fs3,	///< Gb
			G_3,		///< G  ソ
			Gs3,		///< G#

			Ab3 = Gs3,	///< Ab
			A_3,		///< A  ラ  220Hz (3)
			As3,		///< A#
			Bb3 = As3,	///< Bb
			B_3,		///< B  シ
			C_4,		///< C  ド
			Cs4,		///< C#
			Db4 = Cs4,	///< Db
			D_4,		///< D  レ
			Ds4,		///< D#
			Eb4 = Ds4,	///< Eb
			E_4,		///< E  ミ
			F_4,		///< F  ファ
			Fs4,		///< F#
			Gb4 = Fs4,	///< Gb
			G_4,		///< G  ソ
			Gs4,		///< G#

			Ab4 = Gs4,	///< Ab
			A_4,		///< A  ラ  440Hz (4)
			As4,		///< A#
			Bb4 = As4,	///< Bb
			B_4,		///< B  シ
			C_5,		///< C  ド
			Cs5,		///< C#
			Db5 = Cs5,	///< Db
			D_5,		///< D  レ
			Ds5,		///< D#
			Eb5 = Ds5,	///< Eb
			E_5,		///< E  ミ
			F_5,		///< F  ファ
			Fs5,		///< F#
			Gb5 = Fs5,	///< Gb
			G_5,		///< G  ソ
			Gs5,		///< G#

			Ab5 = Gs5,	///< Ab
			A_5,		///< A  ラ  880Hz (5)
			As5,		///< A#
			Bb5 = As5,	///< Bb
			B_5,		///< B  シ
			C_6,		///< C  ド
			Cs6,		///< C#
			Db6 = Cs6,	///< Db
			D_6,		///< D  レ
			Ds6,		///< D#
			Eb6 = Ds6,	///< Eb
			E_6,		///< E  ミ
			F_6,		///< F  ファ
			Fs6,		///< F#
			Gb6 = Fs6,	///< Gb
			G_6,		///< G  ソ
			Gs6,		///< G#

			Ab6 = Gs6,	///< Ab
			A_6,		///< A  ラ 1760Hz (6)
			As6,		///< A#
			Bb6 = As6,	///< Bb
			B_6,		///< B  シ
			C_7,		///< C  ド
			Cs7,		///< C#
			Db7 = Cs7,	///< Db
			D_7,		///< D  レ
			Ds7,		///< D#
			Eb7 = Ds7,	///< Eb
			E_7,		///< E  ミ
			F_7,		///< F  ファ
			Fs7,		///< F#
			Gb7 = Fs7,	///< Gb
			G_7,		///< G  ソ
			Gs7,		///< G#

			Ab7 = Gs7,	///< Ab
			A_7,		///< A  ラ 3520Hz (7)
			As7,		///< A#
			B_7,		///< B  シ
			C_8,		///< C  ド

			Q,		///< 休符
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  制御コマンド
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CTRL : uint8_t {
			TR = 89,	///< (2) トランスポーズ, num(-88 ~ 0 ~ 88)
			SQ25,		///< (1) 波形 SQ25
			SQ50,		///< (1) 波形 SQ50
			SQ75,		///< (1) 波形 SQ75
			TRI,		///< (1) 波形 TRI
			VOLUME,		///< (2) ボリューム, num(0 ~ 128)
			FADE,		///< (2) フェード目標値, num(0 ~ 128)
			FADE_SPEED,	///< (2) フェード速度, num(0 ~ 255)
			TEMPO,		///< (2) テンポ, num(1 ~ 255)
			FOR,		///< (2) ループ開始, num(1 ~ 255)
			BEFORE,		///< (1) ループ終了
			END,		///< (1) 終了
			CALL0,		///< (1) サブルーチンコール０
			CALL1,		///< (1) サブルーチンコール１
			CALL2,		///< (1) サブルーチンコール２
			CALL3,		///< (1) サブルーチンコール３
			CALL4,		///< (1) サブルーチンコール４
			CALL5,		///< (1) サブルーチンコール５
			CALL6,		///< (1) サブルーチンコール６
			CALL7,		///< (1) サブルーチンコール７
			RET,		///< (1) サブルーチンコールから復帰
			REPEAT,		///< (1) リピート
			ATTACK,		///< (2) 音のアタック, gain(0 ~ 255)
			RELEASE,	///< (3) 音のリリース, release_frame(n), gain(0 ~ 255)
			CHOUT,		///< (2) 文字出力, char（楽譜のデバッグ用に文字を出力）
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  スコア・コマンド構造 @n
					・KEY, len @n
					・TR, num @n
					・TEMPO, num @n
					・FOR, num
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct SCORE {
			union {
				KEY		key;
				CTRL	ctrl;
				uint8_t	len;
			};
			constexpr SCORE(KEY k) noexcept : key(k) { }
			constexpr SCORE(CTRL c) noexcept : ctrl(c) { }
			constexpr SCORE(uint8_t l) noexcept : len(l) { }
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  PSG Manager テンプレート class
		@param[in]	SAMPLE	サンプリング周期
		@param[in]	TICK	演奏tick（通常１００Ｈｚ）
		@param[in]	CNUM	チャネル数（通常４）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint16_t SAMPLE, uint16_t TICK, uint16_t CNUM>
	class psg_mng : public psg_base {

		// 12 平均音階率の計算：
		// 2^(1/12) の定数、１２乗すると２倍（１オクターブ上がる）となる。
		static constexpr uint16_t key_tbl_[12] = {
			static_cast<uint16_t>((3520 * 65536.0 * 1.000000000) / SAMPLE),  ///< A  ラ
			static_cast<uint16_t>((3520 * 65536.0 * 1.059463094) / SAMPLE),  ///< A#
			static_cast<uint16_t>((3520 * 65536.0 * 1.122462048) / SAMPLE),  ///< B  シ
			static_cast<uint16_t>((3520 * 65536.0 * 1.189207115) / SAMPLE),  ///< C  ド
			static_cast<uint16_t>((3520 * 65536.0 * 1.25992105 ) / SAMPLE),  ///< C#
			static_cast<uint16_t>((3520 * 65536.0 * 1.334839854) / SAMPLE),  ///< D  レ
			static_cast<uint16_t>((3520 * 65536.0 * 1.414213562) / SAMPLE),  ///< D#
			static_cast<uint16_t>((3520 * 65536.0 * 1.498307077) / SAMPLE),  ///< E  ミ
			static_cast<uint16_t>((3520 * 65536.0 * 1.587401052) / SAMPLE),  ///< F  ファ
			static_cast<uint16_t>((3520 * 65536.0 * 1.681792831) / SAMPLE),  ///< F#
			static_cast<uint16_t>((3520 * 65536.0 * 1.781797436) / SAMPLE),  ///< G  ソ
			static_cast<uint16_t>((3520 * 65536.0 * 1.887748625) / SAMPLE),  ///< G#
		};

		static constexpr uint8_t	SUB_SCORE_NUM = 8;  // サブスコア最大数
		static constexpr uint8_t	STACK_DEPTH = 4;  // 4 レベル
		static constexpr uint16_t	ENV_CYCLE = SAMPLE / TICK;

		struct share_t {
			const SCORE*	sub_score_[SUB_SCORE_NUM];
			bool			pause_;
			share_t() noexcept :
				sub_score_{ nullptr }, pause_(false)
			{ }
		};
		share_t		share_;

		struct stack_t {
			const SCORE*	org_;
			uint16_t		pos_;
		};

		struct channel {
			share_t&	share_;
			uint8_t		volume_;
			uint8_t		fade_;
			uint8_t		fade_spd_;
			uint8_t		fade_cnt_;
			WTYPE		wtype_;
			uint16_t	acc_;
			uint16_t	spd_;
			const SCORE*	score_org_;
			uint16_t	score_pos_;
			uint8_t		tempo_;
			uint16_t	count_;
			uint8_t		tr_;
			uint16_t	loop_org_;
			uint8_t		loop_cnt_;
			uint8_t		env_;  // 0 to 127
			uint16_t	env_cycle_;  // ENV_CYCLE の型と同じにする必要がある。
			uint8_t		attack_;
			uint8_t		rel_frame_;
			uint8_t		release_;
			uint16_t	rel_count_;
			stack_t		stack_[STACK_DEPTH];
			uint8_t		stack_pos_;
			uint16_t	total_count_;
			channel(share_t& share) noexcept : share_(share), volume_(0), fade_(0), fade_spd_(0), fade_cnt_(0),
				wtype_(WTYPE::SQ50), acc_(0), spd_(0),
				score_org_(nullptr), score_pos_(0),
				tempo_(0), count_(0),
				tr_(0), loop_org_(0), loop_cnt_(0),
				env_(0), env_cycle_(0), attack_(0), rel_frame_(0), release_(0), rel_count_(0),
				stack_{ }, stack_pos_(0),
				total_count_(0)
			{ }

			void init() noexcept
			{
				spd_ = 0;
				volume_ = 128;  // ボリューム初期値
				fade_ = 0;
				fade_spd_ = 64;
				fade_cnt_ = 0;
				tempo_ = 64;  // テンポ初期値
				count_ = 0;
				env_ = 0;
				attack_ = 150;  // アタック初期値
				release_ = 10; // リリース減衰初期値
				rel_frame_ = 6; // リリース TICK 標準
			}

			void update() noexcept
			{
				acc_ += spd_;
			}

			int8_t get() noexcept
			{
				if(spd_ == 0) return 0;

				bool on = false;
				int8_t w = 0;
				switch(wtype_) {
				case WTYPE::SQ25:
					if((acc_ & 0xc000) >= 0xc000) on = true;
					// 矩形波は、三角波に比べて、音圧が高いので、バランスを取る為少し弱める。
					w = env_ - (env_ >> 3);
					break;
				case WTYPE::SQ50:
					if((acc_ & 0xc000) >= 0x8000) on = true;
					// 矩形波は、三角波に比べて、音圧が高いので、バランスを取る為少し弱める。
					w = env_ - (env_ >> 3);
					break;
				case WTYPE::SQ75:
					if((acc_ & 0xc000) >= 0x4000) on = true;
					// 矩形波は、三角波に比べて、音圧が高いので、バランスを取る為少し弱める。
					w = env_ - (env_ >> 3);
					break;
				case WTYPE::TRI:
					{
						w = (acc_ >> 11) & 0b111;
						if((acc_ & 0x4000) != 0) w ^= 0b111;
						w *= env_ >> 3;
						if((acc_ & 0x8000) != 0) {
							on = true;
						}
					}
					break;
				case WTYPE::NOISE:
					w = 0;
					break;
				}
				if(!on) { w = -w; }

				++env_cycle_;
				if(env_cycle_ >= ENV_CYCLE) {
					env_cycle_ = 0;
					if(rel_count_ > 0) {
						rel_count_--;
						// +エンベロープ
						env_ += static_cast<uint16_t>((volume_ - env_) * attack_) >> 8;
					} else {
						// -エンベロープ
						uint8_t n = static_cast<uint16_t>(env_ * release_) >> 8;
						if(n > 0) env_ -= n;
						else {
							if(env_ > 0) --env_;
						}
					}
				}
				return w;
			}

			void set_freq(uint16_t frq) noexcept { spd_ = (static_cast<uint32_t>(frq) << 16) / SAMPLE; }

			// 完了なら「true」
			bool service() noexcept
			{
				if(score_org_ == nullptr) return true;

				if(fade_ != 0 && fade_spd_ != 0) {
					uint16_t tmp = fade_cnt_;
					tmp += fade_spd_;
					fade_cnt_ = tmp;
					if(tmp >= 256) {
						fade_cnt_ = 0;
						if(volume_ > fade_) volume_--;
						else if(volume_ < fade_) volume_++;
					}
				}

				if(share_.pause_) return true;

				if(count_ >= tempo_) {
					count_ -= tempo_;
					if(count_ >= tempo_) return true;
				}

				auto v = score_org_[score_pos_];
				++score_pos_;
				if(v.len < 88) {
					v.len += tr_;
					if(v.len >= 0x80) v.len = 0;
					else if(v.len >= 88) v.len = 87;
					auto o = v.len / 12;
					auto k = v.len % 12;
					spd_ = key_tbl_[k] >> (7 - o);
					acc_ = 0;
					env_ = 0;
					total_count_ += score_org_[score_pos_].len;
					count_ += static_cast<uint16_t>(score_org_[score_pos_].len) << 8;
					++score_pos_;
					// リリースポイント計算
					rel_count_ = (count_ / tempo_) - rel_frame_;
					env_cycle_ = 0;
					return true;
				} else if(v.len == 88) {  // 休符
					spd_ = 0;
					acc_ = 0;
					env_ = 0;
					total_count_ += score_org_[score_pos_].len;
					count_ += score_org_[score_pos_].len << 8;
					++score_pos_;
					return true;
				} else {
					switch(v.ctrl) {
					case CTRL::TR:
						tr_ = score_org_[score_pos_].len;
						++score_pos_;
						break;
					case CTRL::SQ25:
						wtype_ = WTYPE::SQ25;
						break;
					case CTRL::SQ50:
						wtype_ = WTYPE::SQ50;
						break;
					case CTRL::SQ75:
						wtype_ = WTYPE::SQ75;
						break;
					case CTRL::TRI:
						wtype_ = WTYPE::TRI;
						break;
					case CTRL::VOLUME:
						volume_ = score_org_[score_pos_].len;
						++score_pos_;
						break;
					case CTRL::FADE:
						fade_ = score_org_[score_pos_].len;
						++score_pos_;
						fade_cnt_ = 0;
						break;
					case CTRL::FADE_SPEED:
						fade_spd_ = score_org_[score_pos_].len;
						++score_pos_;
						fade_cnt_ = 0;
						break;
					case CTRL::TEMPO:
						tempo_ = score_org_[score_pos_].len;
						++score_pos_;
						count_ = 0;
						break;
					case CTRL::FOR:
						loop_cnt_ = score_org_[score_pos_].len;
						++score_pos_;
						loop_org_ = score_pos_;
						break;
					case CTRL::BEFORE:
						if(loop_cnt_ > 1) {
							loop_cnt_--;
							score_pos_ = loop_org_;
						}
						break;
					case CTRL::END:
						score_org_ = nullptr;
						spd_ = 0;
						break;
					case CTRL::CALL0:
					case CTRL::CALL1:
					case CTRL::CALL2:
					case CTRL::CALL3:
					case CTRL::CALL4:
					case CTRL::CALL5:
					case CTRL::CALL6:
					case CTRL::CALL7:
						if(stack_pos_ < STACK_DEPTH) {
							stack_[stack_pos_].org_ = score_org_;
							stack_[stack_pos_].pos_ = score_pos_;
							++stack_pos_;
							score_org_ = share_.sub_score_[v.len - static_cast<uint8_t>(CTRL::CALL0)];
							score_pos_ = 0;
						}
						break;
					case CTRL::RET:
						if(stack_pos_ > 0 && stack_pos_ <= STACK_DEPTH) {
							stack_pos_--;
							score_org_ = stack_[stack_pos_].org_;
							score_pos_ = stack_[stack_pos_].pos_;
						}
						break;
					case CTRL::REPEAT:
						score_pos_ = 0;
						init();
						break;
					case CTRL::ATTACK:
						attack_ = score_org_[score_pos_].len;
						++score_pos_;
						break;
					case CTRL::RELEASE:
						rel_frame_ = score_org_[score_pos_].len;
						++score_pos_;
						release_ = score_org_[score_pos_].len;
						++score_pos_;
						break;
					case CTRL::CHOUT:
						sci_putch(static_cast<char>(score_org_[score_pos_].len));
						++score_pos_;
						break;
					default:
						break;
					}
					return false;
				}
			}
		};

		channel		channel_[CNUM];

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		psg_mng() noexcept :
			share_(),
			channel_{ share_, share_, share_ }
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  波形タイプの設定
			@param[in]	ch		チャネル番号
			@param[in]	wt		波形タイプ
		*/
		//-----------------------------------------------------------------//
		void set_wtype(uint8_t ch, WTYPE wt) noexcept
		{
			if(ch >= CNUM) return;
			channel_[ch].wtype_ = wt;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ボリュームの設定
			@param[in]	ch		チャネル番号
			@param[in]	vol		ボリューム（0 to 15）	
		*/
		//-----------------------------------------------------------------//
		void set_volume(uint8_t ch, uint8_t vol) noexcept
		{
			if(ch >= CNUM) return;
			channel_[ch].vol_ = vol & 15;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  周波数で指定
			@param[in]	ch		チャネル番号
			@param[in]	frq		周波数
		*/
		//-----------------------------------------------------------------//
		void set_freq(uint8_t ch, uint16_t frq) noexcept
		{
			if(ch >= CNUM) return;
			channel_[ch].set_freq(frq);
			channel_[ch].acc_ = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  キー、オクターブで指定
			@param[in]	ch		チャネル番号
			@param[in]	key		キー
		*/
		//-----------------------------------------------------------------//
		void set_key(uint8_t ch, KEY key) noexcept
		{
			if(ch >= CNUM) return;
			auto o = static_cast<uint8_t>(key) / 12;
			auto k = static_cast<uint8_t>(key) % 12;
			channel_[ch].spd_ = key_tbl_[k] >> (7 - o);
			channel_[ch].acc_ = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  レンダリング
			@param[in]	count	波形数
			@param[out]	out		波形出力
		*/
		//-----------------------------------------------------------------//
		void render(uint16_t count, int8_t* out) noexcept
		{
			for(uint16_t i = 0; i < count; ++i) {
				int16_t sum = 0;
				// int8_t n = 0;
				int8_t n = 1;  // 理由がイマイチ判らないが、フルスケールで合成するとノイズが乗るので、とりあえず、全体のゲインを下げる。
				// ノイズが乗る原因は、そもそも PWM 変調に問題があるのかもしれない・・
				for(uint8_t j = 0; j < CNUM; ++j) {
					if(channel_[j].score_org_ != nullptr) {
						channel_[j].update();
						sum += static_cast<int16_t>(channel_[j].get());
						++n;
					}
				}
				out[i] = (sum / n);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  スコアの設定
			@param[in]	ch		チャネル番号
			@param[in]	score	スコア
		*/
		//-----------------------------------------------------------------//
		void set_score(uint8_t ch, const SCORE* score) noexcept
		{
			if(ch >= CNUM) return;

			channel_[ch].score_org_ = score;
			channel_[ch].score_pos_ = 0;
			channel_[ch].init();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サブ・スコアの設定
			@param[in]	idx		インデックス
			@param[in]	score	スコア
		*/
		//-----------------------------------------------------------------//
		void set_sub_score(uint8_t idx, const SCORE* score) noexcept
		{
			if(idx >= SUB_SCORE_NUM) return;

			share_.sub_score_[idx] = score;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  演奏サービス
		*/
		//-----------------------------------------------------------------//
		void service() noexcept
		{
			for(uint8_t i = 0; i < CNUM; ++i) {
				for(;;) {
					if(channel_[i].service()) {
						break;
					}
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  演奏の一時停止
			@param[in]	ena		「false」を指定するとポーズを解除
		*/
		//-----------------------------------------------------------------//
		void pause(bool ena = true) noexcept { share_.pause_ = ena; }


		//-----------------------------------------------------------------//
		/*!
			@brief  合計音長を得る
			@param[in]	ch	チャネル
		*/
		//-----------------------------------------------------------------//
		uint16_t get_total_count(uint8_t ch) const noexcept
		{
			if(ch < CNUM) {
				return channel_[ch].total_count_;
			} else {
				return 0;
			}
		}
	};

	template<uint16_t SAMPLE, uint16_t TICK, uint16_t CNUM>
		constexpr uint16_t psg_mng<SAMPLE, TICK, CNUM>::key_tbl_[12];
}