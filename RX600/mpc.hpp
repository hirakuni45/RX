#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ MPC 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2013, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  マルチファンクションピンコントローラークラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class _>
	struct mpc_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  書き込みプロテクトレジスタ (PWPR)
			@param[in]	base	アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		typedef pwpr_t<0x0008C11F> PWPR_;
		static PWPR_ PWPR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  端子機能制御規定クラス W
			@param[in]	base	アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfsw_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>  PSEL;
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
			bit_rw_t <io, bitpos::B6>     ISEL;
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
		typedef pfsx_t<0x0008C140> P00PFS_;
		typedef pfsx_t<0x0008C141> P01PFS_;
		typedef pfsx_t<0x0008C142> P02PFS_;
		typedef pfsx_t<0x0008C143> P03PFS_;
		typedef pfsx_t<0x0008C145> P05PFS_;
		typedef pfsx_t<0x0008C147> P07PFS_;
		static P00PFS_ P00PFS;
		static P01PFS_ P01PFS;
		static P02PFS_ P02PFS;
		static P03PFS_ P03PFS;
		static P05PFS_ P05PFS;
		static P07PFS_ P07PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P1n 端子機能制御レジスタ（P1nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsy_t<0x0008C148> P10PFS_;
		typedef pfsy_t<0x0008C149> P11PFS_;
		typedef pfsy_t<0x0008C14A> P12PFS_;
		typedef pfsy_t<0x0008C14B> P13PFS_;
		typedef pfsy_t<0x0008C14C> P14PFS_;
		typedef pfsy_t<0x0008C14D> P15PFS_;
		typedef pfsy_t<0x0008C14E> P16PFS_;
		typedef pfsy_t<0x0008C14F> P17PFS_;
		static P10PFS_ P10PFS;
		static P11PFS_ P11PFS;
		static P12PFS_ P12PFS;
		static P13PFS_ P13PFS;
		static P14PFS_ P14PFS;
		static P15PFS_ P15PFS;
		static P16PFS_ P16PFS;
		static P17PFS_ P17PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P2n 端子機能制御レジスタ（P2nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsy_t<0x0008C150> P20PFS_;
		typedef pfsy_t<0x0008C151> P21PFS_;
		typedef pfsy_t<0x0008C152> P22PFS_;
		typedef pfsy_t<0x0008C153> P23PFS_;
		typedef pfsy_t<0x0008C154> P24PFS_;
		typedef pfsy_t<0x0008C155> P25PFS_;
		typedef pfsy_t<0x0008C156> P26PFS_;
		typedef pfsy_t<0x0008C157> P27PFS_;
		static P20PFS_ P20PFS;
		static P21PFS_ P21PFS;
		static P22PFS_ P22PFS;
		static P23PFS_ P23PFS;
		static P24PFS_ P24PFS;
		static P25PFS_ P25PFS;
		static P26PFS_ P26PFS;
		static P27PFS_ P27PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P3n 端子機能制御レジスタ（P3nPFS）（n = 0 ～ 4）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsy_t<0x0008C158> P30PFS_;
		typedef pfsy_t<0x0008C159> P31PFS_;
		typedef pfsy_t<0x0008C15A> P32PFS_;
		typedef pfsy_t<0x0008C15B> P33PFS_;
		typedef pfsy_t<0x0008C15C> P34PFS_;
		static P30PFS_ P30PFS;
		static P31PFS_ P31PFS;
		static P32PFS_ P32PFS;
		static P33PFS_ P33PFS;
		static P34PFS_ P34PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P4n 端子機能制御レジスタ（P4nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsz_t<0x0008C160> P40PFS_;
		typedef pfsz_t<0x0008C161> P41PFS_;
		typedef pfsz_t<0x0008C162> P42PFS_;
		typedef pfsz_t<0x0008C163> P43PFS_;
		typedef pfsz_t<0x0008C164> P44PFS_;
		typedef pfsz_t<0x0008C165> P45PFS_;
		typedef pfsz_t<0x0008C166> P46PFS_;
		typedef pfsz_t<0x0008C167> P47PFS_;
		static P40PFS_ P40PFS;
		static P41PFS_ P41PFS;
		static P42PFS_ P42PFS;
		static P43PFS_ P43PFS;
		static P44PFS_ P44PFS;
		static P45PFS_ P45PFS;
		static P46PFS_ P46PFS;
		static P47PFS_ P47PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P5n 端子機能制御レジスタ（P5nPFS）（n = 0 ～ 2, 4 ～ 6）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsy_t<0x0008C168> P50PFS_;
		typedef pfsy_t<0x0008C169> P51PFS_;
		typedef pfsy_t<0x0008C16A> P52PFS_;
		typedef pfsy_t<0x0008C16C> P54PFS_;
		typedef pfsy_t<0x0008C16D> P55PFS_;
		typedef pfsy_t<0x0008C16E> P56PFS_;
		typedef pfsy_t<0x0008C16F> P57PFS_;
		static P50PFS_ P50PFS;
		static P51PFS_ P51PFS;
		static P52PFS_ P52PFS;
		static P54PFS_ P54PFS;
		static P55PFS_ P55PFS;
		static P56PFS_ P56PFS;
		static P57PFS_ P57PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P6n 端子機能制御レジスタ（P6nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72N)
		typedef pfsy_t<0x0008C170> P60PFS_;
		static P60PFS_ P60PFS;
