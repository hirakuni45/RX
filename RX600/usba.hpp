#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・USBA 定義 @n
			RX64M/RX71M
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
		@brief  USB 2.0 High-Speed ホスト / ファンクションモジュール (USBAa)
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	rvec	R 割り込み Vector
		@param[in]	d0vec	D0 割り込み Vector
		@param[in]	d1vec	D1 割り込み Vector
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec>
	struct usba_t {

		static const auto PERIPHERAL = per;	///< ペリフェラル型
		static const auto R_VEC = rvec;		///< R 割り込み Vector
		static const auto D0_VEC = d0vec;	///< D0 割り込み Vector
		static const auto D1_VEC = d1vec;	///< D0 割り込み Vector


		//-----------------------------------------------------------------//
		/*!
			@brief  システムコンフィギュレーションコントロールレジスタ（SYSCFG）
		*/
		//-----------------------------------------------------------------//
		struct syscfg_t : public rw16_t<base + 0x00> {
			typedef rw16_t<base + 0x00> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>	  USBE;

			bit_rw_t <io_, bitpos::B4>	  DPRPU;
			bit_rw_t <io_, bitpos::B5>	  DRPD;
			bit_rw_t <io_, bitpos::B6>	  DCFM;
			bit_rw_t <io_, bitpos::B7>	  HSE;
			bit_rw_t <io_, bitpos::B8>	  CNEN;
		};
		typedef syscfg_t SYSCFG_;
		static  SYSCFG_ SYSCFG;


		//-----------------------------------------------------------------//
		/*!
			@brief  CPU バスウェイトレジスタ (BUSWAIT)
		*/
		//-----------------------------------------------------------------//
		struct buswait_t : public rw16_t<base + 0x02> {
			typedef rw16_t<base + 0x02> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t <io_, bitpos::B0, 4>  BWAIT;
		};
		typedef buswait_t BUSWAIT_;
		static  BUSWAIT_ BUSWAIT;


		//-----------------------------------------------------------------//
		/*!
			@brief  システムコンフィギュレーションステータスレジスタ 0（SYSSTS0）
		*/
		//-----------------------------------------------------------------//
		struct syssts0_t : public ro16_t<base + 0x04> {
			typedef ro16_t<base + 0x04> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B0, 2>   LNST;
			bit_ro_t <in_, bitpos::B2>	    IDMON;

			bit_ro_t <in_, bitpos::B5>	    SOFEA;
			bit_ro_t <in_, bitpos::B6>	    HTACT;

			bits_ro_t<in_, bitpos::B14, 2>  OVCMON;
		};
		typedef syssts0_t SYSSTS0_;
		static  SYSSTS0_ SYSSTS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  PLL ステータスレジスタ (PLLSTA)
		*/
		//-----------------------------------------------------------------//
		struct pllsta_t : public ro16_t<base + 0x06> {
			typedef ro16_t<base + 0x06> io_;
			using io_::operator ();

			bit_ro_t<io_, bitpos::B0>  PLLLOCK;
		};
		typedef pllsta_t PLLSTA_;
		static  PLLSTA_ PLLSTA;


		//-----------------------------------------------------------------//
		/*!
			@brief  デバイスステートコントロールレジスタ 0（DVSTCTR0）
		*/
		//-----------------------------------------------------------------//
		struct dvstctr0_t : public rw16_t<base + 0x08> {
			typedef rw16_t<base + 0x08> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_ro_t<io_, bitpos::B0, 3>   RHST;

			bit_rw_t <io_, bitpos::B4>	    UACT;
			bit_rw_t <io_, bitpos::B5>	    RESUME;
			bit_rw_t <io_, bitpos::B6>	    USBRST;
			bit_rw_t <io_, bitpos::B7>	    RWUPE;
			bit_rw_t <io_, bitpos::B8>	    WKUP;
			bit_rw_t <io_, bitpos::B9>	    VBUSEN;
			bit_rw_t <io_, bitpos::B10>	    EXICEN;
			bit_rw_t <io_, bitpos::B11>	    HNPBTOA;
		};
		typedef dvstctr0_t DVSTCTR0_;
		static  DVSTCTR0_ DVSTCTR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  USB テストモードレジスタ (TESTMODE)
		*/
		//-----------------------------------------------------------------//
		struct testmode_t : public rw16_t<base + 0x0C> {
			typedef rw16_t<base + 0x0C> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>   UTST;
		};
		typedef testmode_t TESTMODE_;
		static  TESTMODE_ TESTMODE;


		//-----------------------------------------------------------------//
		/*!
			@brief  CFIFO ポートレジスタ（CFIFO）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x14> CFIFO_;
		static  CFIFO_ CFIFO;
		typedef rw16_t<base + 0x16> CFIFOH_;
		static  CFIFOH_ CFIFOH;
		typedef rw8_t <base + 0x17> CFIFOHH_;
		static  CFIFOHH_ CFIFOHH;


		//-----------------------------------------------------------------//
		/*!
			@brief  D0FIFO ポートレジスタ（D0FIFO）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x18> D0FIFO_;
		static  D0FIFO_ D0FIFO;
		typedef rw16_t<base + 0x1A> D0FIFOH_;
		static  D0FIFOH_ D0FIFOH;
		typedef rw8_t <base + 0x1B> D0FIFOHH_;
		static  D0FIFOHH_ D0FIFOHH;


		//-----------------------------------------------------------------//
		/*!
			@brief  D1FIFO ポートレジスタ（D1FIFO）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x1C> D1FIFO_;
		static  D1FIFO_ D1FIFO;
		typedef rw16_t<base + 0x1E> D1FIFOH_;
		static  D1FIFOH_ D1FIFOH;
		typedef rw8_t <base + 0x1F> D1FIFOHH_;
		static  D1FIFOHH_ D1FIFOHH;


		//-----------------------------------------------------------------//
		/*!
			@brief  CFIFO ポート選択レジスタ（CFIFOSEL）
		*/
		//-----------------------------------------------------------------//
		struct cfifosel_t : public rw16_t<base + 0x20> {
			typedef rw16_t<base + 0x20> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>   CURPIPE;

			bit_rw_t <io_, bitpos::B5>	    ISEL;
			bit_rw_t <io_, bitpos::B8>	    BIGEND;

			bits_rw_t<io_, bitpos::B10, 2>	MBW;

			bit_rw_t <io_, bitpos::B14>	    REW;
			bit_rw_t <io_, bitpos::B15>	    RCNT;
		};
		typedef cfifosel_t CFIFOSEL_;
		static  CFIFOSEL_ CFIFOSEL;


		//-----------------------------------------------------------------//
		/*!
			@brief  CFIFO ポート選択レジスタ（D0FIFOSEL, D1FIFOSEL）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dxfifosel_t : public rw16_t<base + ofs> {
			typedef rw16_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>   CURPIPE;

			bit_rw_t <io_, bitpos::B8>	    BIGEND;

			bits_rw_t<io_, bitpos::B10, 2>	MBW;

			bit_rw_t <io_, bitpos::B12>	    DREQE;
			bit_rw_t <io_, bitpos::B13>	    DCLRM;
			bit_rw_t <io_, bitpos::B14>	    REW;
			bit_rw_t <io_, bitpos::B15>	    RCNT;
		};
		typedef dxfifosel_t<0x28> D0FIFOSEL_;
		static  D0FIFOSEL_ D0FIFOSEL;
		typedef dxfifosel_t<0x2C> D1FIFOSEL_;
		static  D1FIFOSEL_ D1FIFOSEL;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートコントロールレジスタ（CFIFOCTR, D0FIFOCTR, D1FIFOCTR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct xfifoctr_t : public rw16_t<base + ofs> {
			typedef rw16_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 12>  DTLN;

			bit_rw_t <io_, bitpos::B13>	    FRDY;
			bit_rw_t <io_, bitpos::B14>	    BCLR;
			bit_rw_t <io_, bitpos::B15>	    BVAL;
		};
		typedef xfifoctr_t<0x22> CFIFOCTR_;
		static  CFIFOCTR_ CFIFOCTR;
		typedef xfifoctr_t<0x2A> D0FIFOCTR_;
		static  D0FIFOCTR_ D0FIFOCTR;
		typedef xfifoctr_t<0x2E> D1FIFOCTR_;
		static  D1FIFOCTR_ D1FIFOCTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込み許可レジスタ 0（INTENB0）
		*/
		//-----------------------------------------------------------------//
		struct intenb0_t : public rw16_t<base + 0x30> {
			typedef rw16_t<base + 0x30> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B8>	    BRDYE;
			bit_rw_t <io_, bitpos::B9>	    NRDYE;
			bit_rw_t <io_, bitpos::B10>	    BEMPE;
			bit_rw_t <io_, bitpos::B11>	    CTRE;
			bit_rw_t <io_, bitpos::B12>	    DVSE;
			bit_rw_t <io_, bitpos::B13>	    SOFE;
			bit_rw_t <io_, bitpos::B14>	    RSME;
			bit_rw_t <io_, bitpos::B15>	    VBSE;
		};
		typedef intenb0_t INTENB0_;
		static  INTENB0_ INTENB0;


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込み許可レジスタ 1（INTENB1）
		*/
		//-----------------------------------------------------------------//
		struct intenb1_t : public rw16_t<base + 0x32> {
			typedef rw16_t<base + 0x32> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>	    PDDETINTE;

			bit_rw_t <io_, bitpos::B4>	    SACKE;
			bit_rw_t <io_, bitpos::B5>	    SIGNE;
			bit_rw_t <io_, bitpos::B6>	    EOFERRE;

			bit_rw_t <io_, bitpos::B8>	    LPMENDE;
			bit_rw_t <io_, bitpos::B9>	    L1RSMENDE;

			bit_rw_t <io_, bitpos::B11>	    ATTCHE;
			bit_rw_t <io_, bitpos::B12>	    DTCHE;

			bit_rw_t <io_, bitpos::B14>	    BCHGE;
			bit_rw_t <io_, bitpos::B15>	    OVRCRE;
		};
		typedef intenb1_t INTENB1_;
		static  INTENB1_ INTENB1;


		//-----------------------------------------------------------------//
		/*!
			@brief  BRDY 割り込み許可レジスタ（BRDYENB）
		*/
		//-----------------------------------------------------------------//
		struct brdyenb_t : public rw16_t<base + 0x36> {
			typedef rw16_t<base + 0x36> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 10>	 PIPEBRDYE;
		};
		typedef brdyenb_t BRDYENB_;
		static  BRDYENB_ BRDYENB;


		//-----------------------------------------------------------------//
		/*!
			@brief  NRDY 割り込み許可レジスタ（NRDYENB）
		*/
		//-----------------------------------------------------------------//
		struct nrdyenb_t : public rw16_t<base + 0x38> {
			typedef rw16_t<base + 0x38> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 10>	 PIPENRDYE;
		};
		typedef nrdyenb_t NRDYENB_;
		static  NRDYENB_ NRDYENB;


		//-----------------------------------------------------------------//
		/*!
			@brief  BEMP 割り込み許可レジスタ（BEMPENB）
		*/
		//-----------------------------------------------------------------//
		struct bempenb_t : public rw16_t<base + 0x3A> {
			typedef rw16_t<base + 0x3A> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 10>	 PIPEBEMPE;;
		};
		typedef bempenb_t BEMPENB_;
		static  BEMPENB_ BEMPENB;


		//-----------------------------------------------------------------//
		/*!
			@brief  SOF 出力コンフィギュレーションレジスタ（SOFCFG）
		*/
		//-----------------------------------------------------------------//
		struct sofcfg_t : public rw16_t<base + 0x3C> {
			typedef rw16_t<base + 0x3C> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B4>	EDGESTS;
			bit_rw_t<io_, bitpos::B5>	INTL;
			bit_rw_t<io_, bitpos::B6>	BRDYM;

			bit_rw_t<io_, bitpos::B8>	TRNENSEL;
		};
		typedef sofcfg_t SOFCFG_;
		static  SOFCFG_ SOFCFG;


		//-----------------------------------------------------------------//
		/*!
			@brief  PHY 設定レジスタ (PHYSET)
		*/
		//-----------------------------------------------------------------//
		struct physet_t : public rw16_t<base + 0x3E> {
			typedef rw16_t<base + 0x3E> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     DIRPD;
			bit_rw_t <io_, bitpos::B1>     PLLRESET;

			bit_rw_t <io_, bitpos::B3>     CDPEN;
			bits_rw_t<io_, bitpos::B4, 2>  CLKSEL;

			bits_rw_t<io_, bitpos::B8, 2>  REPSEL;

			bit_rw_t <io_, bitpos::B15>    HSEB;
		};
		typedef physet_t  PHYSET_;
		static  PHYSET_ PHYSET;


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みステータスレジスタ 0（INTSTS0）
		*/
		//-----------------------------------------------------------------//
		struct intsts0_t : public rw16_t<base + 0x40> {
			typedef rw16_t<base + 0x40> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_ro_t<io_, bitpos::B0, 3>  CTSQ;
			bit_rw_t <io_, bitpos::B3>     VALID;
			bits_ro_t<io_, bitpos::B4, 3>  DVSQ;
			bit_ro_t <io_, bitpos::B7>     VBSTS;
			bit_ro_t <io_, bitpos::B8>     BRDY;
			bit_ro_t <io_, bitpos::B9>     NRDY;
			bit_ro_t <io_, bitpos::B10>    BEMP;
			bit_rw_t <io_, bitpos::B11>    CTRT;
			bit_rw_t <io_, bitpos::B12>    DVST;
			bit_rw_t <io_, bitpos::B13>    SOFR;
			bit_rw_t <io_, bitpos::B14>    RESM;
			bit_rw_t <io_, bitpos::B15>    VBINT;
		};
		typedef intsts0_t INTSTS0_;
		static  INTSTS0_ INTSTS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みステータスレジスタ 1（INTSTS1）
		*/
		//-----------------------------------------------------------------//
		struct intsts1_t : public rw16_t<base + 0x42> {
			typedef rw16_t<base + 0x42> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>     PDDETINT;

			bit_rw_t<io_, bitpos::B4>     SACK;
			bit_rw_t<io_, bitpos::B5>     SIGN;
			bit_rw_t<io_, bitpos::B6>     EOFERR;

			bit_rw_t<io_, bitpos::B8>     LPMEND;
			bit_rw_t<io_, bitpos::B9>     L1RSMEND;

			bit_rw_t<io_, bitpos::B11>    ATTCH;
			bit_rw_t<io_, bitpos::B12>    DTCH;

			bit_rw_t<io_, bitpos::B14>    BCHG;
			bit_rw_t<io_, bitpos::B15>    OVRCR;
		};
		typedef intsts1_t INTSTS1_;
		static  INTSTS1_ INTSTS1;


		//-----------------------------------------------------------------//
		/*!
			@brief  BRDY 割り込みステータスレジスタ（BRDYSTS）
		*/
		//-----------------------------------------------------------------//
		struct brdysts_t : public rw16_t<base + 0x46> {
			typedef rw16_t<base + 0x46> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 10>   PIPEBRDY;
		};
		typedef brdysts_t BRDYSTS_;
		static  BRDYSTS_ BRDYSTS;


		//-----------------------------------------------------------------//
		/*!
			@brief  NRDY 割り込みステータスレジスタ（NRDYSTS）
		*/
		//-----------------------------------------------------------------//
		struct nrdysts_t : public rw16_t<base + 0x48> {
			typedef rw16_t<base + 0x48> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 10>   PIPENRDY;
		};
		typedef nrdysts_t NRDYSTS_;
		static  NRDYSTS_ NRDYSTS;


		//-----------------------------------------------------------------//
		/*!
			@brief  BEMP 割り込みステータスレジスタ（BEMPSTS）
		*/
		//-----------------------------------------------------------------//
		struct bempsts_t : public rw16_t<base + 0x4A> {
			typedef rw16_t<base + 0x4A> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 10>   PIPEBEMP;
		};
		typedef bempsts_t BEMPSTS_;
		static  BEMPSTS_ BEMPSTS;


		//-----------------------------------------------------------------//
		/*!
			@brief  フレームナンバレジスタ（FRMNUM）
		*/
		//-----------------------------------------------------------------//
		struct frmnum_t : public rw16_t<base + 0x4C> {
			typedef rw16_t<base + 0x4C> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 11>   FRNM;

			bit_rw_t <io_, bitpos::B14>       CRCE;
			bit_rw_t <io_, bitpos::B15>       OVRN;
		};
		typedef frmnum_t FRMNUM_;
		static  FRMNUM_ FRMNUM;


		//-----------------------------------------------------------------//
		/*!
			@brief  マイクロフレームナンバレジスタ (UFRMNUM)
		*/
		//-----------------------------------------------------------------//
		struct ufrmnum_t : public rw16_t<base + 0x4E> {
			typedef rw16_t<base + 0x4E> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>   UFRNM;
		};
		typedef ufrmnum_t UFRMNUM_;
		static  UFRMNUM_ UFRMNUM;


		//-----------------------------------------------------------------//
		/*!
			@brief  USB アドレスレジスタ (USBADDR)
		*/
		//-----------------------------------------------------------------//
		struct usbaddr_t : public rw16_t<base + 0x50> {
			typedef rw16_t<base + 0x50> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 7>   USBADDR;
		};
		typedef usbaddr_t USBADDR_;
		static  USBADDR_ USBADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  USB リクエストタイプレジスタ (USBREQ)
		*/
		//-----------------------------------------------------------------//
		struct usbreq_t : public rw16_t<base + 0x54> {
			typedef rw16_t<base + 0x54> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>   BMREQUESTTYPE;
			bits_rw_t<io_, bitpos::B8, 8>   BREQUEST;
		};
		typedef usbreq_t USBREQ_;
		static  USBREQ_ USBREQ;


		//-----------------------------------------------------------------//
		/*!
			@brief  USB リクエストバリューレジスタ (USBVAL)
		*/
		//-----------------------------------------------------------------//
		struct usbval_t : public rw16_t<base + 0x56> {
			typedef rw16_t<base + 0x56> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>   WVALUE;
		};
		typedef usbval_t USBVAL_;
		static  USBVAL_ USBVAL;


		//-----------------------------------------------------------------//
		/*!
			@brief  USB リクエストインデックスレジスタ (USBINDX)
		*/
		//-----------------------------------------------------------------//
		struct usbindx_t : public rw16_t<base + 0x58> {
			typedef rw16_t<base + 0x58> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>   WINDEX;
		};
		typedef usbindx_t USBINDX_;
		static  USBINDX_ USBINDX;


		//-----------------------------------------------------------------//
		/*!
			@brief  USB リクエストレングスレジスタ (USBLENG)
		*/
		//-----------------------------------------------------------------//
		struct usbleng_t : public rw16_t<base + 0x5A> {
			typedef rw16_t<base + 0x5A> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>   WLENGTH;
		};
		typedef usbleng_t USBLENG_;
		static  USBLENG_ USBLENG;


		//-----------------------------------------------------------------//
		/*!
			@brief  DCP コンフィギュレーションレジスタ（DCPCFG）
		*/
		//-----------------------------------------------------------------//
		struct dcpcfg_t : public rw16_t<base + 0x5C> {
			typedef rw16_t<base + 0x5C> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B4>   DIR;

			bit_rw_t<io_, bitpos::B7>   SHTNAK;
			bit_rw_t<io_, bitpos::B8>   CNTMD;
		};
		typedef dcpcfg_t DCPCFG_;
		static  DCPCFG_ DCPCFG;


		//-----------------------------------------------------------------//
		/*!
			@brief  DCP マックスパケットサイズレジスタ（DCPMAXP）
		*/
		//-----------------------------------------------------------------//
		struct dcpmaxp_t : public rw16_t<base + 0x5E> {
			typedef rw16_t<base + 0x5E> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  7>   MXPS;
			bits_rw_t<io_, bitpos::B12, 4>   DEVSEL;
		};
		typedef dcpmaxp_t DCPMAXP_;
		static  DCPMAXP_ DCPMAXP;


		//-----------------------------------------------------------------//
		/*!
			@brief  DCP コントロールレジスタ（DCPCTR）
		*/
		//-----------------------------------------------------------------//
		struct dcpctr_t : public rw16_t<base + 0x60> {
			typedef rw16_t<base + 0x60> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>   PID;
			bit_rw_t <io_, bitpos::B2>      CCPL;

			bit_rw_t <io_, bitpos::B4>      PINGE;
			bit_rw_t <io_, bitpos::B5>      PBUSY;
			bit_rw_t <io_, bitpos::B6>      SQMON;
			bit_rw_t <io_, bitpos::B7>      SQSET;
			bit_rw_t <io_, bitpos::B8>      SQCLR;

			bit_rw_t <io_, bitpos::B11>     SUREQCLR;
			bit_rw_t <io_, bitpos::B12>     CSSTS;
			bit_rw_t <io_, bitpos::B13>     CSCLR;
			bit_rw_t <io_, bitpos::B14>     SUREQ;
			bit_rw_t <io_, bitpos::B15>     BSTS;
		};
		typedef dcpctr_t DCPCTR_;
		static  DCPCTR_ DCPCTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  パイプウィンドウ選択レジスタ（PIPESEL）
		*/
		//-----------------------------------------------------------------//
		struct pipesel_t : public rw16_t<base + 0x64> {
			typedef rw16_t<base + 0x64> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>   PIPESEL;
		};
		typedef pipesel_t PIPESEL_;
		static  PIPESEL_ PIPESEL;


		//-----------------------------------------------------------------//
		/*!
			@brief  パイプコンフィギュレーションレジスタ（PIPECFG）
		*/
		//-----------------------------------------------------------------//
		struct pipecfg_t : public rw16_t<base + 0x68> {
			typedef rw16_t<base + 0x68> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>   EPNUM;
			bit_rw_t <io_, bitpos::B4>      DIR;

			bit_rw_t <io_, bitpos::B7>      SHTNAK;
			bit_rw_t <io_, bitpos::B8>      CNTMD;
			bit_rw_t <io_, bitpos::B9>      DBLB;
			bit_rw_t <io_, bitpos::B10>     BFRE;

			bits_rw_t<io_, bitpos::B14, 2>  TYPE;
		};
		typedef pipecfg_t PIPECFG_;
		static  PIPECFG_ PIPECFG;


		//-----------------------------------------------------------------//
		/*!
			@brief  パイプバッファ指定レジスタ (PIPEBUF)
		*/
		//-----------------------------------------------------------------//
		struct pipebuf_t : public rw16_t<base + 0x6A> {
			typedef rw16_t<base + 0x6A> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>  BUFNMB;
			bits_rw_t<io_, bitpos::B10, 5>  BUFSIZE;
		};
		typedef pipebuf_t PIPEBUF_;
		static  PIPEBUF_ PIPEBUF;


		//-----------------------------------------------------------------//
		/*!
			@brief  パイプマックスパケットサイズレジスタ（PIPEMAXP）
		*/
		//-----------------------------------------------------------------//
		struct pipemaxp_t : public rw16_t<base + 0x6C> {
			typedef rw16_t<base + 0x6C> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 11>  MXPS;

			bits_rw_t<io_, bitpos::B12, 4>  DEVSEL;
		};
		typedef pipemaxp_t PIPEMAXP_;
		static  PIPEMAXP_ PIPEMAXP;


		//-----------------------------------------------------------------//
		/*!
			@brief  パイプ周期制御レジスタ（PIPEPERI）
		*/
		//-----------------------------------------------------------------//
		struct pipeperi_t : public rw16_t<base + 0x6E> {
			typedef rw16_t<base + 0x6E> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>   IITV;

			bit_rw_t <io_, bitpos::B12>     IFIS;
		};
		typedef pipeperi_t PIPEPERI_;
		static  PIPEPERI_ PIPEPERI;


		//-----------------------------------------------------------------//
		/*!
			@brief  パイプ n コントロールレジスタ（PIPExCTR）（n = 1 ～ 9）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pipexctr_t : public rw16_t<base + ofs> {
			typedef rw16_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>   PID;

			bit_rw_t <io_, bitpos::B5>      PBUSY;
			bit_rw_t <io_, bitpos::B6>      SQMON;
			bit_rw_t <io_, bitpos::B7>      SQSET;
			bit_rw_t <io_, bitpos::B8>      SQCLR;
			bit_rw_t <io_, bitpos::B9>      ACLRM;
			bit_rw_t <io_, bitpos::B10>     ATREPM;

			bit_rw_t <io_, bitpos::B12>     CSSTS;
			bit_rw_t <io_, bitpos::B13>     CSCLR;
			bit_rw_t <io_, bitpos::B14>     INBUFM;
			bit_rw_t <io_, bitpos::B15>     BSTS;
		};
		typedef pipexctr_t<0x70>  PIPE1CTR_;
		static  PIPE1CTR_ PIPE1CTR;
		typedef pipexctr_t<0x72>  PIPE2CTR_;
		static  PIPE2CTR_ PIPE2CTR;
		typedef pipexctr_t<0x74>  PIPE3CTR_;
		static  PIPE3CTR_ PIPE3CTR;
		typedef pipexctr_t<0x76>  PIPE4CTR_;
		static  PIPE4CTR_ PIPE4CTR;
		typedef pipexctr_t<0x78>  PIPE5CTR_;
		static  PIPE5CTR_ PIPE5CTR;
		typedef pipexctr_t<0x7A>  PIPE6CTR_;
		static  PIPE6CTR_ PIPE6CTR;
		typedef pipexctr_t<0x7C>  PIPE7CTR_;
		static  PIPE7CTR_ PIPE7CTR;
		typedef pipexctr_t<0x7E>  PIPE8CTR_;
		static  PIPE8CTR_ PIPE8CTR;
		typedef pipexctr_t<0x80>  PIPE9CTR_;
		static  PIPE9CTR_ PIPE9CTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  パイプ n トランザクションカウンタイネーブルレジスタ（PIPEnTRE）（n = 1 ～ 5）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pipentre_t : public rw16_t<base + ofs> {
			typedef rw16_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B8>   TRCLR;
			bit_rw_t<io_, bitpos::B9>   TRENB;
		};
		typedef pipentre_t<0x90>  PIPE1TRE_;
		static  PIPE1TRE_ PIPE1TRE;
		typedef pipentre_t<0x94>  PIPE2TRE_;
		static  PIPE2TRE_ PIPE2TRE;
		typedef pipentre_t<0x98>  PIPE3TRE_;
		static  PIPE3TRE_ PIPE3TRE;
		typedef pipentre_t<0x9C>  PIPE4TRE_;
		static  PIPE4TRE_ PIPE4TRE;
		typedef pipentre_t<0xA0>  PIPE5TRE_;
		static  PIPE5TRE_ PIPE5TRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  パイプ n トランザクションカウンタレジスタ（PIPEnTRN）（n = 1 ～ 5）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pipentrn_t : public rw16_t<base + ofs> {
			typedef rw16_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>  TRNCNT;
		};
		typedef pipentrn_t<0x92>  PIPE1TRN_;
		static  PIPE1TRN_ PIPE1TRN;
		typedef pipentrn_t<0x96>  PIPE2TRN_;
		static  PIPE2TRN_ PIPE2TRN;
		typedef pipentrn_t<0x9A>  PIPE3TRN_;
		static  PIPE3TRN_ PIPE3TRN;
		typedef pipentrn_t<0x9E>  PIPE4TRN_;
		static  PIPE4TRN_ PIPE4TRN;
		typedef pipentrn_t<0xA2>  PIPE5TRN_;
		static  PIPE5TRN_ PIPE5TRN;


		//-----------------------------------------------------------------//
		/*!
			@brief  デバイスアドレス m コンフィギュレーションレジスタ（DEVADDm）（m = 0 ～ A）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct devaddm_t : public rw16_t<base + ofs> {
			typedef rw16_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B6,  2>  USBSPD;
			bits_rw_t<io_, bitpos::B8,  3>  HUBPORT;
			bits_rw_t<io_, bitpos::B11, 4>  UPPHUB;
		};
		typedef devaddm_t<0xD0>  DEVADD0_;
		static  DEVADD0_ DEVADD0;
		typedef devaddm_t<0xD2>  DEVADD1_;
		static  DEVADD1_ DEVADD1;
		typedef devaddm_t<0xD4>  DEVADD2_;
		static  DEVADD2_ DEVADD2;
		typedef devaddm_t<0xD6>  DEVADD3_;
		static  DEVADD3_ DEVADD3;
		typedef devaddm_t<0xD8>  DEVADD4_;
		static  DEVADD4_ DEVADD4;
		typedef devaddm_t<0xDA>  DEVADD5_;
		static  DEVADD5_ DEVADD5;
		typedef devaddm_t<0xDC>  DEVADD6_;
		static  DEVADD6_ DEVADD6;
		typedef devaddm_t<0xDE>  DEVADD7_;
		static  DEVADD7_ DEVADD7;
		typedef devaddm_t<0xE0>  DEVADD8_;
		static  DEVADD8_ DEVADD8;
		typedef devaddm_t<0xE2>  DEVADD9_;
		static  DEVADD9_ DEVADD9;
		typedef devaddm_t<0xE4>  DEVADDA_;
		static  DEVADDA_ DEVADDA;


		//-----------------------------------------------------------------//
		/*!
			@brief  ローパワーコントロールレジスタ (LPCTRL)
		*/
		//-----------------------------------------------------------------//
		struct lpctrl_t : public rw16_t<base + 0x100> {
			typedef rw16_t<base + 0x100> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B7>   HWUPM;
		};
		typedef lpctrl_t LPCTRL_;
		static  LPCTRL_ LPCTRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  ローパワーステータスレジスタ (LPSTS)
		*/
		//-----------------------------------------------------------------//
		struct lpsts_t : public rw16_t<base + 0x102> {
			typedef rw16_t<base + 0x102> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B14>   SUSPENDM;
		};
		typedef lpsts_t LPSTS_;
		static  LPSTS_ LPSTS;


		//-----------------------------------------------------------------//
		/*!
			@brief  Battery Charging コントロールレジスタ (BCCTRL)
		*/
		//-----------------------------------------------------------------//
		struct bcctrl_t : public rw16_t<base + 0x140> {
			typedef rw16_t<base + 0x140> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   IDPSRCE;
			bit_rw_t<io_, bitpos::B1>   IDMSINKE;
			bit_rw_t<io_, bitpos::B2>   VDPSRCE;
			bit_rw_t<io_, bitpos::B3>   IDPSINKE;
			bit_rw_t<io_, bitpos::B4>   VDMSRCE;

			bit_rw_t<io_, bitpos::B8>   CHGDETSTS;
			bit_rw_t<io_, bitpos::B9>   PDDETSTS;
		};
		typedef bcctrl_t BCCTRL_;
		static  BCCTRL_ BCCTRL;


		//-----------------------------------------------------------------//
		/*!
			@brief  ファンクション L1 コントロールレジスタ 1 (PL1CTRL1)
		*/
		//-----------------------------------------------------------------//
		struct pl1ctrl1_t : public rw16_t<base + 0x144> {
			typedef rw16_t<base + 0x144> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     L1RESPEN;
			bits_rw_t<io_, bitpos::B1, 2>  L1RESPMD;
			bit_rw_t <io_, bitpos::B3>     L1NEGOMD;
			bits_rw_t<io_, bitpos::B4, 3>  DVSQ;
			bit_rw_t <io_, bitpos::B7>     DVSQ3;
			bits_rw_t<io_, bitpos::B8, 4>  HIRDTHR;
			bit_rw_t <io_, bitpos::B14>    L1EXTMD;
		};
		typedef pl1ctrl1_t PL1CTRL1_;
		static  PL1CTRL1_ PL1CTRL1;


		//-----------------------------------------------------------------//
		/*!
			@brief  ファンクション L1 コントロールレジスタ 2 (PL1CTRL2)
		*/
		//-----------------------------------------------------------------//
		struct pl1ctrl2_t : public rw16_t<base + 0x146> {
			typedef rw16_t<base + 0x146> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B8, 4>  HIRDMON;
			bit_rw_t <io_, bitpos::B12>    RWEMON;
		};
		typedef pl1ctrl2_t PL1CTRL2_;
		static  PL1CTRL2_ PL1CTRL2;


		//-----------------------------------------------------------------//
		/*!
			@brief  ホスト L1 コントロールレジスタ 1 (HL1CTRL1)
		*/
		//-----------------------------------------------------------------//
		struct hl1ctrl1_t : public rw16_t<base + 0x148> {
			typedef rw16_t<base + 0x148> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     L1REQ;
			bits_rw_t<io_, bitpos::B1, 2>  L1STATUS;
		};
		typedef hl1ctrl1_t HL1CTRL1_;
		static  HL1CTRL1_ HL1CTRL1;


		//-----------------------------------------------------------------//
		/*!
			@brief  ホスト L1 コントロールレジスタ 2 (HL1CTRL2)
		*/
		//-----------------------------------------------------------------//
		struct hl1ctrl2_t : public rw16_t<base + 0x14A> {
			typedef rw16_t<base + 0x14A> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  L1ADDR;

			bits_rw_t<io_, bitpos::B8, 4>  HIRD;
			bit_rw_t <io_, bitpos::B12>    L1RWE;

			bit_rw_t <io_, bitpos::B15>    BESL;
		};
		typedef hl1ctrl2_t HL1CTRL2_;
		static  HL1CTRL2_ HL1CTRL2;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイ USB トランシーバ制御 / 端子モニタレジスタ（DPUSR0R）
		*/
		//-----------------------------------------------------------------//
		struct dpusr0r_t : public rw32_t<base + 0x160> {
			typedef rw32_t<base + 0x160> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B20>  DOVCAHM;
			bit_rw_t<io_, bitpos::B20>  DOVCBHM;

			bit_rw_t<io_, bitpos::B23>  DVBSTSHM;
		};
		typedef dpusr0r_t  DPUSR0R_;
		static  DPUSR0R_ DPUSR0R;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイ USB サスペンド / レジューム割り込みレジスタ（DPUSR1R）
		*/
		//-----------------------------------------------------------------//
		struct dpusr1r_t : public rw32_t<base + 0x164> {
			typedef rw32_t<base + 0x164> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B4>   DOVCAHE;
			bit_rw_t<io_, bitpos::B5>   DOVCBHE;

			bit_rw_t<io_, bitpos::B7>   DVBSTSHE;

			bit_rw_t<io_, bitpos::B20>  DOVCAH;
			bit_rw_t<io_, bitpos::B20>  DOVCBH;

			bit_rw_t<io_, bitpos::B23>  DVBSTSH;
		};
		typedef dpusr1r_t  DPUSR1R_;
		static  DPUSR1R_ DPUSR1R;
	};
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::SYSCFG_ usba_t<base, per, rvec, d0vec, d1vec>::SYSCFG;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::BUSWAIT_ usba_t<base, per, rvec, d0vec, d1vec>::BUSWAIT;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::SYSSTS0_ usba_t<base, per, rvec, d0vec, d1vec>::SYSSTS0;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PLLSTA_ usba_t<base, per, rvec, d0vec, d1vec>::PLLSTA;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::DVSTCTR0_ usba_t<base, per, rvec, d0vec, d1vec>::DVSTCTR0;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::TESTMODE_ usba_t<base, per, rvec, d0vec, d1vec>::TESTMODE;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::CFIFO_ usba_t<base, per, rvec, d0vec, d1vec>::CFIFO;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::CFIFOH_ usba_t<base, per, rvec, d0vec, d1vec>::CFIFOH;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::CFIFOHH_ usba_t<base, per, rvec, d0vec, d1vec>::CFIFOHH;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::D0FIFO_ usba_t<base, per, rvec, d0vec, d1vec>::D0FIFO;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::D0FIFOH_ usba_t<base, per, rvec, d0vec, d1vec>::D0FIFOH;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::D0FIFOHH_ usba_t<base, per, rvec, d0vec, d1vec>::D0FIFOHH;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::D1FIFO_ usba_t<base, per, rvec, d0vec, d1vec>::D1FIFO;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::D1FIFOH_ usba_t<base, per, rvec, d0vec, d1vec>::D1FIFOH;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::D1FIFOHH_ usba_t<base, per, rvec, d0vec, d1vec>::D1FIFOHH;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::CFIFOSEL_ usba_t<base, per, rvec, d0vec, d1vec>::CFIFOSEL;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::D0FIFOSEL_ usba_t<base, per, rvec, d0vec, d1vec>::D0FIFOSEL;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::D1FIFOSEL_ usba_t<base, per, rvec, d0vec, d1vec>::D1FIFOSEL;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::CFIFOCTR_ usba_t<base, per, rvec, d0vec, d1vec>::CFIFOCTR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::D0FIFOCTR_ usba_t<base, per, rvec, d0vec, d1vec>::D0FIFOCTR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::D1FIFOCTR_ usba_t<base, per, rvec, d0vec, d1vec>::D1FIFOCTR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::INTENB0_ usba_t<base, per, rvec, d0vec, d1vec>::INTENB0;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::INTENB1_ usba_t<base, per, rvec, d0vec, d1vec>::INTENB1;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::BRDYENB_ usba_t<base, per, rvec, d0vec, d1vec>::BRDYENB;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::NRDYENB_ usba_t<base, per, rvec, d0vec, d1vec>::NRDYENB;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::BEMPENB_ usba_t<base, per, rvec, d0vec, d1vec>::BEMPENB;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::SOFCFG_ usba_t<base, per, rvec, d0vec, d1vec>::SOFCFG;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PHYSET_ usba_t<base, per, rvec, d0vec, d1vec>::PHYSET;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::INTSTS0_ usba_t<base, per, rvec, d0vec, d1vec>::INTSTS0;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::INTSTS1_ usba_t<base, per, rvec, d0vec, d1vec>::INTSTS1;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::BRDYSTS_ usba_t<base, per, rvec, d0vec, d1vec>::BRDYSTS;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::NRDYSTS_ usba_t<base, per, rvec, d0vec, d1vec>::NRDYSTS;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::BEMPSTS_ usba_t<base, per, rvec, d0vec, d1vec>::BEMPSTS;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::FRMNUM_ usba_t<base, per, rvec, d0vec, d1vec>::FRMNUM;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::UFRMNUM_ usba_t<base, per, rvec, d0vec, d1vec>::UFRMNUM;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::USBADDR_ usba_t<base, per, rvec, d0vec, d1vec>::USBADDR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::USBREQ_ usba_t<base, per, rvec, d0vec, d1vec>::USBREQ;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::USBVAL_ usba_t<base, per, rvec, d0vec, d1vec>::USBVAL;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::USBINDX_ usba_t<base, per, rvec, d0vec, d1vec>::USBINDX;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::USBLENG_ usba_t<base, per, rvec, d0vec, d1vec>::USBLENG;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::DCPCFG_ usba_t<base, per, rvec, d0vec, d1vec>::DCPCFG;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::DCPMAXP_ usba_t<base, per, rvec, d0vec, d1vec>::DCPMAXP;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::DCPCTR_ usba_t<base, per, rvec, d0vec, d1vec>::DCPCTR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PIPESEL_ usba_t<base, per, rvec, d0vec, d1vec>::PIPESEL;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PIPECFG_ usba_t<base, per, rvec, d0vec, d1vec>::PIPECFG;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PIPEBUF_ usba_t<base, per, rvec, d0vec, d1vec>::PIPEBUF;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PIPEMAXP_ usba_t<base, per, rvec, d0vec, d1vec>::PIPEMAXP;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PIPEPERI_ usba_t<base, per, rvec, d0vec, d1vec>::PIPEPERI;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PIPE1CTR_ usba_t<base, per, rvec, d0vec, d1vec>::PIPE1CTR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PIPE2CTR_ usba_t<base, per, rvec, d0vec, d1vec>::PIPE2CTR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PIPE3CTR_ usba_t<base, per, rvec, d0vec, d1vec>::PIPE3CTR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PIPE4CTR_ usba_t<base, per, rvec, d0vec, d1vec>::PIPE4CTR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PIPE5CTR_ usba_t<base, per, rvec, d0vec, d1vec>::PIPE5CTR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PIPE6CTR_ usba_t<base, per, rvec, d0vec, d1vec>::PIPE6CTR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PIPE7CTR_ usba_t<base, per, rvec, d0vec, d1vec>::PIPE7CTR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PIPE8CTR_ usba_t<base, per, rvec, d0vec, d1vec>::PIPE8CTR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PIPE9CTR_ usba_t<base, per, rvec, d0vec, d1vec>::PIPE9CTR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PIPE1TRE_ usba_t<base, per, rvec, d0vec, d1vec>::PIPE1TRE;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PIPE2TRE_ usba_t<base, per, rvec, d0vec, d1vec>::PIPE2TRE;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PIPE3TRE_ usba_t<base, per, rvec, d0vec, d1vec>::PIPE3TRE;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PIPE4TRE_ usba_t<base, per, rvec, d0vec, d1vec>::PIPE4TRE;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PIPE5TRE_ usba_t<base, per, rvec, d0vec, d1vec>::PIPE5TRE;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PIPE1TRN_ usba_t<base, per, rvec, d0vec, d1vec>::PIPE1TRN;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PIPE2TRN_ usba_t<base, per, rvec, d0vec, d1vec>::PIPE2TRN;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PIPE3TRN_ usba_t<base, per, rvec, d0vec, d1vec>::PIPE3TRN;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PIPE4TRN_ usba_t<base, per, rvec, d0vec, d1vec>::PIPE4TRN;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PIPE5TRN_ usba_t<base, per, rvec, d0vec, d1vec>::PIPE5TRN;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::DEVADD0_ usba_t<base, per, rvec, d0vec, d1vec>::DEVADD0;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::DEVADD1_ usba_t<base, per, rvec, d0vec, d1vec>::DEVADD1;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::DEVADD2_ usba_t<base, per, rvec, d0vec, d1vec>::DEVADD2;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::DEVADD3_ usba_t<base, per, rvec, d0vec, d1vec>::DEVADD3;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::DEVADD4_ usba_t<base, per, rvec, d0vec, d1vec>::DEVADD4;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::DEVADD5_ usba_t<base, per, rvec, d0vec, d1vec>::DEVADD5;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::DEVADD6_ usba_t<base, per, rvec, d0vec, d1vec>::DEVADD6;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::DEVADD7_ usba_t<base, per, rvec, d0vec, d1vec>::DEVADD7;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::DEVADD8_ usba_t<base, per, rvec, d0vec, d1vec>::DEVADD8;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::DEVADD9_ usba_t<base, per, rvec, d0vec, d1vec>::DEVADD9;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::DEVADDA_ usba_t<base, per, rvec, d0vec, d1vec>::DEVADDA;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::LPCTRL_ usba_t<base, per, rvec, d0vec, d1vec>::LPCTRL;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::LPSTS_ usba_t<base, per, rvec, d0vec, d1vec>::LPSTS;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::BCCTRL_ usba_t<base, per, rvec, d0vec, d1vec>::BCCTRL;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PL1CTRL1_ usba_t<base, per, rvec, d0vec, d1vec>::PL1CTRL1;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::PL1CTRL2_ usba_t<base, per, rvec, d0vec, d1vec>::PL1CTRL2;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::HL1CTRL1_ usba_t<base, per, rvec, d0vec, d1vec>::HL1CTRL1;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::HL1CTRL2_ usba_t<base, per, rvec, d0vec, d1vec>::HL1CTRL2;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::DPUSR0R_ usba_t<base, per, rvec, d0vec, d1vec>::DPUSR0R;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::DPUSR1R_ usba_t<base, per, rvec, d0vec, d1vec>::DPUSR1R;


	typedef usba_t<0x000D0400, peripheral::USBA, ICU::VECTOR::USBAR,
		ICU::VECTOR::D0FIFO2, ICU::VECTOR::D1FIFO2> USBA;
}
