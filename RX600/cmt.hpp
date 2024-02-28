#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600/RX700 グループ CMT 定義 @n
			RX140 (CMT0/CMT1 のみ) @n
			RX220 @n
			RX231 @n
			RX24T @n
			RX26T @n
			RX62N/RX621 @n
			RX63N/RX631 @n
			RX63T @n
			RX64M/RX71M @n
			RX65N/RX651 @n
			RX66N @n
			RX671 @n
			RX66T/RX72T @n
			RX72N/RX72M
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2013, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CMT 定義基底クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct cmt_core_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CMSTR0 レジスタ
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct cmstr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> STR0;
			bit_rw_t<io_, bitpos::B1> STR1;
		};
		static inline cmstr0_t<0x0008'8000> CMSTR0;

#ifndef SIG_RX140
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CMSTR1 レジスタ
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct cmstr1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> STR2;
			bit_rw_t<io_, bitpos::B1> STR3;
		};
		static inline cmstr1_t<0x0008'8010> CMSTR1;
#endif

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CMCR レジスタ
			@param[in]	ofs		レジスタ・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct cmcr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> CKS;
			bit_rw_t <io_, bitpos::B6>    CMIE;
		};
		static inline cmcr_t<base + 0x00> CMCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CMCNT レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw16_t<base + 0x02> CMCNT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CMCOR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw16_t<base + 0x04> CMCOR;


		//-----------------------------------------------------------------//
		/*!
			@brief  許可・不許可
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
#ifndef SIG_RX140
			case peripheral::CMT2:
				CMSTR1.STR2 = ena;
				break;
			case peripheral::CMT3:
				CMSTR1.STR3 = ena;
				break;
#endif
			} 			
		}
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CMT 定義クラス（ICU::VECTOR 型）
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル
		@param[in]	cmi		割り込みベクター
		@param[in]	clk		駆動クロック
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR cmi, uint32_t clk>
	struct cmt_nom_t : public cmt_core_t<base, per> {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto CMI  = cmi;		///< 割り込みベクター
		static constexpr auto PCLK = clk;		///< PCLK 周波数

	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CMT 定義クラス（ベクター自由型）
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル
		@param[in]	IVEC	割り込みベクター型
		@param[in]	cmi		割り込みベクター
		@param[in]	clk		駆動クロック
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, typename IVEC, IVEC cmi, uint32_t clk>
	struct cmt_sel_t : public cmt_core_t<base, per> {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto CMI  = cmi;		///< 割り込みベクター
		static constexpr auto PCLK = clk;		///< PCLK 周波数

	};

#if defined(SIG_RX140)
	typedef cmt_nom_t<0x0008'8002, peripheral::CMT0, ICU::VECTOR::CMI0, clock_profile::PCLKB> CMT0;
	typedef cmt_nom_t<0x0008'8008, peripheral::CMT1, ICU::VECTOR::CMI1, clock_profile::PCLKB> CMT1;
#elif defined(SIG_RX621) || defined(SIG_RX62N)
	typedef cmt_nom_t<0x0008'8002, peripheral::CMT0, ICU::VECTOR::CMI0, clock_profile::PCLK> CMT0;
	typedef cmt_nom_t<0x0008'8008, peripheral::CMT1, ICU::VECTOR::CMI1, clock_profile::PCLK> CMT1;
	typedef cmt_nom_t<0x0008'8012, peripheral::CMT2, ICU::VECTOR::CMI2, clock_profile::PCLK> CMT2;
	typedef cmt_nom_t<0x0008'8018, peripheral::CMT3, ICU::VECTOR::CMI3, clock_profile::PCLK> CMT3;
#elif defined(SIG_RX220) || defined(SIG_RX231) || defined(SIG_RX63T) || defined(SIG_RX63T_S) || defined(SIG_RX631) || defined(SIG_RX63N) || defined(SIG_RX24T) || defined(SIG_RX26T) || defined(SIG_RX66T) || defined(SIG_RX72T)
	typedef cmt_nom_t<0x0008'8002, peripheral::CMT0, ICU::VECTOR::CMI0, clock_profile::PCLKB> CMT0;
	typedef cmt_nom_t<0x0008'8008, peripheral::CMT1, ICU::VECTOR::CMI1, clock_profile::PCLKB> CMT1;
	typedef cmt_nom_t<0x0008'8012, peripheral::CMT2, ICU::VECTOR::CMI2, clock_profile::PCLKB> CMT2;
	typedef cmt_nom_t<0x0008'8018, peripheral::CMT3, ICU::VECTOR::CMI3, clock_profile::PCLKB> CMT3;
#elif defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX651) || defined(SIG_RX66N) || defined(SIG_RX671) || defined(SIG_RX72M) || defined(SIG_RX72N)
	typedef cmt_nom_t<0x0008'8002, peripheral::CMT0, ICU::VECTOR::CMI0, clock_profile::PCLKB> CMT0;
	typedef cmt_nom_t<0x0008'8008, peripheral::CMT1, ICU::VECTOR::CMI1, clock_profile::PCLKB> CMT1;
	typedef cmt_sel_t<0x0008'8012, peripheral::CMT2, ICU::SELECTB, ICU::SELECTB::CMI2, clock_profile::PCLKB> CMT2;
	typedef cmt_sel_t<0x0008'8018, peripheral::CMT3, ICU::SELECTB, ICU::SELECTB::CMI3, clock_profile::PCLKB> CMT3;
#endif
}
