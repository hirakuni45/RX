#pragma once
//=========================================================================//
/*!	@file
	@brief	RX63T グループ・システム定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  システム定義基底クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class _>
	struct system_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  システムクロックコントロールレジスタ（SCKCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sckcr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  4> PCKD;
			bits_rw_t<io_, bitpos::B4,  4> PCKC;
			bits_rw_t<io_, bitpos::B8,  4> PCKB;
			bits_rw_t<io_, bitpos::B12, 4> PCKA;
			bits_rw_t<io_, bitpos::B16, 4> BCK;
			bit_rw_t <io_, bitpos::B23>    PSTOP1;
			bits_rw_t<io_, bitpos::B24, 4> ICK;
			bits_rw_t<io_, bitpos::B28, 4> FCK;
		};
		typedef sckcr_t<0x0008'0020> SCKCR_;
		static SCKCR_ SCKCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  システムクロックコントロールレジスタ 2（SCKCR2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sckcr2_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B4, 4> UCK;
		};
		typedef sckcr2_t<0x0008'0024> SCKCR2_;
		static SCKCR2_ SCKCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  システムクロックコントロールレジスタ 3（SCKCR3）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sckcr3_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B8, 3> CKSEL;
		};
		typedef sckcr3_t<0x0008'0026> SCKCR3_;
		static SCKCR3_ SCKCR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  PLL コントロールレジスタ（PLLCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pllcr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> PLIDIV;
			bits_rw_t<io_, bitpos::B8, 6> STC;
		};
		typedef pllcr_t<0x0008'0028> PLLCR_;
		static PLLCR_ PLLCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  PLL コントロールレジスタ 2（PLLCR2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pllcr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> PLLEN;
		};
		typedef pllcr2_t<0x0008'002A> PLLCR2_;
		static PLLCR2_ PLLCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  外部バスクロックコントロールレジスタ（BCKCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct bckcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> PLLEN;
		};
		typedef bckcr_t<0x0008'0030> BCKCR_;
		static BCKCR_ BCKCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  メインクロック発振器コントロールレジスタ（MOSCCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mosccr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> MOSTP;
		};
		typedef mosccr_t<0x0008'0032> MOSCCR_;
		static MOSCCR_ MOSCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  低速オンチップオシレータコントロールレジスタ（LOCOCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct lococr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> LCSTP;
		};
		typedef lococr_t<0x0008'0034> LOCOCR_;
		static LOCOCR_ LOCOCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  IWDT 専用オンチップオシレータコントロールレジスタ（ILOCOCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ilococr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> ILCSTP;
		};
		typedef ilococr_t<0x0008'0035> ILOCOCR_;
		static ILOCOCR_ ILOCOCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  発振停止検出コントロールレジスタ（OSTDCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ostdcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> OSTDIE;
			bit_rw_t<io_, bitpos::B7> OSTDE;
		};
		typedef ostdcr_t<0x0008'0040> OSTDCR_;
		static OSTDCR_ OSTDCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  発振停止検出ステータスレジスタ（OSTDSR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ostdsr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> OSTDF;
		};
		typedef ostdsr_t<0x0008'0041> OSTDSR_;
		static OSTDSR_ OSTDSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	メインクロック発振器強制発振コントロールレジスタ（MOFCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mofcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> MOFXIN;
		};
		typedef mofcr_t<0x0008'C293> MOFCR_;
		static MOFCR_ MOFCR;


		//----  消費電力低減機能  ---------------------------------------------//

		//-----------------------------------------------------------------//
		/*!
			@brief  スタンバイコントロールレジスタ（SBYCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sbycr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B14>	OPE;

			bit_rw_t<io_, bitpos::B15>	SSBY;
		};
		typedef sbycr_t<0x0008'000C> SBYCR_;
		static SBYCR_ SBYCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  モジュールストップコントロールレジスタ A（MSTPCRA）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mstpcra_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B6>  MSTPA6;
			bit_rw_t<io_, bitpos::B7>  MSTPA7;

			bit_rw_t<io_, bitpos::B9>  MSTPA9;

			bit_rw_t<io_, bitpos::B14> MSTPA14;
			bit_rw_t<io_, bitpos::B15> MSTPA15;
			bit_rw_t<io_, bitpos::B16> MSTPA16;
			bit_rw_t<io_, bitpos::B17> MSTPA17;

			bit_rw_t<io_, bitpos::B19> MSTPA19;

			bit_rw_t<io_, bitpos::B23> MSTPA23;
			bit_rw_t<io_, bitpos::B24> MSTPA24;

			bit_rw_t<io_, bitpos::B27> MSTPA27;
			bit_rw_t<io_, bitpos::B28> MSTPA28;
			bit_rw_t<io_, bitpos::B29> MSTPA29;

			bit_rw_t<io_, bitpos::B31> ACSE;
		};
		typedef mstpcra_t<0x0008'0010> MSTPCRA_;
		static MSTPCRA_ MSTPCRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  モジュールストップコントロールレジスタ B（MSTPCRB）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mstpcrb_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B1>  MSTPB1;

			bit_rw_t<io_, bitpos::B4>  MSTPB4;

			bit_rw_t<io_, bitpos::B6>  MSTPB6;

			bit_rw_t<io_, bitpos::B16> MSTPB16;
			bit_rw_t<io_, bitpos::B17> MSTPB17;

			bit_rw_t<io_, bitpos::B19> MSTPB19;
			bit_rw_t<io_, bitpos::B20> MSTPB20;
			bit_rw_t<io_, bitpos::B21> MSTPB21;

			bit_rw_t<io_, bitpos::B23> MSTPB23;

			bit_rw_t<io_, bitpos::B28> MSTPB28;
			bit_rw_t<io_, bitpos::B29> MSTPB29;
			bit_rw_t<io_, bitpos::B30> MSTPB30;
			bit_rw_t<io_, bitpos::B31> MSTPB31;
		};
		typedef mstpcrb_t<0x0008'0014> MSTPCRB_;
		static MSTPCRB_ MSTPCRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  モジュールストップコントロールレジスタ C（MSTPCRC）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mstpcrc_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MSTPC0;

			bit_rw_t<io_, bitpos::B19> MSTPC19;

			bit_rw_t<io_, bitpos::B31> MSTPC31;
		};
		typedef mstpcrc_t<0x0008'0018> MSTPCRC_;
		static MSTPCRC_ MSTPCRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  メインクロック発振器ウェイトコントロールレジスタ（MOSCWTCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct moscwtcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5> MSTS;
		};
		typedef moscwtcr_t<0x0008'00A2> MOSCWTCR_;
		static MOSCWTCR_ MOSCWTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  PLL ウェイトコントロールレジスタ（PLLWTCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pllwtcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5> MSTS;
		};
		typedef pllwtcr_t<0x0008'00A6> PLLWTCR_;
		static PLLWTCR_ PLLWTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイコントロールレジスタ（DPSBYCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dpsbycr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B6> IOKEEP;
			bit_rw_t<io_, bitpos::B7> DPSBY;
		};
		typedef dpsbycr_t<0x0008'C280> DPSBYCR_;
		static DPSBYCR_ DPSBYCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイインタラプトイネーブルレジスタ 0（DPSIER0）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dpsier0_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DIRQ0E;
			bit_rw_t<io_, bitpos::B1> DIRQ1E;
			bit_rw_t<io_, bitpos::B2> DIRQ2E;
			bit_rw_t<io_, bitpos::B3> DIRQ3E;
			bit_rw_t<io_, bitpos::B4> DIRQ4E;
			bit_rw_t<io_, bitpos::B5> DIRQ5E;
			bit_rw_t<io_, bitpos::B6> DIRQ6E;
			bit_rw_t<io_, bitpos::B7> DIRQ7E;
		};
		typedef dpsier0_t<0x0008'C282> DPSIER0_;
		static DPSIER0_ DPSIER0;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイインタラプトイネーブルレジスタ 2（DPSIER2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dpsier2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DLVD1IE;
			bit_rw_t<io_, bitpos::B1> DLVD2IE;

			bit_rw_t<io_, bitpos::B4> DNMIE;
		};
		typedef dpsier2_t<0x0008'C284> DPSIER2_;
		static DPSIER2_ DPSIER2;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイインタラプトフラグレジスタ 0（DPSIFR0）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dpsifr0_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DIRQ0F;
			bit_rw_t<io_, bitpos::B1> DIRQ1F;
			bit_rw_t<io_, bitpos::B2> DIRQ2F;
			bit_rw_t<io_, bitpos::B3> DIRQ3F;
			bit_rw_t<io_, bitpos::B4> DIRQ4F;
			bit_rw_t<io_, bitpos::B5> DIRQ5F;
			bit_rw_t<io_, bitpos::B6> DIRQ6F;
			bit_rw_t<io_, bitpos::B7> DIRQ7F;
		};
		typedef dpsifr0_t<0x0008'C286> DPSIFR0_;
		static DPSIFR0_ DPSIFR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイインタラプトフラグレジスタ 2（DPSIFR2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dpsifr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DLVD1IF;
			bit_rw_t<io_, bitpos::B1> DLVD2IF;

			bit_rw_t<io_, bitpos::B4> DNMIF;
		};
		typedef dpsifr2_t<0x0008'C288> DPSIFR2_;
		static DPSIFR2_ DPSIFR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイインタラプトエッジレジスタ 0（DPSIEGR0）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dpsiegr0_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DIRQ0EG;
			bit_rw_t<io_, bitpos::B1> DIRQ1EG;
			bit_rw_t<io_, bitpos::B2> DIRQ2EG;
			bit_rw_t<io_, bitpos::B3> DIRQ3EG;
			bit_rw_t<io_, bitpos::B4> DIRQ4EG;
			bit_rw_t<io_, bitpos::B5> DIRQ5EG;
			bit_rw_t<io_, bitpos::B6> DIRQ6EG;
			bit_rw_t<io_, bitpos::B7> DIRQ7EG;
		};
		typedef dpsiegr0_t<0x0008'C28A> DPSIEGR0_;
		static DPSIEGR0_ DPSIEGR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイインタラプトエッジレジスタ 2（DPSIEGR2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dpsiegr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DLVD1IEG;
			bit_rw_t<io_, bitpos::B1> DLVD2IEG;

			bit_rw_t<io_, bitpos::B4> DNMIEG;
		};
		typedef dpsiegr2_t<0x0008'C28C> DPSIEGR2_;
		static DPSIEGR2_ DPSIEGR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  ディープスタンバイバックアップレジスタ（DPSBKRy）（y=0 ～ 31）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct dpsbkr_t {
			uint8_t& operator[] (uint32_t idx) {
				idx &= 31;
				return *reinterpret_cast<uint8_t*>(base + idx);
			}
		};
		typedef dpsbkr_t<0x0008'C2A0> DPSBKR_;
		static DPSBKR_ DPSBKR;


		//-------- レジスタライトプロテクション機能

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  プロテクトレジスタ（PRCR）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct prcr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>	   PRC0;
			bit_rw_t <io_, bitpos::B1>	   PRC1;

			bit_rw_t <io_, bitpos::B3>     PRC3;
			bits_rw_t<io_, bitpos::B8, 8>  PRKEY;
		};
		typedef prcr_t<0x0008'03FE> PRCR_;
		static PRCR_ PRCR;


		//-------- リセット機能

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  リセットステータスレジスタ 0（RSTSR0）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct rstsr0_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  PORF;
			bit_rw_t <io_, bitpos::B1>  LVD0RF;
			bit_rw_t <io_, bitpos::B2>  LVD1RF;
			bit_rw_t <io_, bitpos::B3>  LVD2RF;

			bit_rw_t <io_, bitpos::B7>  DPSRSTF;
		};
		typedef rstsr0_t<0x0008'C290> RSTSR0_;
		static RSTSR0_ RSTSR0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  リセットステータスレジスタ 1（RSTSR1）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct rstsr1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  CWSF;
		};
		typedef rstsr1_t<0x0008'C291> RSTSR1_;
		static RSTSR1_ RSTSR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  リセットステータスレジスタ 2（RSTSR2）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct rstsr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  IWDTRF;
			bit_rw_t <io_, bitpos::B1>  WDTRF;
			bit_rw_t <io_, bitpos::B2>  SWRF;
		};
		typedef rstsr2_t<0x0008'00C0> RSTSR2_;
		static RSTSR2_ RSTSR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ソフトウェアリセットレジスタ（SWRR）@n
					0xA501 を書き込むとリセットされます。
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<0x0008'00C2> SWRR_;
		static SWRR_ SWRR;
	};
	template<class _> typename system_t<_>::SCKCR_ system_t<_>::SCKCR;
	template<class _> typename system_t<_>::SCKCR2_ system_t<_>::SCKCR2;
	template<class _> typename system_t<_>::SCKCR3_ system_t<_>::SCKCR3;
	template<class _> typename system_t<_>::PLLCR_ system_t<_>::PLLCR;
	template<class _> typename system_t<_>::PLLCR2_ system_t<_>::PLLCR2;
	template<class _> typename system_t<_>::MOSCCR_ system_t<_>::MOSCCR;
	template<class _> typename system_t<_>::LOCOCR_ system_t<_>::LOCOCR;
	template<class _> typename system_t<_>::ILOCOCR_ system_t<_>::ILOCOCR;
	template<class _> typename system_t<_>::OSTDCR_ system_t<_>::OSTDCR;
	template<class _> typename system_t<_>::OSTDSR_ system_t<_>::OSTDSR;
	template<class _> typename system_t<_>::MOFCR_ system_t<_>::MOFCR;
	template<class _> typename system_t<_>::SBYCR_ system_t<_>::SBYCR;
	template<class _> typename system_t<_>::MSTPCRA_ system_t<_>::MSTPCRA;
	template<class _> typename system_t<_>::MSTPCRB_ system_t<_>::MSTPCRB;
	template<class _> typename system_t<_>::MSTPCRC_ system_t<_>::MSTPCRC;
	template<class _> typename system_t<_>::MOSCWTCR_ system_t<_>::MOSCWTCR;
	template<class _> typename system_t<_>::PLLWTCR_ system_t<_>::PLLWTCR;
	template<class _> typename system_t<_>::DPSBYCR_ system_t<_>::DPSBYCR;
	template<class _> typename system_t<_>::DPSIER0_ system_t<_>::DPSIER0;
	template<class _> typename system_t<_>::DPSIER2_ system_t<_>::DPSIER2;
	template<class _> typename system_t<_>::DPSIFR0_ system_t<_>::DPSIFR0;
	template<class _> typename system_t<_>::DPSIFR2_ system_t<_>::DPSIFR2;
	template<class _> typename system_t<_>::DPSIEGR0_ system_t<_>::DPSIEGR0;
	template<class _> typename system_t<_>::DPSBKR_ system_t<_>::DPSBKR;
	template<class _> typename system_t<_>::PRCR_ system_t<_>::PRCR;
	template<class _> typename system_t<_>::RSTSR0_ system_t<_>::RSTSR0;
	template<class _> typename system_t<_>::RSTSR1_ system_t<_>::RSTSR1;
	template<class _> typename system_t<_>::RSTSR2_ system_t<_>::RSTSR2;
	template<class _> typename system_t<_>::SWRR_ system_t<_>::SWRR;

	typedef system_t<void> SYSTEM;
}
