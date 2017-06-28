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

		arp_info	cash_[SIZE];
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
		void reset()
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
		uint32_t lookup(const ip_adrs& ipa)
		{
			for(uint32_t i = 0; i < pos_; ++i) {
				if(cash_[i].ipa == ipa) {
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
		bool insert(const ip_adrs& ipa, const uint8_t* mac)
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
				std::memcpy(cash_[n].mac, mac, 6);  // MAC アドレス更新
				cash_[n].time = 0;  // タイムスタンプ、リセット
				return true;
			} else {
				if(pos_ < SIZE) {
					cash_[pos_].ipa = ipa;
					std::memcpy(cash_[pos_].mac, mac, 6);
					cash_[pos_].time = 0;
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
		void update()
		{
			for(uint32_t i = 0; i < pos_; ++i) {
				if(cash_[i].time < 0xffff) {
					++cash_[i].time;
				}
			}
		}
	};
}

