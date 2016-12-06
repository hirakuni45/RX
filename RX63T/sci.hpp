#pragma once
//=====================================================================//
/*!	@file
	@brief	RX63T グループ・SCI 定義 @n
			Copyright 2013 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/io_utils.hpp"
#include "RX63T/peripheral.hpp"
#include "RX63T/icu.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCIc, SCId 定義基底クラス
		@param[in]	base	ベース・アドレス
		@param[in]	t		ペリフェラル型
		@param[in]	rxv		受信ベクター
		@param[in]	tev		送信ベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral t, ICU::VECTOR rxv, ICU::VECTOR tev>
	struct sci_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルモードレジスタ (SMR)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x00> smr_io;
		struct smr_t : public smr_io {
			using smr_io::operator =;
			using smr_io::operator ();
			using smr_io::operator |=;
			using smr_io::operator &=;

			bits_rw_t<smr_io, bitpos::B0, 2>  CKS;
			bit_rw_t< smr_io, bitpos::B2>	  MP;
			bit_rw_t< smr_io, bitpos::B3>	  STOP;
			bit_rw_t< smr_io, bitpos::B4>	  PM;
			bit_rw_t< smr_io, bitpos::B5>	  PE;
			bit_rw_t< smr_io, bitpos::B6>	  CHR;
			bit_rw_t< smr_io, bitpos::B7>	  CM;

			bits_rw_t< smr_io, bitpos::B2, 2> BCP;
			bit_rw_t< smr_io, bitpos::B6>	  BLK;
			bit_rw_t< smr_io, bitpos::B7>	  GM;
		};
		static smr_t SMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ビットレートレジスタ (BRR)
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0x01> BRR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルコントロールレジスタ (SCR)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x02> scr_io;
		struct scr_t : public scr_io {
			using scr_io::operator =;
			using scr_io::operator ();
			using scr_io::operator |=;
			using scr_io::operator &=;

			bits_rw_t<scr_io, bitpos::B0, 2>	CKE;
			bit_rw_t< scr_io, bitpos::B2>	TEIE;
			bit_rw_t< scr_io, bitpos::B3>	MPIE;
			bit_rw_t< scr_io, bitpos::B4>	RE;
			bit_rw_t< scr_io, bitpos::B5>	TE;
			bit_rw_t< scr_io, bitpos::B6>	RIE;
			bit_rw_t< scr_io, bitpos::B7>	TIE;
		};
		static scr_t SCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  トランスミットデータレジスタ (TDR)
		*/
		//-----------------------------------------------------------------//
		static rw8_t<base + 0x03> TDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアルステータスレジスタ (SSR)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x04> ssr_io;
		struct ssr_t : public ssr_io {
			using ssr_io::operator =;
			using ssr_io::operator ();
			using ssr_io::operator |=;
			using ssr_io::operator &=;

			bit_rw_t<ssr_io, bitpos::B0>	MPBT;
			bit_rw_t<ssr_io, bitpos::B1>	MPB;
			bit_rw_t<ssr_io, bitpos::B2>	TEND;
			bit_rw_t<ssr_io, bitpos::B3>	PER;
			bit_rw_t<ssr_io, bitpos::B4>	FER;
			bit_rw_t<ssr_io, bitpos::B4>	ERS;
			bit_rw_t<ssr_io, bitpos::B5>	ORER;
		};
		static ssr_t SSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  レシーブデータレジスタ (RDR)
		*/
		//-----------------------------------------------------------------//
		static ro8_t<base + 0x05> RDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  スマートカードモードレジスタ (SCMR)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x06> scmr_io;
		struct scmr_t : public scmr_io {
			using scmr_io::operator =;
			using scmr_io::operator ();
			using scmr_io::operator |=;
			using scmr_io::operator &=;

			bit_rw_t<scmr_io, bitpos::B0>	SMIF;
			bit_rw_t<scmr_io, bitpos::B2>	SINV;
			bit_rw_t<scmr_io, bitpos::B3>	SDIR;
			bit_rw_t<scmr_io, bitpos::B7>	BCP2;
		};
		static scmr_t SCMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアル拡張レジスタ (SEMR)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x07> semr_io;
		struct semr_t : public semr_io {
			using semr_io::operator =;
			using semr_io::operator ();
			using semr_io::operator |=;
			using semr_io::operator &=;

			bit_rw_t<semr_io, bitpos::B0>	ACS0;
			bit_rw_t<semr_io, bitpos::B4>	ABCS;
			bit_rw_t<semr_io, bitpos::B5>	NFEN;
		};
		static semr_t SEMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ノイズフィルタ設定レジスタ (SNFR)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x08> snfr_io;
		struct snfr_t : public snfr_io {
			using snfr_io::operator =;
			using snfr_io::operator ();
			using snfr_io::operator |=;
			using snfr_io::operator &=;

			bits_rw_t<snfr_io, bitpos::B0, 3>	NFCS;
		};
		static snfr_t SNFR;


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C モードレジスタ１ (SIMR1)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x09> simr1_io;
		struct simr1_t : public simr1_io {
			using simr1_io::operator =;
			using simr1_io::operator ();
			using simr1_io::operator |=;
			using simr1_io::operator &=;

			bit_rw_t< simr1_io, bitpos::B0>	    IICM;
			bits_rw_t<simr1_io, bitpos::B3, 5>	IICDL;
		};
		static simr1_t SIMR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C モードレジスタ２ (SIMR2)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x0a> simr2_io;
		struct simr2_t : public simr2_io {
			using simr2_io::operator =;
			using simr2_io::operator ();
			using simr2_io::operator |=;
			using simr2_io::operator &=;

			bit_rw_t<simr2_io, bitpos::B0>	    IICINTM;
			bit_rw_t<simr2_io, bitpos::B1>	    IICCSC;
			bit_rw_t<simr2_io, bitpos::B5>	    IICACKT;
		};
		static simr2_t SIMR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C モードレジスタ３ (SIMR3)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x0b> simr3_io;
		struct simr3_t : public simr3_io {
			using simr3_io::operator =;
			using simr3_io::operator ();
			using simr3_io::operator |=;
			using simr3_io::operator &=;

			bit_rw_t< simr3_io, bitpos::B0>	    IICSTAREQ;
			bit_rw_t< simr3_io, bitpos::B1>	    IICRSTAREQ;
			bit_rw_t< simr3_io, bitpos::B2>	    IICSTPREQ;
			bit_rw_t< simr3_io, bitpos::B3>	    IICSTIF;
			bits_rw_t<simr3_io, bitpos::B4, 2>	IICSDAS;
			bits_rw_t<simr3_io, bitpos::B6, 2>	IICSCLS;
		};
		static simr3_t SIMR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  I2C ステータスレジスタ (SISR)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x0c> sisr_io;
		struct sisr_t : public sisr_io {
			using sisr_io::operator =;
			using sisr_io::operator ();
			using sisr_io::operator |=;
			using sisr_io::operator &=;

			bit_rw_t<sisr_io, bitpos::B0>	IICACKR;
		};
		static sisr_t SISR;


		//-----------------------------------------------------------------//
		/*!
			@brief  SPI モードレジスタ (SPMR)
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x0d> spmr_io;
		struct spmr_t : public spmr_io {
			using spmr_io::operator =;
			using spmr_io::operator ();
			using spmr_io::operator |=;
			using spmr_io::operator &=;

			bit_rw_t<spmr_io, bitpos::B0>	SSE;
			bit_rw_t<spmr_io, bitpos::B1>	CTSE;
			bit_rw_t<spmr_io, bitpos::B2>	MSS;
			bit_rw_t<spmr_io, bitpos::B4>	MFF;
			bit_rw_t<spmr_io, bitpos::B6>	CKPOL;
			bit_rw_t<spmr_io, bitpos::B7>	CKPH;
		};
		static spmr_t SPMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  拡張シリアルモード有効レジスタ (ESMER) @n
					※SIC12 にのみ有効なレジスタ
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<base + 0x20> esmer_io;
		struct esmer_t : public esmer_io {
			using esmer_io::operator =;
			using esmer_io::operator ();
			using esmer_io::operator |=;
			using esmer_io::operator &=;

			bit_rw_t<esmer_io, bitpos::B0>	ESME;
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


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return t; }


		//-----------------------------------------------------------------//
		/*!
			@brief  受信割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR get_rx_vec() { return rxv; }


		//-----------------------------------------------------------------//
		/*!
			@brief  送信割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR get_te_vec() { return tev; }
	};

	typedef sci_t<0x0008a000, peripheral::SCI0, ICU::VECTOR::RXI0, ICU::VECTOR::TEI0> SCI0;
	typedef sci_t<0x0008a020, peripheral::SCI1, ICU::VECTOR::RXI1, ICU::VECTOR::TEI1> SCI1;
	typedef sci_t<0x0008a040, peripheral::SCI2, ICU::VECTOR::RXI2, ICU::VECTOR::TEI2> SCI2;
	typedef sci_t<0x0008a060, peripheral::SCI3, ICU::VECTOR::RXI3, ICU::VECTOR::TEI3> SCI3;

//	typedef sci_t<0x0008b300> SCI12;
}
