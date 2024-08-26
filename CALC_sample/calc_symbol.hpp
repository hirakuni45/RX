#pragma once
//=====================================================================//
/*! @file
    @brief  電卓シンボルクラス
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
    class calc_symbol {

		static constexpr uint32_t USER_SYM_NUM = 16;

		NVAL	ans_;

		NVAL	v_[4 + 10 + USER_SYM_NUM];  // 基底変数４＋１０個

		MAP&	map_;

		uint8_t	id_;

	public:
		//=============================================================//
		/*!
			@brief  固定シンボル型 (0x80 to 0xBF) 64 個
		*/
		//=============================================================//
		enum class NAME : uint8_t {
			NONE = 0,		///< 未定義

			org = 0x80,

			PI = 0x80,		///< PI
			LOG2,			///< ２の自然対数
			EULER,			///< オイラー数（ネイピア数）
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

			last,
			limit = 0xBF
		};


		void insert(const char* str, NAME name) noexcept
		{
			map_.insert(std::pair(str, static_cast<uint8_t>(name)));
		}


		//-------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
			@param[in]	map		MAP クラス
		*/
		//-------------------------------------------------------------//
		calc_symbol(MAP& map) noexcept : ans_(), v_{ }, map_(map), id_(static_cast<uint8_t>(NAME::last))
		{
			insert("PI",    NAME::PI);
			insert("LOG2",  NAME::LOG2);
			insert("EULER", NAME::EULER);
			insert("ANS",   NAME::ANS);
			insert("V0",    NAME::V0);
			insert("V1",    NAME::V1);
			insert("V2",    NAME::V2);
			insert("V3",    NAME::V3);
			insert("V4",    NAME::V4);
			insert("V5",    NAME::V5);
			insert("V6",    NAME::V6);
			insert("V7",    NAME::V7);
			insert("V8",    NAME::V8);
			insert("V9",    NAME::V9);
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
			@brief  文字列の取得
			@param[in]	id	ID
			@return 文字列
		*/
		//-------------------------------------------------------------//
		auto get_name(NAME id) const
		{
			for(auto it : map_) {
				if(static_cast<NAME>(it.second) == id) {
					return it.first;
				}
			}
			static typename MAP::key_type t;
			return t;
		}


		//-------------------------------------------------------------//
		/*!
			@brief  シンボル名の取得
			@param[in]	text	関数文字列
			@param[out]	name	関数名型
			@return 移動後のポインター
		*/
		//-------------------------------------------------------------//
		const char* get_code(const char* text, NAME& name) const
		{
			if(text == nullptr) {
				name = NAME::NONE;
				return text;
			}

			auto p = text;
			char ch;
			bool first = true;
			while((ch = *p) != 0) {
				if(ch >= 'A' && ch <= 'Z') ;
				else if(ch >= 'a' && ch <= 'z') ;
				else if(ch == '_') ;
				else if(!first && ch >= '0' && ch <= '9') ;
				else {
					break;
				}
				++p;
				first = false;
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