#if defined(SIG_RX72N)
		typedef pfsy_t<0x0008C171> P61PFS_;
		typedef pfsy_t<0x0008C172> P62PFS_;
		typedef pfsy_t<0x0008C173> P63PFS_;
		typedef pfsy_t<0x0008C174> P64PFS_;
		static P61PFS_ P61PFS;
		static P62PFS_ P62PFS;
		static P63PFS_ P63PFS;
		static P64PFS_ P64PFS;
#endif
		typedef pfsy_t<0x0008C176> P66PFS_;
		typedef pfsy_t<0x0008C177> P67PFS_;
		static P66PFS_ P66PFS;
		static P67PFS_ P67PFS;

#elif defined(SIG_RX66T)
		typedef pfsz_t<0x0008C170> P60PFS_;
		typedef pfsz_t<0x0008C171> P61PFS_;
		typedef pfsz_t<0x0008C172> P62PFS_;
		typedef pfsz_t<0x0008C173> P63PFS_;
		typedef pfsz_t<0x0008C174> P64PFS_;
		typedef pfsz_t<0x0008C175> P65PFS_;
		static P60PFS_ P60PFS;
		static P61PFS_ P61PFS;
		static P62PFS_ P62PFS;
		static P63PFS_ P63PFS;
		static P64PFS_ P64PFS;
		static P65PFS_ P65PFS;
