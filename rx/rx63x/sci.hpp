#pragma once
//=====================================================================//
/*!	@file
	@brief	RX63x グループ・SCI 定義 @n
			Copyright 2013 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "../io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCIc, SCId 定義基底クラス
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct sci_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルモードレジスタ (SMR)
		*/
		//-----------------------------------------------------------------//
		typedef io8<base + 0x00> smr_io;
		struct smr_t : public smr_io {
			using smr_io::operator =;
			using smr_io::operator ();
			using smr_io::operator |=;
			using smr_io::operator &=;

			bits_t<smr_io, 0, 2>  CKS;
			bit_t< smr_io, 2>	  MP;
			bit_t< smr_io, 3>	  STOP;
			bit_t< smr_io, 4>	  PM;
			bit_t< smr_io, 5>	  PE;
			bit_t< smr_io, 6>	  CHR;
			bit_t< smr_io, 7>	  CM;

			bits_t< smr_io, 2, 2> BCP;
			bit_t< smr_io,  6>	  BLK;
			bit_t< smr_io,  7>	  GM;
		};
		static smr_t SMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ビットレートレジスタ (BRR)
		*/
		//-----------------------------------------------------------------//
		static io8<base + 0x01> BRR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルコントロールレジスタ (SCR)
		*/
		//-----------------------------------------------------------------//
		typedef io8<base + 0x02> scr_io;
		struct scr_t : public scr_io {
			using scr_io::operator =;
			using scr_io::operator ();
			using scr_io::operator |=;
			using scr_io::operator &=;

			bits_t<scr_io, 0, 2>	CKE;
			bit_t< scr_io, 2>	TEIE;
			bit_t< scr_io, 3>	MPIE;
			bit_t< scr_io, 4>	RE;
			bit_t< scr_io, 5>	TE;
			bit_t< scr_io, 6>	RIE;
			bit_t< scr_io, 7>	TIE;
		};
		static scr_t SCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  トランスミットデータレジスタ (TDR)
		*/
		//-----------------------------------------------------------------//
		static io8<base + 0x03> TDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルステータスレジスタ (SSR)
		*/
		//-----------------------------------------------------------------//
		typedef io8<base + 0x04> ssr_io;
		struct ssr_t : public ssr_io {
			using ssr_io::operator =;
			using ssr_io::operator ();
			using ssr_io::operator |=;
			using ssr_io::operator &=;

			bit_t<ssr_io, 0>	MPBT;
			bit_t<ssr_io, 1>	MPB;
			bit_t<ssr_io, 2>	TEND;
			bit_t<ssr_io, 3>	PER;
			bit_t<ssr_io, 4>	FER;
			bit_t<ssr_io, 4>	ERS;
			bit_t<ssr_io, 5>	ORER;
		};
		static ssr_t SSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  レシーブデータレジスタ (RDR)
		*/
		//-----------------------------------------------------------------//
		static io8_ro<base + 0x05> RDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  スマートカードモードレジスタ (SCMR)
		*/
		//-----------------------------------------------------------------//
		typedef io8<base + 0x06> scmr_io;
		struct scmr_t : public scmr_io {
			using scmr_io::operator =;
			using scmr_io::operator ();
			using scmr_io::operator |=;
			using scmr_io::operator &=;

			bit_t<scmr_io, 0>	SMIF;
			bit_t<scmr_io, 2>	SINV;
			bit_t<scmr_io, 3>	SDIR;
			bit_t<scmr_io, 7>	BCP2;
		};
		static scmr_t SCMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアル拡張レジスタ (SEMR)
		*/
		//-----------------------------------------------------------------//
		typedef io8<base + 0x07> semr_io;
		struct semr_t : public semr_io {
			using semr_io::operator =;
			using semr_io::operator ();
			using semr_io::operator |=;
			using semr_io::operator &=;

			bit_t<semr_io, 0>	ACS0;
			bit_t<semr_io, 4>	ABCS;
			bit_t<semr_io, 5>	NFEN;
		};
		static semr_t SEMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタ設定レジスタ (SNFR)
		*/
		//-----------------------------------------------------------------//
		typedef io8<base + 0x08> snfr_io;
		struct snfr_t : public snfr_io {
			using snfr_io::operator =;
			using snfr_io::operator ();
			using snfr_io::operator |=;
			using snfr_io::operator &=;

			bits<snfr_io, 0, 3>	NFCS;
		};
		static snfr_t SNFR;


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C モードレジスタ１ (SIMR1)
		*/
		//-----------------------------------------------------------------//
		typedef io8<base + 0x09> simr1_io;
		struct simr1_t : public simr1_io {
			using simr1_io::operator =;
			using simr1_io::operator ();
			using simr1_io::operator |=;
			using simr1_io::operator &=;

			bit_t< simr1_io, 0>	    IICM;
			bits_t<simr1_io, 3, 5>	IICDL;
		};
		static simr1_t SIMR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C モードレジスタ２ (SIMR2)
		*/
		//-----------------------------------------------------------------//
		typedef io8<base + 0x0a> simr2_io;
		struct simr2_t : public simr2_io {
			using simr2_io::operator =;
			using simr2_io::operator ();
			using simr2_io::operator |=;
			using simr2_io::operator &=;

			bit_t<simr2_io, 0>	    IICINTM;
			bit_t<simr2_io, 1>	    IICCSC;
			bit_t<simr2_io, 5>	    IICACKT;
		};
		static simr2_t SIMR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C モードレジスタ３ (SIMR3)
		*/
		//-----------------------------------------------------------------//
		typedef io8<base + 0x0b> simr3_io;
		struct simr3_t : public simr3_io {
			using simr3_io::operator =;
			using simr3_io::operator ();
			using simr3_io::operator |=;
			using simr3_io::operator &=;

			bit_t< simr3_io, 0>	    IICSTAREQ;
			bit_t< simr3_io, 1>	    IICRSTAREQ;
			bit_t< simr3_io, 2>	    IICSTPREQ;
			bit_t< simr3_io, 3>	    IICSTIF;
			bits_t<simr3_io, 4, 2>	IICSDAS;
			bits_t<simr3_io, 6, 2>	IICSCLS;
		};
		static simr3_t SIMR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C ステータスレジスタ (SISR)
		*/
		//-----------------------------------------------------------------//
		typedef io8<base + 0x0c> sisr_io;
		struct sisr_t : public sisr_io {
			using sisr_io::operator =;
			using sisr_io::operator ();
			using sisr_io::operator |=;
			using sisr_io::operator &=;

			bit_t<sisr_io, 0>	IICACKR;
		};
		static sisr_t SISR;


		//-----------------------------------------------------------------//
		/*!
			@brief  SPI モードレジスタ (SPMR)
		*/
		//-----------------------------------------------------------------//
		typedef io8<base + 0x0d> spmr_io;
		struct spmr_t : public spmr_io {
			using spmr_io::operator =;
			using spmr_io::operator ();
			using spmr_io::operator |=;
			using spmr_io::operator &=;

			bit_t<spmr_io, 0>	SSE;
			bit_t<spmr_io, 1>	CTSE;
			bit_t<spmr_io, 2>	MSS;
			bit_t<spmr_io, 4>	MFF;
			bit_t<spmr_io, 6>	CKPOL;
			bit_t<spmr_io, 7>	CKPH;
		};
		static spmr_t SPMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  拡張シリアルモード有効レジスタ (ESMER) @n
					※SIC12 にのみ有効なレジスタ
		*/
		//-----------------------------------------------------------------//
		typedef io8<base + 0x20> esmer_io;
		struct esmer_t : public esmer_io {
			using esmer_io::operator =;
			using esmer_io::operator ();
			using esmer_io::operator |=;
			using esmer_io::operator &=;

			bit<esmer_io, 0>	ESME;
		};
		static esmer_t ESMER;




		//-----------------------------------------------------------------//
		/*!
			@brief  チャネルを返す
			@return チャネル（０、１、２、３、１２）
		*/
		//-----------------------------------------------------------------//
		static uint32_t get_chanel() {
			if(base == 0x0008b300) return 12; 
			return (base >> 5) & 3;
		}
	};

	typedef sci_t<0x0008a000> SCI0;
	typedef sci_t<0x0008a020> SCI1;
	typedef sci_t<0x0008a040> SCI2;
	typedef sci_t<0x0008a060> SCI3;
	typedef sci_t<0x0008b300> SCI12;
}
