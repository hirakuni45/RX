#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ MPC 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2013, 2018 Kunihito Hiramatsu @n
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
			@param[in]	base	アドレス
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
			@brief  端子機能制御規定クラス W
			@param[in]	base	アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfsw_t_ : public rw8_t<base> {
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
		struct pfsm_t_ : public rw8_t<base> {
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
		struct pfsx_t_ : public rw8_t<base> {
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
		struct pfsy_t_ : public rw8_t<base> {
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
		struct pfsz_t_ : public rw8_t<base> {
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
		typedef pfsx_t_<0x0008C140> p00pfs_t;
		static p00pfs_t P00PFS;
		typedef pfsx_t_<0x0008C141> p01pfs_t;
		static p01pfs_t P01PFS;
		typedef pfsx_t_<0x0008C142> p02pfs_t;
		static p02pfs_t P02PFS;
		typedef pfsx_t_<0x0008C143> p03pfs_t;
		static p03pfs_t P03PFS;
		typedef pfsx_t_<0x0008C145> p05pfs_t;
		static p05pfs_t P05PFS;
		typedef pfsx_t_<0x0008C147> p07pfs_t;
		static p07pfs_t P07PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P1n 端子機能制御レジスタ（P1nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsy_t_<0x0008C148> p10pfs_t;
		static p10pfs_t P10PFS;
		typedef pfsy_t_<0x0008C149> p11pfs_t;
		static p11pfs_t P11PFS;
		typedef pfsy_t_<0x0008C14A> p12pfs_t;
		static p12pfs_t P12PFS;
		typedef pfsy_t_<0x0008C14B> p13pfs_t;
		static p13pfs_t P13PFS;
		typedef pfsy_t_<0x0008C14C> p14pfs_t;
		static p14pfs_t P14PFS;
		typedef pfsy_t_<0x0008C14D> p15pfs_t;
		static p15pfs_t P15PFS;
		typedef pfsy_t_<0x0008C14E> p16pfs_t;
		static p16pfs_t P16PFS;
		typedef pfsy_t_<0x0008C14F> p17pfs_t;
		static p17pfs_t P17PFS;


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
		typedef pfsy_t_<0x0008C155> p25pfs_t;
		static p25pfs_t P25PFS;
		typedef pfsy_t_<0x0008C156> p26pfs_t;
		static p26pfs_t P26PFS;
		typedef pfsy_t_<0x0008C157> p27pfs_t;
		static p27pfs_t P27PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P3n 端子機能制御レジスタ（P3nPFS）（n = 0 ～ 4）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsy_t_<0x0008C158> p30pfs_t;
		static p30pfs_t P30PFS;
		typedef pfsy_t_<0x0008C159> p31pfs_t;
		static p31pfs_t P31PFS;
		typedef pfsy_t_<0x0008C15A> p32pfs_t;
		static p32pfs_t P32PFS;
		typedef pfsy_t_<0x0008C15B> p33pfs_t;
		static p33pfs_t P33PFS;
		typedef pfsy_t_<0x0008C15C> p34pfs_t;
		static p34pfs_t P34PFS;


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
			@brief  P5n 端子機能制御レジスタ（P5nPFS）（n = 0 ～ 2, 4 ～ 6）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsy_t_<0x0008C168> p50pfs_t;
		static p50pfs_t P50PFS;
		typedef pfsy_t_<0x0008C169> p51pfs_t;
		static p51pfs_t P51PFS;
		typedef pfsy_t_<0x0008C16A> p52pfs_t;
		static p52pfs_t P52PFS;
		typedef pfsy_t_<0x0008C16C> p54pfs_t;
		static p54pfs_t P54PFS;
		typedef pfsy_t_<0x0008C16D> p55pfs_t;
		static p55pfs_t P55PFS;
		typedef pfsy_t_<0x0008C16E> p56pfs_t;
		static p56pfs_t P56PFS;
		typedef pfsy_t_<0x0008C16F> p57pfs_t;
		static p57pfs_t P57PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P6n 端子機能制御レジスタ（P6nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
		typedef pfsy_t_<0x0008C170> p60pfs_t;
		static p60pfs_t P60PFS;
		typedef pfsy_t_<0x0008C176> p66pfs_t;
		static p66pfs_t P66PFS;
		typedef pfsy_t_<0x0008C177> p67pfs_t;
		static p67pfs_t P67PFS;
#elif defined(SIG_RX66T)
		typedef pfsz_t_<0x0008C170> p60pfs_t;
		static p60pfs_t P60PFS;
		typedef pfsz_t_<0x0008C171> p61pfs_t;
		static p61pfs_t P61PFS;
		typedef pfsz_t_<0x0008C172> p62pfs_t;
		static p62pfs_t P62PFS;
		typedef pfsz_t_<0x0008C173> p63pfs_t;
		static p63pfs_t P63PFS;
		typedef pfsz_t_<0x0008C174> p64pfs_t;
		static p64pfs_t P64PFS;
		typedef pfsz_t_<0x0008C175> p65pfs_t;
		static p65pfs_t P65PFS;
#endif

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P7n 端子機能制御レジスタ（P7nPFS）（n = 1 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsw_t_<0x0008C179> p71pfs_t;
		static p71pfs_t P71PFS;
		typedef pfsw_t_<0x0008C17A> p72pfs_t;
		static p72pfs_t P72PFS;
		typedef pfsw_t_<0x0008C17B> p73pfs_t;
		static p73pfs_t P73PFS;
		typedef pfsw_t_<0x0008C17C> p74pfs_t;
		static p74pfs_t P74PFS;
		typedef pfsw_t_<0x0008C17D> p75pfs_t;
		static p75pfs_t P75PFS;
		typedef pfsw_t_<0x0008C17E> p76pfs_t;
		static p76pfs_t P76PFS;
		typedef pfsw_t_<0x0008C17F> p77pfs_t;
		static p77pfs_t P77PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P8n 端子機能制御レジスタ（P8nPFS）（n = 0 ～ 3, 6, 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsw_t_<0x0008C180> p80pfs_t;
		static p80pfs_t P80PFS;
		typedef pfsw_t_<0x0008C181> p81pfs_t;
		static p81pfs_t P81PFS;
		typedef pfsw_t_<0x0008C182> p82pfs_t;
		static p82pfs_t P82PFS;
		typedef pfsw_t_<0x0008C183> p83pfs_t;
		static p83pfs_t P83PFS;
		typedef pfsw_t_<0x0008C184> p84pfs_t;
		static p84pfs_t P84PFS;
		typedef pfsw_t_<0x0008C185> p85pfs_t;
		static p85pfs_t P85PFS;
		typedef pfsw_t_<0x0008C186> p86pfs_t;
		static p86pfs_t P86PFS;
		typedef pfsw_t_<0x0008C187> p87pfs_t;
		static p87pfs_t P87PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
		  @brief  P9n 端子機能制御レジスタ（P9nPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsm_t_<0x0008C188> p90pfs_t;
		static p90pfs_t P90PFS;
		typedef pfsm_t_<0x0008C189> p91pfs_t;
		static p91pfs_t P91PFS;
		typedef pfsm_t_<0x0008C18A> p92pfs_t;
		static p92pfs_t P92PFS;
		typedef pfsm_t_<0x0008C18B> p93pfs_t;
		static p93pfs_t P93PFS;
		typedef pfsm_t_<0x0008C18C> p94pfs_t;
		static p94pfs_t P94PFS;
		typedef pfsm_t_<0x0008C18D> p95pfs_t;
		static p95pfs_t P95PFS;
		typedef pfsm_t_<0x0008C18E> p96pfs_t;
		static p96pfs_t P96PFS;
		typedef pfsm_t_<0x0008C18F> p97pfs_t;
		static p97pfs_t P97PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
		  @brief  PAn 端子機能制御レジスタ（PAnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsy_t_<0x0008C190> pa0pfs_t;
		static pa0pfs_t PA0PFS;
		typedef pfsy_t_<0x0008C191> pa1pfs_t;
		static pa1pfs_t PA1PFS;
		typedef pfsy_t_<0x0008C192> pa2pfs_t;
		static pa2pfs_t PA2PFS;
		typedef pfsy_t_<0x0008C193> pa3pfs_t;
		static pa3pfs_t PA3PFS;
		typedef pfsy_t_<0x0008C194> pa4pfs_t;
		static pa4pfs_t PA4PFS;
		typedef pfsy_t_<0x0008C195> pa5pfs_t;
		static pa5pfs_t PA5PFS;
		typedef pfsy_t_<0x0008C196> pa6pfs_t;
		static pa6pfs_t PA6PFS;
		typedef pfsy_t_<0x0008C197> pa7pfs_t;
		static pa7pfs_t PA7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
		  @brief  PBn 端子機能制御レジスタ（PBnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsy_t_<0x0008C198> pb0pfs_t;
		static pb0pfs_t PB0PFS;
		typedef pfsy_t_<0x0008C199> pb1pfs_t;
		static pb1pfs_t PB1PFS;
		typedef pfsy_t_<0x0008C19A> pb2pfs_t;
		static pb2pfs_t PB2PFS;
		typedef pfsy_t_<0x0008C19B> pb3pfs_t;
		static pb3pfs_t PB3PFS;
		typedef pfsy_t_<0x0008C19C> pb4pfs_t;
		static pb4pfs_t PB4PFS;
		typedef pfsy_t_<0x0008C19D> pb5pfs_t;
		static pb5pfs_t PB5PFS;
		typedef pfsy_t_<0x0008C19E> pb6pfs_t;
		static pb6pfs_t PB6PFS;
		typedef pfsy_t_<0x0008C19F> pb7pfs_t;
		static pb7pfs_t PB7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
		  @brief  PCn 端子機能制御レジスタ（PCnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsy_t_<0x0008C1A0> pc0pfs_t;
		static pc0pfs_t PC0PFS;
		typedef pfsy_t_<0x0008C1A1> pc1pfs_t;
		static pc1pfs_t PC1PFS;
		typedef pfsy_t_<0x0008C1A2> pc2pfs_t;
		static pc2pfs_t PC2PFS;
		typedef pfsy_t_<0x0008C1A3> pc3pfs_t;
		static pc3pfs_t PC3PFS;
		typedef pfsy_t_<0x0008C1A4> pc4pfs_t;
		static pc4pfs_t PC4PFS;
		typedef pfsy_t_<0x0008C1A5> pc5pfs_t;
		static pc5pfs_t PC5PFS;
		typedef pfsy_t_<0x0008C1A6> pc6pfs_t;
		static pc6pfs_t PC6PFS;
		typedef pfsy_t_<0x0008C1A7> pc7pfs_t;
		static pc7pfs_t PC7PFS;


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
		typedef pfsx_t_<0x0008C1B6> pe6pfs_t;
		static pe6pfs_t PE6PFS;
		typedef pfsx_t_<0x0008C1B7> pe7pfs_t;
		static pe7pfs_t PE7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PFn 端子機能制御レジスタ（PFnPFS）（n = 0 ～ 2）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsy_t_<0x0008C1B8> pf0pfs_t;
		static pf0pfs_t PF0PFS;
		typedef pfsy_t_<0x0008C1B9> pf1pfs_t;
		static pf1pfs_t PF1PFS;
		typedef pfsy_t_<0x0008C1BA> pf2pfs_t;
		static pf2pfs_t PF2PFS;
		typedef pfsy_t_<0x0008C1BB> pf3pfs_t;
		static pf3pfs_t PF3PFS;
		typedef pfsy_t_<0x0008C1BC> pf4pfs_t;
		static pf4pfs_t PF4PFS;
		typedef pfsy_t_<0x0008C1BD> pf5pfs_t;
		static pf5pfs_t PF5PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PGn 端子機能制御レジスタ（PGnPFS）（n = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsw_t_<0x0008C1C0> pg0pfs_t;
		static pg0pfs_t PG0PFS;
		typedef pfsw_t_<0x0008C1C1> pg1pfs_t;
		static pg1pfs_t PG1PFS;
		typedef pfsw_t_<0x0008C1C2> pg2pfs_t;
		static pg2pfs_t PG2PFS;
		typedef pfsw_t_<0x0008C1C3> pg3pfs_t;
		static pg3pfs_t PG3PFS;
		typedef pfsw_t_<0x0008C1C4> pg4pfs_t;
		static pg4pfs_t PG4PFS;
		typedef pfsw_t_<0x0008C1C5> pg5pfs_t;
		static pg5pfs_t PG5PFS;
		typedef pfsw_t_<0x0008C1C6> pg6pfs_t;
		static pg6pfs_t PG6PFS;
		typedef pfsw_t_<0x0008C1C7> pg7pfs_t;
		static pg7pfs_t PG7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PJn 端子機能制御レジスタ（PJnPFS）（n = 3, 5）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfsw_t_<0x0008C1D3> pj3pfs_t;
		static pj3pfs_t PJ3PFS;
		typedef pfsw_t_<0x0008C1D5> pj5pfs_t;
		static pj5pfs_t PJ5PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CS 出力許可レジスタ（PFCSE）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfcse_t_ : public rw8_t<base> {
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
		typedef pfcse_t_<0x0008C100> pfcse_t;
		static pfcse_t PFCSE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CS 出力端子選択レジスタ 0（PFCSS0）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfcss0_t_ : public rw8_t<base> {
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
		typedef pfcss0_t_<0x0008C102> pfcss0_t;
		static pfcss0_t PFCSS0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CS 出力端子選択レジスタ 1（PFCSS1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfcss1_t_ : public rw8_t<base> {
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
		typedef pfcss1_t_<0x0008C103> pfcss1_t;
		static pfcss1_t PFCSS1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アドレス出力許可レジスタ 0（PFAOE0）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfaoe0_t_ : public rw8_t<base> {
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
		typedef pfaoe0_t_<0x0008C104> pfaoe0_t;
		static pfaoe0_t PFAOE0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アドレス出力許可レジスタ 1（PFAOE1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfaoe1_t_ : public rw8_t<base> {
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
		typedef pfaoe0_t_<0x0008C105> pfaoe1_t;
		static pfaoe1_t PFAOE1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  外部バス制御レジスタ 0（PFBCR0）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfbcr0_t_ : public rw8_t<base> {
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
		typedef pfbcr0_t_<0x0008C106> pfbcr0_t;
		static pfbcr0_t PFBCR0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  外部バス制御レジスタ 1（PFBCR1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfbcr1_t_ : public rw8_t<base> {
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
		typedef pfbcr1_t_<0x0008C107> pfbcr1_t;
		static pfbcr1_t PFBCR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  イーサネット制御レジスタ（PFENET）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfenet_t_ : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B4>  PHYMODE0;
			bit_rw_t<io, bitpos::B5>  PHYMODE1;
		};
		typedef pfenet_t_<0x0008C10E> pfenet_t;
		static pfenet_t PFENET;

	};
	typedef mpc_t_<void> MPC;

	template<class _> typename mpc_t_<_>:: pwpr_t   mpc_t_<_>::PWPR;
	template<class _> typename mpc_t_<_>:: p00pfs_t mpc_t_<_>::P00PFS;
	template<class _> typename mpc_t_<_>:: p01pfs_t mpc_t_<_>::P01PFS;
	template<class _> typename mpc_t_<_>:: p02pfs_t mpc_t_<_>::P02PFS;
	template<class _> typename mpc_t_<_>:: p03pfs_t mpc_t_<_>::P03PFS;
	template<class _> typename mpc_t_<_>:: p05pfs_t mpc_t_<_>::P05PFS;
	template<class _> typename mpc_t_<_>:: p07pfs_t mpc_t_<_>::P07PFS;
	template<class _> typename mpc_t_<_>:: p10pfs_t mpc_t_<_>::P10PFS;
	template<class _> typename mpc_t_<_>:: p11pfs_t mpc_t_<_>::P11PFS;
	template<class _> typename mpc_t_<_>:: p12pfs_t mpc_t_<_>::P12PFS;
	template<class _> typename mpc_t_<_>:: p13pfs_t mpc_t_<_>::P13PFS;
	template<class _> typename mpc_t_<_>:: p14pfs_t mpc_t_<_>::P14PFS;
	template<class _> typename mpc_t_<_>:: p15pfs_t mpc_t_<_>::P15PFS;
	template<class _> typename mpc_t_<_>:: p16pfs_t mpc_t_<_>::P16PFS;
	template<class _> typename mpc_t_<_>:: p17pfs_t mpc_t_<_>::P17PFS;
	template<class _> typename mpc_t_<_>:: p20pfs_t mpc_t_<_>::P20PFS;
	template<class _> typename mpc_t_<_>:: p21pfs_t mpc_t_<_>::P21PFS;
	template<class _> typename mpc_t_<_>:: p22pfs_t mpc_t_<_>::P22PFS;
	template<class _> typename mpc_t_<_>:: p23pfs_t mpc_t_<_>::P23PFS;
	template<class _> typename mpc_t_<_>:: p24pfs_t mpc_t_<_>::P24PFS;
	template<class _> typename mpc_t_<_>:: p25pfs_t mpc_t_<_>::P25PFS;
	template<class _> typename mpc_t_<_>:: p26pfs_t mpc_t_<_>::P26PFS;
	template<class _> typename mpc_t_<_>:: p27pfs_t mpc_t_<_>::P27PFS;
	template<class _> typename mpc_t_<_>:: p30pfs_t mpc_t_<_>::P30PFS;
	template<class _> typename mpc_t_<_>:: p31pfs_t mpc_t_<_>::P31PFS;
	template<class _> typename mpc_t_<_>:: p32pfs_t mpc_t_<_>::P32PFS;
	template<class _> typename mpc_t_<_>:: p33pfs_t mpc_t_<_>::P33PFS;
	template<class _> typename mpc_t_<_>:: p34pfs_t mpc_t_<_>::P34PFS;
	template<class _> typename mpc_t_<_>:: p40pfs_t mpc_t_<_>::P40PFS;
	template<class _> typename mpc_t_<_>:: p41pfs_t mpc_t_<_>::P41PFS;
	template<class _> typename mpc_t_<_>:: p42pfs_t mpc_t_<_>::P42PFS;
	template<class _> typename mpc_t_<_>:: p43pfs_t mpc_t_<_>::P43PFS;
	template<class _> typename mpc_t_<_>:: p44pfs_t mpc_t_<_>::P44PFS;
	template<class _> typename mpc_t_<_>:: p45pfs_t mpc_t_<_>::P45PFS;
	template<class _> typename mpc_t_<_>:: p46pfs_t mpc_t_<_>::P46PFS;
	template<class _> typename mpc_t_<_>:: p47pfs_t mpc_t_<_>::P47PFS;
	template<class _> typename mpc_t_<_>:: p50pfs_t mpc_t_<_>::P50PFS;
	template<class _> typename mpc_t_<_>:: p51pfs_t mpc_t_<_>::P51PFS;
	template<class _> typename mpc_t_<_>:: p52pfs_t mpc_t_<_>::P52PFS;
	template<class _> typename mpc_t_<_>:: p54pfs_t mpc_t_<_>::P54PFS;
	template<class _> typename mpc_t_<_>:: p55pfs_t mpc_t_<_>::P55PFS;
	template<class _> typename mpc_t_<_>:: p56pfs_t mpc_t_<_>::P56PFS;
	template<class _> typename mpc_t_<_>:: p57pfs_t mpc_t_<_>::P57PFS;
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
	template<class _> typename mpc_t_<_>:: p60pfs_t mpc_t_<_>::P60PFS;
	template<class _> typename mpc_t_<_>:: p66pfs_t mpc_t_<_>::P66PFS;
	template<class _> typename mpc_t_<_>:: p67pfs_t mpc_t_<_>::P67PFS;
	#elif defined(SIG_RX66T)
	template<class _> typename mpc_t_<_>:: p60pfs_t mpc_t_<_>::P60PFS;
	template<class _> typename mpc_t_<_>:: p61pfs_t mpc_t_<_>::P61PFS;
	template<class _> typename mpc_t_<_>:: p62pfs_t mpc_t_<_>::P62PFS;
	template<class _> typename mpc_t_<_>:: p63pfs_t mpc_t_<_>::P63PFS;
	template<class _> typename mpc_t_<_>:: p64pfs_t mpc_t_<_>::P64PFS;
	template<class _> typename mpc_t_<_>:: p65pfs_t mpc_t_<_>::P65PFS;
#endif
	template<class _> typename mpc_t_<_>:: p71pfs_t mpc_t_<_>::P71PFS;
	template<class _> typename mpc_t_<_>:: p72pfs_t mpc_t_<_>::P72PFS;
	template<class _> typename mpc_t_<_>:: p73pfs_t mpc_t_<_>::P73PFS;
	template<class _> typename mpc_t_<_>:: p74pfs_t mpc_t_<_>::P74PFS;
	template<class _> typename mpc_t_<_>:: p75pfs_t mpc_t_<_>::P75PFS;
	template<class _> typename mpc_t_<_>:: p76pfs_t mpc_t_<_>::P76PFS;
	template<class _> typename mpc_t_<_>:: p77pfs_t mpc_t_<_>::P77PFS;
	template<class _> typename mpc_t_<_>:: p80pfs_t mpc_t_<_>::P80PFS;
	template<class _> typename mpc_t_<_>:: p81pfs_t mpc_t_<_>::P81PFS;
	template<class _> typename mpc_t_<_>:: p82pfs_t mpc_t_<_>::P82PFS;
	template<class _> typename mpc_t_<_>:: p83pfs_t mpc_t_<_>::P83PFS;
	template<class _> typename mpc_t_<_>:: p84pfs_t mpc_t_<_>::P84PFS;
	template<class _> typename mpc_t_<_>:: p85pfs_t mpc_t_<_>::P85PFS;
	template<class _> typename mpc_t_<_>:: p86pfs_t mpc_t_<_>::P86PFS;
	template<class _> typename mpc_t_<_>:: p87pfs_t mpc_t_<_>::P87PFS;
	template<class _> typename mpc_t_<_>:: p90pfs_t mpc_t_<_>::P90PFS;
	template<class _> typename mpc_t_<_>:: p91pfs_t mpc_t_<_>::P91PFS;
	template<class _> typename mpc_t_<_>:: p92pfs_t mpc_t_<_>::P92PFS;
	template<class _> typename mpc_t_<_>:: p93pfs_t mpc_t_<_>::P93PFS;
	template<class _> typename mpc_t_<_>:: p94pfs_t mpc_t_<_>::P94PFS;
	template<class _> typename mpc_t_<_>:: p95pfs_t mpc_t_<_>::P95PFS;
	template<class _> typename mpc_t_<_>:: p96pfs_t mpc_t_<_>::P96PFS;
	template<class _> typename mpc_t_<_>:: p97pfs_t mpc_t_<_>::P97PFS;
	template<class _> typename mpc_t_<_>:: pa0pfs_t mpc_t_<_>::PA0PFS;
	template<class _> typename mpc_t_<_>:: pa1pfs_t mpc_t_<_>::PA1PFS;
	template<class _> typename mpc_t_<_>:: pa2pfs_t mpc_t_<_>::PA2PFS;
	template<class _> typename mpc_t_<_>:: pa3pfs_t mpc_t_<_>::PA3PFS;
	template<class _> typename mpc_t_<_>:: pa4pfs_t mpc_t_<_>::PA4PFS;
	template<class _> typename mpc_t_<_>:: pa5pfs_t mpc_t_<_>::PA5PFS;
	template<class _> typename mpc_t_<_>:: pa6pfs_t mpc_t_<_>::PA6PFS;
	template<class _> typename mpc_t_<_>:: pa7pfs_t mpc_t_<_>::PA7PFS;
	template<class _> typename mpc_t_<_>:: pb0pfs_t mpc_t_<_>::PB0PFS;
	template<class _> typename mpc_t_<_>:: pb1pfs_t mpc_t_<_>::PB1PFS;
	template<class _> typename mpc_t_<_>:: pb2pfs_t mpc_t_<_>::PB2PFS;
	template<class _> typename mpc_t_<_>:: pb3pfs_t mpc_t_<_>::PB3PFS;
	template<class _> typename mpc_t_<_>:: pb4pfs_t mpc_t_<_>::PB4PFS;
	template<class _> typename mpc_t_<_>:: pb5pfs_t mpc_t_<_>::PB5PFS;
	template<class _> typename mpc_t_<_>:: pb6pfs_t mpc_t_<_>::PB6PFS;
	template<class _> typename mpc_t_<_>:: pb7pfs_t mpc_t_<_>::PB7PFS;
	template<class _> typename mpc_t_<_>:: pc0pfs_t mpc_t_<_>::PC0PFS;
	template<class _> typename mpc_t_<_>:: pc1pfs_t mpc_t_<_>::PC1PFS;
	template<class _> typename mpc_t_<_>:: pc2pfs_t mpc_t_<_>::PC2PFS;
	template<class _> typename mpc_t_<_>:: pc3pfs_t mpc_t_<_>::PC3PFS;
	template<class _> typename mpc_t_<_>:: pc4pfs_t mpc_t_<_>::PC4PFS;
	template<class _> typename mpc_t_<_>:: pc5pfs_t mpc_t_<_>::PC5PFS;
	template<class _> typename mpc_t_<_>:: pc6pfs_t mpc_t_<_>::PC6PFS;
	template<class _> typename mpc_t_<_>:: pc7pfs_t mpc_t_<_>::PC7PFS;
	template<class _> typename mpc_t_<_>:: pd0pfs_t mpc_t_<_>::PD0PFS;
	template<class _> typename mpc_t_<_>:: pd1pfs_t mpc_t_<_>::PD1PFS;
	template<class _> typename mpc_t_<_>:: pd2pfs_t mpc_t_<_>::PD2PFS;
	template<class _> typename mpc_t_<_>:: pd3pfs_t mpc_t_<_>::PD3PFS;
	template<class _> typename mpc_t_<_>:: pd4pfs_t mpc_t_<_>::PD4PFS;
	template<class _> typename mpc_t_<_>:: pd5pfs_t mpc_t_<_>::PD5PFS;
	template<class _> typename mpc_t_<_>:: pd6pfs_t mpc_t_<_>::PD6PFS;
	template<class _> typename mpc_t_<_>:: pd7pfs_t mpc_t_<_>::PD7PFS;
	template<class _> typename mpc_t_<_>:: pe0pfs_t mpc_t_<_>::PE0PFS;
	template<class _> typename mpc_t_<_>:: pe1pfs_t mpc_t_<_>::PE1PFS;
	template<class _> typename mpc_t_<_>:: pe2pfs_t mpc_t_<_>::PE2PFS;
	template<class _> typename mpc_t_<_>:: pe3pfs_t mpc_t_<_>::PE3PFS;
	template<class _> typename mpc_t_<_>:: pe4pfs_t mpc_t_<_>::PE4PFS;
	template<class _> typename mpc_t_<_>:: pe5pfs_t mpc_t_<_>::PE5PFS;
	template<class _> typename mpc_t_<_>:: pe6pfs_t mpc_t_<_>::PE6PFS;
	template<class _> typename mpc_t_<_>:: pe7pfs_t mpc_t_<_>::PE7PFS;
	template<class _> typename mpc_t_<_>:: pf0pfs_t mpc_t_<_>::PF0PFS;
	template<class _> typename mpc_t_<_>:: pf1pfs_t mpc_t_<_>::PF1PFS;
	template<class _> typename mpc_t_<_>:: pf2pfs_t mpc_t_<_>::PF2PFS;
	template<class _> typename mpc_t_<_>:: pf3pfs_t mpc_t_<_>::PF3PFS;
	template<class _> typename mpc_t_<_>:: pf4pfs_t mpc_t_<_>::PF4PFS;
	template<class _> typename mpc_t_<_>:: pf5pfs_t mpc_t_<_>::PF5PFS;
	template<class _> typename mpc_t_<_>:: pg0pfs_t mpc_t_<_>::PG0PFS;
	template<class _> typename mpc_t_<_>:: pg1pfs_t mpc_t_<_>::PG1PFS;
	template<class _> typename mpc_t_<_>:: pg2pfs_t mpc_t_<_>::PG2PFS;
	template<class _> typename mpc_t_<_>:: pg3pfs_t mpc_t_<_>::PG3PFS;
	template<class _> typename mpc_t_<_>:: pg4pfs_t mpc_t_<_>::PG4PFS;
	template<class _> typename mpc_t_<_>:: pg5pfs_t mpc_t_<_>::PG5PFS;
	template<class _> typename mpc_t_<_>:: pg6pfs_t mpc_t_<_>::PG6PFS;
	template<class _> typename mpc_t_<_>:: pg7pfs_t mpc_t_<_>::PG7PFS;
	template<class _> typename mpc_t_<_>:: pj3pfs_t mpc_t_<_>::PJ3PFS;
	template<class _> typename mpc_t_<_>:: pj5pfs_t mpc_t_<_>::PJ5PFS;
	template<class _> typename mpc_t_<_>:: pfcse_t  mpc_t_<_>::PFCSE;
	template<class _> typename mpc_t_<_>:: pfcss0_t mpc_t_<_>::PFCSS0;
	template<class _> typename mpc_t_<_>:: pfcss1_t mpc_t_<_>::PFCSS1;
	template<class _> typename mpc_t_<_>:: pfaoe0_t mpc_t_<_>::PFAOE0;
	template<class _> typename mpc_t_<_>:: pfaoe1_t mpc_t_<_>::PFAOE1;
	template<class _> typename mpc_t_<_>:: pfbcr0_t mpc_t_<_>::PFBCR0;
	template<class _> typename mpc_t_<_>:: pfbcr1_t mpc_t_<_>::PFBCR1;
	template<class _> typename mpc_t_<_>:: pfenet_t mpc_t_<_>::PFENET;
}