#endif

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P7n 端子機能制御レジスタ（P7nPFS）（n = 1 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsw_t<0x0008C179> P71PFS_;
		typedef pfsw_t<0x0008C17A> P72PFS_;
		typedef pfsw_t<0x0008C17B> P73PFS_;
		typedef pfsw_t<0x0008C17C> P74PFS_;
		typedef pfsw_t<0x0008C17D> P75PFS_;
		typedef pfsw_t<0x0008C17E> P76PFS_;
		typedef pfsw_t<0x0008C17F> P77PFS_;
		static P71PFS_ P71PFS;
		static P72PFS_ P72PFS;
		static P73PFS_ P73PFS;
		static P74PFS_ P74PFS;
		static P75PFS_ P75PFS;
		static P76PFS_ P76PFS;
		static P77PFS_ P77PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P8n 端子機能制御レジスタ（P8nPFS）（n = 0 ～ 3, 6, 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsw_t<0x0008C180> P80PFS_;
		typedef pfsw_t<0x0008C181> P81PFS_;
		typedef pfsw_t<0x0008C182> P82PFS_;
		typedef pfsw_t<0x0008C183> P83PFS_;
		typedef pfsw_t<0x0008C184> P84PFS_;
		typedef pfsw_t<0x0008C185> P85PFS_;
		typedef pfsw_t<0x0008C186> P86PFS_;
		typedef pfsw_t<0x0008C187> P87PFS_;
		static P80PFS_ P80PFS;
		static P81PFS_ P81PFS;
		static P82PFS_ P82PFS;
		static P83PFS_ P83PFS;
		static P84PFS_ P84PFS;
		static P85PFS_ P85PFS;
		static P86PFS_ P86PFS;
		static P87PFS_ P87PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P9n 端子機能制御レジスタ（P9nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsm_t<0x0008C188> P90PFS_;
		typedef pfsm_t<0x0008C189> P91PFS_;
		typedef pfsm_t<0x0008C18A> P92PFS_;
		typedef pfsm_t<0x0008C18B> P93PFS_;
		typedef pfsm_t<0x0008C18C> P94PFS_;
		typedef pfsm_t<0x0008C18D> P95PFS_;
		typedef pfsm_t<0x0008C18E> P96PFS_;
		typedef pfsm_t<0x0008C18F> P97PFS_;
		static P90PFS_ P90PFS;
		static P91PFS_ P91PFS;
		static P92PFS_ P92PFS;
		static P93PFS_ P93PFS;
		static P94PFS_ P94PFS;
		static P95PFS_ P95PFS;
		static P96PFS_ P96PFS;
		static P97PFS_ P97PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PAn 端子機能制御レジスタ（PAnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsy_t<0x0008C190> PA0PFS_;
		typedef pfsy_t<0x0008C191> PA1PFS_;
		typedef pfsy_t<0x0008C192> PA2PFS_;
		typedef pfsy_t<0x0008C193> PA3PFS_;
		typedef pfsy_t<0x0008C194> PA4PFS_;
		typedef pfsy_t<0x0008C195> PA5PFS_;
		typedef pfsy_t<0x0008C196> PA6PFS_;
		typedef pfsy_t<0x0008C197> PA7PFS_;
		static PA0PFS_ PA0PFS;
		static PA1PFS_ PA1PFS;
		static PA2PFS_ PA2PFS;
		static PA3PFS_ PA3PFS;
		static PA4PFS_ PA4PFS;
		static PA5PFS_ PA5PFS;
		static PA6PFS_ PA6PFS;
		static PA7PFS_ PA7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PBn 端子機能制御レジスタ（PBnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsy_t<0x0008C198> PB0PFS_;
		typedef pfsy_t<0x0008C199> PB1PFS_;
		typedef pfsy_t<0x0008C19A> PB2PFS_;
		typedef pfsy_t<0x0008C19B> PB3PFS_;
		typedef pfsy_t<0x0008C19C> PB4PFS_;
		typedef pfsy_t<0x0008C19D> PB5PFS_;
		typedef pfsy_t<0x0008C19E> PB6PFS_;
		typedef pfsy_t<0x0008C19F> PB7PFS_;
		static PB0PFS_ PB0PFS;
		static PB1PFS_ PB1PFS;
		static PB2PFS_ PB2PFS;
		static PB3PFS_ PB3PFS;
		static PB4PFS_ PB4PFS;
		static PB5PFS_ PB5PFS;
		static PB6PFS_ PB6PFS;
		static PB7PFS_ PB7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PCn 端子機能制御レジスタ（PCnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsy_t<0x0008C1A0> PC0PFS_;
		typedef pfsy_t<0x0008C1A1> PC1PFS_;
		typedef pfsy_t<0x0008C1A2> PC2PFS_;
		typedef pfsy_t<0x0008C1A3> PC3PFS_;
		typedef pfsy_t<0x0008C1A4> PC4PFS_;
		typedef pfsy_t<0x0008C1A5> PC5PFS_;
		typedef pfsy_t<0x0008C1A6> PC6PFS_;
		typedef pfsy_t<0x0008C1A7> PC7PFS_;
		static PC0PFS_ PC0PFS;
		static PC1PFS_ PC1PFS;
		static PC2PFS_ PC2PFS;
		static PC3PFS_ PC3PFS;
		static PC4PFS_ PC4PFS;
		static PC5PFS_ PC5PFS;
		static PC6PFS_ PC6PFS;
		static PC7PFS_ PC7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PDn 端子機能制御レジスタ（PDnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsx_t<0x0008C1A8> PD0PFS_;
		typedef pfsx_t<0x0008C1A9> PD1PFS_;
		typedef pfsx_t<0x0008C1AA> PD2PFS_;
		typedef pfsx_t<0x0008C1AB> PD3PFS_;
		typedef pfsx_t<0x0008C1AC> PD4PFS_;
		typedef pfsx_t<0x0008C1AD> PD5PFS_;
		typedef pfsx_t<0x0008C1AE> PD6PFS_;
		typedef pfsx_t<0x0008C1AF> PD7PFS_;
		static PD0PFS_ PD0PFS;
		static PD1PFS_ PD1PFS;
		static PD2PFS_ PD2PFS;
		static PD3PFS_ PD3PFS;
		static PD4PFS_ PD4PFS;
		static PD5PFS_ PD5PFS;
		static PD6PFS_ PD6PFS;
		static PD7PFS_ PD7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PEn 端子機能制御レジスタ（PEnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsx_t<0x0008C1B0> PE0PFS_;
		typedef pfsx_t<0x0008C1B1> PE1PFS_;
		typedef pfsx_t<0x0008C1B2> PE2PFS_;
		typedef pfsx_t<0x0008C1B3> PE3PFS_;
		typedef pfsx_t<0x0008C1B4> PE4PFS_;
		typedef pfsx_t<0x0008C1B5> PE5PFS_;
		typedef pfsx_t<0x0008C1B6> PE6PFS_;
		typedef pfsx_t<0x0008C1B7> PE7PFS_;
		static PE0PFS_ PE0PFS;
		static PE1PFS_ PE1PFS;
		static PE2PFS_ PE2PFS;
		static PE3PFS_ PE3PFS;
		static PE4PFS_ PE4PFS;
		static PE5PFS_ PE5PFS;
		static PE6PFS_ PE6PFS;
		static PE7PFS_ PE7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PFn 端子機能制御レジスタ（PFnPFS）（n = 0 ～ 5）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsy_t<0x0008C1B8> PF0PFS_;
		typedef pfsy_t<0x0008C1B9> PF1PFS_;
		typedef pfsy_t<0x0008C1BA> PF2PFS_;
		typedef pfsy_t<0x0008C1BB> PF3PFS_;
		typedef pfsy_t<0x0008C1BC> PF4PFS_;
		typedef pfsy_t<0x0008C1BD> PF5PFS_;
		static PF0PFS_ PF0PFS;
		static PF1PFS_ PF1PFS;
		static PF2PFS_ PF2PFS;
		static PF3PFS_ PF3PFS;
		static PF4PFS_ PF4PFS;
		static PF5PFS_ PF5PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PGn 端子機能制御レジスタ（PGnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsw_t<0x0008C1C0> PG0PFS_;
		typedef pfsw_t<0x0008C1C1> PG1PFS_;
		typedef pfsw_t<0x0008C1C2> PG2PFS_;
		typedef pfsw_t<0x0008C1C3> PG3PFS_;
		typedef pfsw_t<0x0008C1C4> PG4PFS_;
		typedef pfsw_t<0x0008C1C5> PG5PFS_;
		typedef pfsw_t<0x0008C1C6> PG6PFS_;
		typedef pfsw_t<0x0008C1C7> PG7PFS_;
		static PG0PFS_ PG0PFS;
		static PG1PFS_ PG1PFS;
		static PG2PFS_ PG2PFS;
		static PG3PFS_ PG3PFS;
		static PG4PFS_ PG4PFS;
		static PG5PFS_ PG5PFS;
		static PG6PFS_ PG6PFS;
		static PG7PFS_ PG7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PJn 端子機能制御レジスタ（PJnPFS）（n = 0 ～ 3, 5）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
