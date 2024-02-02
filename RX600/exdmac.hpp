#pragma once
//=============================================================================//
/*!	@file
	@brief	RX64M, RX71M, RX65[1N], RX66N, RX72[NM] EXDMAC 定義 (EXDMACa)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  exdmac core 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct exdmac_core_t {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA 転送元アドレスレジスタ（EDMSAR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x00> EDMSAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA 転送先アドレスレジスタ（EDMDAR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x04> EDMDAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA 転送カウントレジスタ（EDMCRA）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x08> EDMCRA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA ブロック転送カウントレジスタ（EDMCRB）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw16_t<base + 0x0C> EDMCRB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA 転送モードレジスタ（EDMTMD）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edmtmd_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  DCTG;

			bits_rw_t<io_, bitpos::B8, 2>  SZ;

			bits_rw_t<io_, bitpos::B12, 2> DTS;
			bits_rw_t<io_, bitpos::B14, 2> MD;
		};
		static inline edmtmd_t<base + 0x10> EDMTMD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA 出力設定レジスタ（EDMOMD）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edmomd_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DACKSEL;
			bit_rw_t<io_, bitpos::B1> DACKW;
			bit_rw_t<io_, bitpos::B2> DACKE;
			bit_rw_t<io_, bitpos::B3> DACKS;
		};
		static inline edmomd_t<base + 0x12> EDMOMD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA 割り込み設定レジスタ（EDMINT）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edmint_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DARIE;
			bit_rw_t<io_, bitpos::B1> SARIE;
			bit_rw_t<io_, bitpos::B2> RPTIE;
			bit_rw_t<io_, bitpos::B3> ESIE;
			bit_rw_t<io_, bitpos::B4> DTIE;
		};
		static inline edmint_t<base + 0x13> EDMINT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA アドレスモードレジスタ（EDMAMD）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edmamd_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  5>  DARA;

			bits_rw_t<io_, bitpos::B6,  2>  DM;
			bits_rw_t<io_, bitpos::B8,  5>  SARA;

			bits_rw_t<io_, bitpos::B14, 2>  SM;
			bit_rw_t <io_, bitpos::B16>     DIR;
			bit_rw_t <io_, bitpos::B17>     AMS;
		};
		static inline edmamd_t<base + 0x14> EDMAMD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA 転送許可レジスタ（EDMCNT）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edmcnt_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DTE;
		};
		static inline edmcnt_t<base + 0x1C> EDMCNT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA ソフトウェア起動レジスタ（EDMREQ）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edmreq_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SWREQ;
			bit_rw_t<io_, bitpos::B4> CLRS;
		};
		static inline edmreq_t<base + 0x1D> EDMREQ;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA ステータスレジスタ（EDMSTS）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edmsts_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> ESIF;

			bit_rw_t<io_, bitpos::B4> DTIF;

			bit_ro_t<io_, bitpos::B7> ACT;
		};
		static inline edmsts_t<base + 0x1E> EDMSTS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA 外部要求センスモードレジスタ（EDMRMD）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edmrmd_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> DREQS;
		};
		static inline edmrmd_t<base + 0x20> EDMRMD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA 外部要求フラグレジスタ（EDMERF）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edmerf_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> EREQ;
		};
		static inline edmerf_t<base + 0x21> EDMERF;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA 周辺要求フラグレジスタ（EDMPRF）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edmprf_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> PREQ;
		};
		static inline edmprf_t<base + 0x22> EDMPRF;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  exdmac 定義（EXDMAC0、EXDMAC1 共通クラス）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct exdmac_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA モジュール起動レジスタ（EDMAST）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edmast_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DMST;
		};
		static inline edmast_t<0x0008'2A00> EDMAST;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  クラスタバッファレジスタ y（CLSBRy）（y = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<0x0008'2BE0> CLSBR0;
		static inline rw32_t<0x0008'2BE4> CLSBR1;
		static inline rw32_t<0x0008'2BE8> CLSBR2;
		static inline rw32_t<0x0008'2BEC> CLSBR3;
		static inline rw32_t<0x0008'2BF0> CLSBR4;
		static inline rw32_t<0x0008'2BF4> CLSBR5;
		static inline rw32_t<0x0008'2BF8> CLSBR6;
		static inline rw32_t<0x0008'2BFC> CLSBR7;
	};
	typedef exdmac_t EXDMAC;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  edmac 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	ivec	割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR ivec>
	struct exdmac0_t : public exdmac_core_t<base, per> {

		static constexpr auto IVEC = ivec;

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA オフセットレジスタ（EDMOFR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x18> EDMOFR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  edmac 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	ivec	割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR ivec>
	struct exdmac1_t : public exdmac_core_t<base, per> {

		static constexpr auto IVEC = ivec;

	};

#if defined(SIG_RX621) || defined(SIG_RX62N)
	typedef exdmac0_t<0x0008'2800, peripheral::EXDMAC0, ICU::VECTOR::EXDMACI0> EXDMAC0;
	typedef exdmac1_t<0x0008'2840, peripheral::EXDMAC1, ICU::VECTOR::EXDMACI1> EXDMAC1;
#else
	typedef exdmac0_t<0x0008'2800, peripheral::EXDMAC0, ICU::VECTOR::EXDMAC0I> EXDMAC0;
	typedef exdmac1_t<0x0008'2840, peripheral::EXDMAC1, ICU::VECTOR::EXDMAC1I> EXDMAC1;
#endif
}
