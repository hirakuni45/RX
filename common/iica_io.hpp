#pragma once
//=====================================================================//
/*!	@file
	@brief	RX グループ・IICA 制御 @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "vect.h"

/// F_PCKB はボーレートパラメーター計算で必要で、設定が無いとエラーにします。
#ifndef F_PCKB
#  error "iica_io.hpp requires F_PCKB to be defined"
#endif

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

		enum class event {
			none,
		};
		static event  event_;

		static INTERRUPT_FUNC void event_task_()
		{
		}

		static INTERRUPT_FUNC void recv_task_()
		{
		}

		static INTERRUPT_FUNC void send_task_()
		{
		}

		static INTERRUPT_FUNC void end_task_()
		{
		}

		static uint32_t intr_vec_(ICU::VECTOR v) { return static_cast<uint32_t>(v); }

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

			port_map::turn(IICA::get_peripheral());

			power_cfg::turn(IICA::get_peripheral());

			IICA::ICCR1.ICE = 0;
			IICA::ICCR1.IICRST = 1;
			IICA::ICCR1.ICE = 1;

			IICA::ICSER = 0x00;

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

			IICA::ICFER.TMOE = 1;  // TimeOut Enable

			if(level_) {
				set_interrupt_task(event_task_, static_cast<uint32_t>(IICA::get_eei_vec()));
				set_interrupt_task(recv_task_,  static_cast<uint32_t>(IICA::get_rxi_vec()));
				set_interrupt_task(send_task_,  static_cast<uint32_t>(IICA::get_txi_vec()));
				set_interrupt_task(end_task_,   static_cast<uint32_t>(IICA::get_tei_vec()));
			} else {
				set_interrupt_task(nullptr, static_cast<uint32_t>(IICA::get_eei_vec()));
				set_interrupt_task(nullptr, static_cast<uint32_t>(IICA::get_rxi_vec()));
				set_interrupt_task(nullptr, static_cast<uint32_t>(IICA::get_txi_vec()));
				set_interrupt_task(nullptr, static_cast<uint32_t>(IICA::get_tei_vec()));
			}

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
			@brief	送信
			@param[in]	adr	７ビットアドレス
			@param[in]	src	転送先
			@param[in]	len	受信バイト数
			@return 送信が完了した場合「true」
		 */
		//-----------------------------------------------------------------//
		bool send(uint8_t adr, const uint8_t* src, uint8_t len)
		{
			error_ = error::none;

			while(IICA::ICCR2.BBSY() != 0) {
				if(IICA::ICSR2.TMOF()) {
					IICA::ICSR2.TMOF = 0;
					error_ = error::bus_open;
					return false;
				}
			}

			IICA::ICCR2.ST = 1;

			bool ret = true;
			bool first = true;
			while(len > 0) {

				if(IICA::ICSR2.NACKF() != 0) {
					ret = false;
					break;
				}

				while(IICA::ICSR2.TDRE() == 0) ;

				if(first) {
					IICA::ICDRT = (adr << 1);
					first = false;
				} else {
					IICA::ICDRT = *src++;
					--len;
				}
			}

			while(IICA::ICSR2.TEND() == 0) ;

			IICA::ICSR2.STOP = 0;
			IICA::ICCR2.SP = 1;

			while(IICA::ICSR2.STOP() == 0) ;

			IICA::ICSR2.NACKF = 0;
			IICA::ICSR2.STOP = 0;

			return ret;
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
		bool recv(uint8_t adr, uint8_t* dst, uint8_t len)
		{
			error_ = error::none;

			while(IICA::ICCR2.BBSY() != 0) {
				if(IICA::ICSR2.TMOF()) {
					IICA::ICSR2.TMOF = 0;
					error_ = error::bus_open;
					return false;
				}
			}

			IICA::ICCR2.ST = 1;

			while(IICA::ICSR2.TDRE() == 0) ;

			IICA::ICDRT = (adr << 1) | 0x01;	// Slave Address

			while(IICA::ICSR2.RDRF() == 0) ;

			bool ret = true;
			int8_t da;
			if(IICA::ICSR2.NACKF() == 0) {

				da = IICA::ICDRR();	///< dummy read

				while(1) {

					while(IICA::ICSR2.RDRF() == 0) ;

					if(len <= 1) {
						break;
					}

					if(len <= 2) {
						IICA::ICMR3.WAIT = 1;
					}

					da = IICA::ICDRR();
					*dst++ = da;
					--len;
				}

				// NACK を返す必要がある場合
				if(IICA::ICMR3.RDRFS() == 0) {
					IICA::ICMR3.ACKWP = 1;
					IICA::ICMR3.ACKBT = 1;
					IICA::ICMR3.ACKWP = 0;
				}

				da = IICA::ICDRR();			// last read data
				if(len) {
					*dst++ = da;
					--len;
				}

				while(IICA::ICSR2.RDRF() == 0) ;

				IICA::ICSR2.STOP = 0;
				IICA::ICCR2.SP = 1;

				da = IICA::ICDRR();			// read data
				if(len) {
					*dst = da;
				}
				IICA::ICMR3.WAIT = 0;

			} else {
				IICA::ICSR2.STOP = 0;
				IICA::ICCR2.SP = 1;
				da = IICA::ICDRR();			///< dummy read
				ret = false;
			}

			while(IICA::ICSR2.STOP() == 0) {	// ICSR2.STOP(B3) == 1?
			}

			IICA::ICSR2.NACKF = 0;
			IICA::ICSR2.STOP = 0;

			return ret;
		}

	};

	template<class IICA> typename iica_io<IICA>::event iica_io<IICA>::event_;

}
