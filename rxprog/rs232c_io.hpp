#pragma once
//=====================================================================//
/*!	@file
	@brief	RS232C 入出力クラス
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <limits.h>
#include <sys/ioctl.h>
#include <string>
#include <iostream>
#include <cstring>
#include <cstdio>

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	RS232C I/O クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class rs232c_io {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	パリティの設定
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class parity {
			none,
			even,
			odd
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	キャラクター長
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class char_len {
			bits7,
			bits8
		};


	private:
		int    fd_;

		termios		attr_back_;
		termios		attr_;

		void close_() {
			tcsetattr(fd_, TCSANOW, &attr_back_);
			::close(fd_);
			fd_ = -1;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-----------------------------------------------------------------//
		rs232c_io() : fd_(-1) { }


		//-----------------------------------------------------------------//
		/*!
			@brief オープン
			@param[in]	path	シリアルポートパス
			@param[in]	brate	接続ボーレート
			@param[in]	clen	キャラクター長
			@param[in]	par		パリティ・ビット
			@return 正常なら「true」
		*/
		//-----------------------------------------------------------------//
		bool open(const std::string& path, speed_t brate, char_len clen = char_len::bits8, parity par = parity::none) {
			fd_ = ::open(path.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
			if(fd_ < 0) {
				return false;
			}

			if(tcgetattr(fd_, &attr_back_) == -1) {
				::close(fd_);
				fd_ = -1;
			}

			int cpar = 0;
			int ipar = IGNPAR;
			switch(par) {
			default:
			case parity::none:
				cpar = 0;
				ipar = IGNPAR;
				break;
			case parity::even:
				cpar = PARENB;
				ipar = INPCK;
				break;
			case parity::odd:
				cpar = (PARENB | PARODD);
				ipar = INPCK;
				break;
			}

			int bstop = 0;
#if 0
			switch(mode[2]) {
			case '1': bstop = 0;
				break;
			case '2': bstop = CSTOPB;
				break;
			}
#endif

			int cbits;
			switch(clen) {
			default:
			case char_len::bits8:
				cbits = CS8;
				break;
			case char_len::bits7:
				cbits = CS7;
				break;
			}

			memset(&attr_, 0, sizeof(attr_));
			attr_.c_cflag = cbits | cpar | bstop | CLOCAL | CREAD;
			attr_.c_iflag = ipar;
			attr_.c_oflag = 0;
			attr_.c_lflag = 0;
			attr_.c_cc[VMIN]  = 1;     // block untill n bytes are received
			attr_.c_cc[VTIME] = 0;     // block untill a timer expires (n * 100 mSec.)

			if(cfsetspeed(&attr_, brate) == -1) {
				close_();
				return false;
			}

			if(tcsetattr(fd_, TCSANOW, &attr_) == -1) {
				close_();
				return false;
			}

			int status;
			if(ioctl(fd_, TIOCMGET, &status) == -1) {
				close_();
				return false;
			}

			return true;
		}


		bool change_speed(speed_t brate) {
			if(fd_ < 0) return false;

			if(cfsetspeed(&attr_, brate) == -1) {
				close_();
				return false;
			}
			if(tcsetattr(fd_, TCSANOW, &attr_) == -1) {
				close_();
				return false;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	クローズ
			@return 正常なら「true」
		*/
		//-----------------------------------------------------------------//
		bool close() {
			if(fd_ < 0) return false;

			int status;
			if(ioctl(fd_, TIOCMGET, &status) == -1) {
				close_();
				return false;
			}

			status &= ~TIOCM_DTR;    /* turn off DTR */
			status &= ~TIOCM_RTS;    /* turn off RTS */

			if(ioctl(fd_, TIOCMSET, &status) == -1) {
				close_();
				return false;
			}

			close_();

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	送信同期
			@return 正常なら「true」
		*/
		//-----------------------------------------------------------------//
		bool sync_send() const {
			if(fd_ < 0) return false;

			tcdrain(fd_);
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	受信
			@param[out]	dst	受信データ転送先
			@param[in]	len	受信最大長さ
			@return 受信した長さ
		*/
		//-----------------------------------------------------------------//
		size_t recv(void* dst, size_t len) {
			if(fd_ < 0) return 0;

			return ::read(fd_, dst, len);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	受信
			@param[out]	dst	受信データ転送先
			@param[in]	len	受信最大長さ
			@param[in]	tv	タイムアウト指定
			@return 受信した長さ
		*/
		//-----------------------------------------------------------------//
		size_t recv(void* dst, size_t len, const timeval& tv) {
			if(fd_ < 0) return 0;

			size_t total = 0;
			uint8_t* p = static_cast<uint8_t*>(dst);
			while(total < len) {
				fd_set fds;
				FD_ZERO(&fds);
				FD_SET(fd_, &fds);
				timeval t;
				t = tv;
				int ret = select(fd_ + 1, &fds, NULL, NULL, &t);
				if(ret == -1) {  // for error..
					break;
				} else if(ret > 0) {
					size_t rl = ::read(fd_, p, len);
					total += rl;
					p += rl;
				} else {
					break;
				}
			}
			return total;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	１バイト受信（タイムアウト）
			@param[in]	tv	タイムアウト指定
			@return 受信した長さ
		*/
		//-----------------------------------------------------------------//
		int recv(const timeval& tv) {
			uint8_t buff[1];
			if(recv(buff, 1, tv) != 1) {
				return EOF;
			}
			return static_cast<int>(buff[0]);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	送信
			@param[in]	src	送信データ転送元
			@param[in]	len	送信長さ
			@return 送信した長さ
		*/
		//-----------------------------------------------------------------//
		size_t send(const void* src, size_t len) {
			if(fd_ < 0) return 0;

			return ::write(fd_, src, len);
		}


		bool send(char ch) {
			if(fd_ < 0) return false;

			char buff[1];
			buff[0] = ch;
			return send(buff, 1) == 1;
		}


		bool get_DCD() const {
			if(fd_ < 0) return false;

			int status;
			if(ioctl(fd_, TIOCMGET, &status) == -1) {
				return false;
			}

			return status & TIOCM_CAR;
		}


		bool get_CTS() const {
			if(fd_ < 0) return false;

			int status;
			if(ioctl(fd_, TIOCMGET, &status) == -1) {
				return false;
			}

			return status & TIOCM_CTS;
		}


		bool get_DSR() const {
			if(fd_ < 0) return false;

			int status;

			if(ioctl(fd_, TIOCMGET, &status) == -1) {
				return false;
			}

			return status & TIOCM_DSR;
		}


		bool enable_DTR(bool ena = true) {
			if(fd_ < 0) return false;

			int status;
			if(ioctl(fd_, TIOCMGET, &status) == -1) {
				return false;
			}

			if(ena) status |= TIOCM_DTR;
			else status &= ~TIOCM_DTR;

			if(ioctl(fd_, TIOCMSET, &status) == -1) {
				return false;
			}

			return true;
		}


		bool enable_RTS(bool ena = true) {
			if(fd_ < 0) return false;

			int status;
			if(ioctl(fd_, TIOCMGET, &status) == -1) {
				return false;
			}

			if(ena) status |= TIOCM_RTS;
			else status &= ~TIOCM_RTS;

			if(ioctl(fd_, TIOCMSET, &status) == -1) {
				return false;
			}

			return true;
		}

	};
}

