#pragma once
//=========================================================================//
/*!	@file
	@brief	RX66T/RX72T グループ・HRPWM 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019, 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief   高分解能 PWM 波形生成回路 クラス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per>
	struct hrpwm_t {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型

		//=================================================================//
		/*!
			@brief  HRPWM 動作制御レジスタ (HROCR)
			@param[in]	base	ベースアドレス
		*/
		//=================================================================//
		template <uint32_t base>
		struct hrocr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  DLLEN;
			bit_rw_t<io_, bitpos::B1>  HRRST;
		};
		typedef hrocr_t<0x000C'2A00> HROCR_;
		static HROCR_ HROCR;


		//=================================================================//
		/*!
			@brief  HRPWM 動作制御レジスタ 2 (HROCR2)
			@param[in]	base	ベースアドレス
		*/
		//=================================================================//
		template <uint32_t base>
		struct hrocr2_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   HRSEL0;
			bit_rw_t<io_, bitpos::B1>   HRSEL1;
			bit_rw_t<io_, bitpos::B2>   HRSEL2;
			bit_rw_t<io_, bitpos::B3>   HRSEL3;

			bit_rw_t<io_, bitpos::B8>   HRDIS0;
			bit_rw_t<io_, bitpos::B9>   HRDIS1;
			bit_rw_t<io_, bitpos::B10>  HRDIS2;
			bit_rw_t<io_, bitpos::B11>  HRDIS3;
		};
		typedef hrocr2_t<0x000C'2A02> HROCR2_;
		static HROCR2_ HROCR2;


		//=================================================================//
		/*!
			@brief  GTIOCnA 端子立ち上がりエッジ調整レジスタ (HRREARnA) (n = 0 ～ 3)
			@param[in]	base	ベースアドレス
		*/
		//=================================================================//
		template <uint32_t base>
		struct hrrearna_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  DLY;
		};
		typedef hrrearna_t<0x000C'2A18> HRREAR0A_;
		static HRREAR0A_ HRREAR0A;
		typedef hrrearna_t<0x000C'2A1C> HRREAR1A_;
		static HRREAR1A_ HRREAR1A;
		typedef hrrearna_t<0x000C'2A20> HRREAR2A_;
		static HRREAR2A_ HRREAR2A;
		typedef hrrearna_t<0x000C'2A24> HRREAR3A_;
		static HRREAR3A_ HRREAR3A;


		//=================================================================//
		/*!
			@brief  GTIOCnA 端子立ち下がりエッジ調整レジスタ (HRFEARnA) (n = 0 ～ 3)
			@param[in]	base	ベースアドレス
		*/
		//=================================================================//
		template <uint32_t base>
		struct hrfearna_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  DLY;
		};
		typedef hrfearna_t<0x000C'2A28> HRFEAR0A_;
		static HRFEAR0A_ HRFEAR0A;
		typedef hrfearna_t<0x000C'2A2C> HRFEAR1A_;
		static HRFEAR1A_ HRFEAR1A;
		typedef hrfearna_t<0x000C'2A30> HRFEAR2A_;
		static HRFEAR2A_ HRFEAR2A;
		typedef hrfearna_t<0x000C'2A34> HRFEAR3A_;
		static HRFEAR3A_ HRFEAR3A;


		//=================================================================//
		/*!
			@brief  GTIOCnB 端子立ち上がりエッジ調整レジスタ (HRREARnB) (n = 0 ～ 3)
			@param[in]	base	ベースアドレス
		*/
		//=================================================================//
		template <uint32_t base>
		struct hrrearnb_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  DLY;
		};
		typedef hrrearnb_t<0x000C'2A1A> HRREAR0B_;
		static HRREAR0B_ HRREAR0B;
		typedef hrrearnb_t<0x000C'2A1E> HRREAR1B_;
		static HRREAR1B_ HRREAR1B;
		typedef hrrearnb_t<0x000C'2A22> HRREAR2B_;
		static HRREAR2B_ HRREAR2B;
		typedef hrrearnb_t<0x000C'2A26> HRREAR3B_;
		static HRREAR3B_ HRREAR3B;


		//=================================================================//
		/*!
			@brief  GTIOCnB 端子立ち下がりエッジ調整レジスタ (HRFEARnB) (n = 0 ～ 3)
			@param[in]	base	ベースアドレス
		*/
		//=================================================================//
		template <uint32_t base>
		struct hrfearnb_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  DLY;
		};
		typedef hrfearnb_t<0x000C'2A1A> HRFEAR0B_;
		static HRFEAR0B_ HRFEAR0B;
		typedef hrfearnb_t<0x000C'2A1E> HRFEAR1B_;
		static HRFEAR1B_ HRFEAR1B;
		typedef hrfearnb_t<0x000C'2A22> HRFEAR2B_;
		static HRFEAR2B_ HRFEAR2B;
		typedef hrfearnb_t<0x000C'2A26> HRFEAR3B_;
		static HRFEAR3B_ HRFEAR3B;

