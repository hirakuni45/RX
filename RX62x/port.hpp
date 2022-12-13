#pragma once
//=====================================================================//
/*!	@file
	@brief	RX621/RX62N グループ・ポート・レジスター定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート定義基底クラス（DDR, DR, PORT, ICR, ODR）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct portx_t {

		static constexpr uint32_t base_address_ = base;	///< ベースアドレス

		typedef rw8_t<base + 0x00>  ddr_io;
		typedef rw8_t<base + 0x20>  dr_io;
		typedef rw8_t<base + 0x40>  port_io;
		typedef rw8_t<base + 0x60>  icr_io;
		typedef rw8_t<base + 0x80>  odr_io;

		//-----------------------------------------------------------------//
		/*!
			@brief  DDR レジスタ
		*/
		//-----------------------------------------------------------------//
		struct ddr_t : public ddr_io {
			using ddr_io::operator =;
			using ddr_io::operator ();
			using ddr_io::operator |=;
			using ddr_io::operator &=;

			bit_rw_t<ddr_io, bitpos::B0> B0;
			bit_rw_t<ddr_io, bitpos::B1> B1;
			bit_rw_t<ddr_io, bitpos::B2> B2;
			bit_rw_t<ddr_io, bitpos::B3> B3;
			bit_rw_t<ddr_io, bitpos::B4> B4;
			bit_rw_t<ddr_io, bitpos::B5> B5;
			bit_rw_t<ddr_io, bitpos::B6> B6;
			bit_rw_t<ddr_io, bitpos::B7> B7;
		};
		typedef ddr_t DDR_;
		static DDR_ DDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  DR レジスタ
		*/
		//-----------------------------------------------------------------//
		struct dr_t : public dr_io {
			using dr_io::operator =;
			using dr_io::operator ();
			using dr_io::operator |=;
			using dr_io::operator &=;

			bit_rw_t<dr_io, bitpos::B0> B0;
			bit_rw_t<dr_io, bitpos::B1> B1;
			bit_rw_t<dr_io, bitpos::B2> B2;
			bit_rw_t<dr_io, bitpos::B3> B3;
			bit_rw_t<dr_io, bitpos::B4> B4;
			bit_rw_t<dr_io, bitpos::B5> B5;
			bit_rw_t<dr_io, bitpos::B6> B6;
			bit_rw_t<dr_io, bitpos::B7> B7;

		};
		typedef dr_t DR_;
		static DR_ DR;


		//-----------------------------------------------------------------//
		/*!
			@brief  PORT
		*/
		//-----------------------------------------------------------------//
		struct port_t : public port_io {
			using port_io::operator ();

			bit_ro_t<port_io, bitpos::B0> B0;
			bit_ro_t<port_io, bitpos::B1> B1;
			bit_ro_t<port_io, bitpos::B2> B2;
			bit_ro_t<port_io, bitpos::B3> B3;
			bit_ro_t<port_io, bitpos::B4> B4;
			bit_ro_t<port_io, bitpos::B5> B5;
			bit_ro_t<port_io, bitpos::B6> B6;
			bit_ro_t<port_io, bitpos::B7> B7;
		};
		typedef port_t PORT_;
		static PORT_ PORT;


		//-----------------------------------------------------------------//
		/*!
			@brief  ICR レジスタ
		*/
		//-----------------------------------------------------------------//
		struct icr_t : public icr_io {
			using icr_io::operator =;
			using icr_io::operator ();
			using icr_io::operator |=;
			using icr_io::operator &=;

			bit_rw_t<icr_io, bitpos::B0> B0;
			bit_rw_t<icr_io, bitpos::B1> B1;
			bit_rw_t<icr_io, bitpos::B2> B2;
			bit_rw_t<icr_io, bitpos::B3> B3;
			bit_rw_t<icr_io, bitpos::B4> B4;
			bit_rw_t<icr_io, bitpos::B5> B5;
			bit_rw_t<icr_io, bitpos::B6> B6;
			bit_rw_t<icr_io, bitpos::B7> B7;
		};
		typedef icr_t ICR_;
		static ICR_ ICR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ODR レジスタ
		*/
		//-----------------------------------------------------------------//
		struct odr_t : public odr_io {
			using odr_io::operator =;
			using odr_io::operator ();
			using odr_io::operator |=;
			using odr_io::operator &=;

			bit_rw_t<odr_io, bitpos::B0> B0;
			bit_rw_t<odr_io, bitpos::B1> B1;
			bit_rw_t<odr_io, bitpos::B2> B2;
			bit_rw_t<odr_io, bitpos::B3> B3;
			bit_rw_t<odr_io, bitpos::B4> B4;
			bit_rw_t<odr_io, bitpos::B5> B5;
			bit_rw_t<odr_io, bitpos::B6> B6;
			bit_rw_t<odr_io, bitpos::B7> B7;
		};
		typedef odr_t ODR_;
		static ODR_ ODR;
	};
	template <uint32_t base> typename portx_t<base>::DDR_  portx_t<base>::DDR;
	template <uint32_t base> typename portx_t<base>::DR_   portx_t<base>::DR;
	template <uint32_t base> typename portx_t<base>::PORT_ portx_t<base>::PORT;
	template <uint32_t base> typename portx_t<base>::ICR_  portx_t<base>::ICR;
	template <uint32_t base> typename portx_t<base>::ODR_  portx_t<base>::ODR;


	typedef portx_t<0x0008'C000> PORT0;
	typedef portx_t<0x0008'C001> PORT1;
	typedef portx_t<0x0008'C002> PORT2;
	typedef portx_t<0x0008'C003> PORT3;
	typedef portx_t<0x0008'C004> PORT4;
	typedef portx_t<0x0008'C005> PORT5;
	typedef portx_t<0x0008'C006> PORT6;
	typedef portx_t<0x0008'C007> PORT7;
	typedef portx_t<0x0008'C008> PORT8;
	typedef portx_t<0x0008'C009> PORT9;
	typedef portx_t<0x0008'C00A> PORTA;
	typedef portx_t<0x0008'C00B> PORTB;
	typedef portx_t<0x0008'C00C> PORTC;
	typedef portx_t<0x0008'C00D> PORTD;
	typedef portx_t<0x0008'C00E> PORTE;
	typedef portx_t<0x0008'C00F> PORTF;
	typedef portx_t<0x0008'C010> PORTG;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポート・オープンドレイン・タイプ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct PORT_BASE {
		enum class OD_TYPE : uint8_t {
			NONE,	///< 無し
			N_CH,	///< N-Channel
//			P_CH,	///< P-Channel
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  単ポート定義テンプレート
		@param[in]	PORT	ポート・クラス
		@param[in]	BPOS	ビット位置
		@param[in]	ASSERT	アサート論理 @n
							※反転入力、反転出力として扱う場合「０」
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class PORTX, bitpos BPOS, bool ASSERT = 1>
	struct PORT : public PORT_BASE {

		static constexpr uint8_t PNO     = static_cast<uint8_t>(PORTX::base_address_ & 0x1f);
		static constexpr uint8_t BIT_POS = static_cast<uint8_t>(BPOS);

		//-----------------------------------------------------------------//
		/*!
			@brief  ポート方向レジスタ
		*/
		//-----------------------------------------------------------------//
		typedef bit_rw_t<rw8_t<PORTX::base_address_ + 0x00>, BPOS> DIR_;
		static DIR_ DIR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートを出力にする
		*/
		//-----------------------------------------------------------------//
		static void OUTPUT() { DIR = 1; }


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートを入力にする
		*/
		//-----------------------------------------------------------------//
		static void INPUT() { DIR = 0; }


		//-----------------------------------------------------------------//
		/*!
			@brief  プルアップ制御・レジスタ
		*/
		//-----------------------------------------------------------------//
		typedef bit_rw_t<rw8_t<PORTX::base_address_ + 0xC0>, BPOS> PU_;
		static PU_ PU;


		//-----------------------------------------------------------------//
		/*!
			@brief  オープンドレイン制御・レジスタ
		*/
		//-----------------------------------------------------------------//
		struct od_t {
			static rw8_t<PORTX::base_address_ + 0x80> ODR;

			void operator = (OD_TYPE val) {
				uint8_t pos = static_cast<uint8_t>(BPOS);
				ODR = (ODR() & ~(3 << pos)) | (static_cast<uint8_t>(val) << pos);
			}

			OD_TYPE operator () () {
				uint8_t pos = static_cast<uint8_t>(BPOS);
				return static_cast<OD_TYPE>(ODR() & (3 << pos));
			}
		};
		typedef od_t OD_;
		static OD_ OD;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポート・レジスタ @n
					※ポート出力と、ポート入力が異なる
		*/
		//-----------------------------------------------------------------//
		struct port_t {
			typedef bit_rw_t<rw8_t<PORTX::base_address_ + 0x20>, BPOS> PO_;
			static PO_ PO;  // ポート出力用
			typedef bit_ro_t<ro8_t<PORTX::base_address_ + 0x40>, BPOS> PI_;
			static PI_ PI;  // ポート入力用

			void operator = (bool val) {
				if(ASSERT) { PO = val; } else { PO = !val; }
			}
			bool operator () () {
				if(ASSERT) { return PI(); } 
				else { return !PI(); }
			}
		};
		typedef port_t P_;
		static P_ P;


		//-----------------------------------------------------------------//
		/*!
			@brief  反転
		*/
		//-----------------------------------------------------------------//
		static void FLIP() { P = !P(); }
	};
	template <class PORTX, bitpos BPOS, bool ASSERT>
		typename PORT<PORTX, BPOS, ASSERT>::DIR_ PORT<PORTX, BPOS, ASSERT>::DIR;
	template <class PORTX, bitpos BPOS, bool ASSERT>
		typename PORT<PORTX, BPOS, ASSERT>::PU_ PORT<PORTX, BPOS, ASSERT>::PU;
	template <class PORTX, bitpos BPOS, bool ASSERT>
		typename PORT<PORTX, BPOS, ASSERT>::OD_ PORT<PORTX, BPOS, ASSERT>::OD;
	template <class PORTX, bitpos BPOS, bool ASSERT>
		typename PORT<PORTX, BPOS, ASSERT>::port_t::PO_ PORT<PORTX, BPOS, ASSERT>::port_t::PO;
	template <class PORTX, bitpos BPOS, bool ASSERT>
		typename PORT<PORTX, BPOS, ASSERT>::port_t::PI_ PORT<PORTX, BPOS, ASSERT>::port_t::PI;
	template <class PORTX, bitpos BPOS, bool ASSERT>
		typename PORT<PORTX, BPOS, ASSERT>::P_ PORT<PORTX, BPOS, ASSERT>::P;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ８ビット・ポート定義
		@param[in]	PORTx	ポート・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class PORTx>
	struct PORT_BYTE {

		//-----------------------------------------------------------------//
		/*!
			@brief  ポート方向レジスタ
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<PORTx::base_address_ + 0x00> DIR_;
		static DIR_ DIR;


		//-----------------------------------------------------------------//
		/*!
			@brief  プルアップ制御・レジスタ
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<PORTx::base_address_ + 0xC0> PU_;
		static PU_ PU;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポート・レジスタ @n
					※ポート出力と、ポート入力が異なる
		*/
		//-----------------------------------------------------------------//
		struct port_t {
			typedef rw8_t<PORTx::base_address_ + 0x20> PO_;
			static PO_ PO;	// ポート出力用
			typedef ro8_t<PORTx::base_address_ + 0x40> PI_;
			static PI_ PI;  // ポート入力用

			void operator = (uint8_t val) { PO = val; }
			uint8_t operator () () { return PI(); }
		};
		typedef port_t P_;
		static P_ P;
	};
	template <class PORTx> typename PORT_BYTE<PORTx>::DIR_ PORT_BYTE<PORTx>::DIR;
	template <class PORTx> typename PORT_BYTE<PORTx>::PU_  PORT_BYTE<PORTx>::PU;
	template <class PORTx> typename PORT_BYTE<PORTx>::P_::PO_  PORT_BYTE<PORTx>::P_::PO;
	template <class PORTx> typename PORT_BYTE<PORTx>::P_::PI_  PORT_BYTE<PORTx>::P_::PI;
	template <class PORTx> typename PORT_BYTE<PORTx>::P_   PORT_BYTE<PORTx>::P;


	template <class _>
	struct mpc_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  ポートファンクションレジスタ 8（PF8IRQ）
			@param[in] base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pf8irq_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B0> ITS8;
			bit_rw_t<io, bitpos::B1> ITS9;
			bit_rw_t<io, bitpos::B2> ITS10;
			bit_rw_t<io, bitpos::B3> ITS11;

			bit_rw_t<io, bitpos::B5> ITS13;

			bit_rw_t<io, bitpos::B7> ITS15;
		};
		typedef pf8irq_t<0x0008'C108> PF8IRQ_;
		static PF8IRQ_ PF8IRQ;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートファンクションレジスタ 9（PF9IRQ）
			@param[in] base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pf9irq_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B0> ITS0;
			bit_rw_t<io, bitpos::B1> ITS1;
			bit_rw_t<io, bitpos::B2> ITS2;
			bit_rw_t<io, bitpos::B3> ITS3;
			bit_rw_t<io, bitpos::B4> ITS4;
			bit_rw_t<io, bitpos::B5> ITS5;
			bit_rw_t<io, bitpos::B6> ITS6;
			bit_rw_t<io, bitpos::B7> ITS7;
		};
		typedef pf9irq_t<0x0008'C109> PF9IRQ_;
		static PF9IRQ_ PF9IRQ;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートファンクションレジスタ C（PFCMTU）
			@param[in] base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pfcmtu_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B2> MTUS2;
			bit_rw_t<io, bitpos::B3> MTUS3;
			bit_rw_t<io, bitpos::B4> MTUS4;
			bit_rw_t<io, bitpos::B5> MTUS5;
			bit_rw_t<io, bitpos::B6> MTUS6;
			bit_rw_t<io, bitpos::B7> TCLKS;
		};
		typedef pfcmtu_t<0x0008'C10C> PFCMTU_;
		static PFCMTU_ PFCMTU;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートファンクションレジスタ D（PFDMTU）
			@param[in] base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pfdmtu_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B6> MTUS6;
			bit_rw_t<io, bitpos::B7> TCLKS;
		};
		typedef pfdmtu_t<0x0008'C10D> PFDMTU_;
		static PFDMTU_ PFDMTU;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートファンクションレジスタ F（PFFSCI）
			@param[in] base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pffsci_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B1> SCI1S;
			bit_rw_t<io, bitpos::B2> SCI2S;
			bit_rw_t<io, bitpos::B3> SCI3S;

			bit_rw_t<io, bitpos::B6> SCI6S;
		};
		typedef pffsci_t<0x0008'C10F> PFFSCI_;
		static PFFSCI_ PFFSCI;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートファンクションレジスタ G（PFGSPI）
			@param[in] base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pfxspi_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B0> RSPIS;
			bit_rw_t<io, bitpos::B1> RSPCKE;
			bit_rw_t<io, bitpos::B2> MOSIE;
			bit_rw_t<io, bitpos::B3> MISOE;
			bit_rw_t<io, bitpos::B4> SSL0E;
			bit_rw_t<io, bitpos::B5> SSL1E;
			bit_rw_t<io, bitpos::B6> SSL2E;
			bit_rw_t<io, bitpos::B7> SSL3E;
		};
		typedef pfxspi_t<0x0008'C110> PFGSPI_;
		static PFGSPI_ PFGSPI;
		typedef pfxspi_t<0x0008'C111> PFHSPI_;
		static PFHSPI_ PFHSPI;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートファンクションレジスタ J（PFJCAN）
			@param[in] base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pfjcan_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B0> CAN0E;
		};
		typedef pfjcan_t<0x0008'C113> PFJCAN_;
		static PFJCAN_ PFJCAN;
	};
	template <class _> typename mpc_t<_>::PF8IRQ_ mpc_t<_>::PF8IRQ;
	template <class _> typename mpc_t<_>::PF9IRQ_ mpc_t<_>::PF9IRQ;
	template <class _> typename mpc_t<_>::PFCMTU_ mpc_t<_>::PFCMTU;
	template <class _> typename mpc_t<_>::PFDMTU_ mpc_t<_>::PFDMTU;
	template <class _> typename mpc_t<_>::PFFSCI_ mpc_t<_>::PFFSCI;
	template <class _> typename mpc_t<_>::PFGSPI_ mpc_t<_>::PFGSPI;
	template <class _> typename mpc_t<_>::PFHSPI_ mpc_t<_>::PFHSPI;
	template <class _> typename mpc_t<_>::PFJCAN_ mpc_t<_>::PFJCAN;

	typedef mpc_t<void> MPC;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  無効ポート定義
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class _>
	struct NULL_PORT_t {

		static constexpr uint8_t PNO     = 0xff;
		static constexpr uint8_t BIT_POS = 0xff;

		struct null_t {
			void operator = (bool f) { }
			bool operator () () const { return 0; } 
		};

		//-----------------------------------------------------------------//
		/*!
			@brief  ポート方向レジスタ
		*/
		//-----------------------------------------------------------------//
		static null_t DIR;


		//-----------------------------------------------------------------//
		/*!
			@brief  プルアップ制御・レジスタ
		*/
		//-----------------------------------------------------------------//
		static null_t PU;


		//-----------------------------------------------------------------//
		/*!
			@brief  オープンドレイン制御・レジスタ
		*/
		//-----------------------------------------------------------------//
		static null_t OD;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポート・レジスタ
		*/
		//-----------------------------------------------------------------//
		static null_t P;
	};
	typedef NULL_PORT_t<void> NULL_PORT;
	template <class _> typename NULL_PORT_t<_>::null_t NULL_PORT_t<_>::DIR;
	template <class _> typename NULL_PORT_t<_>::null_t NULL_PORT_t<_>::PU;
	template <class _> typename NULL_PORT_t<_>::null_t NULL_PORT_t<_>::OD;
	template <class _> typename NULL_PORT_t<_>::null_t NULL_PORT_t<_>::P;
}

