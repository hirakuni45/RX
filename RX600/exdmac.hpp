#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ　EXDMAC 定義 (a)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2020 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
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

		static const auto PERIPHERAL = per;	///< ペリフェラル型

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA 転送元アドレスレジスタ（EDMSAR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x00> EDMSAR_;
		static  EDMSAR_ EDMSAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA 転送先アドレスレジスタ（EDMDAR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x04> EDMDAR_;
		static  EDMDAR_ EDMDAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA 転送カウントレジスタ（EDMCRA）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x08> EDMCRA_;
		static  EDMCRA_ EDMCRA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA ブロック転送カウントレジスタ（EDMCRB）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<base + 0x0C> EDMCRB_;
		static  EDMCRB_ EDMCRB;


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
		typedef edmtmd_t<base + 0x10> EDMTMD_;
		static  EDMTMD_ EDMTMD;


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
		typedef edmomd_t<base + 0x12> EDMOMD_;
		static  EDMOMD_ EDMOMD;


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
		typedef edmint_t<base + 0x13> EDMINT_;
		static  EDMINT_ EDMINT;


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

			bits_rw_t<io_, bitpos::B0,  4>  DARA;

			bits_rw_t<io_, bitpos::B6,  2>  DM;
			bits_rw_t<io_, bitpos::B8,  4>  SARA;

			bits_rw_t<io_, bitpos::B14, 2>  SM;
			bit_rw_t <io_, bitpos::B16>     DIR;
			bit_rw_t <io_, bitpos::B17>     AMS;
		};
		typedef edmamd_t<base + 0x14> EDMAMD_;
		static  EDMAMD_ EDMAMD;


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
		typedef edmcnt_t<base + 0x1C> EDMCNT_;
		static  EDMCNT_ EDMCNT;


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
		typedef edmreq_t<base + 0x1D> EDMREQ_;
		static  EDMREQ_ EDMREQ;


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
		typedef edmsts_t<base + 0x1E> EDMSTS_;
		static  EDMSTS_ EDMSTS;


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
		typedef edmrmd_t<base + 0x20> EDMRMD_;
		static  EDMRMD_ EDMRMD;


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
		typedef edmerf_t<base + 0x21> EDMERF_;
		static  EDMERF_ EDMERF;


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
		typedef edmprf_t<base + 0x22> EDMPRF_;
		static  EDMPRF_ EDMPRF;


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
		typedef edmast_t<0x00082A00> EDMAST_;
		static  EDMAST_ EDMAST;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  クラスタバッファレジスタ y（CLSBRy）（y = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<0x00082BE0> CLSBR0_;
		static  CLSBR0_ CLSBR0;
		typedef rw32_t<0x00082BE4> CLSBR1_;
		static  CLSBR1_ CLSBR1;
		typedef rw32_t<0x00082BE8> CLSBR2_;
		static  CLSBR2_ CLSBR2;
		typedef rw32_t<0x00082BEC> CLSBR3_;
		static  CLSBR3_ CLSBR3;
		typedef rw32_t<0x00082BF0> CLSBR4_;
		static  CLSBR4_ CLSBR4;
		typedef rw32_t<0x00082BF4> CLSBR5_;
		static  CLSBR5_ CLSBR5;
		typedef rw32_t<0x00082BF8> CLSBR6_;
		static  CLSBR6_ CLSBR6;
		typedef rw32_t<0x00082BFC> CLSBR7_;
		static  CLSBR7_ CLSBR7;
	};
	template <uint32_t base, peripheral per> typename exdmac_core_t<base, per>::EDMSAR_ exdmac_core_t<base, per>::EDMSAR;
	template <uint32_t base, peripheral per> typename exdmac_core_t<base, per>::EDMDAR_ exdmac_core_t<base, per>::EDMDAR;
	template <uint32_t base, peripheral per> typename exdmac_core_t<base, per>::EDMCRA_ exdmac_core_t<base, per>::EDMCRA;
	template <uint32_t base, peripheral per> typename exdmac_core_t<base, per>::EDMCRB_ exdmac_core_t<base, per>::EDMCRB;
	template <uint32_t base, peripheral per> typename exdmac_core_t<base, per>::EDMTMD_ exdmac_core_t<base, per>::EDMTMD;
	template <uint32_t base, peripheral per> typename exdmac_core_t<base, per>::EDMOMD_ exdmac_core_t<base, per>::EDMOMD;
	template <uint32_t base, peripheral per> typename exdmac_core_t<base, per>::EDMINT_ exdmac_core_t<base, per>::EDMINT;
	template <uint32_t base, peripheral per> typename exdmac_core_t<base, per>::EDMAMD_ exdmac_core_t<base, per>::EDMAMD;
	template <uint32_t base, peripheral per> typename exdmac_core_t<base, per>::EDMCNT_ exdmac_core_t<base, per>::EDMCNT;
	template <uint32_t base, peripheral per> typename exdmac_core_t<base, per>::EDMREQ_ exdmac_core_t<base, per>::EDMREQ;
	template <uint32_t base, peripheral per> typename exdmac_core_t<base, per>::EDMSTS_ exdmac_core_t<base, per>::EDMSTS;
	template <uint32_t base, peripheral per> typename exdmac_core_t<base, per>::EDMRMD_ exdmac_core_t<base, per>::EDMRMD;
	template <uint32_t base, peripheral per> typename exdmac_core_t<base, per>::EDMERF_ exdmac_core_t<base, per>::EDMERF;
	template <uint32_t base, peripheral per> typename exdmac_core_t<base, per>::EDMPRF_ exdmac_core_t<base, per>::EDMPRF;
	template <uint32_t base, peripheral per> typename exdmac_core_t<base, per>::EDMAST_ exdmac_core_t<base, per>::EDMAST;
	template <uint32_t base, peripheral per> typename exdmac_core_t<base, per>::CLSBR0_ exdmac_core_t<base, per>::CLSBR0;
	template <uint32_t base, peripheral per> typename exdmac_core_t<base, per>::CLSBR1_ exdmac_core_t<base, per>::CLSBR1;
	template <uint32_t base, peripheral per> typename exdmac_core_t<base, per>::CLSBR2_ exdmac_core_t<base, per>::CLSBR2;
	template <uint32_t base, peripheral per> typename exdmac_core_t<base, per>::CLSBR3_ exdmac_core_t<base, per>::CLSBR3;
	template <uint32_t base, peripheral per> typename exdmac_core_t<base, per>::CLSBR4_ exdmac_core_t<base, per>::CLSBR4;
	template <uint32_t base, peripheral per> typename exdmac_core_t<base, per>::CLSBR5_ exdmac_core_t<base, per>::CLSBR5;
	template <uint32_t base, peripheral per> typename exdmac_core_t<base, per>::CLSBR6_ exdmac_core_t<base, per>::CLSBR6;
	template <uint32_t base, peripheral per> typename exdmac_core_t<base, per>::CLSBR7_ exdmac_core_t<base, per>::CLSBR7;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  edmac 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct exdmac0_t : public exdmac_core_t<base, per> {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA オフセットレジスタ（EDMOFR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x18> EDMOFR_;
		static  EDMOFR_ EDMOFR;
	};
	template <uint32_t base, peripheral per> typename exdmac0_t<base, per>::EDMOFR_ exdmac0_t<base, per>::EDMOFR;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  edmac 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct exdmac1_t : public exdmac_core_t<base, per> {
	};


	typedef exdmac0_t<0x00082800, peripheral::EXDMAC0>  EXDMAC0;
	typedef exdmac1_t<0x00082840, peripheral::EXDMAC1>  EXDMAC1;
}
