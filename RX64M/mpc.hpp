#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M グループ MPC 定義 @n
			Copyright 2013 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  マルチファンクションピンコントローラークラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct mpc_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  書き込みプロテクトレジスタ (PWPR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x0008C11F> pwpr_io;
		struct pwpr_t : public pwpr_io {
			using pwpr_io::operator =;
			using pwpr_io::operator ();
			using pwpr_io::operator |=;
			using pwpr_io::operator &=;

			bit_rw_t<pwpr_io, bitpos::B6> PFSWE;
			bit_rw_t<pwpr_io, bitpos::B7> B0WI;
		};
		static pwpr_t PWPR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  端子機能制御規定クラス W
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfsw_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bits_rw_t<io, bitpos::B0, 6>  PSEL;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  端子機能制御規定クラス M
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfsm_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bits_rw_t<io, bitpos::B0, 6>  PSEL;
			bit_rw_t< io, bitpos::B7>     ASEL;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  端子機能制御規定クラス X
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfsx_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bits_rw_t<io, bitpos::B0, 6>  PSEL;
			bit_rw_t< io, bitpos::B6>     ISEL;
			bit_rw_t< io, bitpos::B7>     ASEL;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  端子機能制御規定クラス Y
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfsy_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bits_rw_t<io, bitpos::B0, 6>  PSEL;
			bit_rw_t<io, bitpos::B6>      ISEL;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  端子機能制御規定クラス Z
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfsz_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B6>      ISEL;
			bit_rw_t<io, bitpos::B7>      ASEL;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P0n 端子機能制御レジスタ（P0nPFS）（n = 0 ～ 3, 5, 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsx_t<0x0008C140> P00PFS;
		static pfsx_t<0x0008C141> P01PFS;
		static pfsx_t<0x0008C142> P02PFS;
		static pfsx_t<0x0008C143> P03PFS;
		static pfsx_t<0x0008C145> P05PFS;
		static pfsx_t<0x0008C147> P07PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P1n 端子機能制御レジスタ（P1nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsy_t<0x0008C148> P10PFS;
		static pfsy_t<0x0008C149> P11PFS;
		static pfsy_t<0x0008C14A> P12PFS;
		static pfsy_t<0x0008C14B> P13PFS;
		static pfsy_t<0x0008C14C> P14PFS;
		static pfsy_t<0x0008C14D> P15PFS;
		static pfsy_t<0x0008C14E> P16PFS;
		static pfsy_t<0x0008C14F> P17PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P2n 端子機能制御レジスタ（P2nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsy_t<0x0008C150> P20PFS;
		static pfsy_t<0x0008C151> P21PFS;
		static pfsy_t<0x0008C152> P22PFS;
		static pfsy_t<0x0008C153> P23PFS;
		static pfsy_t<0x0008C154> P24PFS;
		static pfsy_t<0x0008C155> P25PFS;
		static pfsy_t<0x0008C156> P26PFS;
		static pfsy_t<0x0008C157> P27PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P3n 端子機能制御レジスタ（P3nPFS）（n = 0 ～ 4）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsy_t<0x0008C158> P30PFS;
		static pfsy_t<0x0008C159> P31PFS;
		static pfsy_t<0x0008C15A> P32PFS;
		static pfsy_t<0x0008C15B> P33PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P4n 端子機能制御レジスタ（P4nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsz_t<0x0008C160> P40PFS;
		static pfsz_t<0x0008C161> P41PFS;
		static pfsz_t<0x0008C162> P42PFS;
		static pfsz_t<0x0008C163> P43PFS;
		static pfsz_t<0x0008C164> P44PFS;
		static pfsz_t<0x0008C165> P45PFS;
		static pfsz_t<0x0008C166> P46PFS;
		static pfsz_t<0x0008C167> P47PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P5n 端子機能制御レジスタ（P5nPFS）（n = 0 ～ 2, 4 ～ 6）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsy_t<0x0008C168> P50PFS;
		static pfsy_t<0x0008C169> P51PFS;
		static pfsy_t<0x0008C16A> P52PFS;
		static pfsy_t<0x0008C16C> P54PFS;
		static pfsy_t<0x0008C16D> P55PFS;
		static pfsy_t<0x0008C16E> P56PFS;
		static pfsy_t<0x0008C16F> P57PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P6n 端子機能制御レジスタ（P6nPFS）（n = 0, 6, 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsy_t<0x0008C170> P60PFS;
		static pfsy_t<0x0008C176> P66PFS;
		static pfsy_t<0x0008C177> P67PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P7n 端子機能制御レジスタ（P7nPFS）（n = 1 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsw_t<0x0008C179> P71PFS;
		static pfsw_t<0x0008C17A> P72PFS;
		static pfsw_t<0x0008C17B> P73PFS;
		static pfsw_t<0x0008C17C> P74PFS;
		static pfsw_t<0x0008C17D> P75PFS;
		static pfsw_t<0x0008C17E> P76PFS;
		static pfsw_t<0x0008C17F> P77PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P8n 端子機能制御レジスタ（P8nPFS）（n = 0 ～ 3, 6, 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsw_t<0x0008C180> P80PFS;
		static pfsw_t<0x0008C181> P81PFS;
		static pfsw_t<0x0008C182> P82PFS;
		static pfsw_t<0x0008C183> P83PFS;
		static pfsw_t<0x0008C186> P86PFS;
		static pfsw_t<0x0008C187> P87PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P9n 端子機能制御レジスタ（P9nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsm_t<0x0008C188> P90PFS;
		static pfsm_t<0x0008C189> P91PFS;
		static pfsm_t<0x0008C18A> P92PFS;
		static pfsm_t<0x0008C18B> P93PFS;
		static pfsm_t<0x0008C18C> P94PFS;
		static pfsm_t<0x0008C18D> P95PFS;
		static pfsm_t<0x0008C18E> P96PFS;
		static pfsm_t<0x0008C18F> P97PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PAn 端子機能制御レジスタ（PAnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsy_t<0x0008C190> PA0PFS;
		static pfsy_t<0x0008C191> PA1PFS;
		static pfsy_t<0x0008C192> PA2PFS;
		static pfsy_t<0x0008C193> PA3PFS;
		static pfsy_t<0x0008C194> PA4PFS;
		static pfsy_t<0x0008C195> PA5PFS;
		static pfsy_t<0x0008C196> PA6PFS;
		static pfsy_t<0x0008C197> PA7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PBn 端子機能制御レジスタ（PBnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsy_t<0x0008C198> PB0PFS;
		static pfsy_t<0x0008C199> PB1PFS;
		static pfsy_t<0x0008C19A> PB2PFS;
		static pfsy_t<0x0008C19B> PB3PFS;
		static pfsy_t<0x0008C19C> PB4PFS;
		static pfsy_t<0x0008C19D> PB5PFS;
		static pfsy_t<0x0008C19E> PB6PFS;
		static pfsy_t<0x0008C19F> PB7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PCn 端子機能制御レジスタ（PCnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsy_t<0x0008C1A0> PC0PFS;
		static pfsy_t<0x0008C1A1> PC1PFS;
		static pfsy_t<0x0008C1A2> PC2PFS;
		static pfsy_t<0x0008C1A3> PC3PFS;
		static pfsy_t<0x0008C1A4> PC4PFS;
		static pfsy_t<0x0008C1A5> PC5PFS;
		static pfsy_t<0x0008C1A6> PC6PFS;
		static pfsy_t<0x0008C1A7> PC7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PDn 端子機能制御レジスタ（PDnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsx_t<0x0008C1A8> PD0PFS;
		static pfsx_t<0x0008C1A9> PD1PFS;
		static pfsx_t<0x0008C1AA> PD2PFS;
		static pfsx_t<0x0008C1AB> PD3PFS;
		static pfsx_t<0x0008C1AC> PD4PFS;
		static pfsx_t<0x0008C1AD> PD5PFS;
		static pfsx_t<0x0008C1AE> PD6PFS;
		static pfsx_t<0x0008C1AF> PD7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PEn 端子機能制御レジスタ（PEnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsx_t<0x0008C1B0> PE0PFS;
		static pfsx_t<0x0008C1B1> PE1PFS;
		static pfsx_t<0x0008C1B2> PE2PFS;
		static pfsx_t<0x0008C1B3> PE3PFS;
		static pfsx_t<0x0008C1B4> PE4PFS;
		static pfsx_t<0x0008C1B5> PE5PFS;
		static pfsx_t<0x0008C1B6> PE6PFS;
		static pfsx_t<0x0008C1B7> PE7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PFn 端子機能制御レジスタ（PFnPFS）（n = 0 ～ 2）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsy_t<0x0008C1B8> PF0PFS;
		static pfsy_t<0x0008C1B9> PF1PFS;
		static pfsy_t<0x0008C1BA> PF2PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PGn 端子機能制御レジスタ（PGnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsw_t<0x0008C1C0> PG0PFS;
		static pfsw_t<0x0008C1C1> PG1PFS;
		static pfsw_t<0x0008C1C2> PG2PFS;
		static pfsw_t<0x0008C1C3> PG3PFS;
		static pfsw_t<0x0008C1C4> PG4PFS;
		static pfsw_t<0x0008C1C5> PG5PFS;
		static pfsw_t<0x0008C1C6> PG6PFS;
		static pfsw_t<0x0008C1C7> PG7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PJn 端子機能制御レジスタ（PJnPFS）（n = 3, 5）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsw_t<0x0008C1D3> PJ3PFS;
		static pfsw_t<0x0008C1D5> PJ5PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CS 出力許可レジスタ（PFCSE）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfcse_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B0>  CS0E;
			bit_rw_t<io, bitpos::B1>  CS1E;
			bit_rw_t<io, bitpos::B2>  CS2E;
			bit_rw_t<io, bitpos::B3>  CS3E;
			bit_rw_t<io, bitpos::B4>  CS4E;
			bit_rw_t<io, bitpos::B5>  CS5E;
			bit_rw_t<io, bitpos::B6>  CS6E;
			bit_rw_t<io, bitpos::B7>  CS7E;
		};
		static pfcse_t<0x0008C100> PFCSE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CS 出力端子選択レジスタ 0（PFCSS0）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfcss0_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B0>  CS0S;
			bits_rw_t<io, bitpos::B2, 2>  CS1S;
			bits_rw_t<io, bitpos::B4, 2>  CS2S;
			bits_rw_t<io, bitpos::B6, 2>  CS3S;
		};
		static pfcss0_t<0x0008C102> PFCSS0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CS 出力端子選択レジスタ 1（PFCSS1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfcss1_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bits_rw_t<io, bitpos::B0, 2>  CS4S;
			bits_rw_t<io, bitpos::B2, 2>  CS5S;
			bits_rw_t<io, bitpos::B4, 2>  CS6S;
			bits_rw_t<io, bitpos::B6, 2>  CS7S;
		};
		static pfcss1_t<0x0008C103> PFCSS1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アドレス出力許可レジスタ 0（PFAOE0）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfaoe0_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B0>  A8E;
			bit_rw_t<io, bitpos::B1>  A9E;
			bit_rw_t<io, bitpos::B2>  A10E;
			bit_rw_t<io, bitpos::B3>  A11E;
			bit_rw_t<io, bitpos::B4>  A12E;
			bit_rw_t<io, bitpos::B5>  A13E;
			bit_rw_t<io, bitpos::B6>  A14E;
			bit_rw_t<io, bitpos::B7>  A15E;
		};
		static pfaoe0_t<0x0008C104> PFAOE0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アドレス出力許可レジスタ 1（PFAOE1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfaoe1_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B0>  A16E;
			bit_rw_t<io, bitpos::B1>  A17E;
			bit_rw_t<io, bitpos::B2>  A18E;
			bit_rw_t<io, bitpos::B3>  A19E;
			bit_rw_t<io, bitpos::B4>  A20E;
			bit_rw_t<io, bitpos::B5>  A21E;
			bit_rw_t<io, bitpos::B6>  A22E;
			bit_rw_t<io, bitpos::B7>  A23E;
		};
		static pfaoe0_t<0x0008C105> PFAOE1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  外部バス制御レジスタ 0（PFBCR0）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//



		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  外部バス制御レジスタ 1（PFBCR1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//



	};
	typedef mpc_t MPC;
}
