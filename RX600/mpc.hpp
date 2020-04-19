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
		typedef pwpr_t<0x0008C11F> PWPR_t;
		static PWPR_t PWPR;


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
		typedef pfsx_t<0x0008C140> P00PFS_t;
		typedef pfsx_t<0x0008C141> P01PFS_t;
		typedef pfsx_t<0x0008C142> P02PFS_t;
		typedef pfsx_t<0x0008C143> P03PFS_t;
		typedef pfsx_t<0x0008C145> P05PFS_t;
		typedef pfsx_t<0x0008C147> P07PFS_t;
		static P00PFS_t P00PFS;
		static P01PFS_t P01PFS;
		static P02PFS_t P02PFS;
		static P03PFS_t P03PFS;
		static P05PFS_t P05PFS;
		static P07PFS_t P07PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P1n 端子機能制御レジスタ（P1nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsy_t<0x0008C148> P10PFS_t;
		typedef pfsy_t<0x0008C149> P11PFS_t;
		typedef pfsy_t<0x0008C14A> P12PFS_t;
		typedef pfsy_t<0x0008C14B> P13PFS_t;
		typedef pfsy_t<0x0008C14C> P14PFS_t;
		typedef pfsy_t<0x0008C14D> P15PFS_t;
		typedef pfsy_t<0x0008C14E> P16PFS_t;
		typedef pfsy_t<0x0008C14F> P17PFS_t;
		static P10PFS_t P10PFS;
		static P11PFS_t P11PFS;
		static P12PFS_t P12PFS;
		static P13PFS_t P13PFS;
		static P14PFS_t P14PFS;
		static P15PFS_t P15PFS;
		static P16PFS_t P16PFS;
		static P17PFS_t P17PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P2n 端子機能制御レジスタ（P2nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsy_t<0x0008C150> P20PFS_t;
		typedef pfsy_t<0x0008C151> P21PFS_t;
		typedef pfsy_t<0x0008C152> P22PFS_t;
		typedef pfsy_t<0x0008C153> P23PFS_t;
		typedef pfsy_t<0x0008C154> P24PFS_t;
		typedef pfsy_t<0x0008C155> P25PFS_t;
		typedef pfsy_t<0x0008C156> P26PFS_t;
		typedef pfsy_t<0x0008C157> P27PFS_t;
		static P20PFS_t P20PFS;
		static P21PFS_t P21PFS;
		static P22PFS_t P22PFS;
		static P23PFS_t P23PFS;
		static P24PFS_t P24PFS;
		static P25PFS_t P25PFS;
		static P26PFS_t P26PFS;
		static P27PFS_t P27PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P3n 端子機能制御レジスタ（P3nPFS）（n = 0 ～ 4）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsy_t<0x0008C158> P30PFS_t;
		typedef pfsy_t<0x0008C159> P31PFS_t;
		typedef pfsy_t<0x0008C15A> P32PFS_t;
		typedef pfsy_t<0x0008C15B> P33PFS_t;
		typedef pfsy_t<0x0008C15C> P34PFS_t;
		static P30PFS_t P30PFS;
		static P31PFS_t P31PFS;
		static P32PFS_t P32PFS;
		static P33PFS_t P33PFS;
		static P34PFS_t P34PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P4n 端子機能制御レジスタ（P4nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsz_t<0x0008C160> P40PFS_t;
		typedef pfsz_t<0x0008C161> P41PFS_t;
		typedef pfsz_t<0x0008C162> P42PFS_t;
		typedef pfsz_t<0x0008C163> P43PFS_t;
		typedef pfsz_t<0x0008C164> P44PFS_t;
		typedef pfsz_t<0x0008C165> P45PFS_t;
		typedef pfsz_t<0x0008C166> P46PFS_t;
		typedef pfsz_t<0x0008C167> P47PFS_t;
		static P40PFS_t P40PFS;
		static P41PFS_t P41PFS;
		static P42PFS_t P42PFS;
		static P43PFS_t P43PFS;
		static P44PFS_t P44PFS;
		static P45PFS_t P45PFS;
		static P46PFS_t P46PFS;
		static P47PFS_t P47PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P5n 端子機能制御レジスタ（P5nPFS）（n = 0 ～ 2, 4 ～ 6）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsy_t<0x0008C168> P50PFS_t;
		typedef pfsy_t<0x0008C169> P51PFS_t;
		typedef pfsy_t<0x0008C16A> P52PFS_t;
		typedef pfsy_t<0x0008C16C> P54PFS_t;
		typedef pfsy_t<0x0008C16D> P55PFS_t;
		typedef pfsy_t<0x0008C16E> P56PFS_t;
		typedef pfsy_t<0x0008C16F> P57PFS_t;
		static P50PFS_t P50PFS;
		static P51PFS_t P51PFS;
		static P52PFS_t P52PFS;
		static P54PFS_t P54PFS;
		static P55PFS_t P55PFS;
		static P56PFS_t P56PFS;
		static P57PFS_t P57PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P6n 端子機能制御レジスタ（P6nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72N)
		typedef pfsy_t<0x0008C170> P60PFS_t;
		static P60PFS_t P60PFS;
