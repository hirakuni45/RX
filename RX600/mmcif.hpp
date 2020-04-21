#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M/RX71M/RX65N/RX651 マルチメディアカードインタフェース（MMCIF）定義
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
		@brief  マルチメディアカードインタフェースクラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct mmcif_t {

		static const auto PERIPHERAL = per;	///< ペリフェラル型
		static const auto ACC_VEC  = ICU::VECTOR_BL1::ACCIO;
		static const auto ERR_VEC  = ICU::VECTOR_BL1::ERRIO;
		static const auto CDET_VEC = ICU::VECTOR_BL1::CDETIO;
		static const auto MBFA_VEC = ICU::VECTOR::MBFAI;

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  コマンド設定レジスタ（ CECMDSET ）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t ofs>
		struct cecmdset_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>   DATW;

			bit_rw_t <io_, bitpos::B3>      SBIT;

			bit_rw_t <io_, bitpos::B6>      CPDM;
			bit_rw_t <io_, bitpos::B7>      TBIT;
			bit_rw_t <io_, bitpos::B8>      CRCSTE;
			bit_rw_t <io_, bitpos::B9>      BOOTACK;
			bit_rw_t <io_, bitpos::B10>     CRC16C;

			bits_rw_t<io_, bitpos::B12, 2>  RCRC7C;
			bits_rw_t<io_, bitpos::B14, 2>  RIDXC;
			bit_rw_t <io_, bitpos::B16>     CMD12EN;
			bit_rw_t <io_, bitpos::B17>     CMLTE;
			bit_rw_t <io_, bitpos::B18>     DWEN;
			bit_rw_t <io_, bitpos::B19>     WDAT;

			bit_rw_t <io_, bitpos::B21>     RBSY;
			bits_rw_t<io_, bitpos::B22, 2>  RTYP;
			bits_rw_t<io_, bitpos::B24, 6>  CMD;
			bit_rw_t <io_, bitpos::B30>     BOOT;
		};
		typedef cecmdset_t<base + 0x00> CECMDSET_;
		static  CECMDSET_ CECMDSET;


		//-----------------------------------------------------------------//
		/*!
			@brief  アーギュメントレジスタ（ CEARG ）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x08>  CEARG_;
		static  CEARG_ CEARG;


		//-----------------------------------------------------------------//
		/*!
			@brief  自動 CMD12 アーギュメントレジスタ（ CEARGCMD12 ）
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x0C>  CEARGCMD12_;
		static  CEARGCMD12_ CEARGCMD12;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  コマンド制御レジスタ（ CECMDCTRL ）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t ofs>
		struct cecmdctrl_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B3>  BREAK;
		};
		typedef cecmdctrl_t<base + 0x10> CECMDCTRL_;
		static  CECMDCTRL_ CECMDCTRL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  転送ブロック設定レジスタ（ CEBLOCKSET ）
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t ofs>
		struct ceblockset_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  16>  BLKSIZ;
			bits_rw_t<io_, bitpos::B16, 16>  BLKCNT;
		};
		typedef ceblockset_t<base + 0x14> CEBLOCKSET_;
		static  CEBLOCKSET_ CEBLOCKSET;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  クロックコントロールレジスタ (CECLKCTRL)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t ofs>
		struct ceclkctrl_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B4,  4>   SRWDTO;

			bits_rw_t<io_, bitpos::B8,  4>   SRBSYTO;
			bits_rw_t<io_, bitpos::B12, 2>   SRSTOP;
			bits_rw_t<io_, bitpos::B16, 4>   CLKDIV;

			bit_rw_t <io_, bitpos::B24>      CLKEN;

			bit_rw_t <io_, bitpos::B24>      MMCBUSBSY;
		};
		typedef ceclkctrl_t<base + 0x18> CECLKCTRL_;
		static  CECLKCTRL_ CECLKCTRL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バッファアクセス設定レジスタ (CEBUFACC)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t ofs>
		struct cebufacc_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B24>      DMAREN;
			bit_rw_t <io_, bitpos::B25>      DMAWEN;
			bit_rw_t <io_, bitpos::B26>      DMATYP;
		};
		typedef cebufacc_t<base + 0x1C> CEBUFACC_;
		static  CEBUFACC_ CEBUFACC;


		//-----------------------------------------------------------------//
		/*!
			@brief  レスポンスレジスタ 3 (CERESP3)
		*/
		//-----------------------------------------------------------------//
		typedef ro32_t<base + 0x20>  CERESP3_;
		static  CERESP3_ CERESP3;


		//-----------------------------------------------------------------//
		/*!
			@brief  レスポンスレジスタ 2 (CERESP2)
		*/
		//-----------------------------------------------------------------//
		typedef ro32_t<base + 0x24>  CERESP2_;
		static  CERESP2_ CERESP2;


		//-----------------------------------------------------------------//
		/*!
			@brief  レスポンスレジスタ 1 (CERESP1)
		*/
		//-----------------------------------------------------------------//
		typedef ro32_t<base + 0x28>  CERESP1_;
		static  CERESP1_ CERESP1;


		//-----------------------------------------------------------------//
		/*!
			@brief  レスポンスレジスタ 0 (CERESP0)
		*/
		//-----------------------------------------------------------------//
		typedef ro32_t<base + 0x2C>  CERESP0_;
		static  CERESP0_ CERESP0;


		//-----------------------------------------------------------------//
		/*!
			@brief  自動 CMD12 レスポンスレジスタ (CERESPCMD12)
		*/
		//-----------------------------------------------------------------//
		typedef ro32_t<base + 0x30>  CERESPCMD12_;
		static  CERESPCMD12_ CERESPCMD12;


		//-----------------------------------------------------------------//
		/*!
			@brief  データレジスタ (CEDATA)
		*/
		//-----------------------------------------------------------------//
		typedef rw32_t<base + 0x34>  CEDATA_;
		static  CEDATA_ CEDATA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Boot Operation 設定レジスタ (CEBOOT)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t ofs>
		struct ceboot_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 4>   SBTDATTO;
			bits_rw_t<io_, bitpos::B20, 4>   SFSTBTDATTO;
			bits_rw_t<io_, bitpos::B24, 4>   SBTACKTO;
			bits_rw_t<io_, bitpos::B28, 4>   SBTCLKDIV;
		};
		typedef ceboot_t<base + 0x3C> CEBOOT_;
		static  CEBOOT_ CEBOOT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込みステータスフラグレジスタ (CEINT)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t ofs>
		struct ceint_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   RSPTO;
			bit_rw_t<io_, bitpos::B1>   RBSYTO;
			bit_rw_t<io_, bitpos::B2>   RDATTO;
			bit_rw_t<io_, bitpos::B3>   WDATTO;
			bit_rw_t<io_, bitpos::B4>   CRCSTO;

			bit_rw_t<io_, bitpos::B8>   RSPERR;
			bit_rw_t<io_, bitpos::B9>   RIDXERR;
			bit_rw_t<io_, bitpos::B10>  RDATERR;
			bit_rw_t<io_, bitpos::B11>  WDATERR;

			bit_rw_t<io_, bitpos::B14>  BUFVIO;
			bit_rw_t<io_, bitpos::B15>  CMDVIO;
			bit_rw_t<io_, bitpos::B16>  CRSPE;
			bit_rw_t<io_, bitpos::B17>  RBSYE;

			bit_rw_t<io_, bitpos::B20>  BUFREN;
			bit_rw_t<io_, bitpos::B21>  BUFWEN;
			bit_rw_t<io_, bitpos::B22>  BUFRE;
			bit_rw_t<io_, bitpos::B23>  DTRANE;
			bit_rw_t<io_, bitpos::B24>  CMD12CRE;
			bit_rw_t<io_, bitpos::B25>  CMD12RBE;
			bit_rw_t<io_, bitpos::B26>  CMD12DRE;
		};
		typedef ceint_t<base + 0x40> CEINT_;
		static  CEINT_ CEINT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込み要求許可レジスタ (CEINTEN)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t ofs>
		struct ceinten_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   MRSPTO;
			bit_rw_t<io_, bitpos::B1>   MRBSYTO;
			bit_rw_t<io_, bitpos::B2>   MRDATTO;
			bit_rw_t<io_, bitpos::B3>   MWDATTO;
			bit_rw_t<io_, bitpos::B4>   MCRCSTO;

			bit_rw_t<io_, bitpos::B8>   MRSPERR;
			bit_rw_t<io_, bitpos::B9>   MRIDXERR;
			bit_rw_t<io_, bitpos::B10>  MRDATERR;
			bit_rw_t<io_, bitpos::B11>  MWDATERR;

			bit_rw_t<io_, bitpos::B14>  MBUFVIO;
			bit_rw_t<io_, bitpos::B15>  MCMDVIO;
			bit_rw_t<io_, bitpos::B16>  MCRSPE;
			bit_rw_t<io_, bitpos::B17>  MRBSYE;

			bit_rw_t<io_, bitpos::B20>  MBUFREN;
			bit_rw_t<io_, bitpos::B21>  MBUFWEN;
			bit_rw_t<io_, bitpos::B22>  MBUFRE;
			bit_rw_t<io_, bitpos::B23>  MDTRANE;
			bit_rw_t<io_, bitpos::B24>  MCMD12CRE;
			bit_rw_t<io_, bitpos::B25>  MCMD12RBE;
			bit_rw_t<io_, bitpos::B26>  MCMD12DRE;
		};
		typedef ceinten_t<base + 0x44> CEINTEN_;
		static  CEINTEN_ CEINTEN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ステータスレジスタ 1 (CEHOSTSTS1)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t ofs>
		struct cehoststs1_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  16>  RCVBLK;
			bits_rw_t<io_, bitpos::B16,  8>  DATSIG;
			bits_rw_t<io_, bitpos::B24,  8>  RSPIDX;
			bit_rw_t <io_, bitpos::B30>      CMDSIG;
			bit_rw_t <io_, bitpos::B31>      CMDSEQ;
		};
		typedef cehoststs1_t<base + 0x48> CEHOSTSTS1_;
		static  CEHOSTSTS1_ CEHOSTSTS1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ステータスレジスタ 2 (CEHOSTSTS2)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t ofs>
		struct cehoststs2_t : public ro32_t<ofs> {
			typedef ro32_t<ofs> io_;
			using io_::operator ();

			bit_ro_t <io_, bitpos::B5>      BTDATTO;
			bit_ro_t <io_, bitpos::B6>      FSTBTDATTO;
			bit_ro_t <io_, bitpos::B7>      BTACKTO;
			bit_ro_t <io_, bitpos::B8>      STRSPTO;
			bit_ro_t <io_, bitpos::B9>      AC12RSPTO;
			bit_ro_t <io_, bitpos::B10>     RSPBSYTO;
			bit_ro_t <io_, bitpos::B11>     AC12BSYTO;
			bit_ro_t <io_, bitpos::B12>     CRCSTTO;
			bit_ro_t <io_, bitpos::B13>     DATBSYTO;
			bit_ro_t <io_, bitpos::B14>     STRDATTO;

			bits_ro_t<io_, bitpos::B16, 3>  CRCST;

			bit_ro_t <io_, bitpos::B20>     BTACKEBE;
			bit_ro_t <io_, bitpos::B21>     BTACKPATE;
			bit_ro_t <io_, bitpos::B22>     RSPIDXE;
			bit_ro_t <io_, bitpos::B23>     AC12IDXE;
			bit_ro_t <io_, bitpos::B24>     RSPEBE;
			bit_ro_t <io_, bitpos::B25>     AC12REBE;
			bit_ro_t <io_, bitpos::B26>     RDATEBE;
			bit_ro_t <io_, bitpos::B27>     CRCSTEBE;
			bit_ro_t <io_, bitpos::B28>     RSPCRC7E;
			bit_ro_t <io_, bitpos::B29>     AC12CRCE;
			bit_ro_t <io_, bitpos::B30>     CRC16E;
			bit_ro_t <io_, bitpos::B31>     CRCSTE;
		};
		typedef cehoststs2_t<base + 0x4C> CEHOSTSTS2_;
		static  CEHOSTSTS2_ CEHOSTSTS2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  MMC 検出 / ポート制御レジスタ (CEDETECT)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t ofs>
		struct cedetect_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B4>   MCDFALL;
			bit_rw_t <io_, bitpos::B5>   MCDRISE;

			bit_rw_t <io_, bitpos::B12>  CDFALL;
			bit_rw_t <io_, bitpos::B13>  CDRISE;
			bit_rw_t <io_, bitpos::B14>  CDSIG;
		};
		typedef cedetect_t<base + 0x70> CEDETECT_;
		static  CEDETECT_ CEDETECT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  特殊モード設定レジスタ (CEADDMODE)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t ofs>
		struct ceaddmode_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B19>  CLKMAIN;

			bit_rw_t <io_, bitpos::B21>  RESNOUT;
		};
		typedef ceaddmode_t<base + 0x74> CEADDMODE_;
		static  CEADDMODE_ CEADDMODE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バージョンレジスタ (CEVERSION)
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t ofs>
		struct ceversion_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 16>  VERSION;

			bit_rw_t <io_, bitpos::B31>     SWRST;
		};
		typedef ceversion_t<base + 0x7C> CEVERSION_;
		static  CEVERSION_ CEVERSION;
	};
	template <uint32_t base, peripheral per> typename mmcif_t<base, per>::CECMDSET_ mmcif_t<base, per>::CECMDSET;
	template <uint32_t base, peripheral per> typename mmcif_t<base, per>::CEARG_ mmcif_t<base, per>::CEARG;
	template <uint32_t base, peripheral per> typename mmcif_t<base, per>::CEARGCMD12_ mmcif_t<base, per>::CEARGCMD12;
	template <uint32_t base, peripheral per> typename mmcif_t<base, per>::CECMDCTRL_ mmcif_t<base, per>::CECMDCTRL;
	template <uint32_t base, peripheral per> typename mmcif_t<base, per>::CEBLOCKSET_ mmcif_t<base, per>::CEBLOCKSET;
	template <uint32_t base, peripheral per> typename mmcif_t<base, per>::CECLKCTRL_ mmcif_t<base, per>::CECLKCTRL;
	template <uint32_t base, peripheral per> typename mmcif_t<base, per>::CEBUFACC_ mmcif_t<base, per>::CEBUFACC;
	template <uint32_t base, peripheral per> typename mmcif_t<base, per>::CERESP3_ mmcif_t<base, per>::CERESP3;
	template <uint32_t base, peripheral per> typename mmcif_t<base, per>::CERESP2_ mmcif_t<base, per>::CERESP2;
	template <uint32_t base, peripheral per> typename mmcif_t<base, per>::CERESP1_ mmcif_t<base, per>::CERESP1;
	template <uint32_t base, peripheral per> typename mmcif_t<base, per>::CERESP0_ mmcif_t<base, per>::CERESP0;
	template <uint32_t base, peripheral per> typename mmcif_t<base, per>::CERESPCMD12_ mmcif_t<base, per>::CERESPCMD12;
	template <uint32_t base, peripheral per> typename mmcif_t<base, per>::CEDATA_ mmcif_t<base, per>::CEDATA;
	template <uint32_t base, peripheral per> typename mmcif_t<base, per>::CEBOOT_ mmcif_t<base, per>::CEBOOT;
	template <uint32_t base, peripheral per> typename mmcif_t<base, per>::CEINT_ mmcif_t<base, per>::CEINT;
	template <uint32_t base, peripheral per> typename mmcif_t<base, per>::CEINTEN_ mmcif_t<base, per>::CEINTEN;
	template <uint32_t base, peripheral per> typename mmcif_t<base, per>::CEHOSTSTS1_ mmcif_t<base, per>::CEHOSTSTS1;
	template <uint32_t base, peripheral per> typename mmcif_t<base, per>::CEHOSTSTS2_ mmcif_t<base, per>::CEHOSTSTS2;
	template <uint32_t base, peripheral per> typename mmcif_t<base, per>::CEDETECT_ mmcif_t<base, per>::CEDETECT;
	template <uint32_t base, peripheral per> typename mmcif_t<base, per>::CEADDMODE_ mmcif_t<base, per>::CEADDMODE;
	template <uint32_t base, peripheral per> typename mmcif_t<base, per>::CEVERSION_ mmcif_t<base, per>::CEVERSION;


	typedef mmcif_t<0x00088500, peripheral::MMCIF> MMCIF;
}
