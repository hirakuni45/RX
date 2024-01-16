#pragma once
//=====================================================================//
/*!	@file
	@brief	RX231 ポートアウトプットイネーブル POE2a 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  POE2a クラス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <peripheral per>
	struct poe2_t {

		static constexpr auto PERIPHERAL = per;			///< ペリフェラル型
		static constexpr auto OEI1 = ICU::VECTOR::OEI1;	///< OEI1 割り込みベクター
		static constexpr auto OEI2 = ICU::VECTOR::OEI2;	///< OEI2 割り込みベクター


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

			bits_rw_t<io_, bitpos::B0, 2>  POE0M;
			bits_rw_t<io_, bitpos::B2, 2>  POE1M;
			bits_rw_t<io_, bitpos::B4, 2>  POE2M;
			bits_rw_t<io_, bitpos::B6, 2>  POE3M;
			bit_rw_t <io_, bitpos::B8>     PIE1;

			bit_rw_t <io_, bitpos::B12>    POE0F;
			bit_rw_t <io_, bitpos::B13>    POE1F;
			bit_rw_t <io_, bitpos::B14>    POE2F;
			bit_rw_t <io_, bitpos::B15>    POE3F;
		};
		typedef icsr1_t<0x0008'8900> ICSR1_;
		static  ICSR1_ ICSR1;


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
		typedef ocsr1_t<0x0008'8902> OCSR1_;
		static  OCSR1_ OCSR1;


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

			bits_rw_t<io_, bitpos::B0, 2>  POE4M;

			bit_rw_t <io_, bitpos::B8>     PIE2;
			bit_rw_t <io_, bitpos::B9>     POE8E;

			bit_rw_t <io_, bitpos::B12>    POE8F;
		};
		typedef icsr2_t<0x0008'8908> ICSR2_;
		static  ICSR2_ ICSR2;


		//-----------------------------------------------------------------//
		/*!
			@brief	ソフトウェアポートアウトプットイネーブルレジスタ（SPOER）
			@param[in]	base	ベースアドレス
		*/
		//-----------------------------------------------------------------//
		template <uint32_t base>
		struct spoer_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  CH34HIZ;
			bit_rw_t<io_, bitpos::B1>  CH0HIZ;
		};
		typedef spoer_t<0x0008'890A> SPOER_;
		static  SPOER_ SPOER;


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

			bit_rw_t<io_, bitpos::B0>  PE0ZE;
			bit_rw_t<io_, bitpos::B1>  PE1ZE;
			bit_rw_t<io_, bitpos::B2>  PE2ZE;
			bit_rw_t<io_, bitpos::B3>  PE3ZE;
		};
		typedef poecr1_t<0x0008'890B> POECR1_;
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

			bit_rw_t<io_, bitpos::B4>   P3CZE;
			bit_rw_t<io_, bitpos::B5>   P2CZE;
			bit_rw_t<io_, bitpos::B6>   P1CZE;
		};
		typedef poecr2_t<0x0008'890C> POECR2_;
		static  POECR2_ POECR2;


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

			bit_rw_t <io_, bitpos::B9>     OSTSTE;

			bit_rw_t <io_, bitpos::B12>    OSTSTF;
		};
		typedef icsr3_t<0x0008'890E> ICSR3_;
		static  ICSR3_ ICSR3;
	};
	template <peripheral per> typename poe2_t<per>::ICSR1_  poe2_t<per>::ICSR1;
	template <peripheral per> typename poe2_t<per>::OCSR1_  poe2_t<per>::OCSR1;
	template <peripheral per> typename poe2_t<per>::ICSR2_  poe2_t<per>::ICSR2;
	template <peripheral per> typename poe2_t<per>::SPOER_  poe2_t<per>::SPOER;
	template <peripheral per> typename poe2_t<per>::POECR1_ poe2_t<per>::POECR1;
	template <peripheral per> typename poe2_t<per>::POECR2_ poe2_t<per>::POECR2;
	template <peripheral per> typename poe2_t<per>::ICSR3_  poe2_t<per>::ICSR3;

	typedef poe2_t<peripheral::POE2> POE2;
}