#if defined(SIG_RX72N)
		typedef pfsy_t<0x0008C171> P61PFS_t;
		typedef pfsy_t<0x0008C172> P62PFS_t;
		typedef pfsy_t<0x0008C173> P63PFS_t;
		typedef pfsy_t<0x0008C174> P64PFS_t;
		static P61PFS_t P61PFS;
		static P62PFS_t P62PFS;
		static P63PFS_t P63PFS;
		static P64PFS_t P64PFS;
#endif
		typedef pfsy_t<0x0008C176> P66PFS_t;
		typedef pfsy_t<0x0008C177> P67PFS_t;
		static P66PFS_t P66PFS;
		static P67PFS_t P67PFS;

#elif defined(SIG_RX66T)
		typedef pfsz_t<0x0008C170> P60PFS_t;
		typedef pfsz_t<0x0008C171> P61PFS_t;
		typedef pfsz_t<0x0008C172> P62PFS_t;
		typedef pfsz_t<0x0008C173> P63PFS_t;
		typedef pfsz_t<0x0008C174> P64PFS_t;
		typedef pfsz_t<0x0008C175> P65PFS_t;
		static P60PFS_t P60PFS;
		static P61PFS_t P61PFS;
		static P62PFS_t P62PFS;
		static P63PFS_t P63PFS;
		static P64PFS_t P64PFS;
		static P65PFS_t P65PFS;
