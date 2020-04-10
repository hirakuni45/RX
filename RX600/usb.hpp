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
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  USB 定義基底クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	IVT		ivec タイプ
		@param[in]	ivec	USBI 割り込み Vector
		@param[in]	rvec	USBR 割り込み Vector
		@param[in]	d0vec	D0 割り込み Vector
		@param[in]	d1vec	D1 割り込み Vector
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, class IVT, IVT ivec, 
		ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec>
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
		typedef rw16_t<base + 0x14> cfifo_t;
		static cfifo_t CFIFO;
		typedef rw8_t<base + 0x14> cfifol_t;
		static cfifol_t CFIFOL;


		//-----------------------------------------------------------------//
		/*!
			@brief  D0FIFO ポートレジスタ（D0FIFO）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x18> d0fifo_t;
		static d0fifo_t D0FIFO;
		typedef rw8_t<base + 0x18> d0fifol_t;
		static d0fifol_t D0FIFOL;


		//-----------------------------------------------------------------//
		/*!
			@brief  D1FIFO ポートレジスタ（D1FIFO）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x1C> d1fifo_t;
		static d1fifo_t D1FIFO;
		typedef rw8_t<base + 0x1C> d1fifol_t;
		static d1fifol_t D1FIFOL;


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
		struct dxfifosel_t_ : public rw16_t<base + ofs> {
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

			bits_rw_t<io_, bitpos::B0, 9>   DTLN;

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

			bit_rw_t<io_, bitpos::B8>	  BRDYE;
			bit_rw_t<io_, bitpos::B9>	  NRDYE;
			bit_rw_t<io_, bitpos::B10>	  BEMPE;
			bit_rw_t<io_, bitpos::B11>	  CTRE;
			bit_rw_t<io_, bitpos::B12>	  DVSE;
			bit_rw_t<io_, bitpos::B13>	  SOFE;
			bit_rw_t<io_, bitpos::B14>	  RSME;
			bit_rw_t<io_, bitpos::B15>	  VBSE;
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

			bit_rw_t<io_, bitpos::B4>	  SACKE;
			bit_rw_t<io_, bitpos::B5>	  SIGNE;
			bit_rw_t<io_, bitpos::B6>	  EOFERRE;

			bit_rw_t<io_, bitpos::B11>	  ATTCHE;
			bit_rw_t<io_, bitpos::B12>	  DTCHE;

			bit_rw_t<io_, bitpos::B14>	  BCHGE;
			bit_rw_t<io_, bitpos::B15>	  OVRCRE;
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

			bit_rw_t<io_, bitpos::B0>	  PIPE0BRDYE;
			bit_rw_t<io_, bitpos::B1>	  PIPE1BRDYE;
			bit_rw_t<io_, bitpos::B2>	  PIPE2BRDYE;
			bit_rw_t<io_, bitpos::B3>	  PIPE3BRDYE;
			bit_rw_t<io_, bitpos::B4>	  PIPE4BRDYE;
			bit_rw_t<io_, bitpos::B5>	  PIPE5BRDYE;
			bit_rw_t<io_, bitpos::B6>	  PIPE6BRDYE;
			bit_rw_t<io_, bitpos::B7>	  PIPE7BRDYE;
			bit_rw_t<io_, bitpos::B8>	  PIPE8BRDYE;
			bit_rw_t<io_, bitpos::B9>	  PIPE9BRDYE;

			bits_rw_t<io_, bitpos::B0, 10>	PIPEBRDYE;
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

			bit_rw_t<io_, bitpos::B0>	  PIPE0BNRDYE;
			bit_rw_t<io_, bitpos::B1>	  PIPE1BNRDYE;
			bit_rw_t<io_, bitpos::B2>	  PIPE2BNRDYE;
			bit_rw_t<io_, bitpos::B3>	  PIPE3BNRDYE;
			bit_rw_t<io_, bitpos::B4>	  PIPE4BNRDYE;
			bit_rw_t<io_, bitpos::B5>	  PIPE5BNRDYE;
			bit_rw_t<io_, bitpos::B6>	  PIPE6BNRDYE;
			bit_rw_t<io_, bitpos::B7>	  PIPE7BNRDYE;
			bit_rw_t<io_, bitpos::B8>	  PIPE8BNRDYE;
			bit_rw_t<io_, bitpos::B9>	  PIPE9BNRDYE;

			bits_rw_t<io_, bitpos::B0, 10>	PIPEBNRDYE;
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

			bit_rw_t<io_, bitpos::B0>	  PIPE0BEMPE;
			bit_rw_t<io_, bitpos::B1>	  PIPE1BEMPE;
			bit_rw_t<io_, bitpos::B2>	  PIPE2BEMPE;
			bit_rw_t<io_, bitpos::B3>	  PIPE3BEMPE;
			bit_rw_t<io_, bitpos::B4>	  PIPE4BEMPE;
			bit_rw_t<io_, bitpos::B5>	  PIPE5BEMPE;
			bit_rw_t<io_, bitpos::B6>	  PIPE6BEMPE;
			bit_rw_t<io_, bitpos::B7>	  PIPE7BEMPE;
			bit_rw_t<io_, bitpos::B8>	  PIPE8BEMPE;
			bit_rw_t<io_, bitpos::B9>	  PIPE9BEMPE;

			bits_rw_t<io_, bitpos::B0, 10>	PIPEBEMPE;
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

			bit_rw_t<io_, bitpos::B4>    EDGESTS;

			bit_rw_t<io_, bitpos::B6>    BRDYM;

			bit_rw_t<io_, bitpos::B8>    TRNENSEL;
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

			bit_rw_t<io_, bitpos::B0>   PIPE0BRDY;
			bit_rw_t<io_, bitpos::B1>   PIPE1BRDY;
			bit_rw_t<io_, bitpos::B2>   PIPE2BRDY;
			bit_rw_t<io_, bitpos::B3>   PIPE3BRDY;
			bit_rw_t<io_, bitpos::B4>   PIPE4BRDY;
			bit_rw_t<io_, bitpos::B5>   PIPE5BRDY;
			bit_rw_t<io_, bitpos::B6>   PIPE6BRDY;
			bit_rw_t<io_, bitpos::B7>   PIPE7BRDY;
			bit_rw_t<io_, bitpos::B8>   PIPE8BRDY;
			bit_rw_t<io_, bitpos::B9>   PIPE9BRDY;

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

			bit_rw_t<io_, bitpos::B0>   PIPE0NRDY;
			bit_rw_t<io_, bitpos::B1>   PIPE1NRDY;
			bit_rw_t<io_, bitpos::B2>   PIPE2NRDY;
			bit_rw_t<io_, bitpos::B3>   PIPE3NRDY;
			bit_rw_t<io_, bitpos::B4>   PIPE4NRDY;
			bit_rw_t<io_, bitpos::B5>   PIPE5NRDY;
			bit_rw_t<io_, bitpos::B6>   PIPE6NRDY;
			bit_rw_t<io_, bitpos::B7>   PIPE7NRDY;
			bit_rw_t<io_, bitpos::B8>   PIPE8NRDY;
			bit_rw_t<io_, bitpos::B9>   PIPE9NRDY;

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

			bit_rw_t<io_, bitpos::B0>   PIPE0BEMP;
			bit_rw_t<io_, bitpos::B1>   PIPE1BEMP;
			bit_rw_t<io_, bitpos::B2>   PIPE2BEMP;
			bit_rw_t<io_, bitpos::B3>   PIPE3BEMP;
			bit_rw_t<io_, bitpos::B4>   PIPE4BEMP;
			bit_rw_t<io_, bitpos::B5>   PIPE5BEMP;
			bit_rw_t<io_, bitpos::B6>   PIPE6BEMP;
			bit_rw_t<io_, bitpos::B7>   PIPE7BEMP;
			bit_rw_t<io_, bitpos::B8>   PIPE8BEMP;
			bit_rw_t<io_, bitpos::B9>   PIPE9BEMP;

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

			bit_rw_t <io_, bitpos::B14>      CRCE;
			bit_rw_t <io_, bitpos::B15>      OVRN;
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

			bit_rw_t<io_, bitpos::B15>   DVCHG;
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

			bits_rw_t<io_, bitpos::B0, 7>   USBADDR;
			bits_rw_t<io_, bitpos::B8, 4>   STSRECOV;
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

			bits_rw_t<io_, bitpos::B0, 8>   BMREQUESTTYPE;
			bits_rw_t<io_, bitpos::B8, 8>   BREQUEST;
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

			bits_rw_t<io_, bitpos::B0, 16>   WVALUE;
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

			bits_rw_t<io_, bitpos::B0, 16>   WINDEX;
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
			@brief  パイプ n コントロールレジスタ（PIPExCTR）（n = 1 ～ 5）
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


		//-----------------------------------------------------------------//
		/*!
			@brief  パイプ n コントロールレジスタ（PIPEyCTR）（n = 6 ～ 9）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pipeyctr_t_ : public rw16_t<base + ofs> {
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
		typedef pipeyctr_t_<0x7A> pipe6ctr_t;
		static pipe6ctr_t PIPE6CTR;
		typedef pipeyctr_t_<0x7C> pipe7ctr_t;
		static pipe7ctr_t PIPE7CTR;
		typedef pipeyctr_t_<0x7E> pipe8ctr_t;
		static pipe8ctr_t PIPE8CTR;
		typedef pipeyctr_t_<0x80> pipe9ctr_t;
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

			bit_rw_t <io_, bitpos::B8>      TRCLR;
			bit_rw_t <io_, bitpos::B9>      TRENB;
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
			@brief  デバイスアドレス n コンフィギュレーションレジスタ（DEVADDn）（n = 0 ～ 5）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct devaddn_t_ : public rw16_t<base + ofs> {
			typedef rw16_t<base + ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B6, 2>  USBSPD;
		};
		typedef devaddn_t_<0xD0> devadd0_t;
		static devadd0_t DEVADD0;
		typedef devaddn_t_<0xD2> devadd1_t;
		static devadd1_t DEVADD1;
		typedef devaddn_t_<0xD4> devadd2_t;
		static devadd2_t DEVADD2;
		typedef devaddn_t_<0xD6> devadd3_t;
		static devadd3_t DEVADD3;
		typedef devaddn_t_<0xD8> devadd4_t;
		static devadd4_t DEVADD4;
		typedef devaddn_t_<0xDA> devadd5_t;
		static devadd5_t DEVADD5;


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
		static auto get_peripheral() { return per; }


		//-----------------------------------------------------------------//
		/*!
			@brief  USBI0 割り込みベクタを返す
			@return USBI0 割り込みベクタ
		*/
		//-----------------------------------------------------------------//
		static auto get_i_vec() { return ivec; }


		//-----------------------------------------------------------------//
		/*!
			@brief  USBR0 割り込みベクタを返す
			@return USBR0 割り込みベクタ
		*/
		//-----------------------------------------------------------------//
		static auto get_r_vec() { return rvec; }


		//-----------------------------------------------------------------//
		/*!
			@brief  D0FIFO 割り込みベクタを返す
			@return D0FIFO 割り込みベクタ
		*/
		//-----------------------------------------------------------------//
		static auto get_d0_vec() { return d0vec; }


		//-----------------------------------------------------------------//
		/*!
			@brief  D1FIFO 割り込みベクタを返す
			@return D1FIFO 割り込みベクタ
		*/
		//-----------------------------------------------------------------//
		static auto get_d1_vec() { return d1vec; }
	};