#if defined(SIG_RX72T)
		//=================================================================//
		/*!
			@brief  HRPWM 動作クロック選択レジスタ (HRCKSR)
			@param[in]	base	ベースアドレス
		*/
		//=================================================================//
		template <uint32_t base>
		struct hrcksr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  HRCKSEL;
		};
		typedef hrcksr_t<0x000C'2A70> HRCKSR_;
		static HRCKSR_ HRCKSR;
#endif


		//-----------------------------------------------------------------//
		/*!
			@brief  HRPWM 動作クロック選択レジスタ (HRCKSR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		static void set_base_clock()
		{
#if defined(SIG_RX72T)
			HRCKSR.HRCKSEL = (clock_profile::PCLKC < 160'000'000) ? 0b00 : 0b01;
#endif
		}
	};
	template <peripheral per> typename hrpwm_t<per>::HROCR_ hrpwm_t<per>::HROCR;
	template <peripheral per> typename hrpwm_t<per>::HROCR2_ hrpwm_t<per>::HROCR2;
	template <peripheral per> typename hrpwm_t<per>::HRREAR0A_ hrpwm_t<per>::HRREAR0A;
	template <peripheral per> typename hrpwm_t<per>::HRREAR1A_ hrpwm_t<per>::HRREAR1A;
	template <peripheral per> typename hrpwm_t<per>::HRREAR2A_ hrpwm_t<per>::HRREAR2A;
	template <peripheral per> typename hrpwm_t<per>::HRREAR3A_ hrpwm_t<per>::HRREAR3A;
	template <peripheral per> typename hrpwm_t<per>::HRFEAR0A_ hrpwm_t<per>::HRFEAR0A;
	template <peripheral per> typename hrpwm_t<per>::HRFEAR1A_ hrpwm_t<per>::HRFEAR1A;
	template <peripheral per> typename hrpwm_t<per>::HRFEAR2A_ hrpwm_t<per>::HRFEAR2A;
	template <peripheral per> typename hrpwm_t<per>::HRFEAR3A_ hrpwm_t<per>::HRFEAR3A;
	template <peripheral per> typename hrpwm_t<per>::HRREAR0B_ hrpwm_t<per>::HRREAR0B;
	template <peripheral per> typename hrpwm_t<per>::HRREAR1B_ hrpwm_t<per>::HRREAR1B;
	template <peripheral per> typename hrpwm_t<per>::HRREAR2B_ hrpwm_t<per>::HRREAR2B;
	template <peripheral per> typename hrpwm_t<per>::HRREAR3B_ hrpwm_t<per>::HRREAR3B;
	template <peripheral per> typename hrpwm_t<per>::HRFEAR0B_ hrpwm_t<per>::HRFEAR0B;
	template <peripheral per> typename hrpwm_t<per>::HRFEAR1B_ hrpwm_t<per>::HRFEAR1B;
	template <peripheral per> typename hrpwm_t<per>::HRFEAR2B_ hrpwm_t<per>::HRFEAR2B;
	template <peripheral per> typename hrpwm_t<per>::HRFEAR3B_ hrpwm_t<per>::HRFEAR3B;
#if defined(SIG_RX72T)
	template <peripheral per> typename hrpwm_t<per>::HRCKSR_ hrpwm_t<per>::HRCKSR;
#endif

	typedef hrpwm_t<peripheral::HRPWM> HRPWM;
}