#endif

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P7n 端子機能制御レジスタ（P7nPFS）（n = 1 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsw_t<0x0008C179> P71PFS_t;
		typedef pfsw_t<0x0008C17A> P72PFS_t;
		typedef pfsw_t<0x0008C17B> P73PFS_t;
		typedef pfsw_t<0x0008C17C> P74PFS_t;
		typedef pfsw_t<0x0008C17D> P75PFS_t;
		typedef pfsw_t<0x0008C17E> P76PFS_t;
		typedef pfsw_t<0x0008C17F> P77PFS_t;
		static P71PFS_t P71PFS;
		static P72PFS_t P72PFS;
		static P73PFS_t P73PFS;
		static P74PFS_t P74PFS;
		static P75PFS_t P75PFS;
		static P76PFS_t P76PFS;
		static P77PFS_t P77PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P8n 端子機能制御レジスタ（P8nPFS）（n = 0 ～ 3, 6, 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsw_t<0x0008C180> P80PFS_t;
		typedef pfsw_t<0x0008C181> P81PFS_t;
		typedef pfsw_t<0x0008C182> P82PFS_t;
		typedef pfsw_t<0x0008C183> P83PFS_t;
		typedef pfsw_t<0x0008C184> P84PFS_t;
		typedef pfsw_t<0x0008C185> P85PFS_t;
		typedef pfsw_t<0x0008C186> P86PFS_t;
		typedef pfsw_t<0x0008C187> P87PFS_t;
		static P80PFS_t P80PFS;
		static P81PFS_t P81PFS;
		static P82PFS_t P82PFS;
		static P83PFS_t P83PFS;
		static P84PFS_t P84PFS;
		static P85PFS_t P85PFS;
		static P86PFS_t P86PFS;
		static P87PFS_t P87PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P9n 端子機能制御レジスタ（P9nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsm_t<0x0008C188> P90PFS_t;
		typedef pfsm_t<0x0008C189> P91PFS_t;
		typedef pfsm_t<0x0008C18A> P92PFS_t;
		typedef pfsm_t<0x0008C18B> P93PFS_t;
		typedef pfsm_t<0x0008C18C> P94PFS_t;
		typedef pfsm_t<0x0008C18D> P95PFS_t;
		typedef pfsm_t<0x0008C18E> P96PFS_t;
		typedef pfsm_t<0x0008C18F> P97PFS_t;
		static P90PFS_t P90PFS;
		static P91PFS_t P91PFS;
		static P92PFS_t P92PFS;
		static P93PFS_t P93PFS;
		static P94PFS_t P94PFS;
		static P95PFS_t P95PFS;
		static P96PFS_t P96PFS;
		static P97PFS_t P97PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PAn 端子機能制御レジスタ（PAnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsy_t<0x0008C190> PA0PFS_t;
		typedef pfsy_t<0x0008C191> PA1PFS_t;
		typedef pfsy_t<0x0008C192> PA2PFS_t;
		typedef pfsy_t<0x0008C193> PA3PFS_t;
		typedef pfsy_t<0x0008C194> PA4PFS_t;
		typedef pfsy_t<0x0008C195> PA5PFS_t;
		typedef pfsy_t<0x0008C196> PA6PFS_t;
		typedef pfsy_t<0x0008C197> PA7PFS_t;
		static PA0PFS_t PA0PFS;
		static PA1PFS_t PA1PFS;
		static PA2PFS_t PA2PFS;
		static PA3PFS_t PA3PFS;
		static PA4PFS_t PA4PFS;
		static PA5PFS_t PA5PFS;
		static PA6PFS_t PA6PFS;
		static PA7PFS_t PA7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PBn 端子機能制御レジスタ（PBnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsy_t<0x0008C198> PB0PFS_t;
		typedef pfsy_t<0x0008C199> PB1PFS_t;
		typedef pfsy_t<0x0008C19A> PB2PFS_t;
		typedef pfsy_t<0x0008C19B> PB3PFS_t;
		typedef pfsy_t<0x0008C19C> PB4PFS_t;
		typedef pfsy_t<0x0008C19D> PB5PFS_t;
		typedef pfsy_t<0x0008C19E> PB6PFS_t;
		typedef pfsy_t<0x0008C19F> PB7PFS_t;
		static PB0PFS_t PB0PFS;
		static PB1PFS_t PB1PFS;
		static PB2PFS_t PB2PFS;
		static PB3PFS_t PB3PFS;
		static PB4PFS_t PB4PFS;
		static PB5PFS_t PB5PFS;
		static PB6PFS_t PB6PFS;
		static PB7PFS_t PB7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PCn 端子機能制御レジスタ（PCnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsy_t<0x0008C1A0> PC0PFS_t;
		typedef pfsy_t<0x0008C1A1> PC1PFS_t;
		typedef pfsy_t<0x0008C1A2> PC2PFS_t;
		typedef pfsy_t<0x0008C1A3> PC3PFS_t;
		typedef pfsy_t<0x0008C1A4> PC4PFS_t;
		typedef pfsy_t<0x0008C1A5> PC5PFS_t;
		typedef pfsy_t<0x0008C1A6> PC6PFS_t;
		typedef pfsy_t<0x0008C1A7> PC7PFS_t;
		static PC0PFS_t PC0PFS;
		static PC1PFS_t PC1PFS;
		static PC2PFS_t PC2PFS;
		static PC3PFS_t PC3PFS;
		static PC4PFS_t PC4PFS;
		static PC5PFS_t PC5PFS;
		static PC6PFS_t PC6PFS;
		static PC7PFS_t PC7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PDn 端子機能制御レジスタ（PDnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsx_t<0x0008C1A8> PD0PFS_t;
		typedef pfsx_t<0x0008C1A9> PD1PFS_t;
		typedef pfsx_t<0x0008C1AA> PD2PFS_t;
		typedef pfsx_t<0x0008C1AB> PD3PFS_t;
		typedef pfsx_t<0x0008C1AC> PD4PFS_t;
		typedef pfsx_t<0x0008C1AD> PD5PFS_t;
		typedef pfsx_t<0x0008C1AE> PD6PFS_t;
		typedef pfsx_t<0x0008C1AF> PD7PFS_t;
		static PD0PFS_t PD0PFS;
		static PD1PFS_t PD1PFS;
		static PD2PFS_t PD2PFS;
		static PD3PFS_t PD3PFS;
		static PD4PFS_t PD4PFS;
		static PD5PFS_t PD5PFS;
		static PD6PFS_t PD6PFS;
		static PD7PFS_t PD7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PEn 端子機能制御レジスタ（PEnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsx_t<0x0008C1B0> PE0PFS_t;
		typedef pfsx_t<0x0008C1B1> PE1PFS_t;
		typedef pfsx_t<0x0008C1B2> PE2PFS_t;
		typedef pfsx_t<0x0008C1B3> PE3PFS_t;
		typedef pfsx_t<0x0008C1B4> PE4PFS_t;
		typedef pfsx_t<0x0008C1B5> PE5PFS_t;
		typedef pfsx_t<0x0008C1B6> PE6PFS_t;
		typedef pfsx_t<0x0008C1B7> PE7PFS_t;
		static PE0PFS_t PE0PFS;
		static PE1PFS_t PE1PFS;
		static PE2PFS_t PE2PFS;
		static PE3PFS_t PE3PFS;
		static PE4PFS_t PE4PFS;
		static PE5PFS_t PE5PFS;
		static PE6PFS_t PE6PFS;
		static PE7PFS_t PE7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PFn 端子機能制御レジスタ（PFnPFS）（n = 0 ～ 5）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsy_t<0x0008C1B8> PF0PFS_t;
		typedef pfsy_t<0x0008C1B9> PF1PFS_t;
		typedef pfsy_t<0x0008C1BA> PF2PFS_t;
		typedef pfsy_t<0x0008C1BB> PF3PFS_t;
		typedef pfsy_t<0x0008C1BC> PF4PFS_t;
		typedef pfsy_t<0x0008C1BD> PF5PFS_t;
		static PF0PFS_t PF0PFS;
		static PF1PFS_t PF1PFS;
		static PF2PFS_t PF2PFS;
		static PF3PFS_t PF3PFS;
		static PF4PFS_t PF4PFS;
		static PF5PFS_t PF5PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PGn 端子機能制御レジスタ（PGnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsw_t<0x0008C1C0> PG0PFS_t;
		typedef pfsw_t<0x0008C1C1> PG1PFS_t;
		typedef pfsw_t<0x0008C1C2> PG2PFS_t;
		typedef pfsw_t<0x0008C1C3> PG3PFS_t;
		typedef pfsw_t<0x0008C1C4> PG4PFS_t;
		typedef pfsw_t<0x0008C1C5> PG5PFS_t;
		typedef pfsw_t<0x0008C1C6> PG6PFS_t;
		typedef pfsw_t<0x0008C1C7> PG7PFS_t;
		static PG0PFS_t PG0PFS;
		static PG1PFS_t PG1PFS;
		static PG2PFS_t PG2PFS;
		static PG3PFS_t PG3PFS;
		static PG4PFS_t PG4PFS;
		static PG5PFS_t PG5PFS;
		static PG6PFS_t PG6PFS;
		static PG7PFS_t PG7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PJn 端子機能制御レジスタ（PJnPFS）（n = 0 ～ 3, 5）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
