#pragma once
//=========================================================================//
/*!	@file
	@brief	Port Output Enable 3 / ポートアウトプットイネーブル 3 (POE3E) @n
			RX14T
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2026 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  POE3E base class
		@param[in]	base	モジュール先頭アドレス
		@param[in]	per	ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct poe3e_base_t {

		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 1 (ICSR1)
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

			bits_rw_t<io_, bitpos::B0, 4>   POE0M;
			bits_rw_t<io_, bitpos::B4, 4>   POE0M2;
			bit_rw_t <io_, bitpos::B8>      PIE1;

			bit_rw_t <io_, bitpos::B12>     POE0F;

			bit_rw_t <io_, bitpos::B15>     INV;
		};
		static inline icsr1_t<base + 0x00> ICSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 3 (ICSR3)
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

			bits_rw_t<io_, bitpos::B0, 4>   POE8M;
			bits_rw_t<io_, bitpos::B4, 4>   POE8M2;
			bit_rw_t <io_, bitpos::B8>      PIE3;
			bit_rw_t <io_, bitpos::B9>      POE8E;

			bit_rw_t <io_, bitpos::B12>     POE8F;

			bit_rw_t <io_, bitpos::B15>     INV;
		};
		static inline icsr3_t<base + 0x08> ICSR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 4 (ICSR4)
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

			bits_rw_t<io_, bitpos::B0, 4>   POE10M;
			bits_rw_t<io_, bitpos::B4, 4>   POE10M2;
			bit_rw_t <io_, bitpos::B8>      PIE4;
			bit_rw_t <io_, bitpos::B9>      POE10E;

			bit_rw_t <io_, bitpos::B12>     POE10F;

			bit_rw_t <io_, bitpos::B15>     INV;
		};
		static inline icsr4_t<base + 0x16> ICSR4;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 5 (ICSR5)
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

			bits_rw_t<io_, bitpos::B0, 4>   POE11M;
			bits_rw_t<io_, bitpos::B4, 4>   POE11M2;
			bit_rw_t <io_, bitpos::B8>      PIE5;
			bit_rw_t <io_, bitpos::B9>      POE11E;

			bit_rw_t <io_, bitpos::B12>     POE11F;

			bit_rw_t <io_, bitpos::B15>     INV;
		};
		static inline icsr5_t<base + 0x18> ICSR5;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 6 (ICSR6)
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

			bit_rw_t <io_, bitpos::B9>      OSTSTE;

			bit_rw_t <io_, bitpos::B12>     OSTSTF;
		};
		static inline icsr6_t<base + 0x1C> ICSR6;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 7 (ICSR7)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct icsr7_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>   POE12M;
			bits_rw_t<io_, bitpos::B4, 4>   POE12M2;
			bit_rw_t <io_, bitpos::B8>      PIE7;
			bit_rw_t <io_, bitpos::B9>      POE12E;

			bit_rw_t <io_, bitpos::B12>     POE12F;

			bit_rw_t <io_, bitpos::B15>     INV;
		};
		static inline icsr7_t<base + 0x20> ICSR7;


		//-----------------------------------------------------------------//
		/*!
			@brief	出力レベルコントロール / ステータスレジスタ 1 (OCSR1)
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

			bit_rw_t <io_, bitpos::B8>      OIE1;
			bit_rw_t <io_, bitpos::B9>      OCE1;

			bit_rw_t <io_, bitpos::B15>     OSF1;
		};
		static inline ocsr1_t<base + 0x02> OCSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	出力レベルコントロール / ステータスレジスタ 3 (OCSR3)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ocsr3_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B8>      OIE3;
			bit_rw_t <io_, bitpos::B9>      OCE3;

			bit_rw_t <io_, bitpos::B15>     OSF3;
		};
		static inline ocsr3_t<base + 0x2A> OCSR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	アクティブレベルレジスタ 1 (ALR1)
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

			bit_rw_t <io_, bitpos::B0>      OLSG0A;
			bit_rw_t <io_, bitpos::B1>      OLSG0B;
			bit_rw_t <io_, bitpos::B2>      OLSG1A;
			bit_rw_t <io_, bitpos::B3>      OLSG1B;
			bit_rw_t <io_, bitpos::B4>      OLSG2A;
			bit_rw_t <io_, bitpos::B5>      OLSG2B;

			bit_rw_t <io_, bitpos::B7>      OLSEN;
		};
		static inline alr1_t<base + 0x1A> ALR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	アクティブレベルレジスタ 3 (ALR3)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct alr3_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      OLSG0A;
			bit_rw_t <io_, bitpos::B1>      OLSG0B;
			bit_rw_t <io_, bitpos::B2>      OLSG1A;
			bit_rw_t <io_, bitpos::B3>      OLSG1B;
			bit_rw_t <io_, bitpos::B4>      OLSG2A;
			bit_rw_t <io_, bitpos::B5>      OLSG2B;

			bit_rw_t <io_, bitpos::B7>      OLSEN;
		};
		static inline alr3_t<base + 0x2C> ALR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	ソフトウェアポートアウトプットイネーブルレジスタ (SPOER)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct spoer_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      MTUCH34HIZ;

			bit_rw_t <io_, bitpos::B2>      MTUCH0HIZ;
			bit_rw_t <io_, bitpos::B3>      GPT01HIZ;
			bit_rw_t <io_, bitpos::B4>      GPT23HIZ;

			bit_rw_t <io_, bitpos::B8>      GPT02HIZ;
		};
		static inline spoer_t<base + 0x2E> SPOER;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 1 (POECR1)
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

			bit_rw_t <io_, bitpos::B0>      MTU0AZE;
			bit_rw_t <io_, bitpos::B1>      MTU0BZE;
			bit_rw_t <io_, bitpos::B2>      MTU0CZE;
			bit_rw_t <io_, bitpos::B3>      MTU0DZE;
		};
		static inline poecr1_t<base + 0x0B> POECR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 2 (POECR2)
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

			bit_rw_t <io_, bitpos::B8>      MTU4BDZE;
			bit_rw_t <io_, bitpos::B9>      MTU4ACZE;
			bit_rw_t <io_, bitpos::B10>     MTU3BDZE;
		};
		static inline poecr2_t<base + 0x0C> POECR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 3 (POECR3)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr3_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      GPT0ABZE;
			bit_rw_t <io_, bitpos::B1>      GPT1ABZE;
			bit_rw_t <io_, bitpos::B2>      GPT2ABZE;
		};
		static inline poecr3_t<base + 0x0E> POECR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 4 (POECR4)
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

			bit_rw_t <io_, bitpos::B0>      CMADDMT34ZE;
			bit_rw_t <io_, bitpos::B1>      IC1ADDMT34ZE;
			bit_rw_t <io_, bitpos::B2>      IC2ADDMT34ZE;
			bit_rw_t <io_, bitpos::B3>      IC3ADDMT34ZE;
			bit_rw_t <io_, bitpos::B4>      IC4ADDMT34ZE;
			bit_rw_t <io_, bitpos::B5>      IC5ADDMT34ZE;
			bit_rw_t <io_, bitpos::B6>      IC6ADDMT34ZE;
		};
		static inline poecr4_t<base + 0x10> POECR4;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 5 (POECR5)
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

			bit_rw_t <io_, bitpos::B0>      CMADDMT0ZE;
			bit_rw_t <io_, bitpos::B1>      IC1ADDMT0ZE;

			bit_rw_t <io_, bitpos::B3>      IC3ADDMT0ZE;
			bit_rw_t <io_, bitpos::B4>      IC4ADDMT0ZE;
			bit_rw_t <io_, bitpos::B5>      IC5ADDMT0ZE;
			bit_rw_t <io_, bitpos::B6>      IC6ADDMT0ZE;
		};
		static inline poecr5_t<base + 0x12> POECR5;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 6 (POECR6)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr6_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      CMADDGPT01ZE;
			bit_rw_t <io_, bitpos::B1>      IC1ADDGPT01ZE;

			bit_rw_t <io_, bitpos::B3>      IC3ADDGPT01ZE;
			bit_rw_t <io_, bitpos::B4>      IC4ADDGPT01ZE;
			bit_rw_t <io_, bitpos::B5>      IC5ADDGPT01ZE;
			bit_rw_t <io_, bitpos::B6>      IC6ADDGPT01ZE;
		};
		static inline poecr6_t<base + 0x14> POECR6;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 6B (POECR6B)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr6b_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      CMADDGPT23ZE;
			bit_rw_t <io_, bitpos::B1>      IC1ADDGPT23ZE;

			bit_rw_t <io_, bitpos::B3>      IC3ADDGPT23ZE;
			bit_rw_t <io_, bitpos::B4>      IC4ADDGPT23ZE;
			bit_rw_t <io_, bitpos::B5>      IC5ADDGPT23ZE;
			bit_rw_t <io_, bitpos::B6>      IC6ADDGPT23ZE;
		};
		static inline poecr6b_t<base + 0x50> POECR6B;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 9 (POECR9)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr9_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      CMADDGPT02ZE;
			bit_rw_t <io_, bitpos::B1>      IC1ADDGPT02ZE;

			bit_rw_t <io_, bitpos::B3>      IC3ADDGPT02ZE;
			bit_rw_t <io_, bitpos::B4>      IC4ADDGPT02ZE;
			bit_rw_t <io_, bitpos::B5>      IC5ADDGPT02ZE;
			bit_rw_t <io_, bitpos::B6>      IC6ADDGPT02ZE;
		};
		static inline poecr9_t<base + 0x52> POECR9;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートモードマスクコントロールレジスタ 0 (PMMCR0)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pmmcr0_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      MTU0AME;
			bit_rw_t <io_, bitpos::B1>      MTU0BME;
			bit_rw_t <io_, bitpos::B2>      MTU0CME;
			bit_rw_t <io_, bitpos::B3>      MTU0DME;
		};
		static inline pmmcr0_t<base + 0x30> PMMCR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートモードマスクコントロールレジスタ 1 (PMMCR1)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pmmcr1_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B8>      MTU4BME;
			bit_rw_t <io_, bitpos::B9>      MTU4AME;
			bit_rw_t <io_, bitpos::B10>     MTU3BME;
			bit_rw_t <io_, bitpos::B11>     MTU4DME;
			bit_rw_t <io_, bitpos::B12>     MTU4CME;
			bit_rw_t <io_, bitpos::B13>     MTU3DME;
		};
		static inline pmmcr1_t<base + 0x32> PMMCR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートモードマスクコントロールレジスタ 2 (PMMCR2)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pmmcr2_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      GPT0AME;
			bit_rw_t <io_, bitpos::B1>      GPT0BME;
			bit_rw_t <io_, bitpos::B2>      GPT1AME;
			bit_rw_t <io_, bitpos::B3>      GPT1BME;
			bit_rw_t <io_, bitpos::B4>      GPT2AME;
			bit_rw_t <io_, bitpos::B5>      GPT2BME;
		};
		static inline pmmcr2_t<base + 0x34> PMMCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコンパレータ検出フラグレジスタ (POECMPFR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecmpfr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      C0FLAG;
			bit_rw_t <io_, bitpos::B1>      C1FLAG;
			bit_rw_t <io_, bitpos::B2>      C2FLAG;
		};
		static inline poecmpfr_t<base + 0x26> POECMPFR;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコンパレータ要求選択レジスタ (POECMPSEL)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecmpsel_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      POEREQ0;
			bit_rw_t <io_, bitpos::B1>      POEREQ1;
			bit_rw_t <io_, bitpos::B2>      POEREQ2;
		};
		static inline poecmpsel_t<base + 0x28> POECMPSEL;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコンパレータ要求拡張選択レジスタ (POECMPEX[m]) (m = 0, 2, 4 ～ 6)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecmpex_t : public rw8_index_t<ofs> {
			typedef rw8_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j <= 6) { io_::index = j; } }

			bit_rw_t <io_, bitpos::B0>       POEREQ0;
			bit_rw_t <io_, bitpos::B1>       POEREQ1;
			bit_rw_t <io_, bitpos::B2>       POEREQ2;

			poecmpex_t& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline poecmpex_t<base + 0x38> POECMPEX;


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU0 端子選択レジスタ 1 (M0SELR1)
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

			bits_rw_t<io_, bitpos::B0, 4>   M0ASEL;
			bits_rw_t<io_, bitpos::B4, 4>   M0BSEL;
		};
		static inline m0selr1_t<base + 0x60> M0SELR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU0 端子選択レジスタ 2 (M0SELR2)
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

			bits_rw_t<io_, bitpos::B0, 4>   M0CSEL;
			bits_rw_t<io_, bitpos::B4, 4>   M0DSEL;
		};
		static inline m0selr2_t<base + 0x61> M0SELR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU3 端子選択レジスタ (M3SELR)
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

			bits_rw_t<io_, bitpos::B0, 4>   M3BSEL;
			bits_rw_t<io_, bitpos::B4, 4>   M3DSEL;
		};
		static inline m3selr_t<base + 0x62> M3SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU4 端子選択レジスタ 1 (M4SELR1)
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

			bits_rw_t<io_, bitpos::B0, 4>   M4ASEL;
			bits_rw_t<io_, bitpos::B4, 4>   M4CSEL;
		};
		static inline m4selr1_t<base + 0x63> M4SELR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU4 端子選択レジスタ 2 (M4SELR2)
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

			bits_rw_t<io_, bitpos::B0, 4>   M4BSEL;
			bits_rw_t<io_, bitpos::B4, 4>   M4DSEL;
		};
		static inline m4selr2_t<base + 0x64> M4SELR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPTW0 端子選択レジスタ (G0SELR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct g0selr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>   G0ASEL;
			bits_rw_t<io_, bitpos::B4, 4>   G0BSEL;
		};
		static inline g0selr_t<base + 0x6A> G0SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPTW1 端子選択レジスタ (G1SELR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct g1selr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>   G1ASEL;
			bits_rw_t<io_, bitpos::B4, 4>   G1BSEL;
		};
		static inline g1selr_t<base + 0x6B> G1SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPTW2 端子選択レジスタ (G2SELR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct g2selr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>   G2ASEL;
			bits_rw_t<io_, bitpos::B4, 4>   G2BSEL;
		};
		static inline g2selr_t<base + 0x6C> G2SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力信号マスク制御レジスタ 0 (IMCR0)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct imcr0_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>   POE0MS;
		};
		static inline imcr0_t<base + 0x5C> IMCR0;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力信号マスク制御レジスタ 2 (IMCR2)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct imcr2_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>   POE8MS;
		};
		static inline imcr2_t<base + 0x5E> IMCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力信号マスク制御レジスタ 3 (IMCR3)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct imcr3_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>   POE10MS;
		};
		static inline imcr3_t<base + 0x5F> IMCR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力信号マスク制御レジスタ 4 (IMCR4)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct imcr4_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>   POE11MS;
		};
		static inline imcr4_t<base + 0x74> IMCR4;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力信号マスク制御レジスタ 5 (IMCR5)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct imcr5_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>   POE12MS;
		};
		static inline imcr5_t<base + 0x75> IMCR5;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力信号マスク制御レジスタ 9 (IMCR9)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct imcr9_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>   CMP0MS;
		};
		static inline imcr9_t<base + 0x79> IMCR9;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力信号マスク制御レジスタ 10 (IMCR10)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct imcr10_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>   CMP1MS;
		};
		static inline imcr10_t<base + 0x7A> IMCR10;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力信号マスク制御レジスタ 11 (IMCR11)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct imcr11_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6>   CMP2MS;
		};
		static inline imcr11_t<base + 0x7B> IMCR11;
	};

#if defined(SIG_RX14T)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポートアウトプットイネーブル 3 (POE3E) クラス
		@param[in]	base	モジュール先頭アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct poe3e_t : public poe3e_base_t<base> {

		static constexpr auto PERIPHERAL = peripheral::POE3E;	///< ペリフェラル型
	};
	static inline poe3e_t<0x0009'E400> POE3E;
#endif
}
