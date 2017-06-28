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
			@brief  キャッシュをリセット
		*/
		//-----------------------------------------------------------------//
		void reset() noexcept
		{
			pos_ = 0;
		}


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
			@brief  登録
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
			if(tools::check_brodcast_mac(mac)) {  // MAC アドレスの確認
				return false;
			}
			if(tools::check_allzero_mac(mac)) {  // MAC アドレスの確認
				return false;
			}
			uint32_t n = lookup(ipa);
			if(n < SIZE) {
				std::memcpy(info_[n].mac, mac, 6);  // MAC アドレス更新
				info_[n].time = 0;  // タイムスタンプ、リセット
				return true;
			} else {
				if(pos_ < SIZE) {
					info_[pos_].ipa = ipa;
					std::memcpy(info_[pos_].mac, mac, 6);
					info_[pos_].time = 0;
					utils::format("Insert ARP cash (%d): %s -> %s\n")
						% pos_
						% tools::ip_str(ipa.get())
						% tools::mac_str(mac);
					++pos_;
					return true;
				} else {
					return false;
				}
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  アップデート @n
					登録済みのタイムカウントを進める
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
			@brief  リスト
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


		//-----------------------------------------------------------------//
		/*!
			@brief  [] オペレーター
			@param[in]	idx	参照ポイント
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
	};
}