#if defined(SIG_RX72N)
		typedef pfsw_t<0x0008C1D0> PJ0PFS_t;
		static PJ0PFS_t PJ0PFS;
		typedef pfsw_t<0x0008C1D1> PJ1PFS_t;
		static PJ1PFS_t PJ1PFS;
		typedef pfsw_t<0x0008C1D2> PJ2PFS_t;
		static PJ2PFS_t PJ2PFS;
#endif
		typedef pfsw_t<0x0008C1D3> PJ3PFS_t;
		static PJ3PFS_t PJ3PFS;
		typedef pfsw_t<0x0008C1D5> PJ5PFS_t;
		static PJ5PFS_t PJ5PFS;


#if defined(SIG_RX72N)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PKn 端子機能制御レジスタ (PKnPFS) (n = 0 ～ 7)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsw_t<0x0008C1D8> PK0PFS_t;
		typedef pfsw_t<0x0008C1D9> PK1PFS_t;
		typedef pfsw_t<0x0008C1DA> PK2PFS_t;
		typedef pfsw_t<0x0008C1DB> PK3PFS_t;
		typedef pfsw_t<0x0008C1DC> PK4PFS_t;
		typedef pfsw_t<0x0008C1DD> PK5PFS_t;
		typedef pfsw_t<0x0008C1DE> PK6PFS_t;
		typedef pfsw_t<0x0008C1DF> PK7PFS_t;
		static PK0PFS_t PK0PFS;
		static PK1PFS_t PK1PFS;
		static PK2PFS_t PK2PFS;
		static PK3PFS_t PK3PFS;
		static PK4PFS_t PK4PFS;
		static PK5PFS_t PK5PFS;
		static PK6PFS_t PK6PFS;
		static PK7PFS_t PK7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	PLn 端子機能制御レジスタ (PLnPFS) (n = 0 ～ 7)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsw_t<0x0008C1E0> PL0PFS_t;
		typedef pfsw_t<0x0008C1E1> PL1PFS_t;
		typedef pfsw_t<0x0008C1E2> PL2PFS_t;
		typedef pfsw_t<0x0008C1E3> PL3PFS_t;
		typedef pfsw_t<0x0008C1E4> PL4PFS_t;
		typedef pfsw_t<0x0008C1E5> PL5PFS_t;
		typedef pfsw_t<0x0008C1E6> PL6PFS_t;
		typedef pfsw_t<0x0008C1E7> PL7PFS_t;
		static PL0PFS_t PL0PFS;
		static PL1PFS_t PL1PFS;
		static PL2PFS_t PL2PFS;
		static PL3PFS_t PL3PFS;
		static PL4PFS_t PL4PFS;
		static PL5PFS_t PL5PFS;
		static PL6PFS_t PL6PFS;
		static PL7PFS_t PL7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	PMn 端子機能制御レジスタ (PMnPFS) (n = 0 ～ 7)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsw_t<0x0008C1E8> PM0PFS_t;
		typedef pfsw_t<0x0008C1E9> PM1PFS_t;
		typedef pfsw_t<0x0008C1EA> PM2PFS_t;
		typedef pfsw_t<0x0008C1EB> PM3PFS_t;
		typedef pfsw_t<0x0008C1EC> PM4PFS_t;
		typedef pfsw_t<0x0008C1ED> PM5PFS_t;
		typedef pfsw_t<0x0008C1EE> PM6PFS_t;
		typedef pfsw_t<0x0008C1EF> PM7PFS_t;
		static PM0PFS_t PM0PFS;
		static PM1PFS_t PM1PFS;
		static PM2PFS_t PM2PFS;
		static PM3PFS_t PM3PFS;
		static PM4PFS_t PM4PFS;
		static PM5PFS_t PM5PFS;
		static PM6PFS_t PM6PFS;
		static PM7PFS_t PM7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	PNn 端子機能制御レジスタ (PNnPFS) (n = 0 ～ 5)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsw_t<0x0008C1F0> PN0PFS_t;
		typedef pfsw_t<0x0008C1F1> PN1PFS_t;
		typedef pfsw_t<0x0008C1F2> PN2PFS_t;
		typedef pfsw_t<0x0008C1F3> PN3PFS_t;
		typedef pfsw_t<0x0008C1F4> PN4PFS_t;
		typedef pfsw_t<0x0008C1F5> PN5PFS_t;
		static PN0PFS_t PN0PFS;
		static PN1PFS_t PN1PFS;
		static PN2PFS_t PN2PFS;
		static PN3PFS_t PN3PFS;
		static PN4PFS_t PN4PFS;
		static PN5PFS_t PN5PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	PQn 端子機能制御レジスタ (PQnPFS) (n = 0 ～ 7)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsw_t<0x0008C1F8> PQ0PFS_t;
		typedef pfsw_t<0x0008C1F9> PQ1PFS_t;
		typedef pfsw_t<0x0008C1FA> PQ2PFS_t;
		typedef pfsw_t<0x0008C1FB> PQ3PFS_t;
		typedef pfsw_t<0x0008C1FC> PQ4PFS_t;
		typedef pfsw_t<0x0008C1FD> PQ5PFS_t;
		typedef pfsw_t<0x0008C1FE> PQ6PFS_t;
		typedef pfsw_t<0x0008C1FF> PQ7PFS_t;
		static PQ0PFS_t PQ0PFS;
		static PQ1PFS_t PQ1PFS;
		static PQ2PFS_t PQ2PFS;
		static PQ3PFS_t PQ3PFS;
		static PQ4PFS_t PQ4PFS;
		static PQ5PFS_t PQ5PFS;
		static PQ6PFS_t PQ6PFS;
		static PQ7PFS_t PQ7PFS;
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
		typedef pfcse_t<0x0008C100> PFCSE_t;
		static PFCSE_t PFCSE;


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
		typedef pfcss0_t<0x0008C102> PFCSS0_t;
		static PFCSS0_t PFCSS0;


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
		typedef pfcss1_t<0x0008C103> PFCSS1_t;
		static PFCSS1_t PFCSS1;


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
		typedef pfaoe0_t<0x0008C104> PFAOE0_t;
		static PFAOE0_t PFAOE0;


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
		typedef pfaoe0_t<0x0008C105> PFAOE1_t;
		static PFAOE1_t PFAOE1;


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
		typedef pfbcr0_t<0x0008C106> PFBCR0_t;
		static PFBCR0_t PFBCR0;


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
		typedef pfbcr1_t<0x0008C107> PFBCR1_t;
		static PFBCR1_t PFBCR1;


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
		typedef pfbcr2_t<0x0008C108> PFBCR2_t;
		static PFBCR2_t PFBCR2;


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
		typedef pfbcr3_t<0x0008C109> PFBCR3_t;
		static PFBCR3_t PFBCR3;
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
		typedef pfenet_t<0x0008C10E> PFENET_t;
		static PFENET_t PFENET;
	};
	typedef mpc_t<void> MPC;

	template<class _> typename mpc_t<_>::PWPR_t   mpc_t<_>::PWPR;

	template<class _> typename mpc_t<_>::P00PFS_t mpc_t<_>::P00PFS;
	template<class _> typename mpc_t<_>::P01PFS_t mpc_t<_>::P01PFS;
	template<class _> typename mpc_t<_>::P02PFS_t mpc_t<_>::P02PFS;
	template<class _> typename mpc_t<_>::P03PFS_t mpc_t<_>::P03PFS;
	template<class _> typename mpc_t<_>::P05PFS_t mpc_t<_>::P05PFS;
	template<class _> typename mpc_t<_>::P07PFS_t mpc_t<_>::P07PFS;

	template<class _> typename mpc_t<_>::P10PFS_t mpc_t<_>::P10PFS;
	template<class _> typename mpc_t<_>::P11PFS_t mpc_t<_>::P11PFS;
	template<class _> typename mpc_t<_>::P12PFS_t mpc_t<_>::P12PFS;
	template<class _> typename mpc_t<_>::P13PFS_t mpc_t<_>::P13PFS;
	template<class _> typename mpc_t<_>::P14PFS_t mpc_t<_>::P14PFS;
	template<class _> typename mpc_t<_>::P15PFS_t mpc_t<_>::P15PFS;
	template<class _> typename mpc_t<_>::P16PFS_t mpc_t<_>::P16PFS;
	template<class _> typename mpc_t<_>::P17PFS_t mpc_t<_>::P17PFS;

	template<class _> typename mpc_t<_>::P20PFS_t mpc_t<_>::P20PFS;
	template<class _> typename mpc_t<_>::P21PFS_t mpc_t<_>::P21PFS;
	template<class _> typename mpc_t<_>::P22PFS_t mpc_t<_>::P22PFS;
	template<class _> typename mpc_t<_>::P23PFS_t mpc_t<_>::P23PFS;
	template<class _> typename mpc_t<_>::P24PFS_t mpc_t<_>::P24PFS;
	template<class _> typename mpc_t<_>::P25PFS_t mpc_t<_>::P25PFS;
	template<class _> typename mpc_t<_>::P26PFS_t mpc_t<_>::P26PFS;
	template<class _> typename mpc_t<_>::P27PFS_t mpc_t<_>::P27PFS;

	template<class _> typename mpc_t<_>::P30PFS_t mpc_t<_>::P30PFS;
	template<class _> typename mpc_t<_>::P31PFS_t mpc_t<_>::P31PFS;
	template<class _> typename mpc_t<_>::P32PFS_t mpc_t<_>::P32PFS;
	template<class _> typename mpc_t<_>::P33PFS_t mpc_t<_>::P33PFS;
	template<class _> typename mpc_t<_>::P34PFS_t mpc_t<_>::P34PFS;

	template<class _> typename mpc_t<_>::P40PFS_t mpc_t<_>::P40PFS;
	template<class _> typename mpc_t<_>::P41PFS_t mpc_t<_>::P41PFS;
	template<class _> typename mpc_t<_>::P42PFS_t mpc_t<_>::P42PFS;
	template<class _> typename mpc_t<_>::P43PFS_t mpc_t<_>::P43PFS;
	template<class _> typename mpc_t<_>::P44PFS_t mpc_t<_>::P44PFS;
	template<class _> typename mpc_t<_>::P45PFS_t mpc_t<_>::P45PFS;
	template<class _> typename mpc_t<_>::P46PFS_t mpc_t<_>::P46PFS;
	template<class _> typename mpc_t<_>::P47PFS_t mpc_t<_>::P47PFS;

	template<class _> typename mpc_t<_>::P50PFS_t mpc_t<_>::P50PFS;
	template<class _> typename mpc_t<_>::P51PFS_t mpc_t<_>::P51PFS;
	template<class _> typename mpc_t<_>::P52PFS_t mpc_t<_>::P52PFS;
	template<class _> typename mpc_t<_>::P54PFS_t mpc_t<_>::P54PFS;
	template<class _> typename mpc_t<_>::P55PFS_t mpc_t<_>::P55PFS;
	template<class _> typename mpc_t<_>::P56PFS_t mpc_t<_>::P56PFS;
	template<class _> typename mpc_t<_>::P57PFS_t mpc_t<_>::P57PFS;

