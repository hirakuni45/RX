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
		static rw32_t<base + 0x14> CFIFO;
		static rw16_t<base + 0x16> CFIFOH;
		static rw8_t <base + 0x17> CFIFOHH;


		//-----------------------------------------------------------------//
		/*!
			@brief  D0FIFO ポートレジスタ（D0FIFO）
		*/
		//-----------------------------------------------------------------//
		static rw32_t<base + 0x18> D0FIFO;
		static rw16_t<base + 0x1A> D0FIFOH;
		static rw8_t <base + 0x1B> D0FIFOHH;


		//-----------------------------------------------------------------//
		/*!
			@brief  D1FIFO ポートレジスタ（D1FIFO）
		*/
		//-----------------------------------------------------------------//
		static rw32_t<base + 0x1C> D1FIFO;
		static rw16_t<base + 0x1E> D1FIFOH;
		static rw8_t <base + 0x1F> D1FIFOHH;


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
		static dxfifosel_t<0x28> D0FIFOSEL;
		static dxfifosel_t<0x2C> D1FIFOSEL;


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
		static xfifoctr_t<0x22> CFIFOCTR;
		static xfifoctr_t<0x2A> D0FIFOCTR;
		static xfifoctr_t<0x2E> D1FIFOCTR;


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
		static pipexctr_t<0x70>  PIPE1CTR;
		static pipexctr_t<0x72>  PIPE2CTR;
		static pipexctr_t<0x74>  PIPE3CTR;
		static pipexctr_t<0x76>  PIPE4CTR;
		static pipexctr_t<0x78>  PIPE5CTR;
		static pipexctr_t<0x7A>  PIPE6CTR;
		static pipexctr_t<0x7C>  PIPE7CTR;
		static pipexctr_t<0x7E>  PIPE8CTR;
		static pipexctr_t<0x80>  PIPE9CTR;


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
		static pipentre_t<0x90>  PIPE1TRE;
		static pipentre_t<0x94>  PIPE2TRE;
		static pipentre_t<0x98>  PIPE3TRE;
		static pipentre_t<0x9C>  PIPE4TRE;
		static pipentre_t<0xA0>  PIPE5TRE;


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
		static pipentrn_t<0x92>  PIPE1TRN;
		static pipentrn_t<0x96>  PIPE2TRN;
		static pipentrn_t<0x9A>  PIPE3TRN;
		static pipentrn_t<0x9E>  PIPE4TRN;
		static pipentrn_t<0xA2>  PIPE5TRN;


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
		static devaddm_t<0xD0>  DEVADD0;
		static devaddm_t<0xD2>  DEVADD1;
		static devaddm_t<0xD4>  DEVADD2;
		static devaddm_t<0xD6>  DEVADD3;
		static devaddm_t<0xD8>  DEVADD4;
		static devaddm_t<0xDA>  DEVADD5;
		static devaddm_t<0xDC>  DEVADD6;
		static devaddm_t<0xDE>  DEVADD7;
		static devaddm_t<0xE0>  DEVADD8;
		static devaddm_t<0xE2>  DEVADD9;
		static devaddm_t<0xE4>  DEVADDA;


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
}
