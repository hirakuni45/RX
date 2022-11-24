#pragma once
//=========================================================================//
/*!	@file
	@brief	モニター（メモリの読出し、書き込み）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/command.hpp"
#include "common/format.hpp"
#include "common/input.hpp"
#include "common/fixed_string.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  モニター・クラス
		@param[in] SYM_MAX	最大シンボル数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t SYM_MAX>
	class monitor {

		uint32_t	sym_cnt_;
		uint32_t	sym_adr_[SYM_MAX];
		STR16		sym_str_[SYM_MAX];

		enum class B_WIDTH : uint8_t {
			BYTE,
			WORD,	// 16 bits
			LONG	// 32 bits
		};

		B_WIDTH		b_width_;

		uint32_t	address_;

		typedef command<256> CMD;
		CMD 	cmd_;		

		bool	init_;

		uint32_t step_() const noexcept
		{
			switch(b_width_) {
			case B_WIDTH::BYTE:
				return 1;
			case B_WIDTH::WORD:
				return 2;
			case B_WIDTH::LONG:
				return 4;
			}
			return 0;
		}

		uint32_t mask_() const noexcept
		{
			switch(b_width_) {
			case B_WIDTH::WORD:
				return 0xffff'fffe;
			case B_WIDTH::LONG:
				return 0xffff'fffc;
			default:
				return 0xffff'ffff;
			}
		}

		uint32_t rd_(uint32_t adr) const noexcept
		{
			switch(b_width_) {
			case B_WIDTH::BYTE:
				return device::rd8_(adr);
			case B_WIDTH::WORD:
				return device::rd16_(adr);
			case B_WIDTH::LONG:
				return device::rd32_(adr);
			}
			return 0;
		}

		void wr_(uint32_t adr, uint32_t data) const noexcept
		{
			switch(b_width_) {
			case B_WIDTH::BYTE:
				device::wr8_(adr, data);
				break;
			case B_WIDTH::WORD:
				adr &= 0xffff'fffe;
				device::wr16_(adr, data);
				break;
			case B_WIDTH::LONG:
				adr &= 0xffff'fffc;
				device::wr32_(adr, data);
				break;
			}
		}

		void data_(uint32_t org) const noexcept
		{
			org &= mask_();
			switch(b_width_) {
			case B_WIDTH::BYTE:
				utils::format(" %02X") % static_cast<uint32_t>(device::rd8_(org));
				break;
			case B_WIDTH::WORD:
				utils::format(" %04X") % static_cast<uint32_t>(device::rd16_(org));
				break;
			case B_WIDTH::LONG:
				utils::format(" %08X") % static_cast<uint32_t>(device::rd32_(org));
				break;
			}
		}

		void dump_(uint32_t org, uint32_t end) const noexcept
		{
			org &= mask_();
			if((org & 0xf) != 0) {
				utils::format("%08X:") % org;
				for(uint32_t i = 0; i < (org & 0xf); ++i) {
					if(((i + org) & 0xf) == 8) {
						utils::format(" ");
					}
					utils::format("   ");
				}
			}
			while(org <= end) {
				if((org & 0xf) == 8) {
					utils::format(" ");
				} else if((org & 0xf) == 0) {
					utils::format("%08X:") % org;
				}
				data_(org);
				org += step_();
				if((org & 0xf) == 0) {
					utils::format("\n");
				}
			}
			if((org & 0xf) != 0) {
				utils::format("\n");
			}
		}

		void read_(uint32_t org) const noexcept
		{
			utils::format("%08X:") % org;
			data_(org);
			utils::format("\n");
		}

		void list_(const char* match = nullptr) const noexcept
		{
			if(match == nullptr) {
				for(uint32_t i = 0; i < sym_cnt_; ++i) {
					utils::format("%08X: %s\n") % sym_adr_[i] % sym_str_[i].c_str();
				}
			} else {
				for(uint32_t i = 0; i < sym_cnt_; ++i) {
					if(sym_str_[i] == match) {
						utils::format("%08X: %s\n") % sym_adr_[i] % sym_str_[i].c_str();
						return;
					}
				}
			}
		}

		enum class OPR : uint8_t {
			NONE,
			DUMP,
			READ,
			WRITE,
			BUS,
			SYM,
			LIST,
		};

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		monitor() noexcept :
			sym_cnt_(0), sym_adr_{ 0 }, sym_str_{ },
			b_width_(B_WIDTH::BYTE), address_(0),
			cmd_(), init_(false)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス（コマンド解析）
		*/
		//-----------------------------------------------------------------//
		void service() noexcept
		{
			if(!init_) {
				init_ = true;
				cmd_.set_prompt("# ");
			}

			if(!cmd_.service()) {
				return;
			}

			uint32_t cmdn = cmd_.get_words();
			if(cmdn == 0) return;

			if(cmdn == 1 && cmd_.cmp_word(0, "help")) {
				utils::format("d[ump] [org] [end]      Dump memory.\n");
				utils::format("r[ead] [org]            Read memory.\n");
				utils::format("w[rite] org data ...    Write memory.\n");
				utils::format("bus [124]               Current bus width\n");
				utils::format("sym address name        Set symbol\n");
//				utils::format("list [name] ...         List symbol\n");
				return;
			}

			auto opr = OPR::NONE;
			if(cmdn >= 1) {
				if(cmd_.cmp_word(0, "dump")) {
					opr = OPR::DUMP;
				} else if(cmd_.cmp_word(0, "d")) {
					opr = OPR::DUMP;
				} else if(cmd_.cmp_word(0, "read")) {
					opr = OPR::READ;
				} else if(cmd_.cmp_word(0, "r")) {
					opr = OPR::READ;
				} else if(cmd_.cmp_word(0, "write")) {
					opr = OPR::WRITE;
				} else if(cmd_.cmp_word(0, "w")) {
					opr = OPR::WRITE;
				} else if(cmd_.cmp_word(0, "bus")) {
					opr = OPR::BUS;
				} else if(cmd_.cmp_word(0, "sym")) {
					opr = OPR::SYM;
				} else if(cmd_.cmp_word(0, "list")) {
					opr = OPR::LIST;
				}
			}
			if(opr == OPR::NONE) {
				char tmp[256];
				cmd_.get_word(0, tmp, sizeof(tmp));
				utils::format("Monitor command: '%s' ?\n") % tmp;
				return;
			}

			uint32_t n = 1;
			uint32_t org = address_;
			uint32_t end = address_ + 16 - step_();
			uint32_t m = 0;
			while(n < cmdn) {
				char tmp[256];
				cmd_.get_word(n, tmp, sizeof(tmp));
				uint32_t v = 0;
				if((utils::input("%x", tmp) % v).status()) {
					if(m == 0) {
						org = v;
						end = v + 16;
						++m;
					} else {
						if(m >= 2) {
							org = end;
						}
						end = v;
						++m;
					}
					if(opr == OPR::READ) {
						v &= mask_();
						read_(v);
						address_ = v;
						address_ += step_();
					} else if(m >= 2) {
						if(opr == OPR::SYM) {
							if(sym_cnt_ < SYM_MAX) {
								sym_adr_[sym_cnt_] = org;
								sym_str_[sym_cnt_] = tmp;
								++sym_cnt_;
							}
						} else if(opr == OPR::WRITE) {
							wr_(org, v);
							org += step_();
						}
					}
				} else {
					utils::format("Value: '%s' ?\n") % tmp;
					return;
				}
				++n;
			}
			switch(opr) {
			case OPR::DUMP:
				if(org > end) {
					end = org + 16;
				}
				if((end & 0xf) != 0xf) {
					end |= 0xf;
				}
				dump_(org, end);
				address_ = end + step_();
				break;
			case OPR::READ:
				if(cmdn == 1) {
					read_(address_);
					address_ += step_();
				}
				break;
			case OPR::WRITE:
				if(cmdn == 1) {
					utils::format("Write param fail.\n");
				}
				break;
			case OPR::BUS:
				if(org == 1) b_width_ = B_WIDTH::BYTE;
				else if(org == 2) b_width_ = B_WIDTH::WORD;
				else if(org == 4) b_width_ = B_WIDTH::LONG;
				else { 
					utils::format("Bus width fail: %x\n") % org;
				}
				break;
			case OPR::LIST:
				if(cmdn == 1) {
					list_();
				}
				break;
			default:
				break;
			}
		}
	};
}