#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72N)
	template<class _> typename mpc_t<_>::P60PFS_t mpc_t<_>::P60PFS;
#if defined(SIG_RX72N)
	template<class _> typename mpc_t<_>::P61PFS_t mpc_t<_>::P61PFS;
	template<class _> typename mpc_t<_>::P62PFS_t mpc_t<_>::P62PFS;
	template<class _> typename mpc_t<_>::P63PFS_t mpc_t<_>::P63PFS;
	template<class _> typename mpc_t<_>::P64PFS_t mpc_t<_>::P64PFS;
#endif
	template<class _> typename mpc_t<_>::P66PFS_t mpc_t<_>::P66PFS;
	template<class _> typename mpc_t<_>::P67PFS_t mpc_t<_>::P67PFS;
#elif defined(SIG_RX66T)
	template<class _> typename mpc_t<_>::P60PFS_t mpc_t<_>::P60PFS;
	template<class _> typename mpc_t<_>::P60PFS_t mpc_t<_>::P61PFS;
	template<class _> typename mpc_t<_>::P60PFS_t mpc_t<_>::P62PFS;
	template<class _> typename mpc_t<_>::P60PFS_t mpc_t<_>::P63PFS;
	template<class _> typename mpc_t<_>::P60PFS_t mpc_t<_>::P64PFS;
	template<class _> typename mpc_t<_>::P60PFS_t mpc_t<_>::P65PFS;
