#pragma once
//=========================================================================//
/*!	@file
	@brief	RX621/RX62N/RX631/RX63N グループ USB 定義 @n
			※この USB ペリフェラルは、LowSpeed(1.5Mbps）に対応していない。
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
		static inline syscfg_t<base + 0x00> SYSCFG;


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

			bit_ro_t <in_, bitpos::B6>	    HTACT;

			bits_ro_t<in_, bitpos::B14, 2>  OVCMON;
		};
		static inline syssts0_t<base + 0x04> SYSSTS0;


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
		static inline dvstctr0_t<base + 0x08> DVSTCTR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  CFIFO ポートレジスタ（CFIFO）
			@param[in]	ofs		オフセット・アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct cfifo_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  H;
			bits_rw_t<io_, bitpos::B8, 8>  L;
		};
		static inline cfifo_t<base + 0x14> CFIFO;


		//-----------------------------------------------------------------//
		/*!
			@brief  D0FIFO ポートレジスタ（D0FIFO）
		*/
		//-----------------------------------------------------------------//
		static inline cfifo_t <base + 0x18> D0FIFO;


		//-----------------------------------------------------------------//
		/*!
			@brief  D1FIFO ポートレジスタ（D1FIFO）
		*/
		//-----------------------------------------------------------------//
		static inline cfifo_t <base + 0x1C> D1FIFO;


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
		static inline cfifosel_t<base + 0x20> CFIFOSEL;


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
		static inline dxfifosel_t<base + 0x28> D0FIFOSEL;
		static inline dxfifosel_t<base + 0x2C> D1FIFOSEL;


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
		static inline xfifoctr_t<base + 0x22> CFIFOCTR;
		static inline xfifoctr_t<base + 0x2A> D0FIFOCTR;
		static inline xfifoctr_t<base + 0x2E> D1FIFOCTR;


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
		static inline intenb0_t<base + 0x30> INTENB0;


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
		static inline intenb1_t<base + 0x32> INTENB1;


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
		static inline brdyenb_t<base + 0x36> BRDYENB;


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
		static inline nrdyenb_t<base + 0x38> NRDYENB;


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
		static inline bempenb_t<base + 0x3A> BEMPENB;


		//-----------------------------------------------------------------//
		/*!
			@brief  SOF 出力コンフィギュレーションレジスタ（SOFCFG）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct sofcfg_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B4>    EDGESTS;

			bit_rw_t<io_, bitpos::B6>    BRDYM;
		};
		static inline sofcfg_t<base + 0x3C> SOFCFG;


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
		static inline intsts0_t<base + 0x40> INTSTS0;


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
		static inline intsts1_t<base + 0x42> INTSTS1;


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
		static inline brdysts_t<base + 0x46> BRDYSTS;


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
		static inline nrdysts_t<base + 0x48> NRDYSTS;


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
		static inline bempsts_t<base + 0x4A> BEMPSTS;


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
		static inline frmnum_t<base + 0x4C> FRMNUM;


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
		static inline dvchgr_t<base + 0x4E> DVCHGR;


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
		static inline usbaddr_t<base + 0x50> USBADDR;


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
		static inline usbreq_t<base + 0x54> USBREQ;


		//-----------------------------------------------------------------//
		/*!
			@brief  USB リクエストバリューレジスタ（USBVAL）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x56> USBVAL;


		//-----------------------------------------------------------------//
		/*!
			@brief  USB リクエストインデックスレジスタ（USBINDX）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x58> USBINDX;


		//-----------------------------------------------------------------//
		/*!
			@brief  USB リクエストレングスレジスタ（USBLENG）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x5A> USBLENG;


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
		static inline dcpcfg_t<base + 0x5C> DCPCFG;


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
		static inline dcpmaxp_t<base + 0x5E> DCPMAXP;


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
		static inline dcpctr_t<base + 0x60> DCPCTR;


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
		static inline pipesel_t<base + 0x64> PIPESEL;


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
		static inline pipecfg_t<base + 0x68> PIPECFG;


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
		static inline pipemaxp_t<base + 0x6C> PIPEMAXP;


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
		static inline pipeperi_t<base + 0x6E> PIPEPERI;


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
		static inline pipexctr_t<base + 0x70>  PIPE1CTR;
		static inline pipexctr_t<base + 0x72>  PIPE2CTR;
		static inline pipexctr_t<base + 0x74>  PIPE3CTR;
		static inline pipexctr_t<base + 0x76>  PIPE4CTR;
		static inline pipexctr_t<base + 0x78>  PIPE5CTR;


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
		static inline pipeyctr_t<base + 0x7A>  PIPE6CTR;
		static inline pipeyctr_t<base + 0x7C>  PIPE7CTR;
		static inline pipeyctr_t<base + 0x7E>  PIPE8CTR;
		static inline pipeyctr_t<base + 0x80>  PIPE9CTR;


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
		static inline pipectr_t<base + 0x70>  PIPECTR;


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
		static inline pipentre_t<base + 0x90>  PIPE1TRE;
		static inline pipentre_t<base + 0x94>  PIPE2TRE;
		static inline pipentre_t<base + 0x98>  PIPE3TRE;
		static inline pipentre_t<base + 0x9C>  PIPE4TRE;
		static inline pipentre_t<base + 0xA0>  PIPE5TRE;


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
		static inline pipetre_t<base + 0x90> PIPETRE;


		//-----------------------------------------------------------------//
		/*!
			@brief  パイプ n トランザクションカウンタレジスタ（PIPEnTRN）（n = 1 ～ 5）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x92>  PIPE1TRN;
		static inline rw16_t<base + 0x96>  PIPE2TRN;
		static inline rw16_t<base + 0x9A>  PIPE3TRN;
		static inline rw16_t<base + 0x9E>  PIPE4TRN;
		static inline rw16_t<base + 0xA2>  PIPE5TRN;


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
		static inline pipetrn_t<base + 0x92> PIPETRN;


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
		static inline devaddn_t<base + 0xD0>  DEVADD0;
		static inline devaddn_t<base + 0xD2>  DEVADD1;
		static inline devaddn_t<base + 0xD4>  DEVADD2;
		static inline devaddn_t<base + 0xD6>  DEVADD3;
		static inline devaddn_t<base + 0xD8>  DEVADD4;
		static inline devaddn_t<base + 0xDA>  DEVADD5;


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
		static inline devadd_t<base + 0xD0>  DEVADD;


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

			bit_rw_t<io_, bitpos::B4>   FIXPHY0;

			bit_rw_t<io_, bitpos::B16>  DP0;
			bit_rw_t<io_, bitpos::B17>  DM0;

			bit_rw_t<io_, bitpos::B20>  DOVCA0;
			bit_rw_t<io_, bitpos::B21>  DOVCB0;

			bit_rw_t<io_, bitpos::B23>  DVBSTS0;

			bit_rw_t<io_, bitpos::B24>  DP1;
			bit_rw_t<io_, bitpos::B24>  DM1;

			bit_rw_t<io_, bitpos::B28>  DOVCA1;
			bit_rw_t<io_, bitpos::B29>  DOVCB1;

			bit_rw_t<io_, bitpos::B31>  DVBSTS1;
		};
		static inline dpusr0r_t<0x000A'0400>  DPUSR0R;


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

			bit_rw_t<io_, bitpos::B8>   DPINTE1;
			bit_rw_t<io_, bitpos::B9>   DMINTE1;

			bit_rw_t<io_, bitpos::B12>  DOVRCRAE1;
			bit_rw_t<io_, bitpos::B13>  DOVRCRBE1;

			bit_rw_t<io_, bitpos::B15>  DVBSE1;

			bit_rw_t<io_, bitpos::B16>  DPINT0;
			bit_rw_t<io_, bitpos::B17>  DMINT0;

			bit_rw_t<io_, bitpos::B20>  DOVRCRA0;
			bit_rw_t<io_, bitpos::B21>  DOVRCRB0;

			bit_rw_t<io_, bitpos::B23>  DVBINT0;

			bit_rw_t<io_, bitpos::B24>  DPINT1;
			bit_rw_t<io_, bitpos::B25>  DMINT1;

			bit_rw_t<io_, bitpos::B28>  DOVRCRA1;
			bit_rw_t<io_, bitpos::B29>  DOVRCRB1;

			bit_rw_t<io_, bitpos::B31>  DVBINT1;
		};
		static inline dpusr1r_t<0x000A'0404>  DPUSR1R;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  USB 定義クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	ivec	USBI 割り込み Vector
		@param[in]	rvec	USBR 割り込み Vector
		@param[in]	d0vec	D0 割り込み Vector
		@param[in]	d1vec	D1 割り込み Vector
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR ivec, ICU::VECTOR rvec, ICU::VECTOR d0vec, ICU::VECTOR d1vec>
	struct usb_t : public usb_core_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto I_VEC      = ivec;	///< USBI 割り込み Vector
		static constexpr auto R_VEC      = rvec;	///< USBR 割り込み Vector
		static constexpr auto D0_VEC     = d0vec;	///< D0 割り込み Vector
		static constexpr auto D1_VEC     = d1vec;	///< D1 割り込み Vector
	};

	typedef usb_t<0x000A'0000, peripheral::USB0,
		ICU::VECTOR::USBI0, ICU::VECTOR::USBR0, ICU::VECTOR::D0FIFO0, ICU::VECTOR::D1FIFO0> USB0;
	typedef usb_t<0x000A'0200, peripheral::USB1,
		ICU::VECTOR::USBI1, ICU::VECTOR::USBR1, ICU::VECTOR::D0FIFO1, ICU::VECTOR::D1FIFO1> USB1;
}
