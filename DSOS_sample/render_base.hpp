#pragma once
//=========================================================================//
/*! @file
    @brief  描画ベースクラス
    @author 平松邦仁 (hira@rvf-rc45.net)
    @copyright  Copyright (C) 2020 Kunihito Hiramatsu @n
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

		/// グリッド単位数
		static const int16_t GRID = 40;


		/// チャネル・倍率文字列
		static constexpr char CH_MULT_STR[] = "X1,X10";


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  チャネル・倍率型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CH_MULT : uint8_t {
			X1,
			X10
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
			AC,
			GND,
			DC,
			OFF
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
		static constexpr char CH_VOLT_STR[] = "5V,1V,500mV,100mV,50mV,10mV";


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  チャネル・電圧型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class CH_VOLT : uint8_t {
			_5V,
			_1V,
			_500mV,
			_100mV,
			_50mV,
			_10mV
		};


		const char* get_ch_volt_str(CH_VOLT volt)
		{
			static char tmp[8];
			tmp[0] = 0;
			auto n = static_cast<uint8_t>(volt);
			utils::str::get_word(CH_VOLT_STR, n, tmp, sizeof(tmp), ',');
			return tmp;
		}


		static constexpr int32_t VOLT_MV[] = {
			5000,
			1000,
			 500,
			 100,
			  50,
			  10
		};


		static int32_t get_volt(CH_VOLT val)
		{
			return VOLT_MV[static_cast<uint8_t>(val)];
		}


		/// トリガー文字列
		static constexpr char TRG_MODE_STR[] = "None,One,Run,CH0-Pos,CH1-Pos,CH0-Neg,CH1-Neg";


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  チャネル・電圧型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class TRG_MODE : uint8_t {
			NONE,		///< 何もしない
			ONE,		///< ワンショット
			RUN,		///< フリーランニング
			CH0_POS,	///< CH0 立ち上がりエッジ
			CH1_POS,	///< CH1 立ち上がりエッジ
			CH0_NEG,	///< CH0 立ち下がりエッジ
			CH1_NEG,	///< CH1 立ち下がりエッジ
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
		static constexpr char SMP_UNIT_STR[] = "1us,10us,100us,1ms,10ms,100ms";

		/// サンプリング・ファイン文字列
		static constexpr char SMP_FINE0_STR[] = "1us,2us,5us";
		static constexpr char SMP_FINE1_STR[] = "10us,20us,50us";
		static constexpr char SMP_FINE2_STR[] = "100us,200us,500us";
		static constexpr char SMP_FINE3_STR[] = "1ms,2ms,5ms";
		static constexpr char SMP_FINE4_STR[] = "10ms,20ms,50ms";
		static constexpr char SMP_FINE5_STR[] = "100ms,200ms,500ms";

		static const uint8_t SMP_FINE_NUM = 3;

		static constexpr int32_t SMP_RATE_MS[] = {
			     1,      2,      5,
			    10,     20,     50,
			   100,    200,    500,
			  1000,   2000,   5000,
			 10000,  20000,  50000,
			100000, 200000, 500000
		};

		enum class SMP_MODE : uint8_t {
			_1us,
			_2us,
			_5us,
			_10us,
			_20us,
			_50us,
			_100us,
			_200us,
			_500us,
			_1ms,
			_2ms,
			_5ms,
			_10ms,
			_20ms,
			_50ms,
			_100ms,
			_200ms,
			_500ms
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
			case 5:
				unit = SMP_FINE5_STR;
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
			return SMP_RATE_MS[static_cast<uint8_t>(smp)];
		}


		/// 計測タイプ文字列
		static constexpr char MES_MODE_STR[] = "Off,Volt,Time";

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  計測型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class MEASERE : uint8_t {
			OFF,
			VOLT,
			TIME,
		};

		typedef graphics::def_color DEF_COLOR;

		const graphics::share_color&	CH0_COLOR;	///< チャネル０カラー
		const graphics::share_color&	CH1_COLOR;	///< チャネル１カラー
		const graphics::share_color&	TRG_COLOR;	///< トリガーカラー
		const graphics::share_color&	SMP_COLOR;	///< サンプルカラー
		const graphics::share_color&	MES_COLOR;	///< 計測カラー

		render_base() noexcept :
			CH0_COLOR(DEF_COLOR::Yellow),
			CH1_COLOR(DEF_COLOR::Fuchsi),
			TRG_COLOR(DEF_COLOR::Orange),
			SMP_COLOR(DEF_COLOR::SafeColor),
			MES_COLOR(DEF_COLOR::Green)
		{ }
	};
}
