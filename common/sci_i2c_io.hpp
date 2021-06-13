#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ SCI 簡易 I2C 制御 @n
			※RX600 シリーズでは、グループ割り込みとして TEIx を共有する @n
			ので、割り込みレベルには注意する事（上書きされる）@n
			※現在、マスターモードのみ実装
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"
#include "common/fixed_fifo.hpp"
#include "common/vect.h"
#include "common/i2c_base.hpp"

/// F_PCLKB はボーレートパラメーター計算に必要で、設定が無いとエラーにします。
#ifndef F_PCLKB
#  error "sci_i2c_io.hpp requires F_PCLKB to be defined"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCI/I2C 構造体
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct sci_i2c_t {

		enum class TASK : uint8_t {
			IDLE,

			START_SEND,		// start send
			SEND_FIRST,		// send 1st
			SEND_DATA,		// send data
			STOP_SEND,		// stop condition

			START_RECV,		// start recv
			RECV_DATA_PRE,	// recv data pre (first 1)
			RECV_DATA,		// recv data
			STOP_RECV,		// stop for recv

		};

		uint8_t		adr_;
		uint8_t*	dst_;
		uint16_t	len_;
		i2c_base::FUNC_TYPE		func_;
		sci_i2c_t(uint8_t adr = 0) noexcept : adr_(adr), dst_(nullptr), len_(0), func_(nullptr)
			{ }
	};
	// I2C の最大コマンド受付数は（１６－１）個
	typedef utils::fixed_fifo<sci_i2c_t, 16> I2C_BUFF;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCI I2C I/O 制御クラス
		@param[in]	SCI		SCI 型
		@param[in]	RBF		受信バッファクラス
		@param[in]	SBF		送信バッファクラス
		@param[in]	PSEL	ポート選択
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SCI, class RBF, class SBF, port_map::ORDER PSEL = port_map::ORDER::FIRST>
	class sci_i2c_io : public i2c_base {
	public:

	private:
		static RBF	recv_;
		static SBF	send_;

		uint8_t		level_;
		ERROR		error_;
		uint16_t	i2c_loop_;

		static volatile sci_i2c_t::TASK	task_;
		static volatile uint8_t	state_;
		static I2C_BUFF	i2c_buff_;

		// ※マルチタスクの場合適切な実装をする
		void sleep_() noexcept { asm("nop"); }

		void Print(sci_i2c_t::TASK task) const
		{
			switch(task) {
			case sci_i2c_t::TASK::IDLE:
				utils::format("IDLE");
				break;
			case sci_i2c_t::TASK::START_SEND:
				utils::format("START_SEND 0b%07b, (%d)")
					% static_cast<uint16_t>(i2c_buff_.get_at().adr_) % send_.length();
				break;
			case sci_i2c_t::TASK::SEND_DATA:
				utils::format("SEND_DATA (%d)") % send_.length();
				break;
			case sci_i2c_t::TASK::START_RECV:
				utils::format("START_RECV 0b%07b, (%d)")
					% static_cast<uint16_t>(i2c_buff_.get_at().adr_) % recv_.length();
				break;
			case sci_i2c_t::TASK::RECV_DATA_PRE:
				utils::format("RECV_DATA_PRE");
				break;
			case sci_i2c_t::TASK::RECV_DATA:
				utils::format("RECV_DATA");
				break;
			case sci_i2c_t::TASK::STOP_RECV:
				utils::format("STOP_RECV");
				break;
			case sci_i2c_t::TASK::STOP_SEND:
				utils::format("STOP_SEND");
				break;
			default:
				break;
			}
			utils::format("\n");
		}


		static void i2c_service_()
		{
			const auto& t = i2c_buff_.get_at();
			switch(task_) {
			case sci_i2c_t::TASK::IDLE:
				break;
			case sci_i2c_t::TASK::START_SEND:
				SCI::SIMR3 = SCI::SIMR3.IICSTIF.b(0) |
							 SCI::SIMR3.IICSCLS.b(0b00) | SCI::SIMR3.IICSDAS.b(0b00);				
				SCI::TDR = t.adr_ << 1;  // R/W = 0 (write)
				task_ = sci_i2c_t::TASK::SEND_FIRST;
				break;
			case sci_i2c_t::TASK::SEND_FIRST:
				if(SCI::SISR.IICACKR()) {
					if(send_.length() > 0) {
						SCI::TDR = send_.get();
						task_ = sci_i2c_t::TASK::SEND_DATA;
						break;
					} else {
						SCI::SIMR3 = SCI::SIMR3.IICSTPREQ.b(1) |
								 SCI::SIMR3.IICSCLS.b(0b00) | SCI::SIMR3.IICSDAS.b(0b00);
						task_ = sci_i2c_t::TASK::STOP_SEND;
					}
				} else {
					SCI::SIMR3 = SCI::SIMR3.IICSTPREQ.b(1) |
								 SCI::SIMR3.IICSCLS.b(0b00) | SCI::SIMR3.IICSDAS.b(0b00);
					task_ = sci_i2c_t::TASK::STOP_SEND;
				}
				break;
			case sci_i2c_t::TASK::SEND_DATA:
				if(send_.length() > 0) {
					SCI::TDR = send_.get();
				} else {
					SCI::SIMR3 = SCI::SIMR3.IICSTPREQ.b(1) |
								 SCI::SIMR3.IICSCLS.b(0b00) | SCI::SIMR3.IICSDAS.b(0b00);
					task_ = sci_i2c_t::TASK::STOP_SEND;
				}
				break;
			case sci_i2c_t::TASK::STOP_SEND:
				if(t.func_ != nullptr) t.func_();
				i2c_buff_.get_go();
				SCI::SIMR3 = SCI::SIMR3.IICSTIF.b(0) |
							 SCI::SIMR3.IICSCLS.b(0b11) | SCI::SIMR3.IICSDAS.b(0b11);
				task_ = sci_i2c_t::TASK::IDLE;
				SCI::SCR.TEIE = 0;
				SCI::SCR.TIE = 0;
				break;


			case sci_i2c_t::TASK::START_RECV:
				SCI::TDR = (t.adr_ << 1) | 1;  // R/W = 1 (read)
				task_ = sci_i2c_t::TASK::RECV_DATA_PRE;
				SCI::SCR.TIE = 1;
				break;

			case sci_i2c_t::TASK::RECV_DATA_PRE:
				if(SCI::SISR.IICACKR() != 0) {
					SCI::SCR.RIE = 0;
					task_ = sci_i2c_t::TASK::STOP_RECV;
					state_ = static_cast<uint8_t>(ERROR::ACK);
					SCI::SCR.TEIE = 1;
				} else {
					if(t.len_ > 1) {
						SCI::SIMR2.IICACKT = 0;
					} else {
						SCI::SIMR2.IICACKT = 1;
					}
					SCI::TDR = 0xff;  // dummy data
					task_ = sci_i2c_t::TASK::RECV_DATA;
					SCI::SCR.RIE = 1;
				}
				break;
			case sci_i2c_t::TASK::RECV_DATA:
					if(t.len_ == (recv_.length() + 1)) {
						SCI::SIMR2.IICACKT = 1;
					}
					recv_.put(SCI::RDR());
					SCI::TDR = 0xff;  // dummy data
					if(t.len_ == recv_.length()) {
						SCI::SCR.RIE = 0;
						task_ = sci_i2c_t::TASK::STOP_RECV;
						SCI::SCR.TEIE = 1;
					}
				break;
			case sci_i2c_t::TASK::STOP_RECV:
				{
					uint8_t* p = t.dst_;
					for(uint16_t i = 0; i < t.len_; ++i) {
						*p++ = recv_.get();
					}
				}

			default:
				break;
			}
		}


		static INTERRUPT_FUNC void recv_task_()
		{
			i2c_service_();
		}


		static INTERRUPT_FUNC void send_task_()
		{
			i2c_service_();
		}


		static INTERRUPT_FUNC void i2c_condition_task_()
		{
			i2c_service_();
		}


		bool i2c_start_() noexcept
		{
			SCI::SIMR3 = SCI::SIMR3.IICSTAREQ.b() |
						 SCI::SIMR3.IICSCLS.b(0b01) | SCI::SIMR3.IICSDAS.b(0b01);
			uint32_t n = 0;
			bool ret = true;
			while(SCI::SIMR3.IICSTIF() == 0) {
				++n;
				if(n >= i2c_loop_) {
					ret = false;
					break;
				}
			}
			SCI::SIMR3 = SCI::SIMR3.IICSCLS.b(0b00) | SCI::SIMR3.IICSDAS.b(0b00);
			return ret;
		}


		bool i2c_stop_() noexcept
		{
			SCI::SIMR3 = SCI::SIMR3.IICSTPREQ.b() |
						 SCI::SIMR3.IICSCLS.b(0b01) | SCI::SIMR3.IICSDAS.b(0b01);
			uint32_t n = 0;
			bool ret = true;
			while(SCI::SIMR3.IICSTIF() == 0) {
				++n;
				if(n >= i2c_loop_) {
					ret = false;
					break;
				}
			}
			SCI::SIMR3 = SCI::SIMR3.IICSCLS.b(0b11) | SCI::SIMR3.IICSDAS.b(0b11);
			return ret;
		}


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		sci_i2c_io() noexcept : level_(0), error_(ERROR::NONE), i2c_loop_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  最終エラーコードを取得
			@return 最終エラーコード
		*/
		//-----------------------------------------------------------------//
		ERROR get_last_error() const noexcept { return error_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C を有効にする
			@param[in]	spd		スピード・タイプ
			@param[in]	mode	動作モード（マスターモードのみ）
			@param[in]	level	割り込みレベル（０の場合ポーリング）
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool start(SPEED spd, MODE mode, uint8_t level = 0) noexcept
		{
			// I2C オプションが無い場合エラー
			if(PSEL == port_map::ORDER::FIRST_I2C || PSEL == port_map::ORDER::SECOND_I2C || PSEL == port_map::ORDER::THIRD_I2C) {
			} else {
				return false;
			}
// 割り込み動作に不具合があるので、強制的にポーリングとする。
level = 0;
			uint32_t clk = static_cast<uint32_t>(spd);
			uint32_t brr = F_PCLKB * 8 / clk;
			uint32_t mddr = ((brr & 0xff00) << 8) / brr;
			brr >>= 8;
			if(brr >= 256 || brr <= 1) {
				return false;
			}
			--brr;
//			utils::format("BRR: %d, MDDR: %d\n")
//				% static_cast<uint16_t>(brr) % static_cast<uint16_t>(mddr);

			// ポーリング時の I2C ループ定数
			// 200 ---> I2C Start/Stop loop for STANDARD
			// 5 ---> マージン倍率
			i2c_loop_ = 200 * 5;

			level_ = level;

			power_mgr::turn(SCI::PERIPHERAL);

			SCI::SCR = 0x00;		// TE, RE disable. CKE = 0
			port_map::turn(SCI::PERIPHERAL, true, PSEL);

			SCI::SIMR3 = SCI::SIMR3.IICSDAS.b(0b11) | SCI::SIMR3.IICSCLS.b(0b11);
			SCI::SMR   = 0x00;
			SCI::SCMR  = SCI::SCMR.SDIR.b();
			SCI::BRR   = brr;
			SCI::MDDR  = mddr;

			bool brme = false;
			if(mddr >= 128) brme = true;
			// NFEN: ノイズ除去有効の場合「１」
			SCI::SEMR = SCI::SEMR.NFEN.b(0) | SCI::SEMR.BRME.b(brme);
			SCI::SNFR = SCI::SNFR.NFCS.b(0b001);  // 1/1
			SCI::SIMR1 = SCI::SIMR1.IICM.b() | SCI::SIMR1.IICDL.b(0b00000);
			SCI::SIMR2 = SCI::SIMR2.IICACKT.b() | SCI::SIMR2.IICCSC.b() | SCI::SIMR2.IICINTM.b();
			SCI::SPMR = 0x00;

			if(level_ > 0) {
				task_ = sci_i2c_t::TASK::IDLE;

				// RXI, TXI の設定
				icu_mgr::set_interrupt(SCI::RX_VEC, recv_task_, level_);
				icu_mgr::set_interrupt(SCI::TX_VEC, send_task_, level_);

				// TEIx (STI interrupt)
				auto grp = ICU::get_group_vector(SCI::TE_VEC);
				if(grp == ICU::VECTOR::NONE) {  // NONE が返ると通常割り込み
					// 通常ベクターの場合、割り込み関数を登録、
					// tev がグループベクターの場合にコンパイルエラーになるので回避
					icu_mgr::set_task(static_cast<ICU::VECTOR>(SCI::TE_VEC), i2c_condition_task_);
					icu_mgr::set_level(static_cast<ICU::VECTOR>(SCI::TE_VEC), level_);
				} else {
					// グループベクターの場合、通常関数を登録
					icu_mgr::set_level(grp, level_);
					icu_mgr::install_group_task(SCI::TE_VEC, i2c_service_);
					utils::format("install group vector for TE (LVL:%d)\n") % static_cast<uint16_t>(level_);
				}
			}
			SCI::SCR = SCI::SCR.RE.b() | SCI::SCR.TE.b();

			error_ = ERROR::NONE;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  同期 @n
					※ポーリング時スルー
		*/
		//-----------------------------------------------------------------//
		void sync() noexcept
		{
			if(level_ == 0) return;

			utils::format("SCI-I2C Start sync...\n");
			auto task = task_;
			utils::format("Begin: ");
			Print(task);
			while(task_ != sci_i2c_t::TASK::IDLE) {
				if(task != task_) {
					utils::format("End: ");
					Print(task);
					task = task_;
					utils::format("Begin: ");
					Print(task);
				}
			}
			if(state_ != 0) {
				utils::format("State: %d\n") % static_cast<uint16_t>(state_);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  データ送信
			@param[in]	adr		I2C アドレス（下位７ビット）
			@param[in]	src		送信データ
			@param[in]	len		送信長
			@param[in]	func	送信終了タスク
			@return 送信正常終了なら「true」
		*/
		//-----------------------------------------------------------------//
		bool send(uint8_t adr, const void* src, uint16_t len, FUNC_TYPE func = nullptr) noexcept
		{
			if(src == nullptr || len == 0) return false;

			if(level_ == 0) {  // ポーリング動作時
				if(!i2c_start_()) {
					error_ = ERROR::START;
					i2c_stop_();
					return false;
				}

				SCI::TDR = adr << 1;  // R/W = 0 (write)
				while(SCI::SSR.TDRE() == 0) {
					sleep_();
				}
				while(SCI::SSR.TEND() == 0) {
					sleep_();
				}

				const uint8_t* p = static_cast<const uint8_t*>(src);
				while(len > 0) {
					if(SCI::SISR.IICACKR()) {
						break;
					}
					SCI::TDR = *p++;
					--len;

					while(SCI::SSR.TDRE() == 0) {
						sleep_();
					}
					while(SCI::SSR.TEND() == 0) {
						sleep_();
					}
				}

				if(!i2c_stop_()) {
					error_ = ERROR::STOP;
					return false;
				}
				if(func != nullptr) func();
				error_ = ERROR::NONE;
			} else {  // 割り込み動作時
				const uint8_t* p = static_cast<const uint8_t*>(src);
				for(uint32_t i = 0; i < len; ++i) {
					send_.put(*p);
					++p;
				}
				sci_i2c_t t;
				t.adr_ = adr;
				t.dst_ = nullptr;
				t.len_ = len;
				t.func_ = func;
				i2c_buff_.put(t);
				if(task_ == sci_i2c_t::TASK::IDLE) {
					state_ = 0;
					task_ = sci_i2c_t::TASK::START_SEND;
					SCI::SIMR3 = SCI::SIMR3.IICSTAREQ.b() |
								 SCI::SIMR3.IICSCLS.b(0b01) | SCI::SIMR3.IICSDAS.b(0b01);
					SCI::SCR.TIE = 1;
					SCI::SCR.TEIE = 1;
				}
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  データ受信
			@param[in]	adr		I2C アドレス（下位７ビット）
			@param[in]	dst		受信データ
			@param[in]	len		受信長
			@param[in]	func	受信終了関数
			@return 送信正常終了なら「true」
		*/
		//-----------------------------------------------------------------//
		bool recv(uint8_t adr, void* dst, uint16_t len, FUNC_TYPE func = nullptr) noexcept
		{
			if(dst == nullptr || len == 0) return false;

			if(level_ == 0) {  // ポーリング動作
				if(!i2c_start_()) {
					error_ = ERROR::START;
					i2c_stop_();
					return false;
				}

				SCI::TDR = (adr << 1) | 1;  // R/W = 1 (read)
				while(SCI::SSR.TDRE() == 0) {
					sleep_();
				}
				while(SCI::SSR.TEND() == 0) {
					sleep_();
				}
				volatile uint8_t tmp = SCI::RDR();  // ダミーリード

				if(SCI::SISR.IICACKR() != 0) {
					error_ = ERROR::ACK;
					i2c_stop_();
					return false;
				}

				if(len > 1) {
					SCI::SIMR2.IICACKT = 0;
				}
				uint8_t* p = static_cast<uint8_t*>(dst);
				while(len > 0) {
					if(len == 1) {
						SCI::SIMR2.IICACKT = 1;
					}
					SCI::TDR = 0xff;  // dummy data
					while(SCI::SSR.RDRF() == 0) {
						sleep_();
					}
					*p++ = SCI::RDR();
					--len;
					while(SCI::SSR.TEND() == 0) {
						sleep_();
					}
				}

				if(!i2c_stop_()) {
					error_ = ERROR::STOP;
					return false;
				}
				if(func != nullptr) func();
				error_ = ERROR::NONE;
			} else {
				sci_i2c_t t;
				t.adr_ = adr;
				t.dst_ = static_cast<uint8_t*>(dst);
				t.len_ = len;
				t.func_ = func;
				i2c_buff_.put(t);
				if(task_ == sci_i2c_t::TASK::IDLE) {
					state_ = 0;
					task_ = sci_i2c_t::TASK::START_RECV;
					SCI::SIMR3 = SCI::SIMR3.IICSTAREQ.b() |
								 SCI::SIMR3.IICSCLS.b(0b01) | SCI::SIMR3.IICSDAS.b(0b01);
					SCI::SCR.TEIE = 1;
				}
			}
			return true;
		}
	};

	// テンプレート関数、実態の定義
	template<class SCI, class RBF, class SBF, port_map::ORDER PSEL>
		RBF sci_i2c_io<SCI, RBF, SBF, PSEL>::recv_;
	template<class SCI, class RBF, class SBF, port_map::ORDER PSEL>
		SBF sci_i2c_io<SCI, RBF, SBF, PSEL>::send_;
	template<class SCI, class RBF, class SBF, port_map::ORDER PSEL>
		volatile sci_i2c_t::TASK sci_i2c_io<SCI, RBF, SBF, PSEL>::task_;
	template<class SCI, class RBF, class SBF, port_map::ORDER PSEL>
		volatile uint8_t sci_i2c_io<SCI, RBF, SBF, PSEL>::state_;
	template<class SCI, class RBF, class SBF, port_map::ORDER PSEL>
		I2C_BUFF sci_i2c_io<SCI, RBF, SBF, PSEL>::i2c_buff_;
}
