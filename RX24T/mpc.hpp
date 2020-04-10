#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ MPC 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
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
	struct mpc_t_ {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  書き込みプロテクトレジスタ (PWPR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pwpr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B6> PFSWE;
			bit_rw_t<io_, bitpos::B7> B0WI;
		};
		typedef pwpr_t_<0x0008C11F> pwpr_t;
		static pwpr_t PWPR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  端子機能制御規定クラス X
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfsx_t_ : public rw8_t<base> {
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
		struct pfsy_t_ : public rw8_t<base> {
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
		struct pfsz_t_ : public rw8_t<base> {
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
		struct pfsw_t_ : public rw8_t<base> {
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
		struct pfsm_t_ : public rw8_t<base> {
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
		typedef pfsx_t_<0x0008C140> p00pfs_t;
		static p00pfs_t P00PFS;
		typedef pfsx_t_<0x0008C141> p01pfs_t;
		static p01pfs_t P01PFS;
		typedef pfsx_t_<0x0008C142> p02pfs_t;
		static p02pfs_t P02PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P1n 端子機能制御レジスタ（P1nPFS）（n = 0, 1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsx_t_<0x0008C148> p10pfs_t;
		static p10pfs_t P10PFS;
		typedef pfsx_t_<0x0008C149> p11pfs_t;
		static p11pfs_t P11PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P2n 端子機能制御レジスタ（P2nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsy_t_<0x0008C150> p20pfs_t;
		static p20pfs_t P20PFS;
		typedef pfsy_t_<0x0008C151> p21pfs_t;
		static p21pfs_t P21PFS;
		typedef pfsy_t_<0x0008C152> p22pfs_t;
		static p22pfs_t P22PFS;
		typedef pfsy_t_<0x0008C153> p23pfs_t;
		static p23pfs_t P23PFS;
		typedef pfsy_t_<0x0008C154> p24pfs_t;
		static p24pfs_t P24PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P3n 端子機能制御レジスタ（P3nPFS）（n = 0 ～ 4）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsx_t_<0x0008C158> p30pfs_t;
		static p30pfs_t P30PFS;
		typedef pfsx_t_<0x0008C159> p31pfs_t;
		static p31pfs_t P31PFS;
		typedef pfsx_t_<0x0008C15A> p32pfs_t;
		static p32pfs_t P32PFS;
		typedef pfsx_t_<0x0008C15B> p33pfs_t;
		static p33pfs_t P33PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P4n 端子機能制御レジスタ（P4nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsz_t_<0x0008C160> p40pfs_t;
		static p40pfs_t P40PFS;
		typedef pfsz_t_<0x0008C161> p41pfs_t;
		static p41pfs_t P41PFS;
		typedef pfsz_t_<0x0008C162> p42pfs_t;
		static p42pfs_t P42PFS;
		typedef pfsz_t_<0x0008C163> p43pfs_t;
		static p43pfs_t P43PFS;
		typedef pfsz_t_<0x0008C164> p44pfs_t;
		static p44pfs_t P44PFS;
		typedef pfsz_t_<0x0008C165> p45pfs_t;
		static p45pfs_t P45PFS;
		typedef pfsz_t_<0x0008C166> p46pfs_t;
		static p46pfs_t P46PFS;
		typedef pfsz_t_<0x0008C167> p47pfs_t;
		static p47pfs_t P47PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P5n 端子機能制御レジスタ（P5nPFS）（n = 0 ～ 5）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsw_t_<0x0008C168> p50pfs_t;
		static p50pfs_t P50PFS;
		typedef pfsw_t_<0x0008C169> p51pfs_t;
		static p51pfs_t P51PFS;
		typedef pfsw_t_<0x0008C16A> p52pfs_t;
		static p52pfs_t P52PFS;
		typedef pfsw_t_<0x0008C16B> p53pfs_t;
		static p53pfs_t P53PFS;
		typedef pfsw_t_<0x0008C16C> p54pfs_t;
		static p54pfs_t P54PFS;
		typedef pfsw_t_<0x0008C16D> p55pfs_t;
		static p55pfs_t P55PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P6n 端子機能制御レジスタ（P6nPFS）（n = 0 ～ 5）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsw_t_<0x0008C170> p60pfs_t;
		static p60pfs_t P60PFS;
		typedef pfsw_t_<0x0008C171> p61pfs_t;
		static p61pfs_t P61PFS;
		typedef pfsw_t_<0x0008C172> p62pfs_t;
		static p62pfs_t P62PFS;
		typedef pfsw_t_<0x0008C173> p63pfs_t;
		static p63pfs_t P63PFS;
		typedef pfsw_t_<0x0008C174> p64pfs_t;
		static p64pfs_t P64PFS;
		typedef pfsw_t_<0x0008C175> p65pfs_t;
		static p65pfs_t P65PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P7n 端子機能制御レジスタ（P7nPFS）（n = 1 ～ 6）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsx_t_<0x0008C179> p71pfs_t;
		static p71pfs_t P71PFS;
		typedef pfsx_t_<0x0008C17A> p72pfs_t;
		static p72pfs_t P72PFS;
		typedef pfsx_t_<0x0008C17B> p73pfs_t;
		static p73pfs_t P73PFS;
		typedef pfsx_t_<0x0008C17C> p74pfs_t;
		static p74pfs_t P74PFS;
		typedef pfsx_t_<0x0008C17D> p75pfs_t;
		static p75pfs_t P75PFS;
		typedef pfsx_t_<0x0008C17E> p76pfs_t;
		static p76pfs_t P76PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P8n 端子機能制御レジスタ（P8nPFS）（n = 0 ～ 2）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsm_t_<0x0008C180> p80pfs_t;
		static p80pfs_t P80PFS;
		typedef pfsm_t_<0x0008C181> p81pfs_t;
		static p81pfs_t P81PFS;
		typedef pfsm_t_<0x0008C182> p82pfs_t;
		static p82pfs_t P82PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P9n 端子機能制御レジスタ（P9nPFS）（n = 0 ～ 6）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsx_t_<0x0008C188> p90pfs_t;
		static p90pfs_t P90PFS;
		typedef pfsx_t_<0x0008C189> p91pfs_t;
		static p91pfs_t P91PFS;
		typedef pfsx_t_<0x0008C18A> p92pfs_t;
		static p92pfs_t P92PFS;
		typedef pfsx_t_<0x0008C18B> p93pfs_t;
		static p93pfs_t P93PFS;
		typedef pfsx_t_<0x0008C18C> p94pfs_t;
		static p94pfs_t P94PFS;
		typedef pfsx_t_<0x0008C18D> p95pfs_t;
		static p95pfs_t P95PFS;
		typedef pfsx_t_<0x0008C18E> p96pfs_t;
		static p96pfs_t P96PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PAn 端子機能制御レジスタ（PAnPFS）（n = 0 ～ 5）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsx_t_<0x0008C190> pa0pfs_t;
		static pa0pfs_t PA0PFS;
		typedef pfsx_t_<0x0008C191> pa1pfs_t;
		static pa1pfs_t PA1PFS;
		typedef pfsx_t_<0x0008C192> pa2pfs_t;
		static pa2pfs_t PA2PFS;
		typedef pfsx_t_<0x0008C193> pa3pfs_t;
		static pa3pfs_t PA3PFS;
		typedef pfsx_t_<0x0008C194> pa4pfs_t;
		static pa4pfs_t PA4PFS;
		typedef pfsx_t_<0x0008C195> pa5pfs_t;
		static pa5pfs_t PA5PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PBn 端子機能制御レジスタ（PBnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsx_t_<0x0008C198> pb0pfs_t;
		static pb0pfs_t PB0PFS;
		typedef pfsx_t_<0x0008C199> pb1pfs_t;
		static pb1pfs_t PB1PFS;
		typedef pfsx_t_<0x0008C19A> pb2pfs_t;
		static pb2pfs_t PB2PFS;
		typedef pfsx_t_<0x0008C19B> pb3pfs_t;
		static pb3pfs_t PB3PFS;
		typedef pfsx_t_<0x0008C19C> pb4pfs_t;
		static pb4pfs_t PB4PFS;
		typedef pfsx_t_<0x0008C19D> pb5pfs_t;
		static pb5pfs_t PB5PFS;
		typedef pfsx_t_<0x0008C19E> pb6pfs_t;
		static pb6pfs_t PB6PFS;
		typedef pfsx_t_<0x0008C19F> pb7pfs_t;
		static pb7pfs_t PB7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PDn 端子機能制御レジスタ（PDnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsx_t_<0x0008C1A8> pd0pfs_t;
		static pd0pfs_t PD0PFS;
		typedef pfsx_t_<0x0008C1A9> pd1pfs_t;
		static pd1pfs_t PD1PFS;
		typedef pfsx_t_<0x0008C1AA> pd2pfs_t;
		static pd2pfs_t PD2PFS;
		typedef pfsx_t_<0x0008C1AB> pd3pfs_t;
		static pd3pfs_t PD3PFS;
		typedef pfsx_t_<0x0008C1AC> pd4pfs_t;
		static pd4pfs_t PD4PFS;
		typedef pfsx_t_<0x0008C1AD> pd5pfs_t;
		static pd5pfs_t PD5PFS;
		typedef pfsx_t_<0x0008C1AE> pd6pfs_t;
		static pd6pfs_t PD6PFS;
		typedef pfsx_t_<0x0008C1AF> pd7pfs_t;
		static pd7pfs_t PD7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PEn 端子機能制御レジスタ（PEnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsx_t_<0x0008C1B0> pe0pfs_t;
		static pe0pfs_t PE0PFS;
		typedef pfsx_t_<0x0008C1B1> pe1pfs_t;
		static pe1pfs_t PE1PFS;
		typedef pfsx_t_<0x0008C1B2> pe2pfs_t;
		static pe2pfs_t PE2PFS;
		typedef pfsx_t_<0x0008C1B3> pe3pfs_t;
		static pe3pfs_t PE3PFS;
		typedef pfsx_t_<0x0008C1B4> pe4pfs_t;
		static pe4pfs_t PE4PFS;
		typedef pfsx_t_<0x0008C1B5> pe5pfs_t;
		static pe5pfs_t PE5PFS;

	};
	typedef mpc_t_<void> MPC;

	template<class _> typename mpc_t_<_>::pwpr_t mpc_t_<_>::PWPR;
	template<class _> typename mpc_t_<_>::p00pfs_t mpc_t_<_>::P00PFS;
	template<class _> typename mpc_t_<_>::p01pfs_t mpc_t_<_>::P01PFS;
	template<class _> typename mpc_t_<_>::p02pfs_t mpc_t_<_>::P02PFS;
	template<class _> typename mpc_t_<_>::p10pfs_t mpc_t_<_>::P10PFS;
	template<class _> typename mpc_t_<_>::p11pfs_t mpc_t_<_>::P11PFS;
	template<class _> typename mpc_t_<_>::p20pfs_t mpc_t_<_>::P20PFS;
	template<class _> typename mpc_t_<_>::p21pfs_t mpc_t_<_>::P21PFS;
	template<class _> typename mpc_t_<_>::p22pfs_t mpc_t_<_>::P22PFS;
	template<class _> typename mpc_t_<_>::p23pfs_t mpc_t_<_>::P23PFS;
	template<class _> typename mpc_t_<_>::p24pfs_t mpc_t_<_>::P24PFS;
	template<class _> typename mpc_t_<_>::p30pfs_t mpc_t_<_>::P30PFS;
	template<class _> typename mpc_t_<_>::p31pfs_t mpc_t_<_>::P31PFS;
	template<class _> typename mpc_t_<_>::p32pfs_t mpc_t_<_>::P32PFS;
	template<class _> typename mpc_t_<_>::p33pfs_t mpc_t_<_>::P33PFS;
	template<class _> typename mpc_t_<_>::p40pfs_t mpc_t_<_>::P40PFS;
	template<class _> typename mpc_t_<_>::p41pfs_t mpc_t_<_>::P41PFS;
	template<class _> typename mpc_t_<_>::p42pfs_t mpc_t_<_>::P42PFS;
	template<class _> typename mpc_t_<_>::p43pfs_t mpc_t_<_>::P43PFS;
	template<class _> typename mpc_t_<_>::p44pfs_t mpc_t_<_>::P44PFS;
	template<class _> typename mpc_t_<_>::p45pfs_t mpc_t_<_>::P45PFS;
	template<class _> typename mpc_t_<_>::p46pfs_t mpc_t_<_>::P46PFS;
	template<class _> typename mpc_t_<_>::p47pfs_t mpc_t_<_>::P47PFS;
	template<class _> typename mpc_t_<_>::p50pfs_t mpc_t_<_>::P50PFS;
	template<class _> typename mpc_t_<_>::p51pfs_t mpc_t_<_>::P51PFS;
	template<class _> typename mpc_t_<_>::p52pfs_t mpc_t_<_>::P52PFS;
	template<class _> typename mpc_t_<_>::p53pfs_t mpc_t_<_>::P53PFS;
	template<class _> typename mpc_t_<_>::p54pfs_t mpc_t_<_>::P54PFS;
	template<class _> typename mpc_t_<_>::p55pfs_t mpc_t_<_>::P55PFS;
	template<class _> typename mpc_t_<_>::p60pfs_t mpc_t_<_>::P60PFS;
	template<class _> typename mpc_t_<_>::p61pfs_t mpc_t_<_>::P61PFS;
	template<class _> typename mpc_t_<_>::p62pfs_t mpc_t_<_>::P62PFS;
	template<class _> typename mpc_t_<_>::p63pfs_t mpc_t_<_>::P63PFS;
	template<class _> typename mpc_t_<_>::p64pfs_t mpc_t_<_>::P64PFS;
	template<class _> typename mpc_t_<_>::p65pfs_t mpc_t_<_>::P65PFS;
	template<class _> typename mpc_t_<_>::p71pfs_t mpc_t_<_>::P71PFS;
	template<class _> typename mpc_t_<_>::p72pfs_t mpc_t_<_>::P72PFS;
	template<class _> typename mpc_t_<_>::p73pfs_t mpc_t_<_>::P73PFS;
	template<class _> typename mpc_t_<_>::p74pfs_t mpc_t_<_>::P74PFS;
	template<class _> typename mpc_t_<_>::p75pfs_t mpc_t_<_>::P75PFS;
	template<class _> typename mpc_t_<_>::p76pfs_t mpc_t_<_>::P76PFS;
	template<class _> typename mpc_t_<_>::p80pfs_t mpc_t_<_>::P80PFS;
	template<class _> typename mpc_t_<_>::p81pfs_t mpc_t_<_>::P81PFS;
	template<class _> typename mpc_t_<_>::p82pfs_t mpc_t_<_>::P82PFS;
	template<class _> typename mpc_t_<_>::p90pfs_t mpc_t_<_>::P90PFS;
	template<class _> typename mpc_t_<_>::p91pfs_t mpc_t_<_>::P91PFS;
	template<class _> typename mpc_t_<_>::p92pfs_t mpc_t_<_>::P92PFS;
	template<class _> typename mpc_t_<_>::p93pfs_t mpc_t_<_>::P93PFS;
	template<class _> typename mpc_t_<_>::p94pfs_t mpc_t_<_>::P94PFS;
	template<class _> typename mpc_t_<_>::p95pfs_t mpc_t_<_>::P95PFS;
	template<class _> typename mpc_t_<_>::p96pfs_t mpc_t_<_>::P96PFS;
	template<class _> typename mpc_t_<_>::pa0pfs_t mpc_t_<_>::PA0PFS;
	template<class _> typename mpc_t_<_>::pa1pfs_t mpc_t_<_>::PA1PFS;
	template<class _> typename mpc_t_<_>::pa2pfs_t mpc_t_<_>::PA2PFS;
	template<class _> typename mpc_t_<_>::pa3pfs_t mpc_t_<_>::PA3PFS;
	template<class _> typename mpc_t_<_>::pa4pfs_t mpc_t_<_>::PA4PFS;
	template<class _> typename mpc_t_<_>::pa5pfs_t mpc_t_<_>::PA5PFS;
	template<class _> typename mpc_t_<_>::pb0pfs_t mpc_t_<_>::PB0PFS;
	template<class _> typename mpc_t_<_>::pb1pfs_t mpc_t_<_>::PB1PFS;
	template<class _> typename mpc_t_<_>::pb2pfs_t mpc_t_<_>::PB2PFS;
	template<class _> typename mpc_t_<_>::pb3pfs_t mpc_t_<_>::PB3PFS;
	template<class _> typename mpc_t_<_>::pb4pfs_t mpc_t_<_>::PB4PFS;
	template<class _> typename mpc_t_<_>::pb5pfs_t mpc_t_<_>::PB5PFS;
	template<class _> typename mpc_t_<_>::pb6pfs_t mpc_t_<_>::PB6PFS;
	template<class _> typename mpc_t_<_>::pb7pfs_t mpc_t_<_>::PB7PFS;
	template<class _> typename mpc_t_<_>::pd0pfs_t mpc_t_<_>::PD0PFS;
	template<class _> typename mpc_t_<_>::pd1pfs_t mpc_t_<_>::PD1PFS;
	template<class _> typename mpc_t_<_>::pd2pfs_t mpc_t_<_>::PD2PFS;
	template<class _> typename mpc_t_<_>::pd3pfs_t mpc_t_<_>::PD3PFS;
	template<class _> typename mpc_t_<_>::pd4pfs_t mpc_t_<_>::PD4PFS;
	template<class _> typename mpc_t_<_>::pd5pfs_t mpc_t_<_>::PD5PFS;
	template<class _> typename mpc_t_<_>::pd6pfs_t mpc_t_<_>::PD6PFS;
	template<class _> typename mpc_t_<_>::pd7pfs_t mpc_t_<_>::PD7PFS;
	template<class _> typename mpc_t_<_>::pe0pfs_t mpc_t_<_>::PE0PFS;
	template<class _> typename mpc_t_<_>::pe1pfs_t mpc_t_<_>::PE1PFS;
	template<class _> typename mpc_t_<_>::pe2pfs_t mpc_t_<_>::PE2PFS;
	template<class _> typename mpc_t_<_>::pe3pfs_t mpc_t_<_>::PE3PFS;
	template<class _> typename mpc_t_<_>::pe4pfs_t mpc_t_<_>::PE4PFS;
	template<class _> typename mpc_t_<_>::pe5pfs_t mpc_t_<_>::PE5PFS;
}
