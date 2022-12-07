#pragma once
//=========================================================================//
/*!	@file
	@brief	RX66T/RX72T ポートアウトプットイネーブル 3（POE3B）定義
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
		static constexpr auto OEI5 = ICU::GROUPBL1::OEI5;		///< アウトプットイネーブル割り込み5


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

			bits_rw_t<io_, bitpos::B0, 4>  POE0M;
			bits_rw_t<io_, bitpos::B4, 4>  POE0M2;
			bit_rw_t <io_, bitpos::B8>     PIE1;

			bit_rw_t <io_, bitpos::B12>    POE0F;
		};
		typedef icsr1_t<base + 0x00> ICSR1_;
		static  ICSR1_ ICSR1;


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

			bits_rw_t<io_, bitpos::B0, 4>  POE4M;
			bits_rw_t<io_, bitpos::B4, 4>  POE4M2;
			bit_rw_t <io_, bitpos::B8>     PIE2;

			bit_rw_t <io_, bitpos::B12>    POE4F;
		};
		typedef icsr2_t<base + 0x04> ICSR2_;
		static  ICSR2_ ICSR2;


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

			bits_rw_t<io_, bitpos::B0, 4>  POE8M;
			bits_rw_t<io_, bitpos::B4, 4>  POE8M2;
			bit_rw_t <io_, bitpos::B8>     PIE3;
			bit_rw_t <io_, bitpos::B9>     POE8E;

			bit_rw_t <io_, bitpos::B12>    POE8F;
		};
		typedef icsr3_t<base + 0x08> ICSR3_;
		static  ICSR3_ ICSR3;


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

			bits_rw_t<io_, bitpos::B0, 4>  POE10M;
			bits_rw_t<io_, bitpos::B4, 4>  POE10M2;
			bit_rw_t <io_, bitpos::B8>     PIE4;
			bit_rw_t <io_, bitpos::B9>     POE10E;

			bit_rw_t <io_, bitpos::B12>    POE10F;
		};
		typedef icsr4_t<base + 0x16> ICSR4_;
		static  ICSR4_ ICSR4;


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

			bits_rw_t<io_, bitpos::B0, 4>  POE11M;
			bits_rw_t<io_, bitpos::B4, 4>  POE11M2;
			bit_rw_t <io_, bitpos::B8>     PIE5;
			bit_rw_t <io_, bitpos::B9>     POE11E;

			bit_rw_t <io_, bitpos::B12>    POE11F;
		};
		typedef icsr5_t<base + 0x18> ICSR5_;
		static  ICSR5_ ICSR5;
	

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
		typedef icsr6_t<base + 0x1C> ICSR6_;
		static  ICSR6_ ICSR6;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 7（ICSR7）
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

			bits_rw_t<io_, bitpos::B0, 4>  POE12M;
			bits_rw_t<io_, bitpos::B4, 4>  POE12M2;
			bit_rw_t <io_, bitpos::B8>     PIE7;
			bit_rw_t <io_, bitpos::B9>     POE12E;

			bit_rw_t <io_, bitpos::B12>    POE12F;
		};
		typedef icsr7_t<base + 0x20> ICSR7_;
		static  ICSR7_ ICSR7;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 8（ICSR8）
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

			bits_rw_t<io_, bitpos::B0, 4>  POE9M;
			bits_rw_t<io_, bitpos::B4, 4>  POE9M2;
			bit_rw_t <io_, bitpos::B8>     PIE8;
			bit_rw_t <io_, bitpos::B9>     POE9E;

			bit_rw_t <io_, bitpos::B12>    POE9F;
		};
		typedef icsr8_t<base + 0x40> ICSR8_;
		static  ICSR8_ ICSR8;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 9（ICSR9）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct icsr9_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  POE13M;
			bits_rw_t<io_, bitpos::B4, 4>  POE13M2;
			bit_rw_t <io_, bitpos::B8>     PIE9;
			bit_rw_t <io_, bitpos::B9>     POE13E;

			bit_rw_t <io_, bitpos::B12>    POE13F;
		};
		typedef icsr9_t<base + 0x42> ICSR9_;
		static  ICSR9_ ICSR9;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 10（ICSR10）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct icsr10_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  POE14M;
			bits_rw_t<io_, bitpos::B4, 4>  POE14M2;
			bit_rw_t <io_, bitpos::B8>     PIE7;
			bit_rw_t <io_, bitpos::B9>     POE14E;

			bit_rw_t <io_, bitpos::B12>    POE14F;
		};
		typedef icsr10_t<base + 0x44> ICSR10_;
		static  ICSR10_ ICSR10;


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
		typedef ocsr1_t<base + 0x02> OCSR1_;
		static  OCSR1_ OCSR1;


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
		typedef ocsr2_t<base + 0x06> OCSR2_;
		static  OCSR2_ OCSR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	出力レベルコントロール / ステータスレジスタ 3（OCSR3）
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

			bit_rw_t<io_, bitpos::B8>   OIE3;
			bit_rw_t<io_, bitpos::B9>   OCE3;

			bit_rw_t<io_, bitpos::B15>  OSF3;
		};
		typedef ocsr3_t<base + 0x2A> OCSR3_;
		static  OCSR3_ OCSR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	出力レベルコントロール / ステータスレジスタ 4（OCSR4）
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

			bit_rw_t<io_, bitpos::B8>   OIE4;
			bit_rw_t<io_, bitpos::B9>   OCE4;

			bit_rw_t<io_, bitpos::B15>  OSF4;
		};
		typedef ocsr4_t<base + 0x46> OCSR4_;
		static  OCSR4_ OCSR4;


		//-----------------------------------------------------------------//
		/*!
			@brief	出力レベルコントロール / ステータスレジスタ 5（OCSR5）
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

			bit_rw_t<io_, bitpos::B8>   OIE5;
			bit_rw_t<io_, bitpos::B9>   OCE5;

			bit_rw_t<io_, bitpos::B15>  OSF5;
		};
		typedef ocsr5_t<base + 0x48> OCSR5_;
		static  OCSR5_ OCSR5;


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
		typedef alr1_t<base + 0x1A> ALR1_;
		static  ALR1_ ALR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	アクティブレベルレジスタ 2（ALR2）
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

			bit_rw_t<io_, bitpos::B0>  OLSG4A;
			bit_rw_t<io_, bitpos::B1>  OLSG4B;
			bit_rw_t<io_, bitpos::B2>  OLSG5A;
			bit_rw_t<io_, bitpos::B3>  OLSG5B;
			bit_rw_t<io_, bitpos::B4>  OLSG6A;
			bit_rw_t<io_, bitpos::B5>  OLSG6B;

			bit_rw_t<io_, bitpos::B7>  OLSEN;
		};
		typedef alr2_t<base + 0x1E> ALR2_;
		static  ALR2_ ALR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	アクティブレベルレジスタ 3（ALR3）
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

			bit_rw_t<io_, bitpos::B0>  OLSG0A;
			bit_rw_t<io_, bitpos::B1>  OLSG0B;
			bit_rw_t<io_, bitpos::B2>  OLSG1A;
			bit_rw_t<io_, bitpos::B3>  OLSG1B;
			bit_rw_t<io_, bitpos::B4>  OLSG2A;
			bit_rw_t<io_, bitpos::B5>  OLSG2B;

			bit_rw_t<io_, bitpos::B7>  OLSEN;
		};
		typedef alr3_t<base + 0x2C> ALR3_;
		static  ALR3_ ALR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	アクティブレベルレジスタ 4（ALR4）
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

			bit_rw_t<io_, bitpos::B0>  OLSG0A;
			bit_rw_t<io_, bitpos::B1>  OLSG0B;
			bit_rw_t<io_, bitpos::B2>  OLSG1A;
			bit_rw_t<io_, bitpos::B3>  OLSG1B;
			bit_rw_t<io_, bitpos::B4>  OLSG2A;
			bit_rw_t<io_, bitpos::B5>  OLSG2B;

			bit_rw_t<io_, bitpos::B7>  OLSEN;
		};
		typedef alr4_t<base + 0x4A> ALR4_;
		static  ALR4_ ALR4;


		//-----------------------------------------------------------------//
		/*!
			@brief	アクティブレベルレジスタ 5（ALR5）
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

			bit_rw_t<io_, bitpos::B0>  OLSG0A;
			bit_rw_t<io_, bitpos::B1>  OLSG0B;
			bit_rw_t<io_, bitpos::B2>  OLSG1A;
			bit_rw_t<io_, bitpos::B3>  OLSG1B;
			bit_rw_t<io_, bitpos::B4>  OLSG2A;
			bit_rw_t<io_, bitpos::B5>  OLSG2B;

			bit_rw_t<io_, bitpos::B7>  OLSEN;
		};
		typedef alr5_t<base + 0x4C> ALR5_;
		static  ALR5_ ALR5;


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
			bit_rw_t<io_, bitpos::B3>  GPT01HIZ;
			bit_rw_t<io_, bitpos::B4>  GPT23HIZ;

			bit_rw_t<io_, bitpos::B6>  MTUCH9HIZ;

			bit_rw_t<io_, bitpos::B8>  GPT02HIZ;
			bit_rw_t<io_, bitpos::B9>  GPT46HIZ;
			bit_rw_t<io_, bitpos::B10> GPT79HIZ;
		};
		typedef spoer_t<base + 0x0A> SPOER_;
		static  SPOER_ SPOER;


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
		typedef poecr1_t<base + 0x0B> POECR1_;
		static  POECR1_ POECR1;


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
		typedef poecr2_t<base + 0x0C> POECR2_;
		static  POECR2_ POECR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 3（POECR3）
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

			bit_rw_t<io_, bitpos::B0>   GPT0ABZE;
			bit_rw_t<io_, bitpos::B1>   GPT1ABZE;
			bit_rw_t<io_, bitpos::B2>   GPT2ABZE;
			bit_rw_t<io_, bitpos::B3>   GPT3ABZE;
			bit_rw_t<io_, bitpos::B4>   GPT4ABZE;
			bit_rw_t<io_, bitpos::B5>   GPT5ABZE;
			bit_rw_t<io_, bitpos::B6>   GPT6ABZE;
			bit_rw_t<io_, bitpos::B7>   GPT7ABZE;
			bit_rw_t<io_, bitpos::B8>   GPT8ABZE;
			bit_rw_t<io_, bitpos::B9>   GPT9ABZE;
		};
		typedef poecr3_t<base + 0x0E> POECR3_;
		static  POECR3_ POECR3;


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

			bit_rw_t<io_, bitpos::B0>  CMADDMT34ZE;
			bit_rw_t<io_, bitpos::B2>  IC1ADDMT34ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDMT34ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDMT34ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDMT34ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT34ZE;
			bit_rw_t<io_, bitpos::B6>  IC6ADDMT34ZE;

			bit_rw_t<io_, bitpos::B8>  IC8ADDMT34ZE;
			bit_rw_t<io_, bitpos::B9>  IC9ADDMT34ZE;
			bit_rw_t<io_, bitpos::B10> IC10ADDMT34ZE;
		};
		typedef poecr4_t<base + 0x10> POECR4_;
		static  POECR4_ POECR4;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 4B（POECR4B）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr4B_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMADDMT67ZE;
			bit_rw_t<io_, bitpos::B2>  IC1ADDMT67ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDMT67ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDMT67ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDMT67ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT67ZE;
			bit_rw_t<io_, bitpos::B6>  IC6ADDMT67ZE;

			bit_rw_t<io_, bitpos::B8>  IC8ADDMT67ZE;
			bit_rw_t<io_, bitpos::B9>  IC9ADDMT67ZE;
			bit_rw_t<io_, bitpos::B10> IC10ADDMT67ZE;
		};
		typedef poecr4B_t<base + 0x4E> POECR4B_;
		static  POECR4B_ POECR4B;


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

			bit_rw_t<io_, bitpos::B0>  CMADDMT0ZE;
			bit_rw_t<io_, bitpos::B1>  IC1ADDMT0ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDMT0ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDMT0ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDMT0ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT0ZE;
			bit_rw_t<io_, bitpos::B6>  IC6ADDMT0ZE;

			bit_rw_t<io_, bitpos::B8>  IC8ADDMT0ZE;
			bit_rw_t<io_, bitpos::B9>  IC9ADDMT0ZE;
			bit_rw_t<io_, bitpos::B10> IC10ADDMT0ZE;
		};
		typedef poecr5_t<base + 0x12> POECR5_;
		static  POECR5_ POECR5;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 6（POECR6）
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

			bit_rw_t<io_, bitpos::B0>  CMADDGPT01ZE;
			bit_rw_t<io_, bitpos::B1>  IC1ADDGPT01ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDGPT01ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDGPT01ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDGPT01ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDGPT01ZE;
			bit_rw_t<io_, bitpos::B6>  IC6ADDGPT01ZE;

			bit_rw_t<io_, bitpos::B8>  IC8ADDGPT01ZE;
			bit_rw_t<io_, bitpos::B9>  IC9ADDGPT01ZE;
			bit_rw_t<io_, bitpos::B10> IC10ADDGPT01ZE;
		};
		typedef poecr6_t<base + 0x14> POECR6_;
		static  POECR6_ POECR6;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 6B（POECR6B）
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

			bit_rw_t<io_, bitpos::B0>  CMADDGPT23ZE;
			bit_rw_t<io_, bitpos::B1>  IC1ADDGPT23ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDGPT23ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDGPT23ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDGPT23ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDGPT23ZE;
			bit_rw_t<io_, bitpos::B6>  IC6ADDGPT23ZE;

			bit_rw_t<io_, bitpos::B8>  IC8ADDGPT23ZE;
			bit_rw_t<io_, bitpos::B9>  IC9ADDGPT23ZE;
			bit_rw_t<io_, bitpos::B10> IC10ADDGPT23ZE;
		};
		typedef poecr6b_t<base + 0x50> POECR6B_;
		static  POECR6B_ POECR6B;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 7（POECR7）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr7_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MTU9AZE;
			bit_rw_t<io_, bitpos::B1>  MTU9BZE;
			bit_rw_t<io_, bitpos::B2>  MTU9CZE;
			bit_rw_t<io_, bitpos::B3>  MTU9DZE;
		};
		typedef poecr7_t<base + 0x22> POECR7_;
		static  POECR7_ POECR7;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 8（POECR8）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr8_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMADDMT9ZE;
			bit_rw_t<io_, bitpos::B1>  IC1ADDMT9ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDMT9ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDMT9ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDMT9ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT9ZE;
			bit_rw_t<io_, bitpos::B6>  IC6ADDMT9ZE;

			bit_rw_t<io_, bitpos::B8>  IC8ADDMT9ZE;
			bit_rw_t<io_, bitpos::B9>  IC9ADDMT9ZE;
			bit_rw_t<io_, bitpos::B10> IC10ADDMT9ZE;
		};
		typedef poecr8_t<base + 0x24> POECR8_;
		static  POECR8_ POECR8;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 9（POECR9）
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

			bit_rw_t<io_, bitpos::B0>  CMADDGPT02ZE;
			bit_rw_t<io_, bitpos::B1>  IC1ADDGPT02ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDGPT02ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDGPT02ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDGPT02ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDGPT02ZE;
			bit_rw_t<io_, bitpos::B6>  IC6ADDGPT02ZE;

			bit_rw_t<io_, bitpos::B8>  IC8ADDGPT02ZE;
			bit_rw_t<io_, bitpos::B9>  IC9ADDGPT02ZE;
			bit_rw_t<io_, bitpos::B10> IC10ADDGPT02ZE;
		};
		typedef poecr9_t<base + 0x52> POECR9_;
		static  POECR9_ POECR9;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 10（POECR10）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr10_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMADDGPT46ZE;
			bit_rw_t<io_, bitpos::B1>  IC1ADDGPT46ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDGPT46ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDGPT46ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDGPT46ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDGPT46ZE;
			bit_rw_t<io_, bitpos::B6>  IC6ADDGPT46ZE;

			bit_rw_t<io_, bitpos::B8>  IC8ADDGPT46ZE;
			bit_rw_t<io_, bitpos::B9>  IC9ADDGPT46ZE;
			bit_rw_t<io_, bitpos::B10> IC10ADDGPT46ZE;
		};
		typedef poecr10_t<base + 0x54> POECR10_;
		static  POECR10_ POECR10;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 11（POECR11）
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecr11_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMADDGPT79ZE;
			bit_rw_t<io_, bitpos::B1>  IC1ADDGPT79ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDGPT79ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDGPT79ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDGPT79ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDGPT79ZE;
			bit_rw_t<io_, bitpos::B6>  IC6ADDGPT79ZE;

			bit_rw_t<io_, bitpos::B8>  IC8ADDGPT79ZE;
			bit_rw_t<io_, bitpos::B9>  IC9ADDGPT79ZE;
			bit_rw_t<io_, bitpos::B10> IC10ADDGPT79ZE;
		};
		typedef poecr11_t<base + 0x56> POECR11_;
		static  POECR11_ POECR11;


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

			bit_rw_t<io_, bitpos::B0>  MTU0AME;
			bit_rw_t<io_, bitpos::B1>  MTU0BME;
			bit_rw_t<io_, bitpos::B2>  MTU0CME;
			bit_rw_t<io_, bitpos::B3>  MTU0DME;

			bit_rw_t<io_, bitpos::B4>  MTU9AME;
			bit_rw_t<io_, bitpos::B5>  MTU9BME;
			bit_rw_t<io_, bitpos::B6>  MTU9CME;
			bit_rw_t<io_, bitpos::B7>  MTU9DME;
		};
		typedef pmmcr0_t<base + 0x30> PMMCR0_;
		static  PMMCR0_ PMMCR0;


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

			bit_rw_t<io_, bitpos::B0>  MTU7BME;
			bit_rw_t<io_, bitpos::B1>  MTU7AME;
			bit_rw_t<io_, bitpos::B2>  MTU6BME;
			bit_rw_t<io_, bitpos::B3>  MTU7DME;
			bit_rw_t<io_, bitpos::B4>  MTU7CME;
			bit_rw_t<io_, bitpos::B5>  MTU6DME;

			bit_rw_t<io_, bitpos::B8>  MTU4BME;
			bit_rw_t<io_, bitpos::B9>  MTU4AME;
			bit_rw_t<io_, bitpos::B10> MTU3BME;
			bit_rw_t<io_, bitpos::B11> MTU4DME;
			bit_rw_t<io_, bitpos::B12> MTU4CME;
			bit_rw_t<io_, bitpos::B13> MTU3DME;
		};
		typedef pmmcr1_t<base + 0x32> PMMCR1_;
		static  PMMCR1_ PMMCR1;


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

			bit_rw_t<io_, bitpos::B0>  GPT0AME;
			bit_rw_t<io_, bitpos::B1>  GPT0BME;
			bit_rw_t<io_, bitpos::B2>  GPT1AME;
			bit_rw_t<io_, bitpos::B3>  GPT1BME;
			bit_rw_t<io_, bitpos::B4>  GPT2AME;
			bit_rw_t<io_, bitpos::B5>  GPT2BME;
			bit_rw_t<io_, bitpos::B6>  GPT3AME;
			bit_rw_t<io_, bitpos::B7>  GPT3BME;
			bit_rw_t<io_, bitpos::B8>  GPT4AME;
			bit_rw_t<io_, bitpos::B9>  GPT4BME;
			bit_rw_t<io_, bitpos::B10> GPT5AME;
			bit_rw_t<io_, bitpos::B11> GPT5BME;
			bit_rw_t<io_, bitpos::B12> GPT6AME;
			bit_rw_t<io_, bitpos::B13> GPT6BME;
			bit_rw_t<io_, bitpos::B14> GPT7AME;
			bit_rw_t<io_, bitpos::B15> GPT7BME;
		};
		typedef pmmcr2_t<base + 0x34> PMMCR2_;
		static  PMMCR2_ PMMCR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートモードマスクコントロールレジスタ 3 (PMMCR3)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct pmmcr3_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  GPT8AME;
			bit_rw_t<io_, bitpos::B1>  GPT8BME;
			bit_rw_t<io_, bitpos::B2>  GPT9AME;
			bit_rw_t<io_, bitpos::B3>  GPT9BME;
		};
		typedef pmmcr3_t<base + 0x36> PMMCR3_;
		static  PMMCR3_ PMMCR3;


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

			bit_rw_t<io_, bitpos::B0>  C0FLAG;
			bit_rw_t<io_, bitpos::B1>  C1FLAG;
			bit_rw_t<io_, bitpos::B2>  C2FLAG;
			bit_rw_t<io_, bitpos::B3>  C3FLAG;
			bit_rw_t<io_, bitpos::B4>  C4FLAG;
			bit_rw_t<io_, bitpos::B5>  C5FLAG;
		};
		typedef poecmpfr_t<base + 0x26> POECMPFR_;
		static  POECMPFR_ POECMPFR;


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

			bit_rw_t<io_, bitpos::B0>  POEREQ0;
			bit_rw_t<io_, bitpos::B1>  POEREQ1;
			bit_rw_t<io_, bitpos::B2>  POEREQ2;
			bit_rw_t<io_, bitpos::B3>  POEREQ3;
			bit_rw_t<io_, bitpos::B4>  POEREQ4;
			bit_rw_t<io_, bitpos::B5>  POEREQ5;
		};
		typedef poecmpsel_t<base + 0x28> POECMPSEL_;
		static  POECMPSEL_ POECMPSEL;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコンパレータ要求拡張選択レジスタ m @n
					(POECMPEXm) (m = 0 ～ 8)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct poecmpexm_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  POEREQ0;
			bit_rw_t<io_, bitpos::B1>  POEREQ1;
			bit_rw_t<io_, bitpos::B2>  POEREQ2;
			bit_rw_t<io_, bitpos::B3>  POEREQ3;
			bit_rw_t<io_, bitpos::B4>  POEREQ4;
			bit_rw_t<io_, bitpos::B5>  POEREQ5;
		};
		typedef poecmpexm_t<base + 0x38> POECMPEX0_;
		static  POECMPEX0_ POECMPEX0;
		typedef poecmpexm_t<base + 0x39> POECMPEX1_;
		static  POECMPEX1_ POECMPEX1;
		typedef poecmpexm_t<base + 0x3A> POECMPEX2_;
		static  POECMPEX2_ POECMPEX2;
		typedef poecmpexm_t<base + 0x3B> POECMPEX3_;
		static  POECMPEX3_ POECMPEX3;
		typedef poecmpexm_t<base + 0x3C> POECMPEX4_;
		static  POECMPEX4_ POECMPEX4;
		typedef poecmpexm_t<base + 0x3D> POECMPEX5_;
		static  POECMPEX5_ POECMPEX5;
		typedef poecmpexm_t<base + 0x58> POECMPEX6_;
		static  POECMPEX6_ POECMPEX6;
		typedef poecmpexm_t<base + 0x59> POECMPEX7_;
		static  POECMPEX7_ POECMPEX7;
		typedef poecmpexm_t<base + 0x5A> POECMPEX8_;
		static  POECMPEX8_ POECMPEX8;


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

			bits_rw_t<io_, bitpos::B0, 4>  M0ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  M0BSEL;
		};
		typedef m0selr1_t<base + 0x60> M0SELR1_;
		static  M0SELR1_ M0SELR1;


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

			bits_rw_t<io_, bitpos::B0, 4>  M0CSEL;
			bits_rw_t<io_, bitpos::B4, 4>  M0DSEL;
		};
		typedef m0selr2_t<base + 0x61> M0SELR2_;
		static  M0SELR2_ M0SELR2;


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

			bits_rw_t<io_, bitpos::B0, 4>  M3BSEL;
			bits_rw_t<io_, bitpos::B4, 4>  M3DSEL;
		};
		typedef m3selr_t<base + 0x62> M3SELR_;
		static  M3SELR_ M3SELR;


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

			bits_rw_t<io_, bitpos::B0, 4>  M4ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  M4CSEL;
		};
		typedef m4selr1_t<base + 0x63> M4SELR1_;
		static  M4SELR1_ M4SELR1;


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

			bits_rw_t<io_, bitpos::B0, 4>  M4BSEL;
			bits_rw_t<io_, bitpos::B4, 4>  M4DSEL;
		};
		typedef m4selr2_t<base + 0x64> M4SELR2_;
		static  M4SELR2_ M4SELR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU6 端子選択レジスタ (M6SELR)
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
		typedef m6selr_t<base + 0x65> M6SELR_;
		static  M6SELR_ M6SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU7 端子選択レジスタ 1 (M7SELR1)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct m7selr1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M7ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  M7CSEL;
		};
		typedef m7selr1_t<base + 0x66> M7SELR1_;
		static  M7SELR1_ M7SELR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU7 端子選択レジスタ 2 (M7SELR2)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct m7selr2_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M7BSEL;
			bits_rw_t<io_, bitpos::B4, 4>  M7DSEL;
		};
		typedef m7selr2_t<base + 0x67> M7SELR2_;
		static  M7SELR2_ M7SELR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU9 端子選択レジスタ 1 (M9SELR1)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct m9selr1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M9ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  M9CSEL;
		};
		typedef m9selr1_t<base + 0x68> M9SELR1_;
		static  M9SELR1_ M9SELR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU9 端子選択レジスタ 2 (M9SELR2)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct m9selr2_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M9BSEL;
			bits_rw_t<io_, bitpos::B4, 4>  M9DSEL;
		};
		typedef m9selr2_t<base + 0x69> M9SELR2_;
		static  M9SELR2_ M9SELR2;
	

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

			bits_rw_t<io_, bitpos::B0, 4>  G0ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G0BSEL;
		};
		typedef g0selr_t<base + 0x6A> G0SELR_;
		static  G0SELR_ G0SELR;


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

			bits_rw_t<io_, bitpos::B0, 4>  G1ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G1BSEL;
		};
		typedef g1selr_t<base + 0x6B> G1SELR_;
		static  G1SELR_ G1SELR;


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

			bits_rw_t<io_, bitpos::B0, 4>  G2ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G2BSEL;
		};
		typedef g2selr_t<base + 0x6C> G2SELR_;
		static  G2SELR_ G2SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPTW3 端子選択レジスタ (G3SELR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct g3selr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G3ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G3BSEL;
		};
		typedef g3selr_t<base + 0x6D> G3SELR_;
		static  G3SELR_ G3SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPTW4 端子選択レジスタ (G4SELR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct g4selr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G4ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G4BSEL;
		};
		typedef g4selr_t<base + 0x6E> G4SELR_;
		static  G4SELR_ G4SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPTW5 端子選択レジスタ (G5SELR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct g5selr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G5ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G5BSEL;
		};
		typedef g5selr_t<base + 0x6F> G5SELR_;
		static  G5SELR_ G5SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPTW6 端子選択レジスタ (G6SELR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct g6selr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G6ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G6BSEL;
		};
		typedef g6selr_t<base + 0x70> G6SELR_;
		static  G6SELR_ G6SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPTW7 端子選択レジスタ (G7SELR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct g7selr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G7ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G7BSEL;
		};
		typedef g7selr_t<base + 0x71> G7SELR_;
		static  G7SELR_ G7SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPTW8 端子選択レジスタ (G8SELR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct g8selr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G8ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G8BSEL;
		};
		typedef g8selr_t<base + 0x72> G8SELR_;
		static  G8SELR_ G8SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPTW9 端子選択レジスタ (G9SELR)
			@param[in]	ofs		オフセット
		*/
		//-----------------------------------------------------------------//
		template <uint32_t ofs>
		struct g9selr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G9ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G9BSEL;
		};
		typedef g9selr_t<base + 0x73> G9SELR_;
		static  G9SELR_ G9SELR;
	};
	template <uint32_t base> typename poe3_t<base>::ICSR1_ poe3_t<base>::ICSR1;
	template <uint32_t base> typename poe3_t<base>::ICSR2_ poe3_t<base>::ICSR2;
	template <uint32_t base> typename poe3_t<base>::ICSR3_ poe3_t<base>::ICSR3;
	template <uint32_t base> typename poe3_t<base>::ICSR4_ poe3_t<base>::ICSR4;
	template <uint32_t base> typename poe3_t<base>::ICSR5_ poe3_t<base>::ICSR5;
	template <uint32_t base> typename poe3_t<base>::ICSR6_ poe3_t<base>::ICSR6;
	template <uint32_t base> typename poe3_t<base>::ICSR7_ poe3_t<base>::ICSR7;
	template <uint32_t base> typename poe3_t<base>::ICSR8_ poe3_t<base>::ICSR8;
	template <uint32_t base> typename poe3_t<base>::ICSR9_ poe3_t<base>::ICSR9;
	template <uint32_t base> typename poe3_t<base>::ICSR10_ poe3_t<base>::ICSR10;
	template <uint32_t base> typename poe3_t<base>::OCSR1_ poe3_t<base>::OCSR1;
	template <uint32_t base> typename poe3_t<base>::OCSR2_ poe3_t<base>::OCSR2;
	template <uint32_t base> typename poe3_t<base>::OCSR3_ poe3_t<base>::OCSR3;
	template <uint32_t base> typename poe3_t<base>::OCSR4_ poe3_t<base>::OCSR4;
	template <uint32_t base> typename poe3_t<base>::OCSR5_ poe3_t<base>::OCSR5;
	template <uint32_t base> typename poe3_t<base>::ALR1_ poe3_t<base>::ALR1;
	template <uint32_t base> typename poe3_t<base>::ALR2_ poe3_t<base>::ALR2;
	template <uint32_t base> typename poe3_t<base>::ALR3_ poe3_t<base>::ALR3;
	template <uint32_t base> typename poe3_t<base>::ALR4_ poe3_t<base>::ALR4;
	template <uint32_t base> typename poe3_t<base>::ALR5_ poe3_t<base>::ALR5;
	template <uint32_t base> typename poe3_t<base>::SPOER_ poe3_t<base>::SPOER;
	template <uint32_t base> typename poe3_t<base>::POECR1_ poe3_t<base>::POECR1;
	template <uint32_t base> typename poe3_t<base>::POECR2_ poe3_t<base>::POECR2;
	template <uint32_t base> typename poe3_t<base>::POECR3_ poe3_t<base>::POECR3;
	template <uint32_t base> typename poe3_t<base>::POECR4_ poe3_t<base>::POECR4;
	template <uint32_t base> typename poe3_t<base>::POECR4B_ poe3_t<base>::POECR4B;
	template <uint32_t base> typename poe3_t<base>::POECR5_ poe3_t<base>::POECR5;
	template <uint32_t base> typename poe3_t<base>::POECR6_ poe3_t<base>::POECR6;
	template <uint32_t base> typename poe3_t<base>::POECR6B_ poe3_t<base>::POECR6B;
	template <uint32_t base> typename poe3_t<base>::POECR7_ poe3_t<base>::POECR7;
	template <uint32_t base> typename poe3_t<base>::POECR8_ poe3_t<base>::POECR8;
	template <uint32_t base> typename poe3_t<base>::POECR9_ poe3_t<base>::POECR9;
	template <uint32_t base> typename poe3_t<base>::POECR10_ poe3_t<base>::POECR10;
	template <uint32_t base> typename poe3_t<base>::POECR11_ poe3_t<base>::POECR11;
	template <uint32_t base> typename poe3_t<base>::PMMCR0_ poe3_t<base>::PMMCR0;
	template <uint32_t base> typename poe3_t<base>::PMMCR1_ poe3_t<base>::PMMCR1;
	template <uint32_t base> typename poe3_t<base>::PMMCR2_ poe3_t<base>::PMMCR2;
	template <uint32_t base> typename poe3_t<base>::PMMCR3_ poe3_t<base>::PMMCR3;
	template <uint32_t base> typename poe3_t<base>::POECMPFR_ poe3_t<base>::POECMPFR;
	template <uint32_t base> typename poe3_t<base>::POECMPSEL_ poe3_t<base>::POECMPSEL;
	template <uint32_t base> typename poe3_t<base>::POECMPEX0_ poe3_t<base>::POECMPEX0;
	template <uint32_t base> typename poe3_t<base>::POECMPEX1_ poe3_t<base>::POECMPEX1;
	template <uint32_t base> typename poe3_t<base>::POECMPEX2_ poe3_t<base>::POECMPEX2;
	template <uint32_t base> typename poe3_t<base>::POECMPEX3_ poe3_t<base>::POECMPEX3;
	template <uint32_t base> typename poe3_t<base>::POECMPEX4_ poe3_t<base>::POECMPEX4;
	template <uint32_t base> typename poe3_t<base>::POECMPEX5_ poe3_t<base>::POECMPEX5;
	template <uint32_t base> typename poe3_t<base>::POECMPEX6_ poe3_t<base>::POECMPEX6;
	template <uint32_t base> typename poe3_t<base>::POECMPEX7_ poe3_t<base>::POECMPEX7;
	template <uint32_t base> typename poe3_t<base>::POECMPEX8_ poe3_t<base>::POECMPEX8;
	template <uint32_t base> typename poe3_t<base>::M0SELR1_ poe3_t<base>::M0SELR1;
	template <uint32_t base> typename poe3_t<base>::M0SELR2_ poe3_t<base>::M0SELR2;
	template <uint32_t base> typename poe3_t<base>::M3SELR_ poe3_t<base>::M3SELR;
	template <uint32_t base> typename poe3_t<base>::M4SELR1_ poe3_t<base>::M4SELR1;
	template <uint32_t base> typename poe3_t<base>::M4SELR2_ poe3_t<base>::M4SELR2;
	template <uint32_t base> typename poe3_t<base>::M6SELR_ poe3_t<base>::M6SELR;
	template <uint32_t base> typename poe3_t<base>::M7SELR1_ poe3_t<base>::M7SELR1;
	template <uint32_t base> typename poe3_t<base>::M7SELR2_ poe3_t<base>::M7SELR2;
	template <uint32_t base> typename poe3_t<base>::M9SELR1_ poe3_t<base>::M9SELR1;
	template <uint32_t base> typename poe3_t<base>::M9SELR2_ poe3_t<base>::M9SELR2;
	template <uint32_t base> typename poe3_t<base>::G0SELR_ poe3_t<base>::G0SELR;
	template <uint32_t base> typename poe3_t<base>::G1SELR_ poe3_t<base>::G1SELR;
	template <uint32_t base> typename poe3_t<base>::G2SELR_ poe3_t<base>::G2SELR;
	template <uint32_t base> typename poe3_t<base>::G3SELR_ poe3_t<base>::G3SELR;
	template <uint32_t base> typename poe3_t<base>::G4SELR_ poe3_t<base>::G4SELR;
	template <uint32_t base> typename poe3_t<base>::G5SELR_ poe3_t<base>::G5SELR;
	template <uint32_t base> typename poe3_t<base>::G6SELR_ poe3_t<base>::G6SELR;
	template <uint32_t base> typename poe3_t<base>::G7SELR_ poe3_t<base>::G7SELR;
	template <uint32_t base> typename poe3_t<base>::G8SELR_ poe3_t<base>::G8SELR;
	template <uint32_t base> typename poe3_t<base>::G9SELR_ poe3_t<base>::G9SELR;


	typedef poe3_t<0x0009'E400> POE3;
}
