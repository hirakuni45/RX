#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600 グループ・USB[ab] 定義 @n
			RX64M/RX71M/RX651/RX65N/RX72M/RX72N/RX66T/RX72T
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  USB コア・クラス
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct usb_core_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  システムコンフィギュレーションコントロールレジスタ（SYSCFG）
			@param[in]	ofs		オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct syscfg_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		typedef syscfg_t<base + 0x00> SYSCFG_;
		static  SYSCFG_ SYSCFG;


		//-----------------------------------------------------------------//
		/*!
			@brief  システムコンフィギュレーションステータスレジスタ 0（SYSSTS0）
			@param[in]	ofs		オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct syssts0_t : public ro16_t<ofs> {
			typedef ro16_t<ofs> in_;
			using in_::operator ();

			bits_ro_t<in_, bitpos::B0, 2>   LNST;
			bit_ro_t <in_, bitpos::B2>	    IDMON;

			bit_ro_t <in_, bitpos::B5>	    SOFEA;
			bit_ro_t <in_, bitpos::B6>	    HTACT;

			bits_ro_t<in_, bitpos::B14, 2>  OVCMON;
		};
		typedef syssts0_t<base + 0x04> SYSSTS0_;
		static  SYSSTS0_ SYSSTS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  デバイスステートコントロールレジスタ 0（DVSTCTR0）
			@param[in]	ofs		オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dvstctr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		typedef dvstctr0_t<base + 0x08> DVSTCTR0_;
		static  DVSTCTR0_ DVSTCTR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  CFIFO ポートレジスタ（CFIFO）
			@param[in]	ofs		オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x14> CFIFO_;  // MBW: 1
		static  CFIFO_ CFIFO;
		typedef rw8_t<base + 0x14> CFIFOL_;  // MBW: 0
		static  CFIFOL_ CFIFOL;


		//-----------------------------------------------------------------//
		/*!
			@brief  D0FIFO ポートレジスタ（D0FIFO）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t <base + 0x18> D0FIFO_;
		static  D0FIFO_ D0FIFO;
		typedef rw8_t <base + 0x18> D0FIFOL_;
		static  D0FIFOL_ D0FIFOL;


		//-----------------------------------------------------------------//
		/*!
			@brief  D1FIFO ポートレジスタ（D1FIFO）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t <base + 0x1C> D1FIFO_;
		static  D1FIFO_ D1FIFO;
		typedef rw8_t <base + 0x1C> D1FIFOL_;
		static  D1FIFOL_ D1FIFOL;


		//-----------------------------------------------------------------//
		/*!
			@brief  CFIFO ポート選択レジスタ（CFIFOSEL）
			@param[in]	ofs		オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cfifosel_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		typedef cfifosel_t<base + 0x20> CFIFOSEL_;
		static  CFIFOSEL_ CFIFOSEL;


		//-----------------------------------------------------------------//
		/*!
			@brief  CFIFO ポート選択レジスタ（D0FIFOSEL, D1FIFOSEL）
			@param[in]	ofs		オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dxfifosel_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		typedef dxfifosel_t<base + 0x28> D0FIFOSEL_;
		static  D0FIFOSEL_ D0FIFOSEL;
		typedef dxfifosel_t<base + 0x2C> D1FIFOSEL_;
		static  D1FIFOSEL_ D1FIFOSEL;


		//-----------------------------------------------------------------//
		/*!
			@brief  ポートコントロールレジスタ（CFIFOCTR, D0FIFOCTR, D1FIFOCTR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct xfifoctr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 9>   DTLN;

			bit_rw_t <io_, bitpos::B13>	    FRDY;
			bit_rw_t <io_, bitpos::B14>	    BCLR;
			bit_rw_t <io_, bitpos::B15>	    BVAL;
		};
		typedef xfifoctr_t<base + 0x22> CFIFOCTR_;
		static  CFIFOCTR_ CFIFOCTR;
		typedef xfifoctr_t<base + 0x2A> D0FIFOCTR_;
		static  D0FIFOCTR_ D0FIFOCTR;
		typedef xfifoctr_t<base + 0x2E> D1FIFOCTR_;
		static  D1FIFOCTR_ D1FIFOCTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込み許可レジスタ 0（INTENB0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct intenb0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		typedef intenb0_t<base + 0x30> INTENB0_;
		static  INTENB0_ INTENB0;


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込み許可レジスタ 1（INTENB1）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct intenb1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		typedef intenb1_t<base + 0x32> INTENB1_;
		static  INTENB1_ INTENB1;


		//-----------------------------------------------------------------//
		/*!
			@brief  BRDY 割り込み許可レジスタ（BRDYENB）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct brdyenb_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		typedef brdyenb_t<base + 0x36> BRDYENB_;
		static  BRDYENB_ BRDYENB;


		//-----------------------------------------------------------------//
		/*!
			@brief  NRDY 割り込み許可レジスタ（NRDYENB）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct nrdyenb_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		typedef nrdyenb_t<base + 0x38> NRDYENB_;
		static  NRDYENB_ NRDYENB;


		//-----------------------------------------------------------------//
		/*!
			@brief  BEMP 割り込み許可レジスタ（BEMPENB）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct bempenb_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		typedef bempenb_t<base + 0x3A> BEMPENB_;
		static  BEMPENB_ BEMPENB;


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みステータスレジスタ 0（INTSTS0）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct intsts0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		typedef intsts0_t<base + 0x40> INTSTS0_;
		static  INTSTS0_ INTSTS0;


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みステータスレジスタ 1（INTSTS1）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct intsts1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		typedef intsts1_t<base + 0x42> INTSTS1_;
		static  INTSTS1_ INTSTS1;


		//-----------------------------------------------------------------//
		/*!
			@brief  BRDY 割り込みステータスレジスタ（BRDYSTS）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct brdysts_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		typedef brdysts_t<base + 0x46> BRDYSTS_;
		static  BRDYSTS_ BRDYSTS;


		//-----------------------------------------------------------------//
		/*!
			@brief  NRDY 割り込みステータスレジスタ（NRDYSTS）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct nrdysts_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		typedef nrdysts_t<base + 0x48> NRDYSTS_;
		static  NRDYSTS_ NRDYSTS;


		//-----------------------------------------------------------------//
		/*!
			@brief  BEMP 割り込みステータスレジスタ（BEMPSTS）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct bempsts_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		typedef bempsts_t<base + 0x4A> BEMPSTS_;
		static  BEMPSTS_ BEMPSTS;


		//-----------------------------------------------------------------//
		/*!
			@brief  フレームナンバレジスタ（FRMNUM）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct frmnum_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 11>   FRNM;

			bit_rw_t <io_, bitpos::B14>      CRCE;
			bit_rw_t <io_, bitpos::B15>      OVRN;
		};
		typedef frmnum_t<base + 0x4C> FRMNUM_;
		static  FRMNUM_ FRMNUM;


		//-----------------------------------------------------------------//
		/*!
			@brief  デバイスステート切り替えレジスタ（DVCHGR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dvchgr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B15>   DVCHG;
		};
		typedef dvchgr_t<base + 0x4E> DVCHGR_;
		static  DVCHGR_ DVCHGR;


		//-----------------------------------------------------------------//
		/*!
			@brief  USB アドレスレジスタ（USBADDR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct usbaddr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 7>   USBADDR;
			bits_rw_t<io_, bitpos::B8, 4>   STSRECOV;
		};
		typedef usbaddr_t<base + 0x50> USBADDR_;
		static  USBADDR_ USBADDR;


		//-----------------------------------------------------------------//
		/*!
			@brief  USB リクエストタイプレジスタ（USBREQ）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct usbreq_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>   BMREQUESTTYPE;
			bits_rw_t<io_, bitpos::B8, 8>   BREQUEST;
		};
		typedef usbreq_t<base + 0x54> USBREQ_;
		static  USBREQ_ USBREQ;


		//-----------------------------------------------------------------//
		/*!
			@brief  USB リクエストバリューレジスタ（USBVAL）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x56> USBVAL_;
		static  USBVAL_ USBVAL;


		//-----------------------------------------------------------------//
		/*!
			@brief  USB リクエストインデックスレジスタ（USBINDX）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x58> USBINDX_;
		static  USBINDX_ USBINDX;


		//-----------------------------------------------------------------//
		/*!
			@brief  USB リクエストレングスレジスタ（USBLENG）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x5A> USBLENG_;
		static  USBLENG_ USBLENG;


		//-----------------------------------------------------------------//
		/*!
			@brief  DCP コンフィギュレーションレジスタ（DCPCFG）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dcpcfg_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B4>   DIR;

			bit_rw_t<io_, bitpos::B7>   SHTNAK;
		};
		typedef dcpcfg_t<base + 0x5C> DCPCFG_;
		static  DCPCFG_ DCPCFG;


		//-----------------------------------------------------------------//
		/*!
			@brief  DCP マックスパケットサイズレジスタ（DCPMAXP）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dcpmaxp_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  7>   MXPS;

			bits_rw_t<io_, bitpos::B12, 4>   DEVSEL;
		};
		typedef dcpmaxp_t<base + 0x5E> DCPMAXP_;
		static  DCPMAXP_ DCPMAXP;


		//-----------------------------------------------------------------//
		/*!
			@brief  DCP コントロールレジスタ（DCPCTR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dcpctr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		typedef dcpctr_t<base + 0x60> DCPCTR_;
		static  DCPCTR_ DCPCTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  パイプウィンドウ選択レジスタ（PIPESEL）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pipesel_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>   PIPESEL;
		};
		typedef pipesel_t<base + 0x64> PIPESEL_;
		static  PIPESEL_ PIPESEL;


		//-----------------------------------------------------------------//
		/*!
			@brief  パイプコンフィギュレーションレジスタ（PIPECFG）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pipecfg_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		typedef pipecfg_t<base + 0x68> PIPECFG_;
		static  PIPECFG_ PIPECFG;


		//-----------------------------------------------------------------//
		/*!
			@brief  パイプマックスパケットサイズレジスタ（PIPEMAXP）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pipemaxp_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 9>   MXPS;

			bits_rw_t<io_, bitpos::B12, 4>  DEVSEL;
		};
		typedef pipemaxp_t<base + 0x6C> PIPEMAXP_;
		static  PIPEMAXP_ PIPEMAXP;


		//-----------------------------------------------------------------//
		/*!
			@brief  パイプ周期制御レジスタ（PIPEPERI）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pipeperi_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>   IITV;

			bit_rw_t <io_, bitpos::B12>     IFIS;
		};
		typedef pipeperi_t<base + 0x6E> PIPEPERI_;
		static  PIPEPERI_ PIPEPERI;


		//-----------------------------------------------------------------//
		/*!
			@brief  パイプ n コントロールレジスタ（PIPExCTR）（n = 1 ～ 5）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pipexctr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		typedef pipexctr_t<base + 0x70>  PIPE1CTR_;
		static  PIPE1CTR_ PIPE1CTR;
		typedef pipexctr_t<base + 0x72>  PIPE2CTR_;
		static  PIPE2CTR_ PIPE2CTR;
		typedef pipexctr_t<base + 0x74>  PIPE3CTR_;
		static  PIPE3CTR_ PIPE3CTR;
		typedef pipexctr_t<base + 0x76>  PIPE4CTR_;
		static  PIPE4CTR_ PIPE4CTR;
		typedef pipexctr_t<base + 0x78>  PIPE5CTR_;
		static  PIPE5CTR_ PIPE5CTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  パイプ n コントロールレジスタ（PIPEyCTR）（n = 6 ～ 9）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pipeyctr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
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
		typedef pipeyctr_t<base + 0x7A>  PIPE6CTR_;
		static  PIPE6CTR_ PIPE6CTR;
		typedef pipeyctr_t<base + 0x7C>  PIPE7CTR_;
		static  PIPE7CTR_ PIPE7CTR;
		typedef pipeyctr_t<base + 0x7E>  PIPE8CTR_;
		static  PIPE8CTR_ PIPE8CTR;
		typedef pipeyctr_t<base + 0x80>  PIPE9CTR_;
		static  PIPE9CTR_ PIPE9CTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  パイプコントロールレジスタ（PIPECTR）（[0 ～ 8]）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pipectr_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j < 9) { io_::index = j * 2; } }

			bits_rw_t<io_, bitpos::B0, 2>   PID;

			bit_rw_t <io_, bitpos::B5>      PBUSY;
			bit_rw_t <io_, bitpos::B6>      SQMON;
			bit_rw_t <io_, bitpos::B7>      SQSET;
			bit_rw_t <io_, bitpos::B8>      SQCLR;
			bit_rw_t <io_, bitpos::B9>      ACLRM;

			bit_rw_t <io_, bitpos::B10>     ATREPM;		///< for 0 to 4

			bit_rw_t <io_, bitpos::B14>     INBUFM;		///< for 0 to 4
			bit_rw_t <io_, bitpos::B15>     BSTS;

			pipectr_t& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef pipectr_t<base + 0x70>  PIPECTR_;
		static  PIPECTR_ PIPECTR;


		//-----------------------------------------------------------------//
		/*!
			@brief  パイプ n トランザクションカウンタイネーブルレジスタ（PIPEnTRE）（n = 1 ～ 5）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pipentre_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B8>      TRCLR;
			bit_rw_t <io_, bitpos::B9>      TRENB;
		};
		typedef pipentre_t<base + 0x90>  PIPE1TRE_;
		static  PIPE1TRE_ PIPE1TRE;
		typedef pipentre_t<base + 0x94>  PIPE2TRE_;
		static  PIPE2TRE_ PIPE2TRE;
		typedef pipentre_t<base + 0x98>  PIPE3TRE_;
		static  PIPE3TRE_ PIPE3TRE;
		typedef pipentre_t<base + 0x9C>  PIPE4TRE_;
		static  PIPE4TRE_ PIPE4TRE;
		typedef pipentre_t<base + 0xA0>  PIPE5TRE_;
		static  PIPE5TRE_ PIPE5TRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  パイプトランザクションカウンタイネーブルレジスタ（PIPETRE）（0 ～ 4）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pipetre_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j < 5) { io_::index = j * 4; } }

			bit_rw_t<io_, bitpos::B8>   TRCLR;
			bit_rw_t<io_, bitpos::B9>   TRENB;

			pipetre_t& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef pipetre_t<base + 0x90> PIPETRE_;
		static PIPETRE_ PIPETRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  パイプ n トランザクションカウンタレジスタ（PIPEnTRN）（n = 1 ～ 5）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x92>  PIPE1TRN_;
		static  PIPE1TRN_ PIPE1TRN;
		typedef rw16_t<base + 0x96>  PIPE2TRN_;
		static  PIPE2TRN_ PIPE2TRN;
		typedef rw16_t<base + 0x9A>  PIPE3TRN_;
		static  PIPE3TRN_ PIPE3TRN;
		typedef rw16_t<base + 0x9E>  PIPE4TRN_;
		static  PIPE4TRN_ PIPE4TRN;
		typedef rw16_t<base + 0xA2>  PIPE5TRN_;
		static  PIPE5TRN_ PIPE5TRN;


		//-----------------------------------------------------------------//
		/*!
			@brief  パイプトランザクションカウンタレジスタ（PIPETRN）（0 ～ 4）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pipetrn_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j < 5) { io_::index = j * 4; } }

			pipetrn_t& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef pipetrn_t<base + 0x92> PIPETRN_;
		static PIPETRN_ PIPETRN;


		//-----------------------------------------------------------------//
		/*!
			@brief  デバイスアドレス n コンフィギュレーションレジスタ（DEVADDn）（n = 0 ～ 5）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct devaddn_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B6, 2>  USBSPD;
		};
		typedef devaddn_t<base + 0xD0>  DEVADD0_;
		static  DEVADD0_ DEVADD0;
		typedef devaddn_t<base + 0xD2>  DEVADD1_;
		static  DEVADD1_ DEVADD1;
		typedef devaddn_t<base + 0xD4>  DEVADD2_;
		static  DEVADD2_ DEVADD2;
		typedef devaddn_t<base + 0xD6>  DEVADD3_;
		static  DEVADD3_ DEVADD3;
		typedef devaddn_t<base + 0xD8>  DEVADD4_;
		static  DEVADD4_ DEVADD4;
		typedef devaddn_t<base + 0xDA>  DEVADD5_;
		static  DEVADD5_ DEVADD5;


		//-----------------------------------------------------------------//
		/*!
			@brief  デバイスアドレスコンフィギュレーションレジスタ（DEVADD）（[0 ～ 5]）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct devadd_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j < 6) { io_::index = j * 2; } }

			bits_rw_t<io_, bitpos::B6, 2>  USBSPD;

			devadd_t& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef devadd_t<base + 0xD0>  DEVADD_;
		static DEVADD_ DEVADD;
	};
	template <uint32_t base> typename usb_core_t<base>::SYSCFG_     usb_core_t<base>::SYSCFG;
	template <uint32_t base> typename usb_core_t<base>::SYSSTS0_    usb_core_t<base>::SYSSTS0;
	template <uint32_t base> typename usb_core_t<base>::DVSTCTR0_   usb_core_t<base>::DVSTCTR0;
	template <uint32_t base> typename usb_core_t<base>::CFIFO_      usb_core_t<base>::CFIFO;
	template <uint32_t base> typename usb_core_t<base>::D0FIFO_     usb_core_t<base>::D0FIFO;
	template <uint32_t base> typename usb_core_t<base>::D1FIFO_     usb_core_t<base>::D1FIFO;
	template <uint32_t base> typename usb_core_t<base>::CFIFOSEL_   usb_core_t<base>::CFIFOSEL;
	template <uint32_t base> typename usb_core_t<base>::D0FIFOSEL_  usb_core_t<base>::D0FIFOSEL;
	template <uint32_t base> typename usb_core_t<base>::D1FIFOSEL_  usb_core_t<base>::D1FIFOSEL;
	template <uint32_t base> typename usb_core_t<base>::CFIFOCTR_   usb_core_t<base>::CFIFOCTR;
	template <uint32_t base> typename usb_core_t<base>::D0FIFOCTR_  usb_core_t<base>::D0FIFOCTR;
	template <uint32_t base> typename usb_core_t<base>::D1FIFOCTR_  usb_core_t<base>::D1FIFOCTR;
	template <uint32_t base> typename usb_core_t<base>::INTENB0_    usb_core_t<base>::INTENB0;
	template <uint32_t base> typename usb_core_t<base>::INTENB1_    usb_core_t<base>::INTENB1;
	template <uint32_t base> typename usb_core_t<base>::BRDYENB_    usb_core_t<base>::BRDYENB;
	template <uint32_t base> typename usb_core_t<base>::NRDYENB_    usb_core_t<base>::NRDYENB;
	template <uint32_t base> typename usb_core_t<base>::BEMPENB_    usb_core_t<base>::BEMPENB;
	template <uint32_t base> typename usb_core_t<base>::INTSTS0_    usb_core_t<base>::INTSTS0;
	template <uint32_t base> typename usb_core_t<base>::INTSTS1_    usb_core_t<base>::INTSTS1;
	template <uint32_t base> typename usb_core_t<base>::BRDYSTS_    usb_core_t<base>::BRDYSTS;
	template <uint32_t base> typename usb_core_t<base>::NRDYSTS_    usb_core_t<base>::NRDYSTS;
	template <uint32_t base> typename usb_core_t<base>::BEMPSTS_    usb_core_t<base>::BEMPSTS;
	template <uint32_t base> typename usb_core_t<base>::FRMNUM_     usb_core_t<base>::FRMNUM;
	template <uint32_t base> typename usb_core_t<base>::DVCHGR_     usb_core_t<base>::DVCHGR;
	template <uint32_t base> typename usb_core_t<base>::USBADDR_    usb_core_t<base>::USBADDR;
	template <uint32_t base> typename usb_core_t<base>::USBREQ_     usb_core_t<base>::USBREQ;
	template <uint32_t base> typename usb_core_t<base>::USBVAL_     usb_core_t<base>::USBVAL;
	template <uint32_t base> typename usb_core_t<base>::USBINDX_    usb_core_t<base>::USBINDX;
	template <uint32_t base> typename usb_core_t<base>::USBLENG_    usb_core_t<base>::USBLENG;
	template <uint32_t base> typename usb_core_t<base>::DCPCFG_     usb_core_t<base>::DCPCFG;
	template <uint32_t base> typename usb_core_t<base>::DCPMAXP_    usb_core_t<base>::DCPMAXP;
	template <uint32_t base> typename usb_core_t<base>::DCPCTR_     usb_core_t<base>::DCPCTR;
	template <uint32_t base> typename usb_core_t<base>::PIPESEL_    usb_core_t<base>::PIPESEL;
	template <uint32_t base> typename usb_core_t<base>::PIPECFG_    usb_core_t<base>::PIPECFG;
	template <uint32_t base> typename usb_core_t<base>::PIPEMAXP_   usb_core_t<base>::PIPEMAXP;
	template <uint32_t base> typename usb_core_t<base>::PIPEPERI_   usb_core_t<base>::PIPEPERI;
	template <uint32_t base> typename usb_core_t<base>::PIPE1CTR_   usb_core_t<base>::PIPE1CTR;
	template <uint32_t base> typename usb_core_t<base>::PIPE2CTR_   usb_core_t<base>::PIPE2CTR;
	template <uint32_t base> typename usb_core_t<base>::PIPE3CTR_   usb_core_t<base>::PIPE3CTR;
	template <uint32_t base> typename usb_core_t<base>::PIPE4CTR_   usb_core_t<base>::PIPE4CTR;
	template <uint32_t base> typename usb_core_t<base>::PIPE5CTR_   usb_core_t<base>::PIPE5CTR;
	template <uint32_t base> typename usb_core_t<base>::PIPE6CTR_   usb_core_t<base>::PIPE6CTR;
	template <uint32_t base> typename usb_core_t<base>::PIPE7CTR_   usb_core_t<base>::PIPE7CTR;
	template <uint32_t base> typename usb_core_t<base>::PIPE8CTR_   usb_core_t<base>::PIPE8CTR;
	template <uint32_t base> typename usb_core_t<base>::PIPE9CTR_   usb_core_t<base>::PIPE9CTR;
	template <uint32_t base> typename usb_core_t<base>::PIPECTR_    usb_core_t<base>::PIPECTR;
	template <uint32_t base> typename usb_core_t<base>::PIPE1TRE_   usb_core_t<base>::PIPE1TRE;
	template <uint32_t base> typename usb_core_t<base>::PIPE2TRE_   usb_core_t<base>::PIPE2TRE;
	template <uint32_t base> typename usb_core_t<base>::PIPE3TRE_   usb_core_t<base>::PIPE3TRE;
	template <uint32_t base> typename usb_core_t<base>::PIPE4TRE_   usb_core_t<base>::PIPE4TRE;
	template <uint32_t base> typename usb_core_t<base>::PIPE5TRE_   usb_core_t<base>::PIPE5TRE;
	template <uint32_t base> typename usb_core_t<base>::PIPETRE_    usb_core_t<base>::PIPETRE;
	template <uint32_t base> typename usb_core_t<base>::PIPE1TRN_   usb_core_t<base>::PIPE1TRN;
	template <uint32_t base> typename usb_core_t<base>::PIPE2TRN_   usb_core_t<base>::PIPE2TRN;
	template <uint32_t base> typename usb_core_t<base>::PIPE3TRN_   usb_core_t<base>::PIPE3TRN;
	template <uint32_t base> typename usb_core_t<base>::PIPE4TRN_   usb_core_t<base>::PIPE4TRN;
	template <uint32_t base> typename usb_core_t<base>::PIPE5TRN_   usb_core_t<base>::PIPE5TRN;
	template <uint32_t base> typename usb_core_t<base>::PIPETRN_    usb_core_t<base>::PIPETRN;
	template <uint32_t base> typename usb_core_t<base>::DEVADD0_    usb_core_t<base>::DEVADD0;
	template <uint32_t base> typename usb_core_t<base>::DEVADD1_    usb_core_t<base>::DEVADD1;
	template <uint32_t base> typename usb_core_t<base>::DEVADD2_    usb_core_t<base>::DEVADD2;
	template <uint32_t base> typename usb_core_t<base>::DEVADD3_    usb_core_t<base>::DEVADD3;
	template <uint32_t base> typename usb_core_t<base>::DEVADD4_    usb_core_t<base>::DEVADD4;
	template <uint32_t base> typename usb_core_t<base>::DEVADD5_    usb_core_t<base>::DEVADD5;
	template <uint32_t base> typename usb_core_t<base>::DEVADD_     usb_core_t<base>::DEVADD;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  USBa 定義クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	IVT		割り込みベクター型
		@param[in]	ivec	USBI 割り込み Vector
		@param[in]	rvec	USBR 割り込み Vector
		@param[in]	d0vec	D0 割り込み Vector
		@param[in]	d1vec	D1 割り込み Vector
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, typename IVT,
		IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec>
	struct usb_a_t : public usb_core_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto I_VEC      = ivec;	///< USBI 割り込み Vector
		static constexpr auto R_VEC      = rvec;	///< USBR 割り込み Vector
		static constexpr auto D0_VEC     = d0vec;	///< D0 割り込み Vector
		static constexpr auto D1_VEC     = d1vec;	///< D1 割り込み Vector


		//-----------------------------------------------------------------//
		/*!
			@brief  SOF 出力コンフィギュレーションレジスタ（SOFCFGa）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sofcfg_a_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B4>    EDGESTS;

			bit_rw_t<io_, bitpos::B6>    BRDYM;
		};
		typedef sofcfg_a_t<base + 0x3C> SOFCFG_;
		static  SOFCFG_ SOFCFG;
	};
	template <uint32_t base, peripheral per,
		typename IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec>
		typename usb_a_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::SOFCFG_
		usb_a_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::SOFCFG;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  USBb 定義クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	IVT		割り込みベクター型
		@param[in]	ivec	USBI 割り込み Vector
		@param[in]	rvec	USBR 割り込み Vector
		@param[in]	d0vec	D0 割り込み Vector
		@param[in]	d1vec	D1 割り込み Vector
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, typename IVT,
		IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec>
	struct usb_b_t : public usb_core_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto I_VEC      = ivec;	///< USBI 割り込み Vector
		static constexpr auto R_VEC      = rvec;	///< USBR 割り込み Vector
		static constexpr auto D0_VEC     = d0vec;	///< D0 割り込み Vector
		static constexpr auto D1_VEC     = d1vec;	///< D1 割り込み Vector


		//-----------------------------------------------------------------//
		/*!
			@brief  SOF 出力コンフィギュレーションレジスタ（SOFCFGb）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sofcfg_b_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B4>    EDGESTS;

			bit_rw_t<io_, bitpos::B6>    BRDYM;

			bit_rw_t<io_, bitpos::B8>    TRNENSEL;
		};
		typedef sofcfg_b_t<base + 0x3C> SOFCFG_;
		static  SOFCFG_ SOFCFG;


		//-----------------------------------------------------------------//
		/*!
			@brief  PHY クロスポイント調整レジスタ（PHYSLEW）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct physlew_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  SLEWR00;
			bit_rw_t<io_, bitpos::B1>  SLEWR01;
			bit_rw_t<io_, bitpos::B2>  SLEWF00;
			bit_rw_t<io_, bitpos::B3>  SLEWF01;
		};
		typedef physlew_t<base + 0xF0>  PHYSLEW_;
		static  PHYSLEW_ PHYSLEW;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイ USB トランシーバ制御 / 端子モニタレジスタ（DPUSR0R）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dpusr0r_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   SRPC0;
			bit_rw_t<io_, bitpos::B1>   RPUE0;

			bit_rw_t<io_, bitpos::B4>   FIXPHY0;

			bit_rw_t<io_, bitpos::B16>  DP0;
			bit_rw_t<io_, bitpos::B17>  DM0;

			bit_rw_t<io_, bitpos::B20>  DOVCA0;
			bit_rw_t<io_, bitpos::B21>  DOVCB0;

			bit_rw_t<io_, bitpos::B23>  DVBSTS0;
		};
		typedef dpusr0r_t<0x000A'0400>  DPUSR0R_;
		static  DPUSR0R_ DPUSR0R;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイ USB サスペンド / レジューム割り込みレジスタ（DPUSR1R）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dpusr1r_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
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
			bit_rw_t<io_, bitpos::B21>  DOVRCRB0;

			bit_rw_t<io_, bitpos::B23>  DVBINT0;
		};
		typedef dpusr1r_t<0x000A'0404>  DPUSR1R_;
		static  DPUSR1R_ DPUSR1R;
	};
	template <uint32_t base, peripheral per,
		typename IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec>
		typename usb_b_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::SOFCFG_
		usb_b_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::SOFCFG;
	template <uint32_t base, peripheral per,
		typename IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec>
		typename usb_b_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::PHYSLEW_
		usb_b_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::PHYSLEW;
	template <uint32_t base, peripheral per,
		typename IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec>
		typename usb_b_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::DPUSR0R_
		usb_b_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::DPUSR0R;
	template <uint32_t base, peripheral per,
		typename IVT, IVT ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec>
		typename usb_b_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::DPUSR1R_
		usb_b_t<base, per, IVT, ivec, rvec, d0vec, d1vec>::DPUSR1R;


#if defined(SIG_RX63T) || defined(SIG_RX63T_S)
	typedef usb_a_t<0x000A'0000, peripheral::USB0, ICU::VECTOR,
		ICU::VECTOR::USBI0, ICU::VECTOR::USBR0, ICU::VECTOR::D0FIFO0, ICU::VECTOR::D1FIFO0> USB0;
#elif defined(SIG_RX66T) || defined(SIG_RX72T)
	typedef usb_b_t<0x000A'0000, peripheral::USB0, ICU::VECTOR,
		ICU::VECTOR::USBI0, ICU::VECTOR::USBR0, ICU::VECTOR::D0FIFO0, ICU::VECTOR::D1FIFO0> USB0;
#else
	typedef usb_b_t<0x000A'0000, peripheral::USB0, ICU::SELECTB,
		ICU::SELECTB::USBI0, ICU::VECTOR::USBR0, ICU::VECTOR::D0FIFO0, ICU::VECTOR::D1FIFO0> USB0;
#endif
}