#if defined(SIG_RX72N)
		typedef pfsw_t<0x0008C1D0> PJ0PFS_;
		static PJ0PFS_ PJ0PFS;
		typedef pfsw_t<0x0008C1D1> PJ1PFS_;
		static PJ1PFS_ PJ1PFS;
		typedef pfsw_t<0x0008C1D2> PJ2PFS_;
		static PJ2PFS_ PJ2PFS;
#endif
		typedef pfsw_t<0x0008C1D3> PJ3PFS_;
		static PJ3PFS_ PJ3PFS;
		typedef pfsw_t<0x0008C1D5> PJ5PFS_;
		static PJ5PFS_ PJ5PFS;


#if defined(SIG_RX72N)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PKn 端子機能制御レジスタ (PKnPFS) (n = 0 ～ 7)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsw_t<0x0008C1D8> PK0PFS_;
		typedef pfsw_t<0x0008C1D9> PK1PFS_;
		typedef pfsw_t<0x0008C1DA> PK2PFS_;
		typedef pfsw_t<0x0008C1DB> PK3PFS_;
		typedef pfsw_t<0x0008C1DC> PK4PFS_;
		typedef pfsw_t<0x0008C1DD> PK5PFS_;
		typedef pfsw_t<0x0008C1DE> PK6PFS_;
		typedef pfsw_t<0x0008C1DF> PK7PFS_;
		static PK0PFS_ PK0PFS;
		static PK1PFS_ PK1PFS;
		static PK2PFS_ PK2PFS;
		static PK3PFS_ PK3PFS;
		static PK4PFS_ PK4PFS;
		static PK5PFS_ PK5PFS;
		static PK6PFS_ PK6PFS;
		static PK7PFS_ PK7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	PLn 端子機能制御レジスタ (PLnPFS) (n = 0 ～ 7)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsw_t<0x0008C1E0> PL0PFS_;
		typedef pfsw_t<0x0008C1E1> PL1PFS_;
		typedef pfsw_t<0x0008C1E2> PL2PFS_;
		typedef pfsw_t<0x0008C1E3> PL3PFS_;
		typedef pfsw_t<0x0008C1E4> PL4PFS_;
		typedef pfsw_t<0x0008C1E5> PL5PFS_;
		typedef pfsw_t<0x0008C1E6> PL6PFS_;
		typedef pfsw_t<0x0008C1E7> PL7PFS_;
		static PL0PFS_ PL0PFS;
		static PL1PFS_ PL1PFS;
		static PL2PFS_ PL2PFS;
		static PL3PFS_ PL3PFS;
		static PL4PFS_ PL4PFS;
		static PL5PFS_ PL5PFS;
		static PL6PFS_ PL6PFS;
		static PL7PFS_ PL7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	PMn 端子機能制御レジスタ (PMnPFS) (n = 0 ～ 7)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsw_t<0x0008C1E8> PM0PFS_;
		typedef pfsw_t<0x0008C1E9> PM1PFS_;
		typedef pfsw_t<0x0008C1EA> PM2PFS_;
		typedef pfsw_t<0x0008C1EB> PM3PFS_;
		typedef pfsw_t<0x0008C1EC> PM4PFS_;
		typedef pfsw_t<0x0008C1ED> PM5PFS_;
		typedef pfsw_t<0x0008C1EE> PM6PFS_;
		typedef pfsw_t<0x0008C1EF> PM7PFS_;
		static PM0PFS_ PM0PFS;
		static PM1PFS_ PM1PFS;
		static PM2PFS_ PM2PFS;
		static PM3PFS_ PM3PFS;
		static PM4PFS_ PM4PFS;
		static PM5PFS_ PM5PFS;
		static PM6PFS_ PM6PFS;
		static PM7PFS_ PM7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	PNn 端子機能制御レジスタ (PNnPFS) (n = 0 ～ 5)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsw_t<0x0008C1F0> PN0PFS_;
		typedef pfsw_t<0x0008C1F1> PN1PFS_;
		typedef pfsw_t<0x0008C1F2> PN2PFS_;
		typedef pfsw_t<0x0008C1F3> PN3PFS_;
		typedef pfsw_t<0x0008C1F4> PN4PFS_;
		typedef pfsw_t<0x0008C1F5> PN5PFS_;
		static PN0PFS_ PN0PFS;
		static PN1PFS_ PN1PFS;
		static PN2PFS_ PN2PFS;
		static PN3PFS_ PN3PFS;
		static PN4PFS_ PN4PFS;
		static PN5PFS_ PN5PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	PQn 端子機能制御レジスタ (PQnPFS) (n = 0 ～ 7)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsw_t<0x0008C1F8> PQ0PFS_;
		typedef pfsw_t<0x0008C1F9> PQ1PFS_;
		typedef pfsw_t<0x0008C1FA> PQ2PFS_;
		typedef pfsw_t<0x0008C1FB> PQ3PFS_;
		typedef pfsw_t<0x0008C1FC> PQ4PFS_;
		typedef pfsw_t<0x0008C1FD> PQ5PFS_;
		typedef pfsw_t<0x0008C1FE> PQ6PFS_;
		typedef pfsw_t<0x0008C1FF> PQ7PFS_;
		static PQ0PFS_ PQ0PFS;
		static PQ1PFS_ PQ1PFS;
		static PQ2PFS_ PQ2PFS;
		static PQ3PFS_ PQ3PFS;
		static PQ4PFS_ PQ4PFS;
		static PQ5PFS_ PQ5PFS;
		static PQ6PFS_ PQ6PFS;
		static PQ7PFS_ PQ7PFS;
