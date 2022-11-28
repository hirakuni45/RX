#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ・SCI I/O 制御 @n
			・DMAC による転送をサポートしていませんが、必要性を感じていません。@n
			・同期通信で、ブロック転送を行うような場合は、必要かもしれません。@n
			Ex: 定義例 @n
			・受信バッファ、送信バッファの大きさは、最低１６バイトは必要でしょう。@n
			・ボーレート、サービスする内容に応じて適切に設定して下さい。@n
			  typedef utils::fixed_fifo<char, 512>  RBF;  // 受信バッファ定義 @n
			  typedef utils::fixed_fifo<char, 1024> SBF;  // 送信バッファ定義 @n
			  typedef device::sci_io<device::SCI1, RBF, SBF> SCI;  // SCI1 の場合 @n
			  SCI	sci_; // 実態の宣言 @n
			Ex: 開始例 @n
			  uint8_t intr_level = 2;    // 割り込みレベル(2) @n
			  uint32_t baud = 115200;    // ボーレート設定(115200) @n
			  sci_.start(baud, intr_level); @n  
			Ex: POSIX 関数 (printf など) への通路設定 @n
              C の関数「sci_putch(), sci_getch()」を定義してリンク可能にする。 @n
			  syscalls.c ソースをプロジェクトにリンクする。 @n
			  POSIX read, write 関数が、stdout ディスクリプタに対してアクセスする。 @n
			  extern "C" { @n
				void sci_putch(char ch) @n
				{ @n
					sci_.putch(ch); @n
				} @n
				char sci_getch(void) @n
				{ @n
					return sci_.getch(); @n
				} @n
			  }; @n
			上記関数を定義しておけば、syscalls.c との連携で、printf が使えるようになる。 @n
			※ C++ では printf は推奨しないし使う理由が無い、utils::format を使って下さい。 @n
			RS-485： @n
			・レシーバーの受信ゲートは常に有効にしておく。 @n
			・送信が正常に行えたかのケア（送信した文字列と受信した文字列の比較など）は、アプリ側で行う。 @n
			・レシーバーの送信ゲート制御のみ、ドライバーが行う。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2013, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"
