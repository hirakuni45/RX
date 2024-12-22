#pragma once
//=========================================================================//
/*!	@file
	@brief	Multi-Function Pin Controller / マルチファンクションピンコントローラ (RX651/RX65N)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  MPC class
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct mpc_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  書き込みプロテクトレジスタ (PWPR)
			@param[in]	base	アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pwpr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B6> PFSWE;
			bit_rw_t<io_, bitpos::B7> B0WI;
		};
		static inline pwpr_t<0x0008'C11F> PWPR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  端子機能制御規定クラス W
			@param[in]	base	アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfs_p_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>  PSEL;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  端子機能制御規定クラス PA
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfs_pa_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bits_rw_t<io, bitpos::B0, 6>  PSEL;
			bit_rw_t< io, bitpos::B7>     ASEL;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  端子機能制御規定クラス PIA
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfs_pia_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bits_rw_t<io, bitpos::B0, 6>  PSEL;
			bit_rw_t< io, bitpos::B6>     ISEL;
			bit_rw_t< io, bitpos::B7>     ASEL;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  端子機能制御規定クラス PI
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfs_pi_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bits_rw_t<io, bitpos::B0, 6>  PSEL;
			bit_rw_t <io, bitpos::B6>     ISEL;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  端子機能制御規定クラス IA
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfs_ia_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B6>      ISEL;
			bit_rw_t<io, bitpos::B7>      ASEL;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  端子機能制御規定クラス A
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfs_a_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B7>      ASEL;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P0n 端子機能制御レジスタ（P0nPFS）（n = 0 ～ 3, 5, 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_pia_t<0x0008'C140> P00PFS;
		static inline pfs_pia_t<0x0008'C141> P01PFS;
		static inline pfs_pia_t<0x0008'C142> P02PFS;
		static inline pfs_pia_t<0x0008'C143> P03PFS;
		static inline pfs_pia_t<0x0008'C145> P05PFS;
		static inline pfs_pia_t<0x0008'C147> P07PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P1n 端子機能制御レジスタ（P1nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_pi_t<0x0008'C148> P10PFS;
		static inline pfs_pi_t<0x0008'C149> P11PFS;
		static inline pfs_pi_t<0x0008'C14A> P12PFS;
		static inline pfs_pi_t<0x0008'C14B> P13PFS;
		static inline pfs_pi_t<0x0008'C14C> P14PFS;
		static inline pfs_pi_t<0x0008'C14D> P15PFS;
		static inline pfs_pi_t<0x0008'C14E> P16PFS;
		static inline pfs_pi_t<0x0008'C14F> P17PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P2n 端子機能制御レジスタ（P2nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_pi_t<0x0008'C150> P20PFS;
		static inline pfs_pi_t<0x0008'C151> P21PFS;
		static inline pfs_pi_t<0x0008'C152> P22PFS;
		static inline pfs_pi_t<0x0008'C153> P23PFS;
		static inline pfs_pi_t<0x0008'C154> P24PFS;
		static inline pfs_pi_t<0x0008'C155> P25PFS;
		static inline pfs_pi_t<0x0008'C156> P26PFS;
		static inline pfs_pi_t<0x0008'C157> P27PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P3n 端子機能制御レジスタ（P3nPFS）（n = 0 ～ 4）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_pi_t<0x0008'C158> P30PFS;
		static inline pfs_pi_t<0x0008'C159> P31PFS;
		static inline pfs_pi_t<0x0008'C15A> P32PFS;
		static inline pfs_pi_t<0x0008'C15B> P33PFS;
		static inline pfs_pi_t<0x0008'C15C> P34PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P4n 端子機能制御レジスタ（P4nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ia_t<0x0008'C160> P40PFS;
		static inline pfs_ia_t<0x0008'C161> P41PFS;
		static inline pfs_ia_t<0x0008'C162> P42PFS;
		static inline pfs_ia_t<0x0008'C163> P43PFS;
		static inline pfs_ia_t<0x0008'C164> P44PFS;
		static inline pfs_ia_t<0x0008'C165> P45PFS;
		static inline pfs_ia_t<0x0008'C166> P46PFS;
		static inline pfs_ia_t<0x0008'C167> P47PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P5n 端子機能制御レジスタ（P5nPFS）（n = 0 ～ 2, 4 ～ 6）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_pi_t<0x0008'C168> P50PFS;
		static inline pfs_pi_t<0x0008'C169> P51PFS;
		static inline pfs_pi_t<0x0008'C16A> P52PFS;
		static inline pfs_pi_t<0x0008'C16C> P54PFS;
		static inline pfs_pi_t<0x0008'C16D> P55PFS;
		static inline pfs_pi_t<0x0008'C16E> P56PFS;
		static inline pfs_pi_t<0x0008'C16F> P57PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P6n 端子機能制御レジスタ（P6nPFS）（n = 6, 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_pi_t<0x0008'C170> P60PFS;
		static inline pfs_pi_t<0x0008'C176> P66PFS;
		static inline pfs_pi_t<0x0008'C177> P67PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P7n 端子機能制御レジスタ（P7nPFS）（n = 1 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_p_t<0x0008'C178> P70PFS;
		static inline pfs_p_t<0x0008'C179> P71PFS;
		static inline pfs_p_t<0x0008'C17A> P72PFS;
		static inline pfs_p_t<0x0008'C17B> P73PFS;
		static inline pfs_p_t<0x0008'C17C> P74PFS;
		static inline pfs_p_t<0x0008'C17D> P75PFS;
		static inline pfs_p_t<0x0008'C17E> P76PFS;
		static inline pfs_p_t<0x0008'C17F> P77PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P8n 端子機能制御レジスタ（P8nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_p_t<0x0008'C180> P80PFS;
		static inline pfs_p_t<0x0008'C181> P81PFS;
		static inline pfs_p_t<0x0008'C182> P82PFS;
		static inline pfs_p_t<0x0008'C183> P83PFS;
		static inline pfs_p_t<0x0008'C184> P84PFS;
		static inline pfs_p_t<0x0008'C185> P85PFS;
		static inline pfs_p_t<0x0008'C186> P86PFS;
		static inline pfs_p_t<0x0008'C187> P87PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P9n 端子機能制御レジスタ（P9nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_pa_t<0x0008'C188> P90PFS;
		static inline pfs_pa_t<0x0008'C189> P91PFS;
		static inline pfs_pa_t<0x0008'C18A> P92PFS;
		static inline pfs_pa_t<0x0008'C18B> P93PFS;
		static inline pfs_pa_t<0x0008'C18C> P94PFS;
		static inline pfs_pa_t<0x0008'C18D> P95PFS;
		static inline pfs_pa_t<0x0008'C18E> P96PFS;
		static inline pfs_pa_t<0x0008'C18F> P97PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PAn 端子機能制御レジスタ（PAnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_pi_t<0x0008'C190> PA0PFS;
		static inline pfs_pi_t<0x0008'C191> PA1PFS;
		static inline pfs_pi_t<0x0008'C192> PA2PFS;
		static inline pfs_pi_t<0x0008'C193> PA3PFS;
		static inline pfs_pi_t<0x0008'C194> PA4PFS;
		static inline pfs_pi_t<0x0008'C195> PA5PFS;
		static inline pfs_pi_t<0x0008'C196> PA6PFS;
		static inline pfs_pi_t<0x0008'C197> PA7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PBn 端子機能制御レジスタ（PBnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_pi_t<0x0008'C198> PB0PFS;
		static inline pfs_pi_t<0x0008'C199> PB1PFS;
		static inline pfs_pi_t<0x0008'C19A> PB2PFS;
		static inline pfs_pi_t<0x0008'C19B> PB3PFS;
		static inline pfs_pi_t<0x0008'C19C> PB4PFS;
		static inline pfs_pi_t<0x0008'C19D> PB5PFS;
		static inline pfs_pi_t<0x0008'C19E> PB6PFS;
		static inline pfs_pi_t<0x0008'C19F> PB7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PCn 端子機能制御レジスタ（PCnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_pi_t<0x0008'C1A0> PC0PFS;
		static inline pfs_pi_t<0x0008'C1A1> PC1PFS;
		static inline pfs_pi_t<0x0008'C1A2> PC2PFS;
		static inline pfs_pi_t<0x0008'C1A3> PC3PFS;
		static inline pfs_pi_t<0x0008'C1A4> PC4PFS;
		static inline pfs_pi_t<0x0008'C1A5> PC5PFS;
		static inline pfs_pi_t<0x0008'C1A6> PC6PFS;
		static inline pfs_pi_t<0x0008'C1A7> PC7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PDn 端子機能制御レジスタ（PDnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_pia_t<0x0008'C1A8> PD0PFS;
		static inline pfs_pia_t<0x0008'C1A9> PD1PFS;
		static inline pfs_pia_t<0x0008'C1AA> PD2PFS;
		static inline pfs_pia_t<0x0008'C1AB> PD3PFS;
		static inline pfs_pia_t<0x0008'C1AC> PD4PFS;
		static inline pfs_pia_t<0x0008'C1AD> PD5PFS;
		static inline pfs_pia_t<0x0008'C1AE> PD6PFS;
		static inline pfs_pia_t<0x0008'C1AF> PD7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PEn 端子機能制御レジスタ（PEnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_pia_t<0x0008'C1B0> PE0PFS;
		static inline pfs_pia_t<0x0008'C1B1> PE1PFS;
		static inline pfs_pia_t<0x0008'C1B2> PE2PFS;
		static inline pfs_pia_t<0x0008'C1B3> PE3PFS;
		static inline pfs_pia_t<0x0008'C1B4> PE4PFS;
		static inline pfs_pia_t<0x0008'C1B5> PE5PFS;
		static inline pfs_pia_t<0x0008'C1B6> PE6PFS;
		static inline pfs_pia_t<0x0008'C1B7> PE7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PFn 端子機能制御レジスタ（PFnPFS）（n = 0 ～ 2, 5）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_pi_t<0x0008'C1B8> PF0PFS;
		static inline pfs_pi_t<0x0008'C1B9> PF1PFS;
		static inline pfs_pi_t<0x0008'C1BA> PF2PFS;
		static inline pfs_pi_t<0x0008'C1BD> PF5PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PJn 端子機能制御レジスタ（PJnPFS）（n = 0 ～ 3, 5）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_p_t<0x0008'C1D0> PJ0PFS;
		static inline pfs_p_t<0x0008'C1D1> PJ1PFS;
		static inline pfs_p_t<0x0008'C1D2> PJ2PFS;
		static inline pfs_p_t<0x0008'C1D3> PJ3PFS;
		static inline pfs_p_t<0x0008'C1D5> PJ5PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CS 出力許可レジスタ（PFCSE）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		static inline pfcse_t<0x0008'C100> PFCSE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CS 出力端子選択レジスタ 0（PFCSS0）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfcss0_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B0>      CS0S;
			bits_rw_t<io, bitpos::B2, 2>  CS1S;
			bits_rw_t<io, bitpos::B4, 2>  CS2S;
			bits_rw_t<io, bitpos::B6, 2>  CS3S;
		};
		static inline pfcss0_t<0x0008'C102> PFCSS0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CS 出力端子選択レジスタ 1（PFCSS1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		static inline pfcss1_t<0x0008'C103> PFCSS1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アドレス出力許可レジスタ 0（PFAOE0）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		static inline pfaoe0_t<0x0008'C104> PFAOE0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アドレス出力許可レジスタ 1（PFAOE1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		static inline pfaoe0_t<0x0008'C105> PFAOE1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  外部バス制御レジスタ 0（PFBCR0）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfbcr0_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B0>  ADRLE;
			bit_rw_t<io, bitpos::B1>  ADRHMS;
			bit_rw_t<io, bitpos::B2>  ADRHMS2;
			bit_rw_t<io, bitpos::B3>  BCLKO;
			bit_rw_t<io, bitpos::B4>  DHE;
			bit_rw_t<io, bitpos::B5>  DH32E;
			bit_rw_t<io, bitpos::B6>  WR1BC1E;
			bit_rw_t<io, bitpos::B7>  WR32BC32E;
		};
		static inline pfbcr0_t<0x0008'C106> PFBCR0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  外部バス制御レジスタ 1（PFBCR1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfbcr1_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bits_rw_t<io, bitpos::B0, 2>  WAITS;
			bit_rw_t <io, bitpos::B2>     ALEOE;
			bit_rw_t <io, bitpos::B3>     ALES;
			bit_rw_t <io, bitpos::B4>     MDSDE;
			bit_rw_t <io, bitpos::B6>     DQM1E;
			bit_rw_t <io, bitpos::B7>     SDCLKE;
		};
		static inline pfbcr1_t<0x0008'C107> PFBCR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  外部バス制御レジスタ 2（PFBCR2）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfbcr2_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bits_rw_t<io, bitpos::B0, 2>  D0S;
			bits_rw_t<io, bitpos::B2, 2>  D1S;
			bits_rw_t<io, bitpos::B4, 2>  D2S;
			bits_rw_t<io, bitpos::B6, 2>  D3S;
		};
		static inline pfbcr2_t<0x0008'C108> PFBCR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  外部バス制御レジスタ 3（PFBCR3）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfbcr3_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t <io, bitpos::B0>     DLHS;
		};
		static inline pfbcr3_t<0x0008'C109> PFBCR3;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  イーサネット制御レジスタ（PFENET）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfenet_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B4>  PHYMODE0;
		};
		static inline pfenet_t<0x0008'C10E> PFENET;
	};
	typedef mpc_t MPC;
}
