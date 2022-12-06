#pragma once
//=============================================================================//
/*!	@file
	@brief	RX グループ・ICU ベース定義（共通部分）
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2021, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX グループ割り込みコントローラ、ベースクラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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

			bits_rw_t<io_, bitpos::B0, 8> FVCT;
			bit_rw_t <io_, bitpos::B15>   FIEN;
		};
		typedef fir_t<0x0008'72F0> FIR_;
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

			bit_rw_t <io_, bitpos::B0>  SWINT;
		};
		typedef swintr_t<0x0008'72E0> SWINTR_;
		static SWINTR_ SWINTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ソフトウェア割り込み 2 起動レジスタ (SWINT2R)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct swint2r_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  SWINT2;
		};
		typedef swint2r_t<0x0008'72E1> SWINT2R_;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	DTC 転送要求許可レジスタ n (DTCERn)
			@param[in]	base	ベースアドレス
			@param[in]	VECT	割り込みベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base, typename VECT>
		struct dtcer_t : public rw8_index_t<base> {
			typedef rw8_index_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  DTCE;

			void set_index(VECT vector) noexcept
			{
				io_::index_ = static_cast<uint32_t>(vector);
			}

			dtcer_t& operator[] (VECT vector) noexcept
			{
				set_index(vector);
				return *this;
			}

		private:
			void operator = (const dtcer_t& t) { };  // 代入は禁止
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DMAC 起動要因選択レジスタ m（DMRSRm）（m = DMAC チャネル番号）
			@param[in]	base	ベースアドレス
			@param[in]	num		最大数
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base, uint32_t num>
		struct dmrsr_t : public rw8_index_t<base> {
			typedef rw8_index_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t index) noexcept
			{
				if(index < num) {
					io_::index_ = index;
				}
			}

			dmrsr_t& operator[] (uint32_t index) noexcept
			{
				set_index(index);
				return *this;
			}

		private:
			void operator = (const dmrsr_t& t) { };  // 代入は禁止
		};
		typedef dmrsr_t<0x0008'7400, 4> DMRSR4N_;
		typedef dmrsr_t<0x0008'7400, 8> DMRSR8N_;
		typedef rw8_t<0x0008'7400> DMRSR0_;
		typedef rw8_t<0x0008'7404> DMRSR1_;
		typedef rw8_t<0x0008'7408> DMRSR2_;
		typedef rw8_t<0x0008'740C> DMRSR3_;
		typedef rw8_t<0x0008'7410> DMRSR4_;
		typedef rw8_t<0x0008'7414> DMRSR5_;
		typedef rw8_t<0x0008'7418> DMRSR6_;
		typedef rw8_t<0x0008'741C> DMRSR7_;


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
		typedef nmisr_t<0x0008'7580> NMISR_;
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
		typedef nmier_t<0x0008'7581> NMIER_;
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
		typedef nmiclr_t<0x0008'7582> NMICLR_;
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
		typedef nmicr_t<0x0008'7583> NMICR_;
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
		typedef nmiflte_t<0x0008'7590> NMIFLTE_;
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
		typedef nmifltc_t<0x0008'7594> NMIFLTC_;
		static NMIFLTC_ NMIFLTC;
	};
	template<class _> typename icu_base_t<_>::FIR_ icu_base_t<_>::FIR;
	template<class _> typename icu_base_t<_>::SWINTR_ icu_base_t<_>::SWINTR;
	template<class _> typename icu_base_t<_>::NMISR_ icu_base_t<_>::NMISR;
	template<class _> typename icu_base_t<_>::NMIER_ icu_base_t<_>::NMIER;
	template<class _> typename icu_base_t<_>::NMICLR_ icu_base_t<_>::NMICLR;
	template<class _> typename icu_base_t<_>::NMICR_ icu_base_t<_>::NMICR;
	template<class _> typename icu_base_t<_>::NMIFLTE_ icu_base_t<_>::NMIFLTE;
	template<class _> typename icu_base_t<_>::NMIFLTC_ icu_base_t<_>::NMIFLTC;

	typedef icu_base_t<void> ICU_BASE;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX グループ割り込みコントローラ、IRQ8 クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class _>
	struct icu_irq8_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	割り込みレベル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class LEVEL : uint8_t {
			NONE,
			_1,		///< level-1
			_2,		///< level-2
			_3,		///< level-3
			_4,		///< level-4
			_5,		///< level-5
			_6,		///< level-6
			_7,		///< level-7
		};


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
		typedef irqcrn_t<0x0008'7500> IRQCR0_;
		typedef irqcrn_t<0x0008'7501> IRQCR1_;
		typedef irqcrn_t<0x0008'7502> IRQCR2_;
		typedef irqcrn_t<0x0008'7503> IRQCR3_;
		typedef irqcrn_t<0x0008'7504> IRQCR4_;
		typedef irqcrn_t<0x0008'7505> IRQCR5_;
		typedef irqcrn_t<0x0008'7506> IRQCR6_;
		typedef irqcrn_t<0x0008'7507> IRQCR7_;
		static IRQCR0_ IRQCR0;
		static IRQCR1_ IRQCR1;
		static IRQCR2_ IRQCR2;
		static IRQCR3_ IRQCR3;
		static IRQCR4_ IRQCR4;
		static IRQCR5_ IRQCR5;
		static IRQCR6_ IRQCR6;
		static IRQCR7_ IRQCR7;


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
		typedef irqflte0_t<0x0008'7510> IRQFLTE0_;
		static IRQFLTE0_ IRQFLTE0;


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
		typedef irqfltc0_t<0x0008'7514> IRQFLTC0_;
		static IRQFLTC0_ IRQFLTC0;
	};
	template<class _> typename icu_irq8_t<_>::IRQCR0_ icu_irq8_t<_>::IRQCR0;
	template<class _> typename icu_irq8_t<_>::IRQCR1_ icu_irq8_t<_>::IRQCR1;
	template<class _> typename icu_irq8_t<_>::IRQCR2_ icu_irq8_t<_>::IRQCR2;
	template<class _> typename icu_irq8_t<_>::IRQCR3_ icu_irq8_t<_>::IRQCR3;
	template<class _> typename icu_irq8_t<_>::IRQCR4_ icu_irq8_t<_>::IRQCR4;
	template<class _> typename icu_irq8_t<_>::IRQCR5_ icu_irq8_t<_>::IRQCR5;
	template<class _> typename icu_irq8_t<_>::IRQCR6_ icu_irq8_t<_>::IRQCR6;
	template<class _> typename icu_irq8_t<_>::IRQCR7_ icu_irq8_t<_>::IRQCR7;
	template<class _> typename icu_irq8_t<_>::IRQFLTE0_ icu_irq8_t<_>::IRQFLTE0;
	template<class _> typename icu_irq8_t<_>::IRQFLTC0_ icu_irq8_t<_>::IRQFLTC0;

	typedef icu_irq8_t<void> ICU_IRQ8;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RX グループ割り込みコントローラ、IRQ16 クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class _>
	struct icu_irq16_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	割り込みレベル型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class LEVEL : uint8_t {
			NONE,
			_1,		///< level-1
			_2,		///< level-2
			_3,		///< level-3
			_4,		///< level-4
			_5,		///< level-5
			_6,		///< level-6
			_7,		///< level-7
			_8,		///< level-8
			_9,		///< level-9
			_10,	///< level-10
			_11,	///< level-11
			_12,	///< level-12
			_13,	///< level-13
			_14,	///< level-14
			_15,	///< level-15
		};


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
		typedef irqcrn_t<0x0008'7500> IRQCR0_;
		typedef irqcrn_t<0x0008'7501> IRQCR1_;
		typedef irqcrn_t<0x0008'7502> IRQCR2_;
		typedef irqcrn_t<0x0008'7503> IRQCR3_;
		typedef irqcrn_t<0x0008'7504> IRQCR4_;
		typedef irqcrn_t<0x0008'7505> IRQCR5_;
		typedef irqcrn_t<0x0008'7506> IRQCR6_;
		typedef irqcrn_t<0x0008'7507> IRQCR7_;
		typedef irqcrn_t<0x0008'7508> IRQCR8_;
		typedef irqcrn_t<0x0008'7509> IRQCR9_;
		typedef irqcrn_t<0x0008'750A> IRQCR10_;
		typedef irqcrn_t<0x0008'750B> IRQCR11_;
		typedef irqcrn_t<0x0008'750C> IRQCR12_;
		typedef irqcrn_t<0x0008'750D> IRQCR13_;
		typedef irqcrn_t<0x0008'750E> IRQCR14_;
		typedef irqcrn_t<0x0008'750F> IRQCR15_;
		static IRQCR0_ IRQCR0;
		static IRQCR1_ IRQCR1;
		static IRQCR2_ IRQCR2;
		static IRQCR3_ IRQCR3;
		static IRQCR4_ IRQCR4;
		static IRQCR5_ IRQCR5;
		static IRQCR6_ IRQCR6;
		static IRQCR7_ IRQCR7;
		static IRQCR8_ IRQCR8;
		static IRQCR9_ IRQCR9;
		static IRQCR10_ IRQCR10;
		static IRQCR11_ IRQCR11;
		static IRQCR12_ IRQCR12;
		static IRQCR13_ IRQCR13;
		static IRQCR14_ IRQCR14;
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
		typedef irqflte0_t<0x0008'7520> IRQFLTE0_;
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
		typedef irqflte1_t<0x0008'7521> IRQFLTE1_;
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
		typedef irqfltc0_t<0x0008'7528> IRQFLTC0_;
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
		typedef irqfltc1_t<0x0008'752A> IRQFLTC1_;
		static IRQFLTC1_ IRQFLTC1;
	};
	template<class _> typename icu_irq16_t<_>::IRQCR0_ icu_irq16_t<_>::IRQCR0;
	template<class _> typename icu_irq16_t<_>::IRQCR1_ icu_irq16_t<_>::IRQCR1;
	template<class _> typename icu_irq16_t<_>::IRQCR2_ icu_irq16_t<_>::IRQCR2;
	template<class _> typename icu_irq16_t<_>::IRQCR3_ icu_irq16_t<_>::IRQCR3;
	template<class _> typename icu_irq16_t<_>::IRQCR4_ icu_irq16_t<_>::IRQCR4;
	template<class _> typename icu_irq16_t<_>::IRQCR5_ icu_irq16_t<_>::IRQCR5;
	template<class _> typename icu_irq16_t<_>::IRQCR6_ icu_irq16_t<_>::IRQCR6;
	template<class _> typename icu_irq16_t<_>::IRQCR7_ icu_irq16_t<_>::IRQCR7;
	template<class _> typename icu_irq16_t<_>::IRQCR8_ icu_irq16_t<_>::IRQCR8;
	template<class _> typename icu_irq16_t<_>::IRQCR9_ icu_irq16_t<_>::IRQCR9;
	template<class _> typename icu_irq16_t<_>::IRQCR10_ icu_irq16_t<_>::IRQCR10;
	template<class _> typename icu_irq16_t<_>::IRQCR11_ icu_irq16_t<_>::IRQCR11;
	template<class _> typename icu_irq16_t<_>::IRQCR12_ icu_irq16_t<_>::IRQCR12;
	template<class _> typename icu_irq16_t<_>::IRQCR13_ icu_irq16_t<_>::IRQCR13;
	template<class _> typename icu_irq16_t<_>::IRQCR14_ icu_irq16_t<_>::IRQCR14;
	template<class _> typename icu_irq16_t<_>::IRQCR15_ icu_irq16_t<_>::IRQCR15;
	template<class _> typename icu_irq16_t<_>::IRQFLTE0_ icu_irq16_t<_>::IRQFLTE0;
	template<class _> typename icu_irq16_t<_>::IRQFLTE1_ icu_irq16_t<_>::IRQFLTE1;
	template<class _> typename icu_irq16_t<_>::IRQFLTC0_ icu_irq16_t<_>::IRQFLTC0;
	template<class _> typename icu_irq16_t<_>::IRQFLTC1_ icu_irq16_t<_>::IRQFLTC1;

	typedef icu_irq16_t<void> ICU_IRQ16;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  グループ型割り込みクラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class _>
	struct icu_group_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み要求レジスタ
			@param[in]	base	ベースアドレス
			@param[in]	GVEC	グループベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base, typename GVEC>
		struct grp_t : public ro32_t<base> {
			typedef ro32_t<base> io_;
			using io_::operator ();

			bit_ro_t <io_, bitpos::B0>  IS0;
			bit_ro_t <io_, bitpos::B1>  IS1;
			bit_ro_t <io_, bitpos::B2>  IS2;
			bit_ro_t <io_, bitpos::B3>  IS3;
			bit_ro_t <io_, bitpos::B4>  IS4;
			bit_ro_t <io_, bitpos::B5>  IS5;
			bit_ro_t <io_, bitpos::B6>  IS6;
			bit_ro_t <io_, bitpos::B7>  IS7;
			bit_ro_t <io_, bitpos::B8>  IS8;
			bit_ro_t <io_, bitpos::B9>  IS9;
			bit_ro_t <io_, bitpos::B10> IS10;
			bit_ro_t <io_, bitpos::B11> IS11;
			bit_ro_t <io_, bitpos::B12> IS12;
			bit_ro_t <io_, bitpos::B13> IS13;
			bit_ro_t <io_, bitpos::B14> IS14;
			bit_ro_t <io_, bitpos::B15> IS15;
			bit_ro_t <io_, bitpos::B16> IS16;
			bit_ro_t <io_, bitpos::B17> IS17;
			bit_ro_t <io_, bitpos::B18> IS18;
			bit_ro_t <io_, bitpos::B19> IS19;
			bit_ro_t <io_, bitpos::B20> IS20;
			bit_ro_t <io_, bitpos::B21> IS21;
			bit_ro_t <io_, bitpos::B22> IS22;
			bit_ro_t <io_, bitpos::B23> IS23;
			bit_ro_t <io_, bitpos::B24> IS24;
			bit_ro_t <io_, bitpos::B25> IS25;
			bit_ro_t <io_, bitpos::B26> IS26;
			bit_ro_t <io_, bitpos::B27> IS27;
			bit_ro_t <io_, bitpos::B28> IS28;
			bit_ro_t <io_, bitpos::B29> IS29;
			bit_ro_t <io_, bitpos::B30> IS30;
			bit_ro_t <io_, bitpos::B31> IS31;

			bool get(GVEC gvec) noexcept
			{
				auto bit = 1 << static_cast<uint32_t>(gvec);
				return (rd32_(base) & bit) != 0;
			}
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込み要求許可レジスタ
			@param[in]	base	ベースアドレス
			@param[in]	GVEC	グループベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base, typename GVEC>
		struct gen_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  EN0;
			bit_rw_t<io_, bitpos::B1>  EN1;
			bit_rw_t<io_, bitpos::B2>  EN2;
			bit_rw_t<io_, bitpos::B3>  EN3;
			bit_rw_t<io_, bitpos::B4>  EN4;
			bit_rw_t<io_, bitpos::B5>  EN5;
			bit_rw_t<io_, bitpos::B6>  EN6;
			bit_rw_t<io_, bitpos::B7>  EN7;
			bit_rw_t<io_, bitpos::B8>  EN8;
			bit_rw_t<io_, bitpos::B9>  EN9;
			bit_rw_t<io_, bitpos::B10> EN10;
			bit_rw_t<io_, bitpos::B11> EN11;
			bit_rw_t<io_, bitpos::B12> EN12;
			bit_rw_t<io_, bitpos::B13> EN13;
			bit_rw_t<io_, bitpos::B14> EN14;
			bit_rw_t<io_, bitpos::B15> EN15;
			bit_rw_t<io_, bitpos::B16> EN16;
			bit_rw_t<io_, bitpos::B17> EN17;
			bit_rw_t<io_, bitpos::B18> EN18;
			bit_rw_t<io_, bitpos::B19> EN19;
			bit_rw_t<io_, bitpos::B20> EN20;
			bit_rw_t<io_, bitpos::B21> EN21;
			bit_rw_t<io_, bitpos::B22> EN22;
			bit_rw_t<io_, bitpos::B23> EN23;
			bit_rw_t<io_, bitpos::B24> EN24;
			bit_rw_t<io_, bitpos::B25> EN25;
			bit_rw_t<io_, bitpos::B26> EN26;
			bit_rw_t<io_, bitpos::B27> EN27;
			bit_rw_t<io_, bitpos::B28> EN28;
			bit_rw_t<io_, bitpos::B29> EN29;
			bit_rw_t<io_, bitpos::B30> EN30;
			bit_rw_t<io_, bitpos::B31> EN31;

			bool get(GVEC gvec) noexcept
			{
				auto bit = 1 << static_cast<uint32_t>(gvec);
				return (rd32_(base) & bit) != 0;
			}

			void set(GVEC gvec, bool ena = true) noexcept
			{
				auto bit = 1 << static_cast<uint32_t>(gvec);
				if(ena) {
					wr32_(base, rd32_(base) | bit);
				} else {
					wr32_(base, rd32_(base) & ~bit);
				}
			}
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グループ割り込みクリアレジスタ
			@param[in]	base	ベースアドレス
			@param[in]	GVEC	グループベクター型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base, typename GVEC>
		struct gcr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  CLR0;
			bit_rw_t <io_, bitpos::B1>  CLR1;
			bit_rw_t <io_, bitpos::B2>  CLR2;
			bit_rw_t <io_, bitpos::B3>  CLR3;
			bit_rw_t <io_, bitpos::B4>  CLR4;
			bit_rw_t <io_, bitpos::B5>  CLR5;
			bit_rw_t <io_, bitpos::B6>  CLR6;
			bit_rw_t <io_, bitpos::B7>  CLR7;
			bit_rw_t <io_, bitpos::B8>  CLR8;
			bit_rw_t <io_, bitpos::B9>  CLR9;
			bit_rw_t <io_, bitpos::B10> CLR10;
			bit_rw_t <io_, bitpos::B11> CLR11;
			bit_rw_t <io_, bitpos::B12> CLR12;
			bit_rw_t <io_, bitpos::B13> CLR13;
			bit_rw_t <io_, bitpos::B14> CLR14;
			bit_rw_t <io_, bitpos::B15> CLR15;
			bit_rw_t <io_, bitpos::B16> CLR16;
			bit_rw_t <io_, bitpos::B17> CLR17;
			bit_rw_t <io_, bitpos::B18> CLR18;
			bit_rw_t <io_, bitpos::B19> CLR19;
			bit_rw_t <io_, bitpos::B20> CLR20;
			bit_rw_t <io_, bitpos::B21> CLR21;
			bit_rw_t <io_, bitpos::B22> CLR22;
			bit_rw_t <io_, bitpos::B23> CLR23;
			bit_rw_t <io_, bitpos::B24> CLR24;
			bit_rw_t <io_, bitpos::B25> CLR25;
			bit_rw_t <io_, bitpos::B26> CLR26;
			bit_rw_t <io_, bitpos::B27> CLR27;
			bit_rw_t <io_, bitpos::B28> CLR28;
			bit_rw_t <io_, bitpos::B29> CLR29;
			bit_rw_t <io_, bitpos::B30> CLR30;
			bit_rw_t <io_, bitpos::B31> CLR31;

			bool get(GVEC gvec) noexcept
			{
				auto bit = 1 << static_cast<uint32_t>(gvec);
				return (rd32_(base) & bit) != 0;
			}

			void set(GVEC gvec, bool ena = true) noexcept
			{
				auto bit = 1 << static_cast<uint32_t>(gvec);
				if(ena) {
					wr32_(base, rd32_(base) | bit);
				} else {
					wr32_(base, rd32_(base) & ~bit);
				}
			}
		};
	};

	typedef icu_group_t<void> ICU_GROUP;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  選択型割り込みクラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class _>
	struct icu_select_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込み [AB] 要求レジスタ k (PI[AB]Rk) (k = 0h ～ Bh)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pixr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  PIR0;
			bit_rw_t <io_, bitpos::B1>  PIR1;
			bit_rw_t <io_, bitpos::B2>  PIR2;
			bit_rw_t <io_, bitpos::B3>  PIR3;
			bit_rw_t <io_, bitpos::B4>  PIR4;
			bit_rw_t <io_, bitpos::B5>  PIR5;
			bit_rw_t <io_, bitpos::B6>  PIR6;
			bit_rw_t <io_, bitpos::B7>  PIR7;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込み B 要求レジスタ k（PIBRk）（k = 0h ～ Bh）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pixr_t<0x0008'7700> PIBR0_;
		typedef pixr_t<0x0008'7701> PIBR1_;
		typedef pixr_t<0x0008'7702> PIBR2_;
		typedef pixr_t<0x0008'7703> PIBR3_;
		typedef pixr_t<0x0008'7704> PIBR4_;
		typedef pixr_t<0x0008'7705> PIBR5_;
		typedef pixr_t<0x0008'7706> PIBR6_;
		typedef pixr_t<0x0008'7707> PIBR7_;
		typedef pixr_t<0x0008'7708> PIBR8_;
		typedef pixr_t<0x0008'7709> PIBR9_;
		typedef pixr_t<0x0008'770A> PIBRA_;
		typedef pixr_t<0x0008'770B> PIBRB_;
		static PIBR0_ PIBR0;
		static PIBR1_ PIBR1;
		static PIBR2_ PIBR2;
		static PIBR3_ PIBR3;
		static PIBR4_ PIBR4;
		static PIBR5_ PIBR5;
		static PIBR6_ PIBR6;
		static PIBR7_ PIBR7;
		static PIBR8_ PIBR8;
		static PIBR9_ PIBR9;
		static PIBRA_ PIBRA;
		static PIBRB_ PIBRB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込み A 要求レジスタ k（PIARk）（k = 0h ～ 12h）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef pixr_t<0x0008'7900> PIAR0_;
		typedef pixr_t<0x0008'7901> PIAR1_;
		typedef pixr_t<0x0008'7902> PIAR2_;
		typedef pixr_t<0x0008'7903> PIAR3_;
		typedef pixr_t<0x0008'7904> PIAR4_;
		typedef pixr_t<0x0008'7905> PIAR5_;
		typedef pixr_t<0x0008'7906> PIAR6_;
		typedef pixr_t<0x0008'7907> PIAR7_;
		typedef pixr_t<0x0008'7908> PIAR8_;
		typedef pixr_t<0x0008'7909> PIAR9_;
		typedef pixr_t<0x0008'790A> PIARA_;
		typedef pixr_t<0x0008'790B> PIARB_;
		typedef pixr_t<0x0008'790C> PIARC_;
		typedef pixr_t<0x0008'790D> PIARD_;
		typedef pixr_t<0x0008'790E> PIARE_;
		typedef pixr_t<0x0008'790F> PIARF_;
		typedef pixr_t<0x0008'7910> PIAR10_;
		typedef pixr_t<0x0008'7911> PIAR11_;
		typedef pixr_t<0x0008'7912> PIAR12_;
		static PIAR0_ PIAR0;
		static PIAR1_ PIAR1;
		static PIAR2_ PIAR2;
		static PIAR3_ PIAR3;
		static PIAR4_ PIAR4;
		static PIAR5_ PIAR5;
		static PIAR6_ PIAR6;
		static PIAR7_ PIAR7;
		static PIAR8_ PIAR8;
		static PIAR9_ PIAR9;
		static PIARA_ PIARA;
		static PIARB_ PIARB;
		static PIARC_ PIARC;
		static PIARD_ PIARD;
		static PIARE_ PIARE;
		static PIARF_ PIARF;
		static PIAR10_ PIAR10;
		static PIAR11_ PIAR11;
		static PIAR12_ PIAR12;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMAC 起動割り込み選択レジスタ (SELEXDR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct selexdr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  SELEXD0;
			bit_rw_t <io_, bitpos::B1>  SELEXD1;
		};
		typedef selexdr_t<0x0008'7A01> SELEXDR_;
		static SELEXDR_ SELEXDR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  選択型割り込み要因選択レジスタ書き込み保護レジスタ (SLIPRCR)
			@param[in]	base	ベースアドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct sliprcr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  WPRC;
		};
		typedef sliprcr_t<0x0008'7A00> SLIPRCR_;
		static SLIPRCR_ SLIPRCR;
	};
	template<class _> typename icu_select_t<_>::PIBR0_ icu_select_t<_>::PIBR0;
	template<class _> typename icu_select_t<_>::PIBR1_ icu_select_t<_>::PIBR1;
	template<class _> typename icu_select_t<_>::PIBR2_ icu_select_t<_>::PIBR2;
	template<class _> typename icu_select_t<_>::PIBR3_ icu_select_t<_>::PIBR3;
	template<class _> typename icu_select_t<_>::PIBR4_ icu_select_t<_>::PIBR4;
	template<class _> typename icu_select_t<_>::PIBR5_ icu_select_t<_>::PIBR5;
	template<class _> typename icu_select_t<_>::PIBR6_ icu_select_t<_>::PIBR6;
	template<class _> typename icu_select_t<_>::PIBR7_ icu_select_t<_>::PIBR7;
	template<class _> typename icu_select_t<_>::PIBR8_ icu_select_t<_>::PIBR8;
	template<class _> typename icu_select_t<_>::PIBR9_ icu_select_t<_>::PIBR9;
	template<class _> typename icu_select_t<_>::PIBRA_ icu_select_t<_>::PIBRA;
	template<class _> typename icu_select_t<_>::PIBRB_ icu_select_t<_>::PIBRB;
	template<class _> typename icu_select_t<_>::PIAR0_ icu_select_t<_>::PIAR0;
	template<class _> typename icu_select_t<_>::PIAR1_ icu_select_t<_>::PIAR1;
	template<class _> typename icu_select_t<_>::PIAR2_ icu_select_t<_>::PIAR2;
	template<class _> typename icu_select_t<_>::PIAR3_ icu_select_t<_>::PIAR3;
	template<class _> typename icu_select_t<_>::PIAR4_ icu_select_t<_>::PIAR4;
	template<class _> typename icu_select_t<_>::PIAR5_ icu_select_t<_>::PIAR5;
	template<class _> typename icu_select_t<_>::PIAR6_ icu_select_t<_>::PIAR6;
	template<class _> typename icu_select_t<_>::PIAR7_ icu_select_t<_>::PIAR7;
	template<class _> typename icu_select_t<_>::PIAR8_ icu_select_t<_>::PIAR8;
	template<class _> typename icu_select_t<_>::PIAR9_ icu_select_t<_>::PIAR9;
	template<class _> typename icu_select_t<_>::PIARA_ icu_select_t<_>::PIARA;
	template<class _> typename icu_select_t<_>::PIARB_ icu_select_t<_>::PIARB;
	template<class _> typename icu_select_t<_>::PIARC_ icu_select_t<_>::PIARC;
	template<class _> typename icu_select_t<_>::PIARD_ icu_select_t<_>::PIARD;
	template<class _> typename icu_select_t<_>::PIARE_ icu_select_t<_>::PIARE;
	template<class _> typename icu_select_t<_>::PIARF_ icu_select_t<_>::PIARF;
	template<class _> typename icu_select_t<_>::PIAR10_ icu_select_t<_>::PIAR10;
	template<class _> typename icu_select_t<_>::PIAR11_ icu_select_t<_>::PIAR11;
	template<class _> typename icu_select_t<_>::PIAR12_ icu_select_t<_>::PIAR12;
	template<class _> typename icu_select_t<_>::SELEXDR_ icu_select_t<_>::SELEXDR;
	template<class _> typename icu_select_t<_>::SLIPRCR_ icu_select_t<_>::SLIPRCR;

	typedef icu_select_t<void> ICU_SELECT;
}