#endif
	template<class _> typename mpc_t<_>::P71PFS_t mpc_t<_>::P71PFS;
	template<class _> typename mpc_t<_>::P72PFS_t mpc_t<_>::P72PFS;
	template<class _> typename mpc_t<_>::P73PFS_t mpc_t<_>::P73PFS;
	template<class _> typename mpc_t<_>::P74PFS_t mpc_t<_>::P74PFS;
	template<class _> typename mpc_t<_>::P75PFS_t mpc_t<_>::P75PFS;
	template<class _> typename mpc_t<_>::P76PFS_t mpc_t<_>::P76PFS;
	template<class _> typename mpc_t<_>::P77PFS_t mpc_t<_>::P77PFS;

	template<class _> typename mpc_t<_>::P80PFS_t mpc_t<_>::P80PFS;
	template<class _> typename mpc_t<_>::P81PFS_t mpc_t<_>::P81PFS;
	template<class _> typename mpc_t<_>::P82PFS_t mpc_t<_>::P82PFS;
	template<class _> typename mpc_t<_>::P83PFS_t mpc_t<_>::P83PFS;
	template<class _> typename mpc_t<_>::P84PFS_t mpc_t<_>::P84PFS;
	template<class _> typename mpc_t<_>::P85PFS_t mpc_t<_>::P85PFS;
	template<class _> typename mpc_t<_>::P86PFS_t mpc_t<_>::P86PFS;
	template<class _> typename mpc_t<_>::P87PFS_t mpc_t<_>::P87PFS;

	template<class _> typename mpc_t<_>::P90PFS_t mpc_t<_>::P90PFS;
	template<class _> typename mpc_t<_>::P91PFS_t mpc_t<_>::P91PFS;
	template<class _> typename mpc_t<_>::P92PFS_t mpc_t<_>::P92PFS;
	template<class _> typename mpc_t<_>::P93PFS_t mpc_t<_>::P93PFS;
	template<class _> typename mpc_t<_>::P94PFS_t mpc_t<_>::P94PFS;
	template<class _> typename mpc_t<_>::P95PFS_t mpc_t<_>::P95PFS;
	template<class _> typename mpc_t<_>::P96PFS_t mpc_t<_>::P96PFS;
	template<class _> typename mpc_t<_>::P97PFS_t mpc_t<_>::P97PFS;

	template<class _> typename mpc_t<_>::PA0PFS_t mpc_t<_>::PA0PFS;
	template<class _> typename mpc_t<_>::PA1PFS_t mpc_t<_>::PA1PFS;
	template<class _> typename mpc_t<_>::PA2PFS_t mpc_t<_>::PA2PFS;
	template<class _> typename mpc_t<_>::PA3PFS_t mpc_t<_>::PA3PFS;
	template<class _> typename mpc_t<_>::PA4PFS_t mpc_t<_>::PA4PFS;
	template<class _> typename mpc_t<_>::PA5PFS_t mpc_t<_>::PA5PFS;
	template<class _> typename mpc_t<_>::PA6PFS_t mpc_t<_>::PA6PFS;
	template<class _> typename mpc_t<_>::PA7PFS_t mpc_t<_>::PA7PFS;

	template<class _> typename mpc_t<_>::PB0PFS_t mpc_t<_>::PB0PFS;
	template<class _> typename mpc_t<_>::PB1PFS_t mpc_t<_>::PB1PFS;
	template<class _> typename mpc_t<_>::PB2PFS_t mpc_t<_>::PB2PFS;
	template<class _> typename mpc_t<_>::PB3PFS_t mpc_t<_>::PB3PFS;
	template<class _> typename mpc_t<_>::PB4PFS_t mpc_t<_>::PB4PFS;
	template<class _> typename mpc_t<_>::PB5PFS_t mpc_t<_>::PB5PFS;
	template<class _> typename mpc_t<_>::PB6PFS_t mpc_t<_>::PB6PFS;
	template<class _> typename mpc_t<_>::PB7PFS_t mpc_t<_>::PB7PFS;

	template<class _> typename mpc_t<_>::PC0PFS_t mpc_t<_>::PC0PFS;
	template<class _> typename mpc_t<_>::PC1PFS_t mpc_t<_>::PC1PFS;
	template<class _> typename mpc_t<_>::PC2PFS_t mpc_t<_>::PC2PFS;
	template<class _> typename mpc_t<_>::PC3PFS_t mpc_t<_>::PC3PFS;
	template<class _> typename mpc_t<_>::PC4PFS_t mpc_t<_>::PC4PFS;
	template<class _> typename mpc_t<_>::PC5PFS_t mpc_t<_>::PC5PFS;
	template<class _> typename mpc_t<_>::PC6PFS_t mpc_t<_>::PC6PFS;
	template<class _> typename mpc_t<_>::PC7PFS_t mpc_t<_>::PC7PFS;

	template<class _> typename mpc_t<_>::PD0PFS_t mpc_t<_>::PD0PFS;
	template<class _> typename mpc_t<_>::PD1PFS_t mpc_t<_>::PD1PFS;
	template<class _> typename mpc_t<_>::PD2PFS_t mpc_t<_>::PD2PFS;
	template<class _> typename mpc_t<_>::PD3PFS_t mpc_t<_>::PD3PFS;
	template<class _> typename mpc_t<_>::PD4PFS_t mpc_t<_>::PD4PFS;
	template<class _> typename mpc_t<_>::PD5PFS_t mpc_t<_>::PD5PFS;
	template<class _> typename mpc_t<_>::PD6PFS_t mpc_t<_>::PD6PFS;
	template<class _> typename mpc_t<_>::PD7PFS_t mpc_t<_>::PD7PFS;

	template<class _> typename mpc_t<_>::PE0PFS_t mpc_t<_>::PE0PFS;
	template<class _> typename mpc_t<_>::PE1PFS_t mpc_t<_>::PE1PFS;
	template<class _> typename mpc_t<_>::PE2PFS_t mpc_t<_>::PE2PFS;
	template<class _> typename mpc_t<_>::PE3PFS_t mpc_t<_>::PE3PFS;
	template<class _> typename mpc_t<_>::PE4PFS_t mpc_t<_>::PE4PFS;
	template<class _> typename mpc_t<_>::PE5PFS_t mpc_t<_>::PE5PFS;
	template<class _> typename mpc_t<_>::PE6PFS_t mpc_t<_>::PE6PFS;
	template<class _> typename mpc_t<_>::PE7PFS_t mpc_t<_>::PE7PFS;

	template<class _> typename mpc_t<_>::PF0PFS_t mpc_t<_>::PF0PFS;
	template<class _> typename mpc_t<_>::PF1PFS_t mpc_t<_>::PF1PFS;
	template<class _> typename mpc_t<_>::PF2PFS_t mpc_t<_>::PF2PFS;
	template<class _> typename mpc_t<_>::PF3PFS_t mpc_t<_>::PF3PFS;
	template<class _> typename mpc_t<_>::PF4PFS_t mpc_t<_>::PF4PFS;
	template<class _> typename mpc_t<_>::PF5PFS_t mpc_t<_>::PF5PFS;

	template<class _> typename mpc_t<_>::PG0PFS_t mpc_t<_>::PG0PFS;
	template<class _> typename mpc_t<_>::PG1PFS_t mpc_t<_>::PG1PFS;
	template<class _> typename mpc_t<_>::PG2PFS_t mpc_t<_>::PG2PFS;
	template<class _> typename mpc_t<_>::PG3PFS_t mpc_t<_>::PG3PFS;
	template<class _> typename mpc_t<_>::PG4PFS_t mpc_t<_>::PG4PFS;
	template<class _> typename mpc_t<_>::PG5PFS_t mpc_t<_>::PG5PFS;
	template<class _> typename mpc_t<_>::PG6PFS_t mpc_t<_>::PG6PFS;
	template<class _> typename mpc_t<_>::PG7PFS_t mpc_t<_>::PG7PFS;

