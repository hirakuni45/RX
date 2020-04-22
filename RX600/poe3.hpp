#pragma once
//=====================================================================//
/*!	@file
	@brief	ポートアウトプットイネーブル 3（POE3）定義 @n
			RX64M, RX71M, RX65N, RX651, RX66T, RX24T
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ポートアウトプットイネーブル 3 クラス
		@param[in]	org		POE3 モジュール先頭アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t org, peripheral per>
	struct poe3_t {

		static const auto PERIPHERAL = per;	///< ペリフェラル型

#if defined(SIG_RX24T)
		/// アウトプットイネーブル割り込み 1 POE0F, OSF1
		static const auto OEI1_VEC = ICU::VECTOR::OEI1;
		/// アウトプットイネーブル割り込み 2 POE4F, OSF2
		static const auto OEI2_VEC = ICU::VECTOR::OEI2;
		/// アウトプットイネーブル割り込み 3 POE8F, RX66T: POE8F, POE9F
		static const auto OEI3_VEC = ICU::VECTOR::OEI3;
		/// アウトプットイネーブル割り込み 4 POE10F, OSF11F
		static const auto OEI4_VEC = ICU::VECTOR::OEI4;
		/// アウトプットイネーブル割り込み 5 POE4F, OSF12F
		static const auto OEI5_VEC = ICU::VECTOR::OEI5;


#elif defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T)
		/// アウトプットイネーブル割り込み 1 POE0F, OSF1
		static const auto OEI1_VEC = ICU::VECTOR_BL1::OEI1;
		/// アウトプットイネーブル割り込み 2 POE4F, OSF2
		static const auto OEI2_VEC = ICU::VECTOR_BL1::OEI2;
		/// アウトプットイネーブル割り込み 3 POE8F
		static const auto OEI3_VEC = ICU::VECTOR_BL1::OEI3;
		/// アウトプットイネーブル割り込み 4 POE10F, OSF11F
		static const auto OEI4_VEC = ICU::VECTOR_BL1::OEI4;

#if defined(SIG_RX66T)
		/// アウトプットイネーブル割り込み 5 POE12F, OSF13F, POE14F, OSF3, OSF4, OSF5
		static const auto OEI5_VEC = ICU::VECTOR_BL1::OEI5;
#endif
#endif

		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 1（ICSR1）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct icsr1_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

#if defined(SIG_RX66T)
			bits_rw_t<io_, bitpos::B0, 4>  POE0M;
			bits_rw_t<io_, bitpos::B4, 4>  POE0M2;
#else
			bits_rw_t<io_, bitpos::B0, 2>  POE0M;
#endif
			bit_rw_t <io_, bitpos::B8>     PIE1;
			bit_rw_t <io_, bitpos::B12>    POE0F;
		};
		typedef icsr1_t<org + 0x00> ICSR1_;
		static  ICSR1_ ICSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 2（ICSR2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct icsr2_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

#if defined(SIG_RX66T)
			bits_rw_t<io_, bitpos::B0, 4>  POE4M;
			bits_rw_t<io_, bitpos::B4, 4>  POE4M2;
#else
			bits_rw_t<io_, bitpos::B0, 2>  POE4M;
#endif
			bit_rw_t <io_, bitpos::B8>     PIE2;
			bit_rw_t <io_, bitpos::B12>    POE4F;
		};
		typedef icsr2_t<org + 0x04> ICSR2_;
		static  ICSR2_ ICSR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 3（ICSR3）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct icsr3_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

#if defined(SIG_RX66T)
			bits_rw_t<io_, bitpos::B0, 4>  POE8M;
			bits_rw_t<io_, bitpos::B4, 4>  POE8M2;
#else
			bits_rw_t<io_, bitpos::B0, 2>  POE8M;
#endif
			bit_rw_t <io_, bitpos::B8>     PIE3;
			bit_rw_t <io_, bitpos::B9>     POE8E;
			bit_rw_t <io_, bitpos::B12>    POE8F;
		};
		typedef icsr3_t<org + 0x08> ICSR3_;
		static  ICSR3_ ICSR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 4（ICSR4）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct icsr4_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

#if defined(SIG_RX66T)
			bits_rw_t<io_, bitpos::B0, 4>  POE10M;
			bits_rw_t<io_, bitpos::B4, 4>  POE10M2;
#else
			bits_rw_t<io_, bitpos::B0, 2>  POE10M;
#endif
			bit_rw_t <io_, bitpos::B8>     PIE4;
			bit_rw_t <io_, bitpos::B9>     POE10E;
			bit_rw_t <io_, bitpos::B12>    POE10F;
		};
		typedef icsr4_t<org + 0x16> ICSR4_;
		static  ICSR4_ ICSR4;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 5（ICSR5）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct icsr5_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

#if defined(SIG_RX66T)
			bits_rw_t<io_, bitpos::B0, 4>  POE11M;
			bits_rw_t<io_, bitpos::B4, 4>  POE11M2;
#else
			bits_rw_t<io_, bitpos::B0, 2>  POE11M;
#endif
			bit_rw_t <io_, bitpos::B8>     PIE5;
			bit_rw_t <io_, bitpos::B9>     POE11E;
			bit_rw_t <io_, bitpos::B12>    POE11F;
		};
		typedef icsr5_t<org + 0x18> ICSR5_;
		static  ICSR5_ ICSR5;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 6（ICSR6）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct icsr6_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B9>     OSTSTE;
			bit_rw_t <io_, bitpos::B12>    OSTSTF;
		};
		typedef icsr6_t<org + 0x1C> ICSR6_;
		static  ICSR6_ ICSR6;

#if defined(SIG_RX24T) || defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 7（ICSR7）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct icsr7_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

#if defined(SIG_RX24T)
			bits_rw_t<io_, bitpos::B0, 2>  POE12M;
#elif defined(SIG_RX66T)
			bits_rw_t<io_, bitpos::B0, 4>  POE12M;
			bits_rw_t<io_, bitpos::B4, 4>  POE12M2;
#endif
			bit_rw_t <io_, bitpos::B8>     PIE7;
			bit_rw_t <io_, bitpos::B9>     POE12E;
			bit_rw_t <io_, bitpos::B12>    POE12F;
		};
		typedef icsr7_t<org + 0x20> ICSR7_;
		static  ICSR7_ ICSR7;
#endif

#if defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 8（ICSR8）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct icsr8_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
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
		typedef icsr8_t<org + 0x40> ICSR8_;
		static  ICSR8_ ICSR8;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 9（ICSR9）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct icsr9_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
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
		typedef icsr9_t<org + 0x42> ICSR9_;
		static  ICSR9_ ICSR9;


		//-----------------------------------------------------------------//
		/*!
			@brief	入力レベルコントロール / ステータスレジスタ 10（ICSR10）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct icsr10_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  POE14M;
			bits_rw_t<io_, bitpos::B4, 4>  POE14M2;
			bit_rw_t <io_, bitpos::B8>     PIE10;
			bit_rw_t <io_, bitpos::B9>     POE14E;
			bit_rw_t <io_, bitpos::B12>    POE14F;
		};
		typedef icsr10_t<org + 0x44> ICSR10_;
		static  ICSR10_ ICSR10;
#endif


		//-----------------------------------------------------------------//
		/*!
			@brief	出力レベルコントロール / ステータスレジスタ 1（OCSR1）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ocsr1_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B8>   OIE1;
			bit_rw_t<io_, bitpos::B9>   OCE1;
			bit_rw_t<io_, bitpos::B15>  OSF1;
		};
		typedef ocsr1_t<org + 0x02> OCSR1_;
		static  OCSR1_ OCSR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	出力レベルコントロール / ステータスレジスタ 2（OCSR2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ocsr2_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B8>   OIE2;
			bit_rw_t<io_, bitpos::B9>   OCE2;
			bit_rw_t<io_, bitpos::B15>  OSF2;
		};
		typedef ocsr2_t<org + 0x06> OCSR2_;
		static  OCSR2_ OCSR2;


#if defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	出力レベルコントロール / ステータスレジスタ 3（OCSR3）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ocsr3_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B8>   OIE3;
			bit_rw_t<io_, bitpos::B9>   OCE3;
			bit_rw_t<io_, bitpos::B15>  OSF3;
		};
		typedef ocsr3_t<org + 0x2A> OCSR3_;
		static  OCSR3_ OCSR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	出力レベルコントロール / ステータスレジスタ 4（OCSR4）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ocsr4_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B8>   OIE4;
			bit_rw_t<io_, bitpos::B9>   OCE4;
			bit_rw_t<io_, bitpos::B15>  OSF4;
		};
		typedef ocsr4_t<org + 0x46> OCSR4_;
		static  OCSR4_ OCSR4;


		//-----------------------------------------------------------------//
		/*!
			@brief	出力レベルコントロール / ステータスレジスタ 5（OCSR5）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct ocsr5_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B8>   OIE5;
			bit_rw_t<io_, bitpos::B9>   OCE5;
			bit_rw_t<io_, bitpos::B15>  OSF5;
		};
		typedef ocsr5_t<org + 0x48> OCSR5_;
		static  OCSR5_ OCSR5;
#endif


		//-----------------------------------------------------------------//
		/*!
			@brief	アクティブレベルレジスタ 1（ALR1）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct alr1_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
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
		typedef alr1_t<org + 0x1A> ALR1_;
		static  ALR1_ ALR1;


#if defined(SIG_RX24T) || defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	アクティブレベルレジスタ 2（ALR2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct alr2_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
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
		typedef alr2_t<org + 0x1E> ALR2_;
		static  ALR2_ ALR2;
#endif


#if defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	アクティブレベルレジスタ 3（ALR3）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct alr3_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
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
		typedef alr3_t<org + 0x2C> ALR3_;
		static  ALR3_ ALR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	アクティブレベルレジスタ 4（ALR4）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct alr4_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
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
		typedef alr4_t<org + 0x4A> ALR4_;
		static  ALR4_ ALR4;


		//-----------------------------------------------------------------//
		/*!
			@brief	アクティブレベルレジスタ 5（ALR5）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct alr5_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
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
		typedef alr5_t<org + 0x4C> ALR5_;
		static  ALR5_ ALR5;
#endif


		//-----------------------------------------------------------------//
		/*!
			@brief	ソフトウェアポートアウトプットイネーブルレジスタ（SPOER）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
		template <uint32_t base>
		struct spoer_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MTUCH34HIZ;
			bit_rw_t<io_, bitpos::B1>  MTUCH67HIZ;
			bit_rw_t<io_, bitpos::B2>  MTUCH0HIZ;
			bit_rw_t<io_, bitpos::B3>  GPT01HIZ;
			bit_rw_t<io_, bitpos::B4>  GPT23HIZ;
		};
		typedef spoer_t<org + 0x0A> SPOER_;
		static  SPOER_ SPOER;
#elif defined(SIG_RX24T)
		template <uint32_t base>
		struct spoer_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MTUCH34HIZ;
			bit_rw_t<io_, bitpos::B1>  MTUCH67HIZ;
			bit_rw_t<io_, bitpos::B2>  MTUCH0HIZ;

			bit_rw_t<io_, bitpos::B4>  GPT03HIZ;

			bit_rw_t<io_, bitpos::B6>  MTUCH9HIZ;
		};
		typedef spoer_t<org + 0x0A> SPOER_;
		static  SPOER_ SPOER;
#elif defined(SIG_RX66T)
		template <uint32_t base>
		struct spoer_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MTUCH34HIZ;
			bit_rw_t<io_, bitpos::B1>  MTUCH67HIZ;
			bit_rw_t<io_, bitpos::B2>  MTUCH0HIZ;
			bit_rw_t<io_, bitpos::B3>  GPT01HIZ;
			bit_rw_t<io_, bitpos::B4>  GPT03HIZ;

			bit_rw_t<io_, bitpos::B6>  MTUCH9HIZ;

			bit_rw_t<io_, bitpos::B8>  GPT02HIZ;
			bit_rw_t<io_, bitpos::B9>  GPT46HIZ;
			bit_rw_t<io_, bitpos::B10> GPT79HIZ;
		};
		typedef spoer_t<org + 0x2E> SPOER_;
		static  SPOER_ SPOER;
#endif


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 1（POECR1）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecr1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MTU0AZE;
			bit_rw_t<io_, bitpos::B1>  MTU0BZE;
			bit_rw_t<io_, bitpos::B2>  MTU0CZE;
			bit_rw_t<io_, bitpos::B3>  MTU0DZE;
#if defined(SIG_RX24T)
			bit_rw_t<io_, bitpos::B4>  MTU0A1ZE;
			bit_rw_t<io_, bitpos::B5>  MTU0B1ZE;
#endif
		};
		typedef poecr1_t<org + 0x0B> POECR1_;
		static  POECR1_ POECR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 2（POECR2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecr2_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
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
		typedef poecr2_t<org + 0x0C> POECR2_;
		static  POECR2_ POECR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 3（POECR3）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecr3_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

#if defined(SIG_RX24T)
			bit_rw_t<io_, bitpos::B8>   GPT0A1ZE;
			bit_rw_t<io_, bitpos::B9>   GPT0B1ZE;
			bit_rw_t<io_, bitpos::B10>  GPT1A1ZE;
			bit_rw_t<io_, bitpos::B11>  GPT1B1ZE;
			bit_rw_t<io_, bitpos::B12>  GPT2A1ZE;
			bit_rw_t<io_, bitpos::B13>  GPT2B1ZE;
			bit_rw_t<io_, bitpos::B14>  GPT3A1ZE;
			bit_rw_t<io_, bitpos::B15>  GPT3B1ZE;
#elif defined(SIG_RX64M) || defined(SIG_RX71M)
			bit_rw_t<io_, bitpos::B0>   GPT0ABZE;
			bit_rw_t<io_, bitpos::B1>   GPT1ABZE;
			bit_rw_t<io_, bitpos::B8>   GPT2ABZE;
			bit_rw_t<io_, bitpos::B9>   GPT3ABZE;
#elif defined(SIG_RX66T)
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
#endif
		};
		typedef poecr3_t<org + 0x0E> POECR3_;
		static  POECR3_ POECR3;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 4（POECR4）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecr4_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

#if defined(SIG_RX24T)
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
#elif defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
			bit_rw_t<io_, bitpos::B2>  IC2ADDMT34ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDMT34ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDMT34ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT34ZE;

			bit_rw_t<io_, bitpos::B9>  IC1ADDMT67ZE;

			bit_rw_t<io_, bitpos::B3>  IC3ADDMT67ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDMT67ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT67ZE;
#elif defined(SIG_RX66T)
			bit_rw_t<io_, bitpos::B0>  CMADDMT34ZE;
			bit_rw_t<io_, bitpos::B1>  IC1ADDMT34ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDMT34ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDMT34ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDMT34ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT34ZE;
			bit_rw_t<io_, bitpos::B6>  IC6ADDMT34ZE;

			bit_rw_t<io_, bitpos::B8>  IC8ADDMT34ZE;
			bit_rw_t<io_, bitpos::B9>  IC9ADDMT34ZE;
			bit_rw_t<io_, bitpos::B10> IC10ADDMT34ZE;
#endif
		};
		typedef poecr4_t<org + 0x10> POECR4_;
		static  POECR4_ POECR4;


#if defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 4B（POECR4B）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecr4b_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CMADDMT67ZE;
			bit_rw_t<io_, bitpos::B1>  IC1ADDMT67ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDMT67ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDMT67ZE;
			bit_rw_t<io_, bitpos::B4>  IC4ADDMT67ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT67ZE;
			bit_rw_t<io_, bitpos::B6>  IC6ADDMT67ZE;

			bit_rw_t<io_, bitpos::B8>  IC8ADDMT67ZE;
			bit_rw_t<io_, bitpos::B9>  IC9ADDMT67ZE;
			bit_rw_t<io_, bitpos::B10> IC10ADDMT67ZE;
		};
		typedef poecr4b_t<org + 0x4E> POECR4B_;
		static  POECR4B_ POECR4B;
#endif


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 5（POECR5）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecr5_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

#if defined(SIG_RX24T)
			bit_rw_t<io_, bitpos::B0>  CMADDMT0ZE;
			bit_rw_t<io_, bitpos::B1>  IC1ADDMT0ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDMT0ZE;

			bit_rw_t<io_, bitpos::B4>  IC4ADDMT0ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT0ZE;
			bit_rw_t<io_, bitpos::B6>  IC6ADDMT0ZE;
#elif defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
			bit_rw_t<io_, bitpos::B1>  IC1ADDMT0ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDMT0ZE;

			bit_rw_t<io_, bitpos::B4>  IC4ADDMT0ZE;
			bit_rw_t<io_, bitpos::B5>  IC5ADDMT0ZE;
#elif defined(SIG_RX66T)
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
#endif 
		};
		typedef poecr5_t<org + 0x12> POECR5_;
		static  POECR5_ POECR5;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 6（POECR6）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecr6_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

#if defined(SIG_RX24T)
			bit_rw_t<io_, bitpos::B8>  CMADDGPT03ZE;
			bit_rw_t<io_, bitpos::B9>  IC1ADDGPT03ZE;
			bit_rw_t<io_, bitpos::B10> IC2ADDGPT03ZE;
			bit_rw_t<io_, bitpos::B11> IC3ADDGPT03ZE;
			bit_rw_t<io_, bitpos::B12> IC4ADDGPT03ZE;

			bit_rw_t<io_, bitpos::B14> IC6ADDGPT03ZE;
#elif defined(SIG_RX64M) || defined(SIG_RX71M)
			bit_rw_t<io_, bitpos::B1>  IC1ADDGPT01ZE;
			bit_rw_t<io_, bitpos::B2>  IC2ADDGPT01ZE;
			bit_rw_t<io_, bitpos::B3>  IC3ADDGPT01ZE;

			bit_rw_t<io_, bitpos::B5>  IC5ADDGPT01ZE;

			bit_rw_t<io_, bitpos::B9>  IC1ADDGPT23ZE;
			bit_rw_t<io_, bitpos::B10> IC2ADDGPT23ZE;
			bit_rw_t<io_, bitpos::B11> IC3ADDGPT23ZE;
			bit_rw_t<io_, bitpos::B12> IC4ADDGPT23ZE;
#elif defined(SIG_RX66T)
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
#endif 
		};
#if defined(SIG_RX24T) || defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX66T)
		typedef poecr6_t<org + 0x14> POECR6_;
		static  POECR6_ POECR6;
#endif


#if defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 6B（POECR6B）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecr6B_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
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
		typedef poecr6B_t<org + 0x50> POECR6B_;
		static  POECR6B_ POECR6B;
#endif


#if defined(SIG_RX24T) || defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 7（POECR7）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecr7_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MTU9AZE;
			bit_rw_t<io_, bitpos::B1>  MTU9BZE;
			bit_rw_t<io_, bitpos::B2>  MTU9CZE;
			bit_rw_t<io_, bitpos::B3>  MTU9DZE;
#if defined(SIG_RX24T)
			bit_rw_t<io_, bitpos::B4>  MTU9A1ZE;
			bit_rw_t<io_, bitpos::B5>  MTU9B1ZE;
			bit_rw_t<io_, bitpos::B6>  MTU9C1ZE;
			bit_rw_t<io_, bitpos::B7>  MTU9D1ZE;
#endif
		};
		typedef poecr7_t<org + 0x22> POECR7_;
		static  POECR7_ POECR7;
#endif


#if defined(SIG_RX24T) || defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 8（POECR8）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecr8_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
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
#if defined(SIG_RX66T)
			bit_rw_t<io_, bitpos::B6>  IC6ADDMT9ZE;

			bit_rw_t<io_, bitpos::B8>  IC8ADDMT9ZE;
			bit_rw_t<io_, bitpos::B9>  IC9ADDMT9ZE;
			bit_rw_t<io_, bitpos::B10> IC10ADDMT9ZE;
#endif
		};
		typedef poecr8_t<org + 0x24> POECR8_;
		static  POECR8_ POECR8;
#endif


#if defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 9（POECR9）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecr9_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
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
		typedef poecr9_t<org + 0x52> POECR9_;
		static  POECR9_ POECR9;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 10（POECR10）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecr10_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
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
		typedef poecr10_t<org + 0x54> POECR10_;
		static  POECR10_ POECR10;


		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコントロールレジスタ 11（POECR11）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecr11_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
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
		typedef poecr11_t<org + 0x56> POECR11_;
		static  POECR11_ POECR11;
#endif


#if defined(SIG_RX24T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートモードマスクコントロールレジスタ 0 (PMMCR0)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pmmcr0_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MTU0AME;
			bit_rw_t<io_, bitpos::B1>  MTU0BME;
			bit_rw_t<io_, bitpos::B2>  MTU0CME;
			bit_rw_t<io_, bitpos::B3>  MTU0DME;
			bit_rw_t<io_, bitpos::B4>  MTU0A1ME;
			bit_rw_t<io_, bitpos::B5>  MTU0B1ME;
		};
		typedef pmmcr0_t<org + 0x30> PMMCR0_;
		static  PMMCR0_ PMMCR0;
#elif defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートモードマスクコントロールレジスタ 0 (PMMCR0)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pmmcr0_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MTU0AME;
			bit_rw_t<io_, bitpos::B1>  MTU0BME;
			bit_rw_t<io_, bitpos::B2>  MTU0CME;
			bit_rw_t<io_, bitpos::B3>  MTU0DME;

			bit_rw_t<io_, bitpos::B8>  MTU9AME;
			bit_rw_t<io_, bitpos::B9>  MTU9BME;
			bit_rw_t<io_, bitpos::B10> MTU9CME;
			bit_rw_t<io_, bitpos::B11> MTU9DME;
		};
		typedef pmmcr0_t<org + 0x30> PMMCR0_;
		static  PMMCR0_ PMMCR0;
#endif


#if defined(SIG_RX24T) || defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートモードマスクコントロールレジスタ 1 (PMMCR1)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pmmcr1_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
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
		typedef pmmcr1_t<org + 0x32> PMMCR1_;
		static  PMMCR1_ PMMCR1;
#endif


#if defined(SIG_RX24T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートモードマスクコントロールレジスタ 2 (PMMCR2)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pmmcr2_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B8>  GPT0A1ME;
			bit_rw_t<io_, bitpos::B9>  GPT0B1ME;
			bit_rw_t<io_, bitpos::B10> GPT1A1ME;
			bit_rw_t<io_, bitpos::B11> GPT1B1ME;
			bit_rw_t<io_, bitpos::B12> GPT2A1ME;
			bit_rw_t<io_, bitpos::B13> GPT2B1ME;
			bit_rw_t<io_, bitpos::B14> GPT3A1ME;
			bit_rw_t<io_, bitpos::B15> GPT3B1ME;
		};
		typedef pmmcr2_t<org + 0x34> PMMCR2_;
		static  PMMCR2_ PMMCR2;
#elif defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートモードマスクコントロールレジスタ 2 (PMMCR2)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pmmcr2_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
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
		typedef pmmcr2_t<org + 0x34> PMMCR2_;
		static  PMMCR2_ PMMCR2;
#endif


#if defined(SIG_RX24T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートモードマスクコントロールレジスタ 3 (PMMCR3)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pmmcr3_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MTU9AME;
			bit_rw_t<io_, bitpos::B1>  MTU9BME;
			bit_rw_t<io_, bitpos::B2>  MTU9CME;
			bit_rw_t<io_, bitpos::B3>  MTU9DME;
			bit_rw_t<io_, bitpos::B4>  MTU9A1ME;
			bit_rw_t<io_, bitpos::B5>  MTU9B1ME;
			bit_rw_t<io_, bitpos::B6>  MTU9C1ME;
			bit_rw_t<io_, bitpos::B7>  MTU9D1ME;
		};
		typedef pmmcr3_t<org + 0x36> PMMCR3_;
		static  PMMCR3_ PMMCR3;
#elif defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートモードマスクコントロールレジスタ 3 (PMMCR3)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct pmmcr3_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  GPT8AME;
			bit_rw_t<io_, bitpos::B1>  GPT8BME;
			bit_rw_t<io_, bitpos::B2>  GPT9AME;
			bit_rw_t<io_, bitpos::B3>  GPT9BME;
		};
		typedef pmmcr3_t<org + 0x36> PMMCR3_;
		static  PMMCR3_ PMMCR3;
#endif


#if defined(SIG_RX24T) || defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコンパレータ検出フラグレジスタ（POECMPFR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecmpfr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  C0FLAG;
			bit_rw_t<io_, bitpos::B1>  C1FLAG;
			bit_rw_t<io_, bitpos::B2>  C2FLAG;
			bit_rw_t<io_, bitpos::B3>  C3FLAG;
#if defined(SIG_RX66T)
			bit_rw_t<io_, bitpos::B4>  C4FLAG;
			bit_rw_t<io_, bitpos::B5>  C5FLAG;
#endif
		};
		typedef poecmpfr_t<org + 0x26> POECMPFR_;
		static  POECMPFR_ POECMPFR;
#endif


#if defined(SIG_RX24T) || defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコンパレータ要求選択レジスタ（POECMPSEL）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecmpsel_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  POEREQ0;
			bit_rw_t<io_, bitpos::B1>  POEREQ1;
			bit_rw_t<io_, bitpos::B2>  POEREQ2;
			bit_rw_t<io_, bitpos::B3>  POEREQ3;
#if defined(SIG_RX66T)
			bit_rw_t<io_, bitpos::B4>  POEREQ4;
			bit_rw_t<io_, bitpos::B5>  POEREQ5;
#endif
		};
		typedef poecmpsel_t<org + 0x28> POECMPSEL_;
		static  POECMPSEL_ POECMPSEL;
#endif


#if defined(SIG_RX24T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコンパレータ要求拡張選択レジスタ m @n
					(POECMPEXm) (m = 0 ～ 2, 4, 5)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecmpex_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  POEREQ0;
			bit_rw_t<io_, bitpos::B1>  POEREQ1;
			bit_rw_t<io_, bitpos::B2>  POEREQ2;
			bit_rw_t<io_, bitpos::B3>  POEREQ3;
		};
		typedef poecmpex_t<org + 0x38> POECMPEX0_;
		static  POECMPEX0_ POECMPEX0;
		typedef poecmpex_t<org + 0x39> POECMPEX1_;
		static  POECMPEX1_ POECMPEX1;
		typedef poecmpex_t<org + 0x3A> POECMPEX2_;
		static  POECMPEX2_ POECMPEX2;
		typedef poecmpex_t<org + 0x3C> POECMPEX4_;
		static  POECMPEX4_ POECMPEX4;
		typedef poecmpex_t<org + 0x3D> POECMPEX5_;
		static  POECMPEX5_ POECMPEX5;
#elif defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	ポートアウトプットイネーブルコンパレータ要求拡張選択レジスタ m @n
					(POECMPEXm) (m = 0 ～ 2, 4, 5)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct poecmpex_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
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
		typedef poecmpex_t<org + 0x38> POECMPEX0_;
		static  POECMPEX0_ POECMPEX0;
		typedef poecmpex_t<org + 0x39> POECMPEX1_;
		static  POECMPEX1_ POECMPEX1;
		typedef poecmpex_t<org + 0x3A> POECMPEX2_;
		static  POECMPEX2_ POECMPEX2;
		typedef poecmpex_t<org + 0x3B> POECMPEX3_;
		static  POECMPEX3_ POECMPEX3;
		typedef poecmpex_t<org + 0x3C> POECMPEX4_;
		static  POECMPEX4_ POECMPEX4;
		typedef poecmpex_t<org + 0x3D> POECMPEX5_;
		static  POECMPEX5_ POECMPEX5;
		typedef poecmpex_t<org + 0x58> POECMPEX6_;
		static  POECMPEX6_ POECMPEX6;
		typedef poecmpex_t<org + 0x59> POECMPEX7_;
		static  POECMPEX7_ POECMPEX7;
		typedef poecmpex_t<org + 0x5A> POECMPEX8_;
		static  POECMPEX8_ POECMPEX8;
#endif


#if defined(SIG_RX64M) || defined(SIG_RX71M)
		//-----------------------------------------------------------------//
		/*!
			@brief	GPT0 端子選択レジスタ（G0SELR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct g0selr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G0ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G0BSEL;
		};
		typedef g0selr_t<org + 0x20> G0SELR_;
		static  G0SELR_ G0SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPT1 端子選択レジスタ（G1SELR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct g1selr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G1ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G1BSEL;
		};
		typedef g1selr_t<org + 0x21> G1SELR_;
		static  G1SELR_ G1SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPT2 端子選択レジスタ（G2SELR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct g2selr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G2ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G2BSEL;
		};
		typedef g2selr_t<org + 0x22> G2SELR_;
		static  G2SELR_ G2SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPT3 端子選択レジスタ（G3SELR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct g3selr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G3ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G3BSEL;
		};
		typedef g3selr_t<org + 0x23> G3SELR_;
		static  G3SELR_ G3SELR;
#endif


#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N) || defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	MTU0 端子選択レジスタ（M0SELR1）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct m0selr1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M0ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  M0BSEL;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU0 端子選択レジスタ 2（M0SELR2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct m0selr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M0CSEL;
			bits_rw_t<io_, bitpos::B4, 4>  M0DSEL;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU3 端子選択レジスタ（M3SELR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct m3selr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M3BSEL;
			bits_rw_t<io_, bitpos::B4, 4>  M3DSEL;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU4 端子選択レジスタ 1（M4SELR1）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct m4selr1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M4ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  M4CSEL;
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU4 端子選択レジスタ 2（M4SELR2）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct m4selr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M4BSEL;
			bits_rw_t<io_, bitpos::B4, 4>  M4DSEL;
		};
#endif

#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
		typedef m0selr1_t<org + 0x24> M0SELR1_;
		static  M0SELR1_ M0SELR1;
		typedef m0selr2_t<org + 0x25> M0SELR2_;
		static  M0SELR2_ M0SELR2;
		typedef m3selr_t<org + 0x26>  M3SELR_;
		static  M3SELR_ M3SELR;
		typedef m4selr1_t<org + 0x27> M4SELR1_;
		static  M4SELR1_ M4SELR1;
		typedef m4selr2_t<org + 0x28> M4SELR2_;
		static  M4SELR2_ M4SELR2;
#elif defined(SIG_RX66T)
		typedef m0selr1_t<org + 0x60> M0SELR1_;
		static  M0SELR1_ M0SELR1;
		typedef m0selr2_t<org + 0x61> M0SELR2_;
		static  M0SELR2_ M0SELR2;
		typedef m3selr_t<org + 0x62>  M3SELR_;
		static  M3SELR_ M3SELR;
		typedef m4selr1_t<org + 0x63> M4SELR1_;
		static  M4SELR1_ M4SELR1;
		typedef m4selr2_t<org + 0x64> M4SELR2_;
		static  M4SELR2_ M4SELR2;
#endif


#if defined(SIG_RX64M) || defined(SIG_RX71M)
		//-----------------------------------------------------------------//
		/*!
			@brief	MTU/GPT 端子機能選択レジスタ（MGSELR）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct mgselr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  M3G0SEL;
			bit_rw_t<io_, bitpos::B1>  M4G1SEL;
			bit_rw_t<io_, bitpos::B2>  M4G2SEL;
		};
		typedef mgselr_t<org + 0x29> MGSELR_;
		static  MGSELR_ MGSELR;
#endif


#if defined(SIG_RX66T)
		//-----------------------------------------------------------------//
		/*!
			@brief	MTU6 端子選択レジスタ (M6SELR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct m6selr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M6BSEL;
			bits_rw_t<io_, bitpos::B4, 4>  M6DSEL;
		};
		typedef m6selr_t<org + 0x65> M6SELR_;
		static  M6SELR_ M6SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU7 端子選択レジスタ 1 (M7SELR1)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct m7selr1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M7ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  M7CSEL;
		};
		typedef m7selr1_t<org + 0x66> M7SELR1_;
		static  M7SELR1_ M7SELR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU7 端子選択レジスタ 2 (M7SELR2)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct m7selr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M7BSEL;
			bits_rw_t<io_, bitpos::B4, 4>  M7DSEL;
		};
		typedef m7selr2_t<org + 0x67> M7SELR2_;
		static  M7SELR2_ M7SELR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU9 端子選択レジスタ 1 (M9SELR1)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct m9selr1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M9ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  M9BSEL;
		};
		typedef m9selr1_t<org + 0x68> M9SELR1_;
		static  M9SELR1_ M9SELR1;


		//-----------------------------------------------------------------//
		/*!
			@brief	MTU9 端子選択レジスタ 2 (M9SELR2)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct m9selr2_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  M9CSEL;
			bits_rw_t<io_, bitpos::B4, 4>  M9DSEL;
		};
		typedef m9selr2_t<org + 0x69> M9SELR2_;
		static  M9SELR2_ M9SELR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPTW0 端子選択レジスタ (G0SELR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct g0selr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G0ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G0BSEL;
		};
		typedef g0selr_t<org + 0x6A> G0SELR_;
		static  G0SELR_ G0SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPTW1 端子選択レジスタ (G1SELR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct g1selr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G1ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G1BSEL;
		};
		typedef g1selr_t<org + 0x6B> G1SELR_;
		static  G1SELR_ G1SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPTW2 端子選択レジスタ (G2SELR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct g2selr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G2ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G2BSEL;
		};
		typedef g2selr_t<org + 0x6C> G2SELR_;
		static  G2SELR_ G2SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPTW3 端子選択レジスタ (G3SELR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct g3selr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G3ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G3BSEL;
		};
		typedef g3selr_t<org + 0x6D> G3SELR_;
		static  G3SELR_ G3SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPTW4 端子選択レジスタ (G4SELR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct g4selr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G4ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G4BSEL;
		};
		typedef g4selr_t<org + 0x6E> G4SELR_;
		static  G4SELR_ G4SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPTW5 端子選択レジスタ (G5SELR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct g5selr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G5ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G5BSEL;
		};
		typedef g5selr_t<org + 0x6F> G5SELR_;
		static  G5SELR_ G5SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPTW6 端子選択レジスタ (G6SELR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct g6selr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G6ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G6BSEL;
		};
		typedef g6selr_t<org + 0x70> G6SELR_;
		static  G6SELR_ G6SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPTW7 端子選択レジスタ (G7SELR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct g7selr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G7ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G7BSEL;
		};
		typedef g7selr_t<org + 0x71> G7SELR_;
		static  G7SELR_ G7SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPTW8 端子選択レジスタ (G8SELR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct g8selr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G8ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G8BSEL;
		};
		typedef g8selr_t<org + 0x72> G8SELR_;
		static  G8SELR_ G8SELR;


		//-----------------------------------------------------------------//
		/*!
			@brief	GPTW9 端子選択レジスタ (G9SELR)
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct g9selr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  G9ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G9BSEL;
		};
		typedef g9selr_t<org + 0x73> G9SELR_;
		static  G9SELR_ G9SELR;
#endif
	};
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::ICSR1_ poe3_t<base, per>::ICSR1;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::ICSR2_ poe3_t<base, per>::ICSR2;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::ICSR3_ poe3_t<base, per>::ICSR3;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::ICSR4_ poe3_t<base, per>::ICSR4;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::ICSR5_ poe3_t<base, per>::ICSR5;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::ICSR6_ poe3_t<base, per>::ICSR6;
#if defined(SIG_RX24T) || defined(SIG_RX24T)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::ICSR7_ poe3_t<base, per>::ICSR7;
#endif
#if defined(SIG_RX66T)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::ICSR8_ poe3_t<base, per>::ICSR8;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::ICSR9_ poe3_t<base, per>::ICSR9;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::ICSR10_ poe3_t<base, per>::ICSR10;
#endif
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::OCSR1_ poe3_t<base, per>::OCSR1;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::OCSR2_ poe3_t<base, per>::OCSR2;
#if defined(SIG_RX66T)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::OCSR3_ poe3_t<base, per>::OCSR3;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::OCSR4_ poe3_t<base, per>::OCSR4;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::OCSR5_ poe3_t<base, per>::OCSR5;
#endif
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::ALR1_ poe3_t<base, per>::ALR1;
#if defined(SIG_RX24T) || defined(SIG_RX66T)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::ALR2_ poe3_t<base, per>::ALR2;
#endif
#if defined(SIG_RX66T)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::ALR3_ poe3_t<base, per>::ALR3;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::ALR4_ poe3_t<base, per>::ALR4;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::ALR5_ poe3_t<base, per>::ALR5;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::SPOER_ poe3_t<base, per>::SPOER;
#elif defined(SIG_RX24T)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::SPOER_ poe3_t<base, per>::SPOER;
#elif defined(SIG_RX66T)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::SPOER_ poe3_t<base, per>::SPOER;
#endif
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECR1_ poe3_t<base, per>::POECR1;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECR2_ poe3_t<base, per>::POECR2;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECR3_ poe3_t<base, per>::POECR3;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECR4_ poe3_t<base, per>::POECR4;
#if defined(SIG_RX66T)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECR4B_ poe3_t<base, per>::POECR4B;
#endif
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECR5_ poe3_t<base, per>::POECR5;
#if defined(SIG_RX24T) || defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX66T)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECR6_ poe3_t<base, per>::POECR6;
#endif
#if defined(SIG_RX66T)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECR6B_ poe3_t<base, per>::POECR6B;
#endif
#if defined(SIG_RX24T) || defined(SIG_RX66T)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECR7_ poe3_t<base, per>::POECR7;
#endif
#if defined(SIG_RX24T) || defined(SIG_RX66T)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECR8_ poe3_t<base, per>::POECR8;
#endif
#if defined(SIG_RX66T)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECR9_ poe3_t<base, per>::POECR9;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECR10_ poe3_t<base, per>::POECR10;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECR11_ poe3_t<base, per>::POECR11;
#endif
#if defined(SIG_RX24T)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::PMMCR0_ poe3_t<base, per>::PMMCR0;
#elif defined(SIG_RX66T)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::PMMCR0_ poe3_t<base, per>::PMMCR0;
#endif
#if defined(SIG_RX24T) || defined(SIG_RX66T)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::PMMCR1_ poe3_t<base, per>::PMMCR1;
#endif
#if defined(SIG_RX24T)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::PMMCR2_ poe3_t<base, per>::PMMCR2;
#elif defined(SIG_RX66T)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::PMMCR2_ poe3_t<base, per>::PMMCR2;
#endif
#if defined(SIG_RX24T)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::PMMCR3_ poe3_t<base, per>::PMMCR3;
#elif defined(SIG_RX66T)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::PMMCR3_ poe3_t<base, per>::PMMCR3;
#endif
#if defined(SIG_RX24T) || defined(SIG_RX66T)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECMPFR_ poe3_t<base, per>::POECMPFR;
#endif
#if defined(SIG_RX24T) || defined(SIG_RX66T)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECMPSEL_ poe3_t<base, per>::POECMPSEL;
#endif
#if defined(SIG_RX24T)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECMPEX0_ poe3_t<base, per>::POECMPEX0;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECMPEX1_ poe3_t<base, per>::POECMPEX1;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECMPEX2_ poe3_t<base, per>::POECMPEX2;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECMPEX4_ poe3_t<base, per>::POECMPEX4;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECMPEX5_ poe3_t<base, per>::POECMPEX5;
#elif defined(SIG_RX66T)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECMPEX0_ poe3_t<base, per>::POECMPEX0;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECMPEX1_ poe3_t<base, per>::POECMPEX1;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECMPEX2_ poe3_t<base, per>::POECMPEX2;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECMPEX3_ poe3_t<base, per>::POECMPEX3;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECMPEX4_ poe3_t<base, per>::POECMPEX4;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECMPEX5_ poe3_t<base, per>::POECMPEX5;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECMPEX6_ poe3_t<base, per>::POECMPEX6;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECMPEX7_ poe3_t<base, per>::POECMPEX7;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::POECMPEX8_ poe3_t<base, per>::POECMPEX8;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::G0SELR_ poe3_t<base, per>::G0SELR;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::G1SELR_ poe3_t<base, per>::G1SELR;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::G2SELR_ poe3_t<base, per>::G2SELR;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::G3SELR_ poe3_t<base, per>::G3SELR;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::M0SELR1_ poe3_t<base, per>::M0SELR1;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::M0SELR2_ poe3_t<base, per>::M0SELR2;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::M3SELR_ poe3_t<base, per>::M3SELR;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::M4SELR1_ poe3_t<base, per>::M4SELR1;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::M4SELR2_ poe3_t<base, per>::M4SELR2;
#elif defined(SIG_RX66T)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::M0SELR1_ poe3_t<base, per>::M0SELR1;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::M0SELR2_ poe3_t<base, per>::M0SELR2;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::M3SELR_ poe3_t<base, per>::M3SELR;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::M4SELR1_ poe3_t<base, per>::M4SELR1;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::M4SELR2_ poe3_t<base, per>::M4SELR2;
#endif
#if defined(SIG_RX64M) || defined(SIG_RX71M)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::MGSELR_ poe3_t<base, per>::MGSELR;
#endif
#if defined(SIG_RX66T)
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::M6SELR_ poe3_t<base, per>::M6SELR;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::M7SELR1_ poe3_t<base, per>::M7SELR1;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::M7SELR2_ poe3_t<base, per>::M7SELR2;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::M9SELR1_ poe3_t<base, per>::M9SELR1;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::M9SELR2_ poe3_t<base, per>::M9SELR2;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::G0SELR_ poe3_t<base, per>::G0SELR;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::G1SELR_ poe3_t<base, per>::G1SELR;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::G2SELR_ poe3_t<base, per>::G2SELR;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::G3SELR_ poe3_t<base, per>::G3SELR;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::G4SELR_ poe3_t<base, per>::G4SELR;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::G5SELR_ poe3_t<base, per>::G5SELR;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::G6SELR_ poe3_t<base, per>::G6SELR;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::G7SELR_ poe3_t<base, per>::G7SELR;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::G8SELR_ poe3_t<base, per>::G8SELR;
	template <uint32_t base, peripheral per> typename poe3_t<base, per>::G9SELR_ poe3_t<base, per>::G9SELR;
#endif

#if defined(SIG_RX24T) || defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
	typedef poe3_t<0x0008C4C0, peripheral::POE> POE3;
#elif defined(SIG_RX66T)
	typedef poe3_t<0x0009E400, peripheral::POE> POE3;
#endif
}
