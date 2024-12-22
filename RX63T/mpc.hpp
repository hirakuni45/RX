#pragma once
//=========================================================================//
/*!	@file
	@brief	Multi-Function Pin Controller / マルチファンクションピンコントローラ (RX63T)
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
			@brief  端子機能制御規定クラス X
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfs_ip_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bits_rw_t<io, bitpos::B0, 5>  PSEL;
			bit_rw_t< io, bitpos::B6>     ISEL;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  端子機能制御規定クラス Y
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfs_p_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bits_rw_t<io, bitpos::B0, 5>  PSEL;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  端子機能制御規定クラス Z
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
			@brief  P0n 端子機能制御レジスタ（P0nPFS）（n = 0 ～ 3）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ip_t<0x0008'C140> P00PFS;
		static inline pfs_ip_t<0x0008'C141> P01PFS;
		static inline pfs_ip_t<0x0008'C142> P02PFS;
		static inline pfs_ip_t<0x0008'C143> P03PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P1n 端子機能制御レジスタ（P1nPFS）（n = 0 ～ 4）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ip_t<0x0008'C148> P10PFS;
		static inline pfs_ip_t<0x0008'C149> P11PFS;
		static inline pfs_ip_t<0x0008'C14A> P12PFS;
		static inline pfs_ip_t<0x0008'C14B> P13PFS;
		static inline pfs_ip_t<0x0008'C14C> P14PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P2n 端子機能制御レジスタ（P2nPFS）（n = 0 ～ 6）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ip_t<0x0008'C150> P20PFS;
		static inline pfs_ip_t<0x0008'C151> P21PFS;
		static inline pfs_ip_t<0x0008'C152> P22PFS;
		static inline pfs_ip_t<0x0008'C153> P23PFS;
		static inline pfs_ip_t<0x0008'C154> P24PFS;
		static inline pfs_ip_t<0x0008'C155> P25PFS;
		static inline pfs_ip_t<0x0008'C156> P26PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P3n 端子機能制御レジスタ（P3nPFS）（n = 0 ～ 5）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ip_t<0x0008'C158> P30PFS;
		static inline pfs_ip_t<0x0008'C159> P31PFS;
		static inline pfs_ip_t<0x0008'C15A> P32PFS;
		static inline pfs_ip_t<0x0008'C15B> P33PFS;
		static inline pfs_ip_t<0x0008'C15C> P34PFS;
		static inline pfs_ip_t<0x0008'C15D> P35PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P4n 端子機能制御レジスタ（P4nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_a_t<0x0008'C160> P40PFS;
		static inline pfs_a_t<0x0008'C161> P41PFS;
		static inline pfs_a_t<0x0008'C162> P42PFS;
		static inline pfs_a_t<0x0008'C163> P43PFS;
		static inline pfs_a_t<0x0008'C164> P44PFS;
		static inline pfs_a_t<0x0008'C165> P45PFS;
		static inline pfs_a_t<0x0008'C166> P46PFS;
		static inline pfs_a_t<0x0008'C167> P47PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P5n 端子機能制御レジスタ（P5nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_a_t<0x0008'C168> P50PFS;
		static inline pfs_a_t<0x0008'C169> P51PFS;
		static inline pfs_a_t<0x0008'C16A> P52PFS;
		static inline pfs_a_t<0x0008'C16B> P53PFS;
		static inline pfs_a_t<0x0008'C16C> P54PFS;
		static inline pfs_a_t<0x0008'C16D> P55PFS;
		static inline pfs_a_t<0x0008'C16E> P56PFS;
		static inline pfs_a_t<0x0008'C16F> P57PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P6n 端子機能制御レジスタ（P6nPFS）（n = 0 ～ 5）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_a_t<0x0008'C170> P60PFS;
		static inline pfs_a_t<0x0008'C171> P61PFS;
		static inline pfs_a_t<0x0008'C172> P62PFS;
		static inline pfs_a_t<0x0008'C173> P63PFS;
		static inline pfs_a_t<0x0008'C174> P64PFS;
		static inline pfs_a_t<0x0008'C175> P65PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P7n 端子機能制御レジスタ（P7nPFS）（n = 0 ～ 6）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ip_t<0x0008'C178> P70PFS;
		static inline pfs_ip_t<0x0008'C179> P71PFS;
		static inline pfs_ip_t<0x0008'C17A> P72PFS;
		static inline pfs_ip_t<0x0008'C17B> P73PFS;
		static inline pfs_ip_t<0x0008'C17C> P74PFS;
		static inline pfs_ip_t<0x0008'C17D> P75PFS;
		static inline pfs_ip_t<0x0008'C17E> P76PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P8n 端子機能制御レジスタ（P8nPFS）（n = 0 ～ 2）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ip_t<0x0008'C180> P80PFS;
		static inline pfs_ip_t<0x0008'C181> P81PFS;
		static inline pfs_ip_t<0x0008'C182> P82PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P9n 端子機能制御レジスタ（P9nPFS）（n = 0 ～ 6）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ip_t<0x0008'C188> P90PFS;
		static inline pfs_ip_t<0x0008'C189> P91PFS;
		static inline pfs_ip_t<0x0008'C18A> P92PFS;
		static inline pfs_ip_t<0x0008'C18B> P93PFS;
		static inline pfs_ip_t<0x0008'C18C> P94PFS;
		static inline pfs_ip_t<0x0008'C18D> P95PFS;
		static inline pfs_ip_t<0x0008'C18E> P96PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PAn 端子機能制御レジスタ（PAnPFS）（n = 0 ～ 6）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_p_t<0x0008'C190> PA0PFS;
		static inline pfs_p_t<0x0008'C191> PA1PFS;
		static inline pfs_p_t<0x0008'C192> PA2PFS;
		static inline pfs_p_t<0x0008'C193> PA3PFS;
		static inline pfs_p_t<0x0008'C194> PA4PFS;
		static inline pfs_p_t<0x0008'C195> PA5PFS;
		static inline pfs_p_t<0x0008'C196> PA6PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PBn 端子機能制御レジスタ（PBnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ip_t<0x0008'C198> PB0PFS;
		static inline pfs_ip_t<0x0008'C199> PB1PFS;
		static inline pfs_ip_t<0x0008'C19A> PB2PFS;
		static inline pfs_ip_t<0x0008'C19B> PB3PFS;
		static inline pfs_ip_t<0x0008'C19C> PB4PFS;
		static inline pfs_ip_t<0x0008'C19D> PB5PFS;
		static inline pfs_ip_t<0x0008'C19E> PB6PFS;
		static inline pfs_ip_t<0x0008'C19F> PB7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PCn 端子機能制御レジスタ（PCnPFS）（n = 0 ～ 5）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_a_t<0x0008'C1A0> PC0PFS;
		static inline pfs_a_t<0x0008'C1A1> PC1PFS;
		static inline pfs_a_t<0x0008'C1A2> PC2PFS;
		static inline pfs_a_t<0x0008'C1A3> PC3PFS;
		static inline pfs_a_t<0x0008'C1A4> PC4PFS;
		static inline pfs_a_t<0x0008'C1A5> PC5PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PDn 端子機能制御レジスタ（PDnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ip_t<0x0008'C1A8> PD0PFS;
		static inline pfs_ip_t<0x0008'C1A9> PD1PFS;
		static inline pfs_ip_t<0x0008'C1AA> PD2PFS;
		static inline pfs_ip_t<0x0008'C1AB> PD3PFS;
		static inline pfs_ip_t<0x0008'C1AC> PD4PFS;
		static inline pfs_ip_t<0x0008'C1AD> PD5PFS;
		static inline pfs_ip_t<0x0008'C1AE> PD6PFS;
		static inline pfs_ip_t<0x0008'C1AF> PD7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PEn 端子機能制御レジスタ（PEnPFS）（n = 0 ～ 5）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ip_t<0x0008'C1B0> PE0PFS;
		static inline pfs_ip_t<0x0008'C1B1> PE1PFS;
		static inline pfs_ip_t<0x0008'C1B2> PE2PFS;
		static inline pfs_ip_t<0x0008'C1B3> PE3PFS;
		static inline pfs_ip_t<0x0008'C1B4> PE4PFS;
		static inline pfs_ip_t<0x0008'C1B5> PE5PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PFn 端子機能制御レジスタ（PFnPFS）（n = 2, 3）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ip_t<0x0008'C1BA> PF2PFS;
		static inline pfs_ip_t<0x0008'C1BB> PF3PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PGn 端子機能制御レジスタ（PGnPFS）（n = 0 ～ 6）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ip_t<0x0008'C1C0> PG0PFS;
		static inline pfs_ip_t<0x0008'C1C1> PG1PFS;
		static inline pfs_ip_t<0x0008'C1C2> PG2PFS;
		static inline pfs_ip_t<0x0008'C1C3> PG3PFS;
		static inline pfs_ip_t<0x0008'C1C4> PG4PFS;
		static inline pfs_ip_t<0x0008'C1C5> PG5PFS;
		static inline pfs_ip_t<0x0008'C1C6> PG6PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  USB0_DPUPE 端子機能制御レジスタ（UDPUPEPFS）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_p_t<0x0008'C1D0> UDPUPEPFS;


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

			bit_rw_t<io, bitpos::B0>   CS0E;
			bit_rw_t<io, bitpos::B1>   CS1E;
			bit_rw_t<io, bitpos::B2>   CS2E;
			bit_rw_t<io, bitpos::B3>   CS3E;
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

			bit_rw_t<io, bitpos::B0>   A8E;
			bit_rw_t<io, bitpos::B1>   A9E;
			bit_rw_t<io, bitpos::B2>   A10E;
			bit_rw_t<io, bitpos::B3>   A11E;
			bit_rw_t<io, bitpos::B4>   A12E;
			bit_rw_t<io, bitpos::B5>   A13E;
			bit_rw_t<io, bitpos::B6>   A14E;
			bit_rw_t<io, bitpos::B7>   A15E;
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

			bit_rw_t<io, bitpos::B0>   A16E;
			bit_rw_t<io, bitpos::B1>   A17E;
			bit_rw_t<io, bitpos::B2>   A18E;
			bit_rw_t<io, bitpos::B3>   A19E;
		};
		static inline pfaoe1_t<0x0008'C105> PFAOE1;


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

			bit_rw_t<io, bitpos::B0>   ADRLE;

			bit_rw_t<io, bitpos::B4>   DHE;

			bit_rw_t<io, bitpos::B6>   WR1BC1E;
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
		};
		static inline pfbcr1_t<0x0008'C107> PFBCR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  USB0 制御レジスタ（PFUSB0）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfusb0_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B2>     PUPHZS;
			bit_rw_t<io, bitpos::B3>     PDHZS;
		};
		static inline pfusb0_t<0x0008'C114> PFUSB0;
	};
	typedef mpc_t MPC;
}
