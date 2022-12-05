#pragma once
//=====================================================================//
/*!	@file
	@brief	RX220 グループ・システム定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
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

			bits_rw_t<io_, bitpos::B8,  4> PCKB;

			bits_rw_t<io_, bitpos::B16, 4> BCK;

			bits_rw_t<io_, bitpos::B24, 4> ICK;
			bits_rw_t<io_, bitpos::B28, 4> FCK;
		};
		typedef sckcr_t<0x0008'0020> SCKCR_;
		static SCKCR_ SCKCR;


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
			@brief  高速オンチップオシレータコントロールレジスタ (HOCOCR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct hococr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> HCSTP;
		};
		typedef hococr_t<0x0008'0036> HOCOCR_;
		static HOCOCR_ HOCOCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  高速オンチップオシレータコントロールレジスタ 2 (HOCOCR2)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct hococr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> HCFRQ;
		};
		typedef hococr2_t<0x0008'0037> HOCOCR2_;
		static HOCOCR2_ HOCOCR2;


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

			bits_rw_t<io_, bitpos::B1, 3> MODRV;
			bits_rw_t<io_, bitpos::B4, 2> MODRV2;
			bit_rw_t <io_, bitpos::B6>    MOSEL;
		};
		typedef mofcr_t<0x0008'C293> MOFCR_;
		static MOFCR_ MOFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	高速オンチップオシレータ電源コントロールレジスタ（HOCOPCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct hocopcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  HOCOPCNT;
		};
		typedef hocopcr_t<0x0008'C294> HOCOPCR_;
		static HOCOPCR_ HOCOPCR;


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

			bit_rw_t<io_, bitpos::B4>  MSTPA4;
			bit_rw_t<io_, bitpos::B5>  MSTPA5;

			bit_rw_t<io_, bitpos::B9>  MSTPA9;

			bit_rw_t<io_, bitpos::B14> MSTPA14;
			bit_rw_t<io_, bitpos::B15> MSTPA15;

			bit_rw_t<io_, bitpos::B17> MSTPA17;

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

			bit_rw_t<io_, bitpos::B4>  MSTPB4;

			bit_rw_t<io_, bitpos::B6>  MSTPB6;

			bit_rw_t<io_, bitpos::B9>  MSTPB9;

			bit_rw_t<io_, bitpos::B17> MSTPB17;

			bit_rw_t<io_, bitpos::B21> MSTPB21;

			bit_rw_t<io_, bitpos::B23> MSTPB23;

			bit_rw_t<io_, bitpos::B25> MSTPB25;
			bit_rw_t<io_, bitpos::B26> MSTPB26;

			bit_rw_t<io_, bitpos::B30> MSTPB30;
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

			bit_rw_t<io_, bitpos::B6>  MSTPC0;

			bit_rw_t<io_, bitpos::B19> MSTPC19;
			bit_rw_t<io_, bitpos::B20> MSTPC20;

			bit_rw_t<io_, bitpos::B26> MSTPC26;
		};
		typedef mstpcrc_t<0x0008'0018> MSTPCRC_;
		static MSTPCRC_ MSTPCRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  動作電力コントロールレジスタ（OPCCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct opccr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> OPCM;

			bit_rw_t <io_, bitpos::B4>    OPCMTSF;
		};
		typedef opccr_t<0x0008'00A0> OPCCR_;
		static OPCCR_ OPCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  スリープモード復帰クロックソース切り替えレジスタ（RSTCKCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct rstckcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> RSTCKSEL;

			bit_rw_t <io_, bitpos::B4>    RSTCKEN;
		};
		typedef rstckcr_t<0x0008'00A1> RSTCKCR_;
		static RSTCKCR_ RSTCKCR;


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
			@brief  サブクロック発振器ウェイトコントロールレジスタ（SOSCWTCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct soscwtcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5> SSTS;
		};
		typedef soscwtcr_t<0x0008'00A3> SOSCWTCR_;
		static SOSCWTCR_ SOSCWTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  HOCO ウェイトコントロールレジスタ 2（HOCOWTCR2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct hocowtcr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5> HSTS2;
		};
		typedef hocowtcr2_t<0x0008'00A9> HOCOWTCR2_;
		static HOCOWTCR2_ HOCOWTCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  フラッシュ HOCO ソフトウェアスタンバイコントロールレジスタ（FHSSBYCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct fhssbycr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> SOFTCUT;
		};
		typedef fhssbycr_t<0x0008'C28F> FHSSBYCR_;
		static FHSSBYCR_ FHSSBYCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  プロテクトレジスタ（PRCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct prcr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    PRC0;
			bit_rw_t <io_, bitpos::B1>    PRC1;

			bit_rw_t <io_, bitpos::B3>    PRC3;
			bits_rw_t<io_, bitpos::B8, 8> PRKEY;
		};
		typedef prcr_t<0x0008'03FE> PRCR_;
		static PRCR_ PRCR;
	};
	template<class _> typename system_t<_>::SCKCR_ system_t<_>::SCKCR;
	template<class _> typename system_t<_>::SCKCR3_ system_t<_>::SCKCR3;
	template<class _> typename system_t<_>::MOSCCR_ system_t<_>::MOSCCR;
	template<class _> typename system_t<_>::LOCOCR_ system_t<_>::LOCOCR;
	template<class _> typename system_t<_>::ILOCOCR_ system_t<_>::ILOCOCR;
	template<class _> typename system_t<_>::HOCOCR_ system_t<_>::HOCOCR;
	template<class _> typename system_t<_>::HOCOCR2_ system_t<_>::HOCOCR2;
	template<class _> typename system_t<_>::OSTDCR_ system_t<_>::OSTDCR;
	template<class _> typename system_t<_>::OSTDSR_ system_t<_>::OSTDSR;
	template<class _> typename system_t<_>::MOFCR_ system_t<_>::MOFCR;
	template<class _> typename system_t<_>::HOCOPCR_ system_t<_>::HOCOPCR;
	template<class _> typename system_t<_>::SBYCR_ system_t<_>::SBYCR;
	template<class _> typename system_t<_>::MSTPCRA_ system_t<_>::MSTPCRA;
	template<class _> typename system_t<_>::MSTPCRB_ system_t<_>::MSTPCRB;
	template<class _> typename system_t<_>::MSTPCRC_ system_t<_>::MSTPCRC;
	template<class _> typename system_t<_>::OPCCR_ system_t<_>::OPCCR;
	template<class _> typename system_t<_>::RSTCKCR_ system_t<_>::RSTCKCR;
	template<class _> typename system_t<_>::MOSCWTCR_ system_t<_>::MOSCWTCR;
	template<class _> typename system_t<_>::SOSCWTCR_ system_t<_>::SOSCWTCR;
	template<class _> typename system_t<_>::HOCOWTCR2_ system_t<_>::HOCOWTCR2;
	template<class _> typename system_t<_>::FHSSBYCR_ system_t<_>::FHSSBYCR;
	template<class _> typename system_t<_>::PRCR_ system_t<_>::PRCR;

	typedef system_t<void> SYSTEM;
}
