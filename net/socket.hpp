#pragma once
//=====================================================================//
/*!	@file
	@brief	ソケット・クラス @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <cstdint>
#include <errno.h>
#include "common/format.hpp"
#include "r_socket_rx/r_socket_rx_if.h"
#include "ip_adrs.hpp"

#define SOCKET_DEBUG

namespace net {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  socket クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class ETHER_IO>
	class socket {

#ifndef SOCKET_DEBUG
		typedef utils::null_format debug_format;
#else
		typedef utils::format debug_format;
#endif

		ETHER_IO&	io_;

		int			fd_;
		int			afd_;
		int			afd_back_;
		uint32_t	count_;

		ip_adrs		src_adrs_;
		uint16_t	src_port_;

		ip_adrs		dst_adrs_;
		uint16_t	dst_port_;

		bool		server_;

		enum class task : uint8_t {
			idle,
			connect,
			bind,
			listen,
			accept,
			connected,
			close,
		};

		task		task_;

		uint32_t	timeout_;

		static bool	init_;

		static void make_adrs_(const ip_adrs& adr, uint16_t port, sockaddr_in& dst)
		{
			memset(&dst, 0, sizeof(sockaddr_in));
			dst.sin_family = PF_INET;
			if(adr.is_any()) {
				dst.sin_addr.s_addr = htonl(INADDR_ANY);
			} else {
				dst.sin_addr.s_addr = htonl(adr.getw());
			}
			dst.sin_port = htons(port);
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		socket(ETHER_IO& io) : io_(io), fd_(-1), afd_(-1), afd_back_(-1), count_(0),
			src_adrs_(), src_port_(0), dst_adrs_(), dst_port_(0), server_(false),
			task_(task::idle), timeout_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  デストラクター
		*/
		//-----------------------------------------------------------------//
		~socket() { end(); }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		static bool start()
		{
			if(init_) return false;

			auto ret = R_SOCKET_Open();
			if(ret < 0) {
				return false;
			} else {
				init_ = true;
				ip_adrs ipa(tcpudp_env[0].ipaddr);
				debug_format("Socket start (%s): work %u bytes\n")
					% ipa.c_str() % static_cast<uint32_t>(ret);
				return true;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ソース・アドレスの取得
			@return ソース・アドレス
		*/
		//-----------------------------------------------------------------//
		const ip_adrs& get_src_adrs() const { return src_adrs_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  ソース・ポートの取得
			@return ソース・ポート
		*/
		//-----------------------------------------------------------------//
		uint16_t get_src_port() const { return src_port_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  接続先アドレスの取得
			@return 接続先アドレス
		*/
		//-----------------------------------------------------------------//
		const ip_adrs& get_dst_adrs() const { return dst_adrs_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  接続先ポートの取得
			@return 接続先ポート
		*/
		//-----------------------------------------------------------------//
		uint16_t get_dst_port() const { return dst_port_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  ディスクリプタの取得
			@return ディスクリプタ
		*/
		//-----------------------------------------------------------------//
		int get_desc() const {
			if(task_ == task::connected) {
				return afd_;
			} else {
				return fd_;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  接続の確認
			@return 接続なら「true」
		*/
		//-----------------------------------------------------------------//
		bool connected() const { return task_ == task::connected; }


		//-----------------------------------------------------------------//
		/*!
			@brief  オープン
			@param[in]	port	ポート
			@param[in]	server	クライアントの場合「false」
			@param[in]	adrs	アドレス
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool open(uint16_t port, bool server = true, const ip_adrs& adrs = ip_adrs()) 
		{
			if(fd_ >= 0 || !init_) {
				debug_format("Socket open error\n");
				return false;
			}

			if(task_ != task::idle) {
				debug_format("Socket open error (invalid task)\n");
				return false;
			}

			fd_ = r_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if(fd_ >= 0) {
				if(server && adrs.is_any()) {
///					src_adrs_.set(tcpudp_env[0].ipaddr);
				} else { 
					src_adrs_ = adrs;
				}
				src_port_ = port;

				debug_format("Socket socket (%s): %d\n")
					% (server ? "Server" : "Client") % fd_;

				// setup no-block mode
///				if(r_fcntl(fd_, F_SETFL, O_NONBLOCK) != E_OK) {
///					utils::format("r_fcntl: error\n");
///				}

				server_ = server;
				if(server) {
					task_ = task::bind;
				} else {
					task_ = task::connect;
				}
			} else {
				debug_format("Socket socket error: %d\n") % fd_;
			}
			return (fd_ >= 0);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  サービス
		*/
		//-----------------------------------------------------------------//
		void service()
		{
			if(fd_ < 0 && afd_ < 0) return;

			switch(task_) {
			case task::idle:
				break;

			case task::connect:
				{
					sockaddr_in a;
					make_adrs_(src_adrs_, src_port_, a);
					int ret = r_connect(fd_, &a);
					if(ret == E_OK) {
						debug_format("Socket connect: %d, %s (%d)\n") % fd_
							% src_adrs_.c_str() % static_cast<int>(src_port_);
						afd_ = fd_;
						fd_ = -1;
						task_ = task::connected;
					}
				}
				break;

			case task::bind:
				{
					sockaddr_in a;
					make_adrs_(src_adrs_, src_port_, a);
					int ret = r_bind(fd_, &a);
					if(ret == E_OK) {
						debug_format("Socket bind: %d, %s (%d)\n") % fd_
							% src_adrs_.c_str() % static_cast<int>(src_port_);
						task_ = task::listen;
					} else {
						debug_format("Socket bind error: %d\n") % ret;
						task_ = task::close;
					}
				}
				break;

			case task::listen:
				{
					int ret = r_listen(fd_, 1);  // backlog only 1 (for Tiny Socket)
					if(ret == E_OK) {
						debug_format("Socket listen: %d\n") % fd_;
						afd_back_ = 0;
						count_ = 0;
						timeout_ = 5000;  // 5 sec
						task_ = task::accept;
					} else {
						debug_format("Socket listen error: %d\n") % ret;
						task_ = task::close;
					}
				}
				break;

			case task::accept:
				{
					sockaddr_in a;
					afd_ = r_accept(fd_, &a);
					if(afd_ >= 0) {
						dst_adrs_ = htonl(a.sin_addr.s_addr);
						dst_port_ = htons(a.sin_port);
						debug_format("Socket accept: %d, %s (%d)\n") % afd_
							% dst_adrs_.c_str() % static_cast<int>(dst_port_);
						r_close(fd_);
						fd_ = -1;
						task_ = task::connected;
					} else {
						if(timeout_ > 0) {
							--timeout_;
						} else {
							task_ = task::close;
						}
						int n = errno;
						if(n != afd_back_) {
///							debug_format("Socket accept state: %d\n") % n;
							afd_back_ = n;
						}
						++count_;
						if(count_ >= 100) {
							afd_back_ = 0;
							count_ = 0;
						}
					}
				}
				break;

			case task::connected:
				break;

			case task::close:
				{
					int ret = r_close(afd_);
					debug_format("Socket close: %d, %d\n") % ret % afd_;
					afd_ = -1;
					task_ = task::idle;
				}
				break;

			default:
				break;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  指定送信
			@param[in]	src		転送元
			@param[in]	len		長さ
			@param[in]	adrs	送信アドレス
			@param[in]	port	送信ポート番号
			@return 送信バイト
		*/
		//-----------------------------------------------------------------//
		int send(const void* src, uint32_t len, const ip_adrs& adrs, uint16_t port)
		{
			if(afd_ < 0 || src == nullptr) {
				return -1;
			}

			if(task_ != task::connected) {
				return 0;
			}

			sockaddr_in a;
			make_adrs_(adrs, port, a);
			int ret = r_sendto(afd_, src, len, &a);
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  送信
			@param[in]	src	転送元
			@param[in]	len	長さ
			@return 送信バイト
		*/
		//-----------------------------------------------------------------//
		int send(const void* src, uint32_t len)
		{
			if(afd_ < 0 || src == nullptr) {
				return -1;
			}

			if(task_ != task::connected) {
				return 0;
			}

			int ret = r_send(afd_, src, len);
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  指定受信
			@param[in]	dst	転送先
			@param[in]	len	長さ
			@param[in]	adrs	受信アドレス
			@param[in]	port	受信ポート番号
			@return 送信バイト
		*/
		//-----------------------------------------------------------------//
		int recv(void* dst, uint32_t len, const ip_adrs& adrs, uint16_t port)
		{
			if(afd_ < 0 || dst == nullptr) {
				return -1;
			}

			if(task_ != task::connected) {
				return 0;
			}

			sockaddr_in a;
			make_adrs_(adrs, port, a);
			int ret = r_recvfrom(afd_, dst, len, &a);
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  受信
			@param[in]	dst	転送先
			@param[in]	len	長さ
			@return 送信バイト
		*/
		//-----------------------------------------------------------------//
		int recv(void* dst, uint32_t len)
		{
			if(afd_ < 0 || dst == nullptr) {
				return -1;
			}

			if(task_ != task::connected) {
				return 0;
			}

			int ret = r_recv(afd_, dst, len);
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  クローズ
		*/
		//-----------------------------------------------------------------//
		void close()
		{
			task_ = task::close;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  終了
		*/
		//-----------------------------------------------------------------//
		static void end()
		{
			R_SOCKET_Close();
			init_ = false;
		}
	};

	template <class ETHER_IO> bool socket<ETHER_IO>::init_ = false;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  socket 文字出力テンプレートクラス
		@param[in]	ID		スタテッック領域の識別子として使用
		@param[in]	SIZE	バッファ・サイズ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t SIZE>
	class socket_string
	{
	public:
		typedef utils::fixed_string<SIZE + 1> STR;

	private:
		STR		str_;
		int		fd_;

	public:
		socket_string() : str_(), fd_(-1) { }

		void clear() {
			str_.clear();
		}

		void flush() {
			if(str_.size() > 0) {
				if(fd_ >= 0) {
					uint32_t len = str_.size();
					const char* p = str_.c_str();
#if 0
					while(len > 0) {
						uint32_t l = len;
						if(l >= 2048) {
							l = 2048;
						}
						r_send(fd_, p, l);
						len -= l;
						p += l;
					}
#else
					r_send(fd_, p, len);
#endif				
				} else {
					utils::format("ether_string: FD is null.\n");
				}
			}
			clear();
		}

		void operator() (char ch) {
			if(ch == '\n') {
				str_ += '\r';  // 改行を「CR+LF」とする
				if(str_.size() >= (str_.capacity() - 1)) {
					flush();
				}
			}
			str_ += ch;
			if(str_.size() >= (str_.capacity() - 1)) {
				flush();
			}
		}

		uint32_t size() const { return str_.size(); }

		void set_fd(int fd) { fd_ = fd; }

		STR& at_str() { return str_; }
	};
}
