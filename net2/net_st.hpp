#pragma once
//=========================================================================//
/*! @file
    @brief  NET 関係構造体 @n
			Copyright 2017 Kunihito Hiramatsu
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=========================================================================//
#include <cstdint>
#include <cstring>
#include "common/net_tools.hpp"
#include "common/ip_adrs.hpp"
#include "common/format.hpp"
#include "common/fixed_fifo.hpp"
#include "net2/mac_cash.hpp"

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ネット共有コンテナ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct net_share {

		typedef utils::fixed_fifo<ip_adrs, 8> MAC_REQUEST;
		MAC_REQUEST		mac_request_;

	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ネット情報構造体
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct net_info {
		uint8_t		mac[6];  ///< イーサーネット、ＭＡＣアドレス（EUI-48）

		ip_adrs		ip;      ///< IP アドレス 
		ip_adrs		mask;    ///< ネット・マスク
		ip_adrs		gw;      ///< ゲートウェイ
		ip_adrs		dns;     ///< Domain Name Server
		ip_adrs		dns2;    ///< Domain Name Server 2ND

	private:
		typedef mac_cash<8> CASH;
		CASH		cash_;

		net_share	share_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		net_info() : mac{ 0 }, ip(), mask(), gw(), dns(), dns2(), cash_() { }


		//-----------------------------------------------------------------//
		/*!
			@brief  MAC キャッシュの参照
			@return MAC キャッシュ
		*/
		//-----------------------------------------------------------------//
		CASH& at_cash() { return cash_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  MAC キャッシュの参照（const）
			@return MAC キャッシュ
		*/
		//-----------------------------------------------------------------//
		const CASH& get_cash() const { return cash_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  ネット共有コンテナの参照
			@return ネット共有コンテナ
		*/
		//-----------------------------------------------------------------//
		net_share& at_share() { return share_; }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  イーサーネット・タイプ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class eth_type : uint16_t {
		IPV4       = 0x0800,  ///< IPV4
		ARP        = 0x0806,  ///< ARP
		APPLETALK  = 0x809B,  ///< AppleTalk
		IEEE802_1Q = 0x8100,  ///< IEEE802.1Q
		IPX        = 0x8137,  ///< IPX
		IPV6       = 0x86DD,  ///< IPV6
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  イーサーネット・ヘッダー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class eth_h {

		uint8_t		dst_[6];  ///< destination MAC address 受信先
		uint8_t		src_[6];  ///< source MAC address 送信元
		eth_type	type_;    ///< type

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  Destination MAC の取得
			@return Destination MAC
		*/
		//-----------------------------------------------------------------//
		const uint8_t* get_dst() const noexcept { return dst_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  Destination MAC の取得
			@param[in]	ptr	元ポインター
		*/
		//-----------------------------------------------------------------//
		void set_dst(const uint8_t* ptr) noexcept { std::memcpy(dst_, ptr, 6); }


		//-----------------------------------------------------------------//
		/*!
			@brief  Destination MAC の取得
			@return Destination MAC
		*/
		//-----------------------------------------------------------------//
		const uint8_t* get_src() const noexcept { return src_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  Destination MAC の取得
			@param[in]	ptr	元ポインター
		*/
		//-----------------------------------------------------------------//
		void set_src(const uint8_t* ptr) noexcept { std::memcpy(src_, ptr, 6); }


		//-----------------------------------------------------------------//
		/*!
			@brief  イーサーネット・タイプの取得
			@return イーサーネット・タイプ
		*/
		//-----------------------------------------------------------------//
		eth_type get_type() const noexcept {
			return static_cast<eth_type>(tools::htons(static_cast<uint16_t>(type_)));
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  イーサーネット・タイプの設定
			@return イーサーネット・タイプ
		*/
		//-----------------------------------------------------------------//
		void set_type(eth_type t) noexcept {
			type_ = static_cast<eth_type>(tools::htons(static_cast<uint16_t>(t)));
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ヘッダー終端ポインターの取得
			@return ヘッダー終端ポインター
		*/
		//-----------------------------------------------------------------//
		static void* next_ptr(void* org) noexcept {
			return static_cast<void*>(static_cast<uint8_t*>(org) + sizeof(eth_h));
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ヘッダー終端ポインターの取得（const）
			@return ヘッダー終端ポインター
		*/
		//-----------------------------------------------------------------//
		static const void* next_ptr(const void* org) noexcept {
			return static_cast<const void*>(static_cast<const uint8_t*>(org) + sizeof(eth_h));
		}
	} __attribute__((__packed__));


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  イーサーネット・ヘッダー、スワップコピー
		@param[out]	dst	コピー先
		@param[in]	src	コピー元
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	static void swap_copy_eth_h(eth_h* dst, const eth_h* src)
	{
		dst->set_dst(src->get_src());
		dst->set_src(src->get_dst());
		dst->set_type(src->get_type());
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  イーサーネット・ヘッダーのダンプ
		@param[in]	h	イーサーネット・ヘッダー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	static void dump(const eth_h& h) {
		utils::format("Ethernet Header:\n");
		utils::format("  src(%s), dst(%s), type(%04X)\n")
			% tools::mac_str(h.get_src())
			% tools::mac_str(h.get_dst())
			% static_cast<uint32_t>(h.get_type());
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  IPV4 ヘッダー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct ipv4_h {
	
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IPV4 プロトコル
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class protocol : uint8_t {
			ICMP = 0x01,	///< ICMP
			TCP  = 0x06,	///< TCP
			UDP  = 0x11,	///< UDP
		};

		uint8_t		ver_hlen_;    ///< バージョン(B0-B3)、ヘッダー長(B4-B7)
		uint8_t		type_;        ///< サービス・タイプ
		uint16_t	length_;      ///< 全長
		uint16_t	id_;          ///< 識別番号
		uint16_t	f_offset_;    ///< フラグ(B0-B2)、フラグメントオフセット(B3-B15)
		uint8_t		time_;        ///< 生存時間
		protocol	protocol_;    ///< プロトコル
		uint16_t	csum_;        ///< ヘッダ・チェックサム

		uint8_t		src_ipa_[4];  ///< 送信元 IP アドレス
		uint8_t		dst_ipa_[4];  ///< 宛先 IP アドレス

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  IPV4 バージョンの取得
			@return IPV4 バージョン
		*/
		//-----------------------------------------------------------------//
		uint16_t get_version() const noexcept { return ver_hlen_ & 0x0f; }


		//-----------------------------------------------------------------//
		/*!
			@brief  IPV4 バージョンの設定
			@param[in]	ver	IPV4 バージョン
		*/
		//-----------------------------------------------------------------//
		void set_version(uint8_t ver) noexcept {
			ver_hlen_ &= 0xf0;
			ver_hlen_ |= ver;
		}

		uint16_t get_header_length() const noexcept { return ver_hlen_ >> 4; }
		void set_header_length(uint8_t length) noexcept {
			ver_hlen_ &= 0x0f;
			ver_hlen_ |= length << 4;
		}

		uint16_t get_length() const noexcept { return tools::htons(length_); }
		void set_length(uint16_t length) noexcept { length_ = tools::htons(length); }

		uint16_t get_id() const noexcept { return tools::htons(id_); }
		void set_id(uint16_t id) noexcept { id_ = tools::htons(id); }

		/// 下位３ビット
		uint8_t get_flag() const noexcept { return tools::htons(f_offset_) >> 13; }
		void set_flag(uint8_t flag) noexcept {
			uint16_t tmp = tools::htons(f_offset_);
			tmp &= 0x1fff;
			tmp |= static_cast<uint16_t>(flag) << 13;
			f_offset_ = tools::htons(tmp);
		}

		uint16_t get_flagment_offset() const noexcept { return tools::htons(f_offset_) & 0x1fff; }
		void set_flagment_offset(uint16_t ofs) noexcept {
			uint16_t tmp = tools::htons(f_offset_);
			tmp &= 0xe000;
			tmp |= ofs;
			f_offset_ = tools::htons(tmp);
		}

		uint16_t get_time() const noexcept { return static_cast<uint16_t>(time_); }
		void set_time(uint16_t time) noexcept { time_ = tools::htons(time); }

		protocol get_protocol() const noexcept { return protocol_; }
		void set_protocol(protocol prop) noexcept { protocol_ = prop; }

		uint16_t get_csum() const noexcept { return tools::htons(csum_); }
		void set_csum(uint16_t csum) noexcept { csum_ = tools::htons(csum); }

		const uint8_t* get_src_ipa() const noexcept { return src_ipa_; }
		void set_src_ipa(const uint8_t* src) noexcept { std::memcpy(src_ipa_, src, 4); }

		const uint8_t* get_dst_ipa() const noexcept { return dst_ipa_; }
		void set_dst_ipa(const uint8_t* src) noexcept { std::memcpy(dst_ipa_, src, 4); }
	} __attribute__((__packed__));


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  IPV4 ヘッダー、スワップコピー
		@param[out]	dst	コピー先
		@param[in]	src	コピー元
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	static void swap_copy_ipv4_h(ipv4_h* dst, const ipv4_h* src)
	{
		std::memcpy(dst, src, 12);
		dst->set_src_ipa(src->get_dst_ipa());
		dst->set_dst_ipa(src->get_src_ipa());
	}


	//-----------------------------------------------------------------//
	/*!
		@brief  IPV4 ヘッダーのダンプ
		@param[in]	h	IPV4 ヘッダー
	*/
	//-----------------------------------------------------------------//
	static void dump(const ipv4_h& h)
	{
		utils::format("IP Header:\n");
		utils::format("  version: %d, header length: %d\n")
			% h.get_version()
			% h.get_header_length();
		utils::format("  length: %d") % h.get_length();
		utils::format(", id: %d") % h.get_id();
		utils::format(", flag: %d, flagment ofs: %d\n")
			% h.get_flag()
			% h.get_flagment_offset();
		utils::format("  time: %d") % h.get_time();

		switch(h.get_protocol()) {
		case ipv4_h::protocol::ICMP:
			utils::format(", ICMP\n");
			break;
		case ipv4_h::protocol::TCP:
			utils::format(", TCP\n");
			break;
		case ipv4_h::protocol::UDP:
			utils::format(", UDP\n");
			break;
		default:
			utils::format(", Other(%d)\n") % static_cast<uint32_t>(h.get_protocol());
			break;
		}

		utils::format("  csum: 0x%04X, src: %s, dst: %s\n")
			% h.get_csum()
			% tools::ip_str(h.get_src_ipa())
			% tools::ip_str(h.get_dst_ipa());
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  UDP セグメント・ヘッダー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class udp_h {

		uint16_t	src_port_;	///< 送信元ポート番号
		uint16_t	dst_port_;	///< あて先ポート番号
		uint16_t	length_;	///< 長さ
		uint16_t	csum_;		///< チェックサム

	public:

		uint16_t get_src_port() const noexcept { return tools::htons(src_port_); }
		void set_src_port(uint16_t port) noexcept { src_port_ = tools::htons(port); }

		uint16_t get_dst_port() const noexcept { return tools::htons(dst_port_); }
		void set_dst_port(uint16_t port) noexcept { dst_port_ = tools::htons(port); }

		uint16_t get_length_() const noexcept { return length_; }
		uint16_t get_length() const noexcept { return tools::htons(length_); }
		void set_length(uint16_t length) noexcept { length_ = tools::htons(length); }

		uint16_t get_csum() const noexcept { return tools::htons(csum_); }
		void set_csum(uint16_t csum) noexcept { csum_ = tools::htons(csum); }

		static void* get_data_ptr(udp_h* org) {
			return reinterpret_cast<uint8_t*>(org) + sizeof(udp_h);
		}

		static const void* get_data_ptr(const udp_h* org) {
			return reinterpret_cast<const uint8_t*>(org) + sizeof(udp_h);
		}

		uint16_t get_data_len() const { return get_length() - sizeof(udp_h); }

	} __attribute__((__packed__));


	//-----------------------------------------------------------------//
	/*!
		@brief  udp_segment  ヘッダーのダンプ
		@param[in]	h	udp_segment ヘッダー
	*/
	//-----------------------------------------------------------------//
	static void dump(const udp_h& h)
	{
		utils::format("UDP Segment: src(%d), dst(%d)\n")
			% h.get_src_port()
			% h.get_dst_port();
		utils::format("  Length: %d, CSUM: %04X\n") % h.get_length() % h.get_csum();
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  TCP セグメント・ヘッダー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class tcp_h {

		uint16_t	src_port_;
		uint16_t	dst_port_;
		uint32_t	seq_;
		uint32_t	ack_;
		uint16_t	flag_ofs_;
		uint16_t	window_;
		uint16_t	csum_;
		uint16_t	urgent_ptr_;

		void set_flag_(bool f, uint16_t mask, uint16_t* dst) {
			if(f) {
				*dst |=  mask;
			} else {
				*dst &= ~mask;
			}
		}

	public:
		uint16_t get_src_port() const { return tools::htons(src_port_); }
		void set_src_port(uint16_t port) { src_port_ = tools::htons(port); }

		uint16_t get_dst_port() const { return tools::htons(dst_port_); }
		void set_dst_port(uint16_t port) { dst_port_ = tools::htons(port); }

		uint32_t get_seq() const { return tools::htonl(seq_); }
		void set_seq(uint32_t seq) { seq_ = tools::htonl(seq); }

		uint32_t get_ack() const { return tools::htonl(ack_); }
		void set_ack(uint32_t ack) { ack_ = tools::htonl(ack); }

		uint16_t get_flag_ofs() const { return tools::htons(flag_ofs_); }
		void set_flag_ofs(uint16_t ofs) { flag_ofs_ = tools::htons(ofs); }

		uint16_t get_window() const { return tools::htons(window_); }
		void set_window(uint16_t win) { window_ = tools::htons(win); }

		uint16_t get_csum() const { return tools::htons(csum_); }
		void set_csum(uint16_t sum) { csum_ = tools::htons(sum); }

		uint16_t get_urgent_ptr() const { return tools::htons(urgent_ptr_); }
		void set_urgent_ptr(uint16_t ptr) { urgent_ptr_ = tools::htons(ptr); }

		bool get_flag_urg() const { return (flag_ofs_ & 0x0004) != 0; }
		void set_flag_urg(bool f) { set_flag_(f, 0x0004, &flag_ofs_); }

		bool get_flag_ack() const { return (flag_ofs_ & 0x0008) != 0; }
		void set_flag_ack(bool f) { set_flag_(f, 0x0008, &flag_ofs_); }

		bool get_flag_psh() const { return (flag_ofs_ & 0x0010) != 0; }
		void set_flag_psh(bool f) { set_flag_(f, 0x0010, &flag_ofs_); }

		bool get_flag_rst() const { return (flag_ofs_ & 0x0020) != 0; }
		void set_flag_rst(bool f) { set_flag_(f, 0x0020, &flag_ofs_); }

		bool get_flag_syn() const { return (flag_ofs_ & 0x0040) != 0; }
		void set_flag_syn(bool f) { set_flag_(f, 0x0040, &flag_ofs_); }

		bool get_flag_fin() const { return (flag_ofs_ & 0x0080) != 0; }
		void set_flag_fin(bool f) { set_flag_(f, 0x0080, &flag_ofs_); }
	} __attribute__((__packed__));


	//-----------------------------------------------------------------//
	/*!
		@brief  tcp_segment  ヘッダーのダンプ
		@param[in]	h	tcp_segment ヘッダー
	*/
	//-----------------------------------------------------------------//
	static void dump(const tcp_h& h)
	{
		utils::format("TCP Segment: src(%d), dst(%d)\n")
			% h.get_src_port()
			% h.get_dst_port();
		utils::format("  Seq: %d, Aack: %d\n") % h.get_seq() % h.get_ack();
		utils::format("  flags: URG: %d, ACK: %d, PSH:%d, RST:%d, SYN:%d, FIN:%d\n")
			% h.get_flag_urg()
			% h.get_flag_ack()
			% h.get_flag_psh()
			% h.get_flag_rst()
			% h.get_flag_syn()
			% h.get_flag_fin();
		utils::format("  offset(header length): %d\n") % h.get_flag_ofs();
		utils::format("  Window: %d, C-Sum: %04X, Urgent PTR: %d\n")
			% h.get_window()
			% h.get_csum()
			% h.get_urgent_ptr();
	}
}
