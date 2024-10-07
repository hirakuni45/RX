#pragma once
//=========================================================================//
/*!	@file
	@brief	RX621/RX62N プログラミング・プロトコル・クラス @n
			・リセット起動直後のデータマットプロテクト状態 @n
			DFLREk、DFLWEk レジスタ (k=0,1) の初期値が 0000h であるため、 @n
			リセット起動直後のデータマットの読み出し／書き込み／消去は禁止状態です。 
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "protocol_base.hpp"
#include <set>

namespace rx62x {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	RX621/RX62N プログラミング・プロトコル・クラス
				Support device: RX621/RX62N @n
				RX62x はクロック生成ハードウェアーの仕様により、高いボーレートで誤差が大きく、 @n
				ボーレートは、115200 に制限される。
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class protocol : public rx::protocol_base {

		static constexpr uint32_t LIMIT_BAUDRATE = 115200;

		bool				verbose_ = false;

		bool				connection_ = false;

		rx::protocol::devices		devices_;
		rx::protocol::clock_modes	clock_modes_;
		uint8_t						clock_num_ = 0;
		rx::protocol::multipliers	multipliers_;
		rx::protocol::frequencies	frequencies_;
		rx::protocol::areas			boot_area_;
		rx::protocol::areas			area_;
		rx::protocol::areas			blocks_;
		uint32_t					prog_size_ = 0;
//		bool						data_ = false;
//		rx::protocol::areas			data_areas_;
		bool						id_protect_ = false;
		bool						pe_turn_on_ = false;
		bool						erase_select_ = false;
		bool						select_write_area_ = false;

		typedef std::set<uint32_t> ERASE_SET;
		ERASE_SET					erase_set_;

		uint32_t	   				baud_speed_ = 0;
		speed_t						baud_rate_ = B9600;

		uint8_t						last_error_ = 0;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		protocol() noexcept { }


		//-----------------------------------------------------------------//
		/*!
			@brief	接続
			@param[in]	path	シリアルデバイスパス
			@param[in]	brate	ボーレート
			@param[in]	rx		CPU 設定
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool bind(const std::string& path, uint32_t brate, const rx::protocol::rx_t& rx) noexcept
		{
			verbose_ = rx.verbose_;

			if(!start(path)) {
				std::cerr << "Can't open path: '" << path << "'" << std::endl;
				return false;
			}

			// コネクション
			if(!connection()) {
				std::cerr << "Can't connection." << std::endl;
				return false;
			}
			if(verbose_) {
				std::cout << "Connection OK. (RX62x)" << std::endl;
			}

			// サポート・デバイス問い合わせ
			{
				if(!inquiry_device()) {
					std::cerr << "Inquiry device error." << std::endl;
					return false;
				}
				auto as = get_device();
				if(verbose_) {
					int i = 0;
					for(auto a : as) {
						++i;
						a.info(out_section_(i, as.size()));
					}
				}
				// デバイス選択
				if(!select_device(as[0].code_)) {  // デバイスリストの最初をサポートとして返す
					std::cerr << "Select device error." << std::endl;
					return false;
				}
			}

			// クロック・モード問い合わせ
			{
				if(!inquiry_clock_mode()) {
					std::cerr << "Inquiry clock-mode error." << std::endl;
					return false;
				}
				auto as = get_clock_mode();
				if(verbose_) {
					int i = 0;
					for(auto a : as) {
						++i;
						a.info(out_section_(i, as.size()));
					}				
				}
				// クロック・モード選択
				if(!select_clock_mode(as[0])) {
					std::cerr << "Select clock-mode error." << std::endl;
					return false;
				}
			}

			// 逓倍比問い合わせ
			{
				if(!inquiry_multiplier()) {
					std::cerr << "Inquiry multiplier error." << std::endl;
					return false;
				}
				if(verbose_) {
					auto as = get_multiplier();
					int i = 0;
					for(auto a : as) {
						++i;
						a.info(out_section_(i, as.size()));
					}				
				}
			}

			// 動作周波数問い合わせ
			{
				if(!inquiry_frequency()) {
					std::cerr << "Inquiry frequency error." << std::endl;
					return false;
				}
				if(verbose_) {
					auto as = get_frequency();
					int i = 0;
					for(auto a : as) {
						++i;
						a.info(out_section_(i, as.size()));
					}				
				}
			}

			// ボーレート変更
			{
				if(!change_speed(rx, brate)) {
					std::cerr << "Can't change baud rate speed." << std::endl;
					return false;
				}
				if(verbose_) {
					auto sect = out_section_(1, 1);
					std::cout << sect << "Change baud rate: " << baud_speed_ << std::endl;
				}
			}

			// ユーザー・ブート領域問い合わせ
			{
				if(!inquiry_boot_area()) {
					std::cerr << "Inquiry boot-area error." << std::endl;
					return false;
				}
				if(verbose_) {
					auto as = get_boot_area();
					int i = 0;
					for(auto a : as) {
						++i;
						a.info(out_section_(i, as.size()) + "Boot ");
					}				
				}
			}

			// ユーザー領域問い合わせ
			{
				if(!inquiry_area()) {
					std::cerr << "Inquiry area error." << std::endl;
					return false;
				}
				if(verbose_) {
					auto as = get_area();
					int i = 0;
					for(auto a : as) {
						++i;
						a.info(out_section_(i, as.size()));
					}				
				}
			}

			// ブロック情報問い合わせ
			{
				if(!inquiry_block()) {
					std::cerr << "Inquiry block error." << std::endl;
					return false;
				}
				if(verbose_) {
					auto as = get_block();
					int i = 0;
					for(auto a : as) {
						++i;
						a.info(out_section_(i, as.size()));
					}				
				}
			}

			// プログラム・サイズ問い合わせ
			{
				if(!inquiry_prog_size()) {
					std::cerr << "Inquiry prog-size error." << std::endl;
					return false;
				}
				if(verbose_) {
					auto sz = get_prog_size();
					auto sect = out_section_(1, 1);
					std::cout << sect << (boost::format("Program size: %u Bytes") % sz) << std::endl;
				}
			}

// for RX62x では、初期状態で、データフラッシュプロテクト状態となっている。
#if 0
			// データ量域の有無問い合わせ(RX63T向け)
			{
				if(!inquiry_data()) {
					std::cerr << "Inquiry data error." << std::endl;
					return false;
				}
				if(verbose_) {
					auto sect = out_section_(1, 1);
					std::cout << sect << "Data area: ";
					if(get_data()) {
						std::cout << "true" << std::endl;
					} else {
						std::cout << "false" << std::endl;
					}
				}
			}

			// データ量域情報問い合わせ
			{
				if(!inquiry_data_area()) {
					std::cerr << "Inquiry data-area error." << std::endl;
					return false;
				}
				if(verbose_) {
					auto as = get_data_area();
					int i = 0;
					for(auto a : as) {
						++i;
						a.info(out_section_(i, as.size()) + "Data ");
					}				
				}
			}
#endif

			// P/E ステータスに移行
			{
				if(!turn_pe_status()) {
					std::cerr << "P/E status error." << std::endl;
					return false;
				}
				if(verbose_) {
					auto sect = out_section_(1, 1);
					std::cout << sect << "ID Protect: ";
					if(get_protect()) {
						std::cout << "true" << std::endl;
					} else {
						std::cout << "false" << std::endl;
					}					
				}
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@param[in]	path	シリアルデバイスパス
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool start(const std::string& path) noexcept
		{
			return rx::protocol_base::start(path);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	コネクションの確立（startが成功したら呼ぶ）
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool connection() noexcept
		{
			bool ok = false;
			for(int i = 0; i < 30; ++i) {
				if(!command_(0x00)) {
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

			if(!command_(0x55)) {
				return false;
			}

			timeval tv;
			tv.tv_sec  = 1;
			tv.tv_usec = 0;
			int ch = rs232c_.recv(tv);
			if(ch == 0xff || ch != 0xE6) {
				return false;
			}

			connection_ = true;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	サポートデバイス問い合わせ（connection が成功したら呼ぶ）
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_device() noexcept
		{
			if(!connection_) return false;

			if(!command_(0x20)) {
				std::cerr << "(Inquiry) First command error." << std::endl;
				return false;
			}
			uint8_t head[3];
			// head[0]: 0x30
			// head[1]: サイズ
			// head[2]: デバイス数
			if(!read_(head, 3)) {
				std::cerr << "(Inquiry) Read head error." << std::endl;
				return false;
			}
			if(head[0] != 0x30) {
				std::cerr << "(Inquiry) Read status error." << std::endl;
				return false;
			}
			uint32_t total = head[1];

//			std::cout << boost::format("Size: %d") % total << std::endl;
//			std::cout << boost::format("Num:  %d") % static_cast<int>(head[2]) << std::endl;

			uint8_t tmp[total];
			if(!read_(tmp, total)) {
				std::cerr << "(Inquiry) Read body error." << std::endl;
				return false;
			}

//			for(uint32_t i = 0; i < total; ++i) {
//				std::cout << boost::format("0x%02X ") % static_cast<uint16_t>(tmp[i]);
//			}
//			std::cout << std::endl;

			uint8_t sum = sum_(tmp, total - 1);
			sum -= head[0] + head[1] + head[2];
			if(sum != tmp[total - 1]) { 
				std::cerr << boost::format("(Inquiry) Body sum error. (0x%02X : 0x%02X)")
					% static_cast<uint16_t>(sum) % static_cast<uint16_t>(tmp[total - 1]);
				std::cerr << std::endl;
				return false;
			}

			rx::protocol::device d;
			d.code_ = get32_(&tmp[1]);
			tmp[tmp[0] + 1] = 0;
			d.name_ = reinterpret_cast<const char*>(&tmp[5]);
			devices_.push_back(d);

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	デバイスを取得
			@return デバイス
		*/
		//-----------------------------------------------------------------//
		const rx::protocol::devices& get_device() const noexcept { return devices_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	デバイスを選択
			@param[in]	code	デバイス・コード
		*/
		//-----------------------------------------------------------------//
		bool select_device(uint32_t code) noexcept
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
			if(res[0] == 0x06) {
				return true;
			} else if(res[0] == 0x90) {  // エラーの場合
				read_(res, 1);  // エラーコード
				last_error_ = res[0];
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

			if(!command_(0x21)) {
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
		const rx::protocol::clock_modes& get_clock_mode() const noexcept { return clock_modes_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	クロック・モードを選択
			@param[in]	cm	クロック・モード
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

			if(!command_(0x22)) {
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
		const rx::protocol::multipliers& get_multiplier() const noexcept { return multipliers_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	動作周波数問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_frequency() noexcept
		{
			if(!connection_) return false;

			if(!command_(0x23)) {
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
			@brief	新ビットレート選択
			@param[in]	rx		マイコン設定
			@param[in]	spped	シリアル速度
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool change_speed(const rx::protocol::rx_t& rx, uint32_t speed) noexcept
		{
			if(!connection_) return false;

			// RX62x では、最大１１５２００ボーまでとする（誤差が大きい為）
			if(speed > LIMIT_BAUDRATE) {
				speed = LIMIT_BAUDRATE;
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
				std::cerr << "(Change speed) Invalid baud rate error." << std::endl;
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
				std::cerr << "(Change speed) Write command error." << std::endl;
				return false;
			}
			uint8_t res[1];
			if(!read_(res, 1)) {
				std::cerr << "(Change speed) Read respons error." << std::endl;
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
				std::cerr << boost::format("(Change speed) Respons error. (0x%02X)")
					% static_cast<uint16_t>(res[0]) << std::endl;
				if(res[0] == 0x24) {
					std::cerr << boost::format("Change speed select error: %u") % speed << std::endl;
				} else {
					std::cerr << boost::format("(Change speed) Respons error. (0x%02X)")
						% static_cast<uint16_t>(res[0]) << std::endl;
				}
				return false;
			} else if(res[0] != 0x06) {  // 正常レスポンス
				return false;
			}

			usleep(25000);	// 25[ms]

			if(!rs232c_.change_speed(baud_rate_)) {
				std::cerr << "(Change speed) Serial speed change error." << std::endl;
				return false;
			}

			if(!command_(0x06)) {  // 確認
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

			if(!command_(0x24)) {
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
				rx::protocol::area a;
				a.org_ = get32_big_(p);
				p += 4;
				a.end_ = get32_big_(p);
				p += 4;
				boot_area_.push_back(a);
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ユーザー・ブート領域を取得
			@return ユーザー・ブート領域
		*/
		//-----------------------------------------------------------------//
		const rx::protocol::areas& get_boot_area() const noexcept { return boot_area_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ユーザーマット領域問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_area() noexcept
		{
			if(!connection_) return false;

			if(!command_(0x25)) {
				return false;
			}

			uint8_t head[3];
			if(!read_(head, 3)) {
				return false;
			}
			if(head[0] != 0x35) {
				return false;
			}
			uint8_t tmp[256];
			if(!read_(tmp, head[1])) {
				return false;
			}

			auto num = head[2];
			const uint8_t* p = tmp;
			for(uint8_t i = 0; i < num; ++i) {
				rx::protocol::area a;
				a.org_ = get32_big_(p);
				p += 4;
				a.end_ = get32_big_(p);
				p += 4;
				area_.push_back(a);
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ユーザー領域を取得
			@return ユーザー領域
		*/
		//-----------------------------------------------------------------//
		const rx::protocol::areas& get_area() const { return area_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	消去ブロック情報問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_block() noexcept
		{
			if(!connection_) return false;

			if(!command_(0x26)) {
				return false;
			}

			uint8_t head[4];
			if(!read_(head, 4)) {
				return false;
			}
			if(head[0] != 0x36) {
				return false;
			}

			auto num = head[3];
			for(uint8_t i = 0; i < num; ++i) {
				uint8_t tmp[8];
				if(!read_(tmp, 8)) {
					return false;
				}
				rx::protocol::area a;
				a.org_ = get32_big_(&tmp[0]);
				a.end_ = get32_big_(&tmp[4]);
				blocks_.push_back(a);			
			}

			uint8_t sum[1];
			if(!read_(sum, 1)) {
				return false;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ブロック情報を取得
			@return ブロック情報
		*/
		//-----------------------------------------------------------------//
		const rx::protocol::areas& get_block() const noexcept { return blocks_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	書き込みサイズ問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_prog_size() noexcept
		{
			if(!connection_) return false;

			if(!command_(0x27)) {
				return false;
			}

			uint8_t head[5];
			if(!read_(head, 5)) {
				return false;
			}
			if(head[0] != 0x37) {
				return false;
			}

			prog_size_ = get16_big_(&head[2]);

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ページサイズを取得
			@return ページサイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t get_page_size() const noexcept { return 256; }


		//-----------------------------------------------------------------//
		/*!
			@brief	プログラム・サイズを取得
			@return プログラム・サイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t get_prog_size() const noexcept { return prog_size_; }

#if 0
		//-----------------------------------------------------------------//
		/*!
			@brief	データ量域有無問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_data() {
			if(!connection_) return false;

			if(!command_(0x2a)) {
				return false;
			}

			uint8_t head[4];
			if(!read_(head, 4)) {
				return false;
			}
			if(head[0] != 0x3a) {
				return false;
			}

			data_ = head[2] == 0x21;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	データ量域有無取得
			@return データ量域有無「true」ならデータ量域（有）
		*/
		//-----------------------------------------------------------------//
		bool get_data() const { return data_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	データ量域情報問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_data_area() {
			if(!connection_) return false;

			if(!command_(0x2b)) {
				return false;
			}

			uint8_t head[3];
			if(!read_(head, 3)) {
				return false;
			}
			if(head[0] != 0x3b) {
				return false;
			}

			auto num = head[2];
			for(uint8_t i = 0; i < num; ++i) {
				uint8_t tmp[8];
				if(!read_(tmp, 8)) {
					return false;
				}
				rx::protocol::area a;
				a.org_ = get32_big_(&tmp[0]);
				a.end_ = get32_big_(&tmp[4]);
				data_areas_.push_back(a);			
			}

			uint8_t sum[1];
			if(!read_(sum, 1)) {
				return false;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	データ量域情報を取得
			@return データ量域情報
		*/
		//-----------------------------------------------------------------//
		const rx::protocol::areas& get_data_area() const { return data_areas_; }
#endif

		//-----------------------------------------------------------------//
		/*!
			@brief	P/E ステータス遷移
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool turn_pe_status() noexcept
		{
			if(!connection_) return false;

			if(!command_(0x40)) {
				return false;
			}

			uint8_t head[1];
			if(!read_(head, 1)) {  // レスポンス
				return false;
			}
			if(head[0] == 0x26) {  // IDコードプロテクト無効の場合
				id_protect_ = false;
///				std::cout << "Return: 0x26" << std::endl;
			} else if(head[0] == 0x16) {  // IDコードプロテクト有効の場合
				id_protect_ = true;
///				std::cout << "Return: 0x16" << std::endl;
			} else if(head[0] == 0xc0) {  // エラーレスポンス
				if(!read_(head, 1)) {
					return false;
				}
				last_error_ = head[0];  // 通常 0x51
				return false;
			}

			pe_turn_on_ = true;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	プロテクト状態を取得
			@return プロテクト状態
		*/
		//-----------------------------------------------------------------//
		bool get_protect() const noexcept { return id_protect_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	イレース・ページ
			@param[in]	address	アドレス
			@return イレース・ステートを返す
		*/
		//-----------------------------------------------------------------//
		rx::protocol::erase_state erase_page(uint32_t address) noexcept
		{
			if(!connection_) return rx::protocol::erase_state::ERROR;
			if(!pe_turn_on_) return rx::protocol::erase_state::ERROR;

			if(!erase_select_) {  // 消去選択
				if(!command_(0x48)) {
					return rx::protocol::erase_state::ERROR;
				}
				uint8_t tmp[1];
				if(!read_(tmp, 1)) {  // レスポンス
					return rx::protocol::erase_state::ERROR;
				}
				if(tmp[0] != 0x06) {
					return rx::protocol::erase_state::ERROR;
				}
				erase_select_ = true;
			}

			// ブロック消去コマンド発行
			uint8_t block = 0;
			if(address >= 0xffff'8000) {
				block = ((address >> 12) & 0x7) ^ 0x7;
			} else {
				block = ((address >> 14) & 0x1f) ^ 0x1f;
				block += 8;
			}
			if(erase_set_.find(block) != erase_set_.end()) {
				return rx::protocol::erase_state::CHECK_OK;
			} else {
				erase_set_.insert(block);
			}
			uint8_t tmp[4];
			tmp[0] = 0x58;
			tmp[1] = 0x01;  // size 固定値１
			tmp[2] = block;
			tmp[3] = sum_(tmp, 3);
			if(!write_(tmp, 4)) {
				return rx::protocol::erase_state::ERROR;
			}

			{
				uint8_t tmp[1];
				if(!read_(tmp, 1)) {  // レスポンス
					return rx::protocol::erase_state::ERROR;
				}
				if(tmp[0] == 0xD8) {
					if(!read_(tmp, 1)) {  // エラーコード
						return rx::protocol::erase_state::ERROR;
					}
					// 0x11: サムチェックエラー
					// 0x29: ブロック番号エラー
					// 0x51: 消去エラーが発生
					last_error_ = tmp[0];  // エラーコード
					return rx::protocol::erase_state::ERROR;
				} else if(tmp[0] != 0x06) {
					return rx::protocol::erase_state::ERROR;
				}
				return rx::protocol::erase_state::ERASE_OK;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ユーザー・ブート／データ領域書き込み選択
			@param[in]	data	「true」ならデータ領域
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool select_write_area(bool data) noexcept
		{
			if(!connection_) return false;
			if(!pe_turn_on_) return false;
			if(erase_select_) {  // erase-select を解除
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
				if(tmp[0] == 0xD8) {
					if(!read_(tmp, 1)) {  // エラーコード
						return false;
					}
					// 0x11: サムチェックエラー
					// 0x29: ブロック番号エラー
					// 0x51: 消去エラーが発生
					last_error_ = tmp[0];  // エラーコード
					return false;
				} else if(tmp[0] != 0x06) {
					return false;
				}
				erase_select_ = false;
			}

			// 領域選択
			if(!command_(0x43)) {  // ユーザーマット選択コマンド
				return false;
			}

			uint8_t head[1];
			if(!read_(head, 1)) {
				return false;
			}
			if(head[0] != 0x06) {
				return false;
			}

			select_write_area_ = true;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	ライト・ページ（２５６バイト）
			@param[in]	address	アドレス
			@param[in]	src	ライト・データ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool write_page(uint32_t address, const uint8_t* src) noexcept
		{
			if(!connection_) return false;
			if(!pe_turn_on_) return false;
			if(!select_write_area_) return false;

			uint8_t cmd[5 + 256 + 1];
			cmd[0] = 0x50;
///			std::cout << boost::format("Address: %08X") % address << std::endl;			
			if(address != 0xffff'ffff) {
				put32_big_(&cmd[1], address);
				std::memcpy(&cmd[5], src, 256);
				cmd[5 + 256] = sum_(cmd, 5 + 256);

				if(!write_(cmd, 5)) {
					select_write_area_ = false;
					return false;
				}
				for(uint32_t i = 0; i < 16; ++i) {
					if(!write_(&cmd[5 + i * 16], 16)) {
						select_write_area_ = false;
						return false;
					}
				}
				if(!write_(&cmd[5 + 256], 1)) {  // SUM
				  	select_write_area_ = false;
					return false;
				}
			} else {
				put32_big_(&cmd[1], address);
				select_write_area_ = false;
				cmd[5] = sum_(cmd, 5);
				if(!write_(cmd, 6)) {
					return false;
				}
			}

			// レスポンス
			uint8_t head[1];
			if(!read_(head, 1)) {
				select_write_area_ = false;
				return false;
			}
			if(head[0] != 0x06) {
				std::cout << "(Write page) Respons error" << std::endl;
				select_write_area_ = false;
				if(head[0] != 0xd0) {
					return false;
				}
				if(!read_(head, 1)) {
					return false;
				}
				last_error_ = head[0];
///				std::cout << boost::format("Write error code: %02X") % static_cast<uint32_t>(head[0]) << std::endl;
				return false;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	リード・ページ
			@param[in]	adr	アドレス
			@param[out]	dst	リード・データ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool read_page(uint32_t adr, uint8_t* dst) noexcept
		{
			if(!connection_) return false;
			if(!pe_turn_on_) return false;

			uint8_t tmp[12];
			tmp[0] = 0x52;
			tmp[1] = 9;
			tmp[2] = 0x01;  // user-area, data-area
			put32_big_(&tmp[3], adr);
			put32_big_(&tmp[7], 256);
			tmp[11] = sum_(tmp, 11);
			if(!write_(tmp, 12)) {
				return false;
			}

			{
				uint8_t head[5];
				if(!read_(head, 5)) {
					return false;
				}
				if(head[0] != 0x52) {
					return false;
				}
				auto rs = get32_big_(&head[1]);
				/// std::cout << "Read size: " << rs << std::endl;
				if(!read_(dst, rs)) {
//					std::cout << "Read error #0" << std::endl;
					return false;
				}
			}
			{
				uint8_t sum[1];
				if(!read_(sum, 1)) {
//					std::cout << "Read error #1" << std::endl;
					return false;
				}
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	終了
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool end() noexcept
		{
			connection_ = false;
			pe_turn_on_ = false;
			select_write_area_ = false;
			return rx::protocol_base::close();
		}
	};
}
