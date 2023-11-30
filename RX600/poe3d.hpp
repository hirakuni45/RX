#pragma once
//=========================================================================//
/*!	@file
	@brief	RX26T ポートアウトプットイネーブル 3 (POE3D)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポートアウトプットイネーブル 3 (POE3D) ベース・クラス
		@param[in]	base	モジュール先頭アドレス
		@param[in]	per	ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct poe3d_base_t {

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
		typedef icsr1_t<base + 0x00> ICSR1_;
		static  ICSR1_ ICSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 2 (ICSR2)
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

			bits_rw_t<io_, bitpos::B0, 4>   POE4M;
			bits_rw_t<io_, bitpos::B4, 4>   POE4M2;
			bit_rw_t <io_, bitpos::B8>      PIE2;

			bit_rw_t <io_, bitpos::B12>     POE4F;

			bit_rw_t <io_, bitpos::B15>     INV;
		};
		typedef icsr2_t<base + 0x04> ICSR2_;
		static  ICSR2_ ICSR2;


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
		typedef icsr3_t<base + 0x08> ICSR3_;
		static  ICSR3_ ICSR3;


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
		typedef icsr4_t<base + 0x16> ICSR4_;
		static  ICSR4_ ICSR4;


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
		typedef icsr5_t<base + 0x18> ICSR5_;
		static  ICSR5_ ICSR5;


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
		typedef icsr6_t<base + 0x1C> ICSR6_;
		static  ICSR6_ ICSR6;


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
		typedef icsr7_t<base + 0x20> ICSR7_;
		static  ICSR7_ ICSR7;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 8 (ICSR8)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct icsr8_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>   POE9M;
			bits_rw_t<io_, bitpos::B4, 4>   POE9M2;
			bit_rw_t <io_, bitpos::B8>      PIE8;
			bit_rw_t <io_, bitpos::B9>      POE9E;

			bit_rw_t <io_, bitpos::B12>     POE9F;

			bit_rw_t <io_, bitpos::B15>     INV;
		};
		typedef icsr8_t<base + 0x40> ICSR8_;
		static  ICSR8_ ICSR8;


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
		typedef ocsr1_t<base + 0x02> OCSR1_;
		static  OCSR1_ OCSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	出力レベルコントロール / ステータスレジスタ 2 (OCSR2)
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

			bit_rw_t <io_, bitpos::B8>      OIE2;
			bit_rw_t <io_, bitpos::B9>      OCE2;

			bit_rw_t <io_, bitpos::B15>     OSF2;
		};
		typedef ocsr2_t<base + 0x06> OCSR2_;
		static  OCSR2_ OCSR2;


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
		typedef ocsr3_t<base + 0x2A> OCSR3_;
		static  OCSR3_ OCSR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	出力レベルコントロール / ステータスレジスタ 4 (OCSR4)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ocsr4_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B8>      OIE4;
			bit_rw_t <io_, bitpos::B9>      OCE4;

			bit_rw_t <io_, bitpos::B15>     OSF4;
		};
		typedef ocsr4_t<base + 0x46> OCSR4_;
		static  OCSR4_ OCSR4;


		//-----------------------------------------------------------------//
		/*!
			@brief	出力レベルコントロール / ステータスレジスタ 5 (OCSR5)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct ocsr5_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B8>      OIE5;
			bit_rw_t <io_, bitpos::B9>      OCE5;

			bit_rw_t <io_, bitpos::B15>     OSF5;
		};
		typedef ocsr5_t<base + 0x48> OCSR5_;
		static  OCSR5_ OCSR5;


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
		typedef alr1_t<base + 0x1A> ALR1_;
		static  ALR1_ ALR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	アクティブレベルレジスタ 2 (ALR2)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct alr2_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      OLSG4A;
			bit_rw_t <io_, bitpos::B1>      OLSG4B;
			bit_rw_t <io_, bitpos::B2>      OLSG5A;
			bit_rw_t <io_, bitpos::B3>      OLSG5B;
			bit_rw_t <io_, bitpos::B4>      OLSG6A;
			bit_rw_t <io_, bitpos::B5>      OLSG6B;

			bit_rw_t <io_, bitpos::B7>      OLSEN;
		};
		typedef alr2_t<base + 0x1E> ALR2_;
		static  ALR2_ ALR2;


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
		typedef alr3_t<base + 0x2C> ALR3_;
		static  ALR3_ ALR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	アクティブレベルレジスタ 4 (ALR4)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct alr4_t : public rw16_t<ofs> {
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
		typedef alr4_t<base + 0x4A> ALR4_;
		static  ALR4_ ALR4;


		//-----------------------------------------------------------------//
		/*!
			@brief	アクティブレベルレジスタ 5 (ALR5)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct alr5_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      OLSG0A;
			bit_rw_t <io_, bitpos::B1>      OLSG0B;

			bit_rw_t <io_, bitpos::B7>      OLSEN;
		};
		typedef alr5_t<base + 0x4C> ALR5_;
		static  ALR5_ ALR5;


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
			bit_rw_t <io_, bitpos::B1>      MTUCH67HIZ;
			bit_rw_t <io_, bitpos::B2>      MTUCH0HIZ;
			bit_rw_t <io_, bitpos::B3>      GPT01HIZ;
			bit_rw_t <io_, bitpos::B4>      GPT23HIZ;

			bit_rw_t <io_, bitpos::B6>      MTUCH9HIZ;

			bit_rw_t <io_, bitpos::B8>      GPT02HIZ;
			bit_rw_t <io_, bitpos::B9>      GPT46HIZ;
			bit_rw_t <io_, bitpos::B10>     GPT79HIZ;
		};
		typedef spoer_t<base + 0x2E> SPOER_;
		static  SPOER_ SPOER;


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
		typedef poecr1_t<base + 0x0B> POECR1_;
		static  POECR1_ POECR1;


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

			bit_rw_t <io_, bitpos::B0>      MTU7BDZE;
			bit_rw_t <io_, bitpos::B1>      MTU7ACZE;
			bit_rw_t <io_, bitpos::B2>      MTU6BDZE;

			bit_rw_t <io_, bitpos::B8>      MTU4BDZE;
			bit_rw_t <io_, bitpos::B9>      MTU4ACZE;
			bit_rw_t <io_, bitpos::B10>     MTU3BDZE;
		};
		typedef poecr2_t<base + 0x0C> POECR2_;
		static  POECR2_ POECR2;


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
			bit_rw_t <io_, bitpos::B3>      GPT3ABZE;
			bit_rw_t <io_, bitpos::B4>      GPT4ABZE;
			bit_rw_t <io_, bitpos::B5>      GPT5ABZE;
			bit_rw_t <io_, bitpos::B6>      GPT6ABZE;
			bit_rw_t <io_, bitpos::B7>      GPT7ABZE;
		};
		typedef poecr3_t<base + 0x0E> POECR3_;
		static  POECR3_ POECR3;


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

			bit_rw_t <io_, bitpos::B8>      IC8ADDMT34ZE;
		};
		typedef poecr4_t<base + 0x10> POECR4_;
		static  POECR4_ POECR4;





	};
	template <uint32_t base> typename poe3d_base_t<base>::ICSR1_  poe3d_base_t<base>::ICSR1;
	template <uint32_t base> typename poe3d_base_t<base>::ICSR2_  poe3d_base_t<base>::ICSR2;
	template <uint32_t base> typename poe3d_base_t<base>::ICSR3_  poe3d_base_t<base>::ICSR3;
	template <uint32_t base> typename poe3d_base_t<base>::ICSR4_  poe3d_base_t<base>::ICSR4;
	template <uint32_t base> typename poe3d_base_t<base>::ICSR5_  poe3d_base_t<base>::ICSR5;
	template <uint32_t base> typename poe3d_base_t<base>::ICSR6_  poe3d_base_t<base>::ICSR6;
	template <uint32_t base> typename poe3d_base_t<base>::ICSR7_  poe3d_base_t<base>::ICSR7;
	template <uint32_t base> typename poe3d_base_t<base>::ICSR8_  poe3d_base_t<base>::ICSR8;
	template <uint32_t base> typename poe3d_base_t<base>::OCSR1_  poe3d_base_t<base>::OCSR1;
	template <uint32_t base> typename poe3d_base_t<base>::OCSR2_  poe3d_base_t<base>::OCSR2;
	template <uint32_t base> typename poe3d_base_t<base>::OCSR3_  poe3d_base_t<base>::OCSR3;
	template <uint32_t base> typename poe3d_base_t<base>::OCSR4_  poe3d_base_t<base>::OCSR4;
	template <uint32_t base> typename poe3d_base_t<base>::OCSR5_  poe3d_base_t<base>::OCSR5;
	template <uint32_t base> typename poe3d_base_t<base>::ALR1_   poe3d_base_t<base>::ALR1;
	template <uint32_t base> typename poe3d_base_t<base>::ALR2_   poe3d_base_t<base>::ALR2;
	template <uint32_t base> typename poe3d_base_t<base>::ALR3_   poe3d_base_t<base>::ALR3;
	template <uint32_t base> typename poe3d_base_t<base>::ALR4_   poe3d_base_t<base>::ALR4;
	template <uint32_t base> typename poe3d_base_t<base>::ALR5_   poe3d_base_t<base>::ALR5;
	template <uint32_t base> typename poe3d_base_t<base>::SPOER_  poe3d_base_t<base>::SPOER;
	template <uint32_t base> typename poe3d_base_t<base>::POECR1_ poe3d_base_t<base>::POECR1;
	template <uint32_t base> typename poe3d_base_t<base>::POECR2_ poe3d_base_t<base>::POECR2;
	template <uint32_t base> typename poe3d_base_t<base>::POECR3_ poe3d_base_t<base>::POECR3;
	template <uint32_t base> typename poe3d_base_t<base>::POECR4_ poe3d_base_t<base>::POECR4;





#if defined(SIG_RX26T)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポートアウトプットイネーブル 3 (POE3D) クラス
		@param[in]	base	モジュール先頭アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct poe3d_t : public poe3d_base_t<base> {

		static constexpr auto PERIPHERAL = peripheral::POE3D;	///< ペリフェラル型
	};
	typedef poe3d_t<0x0009'E400> POE3D;
#endif
}
