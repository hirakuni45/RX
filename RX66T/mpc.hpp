#pragma once
//=========================================================================//
/*!	@file
	@brief	RX66T/RX72T グループ MPC 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
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
	template <class _>
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
		typedef pwpr_t<0x0008'C11F> PWPR_;
		static PWPR_ PWPR;


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
		typedef pfs_ip_t<0x0008'C140> P00PFS_;
		typedef pfs_ip_t<0x0008'C141> P01PFS_;
		static P00PFS_ P00PFS;
		static P01PFS_ P01PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P1n 端子機能制御レジスタ（P1nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfs_ip_t<0x0008'C148> P10PFS_;
		typedef pfs_ip_t<0x0008'C149> P11PFS_;
		typedef pfs_ip_t<0x0008'C14A> P12PFS_;
		typedef pfs_ip_t<0x0008'C14B> P13PFS_;
		typedef pfs_ip_t<0x0008'C14C> P14PFS_;
		typedef pfs_ip_t<0x0008'C14D> P15PFS_;
		typedef pfs_ip_t<0x0008'C14E> P16PFS_;
		typedef pfs_ip_t<0x0008'C14F> P17PFS_;
		static P10PFS_ P10PFS;
		static P11PFS_ P11PFS;
		static P12PFS_ P12PFS;
		static P13PFS_ P13PFS;
		static P14PFS_ P14PFS;
		static P15PFS_ P15PFS;
		static P16PFS_ P16PFS;
		static P17PFS_ P17PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P2n 端子機能制御レジスタ（P2nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfs_aip_t<0x0008'C150> P20PFS_;
		typedef pfs_aip_t<0x0008'C151> P21PFS_;
		typedef pfs_aip_t<0x0008'C152> P22PFS_;
		typedef pfs_aip_t<0x0008'C153> P23PFS_;
		typedef pfs_aip_t<0x0008'C154> P24PFS_;
		typedef pfs_aip_t<0x0008'C155> P25PFS_;
		typedef pfs_aip_t<0x0008'C156> P26PFS_;
		typedef pfs_aip_t<0x0008'C157> P27PFS_;
		static P20PFS_ P20PFS;
		static P21PFS_ P21PFS;
		static P22PFS_ P22PFS;
		static P23PFS_ P23PFS;
		static P24PFS_ P24PFS;
		static P25PFS_ P25PFS;
		static P26PFS_ P26PFS;
		static P27PFS_ P27PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P3n 端子機能制御レジスタ（P3nPFS）（n = 0 ～ 5）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfs_ip_t<0x0008'C158> P30PFS_;
		typedef pfs_ip_t<0x0008'C159> P31PFS_;
		typedef pfs_ip_t<0x0008'C15A> P32PFS_;
		typedef pfs_ip_t<0x0008'C15B> P33PFS_;
		typedef pfs_ip_t<0x0008'C15C> P34PFS_;
		typedef pfs_ip_t<0x0008'C15D> P35PFS_;
		static P30PFS_ P30PFS;
		static P31PFS_ P31PFS;
		static P32PFS_ P32PFS;
		static P33PFS_ P33PFS;
		static P34PFS_ P34PFS;
		static P35PFS_ P35PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P4n 端子機能制御レジスタ（P4nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfs_a_t<0x0008'C160> P40PFS_;
		typedef pfs_a_t<0x0008'C161> P41PFS_;
		typedef pfs_a_t<0x0008'C162> P42PFS_;
		typedef pfs_a_t<0x0008'C163> P43PFS_;
		typedef pfs_a_t<0x0008'C164> P44PFS_;
		typedef pfs_a_t<0x0008'C165> P45PFS_;
		typedef pfs_a_t<0x0008'C166> P46PFS_;
		typedef pfs_a_t<0x0008'C167> P47PFS_;
		static P40PFS_ P40PFS;
		static P41PFS_ P41PFS;
		static P42PFS_ P42PFS;
		static P43PFS_ P43PFS;
		static P44PFS_ P44PFS;
		static P45PFS_ P45PFS;
		static P46PFS_ P46PFS;
		static P47PFS_ P47PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P5n 端子機能制御レジスタ（P5nPFS）（n = 0 ～ 5）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfs_ai_t<0x0008'C168> P50PFS_;
		typedef pfs_ai_t<0x0008'C169> P51PFS_;
		typedef pfs_ai_t<0x0008'C16A> P52PFS_;
		typedef pfs_ai_t<0x0008'C16B> P53PFS_;
		typedef pfs_ai_t<0x0008'C16C> P54PFS_;
		typedef pfs_ai_t<0x0008'C16D> P55PFS_;
		static P50PFS_ P50PFS;
		static P51PFS_ P51PFS;
		static P52PFS_ P52PFS;
		static P53PFS_ P53PFS;
		static P54PFS_ P54PFS;
		static P55PFS_ P55PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P6n 端子機能制御レジスタ（P6nPFS）（n = 0 ～ 5）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfs_ai_t<0x0008'C170> P60PFS_;
		typedef pfs_ai_t<0x0008'C171> P61PFS_;
		typedef pfs_ai_t<0x0008'C172> P62PFS_;
		typedef pfs_ai_t<0x0008'C173> P63PFS_;
		typedef pfs_ai_t<0x0008'C174> P64PFS_;
		typedef pfs_ai_t<0x0008'C175> P65PFS_;
		static P60PFS_ P60PFS;
		static P61PFS_ P61PFS;
		static P62PFS_ P62PFS;
		static P63PFS_ P63PFS;
		static P64PFS_ P64PFS;
		static P65PFS_ P65PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P7n 端子機能制御レジスタ（P7nPFS）（n = 0 ～ 6）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfs_ip_t<0x0008'C178> P70PFS_;
		typedef pfs_ip_t<0x0008'C179> P71PFS_;
		typedef pfs_ip_t<0x0008'C17A> P72PFS_;
		typedef pfs_ip_t<0x0008'C17B> P73PFS_;
		typedef pfs_ip_t<0x0008'C17C> P74PFS_;
		typedef pfs_ip_t<0x0008'C17D> P75PFS_;
		typedef pfs_ip_t<0x0008'C17E> P76PFS_;
		static P70PFS_ P70PFS;
		static P71PFS_ P71PFS;
		static P72PFS_ P72PFS;
		static P73PFS_ P73PFS;
		static P74PFS_ P74PFS;
		static P75PFS_ P75PFS;
		static P76PFS_ P76PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P8n 端子機能制御レジスタ（P8nPFS）（n = 0 ～ 2）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfs_ip_t<0x0008'C180> P80PFS_;
		typedef pfs_ip_t<0x0008'C181> P81PFS_;
		typedef pfs_ip_t<0x0008'C182> P82PFS_;
		static P80PFS_ P80PFS;
		static P81PFS_ P81PFS;
		static P82PFS_ P82PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P9n 端子機能制御レジスタ（P9nPFS）（n = 0 ～ 6）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfs_ip_t<0x0008'C188> P90PFS_;
		typedef pfs_ip_t<0x0008'C189> P91PFS_;
		typedef pfs_ip_t<0x0008'C18A> P92PFS_;
		typedef pfs_ip_t<0x0008'C18B> P93PFS_;
		typedef pfs_ip_t<0x0008'C18C> P94PFS_;
		typedef pfs_ip_t<0x0008'C18D> P95PFS_;
		typedef pfs_ip_t<0x0008'C18E> P96PFS_;
		static P90PFS_ P90PFS;
		static P91PFS_ P91PFS;
		static P92PFS_ P92PFS;
		static P93PFS_ P93PFS;
		static P94PFS_ P94PFS;
		static P95PFS_ P95PFS;
		static P96PFS_ P96PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PAn 端子機能制御レジスタ（PAnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfs_ip_t<0x0008'C190> PA0PFS_;
		typedef pfs_ip_t<0x0008'C191> PA1PFS_;
		typedef pfs_ip_t<0x0008'C192> PA2PFS_;
		typedef pfs_ip_t<0x0008'C193> PA3PFS_;
		typedef pfs_ip_t<0x0008'C194> PA4PFS_;
		typedef pfs_ip_t<0x0008'C195> PA5PFS_;
		typedef pfs_ip_t<0x0008'C196> PA6PFS_;
		typedef pfs_ip_t<0x0008'C197> PA7PFS_;
		static PA0PFS_ PA0PFS;
		static PA1PFS_ PA1PFS;
		static PA2PFS_ PA2PFS;
		static PA3PFS_ PA3PFS;
		static PA4PFS_ PA4PFS;
		static PA5PFS_ PA5PFS;
		static PA6PFS_ PA6PFS;
		static PA7PFS_ PA7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PBn 端子機能制御レジスタ（PBnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfs_ip_t<0x0008'C198> PB0PFS_;
		typedef pfs_ip_t<0x0008'C199> PB1PFS_;
		typedef pfs_ip_t<0x0008'C19A> PB2PFS_;
		typedef pfs_ip_t<0x0008'C19B> PB3PFS_;
		typedef pfs_ip_t<0x0008'C19C> PB4PFS_;
		typedef pfs_ip_t<0x0008'C19D> PB5PFS_;
		typedef pfs_ip_t<0x0008'C19E> PB6PFS_;
		typedef pfs_ip_t<0x0008'C19F> PB7PFS_;
		static PB0PFS_ PB0PFS;
		static PB1PFS_ PB1PFS;
		static PB2PFS_ PB2PFS;
		static PB3PFS_ PB3PFS;
		static PB4PFS_ PB4PFS;
		static PB5PFS_ PB5PFS;
		static PB6PFS_ PB6PFS;
		static PB7PFS_ PB7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PCn 端子機能制御レジスタ（PCnPFS）（n = 0 ～ 6）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfs_ip_t<0x0008'C1A0> PC0PFS_;
		typedef pfs_ip_t<0x0008'C1A1> PC1PFS_;
		typedef pfs_ip_t<0x0008'C1A2> PC2PFS_;
		typedef pfs_ip_t<0x0008'C1A3> PC3PFS_;
		typedef pfs_ip_t<0x0008'C1A4> PC4PFS_;
		typedef pfs_ip_t<0x0008'C1A5> PC5PFS_;
		typedef pfs_ip_t<0x0008'C1A6> PC6PFS_;
		static PC0PFS_ PC0PFS;
		static PC1PFS_ PC1PFS;
		static PC2PFS_ PC2PFS;
		static PC3PFS_ PC3PFS;
		static PC4PFS_ PC4PFS;
		static PC5PFS_ PC5PFS;
		static PC6PFS_ PC6PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PDn 端子機能制御レジスタ（PDnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfs_ip_t<0x0008'C1A8> PD0PFS_;
		typedef pfs_ip_t<0x0008'C1A9> PD1PFS_;
		typedef pfs_ip_t<0x0008'C1AA> PD2PFS_;
		typedef pfs_ip_t<0x0008'C1AB> PD3PFS_;
		typedef pfs_ip_t<0x0008'C1AC> PD4PFS_;
		typedef pfs_ip_t<0x0008'C1AD> PD5PFS_;
		typedef pfs_ip_t<0x0008'C1AE> PD6PFS_;
		typedef pfs_ip_t<0x0008'C1AF> PD7PFS_;
		static PD0PFS_ PD0PFS;
		static PD1PFS_ PD1PFS;
		static PD2PFS_ PD2PFS;
		static PD3PFS_ PD3PFS;
		static PD4PFS_ PD4PFS;
		static PD5PFS_ PD5PFS;
		static PD6PFS_ PD6PFS;
		static PD7PFS_ PD7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PEn 端子機能制御レジスタ（PEnPFS）（n = 0 ～ 6）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfs_ip_t<0x0008'C1B0> PE0PFS_;
		typedef pfs_ip_t<0x0008'C1B1> PE1PFS_;
		typedef pfs_ip_t<0x0008'C1B2> PE2PFS_;
		typedef pfs_ip_t<0x0008'C1B3> PE3PFS_;
		typedef pfs_ip_t<0x0008'C1B4> PE4PFS_;
		typedef pfs_ip_t<0x0008'C1B5> PE5PFS_;
		typedef pfs_ip_t<0x0008'C1B6> PE6PFS_;
		static PE0PFS_ PE0PFS;
		static PE1PFS_ PE1PFS;
		static PE2PFS_ PE2PFS;
		static PE3PFS_ PE3PFS;
		static PE4PFS_ PE4PFS;
		static PE5PFS_ PE5PFS;
		static PE6PFS_ PE6PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PFn 端子機能制御レジスタ（PFnPFS）（n = 0 ～ 3）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfs_ip_t<0x0008'C1B8> PF0PFS_;
		typedef pfs_ip_t<0x0008'C1B9> PF1PFS_;
		typedef pfs_ip_t<0x0008'C1BA> PF2PFS_;
		typedef pfs_ip_t<0x0008'C1BB> PF3PFS_;
		static PF0PFS_ PF0PFS;
		static PF1PFS_ PF1PFS;
		static PF2PFS_ PF2PFS;
		static PF3PFS_ PF3PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PGn 端子機能制御レジスタ（PGnPFS）（n = 0 ～ 2）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfs_ip_t<0x0008'C1C0> PG0PFS_;
		typedef pfs_ip_t<0x0008'C1C1> PG1PFS_;
		typedef pfs_ip_t<0x0008'C1C2> PG2PFS_;
		static PG0PFS_ PG0PFS;
		static PG1PFS_ PG1PFS;
		static PG2PFS_ PG2PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PHn 端子機能制御レジスタ（PHnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfs_a_t<0x0008'C1C8> PH0PFS_;
		typedef pfs_a_t<0x0008'C1C9> PH1PFS_;
		typedef pfs_a_t<0x0008'C1CA> PH2PFS_;
		typedef pfs_a_t<0x0008'C1CB> PH3PFS_;
		typedef pfs_a_t<0x0008'C1CC> PH4PFS_;
		typedef pfs_a_t<0x0008'C1CD> PH5PFS_;
		typedef pfs_a_t<0x0008'C1CE> PH6PFS_;
		typedef pfs_a_t<0x0008'C1CF> PH7PFS_;
		static PH0PFS_ PH0PFS;
		static PH1PFS_ PH1PFS;
		static PH2PFS_ PH2PFS;
		static PH3PFS_ PH3PFS;
		static PH4PFS_ PH4PFS;
		static PH5PFS_ PH5PFS;
		static PH6PFS_ PH6PFS;
		static PH7PFS_ PH7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PKn 端子機能制御レジスタ（PKnPFS）（n = 0 ～ 2）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfs_ip_t<0x0008'C1D8> PK0PFS_;
		typedef pfs_ip_t<0x0008'C1D9> PK1PFS_;
		typedef pfs_ip_t<0x0008'C1DA> PK2PFS_;
		static PK0PFS_ PK0PFS;
		static PK1PFS_ PK1PFS;
		static PK2PFS_ PK2PFS;


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
		typedef pfcse_t<0x0008'C100> PFCSE_;
		static PFCSE_ PFCSE;


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
		typedef pfcss0_t<0x0008'C102> PFCSS0_;
		static PFCSS0_ PFCSS0;


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
		typedef pfaoe0_t<0x0008'C104> PFAOE0_;
		static PFAOE0_ PFAOE0;


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
		typedef pfaoe1_t<0x0008'C105> PFAOE1_;
		static PFAOE1_ PFAOE1;


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
		typedef pfbcr0_t<0x0008'C106> PFBCR0_;
		static PFBCR0_ PFBCR0;


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
		typedef pfbcr1_t<0x0008'C107> PFBCR1_;
		static PFBCR1_ PFBCR1;


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
		typedef pfbcr2_t<0x0008'C108> PFBCR2_;
		static PFBCR2_ PFBCR2;


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
		typedef pfbcr3_t<0x0008'C109> PFBCR3_;
		static PFBCR3_ PFBCR3;


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
		typedef pfbcr4_t<0x0008'C10A> PFBCR4_;
		static PFBCR4_ PFBCR4;
	};
	template<class _> typename mpc_t<_>::PWPR_ mpc_t<_>::PWPR;
	template<class _> typename mpc_t<_>::P00PFS_ mpc_t<_>::P00PFS;
	template<class _> typename mpc_t<_>::P01PFS_ mpc_t<_>::P01PFS;
	template<class _> typename mpc_t<_>::P10PFS_ mpc_t<_>::P10PFS;
	template<class _> typename mpc_t<_>::P11PFS_ mpc_t<_>::P11PFS;
	template<class _> typename mpc_t<_>::P12PFS_ mpc_t<_>::P12PFS;
	template<class _> typename mpc_t<_>::P13PFS_ mpc_t<_>::P13PFS;
	template<class _> typename mpc_t<_>::P14PFS_ mpc_t<_>::P14PFS;
	template<class _> typename mpc_t<_>::P15PFS_ mpc_t<_>::P15PFS;
	template<class _> typename mpc_t<_>::P16PFS_ mpc_t<_>::P16PFS;
	template<class _> typename mpc_t<_>::P17PFS_ mpc_t<_>::P17PFS;
	template<class _> typename mpc_t<_>::P20PFS_ mpc_t<_>::P20PFS;
	template<class _> typename mpc_t<_>::P21PFS_ mpc_t<_>::P21PFS;
	template<class _> typename mpc_t<_>::P22PFS_ mpc_t<_>::P22PFS;
	template<class _> typename mpc_t<_>::P23PFS_ mpc_t<_>::P23PFS;
	template<class _> typename mpc_t<_>::P24PFS_ mpc_t<_>::P24PFS;
	template<class _> typename mpc_t<_>::P25PFS_ mpc_t<_>::P25PFS;
	template<class _> typename mpc_t<_>::P26PFS_ mpc_t<_>::P26PFS;
	template<class _> typename mpc_t<_>::P27PFS_ mpc_t<_>::P27PFS;
	template<class _> typename mpc_t<_>::P30PFS_ mpc_t<_>::P30PFS;
	template<class _> typename mpc_t<_>::P31PFS_ mpc_t<_>::P31PFS;
	template<class _> typename mpc_t<_>::P32PFS_ mpc_t<_>::P32PFS;
	template<class _> typename mpc_t<_>::P33PFS_ mpc_t<_>::P33PFS;
	template<class _> typename mpc_t<_>::P34PFS_ mpc_t<_>::P34PFS;
	template<class _> typename mpc_t<_>::P35PFS_ mpc_t<_>::P35PFS;
	template<class _> typename mpc_t<_>::P40PFS_ mpc_t<_>::P40PFS;
	template<class _> typename mpc_t<_>::P41PFS_ mpc_t<_>::P41PFS;
	template<class _> typename mpc_t<_>::P42PFS_ mpc_t<_>::P42PFS;
	template<class _> typename mpc_t<_>::P43PFS_ mpc_t<_>::P43PFS;
	template<class _> typename mpc_t<_>::P44PFS_ mpc_t<_>::P44PFS;
	template<class _> typename mpc_t<_>::P45PFS_ mpc_t<_>::P45PFS;
	template<class _> typename mpc_t<_>::P46PFS_ mpc_t<_>::P46PFS;
	template<class _> typename mpc_t<_>::P47PFS_ mpc_t<_>::P47PFS;
	template<class _> typename mpc_t<_>::P50PFS_ mpc_t<_>::P50PFS;
	template<class _> typename mpc_t<_>::P51PFS_ mpc_t<_>::P51PFS;
	template<class _> typename mpc_t<_>::P52PFS_ mpc_t<_>::P52PFS;
	template<class _> typename mpc_t<_>::P53PFS_ mpc_t<_>::P53PFS;
	template<class _> typename mpc_t<_>::P54PFS_ mpc_t<_>::P54PFS;
	template<class _> typename mpc_t<_>::P55PFS_ mpc_t<_>::P55PFS;
	template<class _> typename mpc_t<_>::P60PFS_ mpc_t<_>::P60PFS;
	template<class _> typename mpc_t<_>::P61PFS_ mpc_t<_>::P61PFS;
	template<class _> typename mpc_t<_>::P62PFS_ mpc_t<_>::P62PFS;
	template<class _> typename mpc_t<_>::P63PFS_ mpc_t<_>::P63PFS;
	template<class _> typename mpc_t<_>::P64PFS_ mpc_t<_>::P64PFS;
	template<class _> typename mpc_t<_>::P65PFS_ mpc_t<_>::P65PFS;
	template<class _> typename mpc_t<_>::P70PFS_ mpc_t<_>::P70PFS;
	template<class _> typename mpc_t<_>::P71PFS_ mpc_t<_>::P71PFS;
	template<class _> typename mpc_t<_>::P72PFS_ mpc_t<_>::P72PFS;
	template<class _> typename mpc_t<_>::P73PFS_ mpc_t<_>::P73PFS;
	template<class _> typename mpc_t<_>::P74PFS_ mpc_t<_>::P74PFS;
	template<class _> typename mpc_t<_>::P75PFS_ mpc_t<_>::P75PFS;
	template<class _> typename mpc_t<_>::P76PFS_ mpc_t<_>::P76PFS;
	template<class _> typename mpc_t<_>::P80PFS_ mpc_t<_>::P80PFS;
	template<class _> typename mpc_t<_>::P81PFS_ mpc_t<_>::P81PFS;
	template<class _> typename mpc_t<_>::P82PFS_ mpc_t<_>::P82PFS;
	template<class _> typename mpc_t<_>::P90PFS_ mpc_t<_>::P90PFS;
	template<class _> typename mpc_t<_>::P91PFS_ mpc_t<_>::P91PFS;
	template<class _> typename mpc_t<_>::P92PFS_ mpc_t<_>::P92PFS;
	template<class _> typename mpc_t<_>::P93PFS_ mpc_t<_>::P93PFS;
	template<class _> typename mpc_t<_>::P94PFS_ mpc_t<_>::P94PFS;
	template<class _> typename mpc_t<_>::P95PFS_ mpc_t<_>::P95PFS;
	template<class _> typename mpc_t<_>::P96PFS_ mpc_t<_>::P96PFS;
	template<class _> typename mpc_t<_>::PA0PFS_ mpc_t<_>::PA0PFS;
	template<class _> typename mpc_t<_>::PA1PFS_ mpc_t<_>::PA1PFS;
	template<class _> typename mpc_t<_>::PA2PFS_ mpc_t<_>::PA2PFS;
	template<class _> typename mpc_t<_>::PA3PFS_ mpc_t<_>::PA3PFS;
	template<class _> typename mpc_t<_>::PA4PFS_ mpc_t<_>::PA4PFS;
	template<class _> typename mpc_t<_>::PA5PFS_ mpc_t<_>::PA5PFS;
	template<class _> typename mpc_t<_>::PA6PFS_ mpc_t<_>::PA6PFS;
	template<class _> typename mpc_t<_>::PA7PFS_ mpc_t<_>::PA7PFS;
	template<class _> typename mpc_t<_>::PB0PFS_ mpc_t<_>::PB0PFS;
	template<class _> typename mpc_t<_>::PB1PFS_ mpc_t<_>::PB1PFS;
	template<class _> typename mpc_t<_>::PB2PFS_ mpc_t<_>::PB2PFS;
	template<class _> typename mpc_t<_>::PB3PFS_ mpc_t<_>::PB3PFS;
	template<class _> typename mpc_t<_>::PB4PFS_ mpc_t<_>::PB4PFS;
	template<class _> typename mpc_t<_>::PB5PFS_ mpc_t<_>::PB5PFS;
	template<class _> typename mpc_t<_>::PB6PFS_ mpc_t<_>::PB6PFS;
	template<class _> typename mpc_t<_>::PB7PFS_ mpc_t<_>::PB7PFS;
	template<class _> typename mpc_t<_>::PC0PFS_ mpc_t<_>::PC0PFS;
	template<class _> typename mpc_t<_>::PC1PFS_ mpc_t<_>::PC1PFS;
	template<class _> typename mpc_t<_>::PC2PFS_ mpc_t<_>::PC2PFS;
	template<class _> typename mpc_t<_>::PC3PFS_ mpc_t<_>::PC3PFS;
	template<class _> typename mpc_t<_>::PC4PFS_ mpc_t<_>::PC4PFS;
	template<class _> typename mpc_t<_>::PC5PFS_ mpc_t<_>::PC5PFS;
	template<class _> typename mpc_t<_>::PC6PFS_ mpc_t<_>::PC6PFS;
	template<class _> typename mpc_t<_>::PD0PFS_ mpc_t<_>::PD0PFS;
	template<class _> typename mpc_t<_>::PD1PFS_ mpc_t<_>::PD1PFS;
	template<class _> typename mpc_t<_>::PD2PFS_ mpc_t<_>::PD2PFS;
	template<class _> typename mpc_t<_>::PD3PFS_ mpc_t<_>::PD3PFS;
	template<class _> typename mpc_t<_>::PD4PFS_ mpc_t<_>::PD4PFS;
	template<class _> typename mpc_t<_>::PD5PFS_ mpc_t<_>::PD5PFS;
	template<class _> typename mpc_t<_>::PD6PFS_ mpc_t<_>::PD6PFS;
	template<class _> typename mpc_t<_>::PD7PFS_ mpc_t<_>::PD7PFS;
	template<class _> typename mpc_t<_>::PE0PFS_ mpc_t<_>::PE0PFS;
	template<class _> typename mpc_t<_>::PE1PFS_ mpc_t<_>::PE1PFS;
	template<class _> typename mpc_t<_>::PE2PFS_ mpc_t<_>::PE2PFS;
	template<class _> typename mpc_t<_>::PE3PFS_ mpc_t<_>::PE3PFS;
	template<class _> typename mpc_t<_>::PE4PFS_ mpc_t<_>::PE4PFS;
	template<class _> typename mpc_t<_>::PE5PFS_ mpc_t<_>::PE5PFS;
	template<class _> typename mpc_t<_>::PE6PFS_ mpc_t<_>::PE6PFS;
	template<class _> typename mpc_t<_>::PF0PFS_ mpc_t<_>::PF0PFS;
	template<class _> typename mpc_t<_>::PF1PFS_ mpc_t<_>::PF1PFS;
	template<class _> typename mpc_t<_>::PF2PFS_ mpc_t<_>::PF2PFS;
	template<class _> typename mpc_t<_>::PF3PFS_ mpc_t<_>::PF3PFS;
	template<class _> typename mpc_t<_>::PG0PFS_ mpc_t<_>::PG0PFS;
	template<class _> typename mpc_t<_>::PG1PFS_ mpc_t<_>::PG1PFS;
	template<class _> typename mpc_t<_>::PG2PFS_ mpc_t<_>::PG2PFS;
	template<class _> typename mpc_t<_>::PH0PFS_ mpc_t<_>::PH0PFS;
	template<class _> typename mpc_t<_>::PH1PFS_ mpc_t<_>::PH1PFS;
	template<class _> typename mpc_t<_>::PH2PFS_ mpc_t<_>::PH2PFS;
	template<class _> typename mpc_t<_>::PH3PFS_ mpc_t<_>::PH3PFS;
	template<class _> typename mpc_t<_>::PH4PFS_ mpc_t<_>::PH4PFS;
	template<class _> typename mpc_t<_>::PH5PFS_ mpc_t<_>::PH5PFS;
	template<class _> typename mpc_t<_>::PH6PFS_ mpc_t<_>::PH6PFS;
	template<class _> typename mpc_t<_>::PH7PFS_ mpc_t<_>::PH7PFS;
	template<class _> typename mpc_t<_>::PK0PFS_ mpc_t<_>::PK0PFS;
	template<class _> typename mpc_t<_>::PK1PFS_ mpc_t<_>::PK1PFS;
	template<class _> typename mpc_t<_>::PK2PFS_ mpc_t<_>::PK2PFS;
	template<class _> typename mpc_t<_>::PFCSE_ mpc_t<_>::PFCSE;
	template<class _> typename mpc_t<_>::PFCSS0_ mpc_t<_>::PFCSS0;
	template<class _> typename mpc_t<_>::PFAOE0_ mpc_t<_>::PFAOE0;
	template<class _> typename mpc_t<_>::PFAOE1_ mpc_t<_>::PFAOE1;
	template<class _> typename mpc_t<_>::PFBCR0_ mpc_t<_>::PFBCR0;
	template<class _> typename mpc_t<_>::PFBCR1_ mpc_t<_>::PFBCR1;
	template<class _> typename mpc_t<_>::PFBCR2_ mpc_t<_>::PFBCR2;
	template<class _> typename mpc_t<_>::PFBCR3_ mpc_t<_>::PFBCR3;
	template<class _> typename mpc_t<_>::PFBCR4_ mpc_t<_>::PFBCR4;

	typedef mpc_t<void> MPC;
}
