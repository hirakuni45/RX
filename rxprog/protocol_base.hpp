#pragma once
//=========================================================================//
/*!	@file
	@brief	RX マイコン、プロトコル・ベース・クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "rs232c_io.hpp"
#include "rx_protocol.hpp"
#include <vector>
#include <boost/format.hpp>

namespace rx {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	プロトコル・ベース
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct protocol_base {

		utils::rs232c_io	rs232c_;

		bool				verbose_;
		bool				connection_;
		bool				enable_id_;
		bool				pe_turn_on_;

		uint8_t				last_error_;

		protocol::devices		devices_;
		protocol::clock_modes	clock_modes_;
		uint8_t					clock_num_;
		protocol::multipliers	multipliers_;
		protocol::frequencies	frequencies_;
		protocol::areas			boot_areas_;
		protocol::areas			areas_;

		protocol::device_type	device_type_;

		uint32_t			system_clock_;
		uint32_t			device_clock_;
		uint32_t	   		baud_speed_;
		speed_t				baud_rate_;


		static uint32_t get32_(const uint8_t* p) noexcept
		{
			uint32_t v;
			v  = p[0];
			v |= p[1] << 8;
			v |= p[2] << 16;
			v |= p[3] << 24;
			return v;
		}


		static uint32_t get16_big_(const uint8_t* p) noexcept
		{
			uint32_t v;
			v  = p[1];
			v |= p[0] << 8;
			return v;
		}


		static uint32_t get32_big_(const uint8_t* p) noexcept
		{
			uint32_t v;
			v  = p[3];
			v |= p[2] << 8;
			v |= p[1] << 16;
			v |= p[0] << 24;
			return v;
		}


		static void put16_big_(uint8_t* p, uint32_t val) noexcept
		{
			p[0] = (val >> 8) & 0xff;
			p[1] = val & 0xff;
		}


		static void put32_big_(uint8_t* p, uint32_t val) noexcept
		{
			p[0] = (val >> 24) & 0xff;
			p[1] = (val >> 16) & 0xff;
			p[2] = (val >> 8) & 0xff;
			p[3] =  val & 0xff;
		}


		static uint8_t sum_(const uint8_t* buff, uint32_t len) noexcept
		{
			uint16_t sum = 0;
			for(uint32_t i = 0; i < len; ++i) {
				sum += *buff++;
			}
			return 0x100 - sum;
		}


		static std::string out_section_(uint32_t n, uint32_t num) noexcept
		{
			return (boost::format("#%02d/%02d: ") % n % num).str();
		}


		bool command1_(uint8_t cmd) noexcept
		{
			bool f = rs232c_.send(static_cast<char>(cmd));
			rs232c_.sync_send();
			return f;
		}


		bool read_(void* buff, uint32_t len, const timeval& tv) noexcept
		{
			return rs232c_.recv(buff, len, tv) == len;
		}


		bool read_(void* buff, uint32_t len) noexcept
		{
			timeval tv;
			tv.tv_sec  = 5;
			tv.tv_usec = 0;
			return rs232c_.recv(buff, len, tv) == len;
		}


		bool write_(const void* buff, uint32_t len) noexcept
		{
			uint32_t wr = rs232c_.send(buff, len);
			rs232c_.sync_send();
			return wr == len;
		}


		bool com_(uint8_t soh, uint8_t cmd, uint8_t ext, const uint8_t* src = nullptr, uint32_t len = 0) noexcept
		{
			uint8_t tmp[1 + 2 + 1 + len + 1 + 1];
			tmp[0] = soh;
			put16_big_(&tmp[1], 1 + len);
			tmp[3] = cmd;
			if(len > 0) {
				std::memcpy(&tmp[4], src, len);
			}
			tmp[4 + len] = sum_(&tmp[1], 3 + len);
			tmp[4 + len + 1] = ext;
			uint32_t l = rs232c_.send(tmp, sizeof(tmp));
			rs232c_.sync_send();
			return l == sizeof(tmp);
		}


		bool command_(uint8_t cmd, const uint8_t* src = nullptr, uint32_t len = 0) noexcept
		{
			return com_(0x01, cmd, 0x03, src, len);
		}


		bool status_sub_(uint8_t* dst) noexcept
		{
			if(!read_(dst, 4)) {
				return false;
			}
			if(dst[0] != 0x81) {
				return false;
			}
			auto l = get16_big_(&dst[1]);
			if(l == 1 || l == 2) ;
			else {
				return false;
			}
			--l;
			if(!read_(&dst[4], l + 2)) {
				return false;
			}
			auto sum = sum_(&dst[1], 3 + l);
			if(sum != dst[4 + l]) {
				return false;
			}
			if(dst[4 + l + 1] != 0x03) {
				return false;
			}
			return true;
		}


		bool status_(uint8_t res) noexcept
		{
			uint8_t tmp[4 + 1 + 1 + 1];

			if(!status_sub_(tmp)) {
				return false;
			}

			return tmp[3] == res;
		}


		bool response_(uint8_t& res, uint8_t& err) noexcept
		{
			uint8_t tmp[4 + 1 + 1 + 1];

			if(!status_sub_(tmp)) {
				return false;
			}
			res = tmp[3];
			err = tmp[4];
			return true;
		}


		bool status_back_(uint8_t res) noexcept
		{
			uint8_t tmp[4 + 1 + 1 + 1];

			if(!status_sub_(tmp)) {
				return false;
			}

			if(tmp[3] != res) {
				return false;
			}

			if(!write_(tmp, sizeof(tmp))) {
				return false;
			}
			return true;
		}


		bool status_data_(uint8_t res, uint8_t* dst, uint32_t len) noexcept
		{
			uint8_t tmp[4 + len + 2];
			if(!read_(tmp, 4)) {
				return false;
			}
			if(tmp[0] != 0x81) {
				return false;
			}
			if(tmp[3] != res) {
				return false;
			}
			auto l = get16_big_(&tmp[1]);
			if(l != (len + 1)) {
				return false;
			}
			if(!read_(&tmp[4], len + 2)) {
				return false;
			}
			auto sum = sum_(&tmp[1], len + 3);
			if(sum != tmp[4 + len]) {
				return false;
			}
			if(len > 0) {
				std::memcpy(dst, &tmp[4], len);
			}
			return true;
		}


		void dump_status_() noexcept
		{
			uint8_t tmp[4 + 1024 + 2];
			if(!read_(tmp, 4)) {
				return;
			}
			auto l = get16_big_(&tmp[1]);
			if(!read_(&tmp[4], l + 1)) {
				return;
			}

			std::cout << boost::format("SOD: %02X") % static_cast<uint32_t>(tmp[0]) << std::endl;
			std::cout << boost::format("LEN: %d") % l << std::endl;
			std::cout << boost::format("RES: %02X") % static_cast<uint32_t>(tmp[3]) << std::endl;
			--l;
			if(l > 0) std::cout << "Dat: ";
			for(uint32_t i = 0; i < l; ++i) {
				boost::format(" %02X,") % static_cast<uint32_t>(tmp[4 + i]);
			}
			if(l > 0) std::cout << std::endl;
			std::cout << boost::format("SUM: %02X") % static_cast<uint32_t>(tmp[4 + l]) << std::endl;
			std::cout << boost::format("EXT: %02X") % static_cast<uint32_t>(tmp[4 + l + 1]) << std::endl;
		}


		enum class BLANK_STATE {
			ERROR,
			BLANK_OK,
			BLANK_NG
		};


		enum class RX_GROUP {
			RX2xx,
			RX6xx
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		protocol_base() noexcept :
			rs232c_(),
			verbose_(false), connection_(false), enable_id_(false), pe_turn_on_(false),
			last_error_(0),
			devices_(), clock_modes_(), clock_num_(0), multipliers_(), frequencies_(),
			boot_areas_(), areas_(),
			device_type_(),
			system_clock_(0), device_clock_(0), baud_speed_(0), baud_rate_(B9600)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@param[in]	path	シリアルデバイスパス
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool start(const std::string& path) noexcept
		{
			if(!rs232c_.open(path, B9600)) {
				std::cerr << boost::format("Can't open '%s'") % path << std::endl;
				return false;
			}
			if(!rs232c_.enable_RTS(false)) {
				std::cerr << boost::format("Can't enable RTS") << std::endl;
				return false;
			}
			if(!rs232c_.enable_DTR(false)) {
				std::cerr << boost::format("Can't enable DTR") << std::endl;
				return false;
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	コネクションの確立（start が成功したら呼ぶ）
			@param[in]	id	コネクション確立 ID
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool connection(uint8_t id) noexcept
		{
			bool ok = false;
			for(int i = 0; i < 30; ++i) {
				if(!command1_(0x00)) {
					return false;
				}
				timeval tv;
				tv.tv_sec  = 0;
				tv.tv_usec = 10000;  // 10ms
				int ch = rs232c_.recv(tv);
				if(ch == 0x00) {
					ok =  true;
					break;
				}
			}
			if(!ok) return false;

			if(!command1_(0x55)) {
				return false;
			}

			uint8_t tmp[1];
			if(!read_(tmp, 1)) {
				return false;
			}
			if(tmp[0] == 0xff) {
				return false;
			}
			if(tmp[0] != id) {
				return false;
			}

			connection_ = true;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ID コードチェック @n
					・プロトコルは RX140 の仕様
			@param[in]	id	制御コード + IDコード1～IDコード15
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool check_id_code(uint8_t id[16]) noexcept
		{
			uint8_t tmp[2+16+1];

			tmp[0] = 0x60;
			tmp[1] = 16;
			for(int i = 0; i < 16; ++i) tmp[2+i] = id[i];
			tmp[2+16] = sum_(tmp, 2 + 16);
			if(!write_(tmp, 2 + 16 + 1)) {
				return false;
			}

			if(!read_(tmp, 1)) {
				return false;
			}
			if(tmp[0] == 0x06) {
				return true;
			} else if(tmp[0] == 0xE0) {
				if(!read_(tmp, 1)) {
					return false;
				}
				if(tmp[0] == 0x11) {
					// sum error
				} else if(tmp[0] == 0x61) {
					// ID コード不一致
				} else if(tmp[0] == 63) {
					// ID コード不一致かつイレーズエラー
				}
				return false;
			}
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	サポートデバイス問い合わせ（connection が成功したら呼ぶ） @n
					・RX220, RX231, RX24T, RX62x, RX63x
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_device() noexcept
		{
			if(!connection_) return false;

			if(!command1_(0x20)) {
				std::cerr << "(Inquiry Device) command error." << std::endl;
				return false;
			}
			uint8_t head[3];
			// head[0]: 0x30
			// head[1]: サイズ
			// head[2]: デバイス数
			if(!read_(head, 3)) {
				std::cerr << std::endl << "(InquiryDevice) Read head error." << std::endl;
				return false;
			}
			if(head[0] != 0x30) {
				std::cerr << std::endl << "(InquiryDevice) Read respons error." << std::endl;
				return false;
			}

			uint32_t total = head[1];  // デバイス数、文字数、デバイスコード、シリーズ名のデータの総バイト数
			// デバイス数の分があるので、残り、SUM までのバイト数
//			std::cout << boost::format("Size: %d") % total << std::endl;
//			std::cout << boost::format("Num:  %d") % static_cast<int>(head[2]) << std::endl;

			uint8_t tmp[total];
			if(!read_(tmp, total)) {
				std::cerr << std::endl << "(InquiryDevice) Read body error." << std::endl;
				return false;
			}

			uint8_t sum = sum_(tmp, total - 1);
			sum -= head[0] + head[1] + head[2];
			if(sum != tmp[total - 1]) { 
				std::cerr << std::endl << boost::format("(InquiryDevice) Sum match error. (0x%02X : 0x%02X)")
					% static_cast<uint16_t>(sum) % static_cast<uint16_t>(tmp[total - 1]);
				std::cerr << std::endl;
				return false;
			}

			const uint8_t* p = tmp;
			for(int n = 0; n < head[2]; ++n) {
				protocol::device d;
				auto l = *p++;
				d.code_ = get32_(p);
				p += 4;
				for(uint8_t i = 0; i < (l - 4); ++i) {
					d.name_ += static_cast<char>(*p);
					++p;
				}
				devices_.push_back(d);
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	デバイスを取得
			@return デバイス
		*/
		//-----------------------------------------------------------------//
		const auto& get_device() const noexcept { return devices_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	デバイスを選択
			@param[in]	code	デバイス・コード
			@param[in]	resc	レスポンス・コード
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool select_device(uint32_t code, uint8_t resc) noexcept
		{
			if(!connection_) return false;

			uint8_t tmp[7];
			tmp[0] = 0x10;
			tmp[1] = 4;
			tmp[2] = code & 0xff;
			tmp[3] = (code >> 8) & 0xff;
			tmp[4] = (code >> 16) & 0xff;
			tmp[5] = (code >> 24) & 0xff;
			tmp[6] = sum_(tmp, 6);
			if(!write_(tmp, 7)) {
				return false;
			}
			uint8_t res[1];
			if(!read_(res, 1)) {  // レスポンス取得
				return false;
			}
			if(res[0] == resc) {
				return true;
			} else if(res[0] == 0x90) {  // エラーの場合
				read_(res, 1);  // エラーコード
				std::cerr << std::endl << boost::format("(SelectDevice) error: 0x%02X") % static_cast<uint32_t>(res[0]) << std::endl;
				last_error_ = res[0];
			} else {
				std::cerr << std::endl << "(SelectDevice) response error." << std::endl;
			}
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	クロック・モード問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_clock_mode() noexcept
		{
			if(!connection_) return false;

			if(!command1_(0x21)) {
				return false;
			}

			uint8_t head[2];
			if(!read_(head, 2)) {
				return false;
			}
			if(head[0] != 0x31) {
				return false;
			}
			uint8_t tmp[256];
			if(!read_(tmp, head[1] + 1)) {
				return false;
			}
			for(uint8_t i = 0; i < head[1]; ++i) {
				rx::protocol::clock_mode cm;
				cm.type_ = tmp[i];
				clock_modes_.push_back(cm);
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	デバイスを取得
			@return デバイス
		*/
		//-----------------------------------------------------------------//
		const auto& get_clock_mode() const noexcept { return clock_modes_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	クロック・モードを選択
			@param[in]	cm	クロック・モード
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool select_clock_mode(const rx::protocol::clock_mode& cm) noexcept
		{
			if(!connection_) return false;

			uint8_t tmp[4];
			tmp[0] = 0x11;
			tmp[1] = 1;
			tmp[2] = cm.type_;
			tmp[3] = sum_(tmp, 3);
			if(!write_(tmp, 4)) {
				return false;
			}
			uint8_t res[1];
			if(!read_(res, 1)) {
				return false;
			}
			if(res[0] == 0x06) {
				return true;
			} else if(res[0] == 0x91) {  // エラーレスポンス
				read_(res, 1);
				last_error_ = res[0];
			}
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	逓倍比問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_multiplier() noexcept
		{
			if(!connection_) return false;

			if(!command1_(0x22)) {
				return false;
			}

			uint8_t head[3];
			if(!read_(head, 3)) {
				return false;
			}
			if(head[0] != 0x32) {
				return false;
			}
			uint8_t tmp[256];
			if(!read_(tmp, head[1])) {
				return false;
			}

			clock_num_ = head[2];
			uint8_t i = 0;
			const uint8_t* p = tmp;
			while(i < (head[1] - 1)) {
				auto n = *p++;
				rx::protocol::multiplier mp;
				mp.list_.resize(n);
				for(uint8_t j = 0; j < n; ++j) {
					mp.list_[j] = *p++;
				}
				multipliers_.push_back(mp);
				i += n + 1;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	逓倍比を取得
			@return 逓倍比
		*/
		//-----------------------------------------------------------------//
		const auto& get_multiplier() const noexcept { return multipliers_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	動作周波数問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_frequency() noexcept
		{
			if(!connection_) return false;

			if(!command1_(0x23)) {
				return false;
			}

			uint8_t head[3];
			if(!read_(head, 3)) {
				return false;
			}
			if(head[0] != 0x33) {
				return false;
			}
			uint8_t tmp[256];
			if(!read_(tmp, head[1])) {
				return false;
			}

			auto num = head[2];
			const uint8_t* p = tmp;
			for(uint8_t i = 0; i < num; ++i) {
				rx::protocol::frequency q;
				q.min_ = static_cast<uint16_t>(p[1]) | (static_cast<uint16_t>(p[0]) << 8);
				p += 2;
				q.max_ = static_cast<uint16_t>(p[1]) | (static_cast<uint16_t>(p[0]) << 8);
				p += 2;
//				std::cout << (int)q.min_ << std::endl;
//				std::cout << (int)q.max_ << std::endl;
				frequencies_.push_back(q);
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	動作周波数を取得
			@return 動作周波数
		*/
		//-----------------------------------------------------------------//
		const rx::protocol::frequencies& get_frequency() const noexcept { return frequencies_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	新ビットレート選択（レガシー版）
			@param[in]	rx		マイコン設定
			@param[in]	spped	シリアル速度
			@param[in]	limit	シリアル速度制限
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool change_speed_legacy(const rx::protocol::rx_t& rx, uint32_t speed, uint32_t limit) noexcept
		{
			if(!connection_) return false;

			if(speed > limit) {
				speed = limit;
			}

			uint32_t nbr;
			switch(speed) {
			case 19200:
				nbr = 192;
				baud_rate_ = B19200;
				break;
			case 38400:
				nbr = 384;
				baud_rate_ = B38400;
				break;
			case 57600:
				nbr = 576;
				baud_rate_ = B57600;
				break;
			case 115200:
				nbr = 1152;
				baud_rate_ = B115200;
				break;
			case 230400:
				nbr = 2304;
				baud_rate_ = B230400;
				break;
			default:
				std::cerr << "(Change speed legacy) Invalid baud rate error." << std::endl;
				return false;
			}
			baud_speed_ = speed; 

			uint8_t cmd[10];
			cmd[0] = 0x3f;
			cmd[1] = 7;
			put16_big_(&cmd[2], nbr);
			put16_big_(&cmd[4], rx.master_);
			cmd[6] = 0x02;  // クロック数（システムクロックと周辺クロックの2種類）
			cmd[7] = rx.iclk_multi_;
			cmd[8] = rx.pclk_multi_;
			cmd[9] = sum_(cmd, 9);
			if(!write_(cmd, 10)) {
				std::cerr << "(Change speed legacy) Write command error." << std::endl;
				return false;
			}
			uint8_t res[1];
			if(!read_(res, 1)) {
				std::cerr << "(Change speed legacy) Read respons error." << std::endl;
				return false;
			}
			if(res[0] == 0xbf) {  // エラーレスポンス
				read_(res, 1);
				// 0x11: サムチェックエラー
				// 0x24: ビットレート選択不可エラー
				// 0x25: 入力周波数エラー
				// 0x26: 逓倍エラー
				// 0x27: 動作周波数エラー
				last_error_ = res[0];  // エラーコード
				std::cerr << boost::format("(Change speed legacy) Respons error. (0x%02X)")
					% static_cast<uint16_t>(res[0]) << std::endl;
				if(res[0] == 0x24) {
					std::cerr << boost::format("(Change speed legacy) Select error: %u") % speed << std::endl;
				} else {
					std::cerr << boost::format("(Change speed legacy) Respons error. (0x%02X)")
						% static_cast<uint16_t>(res[0]) << std::endl;
				}
				return false;
			} else if(res[0] != 0x06) {  // 正常レスポンス
				return false;
			}

			usleep(25000);	// 25[ms]

			if(!rs232c_.change_speed(baud_rate_)) {
				std::cerr << "(Change speed legacy) Serial speed change error." << std::endl;
				return false;
			}

			if(!command1_(0x06)) {  // 確認
				return false;
			}
			if(!read_(res, 1)) {
				return false;
			}
			if(res[0] != 0x06) {  // レスポンス
				return false;
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ユーザーブートマット情報問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_boot_area() noexcept
		{
			if(!connection_) return false;

			if(!command1_(0x24)) {
				return false;
			}

			uint8_t head[3];
			if(!read_(head, 3)) {
				return false;
			}
			if(head[0] != 0x34) {
				return false;
			}
			uint8_t tmp[256];
			if(!read_(tmp, head[1])) {
				return false;
			}

			auto num = head[2];
			const uint8_t* p = tmp;
			for(uint8_t i = 0; i < num; ++i) {
				protocol::area a;
				a.org_ = get32_big_(p);
				p += 4;
				a.end_ = get32_big_(p);
				p += 4;
				boot_areas_.push_back(a);
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ユーザー・ブート領域を取得
			@return ユーザー・ブート領域
		*/
		//-----------------------------------------------------------------//
		const auto& get_boot_area() const noexcept { return boot_areas_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ユーザーマット領域問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_area() noexcept
		{
			if(!connection_) return false;

			if(!command1_(0x25)) {
				return false;
			}

			uint8_t tmp[256];
			if(!read_(tmp, 2)) {
				return false;
			}
			if(tmp[0] != 0x35) {
				return false;
			}
			uint32_t total = tmp[1] + 1;
			if(!read_(&tmp[2], total)) {
				return false;
			}

			auto sum = sum_(tmp, tmp[1] + 2);
			if(sum != tmp[2 + total - 1]) {
				return false;
			}

			auto num = tmp[2];
			const uint8_t* p = &tmp[3];
			for(uint8_t i = 0; i < num; ++i) {
				rx::protocol::area a;
				a.org_ = get32_big_(p);
				p += 4;
				a.end_ = get32_big_(p);
				p += 4;
				areas_.push_back(a);
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ユーザー領域を取得
			@return ユーザー領域
		*/
		//-----------------------------------------------------------------//
		const auto& get_area() const { return areas_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	デバイス種別取得（connection が成功したら呼ぶ） @n
					・RX26T、RX64M, RX65x, RX66T, RX72T, RX71M
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_device_type() noexcept
		{
			if(!connection_) return false;

			if(!command_(0x38)) {
				return false;
			}

			if(!status_back_(0x38)) {
				return false;
			}

			uint8_t tmp[24];
			if(!status_data_(0x38, tmp, sizeof(tmp))) {
				return false;
			}

			std::memcpy(device_type_.TYP, &tmp[0], 8);
			device_type_.OSA = get32_big_(&tmp[8]);
			device_type_.OSI = get32_big_(&tmp[8 + 4]);
			device_type_.CPA = get32_big_(&tmp[8 + 4 + 4]);
			device_type_.CPI = get32_big_(&tmp[8 + 4 + 4 + 4]);

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	デバイス種別を取得
			@return デバイス
		*/
		//-----------------------------------------------------------------//
		const auto& get_device_type() const noexcept { return device_type_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	エンディアン通知コマンド
			@param[in]	endian ０ならビッグ、１ならリトル
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool select_endian(uint8_t endian) noexcept
		{
			if(!connection_) return false;

			uint8_t tmp[1];
			tmp[0] = endian;
			if(!command_(0x36, tmp, 1)) {
				return false;
			}

			if(!status_(0x36)) {
				return false;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	周波数設定コマンド
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool select_frequency() noexcept
		{
			if(!connection_) return false;

			uint8_t tmp[8];
			put32_big_(&tmp[0],  16'000'000);
			put32_big_(&tmp[4], 120'000'000);
			if(!command_(0x32, tmp, sizeof(tmp))) {
				return false;
			}

			if(!status_back_(0x32)) {
				return false;
			}

			if(!status_data_(0x32, tmp, sizeof(tmp))) {
				return false;
			}

			system_clock_ = get32_big_(&tmp[0]);
			device_clock_ = get32_big_(&tmp[4]);

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	新ビットレート選択
			@param[in]	rx		マイコン設定
			@param[in]	spped	シリアル速度
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool change_speed(const protocol::rx_t& rx, uint32_t speed) noexcept
		{
			if(!connection_) return false;

			switch(speed) {
			case 19200:
				baud_rate_ = B19200;
				break;
			case 38400:
				baud_rate_ = B38400;
				break;
			case 57600:
				baud_rate_ = B57600;
				break;
			case 115200:
				baud_rate_ = B115200;
				break;
			case 230400:
				baud_rate_ = B230400;
				break;
#ifdef WIN32
			case 460800:
				baud_rate_ = B460800;
				break;
			case 500000:
				baud_rate_ = B500000;
				break;
			case 576000:
				baud_rate_ = B576000;
				break;
#endif
			default:
				return false;
			}
			baud_speed_ = speed; 

			uint8_t tmp[4];
			put32_big_(&tmp[0], speed);
			if(!command_(0x34, tmp, sizeof(tmp))) {
				return false;
			}

			if(!status_(0x34)) {
				return false;
			}

			usleep(1000);	// 1[ms]

			if(!rs232c_.change_speed(baud_rate_)) {
				return false;
			}

			// 同期コマンド
			if(!command_(0x00)) {
				return false;
			}
			if(!status_(0x00)) {
				return false;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ID 認証モード取得コマンド
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_id() noexcept
		{

			if(!connection_) return false;

			if(!command_(0x2C)) {
				return false;
			}

			if(!status_back_(0x2C)) {
				return false;
			}

			uint8_t tmp[1];
			if(!status_data_(0x2C, tmp, sizeof(tmp))) {
				return false;
			}

			if(tmp[0] == 0x00) enable_id_ = true;
			else if(tmp[0] == 0xFF) enable_id_ = false;
			else {
				return false;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	接続 (RX26T, RX64M, RX65x, RX66T, RX72T, RX71M)
			@param[in]	path	シリアルデバイスパス
			@param[in]	brate	ボーレート
			@param[in]	cid		コネクション ID
			@param[in]	rx		CPU 設定
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool bind_RX6xx(const std::string& path, uint32_t brate, uint8_t cid, const rx::protocol::rx_t& rx) noexcept
		{
			verbose_ = rx.verbose_;

			if(!start(path)) {
				std::cerr << "Can't open path: '" << path << "'" << std::endl;
				return false;
			}

			// コネクション
			if(!connection(cid)) {
				std::cerr << "Can't connection." << std::endl;
				return false;
			}
			if(verbose_) {
				std::cout << "# Connection OK." << std::endl;
			}

			// デバイスタイプ取得
			{
				if(!inquiry_device_type()) {
					std::cerr << "Inquiry device type error." << std::endl;
					return false;
				}
				if(verbose_) {
					auto a = get_device_type();
					a.info(out_section_(1, 1));
				}
			}

			// エンディアン通知コマンド
			{
				uint8_t endian = 0x01;
				if(!select_endian(endian)) {
					std::cerr << "Select endian error." << std::endl;
				}
				if(verbose_) {
					std::cout << out_section_(1, 1) << "Endian is "
						<< (endian != 0 ? "little." : "big.") << std::endl;
				}
			}

			// 周波数設定コマンド
			{
				if(!select_frequency()) {
					std::cerr << "Select frequency error." << std::endl;
				}
				if(verbose_) {
					auto s = out_section_(1, 1);
					std::cout << s << boost::format("System clock: %d") % system_clock_ << std::endl; 
					std::cout << s << boost::format("Device clock: %d") % device_clock_ << std::endl; 
				}
			}

			// ボーレート変更
			{
				if(!change_speed(rx, brate)) {
					std::cerr << "Can't change speed." << std::endl;
					return false;
				}
				if(verbose_) {
					auto sect = out_section_(1, 1);
					std::cout << sect << boost::format("Change baud rate: %d") % brate << std::endl;
				}
			}

			// ID 認証確認
			{
				if(!inquiry_id()) {
					std::cerr << "Inquiry ID error." << std::endl;
					return false;
				}
				if(verbose_) {
					auto sect = out_section_(1, 1);
					std::cout << sect
						<< boost::format("ID: %s") % (enable_id_ ? "Enable" : "Disable") << std::endl;
				}
			}

			// ID 認証が有効なら、ID コードチェックを行う
			if(enable_id_) {
			}

			pe_turn_on_ = true;			

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ユーザー領域、ブランクチェック
			@return ブランクチェック後の状態を返す 
		*/
		//-----------------------------------------------------------------//
		BLANK_STATE user_blank_check() noexcept
		{
			if(!command1_(0x4D)) {
				return BLANK_STATE::ERROR;
			}
			uint8_t tmp[1];
			if(!read_(tmp, 1)) {  // レスポンス
				return BLANK_STATE::ERROR;
			}
			if(tmp[0] == 0x06) {
				return BLANK_STATE::BLANK_OK;
			} else if(tmp[0] == 0xCD) {
				if(!read_(tmp, 1)) {  // エラーコード
					return BLANK_STATE::ERROR;
				} else if(tmp[0] == 0x52) {
					return BLANK_STATE::BLANK_NG;
				} else {
					return BLANK_STATE::ERROR;
				}
			} else {
				return BLANK_STATE::ERROR;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	消去選択
			@param[in]	grp		RX マイコン・グループ型
			@param[in]	ena		消去選択を解除する場合「false」
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool enable_erase_select(RX_GROUP grp, bool ena = true) noexcept
		{
			if(ena) {
				if(!command1_(0x48)) {  // 消去選択
					return false;
				}
				uint8_t tmp[1];
				if(!read_(tmp, 1)) {  // レスポンス
					return false;
				}
				if(tmp[0] != 0x06) {
					return false;
				}
				return true;
			} else {
				if(grp == RX_GROUP::RX2xx) {
					uint8_t tmp[7];
					tmp[0] = 0x59;
					tmp[1] = 0x04;
					tmp[2] = 0xff;
					tmp[3] = 0xff;
					tmp[4] = 0xff;
					tmp[5] = 0xff;
					tmp[6] = 0xa7;
					if(!write_(tmp, 7)) {
						return false;
					}

					if(!read_(tmp, 1)) {  // レスポンス
						return false;
					}
					if(tmp[0] == 0x06) {
						return true;
					} else if(tmp[0] == 0xD9) {
						if(!read_(tmp, 1)) {  // エラーコード
							return false;
						}
						// 0x11: サムチェックエラー
						last_error_ = tmp[0];  // エラーコード
					}
					return false;
				} else if(grp == RX_GROUP::RX6xx) {
					uint8_t tmp[4];
					tmp[0] = 0x58;
					tmp[1] = 0x01;  // size 固定値１
					tmp[2] = 0xff;
					tmp[3] = sum_(tmp, 3);
					if(!write_(tmp, 4)) {
						return false;
					}

					if(!read_(tmp, 1)) {  // レスポンス
						return false;
					}
					if(tmp[0] == 0x06) {
						return true;
					} else if(tmp[0] == 0xD8) {
						if(!read_(tmp, 1)) {  // エラーコード
							return false;
						}
						// 0x11: サムチェックエラー
						last_error_ = tmp[0];  // エラーコード
					}
					return false;
				} else {
					return false;
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	クローズ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool close() noexcept
		{
			return rs232c_.close();
		}
	};
}
