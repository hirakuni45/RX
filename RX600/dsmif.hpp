#pragma once
//=========================================================================//
/*!	@file
	@brief	Delta-Sigma Modulator Interface / Δ-Σ モジュレータインタフェース @n
			・RX72M
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  DSMIFn class
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	ocdi	過電流検出割り込み
		@param[in]	sumei	合計電流エラー割り込み
		@param[in]	scdi	短絡検出割り込み
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per,
		ICU::GROUPBL2 ocdi, ICU::GROUPBL2 sumei, ICU::GROUPBL2 scdi>
	struct dsmifn_t {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto OCD_VEC  = ocdi;	///< 過電流検出割り込み
		static constexpr auto SUME_VEC = sumei;	///< 合計電流エラー割り込み
		static constexpr auto SCD_VEC  = scdi;	///< 短絡検出割り込み


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DSMIF 制御レジスタ (DSCR)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		static inline dscr_t<base + 0x00> DSCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DSMIF ステータスレジスタ (DSSR)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		static inline dssr_t<base + 0x04> DSSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  過電流検出下基準値レジスタ (OCLTR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x08> OCLTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  過電流検出上基準値レジスタ (OCHTR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x0C> OCHTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  短絡検出下基準値レジスタ (SCLTR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x10> SCLTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  短絡検出上基準値レジスタ (SCHTR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x14> SCHTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  合計電流エラー検出下基準値レジスタ (SUMLTR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x18> SUMLTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  合計電流エラー検出上基準値レジスタ (SUMHTR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x18> SUMHTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  チャネル x 電流データレジスタ (CDRx) (x = 0 ～ 2)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x20> CDR0;
		static inline rw32_t<base + 0x30> CDR1;
		static inline rw32_t<base + 0x40> CDR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  チャネル x 山電流データレジスタ (CCDRx) (x = 0 ～ 2)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x24> CCDR0;
		static inline rw32_t<base + 0x34> CCDR1;
		static inline rw32_t<base + 0x44> CCDR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  チャネル x 谷電流データレジスタ (TCDRx) (x = 0 ～ 2)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x28> TCDR0;
		static inline rw32_t<base + 0x38> TCDR1;
		static inline rw32_t<base + 0x48> TCDR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  チャネル x 過電流検出用データレジスタ (OCDRx) (x = 0 ～ 2)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x2C> OCDR0;
		static inline rw32_t<base + 0x3C> OCDR1;
		static inline rw32_t<base + 0x4C> OCDR2;
	};
	typedef dsmifn_t<0x000A'0700, peripheral::DSMIF0,
		ICU::GROUPBL2::OCDI0, ICU::GROUPBL2::SUMEI0, ICU::GROUPBL2::SCDI0> DSMIF0;
	typedef dsmifn_t<0x000A'0780, peripheral::DSMIF1,
		ICU::GROUPBL2::OCDI1, ICU::GROUPBL2::SUMEI1, ICU::GROUPBL2::SCDI1> DSMIF1;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  DSMIF 定義
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct dsmif_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DSMIF クロック制御レジスタ (DSCCR)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		static inline dsccr_t<0x000A'07E0> DSCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DSMIF チャネル制御レジスタ (DSCHR)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
		static inline dschr_t<0x000A'07E4> DSCHR;
	};
	typedef dsmif_t DSMIF;
}
