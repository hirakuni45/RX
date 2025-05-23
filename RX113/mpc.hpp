#pragma once
//=========================================================================//
/*!	@file
	@brief	Multi-Function Pin Controller / マルチファンクションピンコントローラ (RX113)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
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
			@param[in]	base	ベース・アドレス
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
			@brief  端子機能制御規定クラス ASEL, PSEL
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfs_ap_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bits_rw_t<io, bitpos::B0, 5>  PSEL;

			bit_rw_t< io, bitpos::B7>     ASEL;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  端子機能制御規定クラス ASEL, ISEL, PSEL
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfs_aip_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bits_rw_t<io, bitpos::B0, 5>  PSEL;

			bit_rw_t< io, bitpos::B6>     ISEL;
			bit_rw_t< io, bitpos::B7>     ASEL;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  端子機能制御規定クラス ISEL, PSEL
			@param[in]	base	ベース・アドレス
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
			@brief  端子機能制御規定クラス PSEL
			@param[in]	base	ベース・アドレス
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
			@brief  端子機能制御規定クラス ASEL
			@param[in]	base	ベース・アドレス
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
			@brief  P0n 端子機能制御レジスタ（P0nPFS）（n = 2, 4、7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_p_t<0x0008'C142> P02PFS;
		static inline pfs_p_t<0x0008'C144> P04PFS;
		static inline pfs_p_t<0x0008'C147> P07PFS;


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
			@brief  P3n 端子機能制御レジスタ（P3nPFS）（n = 0 ～ 2）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ip_t<0x0008'C158> P30PFS;
		static inline pfs_ip_t<0x0008'C159> P31PFS;
		static inline pfs_ip_t<0x0008'C15A> P32PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P4n 端子機能制御レジスタ（P4nPFS）（n = 0 ～ 4, 6）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_a_t<0x0008'C160> P40PFS;
		static inline pfs_a_t<0x0008'C161> P41PFS;
		static inline pfs_a_t<0x0008'C162> P42PFS;
		static inline pfs_a_t<0x0008'C163> P43PFS;
		static inline pfs_a_t<0x0008'C164> P44PFS;
		static inline pfs_a_t<0x0008'C166> P46PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P5n 端子機能制御レジスタ（P5nPFS）（n = 0 ～ 6）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ip_t<0x0008'C168> P50PFS;
		static inline pfs_ip_t<0x0008'C169> P51PFS;
		static inline pfs_ip_t<0x0008'C16A> P52PFS;
		static inline pfs_ip_t<0x0008'C16B> P53PFS;
		static inline pfs_ip_t<0x0008'C16C> P54PFS;
		static inline pfs_ip_t<0x0008'C16D> P55PFS;
		static inline pfs_ip_t<0x0008'C16E> P56PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P9n 端子機能制御レジスタ（P9nPFS）（n = 0 ～ 2）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_a_t<0x0008'C188> P90PFS;
		static inline pfs_a_t<0x0008'C189> P91PFS;
		static inline pfs_a_t<0x0008'C18A> P92PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PAn 端子機能制御レジスタ（PAnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_aip_t<0x0008'C190> PA0PFS;
		static inline pfs_aip_t<0x0008'C191> PA1PFS;
		static inline pfs_aip_t<0x0008'C192> PA2PFS;
		static inline pfs_aip_t<0x0008'C193> PA3PFS;
		static inline pfs_aip_t<0x0008'C194> PA4PFS;
		static inline pfs_aip_t<0x0008'C195> PA5PFS;
		static inline pfs_aip_t<0x0008'C196> PA6PFS;
		static inline pfs_aip_t<0x0008'C197> PA7PFS;


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
			@brief  PCn 端子機能制御レジスタ（PCnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ip_t<0x0008'C1A0> PC0PFS;
		static inline pfs_ip_t<0x0008'C1A1> PC1PFS;
		static inline pfs_ip_t<0x0008'C1A2> PC2PFS;
		static inline pfs_ip_t<0x0008'C1A3> PC3PFS;
		static inline pfs_ip_t<0x0008'C1A4> PC4PFS;
		static inline pfs_ip_t<0x0008'C1A5> PC5PFS;
		static inline pfs_ip_t<0x0008'C1A6> PC6PFS;
		static inline pfs_ip_t<0x0008'C1A7> PC7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PDn 端子機能制御レジスタ（PDnPFS）（n = 0 ～ 4）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ip_t<0x0008'C1A8> PD0PFS;
		static inline pfs_ip_t<0x0008'C1A9> PD1PFS;
		static inline pfs_ip_t<0x0008'C1AA> PD2PFS;
		static inline pfs_ip_t<0x0008'C1AB> PD3PFS;
		static inline pfs_ip_t<0x0008'C1AC> PD4PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PEn 端子機能制御レジスタ（PEnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_aip_t<0x0008'C1B0> PE0PFS;
		static inline pfs_aip_t<0x0008'C1B1> PE1PFS;
		static inline pfs_aip_t<0x0008'C1B2> PE2PFS;
		static inline pfs_aip_t<0x0008'C1B3> PE3PFS;
		static inline pfs_aip_t<0x0008'C1B4> PE4PFS;
		static inline pfs_aip_t<0x0008'C1B5> PE5PFS;
		static inline pfs_aip_t<0x0008'C1B6> PE6PFS;
		static inline pfs_aip_t<0x0008'C1B7> PE7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PFn 端子機能制御レジスタ（PFnPFS）（n = 6, 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_p_t<0x0008'C1BE> PF6PFS;
		static inline pfs_p_t<0x0008'C1BF> PF7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PJn 端子機能制御レジスタ（PJnPFS）（n = 0, 2, 3, 6, 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline pfs_ap_t<0x0008'C1D0> PJ0PFS;
		static inline pfs_ap_t<0x0008'C1D2> PJ2PFS;
		static inline pfs_ap_t<0x0008'C1D3> PJ3PFS;
		static inline pfs_ap_t<0x0008'C1D6> PJ6PFS;
		static inline pfs_ap_t<0x0008'C1D7> PJ7PFS;
	};
	typedef mpc_t MPC;
}