#include "common/fixed_fifo.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCI I/O ベース・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class sci_io_base {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	SCI 通信プロトコル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class PROTOCOL : uint8_t {
			B7_N_1S,	///< 7 ビット、No-Parity、 1 Stop Bit
			B7_E_1S,	///< 7 ビット、Even(偶数)、1 Stop Bit
			B7_O_1S,	///< 7 ビット、Odd (奇数)、1 Stop Bit
			B7_N_2S,	///< 7 ビット、No-Parity、 2 Stop Bits
			B7_E_2S,	///< 7 ビット、Even(偶数)、2 Stop Bits
			B7_O_2S,	///< 7 ビット、Odd (奇数)、2 Stop Bits
			B8_N_1S,	///< 8 ビット、No-Parity、 1 Stop Bit
			B8_E_1S,	///< 8 ビット、Even(偶数)、1 Stop Bit
			B8_O_1S,	///< 8 ビット、Odd (奇数)、1 Stop Bit
			B8_N_2S,	///< 8 ビット、No-Parity、 2 Stop Bits
			B8_E_2S,	///< 8 ビット、Even(偶数)、2 Stop Bits
			B8_O_2S,	///< 8 ビット、Odd (奇数)、2 Stop Bits
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	SCI ボーレート型（シリアル通信で標準的に指定する定型値）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class BAUDRATE : uint32_t {
			B110    =    110,	///<    110 B.P.S.
			B150    =    150,	///<    150 B.P.S.
			B300    =    300,	///<    300 B.P.S.
			B600    =    600,	///<    600 B.P.S.
			B1200   =   1200,	///<   1200 B.P.S.
			B2400   =   2400,	///<   2400 B.P.S.
			B4800   =   4800,	///<   4800 B.P.S.
			B9600   =   9600,	///<   9600 B.P.S.
			B19200  =  19200,	///<  19200 B.P.S.
			B38400  =  38400,	///<  38400 B.P.S.
			B57600  =  57600,	///<  57600 B.P.S.
			B76800  =  76800,	///<  76800 B.P.S.
			B96000  =  96000,	///<  96000 B.P.S.
			B115200 = 115200,	///< 115200 B.P.S.
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	フロー制御型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class FLOW_CTRL : uint8_t {
			NONE,		///< フロー制御をしない
			SOFT,		///< ソフトフロー制御
			HARD,		///< ハードフロー制御（RTS ポートを使う）
			SOFT_HARD,	///< ソフトフローとハードフロー制御
			RS485,		///< RTS ポートを使い、RS485 レシーバーの DE を制御（送信時「1」となる）
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCI I/O 制御クラス
		@param[in]	SCI		SCI 型
		@param[in]	RBF		受信バッファクラス
		@param[in]	SBF		送信バッファクラス
		@param[in]	PSEL	通常ポート候補
		@param[in]	RTS		制御ポート（RTS/RS-485_DE）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class SCI, class RBF, class SBF, port_map::ORDER PSEL = port_map::ORDER::FIRST, class RTS = NULL_PORT>
	class sci_io : public sci_io_base {
	public:
		typedef SCI sci_type;
		typedef RBF rbf_type;
		typedef SBF sbf_type;

	private:

		static constexpr char XON  = 0x11;
		static constexpr char XOFF = 0x13;

		const port_map_order::sci_port_t&	port_map_;

		static RBF	recv_;
		static SBF	send_;

		static_assert(recv_.size() >= 8, "RECV Buffer too small.");
		static_assert(send_.size() >= 8, "SEND Buffer too small.");

		uint8_t		level_;
		bool		auto_crlf_;
		uint32_t	baud_;
		static FLOW_CTRL			flow_ctrl_;
		static volatile bool		stop_;
		static volatile uint16_t	errc_;
		static volatile uint32_t	ch_count_;

		// ※マルチタスクの場合適切な実装をする
		void sleep_() noexcept { asm("nop"); }


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
			volatile uint8_t rd = SCI::RDR();
			if(err) {
				++errc_;
			} else {
				if(flow_ctrl_ == FLOW_CTRL::SOFT || flow_ctrl_ == FLOW_CTRL::HARD || flow_ctrl_ == FLOW_CTRL::SOFT_HARD) {
					if(recv_.length() >= (recv_.size() - 6)) {
						stop_ = true;
						if(flow_ctrl_ == FLOW_CTRL::HARD || flow_ctrl_ == FLOW_CTRL::SOFT_HARD) {
							RTS::P = 0;
						}
					}
				} else if(flow_ctrl_ == FLOW_CTRL::RS485) {
					if(ch_count_ > 0) {
						ch_count_--;
						if(send_.length() == 0 && ch_count_ == 0 && SCI::SCR.TIE() == 0) {
							RTS::P = 0;
						}
					}
				}
				recv_.put(rd);
			}
		}


		static INTERRUPT_FUNC void send_task_()
		{
			if(send_.length() > 0) {
				++ch_count_;
				SCI::TDR = send_.get();
			} else {
				SCI::SCR.TIE = 0;
			}
		}


		static INTERRUPT_FUNC void send_fin_task_()
		{

		}


		void set_intr_(uint8_t level) noexcept
		{
			if(level > 0) {
				icu_mgr::set_task(SCI::RXI, recv_task_);
				icu_mgr::set_task(SCI::TXI, send_task_);
			} else {
				icu_mgr::set_task(SCI::RXI, nullptr);
				icu_mgr::set_task(SCI::TXI, nullptr);
			}
			icu_mgr::set_level(SCI::RXI, level);
			icu_mgr::set_level(SCI::TXI, level);
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
			@param[in]	autocrlf	LF 時、自動で CR の送出をしない場合「false」
			@param[in]	flow_ctrl	フロー制御型
			@param[in]	sci_port	ポート設定を詳細に行う場合
		*/
		//-----------------------------------------------------------------//
		sci_io(bool autocrlf = true, FLOW_CTRL flow_ctrl = FLOW_CTRL::NONE,
			const port_map_order::sci_port_t& sci_port = port_map_order::sci_port_t()) noexcept :
			port_map_(sci_port),
			level_(0),
			auto_crlf_(autocrlf), baud_(0) {
			flow_ctrl_ = flow_ctrl;
			stop_ = false;
			errc_ = 0;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	エラー数の取得
			@return エラー数
		 */
		//-----------------------------------------------------------------//
		static uint16_t get_error_count() noexcept { return errc_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	LF 時、CR 自動送出
			@param[in]	f	「false」なら無効
		 */
		//-----------------------------------------------------------------//
		void auto_crlf(bool f = true) noexcept { auto_crlf_ = f; }


		//-----------------------------------------------------------------//
		/*!
			@brief  ボーレートを設定して、SCI を有効にする @n
					※RX63T では、ポーリングはサポート外
			@param[in]	baud	ボーレート
			@param[in]	level	割り込みレベル（０の場合ポーリング）
			@param[in]	prot	通信プロトコル（標準は、８ビット、パリティ無し、１ストップ）
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t baud, uint8_t level = 0, PROTOCOL prot = PROTOCOL::B8_N_1S) noexcept
		{
#if defined(SIG_RX63T)
			if(level == 0) return false;
#endif
			if(flow_ctrl_ == FLOW_CTRL::RS485 && level == 0) {
				// RS485 では、割り込みを使わない設定は NG
				return false;
			}

			level_ = level;
			stop_ = false;
			recv_.clear();
			send_.clear();

			if(!power_mgr::turn(SCI::PERIPHERAL)) {
				return false;
			}
			// PSEL に、BYPASS が選択された場合、個別のポート設定が有効になる。
			if(PSEL == port_map_order::ORDER::BYPASS) {
// この仕組みは、現在開発中・・・
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX72N) || defined(SIG_RX72T)
				uint8_t ok = 0;
				ok += port_map_sci::turn(SCI::PERIPHERAL, port_map_sci::CHANNEL::CTS, true, port_map_.cts_);
				ok += port_map_sci::turn(SCI::PERIPHERAL, port_map_sci::CHANNEL::RTS, true, port_map_.rts_);
				ok += port_map_sci::turn(SCI::PERIPHERAL, port_map_sci::CHANNEL::RXD, true, port_map_.rxd_);
				ok += port_map_sci::turn(SCI::PERIPHERAL, port_map_sci::CHANNEL::SCK, true, port_map_.sck_);
				ok += port_map_sci::turn(SCI::PERIPHERAL, port_map_sci::CHANNEL::TXD, true, port_map_.txd_);
				if(ok != 5) {
					power_mgr::turn(SCI::PERIPHERAL, false);
					return false;
				}
#endif
			} else {
				if(!port_map::turn(SCI::PERIPHERAL, true, PSEL)) {
					power_mgr::turn(SCI::PERIPHERAL, false);
					return false;
				}
			}

			set_intr_(0);

			SCI::SCR = 0x00;			// TE, RE disable.
			{
				auto tmp = SCI::SSR();
				if(tmp & (SCI::SSR.ORER.b() | SCI::SSR.FER.b() | SCI::SSR.PER.b())) {
					SCI::SSR = 0x00;
				}
			}

			// RS-484 半二重制御ポート
			if(flow_ctrl_ != FLOW_CTRL::NONE) {
				if(flow_ctrl_ == FLOW_CTRL::RS485) {
					RTS::DIR = 1;
					RTS::P = 0;  // disable send driver
				} else if(flow_ctrl_ == FLOW_CTRL::HARD || flow_ctrl_ != FLOW_CTRL::SOFT_HARD) {
					RTS::DIR = 1;
					RTS::P = 1;
				}
			}

			baud_ = baud;
			// BGDM が使える場合、1/8 スタート
			uint32_t mtx = 8;
			uint32_t limit = 1024;
			if(!SCI::SEMR_BGDM) {  // BGDM が使えない場合 1/16 スタート
				mtx = 16;
				limit = 512;
			}
			uint32_t brr = SCI::PCLK / mtx / baud;
			uint8_t cks = 0;
			while(brr > limit) {
				brr >>= 2;
				++cks;
				if(cks >= 4) {  // 範囲外の速度
					port_map::turn(SCI::PERIPHERAL, false, PSEL);
					power_mgr::turn(SCI::PERIPHERAL, false);
					return false;
				}
			}

			// BGDM フラグの設定
			bool bgdm = true;
			if(SCI::SEMR_BGDM) {
				if(brr > 512) { brr >>= 1; bgdm = false; mtx <<= 1; }
			} else {
				bgdm = false;
			}
			bool abcs = true;
			if(brr > 256) { brr >>= 1; abcs = false; mtx <<= 1; }

			set_intr_(level_);

			bool stop = 0;
			bool pm = 0;
			bool pe = 0;
			bool seven = 0;
			switch(prot) {
			case PROTOCOL::B7_N_1S:
				seven = 1;
			case PROTOCOL::B8_N_1S:
				stop = 0;
				pm = 0;
				pe = 0;
				break;
			case PROTOCOL::B7_E_1S:
				seven = 1;
			case PROTOCOL::B8_E_1S:
				stop = 0;
				pm = 0;
				pe = 1;
				break;
			case PROTOCOL::B7_O_1S:
				seven = 1;
			case PROTOCOL::B8_O_1S:
				stop = 0;
				pm = 1;
				pe = 1;
				break;
			case PROTOCOL::B7_N_2S:
				seven = 1;
			case PROTOCOL::B8_N_2S:
				stop = 1;
				pm = 0;
				pe = 0;
				break;
			case PROTOCOL::B7_E_2S:
				seven = 1;
			case PROTOCOL::B8_E_2S:
				stop = 1;
				pm = 0;
				pe = 1;
				break;
			case PROTOCOL::B7_O_2S:
				seven = 1;
			case PROTOCOL::B8_O_2S:
				stop = 1;
				pm = 1;
				pe = 1;
				break;
			default:
				return false;
			}
			SCI::SMR = SCI::SMR.CKS.b(cks) | SCI::SMR.STOP.b(stop)
					 | SCI::SMR.PM.b(pm) | SCI::SMR.PE.b(pe) | SCI::SMR.CHR.b(seven);

			bool brme = false;
			if(SCI::SEMR_BRME) {  // 微調整機能が使える場合
				uint32_t rate = SCI::PCLK / mtx / brr / (1 << (cks * 2));
				uint32_t mddr = (baud_ << 9) / rate;
				if(mddr >= 128 && mddr < 256) {  // 微調整を行う場合
					++mddr;
					mddr >>= 1;
					SCI::MDDR = mddr;
					brme = true;
				}
			}

			SCI::SEMR = SCI::SEMR.ABCS.b(abcs) | SCI::SEMR.BRME.b(brme) | SCI::SEMR.BGDM.b(bgdm);

			if(brr > 0) --brr;
			SCI::BRR = brr;

			if(level > 0) {
				SCI::SCR = SCI::SCR.RIE.b() | SCI::SCR.TE.b() | SCI::SCR.RE.b();
			} else {
				SCI::SCR = SCI::SCR.TE.b() | SCI::SCR.RE.b();
			}

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ボーレート型を使い SCI を有効にする
			@param[in]	baud	ボーレート型
			@param[in]	level	割り込みレベル（０の場合ポーリング）
			@param[in]	prot	通信プロトコル（標準は、８ビット、パリティ無し、１ストップ）
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool start(BAUDRATE baud, uint8_t level = 0, PROTOCOL prot = PROTOCOL::B8_N_1S) noexcept
		{
			return start(static_cast<uint32_t>(baud), level, prot);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	BRR レジスタ値を取得
			@return BRR レジスタ値
		 */
		//-----------------------------------------------------------------//
		uint8_t get_brr() const noexcept { return SCI::BRR(); }


		//-----------------------------------------------------------------//
		/*!
			@brief	設定ボーレートを取得
			@param[in]	real	「true」にした場合、内部で設定された実際の値
			@return ボーレート
		 */
		//-----------------------------------------------------------------//
		uint32_t get_baud_rate(bool real = false) const noexcept
		{
			if(real) {
				uint32_t brr = SCI::BRR();
				uint32_t cks = 1 << (SCI::SMR.CKS() * 2);
				uint32_t mtx = 8;
				if(SCI::SEMR_BGDM) {
					if(!SCI::SEMR.BGDM()) mtx <<= 1;
				} else {
					mtx <<= 1;
				}
				if(!SCI::SEMR.ABCS()) mtx <<= 1;
				auto baud = SCI::PCLK / mtx / cks / (brr + 1);
				if(SCI::SEMR_BRME && SCI::SEMR.BRME()) {
					baud *= SCI::MDDR();
					baud /= 256;
				}
				return baud;
			} else {
				return baud_;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	MDDR レジスタ値を取得（ボーレート周期補正）
			@return MDRR レジスタ値
		 */
		//-----------------------------------------------------------------//
		uint8_t get_mdrr() const noexcept { return SCI::MDDR(); }


		//-----------------------------------------------------------------//
		/*!
			@brief	SCI 出力バッファのサイズを返す
			@return　バッファのサイズ
		 */
		//-----------------------------------------------------------------//
		uint32_t send_length() const noexcept
		{
			if(level_) {
				return send_.length();
			} else {
				return 0;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	SCI 文字出力 @n
					送信バッファの容量が７／８以上の場合は、空になるまで待つ。（フロー制御が無い場合）
			@param[in]	ch	文字コード
		 */
		//-----------------------------------------------------------------//
		void putch(char ch)  noexcept
		{
			if(auto_crlf_ && ch == '\n') {
				putch('\r');
			}
			if(level_ > 0) {
				volatile bool b = SCI::SSR.ORER();
				if(b) {
					SCI::SSR.ORER = 0;
				}
				if(flow_ctrl_ == FLOW_CTRL::NONE) {
					if(send_.length() >= (send_.size() * 7 / 8)) {
						while(send_.length() != 0) sleep_();
					}
				}
				send_.put(ch);
				if(SCI::SCR.TIE() == 0) {
					if(flow_ctrl_ == FLOW_CTRL::RS485) {
						RTS::P = 1;
					}
					SCI::SCR.TIE = 1;
					++ch_count_;
					SCI::TDR = send_.get();
				}
			} else {
				while(SCI::SSR.TEND() == 0) sleep_();
				SCI::TDR = ch;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	入力文字数を取得
			@return	入力文字数
		 */
		//-----------------------------------------------------------------//
		uint32_t recv_length() noexcept
		{
			if(level_ > 0) {
				return recv_.length();
			} else {
				if(SCI::SSR.ORER()) {	///< 受信オーバランエラー状態確認
					SCI::SSR.ORER = 0;	///< 受信オーバランエラークリア
				}
				return SCI::SSR.RDRF();
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	入力文字を捨てる
		 */
		//-----------------------------------------------------------------//
		void flush_recv() noexcept
		{
			if(recv_length() > 0) {
				recv_.clear();
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	文字入力（ブロック関数）
			@return 文字コード
		 */
		//-----------------------------------------------------------------//
		char getch() noexcept
		{
			if(level_ > 0) {  // 割り込み受信
				while(recv_.length() == 0) {
					sleep_();
				}
				auto ch = recv_.get();
				if(flow_ctrl_ == FLOW_CTRL::HARD || flow_ctrl_ == FLOW_CTRL::SOFT_HARD) {
					if(recv_.length() == 0) {
						RTS::P = 1;
					}
				}
				return ch;
			} else {
				while(recv_length() == 0) sleep_();
				return SCI::RDR();	///< 受信データ読み出し
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	文字列出力
			@param[in]	s	出力文字列
		 */
		//-----------------------------------------------------------------//
		void puts(const char* s)  noexcept
		{
			if(s == nullptr) return;
			char ch;
			while((ch = *s++) != 0) {
				putch(ch);
			}
		}
	};

	// テンプレート関数、実態の定義
	template<class SCI, class RBF, class SBF, port_map::ORDER PSEL, class RTS>
		RBF sci_io<SCI, RBF, SBF, PSEL, RTS>::recv_;
	template<class SCI, class RBF, class SBF, port_map::ORDER PSEL, class RTS>
		SBF sci_io<SCI, RBF, SBF, PSEL, RTS>::send_;
	template<class SCI, class RBF, class SBF, port_map::ORDER PSEL, class RTS>
		sci_io_base::FLOW_CTRL sci_io<SCI, RBF, SBF, PSEL, RTS>::flow_ctrl_;
	template<class SCI, class RBF, class SBF, port_map::ORDER PSEL, class RTS>
		volatile bool sci_io<SCI, RBF, SBF, PSEL, RTS>::stop_;
	template<class SCI, class RBF, class SBF, port_map::ORDER PSEL, class RTS>
		volatile uint16_t sci_io<SCI, RBF, SBF, PSEL, RTS>::errc_;
	template<class SCI, class RBF, class SBF, port_map::ORDER PSEL, class RTS>
		volatile uint32_t sci_io<SCI, RBF, SBF, PSEL, RTS>::ch_count_;
}
