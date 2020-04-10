#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ　GLCDC 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/io_utils.hpp"
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  GLCDC 定義
		@param[in]	base	ベース・アドレス
		@param[in]	t		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral t>
	struct glcdc_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CLUT カラー構造体
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		struct clut_t {
			uint8_t		B;	///< B0-B7
			uint8_t		G;	///< B8-B15
			uint8_t		R;	///< B16-B23
			uint8_t		A;	///< B24-B31
			clut_t(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 255) :
				B(b), G(g), R(r), A(a) { }
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  カラールックアップテーブル (GRnCLUTm[k]) (n = 1, 2、m = 0, 1、k = 0 ～ 255)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grclut_t_ {
			volatile uint32_t& operator[] (uint32_t idx) {
				return *reinterpret_cast<volatile uint32_t*>(ofs + (idx & 0xff));
			}
		};
		typedef grclut_t_<base + 0x0000> gr1clut0_t;
		static gr1clut0_t GR1CLUT0;
		typedef grclut_t_<base + 0x0400> gr1clut1_t;
		static gr1clut1_t GR1CLUT1;
		typedef grclut_t_<base + 0x0800> gr2clut0_t;
		static gr2clut0_t GR2CLUT0;
		typedef grclut_t_<base + 0x0C00> gr2clut1_t;
		static gr2clut1_t GR2CLUT1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バックグラウンド画面生成部動作制御レジスタ (BGEN)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct bgen_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B16> SWRST;
			bit_rw_t<io_, bitpos::B8>  VEN;
			bit_rw_t<io_, bitpos::B0>  EN;
		};
		typedef bgen_t_<base + 0x1000> bgen_t;
		static bgen_t BGEN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  自走周期レジスタ (BGPERI)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct bgperi_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  FV;
			bits_rw_t<io_, bitpos::B0,  11>  FH;
		};
		typedef bgperi_t_<base + 0x1004> bgperi_t;
		static bgperi_t BGPERI;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  同期位置レジスタ (BGSYNC)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct bgsync_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 4>  VP;
			bits_rw_t<io_, bitpos::B0,  4>  HP;
		};
		typedef bgsync_t_<base + 0x1008> bgsync_t;
		static bgsync_t BGSYNC;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  垂直サイズレジスタ (BGVSIZE)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct bgvsize_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  VP;
			bits_rw_t<io_, bitpos::B0,  11>  VW;
		};
		typedef bgvsize_t_<base + 0x100C> bgvsize_t;
		static bgvsize_t BGVSIZE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  水平サイズレジスタ (BGHSIZE)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct bghsize_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  HP;
			bits_rw_t<io_, bitpos::B0,  11>  HW;
		};
		typedef bghsize_t_<base + 0x1010> bghsize_t;
		static bghsize_t BGHSIZE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  背景色レジスタ (BGCOLOR)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct bgcolor_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 8>  R;
			bits_rw_t<io_, bitpos::B8,  8>  G;
			bits_rw_t<io_, bitpos::B0,  8>  B;
		};
		typedef bgcolor_t_<base + 0x1014> bgcolor_t;
		static bgcolor_t BGCOLOR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バックグラウンド画面生成部ステータスモニタレジスタ (BGMON)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct bgmon_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B16> SWRST;
			bit_rw_t<io_, bitpos::B8>  VEN;
			bit_rw_t<io_, bitpos::B0>  EN;
		};
		typedef bgmon_t_<base + 0x1018> bgmon_t;
		static bgmon_t BGMON;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n レジスタ更新制御レジスタ (GRnVEN) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnven_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  VEN;
		};
		typedef grnven_t_<base + 0x1100> gr1ven_t;
		static gr1ven_t GR1VEN;
		typedef grnven_t_<base + 0x1200> gr2ven_t;
		static gr2ven_t GR2VEN;




		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n フレームバッファ読み出し制御レジスタ (GRnFLMRD) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnflmrd_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  RENB;
		};
		typedef grnflmrd_t_<base + 0x1104> gr1flmrd_t;
		static gr1flmrd_t GR1FLMRD;
		typedef grnflmrd_t_<base + 0x1204> gr2flmrd_t;
		static gr2flmrd_t GR2FLMRD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n フレームバッファ制御レジスタ 2 (GRnFLM2) (n=1, 2) @n
			        ※下位６ビットは「０」にする事
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x110C> gr1flm2_t;
		static gr1flm2_t GR1FLM2;
		typedef rw32_t<base + 0x120C> gr2flm2_t;
		static gr2flm2_t GR2FLM2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n フレームバッファ制御レジスタ 3 (GRnFLM3) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnflm3_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 16>  LNOFF;
		};
		typedef grnflm3_t_<base + 0x1110> gr1flm3_t;
		static gr1flm3_t GR1FLM3;
		typedef grnflm3_t_<base + 0x1210> gr2flm3_t;
		static gr2flm3_t GR2FLM3;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n フレームバッファ制御レジスタ 5 (GRnFLM5) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnflm5_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  LNNUM;
			bits_rw_t<io_, bitpos::B0,  16>  DATANUM;
		};
		typedef grnflm5_t_<base + 0x1118> gr1flm5_t;
		static gr1flm5_t GR1FLM5;
		typedef grnflm5_t_<base + 0x1218> gr2flm5_t;
		static gr2flm5_t GR2FLM5;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n フレームバッファ制御レジスタ 6 (GRnFLM6) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnflm6_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B28, 3>  FORMAT;
		};
		typedef grnflm6_t_<base + 0x111C> gr1flm6_t;
		static gr1flm6_t GR1FLM6;
		typedef grnflm6_t_<base + 0x121C> gr2flm6_t;
		static gr2flm6_t GR2FLM6;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n アルファブレンド制御レジスタ 1 (GRnAB1) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnab1_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_,  bitpos::B12>    ARCON;
			bit_rw_t<io_,  bitpos::B8>     ARCDISPON;
			bit_rw_t<io_,  bitpos::B4>     GRCDISPON;
			bits_rw_t<io_, bitpos::B0, 2>  DISPSEL;
		};
		typedef grnab1_t_<base + 0x1120> gr1ab1_t;
		static gr1ab1_t GR1AB1;
		typedef grnab1_t_<base + 0x1220> gr2ab1_t;
		static gr2ab1_t GR2AB1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n アルファブレンド制御レジスタ 2 (GRnAB2) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnab2_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  GRCVS;
			bits_rw_t<io_, bitpos::B0,  11>  GRCVW;
		};
		typedef grnab2_t_<base + 0x1124> gr1ab2_t;
		static gr1ab2_t GR1AB2;
		typedef grnab2_t_<base + 0x1224> gr2ab2_t;
		static gr2ab2_t GR2AB2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n アルファブレンド制御レジスタ 3 (GRnAB3) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnab3_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  GRCHS;
			bits_rw_t<io_, bitpos::B0,  11>  GRCHW;
		};
		typedef grnab3_t_<base + 0x1128> gr1ab3_t;
		static gr1ab3_t GR1AB3;
		typedef grnab3_t_<base + 0x1228> gr2ab3_t;
		static gr2ab3_t GR2AB3;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n アルファブレンド制御レジスタ 4 (GRnAB4) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnab4_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  ARCVS;
			bits_rw_t<io_, bitpos::B0,  11>  ARCVW;
		};
		typedef grnab4_t_<base + 0x112C> gr1ab4_t;
		static gr1ab4_t GR1AB4;
		typedef grnab4_t_<base + 0x122C> gr2ab4_t;
		static gr2ab4_t GR2AB4;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n アルファブレンド制御レジスタ 5 (GRnAB5) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnab5_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  ARCHS;
			bits_rw_t<io_, bitpos::B0,  11>  ARCHW;
		};
		typedef grnab5_t_<base + 0x1130> gr1ab5_t;
		static gr1ab5_t GR1AB5;
		typedef grnab5_t_<base + 0x1230> gr2ab5_t;
		static gr2ab5_t GR2AB5;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n アルファブレンド制御レジスタ 6 (GRnAB6) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnab6_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 9>  ARCCOEF;
			bits_rw_t<io_, bitpos::B0,  8>  ARCRATE;
		};
		typedef grnab6_t_<base + 0x1134> gr1ab6_t;
		static gr1ab6_t GR1AB6;
		typedef grnab6_t_<base + 0x1234> gr2ab6_t;
		static gr2ab6_t GR2AB6;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n アルファブレンド制御レジスタ 7 (GRnAB7) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnab7_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 8>  ARCDEF;
			bit_rw_t <io_, bitpos::B0>      CKON;
		};
		typedef grnab7_t_<base + 0x1138> gr1ab7_t;
		static gr1ab7_t GR1AB7;
		typedef grnab7_t_<base + 0x1238> gr2ab7_t;
		static gr2ab7_t GR2AB7;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n アルファブレンド制御レジスタ 8 (GRnAB8) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnab8_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 8>  CKKG;
			bits_rw_t<io_, bitpos::B8,  8>  CKKB;
			bits_rw_t<io_, bitpos::B0,  8>  CKKR;
		};
		typedef grnab8_t_<base + 0x113C> gr1ab8_t;
		static gr1ab8_t GR1AB8;
		typedef grnab8_t_<base + 0x123C> gr2ab8_t;
		static gr2ab8_t GR2AB8;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n アルファブレンド制御レジスタ 9 (GRnAB9) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnab9_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B24, 8>  CKA;
			bits_rw_t<io_, bitpos::B16, 8>  CKG;
			bits_rw_t<io_, bitpos::B8,  8>  CKB;
			bits_rw_t<io_, bitpos::B0,  8>  CKR;
		};
		typedef grnab9_t_<base + 0x1140> gr1ab9_t;
		static gr1ab9_t GR1AB9;
		typedef grnab9_t_<base + 0x1240> gr2ab9_t;
		static gr2ab9_t GR2AB9;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n 背景色制御レジスタ (GRnBASE) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnbase_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 8>  G;
			bits_rw_t<io_, bitpos::B8,  8>  B;
			bits_rw_t<io_, bitpos::B0,  8>  R;
		};
		typedef grnbase_t_<base + 0x114C> gr1base_t;
		static gr1base_t GR1BASE;
		typedef grnbase_t_<base + 0x124C> gr2base_t;
		static gr2base_t GR2BASE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n CLUT/ 割り込み制御レジスタ (GRnCLUTINT) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnclutint_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B16>     SEL;
			bits_rw_t<io_, bitpos::B0, 11>  LINE;
		};
		typedef grnclutint_t_<base + 0x1150> gr1clutint_t;
		static gr1clutint_t GR1CLUTINT;
		typedef grnclutint_t_<base + 0x1250> gr2clutint_t;
		static gr2clutint_t GR2CLUTINT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n ステータスモニタレジスタ (GRnMON) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnmon_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B16> UFST;
			bit_rw_t<io_, bitpos::B0>  ARCST;
		};
		typedef grnmon_t_<base + 0x1154> gr1mon_t;
		static gr1mon_t GR1MON;
		typedef grnmon_t_<base + 0x1254> gr2mon_t;
		static gr2mon_t GR2MON;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x 部レジスタ更新制御レジスタ (GAMxVEN) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxven_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  VEN;
		};
		typedef gamxven_t_<base + 0x1300> gamgven_t;
		static gamgven_t GAMGVEN;
		typedef gamxven_t_<base + 0x1340> gambven_t;
		static gambven_t GAMBVEN;
		typedef gamxven_t_<base + 0x1380> gamrven_t;
		static gamrven_t GAMRVEN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正部機能切り替えレジスタ (GAMSW)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamsw_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  GAMON;
		};
		typedef gamsw_t_<base + 0x1304> gamsw_t;
		static gamsw_t GAMSW;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x テーブル設定レジスタ 1 (GAMxLUT1) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxlut1_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  GGAIN00;
			bits_rw_t<io_, bitpos::B0,  11>  GGAIN01;
		};
		typedef gamxlut1_t_<base + 0x1308> gamglut1_t;
		static gamglut1_t GAMGLUT1;
		typedef gamxlut1_t_<base + 0x1348> gamblut1_t;
		static gamblut1_t GAMBLUT1;
		typedef gamxlut1_t_<base + 0x1388> gamrlut1_t;
		static gamrlut1_t GAMRLUT1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x テーブル設定レジスタ 2 (GAMxLUT2) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxlut2_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  GGAIN02;
			bits_rw_t<io_, bitpos::B0,  11>  GGAIN03;
		};
		typedef gamxlut2_t_<base + 0x130C> gamglut2_t;
		static gamglut2_t GAMGLUT2;
		typedef gamxlut2_t_<base + 0x134C> gamblut2_t;
		static gamblut2_t GAMBLUT2;
		typedef gamxlut2_t_<base + 0x138C> gamrlut2_t;
		static gamrlut2_t GAMRLUT2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x テーブル設定レジスタ 3 (GAMxLUT3) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxlut3_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  GGAIN04;
			bits_rw_t<io_, bitpos::B0,  11>  GGAIN05;
		};
		typedef gamxlut3_t_<base + 0x1310> gamglut3_t;
		static gamglut3_t GAMGLUT3;
		typedef gamxlut3_t_<base + 0x1350> gamblut3_t;
		static gamblut3_t GAMBLUT3;
		typedef gamxlut3_t_<base + 0x1390> gamrlut3_t;
		static gamrlut3_t GAMRLUT3;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x テーブル設定レジスタ 4 (GAMxLUT4) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxlut4_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  GGAIN06;
			bits_rw_t<io_, bitpos::B0,  11>  GGAIN07;
		};
		typedef gamxlut4_t_<base + 0x1314> gamglut4_t;
		static gamglut4_t GAMGLUT4;
		typedef gamxlut4_t_<base + 0x1354> gamblut4_t;
		static gamblut4_t GAMBLUT4;
		typedef gamxlut4_t_<base + 0x1394> gamrlut4_t;
		static gamrlut4_t GAMRLUT4;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x テーブル設定レジスタ 5 (GAMxLUT5) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxlut5_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  GGAIN08;
			bits_rw_t<io_, bitpos::B0,  11>  GGAIN09;
		};
		typedef gamxlut5_t_<base + 0x1318> gamglut5_t;
		static gamglut5_t GAMGLUT5;
		typedef gamxlut5_t_<base + 0x1358> gamblut5_t;
		static gamblut5_t GAMBLUT5;
		typedef gamxlut5_t_<base + 0x1398> gamrlut5_t;
		static gamrlut5_t GAMRLUT5;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x テーブル設定レジスタ 6 (GAMxLUT6) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxlut6_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  GGAIN10;
			bits_rw_t<io_, bitpos::B0,  11>  GGAIN11;
		};
		typedef gamxlut6_t_<base + 0x131C> gamglut6_t;
		static gamglut6_t GAMGLUT6;
		typedef gamxlut6_t_<base + 0x135C> gamblut6_t;
		static gamblut6_t GAMBLUT6;
		typedef gamxlut6_t_<base + 0x139C> gamrlut6_t;
		static gamrlut6_t GAMRLUT6;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x テーブル設定レジスタ 7 (GAMxLUT7) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxlut7_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  GGAIN12;
			bits_rw_t<io_, bitpos::B0,  11>  GGAIN13;
		};
		typedef gamxlut7_t_<base + 0x1320> gamglut7_t;
		static gamglut7_t GAMGLUT7;
		typedef gamxlut7_t_<base + 0x1360> gamblut7_t;
		static gamblut7_t GAMBLUT7;
		typedef gamxlut7_t_<base + 0x13A0> gamrlut7_t;
		static gamrlut7_t GAMRLUT7;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x テーブル設定レジスタ 8 (GAMxLUT8) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxlut8_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  GGAIN14;
			bits_rw_t<io_, bitpos::B0,  11>  GGAIN15;
		};
		typedef gamxlut8_t_<base + 0x1320> gamglut8_t;
		static gamglut8_t GAMGLUT8;
		typedef gamxlut8_t_<base + 0x1360> gamblut8_t;
		static gamblut8_t GAMBLUT8;
		typedef gamxlut8_t_<base + 0x13A0> gamrlut8_t;
		static gamrlut8_t GAMRLUT8;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x 領域設定レジスタ 1 (GAMxAREA1) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxarea1_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B20, 10>  TH01;
			bits_rw_t<io_, bitpos::B10, 10>  TH02;
			bits_rw_t<io_, bitpos::B0,  10>  TH03;
		};
		typedef gamxarea1_t_<base + 0x1328> gamgarea1_t;
		static gamgarea1_t GAMGAREA1;
		typedef gamxarea1_t_<base + 0x1368> gambarea1_t;
		static gambarea1_t GAMBAREA1;
		typedef gamxarea1_t_<base + 0x13A8> gamrarea1_t;
		static gamrarea1_t GAMRAREA1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x 領域設定レジスタ 2 (GAMxAREA2) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxarea2_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B20, 10>  TH04;
			bits_rw_t<io_, bitpos::B10, 10>  TH05;
			bits_rw_t<io_, bitpos::B0,  10>  TH06;
		};
		typedef gamxarea2_t_<base + 0x132C> gamgarea2_t;
		static gamgarea2_t GAMGAREA2;
		typedef gamxarea2_t_<base + 0x136C> gambarea2_t;
		static gambarea2_t GAMBAREA2;
		typedef gamxarea2_t_<base + 0x13AC> gamrarea2_t;
		static gamrarea2_t GAMRAREA2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x 領域設定レジスタ 3 (GAMxAREA3) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxarea3_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B20, 10>  TH07;
			bits_rw_t<io_, bitpos::B10, 10>  TH08;
			bits_rw_t<io_, bitpos::B0,  10>  TH09;
		};
		typedef gamxarea3_t_<base + 0x1330> gamgarea3_t;
		static gamgarea3_t GAMGAREA3;
		typedef gamxarea3_t_<base + 0x1370> gambarea3_t;
		static gambarea3_t GAMBAREA3;
		typedef gamxarea3_t_<base + 0x13B0> gamrarea3_t;
		static gamrarea3_t GAMRAREA3;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x 領域設定レジスタ 4 (GAMxAREA4) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxarea4_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B20, 10>  TH10;
			bits_rw_t<io_, bitpos::B10, 10>  TH11;
			bits_rw_t<io_, bitpos::B0,  10>  TH12;
		};
		typedef gamxarea4_t_<base + 0x1334> gamgarea4_t;
		static gamgarea4_t GAMGAREA4;
		typedef gamxarea4_t_<base + 0x1374> gambarea4_t;
		static gambarea4_t GAMBAREA4;
		typedef gamxarea4_t_<base + 0x13B4> gamrarea4_t;
		static gamrarea4_t GAMRAREA4;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x 領域設定レジスタ 5 (GAMxAREA5) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxarea5_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B20, 10>  TH13;
			bits_rw_t<io_, bitpos::B10, 10>  TH14;
			bits_rw_t<io_, bitpos::B0,  10>  TH15;
		};
		typedef gamxarea5_t_<base + 0x1338> gamgarea5_t;
		static gamgarea5_t GAMGAREA5;
		typedef gamxarea5_t_<base + 0x1378> gambarea5_t;
		static gambarea5_t GAMBAREA5;
		typedef gamxarea5_t_<base + 0x13B8> gamrarea5_t;
		static gamrarea5_t GAMRAREA5;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  出力制御部レジスタ更新制御レジスタ (OUTVEN)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct outven_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  VEN;
		};
		typedef outven_t_<base + 0x13C0> outven_t;
		static outven_t OUTVEN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  出力インタフェースレジスタ (OUTSET)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct outset_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B28>     ENDIANON;
			bit_rw_t <io_, bitpos::B24>     SWAPON;
			bits_rw_t<io_, bitpos::B12, 2>  FORMAT;
			bit_rw_t <io_, bitpos::B9>      FRQSEL;
			bit_rw_t <io_, bitpos::B4>      DIRSEL;
			bits_rw_t<io_, bitpos::B0,  2>  PHASE;
		};
		typedef outset_t_<base + 0x13C4> outset_t;
		static outset_t OUTSET;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  輝度補正レジスタ 1 (BRIGHT1)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct bright1_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 10>  BRTG;
		};
		typedef bright1_t_<base + 0x13C8> bright1_t;
		static bright1_t BRIGHT1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  輝度補正レジスタ 2 (BRIGHT2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct bright2_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 10>  BRTB;
			bits_rw_t<io_, bitpos::B0,  10>  BRTR;
		};
		typedef bright2_t_<base + 0x13CC> bright2_t;
		static bright2_t BRIGHT2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  コントラスト補正レジスタ (CONTRAST)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct contrast_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 8>  CONTG;
			bits_rw_t<io_, bitpos::B8,  8>  CONTB;
			bits_rw_t<io_, bitpos::B0,  8>  CONTR;
		};
		typedef contrast_t_<base + 0x13D0> contrast_t;
		static contrast_t CONTRAST;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  パネルディザ制御レジスタ (PANELDTHA)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct paneldtha_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B20, 2>  SEL;
			bits_rw_t<io_, bitpos::B16, 2>  FORM;
			bits_rw_t<io_, bitpos::B12, 2>  PA;
			bits_rw_t<io_, bitpos::B8,  2>  PB;
			bits_rw_t<io_, bitpos::B4,  2>  PC;
			bits_rw_t<io_, bitpos::B0,  2>  PD;
		};
		typedef paneldtha_t_<base + 0x13D4> paneldtha_t;
		static paneldtha_t PANELDTHA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  出力位相制御レジスタ (CLKPHASE)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct clkphase_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B12> FRONTGAM;
			bit_rw_t<io_, bitpos::B8>  LCDEDG;
			bit_rw_t<io_, bitpos::B6>  TCON0EDG;
			bit_rw_t<io_, bitpos::B5>  TCON1EDG;
			bit_rw_t<io_, bitpos::B4>  TCON2EDG;
			bit_rw_t<io_, bitpos::B3>  TCON3EDG;
		};
		typedef clkphase_t_<base + 0x13E4> clkphase_t;
		static clkphase_t CLKPHASE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  基準タイミング設定レジスタ (TCONTIM)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tcontim_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  HALF;
			bits_rw_t<io_, bitpos::B0,  11>  OFFSET;
		};
		typedef tcontim_t_<base + 0x1404> tcontim_t;
		static tcontim_t TCONTIM;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  垂直タイミング設定レジスタ y1 (TCONSTVy1) (y = A, B)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tconstvy1_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  VS;
			bits_rw_t<io_, bitpos::B0,  11>  VW;
		};
		typedef tconstvy1_t_<base + 0x1408> tconstva1_t;
		static tconstva1_t TCONSTVA1;
		typedef tconstvy1_t_<base + 0x1410> tconstvb1_t;
		static tconstvb1_t TCONSTVB1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  垂直タイミング設定レジスタ y2 (TCONSTVy2) (y = A, B)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tconstvy2_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B4>     INV;
			bits_rw_t<io_, bitpos::B0, 3>  SEL;
		};
		typedef tconstvy2_t_<base + 0x140C> tconstva2_t;
		static tconstva2_t TCONSTVA2;
		typedef tconstvy2_t_<base + 0x1414> tconstvb2_t;
		static tconstvb2_t TCONSTVB2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  水平タイミング設定レジスタ y1 (TCONSTHy1) (y = A, B)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tconsthy1_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  HS;
			bits_rw_t<io_, bitpos::B0,  11>  HW;
		};
		typedef tconsthy1_t_<base + 0x1418> tconstha1_t;
		static tconstha1_t TCONSTHA1;
		typedef tconsthy1_t_<base + 0x1420> tconsthb1_t;
		static tconsthb1_t TCONSTHB1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  水平タイミング設定レジスタ y2 (TCONSTHy2) (y = A, B)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tconsthy2_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B8>     HSSEL;
			bit_rw_t <io_, bitpos::B4>     INV;
			bits_rw_t<io_, bitpos::B0, 3>  SEL;
		};
		typedef tconsthy2_t_<base + 0x141C> tconstha2_t;
		static tconstha2_t TCONSTHA2;
		typedef tconsthy2_t_<base + 0x1424> tconsthb2_t;
		static tconsthb2_t TCONSTHB2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  データイネーブル極性設定レジスタ (TCONDE)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tconde_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  INV;
		};
		typedef tconde_t_<base + 0x1428> tconde_t;
		static tconde_t TCONDE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ステータス検出制御レジスタ (DTCTEN)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dtcten_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B2>  GR2UFDTC;
			bit_rw_t<io_, bitpos::B1>  GR1UFDTC;
			bit_rw_t<io_, bitpos::B0>  VPOSDTC;
		};
		typedef dtcten_t_<base + 0x1440> dtcten_t;
		static dtcten_t DTCTEN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込み要求許可レジスタ (INTEN)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct inten_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B2>  GR2UFINTEN;
			bit_rw_t<io_, bitpos::B1>  GR1UFINTEN;
			bit_rw_t<io_, bitpos::B0>  VPOSINTEN;
		};
		typedef inten_t_<base + 0x1444> inten_t;
		static inten_t INTEN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  検出ステータスクリアレジスタ (STCLR)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct stclr_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B2>  GR2UFCLR;
			bit_rw_t<io_, bitpos::B1>  GR1UFCLR;
			bit_rw_t<io_, bitpos::B0>  VPOSCLR;
		};
		typedef stclr_t_<base + 0x1448> stclr_t;
		static stclr_t STCLR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  検出ステータスモニタレジスタ (STMON)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct stmon_t_ : public ro32_t<ofs> {
			typedef ro32_t<ofs> io_;
			using io_::operator ();

			bit_ro_t<io_, bitpos::B2>  GR2UF;
			bit_ro_t<io_, bitpos::B1>  GR1UF;
			bit_ro_t<io_, bitpos::B0>  VPOS;
		};
		typedef stmon_t_<base + 0x144C> stmon_t;
		static stmon_t STMON;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  パネルクロック制御レジスタ (PANELCLK)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct panelclk_t_ : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B12>    PIXSEL;
			bit_rw_t <io_, bitpos::B8>     CLKSEL;
			bit_rw_t <io_, bitpos::B6>     CLKEN;
			bits_rw_t<io_, bitpos::B0, 6>  DCDR;
		};
		typedef panelclk_t_<base + 0x1450> panelclk_t;
		static panelclk_t PANELCLK;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return t; }
	};

	typedef glcdc_t<0x000E0000, peripheral::GLCDC> GLCDC;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr1clut0_t glcdc_t<base, t>::GR1CLUT0;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr1clut1_t glcdc_t<base, t>::GR1CLUT1;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr2clut0_t glcdc_t<base, t>::GR2CLUT0;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr2clut1_t glcdc_t<base, t>::GR2CLUT1;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::bgen_t glcdc_t<base, t>::BGEN;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::bgperi_t glcdc_t<base, t>::BGPERI;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::bgsync_t glcdc_t<base, t>::BGSYNC;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::bgvsize_t glcdc_t<base, t>::BGVSIZE;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::bghsize_t glcdc_t<base, t>::BGHSIZE;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::bgcolor_t glcdc_t<base, t>::BGCOLOR;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::bgmon_t glcdc_t<base, t>::BGMON;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr1ven_t glcdc_t<base, t>::GR1VEN;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr2ven_t glcdc_t<base, t>::GR2VEN;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr1flmrd_t glcdc_t<base, t>::GR1FLMRD;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr2flmrd_t glcdc_t<base, t>::GR2FLMRD;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr1flm2_t glcdc_t<base, t>::GR1FLM2;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr2flm2_t glcdc_t<base, t>::GR2FLM2;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr1flm3_t glcdc_t<base, t>::GR1FLM3;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr2flm3_t glcdc_t<base, t>::GR2FLM3;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr1flm5_t glcdc_t<base, t>::GR1FLM5;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr2flm5_t glcdc_t<base, t>::GR2FLM5;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr1flm6_t glcdc_t<base, t>::GR1FLM6;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr2flm6_t glcdc_t<base, t>::GR2FLM6;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr1ab1_t glcdc_t<base, t>::GR1AB1;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr2ab1_t glcdc_t<base, t>::GR2AB1;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr1ab2_t glcdc_t<base, t>::GR1AB2;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr2ab2_t glcdc_t<base, t>::GR2AB2;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr1ab3_t glcdc_t<base, t>::GR1AB3;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr2ab3_t glcdc_t<base, t>::GR2AB3;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr1ab4_t glcdc_t<base, t>::GR1AB4;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr2ab4_t glcdc_t<base, t>::GR2AB4;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr1ab5_t glcdc_t<base, t>::GR1AB5;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr2ab5_t glcdc_t<base, t>::GR2AB5;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr1ab6_t glcdc_t<base, t>::GR1AB6;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr2ab6_t glcdc_t<base, t>::GR2AB6;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr1ab7_t glcdc_t<base, t>::GR1AB7;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr2ab7_t glcdc_t<base, t>::GR2AB7;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr1ab8_t glcdc_t<base, t>::GR1AB8;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr2ab8_t glcdc_t<base, t>::GR2AB8;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr1ab9_t glcdc_t<base, t>::GR1AB9;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr2ab9_t glcdc_t<base, t>::GR2AB9;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr1base_t glcdc_t<base, t>::GR1BASE;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr2base_t glcdc_t<base, t>::GR2BASE;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr1clutint_t glcdc_t<base, t>::GR1CLUTINT;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr2clutint_t glcdc_t<base, t>::GR2CLUTINT;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr1mon_t glcdc_t<base, t>::GR1MON;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gr2mon_t glcdc_t<base, t>::GR2MON;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamgven_t glcdc_t<base, t>::GAMGVEN;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gambven_t glcdc_t<base, t>::GAMBVEN;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamrven_t glcdc_t<base, t>::GAMRVEN;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamsw_t glcdc_t<base, t>::GAMSW;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamglut1_t glcdc_t<base, t>::GAMGLUT1;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamblut1_t glcdc_t<base, t>::GAMBLUT1;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamrlut1_t glcdc_t<base, t>::GAMRLUT1;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamglut2_t glcdc_t<base, t>::GAMGLUT2;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamblut2_t glcdc_t<base, t>::GAMBLUT2;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamrlut2_t glcdc_t<base, t>::GAMRLUT2;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamglut3_t glcdc_t<base, t>::GAMGLUT3;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamblut3_t glcdc_t<base, t>::GAMBLUT3;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamrlut3_t glcdc_t<base, t>::GAMRLUT3;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamglut4_t glcdc_t<base, t>::GAMGLUT4;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamblut4_t glcdc_t<base, t>::GAMBLUT4;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamrlut4_t glcdc_t<base, t>::GAMRLUT4;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamglut5_t glcdc_t<base, t>::GAMGLUT5;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamblut5_t glcdc_t<base, t>::GAMBLUT5;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamrlut5_t glcdc_t<base, t>::GAMRLUT5;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamglut6_t glcdc_t<base, t>::GAMGLUT6;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamblut6_t glcdc_t<base, t>::GAMBLUT6;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamrlut6_t glcdc_t<base, t>::GAMRLUT6;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamglut7_t glcdc_t<base, t>::GAMGLUT7;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamblut7_t glcdc_t<base, t>::GAMBLUT7;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamrlut7_t glcdc_t<base, t>::GAMRLUT7;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamglut8_t glcdc_t<base, t>::GAMGLUT8;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamblut8_t glcdc_t<base, t>::GAMBLUT8;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamrlut8_t glcdc_t<base, t>::GAMRLUT8;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamgarea1_t glcdc_t<base, t>::GAMGAREA1;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gambarea1_t glcdc_t<base, t>::GAMBAREA1;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamrarea1_t glcdc_t<base, t>::GAMRAREA1;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamgarea2_t glcdc_t<base, t>::GAMGAREA2;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gambarea2_t glcdc_t<base, t>::GAMBAREA2;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamrarea2_t glcdc_t<base, t>::GAMRAREA2;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamgarea3_t glcdc_t<base, t>::GAMGAREA3;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gambarea3_t glcdc_t<base, t>::GAMBAREA3;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamrarea3_t glcdc_t<base, t>::GAMRAREA3;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamgarea4_t glcdc_t<base, t>::GAMGAREA4;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gambarea4_t glcdc_t<base, t>::GAMBAREA4;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamrarea4_t glcdc_t<base, t>::GAMRAREA4;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamgarea5_t glcdc_t<base, t>::GAMGAREA5;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gambarea5_t glcdc_t<base, t>::GAMBAREA5;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::gamrarea5_t glcdc_t<base, t>::GAMRAREA5;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::outven_t glcdc_t<base, t>::OUTVEN;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::outset_t glcdc_t<base, t>::OUTSET;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::bright1_t glcdc_t<base, t>::BRIGHT1;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::bright2_t glcdc_t<base, t>::BRIGHT2;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::contrast_t glcdc_t<base, t>::CONTRAST;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::paneldtha_t glcdc_t<base, t>::PANELDTHA;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::clkphase_t glcdc_t<base, t>::CLKPHASE;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::tcontim_t glcdc_t<base, t>::TCONTIM;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::tconstva1_t glcdc_t<base, t>::TCONSTVA1;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::tconstvb1_t glcdc_t<base, t>::TCONSTVB1;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::tconstva2_t glcdc_t<base, t>::TCONSTVA2;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::tconstvb2_t glcdc_t<base, t>::TCONSTVB2;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::tconstha1_t glcdc_t<base, t>::TCONSTHA1;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::tconsthb1_t glcdc_t<base, t>::TCONSTHB1;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::tconstha2_t glcdc_t<base, t>::TCONSTHA2;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::tconsthb2_t glcdc_t<base, t>::TCONSTHB2;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::tconde_t glcdc_t<base, t>::TCONDE;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::dtcten_t glcdc_t<base, t>::DTCTEN;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::inten_t glcdc_t<base, t>::INTEN;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::stclr_t glcdc_t<base, t>::STCLR;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::stmon_t glcdc_t<base, t>::STMON;
	template <uint32_t base, peripheral t> typename glcdc_t<base, t>::panelclk_t glcdc_t<base, t>::PANELCLK;
}
