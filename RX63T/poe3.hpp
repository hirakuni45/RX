#pragma once
//=========================================================================//
/*!	@file
	@brief	RX63T ポートアウトプットイネーブル 3（POE3）定義
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
		static constexpr auto OEI1 = ICU::VECTOR::OEI1;			///< アウトプットイネーブル割り込み1
		static constexpr auto OEI2 = ICU::VECTOR::OEI2;			///< アウトプットイネーブル割り込み2
		static constexpr auto OEI3 = ICU::VECTOR::OEI3;			///< アウトプットイネーブル割り込み3
		static constexpr auto OEI4 = ICU::VECTOR::OEI4;			///< アウトプットイネーブル割り込み4
		static constexpr auto OEI5 = ICU::VECTOR::OEI5;			///< アウトプットイネーブル割り込み5


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

			bits_rw_t<io_, bitpos::B0, 2>  POE4M;

			bit_rw_t <io_, bitpos::B8>     PIE2;
			bit_rw_t <io_, bitpos::B12>    POE4F;
		};
		typedef icsr2_t<base + 0x04> ICSR2_;
		static  ICSR2_ ICSR2;


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
			bit_rw_t<io_, bitpos::B8>  MTUCHSEL;
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

			bits_rw_t<io_, bitpos::B0, 2>  POE10M;

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

			bits_rw_t<io_, bitpos::B0, 2>  POE11M;

			bit_rw_t <io_, bitpos::B8>     PIE5;
			bit_rw_t <io_, bitpos::B9>     POE11E;

			bit_rw_t <io_, bitpos::B12>    POE11F;
		};
		typedef icsr5_t<base + 0x18> ICSR5_;
		static  ICSR5_ ICSR5;


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

			bits_rw_t<io_, bitpos::B0, 2>  POE12M;

			bit_rw_t <io_, bitpos::B8>     PIE7;
			bit_rw_t <io_, bitpos::B9>     POE12E;

			bit_rw_t <io_, bitpos::B12>    POE12F;
		};
		typedef icsr7_t<base + 0x20> ICSR7_;
		static  ICSR7_ ICSR7;


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

			bit_rw_t<io_, bitpos::B6>  GPT67HIZ;
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

			bit_rw_t<io_, bitpos::B8>   GPT2ABZE;
			bit_rw_t<io_, bitpos::B9>   GPT3ABZE;
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

			bit_rw_t<io_, bitpos::B2>  IC2ADDMT34ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDMT34ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDMT34ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT34ZE;
			bit_rw_t<io_, bitpos::B6>  IC6ADDMT34ZE;

			bit_rw_t<io_, bitpos::B8>  CMADDMT67ZE;
			bit_rw_t<io_, bitpos::B9>  IC1ADDMT67ZE;

			bit_rw_t<io_, bitpos::B11> IC3ADDMT67ZE;
			bit_rw_t<io_, bitpos::B12> IC4ADDMT67ZE;
			bit_rw_t<io_, bitpos::B13> IC5ADDMT67ZE;
			bit_rw_t<io_, bitpos::B14> IC6ADDMT67ZE;
		};
		typedef poecr4_t<base + 0x10> POECR4_;
		static  POECR4_ POECR4;


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

			bit_rw_t<io_, bitpos::B4>  IC4ADDMT0ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT0ZE;
			bit_rw_t<io_, bitpos::B6>  IC6ADDMT0ZE;
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

			bit_rw_t<io_, bitpos::B5>  IC5ADDGPT01ZE;
			bit_rw_t<io_, bitpos::B6>  IC6ADDGPT01ZE;

			bit_rw_t<io_, bitpos::B8>  CMADDGPT23ZE;
			bit_rw_t<io_, bitpos::B9>  IC1ADDGPT23ZE;
			bit_rw_t<io_, bitpos::B10> IC2ADDGPT23ZE;
			bit_rw_t<io_, bitpos::B11> IC3ADDGPT23ZE;
			bit_rw_t<io_, bitpos::B12> IC4ADDGPT23ZE;

			bit_rw_t<io_, bitpos::B14> IC6ADDGPT23ZE;
		};
		typedef poecr6_t<base + 0x14> POECR6_;
		static  POECR6_ POECR6;


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

			bit_rw_t<io_, bitpos::B8>  GPT6ABZE;
			bit_rw_t<io_, bitpos::B9>  GPT7ABZE;
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

			bit_rw_t<io_, bitpos::B0>  CMADDGPT6ZE;
			bit_rw_t<io_, bitpos::B1>  IC1ADDGPT67ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDGPT67ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDGPT67ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDGPT67ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDGPT67ZE;
		};
		typedef poecr8_t<base + 0x24> POECR8_;
		static  POECR8_ POECR8;


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
	};
	template <uint32_t base> typename poe3_t<base>::ICSR1_ poe3_t<base>::ICSR1;
	template <uint32_t base> typename poe3_t<base>::ICSR2_ poe3_t<base>::ICSR2;
	template <uint32_t base> typename poe3_t<base>::OCSR1_ poe3_t<base>::OCSR1;
	template <uint32_t base> typename poe3_t<base>::OCSR2_ poe3_t<base>::OCSR2;
	template <uint32_t base> typename poe3_t<base>::ALR1_ poe3_t<base>::ALR1;
	template <uint32_t base> typename poe3_t<base>::ALR2_ poe3_t<base>::ALR2;
	template <uint32_t base> typename poe3_t<base>::ICSR3_ poe3_t<base>::ICSR3;
	template <uint32_t base> typename poe3_t<base>::ICSR4_ poe3_t<base>::ICSR4;
	template <uint32_t base> typename poe3_t<base>::ICSR5_ poe3_t<base>::ICSR5;
	template <uint32_t base> typename poe3_t<base>::ICSR7_ poe3_t<base>::ICSR7;
	template <uint32_t base> typename poe3_t<base>::SPOER_ poe3_t<base>::SPOER;
	template <uint32_t base> typename poe3_t<base>::POECR1_ poe3_t<base>::POECR1;
	template <uint32_t base> typename poe3_t<base>::POECR2_ poe3_t<base>::POECR2;
	template <uint32_t base> typename poe3_t<base>::POECR3_ poe3_t<base>::POECR3;
	template <uint32_t base> typename poe3_t<base>::POECR4_ poe3_t<base>::POECR4;
	template <uint32_t base> typename poe3_t<base>::POECR5_ poe3_t<base>::POECR5;
	template <uint32_t base> typename poe3_t<base>::POECR6_ poe3_t<base>::POECR6;
	template <uint32_t base> typename poe3_t<base>::POECR7_ poe3_t<base>::POECR7;
	template <uint32_t base> typename poe3_t<base>::POECR8_ poe3_t<base>::POECR8;
	template <uint32_t base> typename poe3_t<base>::ICSR6_ poe3_t<base>::ICSR6;


	typedef poe3_t<0x0008'C4C0> POE3;
}
