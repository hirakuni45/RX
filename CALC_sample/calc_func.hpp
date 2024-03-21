#pragma once
//=====================================================================//
/*! @file
    @brief  電卓関数クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cmath>
#include <cstring>
#include "common/fixed_string.hpp"

namespace utils {

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    /*!
        @brief  CALC FUNC クラス
		@param[in]	NVAL	数値クラス
		@param[in]	MAP		マップ・クラス
    */
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class NVAL, class MAP>
    struct calc_func {

		//=============================================================//
		/*!
			@brief	関数 (0xC0 to 0xFF)、定義型
		*/
		//=============================================================//
		enum class NAME : uint8_t {
			NONE = 0,		///< 未定義

			org = 0xC0,		///< 開始

			SIN = 0xC0,		///< sin(x)
			COS,			///< cos(x)
			TAN,			///< tan(x)
			ASIN,			///< asin(x)
			ACOS,			///< acos(x)
			ATAN,			///< atan(x)
			SINH,			///< sinh(x)
			COSH,			///< cosh(x)
			TANH,			///< tanh(x)
			ASINH,			///< asinh(x)
			ACOSH,			///< acosh(x)
			ATANH,			///< atanh(x)

			SQRT,			///< sqrt(x)
			LOG,			///< log(x)
			LN,				///< ln(x)
			EINT,			///< eint(x)

			EXP10,			///< exp10(x)
			GAMMA,			///< gamma(x)
			ZETA,			///< zeta(x)

			ABS,			///< abs(x)
			RINT,			///< rint(x)
			FRAC,			///< frac(x)

			last,
			limit = 0xFF
		};


		//=============================================================//
		/*!
			@brief  角度表現型
		*/
		//=============================================================//
		enum class ATYPE : uint8_t {
			Deg,	///< Deg 度数法 (360)
			Rad,	///< Rad 弧度法 (2pai)
			Grad	///< グラード (400)
		};


		//=============================================================//
		/*!
			@brief  数値表現型
		*/
		//=============================================================//
		enum class VTYPE : uint8_t {
			Dec,	///< １０進
			Hex,	///< １６進
			Bin		///< ２進
		};

	private:
		NVAL	rad_;
		NVAL	grad_;
		NVAL	c2_;

		ATYPE	atype_;
		VTYPE	vtype_;

		MAP&	map_;
		uint8_t	id_;

	public:
		//-------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
			@param[in]	map		MAP クラス
		*/
		//-------------------------------------------------------------//
		calc_func(MAP& map) noexcept :
			rad_(360), grad_(400), c2_(2),
			atype_(ATYPE::Deg), vtype_(VTYPE::Dec),
			map_(map), id_(static_cast<uint8_t>(NAME::last))
		{
			map_.insert(std::pair("sin", static_cast<uint8_t>(NAME::SIN)));
			map_.insert(std::pair("cos", static_cast<uint8_t>(NAME::COS)));
			map_.insert(std::pair("tan", static_cast<uint8_t>(NAME::TAN)));
			map_.insert(std::pair("asin", static_cast<uint8_t>(NAME::ASIN)));
			map_.insert(std::pair("acos", static_cast<uint8_t>(NAME::ACOS)));
			map_.insert(std::pair("atan", static_cast<uint8_t>(NAME::ATAN)));
			map_.insert(std::pair("sinh", static_cast<uint8_t>(NAME::SINH)));
			map_.insert(std::pair("cosh", static_cast<uint8_t>(NAME::COSH)));
			map_.insert(std::pair("tanh", static_cast<uint8_t>(NAME::TANH)));
			map_.insert(std::pair("asinh", static_cast<uint8_t>(NAME::ASINH)));
			map_.insert(std::pair("acosh", static_cast<uint8_t>(NAME::ACOSH)));
			map_.insert(std::pair("atanh", static_cast<uint8_t>(NAME::ATANH)));
			map_.insert(std::pair("sqrt", static_cast<uint8_t>(NAME::SQRT)));
			map_.insert(std::pair("log", static_cast<uint8_t>(NAME::LOG)));
			map_.insert(std::pair("ln", static_cast<uint8_t>(NAME::LN)));
			map_.insert(std::pair("eint", static_cast<uint8_t>(NAME::EINT)));
			map_.insert(std::pair("exp10", static_cast<uint8_t>(NAME::EXP10)));
			map_.insert(std::pair("gamma", static_cast<uint8_t>(NAME::GAMMA)));
			map_.insert(std::pair("zeta", static_cast<uint8_t>(NAME::ZETA)));
			map_.insert(std::pair("abs", static_cast<uint8_t>(NAME::ABS)));
			map_.insert(std::pair("rint", static_cast<uint8_t>(NAME::RINT)));
			map_.insert(std::pair("frac", static_cast<uint8_t>(NAME::FRAC)));
		}


		//-------------------------------------------------------------//
		/*!
			@brief  ID が有効であるか？
			@param[in]	id	NAME 型
			@return 「true」なら有効なシンボル
		*/
		//-------------------------------------------------------------//
		static bool probe(NAME id) noexcept
		{
			auto i = static_cast<uint8_t>(id);
			if(i >= static_cast<uint8_t>(NAME::org) && i <= static_cast<uint8_t>(NAME::limit)) {
				return true;
			} else {
				return false;
			}
		}


		//-------------------------------------------------------------//
		/*!
			@brief  関数定義型の次
			@param[out]	id		関数定義型
		*/
		//-------------------------------------------------------------//
		static void next(NAME& id) noexcept
		{
			id = static_cast<NAME>(static_cast<uint8_t>(id) + 1);
		}


		//-------------------------------------------------------------//
		/*!
			@brief  関数登録
			@param[in]	name	関数名
			@param[in]	func	関数
			@return 関数名
		*/
		//-------------------------------------------------------------//
		NAME install(typename MAP::key_type name, const char* func) noexcept
		{
			if(name == nullptr || func == nullptr || id_ == 0) {
				return NAME::NONE;
			}

			auto it = map_.insert(std::pair(name, id_));
			if(it == map_.end()) {

			}


			return NAME::NONE;
		}


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
			@brief  角度型の指定
			@param[in]	t	角度型
		*/
		//-------------------------------------------------------------//
		void set_atype(ATYPE t) noexcept { atype_ = t; }


		//-------------------------------------------------------------//
		/*!
			@brief  角度型の取得
			@return	角度型
		*/
		//-------------------------------------------------------------//
		auto get_atype() const noexcept { return atype_; }


		//-------------------------------------------------------------//
		/*!
			@brief  数値型の指定
			@param[in]	t	数値型
		*/
		//-------------------------------------------------------------//
		void set_vtype(VTYPE t) noexcept { vtype_ = t; }


		//-------------------------------------------------------------//
		/*!
			@brief  角度型の取得
			@return	角度型
		*/
		//-------------------------------------------------------------//
		auto get_vtype() const noexcept { return vtype_; }


		//-------------------------------------------------------------//
		/*!
			@brief  関数文字列の取得
			@param[in]	name	関数名
			@return 関数文字列
		*/
		//-------------------------------------------------------------//
		auto get_name(NAME name) const noexcept
		{
			for(auto it : map_) {
				if(static_cast<NAME>(it.second) == name) {
					return it.first.c_str();
				}
			}
			return "";
		}


		//-------------------------------------------------------------//
		/*!
			@brief  関数名の取得
			@param[in]	text	関数文字列
			@param[out]	name	関数名型
			@return 移動後のポインター
		*/
		//-------------------------------------------------------------//
		const char* get_code(const char* text, NAME& name) const noexcept
		{
			if(text == nullptr) {
				name = NAME::NONE;
				return text;
			}

			auto p = strchr(text, '(');
			if(p == nullptr) {
				name = NAME::NONE;
				return text;
			}
			uint32_t l = p - text;
			typename MAP::key_type str(text, l);
			auto it = map_.find(str);
			if(it != map_.end()) {
				name = static_cast<NAME>(it->second);
				return text + l;
			}

			name = NAME::NONE;
			return text;
		}


		//-------------------------------------------------------------//
		/*!
			@brief	  関数機能
			@param[in]	name	関数型
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
			case NAME::SINH:
				out = NVAL::sinh(in);
				break;
			case NAME::COSH:
				out = NVAL::cosh(in);
				break;
			case NAME::TANH:
				out = NVAL::tanh(in);
				break;
			case NAME::ASINH:
				out = NVAL::asinh(in);
				break;
			case NAME::ACOSH:
				out = NVAL::acosh(in);
				break;
			case NAME::ATANH:
				out = NVAL::atanh(in);
				break;

			case NAME::SQRT:
				out = NVAL::sqrt(in);
				break;
			case NAME::LOG:
				out = NVAL::log10(in);
				break;
			case NAME::LN:
				out = NVAL::log(in);
				break;
			case NAME::EINT:
				out = NVAL::eint(in);
				break;

			case NAME::EXP10:
				out = NVAL::exp10(in);
				break;
			case NAME::GAMMA:
				out = NVAL::gamma(in);
				break;
			case NAME::ZETA:
				out = NVAL::zeta(in);
				break;

			case NAME::ABS:
				out = NVAL::abs(in);
				break;
			case NAME::RINT:
				out = NVAL::rint(in);
				break;
			case NAME::FRAC:
				out = NVAL::frac(in);
				break;
			default:
				return false;
			}
			return true;
		}
	};
}
