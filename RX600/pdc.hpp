#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600/RX700 グループ・PDC 定義 @n
			RX631/RX63N @n
			RX64M/RX71M @n
			RX65N/RX65N @n
			RX66N @n
			RX72N @n
			RX72M
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	パラレルデータキャプチャユニット（PDC）
		@param[in]	per	ペリフェラル
		@param[in]	GPT	グループ割り込み型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per, typename GPT>
	struct pdc_t {

		static constexpr auto PERIPHERAL = per;				///< ペリフェラル型
		static constexpr auto PCDFI = ICU::VECTOR::PCDFI;	///< 受信データレディ割り込み
		static constexpr auto PCFEI = GPT::PCFEI;			///< フレームエンド割り込み
		static constexpr auto PCERI = GPT::PCERI;			///< エラー割り込み


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
		static inline pccr0_t<0x000A'0500>  PCCR0;


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
		static inline pccr1_t<0x000A'0504>  PCCR1;


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
		static inline pcsr_t<0x000A'0508>  PCSR;


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
		static inline pcmonr_t<0x000A'050C>  PCMONR;


		//-----------------------------------------------------------------//
		/*!
			@brief  PDC 受信データレジスタ（ PCDR ）
		*/
		//-----------------------------------------------------------------//
		static inline rw32_t<0x000A'0510>  PCDR;


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
		static inline vcr_t<0x000A'0514>  VCR;


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
		static inline hcr_t<0x000A'0518>  HCR;
	};

#if defined(SIG_RX63N) || defined(SIG_RX631)
	typedef pdc_t<peripheral::PDC, ICU::VECTOR> PDC;
#else
	typedef pdc_t<peripheral::PDC, ICU::GROUPBL0> PDC;
#endif
}
