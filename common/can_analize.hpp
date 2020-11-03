#pragma once
//=====================================================================//
/*!	@file
	@brief	CAN 通信解析クラス @n
			std::map を使う場合、Makefile でのリンクを修正する (USER_DEFS = m stdc++) @n
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <boost/unordered_map.hpp>
// #include <map>
#include "common/can_io.hpp"
#include "common/format.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CAN 通信解析クラス
		@param[in]	CAN_IO	can_io クラス型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class CAN_IO>
	class can_analize {

		CAN_IO&		can_io_;

		typedef device::can_frame FRAME;
		typedef device::can_io_def CANDEF;

		struct info_t {
			uint32_t	count_;
			FRAME		frame_;
			info_t() : count_(0), frame_() { }
			info_t(uint32_t count, const FRAME& frame) : count_(count), frame_(frame) { }
		};

		typedef boost::unordered_map<uint32_t, info_t> MAP;
//		typedef std::map<uint32_t, info_t> MAP;
		MAP			map_;

		void list_line_(const info_t& t) const
		{
			char ch;
			if(t.frame_.get_RTR()) {
				ch = 'R';
			} else {
				ch = 'D';
			}
			if(t.frame_.get_IDE()) {
				utils::format("%c %6u E:x%07X (%u)\n")
					% ch % t.count_ % t.frame_.get_id() % t.frame_.get_id();
			} else {
				utils::format("%c %6u S:x%07X (%u)\n")
					% ch % t.count_ % t.frame_.get_id() % t.frame_.get_id();
			}
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクタ
			@param[in]	can_io	can_io インスタンス
		*/
		//-----------------------------------------------------------------//
		can_analize(CAN_IO& can_io) noexcept : can_io_(can_io), map_() { }


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス @n
					CAN/ID の収集と更新
		*/
		//-----------------------------------------------------------------//
		void service() noexcept
		{
			auto n = can_io_.get_recv_num();
			while(n > 0) {
				auto frm = can_io_.get_recv_frame();
				auto it = map_.find(frm.get_id());
				if(it != map_.end()) {  // 更新
					it->second.count_++;
					it->second.frame_ = frm;
				} else {
					map_.emplace(frm.get_id(), info_t(1, frm));
				}
				--n;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  マップをクリア
		*/
		//-----------------------------------------------------------------//
		void clear() noexcept
		{
			map_.clear();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ID の確認
			@param[in]	id	CAN/ID
			@return ID のフレームが見つかった場合「true」
		*/
		//-----------------------------------------------------------------//
		bool find(uint32_t id) const noexcept
		{
			return map_.find(id) != map_.end();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  CAN/ID のリストを表示
			@param[in]	id		CAN/ID
			@param[in]	verb	詳細表示の場合「true」
			@return ID が見つからない場合「false」
		*/
		//-----------------------------------------------------------------//
		bool list(uint32_t id, bool verb = false) noexcept
		{
			auto it = map_.find(id);
			if(it == map_.end()) {
				return false;
			}
			list_line_(it->second);
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  収集された CAN/ID の全リストを表示
			@param[in]	verb	詳細表示の場合「true」
		*/
		//-----------------------------------------------------------------//
		void list_all(bool verb = false) noexcept
		{
			uint32_t n = 0;
			uint32_t a = 0;
			uint32_t r = 0;
			uint32_t df = 0;
			uint32_t rf = 0;
			for(auto&& it : map_) {
				const auto& t = it.second;
				list_line_(t);
				a += t.count_;
				r += t.frame_.get_DLC();
				if(t.frame_.get_RTR()) {
					++rf;
				} else {
					++df;
				}
				++n;
			}
			utils::format("ID = %u / Total = %u, Records = %u, Df = %u, Rf = %u\n")
				% n % a % r % df % rf;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  CAN/ID フレームデータを表示
			@param[in]	id		CAN/ID
			@return ID が見つからない場合「false」
		*/
		//-----------------------------------------------------------------//
		bool dump(uint32_t id) noexcept
		{
			auto it = map_.find(id);
			if(it == map_.end()) {
				return false;
			}
			list_line_(it->second);
			CANDEF::list(it->second.frame_);
			return true;
		}
	};
}
