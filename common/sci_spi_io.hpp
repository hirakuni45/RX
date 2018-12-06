#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ・SCI/SPI I/O 制御 @n
			※現在、実装中で「未完」となっている。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"
#include "common/vect.h"

/// F_PCLKB はボーレートパラメーター計算に必要で、設定が無いとエラーにします。
#ifndef F_PCLKB
#  error "sci_spi_io.hpp requires F_PCLKB to be defined"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCI/SPI I/O 制御クラス
		@param[in]	SCI		SCI 型
		@param[in]	RBF		受信バッファクラス
		@param[in]	SBF		送信バッファクラス
		@param[in]	PSEL	ポート選択
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SCI, class RBF, class SBF, port_map::option PSEL = port_map::option::FIRST>
	class sci_spi_io {

		static RBF	recv_;
		static SBF	send_;

		uint8_t		level_;

		// ※マルチタスクの場合適切な実装をする
		void sleep_() noexcept { asm("nop"); }

#if 0
		static INTERRUPT_FUNC void recv_task_()
		{
			bool err = false;
			if(SCI::SSR.ORER()) {	///< 受信オーバランエラー状態確認
				SCI::SSR.ORER = 0;	///< 受信オーバランエラークリア
				err = true;
			}
			///< フレーミングエラー/パリティエラー状態確認
			if(SCI::SSR() & (SCI::SSR.FER.b() | SCI::SSR.PER.b())) {
				// エラーフラグの消去
				SCI::SSR.FER = 0;
				SCI::SSR.PER = 0;
				err = true;
			}
			volatile uint8_t data = SCI::RDR();
			if(!err) {
				recv_.put(data);
			}
		}


		static INTERRUPT_FUNC void send_task_()
		{
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
			if(send_.length() > 0) {
				SCI::TDR = send_.get();
			}
			if(send_.length() == 0) {
				SCI::SCR.TIE = 0;
				send_stall_ = true;
			}
#else
			SCI::TDR = send_.get();
			if(send_.length() == 0) {
				SCI::SCR.TEIE = 0;
			}
#endif
		}


		void set_vector_(ICU::VECTOR rx_vec, ICU::VECTOR tx_vec) noexcept
		{
			if(level_) {
				icu_mgr::set_task(rx_vec, recv_task_);
				icu_mgr::set_task(tx_vec, send_task_);
			} else {
				icu_mgr::set_task(rx_vec, nullptr);
				icu_mgr::set_task(tx_vec, nullptr);
			}
		}

		void set_intr_() noexcept
		{
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
			set_vector_(SCI::get_rx_vec(), SCI::get_tx_vec());
#else
			set_vector_(SCI::get_rx_vec(), SCI::get_te_vec());
#endif
			icu_mgr::set_level(SCI::get_peripheral(), level_);
		}
#endif

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		sci_spi_io() noexcept : level_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  簡易 SPI を有効にする
			@param[in]	bps	ビットレート
			@param[in]	level	割り込みレベル（０の場合ポーリング）
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t bps, uint8_t level = 0) noexcept
		{
			level_ = level;

			power_cfg::turn(SCI::get_peripheral());

			SCI::SCR = 0x00;			// TE, RE disable.

			uint32_t brr = F_PCLKB / bps / 2;
			if(brr & 1) { brr >>= 1; ++brr; }
			else { brr >>= 1; }
			uint8_t cks = 0;
			while(brr > 256) {
				brr >>= 2;
				++cks;
			}
			if(cks > 3 || brr > 256) return false;

			set_intr_();

			// LSB(0), MSB(1) first
			SCI::SCMR.SDIR = 1;

			SCI::SIMR1.IICM = 0;
			SCI::SMR = cks | SCI::SMR.CM.b();
			SCI::SPMR.SSE = 0;		///< SS 端子制御しない「０」

			if(master) {
				SCI::SPMR.MSS = 0;
			} else {
				SCI::SPMR.MSS = 1;
			}

			// クロックタイミング種別選択
			SCI::SPMR.CKPOL = 0;
			SCI::SPMR.CKPH  = 0;

			if(brr) --brr;
			SCI::BRR = static_cast<uint8_t>(brr);

			uint8_t scr = 0;
			if(master) {
				scr = SCI::SCR.CKE.b(0b01);
			} else {
				scr = SCI::SCR.CKE.b(0b10);
			}

			if(level_) {
				SCI::SCR = SCI::SCR.RIE.b() | SCI::SCR.TE.b() | SCI::SCR.RE.b() | scr;
			} else {
				SCI::SCR = SCI::SCR.TE.b() | SCI::SCR.RE.b() | scr;
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  送受信（SPI）
			@param[in]	ch	送信データ
			@return	受信データ
		*/
		//-----------------------------------------------------------------//
		inline uint8_t xchg(uint8_t ch = 0xff) noexcept
		{
			if(level_) {
				return 0;
			} else {
				SCI::TDR = ch;
				while(recv_length() == 0) sleep_();
				return SCI::RDR();
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ブロック送信（SPI）
			@param[in]	src	送信ソース
			@param[in]	siz	送信サイズ
		*/
		//-----------------------------------------------------------------//
		void send(const void* src, uint32_t siz) noexcept
		{
			const uint8_t* p = static_cast<const uint8_t*>(src);
			auto end = p + siz;
			while(p < end) {
				xchg(*p);
				++p;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ブロック受信（SPI）
			@param[out]	dst	受信先
			@param[in]	siz	受信サイズ
		*/
		//-----------------------------------------------------------------//
		void recv(void* dst, uint32_t siz) noexcept
		{
			uint8_t* p = static_cast<uint8_t*>(dst);
			auto end = p + siz;
			while(p < end) {
				*p = xchg();
				++p;
			}
		}
	};

	// テンプレート関数、実態の定義
	template<class SCI, class RBF, class SBF, port_map::option PSEL>
		RBF sci_spi_io<SCI, RBF, SBF, PSEL>::recv_;
	template<class SCI, class RBF, class SBF, port_map::option PSEL>
		SBF sci_spi_io<SCI, RBF, SBF, PSEL>::send_;
}
