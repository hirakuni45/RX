#pragma once
//=====================================================================//
/*!	@file
	@brief	RX グループ・IICA 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <cstring>
#include "common/vect.h"
#include "common/renesas.hpp"
#include "common/format.hpp"
#include "common/delay.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  IICA 制御クラス（I2C)
		@param[in]	IICA	IICA 定義基底クラス 
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class IICA>
	class iica_io {
	public:
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I2C の速度タイプ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class speed : uint8_t {
			standard,	///< 100K b.p.s. (Standard mode)
			fast,		///< 400K b.p.s. (Fast mode)
			fast_plus,	///< 1M b.p.s. (Fast plus mode)
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I2C エラー・タイプ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class error : uint8_t {
			none,		///< エラー無し
			start,		///< スタート（初期化）
			bus_open,	///< バス・オープン
			address,	///< アドレス転送
			send_data,	///< 送信データ転送
			recv_data,	///< 受信データ転送
			stop,		///< ストップ・コンディション
		};

	private:
		uint8_t		level_;
		uint8_t		sadr_;
		uint8_t		speed_;
		error		error_;

		enum class event : uint8_t {
			NONE,
			AL,
			NACKF,
			TOMF,
			START,
			STOP,
		};

		struct intr_t {
			volatile event		event_;
			volatile uint8_t	firstb_;
			volatile bool		dummy_recv_;
			const uint8_t*		src_;
			uint8_t*			dst_;
			volatile uint16_t	len_;
			volatile uint16_t	send_id_;
			volatile uint16_t	send_id_back_;
			volatile uint16_t	recv_id_;
			volatile uint16_t	recv_id_back_;
			intr_t() : event_(event::NONE), firstb_(0), dummy_recv_(false),
				src_(nullptr), dst_(nullptr), len_(0),
				send_id_(0), send_id_back_(0), recv_id_(0), recv_id_back_(0) { }
		};
		static intr_t	intr_;

		static INTERRUPT_FUNC void event_task_()
		{
			switch(intr_.event_) {
			case event::NONE:
				break;
			case event::AL:
				break;
			case event::NACKF:
				IICA::ICIER.NAKIE = 0;
				if(intr_.dst_ != nullptr) {
					IICA::ICSR2.STOP = 0;
					IICA::ICCR2.SP = 1;
					volatile auto d = IICA::ICDRR();  // dummy read
				} else {
					IICA::ICIER.TIE = 0;
				}
				break;
			case event::TOMF:
				break;
			case event::START:
				break;
			case event::STOP:
				IICA::ICIER.SPIE = 0;
				IICA::ICSR2.NACKF = 0;
				IICA::ICSR2.STOP = 0;
				intr_.event_ = event::NONE;
				++intr_.send_id_;
				break;
			}
		}

		static INTERRUPT_FUNC void recv_task_()
		{
			if(intr_.dst_ == nullptr || intr_.len_ == 0) {
				IICA::ICIER.RIE = 0;
			} else {
				if(intr_.dummy_recv_) {
					volatile auto d = IICA::ICDRR();
					intr_.dummy_recv_ = false;
				} else {
					*intr_.dst_ = IICA::ICDRR();
					++intr_.dst_;
				   	--intr_.len_;
					if(intr_.len_ <= 1) {
						IICA::ICMR3.WAIT = 1;
					} else if(intr_.len_ == 0) {

					}
				}
			}
		}

		static INTERRUPT_FUNC void send_task_()
		{
			if(intr_.firstb_) {
				IICA::ICDRT = intr_.firstb_;
				intr_.firstb_ = 0;
				if(intr_.dst_ != nullptr) {  // recv
					IICA::ICIER.RIE = 1;
					intr_.event_ = event::NACKF;
					IICA::ICIER.NAKIE = 1;
					intr_.dummy_recv_ = true;
				}
			} else if(intr_.src_ != nullptr && intr_.len_ > 0) {
				IICA::ICDRT = *intr_.src_;
				++intr_.src_;
				--intr_.len_;
				if(intr_.len_ == 0) {
					intr_.src_ = nullptr;
					IICA::ICIER.TIE = 0;
					IICA::ICIER.TEIE = 1;
				}
			}
		}


		static INTERRUPT_FUNC void tend_task_()
		{
			IICA::ICSR2.STOP = 0;
			IICA::ICCR2.SP = 1;
			IICA::ICIER.TEIE = 0;
			intr_.event_ = event::STOP;
			IICA::ICIER.SPIE = 1;
		}


		static uint32_t intr_vec_(ICU::VECTOR v) { return static_cast<uint32_t>(v); }

		void sleep_() {
			asm("nop");
		}


		bool setup_start_() {
			int loop = 0;
			while(IICA::ICCR2.BBSY() != 0) {
#if 0
				if(IICA::ICSR2.TMOF()) {
					IICA::ICSR2.TMOF = 0;
					error_ = error::bus_open;
					return false;
				}
#endif
				utils::delay::micro_second(1);
				++loop;
				if(loop >= 1000) {
					return false;
				}
			}
			return true;
		}


		void setup_ackbt_() {
			IICA::ICMR3.ACKWP = 1;
			IICA::ICMR3.ACKBT = 1;
			IICA::ICMR3.ACKWP = 0;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	sadr	スレーブ・アドレス
		*/
		//-----------------------------------------------------------------//
		iica_io(uint8_t sadr = 0x00) : level_(0), sadr_(sadr), speed_(0), error_(error::none) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	動作開始
			@param[in]	spd_type	速度タイプ（クロックが 40MHz）
			@param[in]	level	割り込みレベル、０の場合ポーリング
			@return 速度範囲エラーの場合「false」	
		 */
		//-----------------------------------------------------------------//
		bool start(speed spd_type, uint8_t level = 0)
		{
			level_ = level;

			power_mgr::turn(IICA::PERIPHERAL);

			port_map::turn(IICA::PERIPHERAL);

			IICA::ICCR1.ICE = 0;
			IICA::ICCR1.IICRST = 1;
			IICA::ICCR1.ICE = 1;

			IICA::SARL0 = sadr_;
			IICA::SARU0 = 0x00;
			IICA::SARL1 = 0x00;
			IICA::SARU1 = 0x00;
			IICA::SARL2 = 0x00;
			IICA::SARU2 = 0x00;

			switch(spd_type) {
			case speed::standard:	///< 100K b.p.s. (Standard mode)
				IICA::ICMR1 = IICA::ICMR1.CKS.b(0b011) | IICA::ICMR1.BCWP.b();
				IICA::ICBRH = 0b11100000 | 19;
				IICA::ICBRL = 0b11100000 | 23;
				break;
			case speed::fast:		///< (50 clock) 400K b.p.s. (Fast mode)
				IICA::ICMR1 = IICA::ICMR1.CKS.b(0b001) | IICA::ICMR1.BCWP.b();
				IICA::ICBRH = 0b11100000 | 11;
				IICA::ICBRL = 0b11100000 | 25;
				break;
			case speed::fast_plus:	///< (40 clock) 1M b.p.s. (Fast plus mode)
				IICA::ICMR1 = IICA::ICMR1.CKS.b(0b000) | IICA::ICMR1.BCWP.b();
				IICA::ICBRH = 0b11100000 | 10;
				IICA::ICBRL = 0b11100000 | 21;
				break;
			default:
				error_ = error::start;
				return false;
			}

///			IICA::ICFER.TMOE = 1;  // TimeOut Enable

			if(level_ > 0) {
				icu_mgr::set_task(IICA::EE_VEC, event_task_);
				icu_mgr::set_task(IICA::RX_VEC, recv_task_);
				icu_mgr::set_task(IICA::TX_VEC, send_task_);
				icu_mgr::set_task(IICA::TE_VEC, tend_task_);
			} else {
				icu_mgr::set_task(IICA::EE_VEC, nullptr);
				icu_mgr::set_task(IICA::RX_VEC, nullptr);
				icu_mgr::set_task(IICA::TX_VEC, nullptr);
				icu_mgr::set_task(IICA::TE_VEC, nullptr);
			}
			IICA::ICIER = 0x00;
			icu_mgr::set_level(IICA::PERIPHERAL, level_);

			IICA::ICCR1.IICRST = 0;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	最終エラーの取得
			@return エラー・タイプ
		 */
		//-----------------------------------------------------------------//
		error get_last_error() const { return error_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	送信状態の検査
			@return 送信が完了なら「true」
		 */
		//-----------------------------------------------------------------//
		static bool get_send_state() { return intr_.send_id_ != intr_.send_id_back_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	受信割り込みIDを取得
			@return 受信割り込みID
		 */
		//-----------------------------------------------------------------//
		static bool get_recv_state() { return intr_.recv_id_ != intr_.recv_id_back_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	送信
			@param[in]	adr	７ビットアドレス
			@param[in]	src	転送先
			@param[in]	len	送信バイト数
			@param[in]	sync	非同期の場合「false」
			@return 送信が完了した場合「true」
		 */
		//-----------------------------------------------------------------//
		bool send(uint8_t adr, const uint8_t* src, uint16_t len, bool sync = true)
		{
			if(len == 0) return false;

			error_ = error::none;

			if(!setup_start_()) {
				error_ = error::start;
				return false;
			}

			bool ret = true;
			if(level_) {
				intr_.send_id_back_ = intr_.send_id_;
				intr_.firstb_ = adr << 1;
				intr_.src_ = src;
				intr_.len_ = len;
				intr_.event_ = event::NACKF;
				IICA::ICIER = IICA::ICIER() | IICA::ICIER.NAKIE.b() | IICA::ICIER.TIE.b();
				IICA::ICCR2.ST = 1;
				if(sync) {
					while(intr_.send_id_back_ == intr_.send_id_) sleep_();
					if(intr_.event_ != event::NONE) {
						error_ = error::send_data;
						ret = false;
					}
				}
			} else {
				IICA::ICCR2.ST = 1;
				bool first = true;
				while(len > 0) {

					if(IICA::ICSR2.NACKF() != 0) {
						ret = false;
						error_ = error::send_data;
						break;
					}

					if(IICA::ICSR2.TDRE() == 0) {
						continue;
					}

					if(first) {
						IICA::ICDRT = (adr << 1);
						first = false;
					} else {
						IICA::ICDRT = *src++;
						--len;
					}
				}
				if(ret) {
					while(IICA::ICSR2.TEND() == 0) ;
				}

				IICA::ICSR2.STOP = 0;
				IICA::ICCR2.SP = 1;

				while(IICA::ICSR2.STOP() == 0) {
				}

				IICA::ICSR2.NACKF = 0;
				IICA::ICSR2.STOP = 0;
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	送信
			@param[in]	adr	７ビットアドレス
			@param[in]	val	転送値
			@param[in]	src	転送先
			@param[in]	len	送信バイト数
			@param[in]	sync	非同期の場合「false」
			@return 送信が完了した場合「true」
		 */
		//-----------------------------------------------------------------//
		bool send(uint8_t adr, uint8_t val, const uint8_t* src, uint16_t len, bool sync = true)
		{
			uint8_t tmp[len + 1];
			tmp[0] = val;
			std::memcpy(&tmp[1], src, len);
			return send(adr, tmp, len + 1, sync);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	受信
			@param[in]	adr	７ビットアドレス
			@param[out]	dst	転送先
			@param[in]	len	受信バイト数
			@return 受信が完了した場合「true」
		 */
		//-----------------------------------------------------------------//
		bool recv(uint8_t adr, uint8_t* dst, uint16_t len)
		{
			if(len == 0) return false;

			error_ = error::none;

			if(!setup_start_()) {
				error_ = error::start;
				return false;
			}

			if(level_) {
				intr_.recv_id_back_ = intr_.recv_id_;
				intr_.firstb_ = (adr << 1) | 0x01;
				intr_.dst_ = dst;
				intr_.len_ = len;

				IICA::ICIER.TIE = 1;
				IICA::ICCR2.ST = 1;

			} else {

				IICA::ICCR2.ST = 1;
				while(IICA::ICSR2.TDRE() == 0) {
				}

				IICA::ICDRT = (adr << 1) | 0x01;
				while(IICA::ICSR2.RDRF() == 0) ;

				if(IICA::ICSR2.NACKF() != 0) {
					IICA::ICSR2.STOP = 0;
					IICA::ICCR2.SP = 1;
					volatile uint8_t tmp = IICA::ICDRR();

					while(IICA::ICSR2.STOP() == 0) ;

					IICA::ICSR2.NACKF = 0;
					IICA::ICSR2.STOP = 0;
					return false;
				}

				if(len <= 2) {
					IICA::ICMR3.WAIT = 1;
					if(len == 2) {
						volatile uint8_t tmp = IICA::ICDRR();  // dummy read
						while(IICA::ICSR2.RDRF() == 0) ;
					}
					setup_ackbt_();
					volatile uint8_t tmp = IICA::ICDRR();
					if(len == 2) {  // 1 バイトの場合ダミーリード
						*dst++ = tmp;
					}
					while(IICA::ICSR2.RDRF() == 0) ;
				} else {
					volatile uint8_t tmp = IICA::ICDRR();  // dummy read
					while(IICA::ICSR2.RDRF() == 0) ;

					while(len > 2) {
						if(len == 3) {
							IICA::ICMR3.WAIT = 1;
						}

						*dst++ = IICA::ICDRR();
						while(IICA::ICSR2.RDRF() == 0) ;
						--len;
					}
					setup_ackbt_();
					*dst++ = IICA::ICDRR();
					while(IICA::ICSR2.RDRF() == 0) ;
				}
				IICA::ICSR2.STOP = 0;
				IICA::ICCR2.SP = 1;
	
				*dst = IICA::ICDRR();

				IICA::ICMR3.WAIT = 0;

				while(IICA::ICSR2.STOP() == 0) ;
				IICA::ICSR2.NACKF = 0;
				IICA::ICSR2.STOP = 0;
			}
			return true;
		}
	};

	template<class IICA> typename iica_io<IICA>::intr_t iica_io<IICA>::intr_;
}
