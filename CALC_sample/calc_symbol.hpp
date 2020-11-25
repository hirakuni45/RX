#pragma once
//=====================================================================//
/*! @file
    @brief  電卓シンボルクラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cmath>
#include <cstring>

namespace utils {

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    /*!
        @brief  CALC FUNC クラス
		@param[in]	NVAL	数値クラス
    */
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class NVAL>
    class calc_symbol {

		NVAL	ans_;

		NVAL	v_[10];

	public:
		//=============================================================//
		/*!
			@brief  シンボル (0x80 to 0xBF)
		*/
		//=============================================================//
		enum class NAME : uint8_t {
			PI = 0x80,		///< PI
			LOG2,			///< ２の自然対数
			EULER,			///< Euler数（ネイピア数）
			ANS,			///< 解答シンボル
			V0,				///< 変素
			V1,				///< 変素
			V2,				///< 変素
			V3,				///< 変素
			V4,				///< 変素
			V5,				///< 変素
			V6,				///< 変素
			V7,				///< 変素
			V8,				///< 変素
			V9,				///< 変素
		};


		//-------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-------------------------------------------------------------//
		calc_symbol() noexcept : ans_(), v_{ } { }


		//-------------------------------------------------------------//
		/*!
			@brief  関数文字列の取得
			@param[in]	name	関数名
		*/
		//-------------------------------------------------------------//
		const char* get_name(NAME name) const
		{
			switch(name) {
			case NAME::PI:   return "π";
			case NAME::LOG2: return "LOG2";  ///< ２の自然対数
			case NAME::EULER: return "е";   ///< オイラー数
			case NAME::ANS:  return "ans";
			case NAME::V0: return "Sm0";
			case NAME::V1: return "Sm1";
			case NAME::V2: return "Sm2";
			case NAME::V3: return "Sm3";
			case NAME::V4: return "Sm4";
			case NAME::V5: return "Sm5";
			case NAME::V6: return "Sm6";
			case NAME::V7: return "Sm7";
			case NAME::V8: return "Sm8";
			case NAME::V9: return "Sm9";
			default:
				break;
			}
			return "";
		}


		//-------------------------------------------------------------//
		/*!
			@brief  関数文字列の取得
			@param[in]	name	関数名
		*/
		//-------------------------------------------------------------//
		uint32_t get_name_size(NAME name) const
		{
			if(name == NAME::PI || name == NAME::EULER) {
				return 16;
			} else {
				return strlen(get_name(name)) * 8;
			}
		}


		//-------------------------------------------------------------//
		/*!
			@brief	  シンボル値を設定
			@param[in]	name	関数名
			@param[in]	val		設定値
			@return 名前がマッチしない場合「false」
		*/
		//-------------------------------------------------------------//
		bool set_value(NAME name, const NVAL& val) noexcept
		{
			switch(name) {
			case NAME::ANS:
				ans_ = val;
				return true;
			case NAME::V0:
			case NAME::V1:
			case NAME::V2:
			case NAME::V3:
			case NAME::V4:
			case NAME::V5:
			case NAME::V6:
			case NAME::V7:
			case NAME::V8:
			case NAME::V9:
				v_[static_cast<uint8_t>(name) - static_cast<uint8_t>(NAME::V0)] = val;
				return true;
			default:
				break;
			}
			return false;		
		}


		//-------------------------------------------------------------//
		/*!
			@brief	  シンボル値返却
			@param[in]	name	関数名
			@param[out]	out		出力
			@return 名前がマッチしない場合「false」
		*/
		//-------------------------------------------------------------//
		bool operator() (NAME name, NVAL& out) noexcept
		{
			bool ret = true;
			switch(name) {
			case NAME::PI:
				out = NVAL::get_pi();
				break;
			case NAME::LOG2:
				out = NVAL::get_log2();
				break;
			case NAME::EULER:
				out = NVAL::get_euler();
				break;
			case NAME::ANS:
				out = ans_;
				break;
			case NAME::V0:
			case NAME::V1:
			case NAME::V2:
			case NAME::V3:
			case NAME::V4:
			case NAME::V5:
			case NAME::V6:
			case NAME::V7:
			case NAME::V8:
			case NAME::V9:
				out = v_[static_cast<uint8_t>(name) - static_cast<uint8_t>(NAME::V0)];
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}
	};
}
