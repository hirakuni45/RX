#pragma once
//=========================================================================//
/*!	@file
	@brief	RX631/RX63N グループ D/A コンバータ（DAa）定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  D/A コンバータ（DAa）
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per>
	struct da_t {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アナログ入出力型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class ANALOG : uint8_t {
			DA0,	///< P03/DA0
			DA1,	///< P05/DA1
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  D/A ポートをアナログ出力に設定
			@param[in]	an		アナログ型
			@param[in]	ena		不許可の場合は「false」
		*/
		//-----------------------------------------------------------------//
		static void enable(ANALOG an, bool ena = true) noexcept
		{
			MPC::PWPR.B0WI = 0;		// PWPR 書き込み許可
			MPC::PWPR.PFSWE = 1;	// PxxPFS 書き込み許可

			switch(an) {
			case ANALOG::DA0:
				if(ena) {
					PORT0::PDR.B3 = 0;
					PORT0::PMR.B3 = 0;
					PORT0::PCR.B3 = 0;
				}
				MPC::P03PFS.ASEL = ena;
				break;
			case ANALOG::DA1:
				if(ena) {
					PORT0::PDR.B5 = 0;
					PORT0::PMR.B5 = 0;
					PORT0::PCR.B5 = 0;
				}
				MPC::P05PFS.ASEL = ena;
				break;
			}

			MPC::PWPR = device::MPC::PWPR.B0WI.b();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  D/A データレジスタ 0（DADR0）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'80C0> DADR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  D/A データレジスタ 1（DADR1）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<0x0008'80C2> DADR1;


		//-----------------------------------------------------------------//
		/*!
			@brief  D/A 制御レジスタ（DACR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dacr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B5> DAE;
			bit_rw_t<io_, bitpos::B6> DAOE0;
			bit_rw_t<io_, bitpos::B7> DAOE1;
		};
		static inline dacr_t<0x0008'80C4> DACR;


		//-----------------------------------------------------------------//
		/*!
			@brief  DADRm フォーマット選択レジスタ（DADPR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct dadpr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B7> DPSEL;
		};
		static inline dadpr_t<0x0008'80C5> DADPR;


		//-----------------------------------------------------------------//
		/*!
			@brief  D/A A/D 同期スタート制御レジスタ（DAADSCR）
			@param[in]	ofs	オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct daadscr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B7> DAADST;
		};
		static inline daadscr_t<0x0008'80C6> DAADSCR;
	};
	typedef da_t<peripheral::DA> DA;
}