#if defined(SIG_RX72N)
	template<class _> typename mpc_t<_>::PJ0PFS_t mpc_t<_>::PJ0PFS;
	template<class _> typename mpc_t<_>::PJ1PFS_t mpc_t<_>::PJ1PFS;
	template<class _> typename mpc_t<_>::PJ2PFS_t mpc_t<_>::PJ2PFS;
#endif
	template<class _> typename mpc_t<_>::PJ3PFS_t mpc_t<_>::PJ3PFS;
	template<class _> typename mpc_t<_>::PJ5PFS_t mpc_t<_>::PJ5PFS;

#if defined(SIG_RX72N)
	template<class _> typename mpc_t<_>::PK0PFS_t mpc_t<_>::PK0PFS;
	template<class _> typename mpc_t<_>::PK1PFS_t mpc_t<_>::PK1PFS;
	template<class _> typename mpc_t<_>::PK2PFS_t mpc_t<_>::PK2PFS;
	template<class _> typename mpc_t<_>::PK3PFS_t mpc_t<_>::PK3PFS;
	template<class _> typename mpc_t<_>::PK4PFS_t mpc_t<_>::PK4PFS;
	template<class _> typename mpc_t<_>::PK5PFS_t mpc_t<_>::PK5PFS;
	template<class _> typename mpc_t<_>::PK6PFS_t mpc_t<_>::PK6PFS;
	template<class _> typename mpc_t<_>::PK7PFS_t mpc_t<_>::PK7PFS;

	template<class _> typename mpc_t<_>::PL0PFS_t mpc_t<_>::PL0PFS;
	template<class _> typename mpc_t<_>::PL1PFS_t mpc_t<_>::PL1PFS;
	template<class _> typename mpc_t<_>::PL2PFS_t mpc_t<_>::PL2PFS;
	template<class _> typename mpc_t<_>::PL3PFS_t mpc_t<_>::PL3PFS;
	template<class _> typename mpc_t<_>::PL4PFS_t mpc_t<_>::PL4PFS;
	template<class _> typename mpc_t<_>::PL5PFS_t mpc_t<_>::PL5PFS;
	template<class _> typename mpc_t<_>::PL6PFS_t mpc_t<_>::PL6PFS;
	template<class _> typename mpc_t<_>::PL7PFS_t mpc_t<_>::PL7PFS;

	template<class _> typename mpc_t<_>::PM0PFS_t mpc_t<_>::PM0PFS;
	template<class _> typename mpc_t<_>::PM1PFS_t mpc_t<_>::PM1PFS;
	template<class _> typename mpc_t<_>::PM2PFS_t mpc_t<_>::PM2PFS;
	template<class _> typename mpc_t<_>::PM3PFS_t mpc_t<_>::PM3PFS;
	template<class _> typename mpc_t<_>::PM4PFS_t mpc_t<_>::PM4PFS;
	template<class _> typename mpc_t<_>::PM5PFS_t mpc_t<_>::PM5PFS;
	template<class _> typename mpc_t<_>::PM6PFS_t mpc_t<_>::PM6PFS;
	template<class _> typename mpc_t<_>::PM7PFS_t mpc_t<_>::PM7PFS;

	template<class _> typename mpc_t<_>::PN0PFS_t mpc_t<_>::PN0PFS;
	template<class _> typename mpc_t<_>::PN1PFS_t mpc_t<_>::PN1PFS;
	template<class _> typename mpc_t<_>::PN2PFS_t mpc_t<_>::PN2PFS;
	template<class _> typename mpc_t<_>::PN3PFS_t mpc_t<_>::PN3PFS;
	template<class _> typename mpc_t<_>::PN4PFS_t mpc_t<_>::PN4PFS;
	template<class _> typename mpc_t<_>::PN5PFS_t mpc_t<_>::PN5PFS;

	template<class _> typename mpc_t<_>::PQ0PFS_t mpc_t<_>::PQ0PFS;
	template<class _> typename mpc_t<_>::PQ1PFS_t mpc_t<_>::PQ1PFS;
	template<class _> typename mpc_t<_>::PQ2PFS_t mpc_t<_>::PQ2PFS;
	template<class _> typename mpc_t<_>::PQ3PFS_t mpc_t<_>::PQ3PFS;
	template<class _> typename mpc_t<_>::PQ4PFS_t mpc_t<_>::PQ4PFS;
	template<class _> typename mpc_t<_>::PQ5PFS_t mpc_t<_>::PQ5PFS;
	template<class _> typename mpc_t<_>::PQ6PFS_t mpc_t<_>::PQ6PFS;
	template<class _> typename mpc_t<_>::PQ7PFS_t mpc_t<_>::PQ7PFS;
#endif

	template<class _> typename mpc_t<_>::PFCSE_t  mpc_t<_>::PFCSE;
	template<class _> typename mpc_t<_>::PFCSS0_t mpc_t<_>::PFCSS0;
	template<class _> typename mpc_t<_>::PFCSS1_t mpc_t<_>::PFCSS1;
	template<class _> typename mpc_t<_>::PFAOE0_t mpc_t<_>::PFAOE0;
	template<class _> typename mpc_t<_>::PFAOE1_t mpc_t<_>::PFAOE1;
	template<class _> typename mpc_t<_>::PFBCR0_t mpc_t<_>::PFBCR0;
	template<class _> typename mpc_t<_>::PFBCR1_t mpc_t<_>::PFBCR1;
#if defined(SIG_RX72N)
	template<class _> typename mpc_t<_>::PFBCR2_t mpc_t<_>::PFBCR2;
	template<class _> typename mpc_t<_>::PFBCR3_t mpc_t<_>::PFBCR3;
#endif
	template<class _> typename mpc_t<_>::PFENET_t mpc_t<_>::PFENET;
}
