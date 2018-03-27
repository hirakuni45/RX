#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ DRW2D 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  DRW2D 定義
		@param[in]	base	ベース・アドレス
		@param[in]	t		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral t>
	struct drw2d_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ジオメトリコントロールレジスタ (CONTROL)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct control_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   LIM1EN;
			bit_rw_t<io_, bitpos::B1>   LIM2EN;
			bit_rw_t<io_, bitpos::B2>   LIM3EN;
			bit_rw_t<io_, bitpos::B3>   LIM4EN;
			bit_rw_t<io_, bitpos::B4>   LIM5EN;
			bit_rw_t<io_, bitpos::B5>   LIM6EN;
			bit_rw_t<io_, bitpos::B6>   QUAD1EN;
			bit_rw_t<io_, bitpos::B7>   QUAD2EN;
			bit_rw_t<io_, bitpos::B8>   QUAD3EN;
			bit_rw_t<io_, bitpos::B9>   LIM1TH;
			bit_rw_t<io_, bitpos::B10>  LIM2TH;
			bit_rw_t<io_, bitpos::B11>  LIM3TH;
			bit_rw_t<io_, bitpos::B12>  LIM4TH;
			bit_rw_t<io_, bitpos::B13>  LIM5TH;
			bit_rw_t<io_, bitpos::B14>  LIM6TH;
			bit_rw_t<io_, bitpos::B15>  BAND1EN;
			bit_rw_t<io_, bitpos::B16>  BAND2EN;
			bit_rw_t<io_, bitpos::B17>  UNION12;
			bit_rw_t<io_, bitpos::B18>  UNION34;
		};
		static control_t<base + 0x00> CONTROL;






		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return t; }
	};

	typedef drw2d_t<0x000E3000, peripheral::DRW2D> DRW2D;
}
