#pragma once
//=====================================================================//
/*!	@file
	@brief	RX700 グループ Δ-Σモジュレータインタフェース定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
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
		static dscr_t<base + 0x00> DSCR;
	};

	typedef dsmif_t<0x000A0700, peripheral::PMGI0,
		ICU::VECTOR_BL2::OCDI0, ICU::VECTOR_BL2::SUMEI0, ICU::VECTOR_BL2::SCDI0> DSMIF0;
	typedef dsmif_t<0x000A0780, peripheral::PMGI1,
		ICU::VECTOR_BL2::OCDI1, ICU::VECTOR_BL2::SUMEI1, ICU::VECTOR_BL2::SCDI1> DSMIF1;
}
