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
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct glcdc_t {

		static const auto PERIPHERAL = per;	///< ペリフェラル型

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
		typedef grclut_t<base + 0x0000> GR1CLUT0_;
		static  GR1CLUT0_ GR1CLUT0;
		typedef grclut_t<base + 0x0400> GR1CLUT1_;
		static  GR1CLUT1_ GR1CLUT1;
		typedef grclut_t<base + 0x0800> GR2CLUT0_;
		static  GR2CLUT0_ GR2CLUT0;
		typedef grclut_t<base + 0x0C00> GR2CLUT1_;
		static  GR2CLUT1_ GR2CLUT1;


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
		typedef bgen_t<base + 0x1000> BGEN_;
		static  BGEN_ BGEN;


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
		typedef bgperi_t<base + 0x1004> BGPERI_;
		static  BGPERI_ BGPERI;


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
		typedef bgsync_t<base + 0x1008> BGSYNC_;
		static  BGSYNC_ BGSYNC;


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
		typedef bgvsize_t<base + 0x100C> BGVSIZE_;
		static  BGVSIZE_ BGVSIZE;


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
		typedef bghsize_t<base + 0x1010> BGHSIZE_;
		static  BGHSIZE_ BGHSIZE;


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
		typedef bgcolor_t<base + 0x1014> BGCOLOR_;
		static  BGCOLOR_ BGCOLOR;


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
		typedef bgmon_t<base + 0x1018> BGMON_;
		static  BGMON_ BGMON;


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
		typedef grnven_t<base + 0x1100> GR1VEN_;
		static  GR1VEN_ GR1VEN;
		typedef grnven_t<base + 0x1200> GR2VEN_;
		static  GR2VEN_ GR2VEN;




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
		typedef grnflmrd_t<base + 0x1104> GR1FLMRD_;
		static  GR1FLMRD_ GR1FLMRD;
		typedef grnflmrd_t<base + 0x1204> GR2FLMRD_;
		static  GR2FLMRD_ GR2FLMRD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  グラフィック n フレームバッファ制御レジスタ 2 (GRnFLM2) (n=1, 2) @n
			        ※下位６ビットは「０」にする事
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x110C> GR1FLM2_;
		static  GR1FLM2_ GR1FLM2;
		typedef rw32_t<base + 0x120C> GR2FLM2_;
		static  GR2FLM2_ GR2FLM2;


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
		typedef grnflm3_t<base + 0x1110> GR1FLM3_;
		static  GR1FLM3_ GR1FLM3;
		typedef grnflm3_t<base + 0x1210> GR2FLM3_;
		static  GR2FLM3_ GR2FLM3;


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
		typedef grnflm5_t<base + 0x1118> GR1FLM5_;
		static  GR1FLM5_ GR1FLM5;
		typedef grnflm5_t<base + 0x1218> GR2FLM5_;
		static  GR2FLM5_ GR2FLM5;


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
		typedef grnflm6_t<base + 0x111C> GR1FLM6_;
		static  GR1FLM6_ GR1FLM6;
		typedef grnflm6_t<base + 0x121C> GR2FLM6_;
		static  GR2FLM6_ GR2FLM6;


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
		typedef grnab1_t<base + 0x1120> GR1AB1_;
		static  GR1AB1_ GR1AB1;
		typedef grnab1_t<base + 0x1220> GR2AB1_;
		static  GR2AB1_ GR2AB1;


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
		typedef grnab2_t<base + 0x1124> GR1AB2_;
		static  GR1AB2_ GR1AB2;
		typedef grnab2_t<base + 0x1224> GR2AB2_;
		static  GR2AB2_ GR2AB2;


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
		typedef grnab3_t<base + 0x1128> GR1AB3_;
		static  GR1AB3_ GR1AB3;
		typedef grnab3_t<base + 0x1228> GR2AB3_;
		static  GR2AB3_ GR2AB3;


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
		typedef grnab4_t<base + 0x112C> GR1AB4_;
		static  GR1AB4_ GR1AB4;
		typedef grnab4_t<base + 0x122C> GR2AB4_;
		static  GR2AB4_ GR2AB4;


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
		typedef grnab5_t<base + 0x1130> GR1AB5_;
		static  GR1AB5_ GR1AB5;
		typedef grnab5_t<base + 0x1230> GR2AB5_;
		static  GR2AB5_ GR2AB5;


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
		typedef grnab6_t<base + 0x1134> GR1AB6_;
		static  GR1AB6_ GR1AB6;
		typedef grnab6_t<base + 0x1234> GR2AB6_;
		static  GR2AB6_ GR2AB6;


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
		typedef grnab7_t<base + 0x1138> GR1AB7_;
		static  GR1AB7_ GR1AB7;
		typedef grnab7_t<base + 0x1238> GR2AB7_;
		static  GR2AB7_ GR2AB7;


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
		typedef grnab8_t<base + 0x113C> GR1AB8_;
		static  GR1AB8_ GR1AB8;
		typedef grnab8_t<base + 0x123C> GR2AB8_;
		static  GR2AB8_ GR2AB8;


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
		typedef grnab9_t<base + 0x1140> GR1AB9_;
		static  GR1AB9_ GR1AB9;
		typedef grnab9_t<base + 0x1240> GR2AB9_;
		static  GR2AB9_ GR2AB9;


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
		typedef grnbase_t<base + 0x114C> GR1BASE_;
		static  GR1BASE_ GR1BASE;
		typedef grnbase_t<base + 0x124C> GR2BASE_;
		static  GR2BASE_ GR2BASE;


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
		typedef grnclutint_t<base + 0x1150> GR1CLUTINT_;
		static  GR1CLUTINT_ GR1CLUTINT;
		typedef grnclutint_t<base + 0x1250> GR2CLUTINT_;
		static  GR2CLUTINT_ GR2CLUTINT;


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
		typedef grnmon_t<base + 0x1154> GR1MON_;
		static  GR1MON_ GR1MON;
		typedef grnmon_t<base + 0x1254> GR2MON_;
		static  GR2MON_ GR2MON;


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
		typedef gamxven_t<base + 0x1300> GAMGVEN_;
		static  GAMGVEN_ GAMGVEN;
		typedef gamxven_t<base + 0x1340> GAMBVEN_;
		static  GAMBVEN_ GAMBVEN;
		typedef gamxven_t<base + 0x1380> GAMRVEN_;
		static  GAMRVEN_ GAMRVEN;


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
		typedef gamsw_t<base + 0x1304> GAMSW_;
		static  GAMSW_ GAMSW;


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
		typedef gamxlut1_t<base + 0x1308> GAMGLUT1_;
		static  GAMGLUT1_ GAMGLUT1;
		typedef gamxlut1_t<base + 0x1348> GAMBLUT1_;
		static  GAMBLUT1_ GAMBLUT1;
		typedef gamxlut1_t<base + 0x1388> GAMRLUT1_;
		static  GAMRLUT1_ GAMRLUT1;


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
		typedef gamxlut2_t<base + 0x130C> GAMGLUT2_;
		static  GAMGLUT2_ GAMGLUT2;
		typedef gamxlut2_t<base + 0x134C> GAMBLUT2_;
		static  GAMBLUT2_ GAMBLUT2;
		typedef gamxlut2_t<base + 0x138C> GAMRLUT2_;
		static  GAMRLUT2_ GAMRLUT2;


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
		typedef gamxlut3_t<base + 0x1310> GAMGLUT3_;
		static  GAMGLUT3_ GAMGLUT3;
		typedef gamxlut3_t<base + 0x1350> GAMBLUT3_;
		static  GAMBLUT3_ GAMBLUT3;
		typedef gamxlut3_t<base + 0x1390> GAMRLUT3_;
		static  GAMRLUT3_ GAMRLUT3;


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
		typedef gamxlut4_t<base + 0x1314> GAMGLUT4_;
		static  GAMGLUT4_ GAMGLUT4;
		typedef gamxlut4_t<base + 0x1354> GAMBLUT4_;
		static  GAMBLUT4_ GAMBLUT4;
		typedef gamxlut4_t<base + 0x1394> GAMRLUT4_;
		static  GAMRLUT4_ GAMRLUT4;


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
		typedef gamxlut5_t<base + 0x1318> GAMGLUT5_;
		static  GAMGLUT5_ GAMGLUT5;
		typedef gamxlut5_t<base + 0x1358> GAMBLUT5_;
		static  GAMBLUT5_ GAMBLUT5;
		typedef gamxlut5_t<base + 0x1398> GAMRLUT5_;
		static  GAMRLUT5_ GAMRLUT5;


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
		typedef gamxlut6_t<base + 0x131C> GAMGLUT6_;
		static  GAMGLUT6_ GAMGLUT6;
		typedef gamxlut6_t<base + 0x135C> GAMBLUT6_;
		static  GAMBLUT6_ GAMBLUT6;
		typedef gamxlut6_t<base + 0x139C> GAMRLUT6_;
		static  GAMRLUT6_ GAMRLUT6;


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
		typedef gamxlut7_t<base + 0x1320> GAMGLUT7_;
		static  GAMGLUT7_ GAMGLUT7;
		typedef gamxlut7_t<base + 0x1360> GAMBLUT7_;
		static  GAMBLUT7_ GAMBLUT7;
		typedef gamxlut7_t<base + 0x13A0> GAMRLUT7_;
		static  GAMRLUT7_ GAMRLUT7;


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
		typedef gamxlut8_t<base + 0x1320> GAMGLUT8_;
		static  GAMGLUT8_ GAMGLUT8;
		typedef gamxlut8_t<base + 0x1360> GAMBLUT8_;
		static  GAMBLUT8_ GAMBLUT8;
		typedef gamxlut8_t<base + 0x13A0> GAMRLUT8_;
		static  GAMRLUT8_ GAMRLUT8;


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
		typedef gamxarea1_t<base + 0x1328> GAMGAREA1_;
		static  GAMGAREA1_ GAMGAREA1;
		typedef gamxarea1_t<base + 0x1368> GAMBAREA1_;
		static  GAMBAREA1_ GAMBAREA1;
		typedef gamxarea1_t<base + 0x13A8> GAMRAREA1_;
		static  GAMRAREA1_ GAMRAREA1;


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
		typedef gamxarea2_t<base + 0x132C> GAMGAREA2_;
		static  GAMGAREA2_ GAMGAREA2;
		typedef gamxarea2_t<base + 0x136C> GAMBAREA2_;
		static  GAMBAREA2_ GAMBAREA2;
		typedef gamxarea2_t<base + 0x13AC> GAMRAREA2_;
		static  GAMRAREA2_ GAMRAREA2;


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
		typedef gamxarea3_t<base + 0x1330> GAMGAREA3_;
		static  GAMGAREA3_ GAMGAREA3;
		typedef gamxarea3_t<base + 0x1370> GAMBAREA3_;
		static  GAMBAREA3_ GAMBAREA3;
		typedef gamxarea3_t<base + 0x13B0> GAMRAREA3_;
		static  GAMRAREA3_ GAMRAREA3;


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
		typedef gamxarea4_t<base + 0x1334> GAMGAREA4_;
		static  GAMGAREA4_ GAMGAREA4;
		typedef gamxarea4_t<base + 0x1374> GAMBAREA4_;
		static  GAMBAREA4_ GAMBAREA4;
		typedef gamxarea4_t<base + 0x13B4> GAMRAREA4_;
		static  GAMRAREA4_ GAMRAREA4;


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
		typedef gamxarea5_t<base + 0x1338> GAMGAREA5_;
		static  GAMGAREA5_ GAMGAREA5;
		typedef gamxarea5_t<base + 0x1378> GAMBAREA5_;
		static  GAMBAREA5_ GAMBAREA5;
		typedef gamxarea5_t<base + 0x13B8> GAMRAREA5_;
		static  GAMRAREA5_ GAMRAREA5;


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
		typedef outven_t<base + 0x13C0> OUTVEN_;
		static  OUTVEN_ OUTVEN;


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
		typedef outset_t<base + 0x13C4> OUTSET_;
		static  OUTSET_ OUTSET;


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
		typedef bright1_t<base + 0x13C8> BRIGHT1_;
		static  BRIGHT1_ BRIGHT1;


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
		typedef bright2_t<base + 0x13CC> BRIGHT2_;
		static  BRIGHT2_ BRIGHT2;


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
		typedef contrast_t<base + 0x13D0> CONTRAST_;
		static  CONTRAST_ CONTRAST;


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
		typedef paneldtha_t<base + 0x13D4> PANELDTHA_;
		static  PANELDTHA_ PANELDTHA;


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
		typedef clkphase_t<base + 0x13E4> CLKPHASE_;
		static  CLKPHASE_ CLKPHASE;


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
		typedef tcontim_t<base + 0x1404> TCONTIM_;
		static  TCONTIM_ TCONTIM;


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
		typedef tconstvy1_t<base + 0x1408> TCONSTVA1_;
		static  TCONSTVA1_ TCONSTVA1;
		typedef tconstvy1_t<base + 0x1410> TCONSTVB1_;
		static  TCONSTVB1_ TCONSTVB1;


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
		typedef tconstvy2_t<base + 0x140C> TCONSTVA2_;
		static  TCONSTVA2_ TCONSTVA2;
		typedef tconstvy2_t<base + 0x1414> TCONSTVB2_;
		static  TCONSTVB2_ TCONSTVB2;


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
		typedef tconsthy1_t<base + 0x1418> TCONSTHA1_;
		static  TCONSTHA1_ TCONSTHA1;
		typedef tconsthy1_t<base + 0x1420> TCONSTHB1_;
		static  TCONSTHB1_ TCONSTHB1;


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
		typedef tconsthy2_t<base + 0x141C> TCONSTHA2_;
		static  TCONSTHA2_ TCONSTHA2;
		typedef tconsthy2_t<base + 0x1424> TCONSTHB2_;
		static  TCONSTHB2_ TCONSTHB2;


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
		typedef tconde_t<base + 0x1428>  TCONDE_;
		static  TCONDE_ TCONDE;


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
		typedef dtcten_t<base + 0x1440>  DTCTEN_;
		static  DTCTEN_ DTCTEN;


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
		typedef inten_t<base + 0x1444>  INTEN_;
		static  INTEN_ INTEN;


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
		typedef stclr_t<base + 0x1448>  STCLR_;
		static  STCLR_ STCLR;


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
		typedef stmon_t<base + 0x144C>  STMON_;
		static  STMON_ STMON;


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
		typedef panelclk_t<base + 0x1450>  PANELCLK_;
		static  PANELCLK_ PANELCLK;
	};
	typedef glcdc_t<0x000E0000, peripheral::GLCDC> GLCDC;

	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR1CLUT0_ glcdc_t<base, per>::GR1CLUT0;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR1CLUT1_ glcdc_t<base, per>::GR1CLUT1;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR2CLUT0_ glcdc_t<base, per>::GR2CLUT0;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR2CLUT1_ glcdc_t<base, per>::GR2CLUT1;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::BGEN_ glcdc_t<base, per>::BGEN;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::BGPERI_ glcdc_t<base, per>::BGPERI;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::BGSYNC_ glcdc_t<base, per>::BGSYNC;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::BGVSIZE_ glcdc_t<base, per>::BGVSIZE;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::BGHSIZE_ glcdc_t<base, per>::BGHSIZE;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::BGCOLOR_ glcdc_t<base, per>::BGCOLOR;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::BGMON_ glcdc_t<base, per>::BGMON;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR1VEN_ glcdc_t<base, per>::GR1VEN;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR2VEN_ glcdc_t<base, per>::GR2VEN;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR1FLMRD_ glcdc_t<base, per>::GR1FLMRD;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR2FLMRD_ glcdc_t<base, per>::GR2FLMRD;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR1FLM2_ glcdc_t<base, per>::GR1FLM2;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR2FLM2_ glcdc_t<base, per>::GR2FLM2;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR1FLM3_ glcdc_t<base, per>::GR1FLM3;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR2FLM3_ glcdc_t<base, per>::GR2FLM3;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR1FLM5_ glcdc_t<base, per>::GR1FLM5;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR2FLM5_ glcdc_t<base, per>::GR2FLM5;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR1FLM6_ glcdc_t<base, per>::GR1FLM6;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR2FLM6_ glcdc_t<base, per>::GR2FLM6;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR1AB1_ glcdc_t<base, per>::GR1AB1;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR2AB1_ glcdc_t<base, per>::GR2AB1;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR1AB2_ glcdc_t<base, per>::GR1AB2;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR2AB2_ glcdc_t<base, per>::GR2AB2;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR1AB3_ glcdc_t<base, per>::GR1AB3;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR2AB3_ glcdc_t<base, per>::GR2AB3;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR1AB4_ glcdc_t<base, per>::GR1AB4;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR2AB4_ glcdc_t<base, per>::GR2AB4;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR1AB5_ glcdc_t<base, per>::GR1AB5;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR2AB5_ glcdc_t<base, per>::GR2AB5;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR1AB6_ glcdc_t<base, per>::GR1AB6;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR2AB6_ glcdc_t<base, per>::GR2AB6;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR1AB7_ glcdc_t<base, per>::GR1AB7;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR2AB7_ glcdc_t<base, per>::GR2AB7;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR1AB8_ glcdc_t<base, per>::GR1AB8;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR2AB8_ glcdc_t<base, per>::GR2AB8;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR1AB9_ glcdc_t<base, per>::GR1AB9;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR2AB9_ glcdc_t<base, per>::GR2AB9;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR1BASE_ glcdc_t<base, per>::GR1BASE;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR2BASE_ glcdc_t<base, per>::GR2BASE;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR1CLUTINT_ glcdc_t<base, per>::GR1CLUTINT;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR2CLUTINT_ glcdc_t<base, per>::GR2CLUTINT;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR1MON_ glcdc_t<base, per>::GR1MON;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GR2MON_ glcdc_t<base, per>::GR2MON;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMGVEN_ glcdc_t<base, per>::GAMGVEN;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMBVEN_ glcdc_t<base, per>::GAMBVEN;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMRVEN_ glcdc_t<base, per>::GAMRVEN;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMSW_ glcdc_t<base, per>::GAMSW;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMGLUT1_ glcdc_t<base, per>::GAMGLUT1;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMBLUT1_ glcdc_t<base, per>::GAMBLUT1;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMRLUT1_ glcdc_t<base, per>::GAMRLUT1;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMGLUT2_ glcdc_t<base, per>::GAMGLUT2;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMBLUT2_ glcdc_t<base, per>::GAMBLUT2;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMRLUT2_ glcdc_t<base, per>::GAMRLUT2;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMGLUT3_ glcdc_t<base, per>::GAMGLUT3;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMBLUT3_ glcdc_t<base, per>::GAMBLUT3;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMRLUT3_ glcdc_t<base, per>::GAMRLUT3;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMGLUT4_ glcdc_t<base, per>::GAMGLUT4;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMBLUT4_ glcdc_t<base, per>::GAMBLUT4;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMRLUT4_ glcdc_t<base, per>::GAMRLUT4;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMGLUT5_ glcdc_t<base, per>::GAMGLUT5;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMBLUT5_ glcdc_t<base, per>::GAMBLUT5;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMRLUT5_ glcdc_t<base, per>::GAMRLUT5;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMGLUT6_ glcdc_t<base, per>::GAMGLUT6;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMBLUT6_ glcdc_t<base, per>::GAMBLUT6;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMRLUT6_ glcdc_t<base, per>::GAMRLUT6;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMGLUT7_ glcdc_t<base, per>::GAMGLUT7;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMBLUT7_ glcdc_t<base, per>::GAMBLUT7;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMRLUT7_ glcdc_t<base, per>::GAMRLUT7;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMGLUT8_ glcdc_t<base, per>::GAMGLUT8;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMBLUT8_ glcdc_t<base, per>::GAMBLUT8;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMRLUT8_ glcdc_t<base, per>::GAMRLUT8;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMGAREA1_ glcdc_t<base, per>::GAMGAREA1;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMBAREA1_ glcdc_t<base, per>::GAMBAREA1;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMRAREA1_ glcdc_t<base, per>::GAMRAREA1;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMGAREA2_ glcdc_t<base, per>::GAMGAREA2;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMBAREA2_ glcdc_t<base, per>::GAMBAREA2;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMRAREA2_ glcdc_t<base, per>::GAMRAREA2;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMGAREA3_ glcdc_t<base, per>::GAMGAREA3;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMBAREA3_ glcdc_t<base, per>::GAMBAREA3;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMRAREA3_ glcdc_t<base, per>::GAMRAREA3;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMGAREA4_ glcdc_t<base, per>::GAMGAREA4;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMBAREA4_ glcdc_t<base, per>::GAMBAREA4;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMRAREA4_ glcdc_t<base, per>::GAMRAREA4;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMGAREA5_ glcdc_t<base, per>::GAMGAREA5;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMBAREA5_ glcdc_t<base, per>::GAMBAREA5;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::GAMRAREA5_ glcdc_t<base, per>::GAMRAREA5;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::OUTVEN_ glcdc_t<base, per>::OUTVEN;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::OUTSET_ glcdc_t<base, per>::OUTSET;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::BRIGHT1_ glcdc_t<base, per>::BRIGHT1;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::BRIGHT2_ glcdc_t<base, per>::BRIGHT2;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::CONTRAST_ glcdc_t<base, per>::CONTRAST;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::PANELDTHA_ glcdc_t<base, per>::PANELDTHA;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::CLKPHASE_ glcdc_t<base, per>::CLKPHASE;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::TCONTIM_ glcdc_t<base, per>::TCONTIM;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::TCONSTVA1_ glcdc_t<base, per>::TCONSTVA1;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::TCONSTVB1_ glcdc_t<base, per>::TCONSTVB1;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::TCONSTVA2_ glcdc_t<base, per>::TCONSTVA2;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::TCONSTVB2_ glcdc_t<base, per>::TCONSTVB2;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::TCONSTHA1_ glcdc_t<base, per>::TCONSTHA1;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::TCONSTHB1_ glcdc_t<base, per>::TCONSTHB1;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::TCONSTHA2_ glcdc_t<base, per>::TCONSTHA2;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::TCONSTHB2_ glcdc_t<base, per>::TCONSTHB2;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::TCONDE_ glcdc_t<base, per>::TCONDE;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::DTCTEN_ glcdc_t<base, per>::DTCTEN;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::INTEN_ glcdc_t<base, per>::INTEN;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::STCLR_ glcdc_t<base, per>::STCLR;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::STMON_ glcdc_t<base, per>::STMON;
	template <uint32_t base, peripheral per> typename glcdc_t<base, per>::PANELCLK_ glcdc_t<base, per>::PANELCLK;

}
