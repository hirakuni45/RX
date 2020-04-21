#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T グループ・DOC 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  データ演算回路（DOC）
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct doc_t {

		//-----------------------------------------------------------------//
		/*!
			@brief  DOC コントロールレジスタ（DOCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct docr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  OMS;
			bit_rw_t <io_, bitpos::B2>     DCSEL;
			bit_rw_t <io_, bitpos::B4>     DOPCIE;
			bit_rw_t <io_, bitpos::B5>     DOPCF;
			bit_rw_t <io_, bitpos::B6>     DOPCFCL;
		};
		typedef docr_t<base + 0x00> DOCR_;
		static  DOCR_ DOCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  DOC データインプットレジスタ（DODIR）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x02> DODIR_;
		static  DODIR_ DODIR;


		//-----------------------------------------------------------------//
		/*!
			@brief  DOC データセッティングレジスタ（DODSR）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<base + 0x04> DODSR_;
		static  DODSR_ DODSR;

	};
	template <uint32_t base, peripheral per>
		typename doc_t<base, per>::DOCR_ doc_t<base, per>::DOCR;
	template <uint32_t base, peripheral per>
		typename doc_t<base, per>::DODIR_ doc_t<base, per>::DODIR;
	template <uint32_t base, peripheral per>
		typename doc_t<base, per>::DODSR_ doc_t<base, per>::DODSR;


#if defined(SIG_RX24T)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  データ演算回路（DOC）
		@param[in]	base	ベース・アドレス
		@param[in]	vec		割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR vec>
	struct doc_norm_t : public doc_t<base, per> {

		static const auto I_VEC = vec;	///< 割り込みベクター

	};
	typedef doc_norm_t<0x0008B080, peripheral::DOC, ICU::VECTOR::DOPCF> DOC;
#endif

#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  データ演算回路（DOC）
		@param[in]	base	ベース・アドレス
		@param[in]	vec		割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR_BL0 vec>
	struct doc_gbl0_t : public doc_t<base, per> {

		static const auto I_VEC = vec;	///< 割り込みベクター

	};
	typedef doc_gbl0_t<0x0008B080, peripheral::DOC, ICU::VECTOR_BL0::DOPCI> DOC;
#endif
}
