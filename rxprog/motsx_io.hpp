#pragma once
//=========================================================================//
/*!	@file
	@brief	モトローラーＳフォーマット入出力 @n
			256 バイト毎に、データ管理を行うので、どのようなロケーションに配置 @n
			されたデータ列であっても、効率良くデータを保持出来る。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <vector>
#include <map>
#include <array>
#include <string>
#include <iomanip>
#include <boost/format.hpp>

#include "file_io.hpp"

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	Motolora S[1-9] Format Encode/Decode クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class motsx_io {
	public:
		static constexpr uint32_t PAGE_MASK = 0xffff'ff00;  ///< Under 256 bytes mask 

		typedef std::array<uint8_t, 256> array;

		struct area_t {
			uint32_t	min_;
			uint32_t	max_;
			area_t(uint32_t min = 0xffff'ffff, uint32_t max = 0) noexcept : min_(min), max_(max) { } 			
		};
		typedef std::vector<area_t> areas;

		struct array_t {
			area_t	area_;
			array	array_;

			array_t() noexcept : area_(), array_() { array_.fill(0xff); }

			bool get(uint32_t adr, uint8_t& data) noexcept {
				if(area_.min_ <= adr && adr <= area_.max_) {
					data = array_[adr & 0xff];
					return true;
				} else {
					return false;
				}
			}

			void set(uint32_t adr, uint8_t data) noexcept {
				if(area_.min_ > adr) area_.min_ = adr;
				if(area_.max_ < adr) area_.max_ = adr;
				array_[adr & 0xff] = data;
			}
		};

	private:
		area_t		area_;
		uint32_t	exec_;

		typedef std::map<uint32_t, array_t>	memory_map;

		memory_map	memory_map_;

		array		fill_array_;

		bool read_byte_(uint32_t address, uint8_t& val) noexcept
		{
			auto base = address & PAGE_MASK;
			memory_map::const_iterator cit = memory_map_.find(base);
			if(cit == memory_map_.end()) {
				return false;
			} else {
				auto t = cit->second;
				return t.get(address, val);
			}
		}

		void write_byte_(uint32_t address, uint8_t val) noexcept
		{
			auto base = address & PAGE_MASK;
			memory_map::iterator it = memory_map_.find(base);
			if(it == memory_map_.end()) {
				array_t t;
				t.set(address, val);
				memory_map_.emplace(base, t);
			} else {
				array_t& t = it->second;
				t.set(address, val);
			}
		}


		bool load_(utils::file_io& fio) noexcept
		{
			area_.min_ = 0xffff'ffff;
			area_.max_ = 0x0000'0000;

			uint32_t value = 0;
			uint32_t type = 0;
			uint32_t length = 0;
			uint32_t address = 0;
			uint32_t sum = 0;
			int vcnt = 0;

			bool toend = false;
			int mode = 0;

			while(1) {
				char ch;
				if(!fio.get_char(ch)) {
					break;
				}

			   	if(ch == ' ') {
			   	} else if(ch == 0x0d || ch == 0x0a) {
				   	if(toend) break;
			   	} else if(mode == 0 && ch == 'S') {
			   		mode = 1;
			   		value = vcnt = 0;
			   	} else if(ch >= '0' && ch <= '9') {
			   		value <<= 4;
			   		value |= ch - '0';
			   		++vcnt;
			   	} else if(ch >= 'A' && ch <= 'F') {
			   		value <<= 4;
			   		value |= ch - 'A' + 10;
			   		++vcnt;
			   	} else {
					std::cerr << "S format illegual character: '";
			   		if(ch >= 0x20 && ch <= 0x7f) {
						std::cerr << ch;
			   		} else {
						std::cerr << boost::format("0x%02X") % static_cast<int>(ch);
			   		}
					std::cerr << "'" << std::endl;
			   		return false;
			   	}

			   	if(mode == 1) {		// タイプ取得(16bits)
			   		if(vcnt == 1) {
			   			type = value;
			   			mode = 2;
			   			value = vcnt = 0;
			   		}
			   	} else if(mode == 2) {	// レングス取得(24bits)
			   		if(vcnt == 2) {
			   			length = value;
			   			sum = value;
			   			mode = 3;
			   			value = vcnt = 0;
			   		}
			   	} else if(mode == 3) {	// アドレス取得(32bits)
			   		int alen = 0;
			   		if(type == 0) {
			   			alen = 4;
			   		} else if(type == 1) {
			   			alen = 4;
			   		} else if(type == 2) {
			   			alen = 6;
			   		} else if(type == 3) {
			   			alen = 8;
			   		} else if(type == 5) {
			   			alen = 4;
			   		} else if(type == 7) {
			   			alen = 8;
			   		} else if(type == 8) {
			   			alen = 6;
			   		} else if(type == 9) {
			   			alen = 4;
			   		} else {
			   			return false;
			   		}

			   		if(vcnt == alen) {
			   			address = value;
			   			if(type >= 1 && type <= 3) {
			   				if(area_.min_ > address) area_.min_ = address;
			   			}
			   			alen >>= 1;
			   			length -= alen;
			   			length -= 1;	// SUM の分サイズを引く
			   			while(alen > 0) {
			   				sum += value;
			   				value >>= 8;
			   				--alen;
			   			}
				   		if(type >= 1 && type <= 3) {
				   			mode = 4;
				   		} else if(type >= 7 && type <= 9) {
							exec_ = value;
				   			mode = 5;
				   		} else {
				   			mode = 4;
				   		}
				   		value = vcnt = 0;
				   	}
			   	} else if(mode == 4) {	// データ・レコード
			   		if(vcnt >= 2) {
			   			if(type >= 1 && type <= 3) {
			   				write_byte_(address, value);
			   				if(area_.max_ < address) area_.max_ = address;
			   				++address;
			   			}
			   			sum += value;
			   			value = vcnt = 0;
			   			--length;
			   			if(length == 0) {
			   				mode = 5;
			   			}
			   		}
			   	} else if(mode == 5) {	// SUM
			   		if(vcnt >= 2) {
			   			value &= 0xff;
			   			sum ^= 0xff;
			   			sum &= 0xff;
			   			if(sum != value) {	// SUM エラー
							std::cerr << "S format SUM error: ";
							std::cerr << boost::format("0x%02X -> %02X")
							    % static_cast<int>(value)
								% static_cast<int>(sum)
								<< std::endl;
			   				return false;
			   			} else {
			   				if(type >= 7 && type <= 9) {
			   					toend = true;
			   				}
			   				mode = 0;
			   				value = vcnt = 0;
			   			}
			   		}
			   	}
		   	}
		   	return true;
		}


		bool save_(utils::file_io& fio, const memory_map::value_type& m) noexcept
		{
			const array_t& a = m.second;
			fio.put_char('S');

			uint8_t sum = 0;
			uint32_t len = (a.area_.max_ - a.area_.min_ + 1) * 2;
			std::string adr;
			if(a.area_.max_ <= 0xffff) {
				adr = (boost::format("1%04X") % a.area_.max_).str();
				len += 4;
			} else if(a.area_.max_ <= 0xff'ffff) {
				adr = (boost::format("2%06X") % a.area_.max_).str();
				len += 6;
			} else {
				adr = (boost::format("3%08X") % a.area_.max_).str();
				len += 8;
			}
			len += 2; // for check sum
			fio.put((boost::format("%02X") % len).str());
			fio.put(adr);

			for(uint32_t i = a.area_.min_; i <= a.area_.max_; ++i) {
				uint8_t data = a.array_[i & 255];
				fio.put((boost::format("%02X") % data).str());
				sum += data;
			}

			fio.put((boost::format("%02X") % static_cast<uint32_t>(sum)).str());

			fio.put_char('\n');
			return false;
		}


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		motsx_io() noexcept : area_(), exec_(0x0000'0000)
		{
			fill_array_.fill(0xff);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ロード
			@param[in]	path	ファイルパス
			@return エラー無しなら「true」
		*/
		//-----------------------------------------------------------------//
		bool load(const std::string& path) noexcept
		{
			utils::file_io fio;
			if(!fio.open(path, "rb")) {
				return false;
			}

			memory_map_.clear();

			if(!load_(fio)) {
				return false;
			}

			fio.close();

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	セーブ
			@param[in]	path	ファイルパス
			@return エラー無しなら「true」
		*/
		//-----------------------------------------------------------------//
		bool save(const std::string& path) noexcept
		{
			if(memory_map_.empty()) return false;

			utils::file_io fio;
			if(!fio.open(path, "wb")) {
				return false;
			}

			for(const auto& m : memory_map_) {
				if(!save_(fio, m)) {
					return false;
				}
			}

			fio.close();

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	メモリーの存在確認
			@param[in]	address	アドレス
			@return メモリー存在なら「true」
		*/
		//-----------------------------------------------------------------//
		bool probe(uint32_t address) noexcept
		{
			uint8_t tmp;
			return read_byte_(address, tmp);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	メモリーの読出し
			@param[in]	address	アドレス
			@param[in]	data	データポインター
			@param[in]	len		長さ
			@return 読み出せたバイト数
		*/
		//-----------------------------------------------------------------//
		uint32_t read(uint32_t address, uint8_t* data, uint32_t len) noexcept
		{
			uint32_t cnt = 0;
			for(uint32_t i = 0; i < len; ++i) {
				if(read_byte_(address + i, data[i])) {
					++cnt;
				}
			}
			return cnt;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	メモリーへの書き込み
			@param[in]	address	アドレス
			@param[in]	data	データポインター
			@param[in]	len		長さ
		*/
		//-----------------------------------------------------------------//
		void write(uint32_t address, const uint8_t* data, uint32_t len) noexcept
		{
			for(uint32_t i = 0; i < len; ++i) {
				write_byte_(address + i, data[i]);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	総ページ数の取得
			@return 総ページ数
		*/
		//-----------------------------------------------------------------//
		uint32_t get_total_page() const noexcept
		{
			return memory_map_.size();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	エリア・マップの作成
			@return エリア・マップ
		*/
		//-----------------------------------------------------------------//
		auto create_area_map() const noexcept
		{
			areas as;
			for(const auto& m : memory_map_) {
				if(as.empty()) {
					as.emplace_back(m.second.area_);
				} else {
					if((as.back().max_ + 1) == m.second.area_.min_) {
						as.back().max_ = m.second.area_.max_;
					} else {
						as.emplace_back(m.second.area_);
					}
				}
			}
			return as;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	エリア・マップの表示
			@param[in]	head	追加の文字列
		*/
		//-----------------------------------------------------------------//
		void list_area_map(const std::string& head) const noexcept
		{
			std::cout << head << boost::format("Motolola Sx format load map: (exec: 0x%08X)") % exec_;
			std::cout << std::endl;

			auto as = create_area_map();
			uint32_t total = 0;
			for(const auto& a : as) {
				auto n = a.max_ - a.min_ + 1;
				std::cout << head << boost::format("  0x%08X to 0x%08X (%d bytes)") % a.min_ % a.max_ % n;
				std::cout << std::endl;
				total += n;
			}
			std::cout << head << boost::format("  Total (%d bytes)") % total << std::endl << std::flush;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	エリアの取得
			@return エリア
		*/
		//-----------------------------------------------------------------//
		const area_t& get_area() const noexcept { return area_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	実行アドレスの取得
			@return 実行アドレス
		*/
		//-----------------------------------------------------------------//
		auto get_exec() const noexcept { return exec_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	利用されているページを探す（有効なページ）
			@param[in]	address	アドレス
			@return 有効なページがあれば「true」
		*/
		//-----------------------------------------------------------------//
		bool find_page(uint32_t address) const noexcept
		{
			return memory_map_.find(address & PAGE_MASK) != memory_map_.end();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ページメモリーの参照を取得
			@param[in]	address	ベースとなるアドレス
			@return ページメモリー @n
					無効なページの場合、内部データは全て 0xff となっている。
		*/
		//-----------------------------------------------------------------//
		const array& get_memory(uint32_t address) const noexcept
		{
			const auto cit = memory_map_.find(address & PAGE_MASK);
			if(cit == memory_map_.end()) {
				return fill_array_;
			}
			return cit->second.array_;
		}
	};
}
