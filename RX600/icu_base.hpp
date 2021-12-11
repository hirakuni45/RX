#pragma once
//=============================================================================//
/*!	@file
	@brief	ＲＸグループ・ICU ベース定義（共通部分）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX 割り込みコントローラ・ベース・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class _>
	struct icu_base_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	高速割り込み設定レジスタ (FIR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct fir_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>  FVCT;
			bit_rw_t <io_, bitpos::B15>     FIEN;
		};
		typedef fir_t<0x000872F0> FIR_;
		static FIR_ FIR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ソフトウェア割り込み起動レジスタ (SWINTR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct swintr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     SWINT;
		};
		typedef swintr_t<0x000872E0> SWINTR_;
		static SWINTR_ SWINTR;


#if defined(RX_DMAC_)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMAC 起動要因選択レジスタ m（DMRSRm）（m = DMAC チャネル番号）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x00087400> DMRSR0_;
		static DMRSR0_ DMRSR0;
		typedef rw8_t<0x00087404> DMRSR1_;
		static DMRSR1_ DMRSR1;
		typedef rw8_t<0x00087408> DMRSR2_;
		static DMRSR2_ DMRSR2;
		typedef rw8_t<0x0008740C> DMRSR3_;
		static DMRSR3_ DMRSR3;
		typedef rw8_t<0x00087410> DMRSR4_;
		static DMRSR4_ DMRSR4;
		typedef rw8_t<0x00087414> DMRSR5_;
		static DMRSR5_ DMRSR5;
		typedef rw8_t<0x00087418> DMRSR6_;
		static DMRSR6_ DMRSR6;
		typedef rw8_t<0x0008741C> DMRSR7_;
		static DMRSR7_ DMRSR7;
#endif


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	IRQ コントロールレジスタ i (IRQCRi) (i = 0 ～ 15)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct irqcrn_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B2, 2>  IRQMD;
		};
		typedef irqcrn_t<0x00087500> IRQCR0_;
		static IRQCR0_ IRQCR0;
		typedef irqcrn_t<0x00087501> IRQCR1_;
		static IRQCR1_ IRQCR1;
		typedef irqcrn_t<0x00087502> IRQCR2_;
		static IRQCR2_ IRQCR2;
		typedef irqcrn_t<0x00087503> IRQCR3_;
		static IRQCR3_ IRQCR3;
		typedef irqcrn_t<0x00087504> IRQCR4_;
		static IRQCR4_ IRQCR4;
		typedef irqcrn_t<0x00087505> IRQCR5_;
		static IRQCR5_ IRQCR5;
		typedef irqcrn_t<0x00087506> IRQCR6_;
		static IRQCR6_ IRQCR6;
		typedef irqcrn_t<0x00087507> IRQCR7_;
		static IRQCR7_ IRQCR7;
		typedef irqcrn_t<0x00087508> IRQCR8_;
		static IRQCR8_ IRQCR8;
		typedef irqcrn_t<0x00087509> IRQCR9_;
		static IRQCR9_ IRQCR9;
		typedef irqcrn_t<0x0008750A> IRQCR10_;
		static IRQCR10_ IRQCR10;
		typedef irqcrn_t<0x0008750B> IRQCR11_;
		static IRQCR11_ IRQCR11;
		typedef irqcrn_t<0x0008750C> IRQCR12_;
		static IRQCR12_ IRQCR12;
		typedef irqcrn_t<0x0008750D> IRQCR13_;
		static IRQCR13_ IRQCR13;
		typedef irqcrn_t<0x0008750E> IRQCR14_;
		static IRQCR14_ IRQCR14;
		typedef irqcrn_t<0x0008750F> IRQCR15_;
		static IRQCR15_ IRQCR15;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IRQ 端子デジタルフィルタ許可レジスタ 0（IRQFLTE0）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct irqflte0_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> FLTEN0;
			bit_rw_t<io_, bitpos::B1> FLTEN1;
			bit_rw_t<io_, bitpos::B2> FLTEN2;
			bit_rw_t<io_, bitpos::B3> FLTEN3;
			bit_rw_t<io_, bitpos::B4> FLTEN4;
			bit_rw_t<io_, bitpos::B5> FLTEN5;
			bit_rw_t<io_, bitpos::B6> FLTEN6;
			bit_rw_t<io_, bitpos::B7> FLTEN7;
		};
		typedef irqflte0_t<0x00087520> IRQFLTE0_;
		static IRQFLTE0_ IRQFLTE0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  IRQ 端子デジタルフィルタ許可レジスタ 1（IRQFLTE1）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct irqflte1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> FLTEN8;
			bit_rw_t<io_, bitpos::B1> FLTEN9;
			bit_rw_t<io_, bitpos::B2> FLTEN10;
			bit_rw_t<io_, bitpos::B3> FLTEN11;
			bit_rw_t<io_, bitpos::B4> FLTEN12;
			bit_rw_t<io_, bitpos::B5> FLTEN13;
			bit_rw_t<io_, bitpos::B6> FLTEN14;
			bit_rw_t<io_, bitpos::B7> FLTEN15;
		};
		typedef irqflte1_t<0x00087521> IRQFLTE1_;
		static IRQFLTE1_ IRQFLTE1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	IRQ 端子デジタルフィルタ設定レジスタ 0（IRQFLTC0）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct irqfltc0_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  2> FCLKSEL0;
			bits_rw_t<io_, bitpos::B2,  2> FCLKSEL1;
			bits_rw_t<io_, bitpos::B4,  2> FCLKSEL2;
			bits_rw_t<io_, bitpos::B6,  2> FCLKSEL3;
			bits_rw_t<io_, bitpos::B8,  2> FCLKSEL4;
			bits_rw_t<io_, bitpos::B10, 2> FCLKSEL5;
			bits_rw_t<io_, bitpos::B12, 2> FCLKSEL6;
			bits_rw_t<io_, bitpos::B14, 2> FCLKSEL7;
		};
		typedef irqfltc0_t<0x00087528> IRQFLTC0_;
		static IRQFLTC0_ IRQFLTC0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	IRQ 端子デジタルフィルタ設定レジスタ 1（IRQFLTC1）
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct irqfltc1_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  2> FCLKSEL8;
			bits_rw_t<io_, bitpos::B2,  2> FCLKSEL9;
			bits_rw_t<io_, bitpos::B4,  2> FCLKSEL10;
			bits_rw_t<io_, bitpos::B6,  2> FCLKSEL11;
			bits_rw_t<io_, bitpos::B8,  2> FCLKSEL12;
			bits_rw_t<io_, bitpos::B10, 2> FCLKSEL13;
			bits_rw_t<io_, bitpos::B12, 2> FCLKSEL14;
			bits_rw_t<io_, bitpos::B14, 2> FCLKSEL15;
		};
		typedef irqfltc1_t<0x0008752A> IRQFLTC1_;
		static IRQFLTC1_ IRQFLTC1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ノンマスカブル割り込みステータスレジスタ (NMISR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct nmisr_t : public ro8_t<base> {
			typedef ro8_t<base> io_;
			using io_::operator ();

			bit_ro_t<io_, bitpos::B0> NMIST;
			bit_ro_t<io_, bitpos::B1> OSTST;
			bit_ro_t<io_, bitpos::B2> WDTST;
			bit_ro_t<io_, bitpos::B3> IWDTST;
			bit_ro_t<io_, bitpos::B4> LVD1ST;
			bit_ro_t<io_, bitpos::B5> LVD2ST;
			bit_ro_t<io_, bitpos::B6> RAMST;
		};
		typedef nmisr_t<0x00087580> NMISR_;
		static NMISR_ NMISR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ノンマスカブル割り込み許可レジスタ (NMIER)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct nmier_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> NMIEN;
			bit_rw_t<io_, bitpos::B1> OSTEN;
			bit_rw_t<io_, bitpos::B2> WDTEN;
			bit_rw_t<io_, bitpos::B3> IWDTEN;
			bit_rw_t<io_, bitpos::B4> LVD1EN;
			bit_rw_t<io_, bitpos::B5> LVD2EN;
			bit_rw_t<io_, bitpos::B6> RAMEN;
		};
		typedef nmier_t<0x00087581> NMIER_;
		static NMIER_ NMIER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ノンマスカブル割り込みステータスクリアレジスタ (NMICLR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct nmiclr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> NMICLR;
			bit_rw_t<io_, bitpos::B1> OSTCLR;
			bit_rw_t<io_, bitpos::B2> WDTCLR;
			bit_rw_t<io_, bitpos::B3> IWDTCLR;
			bit_rw_t<io_, bitpos::B4> LVD1CLR;
			bit_rw_t<io_, bitpos::B5> LVD2CLR;
			bit_rw_t<io_, bitpos::B6> RAMCLR;
		};
		typedef nmiclr_t<0x00087582> NMICLR_;
		static NMICLR_ NMICLR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  NMI 端子割り込みコントロールレジスタ (NMICR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct nmicr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B3> NMIMD;
		};
		typedef nmicr_t<0x00087583> NMICR_;
		static NMICR_ NMICR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  NMI 端子デジタルフィルタ許可レジスタ (NMIFLTE)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct nmiflte_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> NFLTEN;
		};
		typedef nmiflte_t<0x00087590> NMIFLTE_;
		static NMIFLTE_ NMIFLTE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  NMI 端子デジタルフィルタ設定レジスタ (NMIFLTC)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct nmifltc_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> NFCLKSEL;
		};
		typedef nmifltc_t<0x00087594> NMIFLTC_;
		static NMIFLTC_ NMIFLTC;
	};
	template<class _> typename icu_base_t<_>::FIR_ icu_base_t<_>::FIR;
	template<class _> typename icu_base_t<_>::SWINTR_ icu_base_t<_>::SWINTR;

#if defined(RX_DMAC_)
	template<class _> typename icu_base_t<_>::DMRSR0_ icu_base_t<_>::DMRSR0;
	template<class _> typename icu_base_t<_>::DMRSR1_ icu_base_t<_>::DMRSR1;
	template<class _> typename icu_base_t<_>::DMRSR2_ icu_base_t<_>::DMRSR2;
	template<class _> typename icu_base_t<_>::DMRSR3_ icu_base_t<_>::DMRSR3;
	template<class _> typename icu_base_t<_>::DMRSR4_ icu_base_t<_>::DMRSR4;
	template<class _> typename icu_base_t<_>::DMRSR5_ icu_base_t<_>::DMRSR5;
	template<class _> typename icu_base_t<_>::DMRSR6_ icu_base_t<_>::DMRSR6;
	template<class _> typename icu_base_t<_>::DMRSR7_ icu_base_t<_>::DMRSR7;
#endif

	template<class _> typename icu_base_t<_>::IRQCR0_ icu_base_t<_>::IRQCR0;
	template<class _> typename icu_base_t<_>::IRQCR1_ icu_base_t<_>::IRQCR1;
	template<class _> typename icu_base_t<_>::IRQCR2_ icu_base_t<_>::IRQCR2;
	template<class _> typename icu_base_t<_>::IRQCR3_ icu_base_t<_>::IRQCR3;
	template<class _> typename icu_base_t<_>::IRQCR4_ icu_base_t<_>::IRQCR4;
	template<class _> typename icu_base_t<_>::IRQCR5_ icu_base_t<_>::IRQCR5;
	template<class _> typename icu_base_t<_>::IRQCR6_ icu_base_t<_>::IRQCR6;
	template<class _> typename icu_base_t<_>::IRQCR7_ icu_base_t<_>::IRQCR7;
	template<class _> typename icu_base_t<_>::IRQCR8_ icu_base_t<_>::IRQCR8;
	template<class _> typename icu_base_t<_>::IRQCR9_ icu_base_t<_>::IRQCR9;
	template<class _> typename icu_base_t<_>::IRQCR10_ icu_base_t<_>::IRQCR10;
	template<class _> typename icu_base_t<_>::IRQCR11_ icu_base_t<_>::IRQCR11;
	template<class _> typename icu_base_t<_>::IRQCR12_ icu_base_t<_>::IRQCR12;
	template<class _> typename icu_base_t<_>::IRQCR13_ icu_base_t<_>::IRQCR13;
	template<class _> typename icu_base_t<_>::IRQCR14_ icu_base_t<_>::IRQCR14;
	template<class _> typename icu_base_t<_>::IRQCR15_ icu_base_t<_>::IRQCR15;
	template<class _> typename icu_base_t<_>::IRQFLTE0_ icu_base_t<_>::IRQFLTE0;
	template<class _> typename icu_base_t<_>::IRQFLTE1_ icu_base_t<_>::IRQFLTE1;
	template<class _> typename icu_base_t<_>::IRQFLTC0_ icu_base_t<_>::IRQFLTC0;
	template<class _> typename icu_base_t<_>::IRQFLTC1_ icu_base_t<_>::IRQFLTC1;
	template<class _> typename icu_base_t<_>::NMISR_ icu_base_t<_>::NMISR;
	template<class _> typename icu_base_t<_>::NMIER_ icu_base_t<_>::NMIER;
	template<class _> typename icu_base_t<_>::NMICLR_ icu_base_t<_>::NMICLR;
	template<class _> typename icu_base_t<_>::NMICR_ icu_base_t<_>::NMICR;
	template<class _> typename icu_base_t<_>::NMIFLTE_ icu_base_t<_>::NMIFLTE;
	template<class _> typename icu_base_t<_>::NMIFLTC_ icu_base_t<_>::NMIFLTC;

	typedef icu_base_t<void> icu_base;
}
