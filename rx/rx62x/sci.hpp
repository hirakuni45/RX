#pragma once
//=====================================================================//
/*!	@file
	@brief	RX62N, RX621 グループ・SCI 定義 @n
			Copyright 2013 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCI 定義基底クラス
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct sci_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  SMR レジスタ
		*/
		//-----------------------------------------------------------------//
		typedef io8<base + 0x00> smr_io;
		struct smr_t : public smr_io {
			using smr_io::operator =;
			using smr_io::operator ();
			using smr_io::operator |=;
			using smr_io::operator &=;

			bits_t<smr_io, 0, 2>	CKS;
			bit_t<smr_io, 2>	MP;
			bit_t<smr_io, 3>	STOP;
			bit_t<smr_io, 4>	PM;
			bit_t<smr_io, 5>	PE;
			bit_t<smr_io, 6>	CHR;
			bit_t<smr_io, 7>	CM;
		};
		static smr_t SMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  BRR レジスタ
		*/
		//-----------------------------------------------------------------//
		typedef io8<base + 0x01> brr_t;
		static brr_t BRR;


		//-----------------------------------------------------------------//
		/*!
			@brief  SCR レジスタ
		*/
		//-----------------------------------------------------------------//
		typedef io8<base + 0x02> scr_io;
		struct scr_t : public scr_io {
			using scr_io::operator =;
			using scr_io::operator ();
			using scr_io::operator |=;
			using scr_io::operator &=;

			bits_t<scr_io, 0, 2>	CKE;
			bit_t<scr_io, 2>	TEIE;
			bit_t<scr_io, 3>	MPIE;
			bit_t<scr_io, 4>	RE;
			bit_t<scr_io, 5>	TE;
			bit_t<scr_io, 6>	RIE;
			bit_t<scr_io, 7>	TIE;
		};
		static scr_t SCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  TDR レジスタ
		*/
		//-----------------------------------------------------------------//
		typedef io8<base + 0x03> tdr_t;
		static tdr_t TDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  SSR レジスタ
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
			bit_t<ssr_io, 5>	ORER;
			bit_t<ssr_io, 6>	RDRF;
			bit_t<ssr_io, 7>	TDRE;
		};
		static ssr_t SSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  RDR レジスタ
		*/
		//-----------------------------------------------------------------//
		typedef io8<base + 0x05> rdr_t;
		static rdr_t RDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  SCMR レジスタ
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
			@brief  SEMR レジスタ
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
		};
		static semr_t SEMR;


		//-----------------------------------------------------------------//
		/*!
			@brief  チャネルを返す
			@return チャネル（０、１、２、３、５）
		*/
		//-----------------------------------------------------------------//
		uint32_t get_chanel() const {
			return (base >> 3) & 7;
		}
	};

	typedef sci_t<0x00088240> SCI0;
	typedef sci_t<0x00088248> SCI1;
	typedef sci_t<0x00088250> SCI2;
	typedef sci_t<0x00088258> SCI3;
	typedef sci_t<0x00088268> SCI5;
	typedef sci_t<0x00088270> SCI6;
}
