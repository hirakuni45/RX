#pragma once
//=========================================================================//
/*! @file
    @brief  MAC Cash @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=========================================================================//
#include "common/ip_adrs.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ARP キャッシュ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct arp_info {
		ip_adrs		ipa;
		uint8_t		mac[6];
		uint16_t	time;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  mac_cash クラス
		@param[in]	SIZE	キャッシュの最大数
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<uint32_t SIZE>
	class mac_cash {

		arp_info	info_[SIZE];
		uint32_t	pos_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		mac_cash() : pos_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  格納可能な最大サイズを返す（終端の数を除外）
			@return 格納可能な最大サイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t capacity() const noexcept { return SIZE; }


		//-----------------------------------------------------------------//
		/*!
			@brief  現在のサイズを返す
			@return 現在のサイズ
		*/
		//-----------------------------------------------------------------//
		uint32_t size() const noexcept { return pos_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  インデックスが有効か検査
			@param[in]	idx	インデックス
			@return 有効なら「true」
		*/
		//-----------------------------------------------------------------//
		bool is_valid(uint32_t idx) const { return idx != SIZE; } 


		//-----------------------------------------------------------------//
		/*!
			@brief  キャッシュをクリア
		*/
		//-----------------------------------------------------------------//
		void clear() noexcept { pos_ = 0; }


		//-----------------------------------------------------------------//
		/*!
			@brief	検索
			@param[in]	ipa	検索アドレス
			@return 無ければ「SIZE」
		*/
		//-----------------------------------------------------------------//
		uint32_t lookup(const ip_adrs& ipa) noexcept
		{
			for(uint32_t i = 0; i < pos_; ++i) {
				if(info_[i].ipa == ipa) {
					return i;
				}
			}
			return SIZE;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  登録 @n
					・「255.255.255.255」、「0.0.0.0」の場合は登録しない @n
					・「x.x.x.0」、「x.x.x.255」の場合も登録しない
			@param[in]	ipa	登録アドレス
			@param[in]	mac	MAC アドレス
			@return 登録できたら「true」
		*/
		//-----------------------------------------------------------------//
		bool insert(const ip_adrs& ipa, const uint8_t* mac) noexcept
		{
			if(ipa[3] == 0 || ipa[3] == 255) {  // 末尾「０」ゲートウェイ、「２５５」ブロードキャストは無視
				return false;
			}
			if(tools::check_brodcast_mac(mac)) {  // MAC のブロードキャスト確認
				return false;
			}
			if(tools::check_allzero_mac(mac)) {  // MAC の任意アドレス確認
				return false;
			}
			uint32_t n = lookup(ipa);
			if(n < SIZE) {  // 登録済みアドレス
				std::memcpy(info_[n].mac, mac, 6);  // MAC アドレスを更新
				info_[n].time = 0;  // タイムスタンプ、リセット
				return true;
			} else {
				if(pos_ < SIZE) {
					info_[pos_].ipa = ipa;
					std::memcpy(info_[pos_].mac, mac, 6);
					info_[pos_].time = 0;
//					utils::format("Insert ARP cash (%d): %s -> %s\n")
//						% pos_
//						% tools::ip_str(ipa.get())
//						% tools::mac_str(mac);
					++pos_;
					return true;
				} else {  // バッファが満杯の場合の処理
					diet();
					return insert(ipa, mac);
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	削除
			@param[in]	ipa	検索アドレス
			@return 削除した場合「true」
		*/
		//-----------------------------------------------------------------//
		bool erase(const ip_adrs& ipa) noexcept
		{
			auto n = lookup(ipa);
			if(n < SIZE) {
				if(n != (pos_ - 1)) {
					info_[n] = info_[pos_ - 1];
				}
				--pos_;
				return true;
			}
			return false;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  リセット
			@param[in]	idx	参照ポイント
			@return リセット出来た場合「true」
		*/
		//-----------------------------------------------------------------//
		bool reset(uint32_t idx) noexcept
		{
			if(idx < pos_) {
				info_[idx].time = 0;
				return true;
			} else {
				return false;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ダイエット @n
					※利用頻度が最も低い候補を消去する
		*/
		//-----------------------------------------------------------------//
		void diet() noexcept
		{
			if(pos_ < SIZE) {
				return;
			}
			uint32_t n = SIZE;
			uint16_t t = 0;
			for(uint32_t i = 0; i < pos_; ++i) {
				if(info_[i].time > t) {
					t = info_[i].time;
					n = i;
				}
			}
			if(n < SIZE) {
				erase(n);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  [] オペレーター
			@param[in]	idx	参照インデックス
			@return 参照
		*/
		//-----------------------------------------------------------------//
		const arp_info& operator[] (uint32_t idx) const noexcept
		{
			if(idx >= pos_) {
				static arp_info info;
				std::memset(info.mac, 0x00, 6);
				info.time = 0;
				return info;
			}
			return info_[idx];
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  アップデート @n
					※登録済みのタイムカウントを進める
		*/
		//-----------------------------------------------------------------//
		void update() noexcept
		{
			for(uint32_t i = 0; i < pos_; ++i) {
				if(info_[i].time < 0xffff) {
					++info_[i].time;
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  リスト表示
		*/
		//-----------------------------------------------------------------//
		void list() const noexcept
		{
			for(uint32_t i = 0; i < pos_; ++i) {
				utils::format("ARP Cash (%d): %s -> %s (%d)\n")
					% i
					% info_[i].ipa.c_str()
					% tools::mac_str(info_[i].mac)
					% static_cast<uint32_t>(info_[i].time);
			}
		}
	};
}

