#pragma once
//=============================================================================//
/*!	@file
	@brief	RX220 RIIC @n
			RX231 RIIC @n
			RX621/RX62N RIIC 定義 @n
			RX631/RX63N RIIC 定義 @n
			RX64M/RX71M/RX65N/RX671 RIICa @n
			RX24T/RX26T/RX66T/RX72T 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  I 2 C バスインタフェース 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<uint32_t base>
	struct riic_core_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バスコントロールレジスタ 1 (ICCR1)
			@param[in]	ofs		レジスタ・アドレス・オフセット
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
		typedef iccr1_t<base + 0x00> ICCR1_;
		static ICCR1_ ICCR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バスコントロールレジスタ 2 (ICCR2)
			@param[in]	ofs		レジスタ・アドレス・オフセット
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
		typedef iccr2_t<base + 0x01> ICCR2_;
		static ICCR2_ ICCR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バスモードレジスタ 1 (ICMR1)
			@param[in]	ofs		レジスタ・アドレス・オフセット
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
		typedef icmr1_t<base + 0x02> ICMR1_;
		static ICMR1_ ICMR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バスモードレジスタ 2 (ICMR2)
			@param[in]	ofs		レジスタ・アドレス・オフセット
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
		typedef icmr2_t<base + 0x03> ICMR2_;
		static ICMR2_ ICMR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バスモードレジスタ 3 (ICMR3)
			@param[in]	ofs		レジスタ・アドレス・オフセット
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
		typedef icmr3_t<base + 0x04> ICMR3_;
		static ICMR3_ ICMR3;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バスファンクション許可レジスタ (ICFER)
			@param[in]	ofs		レジスタ・アドレス・オフセット
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
			bit_rw_t<io_, bitpos::B7> FMPE;
		};
		typedef icfer_t<base + 0x05> ICFER_;
		static ICFER_ ICFER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バスステータス許可レジスタ (ICSER)
			@param[in]	ofs		レジスタ・アドレス・オフセット
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
		typedef icser_t<base + 0x06> ICSER_;
		static ICSER_ ICSER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バス割り込み許可レジスタ (ICIER)
			@param[in]	ofs		レジスタ・アドレス・オフセット
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
		typedef icier_t<base + 0x07> ICIER_;
		static ICIER_ ICIER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バスステータスレジスタ 1 (ICSR1)
			@param[in]	ofs		レジスタ・アドレス・オフセット
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
		typedef icsr1_t<base + 0x08> ICSR1_;
		static ICSR1_ ICSR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バスステータスレジスタ 2 (ICSR2)
			@param[in]	ofs		レジスタ・アドレス・オフセット
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
		typedef icsr2_t<base + 0x09> ICSR2_;
		static ICSR2_ ICSR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  スレーブアドレスレジスタ Ly (SARLy) (y=0 ～ 2)
			@param[in]	ofs		レジスタ・アドレス・オフセット
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
		typedef sarly_t<base + 0x0A> SARL0_;
		typedef sarly_t<base + 0x0C> SARL1_;
		typedef sarly_t<base + 0x0E> SARL2_;
		static SARL0_ SARL0;
		static SARL1_ SARL1;
		static SARL2_ SARL2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  スレーブアドレスレジスタ Uy (SARUy) (y=0 ～ 2)
			@param[in]	ofs		レジスタ・アドレス・オフセット
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
		typedef saruy_t<base + 0x0B> SARU0_;
		typedef saruy_t<base + 0x0D> SARU1_;
		typedef saruy_t<base + 0x0F> SARU2_;
		static SARU0_ SARU0;
		static SARU1_ SARU1;
		static SARU2_ SARU2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バスビットレート Low レジスタ (ICBRL)
			@param[in]	ofs		レジスタ・アドレス・オフセット
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
		typedef icbrl_t<base + 0x10> ICBRL_;
		static ICBRL_ ICBRL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バスビットレート High レジスタ (ICBRH)
			@param[in]	ofs		レジスタ・アドレス・オフセット
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
		typedef icbrh_t<base + 0x11> ICBRH_;
		static ICBRH_ ICBRH;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バス送信データレジスタ (ICDRT)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<base + 0x12> ICDRT_;
		static ICDRT_ ICDRT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バス受信データレジスタ (ICDRR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<base + 0x13> ICDRR_;
		static ICDRR_ ICDRR;
	};
	template <uint32_t base> typename riic_core_t<base>::ICCR1_ riic_core_t<base>::ICCR1;
	template <uint32_t base> typename riic_core_t<base>::ICCR2_ riic_core_t<base>::ICCR2;
	template <uint32_t base> typename riic_core_t<base>::ICMR1_ riic_core_t<base>::ICMR1;
	template <uint32_t base> typename riic_core_t<base>::ICMR2_ riic_core_t<base>::ICMR2;
	template <uint32_t base> typename riic_core_t<base>::ICMR3_ riic_core_t<base>::ICMR3;
	template <uint32_t base> typename riic_core_t<base>::ICFER_ riic_core_t<base>::ICFER;
	template <uint32_t base> typename riic_core_t<base>::ICSER_ riic_core_t<base>::ICSER;
	template <uint32_t base> typename riic_core_t<base>::ICIER_ riic_core_t<base>::ICIER;
	template <uint32_t base> typename riic_core_t<base>::ICSR1_ riic_core_t<base>::ICSR1;
	template <uint32_t base> typename riic_core_t<base>::ICSR2_ riic_core_t<base>::ICSR2;
	template <uint32_t base> typename riic_core_t<base>::SARL0_ riic_core_t<base>::SARL0;
	template <uint32_t base> typename riic_core_t<base>::SARL1_ riic_core_t<base>::SARL1;
	template <uint32_t base> typename riic_core_t<base>::SARL2_ riic_core_t<base>::SARL2;
	template <uint32_t base> typename riic_core_t<base>::SARU0_ riic_core_t<base>::SARU0;
	template <uint32_t base> typename riic_core_t<base>::SARU1_ riic_core_t<base>::SARU1;
	template <uint32_t base> typename riic_core_t<base>::SARU2_ riic_core_t<base>::SARU2;
	template <uint32_t base> typename riic_core_t<base>::ICBRL_ riic_core_t<base>::ICBRL;
	template <uint32_t base> typename riic_core_t<base>::ICBRH_ riic_core_t<base>::ICBRH;
	template <uint32_t base> typename riic_core_t<base>::ICDRT_ riic_core_t<base>::ICDRT;
	template <uint32_t base> typename riic_core_t<base>::ICDRR_ riic_core_t<base>::ICDRR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  I 2 C バスインタフェース 定義（RIIC 型）
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txi		「送信データエンプティ」ベクター
		@param[in]	rxi		「受信データフル」ベクター
		@param[in]	eei		「通信エラー、通信イベント」ベクター
		@param[in]	tei		「送信終了」ベクター
		@param[in]	pclk	クロック元
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per,
		ICU::VECTOR txi, ICU::VECTOR rxi, ICU::VECTOR eei, ICU::VECTOR tei, uint32_t pclk>
	struct riic_t : riic_core_t<base> {
		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto TXI  = txi;		///< 受信割り込みベクター
		static constexpr auto RXI  = rxi;		///< 送信割り込みベクター
		static constexpr auto EEI  = eei;		///< 通信エラー、イベント割り込みベクター
		static constexpr auto TEI  = tei;		///< 送信終了割り込みベクター
		static constexpr auto PCLK = pclk;		///< クロック周波数


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイムアウト 内部カウンタ（TMOCNTL）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<base + 0x0A> TMOCNTL_;
		static TMOCNTL_ TMOCNTL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイムアウト 内部カウンタ（TMOCNTU）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<base + 0x0B> TMOCNTU_;
		static TMOCNTU_ TMOCNTU;
	};
	template <uint32_t base, peripheral per, ICU::VECTOR txi, ICU::VECTOR rxi, ICU::VECTOR eei, ICU::VECTOR tei, uint32_t pclk>
		typename riic_t<base, per, txi, rxi, eei, tei, pclk>::TMOCNTL_ riic_t<base, per, txi, rxi, eei, tei, pclk>::TMOCNTL;
	template <uint32_t base, peripheral per, ICU::VECTOR txi, ICU::VECTOR rxi, ICU::VECTOR eei, ICU::VECTOR tei, uint32_t pclk>
		typename riic_t<base, per, txi, rxi, eei, tei, pclk>::TMOCNTU_ riic_t<base, per, txi, rxi, eei, tei, pclk>::TMOCNTU;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  I 2 C バスインタフェース 定義（RIICa 型）
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txi		「送信データエンプティ」ベクター
		@param[in]	rxi		「受信データフル」ベクター
		@param[in]	INT		割り込みベクター型
		@param[in]	eei		「通信エラー、通信イベント」ベクター
		@param[in]	tei		「送信終了」ベクター
		@param[in]	pclk	クロック元
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per,
		ICU::VECTOR txi, ICU::VECTOR rxi, typename INT, INT eei, INT tei, uint32_t pclk>
	struct riica_t : riic_core_t<base> {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto TXI  = txi;		///< 受信割り込みベクター
		static constexpr auto RXI  = rxi;		///< 送信割り込みベクター
		static constexpr auto EEI  = eei;		///< 通信エラー、イベント割り込みベクター
		static constexpr auto TEI  = tei;		///< 送信終了割り込みベクター
		static constexpr auto PCLK = pclk;		///< クロック周波数
	};

#if defined(SIG_RX220) || defined(SIG_RX231) || defined(SIG_RX24T)
	typedef riica_t<0x0008'8300, peripheral::RIIC0, ICU::VECTOR::ICTXI0, ICU::VECTOR::ICRXI0,
		ICU::VECTOR, ICU::VECTOR::ICEEI0, ICU::VECTOR::ICTEI0, clock_profile::PCLKB> RIIC0;
#elif defined(SIG_RX63T) || defined(SIG_RX63T_S)
	typedef riic_t<0x0008'8300, peripheral::RIIC0, ICU::VECTOR::ICTXI0, ICU::VECTOR::ICRXI0,
		ICU::VECTOR::ICEEI0, ICU::VECTOR::ICTEI0, clock_profile::PCLKB> RIIC0;
	typedef riic_t<0x0008'8320, peripheral::RIIC1, ICU::VECTOR::ICTXI1, ICU::VECTOR::ICRXI1,
		ICU::VECTOR::ICEEI1, ICU::VECTOR::ICTEI1, clock_profile::PCLKB> RIIC1;
#elif defined(SIG_RX621) || defined(SIG_RX62N)
	typedef riic_t<0x0008'8300, peripheral::RIIC0, ICU::VECTOR::ICTXI0, ICU::VECTOR::ICRXI0,
		ICU::VECTOR::ICEEI0, ICU::VECTOR::ICTEI0, clock_profile::PCLK> RIIC0;
	typedef riic_t<0x0008'8320, peripheral::RIIC1, ICU::VECTOR::ICTXI1, ICU::VECTOR::ICRXI1,
		ICU::VECTOR::ICEEI1, ICU::VECTOR::ICTEI1, clock_profile::PCLK> RIIC1;
#elif defined(SIG_RX631) || defined(SIG_RX63N)
	typedef riic_t<0x0008'8300, peripheral::RIIC0, ICU::VECTOR::ICTXI0, ICU::VECTOR::ICRXI0,
		ICU::VECTOR::ICEEI0, ICU::VECTOR::ICTEI0, clock_profile::PCLKB> RIIC0;
	typedef riic_t<0x0008'8320, peripheral::RIIC1, ICU::VECTOR::ICTXI1, ICU::VECTOR::ICRXI1,
		ICU::VECTOR::ICEEI1, ICU::VECTOR::ICTEI1, clock_profile::PCLKB> RIIC1;
	typedef riic_t<0x0008'8340, peripheral::RIIC2, ICU::VECTOR::ICTXI2, ICU::VECTOR::ICRXI2,
		ICU::VECTOR::ICEEI2, ICU::VECTOR::ICTEI2, clock_profile::PCLKB> RIIC2;
	typedef riic_t<0x0008'8360, peripheral::RIIC3, ICU::VECTOR::ICTXI3, ICU::VECTOR::ICRXI3,
		ICU::VECTOR::ICEEI3, ICU::VECTOR::ICTEI3, clock_profile::PCLKB> RIIC3;
#elif defined(SIG_RX64M) || defined(SIG_RX71M)
	typedef riica_t<0x0008'8300, peripheral::RIIC0, ICU::VECTOR::ICTXI0, ICU::VECTOR::ICRXI0,
		ICU::GROUPBL1, ICU::GROUPBL1::EEI0, ICU::GROUPBL1::TEI0, clock_profile::PCLKB> RIIC0;
	typedef riica_t<0x0008'8340, peripheral::RIIC2, ICU::VECTOR::ICTXI2, ICU::VECTOR::ICRXI2,
		ICU::GROUPBL1, ICU::GROUPBL1::EEI2, ICU::GROUPBL1::TEI2, clock_profile::PCLKB> RIIC2;
#elif defined(SIG_RX65N) || defined(SIG_RX671) || defined(SIG_RX72M) || defined(SIG_RX72N) || defined(SIG_RX66N)
	typedef riica_t<0x0008'8300, peripheral::RIIC0, ICU::VECTOR::ICTXI0, ICU::VECTOR::ICRXI0,
		ICU::GROUPBL1, ICU::GROUPBL1::EEI0, ICU::GROUPBL1::TEI0, clock_profile::PCLKB> RIIC0;
	typedef riica_t<0x0008'8320, peripheral::RIIC1, ICU::VECTOR::ICTXI1, ICU::VECTOR::ICRXI1,
		ICU::GROUPBL1, ICU::GROUPBL1::EEI1, ICU::GROUPBL1::TEI1, clock_profile::PCLKB> RIIC1;
	typedef riica_t<0x0008'8340, peripheral::RIIC2, ICU::VECTOR::ICTXI2, ICU::VECTOR::ICRXI2,
		ICU::GROUPBL1, ICU::GROUPBL1::EEI2, ICU::GROUPBL1::TEI2, clock_profile::PCLKB> RIIC2;
#elif defined(SIG_RX26T) || defined(SIG_RX66T) || defined(SIG_RX72T)
	typedef riica_t<0x0008'8300, peripheral::RIIC0, ICU::VECTOR::ICTXI0, ICU::VECTOR::ICRXI0,
		ICU::GROUPBL1, ICU::GROUPBL1::EEI0, ICU::GROUPBL1::TEI0, clock_profile::PCLKB> RIIC0;
#endif
}
