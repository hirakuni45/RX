#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・USBA 定義 @n
			RX64M/RX71M
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
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
		static syscfg_t SYSCFG;


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
		static buswait_t BUSWAIT;


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
		static syssts0_t SYSSTS0;


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
		static pllsta_t PLLSTA;


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
		static dvstctr0_t DVSTCTR0;


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
		static testmode_t TESTMODE;


		//-----------------------------------------------------------------//
		/*!
			@brief  CFIFO ポートレジスタ（CFIFO）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x14> cfifo_t;
		static cfifo_t CFIFO;
		typedef rw16_t<base + 0x16> cfifoh_t;
		static cfifoh_t CFIFOH;
		typedef rw8_t<base + 0x17> cfifohh_t;
		static cfifohh_t CFIFOHH;


		//-----------------------------------------------------------------//
		/*!
			@brief  D0FIFO ポートレジスタ（D0FIFO）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x18> d0fifo_t;
		static d0fifo_t D0FIFO;
		typedef rw16_t<base + 0x1A> d0fifoh_t;
		static d0fifoh_t D0FIFOH;
		typedef rw8_t<base + 0x1B> d0fifohh_t;
		static d0fifohh_t D0FIFOHH;


		//-----------------------------------------------------------------//
		/*!
			@brief  D1FIFO ポートレジスタ（D1FIFO）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x1C> d1fifo_t;
		static d1fifo_t D1FIFO;
		typedef rw16_t<base + 0x1E> d1fifoh_t;
		static d1fifoh_t D1FIFOH;
		typedef rw8_t<base + 0x1F> d1fifohh_t;
		static d1fifohh_t D1FIFOHH;


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
		static cfifosel_t CFIFOSEL;


		//-----------------------------------------------------------------//
		/*!
			@brief  CFIFO ポート選択レジスタ（D0FIFOSEL, D1FIFOSEL）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dxfifosel_t_ : public rw16_t<base + ofs> {
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
		typedef dxfifosel_t_<0x28> d0fifosel_t;
		static d0fifosel_t D0FIFOSEL;
		typedef dxfifosel_t_<0x2C> d1fifosel_t;
		static d1fifosel_t D1FIFOSEL;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートコントロールレジスタ（CFIFOCTR, D0FIFOCTR, D1FIFOCTR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct xfifoctr_t_ : public rw16_t<base + ofs> {
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
		typedef xfifoctr_t_<0x22> cfifoctr_t;
		static cfifoctr_t CFIFOCTR;
		typedef xfifoctr_t_<0x2A> d0fifoctr_t;
		static d0fifoctr_t D0FIFOCTR;
		typedef xfifoctr_t_<0x2E> d1fifoctr_t;
		static d1fifoctr_t D1FIFOCTR;


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
		static intenb0_t INTENB0;


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
		static intenb1_t INTENB1;


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
		static brdyenb_t BRDYENB;


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
		static nrdyenb_t NRDYENB;


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
		static bempenb_t BEMPENB;


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
		static sofcfg_t SOFCFG;


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
		static physet_t  PHYSET;


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
		static intsts0_t INTSTS0;


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
		static intsts1_t INTSTS1;


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
		static brdysts_t BRDYSTS;


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
		static nrdysts_t NRDYSTS;


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
		static bempsts_t BEMPSTS;


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
		static frmnum_t FRMNUM;


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
		static ufrmnum_t UFRMNUM;


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
		static usbaddr_t USBADDR;


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
		static usbreq_t USBREQ;


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
		static usbval_t USBVAL;


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
		static usbindx_t USBINDX;


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
		static usbleng_t USBLENG;


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
		static dcpcfg_t DCPCFG;


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
		static dcpmaxp_t DCPMAXP;


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
		static dcpctr_t DCPCTR;


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
		static pipesel_t PIPESEL;


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
		static pipecfg_t PIPECFG;


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
		static pipebuf_t PIPEBUF;


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
		static pipemaxp_t PIPEMAXP;


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
		static pipeperi_t PIPEPERI;


		//-----------------------------------------------------------------//
		/*!
			@brief  パイプ n コントロールレジスタ（PIPExCTR）（n = 1 ～ 9）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pipexctr_t_ : public rw16_t<base + ofs> {
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
		typedef pipexctr_t_<0x70> pipe1ctr_t;
		static pipe1ctr_t PIPE1CTR;
		typedef pipexctr_t_<0x72> pipe2ctr_t;
		static pipe2ctr_t PIPE2CTR;
		typedef pipexctr_t_<0x74> pipe3ctr_t;
		static pipe3ctr_t PIPE3CTR;
		typedef pipexctr_t_<0x76> pipe4ctr_t;
		static pipe4ctr_t PIPE4CTR;
		typedef pipexctr_t_<0x78> pipe5ctr_t;
		static pipe5ctr_t PIPE5CTR;
		typedef pipexctr_t_<0x7A> pipe6ctr_t;
		static pipe6ctr_t PIPE6CTR;
		typedef pipexctr_t_<0x7C> pipe7ctr_t;
		static pipe7ctr_t PIPE7CTR;
		typedef pipexctr_t_<0x7E> pipe8ctr_t;
		static pipe8ctr_t PIPE8CTR;
		typedef pipexctr_t_<0x80> pipe9ctr_t;
		static pipe9ctr_t PIPE9CTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  パイプ n トランザクションカウンタイネーブルレジスタ（PIPEnTRE）（n = 1 ～ 5）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pipentre_t_ : public rw16_t<base + ofs> {
			typedef rw16_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B8>   TRCLR;
			bit_rw_t<io_, bitpos::B9>   TRENB;
		};
		typedef pipentre_t_<0x90> pipe1tre_t;
		static pipe1tre_t PIPE1TRE;
		typedef pipentre_t_<0x94> pipe2tre_t;
		static pipe2tre_t PIPE2TRE;
		typedef pipentre_t_<0x98> pipe3tre_t;
		static pipe3tre_t PIPE3TRE;
		typedef pipentre_t_<0x9C> pipe4tre_t;
		static pipe4tre_t PIPE4TRE;
		typedef pipentre_t_<0xA0> pipe5tre_t;
		static pipe5tre_t PIPE5TRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  パイプ n トランザクションカウンタレジスタ（PIPEnTRN）（n = 1 ～ 5）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pipentrn_t_ : public rw16_t<base + ofs> {
			typedef rw16_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>  TRNCNT;
		};
		typedef pipentrn_t_<0x92> pipe1trn_t;
		static pipe1trn_t PIPE1TRN;
		typedef pipentrn_t_<0x96> pipe2trn_t;
		static pipe2trn_t PIPE2TRN;
		typedef pipentrn_t_<0x9A> pipe3trn_t;
		static pipe3trn_t PIPE3TRN;
		typedef pipentrn_t_<0x9E> pipe4trn_t;
		static pipe4trn_t PIPE4TRN;
		typedef pipentrn_t_<0xA2> pipe5trn_t;
		static pipe5trn_t PIPE5TRN;


		//-----------------------------------------------------------------//
		/*!
			@brief  デバイスアドレス m コンフィギュレーションレジスタ（DEVADDm）（m = 0 ～ A）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct devaddm_t_ : public rw16_t<base + ofs> {
			typedef rw16_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B6,  2>  USBSPD;
			bits_rw_t<io_, bitpos::B8,  3>  HUBPORT;
			bits_rw_t<io_, bitpos::B11, 4>  UPPHUB;
		};
		typedef devaddm_t_<0xD0> devadd0_t;
		static devadd0_t DEVADD0;
		typedef devaddm_t_<0xD2> devadd1_t;
		static devadd1_t DEVADD1;
		typedef devaddm_t_<0xD4> devadd2_t;
		static devadd2_t DEVADD2;
		typedef devaddm_t_<0xD6> devadd3_t;
		static devadd3_t DEVADD3;
		typedef devaddm_t_<0xD8> devadd4_t;
		static devadd4_t DEVADD4;
		typedef devaddm_t_<0xDA> devadd5_t;
		static devadd5_t DEVADD5;
		typedef devaddm_t_<0xDC> devadd6_t;
		static devadd6_t DEVADD6;
		typedef devaddm_t_<0xDE> devadd7_t;
		static devadd7_t DEVADD7;
		typedef devaddm_t_<0xE0> devadd8_t;
		static devadd8_t DEVADD8;
		typedef devaddm_t_<0xE2> devadd9_t;
		static devadd9_t DEVADD9;
		typedef devaddm_t_<0xE4> devadda_t;
		static devadda_t DEVADDA;


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
		static lpctrl_t LPCTRL;


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
		static lpsts_t LPSTS;


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
		static bcctrl_t BCCTRL;


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
		static pl1ctrl1_t PL1CTRL1;


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
		static pl1ctrl2_t PL1CTRL2;


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
		static hl1ctrl1_t HL1CTRL1;


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
		static hl1ctrl2_t HL1CTRL2;


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
		static dpusr0r_t  DPUSR0R;


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
		static dpusr1r_t  DPUSR1R;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }


		//-----------------------------------------------------------------//
		/*!
			@brief  I 割り込みベクタを返す @n
					USBA モジュールには、I ベクターはサポートしていない。
			@return I 割り込みベクタ
		*/
		//-----------------------------------------------------------------//
		ICU::VECTOR get_i_vec() { return ICU::VECTOR::NONE; }


		//-----------------------------------------------------------------//
		/*!
			@brief  R 割り込みベクタを返す
			@return R 割り込みベクタ
		*/
		//-----------------------------------------------------------------//
		ICU::VECTOR get_r_vec() { return rvec; }


		//-----------------------------------------------------------------//
		/*!
			@brief  D0FIFO 割り込みベクタを返す
			@return D0FIFO 割り込みベクタ
		*/
		//-----------------------------------------------------------------//
		ICU::VECTOR get_d0_vec() { return d0vec; }


		//-----------------------------------------------------------------//
		/*!
			@brief  D1FIFO 割り込みベクタを返す
			@return D1FIFO 割り込みベクタ
		*/
		//-----------------------------------------------------------------//
		ICU::VECTOR get_d1_vec() { return d1vec; }
	};
	typedef usba_t<0x000D0400, peripheral::USBA, ICU::VECTOR::USBAR,
		ICU::VECTOR::D0FIFO2, ICU::VECTOR::D1FIFO2> USBA;

	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::syscfg_t usba_t<base, per, rvec, d0vec, d1vec>::SYSCFG;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::buswait_t usba_t<base, per, rvec, d0vec, d1vec>::BUSWAIT;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::syssts0_t usba_t<base, per, rvec, d0vec, d1vec>::SYSSTS0;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pllsta_t usba_t<base, per, rvec, d0vec, d1vec>::PLLSTA;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::dvstctr0_t usba_t<base, per, rvec, d0vec, d1vec>::DVSTCTR0;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::testmode_t usba_t<base, per, rvec, d0vec, d1vec>::TESTMODE;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::cfifo_t usba_t<base, per, rvec, d0vec, d1vec>::CFIFO;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::cfifoh_t usba_t<base, per, rvec, d0vec, d1vec>::CFIFOH;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::cfifohh_t usba_t<base, per, rvec, d0vec, d1vec>::CFIFOHH;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::d0fifo_t usba_t<base, per, rvec, d0vec, d1vec>::D0FIFO;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::d0fifoh_t usba_t<base, per, rvec, d0vec, d1vec>::D0FIFOH;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::d0fifohh_t usba_t<base, per, rvec, d0vec, d1vec>::D0FIFOHH;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::d1fifo_t usba_t<base, per, rvec, d0vec, d1vec>::D1FIFO;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::d1fifoh_t usba_t<base, per, rvec, d0vec, d1vec>::D1FIFOH;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::d1fifohh_t usba_t<base, per, rvec, d0vec, d1vec>::D1FIFOHH;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::cfifosel_t usba_t<base, per, rvec, d0vec, d1vec>::CFIFOSEL;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::d0fifosel_t usba_t<base, per, rvec, d0vec, d1vec>::D0FIFOSEL;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::d1fifosel_t usba_t<base, per, rvec, d0vec, d1vec>::D1FIFOSEL;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::cfifoctr_t usba_t<base, per, rvec, d0vec, d1vec>::CFIFOCTR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::d0fifoctr_t usba_t<base, per, rvec, d0vec, d1vec>::D0FIFOCTR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::d1fifoctr_t usba_t<base, per, rvec, d0vec, d1vec>::D1FIFOCTR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::intenb0_t usba_t<base, per, rvec, d0vec, d1vec>::INTENB0;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::intenb1_t usba_t<base, per, rvec, d0vec, d1vec>::INTENB1;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::brdyenb_t usba_t<base, per, rvec, d0vec, d1vec>::BRDYENB;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::nrdyenb_t usba_t<base, per, rvec, d0vec, d1vec>::NRDYENB;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::bempenb_t usba_t<base, per, rvec, d0vec, d1vec>::BEMPENB;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::sofcfg_t usba_t<base, per, rvec, d0vec, d1vec>::SOFCFG;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::physet_t  usba_t<base, per, rvec, d0vec, d1vec>::PHYSET;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::intsts0_t usba_t<base, per, rvec, d0vec, d1vec>::INTSTS0;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::intsts1_t usba_t<base, per, rvec, d0vec, d1vec>::INTSTS1;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::brdysts_t usba_t<base, per, rvec, d0vec, d1vec>::BRDYSTS;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::nrdysts_t usba_t<base, per, rvec, d0vec, d1vec>::NRDYSTS;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::bempsts_t usba_t<base, per, rvec, d0vec, d1vec>::BEMPSTS;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::frmnum_t usba_t<base, per, rvec, d0vec, d1vec>::FRMNUM;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::ufrmnum_t usba_t<base, per, rvec, d0vec, d1vec>::UFRMNUM;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::usbaddr_t usba_t<base, per, rvec, d0vec, d1vec>::USBADDR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::usbreq_t usba_t<base, per, rvec, d0vec, d1vec>::USBREQ;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::usbval_t usba_t<base, per, rvec, d0vec, d1vec>::USBVAL;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::usbindx_t usba_t<base, per, rvec, d0vec, d1vec>::USBINDX;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::usbleng_t usba_t<base, per, rvec, d0vec, d1vec>::USBLENG;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::dcpcfg_t usba_t<base, per, rvec, d0vec, d1vec>::DCPCFG;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::dcpmaxp_t usba_t<base, per, rvec, d0vec, d1vec>::DCPMAXP;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::dcpctr_t usba_t<base, per, rvec, d0vec, d1vec>::DCPCTR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pipesel_t usba_t<base, per, rvec, d0vec, d1vec>::PIPESEL;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pipecfg_t usba_t<base, per, rvec, d0vec, d1vec>::PIPECFG;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pipebuf_t usba_t<base, per, rvec, d0vec, d1vec>::PIPEBUF;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pipemaxp_t usba_t<base, per, rvec, d0vec, d1vec>::PIPEMAXP;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pipeperi_t usba_t<base, per, rvec, d0vec, d1vec>::PIPEPERI;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pipe1ctr_t usba_t<base, per, rvec, d0vec, d1vec>::PIPE1CTR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pipe2ctr_t usba_t<base, per, rvec, d0vec, d1vec>::PIPE2CTR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pipe3ctr_t usba_t<base, per, rvec, d0vec, d1vec>::PIPE3CTR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pipe4ctr_t usba_t<base, per, rvec, d0vec, d1vec>::PIPE4CTR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pipe5ctr_t usba_t<base, per, rvec, d0vec, d1vec>::PIPE5CTR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pipe6ctr_t usba_t<base, per, rvec, d0vec, d1vec>::PIPE6CTR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pipe7ctr_t usba_t<base, per, rvec, d0vec, d1vec>::PIPE7CTR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pipe8ctr_t usba_t<base, per, rvec, d0vec, d1vec>::PIPE8CTR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pipe9ctr_t usba_t<base, per, rvec, d0vec, d1vec>::PIPE9CTR;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pipe1tre_t usba_t<base, per, rvec, d0vec, d1vec>::PIPE1TRE;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pipe2tre_t usba_t<base, per, rvec, d0vec, d1vec>::PIPE2TRE;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pipe3tre_t usba_t<base, per, rvec, d0vec, d1vec>::PIPE3TRE;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pipe4tre_t usba_t<base, per, rvec, d0vec, d1vec>::PIPE4TRE;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pipe5tre_t usba_t<base, per, rvec, d0vec, d1vec>::PIPE5TRE;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pipe1trn_t usba_t<base, per, rvec, d0vec, d1vec>::PIPE1TRN;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pipe2trn_t usba_t<base, per, rvec, d0vec, d1vec>::PIPE2TRN;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pipe3trn_t usba_t<base, per, rvec, d0vec, d1vec>::PIPE3TRN;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pipe4trn_t usba_t<base, per, rvec, d0vec, d1vec>::PIPE4TRN;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pipe5trn_t usba_t<base, per, rvec, d0vec, d1vec>::PIPE5TRN;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::devadd0_t usba_t<base, per, rvec, d0vec, d1vec>::DEVADD0;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::devadd1_t usba_t<base, per, rvec, d0vec, d1vec>::DEVADD1;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::devadd2_t usba_t<base, per, rvec, d0vec, d1vec>::DEVADD2;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::devadd3_t usba_t<base, per, rvec, d0vec, d1vec>::DEVADD3;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::devadd4_t usba_t<base, per, rvec, d0vec, d1vec>::DEVADD4;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::devadd5_t usba_t<base, per, rvec, d0vec, d1vec>::DEVADD5;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::devadd6_t usba_t<base, per, rvec, d0vec, d1vec>::DEVADD6;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::devadd7_t usba_t<base, per, rvec, d0vec, d1vec>::DEVADD7;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::devadd8_t usba_t<base, per, rvec, d0vec, d1vec>::DEVADD8;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::devadd9_t usba_t<base, per, rvec, d0vec, d1vec>::DEVADD9;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::devadda_t usba_t<base, per, rvec, d0vec, d1vec>::DEVADDA;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::lpctrl_t usba_t<base, per, rvec, d0vec, d1vec>::LPCTRL;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::lpsts_t usba_t<base, per, rvec, d0vec, d1vec>::LPSTS;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::bcctrl_t usba_t<base, per, rvec, d0vec, d1vec>::BCCTRL;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pl1ctrl1_t usba_t<base, per, rvec, d0vec, d1vec>::PL1CTRL1;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::pl1ctrl2_t usba_t<base, per, rvec, d0vec, d1vec>::PL1CTRL2;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::hl1ctrl1_t usba_t<base, per, rvec, d0vec, d1vec>::HL1CTRL1;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::hl1ctrl2_t usba_t<base, per, rvec, d0vec, d1vec>::HL1CTRL2;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::dpusr0r_t  usba_t<base, per, rvec, d0vec, d1vec>::DPUSR0R;
	template <uint32_t base, peripheral per, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usba_t<base, per, rvec, d0vec, d1vec>::dpusr1r_t  usba_t<base, per, rvec, d0vec, d1vec>::DPUSR1R;
}
