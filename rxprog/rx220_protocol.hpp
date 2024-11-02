#pragma once
//=========================================================================//
/*!	@file
	@brief	RX220 プログラミング・プロトコル・クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "protocol_base.hpp"
#include <set>

namespace rx220 {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	RX220 プログラミング・プロトコル・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class protocol : public rx::protocol_base {

		static constexpr uint32_t LIMIT_BAUDRATE = 115200;
//		static constexpr uint32_t LIMIT_BAUDRATE = 57600;
		static constexpr uint8_t SEL_DEV_RES = 0x06;

		rx::protocol::areas			blocks_;
		uint32_t					prog_size_;
//		bool						data_ = false;
//		rx::protocol::areas			data_areas_;
		bool						id_protect_;
		bool						pe_turn_on_;
		bool						blank_check_;
		bool						blank_all_;
		bool						erase_select_;
		bool						select_write_area_;

		typedef std::set<uint32_t> ERASE_SET;
		ERASE_SET					erase_set_;

		uint32_t	   				baud_speed_;
		speed_t						baud_rate_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		protocol() noexcept :
			blocks_(), prog_size_(0),
			id_protect_(false), pe_turn_on_(false), blank_check_(false),
			blank_all_(false), erase_select_(false), select_write_area_(false),
			erase_set_(),
			baud_speed_(0), baud_rate_(B9600)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	コネクションの確立（startが成功したら呼ぶ）
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool connection() noexcept
		{
			return rx::protocol_base::connection(0xE6);
		}


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
			return rx::protocol_base::change_speed_legacy(rx, speed, LIMIT_BAUDRATE);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	消去ブロック情報問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_block() noexcept
		{
			if(!connection_) return false;

			if(!command1_(0x26)) {
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
		const rx::protocol::areas& get_block() const { return blocks_; }


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
				std::cout << "Connection OK. (RX220)" << std::endl;
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
				// デバイス選択（リトルエンディアン）
				if(!select_device(as[0].code_, SEL_DEV_RES)) {
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

			// 新ビットレート選択（ボーレート変更）
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

			// 領域書き込み情報問い合わせ
			// ・ユーザー・ブート領域問い合わせ
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

			// ・ユーザー領域問い合わせ
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

			// ・消去ブロック情報問い合わせ
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

			// 書き込みサイズ問い合わせ
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

			// P/E ステータスに推移
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
			@brief	書き込みサイズ問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_prog_size() {
			if(!connection_) return false;

			if(!command1_(0x27)) {
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
			@brief	プログラム・サイズを取得
			@return プログラム・サイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t get_prog_size() const { return prog_size_; }

#if 0
		//-----------------------------------------------------------------//
		/*!
			@brief	データ量域有無問い合わせ
			@return エラー無ければ「true」
		*/
		//-----------------------------------------------------------------//
		bool inquiry_data() {
			if(!connection_) return false;

			if(!command1_(0x2a)) {
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

			if(!command1_(0x2b)) {
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

			if(!command1_(0x40)) {
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
			@brief	ページサイズを取得
			@return ページサイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t get_page_size() const { return 256; }


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

			if(!blank_check_) {  // ブランク・チェック
				switch(user_blank_check()) {
				case BLANK_STATE::ERROR:
					return rx::protocol::erase_state::ERROR;
				case BLANK_STATE::BLANK_OK:
					blank_all_ = true;
					break;
				case BLANK_STATE::BLANK_NG:
					blank_all_ = false;
					break;
				}
				blank_check_ = true;
			}
			if(blank_all_) {
				return rx::protocol::erase_state::CHECK_OK;
			}

			if(!erase_select_) {  // 消去選択
				if(!enable_erase_select(RX_GROUP::RX2xx)) {
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
			}
			return rx::protocol::erase_state::ERASE_OK;
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
				if(!enable_erase_select(RX_GROUP::RX6xx, false)) {  // RX220 は　RX6xx 系の指定
					return false;
				}
				erase_select_ = false;
			}

			// 領域選択
			if(!command1_(0x43)) {  // ユーザーマット選択コマンド
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

			uint8_t cmd[12];
			cmd[0] = 0x52;
			cmd[1] = 9;
			cmd[2] = 0x01;  // user-area, data-area
			put32_big_(&cmd[3], adr);
			put32_big_(&cmd[7], 256);
			cmd[11] = sum_(cmd, 11);
			if(!write_(cmd, 12)) {
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
