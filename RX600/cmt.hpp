#pragma once
//=====================================================================//
/*!	@file
	@brief	RX24T, RX64M, RX65x, RX71M グループ・CMT 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2013, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"
#if defined(SIG_RX24T)
#include "RX24T/peripheral.hpp"
#include "RX24T/icu.hpp"
#elif defined(SIG_RX64M) | defined(SIG_RX65N) | defined(SIG_RX71M)
#include "RX600/peripheral.hpp"
#include "RX600/icu.hpp"
#elif
#  error "cmt.hpp requires SIG_XXXX to be defined"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CMT 定義基底クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct cmt_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CMCR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct cmcr_t : public rw16_t<base + 0x00> {
			typedef rw16_t<base + 0x00> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> CKS;
			bit_rw_t <io_, bitpos::B6>    CMIE;
		};
		static cmcr_t CMCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CMCNT レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw16_t<base + 0x02> CMCNT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CMCOR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw16_t<base + 0x04> CMCOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() noexcept { return per; }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CMT01 定義クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル
		@param[in]	ivec	割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR ivec>
	struct cmt01_t : cmt_t<base, per> {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CMSTR0 レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct cmstr0_t : public rw16_t<0x00088000> {
			typedef rw16_t<0x00088000> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> STR0;
			bit_rw_t<io_, bitpos::B1> STR1;
		};
		static cmstr0_t	CMSTR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  許可
			@param[in]	ena		不許可の場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true) noexcept
		{
			switch(per) {
			case peripheral::CMT0:
				CMSTR0.STR0 = ena;
				break;
			case peripheral::CMT1:
				CMSTR0.STR1 = ena;
				break;
			} 			
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR get_ivec() noexcept { return ivec; }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CMT01 定義クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル
		@param[in]	ivec	割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR_SELB ivec>
	struct cmt23_t : cmt_t<base, per> {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CMSTR1 レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct cmstr1_t : public rw16_t<0x00088010> {
			typedef rw16_t<0x00088010> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> STR2;
			bit_rw_t<io_, bitpos::B1> STR3;
		};
		static cmstr1_t	CMSTR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  許可
			@param[in]	ena		不許可の場合「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(bool ena = true) noexcept
		{
			switch(per) {
			case peripheral::CMT2:
				CMSTR1.STR2 = ena;
				break;
			case peripheral::CMT3:
				CMSTR1.STR3 = ena;
				break;
			} 			
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR_SELB get_ivec() noexcept { return ivec; }
	};

	typedef cmt01_t<0x00088002, peripheral::CMT0, ICU::VECTOR::CMI0> CMT0;
	typedef cmt01_t<0x00088008, peripheral::CMT1, ICU::VECTOR::CMI1> CMT1;
	typedef cmt23_t<0x00088012, peripheral::CMT2, ICU::VECTOR_SELB::CMI2> CMT2;
	typedef cmt23_t<0x00088018, peripheral::CMT3, ICU::VECTOR_SELB::CMI3> CMT3;
}
