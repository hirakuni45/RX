#pragma once
//=========================================================================//
/*!	@file
	@brief	RX66T/RX72T グループ MPC 定義
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
		@brief  マルチファンクションピンコントローラークラス
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
			@brief  端子機能制御規定クラス IP
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfs_ip_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bits_rw_t<io, bitpos::B0, 6>  PSEL;
			bit_rw_t< io, bitpos::B6>     ISEL;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  端子機能制御規定クラス AIP
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfs_aip_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bits_rw_t<io, bitpos::B0, 6>  PSEL;
			bit_rw_t<io, bitpos::B6>      ISEL;
			bit_rw_t<io, bitpos::B6>      ASEL;
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
			@brief  端子機能制御規定クラス AI
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfs_ai_t : public rw8_t<base> {
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
			@brief  端子機能制御規定クラス P
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfs_p_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bits_rw_t<io, bitpos::B0, 6>  PSEL;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P0n 端子機能制御レジスタ（P0nPFS）（n = 0, 1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ip_t<0x0008'C140> P00PFS;
		static inline pfs_ip_t<0x0008'C141> P01PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P1n 端子機能制御レジスタ（P1nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ip_t<0x0008'C148> P10PFS;
		static inline pfs_ip_t<0x0008'C149> P11PFS;
		static inline pfs_ip_t<0x0008'C14A> P12PFS;
		static inline pfs_ip_t<0x0008'C14B> P13PFS;
		static inline pfs_ip_t<0x0008'C14C> P14PFS;
		static inline pfs_ip_t<0x0008'C14D> P15PFS;
		static inline pfs_ip_t<0x0008'C14E> P16PFS;
		static inline pfs_ip_t<0x0008'C14F> P17PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P2n 端子機能制御レジスタ（P2nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_aip_t<0x0008'C150> P20PFS;
		static inline pfs_aip_t<0x0008'C151> P21PFS;
		static inline pfs_aip_t<0x0008'C152> P22PFS;
		static inline pfs_aip_t<0x0008'C153> P23PFS;
		static inline pfs_aip_t<0x0008'C154> P24PFS;
		static inline pfs_aip_t<0x0008'C155> P25PFS;
		static inline pfs_aip_t<0x0008'C156> P26PFS;
		static inline pfs_aip_t<0x0008'C157> P27PFS;


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
			@brief  P5n 端子機能制御レジスタ（P5nPFS）（n = 0 ～ 5）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ai_t<0x0008'C168> P50PFS;
		static inline pfs_ai_t<0x0008'C169> P51PFS;
		static inline pfs_ai_t<0x0008'C16A> P52PFS;
		static inline pfs_ai_t<0x0008'C16B> P53PFS;
		static inline pfs_ai_t<0x0008'C16C> P54PFS;
		static inline pfs_ai_t<0x0008'C16D> P55PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P6n 端子機能制御レジスタ（P6nPFS）（n = 0 ～ 5）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ai_t<0x0008'C170> P60PFS;
		static inline pfs_ai_t<0x0008'C171> P61PFS;
		static inline pfs_ai_t<0x0008'C172> P62PFS;
		static inline pfs_ai_t<0x0008'C173> P63PFS;
		static inline pfs_ai_t<0x0008'C174> P64PFS;
		static inline pfs_ai_t<0x0008'C175> P65PFS;


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
			@brief  PAn 端子機能制御レジスタ（PAnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ip_t<0x0008'C190> PA0PFS;
		static inline pfs_ip_t<0x0008'C191> PA1PFS;
		static inline pfs_ip_t<0x0008'C192> PA2PFS;
		static inline pfs_ip_t<0x0008'C193> PA3PFS;
		static inline pfs_ip_t<0x0008'C194> PA4PFS;
		static inline pfs_ip_t<0x0008'C195> PA5PFS;
		static inline pfs_ip_t<0x0008'C196> PA6PFS;
		static inline pfs_ip_t<0x0008'C197> PA7PFS;


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
			@brief  PCn 端子機能制御レジスタ（PCnPFS）（n = 0 ～ 6）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ip_t<0x0008'C1A0> PC0PFS;
		static inline pfs_ip_t<0x0008'C1A1> PC1PFS;
		static inline pfs_ip_t<0x0008'C1A2> PC2PFS;
		static inline pfs_ip_t<0x0008'C1A3> PC3PFS;
		static inline pfs_ip_t<0x0008'C1A4> PC4PFS;
		static inline pfs_ip_t<0x0008'C1A5> PC5PFS;
		static inline pfs_ip_t<0x0008'C1A6> PC6PFS;


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
			@brief  PEn 端子機能制御レジスタ（PEnPFS）（n = 0 ～ 6）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ip_t<0x0008'C1B0> PE0PFS;
		static inline pfs_ip_t<0x0008'C1B1> PE1PFS;
		static inline pfs_ip_t<0x0008'C1B2> PE2PFS;
		static inline pfs_ip_t<0x0008'C1B3> PE3PFS;
		static inline pfs_ip_t<0x0008'C1B4> PE4PFS;
		static inline pfs_ip_t<0x0008'C1B5> PE5PFS;
		static inline pfs_ip_t<0x0008'C1B6> PE6PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PFn 端子機能制御レジスタ（PFnPFS）（n = 0 ～ 3）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ip_t<0x0008'C1B8> PF0PFS;
		static inline pfs_ip_t<0x0008'C1B9> PF1PFS;
		static inline pfs_ip_t<0x0008'C1BA> PF2PFS;
		static inline pfs_ip_t<0x0008'C1BB> PF3PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PGn 端子機能制御レジスタ（PGnPFS）（n = 0 ～ 2）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ip_t<0x0008'C1C0> PG0PFS;
		static inline pfs_ip_t<0x0008'C1C1> PG1PFS;
		static inline pfs_ip_t<0x0008'C1C2> PG2PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PHn 端子機能制御レジスタ（PHnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_a_t<0x0008'C1C8> PH0PFS;
		static inline pfs_a_t<0x0008'C1C9> PH1PFS;
		static inline pfs_a_t<0x0008'C1CA> PH2PFS;
		static inline pfs_a_t<0x0008'C1CB> PH3PFS;
		static inline pfs_a_t<0x0008'C1CC> PH4PFS;
		static inline pfs_a_t<0x0008'C1CD> PH5PFS;
		static inline pfs_a_t<0x0008'C1CE> PH6PFS;
		static inline pfs_a_t<0x0008'C1CF> PH7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PKn 端子機能制御レジスタ（PKnPFS）（n = 0 ～ 2）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ip_t<0x0008'C1D8> PK0PFS;
		static inline pfs_ip_t<0x0008'C1D9> PK1PFS;
		static inline pfs_ip_t<0x0008'C1DA> PK2PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CS 出力許可レジスタ (PFCSE)
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

			bit_rw_t <io, bitpos::B0>     CS0S;

			bits_rw_t<io, bitpos::B2, 2>  CS1S;
			bits_rw_t<io, bitpos::B4, 2>  CS2S;
			bit_rw_t <io, bitpos::B6>     CS3S;
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
			bit_rw_t<io, bitpos::B4>   A20E;
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
			bit_rw_t<io, bitpos::B1>   ADRHMS;

			bit_rw_t<io, bitpos::B3>   BCLKO;
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

			bit_rw_t <io, bitpos::B2>     DHS;

			bits_rw_t<io, bitpos::B4, 2>  A0S;
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

			bit_rw_t <io, bitpos::B0>     RDS;
		};
		static inline pfbcr3_t<0x0008'C109> PFBCR3;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  外部バス制御レジスタ 4（PFBCR4）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfbcr4_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t <io, bitpos::B3>     CS3S2;
			bits_rw_t<io, bitpos::B4, 2>  ADRLMS;

			bit_rw_t <io, bitpos::B6>     ADRHMS2;
		};
		static inline pfbcr4_t<0x0008'C10A> PFBCR4;
	};
	typedef mpc_t MPC;
}
