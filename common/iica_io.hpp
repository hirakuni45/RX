#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ・IICA 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cstring>
#include "common/renesas.hpp"
#include "common/vect.h"
#include "common/format.hpp"
#include "common/i2c_base.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  IICA 制御クラス（I2C) @n
				※ポートは候補が通常１つしか無い為、指定がありません。
		@param[in]	IICA	IICA 定義基底クラス
		@param[in]	TPSZ	テンポラリーバッファサイズ（I2C 通信で行う最大サイズを指定）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class IICA, uint32_t TPSZ = 256>
	class iica_io : public i2c_base {

		static_assert(TPSZ > 16, "TPSZ is too small.");

		struct clock_t {
			uint8_t	CKS;
			uint8_t ICBRL;
			uint8_t ICBRH;
			constexpr clock_t(uint8_t cks, uint8_t l, uint8_t h) :
				CKS(cks), ICBRL(l), ICBRH(h) { }
		};

		static constexpr clock_t clock_tables_[] = {
			{ 0b100, 15, 18 },  //   50Kbps, PCLK:30MHz
			{ 0b010,  2,  3 },  //  100Kbps, PCLK:30MHz
			{ 0b010,  4,  6 },  //  200Kbps, PCLK:30MHz
			{ 0b001,  8, 19 },  //  400Kbps, PCLK:30MHz
			{ 0b000,  7, 15 },  // 1000Kbps, PCLK:30MHz

			{ 0b100, 17, 20 },  //   50Kbps, PCLK:33MHz
			{ 0b011, 16, 19 },  //  100Kbps, PCLK:33MHz
			{ 0b010, 15, 18 },  //  200Kbps, PCLK:33MHz
			{ 0b001,  9, 21 },  //  400Kbps, PCLK:33MHz
			{ 0b000,  8, 16 },  // 1000Kbps, PCLK:33MHz

			{ 0b100, 21, 24 },  //   50Kbps, PCLK:40MHz
			{ 0b011, 19, 23 },  //  100Kbps, PCLK:40MHz
			{ 0b010, 17, 22 },  //  200Kbps, PCLK:40MHz
			{ 0b001, 11, 25 },  //  400Kbps, PCLK:40MHz
			{ 0b000, 10, 20 },  // 1000Kbps, PCLK:40MHz

			{ 0b100, 26, 31 },  //   50Kbps, PCLK:50MHz
			{ 0b011, 24, 29 },  //  100Kbps, PCLK:50MHz
			{ 0b010, 22, 27 },  //  200Kbps, PCLK:50MHz
			{ 0b010,  7, 16 },  //  400Kbps, PCLK:50MHz
			{ 0b000, 12, 24 },  // 1000Kbps, PCLK:50MHz

			{ 0b101, 15, 18 },  //   50Kbps, PCLK:60MHz
			{ 0b100, 14, 17 },  //  100Kbps, PCLK:60MHz
			{ 0b011, 13, 16 },  //  200Kbps, PCLK:60MHz
			{ 0b010,  8, 19 },  //  400Kbps, PCLK:60MHz
			{ 0b000, 15, 29 },  // 1000Kbps, PCLK:60MHz
		};
		static constexpr uint32_t PCLK_30 = 5 * 0;
		static constexpr uint32_t PCLK_33 = 5 * 1;
		static constexpr uint32_t PCLK_40 = 5 * 2;
		static constexpr uint32_t PCLK_50 = 5 * 3;
		static constexpr uint32_t PCLK_60 = 5 * 4;
		static constexpr uint32_t CLOCK_OFS_50K   = 0;
		static constexpr uint32_t CLOCK_OFS_100K  = 1;
		static constexpr uint32_t CLOCK_OFS_200K  = 2;
		static constexpr uint32_t CLOCK_OFS_400K  = 3;
		static constexpr uint32_t CLOCK_OFS_1000K = 4;

		static constexpr uint32_t BUS_BUSY_MS  = 500;  // バス占有状態待機ループ
		static constexpr uint32_t WAIT_LOOP_MS = 500;  // 500uS

		ICU::LEVEL	level_;
		uint8_t		sadr_;
		uint8_t		speed_;

		enum class event : uint8_t {
			NONE,
			AL,
			NACKF,
			TOMF,
			START,
			STOP,
		};

		struct intr_t {
			uint8_t				buff_[TPSZ];
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
			intr_t() : buff_{ }, event_(event::NONE), firstb_(0), dummy_recv_(false),
				src_(nullptr), dst_(nullptr), len_(0),
				send_id_(0), send_id_back_(0), recv_id_(0), recv_id_back_(0) { }
		};
		static inline intr_t	intr_;

		static void ee_ntask_()
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

		static INTERRUPT_FUNC void ee_itask_() { ee_ntask_(); }

		static INTERRUPT_FUNC void rx_itask_()
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

		static INTERRUPT_FUNC void tx_itask_()
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

		static void te_ntask_()
		{
			IICA::ICSR2.STOP = 0;
			IICA::ICCR2.SP = 1;
			IICA::ICIER.TEIE = 0;
			intr_.event_ = event::STOP;
			IICA::ICIER.SPIE = 1;
		}

		static INTERRUPT_FUNC void te_itask_() { te_ntask_(); }

		void sleep_() noexcept
		{
			asm("nop");
		}


		bool setup_start_() noexcept
		{
			uint32_t loop = 0;
			while(IICA::ICCR2.BBSY() != 0) {  // I2C バス占有状態判定
				utils::delay::micro_second(1);
				++loop;
				if(loop >= BUS_BUSY_MS) {
					return false;
				}
			}
			return true;
		}


		void setup_ackbt_() noexcept
		{
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
		iica_io(uint8_t sadr = 0x00) noexcept : i2c_base(), level_(ICU::LEVEL::NONE), sadr_(sadr), speed_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C を有効にする
			@param[in]	mode	動作モード
			@param[in]	spd		スピード・タイプ
			@param[in]	level	割り込みレベル（０の場合ポーリング）
			@param[in]	nf		ノイズフィルター型
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool start(MODE mode, SPEED spd, ICU::LEVEL level = ICU::LEVEL::NONE, NF nf = NF::PH1) noexcept
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

			uint32_t idx_base = 0;
			if(IICA::PCLK <= 30'000'000) idx_base = PCLK_30;
			else if(IICA::PCLK <= 33'000'000) idx_base = PCLK_33;
			else if(IICA::PCLK <= 40'000'000) idx_base = PCLK_40;
			else if(IICA::PCLK <= 50'000'000) idx_base = PCLK_50;
			else idx_base = PCLK_60;
			switch(spd) {
			case SPEED::_50K:  // 50K b.p.s.
				idx_base += CLOCK_OFS_50K;
				break;
			case SPEED::STANDARD:	// 100K b.p.s. (Standard mode)
			case SPEED::_150K:
				idx_base += CLOCK_OFS_100K;
				break;
			case SPEED::_200K:
			case SPEED::_250K:
			case SPEED::_300K:
			case SPEED::_350K:
				idx_base += CLOCK_OFS_200K;
				break;
			case SPEED::FAST:		// 400K b.p.s. (Fast mode)
				idx_base += CLOCK_OFS_400K;
				break;
			case SPEED::FAST_PLUS:	// 1M b.p.s. (Fast plus mode)
				idx_base += CLOCK_OFS_1000K;
				break;
			default:
				error_ = ERROR::CLOCK_DIVIDE;
				port_map::turn(IICA::PERIPHERAL, false);
				power_mgr::turn(IICA::PERIPHERAL, false);
				return false;
			}
			IICA::ICMR1 = IICA::ICMR1.CKS.b(clock_tables_[idx_base].CKS) | IICA::ICMR1.BCWP.b();
			IICA::ICBRL = 0b11100000 | clock_tables_[idx_base].ICBRL;
			IICA::ICBRH = 0b11100000 | clock_tables_[idx_base].ICBRH;

			if(nf == NF::NONE) {
				IICA::ICFER.NFE = 0;
			} else {
				IICA::ICMR3.NF = static_cast<uint8_t>(nf);
				IICA::ICFER.NFE = 1;
			}

///			IICA::ICFER.TMOE = 1;  // TimeOut Enable

			if(level_ != ICU::LEVEL::NONE) {
				icu_mgr::set_interrupt(IICA::RXI, rx_itask_, level_);
				icu_mgr::set_interrupt(IICA::TXI, tx_itask_, level_);

				if(icu_mgr::get_group_vector(IICA::EEI) == ICU::VECTOR::NONE) {  // 通常割り込みの場合
					icu_mgr::set_interrupt(IICA::EEI, ee_itask_, level_);
				} else {
					icu_mgr::set_interrupt(IICA::EEI, ee_ntask_, level_);	// グループ割り込みの場合、通常の関数を登録
				}
				if(icu_mgr::get_group_vector(IICA::TEI) == ICU::VECTOR::NONE) {  // 通常割り込みの場合
					icu_mgr::set_interrupt(IICA::TEI, te_itask_, level_);
				} else {
					icu_mgr::set_interrupt(IICA::TEI, te_ntask_, level_);  // グループ割り込みの場合、通常の関数を登録
				}
			} else {
				icu_mgr::set_interrupt(IICA::RXI, nullptr, level_);
				icu_mgr::set_interrupt(IICA::TXI, nullptr, level_);
				icu_mgr::set_interrupt(IICA::EEI, nullptr, level_);
				icu_mgr::set_interrupt(IICA::TEI, nullptr, level_);
			}
			IICA::ICIER = 0x00;

			IICA::ICCR1.IICRST = 0;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	送信状態の検査（割り込み動作時）
			@return 送信が完了なら「true」
		 */
		//-----------------------------------------------------------------//
		static bool get_send_state() noexcept { return intr_.send_id_ != intr_.send_id_back_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	受信状態の検査（割り込み動作時）
			@return 受信完了なら「true」
		 */
		//-----------------------------------------------------------------//
		static bool get_recv_state() noexcept { return intr_.recv_id_ != intr_.recv_id_back_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	送信 @n
					割り込み動作で「非同期」の場合、メモリソースの保護が必要
			@param[in]	adr		I2C ７ビットアドレス
			@param[in]	src		転送先
			@param[in]	len		送信バイト数
			@param[in]	sync	非同期の場合「false」
			@return 送信が完了した場合「true」
		 */
		//-----------------------------------------------------------------//
		bool send(uint8_t adr, const void* src, uint32_t len, bool sync = true) noexcept
		{
			if(len == 0 || len > TPSZ) {
				error_ = ERROR::BUFF_SIZE;
				return false;
			}

			if(!setup_start_()) {  // 開始時 I2C バスがビジーの場合、失敗する。
				error_ = ERROR::START;
				return false;
			}

			error_ = ERROR::NONE;

			const uint8_t* ptr = static_cast<const uint8_t*>(src);

			bool ret = true;
			if(level_ != ICU::LEVEL::NONE) {
				intr_.send_id_back_ = intr_.send_id_;
				intr_.firstb_ = adr << 1;
				intr_.src_ = ptr;
				intr_.dst_ = nullptr;
				intr_.len_ = len;
				intr_.event_ = event::NACKF;
				IICA::ICIER = IICA::ICIER() | IICA::ICIER.NAKIE.b() | IICA::ICIER.TIE.b();
				IICA::ICCR2.ST = 1;
				if(sync) {
					while(intr_.send_id_back_ == intr_.send_id_) {
						sleep_();
					}
					if(intr_.event_ != event::NONE) {
						error_ = ERROR::SEND_DATA;
						ret = false;
					}
				}
			} else {
				IICA::ICCR2.ST = 1;

				bool first = true;
				while(len > 0) {

					if(IICA::ICSR2.NACKF() != 0) {
						ret = false;
						if(first) {
							error_ = ERROR::ADDRESS;
						} else {
							error_ = ERROR::SEND_DATA;
						}
						break;
					}

					if(IICA::ICSR2.TDRE() == 0) {
						continue;
					}

					if(first) {
						IICA::ICDRT = (adr << 1);
						first = false;
					} else {
						IICA::ICDRT = *ptr++;
						--len;
					}
				}
				if(ret) {
					// アドレス不一致デバイスでも、転送は出来るが、TEND が有効にならない・・
					uint32_t loop = 0;
					while(IICA::ICSR2.TEND() == 0) {
						utils::delay::micro_second(1);
						++loop;
						if(loop >= WAIT_LOOP_MS) {
							ret = false;
							error_ = ERROR::END;
							break;
						}
					}
				}

				IICA::ICSR2.STOP = 0;
				IICA::ICCR2.SP = 1;
				{
					uint32_t loop = 0;
					while(IICA::ICSR2.STOP() == 0) {
						utils::delay::micro_second(1);
						++loop;
						if(loop >= WAIT_LOOP_MS) {
							ret = false;
							error_ = ERROR::STOP;
							break;
						}
					}
				}
				IICA::ICSR2.NACKF = 0;
				IICA::ICSR2.STOP = 0;
			}
			return ret;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	送信（シングルバイト付き）
			@param[in]	adr		I2C ７ビットアドレス
			@param[in]	first	ファーストバイト
			@param[in]	src		転送先
			@param[in]	len		送信バイト数
			@param[in]	sync	非同期の場合「false」
			@return 送信が完了した場合「true」
		 */
		//-----------------------------------------------------------------//
		bool send(uint8_t adr, uint8_t first, const void* src, uint16_t len, bool sync = true) noexcept
		{
			uint8_t tmp[len + 1];
			tmp[0] = first;
			std::memcpy(&tmp[1], src, len);
			return send(adr, tmp, len + 1, sync);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	送信（ダブルバイト付き）
			@param[in]	adr		I2C ７ビットアドレス
			@param[in]	first	ファーストバイト
			@param[in]	second	セカンドバイト
			@param[in]	src		転送先
			@param[in]	len		送信バイト数
			@param[in]	sync	非同期の場合「false」
			@return 送信が完了した場合「true」
		 */
		//-----------------------------------------------------------------//
		bool send(uint8_t adr, uint8_t first, uint8_t second, const void* src, uint16_t len, bool sync = true) noexcept
		{
			uint8_t tmp[len + 2];
			tmp[0] = first;
			tmp[1] = second;
			std::memcpy(&tmp[2], src, len);
			return send(adr, tmp, len + 2, sync);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	受信
			@param[in]	adr		７ビットアドレス
			@param[out]	dst		転送先
			@param[in]	len		受信バイト数
			@param[in]	sync	転送同期を行わない場合「false」
			@return 受信が完了した場合「true」
		 */
		//-----------------------------------------------------------------//
		bool recv(uint8_t adr, void* dst, uint16_t len, bool sync = true) noexcept
		{
			if(len == 0 || len > TPSZ) {
				error_ = ERROR::BUFF_SIZE;
				return false;
			}

			if(!setup_start_()) {  // 開始時 I2C バスがビジーの場合、失敗する。
				error_ = ERROR::START;
				return false;
			}

			error_ = ERROR::NONE;

			uint8_t* ptr = static_cast<uint8_t*>(dst);

			bool ret = true;
			if(level_ != ICU::LEVEL::NONE) {
				intr_.recv_id_back_ = intr_.recv_id_;
				intr_.firstb_ = (adr << 1) | 0x01;
				intr_.src_ = nullptr;
				intr_.dst_ = ptr;
				intr_.len_ = len;

				IICA::ICIER.TIE = 1;
				IICA::ICCR2.ST = 1;

			} else {

				IICA::ICCR2.ST = 1;
				while(IICA::ICSR2.TDRE() == 0) {
				}

				IICA::ICDRT = (adr << 1) | 0x01;
				uint32_t loop = 0;
				while(IICA::ICSR2.RDRF() == 0) {
#if 0
					utils::delay::micro_second(1);
					++loop;
					if(loop >= WAIT_LOOP_MS) {
						ret = false;
						error_ = ERROR::ADDRESS;
						IICA::ICSR2.NACKF = 0;
						IICA::ICSR2.STOP = 0;
						return false;
					}
#endif
				}

				if(IICA::ICSR2.NACKF() != 0) {
					IICA::ICSR2.STOP = 0;
					IICA::ICCR2.SP = 1;
					volatile uint8_t tmp = IICA::ICDRR();

					while(IICA::ICSR2.STOP() == 0) ;

					IICA::ICSR2.NACKF = 0;
					IICA::ICSR2.STOP = 0;
					error_ = ERROR::ADDRESS;
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
						*ptr++ = tmp;
					}
					while(IICA::ICSR2.RDRF() == 0) ;
				} else {
					volatile uint8_t tmp = IICA::ICDRR();  // dummy read
					while(IICA::ICSR2.RDRF() == 0) ;

					while(len > 2) {
						if(len == 3) {
							IICA::ICMR3.WAIT = 1;
						}

						*ptr++ = IICA::ICDRR();
						while(IICA::ICSR2.RDRF() == 0) ;
						--len;
					}
					setup_ackbt_();
					*ptr++ = IICA::ICDRR();
					while(IICA::ICSR2.RDRF() == 0) ;
				}
				IICA::ICSR2.STOP = 0;
				IICA::ICCR2.SP = 1;
	
				*ptr = IICA::ICDRR();

				IICA::ICMR3.WAIT = 0;

				{
					uint32_t loop = 0;
					while(IICA::ICSR2.STOP() == 0) {
						utils::delay::micro_second(1);
						++loop;
						if(loop >= WAIT_LOOP_MS) {
							ret = false;
							error_ = ERROR::STOP;
							break;
						}
					}
				}
				IICA::ICSR2.NACKF = 0;
				IICA::ICSR2.STOP = 0;
			}
			return ret;
		}
	};
}
