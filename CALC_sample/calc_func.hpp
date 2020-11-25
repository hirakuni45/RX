#pragma once
//=====================================================================//
/*! @file
    @brief  電卓関数クラス
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
    class calc_func {
	public:
		//=============================================================//
		/*!
			@brief	関数 (0xC0 to 0xFF)、定義
		*/
		//=============================================================//
		enum class NAME : uint8_t {
			SIN = 0xC0,		///< sin(x)
			COS,			///< cos(x)
			TAN,			///< tan(x)
			ASIN,			///< asin(x)
			ACOS,			///< acos(x)
			ATAN,			///< atan(x)

			SQRT,			///< sqrt(x)
			LOG,			///< log(x)
			LN,				///< ln(x)

			EXP10,			///< exp10(x)
		};


		//=============================================================//
		/*!
			@brief  角度表現定義
		*/
		//=============================================================//
		enum class ATYPE : uint8_t {
			Deg,	///< Deg 度数法 (360)
			Rad,	///< Rad 弧度法 (2pai)
			Grad	///< 具ラード (400)
		};

	private:
		NVAL	pai_;
		NVAL	rad_;
		NVAL	grad_;
		NVAL	c2_;

		ATYPE	atype_;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
		*/
		//-------------------------------------------------------------//
		calc_func() noexcept :
			rad_(360), grad_(400), c2_(2),
			atype_(ATYPE::Deg) { }


		//-------------------------------------------------------------//
		/*!
			@brief  角度からラジアンへの変換
			@param[in]	ang		角度（０～３６０）
			@return ラジアン（2 x pai)
		*/
		//-------------------------------------------------------------//
		NVAL conv_to_rad(const NVAL& in) noexcept
		{
			switch(atype_) {
			case ATYPE::Deg:
				return in / rad_ * c2_ * NVAL::get_pi();
			case ATYPE::Rad:
				return in;
			case ATYPE::Grad:
				return in / grad_ * c2_ * NVAL::get_pi();
			}
			return in;
		}


		NVAL conv_rad_to(const NVAL& in) noexcept
		{
			switch(atype_) {
			case ATYPE::Deg:
				return in / (c2_ * NVAL::get_pi()) * rad_; 
			case ATYPE::Rad:
				return in;
			case ATYPE::Grad:
				return in / (c2_ * NVAL::get_pi()) * grad_; 
			}
			return in;
		}


		//-------------------------------------------------------------//
		/*!
			@brief  角度タイプの指定
			@param[in]	atype	角度表現
		*/
		//-------------------------------------------------------------//
		void set_atype(ATYPE atype) noexcept { atype_ = atype; }


		//-------------------------------------------------------------//
		/*!
			@brief  角度タイプの取得
			@return	角度表現
		*/
		//-------------------------------------------------------------//
		ATYPE get_atype() const noexcept { return atype_; }


		//-------------------------------------------------------------//
		/*!
			@brief  関数文字列の取得
			@param[in]	name	関数名
		*/
		//-------------------------------------------------------------//
		const char* get_name(NAME name) const
		{
			switch(name) {
			case NAME::SIN:  return "sin";
			case NAME::COS:  return "cos";
			case NAME::TAN:  return "tan";
			case NAME::ASIN:  return "asin";
			case NAME::ACOS:  return "acos";
			case NAME::ATAN:  return "atan";
			case NAME::SQRT: return "sqrt";
			case NAME::LOG:  return "log";
			case NAME::LN:   return "ln";
			case NAME::EXP10: return "e10";
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
			return strlen(get_name(name)) * 8;
		}


		//-------------------------------------------------------------//
		/*!
			@brief	  関数機能
			@param[in]	name	関数名
			@param[in]	in		入力
			@param[out]	out		出力
			@return 関数機能がマッチしない場合「false」
		*/
		//-------------------------------------------------------------//
		bool operator() (NAME name, const NVAL& in, NVAL& out) noexcept
		{
			switch(name) {
			case NAME::SIN:
				{
					auto a = conv_to_rad(in);
					out = NVAL::sin(a);
				}
				break;
			case NAME::COS:
				{
					auto a = conv_to_rad(in);
					out = NVAL::cos(a);
				}
				break;
			case NAME::TAN:
				{
					auto a = conv_to_rad(in);
					out = NVAL::tan(a);
				}
				break;
			case NAME::ASIN:
				{
					auto a = NVAL::asin(in);
					out = conv_rad_to(a);
				}
				break;
			case NAME::ACOS:
				{
					auto a = NVAL::acos(in);
					out = conv_rad_to(a);
				}
				break;
			case NAME::ATAN:
				{
					auto a = NVAL::atan(in);
					out = conv_rad_to(a);
				}
				break;



			case NAME::SQRT:
				{
					out = NVAL::sqrt(in);
				}
				break;
			case NAME::LOG:
				{
					out = NVAL::log10(in);
				}
				break;
			case NAME::LN:
				{
					out = NVAL::log(in);
				}
				break;

			case NAME::EXP10:
				{
					out = NVAL::exp10(in);
				}
				break;
			default:
				return false;
			}
			return true;
		}
	};
}
