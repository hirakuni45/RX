#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ MPC 定義 @n
			Copyright 2016 Kunihito Hiramatsu
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
		static pwpr_t<0x0008C11F> PWPR;


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

			bits_rw_t<io, bitpos::B0, 5>  PSEL;
			bit_rw_t< io, bitpos::B6>     ISEL;
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

			bits_rw_t<io, bitpos::B0, 5>  PSEL;
			bit_rw_t<io, bitpos::B6>      ISEL;
			bit_rw_t<io, bitpos::B6>      ASEL;
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

			bit_rw_t<io, bitpos::B7>      ASEL;
		};


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

			bits_rw_t<io, bitpos::B6, 6>  ISEL;
			bits_rw_t<io, bitpos::B7, 6>  ASEL;
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

			bits_rw_t<io, bitpos::B0, 5>  PSEL;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P0n 端子機能制御レジスタ（P0nPFS）（n = 0 ～ 3, 5, 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsx_t<0x0008C140> P00PFS;
		static pfsx_t<0x0008C141> P01PFS;
		static pfsx_t<0x0008C142> P02PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P1n 端子機能制御レジスタ（P1nPFS）（n = 0, 1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsx_t<0x0008C148> P10PFS;
		static pfsx_t<0x0008C149> P11PFS;


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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P3n 端子機能制御レジスタ（P3nPFS）（n = 0 ～ 4）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsx_t<0x0008C158> P30PFS;
		static pfsx_t<0x0008C159> P31PFS;
		static pfsx_t<0x0008C15A> P32PFS;
		static pfsx_t<0x0008C15B> P33PFS;


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
			@brief  P5n 端子機能制御レジスタ（P5nPFS）（n = 0 ～ 5）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsw_t<0x0008C168> P50PFS;
		static pfsw_t<0x0008C169> P51PFS;
		static pfsw_t<0x0008C16A> P52PFS;
		static pfsw_t<0x0008C16C> P54PFS;
		static pfsw_t<0x0008C16D> P55PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P6n 端子機能制御レジスタ（P6nPFS）（n = 0 ～ 5）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsw_t<0x0008C170> P60PFS;
		static pfsw_t<0x0008C171> P61PFS;
		static pfsw_t<0x0008C172> P62PFS;
		static pfsw_t<0x0008C173> P63PFS;
		static pfsw_t<0x0008C174> P64PFS;
		static pfsw_t<0x0008C175> P65PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P7n 端子機能制御レジスタ（P7nPFS）（n = 1 ～ 6）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsx_t<0x0008C179> P71PFS;
		static pfsx_t<0x0008C17A> P72PFS;
		static pfsx_t<0x0008C17B> P73PFS;
		static pfsx_t<0x0008C17C> P74PFS;
		static pfsx_t<0x0008C17D> P75PFS;
		static pfsx_t<0x0008C17E> P76PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P8n 端子機能制御レジスタ（P8nPFS）（n = 0 ～ 2）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsm_t<0x0008C180> P80PFS;
		static pfsm_t<0x0008C181> P81PFS;
		static pfsm_t<0x0008C182> P82PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P9n 端子機能制御レジスタ（P9nPFS）（n = 0 ～ 6）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsx_t<0x0008C188> P90PFS;
		static pfsx_t<0x0008C189> P91PFS;
		static pfsx_t<0x0008C18A> P92PFS;
		static pfsx_t<0x0008C18B> P93PFS;
		static pfsx_t<0x0008C18C> P94PFS;
		static pfsx_t<0x0008C18D> P95PFS;
		static pfsx_t<0x0008C18E> P96PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PAn 端子機能制御レジスタ（PAnPFS）（n = 0 ～ 5）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsx_t<0x0008C190> PA0PFS;
		static pfsx_t<0x0008C191> PA1PFS;
		static pfsx_t<0x0008C192> PA2PFS;
		static pfsx_t<0x0008C193> PA3PFS;
		static pfsx_t<0x0008C194> PA4PFS;
		static pfsx_t<0x0008C195> PA5PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PBn 端子機能制御レジスタ（PBnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsx_t<0x0008C198> PB0PFS;
		static pfsx_t<0x0008C199> PB1PFS;
		static pfsx_t<0x0008C19A> PB2PFS;
		static pfsx_t<0x0008C19B> PB3PFS;
		static pfsx_t<0x0008C19C> PB4PFS;
		static pfsx_t<0x0008C19D> PB5PFS;
		static pfsx_t<0x0008C19E> PB6PFS;
		static pfsx_t<0x0008C19F> PB7PFS;


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

	};
	typedef mpc_t MPC;
}
