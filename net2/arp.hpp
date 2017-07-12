#pragma once
//=========================================================================//
/*! @file
    @brief  ARP Protocol @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=========================================================================//
#include "net2/net_st.hpp"
#include "common/fixed_fifo.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ARP クラス
		@param[in]	ETHD	イーサーネット・ドライバー・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class ETHD>
	class arp {

		static const uint16_t ARP_REQUEST_WAIT = 100;   ///< 1 sec
		static const uint16_t ARP_REQUEST_NUM  = 5;     ///< 5 times

		ETHD&		ethd_;

		net_info&	info_;

		typedef utils::fixed_fifo<arp_info, 8> ARP_BUFF;
		ARP_BUFF	arp_buff_;

		struct arp_h {
			uint8_t	head[8];
			uint8_t	src_mac[6];
			uint8_t	src_ipa[4];
			uint8_t dst_mac[6];
			uint8_t dst_ipa[4];
		} __attribute__((__packed__));

		struct arp_frame {
			eth_h	eh_;
			arp_h	arp_;
		} __attribute__((__packed__));

		ip_adrs		req_ipa_;
		uint16_t	req_wait_;
		uint16_t	req_num_;


		static const uint8_t* get_arp_head7()
		{
			static const uint8_t head[7] = { 0x00, 0x01, 0x08, 0x00, 0x06, 0x04, 0x00 };
			return head;
		}


		void dump_(const arp_h& arp)
		{
			utils::format("ARP Header:\n");
			utils::format("  %02X%02X\n")
				% static_cast<uint32_t>(arp.head[0]) % static_cast<uint32_t>(arp.head[1]);
			utils::format("  %02X%02X\n")
				% static_cast<uint32_t>(arp.head[2]) % static_cast<uint32_t>(arp.head[3]);
			utils::format("  %02X%02X\n")
				% static_cast<uint32_t>(arp.head[4]) % static_cast<uint32_t>(arp.head[5]);
			utils::format("  %02X%02X\n")
				% static_cast<uint32_t>(arp.head[6]) % static_cast<uint32_t>(arp.head[7]);
			utils::format("  src: %s, %s\n") % tools::mac_str(arp.src_mac) % tools::ip_str(arp.src_ipa);
			utils::format("  dst: %s, %s\n") % tools::mac_str(arp.dst_mac) % tools::ip_str(arp.dst_ipa);
		}


		void send_arp_(const arp_frame& t)
		{
			void* dst;
			uint16_t dlen;
			if(ethd_.send_buff(&dst, dlen) != 0) {
				utils::format("ARP: ether send_buff error\n");
				return;
			}

			uint32_t all = sizeof(arp_frame);
			std::memcpy(dst, &t, all);

			uint8_t* p = reinterpret_cast<uint8_t*>(&dst);
			p += all;

			// ６０バイトに満たない場合は、ダミー・データ（０）を追加する。
			while(all < 60) {
				*p++ = 0;
				++all;
			}
			ethd_.send(all);

//			dump(eh);
//			dump_(arp);
		}


		bool request_sub_(const ip_adrs& ipa)
		{
			arp_frame t;
			t.eh_.set_dst(tools::get_brodcast_mac());
			t.eh_.set_src(info_.mac);
			t.eh_.set_type(eth_type::ARP);

			std::memcpy(t.arp_.head, get_arp_head7(), 7);
			t.arp_.head[7] = 0x01;  // request
			std::memcpy(t.arp_.src_mac, info_.mac, 6);
			std::memcpy(t.arp_.src_ipa, info_.ip.get(), 4);
			std::memset(t.arp_.dst_mac, 0x00, 6);
			std::memcpy(t.arp_.dst_ipa, ipa.get(), 4);

			ethd_.enable_interrupt(false);
			send_arp_(t);
			ethd_.enable_interrupt();

			utils::format("ARP request: %s\n") % ipa.c_str();

			return true;
		}


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	ethd	イーサーネット・ドライバー
			@param[in]	info	ネット情報
		*/
		//-----------------------------------------------------------------//
		arp(ETHD& ethd, net_info& info) : ethd_(ethd), info_(info), arp_buff_(),
			req_ipa_(), req_wait_(0), req_num_(0)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  プロセス @n
					※割り込み外から呼ぶ事は禁止
			@param[in]	h		ヘッダー
			@param[in]	top		先頭ポインター
			@param[in]	len		長さ
		*/
		//-----------------------------------------------------------------//
		bool process(const eth_h& h, const void* top, int32_t len)
		{
			bool ret = false;
			if(static_cast<size_t>(len) < sizeof(arp_h)) {
				goto process_end;
			}

			{
				const arp_h& r = *static_cast<const arp_h*>(top);
				if(std::memcmp(get_arp_head7(), r.head, 7) != 0) {
					goto process_end;
				}

				if(tools::check_brodcast_mac(h.get_dst()) && r.head[7] == 0x01) {  // ARP Request
					if(arp_buff_.length() < (arp_buff_.size() - 1)) {
						arp_info& a = arp_buff_.put_at();
						a.ipa.set(r.src_ipa[0], r.src_ipa[1], r.src_ipa[2], r.src_ipa[3]);
						std::memcpy(a.mac, r.src_mac, 6);
						arp_buff_.put_go();
					}
				} else if(r.head[7] == 0x02) {  // ARP Response
					// IP/MAC の収集
					if(arp_buff_.length() < (arp_buff_.size() - 2)) {
						{
							arp_info& a = arp_buff_.put_at();
							a.ipa.set(r.src_ipa[0], r.src_ipa[1], r.src_ipa[2], r.src_ipa[3]);
							std::memcpy(a.mac, r.src_mac, 6);
							arp_buff_.put_go();
						}
						{
							arp_info& a = arp_buff_.put_at();
							a.ipa.set(r.dst_ipa[0], r.dst_ipa[1], r.dst_ipa[2], r.dst_ipa[3]);
							std::memcpy(a.mac, r.dst_mac, 6);
							arp_buff_.put_go();
						}
					}
					goto process_end;
				} else {
					goto process_end;
				}

				ip_adrs ipa(r.dst_ipa[0], r.dst_ipa[1], r.dst_ipa[2], r.dst_ipa[3]);
				if(info_.ip != ipa) {
					goto process_end;
				}

				arp_frame t;
				t.eh_.set_dst(h.get_src());
				t.eh_.set_src(info_.mac);
				t.eh_.set_type(eth_type::ARP);

				std::memcpy(t.arp_.head, get_arp_head7(), 7);
				t.arp_.head[7] = 0x02;
				std::memcpy(t.arp_.src_mac, info_.mac, 6);
				std::memcpy(t.arp_.src_ipa, info_.ip.get(), 4);
				std::memcpy(t.arp_.dst_mac, r.src_mac, 6);
				std::memcpy(t.arp_.dst_ipa, r.src_ipa, 4);

				send_arp_(t);

//			utils::format("ARP: src: %s, dst: %s\n")
//				% tools::ip_str(r.src_ipa)
//				% tools::ip_str(r.dst_ipa);
			}
			ret = true;

		process_end:

			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  リクエスト
			@param[in]	ipa		リクエストする IP アドレス
			@return 正常終了なら「true」
		*/
		//-----------------------------------------------------------------//
		bool request(const ip_adrs& ipa)
		{
			if(!req_ipa_.is_any()) return false;

			req_ipa_   = ipa;
			req_wait_  = ARP_REQUEST_WAIT;
			req_num_   = ARP_REQUEST_NUM;

			request_sub_(ipa);

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			while(arp_buff_.length() > 0) {
				const arp_info& a = arp_buff_.get_at();
				info_.at_cash().insert(a.ipa, a.mac);
				arp_buff_.get_go();
			}

			if(req_ipa_.is_any()) return;

			auto idx = info_.at_cash().lookup(req_ipa_);
			if(info_.at_cash().is_valid(idx)) {
				req_ipa_.set(0);
			} else {
				if(req_wait_) {
					--req_wait_;
				} else if(req_num_) {
					--req_num_;
					req_wait_ = ARP_REQUEST_WAIT;
					request_sub_(req_ipa_);
				}
			}
		}
	};
}
