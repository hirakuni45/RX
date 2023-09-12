#pragma once
//=========================================================================//
/*!	@file
	@brief	RX26T グループ MPC 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023 Kunihito Hiramatsu @n
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
			@brief  P1n 端子機能制御レジスタ（P1nPFS）（n = 0, 1）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfs_ip_t<0x0008'C148> P10PFS_;
		typedef pfs_ip_t<0x0008'C149> P11PFS_;
		static P10PFS_ P10PFS;
		static P11PFS_ P11PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P2n 端子機能制御レジスタ（P2nPFS）（n = 0 ～ 4, 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfs_aip_t<0x0008'C150> P20PFS_;
		typedef pfs_aip_t<0x0008'C151> P21PFS_;
		typedef pfs_aip_t<0x0008'C152> P22PFS_;
		typedef pfs_aip_t<0x0008'C153> P23PFS_;
		typedef pfs_aip_t<0x0008'C154> P24PFS_;
		typedef pfs_aip_t<0x0008'C157> P27PFS_;
		static P20PFS_ P20PFS;
		static P21PFS_ P21PFS;
		static P22PFS_ P22PFS;
		static P23PFS_ P23PFS;
		static P24PFS_ P24PFS;
		static P27PFS_ P27PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P3n 端子機能制御レジスタ（P3nPFS）（n = 0 ～ 3, 6, 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfs_ip_t<0x0008'C158> P30PFS_;
		typedef pfs_ip_t<0x0008'C159> P31PFS_;
		typedef pfs_ip_t<0x0008'C15A> P32PFS_;
		typedef pfs_ip_t<0x0008'C15B> P33PFS_;
		typedef pfs_ip_t<0x0008'C15E> P36PFS_;
		typedef pfs_ip_t<0x0008'C15F> P37PFS_;
		static P30PFS_ P30PFS;
		static P31PFS_ P31PFS;
		static P32PFS_ P32PFS;
		static P33PFS_ P33PFS;
		static P36PFS_ P36PFS;
		static P37PFS_ P37PFS;


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
			@brief  PAn 端子機能制御レジスタ（PAnPFS）（n = 0 ～ 5）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfs_ip_t<0x0008'C190> PA0PFS_;
		typedef pfs_ip_t<0x0008'C191> PA1PFS_;
		typedef pfs_ip_t<0x0008'C192> PA2PFS_;
		typedef pfs_ip_t<0x0008'C193> PA3PFS_;
		typedef pfs_ip_t<0x0008'C194> PA4PFS_;
		typedef pfs_ip_t<0x0008'C195> PA5PFS_;
		static PA0PFS_ PA0PFS;
		static PA1PFS_ PA1PFS;
		static PA2PFS_ PA2PFS;
		static PA3PFS_ PA3PFS;
		static PA4PFS_ PA4PFS;
		static PA5PFS_ PA5PFS;


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
			@brief  PEn 端子機能制御レジスタ（PEnPFS）（n = 0 ～ 5）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfs_ip_t<0x0008'C1B0> PE0PFS_;
		typedef pfs_ip_t<0x0008'C1B1> PE1PFS_;
		typedef pfs_ip_t<0x0008'C1B2> PE2PFS_;
		typedef pfs_ip_t<0x0008'C1B3> PE3PFS_;
		typedef pfs_ip_t<0x0008'C1B4> PE4PFS_;
		typedef pfs_ip_t<0x0008'C1B5> PE5PFS_;
		static PE0PFS_ PE0PFS;
		static PE1PFS_ PE1PFS;
		static PE2PFS_ PE2PFS;
		static PE3PFS_ PE3PFS;
		static PE4PFS_ PE4PFS;
		static PE5PFS_ PE5PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PNn 端子機能制御レジスタ（PNnPFS）（n = 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pfs_ip_t<0x0008'C1F7> PN7PFS_;
		static PN7PFS_ PN7PFS;
	};
	template<class _> typename mpc_t<_>::PWPR_ mpc_t<_>::PWPR;
	template<class _> typename mpc_t<_>::P00PFS_ mpc_t<_>::P00PFS;
	template<class _> typename mpc_t<_>::P01PFS_ mpc_t<_>::P01PFS;
	template<class _> typename mpc_t<_>::P10PFS_ mpc_t<_>::P10PFS;
	template<class _> typename mpc_t<_>::P11PFS_ mpc_t<_>::P11PFS;
	template<class _> typename mpc_t<_>::P20PFS_ mpc_t<_>::P20PFS;
	template<class _> typename mpc_t<_>::P21PFS_ mpc_t<_>::P21PFS;
	template<class _> typename mpc_t<_>::P22PFS_ mpc_t<_>::P22PFS;
	template<class _> typename mpc_t<_>::P23PFS_ mpc_t<_>::P23PFS;
	template<class _> typename mpc_t<_>::P24PFS_ mpc_t<_>::P24PFS;
	template<class _> typename mpc_t<_>::P27PFS_ mpc_t<_>::P27PFS;
	template<class _> typename mpc_t<_>::P30PFS_ mpc_t<_>::P30PFS;
	template<class _> typename mpc_t<_>::P31PFS_ mpc_t<_>::P31PFS;
	template<class _> typename mpc_t<_>::P32PFS_ mpc_t<_>::P32PFS;
	template<class _> typename mpc_t<_>::P33PFS_ mpc_t<_>::P33PFS;
	template<class _> typename mpc_t<_>::P36PFS_ mpc_t<_>::P36PFS;
	template<class _> typename mpc_t<_>::P37PFS_ mpc_t<_>::P37PFS;
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
	template<class _> typename mpc_t<_>::PB0PFS_ mpc_t<_>::PB0PFS;
	template<class _> typename mpc_t<_>::PB1PFS_ mpc_t<_>::PB1PFS;
	template<class _> typename mpc_t<_>::PB2PFS_ mpc_t<_>::PB2PFS;
	template<class _> typename mpc_t<_>::PB3PFS_ mpc_t<_>::PB3PFS;
	template<class _> typename mpc_t<_>::PB4PFS_ mpc_t<_>::PB4PFS;
	template<class _> typename mpc_t<_>::PB5PFS_ mpc_t<_>::PB5PFS;
	template<class _> typename mpc_t<_>::PB6PFS_ mpc_t<_>::PB6PFS;
	template<class _> typename mpc_t<_>::PB7PFS_ mpc_t<_>::PB7PFS;
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
	template<class _> typename mpc_t<_>::PN7PFS_ mpc_t<_>::PN7PFS;

	typedef mpc_t<void> MPC;
}
