#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M グループ・PDC 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	パラレルデータキャプチャユニット（PDC）
		@param[in]	per	ペリフェラル
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per>
	struct pdc_t {

		static const auto PERIPHERAL = per;	///< ペリフェラル型
		static const auto VEC_DFI = ICU::VECTOR::PCDFI;		///< 受信データレディ割り込み
		static const auto VEC_FEI = ICU::VECTOR_BL0::PCFEI;	///< フレームエンド割り込み
		static const auto VEC_ERI = ICU::VECTOR_BL0::PCERI;	///< エラー割り込み

		//-----------------------------------------------------------------//
		/*!
			@brief  PDC 制御レジスタ 0 （ PCCR0 ）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pccr0_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      PCKE;
			bit_rw_t <io_, bitpos::B1>      VPS;
			bit_rw_t <io_, bitpos::B2>      HPS;
			bit_rw_t <io_, bitpos::B3>      PRST;
			bit_rw_t <io_, bitpos::B4>      DFIE;
			bit_rw_t <io_, bitpos::B5>      FEIE;
			bit_rw_t <io_, bitpos::B6>      OVIE;
			bit_rw_t <io_, bitpos::B7>      UDRIE;
			bit_rw_t <io_, bitpos::B8>      VERIE;
			bit_rw_t <io_, bitpos::B9>      HERIE;
			bit_rw_t <io_, bitpos::B10>     PCKOE;
			bits_rw_t<io_, bitpos::B11, 3>  PCKDIV;
			bit_rw_t <io_, bitpos::B14>     EDS;
		};
		typedef pccr0_t<0x000A0500>  PCCR0_;
		static  PCCR0_ PCCR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  PDC 制御レジスタ 1 （ PCCR1 ）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pccr1_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      PCE;
		};
		typedef pccr1_t<0x000A0504>  PCCR1_;
		static  PCCR1_ PCCR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  PDC ステータスレジスタ（ PCSR ）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pcsr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  FBSY;
			bit_rw_t<io_, bitpos::B1>  FEMPF;
			bit_rw_t<io_, bitpos::B2>  FEF;
			bit_rw_t<io_, bitpos::B3>  OVRF;
			bit_rw_t<io_, bitpos::B4>  UDRF;
			bit_rw_t<io_, bitpos::B5>  VERF;
			bit_rw_t<io_, bitpos::B6>  HERF;
		};
		typedef pcsr_t<0x000A0508>  PCSR_;
		static  PCSR_ PCSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  PDC 端子モニタレジスタ（ PCMONR ）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pcmonr_t : public ro32_t<base> {
			typedef ro32_t<base> io_;
			using io_::operator ();

			bit_rw_t<io_, bitpos::B0>  VSYNC;
			bit_rw_t<io_, bitpos::B1>  HSYNC;
		};
		typedef pcmonr_t<0x000A050C>  PCMONR_;
		static  PCMONR_ PCMONR;


		//-----------------------------------------------------------------//
		/*!
			@brief  PDC 受信データレジスタ（ PCDR ）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<0x000A0510>  PCDR_;
		static  PCDR_ PCDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  垂直方向キャプチャレジスタ（ VCR ）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct vcr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  12>  VST;
			bits_rw_t<io_, bitpos::B16, 12>  VSZ;
		};
		typedef vcr_t<0x000A0514>  VCR_;
		static  VCR_ VCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  水平方向キャプチャレジスタ（ HCR ）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct hcr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  12>  HST;
			bits_rw_t<io_, bitpos::B16, 12>  HSZ;
		};
		typedef hcr_t<0x000A0518>  HCR_;
		static  HCR_ HCR;
	};
	template <peripheral per> typename pdc_t<per>::PCCR0_  pdc_t<per>::PCCR0;
	template <peripheral per> typename pdc_t<per>::PCCR1_  pdc_t<per>::PCCR1;
	template <peripheral per> typename pdc_t<per>::PCSR_   pdc_t<per>::PCSR;
	template <peripheral per> typename pdc_t<per>::PCMONR_ pdc_t<per>::PCMONR;
	template <peripheral per> typename pdc_t<per>::PCDR_   pdc_t<per>::PCDR;
	template <peripheral per> typename pdc_t<per>::VCR_    pdc_t<per>::VCR;
	template <peripheral per> typename pdc_t<per>::HCR_    pdc_t<per>::HCR;


	typedef pdc_t<peripheral::PDC> PDC;
}