#if defined(SIG_RX66T) || defined(SIG_RX72T)
	typedef usb_t<0x000A0000, peripheral::USB0, ICU::VECTOR,
	ICU::VECTOR::USBI0, ICU::VECTOR::USBR0, ICU::VECTOR::D0FIFO0, ICU::VECTOR::D1FIFO0> USB0;
#else
	typedef usb_t<0x000A0000, peripheral::USB0, ICU::VECTOR_SELB,
	ICU::VECTOR_SELB::USBI0, ICU::VECTOR::USBR0, ICU::VECTOR::D0FIFO0, ICU::VECTOR::D1FIFO0> USB0;
#endif

	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::syscfg_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::SYSCFG;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::syssts0_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::SYSSTS0;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::dvstctr0_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::DVSTCTR0;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::cfifo_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::CFIFO;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::cfifol_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::CFIFOL;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::d0fifo_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::D0FIFO;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::d0fifol_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::D0FIFOL;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::d1fifo_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::D1FIFO;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::d1fifol_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::D1FIFOL;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::cfifosel_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::CFIFOSEL;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::d0fifosel_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::D0FIFOSEL;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::d1fifosel_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::D1FIFOSEL;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::cfifoctr_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::CFIFOCTR;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::d0fifoctr_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::D0FIFOCTR;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::d1fifoctr_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::D1FIFOCTR;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::intenb0_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::INTENB0;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::intenb1_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::INTENB1;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::brdyenb_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::BRDYENB;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::nrdyenb_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::NRDYENB;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::bempenb_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::BEMPENB;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::sofcfg_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::SOFCFG;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::intsts0_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::INTSTS0;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::intsts1_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::INTSTS1;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::brdysts_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::BRDYSTS;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::nrdysts_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::NRDYSTS;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::bempsts_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::BEMPSTS;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::frmnum_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::FRMNUM;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::dvchgr_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::DVCHGR;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::usbaddr_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::USBADDR;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::usbreq_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::USBREQ;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::usbval_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::USBVAL;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::usbindx_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::USBINDX;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::usbleng_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::USBLENG;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::dcpcfg_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::DCPCFG;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::dcpmaxp_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::DCPMAXP;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::dcpctr_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::DCPCTR;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::pipesel_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::PIPESEL;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::pipecfg_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::PIPECFG;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::pipemaxp_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::PIPEMAXP;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::pipeperi_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::PIPEPERI;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::pipe1ctr_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::PIPE1CTR;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::pipe2ctr_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::PIPE2CTR;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::pipe3ctr_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::PIPE3CTR;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::pipe4ctr_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::PIPE4CTR;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::pipe5ctr_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::PIPE5CTR;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::pipe6ctr_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::PIPE6CTR;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::pipe7ctr_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::PIPE7CTR;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::pipe8ctr_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::PIPE8CTR;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::pipe9ctr_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::PIPE9CTR;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::pipe1tre_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::PIPE1TRE;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::pipe2tre_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::PIPE2TRE;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::pipe3tre_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::PIPE3TRE;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::pipe4tre_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::PIPE4TRE;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::pipe5tre_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::PIPE5TRE;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::pipe1trn_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::PIPE1TRN;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::pipe2trn_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::PIPE2TRN;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::pipe3trn_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::PIPE3TRN;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::pipe4trn_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::PIPE4TRN;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::pipe5trn_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::PIPE5TRN;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::devadd0_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::DEVADD0;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::devadd1_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::DEVADD1;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::devadd2_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::DEVADD2;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::devadd3_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::DEVADD3;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::devadd4_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::DEVADD4;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::devadd5_t usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::DEVADD5;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::physlew_t  usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::PHYSLEW;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::dpusr0r_t  usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::DPUSR0R;
	template <uint32_t base, peripheral per, class IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec> typename usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::dpusr1r_t  usb_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::DPUSR1R;
}
