#pragma once
//=====================================================================//
/*!	@file
	@brief	RX700 グループ Δ-Σモジュレータインタフェース定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  DSMIF 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	ocdi	過電流検出割り込み
		@param[in]	sumei	合計電流エラー割り込み
		@param[in]	scdi	短絡検出割り込み
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per,
		ICU::VECTOR_BL2 ocdi, ICU::VECTOR_BL2 sumei, ICU::VECTOR_BL2 scdi>
	struct dsmif_t {

		static const auto PERIPHERAL = per;	///< ペリフェラル型
		static const auto OCD_VEC  = ocdi;	///< 過電流検出割り込み
		static const auto SUME_VEC = sumei;	///< 合計電流エラー割り込み
		static const auto SCD_VEC  = scdi;	///< 短絡検出割り込み


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DSMIF 制御レジスタ (DSCR)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dscr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      FEN;
			bit_rw_t <io_, bitpos::B1>      CKDIR;
			bits_rw_t<io_, bitpos::B4,  4>  CKDIV;
			bits_rw_t<io_, bitpos::B8,  2>  CMSINC;

			bits_rw_t<io_, bitpos::B12, 3>  CMDEC;

			bits_rw_t<io_, bitpos::B16, 4>  CMSH;
			bits_rw_t<io_, bitpos::B20, 2>  OCSINC;

			bits_rw_t<io_, bitpos::B24, 3>  OCDEC;

			bits_rw_t<io_, bitpos::B28, 4>  OCSH;
		};
		typedef dscr_t<base + 0x00> DSCR_;
		static  DSCR_ DSCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DSMIF ステータスレジスタ (DSSR)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dssr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      OCF0;
			bit_rw_t <io_, bitpos::B1>      OCF1;
			bit_rw_t <io_, bitpos::B2>      OCF2;

			bit_rw_t <io_, bitpos::B4>      SCF0;
			bit_rw_t <io_, bitpos::B5>      SCF1;
			bit_rw_t <io_, bitpos::B6>      SCF2;

			bit_rw_t <io_, bitpos::B8>      SUMERR;
		};
		typedef dssr_t<base + 0x04> DSSR_;
		static  DSSR_ DSSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  過電流検出下基準値レジスタ (OCLTR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x08> OCLTR_;
		static  OCLTR_ OCLTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  過電流検出上基準値レジスタ (OCHTR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x0C> OCHTR_;
		static  OCHTR_ OCHTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  短絡検出下基準値レジスタ (SCLTR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x10> SCLTR_;
		static  SCLTR_ SCLTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  短絡検出上基準値レジスタ (SCHTR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x14> SCHTR_;
		static  SCHTR_ SCHTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  合計電流エラー検出下基準値レジスタ (SUMLTR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x18> SUMLTR_;
		static  SUMLTR_ SUMLTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  合計電流エラー検出上基準値レジスタ (SUMHTR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x18> SUMHTR_;
		static  SUMHTR_ SUMHTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  チャネル x 電流データレジスタ (CDRx) (x = 0 ～ 2)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x20> CDR0_;
		static  CDR0_ CDR0;
		typedef rw32_t<base + 0x30> CDR1_;
		static  CDR1_ CDR1;
		typedef rw32_t<base + 0x40> CDR2_;
		static  CDR2_ CDR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  チャネル x 山電流データレジスタ (CCDRx) (x = 0 ～ 2)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x24> CCDR0_;
		static  CCDR0_ CCDR0;
		typedef rw32_t<base + 0x34> CCDR1_;
		static  CCDR1_ CCDR1;
		typedef rw32_t<base + 0x44> CCDR2_;
		static  CCDR2_ CCDR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  チャネル x 谷電流データレジスタ (TCDRx) (x = 0 ～ 2)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x28> TCDR0_;
		static  TCDR0_ TCDR0;
		typedef rw32_t<base + 0x38> TCDR1_;
		static  TCDR1_ TCDR1;
		typedef rw32_t<base + 0x48> TCDR2_;
		static  TCDR2_ TCDR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  チャネル x 過電流検出用データレジスタ (OCDRx) (x = 0 ～ 2)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x2C> OCDR0_;
		static  OCDR0_ OCDR0;
		typedef rw32_t<base + 0x3C> OCDR1_;
		static  OCDR1_ OCDR1;
		typedef rw32_t<base + 0x4C> OCDR2_;
		static  OCDR2_ OCDR2;
	};
	typedef dsmif_t<0x000A0700, peripheral::DSMIF0,
		ICU::VECTOR_BL2::OCDI0, ICU::VECTOR_BL2::SUMEI0, ICU::VECTOR_BL2::SCDI0> DSMIF0;
	typedef dsmif_t<0x000A0780, peripheral::DSMIF1,
		ICU::VECTOR_BL2::OCDI1, ICU::VECTOR_BL2::SUMEI1, ICU::VECTOR_BL2::SCDI1> DSMIF1;


	template <uint32_t base, peripheral per, ICU::VECTOR_BL2 ocdi, ICU::VECTOR_BL2 sumei, ICU::VECTOR_BL2 scdi> typename dsmif_t<base, per, ocdi, sumei, scdi>::DSCR_ dsmif_t<base, per, ocdi, sumei, scdi>::DSCR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL2 ocdi, ICU::VECTOR_BL2 sumei, ICU::VECTOR_BL2 scdi> typename dsmif_t<base, per, ocdi, sumei, scdi>::DSSR_ dsmif_t<base, per, ocdi, sumei, scdi>::DSSR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL2 ocdi, ICU::VECTOR_BL2 sumei, ICU::VECTOR_BL2 scdi> typename dsmif_t<base, per, ocdi, sumei, scdi>::OCLTR_ dsmif_t<base, per, ocdi, sumei, scdi>::OCLTR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL2 ocdi, ICU::VECTOR_BL2 sumei, ICU::VECTOR_BL2 scdi> typename dsmif_t<base, per, ocdi, sumei, scdi>::OCHTR_ dsmif_t<base, per, ocdi, sumei, scdi>::OCHTR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL2 ocdi, ICU::VECTOR_BL2 sumei, ICU::VECTOR_BL2 scdi> typename dsmif_t<base, per, ocdi, sumei, scdi>::SCLTR_ dsmif_t<base, per, ocdi, sumei, scdi>::SCLTR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL2 ocdi, ICU::VECTOR_BL2 sumei, ICU::VECTOR_BL2 scdi> typename dsmif_t<base, per, ocdi, sumei, scdi>::SCHTR_ dsmif_t<base, per, ocdi, sumei, scdi>::SCHTR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL2 ocdi, ICU::VECTOR_BL2 sumei, ICU::VECTOR_BL2 scdi> typename dsmif_t<base, per, ocdi, sumei, scdi>::SUMLTR_ dsmif_t<base, per, ocdi, sumei, scdi>::SUMLTR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL2 ocdi, ICU::VECTOR_BL2 sumei, ICU::VECTOR_BL2 scdi> typename dsmif_t<base, per, ocdi, sumei, scdi>::SUMHTR_ dsmif_t<base, per, ocdi, sumei, scdi>::SUMHTR;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL2 ocdi, ICU::VECTOR_BL2 sumei, ICU::VECTOR_BL2 scdi> typename dsmif_t<base, per, ocdi, sumei, scdi>::CDR0_ dsmif_t<base, per, ocdi, sumei, scdi>::CDR0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL2 ocdi, ICU::VECTOR_BL2 sumei, ICU::VECTOR_BL2 scdi> typename dsmif_t<base, per, ocdi, sumei, scdi>::CDR1_ dsmif_t<base, per, ocdi, sumei, scdi>::CDR1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL2 ocdi, ICU::VECTOR_BL2 sumei, ICU::VECTOR_BL2 scdi> typename dsmif_t<base, per, ocdi, sumei, scdi>::CDR2_ dsmif_t<base, per, ocdi, sumei, scdi>::CDR2;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL2 ocdi, ICU::VECTOR_BL2 sumei, ICU::VECTOR_BL2 scdi> typename dsmif_t<base, per, ocdi, sumei, scdi>::CCDR0_ dsmif_t<base, per, ocdi, sumei, scdi>::CCDR0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL2 ocdi, ICU::VECTOR_BL2 sumei, ICU::VECTOR_BL2 scdi> typename dsmif_t<base, per, ocdi, sumei, scdi>::CCDR1_ dsmif_t<base, per, ocdi, sumei, scdi>::CCDR1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL2 ocdi, ICU::VECTOR_BL2 sumei, ICU::VECTOR_BL2 scdi> typename dsmif_t<base, per, ocdi, sumei, scdi>::CCDR2_ dsmif_t<base, per, ocdi, sumei, scdi>::CCDR2;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL2 ocdi, ICU::VECTOR_BL2 sumei, ICU::VECTOR_BL2 scdi> typename dsmif_t<base, per, ocdi, sumei, scdi>::TCDR0_ dsmif_t<base, per, ocdi, sumei, scdi>::TCDR0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL2 ocdi, ICU::VECTOR_BL2 sumei, ICU::VECTOR_BL2 scdi> typename dsmif_t<base, per, ocdi, sumei, scdi>::TCDR1_ dsmif_t<base, per, ocdi, sumei, scdi>::TCDR1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL2 ocdi, ICU::VECTOR_BL2 sumei, ICU::VECTOR_BL2 scdi> typename dsmif_t<base, per, ocdi, sumei, scdi>::TCDR2_ dsmif_t<base, per, ocdi, sumei, scdi>::TCDR2;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL2 ocdi, ICU::VECTOR_BL2 sumei, ICU::VECTOR_BL2 scdi> typename dsmif_t<base, per, ocdi, sumei, scdi>::OCDR0_ dsmif_t<base, per, ocdi, sumei, scdi>::OCDR0;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL2 ocdi, ICU::VECTOR_BL2 sumei, ICU::VECTOR_BL2 scdi> typename dsmif_t<base, per, ocdi, sumei, scdi>::OCDR1_ dsmif_t<base, per, ocdi, sumei, scdi>::OCDR1;
	template <uint32_t base, peripheral per, ICU::VECTOR_BL2 ocdi, ICU::VECTOR_BL2 sumei, ICU::VECTOR_BL2 scdi> typename dsmif_t<base, per, ocdi, sumei, scdi>::OCDR2_ dsmif_t<base, per, ocdi, sumei, scdi>::OCDR2;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  DSMIF 定義
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class _>
	struct dsmif_ {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DSMIF クロック制御レジスタ (DSCCR)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dsccr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  EDGE0;
			bit_rw_t<io_, bitpos::B1>  EDGE1;
			bit_rw_t<io_, bitpos::B2>  EDGE2;
			bit_rw_t<io_, bitpos::B3>  EDGE3;
			bit_rw_t<io_, bitpos::B4>  EDGE4;
			bit_rw_t<io_, bitpos::B5>  EDGE5;
		};
		typedef dsccr_t<0x000A07E0> DSCCR_;
		static  DSCCR_ DSCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DSMIF チャネル制御レジスタ (DSCHR)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dschr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  EDGE0;
			bit_rw_t<io_, bitpos::B1>  EDGE1;
			bit_rw_t<io_, bitpos::B2>  EDGE2;
			bit_rw_t<io_, bitpos::B3>  EDGE3;
			bit_rw_t<io_, bitpos::B4>  EDGE4;
			bit_rw_t<io_, bitpos::B5>  EDGE5;
		};
		typedef dschr_t<0x000A07E4> DSCHR_;
		static  DSCHR_ DSCHR;
	};
	typedef dsmif_<void> DSMIF;


	template <class _> typename dsmif_<_>::DSCCR_ dsmif_<_>::DSCCR;
	template <class _> typename dsmif_<_>::DSCHR_ dsmif_<_>::DSCHR;
}
