#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ SCI ベース定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCIe クラス
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct sci_a_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  レシーブデータレジスタ (RDR)
		*/
		//-----------------------------------------------------------------//
		typedef ro8_t<base + 0x05> RDR_;
		static RDR_ RDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  トランスミットデータレジスタ (TDR)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x03> TDR_;
		static TDR_ TDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルモードレジスタ (SMR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct smr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			// 非スマートカードインタフェースモード
			bits_rw_t<io_, bitpos::B0, 2> CKS;
			bit_rw_t <io_, bitpos::B2>	  MP;
			bit_rw_t <io_, bitpos::B3>	  STOP;
			bit_rw_t <io_, bitpos::B4>	  PM;
			bit_rw_t <io_, bitpos::B5>	  PE;
			bit_rw_t <io_, bitpos::B6>	  CHR;
			bit_rw_t <io_, bitpos::B7>	  CM;

			// スマートカードインタフェースモード
			bits_rw_t<io_, bitpos::B2, 2> BCP;
			bit_rw_t <io_, bitpos::B6>	  BLK;
			bit_rw_t <io_, bitpos::B7>	  GM;
		};
		typedef smr_t<base + 0x00> SMR_;
		static SMR_ SMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルコントロールレジスタ (SCR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct scr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> CKE;
			bit_rw_t <io_, bitpos::B2>	  TEIE;
			bit_rw_t <io_, bitpos::B3>	  MPIE;
			bit_rw_t <io_, bitpos::B4>	  RE;
			bit_rw_t <io_, bitpos::B5>	  TE;
			bit_rw_t <io_, bitpos::B6>	  RIE;
			bit_rw_t <io_, bitpos::B7>	  TIE;
		};
		typedef scr_t<base + 0x02> SCR_;
		static SCR_ SCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルステータスレジスタ (SSR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ssr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> MPBT;
			bit_rw_t<io_, bitpos::B1> MPB;
			bit_rw_t<io_, bitpos::B2> TEND;
			bit_rw_t<io_, bitpos::B3> PER;
			bit_rw_t<io_, bitpos::B4> FER;
			bit_rw_t<io_, bitpos::B4> ERS;  // スマートカードインタフェースモード時
			bit_rw_t<io_, bitpos::B5> ORER;
			bit_rw_t<io_, bitpos::B6> RDRF;  // SCIe では利用不可
			bit_rw_t<io_, bitpos::B7> TDRE;  // SCIe では利用不可
		};
		typedef ssr_t<base + 0x04> SSR_;
		static SSR_ SSR;


 		//-----------------------------------------------------------------//
		/*!
			@brief  スマートカードモードレジスタ (SCMR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct scmr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SMIF;

			bit_rw_t<io_, bitpos::B2> SINV;
			bit_rw_t<io_, bitpos::B3> SDIR;

			bit_rw_t<io_, bitpos::B7> BCP2;
		};
		typedef scmr_t<base + 0x06> SCMR_;
		static SCMR_ SCMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ビットレートレジスタ (BRR)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x01> BRR_;
		static BRR_ BRR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアル拡張レジスタ (SEMR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct semr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> ACS0;

			bit_rw_t<io_, bitpos::B2> BRME;  // 無効

			bit_rw_t<io_, bitpos::B4> ABCS;
			bit_rw_t<io_, bitpos::B5> NFEN;  // 無効
			bit_rw_t<io_, bitpos::B6> BGDM;  // 無効
			bit_rw_t<io_, bitpos::B7> RXDESEL;  // 無効
		};
		typedef semr_t<base + 0x07> SEMR_;
		static SEMR_ SEMR;


		//-----------------------------------------------------------------//
		/*!
			@brief	モジュレーションデューティレジスタ（MDDR）ダミー
		*/
		//-----------------------------------------------------------------//
		typedef rw8_null_t<0x00000000> MDDR_;
		static MDDR_ MDDR;
	};
	template <uint32_t base> typename sci_a_t<base>::RDR_ sci_a_t<base>::RDR;
	template <uint32_t base> typename sci_a_t<base>::TDR_ sci_a_t<base>::TDR;
	template <uint32_t base> typename sci_a_t<base>::SMR_ sci_a_t<base>::SMR;
	template <uint32_t base> typename sci_a_t<base>::SCR_ sci_a_t<base>::SCR;
	template <uint32_t base> typename sci_a_t<base>::SSR_ sci_a_t<base>::SSR;
	template <uint32_t base> typename sci_a_t<base>::SCMR_ sci_a_t<base>::SCMR;
	template <uint32_t base> typename sci_a_t<base>::BRR_ sci_a_t<base>::BRR;
	template <uint32_t base> typename sci_a_t<base>::SEMR_ sci_a_t<base>::SEMR;
	template <uint32_t base> typename sci_a_t<base>::MDDR_ sci_a_t<base>::MDDR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCIc, SCIe クラス
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct sci_ce_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  レシーブデータレジスタ (RDR)
		*/
		//-----------------------------------------------------------------//
		typedef ro8_t<base + 0x05> RDR_;
		static RDR_ RDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  トランスミットデータレジスタ (TDR)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x03> TDR_;
		static TDR_ TDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルモードレジスタ (SMR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct smr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			// 非スマートカードインタフェースモード
			bits_rw_t<io_, bitpos::B0, 2> CKS;
			bit_rw_t <io_, bitpos::B2>	  MP;
			bit_rw_t <io_, bitpos::B3>	  STOP;
			bit_rw_t <io_, bitpos::B4>	  PM;
			bit_rw_t <io_, bitpos::B5>	  PE;
			bit_rw_t <io_, bitpos::B6>	  CHR;
			bit_rw_t <io_, bitpos::B7>	  CM;

			// スマートカードインタフェースモード
			bits_rw_t<io_, bitpos::B2, 2> BCP;
			bit_rw_t <io_, bitpos::B6>	  BLK;
			bit_rw_t <io_, bitpos::B7>	  GM;
		};
		typedef smr_t<base + 0x00> SMR_;
		static SMR_ SMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルコントロールレジスタ (SCR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct scr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> CKE;
			bit_rw_t <io_, bitpos::B2>	  TEIE;
			bit_rw_t <io_, bitpos::B3>	  MPIE;
			bit_rw_t <io_, bitpos::B4>	  RE;
			bit_rw_t <io_, bitpos::B5>	  TE;
			bit_rw_t <io_, bitpos::B6>	  RIE;
			bit_rw_t <io_, bitpos::B7>	  TIE;
		};
		typedef scr_t<base + 0x02> SCR_;
		static SCR_ SCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルステータスレジスタ (SSR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ssr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> MPBT;
			bit_rw_t<io_, bitpos::B1> MPB;
			bit_rw_t<io_, bitpos::B2> TEND;
			bit_rw_t<io_, bitpos::B3> PER;
			bit_rw_t<io_, bitpos::B4> FER;
			bit_rw_t<io_, bitpos::B4> ERS;  // スマートカードインタフェースモード時
			bit_rw_t<io_, bitpos::B5> ORER;
			bit_rw_t<io_, bitpos::B6> RDRF;  // SCIe では利用不可
			bit_rw_t<io_, bitpos::B7> TDRE;  // SCIe では利用不可
		};
		typedef ssr_t<base + 0x04> SSR_;
		static SSR_ SSR;


 		//-----------------------------------------------------------------//
		/*!
			@brief  スマートカードモードレジスタ (SCMR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct scmr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SMIF;

			bit_rw_t<io_, bitpos::B2> SINV;
			bit_rw_t<io_, bitpos::B3> SDIR;

			bit_rw_t<io_, bitpos::B7> BCP2;
		};
		typedef scmr_t<base + 0x06> SCMR_;
		static SCMR_ SCMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ビットレートレジスタ (BRR)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x01> BRR_;
		static BRR_ BRR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアル拡張レジスタ (SEMR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct semr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> ACS0;

			bit_rw_t<io_, bitpos::B2> BRME;

			bit_rw_t<io_, bitpos::B4> ABCS;
			bit_rw_t<io_, bitpos::B5> NFEN;
			bit_rw_t<io_, bitpos::B6> BGDM;
			bit_rw_t<io_, bitpos::B7> RXDESEL;
		};
		typedef semr_t<base + 0x07> SEMR_;
		static SEMR_ SEMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタ設定レジスタ (SNFR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct snfr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> NFCS;
		};
		typedef snfr_t<base + 0x08> SNFR_;
		static SNFR_ SNFR;


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C モードレジスタ１ (SIMR1)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct simr1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    IICM;

			bits_rw_t<io_, bitpos::B3, 5> IICDL;
		};
		typedef simr1_t<base + 0x09> SIMR1_;
		static SIMR1_ SIMR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C モードレジスタ２ (SIMR2)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template < uint32_t ofs>
		struct simr2_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> IICINTM;
			bit_rw_t<io_, bitpos::B1> IICCSC;

			bit_rw_t<io_, bitpos::B5> IICACKT;
		};
		typedef simr2_t<base + 0x0A> SIMR2_;
		static SIMR2_ SIMR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C モードレジスタ３ (SIMR3)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct simr3_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    IICSTAREQ;
			bit_rw_t <io_, bitpos::B1>    IICRSTAREQ;
			bit_rw_t <io_, bitpos::B2>    IICSTPREQ;
			bit_rw_t <io_, bitpos::B3>    IICSTIF;
			bits_rw_t<io_, bitpos::B4, 2> IICSDAS;
			bits_rw_t<io_, bitpos::B6, 2> IICSCLS;
		};
		typedef simr3_t<base + 0x0B> SIMR3_;
		static SIMR3_ SIMR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C ステータスレジスタ (SISR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sisr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> IICACKR;
		};
		typedef sisr_t<base + 0x0C> SISR_;
		static SISR_ SISR;


		//-----------------------------------------------------------------//
		/*!
			@brief  SPI モードレジスタ (SPMR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct spmr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SSE;
			bit_rw_t<io_, bitpos::B1> CTSE;
			bit_rw_t<io_, bitpos::B2> MSS;

			bit_rw_t<io_, bitpos::B4> MFF;

			bit_rw_t<io_, bitpos::B6> CKPOL;
			bit_rw_t<io_, bitpos::B7> CKPH;
		};
		typedef spmr_t<base + 0x0D> SPMR_;
		static SPMR_ SPMR;


		//-----------------------------------------------------------------//
		/*!
			@brief	モジュレーションデューティレジスタ（MDDR）ダミー
		*/
		//-----------------------------------------------------------------//
		typedef rw8_null_t<0x00000000> MDDR_;
		static MDDR_ MDDR;
	};
	template <uint32_t base> typename sci_ce_t<base>::RDR_ sci_ce_t<base>::RDR;
	template <uint32_t base> typename sci_ce_t<base>::TDR_ sci_ce_t<base>::TDR;
	template <uint32_t base> typename sci_ce_t<base>::SMR_ sci_ce_t<base>::SMR;
	template <uint32_t base> typename sci_ce_t<base>::SCR_ sci_ce_t<base>::SCR;
	template <uint32_t base> typename sci_ce_t<base>::SSR_ sci_ce_t<base>::SSR;
	template <uint32_t base> typename sci_ce_t<base>::SCMR_ sci_ce_t<base>::SCMR;
	template <uint32_t base> typename sci_ce_t<base>::BRR_ sci_ce_t<base>::BRR;
	template <uint32_t base> typename sci_ce_t<base>::SEMR_ sci_ce_t<base>::SEMR;
	template <uint32_t base> typename sci_ce_t<base>::SNFR_ sci_ce_t<base>::SNFR;
	template <uint32_t base> typename sci_ce_t<base>::SIMR1_ sci_ce_t<base>::SIMR1;
	template <uint32_t base> typename sci_ce_t<base>::SIMR2_ sci_ce_t<base>::SIMR2;
	template <uint32_t base> typename sci_ce_t<base>::SIMR3_ sci_ce_t<base>::SIMR3;
	template <uint32_t base> typename sci_ce_t<base>::SISR_ sci_ce_t<base>::SISR;
	template <uint32_t base> typename sci_ce_t<base>::SPMR_ sci_ce_t<base>::SPMR;
	template <uint32_t base> typename sci_ce_t<base>::MDDR_ sci_ce_t<base>::MDDR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCIgj クラス
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct sci_gj_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  レシーブデータレジスタ (RDR)
		*/
		//-----------------------------------------------------------------//
		typedef ro8_t<base + 0x05> RDR_;
		static RDR_ RDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  レシーブデータレジスタ H、L、HL (RDRH 、 RDRL 、 RDRHL)
		*/
		//-----------------------------------------------------------------//
		typedef ro8_t<base + 0x10> RDRH_;
		static RDRH_ RDRH;
		typedef ro8_t<base + 0x11> RDRL_;
		static RDRL_ RDRL;
		typedef ro16_t<base + 0x10> RDRHL_;
		static RDRHL_ RDRHL;


		//-----------------------------------------------------------------//
		/*!
			@brief  トランスミットデータレジスタ (TDR)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x03> TDR_;
		static TDR_ TDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  トランスミットデータレジスタ H、L、HL（TDRH、TDRL、TDRHL）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x0E> TDRH_;
		static TDRH_ TDRH;
		typedef rw8_t<base + 0x0F> TDRL_;
		static TDRL_ TDRL;
		typedef rw16_t<base + 0x0E> TDRHL_;
		static TDRHL_ TDRHL;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルモードレジスタ (SMR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct smr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			// 非スマートカードインタフェースモード SCMR.SMIF = 0
			bits_rw_t<io_, bitpos::B0, 2> CKS;
			bit_rw_t <io_, bitpos::B2>	  MP;
			bit_rw_t <io_, bitpos::B3>	  STOP;
			bit_rw_t <io_, bitpos::B4>	  PM;
			bit_rw_t <io_, bitpos::B5>	  PE;
			bit_rw_t <io_, bitpos::B6>	  CHR;
			bit_rw_t <io_, bitpos::B7>	  CM;

			// スマートカードインタフェースモード SCMR.SMIF = 1
			bits_rw_t<io_, bitpos::B2, 2> BCP;
			bit_rw_t <io_, bitpos::B6>	  BLK;
			bit_rw_t <io_, bitpos::B7>	  GM;
		};
		typedef smr_t<base + 0x00> SMR_;
		static SMR_ SMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルコントロールレジスタ (SCR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct scr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> CKE;
			bit_rw_t <io_, bitpos::B2>	  TEIE;
			bit_rw_t <io_, bitpos::B3>	  MPIE;
			bit_rw_t <io_, bitpos::B4>	  RE;
			bit_rw_t <io_, bitpos::B5>	  TE;
			bit_rw_t <io_, bitpos::B6>	  RIE;
			bit_rw_t <io_, bitpos::B7>	  TIE;
		};
		typedef scr_t<base + 0x02> SCR_;
		static SCR_ SCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルステータスレジスタ (SSR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ssr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> MPBT;
			bit_rw_t<io_, bitpos::B1> MPB;
			bit_rw_t<io_, bitpos::B2> TEND;
			bit_rw_t<io_, bitpos::B3> PER;
			bit_rw_t<io_, bitpos::B4> FER;
			bit_rw_t<io_, bitpos::B4> ERS;  // スマートカードインタフェースモード時
			bit_rw_t<io_, bitpos::B5> ORER;
			bit_rw_t<io_, bitpos::B6> RDRF;  // SCIe では利用不可
			bit_rw_t<io_, bitpos::B7> TDRE;  // SCIe では利用不可
		};
		typedef ssr_t<base + 0x04> SSR_;
		static SSR_ SSR;


 		//-----------------------------------------------------------------//
		/*!
			@brief  スマートカードモードレジスタ (SCMR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct scmr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SMIF;

			bit_rw_t<io_, bitpos::B2> SINV;
			bit_rw_t<io_, bitpos::B3> SDIR;
			bit_rw_t<io_, bitpos::B4> CHR1;

			bit_rw_t<io_, bitpos::B7> BCP2;
		};
		typedef scmr_t<base + 0x06> SCMR_;
		static SCMR_ SCMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ビットレートレジスタ (BRR)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x01> BRR_;
		static BRR_ BRR;


		//-----------------------------------------------------------------//
		/*!
			@brief	モジュレーションデューティレジスタ（MDDR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x12> MDDR_;
		static MDDR_ MDDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアル拡張レジスタ (SEMR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct semr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> ACS0;

			bit_rw_t<io_, bitpos::B2> BRME;
			bit_rw_t<io_, bitpos::B4> ABCSE;  // SCIj で追加機能
			bit_rw_t<io_, bitpos::B4> ABCS;
			bit_rw_t<io_, bitpos::B5> NFEN;
			bit_rw_t<io_, bitpos::B6> BGDM;
			bit_rw_t<io_, bitpos::B7> RXDESEL;
		};
		typedef semr_t<base + 0x07> SEMR_;
		static SEMR_ SEMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタ設定レジスタ (SNFR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct snfr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> NFCS;
		};
		typedef snfr_t<base + 0x08> SNFR_;
		static SNFR_ SNFR;


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C モードレジスタ１ (SIMR1)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct simr1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    IICM;

			bits_rw_t<io_, bitpos::B3, 5> IICDL;
		};
		typedef simr1_t<base + 0x09> SIMR1_;
		static SIMR1_ SIMR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C モードレジスタ２ (SIMR2)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template < uint32_t ofs>
		struct simr2_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> IICINTM;
			bit_rw_t<io_, bitpos::B1> IICCSC;

			bit_rw_t<io_, bitpos::B5> IICACKT;
		};
		typedef simr2_t<base + 0x0A> SIMR2_;
		static SIMR2_ SIMR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C モードレジスタ３ (SIMR3)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct simr3_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    IICSTAREQ;
			bit_rw_t <io_, bitpos::B1>    IICRSTAREQ;
			bit_rw_t <io_, bitpos::B2>    IICSTPREQ;
			bit_rw_t <io_, bitpos::B3>    IICSTIF;
			bits_rw_t<io_, bitpos::B4, 2> IICSDAS;
			bits_rw_t<io_, bitpos::B6, 2> IICSCLS;
		};
		typedef simr3_t<base + 0x0B> SIMR3_;
		static SIMR3_ SIMR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C ステータスレジスタ (SISR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sisr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> IICACKR;
		};
		typedef sisr_t<base + 0x0C> SISR_;
		static SISR_ SISR;


		//-----------------------------------------------------------------//
		/*!
			@brief  SPI モードレジスタ (SPMR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct spmr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SSE;
			bit_rw_t<io_, bitpos::B1> CTSE;
			bit_rw_t<io_, bitpos::B2> MSS;

			bit_rw_t<io_, bitpos::B4> MFF;

			bit_rw_t<io_, bitpos::B6> CKPOL;
			bit_rw_t<io_, bitpos::B7> CKPH;
		};
		typedef spmr_t<base + 0x0D> SPMR_;
		static SPMR_ SPMR;
	};
	template <uint32_t base> typename sci_gj_t<base>::RDR_ sci_gj_t<base>::RDR;
	template <uint32_t base> typename sci_gj_t<base>::RDRH_ sci_gj_t<base>::RDRH;
	template <uint32_t base> typename sci_gj_t<base>::RDRL_ sci_gj_t<base>::RDRL;
	template <uint32_t base> typename sci_gj_t<base>::RDRHL_ sci_gj_t<base>::RDRHL;
	template <uint32_t base> typename sci_gj_t<base>::TDR_ sci_gj_t<base>::TDR;
	template <uint32_t base> typename sci_gj_t<base>::TDRH_ sci_gj_t<base>::TDRH;
	template <uint32_t base> typename sci_gj_t<base>::TDRL_ sci_gj_t<base>::TDRL;
	template <uint32_t base> typename sci_gj_t<base>::TDRHL_ sci_gj_t<base>::TDRHL;
	template <uint32_t base> typename sci_gj_t<base>::SMR_ sci_gj_t<base>::SMR;
	template <uint32_t base> typename sci_gj_t<base>::SCR_ sci_gj_t<base>::SCR;
	template <uint32_t base> typename sci_gj_t<base>::SSR_ sci_gj_t<base>::SSR;
	template <uint32_t base> typename sci_gj_t<base>::SCMR_ sci_gj_t<base>::SCMR;
	template <uint32_t base> typename sci_gj_t<base>::BRR_ sci_gj_t<base>::BRR;
	template <uint32_t base> typename sci_gj_t<base>::MDDR_ sci_gj_t<base>::MDDR;
	template <uint32_t base> typename sci_gj_t<base>::SEMR_ sci_gj_t<base>::SEMR;
	template <uint32_t base> typename sci_gj_t<base>::SNFR_ sci_gj_t<base>::SNFR;
	template <uint32_t base> typename sci_gj_t<base>::SIMR1_ sci_gj_t<base>::SIMR1;
	template <uint32_t base> typename sci_gj_t<base>::SIMR2_ sci_gj_t<base>::SIMR2;
	template <uint32_t base> typename sci_gj_t<base>::SIMR3_ sci_gj_t<base>::SIMR3;
	template <uint32_t base> typename sci_gj_t<base>::SISR_ sci_gj_t<base>::SISR;
	template <uint32_t base> typename sci_gj_t<base>::SPMR_ sci_gj_t<base>::SPMR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCI FIFO クラス（sci_gj_t）に追加する機能（FIFO 制御）
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct sci_fifo_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  受信 FIFO データレジスタ (FRDR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct frdr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 9> RDAT;
			bit_rw_t <io_, bitpos::B9>    MPB;
			bit_rw_t <io_, bitpos::B10>   DR;
			bit_rw_t <io_, bitpos::B11>   PER;
			bit_rw_t <io_, bitpos::B12>   FER;
			bit_rw_t <io_, bitpos::B13>   ORER;
			bit_rw_t <io_, bitpos::B14>   RDF;
		};
		typedef frdr_t<base + 0x10> FRDR_;
		static FRDR_ FRDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  送信 FIFO データレジスタ (FTDR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ftdr_t : public wo16_t<ofs> {
			typedef wo16_t<ofs> io_;
			using io_::operator =;

			bits_rw_t<io_, bitpos::B0, 9> RDAT;
			bit_rw_t <io_, bitpos::B9>    MPBT;
		};
		typedef ftdr_t<base + 0x0E> FTDR_;
		static FTDR_ FTDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルステータスレジスタ (SSRFIFO)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ssrfifo_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DR;

			bit_rw_t<io_, bitpos::B2> TEND;
			bit_rw_t<io_, bitpos::B3> PER;
			bit_rw_t<io_, bitpos::B4> FER;
			bit_rw_t<io_, bitpos::B5> ORER;
			bit_rw_t<io_, bitpos::B6> RDRF;
			bit_rw_t<io_, bitpos::B7> TDRE;
		};
		typedef ssrfifo_t<base + 0x04> SSRFIFO_;
		static SSRFIFO_ SSRFIFO;


		//-----------------------------------------------------------------//
		/*!
			@brief  FIFO コントロールレジスタ (FCR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct fcr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     FM;
			bit_rw_t <io_, bitpos::B1>     RFRST;
			bit_rw_t <io_, bitpos::B2>     TFRST;
			bit_rw_t <io_, bitpos::B3>     DRES;
			bits_rw_t<io_, bitpos::B4,  4> TTRG;
			bits_rw_t<io_, bitpos::B8,  4> RTRG;
			bits_rw_t<io_, bitpos::B12, 4> RSTRG;
		};
		typedef fcr_t<base + 0x14> FCR_;
		static FCR_ FCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  FIFO データカウントレジスタ (FDR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct fdr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5> R;

			bits_rw_t<io_, bitpos::B8, 5> T;
		};
		typedef fdr_t<base + 0x16> FDR_;
		static FDR_ FDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ラインステータスレジスタ (LSR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct lsr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    ORER;

			bits_rw_t<io_, bitpos::B2, 5> FNUM;

			bits_rw_t<io_, bitpos::B8, 5> PNUM;
		};
		typedef lsr_t<base + 0x18> LSR_;
		static LSR_ LSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  比較データレジスタ (CDR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cdr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 9> CMPD;
		};
		typedef cdr_t<base + 0x1A> CDR_;
		static CDR_ CDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  データ比較制御レジスタ (DCCR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dccr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>     DCMF;

			bit_rw_t<io_, bitpos::B3>     DPER;
			bit_rw_t<io_, bitpos::B4>     DFER;

			bit_rw_t<io_, bitpos::B6>     IDSEL;
			bit_rw_t<io_, bitpos::B7>     DCME;
		};
		typedef dccr_t<base + 0x13> DCCR_;
		static DCCR_ DCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルポートレジスタ (SPTR)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sptr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>     RXDMON;
			bit_rw_t<io_, bitpos::B1>     SPB2DT;
			bit_rw_t<io_, bitpos::B2>     SPB2IO;
		};
		typedef sptr_t<base + 0x13> SPTR_;
		static SPTR_ SPTR;
	};
	template <uint32_t base> typename sci_fifo_t<base>::FRDR_ sci_fifo_t<base>::FRDR;
	template <uint32_t base> typename sci_fifo_t<base>::SSRFIFO_ sci_fifo_t<base>::SSRFIFO;
	template <uint32_t base> typename sci_fifo_t<base>::FCR_ sci_fifo_t<base>::FCR;
	template <uint32_t base> typename sci_fifo_t<base>::FDR_ sci_fifo_t<base>::FDR;
	template <uint32_t base> typename sci_fifo_t<base>::LSR_ sci_fifo_t<base>::LSR;
	template <uint32_t base> typename sci_fifo_t<base>::CDR_ sci_fifo_t<base>::CDR;
	template <uint32_t base> typename sci_fifo_t<base>::DCCR_ sci_fifo_t<base>::DCCR;
	template <uint32_t base> typename sci_fifo_t<base>::SPTR_ sci_fifo_t<base>::SPTR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCI ext クラス（拡張シリアル）
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct sci_ext_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  拡張シリアルモード有効レジスタ (ESMER) 
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct esmer_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> ESME;
		};
		typedef esmer_t<base + 0x20> ESMER_;
		static ESMER_ ESMER;


		//-----------------------------------------------------------------//
		/*!
			@brief  コントロールレジスタ 0（CR0）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cr0_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_ro_t<io_, bitpos::B1> SCSF;
			bit_ro_t<io_, bitpos::B2> RXDSF;
			bit_rw_t<io_, bitpos::B3> BRME;
		};
		typedef cr0_t<base + 0x21> CR0_;
		static CR0_ CR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  コントロールレジスタ 1（CR1）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cr1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_ro_t <io_, bitpos::B0>    BFE;
			bit_ro_t <io_, bitpos::B1>    CF0RE;
			bits_ro_t<io_, bitpos::B2, 2> CF1DS;
			bit_rw_t <io_, bitpos::B4>    PIBE;
			bits_ro_t<io_, bitpos::B5, 3> PIBS;
		};
		typedef cr1_t<base + 0x22> CR1_;
		static CR1_ CR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  コントロールレジスタ 2（CR2）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cr2_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_ro_t<io_, bitpos::B0, 3> DFCS;

			bits_ro_t<io_, bitpos::B4, 2> BCCS;
			bits_ro_t<io_, bitpos::B6, 2> RTS;
		};
		typedef cr2_t<base + 0x23> CR2_;
		static CR2_ CR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  コントロールレジスタ 3（CR3）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cr3_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_ro_t <io_, bitpos::B0>    SDST;
		};
		typedef cr3_t<base + 0x24> CR3_;
		static CR3_ CR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートコントロールレジスタ（PCR）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_ro_t <io_, bitpos::B0>    TXDXPS;
			bit_ro_t <io_, bitpos::B1>    RXDXPS;

			bit_ro_t <io_, bitpos::B4>    SHARPS;
		};
		typedef pcr_t<base + 0x25> PCR_;
		static PCR_ PCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みコントロールレジスタ（ICR）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct icr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_ro_t <io_, bitpos::B0>    BFDIE;
			bit_ro_t <io_, bitpos::B1>    CF0MIE;
			bit_ro_t <io_, bitpos::B2>    CF1MIE;
			bit_ro_t <io_, bitpos::B3>    PIBDIE;
			bit_ro_t <io_, bitpos::B4>    BCDIE;
			bit_ro_t <io_, bitpos::B5>    AEDIE;
		};
		typedef icr_t<base + 0x26> ICR_;
		static ICR_ ICR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ステータスレジスタ（STR）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct str_t : public ro8_t<ofs> {
			typedef ro8_t<ofs> io_;
			using io_::operator ();

			bit_ro_t <io_, bitpos::B0>    BFDF;
			bit_ro_t <io_, bitpos::B1>    CF0MF;
			bit_ro_t <io_, bitpos::B2>    CF1MF;
			bit_ro_t <io_, bitpos::B3>    PIBDF;
			bit_ro_t <io_, bitpos::B4>    BCDF;
			bit_ro_t <io_, bitpos::B5>    AEDF;
		};
		typedef str_t<base + 0x27> STR_;
		static STR_ STR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ステータスクリアレジスタ（STCR）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct stcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_ro_t <io_, bitpos::B0>    BFDCL;
			bit_ro_t <io_, bitpos::B1>    CF0MCL;
			bit_ro_t <io_, bitpos::B2>    CF1MCL;
			bit_ro_t <io_, bitpos::B3>    PIBDCL;
			bit_ro_t <io_, bitpos::B4>    BCDCL;
			bit_ro_t <io_, bitpos::B5>    AEDCL;
		};
		typedef stcr_t<base + 0x28> STCR_;
		static STCR_ STCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  Control Field 0 データレジスタ（CF0DR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x29> CF0DR_;
		static CF0DR_ CF0DR;


		//-----------------------------------------------------------------//
		/*!
			@brief  Control Field 0 コンペアイネーブルレジスタ（CF0CR）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cf0cr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_ro_t <io_, bitpos::B0>    DF0CE0;
			bit_ro_t <io_, bitpos::B1>    DF0CE1;
			bit_ro_t <io_, bitpos::B2>    DF0CE2;
			bit_ro_t <io_, bitpos::B3>    DF0CE3;
			bit_ro_t <io_, bitpos::B4>    DF0CE4;
			bit_ro_t <io_, bitpos::B5>    DF0CE5;
			bit_ro_t <io_, bitpos::B6>    DF0CE6;
			bit_ro_t <io_, bitpos::B7>    DF0CE7;
		};
		typedef cf0cr_t<base + 0x2A> CF0CR_;
		static CF0CR_ CF0CR;


		//-----------------------------------------------------------------//
		/*!
			@brief  Control Field 0 受信データレジスタ（CF0RR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x2B> CF0RR_;
		static CF0RR_ CF0RR;


		//-----------------------------------------------------------------//
		/*!
			@brief  プライマリ Control Field 1 データレジスタ（PCF1DR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x2C> PCF1DR_;
		static PCF1DR_ PCF1DR;


		//-----------------------------------------------------------------//
		/*!
			@brief  セカンダリ Control Field 1 データレジスタ（SCF1DR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x2D> SCF1DR_;
		static SCF1DR_ SCF1DR;


		//-----------------------------------------------------------------//
		/*!
			@brief  Control Field 1 コンペアイネーブルレジスタ（CF1CR）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cf1cr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_ro_t <io_, bitpos::B0>    CF1CE0;
			bit_ro_t <io_, bitpos::B1>    CF1CE1;
			bit_ro_t <io_, bitpos::B2>    CF1CE2;
			bit_ro_t <io_, bitpos::B3>    CF1CE3;
			bit_ro_t <io_, bitpos::B4>    CF1CE4;
			bit_ro_t <io_, bitpos::B5>    CF1CE5;
			bit_ro_t <io_, bitpos::B6>    CF1CE6;
			bit_ro_t <io_, bitpos::B7>    CF1CE7;
		};
		typedef cf1cr_t<base + 0x2E> CF1CR_;
		static CF1CR_ CF1CR;


		//-----------------------------------------------------------------//
		/*!
			@brief  Control Field 1 受信データレジスタ（CF1RR）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x2F> CF1RR_;
		static CF1RR_ CF1RR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマコントロールレジスタ（TCR）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_ro_t <io_, bitpos::B0>    TCST;
		};
		typedef tcr_t<base + 0x30> TCR_;
		static TCR_ TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマモードレジスタ（TMR）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tmr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_ro_t<io_, bitpos::B0, 2> TOMS;

			bit_ro_t <io_, bitpos::B3>    TWRC;
			bits_ro_t<io_, bitpos::B4, 3> TCSS;
		};
		typedef tmr_t<base + 0x31> TMR_;
		static TMR_ TMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマプリスケーラレジスタ（TPRE）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x32> TPRE_;
		static TPRE_ TPRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウントレジスタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x33> TCNT_;
		static TCNT_ TCNT;
	};
	template <uint32_t base> typename sci_ext_t<base>::ESMER_ sci_ext_t<base>::ESMER;
	template <uint32_t base> typename sci_ext_t<base>::CR0_ sci_ext_t<base>::CR0;
	template <uint32_t base> typename sci_ext_t<base>::CR1_ sci_ext_t<base>::CR1;
	template <uint32_t base> typename sci_ext_t<base>::CR2_ sci_ext_t<base>::CR2;
	template <uint32_t base> typename sci_ext_t<base>::CR3_ sci_ext_t<base>::CR3;
	template <uint32_t base> typename sci_ext_t<base>::PCR_ sci_ext_t<base>::PCR;
	template <uint32_t base> typename sci_ext_t<base>::ICR_ sci_ext_t<base>::ICR;
	template <uint32_t base> typename sci_ext_t<base>::STR_ sci_ext_t<base>::STR;
	template <uint32_t base> typename sci_ext_t<base>::STCR_ sci_ext_t<base>::STCR;
	template <uint32_t base> typename sci_ext_t<base>::CF0DR_ sci_ext_t<base>::CF0DR;
	template <uint32_t base> typename sci_ext_t<base>::CF0RR_ sci_ext_t<base>::CF0RR;
	template <uint32_t base> typename sci_ext_t<base>::PCF1DR_ sci_ext_t<base>::PCF1DR;
	template <uint32_t base> typename sci_ext_t<base>::SCF1DR_ sci_ext_t<base>::SCF1DR;
	template <uint32_t base> typename sci_ext_t<base>::CF1CR_ sci_ext_t<base>::CF1CR;
	template <uint32_t base> typename sci_ext_t<base>::CF1RR_ sci_ext_t<base>::CF1RR;
	template <uint32_t base> typename sci_ext_t<base>::TCR_ sci_ext_t<base>::TCR;
	template <uint32_t base> typename sci_ext_t<base>::TMR_ sci_ext_t<base>::TMR;
	template <uint32_t base> typename sci_ext_t<base>::TPRE_ sci_ext_t<base>::TPRE;
	template <uint32_t base> typename sci_ext_t<base>::TCNT_ sci_ext_t<base>::TCNT;
}
