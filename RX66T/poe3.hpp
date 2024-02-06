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

			bits_rw_t<io_, bitpos::B0, 4>  POE4M;
			bits_rw_t<io_, bitpos::B4, 4>  POE4M2;
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

			bits_rw_t<io_, bitpos::B0, 4>  POE8M;
			bits_rw_t<io_, bitpos::B4, 4>  POE8M2;
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

			bits_rw_t<io_, bitpos::B0, 4>  POE10M;
			bits_rw_t<io_, bitpos::B4, 4>  POE10M2;
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

			bits_rw_t<io_, bitpos::B0, 4>  POE11M;
			bits_rw_t<io_, bitpos::B4, 4>  POE11M2;
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
		static inline icsr7_t<base + 0x20> ICSR7;


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
		static inline icsr8_t<base + 0x40> ICSR8;


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
		static inline icsr9_t<base + 0x42> ICSR9;


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
		static inline icsr10_t<base + 0x44> ICSR10;


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
		static inline ocsr3_t<base + 0x2A> OCSR3;


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
		static inline ocsr4_t<base + 0x46> OCSR4;


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
		static inline ocsr5_t<base + 0x48> OCSR5;


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
		static inline alr2_t<base + 0x1E> ALR2;


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
		static inline alr3_t<base + 0x2C> ALR3;


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
		static inline alr4_t<base + 0x4A> ALR4;


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
		static inline alr5_t<base + 0x4C> ALR5;


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
		static inline poecr3_t<base + 0x0E> POECR3;


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
		static inline poecr4_t<base + 0x10> POECR4;


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
		static inline poecr4B_t<base + 0x4E> POECR4B;


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
		static inline poecr5_t<base + 0x12> POECR5;


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
		static inline poecr6_t<base + 0x14> POECR6;


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
		static inline poecr6b_t<base + 0x50> POECR6B;


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
		static inline poecr7_t<base + 0x22> POECR7;


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
		static inline poecr8_t<base + 0x24> POECR8;


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
		static inline poecr9_t<base + 0x52> POECR9;


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
		static inline poecr10_t<base + 0x54> POECR10;


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
		static inline poecr11_t<base + 0x56> POECR11;


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
		static inline pmmcr2_t<base + 0x34> PMMCR2;


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
		static inline pmmcr3_t<base + 0x36> PMMCR3;


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

			bit_rw_t<io_, bitpos::B0>  POEREQ0;
			bit_rw_t<io_, bitpos::B1>  POEREQ1;
			bit_rw_t<io_, bitpos::B2>  POEREQ2;
			bit_rw_t<io_, bitpos::B3>  POEREQ3;
			bit_rw_t<io_, bitpos::B4>  POEREQ4;
			bit_rw_t<io_, bitpos::B5>  POEREQ5;
		};
		static inline poecmpsel_t<base + 0x28> POECMPSEL;


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
		static inline poecmpexm_t<base + 0x38> POECMPEX0;
		static inline poecmpexm_t<base + 0x39> POECMPEX1;
		static inline poecmpexm_t<base + 0x3A> POECMPEX2;
		static inline poecmpexm_t<base + 0x3B> POECMPEX3;
		static inline poecmpexm_t<base + 0x3C> POECMPEX4;
		static inline poecmpexm_t<base + 0x3D> POECMPEX5;
		static inline poecmpexm_t<base + 0x58> POECMPEX6;
		static inline poecmpexm_t<base + 0x59> POECMPEX7;
		static inline poecmpexm_t<base + 0x5A> POECMPEX8;


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

			bits_rw_t<io_, bitpos::B0, 4>  M0CSEL;
			bits_rw_t<io_, bitpos::B4, 4>  M0DSEL;
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

			bits_rw_t<io_, bitpos::B0, 4>  M3BSEL;
			bits_rw_t<io_, bitpos::B4, 4>  M3DSEL;
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

			bits_rw_t<io_, bitpos::B0, 4>  M4ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  M4CSEL;
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

			bits_rw_t<io_, bitpos::B0, 4>  M4BSEL;
			bits_rw_t<io_, bitpos::B4, 4>  M4DSEL;
		};
		static inline m4selr2_t<base + 0x64> M4SELR2;


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
		static inline m6selr_t<base + 0x65> M6SELR;


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
		static inline m7selr1_t<base + 0x66> M7SELR1;


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
		static inline m7selr2_t<base + 0x67> M7SELR2;


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
		static inline m9selr1_t<base + 0x68> M9SELR1;


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
		static inline m9selr2_t<base + 0x69> M9SELR2;
	

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

			bits_rw_t<io_, bitpos::B0, 4>  G1ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G1BSEL;
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

			bits_rw_t<io_, bitpos::B0, 4>  G2ASEL;
			bits_rw_t<io_, bitpos::B4, 4>  G2BSEL;
		};
		static inline g2selr_t<base + 0x6C> G2SELR;


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
		static inline g3selr_t<base + 0x6D> G3SELR;


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
		static inline g4selr_t<base + 0x6E> G4SELR;


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
		static inline g5selr_t<base + 0x6F> G5SELR;


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
		static inline g6selr_t<base + 0x70> G6SELR;


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
		static inline g7selr_t<base + 0x71> G7SELR;


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
		static inline g8selr_t<base + 0x72> G8SELR;


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
		static inline g9selr_t<base + 0x73> G9SELR;
	};
	typedef poe3_t<0x0009'E400> POE3;
}
