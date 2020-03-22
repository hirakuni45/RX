#pragma once
//=====================================================================//
/*!	@file
	@brief	モニター・クラス
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>
#include <cstring>
#include "common/command.hpp"
#include "common/format.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  モニター・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class monitor {

		command<256>	command_;

		uint32_t		dump_org_ = 0;
		uint32_t		mem_org_ = 0;

		uint32_t hex_(const char* p, char fch = 0) {
			uint32_t val = 0;
			char ch;
			while((ch = *p++) != 0 && ch != fch) {
				uint8_t n = 0;
				if(ch >= '0' && ch <= '9') {
					n = ch - '0';
				} else if(ch >= 'a' && ch <= 'f') {
					n = ch - 'a' + 10;
				} else if(ch >= 'A' && ch <= 'F') {
					n = ch - 'A' + 10;
				} else {
					break;
				}
				val <<= 4;
				val |= n;
			}
			return val;
		}


		void mem_dump_(uint32_t org, uint32_t fin) const {
			if(org >= fin) {
				return;
			}
			auto len = fin - org;
			uint32_t n = 0;
			for(uint32_t i = 0; i < len; ++i) {
				if(n == 0) {
					format("%08X:") % static_cast<unsigned int>(org);
				}
				format(" %02X") % static_cast<unsigned int>(device::rd8_(org + i));
				++n;
				if(n >= 16) {
					n = 0;
					sci_putch('\n');
				}
			}	
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		monitor() { }


		//-----------------------------------------------------------------//
		/*!
			@brief  初期化
		*/
		//-----------------------------------------------------------------//
		void initialize() {
			sci_puts("RX63T start\n");
			sci_puts("Chager\n");
			sci_puts("\n");
			command_.set_prompt("% ");
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
		*/
		//-----------------------------------------------------------------//
		void service() {
			if(!command_.service()) {
				return;
			}

			auto num = command_.get_words();
			if(num > 0) {
				char word[16];
				uint32_t value[2] = { 0, 0 };
				if(num >= 2) {
					if(!command_.get_word(1, sizeof(word), word)) {
						return;
					}
					value[0] = hex_(word);
				}
				if(num >= 3) {
					if(!command_.get_word(2, sizeof(word), word)) {
						return;
					}
					value[1] = hex_(word);
				}

				if(!command_.get_word(0, sizeof(word), word)) {
					return;
				}

				if(std::strcmp(word, "d") == 0) {
					if(num == 1) {
						value[0] = dump_org_;
						value[1] = dump_org_ + 1;
					} else if(num == 2) {
						value[1] = value[0] + 1;
					}
					mem_dump_(value[0], value[1]);
				} else if(std::strcmp(word, "m") == 0) {

				} else {
					sci_puts("Command error: '");
					sci_puts(word);
					sci_puts("'\n");
				}
			}
		}

	};
}