#endif


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
		typedef pfcse_t<0x0008C100> PFCSE_;
		static PFCSE_ PFCSE;


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
		typedef pfcss0_t<0x0008C102> PFCSS0_;
		static PFCSS0_ PFCSS0;


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
		typedef pfcss1_t<0x0008C103> PFCSS1_;
		static PFCSS1_ PFCSS1;


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
		typedef pfaoe0_t<0x0008C104> PFAOE0_;
		static PFAOE0_ PFAOE0;


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
		typedef pfaoe0_t<0x0008C105> PFAOE1_;
		static PFAOE1_ PFAOE1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  外部バス制御レジスタ 0（PFBCR0）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		typedef pfbcr0_t<0x0008C106> PFBCR0_;
		static PFBCR0_ PFBCR0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  外部バス制御レジスタ 1（PFBCR1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		typedef pfbcr1_t<0x0008C107> PFBCR1_;
		static PFBCR1_ PFBCR1;


#if defined(SIG_RX72N)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  外部バス制御レジスタ 2（PFBCR2）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		typedef pfbcr2_t<0x0008C108> PFBCR2_;
		static PFBCR2_ PFBCR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  外部バス制御レジスタ 3（PFBCR3）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfbcr3_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t <io, bitpos::B0>     DLHS;

			bit_rw_t <io, bitpos::B6>     SDCLKDRV;
			bit_rw_t <io, bitpos::B7>     WAITS2;
		};
		typedef pfbcr3_t<0x0008C109> PFBCR3_;
		static PFBCR3_ PFBCR3;
