#pragma once
//=========================================================================//
/*!	@file
	@brief	RX651/RX65N ポートアウトプットイネーブル 3（POE3a）定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポートアウトプットイネーブル 3 クラス
		@param[in]	base	POE3 モジュール先頭アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct poe3_t {

		static constexpr auto PERIPHERAL = peripheral::POE3;	///< ペリフェラル型
		static constexpr auto OEI1 = ICU::GROUPBL1::OEI1;		///< アウトプットイネーブル割り込み1
		static constexpr auto OEI2 = ICU::GROUPBL1::OEI2;		///< アウトプットイネーブル割り込み2
		static constexpr auto OEI3 = ICU::GROUPBL1::OEI3;		///< アウトプットイネーブル割り込み3
		static constexpr auto OEI4 = ICU::GROUPBL1::OEI4;		///< アウトプットイネーブル割り込み4
		static constexpr auto OEI5 = ICU::VECTOR::NONE;			///< アウトプットイネーブル割り込み5


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 1（ICSR1）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct icsr1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  POE0M;

			bit_rw_t <io_, bitpos::B8>     PIE1;

			bit_rw_t <io_, bitpos::B12>    POE0F;
		};
		static inline icsr1_t<base + 0x00> ICSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 2（ICSR2）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct icsr2_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  POE4M;

			bit_rw_t <io_, bitpos::B8>     PIE2;

			bit_rw_t <io_, bitpos::B12>    POE4F;
		};
		static inline icsr2_t<base + 0x04> ICSR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 3（ICSR3）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct icsr3_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  POE8M;

			bit_rw_t <io_, bitpos::B8>     PIE3;
			bit_rw_t <io_, bitpos::B9>     POE8E;

			bit_rw_t <io_, bitpos::B12>    POE8F;
		};
		static inline icsr3_t<base + 0x08> ICSR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 4（ICSR4）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct icsr4_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  POE10M;

			bit_rw_t <io_, bitpos::B8>     PIE4;
			bit_rw_t <io_, bitpos::B9>     POE10E;

			bit_rw_t <io_, bitpos::B12>    POE10F;
		};
		static inline icsr4_t<base + 0x16> ICSR4;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 5（ICSR5）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct icsr5_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  POE11M;

			bit_rw_t <io_, bitpos::B8>     PIE5;
			bit_rw_t <io_, bitpos::B9>     POE11E;

			bit_rw_t <io_, bitpos::B12>    POE11F;
		};
		static inline icsr5_t<base + 0x18> ICSR5;
	

		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 6（ICSR6）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct icsr6_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B9>     OSTSTE;

			bit_rw_t <io_, bitpos::B12>    OSTSTF;
		};
		static inline icsr6_t<base + 0x1C> ICSR6;


		//-----------------------------------------------------------------//
		/*!
			@brief	出力レベルコントロール / ステータスレジスタ 1（OCSR1）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ocsr1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B8>   OIE1;
			bit_rw_t<io_, bitpos::B9>   OCE1;

			bit_rw_t<io_, bitpos::B15>  OSF1;
		};
		static inline ocsr1_t<base + 0x02> OCSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	出力レベルコントロール / ステータスレジスタ 2（OCSR2）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ocsr2_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B8>   OIE2;
			bit_rw_t<io_, bitpos::B9>   OCE2;

			bit_rw_t<io_, bitpos::B15>  OSF2;
		};
		static inline ocsr2_t<base + 0x06> OCSR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	アクティブレベルレジスタ 1（ALR1）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct alr1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  OLSG0A;
			bit_rw_t<io_, bitpos::B1>  OLSG0B;
			bit_rw_t<io_, bitpos::B2>  OLSG1A;
			bit_rw_t<io_, bitpos::B3>  OLSG1B;
			bit_rw_t<io_, bitpos::B4>  OLSG2A;
			bit_rw_t<io_, bitpos::B5>  OLSG2B;

			bit_rw_t<io_, bitpos::B7>  OLSEN;
		};
		static inline alr1_t<base + 0x1A> ALR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	ソフトウェアポートアウトプットイネーブルレジスタ（SPOER）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct spoer_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MTUCH34HIZ;
			bit_rw_t<io_, bitpos::B1>  MTUCH67HIZ;
			bit_rw_t<io_, bitpos::B2>  MTUCH0HIZ;
		};
		static inline spoer_t<base + 0x0A> SPOER;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 1（POECR1）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MTU0AZE;
			bit_rw_t<io_, bitpos::B1>  MTU0BZE;
			bit_rw_t<io_, bitpos::B2>  MTU0CZE;
			bit_rw_t<io_, bitpos::B3>  MTU0DZE;
		};
		static inline poecr1_t<base + 0x0B> POECR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 2（POECR2）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr2_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MTU7BDZE;
			bit_rw_t<io_, bitpos::B1>  MTU7ACZE;
			bit_rw_t<io_, bitpos::B2>  MTU6BDZE;

			bit_rw_t<io_, bitpos::B8>  MTU4BDZE;
			bit_rw_t<io_, bitpos::B9>  MTU4ACZE;
			bit_rw_t<io_, bitpos::B10> MTU3BDZE;
		};
		static inline poecr2_t<base + 0x0C> POECR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 4（POECR4）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr4_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B2>  IC2ADDMT34ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDMT34ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDMT34ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT34ZE;

			bit_rw_t<io_, bitpos::B9>  IC1ADDMT67ZE;

			bit_rw_t<io_, bitpos::B11> IC3ADDMT67ZE;
			bit_rw_t<io_, bitpos::B12> IC4ADDMT67ZE;
			bit_rw_t<io_, bitpos::B13> IC5ADDMT67ZE;
		};
		static inline poecr4_t<base + 0x10> POECR4;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 5（POECR5）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr5_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B1>  IC1ADDMT0ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDMT0ZE;

			bit_rw_t<io_, bitpos::B4>  IC4ADDMT0ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT0ZE;
		};
		static inline poecr5_t<base + 0x12> POECR5;


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU0 端子選択レジスタ 1（M0SELR1）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct m0selr1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M0ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  M0BSEL;
		};
		static inline m0selr1_t<base + 0x24> M0SELR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU0 端子選択レジスタ 2（M0SELR2）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct m0selr2_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M0CSEL;
			bits_rw_t<io_, bitpos::B4, 4>  M0DSEL;
		};
		static inline m0selr2_t<base + 0x25> M0SELR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU3 端子選択レジスタ（M3SELR）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct m3selr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M3ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  M3BSEL;
		};
		static inline m3selr_t<base + 0x26> M3SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU4 端子選択レジスタ 1（M4SELR1）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct m4selr1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M4ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  M4CSEL;
		};
		static inline m4selr1_t<base + 0x27> M4SELR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU4 端子選択レジスタ 2（M4SELR2）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct m4selr2_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M4BSEL;
			bits_rw_t<io_, bitpos::B4, 4>  M4DSEL;
		};
		static inline m4selr2_t<base + 0x27> M4SELR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU6 端子選択レジスタ（M6SELR）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct m6selr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M6BSEL;
			bits_rw_t<io_, bitpos::B4, 4>  M6DSEL;
		};
		static inline m6selr_t<base + 0x2A> M6SELR;
	};
	typedef poe3_t<0x0008'C4C0> POE3;
}
