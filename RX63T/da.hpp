#pragma once
//=========================================================================//
/*!	@file
	@brief	RX63T グループ・D/A 定義
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
		enum class analog : uint8_t {
			DA0,
			DA1,
		};


		//-----------------------------------------------------------------//
		/*!
			@brief  D/A データレジスタ 0（DADR0）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'80C0> DADR0_;
		static DADR0_ DADR0;


		//-----------------------------------------------------------------//
		/*!
			@brief  D/A データレジスタ 1（DADR1）
		*/
		//-----------------------------------------------------------------//
		typedef rw16_t<0x0008'80C2> DADR1_;
		static DADR1_ DADR1;


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
		typedef dacr_t<0x0008'80C4> DACR_;
		static DACR_ DACR;


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
		typedef dadpr_t<0x0008'80C5> DADPR_;
		static DADPR_ DADPR;


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
		typedef daadscr_t<0x0008'80C6> DAADSCR_;
		static DAADSCR_ DAADSCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポート設定と解除
			@param[in]	an	アナログ入力型
			@param[in]	f	ポート無効の場合「false」
		*/
		//-----------------------------------------------------------------//		
		static void enable(analog an, bool f = true)
		{
			switch(an) {
			case analog::DA0:  // P03
				break;
			case analog::DA1:  // P05
				break;
			default:
				break;
			}
		}
	};
	template <peripheral per> typename da_t<per>::DADR0_ da_t<per>::DADR0;
	template <peripheral per> typename da_t<per>::DADR1_ da_t<per>::DADR1;
	template <peripheral per> typename da_t<per>::DACR_  da_t<per>::DACR;
	template <peripheral per> typename da_t<per>::DADPR_ da_t<per>::DADPR;
	template <peripheral per> typename da_t<per>::DAADSCR_ da_t<per>::DAADSCR;

	typedef da_t<peripheral::DA> DA;
}