#endif


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  イーサネット制御レジスタ（PFENET）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfenet_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B4>  PHYMODE0;
			bit_rw_t<io, bitpos::B5>  PHYMODE1;
		};
		typedef pfenet_t<0x0008C10E> PFENET_;
		static PFENET_ PFENET;
	};
	typedef mpc_t<void> MPC;

	template<class _> typename mpc_t<_>::PWPR_   mpc_t<_>::PWPR;

	template<class _> typename mpc_t<_>::P00PFS_ mpc_t<_>::P00PFS;
	template<class _> typename mpc_t<_>::P01PFS_ mpc_t<_>::P01PFS;
	template<class _> typename mpc_t<_>::P02PFS_ mpc_t<_>::P02PFS;
	template<class _> typename mpc_t<_>::P03PFS_ mpc_t<_>::P03PFS;
	template<class _> typename mpc_t<_>::P05PFS_ mpc_t<_>::P05PFS;
	template<class _> typename mpc_t<_>::P07PFS_ mpc_t<_>::P07PFS;

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
	template<class _> typename mpc_t<_>::P54PFS_ mpc_t<_>::P54PFS;
	template<class _> typename mpc_t<_>::P55PFS_ mpc_t<_>::P55PFS;
	template<class _> typename mpc_t<_>::P56PFS_ mpc_t<_>::P56PFS;
	template<class _> typename mpc_t<_>::P57PFS_ mpc_t<_>::P57PFS;

#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72N)
	template<class _> typename mpc_t<_>::P60PFS_ mpc_t<_>::P60PFS;
#if defined(SIG_RX72N)
	template<class _> typename mpc_t<_>::P61PFS_ mpc_t<_>::P61PFS;
	template<class _> typename mpc_t<_>::P62PFS_ mpc_t<_>::P62PFS;
	template<class _> typename mpc_t<_>::P63PFS_ mpc_t<_>::P63PFS;
	template<class _> typename mpc_t<_>::P64PFS_ mpc_t<_>::P64PFS;
#endif
	template<class _> typename mpc_t<_>::P66PFS_ mpc_t<_>::P66PFS;
	template<class _> typename mpc_t<_>::P67PFS_ mpc_t<_>::P67PFS;
#elif defined(SIG_RX66T)
	template<class _> typename mpc_t<_>::P60PFS_ mpc_t<_>::P60PFS;
	template<class _> typename mpc_t<_>::P61PFS_ mpc_t<_>::P61PFS;
	template<class _> typename mpc_t<_>::P62PFS_ mpc_t<_>::P62PFS;
	template<class _> typename mpc_t<_>::P63PFS_ mpc_t<_>::P63PFS;
	template<class _> typename mpc_t<_>::P64PFS_ mpc_t<_>::P64PFS;
	template<class _> typename mpc_t<_>::P65PFS_ mpc_t<_>::P65PFS;
