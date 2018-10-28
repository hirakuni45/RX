#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・USB 定義 @n
			RX64M/RX71M/RX65x
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  USB 定義基底クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct usb_t {

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

			bit_rw_t <io_, bitpos::B10>	  SCKE;
		};
		static syscfg_t SYSCFG;


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
			@brief  デバイスステートコントロールレジスタ 0（DVSTCTR0）
		*/
		//-----------------------------------------------------------------//
		struct dvstctr0_t : public rw16_t<base + 0x08> {
			typedef rw16_t<base + 0x08> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>   RHST;

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
			@brief  CFIFO ポートレジスタ（CFIFO）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x14> CFIFO;
		static rw8_t<base + 0x14> CFIFOL;


		//-----------------------------------------------------------------//
		/*!
			@brief  D0FIFO ポートレジスタ（D0FIFO）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x18> D0FIFO;
		static rw8_t<base + 0x18> D0FIFOL;


		//-----------------------------------------------------------------//
		/*!
			@brief  D1FIFO ポートレジスタ（D1FIFO）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x1C> D1FIFO;
		static rw8_t<base + 0x1C> D1FIFOL;


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

			bit_rw_t <io_, bitpos::B10>	    MBW;

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

			bit_rw_t <io_, bitpos::B10>	    MBW;

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

			bits_rw_t<io_, bitpos::B0, 9>   DTLN;

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

			bit_rw_t <io_, bitpos::B4>	    SACKE;
			bit_rw_t <io_, bitpos::B5>	    SIGNE;
			bit_rw_t <io_, bitpos::B6>	    EOFERRE;

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

			bit_rw_t <io_, bitpos::B0>	    PIPE0BRDYE;
			bit_rw_t <io_, bitpos::B1>	    PIPE1BRDYE;
			bit_rw_t <io_, bitpos::B2>	    PIPE2BRDYE;
			bit_rw_t <io_, bitpos::B3>	    PIPE3BRDYE;
			bit_rw_t <io_, bitpos::B4>	    PIPE4BRDYE;
			bit_rw_t <io_, bitpos::B5>	    PIPE5BRDYE;
			bit_rw_t <io_, bitpos::B6>	    PIPE6BRDYE;
			bit_rw_t <io_, bitpos::B7>	    PIPE7BRDYE;
			bit_rw_t <io_, bitpos::B8>	    PIPE8BRDYE;
			bit_rw_t <io_, bitpos::B9>	    PIPE9BRDYE;
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

			bit_rw_t <io_, bitpos::B0>	    PIPE0BNRDYE;
			bit_rw_t <io_, bitpos::B1>	    PIPE1BNRDYE;
			bit_rw_t <io_, bitpos::B2>	    PIPE2BNRDYE;
			bit_rw_t <io_, bitpos::B3>	    PIPE3BNRDYE;
			bit_rw_t <io_, bitpos::B4>	    PIPE4BNRDYE;
			bit_rw_t <io_, bitpos::B5>	    PIPE5BNRDYE;
			bit_rw_t <io_, bitpos::B6>	    PIPE6BNRDYE;
			bit_rw_t <io_, bitpos::B7>	    PIPE7BNRDYE;
			bit_rw_t <io_, bitpos::B8>	    PIPE8BNRDYE;
			bit_rw_t <io_, bitpos::B9>	    PIPE9BNRDYE;
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

			bit_rw_t <io_, bitpos::B0>	    PIPE0BEMPE;
			bit_rw_t <io_, bitpos::B1>	    PIPE1BEMPE;
			bit_rw_t <io_, bitpos::B2>	    PIPE2BEMPE;
			bit_rw_t <io_, bitpos::B3>	    PIPE3BEMPE;
			bit_rw_t <io_, bitpos::B4>	    PIPE4BEMPE;
			bit_rw_t <io_, bitpos::B5>	    PIPE5BEMPE;
			bit_rw_t <io_, bitpos::B6>	    PIPE6BEMPE;
			bit_rw_t <io_, bitpos::B7>	    PIPE7BEMPE;
			bit_rw_t <io_, bitpos::B8>	    PIPE8BEMPE;
			bit_rw_t <io_, bitpos::B9>	    PIPE9BEMPE;
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

			bit_rw_t <io_, bitpos::B4>	    EDGESTS;

			bit_rw_t <io_, bitpos::B6>	    BRDYM;

			bit_rw_t <io_, bitpos::B8>	    TRNENSEL;
		};
		static sofcfg_t SOFCFG;


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

			bits_rw_t<io_, bitpos::B0, 3>  CTSQ;
			bit_rw_t <io_, bitpos::B3>     VALID;
			bits_rw_t<io_, bitpos::B4, 3>  DVSQ;
			bit_rw_t <io_, bitpos::B7>     VBSTS;
			bit_rw_t <io_, bitpos::B8>     BRDY;
			bit_rw_t <io_, bitpos::B9>     NRDY;
			bit_rw_t <io_, bitpos::B10>    BEMP;
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

			bit_rw_t <io_, bitpos::B4>     SACK;
			bit_rw_t <io_, bitpos::B5>     SIGN;
			bit_rw_t <io_, bitpos::B6>     EOFERR;

			bit_rw_t <io_, bitpos::B11>    ATTCH;
			bit_rw_t <io_, bitpos::B12>    DTCH;

			bit_rw_t <io_, bitpos::B14>    BCHG;
			bit_rw_t <io_, bitpos::B15>    OVRCR;
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

			bit_rw_t <io_, bitpos::B0>   PIPE0BRDY;
			bit_rw_t <io_, bitpos::B1>   PIPE1BRDY;
			bit_rw_t <io_, bitpos::B2>   PIPE2BRDY;
			bit_rw_t <io_, bitpos::B3>   PIPE3BRDY;
			bit_rw_t <io_, bitpos::B4>   PIPE4BRDY;
			bit_rw_t <io_, bitpos::B5>   PIPE5BRDY;
			bit_rw_t <io_, bitpos::B6>   PIPE6BRDY;
			bit_rw_t <io_, bitpos::B7>   PIPE7BRDY;
			bit_rw_t <io_, bitpos::B8>   PIPE8BRDY;
			bit_rw_t <io_, bitpos::B9>   PIPE9BRDY;
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

			bit_rw_t <io_, bitpos::B0>   PIPE0NRDY;
			bit_rw_t <io_, bitpos::B1>   PIPE1NRDY;
			bit_rw_t <io_, bitpos::B2>   PIPE2NRDY;
			bit_rw_t <io_, bitpos::B3>   PIPE3NRDY;
			bit_rw_t <io_, bitpos::B4>   PIPE4NRDY;
			bit_rw_t <io_, bitpos::B5>   PIPE5NRDY;
			bit_rw_t <io_, bitpos::B6>   PIPE6NRDY;
			bit_rw_t <io_, bitpos::B7>   PIPE7NRDY;
			bit_rw_t <io_, bitpos::B8>   PIPE8NRDY;
			bit_rw_t <io_, bitpos::B9>   PIPE9NRDY;
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

			bit_rw_t <io_, bitpos::B0>   PIPE0BEMP;
			bit_rw_t <io_, bitpos::B1>   PIPE1BEMP;
			bit_rw_t <io_, bitpos::B2>   PIPE2BEMP;
			bit_rw_t <io_, bitpos::B3>   PIPE3BEMP;
			bit_rw_t <io_, bitpos::B4>   PIPE4BEMP;
			bit_rw_t <io_, bitpos::B5>   PIPE5BEMP;
			bit_rw_t <io_, bitpos::B6>   PIPE6BEMP;
			bit_rw_t <io_, bitpos::B7>   PIPE7BEMP;
			bit_rw_t <io_, bitpos::B8>   PIPE8BEMP;
			bit_rw_t <io_, bitpos::B9>   PIPE9BEMP;
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

			bits_rw_t <io_, bitpos::B0, 11>   FRNM;

			bit_rw_t <io_, bitpos::B14>       CRCE;
			bit_rw_t <io_, bitpos::B15>       OVRN;
		};
		static frmnum_t FRMNUM;


		//-----------------------------------------------------------------//
		/*!
			@brief  デバイスステート切り替えレジスタ（DVCHGR）
		*/
		//-----------------------------------------------------------------//
		struct dvchgr_t : public rw16_t<base + 0x4E> {
			typedef rw16_t<base + 0x4E> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B15>   DVCHG;
		};
		static dvchgr_t DVCHGR;


		//-----------------------------------------------------------------//
		/*!
			@brief  USB アドレスレジスタ（USBADDR）
		*/
		//-----------------------------------------------------------------//
		struct usbaddr_t : public rw16_t<base + 0x50> {
			typedef rw16_t<base + 0x50> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t <io_, bitpos::B0, 7>   USBADDR;
			bits_rw_t <io_, bitpos::B8, 4>   STSRECOV;
		};
		static usbaddr_t USBADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  USB リクエストタイプレジスタ（USBREQ）
		*/
		//-----------------------------------------------------------------//
		struct usbreq_t : public rw16_t<base + 0x54> {
			typedef rw16_t<base + 0x54> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t <io_, bitpos::B0, 8>   BMREQUESTTYPE;
			bits_rw_t <io_, bitpos::B8, 8>   BREQUEST;
		};
		static usbreq_t USBREQ;


		//-----------------------------------------------------------------//
		/*!
			@brief  USB リクエストバリューレジスタ（USBVAL）
		*/
		//-----------------------------------------------------------------//
		struct usbval_t : public rw16_t<base + 0x56> {
			typedef rw16_t<base + 0x56> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t <io_, bitpos::B0, 16>   WVALUE;
		};
		static usbval_t USBVAL;


		//-----------------------------------------------------------------//
		/*!
			@brief  USB リクエストインデックスレジスタ（USBINDX）
		*/
		//-----------------------------------------------------------------//
		struct usbindx_t : public rw16_t<base + 0x58> {
			typedef rw16_t<base + 0x58> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t <io_, bitpos::B0, 16>   WINDEX;
		};
		static usbindx_t USBINDX;


		//-----------------------------------------------------------------//
		/*!
			@brief  USB リクエストレングスレジスタ（USBLENG）
		*/
		//-----------------------------------------------------------------//
		struct usbleng_t : public rw16_t<base + 0x5A> {
			typedef rw16_t<base + 0x5A> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t <io_, bitpos::B0, 16>   WLENGTH;
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

			bit_rw_t <io_, bitpos::B5>      PBUSY;
			bit_rw_t <io_, bitpos::B6>      SQMON;
			bit_rw_t <io_, bitpos::B7>      SQSET;
			bit_rw_t <io_, bitpos::B8>      SQCLR;

			bit_rw_t <io_, bitpos::B11>     SUREQCLR;

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

			bit_rw_t <io_, bitpos::B9>      DBLB;
			bit_rw_t <io_, bitpos::B10>     BFRE;

			bits_rw_t<io_, bitpos::B14, 2>  TYPE;
		};
		static pipecfg_t PIPECFG;


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

			bits_rw_t<io_, bitpos::B0, 9>   MXPS;

			bits_rw_t<io_, bitpos::B12, 4>  DEVSEL;
		};
		static pipemaxp_t PIPEMAXP;


		//-----------------------------------------------------------------//
		/*!
			@brief  パイプ周期制御レジスタ（PIPEPERI）
		*/
		//-----------------------------------------------------------------//
		struct pipeperi_t : public rw16_t<base + 0x6C> {
			typedef rw16_t<base + 0x6C> io_;
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
			@brief  パイプ n コントロールレジスタ（PIPExCTR）（n = 1 ～ 5）
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

			bit_rw_t <io_, bitpos::B14>     INBUFM;
			bit_rw_t <io_, bitpos::B15>     BSTS;
		};
		static pipexctr_t<0x70>  PIPE1CTR;
		static pipexctr_t<0x72>  PIPE2CTR;
		static pipexctr_t<0x74>  PIPE3CTR;
		static pipexctr_t<0x76>  PIPE4CTR;
		static pipexctr_t<0x78>  PIPE5CTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  パイプ n コントロールレジスタ（PIPEyCTR）（n = 6 ～ 9）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pipeyctr_t : public rw16_t<base + ofs> {
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

			bit_rw_t <io_, bitpos::B15>     BSTS;
		};
		static pipeyctr_t<0x7A>  PIPE6CTR;
		static pipeyctr_t<0x7C>  PIPE7CTR;
		static pipeyctr_t<0x7E>  PIPE8CTR;
		static pipeyctr_t<0x80>  PIPE9CTR;


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

			bit_rw_t <io_, bitpos::B8>      TRCLR;
			bit_rw_t <io_, bitpos::B9>      TRENB;
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
			@brief  デバイスアドレス n コンフィギュレーションレジスタ（DEVADDn）（n = 0 ～ 5）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct devaddn_t : public rw16_t<base + ofs> {
			typedef rw16_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B6, 2>  USBSPD;
		};
		static devaddn_t<0xD0>  DEVADD0;
		static devaddn_t<0xD2>  DEVADD1;
		static devaddn_t<0xD4>  DEVADD2;
		static devaddn_t<0xD6>  DEVADD3;
		static devaddn_t<0xD8>  DEVADD4;
		static devaddn_t<0xDA>  DEVADD5;


		//-----------------------------------------------------------------//
		/*!
			@brief  PHY クロスポイント調整レジスタ（PHYSLEW）
		*/
		//-----------------------------------------------------------------//
		struct physlew_t : public rw32_t<base + 0xF0> {
			typedef rw32_t<base + 0xF0> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SLEWR00;
			bit_rw_t<io_, bitpos::B1>  SLEWR01;
			bit_rw_t<io_, bitpos::B2>  SLEWF00;
			bit_rw_t<io_, bitpos::B3>  SLEWF01;
		};
		static physlew_t  PHYSLEW;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイ USB トランシーバ制御 / 端子モニタレジスタ（DPUSR0R）
		*/
		//-----------------------------------------------------------------//
		struct dpusr0r_t : public rw32_t<base + 0x400> {
			typedef rw32_t<base + 0x400> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   SRPC0;
			bit_rw_t<io_, bitpos::B1>   RPUE0;

			bit_rw_t<io_, bitpos::B3>   DRPD0;
			bit_rw_t<io_, bitpos::B4>   FIXPHY0;

			bit_rw_t<io_, bitpos::B16>  DP0;
			bit_rw_t<io_, bitpos::B17>  DM0;

			bit_rw_t<io_, bitpos::B20>  DOVCA0;
			bit_rw_t<io_, bitpos::B20>  DOVCB0;

			bit_rw_t<io_, bitpos::B23>  DVBSTS0;
		};
		static dpusr0r_t  DPUSR0R;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイ USB サスペンド / レジューム割り込みレジスタ（DPUSR1R）
		*/
		//-----------------------------------------------------------------//
		struct dpusr1r_t : public rw32_t<base + 0x404> {
			typedef rw32_t<base + 0x404> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   DPINTE0;
			bit_rw_t<io_, bitpos::B1>   DMINTE0;

			bit_rw_t<io_, bitpos::B4>   DOVRCRAE0;
			bit_rw_t<io_, bitpos::B5>   DOVRCRBE0;

			bit_rw_t<io_, bitpos::B7>   DVBSE0;

			bit_rw_t<io_, bitpos::B16>  DPINT0;
			bit_rw_t<io_, bitpos::B17>  DMINT0;

			bit_rw_t<io_, bitpos::B20>  DOVRCRA0;
			bit_rw_t<io_, bitpos::B20>  DOVRCRB0;

			bit_rw_t<io_, bitpos::B23>  DVBINT0;
		};
		static dpusr1r_t  DPUSR1R;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }
	};
	typedef usb_t<0x000A0000, peripheral::USB> USB;
}
