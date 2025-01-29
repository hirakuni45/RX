#pragma once
//=============================================================================//
/*!	@file
	@brief	I2C-bus Interface / I2C バスインタフェース @n
			RX110/RX111/RX113/RX130/RX140 @n
			RX220 @n
			RX230/RX231 @n
			RX23W @n
			RX24T/RX24U/RX260/RX261/RX26T @n
			RX621/RX62N @n
			RX631/RX63N @n
			RX66T/RX72T @n
			RX64M/RX71M/RX65N/RX660/RX671 (RIICa)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RIIC core class
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
		static inline iccr1_t<base + 0x00> ICCR1;


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
		static inline iccr2_t<base + 0x01> ICCR2;


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
		static inline icmr1_t<base + 0x02> ICMR1;


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
		static inline icmr2_t<base + 0x03> ICMR2;


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
		static inline icmr3_t<base + 0x04> ICMR3;


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
		static inline icfer_t<base + 0x05> ICFER;


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
		static inline icser_t<base + 0x06> ICSER;


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
		static inline icier_t<base + 0x07> ICIER;


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
		static inline icsr1_t<base + 0x08> ICSR1;


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
		static inline icsr2_t<base + 0x09> ICSR2;


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
		static inline sarly_t<base + 0x0A> SARL0;
		static inline sarly_t<base + 0x0C> SARL1;
		static inline sarly_t<base + 0x0E> SARL2;


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
		static inline saruy_t<base + 0x0B> SARU0;
		static inline saruy_t<base + 0x0D> SARU1;
		static inline saruy_t<base + 0x0F> SARU2;


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
		static inline icbrl_t<base + 0x10> ICBRL;


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
		static inline icbrh_t<base + 0x11> ICBRH;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バス送信データレジスタ (ICDRT)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw8_t<base + 0x12> ICDRT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  I 2 C バス受信データレジスタ (ICDRR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw8_t<base + 0x13> ICDRR;
	};


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
		static inline rw8_t<base + 0x0A> TMOCNTL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイムアウト 内部カウンタ（TMOCNTU）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw8_t<base + 0x0B> TMOCNTU;
	};


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

#if defined(SIG_RX110) || defined(SIG_RX111) || defined(SIG_RX113) || defined(SIG_RX130) || defined(SIG_RX140) || defined(SIG_RX220) || defined(SIG_RX230) || defined(SIG_RX231) || defined(SIG_RX23W) || defined(SIG_RX13T) || defined(SIG_RX23T) || defined(SIG_RX24T) || defined(SIG_RX24U) || defined(SIG_RX260) || defined(SIG_RX261)
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
#elif defined(SIG_RX660)
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