#endif
	template<class _> typename mpc_t<_>::P71PFS_ mpc_t<_>::P71PFS;
	template<class _> typename mpc_t<_>::P72PFS_ mpc_t<_>::P72PFS;
	template<class _> typename mpc_t<_>::P73PFS_ mpc_t<_>::P73PFS;
	template<class _> typename mpc_t<_>::P74PFS_ mpc_t<_>::P74PFS;
	template<class _> typename mpc_t<_>::P75PFS_ mpc_t<_>::P75PFS;
	template<class _> typename mpc_t<_>::P76PFS_ mpc_t<_>::P76PFS;
	template<class _> typename mpc_t<_>::P77PFS_ mpc_t<_>::P77PFS;

	template<class _> typename mpc_t<_>::P80PFS_ mpc_t<_>::P80PFS;
	template<class _> typename mpc_t<_>::P81PFS_ mpc_t<_>::P81PFS;
	template<class _> typename mpc_t<_>::P82PFS_ mpc_t<_>::P82PFS;
	template<class _> typename mpc_t<_>::P83PFS_ mpc_t<_>::P83PFS;
	template<class _> typename mpc_t<_>::P84PFS_ mpc_t<_>::P84PFS;
	template<class _> typename mpc_t<_>::P85PFS_ mpc_t<_>::P85PFS;
	template<class _> typename mpc_t<_>::P86PFS_ mpc_t<_>::P86PFS;
	template<class _> typename mpc_t<_>::P87PFS_ mpc_t<_>::P87PFS;

	template<class _> typename mpc_t<_>::P90PFS_ mpc_t<_>::P90PFS;
	template<class _> typename mpc_t<_>::P91PFS_ mpc_t<_>::P91PFS;
	template<class _> typename mpc_t<_>::P92PFS_ mpc_t<_>::P92PFS;
	template<class _> typename mpc_t<_>::P93PFS_ mpc_t<_>::P93PFS;
	template<class _> typename mpc_t<_>::P94PFS_ mpc_t<_>::P94PFS;
	template<class _> typename mpc_t<_>::P95PFS_ mpc_t<_>::P95PFS;
	template<class _> typename mpc_t<_>::P96PFS_ mpc_t<_>::P96PFS;
	template<class _> typename mpc_t<_>::P97PFS_ mpc_t<_>::P97PFS;

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
	template<class _> typename mpc_t<_>::PC7PFS_ mpc_t<_>::PC7PFS;

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
	template<class _> typename mpc_t<_>::PE7PFS_ mpc_t<_>::PE7PFS;

	template<class _> typename mpc_t<_>::PF0PFS_ mpc_t<_>::PF0PFS;
	template<class _> typename mpc_t<_>::PF1PFS_ mpc_t<_>::PF1PFS;
	template<class _> typename mpc_t<_>::PF2PFS_ mpc_t<_>::PF2PFS;
	template<class _> typename mpc_t<_>::PF3PFS_ mpc_t<_>::PF3PFS;
	template<class _> typename mpc_t<_>::PF4PFS_ mpc_t<_>::PF4PFS;
	template<class _> typename mpc_t<_>::PF5PFS_ mpc_t<_>::PF5PFS;

	template<class _> typename mpc_t<_>::PG0PFS_ mpc_t<_>::PG0PFS;
	template<class _> typename mpc_t<_>::PG1PFS_ mpc_t<_>::PG1PFS;
	template<class _> typename mpc_t<_>::PG2PFS_ mpc_t<_>::PG2PFS;
	template<class _> typename mpc_t<_>::PG3PFS_ mpc_t<_>::PG3PFS;
	template<class _> typename mpc_t<_>::PG4PFS_ mpc_t<_>::PG4PFS;
	template<class _> typename mpc_t<_>::PG5PFS_ mpc_t<_>::PG5PFS;
	template<class _> typename mpc_t<_>::PG6PFS_ mpc_t<_>::PG6PFS;
	template<class _> typename mpc_t<_>::PG7PFS_ mpc_t<_>::PG7PFS;

#if defined(SIG_RX72N)
	template<class _> typename mpc_t<_>::PJ0PFS_ mpc_t<_>::PJ0PFS;
	template<class _> typename mpc_t<_>::PJ1PFS_ mpc_t<_>::PJ1PFS;
	template<class _> typename mpc_t<_>::PJ2PFS_ mpc_t<_>::PJ2PFS;
#endif
	template<class _> typename mpc_t<_>::PJ3PFS_ mpc_t<_>::PJ3PFS;
	template<class _> typename mpc_t<_>::PJ5PFS_ mpc_t<_>::PJ5PFS;

