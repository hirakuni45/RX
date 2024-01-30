#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ SCI ベース定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
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
		static inline ro8_t<base + 0x05> RDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  トランスミットデータレジスタ (TDR)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x03> TDR;


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
		static inline smr_t<base + 0x00> SMR;


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
		static inline scr_t<base + 0x02> SCR;


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
		static inline ssr_t<base + 0x04> SSR;


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
		static inline scmr_t<base + 0x06> SCMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ビットレートレジスタ (BRR)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x01> BRR;


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
		static inline semr_t<base + 0x07> SEMR;


		//-----------------------------------------------------------------//
		/*!
			@brief	モジュレーションデューティレジスタ（MDDR）ダミー
		*/
		//-----------------------------------------------------------------//
		static inline rw8_null_t<0x00000000> MDDR;
	};


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
		static inline ro8_t<base + 0x05> RDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  トランスミットデータレジスタ (TDR)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x03> TDR;


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
		static inline smr_t<base + 0x00> SMR;


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
		static inline scr_t<base + 0x02> SCR;


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
		static inline ssr_t<base + 0x04> SSR;


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
		static inline scmr_t<base + 0x06> SCMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ビットレートレジスタ (BRR)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x01> BRR;


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
		static inline semr_t<base + 0x07> SEMR;


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
		static inline snfr_t<base + 0x08> SNFR;


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
		static inline simr1_t<base + 0x09> SIMR1;


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
		static inline simr2_t<base + 0x0A> SIMR2;


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
		static inline simr3_t<base + 0x0B> SIMR3;


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
		static inline sisr_t<base + 0x0C> SISR;


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
		static inline spmr_t<base + 0x0D> SPMR;


		//-----------------------------------------------------------------//
		/*!
			@brief	モジュレーションデューティレジスタ（MDDR）ダミー
		*/
		//-----------------------------------------------------------------//
		static inline rw8_null_t<0x00000000> MDDR;
	};


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
		static inline ro8_t<base + 0x05> RDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  レシーブデータレジスタ H、L、HL (RDRH 、 RDRL 、 RDRHL)
		*/
		//-----------------------------------------------------------------//
		static inline ro8_t<base + 0x10> RDRH;
		static inline ro8_t<base + 0x11> RDRL;
		static inline ro16_t<base + 0x10> RDRHL;


		//-----------------------------------------------------------------//
		/*!
			@brief  トランスミットデータレジスタ (TDR)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x03> TDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  トランスミットデータレジスタ H、L、HL（TDRH、TDRL、TDRHL）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x0E> TDRH;
		static inline rw8_t<base + 0x0F> TDRL;
		static inline rw16_t<base + 0x0E> TDRHL;


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
		static inline smr_t<base + 0x00> SMR;


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
		static inline scr_t<base + 0x02> SCR;


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
		static inline ssr_t<base + 0x04> SSR;


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
		static inline scmr_t<base + 0x06> SCMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ビットレートレジスタ (BRR)
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x01> BRR;


		//-----------------------------------------------------------------//
		/*!
			@brief	モジュレーションデューティレジスタ（MDDR）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x12> MDDR;


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
		static inline semr_t<base + 0x07> SEMR;


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
		static inline snfr_t<base + 0x08> SNFR;


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
		static inline simr1_t<base + 0x09> SIMR1;


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
		static inline simr2_t<base + 0x0A> SIMR2;


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
		static inline simr3_t<base + 0x0B> SIMR3;


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
		static inline sisr_t<base + 0x0C> SISR;


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
		static inline spmr_t<base + 0x0D> SPMR;
	};


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
		static inline frdr_t<base + 0x10> FRDR;


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
		static inline ftdr_t<base + 0x0E> FTDR;


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
		static inline ssrfifo_t<base + 0x04> SSRFIFO;


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
		static inline fcr_t<base + 0x14> FCR;


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
		static inline fdr_t<base + 0x16> FDR;


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
		static inline lsr_t<base + 0x18> LSR;


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
		static inline cdr_t<base + 0x1A> CDR;


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
		static inline dccr_t<base + 0x13> DCCR;


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
		static inline sptr_t<base + 0x13> SPTR;
	};


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
		static inline esmer_t<base + 0x20> ESMER;


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
		static inline cr0_t<base + 0x21> CR0;


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
		static inline cr1_t<base + 0x22> CR1;


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
		static inline cr2_t<base + 0x23> CR2;


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
		static inline cr3_t<base + 0x24> CR3;


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
		static inline pcr_t<base + 0x25> PCR;


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
		static inline icr_t<base + 0x26> ICR;


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
		static inline str_t<base + 0x27> STR;


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
		static inline stcr_t<base + 0x28> STCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  Control Field 0 データレジスタ（CF0DR）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x29> CF0DR;


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
		static inline cf0cr_t<base + 0x2A> CF0CR;


		//-----------------------------------------------------------------//
		/*!
			@brief  Control Field 0 受信データレジスタ（CF0RR）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x2B> CF0RR;


		//-----------------------------------------------------------------//
		/*!
			@brief  プライマリ Control Field 1 データレジスタ（PCF1DR）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x2C> PCF1DR;


		//-----------------------------------------------------------------//
		/*!
			@brief  セカンダリ Control Field 1 データレジスタ（SCF1DR）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x2D> SCF1DR;


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
		static inline cf1cr_t<base + 0x2E> CF1CR;


		//-----------------------------------------------------------------//
		/*!
			@brief  Control Field 1 受信データレジスタ（CF1RR）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x2F> CF1RR;


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
		static inline tcr_t<base + 0x30> TCR;


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
		static inline tmr_t<base + 0x31> TMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマプリスケーラレジスタ（TPRE）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x32> TPRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  タイマカウントレジスタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x33> TCNT;
	};
}
