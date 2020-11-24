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

	public:
		//=============================================================//
		/*!
			@brief  シンボル (0x80 to 0xBF)
		*/
		//=============================================================//
		enum class NAME : uint8_t {
			PI = 0x80,		///< PI
			ANS,
		};


		//-------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-------------------------------------------------------------//
		calc_symbol() noexcept : ans_() { }


		//-------------------------------------------------------------//
		/*!
			@brief  関数文字列の取得
			@param[in]	name	関数名
		*/
		//-------------------------------------------------------------//
		const char* get_name(NAME name) const
		{
			switch(name) {
			case NAME::PI:  return "π";
			case NAME::ANS: return "ans";
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
			if(name == NAME::PI) return 16;
			else {
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
			case NAME::PI:  return false;
			case NAME::ANS:
				ans_ = val;
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
			case NAME::ANS:
				out = ans_;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}
	};
}
