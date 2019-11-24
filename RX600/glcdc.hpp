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
		struct grclut_t {
			volatile uint32_t& operator[] (uint32_t idx) {
				return *reinterpret_cast<volatile uint32_t*>(ofs + (idx & 0xff));
			}
		};
		static grclut_t<base + 0x0000> GR1CLUT0;
		static grclut_t<base + 0x0400> GR1CLUT1;
		static grclut_t<base + 0x0800> GR2CLUT0;
		static grclut_t<base + 0x0C00> GR2CLUT1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バックグラウンド画面生成部動作制御レジスタ (BGEN)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct bgen_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B16> SWRST;
			bit_rw_t<io_, bitpos::B8>  VEN;
			bit_rw_t<io_, bitpos::B0>  EN;
		};
		static bgen_t<base + 0x1000> BGEN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  自走周期レジスタ (BGPERI)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct bgperi_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  FV;
			bits_rw_t<io_, bitpos::B0,  11>  FH;
		};
		static bgperi_t<base + 0x1004> BGPERI;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  同期位置レジスタ (BGSYNC)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct bgsync_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 4>  VP;
			bits_rw_t<io_, bitpos::B0,  4>  HP;
		};
		static bgsync_t<base + 0x1008> BGSYNC;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  垂直サイズレジスタ (BGVSIZE)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct bgvsize_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  VP;
			bits_rw_t<io_, bitpos::B0,  11>  VW;
		};
		static bgvsize_t<base + 0x100C> BGVSIZE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  水平サイズレジスタ (BGHSIZE)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct bghsize_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  HP;
			bits_rw_t<io_, bitpos::B0,  11>  HW;
		};
		static bghsize_t<base + 0x1010> BGHSIZE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  背景色レジスタ (BGCOLOR)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct bgcolor_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 8>  R;
			bits_rw_t<io_, bitpos::B8,  8>  G;
			bits_rw_t<io_, bitpos::B0,  8>  B;
		};
		static bgcolor_t<base + 0x1014> BGCOLOR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バックグラウンド画面生成部ステータスモニタレジスタ (BGMON)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct bgmon_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B16> SWRST;
			bit_rw_t<io_, bitpos::B8>  VEN;
			bit_rw_t<io_, bitpos::B0>  EN;
		};
		static bgmon_t<base + 0x1018> BGMON;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n レジスタ更新制御レジスタ (GRnVEN) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnven_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  VEN;
		};
		static grnven_t<base + 0x1100> GR1VEN;
		static grnven_t<base + 0x1200> GR2VEN;




		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n フレームバッファ読み出し制御レジスタ (GRnFLMRD) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnflmrd_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  RENB;
		};
		static grnflmrd_t<base + 0x1104> GR1FLMRD;
		static grnflmrd_t<base + 0x1204> GR2FLMRD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n フレームバッファ制御レジスタ 2 (GRnFLM2) (n=1, 2) @n
			        ※下位６ビットは「０」にする事
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static rw32_t<base + 0x110C> GR1FLM2;
		static rw32_t<base + 0x120C> GR2FLM2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n フレームバッファ制御レジスタ 3 (GRnFLM3) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnflm3_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 16>  LNOFF;
		};
		static grnflm3_t<base + 0x1110> GR1FLM3;
		static grnflm3_t<base + 0x1210> GR2FLM3;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n フレームバッファ制御レジスタ 5 (GRnFLM5) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnflm5_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  LNNUM;
			bits_rw_t<io_, bitpos::B0,  16>  DATANUM;
		};
		static grnflm5_t<base + 0x1118> GR1FLM5;
		static grnflm5_t<base + 0x1218> GR2FLM5;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n フレームバッファ制御レジスタ 6 (GRnFLM6) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnflm6_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B28, 3>  FORMAT;
		};
		static grnflm6_t<base + 0x111C> GR1FLM6;
		static grnflm6_t<base + 0x121C> GR2FLM6;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n アルファブレンド制御レジスタ 1 (GRnAB1) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnab1_t : public rw32_t<ofs> {
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
		static grnab1_t<base + 0x1120> GR1AB1;
		static grnab1_t<base + 0x1220> GR2AB1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n アルファブレンド制御レジスタ 2 (GRnAB2) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnab2_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  GRCVS;
			bits_rw_t<io_, bitpos::B0,  11>  GRCVW;
		};
		static grnab2_t<base + 0x1124> GR1AB2;
		static grnab2_t<base + 0x1224> GR2AB2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n アルファブレンド制御レジスタ 3 (GRnAB3) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnab3_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  GRCHS;
			bits_rw_t<io_, bitpos::B0,  11>  GRCHW;
		};
		static grnab3_t<base + 0x1128> GR1AB3;
		static grnab3_t<base + 0x1228> GR2AB3;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n アルファブレンド制御レジスタ 4 (GRnAB4) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnab4_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  ARCVS;
			bits_rw_t<io_, bitpos::B0,  11>  ARCVW;
		};
		static grnab4_t<base + 0x112C> GR1AB4;
		static grnab4_t<base + 0x122C> GR2AB4;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n アルファブレンド制御レジスタ 5 (GRnAB5) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnab5_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  ARCHS;
			bits_rw_t<io_, bitpos::B0,  11>  ARCHW;
		};
		static grnab5_t<base + 0x1130> GR1AB5;
		static grnab5_t<base + 0x1230> GR2AB5;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n アルファブレンド制御レジスタ 6 (GRnAB6) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnab6_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 9>  ARCCOEF;
			bits_rw_t<io_, bitpos::B0,  8>  ARCRATE;
		};
		static grnab6_t<base + 0x1134> GR1AB6;
		static grnab6_t<base + 0x1234> GR2AB6;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n アルファブレンド制御レジスタ 7 (GRnAB7) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnab7_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 8>  ARCDEF;
			bit_rw_t <io_, bitpos::B0>      CKON;
		};
		static grnab7_t<base + 0x1138> GR1AB7;
		static grnab7_t<base + 0x1238> GR2AB7;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n アルファブレンド制御レジスタ 8 (GRnAB8) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnab8_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 8>  CKKG;
			bits_rw_t<io_, bitpos::B8,  8>  CKKB;
			bits_rw_t<io_, bitpos::B0,  8>  CKKR;
		};
		static grnab8_t<base + 0x113C> GR1AB8;
		static grnab8_t<base + 0x123C> GR2AB8;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n アルファブレンド制御レジスタ 9 (GRnAB9) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnab9_t : public rw32_t<ofs> {
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
		static grnab9_t<base + 0x1140> GR1AB9;
		static grnab9_t<base + 0x1240> GR2AB9;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n 背景色制御レジスタ (GRnBASE) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnbase_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 8>  G;
			bits_rw_t<io_, bitpos::B8,  8>  B;
			bits_rw_t<io_, bitpos::B0,  8>  R;
		};
		static grnbase_t<base + 0x114C> GR1BASE;
		static grnbase_t<base + 0x124C> GR2BASE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n CLUT/ 割り込み制御レジスタ (GRnCLUTINT) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnclutint_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B16>     SEL;
			bits_rw_t<io_, bitpos::B0, 11>  LINE;
		};
		static grnclutint_t<base + 0x1150> GR1CLUTINT;
		static grnclutint_t<base + 0x1250> GR2CLUTINT;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n ステータスモニタレジスタ (GRnMON) (n=1, 2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct grnmon_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B16> UFST;
			bit_rw_t<io_, bitpos::B0>  ARCST;
		};
		static grnmon_t<base + 0x1154> GR1MON;
		static grnmon_t<base + 0x1254> GR2MON;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x 部レジスタ更新制御レジスタ (GAMxVEN) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxven_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  VEN;
		};
		static gamxven_t<base + 0x1300> GAMGVEN;
		static gamxven_t<base + 0x1340> GAMBVEN;
		static gamxven_t<base + 0x1380> GAMRVEN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正部機能切り替えレジスタ (GAMSW)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamsw_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  GAMON;
		};
		static gamsw_t<base + 0x1304> GAMSW;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x テーブル設定レジスタ 1 (GAMxLUT1) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxlut1_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  GGAIN00;
			bits_rw_t<io_, bitpos::B0,  11>  GGAIN01;
		};
		static gamxlut1_t<base + 0x1308> GAMGLUT1;
		static gamxlut1_t<base + 0x1348> GAMBLUT1;
		static gamxlut1_t<base + 0x1388> GAMRLUT1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x テーブル設定レジスタ 2 (GAMxLUT2) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxlut2_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  GGAIN02;
			bits_rw_t<io_, bitpos::B0,  11>  GGAIN03;
		};
		static gamxlut2_t<base + 0x130C> GAMGLUT2;
		static gamxlut2_t<base + 0x134C> GAMBLUT2;
		static gamxlut2_t<base + 0x138C> GAMRLUT2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x テーブル設定レジスタ 3 (GAMxLUT3) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxlut3_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  GGAIN04;
			bits_rw_t<io_, bitpos::B0,  11>  GGAIN05;
		};
		static gamxlut3_t<base + 0x1310> GAMGLUT3;
		static gamxlut3_t<base + 0x1350> GAMBLUT3;
		static gamxlut3_t<base + 0x1390> GAMRLUT3;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x テーブル設定レジスタ 4 (GAMxLUT4) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxlut4_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  GGAIN06;
			bits_rw_t<io_, bitpos::B0,  11>  GGAIN07;
		};
		static gamxlut4_t<base + 0x1314> GAMGLUT4;
		static gamxlut4_t<base + 0x1354> GAMBLUT4;
		static gamxlut4_t<base + 0x1394> GAMRLUT4;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x テーブル設定レジスタ 5 (GAMxLUT5) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxlut5_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  GGAIN08;
			bits_rw_t<io_, bitpos::B0,  11>  GGAIN09;
		};
		static gamxlut5_t<base + 0x1318> GAMGLUT5;
		static gamxlut5_t<base + 0x1358> GAMBLUT5;
		static gamxlut5_t<base + 0x1398> GAMRLUT5;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x テーブル設定レジスタ 6 (GAMxLUT6) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxlut6_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  GGAIN10;
			bits_rw_t<io_, bitpos::B0,  11>  GGAIN11;
		};
		static gamxlut6_t<base + 0x131C> GAMGLUT6;
		static gamxlut6_t<base + 0x135C> GAMBLUT6;
		static gamxlut6_t<base + 0x139C> GAMRLUT6;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x テーブル設定レジスタ 7 (GAMxLUT7) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxlut7_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  GGAIN12;
			bits_rw_t<io_, bitpos::B0,  11>  GGAIN13;
		};
		static gamxlut7_t<base + 0x1320> GAMGLUT7;
		static gamxlut7_t<base + 0x1360> GAMBLUT7;
		static gamxlut7_t<base + 0x13A0> GAMRLUT7;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x テーブル設定レジスタ 8 (GAMxLUT8) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxlut8_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  GGAIN14;
			bits_rw_t<io_, bitpos::B0,  11>  GGAIN15;
		};
		static gamxlut8_t<base + 0x1320> GAMGLUT8;
		static gamxlut8_t<base + 0x1360> GAMBLUT8;
		static gamxlut8_t<base + 0x13A0> GAMRLUT8;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x 領域設定レジスタ 1 (GAMxAREA1) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxarea1_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B20, 10>  TH01;
			bits_rw_t<io_, bitpos::B10, 10>  TH02;
			bits_rw_t<io_, bitpos::B0,  10>  TH03;
		};
		static gamxarea1_t<base + 0x1328> GAMGAREA1;
		static gamxarea1_t<base + 0x1368> GAMBAREA1;
		static gamxarea1_t<base + 0x13A8> GAMRAREA1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x 領域設定レジスタ 2 (GAMxAREA2) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxarea2_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B20, 10>  TH04;
			bits_rw_t<io_, bitpos::B10, 10>  TH05;
			bits_rw_t<io_, bitpos::B0,  10>  TH06;
		};
		static gamxarea2_t<base + 0x132C> GAMGAREA2;
		static gamxarea2_t<base + 0x136C> GAMBAREA2;
		static gamxarea2_t<base + 0x13AC> GAMRAREA2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x 領域設定レジスタ 3 (GAMxAREA3) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxarea3_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B20, 10>  TH07;
			bits_rw_t<io_, bitpos::B10, 10>  TH08;
			bits_rw_t<io_, bitpos::B0,  10>  TH09;
		};
		static gamxarea3_t<base + 0x1330> GAMGAREA3;
		static gamxarea3_t<base + 0x1370> GAMBAREA3;
		static gamxarea3_t<base + 0x13B0> GAMRAREA3;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x 領域設定レジスタ 4 (GAMxAREA4) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxarea4_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B20, 10>  TH10;
			bits_rw_t<io_, bitpos::B10, 10>  TH11;
			bits_rw_t<io_, bitpos::B0,  10>  TH12;
		};
		static gamxarea4_t<base + 0x1334> GAMGAREA4;
		static gamxarea4_t<base + 0x1374> GAMBAREA4;
		static gamxarea4_t<base + 0x13B4> GAMRAREA4;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ガンマ補正 x 領域設定レジスタ 5 (GAMxAREA5) (x = G, B, R)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct gamxarea5_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B20, 10>  TH13;
			bits_rw_t<io_, bitpos::B10, 10>  TH14;
			bits_rw_t<io_, bitpos::B0,  10>  TH15;
		};
		static gamxarea5_t<base + 0x1338> GAMGAREA5;
		static gamxarea5_t<base + 0x1378> GAMBAREA5;
		static gamxarea5_t<base + 0x13B8> GAMRAREA5;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  出力制御部レジスタ更新制御レジスタ (OUTVEN)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct outven_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  VEN;
		};
		static outven_t<base + 0x13C0> OUTVEN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  出力インタフェースレジスタ (OUTSET)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct outset_t : public rw32_t<ofs> {
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
		static outset_t<base + 0x13C4> OUTSET;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  輝度補正レジスタ 1 (BRIGHT1)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct bright1_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 10>  BRTG;
		};
		static bright1_t<base + 0x13C8> BRIGHT1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  輝度補正レジスタ 2 (BRIGHT2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct bright2_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 10>  BRTB;
			bits_rw_t<io_, bitpos::B0,  10>  BRTR;
		};
		static bright2_t<base + 0x13CC> BRIGHT2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  コントラスト補正レジスタ (CONTRAST)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct contrast_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 8>  CONTG;
			bits_rw_t<io_, bitpos::B8,  8>  CONTB;
			bits_rw_t<io_, bitpos::B0,  8>  CONTR;
		};
		static contrast_t<base + 0x13D0> CONTRAST;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  パネルディザ制御レジスタ (PANELDTHA)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct paneldtha_t : public rw32_t<ofs> {
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
		static paneldtha_t<base + 0x13D4> PANELDTHA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  出力位相制御レジスタ (CLKPHASE)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct clkphase_t : public rw32_t<ofs> {
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
		static clkphase_t<base + 0x13E4> CLKPHASE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  基準タイミング設定レジスタ (TCONTIM)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tcontim_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  HALF;
			bits_rw_t<io_, bitpos::B0,  11>  OFFSET;
		};
		static tcontim_t<base + 0x1404> TCONTIM;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  垂直タイミング設定レジスタ y1 (TCONSTVy1) (y = A, B)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tconstvy1_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  VS;
			bits_rw_t<io_, bitpos::B0,  11>  VW;
		};
		static tconstvy1_t<base + 0x1408> TCONSTVA1;
		static tconstvy1_t<base + 0x1410> TCONSTVB1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  垂直タイミング設定レジスタ y2 (TCONSTVy2) (y = A, B)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tconstvy2_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B4>     INV;
			bits_rw_t<io_, bitpos::B0, 3>  SEL;
		};
		static tconstvy2_t<base + 0x140C> TCONSTVA2;
		static tconstvy2_t<base + 0x1414> TCONSTVB2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  水平タイミング設定レジスタ y1 (TCONSTHy1) (y = A, B)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tconsthy1_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 11>  HS;
			bits_rw_t<io_, bitpos::B0,  11>  HW;
		};
		static tconsthy1_t<base + 0x1418> TCONSTHA1;
		static tconsthy1_t<base + 0x1420> TCONSTHB1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  水平タイミング設定レジスタ y2 (TCONSTHy2) (y = A, B)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tconsthy2_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B8>     HSSEL;
			bit_rw_t <io_, bitpos::B4>     INV;
			bits_rw_t<io_, bitpos::B0, 3>  SEL;
		};
		static tconsthy2_t<base + 0x141C> TCONSTHA2;
		static tconsthy2_t<base + 0x1424> TCONSTHB2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  データイネーブル極性設定レジスタ (TCONDE)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct tconde_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  INV;
		};
		static tconde_t<base + 0x1428>  TCONDE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ステータス検出制御レジスタ (DTCTEN)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct dtcten_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B2>  GR2UFDTC;
			bit_rw_t<io_, bitpos::B1>  GR1UFDTC;
			bit_rw_t<io_, bitpos::B0>  VPOSDTC;
		};
		static dtcten_t<base + 0x1440>  DTCTEN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込み要求許可レジスタ (INTEN)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct inten_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B2>  GR2UFINTEN;
			bit_rw_t<io_, bitpos::B1>  GR1UFINTEN;
			bit_rw_t<io_, bitpos::B0>  VPOSINTEN;
		};
		static inten_t<base + 0x1444>  INTEN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  検出ステータスクリアレジスタ (STCLR)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct stclr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B2>  GR2UFCLR;
			bit_rw_t<io_, bitpos::B1>  GR1UFCLR;
			bit_rw_t<io_, bitpos::B0>  VPOSCLR;
		};
		static stclr_t<base + 0x1448>  STCLR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  検出ステータスモニタレジスタ (STMON)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct stmon_t : public ro32_t<ofs> {
			typedef ro32_t<ofs> io_;
			using io_::operator ();

			bit_ro_t<io_, bitpos::B2>  GR2UF;
			bit_ro_t<io_, bitpos::B1>  GR1UF;
			bit_ro_t<io_, bitpos::B0>  VPOS;
		};
		static stmon_t<base + 0x144C>  STMON;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  パネルクロック制御レジスタ (PANELCLK)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct panelclk_t : public rw32_t<ofs> {
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
		static panelclk_t<base + 0x1450>  PANELCLK;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return t; }
	};

	typedef glcdc_t<0x000E0000, peripheral::GLCDC> GLCDC;
}
