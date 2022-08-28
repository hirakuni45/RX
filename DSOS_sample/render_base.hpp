#pragma once
//=========================================================================//
/*! @file
    @brief  描画ベースクラス
    @author 平松邦仁 (hira@rvf-rc45.net)
    @copyright  Copyright (C) 2020, 2022 Kunihito Hiramatsu @n
                Released under the MIT license @n
                https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "graphics/color.hpp"

namespace dsos {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  波形描画ベース・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct render_base {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  操作ターゲット型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class TARGET : uint8_t {
			CH0,	///< CH0 電圧軸操作
			CH1,	///< CH1 電圧軸操作
		};


		/// チャネル・倍率文字列
		static constexpr char CH_MULT_STR[] = "X1,X10";

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  チャネル・倍率型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CH_MULT : uint8_t {
			X1,		///< X1 プローブ
			X10		///< X10 プローブ
		};


		const char* get_ch_mult_str(CH_MULT mult)
		{
			static char tmp[8];
			tmp[0] = 0;
			auto n = static_cast<uint8_t>(mult);
			utils::str::get_word(CH_MULT_STR, n, tmp, sizeof(tmp), ',');
			return tmp;
		}


		/// チャネル・モード文字列
		static constexpr char CH_MODE_STR[] = "AC,GND,DC,OFF";


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  チャネル・モード型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CH_MODE : uint8_t {
			AC,		///< AC モード
			GND,	///< GND 固定
			DC,		///< DC モード
			OFF		///< チャネル OFF
		};


		const char* get_ch_mode_str(CH_MODE mode)
		{
			static char tmp[8];
			tmp[0] = 0;
			auto n = static_cast<uint8_t>(mode);
			utils::str::get_word(CH_MODE_STR, n, tmp, sizeof(tmp), ',');
			return tmp;
		}


		/// チャネル・電圧文字列
		static constexpr char CH_VOLT_STR[] = "10V,5V,2V,1V,500mV,200mV,100mV,50mV,25mV";


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  電圧レンジ型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CH_VOLT : uint8_t {
			_10V,		///< 10V/div
			_5V,		///<  5V/div
			_2V,		///<  2V/div
			_1V,		///<  1V/div
			_500mV,		///< 500mV/div
			_200mV,		///< 200mV/div
			_100mV,		///< 100mV/div
			_50mV,		///<  50mV/div
			_25mV		///<  25mV/div
		};


		static constexpr int32_t VOLT_MV[] = {  // ｍV 単位
		   10000,	///< 10000mV (10.0V)
			5000,	///<  5000mV (5.0V)
			2000,	///<  2000mV (2.0V)
			1000,	///<  1000mV (1.0V)
			 500,	///<   500mV (0.5V)
			 200,	///<   200mV (0.2V)
			 100,	///<   100mV (0.1V)
			  50,	///<    50mV (0.05V)
			  25	///<    25mV (0.025V)
		};


		const char* get_ch_volt_str(CH_VOLT volt)
		{
			static char tmp[8];
			tmp[0] = 0;
			auto n = static_cast<uint8_t>(volt);
			utils::str::get_word(CH_VOLT_STR, n, tmp, sizeof(tmp), ',');
			return tmp;
		}


		static int32_t get_mvolt(CH_VOLT val)
		{
			return VOLT_MV[static_cast<uint8_t>(val)];
		}


		/// トリガー文字列
		static constexpr char TRG_MODE_STR[] = "Stop,Single,Auto,CH0-Pos,CH0-Neg,CH1-Pos,CH1-Neg";


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  トリガー型 @n
					'_' が前にある型は、capture クラスが内部的に利用している。
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class TRG_MODE : uint8_t {
			STOP,		///< 何もしない
			SINGLE,		///< シングル・ショット
			AUTO,		///< オートモード
			CH0_POS,	///< CH0 立ち上がりエッジ
			CH0_NEG,	///< CH0 立ち下がりエッジ
			CH1_POS,	///< CH1 立ち上がりエッジ
			CH1_NEG,	///< CH1 立ち下がりエッジ

			_CH0_POSA,	///< CH0 立ち上がりエッジ後 
			_CH1_POSA,	///< CH1 立ち上がりエッジ後
			_CH0_NEGA,	///< CH0 立ち下がりエッジ後
			_CH1_NEGA,	///< CH1 立ち下がりエッジ後
			_BEFORE,	///< 前処理（電圧ディバイダーを設定する）
			_TRG_BEFORE,///< ※内部処理 トリガー前処理
			_TRG_AFTER,	///< ※内部処理 トリガー後処理
		};


		const char* get_trg_mode_str(TRG_MODE trg)
		{
			static char tmp[16];
			tmp[0] = 0;
			auto n = static_cast<uint8_t>(trg);
			utils::str::get_word(TRG_MODE_STR, n, tmp, sizeof(tmp), ',');
			return tmp;
		}


		/// サンプリング・ユニット文字列
		static constexpr char SMP_UNIT_STR[] = "1us,10us,100us,1ms,10ms";

		/// サンプリング・ファイン文字列
		static constexpr char SMP_FINE0_STR[] = "1us,2us,5us";
		static constexpr char SMP_FINE1_STR[] = "10us,20us,50us";
		static constexpr char SMP_FINE2_STR[] = "100us,200us,500us";
		static constexpr char SMP_FINE3_STR[] = "1ms,2ms,5ms";
		static constexpr char SMP_FINE4_STR[] = "10ms,20ms,50ms";

		static constexpr uint8_t SMP_FINE_NUM = 3;

		/// サンプリング時間（マイクロ秒）
		static constexpr int32_t SMP_RATE_US[] = {
			     1,      2,      5,
			    10,     20,     50,
			   100,    200,    500,
			  1000,   2000,   5000,
			 10000,  20000,  50000
		};

		enum class SMP_MODE : uint8_t {
			  _1us,   _2us,   _5us,
			 _10us,  _20us,  _50us,
			_100us, _200us, _500us,
			  _1ms,   _2ms,   _5ms,
			 _10ms,  _20ms,  _50ms
		};

		static const char* get_smp_str(SMP_MODE smp)
		{
			auto p = static_cast<uint8_t>(smp);
			auto n = p / SMP_FINE_NUM;
			auto m = p % SMP_FINE_NUM;
			const char* unit = nullptr;
			switch(n) {
			case 0:
				unit = SMP_FINE0_STR;
				break;
			case 1:
				unit = SMP_FINE1_STR;
				break;
			case 2:
				unit = SMP_FINE2_STR;
				break;
			case 3:
				unit = SMP_FINE3_STR;
				break;
			case 4:
				unit = SMP_FINE4_STR;
				break;
			default:
				break;
			}
			static char tmp[16];
			tmp[0] = 0;
			if(unit != nullptr) {
				utils::str::get_word(unit, m, tmp, sizeof(tmp), ',');
			}
			return tmp;
		}


		static int32_t get_smp_rate(SMP_MODE smp)
		{
			return SMP_RATE_US[static_cast<uint8_t>(smp)];
		}


		/// A/D 変換サンプリングレート（KHz）
		static constexpr int16_t AD_SAMPLE_RATE[] = {
			  2000,   2000,   2000, 
			  2000,   2000,   2000,
			  2000,   2000,   2000,
			  1000,    500,    200,
			   100,     50,     20
		};


		/// 計測メニュー文字列
		static constexpr char MES_MODE_STR[] = "Off,Time Sub,CH0 Sub,CH1 Sub,Time Abs,CH0 Abs,CH1 Abs";


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  計測型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class MEASERE : uint8_t {
			OFF,
			TIME_SUB,	///< 時間差分
			CH0_SUB,	///< CH0 差分
			CH1_SUB,	///< CH1 差分
			TIME_ABS,	///< 時間絶対値
			CH0_ABS,	///< CH0 絶対値
			CH1_ABS		///< CH1 絶対値
		};


		/// オプションメニュー文字列
		static constexpr char OPTION_STR[] = "NONE,Capture,Save-WAV,CH0-FFT,CH1-FFT";


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  オプション型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class OPT_MODE : uint8_t {
			NONE,		///< 何もしない
			CAPTURE,	///< 画面をキャプチャーして画像ファイルとしてセーブ（４８０ｘ２７２）
			SAVE_WAVE,	///< 波形を WAV 形式でセーブ	
			CH0_FFT,	///< CH0 FFT
			CH1_FFT,	///< CH1 FFT
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  波形型（テスト波形生成）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class PWAVE_TYPE : uint8_t {
			SIN,		///< sin
			COS,		///< cos
			TRI_S,		///< 三角波(sin)
			TRI_C,		///< 三角波(cos)
			SQU_S,		///< 矩形波(sin)
			SQU_C,		///< 矩形波(cos)
			FSQU_S,		///< フィルター矩形波(sin)
			FSQU_C,		///< フィルター矩形波(cos)
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  波形情報クラス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct wave_info {

			int16_t		min_;
			int16_t		max_;

			int32_t		org_;
			int32_t		end_;

			float		freq_;

		private:
			int16_t		thv_org_;
			int16_t		thv_end_;
			uint16_t	step_;

		public:
			wave_info() noexcept :
				min_(0), max_(0), org_(0), end_(0), freq_(0.0f),
				thv_org_(0), thv_end_(0), step_(0)
			{ }


			void setup() noexcept
			{
				thv_org_ = (min_ + max_) / 2;
				thv_end_ = (thv_org_ + min_) / 2;
				step_ = 0;
			}


			void update(int16_t v, int32_t pos) noexcept
			{
				switch(step_) {
				case 0:
					if(v < thv_end_) {
						++step_;
					}
					break;
				case 1:
					if(v > thv_org_) {
						org_ = pos;
						step_++;
					}
					break;
				case 2:
					if(v < thv_end_) {
						step_++;
					}
					break;
				case 3:
					if(v > thv_org_) {
						end_ = pos;
						step_++;
					}
					break;
				default:
					break;
				}
			}


			bool probe() const noexcept { return step_ == 4; }

			bool build(uint32_t samplerate) noexcept
			{
				freq_ = 0.0f;

				if(!probe()) return false;

				auto d = end_ - org_;
				if(d == 0) return false;

				freq_ = static_cast<float>(samplerate) / static_cast<float>(d);

				return true;
			}
		};


		typedef graphics::def_color DEF_COLOR;

		static constexpr graphics::share_color	CH0_COLOR = DEF_COLOR::Yellow;		///< チャネル０カラー
		static constexpr graphics::share_color	CH1_COLOR = DEF_COLOR::Fuchsi;		///< チャネル１カラー
		static constexpr graphics::share_color	TRG_COLOR = DEF_COLOR::Orange;		///< トリガーカラー
		static constexpr graphics::share_color	SMP_COLOR = DEF_COLOR::SafeColor;	///< サンプルカラー
		static constexpr graphics::share_color	MES_COLOR = DEF_COLOR::Green;		///< 計測カラー

		render_base() noexcept 
		{ }
	};
}
