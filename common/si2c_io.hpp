#pragma once
//=====================================================================//
/*!	@file
	@brief	ソフト制御 I2C テンプレートクラス @n
			※ポート定義は、オープンドレイン指定が可能な事 @n
			※速度指定は、正確ではなく目安程度 @n
			※「FAST_PLUS」は選択出来ない、エラーとなる
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstdint>
#include "common/delay.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  I2C テンプレートクラス @n
		@param[in]	SDA	SDA ポート定義クラス
		@param[in]	SCL	SCL ポート定義クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SDA, class SCL>
	class si2c_io {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I2C の速度タイプ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class SPEED : uint8_t {
			STANDARD,	///< 100K b.p.s. (Standard mode)
			FAST,		///< 400K b.p.s. (Fast mode)
			FAST_PLUS,	///< 1M b.p.s. (Fast plus mode)
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I2C のエラー
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ERROR : uint8_t {
			NONE,		///< エラー無し
			START,		///< スタート（初期化）
			BUS_OPEN,	///< バス・オープン
			ADDRESS,	///< アドレス転送
			SEND_DATA,	///< 送信データ転送
			RECV_DATA,	///< 受信データ転送
			STOP,		///< ストップ・コンディション
		};

	private:
		uint8_t		clock_;
		ERROR		error_;
		uint16_t	busy_;

		static const uint8_t slow_clock_ = 10 / 2;
		static const uint8_t fast_clock_ = 4 / 2;

		void start_() const {
			SDA::P = 0;
			utils::delay::micro_second(clock_);
			SCL::P = 0;
			utils::delay::micro_second(clock_);
		}


		bool ack_() const {
			SDA::P = 1;
			utils::delay::micro_second(clock_);
			SCL::P = 1;
			SDA::DIR = 0;
			utils::delay::micro_second(clock_);
			bool f = SDA::P();
			SDA::P = 0;
			SDA::DIR = 1;
			SCL::P = 0;
			return f;
		}


		void out_ack_(bool b) const {
			utils::delay::micro_second(clock_);
			SDA::P = b;
			SCL::P = 1;
			utils::delay::micro_second(clock_);
			SCL::P = 0;
		}


		bool wait_() const {
			uint16_t cnt = busy_;
			SCL::DIR = 0;
			while(SCL::P() == 0) {
				utils::delay::micro_second(1);
				if(cnt) {
					--cnt;
				} else {
					SCL::DIR = 1;
					return false;  // wait stall
				}
			}
			SCL::DIR = 1;
			return true;
		}


		void stop_() const {
			utils::delay::micro_second(clock_);
			SCL::P = 1;
			utils::delay::micro_second(clock_);
			SDA::P = 1;
		}


		bool write_(uint8_t val, bool sync) const {
			for(uint8_t n = 0; n < 8; ++n) {
				SDA::P = (val & 0x80) != 0 ? 1 : 0;
				utils::delay::micro_second(clock_);
				SCL::P = 1;
				if(n == 0 && sync) {
					if(!wait_()) return false;
				}
				val <<= 1;
				utils::delay::micro_second(clock_);
				SCL::P = 0;
			}
			return true;
		}


		bool write_(uint8_t data) const {
			if(!write_(data, true)) {
				stop_();
				return false;
			}
			if(ack_()) {
				stop_();
				return false;
			}
			return true;
		}


		bool write_(const uint8_t* src, uint8_t num) const {
			for(uint8_t n = 0; n < num; ++n) {
				if(!write_(*src, true)) {
					stop_();
					return false;
				}
				++src;
				if(ack_()) {
					stop_();
					return false;
				}
			}
			return true;
		}


		bool read_(uint8_t& val, bool sync) const {
			SDA::DIR = 0;
			for(uint8_t n = 0; n < 8; ++n) {
				utils::delay::micro_second(clock_);
				val <<= 1;
				SCL::P = 1;
				if(n == 0 && sync) {
					if(!wait_()) {
						SDA::DIR = 1;
						return false;
					}
				}
				utils::delay::micro_second(clock_);
				if(SDA::P()) val |= 1;
				SCL::P = 0;
			}
			SDA::DIR = 1;
			return true;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		si2c_io() : clock_(slow_clock_), error_(ERROR::NONE), busy_(200) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  初期化
			@param[in]	spd		スピード
			@param[in]	pullup	プルアップを有効にする場合「true」
			@return 成功なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start(SPEED spd, bool pullup = false)
		{
			SCL::OD = 1;
			SDA::OD = 1;
			if(pullup) {
				SCL::PU = 1;
				SDA::PU = 1;
			}
			SCL::DIR = 1;
			SDA::DIR = 1;
			SCL::P = 1;
			SDA::P = 1;
			if(spd == SPEED::STANDARD) {
				set_standard();
			} else if(spd == SPEED::FAST) {
				set_fast();
			} else {
				error_ = ERROR::START;
				return false;
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  クロック設定
			@param[in]	clock	パルス５０％待ち時間（単位マイクロ秒）
		*/
		//-----------------------------------------------------------------//
		void set_clock(uint8_t clock) { clock_ = clock; }


		//-----------------------------------------------------------------//
		/*!
			@brief  標準速度指定（maybe 100KBPS）
		*/
		//-----------------------------------------------------------------//
		void set_standard() { clock_ = slow_clock_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  高速指定（maybe 400KBPS）
		*/
		//-----------------------------------------------------------------//
		void set_fast() { clock_ = fast_clock_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  スレーブデバイスの「待ち」時間の最大値を設定
			@param[in]	busy	待ち時間（単位マイクロ秒）
		*/
		//-----------------------------------------------------------------//
		void set_busy(uint16_t busy) { busy_ = busy; }


		//-----------------------------------------------------------------//
		/*!
			@brief	最終エラーの取得
			@return エラー・タイプ
		 */
		//-----------------------------------------------------------------//
		ERROR get_last_error() const { return error_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  受信（リード）
			@param[in] address スレーブアドレス（７ビット）
			@param[out]	dst	先
			@param[in]	num	数
			@return 失敗なら「false」が返る
		*/
		//-----------------------------------------------------------------//
		bool recv(uint8_t address, uint8_t* dst, uint8_t num) {
			start_();
			write_((address << 1) | 1, false);
			if(ack_()) {
				stop_();
				error_ = ERROR::ADDRESS;
				return false;
			}

			for(uint8_t n = 0; n < num; ++n) {
				if(!read_(*dst, true)) {
					stop_();
					error_ = ERROR::RECV_DATA;
					return false;
				}
				bool f = 0;
				if(n == (num - 1)) f = 1;
				out_ack_(f);
				++dst;
			}
			stop_();
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  送信（ライト）
			@param[in] address スレーブアドレス（７ビット）
			@param[in]	src	元
			@param[in]	num	数
			@return 失敗なら「false」が返る
		*/
		//-----------------------------------------------------------------//
		bool send(uint8_t address, const uint8_t* src, uint8_t num) {
			start_();
			write_(address << 1, false);
			if(ack_()) {
				stop_();
				error_ = ERROR::ADDRESS;
				return false;
			}

			if(!write_(src, num)) {
				stop_();
				error_ = ERROR::SEND_DATA;
				return false;
			}
			stop_();
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  送信（ライト）
			@param[in] address スレーブアドレス（７ビット）
			@param[in]	first	ファーストデータ
			@param[in]	src	元
			@param[in]	num	数
			@return 失敗なら「false」が返る
		*/
		//-----------------------------------------------------------------//
		bool send(uint8_t address, uint8_t first, const uint8_t* src, uint8_t num) {
			start_();
			write_(address << 1, false);
			if(ack_()) {
				stop_();
				error_ = ERROR::ADDRESS;
				return false;
			}

			if(!write_(first)) {
				stop_();
				error_ = ERROR::SEND_DATA;
				return false;
			}

			if(!write_(src, num)) {
				stop_();
				error_ = ERROR::SEND_DATA;
				return false;
			}
			stop_();
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  送信（ライト）
			@param[in] address スレーブアドレス（７ビット）
			@param[in]	first	ファースト・データ
			@param[in]	second	セカンド・データ
			@param[in]	src	元
			@param[in]	num	数
			@return 失敗なら「false」が返る
		*/
		//-----------------------------------------------------------------//
		bool send(uint8_t address, uint8_t first, uint8_t second, const uint8_t* src, uint8_t num) {
			start_();
			write_(address << 1, false);
			if(ack_()) {
				stop_();
				error_ = ERROR::ADDRESS;
				return false;
			}

			if(!write_(first)) {
				stop_();
				error_ = ERROR::SEND_DATA;
				return false;
			}
			if(!write_(second)) {
				stop_();
				error_ = ERROR::SEND_DATA;
				return false;
			}
			if(!write_(src, num)) {
				stop_();
				error_ = ERROR::SEND_DATA;
				return false;
			}
			stop_();
			return true;
		}
	};
}
