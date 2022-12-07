#pragma once
//=====================================================================//
/*!	@file
	@brief	RX グループ CMT 定義 @n
			RX621/RX62N @n
			RX631/RX63N @n
			RX63T @n
			RX24T @n
			RX64M/RX71M @n
			RX65N @n
			RX66T/RX72T @n
			RX72N
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2013, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
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
		typedef cmstr0_t<0x0008'8000> CMSTR0_;
		static CMSTR0_ CMSTR0;


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
		typedef cmstr1_t<0x0008'8010> CMSTR1_;
		static CMSTR1_ CMSTR1;


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
		typedef cmcr_t<base + 0x00> CMCR_;
		static CMCR_ CMCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CMCNT レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<base + 0x02> CMCNT_;
		static CMCNT_ CMCNT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CMCOR レジスタ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<base + 0x04> CMCOR_;
		static CMCOR_ CMCOR;


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
			case peripheral::CMT2:
				CMSTR1.STR2 = ena;
				break;
			case peripheral::CMT3:
				CMSTR1.STR3 = ena;
				break;
			} 			
		}
	};
	template <uint32_t base, peripheral per> typename cmt_core_t<base, per>::CMSTR0_ cmt_core_t<base, per>::CMSTR0;
	template <uint32_t base, peripheral per> typename cmt_core_t<base, per>::CMSTR1_ cmt_core_t<base, per>::CMSTR1;
	template <uint32_t base, peripheral per> typename cmt_core_t<base, per>::CMCR_   cmt_core_t<base, per>::CMCR;
	template <uint32_t base, peripheral per> typename cmt_core_t<base, per>::CMCNT_  cmt_core_t<base, per>::CMCNT;
	template <uint32_t base, peripheral per> typename cmt_core_t<base, per>::CMCOR_  cmt_core_t<base, per>::CMCOR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CMT 定義クラス（ICU::VECTOR）
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
		@brief  CMT 定義クラス（ベクター型指定）
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


#if defined(SIG_RX621) || defined(SIG_RX62N)
	typedef cmt_nom_t<0x0008'8002, peripheral::CMT0, ICU::VECTOR::CMI0, clock_profile::PCLK> CMT0;
	typedef cmt_nom_t<0x0008'8008, peripheral::CMT1, ICU::VECTOR::CMI1, clock_profile::PCLK> CMT1;
	typedef cmt_nom_t<0x0008'8012, peripheral::CMT2, ICU::VECTOR::CMI2, clock_profile::PCLK> CMT2;
	typedef cmt_nom_t<0x0008'8018, peripheral::CMT3, ICU::VECTOR::CMI3, clock_profile::PCLK> CMT3;
#elif defined(SIG_RX220) || defined(SIG_RX63T) || defined(SIG_RX631) || defined(SIG_RX63N) || defined(SIG_RX24T) || defined(SIG_RX66T) || defined(SIG_RX72T)
	typedef cmt_nom_t<0x0008'8002, peripheral::CMT0, ICU::VECTOR::CMI0, clock_profile::PCLKB> CMT0;
	typedef cmt_nom_t<0x0008'8008, peripheral::CMT1, ICU::VECTOR::CMI1, clock_profile::PCLKB> CMT1;
	typedef cmt_nom_t<0x0008'8012, peripheral::CMT2, ICU::VECTOR::CMI2, clock_profile::PCLKB> CMT2;
	typedef cmt_nom_t<0x0008'8018, peripheral::CMT3, ICU::VECTOR::CMI3, clock_profile::PCLKB> CMT3;
#elif defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX72M) || defined(SIG_RX72N)
	typedef cmt_nom_t<0x0008'8002, peripheral::CMT0, ICU::VECTOR::CMI0, clock_profile::PCLKB> CMT0;
	typedef cmt_nom_t<0x0008'8008, peripheral::CMT1, ICU::VECTOR::CMI1, clock_profile::PCLKB> CMT1;
	typedef cmt_sel_t<0x0008'8012, peripheral::CMT2, ICU::SELECTB, ICU::SELECTB::CMI2, clock_profile::PCLKB> CMT2;
	typedef cmt_sel_t<0x0008'8018, peripheral::CMT3, ICU::SELECTB, ICU::SELECTB::CMI3, clock_profile::PCLKB> CMT3;
#endif
}
