#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600 グループ・8 ビットタイマ（TMR）定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  8 ビットタイマ（TMR）
		@param[in]	base	ベースアドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct tmr_base_t {

		//-----------------------------------------------------------------//
		/*!
			@brie	タイマカウンタ（TCNT）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x08> TCNT;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイムコンスタントレジスタ A（TCORA）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x04> TCORA;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイムコンスタントレジスタ B（TCORB）
		*/
		//-----------------------------------------------------------------//
		static inline rw8_t<base + 0x06> TCORB;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマコントロールレジスタ（TCR）
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B3, 2>  CCLR;
			bit_rw_t <io_, bitpos::B5>     OVIE;
			bit_rw_t <io_, bitpos::B6>     CMIEA;
			bit_rw_t <io_, bitpos::B7>     CMIEB;
		};
		static inline tcr_t<base + 0x00> TCR;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマカウンタコントロールレジスタ（TCCR）
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tccr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  CKS;
			bits_rw_t<io_, bitpos::B3, 2>  CSS;
			bit_rw_t <io_, bitpos::B7>     TMRIS;
		};
		static inline tccr_t<base + 0x0A> TCCR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  8 ビットタイマ（TMRa）偶数版
		@param[in]	base	ベースアドレス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
		@param[in]	cmia	CMIA 型割り込みベクター
		@param[in]	cmib	CMIB 型割り込みベクター
		@param[in]	ovi		OVI 型割り込みベクター
		@param[in]	clk		駆動クロック
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, typename INT, INT cmia, INT cmib, INT ovi, uint32_t clk>
	struct tmra0246_t : public tmr_base_t<base> {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto CMIA = cmia;		///< CMIA 割り込みベクタ
		static constexpr auto CMIB = cmib;		///< CMIB 割り込みベクタ
		static constexpr auto OVI  = ovi;		///< OVI 割り込みベクタ
		static constexpr auto PCLK = clk;		///< PCLK 周波数
		static constexpr bool BIND16 = true;	///< 16 ビットバインド有効

		//-----------------------------------------------------------------//
		/*!
			@brie	タイマカウンタ（TCNTW）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x08> TCNT16;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイムコンスタントレジスタ A（TCORA）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x04> TCORA16;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイムコンスタントレジスタ B（TCORB）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x06> TCORB16;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマコントロール／ステータスレジスタ（TCSR）
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tcsr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  OSA;
			bits_rw_t<io_, bitpos::B2, 2>  OSB;
		};
		static inline tcsr_t<base + 0x02> TCSR;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマカウンタスタートレジスタ (TCSTR)
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tcstr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     TCS;
		};
		static inline tcstr_t<base + 0x0C> TCSTR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  8 ビットタイマ（TMR）偶数版
		@param[in]	base	ベースアドレス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
		@param[in]	cmia	CMIA 型割り込みベクター
		@param[in]	cmib	CMIB 型割り込みベクター
		@param[in]	ovi		OVI 型割り込みベクター
		@param[in]	clk		駆動クロック
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, typename INT, INT cmia, INT cmib, INT ovi, uint32_t clk>
	struct tmr0246_t : public tmr_base_t<base> {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto CMIA = cmia;		///< CMIA 割り込みベクタ
		static constexpr auto CMIB = cmib;		///< CMIB 割り込みベクタ
		static constexpr auto OVI  = ovi;		///< OVI 割り込みベクタ
		static constexpr auto PCLK = clk;		///< PCLK 周波数
		static constexpr bool BIND16 = true;	///< 16 ビットバインド有効

		//-----------------------------------------------------------------//
		/*!
			@brie	タイマカウンタ（TCNTW）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x08> TCNT16;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイムコンスタントレジスタ A（TCORA）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x04> TCORA16;


		//-----------------------------------------------------------------//
		/*!
			@brie	タイムコンスタントレジスタ B（TCORB）
		*/
		//-----------------------------------------------------------------//
		static inline rw16_t<base + 0x06> TCORB16;


		//-----------------------------------------------------------------//
		/*!
			@brief	タイマコントロール／ステータスレジスタ（TCSR）
			@param[in]	ofs	アドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct tcsr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  OSA;
			bits_rw_t<io_, bitpos::B2, 2>  OSB;
			bit_rw_t <io_, bitpos::B4>     ADTE;
		};
		static inline tcsr_t<base + 0x02> TCSR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  8 ビットタイマ（TMR）奇数版
		@param[in]	base	ベースアドレス
		@param[in]	per		ペリフェラル型
		@param[in]	INT		割り込み型
		@param[in]	cmia	CMIA 型割り込みベクター
		@param[in]	cmib	CMIB 型割り込みベクター
		@param[in]	ovi		OVI 型割り込みベクター
		@param[in]	clk		駆動クロック
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, typename INT, INT cmia, INT cmib, INT ovi, uint32_t clk>
	struct tmr1357_t : public tmr_base_t<base> {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto CMIA_VEC = cmia;	///< CMIA 割り込みベクタ
		static constexpr auto CMIB_VEC = cmib;	///< CMIB 割り込みベクタ
		static constexpr auto OVI_VEC  = ovi;	///< OVI 割り込みベクタ
		static constexpr auto PCLK = clk;		///< PCLK 周波数
		static constexpr bool BIND16 = false;	///< 16 ビットバインド不可
	};

#if defined(SIG_RX140)
	typedef tmra0246_t<0x0008'8200, peripheral::TMR0, ICU::VECTOR,
		ICU::VECTOR::CMIA0, ICU::VECTOR::CMIB0, ICU::VECTOR::OVI0, clock_profile::PCLKB> TMR0;
	typedef tmr1357_t<0x0008'8201, peripheral::TMR1, ICU::VECTOR,
		ICU::VECTOR::CMIA1, ICU::VECTOR::CMIB1, ICU::VECTOR::OVI1, clock_profile::PCLKB> TMR1;
	typedef tmra0246_t<0x0008'8210, peripheral::TMR2, ICU::VECTOR,
		ICU::VECTOR::CMIA2, ICU::VECTOR::CMIB2, ICU::VECTOR::OVI2, clock_profile::PCLKB> TMR2;
	typedef tmr1357_t<0x0008'8211, peripheral::TMR3, ICU::VECTOR,
		ICU::VECTOR::CMIA3, ICU::VECTOR::CMIB3, ICU::VECTOR::OVI3, clock_profile::PCLKB> TMR3;
#elif defined(SIG_RX220) || defined(SIG_RX231) || defined(SIG_RX631) || defined(SIG_RX63N)
	typedef tmr0246_t<0x0008'8200, peripheral::TMR0, ICU::VECTOR,
		ICU::VECTOR::CMIA0, ICU::VECTOR::CMIB0, ICU::VECTOR::OVI0, clock_profile::PCLKB> TMR0;
	typedef tmr1357_t<0x0008'8201, peripheral::TMR1, ICU::VECTOR,
		ICU::VECTOR::CMIA1, ICU::VECTOR::CMIB1, ICU::VECTOR::OVI1, clock_profile::PCLKB> TMR1;
	typedef tmr0246_t<0x0008'8210, peripheral::TMR2, ICU::VECTOR,
		ICU::VECTOR::CMIA2, ICU::VECTOR::CMIB2, ICU::VECTOR::OVI2, clock_profile::PCLKB> TMR2;
	typedef tmr1357_t<0x0008'8211, peripheral::TMR3, ICU::VECTOR,
		ICU::VECTOR::CMIA3, ICU::VECTOR::CMIB3, ICU::VECTOR::OVI3, clock_profile::PCLKB> TMR3;
#elif defined(SIG_RX621) || defined(SIG_RX62N)
	typedef tmr0246_t<0x0008'8200, peripheral::TMR0, ICU::VECTOR,
		ICU::VECTOR::CMIA0, ICU::VECTOR::CMIB0, ICU::VECTOR::OVI0, clock_profile::PCLK> TMR0;
	typedef tmr1357_t<0x0008'8201, peripheral::TMR1, ICU::VECTOR,
		ICU::VECTOR::CMIA1, ICU::VECTOR::CMIB1, ICU::VECTOR::OVI1, clock_profile::PCLK> TMR1;
	typedef tmr0246_t<0x0008'8210, peripheral::TMR2, ICU::VECTOR,
		ICU::VECTOR::CMIA2, ICU::VECTOR::CMIB2, ICU::VECTOR::OVI2, clock_profile::PCLK> TMR2;
	typedef tmr1357_t<0x0008'8211, peripheral::TMR3, ICU::VECTOR,
		ICU::VECTOR::CMIA3, ICU::VECTOR::CMIB3, ICU::VECTOR::OVI3, clock_profile::PCLK> TMR3;
#elif defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX651) || defined(SIG_RX72M) || defined(SIG_RX72N)
	typedef tmr0246_t<0x0008'8200, peripheral::TMR0, ICU::SELECTB,
		ICU::SELECTB::CMIA0, ICU::SELECTB::CMIB0, ICU::SELECTB::OVI0, clock_profile::PCLKB> TMR0;
	typedef tmr1357_t<0x0008'8201, peripheral::TMR1, ICU::SELECTB,
		ICU::SELECTB::CMIA1, ICU::SELECTB::CMIB1, ICU::SELECTB::OVI1, clock_profile::PCLKB> TMR1;
	typedef tmr0246_t<0x0008'8210, peripheral::TMR2, ICU::SELECTB,
		ICU::SELECTB::CMIA2, ICU::SELECTB::CMIB2, ICU::SELECTB::OVI2, clock_profile::PCLKB> TMR2;
	typedef tmr1357_t<0x0008'8211, peripheral::TMR3, ICU::SELECTB,
		ICU::SELECTB::CMIA3, ICU::SELECTB::CMIB3, ICU::SELECTB::OVI3, clock_profile::PCLKB> TMR3;
#elif defined(SIG_RX24T) || defined(SIG_RX26T) || defined(SIG_RX66T) || defined(SIG_RX72T)
	typedef tmr0246_t<0x0008'8200, peripheral::TMR0, ICU::VECTOR,
		ICU::VECTOR::CMIA0, ICU::VECTOR::CMIB0, ICU::VECTOR::OVI0, clock_profile::PCLKB> TMR0;
	typedef tmr1357_t<0x0008'8201, peripheral::TMR1, ICU::VECTOR,
		ICU::VECTOR::CMIA1, ICU::VECTOR::CMIB1, ICU::VECTOR::OVI1, clock_profile::PCLKB> TMR1;
	typedef tmr0246_t<0x0008'8210, peripheral::TMR2, ICU::VECTOR,
		ICU::VECTOR::CMIA2, ICU::VECTOR::CMIB2, ICU::VECTOR::OVI2, clock_profile::PCLKB> TMR2;
	typedef tmr1357_t<0x0008'8211, peripheral::TMR3, ICU::VECTOR,
		ICU::VECTOR::CMIA3, ICU::VECTOR::CMIB3, ICU::VECTOR::OVI3, clock_profile::PCLKB> TMR3;
	typedef tmr0246_t<0x0008'8220, peripheral::TMR4, ICU::VECTOR,
		ICU::VECTOR::CMIA4, ICU::VECTOR::CMIB4, ICU::VECTOR::OVI4, clock_profile::PCLKB> TMR4;
	typedef tmr1357_t<0x0008'8221, peripheral::TMR5, ICU::VECTOR,
		ICU::VECTOR::CMIA5, ICU::VECTOR::CMIB5, ICU::VECTOR::OVI5, clock_profile::PCLKB> TMR5;
	typedef tmr0246_t<0x0008'8230, peripheral::TMR6, ICU::VECTOR,
		ICU::VECTOR::CMIA6, ICU::VECTOR::CMIB6, ICU::VECTOR::OVI6, clock_profile::PCLKB> TMR6;
	typedef tmr1357_t<0x0008'8231, peripheral::TMR7, ICU::VECTOR,
		ICU::VECTOR::CMIA7, ICU::VECTOR::CMIB7, ICU::VECTOR::OVI7, clock_profile::PCLKB> TMR7;
#endif
}
