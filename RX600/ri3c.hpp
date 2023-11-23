#pragma once
//=============================================================================//
/*!	@file
	@brief	RX26T RI3C
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2023 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  I3C バスインタフェースコア・クラス
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<uint32_t base>
	struct ri3c_core_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モードレジスタ (ICMR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icmr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>      OMS;
		};
		typedef icmr_t<base + 0x00> ICMR_;
		static  ICMR_ ICMR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  制御レジスタ (ICCR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct iccr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>      IBAINC;

			bit_rw_t<io_, bitpos::B8>      HJC;

			bit_rw_t<io_, bitpos::B29>     ABORT;
			bit_rw_t<io_, bitpos::B30>     RESUME;
			bit_rw_t<io_, bitpos::B31>     ICE;
		};
		typedef iccr_t<base + 0x14> ICCR_;
		static  ICCR_ ICCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  コントローラデバイスアドレスレジスタ (ICCAR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct iccar_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 7>  DARD;
	
			bit_rw_t <io_, bitpos::B31>     DAV;
		};
		typedef iccar_t<base + 0x18> ICCAR_;
		static  ICCAR_ ICCAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  リセット制御レジスタ (ICRCR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icrcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bit_rw_t <io_, bitpos::B0>      MRST;
			bit_rw_t <io_, bitpos::B1>      CQRST;
			bit_rw_t <io_, bitpos::B2>      RQRST;
			bit_rw_t <io_, bitpos::B3>      TBRST;
			bit_rw_t <io_, bitpos::B4>      RBRST;
			bit_rw_t <io_, bitpos::B5>      IQRST;
			bit_rw_t <io_, bitpos::B6>      SQRST;

			bit_rw_t <io_, bitpos::B16>     ISRST;
		};
		typedef icrcr_t<base + 0x20> ICRCR_;
		static  ICRCR_ ICRCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	動作モードモニタレジスタ (ICMMR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icmmr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bit_rw_t <io_, bitpos::B2>      ACF;

			bit_rw_t <io_, bitpos::B7>      WP;
		};
		typedef icmmr_t<base + 0x24> ICMMR_;
		static  ICMMR_ ICMMR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	内部ステータスレジスタ (ICISR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icisr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bit_rw_t <io_, bitpos::B10>     BERF;
		};
		typedef icisr_t<base + 0x30> ICISR_;
		static  ICISR_ ICISR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	内部ステータス検出許可レジスタ (ICISER)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct iciser_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bit_rw_t <io_, bitpos::B10>     BERDE;
		};
		typedef iciser_t<base + 0x34> ICISER_;
		static  ICISER_ ICISER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	内部ステータス割り込み許可レジスタ (ICISIER)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icisier_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bit_rw_t <io_, bitpos::B10>     BERIE;
		};
		typedef icisier_t<base + 0x38> ICISIER_;
		static  ICISIER_ ICISIER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	デバイス特性テーブルインデックスレジスタ (ICDCTIR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icdctir_t : public ro32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();
	
			bits_ro_t<in_, bitpos::B19, 5>  INDEX;
		};
		typedef icdctir_t<base + 0x44> ICDCTIR_;
		static  ICDCTIR_ ICDCTIR;






	};
	template <uint32_t base> typename ri3c_core_t<base>::ICMR_    ri3c_core_t<base>::ICMR;
	template <uint32_t base> typename ri3c_core_t<base>::ICCR_    ri3c_core_t<base>::ICCR;
	template <uint32_t base> typename ri3c_core_t<base>::ICCAR_   ri3c_core_t<base>::ICCAR;
	template <uint32_t base> typename ri3c_core_t<base>::ICRCR_   ri3c_core_t<base>::ICRCR;
	template <uint32_t base> typename ri3c_core_t<base>::ICMMR_   ri3c_core_t<base>::ICMMR;
	template <uint32_t base> typename ri3c_core_t<base>::ICISR_   ri3c_core_t<base>::ICISR;
	template <uint32_t base> typename ri3c_core_t<base>::ICISER_  ri3c_core_t<base>::ICISER;
	template <uint32_t base> typename ri3c_core_t<base>::ICISIER_ ri3c_core_t<base>::ICISIER;
	template <uint32_t base> typename ri3c_core_t<base>::ICDCTIR_ ri3c_core_t<base>::ICDCTIR;





#if 0
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  I3C バスインタフェース (RI3C)
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txi		「送信データエンプティ」割り込みベクター
		@param[in]	rxi		「受信データフル」割り込みベクター
		@param[in]	eei		「通信エラー、通信イベント」割り込みベクター
		@param[in]	tei		「送信終了」割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per,
		ICU::VECTOR txi, ICU::VECTOR rxi, ICU::VECTOR eei, ICU::VECTOR tei>
	struct ri3c_t : ri3c_core_t<base> {
		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto TXI  = txi;		///< 受信割り込みベクター
		static constexpr auto RXI  = rxi;		///< 送信割り込みベクター
		static constexpr auto EEI  = eei;		///< 通信エラー、イベント割り込みベクター
		static constexpr auto TEI  = tei;		///< 送信終了割り込みベクター
		static constexpr auto PCLK = clock_profile::PCLKA;	///< クロック周波数
	};
//	template <uint32_t base, peripheral per, ICU::VECTOR txi, ICU::VECTOR rxi, ICU::VECTOR eei, ICU::VECTOR tei, uint32_t pclk>
//		typename riic_t<base, per, txi, rxi, eei, tei, pclk>::TMOCNTL_ riic_t<base, per, txi, rxi, eei, tei, pclk>::TMOCNTL;


#if defined(SIG_RX26T)
	typedef riica_t<0x000E'C000, peripheral::RI3C0, ICU::VECTOR::ICTXI0, ICU::VECTOR::ICRXI0,
		ICU::VECTOR, ICU::VECTOR::ICEEI0, ICU::VECTOR::ICTEI0, clock_profile::PCLKB> RIIC0;
#endif
#endif
}
