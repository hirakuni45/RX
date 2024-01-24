#pragma once
//=========================================================================//
/*!	@file
	@brief	RX24T グループ・システム定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2024 Kunihito Hiramatsu @n
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
	namespace SYSTEM {

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

			bits_rw_t<io_, bitpos::B12, 4> PCKA;

			bits_rw_t<io_, bitpos::B24, 4> ICK;
			bits_rw_t<io_, bitpos::B28, 4> FCK;
		};
		static inline sckcr_t<0x0008'0020> SCKCR;


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
		static inline sckcr3_t<0x0008'0026> SCKCR3;


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
			bit_rw_t <io_, bitpos::B2>    PLLSRCSEL;
			bits_rw_t<io_, bitpos::B8, 6> STC;
		};
		static inline pllcr_t<0x0008'0028> PLLCR;


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
		static inline pllcr2_t<0x0008'002A> PLLCR2;


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
		static inline mosccr_t<0x0008'0032> MOSCCR;


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
		static inline lococr_t<0x0008'0034> LOCOCR;


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
		static inline ilococr_t<0x0008'0035> ILOCOCR;


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
		static inline hococr_t<0x0008'0036> HOCOCR;


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
		static inline hococr2_t<0x0008'0037> HOCOCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  高速オンチップオシレータウェイトコントロールレジスタ (HOCOWTCR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct hocowtcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> HSTS;
		};
		static inline hocowtcr_t<0x0008'00A5> HOCOWTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  発振安定フラグレジスタ（OSCOVFSR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct oscovfsr_t : public ro8_t<base> {
			typedef ro8_t<base> io_;
			using io_::operator ();

			bit_ro_t<ro8_t<base>, bitpos::B0> MOOVF;

			bit_ro_t<ro8_t<base>, bitpos::B2> PLOVF;
			bit_ro_t<ro8_t<base>, bitpos::B3> HCOVF;
		};
		static inline oscovfsr_t<0x0008'003C> OSCOVFSR;


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
		static inline ostdcr_t<0x0008'0040> OSTDCR;


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
		static inline ostdsr_t<0x0008'0041> OSTDSR;


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
		static inline moscwtcr_t<0x0008'00A2> MOSCWTCR;


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

			bit_rw_t<io_, bitpos::B5> MODRV21;
			bit_rw_t<io_, bitpos::B6> MOSEL;
		};
		static inline mofcr_t<0x0008'C293> MOFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  メモリウェイトサイクル設定レジスタ（MEMWAIT）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<0x0008'0031> MEMWAIT;


		//-----------------------------------------------------------------//
		/*!
			@brief  スタンバイコントロールレジスタ（SBYCR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sbycr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B15>	SSBY;
		};
		static inline sbycr_t<0x0008'000C> SBYCR;


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

			bit_rw_t<io_, bitpos::B2>  MSTPA2;
			bit_rw_t<io_, bitpos::B3>  MSTPA3;
			bit_rw_t<io_, bitpos::B4>  MSTPA4;
			bit_rw_t<io_, bitpos::B5>  MSTPA5;

			bit_rw_t<io_, bitpos::B7>  MSTPA7;

			bit_rw_t<io_, bitpos::B9>  MSTPA9;

			bit_rw_t<io_, bitpos::B14> MSTPA14;
			bit_rw_t<io_, bitpos::B15> MSTPA15;
			bit_rw_t<io_, bitpos::B16> MSTPA16;
			bit_rw_t<io_, bitpos::B17> MSTPA17;

			bit_rw_t<io_, bitpos::B19> MSTPA19;

			bit_rw_t<io_, bitpos::B23> MSTPA23;

			bit_rw_t<io_, bitpos::B28> MSTPA28;
		};
		static inline mstpcra_t<0x0008'0010> MSTPCRA;


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

			bit_rw_t<io_, bitpos::B0>  MSTPB0;

			bit_rw_t<io_, bitpos::B6>  MSTPB6;

			bit_rw_t<io_, bitpos::B10> MSTPB10;

			bit_rw_t<io_, bitpos::B17> MSTPB17;

			bit_rw_t<io_, bitpos::B21> MSTPB21;

			bit_rw_t<io_, bitpos::B23> MSTPB23;

			bit_rw_t<io_, bitpos::B25> MSTPB25;
			bit_rw_t<io_, bitpos::B26> MSTPB26;

			bit_rw_t<io_, bitpos::B30> MSTPB30;
		};
		static inline mstpcrb_t<0x0008'0014> MSTPCRB;


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

			bit_rw_t<io_, bitpos::B31> DSLPE;
		};
		static inline mstpcrc_t<0x0008'0018> MSTPCRC;


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
		static inline opccr_t<0x0008'00A0> OPCCR;


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
		static inline prcr_t<0x0008'03FE> PRCR;
	}
}
