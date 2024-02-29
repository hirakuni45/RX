#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600/RX700 グループ・DOC 定義 @n
			RX140 @n
			RX220 @n
			RX231 @n
			RX24T @n
			RX63T @n
			RX64M/RX71M @n
			RX65N/RX651 @n
			RX66N @n
			RX66T/RX72T @n
			RX72N/RX72M
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  データ演算回路（DOC）
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
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
		static inline docr_t<base + 0x00> DOCR;


		//-----------------------------------------------------------------//
		/*!
			@brief  DOC データインプットレジスタ（DODIR）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x02> DODIR;


		//-----------------------------------------------------------------//
		/*!
			@brief  DOC データセッティングレジスタ（DODSR）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x04> DODSR;
	};

#if defined(SIG_RX140) || defined(SIG_RX220) || defined(SIG_RX231) || defined(SIG_RX24T) || defined(SIG_RX63T) || defined(SIG_RX63T_S)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  データ演算回路（DOC）
		@param[in]	base	ベース・アドレス
		@param[in]	dopci	データ演算回路割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, ICU::VECTOR dopci>
	struct doc_norm_t : public doc_t<base> {

		static constexpr auto PERIPHERAL = peripheral::DOC;	///< ペリフェラル型
		static constexpr auto DOPCI = dopci;				///< データ演算回路割り込みベクター
	};
	typedef doc_norm_t<0x0008'B080, ICU::VECTOR::DOPCF> DOC;
#elif defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX651) || defined(SIG_RX66N) || defined(SIG_RX72N) || defined(SIG_RX72M) || defined(SIG_RX66T) || defined(SIG_RX72T)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  データ演算回路（DOC）
		@param[in]	base	ベース・アドレス
		@param[in]	dopci	データ演算回路割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, ICU::GROUPBL0 dopci>
	struct doc_gbl0_t : public doc_t<base> {

		static constexpr auto PERIPHERAL = peripheral::DOC;	///< ペリフェラル型
		static constexpr auto DOPCI = dopci;				///< データ演算回路割り込みベクター
	};
	typedef doc_gbl0_t<0x0008'B080, ICU::GROUPBL0::DOPCI> DOC;
#endif
}
