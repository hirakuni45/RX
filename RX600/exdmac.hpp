#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ　EXDMAC 定義 (a)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
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
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct exdmac_core_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA 転送元アドレスレジスタ（EDMSAR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x00> edmsar_t;
		static edmsar_t EDMSAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA 転送先アドレスレジスタ（EDMDAR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x04> edmdar_t;
		static edmdar_t EDMDAR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA 転送カウントレジスタ（EDMCRA）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x08> edmcra_t;
		static edmcra_t EDMCRA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA ブロック転送カウントレジスタ（EDMCRB）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw16_t<base + 0x0C> edmcrb_t;
		static edmcrb_t EDMCRB;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA 転送モードレジスタ（EDMTMD）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edmtmd_t_ : public rw32_t<ofs> {
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
		typedef edmtmd_t_<base + 0x10> edmtmd_t;
		static edmtmd_t EDMTMD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA 出力設定レジスタ（EDMOMD）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edmomd_t_ : public rw8_t<ofs> {
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
		typedef edmomd_t_<base + 0x12> edmomd_t;
		static edmomd_t EDMOMD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA 割り込み設定レジスタ（EDMINT）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edmint_t_ : public rw8_t<ofs> {
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
		typedef edmint_t_<base + 0x13> edmint_t;
		static edmint_t EDMINT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA アドレスモードレジスタ（EDMAMD）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edmamd_t_ : public rw32_t<ofs> {
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
		typedef edmamd_t_<base + 0x14> edmamd_t;
		static edmamd_t EDMAMD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA 転送許可レジスタ（EDMCNT）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edmcnt_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DTE;
		};
		typedef edmcnt_t_<base + 0x1C> edmcnt_t;
		static edmcnt_t EDMCNT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA ソフトウェア起動レジスタ（EDMREQ）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edmreq_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SWREQ;
			bit_rw_t<io_, bitpos::B4> CLRS;
		};
		typedef edmreq_t_<base + 0x1D> edmreq_t;
		static edmreq_t EDMREQ;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA ステータスレジスタ（EDMSTS）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edmsts_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> ESIF;
			bit_rw_t<io_, bitpos::B4> DTIF;

			bit_ro_t<io_, bitpos::B7> ACT;
		};
		typedef edmsts_t_<base + 0x1E> edmsts_t;
		static edmsts_t EDMSTS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA 外部要求センスモードレジスタ（EDMRMD）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edmrmd_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> DREQS;
		};
		typedef edmrmd_t_<base + 0x20> edmrmd_t;
		static edmrmd_t EDMRMD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA 外部要求フラグレジスタ（EDMERF）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edmerf_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> EREQ;
		};
		typedef edmerf_t_<base + 0x21> edmerf_t;
		static edmerf_t EDMERF;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA 周辺要求フラグレジスタ（EDMPRF）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edmprf_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> PREQ;
		};
		typedef edmprf_t_<base + 0x22> edmprf_t;
		static edmprf_t EDMPRF;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA モジュール起動レジスタ（EDMAST）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct edmast_t_ : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> DMST;
		};
		typedef edmast_t_<0x00082A00> edmast_t;
		static edmast_t EDMAST;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  クラスタバッファレジスタ y（CLSBRy）（y = 0 ～ 7）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<0x00082BE0> clsbr0_t;
		static clsbr0_t CLSBR0;
		typedef rw32_t<0x00082BE4> clsbr1_t;
		static clsbr1_t CLSBR1;
		typedef rw32_t<0x00082BE8> clsbr2_t;
		static clsbr2_t CLSBR2;
		typedef rw32_t<0x00082BEC> clsbr3_t;
		static clsbr3_t CLSBR3;
		typedef rw32_t<0x00082BF0> clsbr4_t;
		static clsbr4_t CLSBR4;
		typedef rw32_t<0x00082BF4> clsbr5_t;
		static clsbr5_t CLSBR5;
		typedef rw32_t<0x00082BF8> clsbr6_t;
		static clsbr6_t CLSBR6;
		typedef rw32_t<0x00082BFC> clsbr7_t;
		static clsbr7_t CLSBR7;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  edmac 定義
		@param[in]	base	ベース・アドレス
		@param[in]	t		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral t>
	struct exdmac0_t : public exdmac_core_t<base> {


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  EXDMA オフセットレジスタ（EDMOFR）
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x18> edmofr_t;
		static edmofr_t EDMOFR;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return t; }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  edmac 定義
		@param[in]	base	ベース・アドレス
		@param[in]	t		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral t>
	struct exdmac1_t : public exdmac_core_t<base> {


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return t; }
	};

	typedef exdmac0_t<0x00082800, peripheral::EXDMAC0>  EXDMAC0;
	typedef exdmac1_t<0x00082840, peripheral::EXDMAC1>  EXDMAC1;

	template <uint32_t base> typename exdmac_core_t<base>::edmsar_t exdmac_core_t<base>::EDMSAR;
	template <uint32_t base> typename exdmac_core_t<base>::edmdar_t exdmac_core_t<base>::EDMDAR;
	template <uint32_t base> typename exdmac_core_t<base>::edmcra_t exdmac_core_t<base>::EDMCRA;
	template <uint32_t base> typename exdmac_core_t<base>::edmcrb_t exdmac_core_t<base>::EDMCRB;
	template <uint32_t base> typename exdmac_core_t<base>::edmtmd_t exdmac_core_t<base>::EDMTMD;
	template <uint32_t base> typename exdmac_core_t<base>::edmomd_t exdmac_core_t<base>::EDMOMD;
	template <uint32_t base> typename exdmac_core_t<base>::edmint_t exdmac_core_t<base>::EDMINT;
	template <uint32_t base> typename exdmac_core_t<base>::edmamd_t exdmac_core_t<base>::EDMAMD;
	template <uint32_t base> typename exdmac_core_t<base>::edmcnt_t exdmac_core_t<base>::EDMCNT;
	template <uint32_t base> typename exdmac_core_t<base>::edmreq_t exdmac_core_t<base>::EDMREQ;
	template <uint32_t base> typename exdmac_core_t<base>::edmsts_t exdmac_core_t<base>::EDMSTS;
	template <uint32_t base> typename exdmac_core_t<base>::edmrmd_t exdmac_core_t<base>::EDMRMD;
	template <uint32_t base> typename exdmac_core_t<base>::edmerf_t exdmac_core_t<base>::EDMERF;
	template <uint32_t base> typename exdmac_core_t<base>::edmprf_t exdmac_core_t<base>::EDMPRF;
	template <uint32_t base> typename exdmac_core_t<base>::edmast_t exdmac_core_t<base>::EDMAST;
	template <uint32_t base> typename exdmac_core_t<base>::clsbr0_t exdmac_core_t<base>::CLSBR0;
	template <uint32_t base> typename exdmac_core_t<base>::clsbr1_t exdmac_core_t<base>::CLSBR1;
	template <uint32_t base> typename exdmac_core_t<base>::clsbr2_t exdmac_core_t<base>::CLSBR2;
	template <uint32_t base> typename exdmac_core_t<base>::clsbr3_t exdmac_core_t<base>::CLSBR3;
	template <uint32_t base> typename exdmac_core_t<base>::clsbr4_t exdmac_core_t<base>::CLSBR4;
	template <uint32_t base> typename exdmac_core_t<base>::clsbr5_t exdmac_core_t<base>::CLSBR5;
	template <uint32_t base> typename exdmac_core_t<base>::clsbr6_t exdmac_core_t<base>::CLSBR6;
	template <uint32_t base> typename exdmac_core_t<base>::clsbr7_t exdmac_core_t<base>::CLSBR7;

	template<uint32_t base, peripheral t> typename exdmac0_t<base, t>::edmofr_t exdmac0_t<base, t>::EDMOFR;
}
