#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M グループ　RIICa 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"
#include "RX64M/peripheral.hpp"
#include "RX64M/icu.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  I2C 定義
		@param[in]	base	ベース・アドレス
		@param[in]	t		ペリフェラル型
		@param[in]	txv		送信ベクター
		@param[in]	rxv		受信ベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral t, ICU::VECTOR txv, ICU::VECTOR rxv>
	struct i2c_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バスコントロールレジスタ 1 (ICCR1)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct iccr1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SDAI;
			bit_rw_t<io_, bitpos::B1> SCLI;
			bit_rw_t<io_, bitpos::B2> SDAO;
			bit_rw_t<io_, bitpos::B3> SCLO;
			bit_rw_t<io_, bitpos::B4> SOWP;
			bit_rw_t<io_, bitpos::B5> CLO;
			bit_rw_t<io_, bitpos::B6> IICRST;
			bit_rw_t<io_, bitpos::B7> ICE;
		};
		static iccr1_t<base + 0x00> ICCR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バスコントロールレジスタ 2 (ICCR2)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct iccr2_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B1> ST;
			bit_rw_t<io_, bitpos::B2> RS;
			bit_rw_t<io_, bitpos::B3> SP;
			bit_rw_t<io_, bitpos::B5> TRS;
			bit_rw_t<io_, bitpos::B6> MST;
			bit_rw_t<io_, bitpos::B7> BBSY;
		};
		static iccr2_t<base + 0x01> ICCR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バスモードレジスタ 1 (ICMR1)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icmr1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> BC;
			bit_rw_t <io_, bitpos::B3>    BCWP;
			bits_rw_t<io_, bitpos::B4, 3> CKS;
			bit_rw_t <io_, bitpos::B7>    MTWP;
		};
		static icmr1_t<base + 0x02> ICMR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バスモードレジスタ 2 (ICMR2)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icmr2_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    TMOS;
			bit_rw_t <io_, bitpos::B1>    TMOL;
			bit_rw_t <io_, bitpos::B2>    TMOH;
			bits_rw_t<io_, bitpos::B4, 3> SDDL;
			bit_rw_t <io_, bitpos::B7>    DLCS;
		};
		static icmr2_t<base + 0x03> ICMR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バスモードレジスタ 3 (ICMR3)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icmr3_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> NF;
			bit_rw_t <io_, bitpos::B2>    ACKBR;
			bit_rw_t <io_, bitpos::B3>    ACKBT;
			bit_rw_t <io_, bitpos::B4>    ACKWP;
			bit_rw_t <io_, bitpos::B5>    RDRFS;
			bit_rw_t <io_, bitpos::B6>    WAIT;
			bit_rw_t <io_, bitpos::B7>    SMBS;
		};
		static icmr3_t<base + 0x04> ICMR3;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バスファンクション許可レジスタ (ICFER)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icfer_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TMOE;
			bit_rw_t<io_, bitpos::B1> MALE;
			bit_rw_t<io_, bitpos::B2> NALE;
			bit_rw_t<io_, bitpos::B3> SALE;
			bit_rw_t<io_, bitpos::B4> NACKE;
			bit_rw_t<io_, bitpos::B5> NFE;
			bit_rw_t<io_, bitpos::B6> SCLE;
			// bit_rw_t<io_, bitpos::B7> FMPE;
		};
		static icfer_t<base + 0x05> ICFER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バスステータス許可レジスタ (ICSER)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icser_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SAR0E;
			bit_rw_t<io_, bitpos::B1> SAR1E;
			bit_rw_t<io_, bitpos::B2> SAR2E;
			bit_rw_t<io_, bitpos::B3> GCAE;
			bit_rw_t<io_, bitpos::B5> DIDE;
			bit_rw_t<io_, bitpos::B7> HOAE;
		};
		static icser_t<base + 0x06> ICSER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バス割り込み許可レジスタ (ICIER)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icier_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TMOIE;
			bit_rw_t<io_, bitpos::B1> ALIE;
			bit_rw_t<io_, bitpos::B2> STIE;
			bit_rw_t<io_, bitpos::B3> SPIE;
			bit_rw_t<io_, bitpos::B4> NAKIE;
			bit_rw_t<io_, bitpos::B5> RIE;
			bit_rw_t<io_, bitpos::B6> TEIE;
			bit_rw_t<io_, bitpos::B7> TIE;
		};
		static icier_t<base + 0x07> ICIER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バスステータスレジスタ 1 (ICSR1)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icsr1_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> AAS0;
			bit_rw_t<io_, bitpos::B1> AAS1;
			bit_rw_t<io_, bitpos::B2> AAS2;
			bit_rw_t<io_, bitpos::B3> GCA;
			bit_rw_t<io_, bitpos::B5> DID;
			bit_rw_t<io_, bitpos::B7> HOA;
		};
		static icsr1_t<base + 0x08> ICSR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バスステータスレジスタ 2 (ICSR2)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icsr2_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> TMOF;
			bit_rw_t<io_, bitpos::B1> AL;
			bit_rw_t<io_, bitpos::B2> START;
			bit_rw_t<io_, bitpos::B3> STOP;
			bit_rw_t<io_, bitpos::B4> NACKF;
			bit_rw_t<io_, bitpos::B5> RDRF;
			bit_rw_t<io_, bitpos::B6> TEND;
			bit_rw_t<io_, bitpos::B7> TDRE;
		};
		static icsr2_t<base + 0x09> ICSR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  スレーブアドレスレジスタ Ly (SARLy) (y=0 ～ 2)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct sarly_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    SVA0;
			bits_rw_t<io_, bitpos::B1, 7> SVA;
		};
		static sarly_t<base + 0x0A> SARL0;
		static sarly_t<base + 0x0C> SARL1;
		static sarly_t<base + 0x0E> SARL2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  スレーブアドレスレジスタ Uy (SARUy) (y=0 ～ 2)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct saruy_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    FS;
			bits_rw_t<io_, bitpos::B1, 2> SVA;
		};
		static saruy_t<base + 0x0B> SARU0;
		static saruy_t<base + 0x0D> SARU1;
		static saruy_t<base + 0x0F> SARU2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バスビットレート Low レジスタ (ICBRL)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icbrl_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t <io_, bitpos::B0, 5> BRL;
		};
		static icbrl_t<base + 0x10> ICBRL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バスビットレート High レジスタ (ICBRH)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icbrh_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t <io_, bitpos::B0, 5> BRH;
		};
		static icbrh_t<base + 0x11> ICBRH;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バス送信データレジスタ (ICDRT)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw8_t<base + 0x12> ICDRT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バス受信データレジスタ (ICDRR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw8_t<base + 0x13> ICDRR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  チャネルを返す
			@return チャネル
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static uint32_t get_chanel() {
			return (base >> 5) & 1;
		}

		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return t; }


		//-----------------------------------------------------------------//
		/*!
			@brief  送信割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR get_tx_vec() { return txv; }


		//-----------------------------------------------------------------//
		/*!
			@brief  受信割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR get_rx_vec() { return rxv; }
	};
	typedef i2c_t<0x00088300, peripheral::RIIC0, ICU::VECTOR::RIIC_TXI0, ICU::VECTOR::RIIC_RXI0> RIIC0;
	typedef i2c_t<0x00088340, peripheral::RIIC2, ICU::VECTOR::RIIC_TXI2, ICU::VECTOR::RIIC_RXI2> RIIC2;
}
