#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ・USB 定義
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
		struct syssts0_t : public rw16_t<base + 0x04> {
			typedef rw16_t<base + 0x04> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>   LNST;
			bit_rw_t <io_, bitpos::B2>	    IDMON;

			bit_rw_t <io_, bitpos::B5>	    SOFEA;
			bit_rw_t <io_, bitpos::B6>	    HTACT;

			bits_rw_t<io_, bitpos::B14, 2>  OVCMON;
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


		//-----------------------------------------------------------------//
		/*!
			@brief  D0FIFO ポートレジスタ（D0FIFO）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x18> D0FIFO;


		//-----------------------------------------------------------------//
		/*!
			@brief  D1FIFO ポートレジスタ（D1FIFO）
		*/
		//-----------------------------------------------------------------//
		static rw16_t<base + 0x1C> D1FIFO;


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
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return per; }
	};
	typedef usb_t<0x000A0000, peripheral::USB> USB;
}