#if defined(SIG_RX72N)
	template<class _> typename mpc_t<_>::PK0PFS_ mpc_t<_>::PK0PFS;
	template<class _> typename mpc_t<_>::PK1PFS_ mpc_t<_>::PK1PFS;
	template<class _> typename mpc_t<_>::PK2PFS_ mpc_t<_>::PK2PFS;
	template<class _> typename mpc_t<_>::PK3PFS_ mpc_t<_>::PK3PFS;
	template<class _> typename mpc_t<_>::PK4PFS_ mpc_t<_>::PK4PFS;
	template<class _> typename mpc_t<_>::PK5PFS_ mpc_t<_>::PK5PFS;
	template<class _> typename mpc_t<_>::PK6PFS_ mpc_t<_>::PK6PFS;
	template<class _> typename mpc_t<_>::PK7PFS_ mpc_t<_>::PK7PFS;

	template<class _> typename mpc_t<_>::PL0PFS_ mpc_t<_>::PL0PFS;
	template<class _> typename mpc_t<_>::PL1PFS_ mpc_t<_>::PL1PFS;
	template<class _> typename mpc_t<_>::PL2PFS_ mpc_t<_>::PL2PFS;
	template<class _> typename mpc_t<_>::PL3PFS_ mpc_t<_>::PL3PFS;
	template<class _> typename mpc_t<_>::PL4PFS_ mpc_t<_>::PL4PFS;
	template<class _> typename mpc_t<_>::PL5PFS_ mpc_t<_>::PL5PFS;
	template<class _> typename mpc_t<_>::PL6PFS_ mpc_t<_>::PL6PFS;
	template<class _> typename mpc_t<_>::PL7PFS_ mpc_t<_>::PL7PFS;

	template<class _> typename mpc_t<_>::PM0PFS_ mpc_t<_>::PM0PFS;
	template<class _> typename mpc_t<_>::PM1PFS_ mpc_t<_>::PM1PFS;
	template<class _> typename mpc_t<_>::PM2PFS_ mpc_t<_>::PM2PFS;
	template<class _> typename mpc_t<_>::PM3PFS_ mpc_t<_>::PM3PFS;
	template<class _> typename mpc_t<_>::PM4PFS_ mpc_t<_>::PM4PFS;
	template<class _> typename mpc_t<_>::PM5PFS_ mpc_t<_>::PM5PFS;
	template<class _> typename mpc_t<_>::PM6PFS_ mpc_t<_>::PM6PFS;
	template<class _> typename mpc_t<_>::PM7PFS_ mpc_t<_>::PM7PFS;

	template<class _> typename mpc_t<_>::PN0PFS_ mpc_t<_>::PN0PFS;
	template<class _> typename mpc_t<_>::PN1PFS_ mpc_t<_>::PN1PFS;
	template<class _> typename mpc_t<_>::PN2PFS_ mpc_t<_>::PN2PFS;
	template<class _> typename mpc_t<_>::PN3PFS_ mpc_t<_>::PN3PFS;
	template<class _> typename mpc_t<_>::PN4PFS_ mpc_t<_>::PN4PFS;
	template<class _> typename mpc_t<_>::PN5PFS_ mpc_t<_>::PN5PFS;

	template<class _> typename mpc_t<_>::PQ0PFS_ mpc_t<_>::PQ0PFS;
	template<class _> typename mpc_t<_>::PQ1PFS_ mpc_t<_>::PQ1PFS;
	template<class _> typename mpc_t<_>::PQ2PFS_ mpc_t<_>::PQ2PFS;
	template<class _> typename mpc_t<_>::PQ3PFS_ mpc_t<_>::PQ3PFS;
	template<class _> typename mpc_t<_>::PQ4PFS_ mpc_t<_>::PQ4PFS;
	template<class _> typename mpc_t<_>::PQ5PFS_ mpc_t<_>::PQ5PFS;
	template<class _> typename mpc_t<_>::PQ6PFS_ mpc_t<_>::PQ6PFS;
	template<class _> typename mpc_t<_>::PQ7PFS_ mpc_t<_>::PQ7PFS;
#endif

	template<class _> typename mpc_t<_>::PFCSE_  mpc_t<_>::PFCSE;
	template<class _> typename mpc_t<_>::PFCSS0_ mpc_t<_>::PFCSS0;
	template<class _> typename mpc_t<_>::PFCSS1_ mpc_t<_>::PFCSS1;
	template<class _> typename mpc_t<_>::PFAOE0_ mpc_t<_>::PFAOE0;
	template<class _> typename mpc_t<_>::PFAOE1_ mpc_t<_>::PFAOE1;
	template<class _> typename mpc_t<_>::PFBCR0_ mpc_t<_>::PFBCR0;
	template<class _> typename mpc_t<_>::PFBCR1_ mpc_t<_>::PFBCR1;
#if defined(SIG_RX72N)
	template<class _> typename mpc_t<_>::PFBCR2_ mpc_t<_>::PFBCR2;
	template<class _> typename mpc_t<_>::PFBCR3_ mpc_t<_>::PFBCR3;
#endif
	template<class _> typename mpc_t<_>::PFENET_ mpc_t<_>::PFENET;
}
