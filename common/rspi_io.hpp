#pragma once
//=====================================================================//
/*!	@file
	@brief	RX グループ・RSPI I/O 制御 @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "vect.h"

/// F_PCKB は速度パラメーター計算で必要で、設定が無いとエラーにします。
#ifndef F_PCKB
#  error "sci_io.hpp requires F_PCKB to be defined"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RSPI 制御クラス
		@param[in]	RSPI	RSPI 定義クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class RSPI>
	class rspi_io {

		T		rspi_;

//		utility::fifo	recv_;
//		utility::fifo	send_;

		uint32_t	recv_lost_;
		uint32_t	xchg_dummy_;

		// 便宜上のスリープ
		void sleep_() { asm("nop"); }

	public:
		//----------------------------------------------------------------//
		/*!
			@brief  開始
			@param[in]	sync	[true」の場合クロック同期式（３線式）
			@param[in]	master	「true」の場合マスタ
			@param[in]	lsbf	LSB first の場合「true」
		*/
		//----------------------------------------------------------------//
		void start(bool sync, bool master, bool lsbf) {
			recv_lost_ = 0;
			xchg_dummy_ = 0xff;

			recv_.initialize(256);
			send_.initialize(1024);

			if(rspi_.get_chanel() == 0) {
				set_interrupt_task(task_SPRI0, ICU::VECTOR::SPRI0);
				set_interrupt_task(task_SPTI0, ICU::VECTOR::SPTI0);
				rspi_task[0].recv = &recv_;
				rspi_task[0].send = &send_;

				ICU::IPR.RSPI0 = 3;	// 割り込みレベルの設定
				ICU::IER.SPRI0 = true;
				ICU::IER.SPII0 = true;

				SYSTEM::MSTPCRB.MSTPB17 = 0;	///< RSPI0
				PORTC::DDR.B6 = 1;	///< MOSI_A
				PORTC::DDR.B5 = 1;	///< RSPCK_A
				PORTC::DDR.B7 = 0;	///< MISO_A
				PORTC::ICR.B7 = 1;	///< MISO_A(ICR=1)

				IOPORT::PFGSPI.RSPIS  = 0;	// SPI 端子選択
				IOPORT::PFGSPI.RSPCKE = 1;
				IOPORT::PFGSPI.MOSIE  = 1;
				IOPORT::PFGSPI.MISOE  = 1;
			} else {
				set_interrupt_task(task_SPRI1, ICU::VECTOR::SPRI1);
				set_interrupt_task(task_SPTI1, ICU::VECTOR::SPTI1);
				rspi_task[1].recv = &recv_;
				rspi_task[1].send = &send_;

				ICU::IPR.RSPI1 = 3;	// 割り込みレベルの設定
				ICU::IER.SPRI1 = true;
				ICU::IER.SPTI1 = true;

				SYSTEM::MSTPCRB.MSTPB16 = 0;	///< RSPI1
				PORT2::DDR.B6 = 1;	///< MOSI_B
				PORT2::DDR.B7 = 1;	///< RSPCK_B
				PORT3::DDR.B0 = 0;	///< MISO_B
				PORT3::ICR.B0 = 1;	///< MISO_B(ICR=1)

				IOPORT::PFHSPI.RSPIS  = 0;	// SPI 端子選択
				IOPORT::PFHSPI.RSPCKE = 1;
				IOPORT::PFHSPI.MOSIE  = 1;
				IOPORT::PFHSPI.MISOE  = 1;
			}

			rspi_.SPCR  = 0x00;	// stop RSPI
			rspi_.SPPCR = 0x00;	// Fixed idle value, disable loop-back
			rspi_.SPSCR = 0x00;	// disable sequence control
			rspi_.SPDCR = 0x20;	// SPLW=1 (long word access) 
			rspi_.SPCMD0 = 0x0700; // SPB=7(8bits width), CPHA=0, CPOL=0
			rspi_.SPCMD0.LSBF = lsbf;

			rspi_.SPCR.SPMS = sync;
			rspi_.SPCR.MSTR = master;

			rspi_.SPCR.SPE = 1;
		}


		//----------------------------------------------------------------//
		/*!
			@brief  SPI のクロックを設定
			@param[in]	clock	設定周波数
			@return 正常なら「true」
		*/
		//----------------------------------------------------------------//
		bool set_spi_clock(uint32_t clock) {
			uint32_t br = F_PCK / 2 / clock - 1;
			if(br > 255) return false;

		    rspi_.SPCR.SPE = 0;
		    rspi_.SPBR = static_cast<uint8_t>(br);
		    rspi_.SPCR.SPE = 1;
			return true;
		}


		//----------------------------------------------------------------//
		/*!
			@brief	リード・ライト（ポーリング）
			@param[in]	data	書き込みデータ
			@return 読み出しデータ
		*/
		//----------------------------------------------------------------//
		uint8_t xchg(uint8_t data)
		{
			rspi_.SPCR.SPTIE = 0;
			rspi_.SPCR.SPRIE = 0;
			rspi_.SPDR = static_cast<uint32_t>(data);
			while(rspi_.SPSR.SPRF() == 0) sleep_();
			uint8_t ret = static_cast<uint8_t>(rspi_.SPDR());
		    return ret;
		}


		//----------------------------------------------------------------//
		/*!
			@brief   バイト送信
			@param[in]	data	書き込みデータ
			@param[in]	pool	ポーリングの場合「true」
		*/
		//----------------------------------------------------------------//
		void put(uint8_t data, bool pool = false)
		{
			if(pool) {
				xchg(data);
			} else {
#if 0
				// ７／８以上サイズの場合は、１／８以下になるまで待つ
				// ※バッファの増減にヒステリシスを設ける
				if(send_.length() >= (send_.size() * 7 / 8)) {
					while(send_.length() != (send_.size() / 8)) sleep_();
				}
				RSPI.SPCR2.SPIIE = false;
				send_.put(data);
				RSPI.SPCR2.SPIIE = true;
#endif
				// ７／８以上サイズの場合は、１／８以下になるまで待つ
				// ※バッファの増減にヒステリシスを設ける
				if(send_.length() >= (send_.size() * 7 / 8)) {
// printf("\nWait: G:%d, P:%d\n", send_.get_pos(), send_.put_pos());
					while(send_.length() != (send_.size() / 8)) {
						sleep_();
						if(!rspi_.SPCR.SPTIE()) break;
					}
				}
				// 割り込み無効な場合はキック！
				if(!rspi_.SPCR.SPTIE()) {
					// 送信割り込みを許可して、最初のデータで割り込みをキック
					rspi_.SPCR.SPTIE = true;
					rspi_.SPDR = static_cast<uint32_t>(data);
				} else {
					send_.put(data);
				}
			}
		}


		//----------------------------------------------------------------//
		/*!
			@brief  バイト読み出し
			@return 読み出しデータ
			@param[in]	pool	ポーリングの場合「true」
		*/
		//----------------------------------------------------------------//
		uint8_t get(bool pool = false) {
			if(pool) {
				return xchg(xchg_dummy_);
			} else {
				while(recv_.length() == 0) sleep_();
				return recv_.get();
			}
		}


		//----------------------------------------------------------------//
		/*!
			@brief  送信バッファのスペースを返す
			@return スペース
		*/
		//----------------------------------------------------------------//
		uint16_t send_space() const {
//			return send_.size() - send_.length();
			return 0;
		}


		//----------------------------------------------------------------//
		/*!
			@brief  マルチバイトの送信
			@param[in]	buff	送信データ
			@param[in]	len		バイト数
			@param[in]	pool	ポーリングの場合「true」
		*/
		//----------------------------------------------------------------//
		void send(const uint8_t* buff, uint32_t len, bool pool = false) {
			for(uint32_t i = 0; i < len; ++i) {
				put(*buff++, pool);
			}
		}


		//----------------------------------------------------------------//
		/*!
			@brief  マルチバイトの受信を許可（割り込み処理）
			@param[in]	f	不許可の場合「false」
		*/
		//----------------------------------------------------------------//
		void recv_enable(bool f = true) {
			rspi_.SPCR.SPRIE = f;
		}


		//----------------------------------------------------------------//
		/*!
			@brief  受信データの長さを返す
			@return スペース
		*/
		//----------------------------------------------------------------//
		uint16_t recv_length() const {
			return recv_.length();
		}


		//----------------------------------------------------------------//
		/*!
			@brief  マルチバイトの受信
			@param[out]	buff	受信データ
			@param[in]	len		バイト数
			@param[in]	pool	ポーリングの場合「true」
		*/
		//----------------------------------------------------------------//
		void recv(uint8_t* buff, uint32_t len, bool pool = false) {
			for(uint32_t i = 0; i < len; ++i) {
				*buff++ = get(pool);
			}
		}
	};
}
