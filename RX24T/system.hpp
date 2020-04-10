#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・システム定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016 Kunihito Hiramatsu @n
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
	struct system_t_ {

		//-----------------------------------------------------------------//
		/*!
			@brief  システムクロックコントロールレジスタ（SCKCR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sckcr_t_ : public rw32_t<base> {
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
		typedef sckcr_t_<0x00080020> sckcr_t;
		static sckcr_t SCKCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  システムクロックコントロールレジスタ 3（SCKCR3）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sckcr3_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B8, 3> CKSEL;
		};
		typedef sckcr3_t_<0x00080026> sckcr3_t;
		static sckcr3_t SCKCR3;


		//-----------------------------------------------------------------//
		/*!
			@brief  PLL コントロールレジスタ（PLLCR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pllcr_t_ : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> PLIDIV;
			bits_rw_t<io_, bitpos::B8, 6> STC;
		};
		typedef pllcr_t_<0x00080028> pllcr_t;
		static pllcr_t PLLCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  PLL コントロールレジスタ 2（PLLCR2）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pllcr2_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> PLLEN;
		};
		typedef pllcr2_t_<0x0008002A> pllcr2_t;
		static pllcr2_t PLLCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief  メインクロック発振器コントロールレジスタ（MOSCCR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mosccr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> MOSTP;
		};
		typedef mosccr_t_<0x00080032> mosccr_t;
		static mosccr_t MOSCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  低速オンチップオシレータコントロールレジスタ（LOCOCR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct lococr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> LCSTP;
		};
		typedef lococr_t_<0x00080034> lococr_t;
		static lococr_t LOCOCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  IWDT 専用オンチップオシレータコントロールレジスタ（ILOCOCR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ilococr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> ILCSTP;
		};
		typedef ilococr_t_<0x00080035> ilococr_t;
		static ilococr_t ILOCOCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  発振安定フラグレジスタ（OSCOVFSR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct oscovfsr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_ro_t<ro8_t<base>, bitpos::B0> MOOVF;
			bit_ro_t<ro8_t<base>, bitpos::B2> PLOVF;
		};
		typedef oscovfsr_t_<0x0008003C> oscovfsr_t;
		static oscovfsr_t OSCOVFSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  発振停止検出コントロールレジスタ（OSTDCR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ostdcr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> OSTDIE;
			bit_rw_t<io_, bitpos::B7> OSTDE;
		};
		typedef ostdcr_t_<0x00080040> ostdcr_t;
		static ostdcr_t OSTDCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  発振停止検出ステータスレジスタ（OSTDSR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ostdsr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> OSTDF;
		};
		typedef ostdsr_t_<0x00080041> ostdsr_t;
		static ostdsr_t OSTDSR;


		//-----------------------------------------------------------------//
		/*!
			@brief  メインクロック発振器ウェイトコントロールレジスタ（MOSCWTCR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct moscwtcr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5> MSTS;
		};
		typedef moscwtcr_t_<0x000800A2> moscwtcr_t;
		static moscwtcr_t MOSCWTCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	メインクロック発振器強制発振コントロールレジスタ（MOFCR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mofcr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B5> MODRV21;
			bit_rw_t<io_, bitpos::B6> MOSEL;
		};
		typedef mofcr_t_<0x0008C293> mofcr_t;
		static mofcr_t MOFCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  メモリウェイトサイクル設定レジスタ（MEMWAIT）
		*/
		//-----------------------------------------------------------------//
		typedef rw8_t<0x00080031> memwait_t;
		static memwait_t MEMWAIT;


		//-----------------------------------------------------------------//
		/*!
			@brief  スタンバイコントロールレジスタ（SBYCR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct sbycr_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B15>	SSBY;
		};
		typedef sbycr_t_<0x0008000C> sbycr_t;
		static sbycr_t SBYCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  モジュールストップコントロールレジスタ A（MSTPCRA）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mstpcra_t_ : public rw32_t<base> {
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
		typedef mstpcra_t_<0x00080010> mstpcra_t;
		static mstpcra_t MSTPCRA;


		//-----------------------------------------------------------------//
		/*!
			@brief  モジュールストップコントロールレジスタ B（MSTPCRB）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mstpcrb_t_ : public rw32_t<base> {
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
		typedef mstpcrb_t_<0x00080014> mstpcrb_t;
		static mstpcrb_t MSTPCRB;


		//-----------------------------------------------------------------//
		/*!
			@brief  モジュールストップコントロールレジスタ C（MSTPCRC）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mstpcrc_t_ : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B6>  MSTPC0;

			bit_rw_t<io_, bitpos::B19> MSTPC19;

			bit_rw_t<io_, bitpos::B31> DSLPE;
		};
		typedef mstpcrb_t_<0x00080018> mstpcrc_t;
		static mstpcrc_t MSTPCRC;


		//-----------------------------------------------------------------//
		/*!
			@brief  動作電力コントロールレジスタ（OPCCR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct opccr_t_ : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> OPCM;

			bit_rw_t <io_, bitpos::B4>    OPCMTSF;
		};
		typedef opccr_t_<0x000800A0> opccr_t;
		static opccr_t OPCCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  プロテクトレジスタ（PRCR）
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct prcr_t_ : public rw16_t<base> {
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
		typedef prcr_t_<0x000803FE> prcr_t;
		static prcr_t PRCR;
	};

	typedef system_t_<void> SYSTEM;

	template<class _> typename system_t_<_>::sckcr_t system_t_<_>::SCKCR;
	template<class _> typename system_t_<_>::sckcr3_t system_t_<_>::SCKCR3;
	template<class _> typename system_t_<_>::pllcr_t system_t_<_>::PLLCR;
	template<class _> typename system_t_<_>::pllcr2_t system_t_<_>::PLLCR2;
	template<class _> typename system_t_<_>::mosccr_t system_t_<_>::MOSCCR;
	template<class _> typename system_t_<_>::lococr_t system_t_<_>::LOCOCR;
	template<class _> typename system_t_<_>::ilococr_t system_t_<_>::ILOCOCR;
	template<class _> typename system_t_<_>::oscovfsr_t system_t_<_>::OSCOVFSR;
	template<class _> typename system_t_<_>::ostdcr_t system_t_<_>::OSTDCR;
	template<class _> typename system_t_<_>::ostdsr_t system_t_<_>::OSTDSR;
	template<class _> typename system_t_<_>::moscwtcr_t system_t_<_>::MOSCWTCR;
	template<class _> typename system_t_<_>::mofcr_t system_t_<_>::MOFCR;
	template<class _> typename system_t_<_>::memwait_t system_t_<_>::MEMWAIT;
	template<class _> typename system_t_<_>::sbycr_t system_t_<_>::SBYCR;
	template<class _> typename system_t_<_>::mstpcra_t system_t_<_>::MSTPCRA;
	template<class _> typename system_t_<_>::mstpcrb_t system_t_<_>::MSTPCRB;
	template<class _> typename system_t_<_>::mstpcrc_t system_t_<_>::MSTPCRC;
	template<class _> typename system_t_<_>::opccr_t system_t_<_>::OPCCR;
	template<class _> typename system_t_<_>::prcr_t system_t_<_>::PRCR;
}
