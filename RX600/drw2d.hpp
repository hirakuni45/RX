#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ DRW2D 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  DRW2D 定義
		@param[in]	base	ベース・アドレス
		@param[in]	t		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral t>
	struct drw2d_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ジオメトリコントロールレジスタ (CONTROL)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct control_t_ : public trw32_t<ofs> {
			typedef trw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>   LIM1EN;
			bit_rw_t<io_, bitpos::B1>   LIM2EN;
			bit_rw_t<io_, bitpos::B2>   LIM3EN;
			bit_rw_t<io_, bitpos::B3>   LIM4EN;
			bit_rw_t<io_, bitpos::B4>   LIM5EN;
			bit_rw_t<io_, bitpos::B5>   LIM6EN;
			bit_rw_t<io_, bitpos::B6>   QUAD1EN;
			bit_rw_t<io_, bitpos::B7>   QUAD2EN;
			bit_rw_t<io_, bitpos::B8>   QUAD3EN;
			bit_rw_t<io_, bitpos::B9>   LIM1TH;
			bit_rw_t<io_, bitpos::B10>  LIM2TH;
			bit_rw_t<io_, bitpos::B11>  LIM3TH;
			bit_rw_t<io_, bitpos::B12>  LIM4TH;
			bit_rw_t<io_, bitpos::B13>  LIM5TH;
			bit_rw_t<io_, bitpos::B14>  LIM6TH;
			bit_rw_t<io_, bitpos::B15>  BAND1EN;
			bit_rw_t<io_, bitpos::B16>  BAND2EN;
			bit_rw_t<io_, bitpos::B17>  UNION12;
			bit_rw_t<io_, bitpos::B18>  UNION34;
			bit_rw_t<io_, bitpos::B19>  UNION56;
			bit_rw_t<io_, bitpos::B20>  UNIONAB;
			bit_rw_t<io_, bitpos::B21>  UNIONCD;
			bit_rw_t<io_, bitpos::B22>  SPANABT;
			bit_rw_t<io_, bitpos::B23>  SPANSTR;
		};
		typedef control_t_<base + 0x00> control_t;
		static control_t CONTROL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サーフェスコントロールレジスタ (CONTROL2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct control2_t_ : public trw32_t<ofs> {
			typedef trw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      PTNEN;
			bit_rw_t <io_, bitpos::B1>      TEXENA;
			bit_rw_t <io_, bitpos::B2>      PTNSRCL5;
			bit_rw_t <io_, bitpos::B3>      USEACB;
			bits_rw_t<io_, bitpos::B4, 2>   RDFMT2;
			bit_rw_t <io_, bitpos::B6>      BSFA;
			bit_rw_t <io_, bitpos::B7>      BDFA;
			bit_rw_t <io_, bitpos::B8>      WRFMT2;
			bit_rw_t <io_, bitpos::B9>      BSF;
			bit_rw_t <io_, bitpos::B10>     BDF;
			bit_rw_t <io_, bitpos::B11>     BSI;
			bit_rw_t <io_, bitpos::B12>     BDI;
			bit_rw_t <io_, bitpos::B13>     BC2;
			bit_rw_t <io_, bitpos::B14>     TEXCLPX;
			bit_rw_t <io_, bitpos::B15>     TEXCLPY;
			bit_rw_t <io_, bitpos::B16>     TEXFILTX;
			bit_rw_t <io_, bitpos::B17>     TEXFILTY;
			bits_rw_t<io_, bitpos::B18, 2>  RDFMT;
			bits_rw_t<io_, bitpos::B20, 2>  WRFMT;
			bits_rw_t<io_, bitpos::B22, 2>  WRALPHA;
			bit_rw_t <io_, bitpos::B24>     RLEEN;
			bit_rw_t <io_, bitpos::B25>     CLUTEN;
			bit_rw_t <io_, bitpos::B26>     COLKEYEN;
			bit_rw_t <io_, bitpos::B27>     CLUTFORM;
			bit_rw_t <io_, bitpos::B28>     BSIA;
			bit_rw_t <io_, bitpos::B29>     BDIA;
			bits_rw_t<io_, bitpos::B30, 2>  RLEPIXW;
		};
		typedef control2_t_<base + 0x04> control2_t;
		static control2_t CONTROL2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込みコントロールレジスタ (IRQCTL)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct irqctl_t_ : public trw32_t<ofs> {
			typedef trw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      ENUIREN;
			bit_rw_t <io_, bitpos::B1>      DLIREN;
			bit_rw_t <io_, bitpos::B2>      ENUIRCLR;
			bit_rw_t <io_, bitpos::B3>      DLIRCLR;
		};
		typedef irqctl_t_<base + 0xC0> irqctl_t;
		static irqctl_t IRQCTL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  キャッシュコントロールレジスタ (CACHECTL)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct cachectl_t_ : public trw32_t<ofs> {
			typedef trw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>      CENFX;
			bit_rw_t <io_, bitpos::B1>      CFLUFX;
			bit_rw_t <io_, bitpos::B2>      CENTX;
			bit_rw_t <io_, bitpos::B3>      CFLUTX;
		};
		typedef cachectl_t_<base + 0xC4> cachectl_t;
		static cachectl_t CACHECTL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ステータスレジスタ (STATUS)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct status_t_ : public ro32_t<ofs> {
			typedef ro32_t<ofs> io_;
			using io_::operator ();

			bit_ro_t <io_, bitpos::B0>      BSYENUM;
			bit_ro_t <io_, bitpos::B1>      BSYWR;
			bit_ro_t <io_, bitpos::B2>      CACHEDTY;
			bit_ro_t <io_, bitpos::B3>      DLSTACT;
			bit_ro_t <io_, bitpos::B4>      ENUIR;
			bit_ro_t <io_, bitpos::B5>      DLIR;
		};
		typedef status_t_<base + 0x00> status_t;
		static status_t STATUS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ハードウェアバージョンレジスタ (HWVER)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct hwver_t_ : public ro32_t<ofs> {
			typedef ro32_t<ofs> io_;
			using io_::operator ();

			bits_ro_t<io_, bitpos::B0, 12>  REV;
			bit_ro_t <io_, bitpos::B17>     DLR;
			bit_ro_t <io_, bitpos::B18>     FBCACHE;
			bit_ro_t <io_, bitpos::B19>     TXCACHE;
			bit_ro_t <io_, bitpos::B20>     PERFCNT;
			bit_ro_t <io_, bitpos::B21>     TEXCLUT;

			bit_ro_t <io_, bitpos::B23>     RLEUNIT;
			bit_ro_t <io_, bitpos::B24>     TEXCLUT256;
			bit_ro_t <io_, bitpos::B25>     COLKEY;

			bit_ro_t <io_, bitpos::B27>     ACBLD;
		};
		typedef hwver_t_<base + 0x04> hwver_t;
		static hwver_t HWVER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ベースカラーレジスタ (COLOR1)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct color1_t_ : public trw32_t<ofs> {
			typedef trw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>    COL1B;
			bits_rw_t<io_, bitpos::B8,  8>    COL1G;
			bits_rw_t<io_, bitpos::B16, 8>    COL1R;
			bits_rw_t<io_, bitpos::B24, 8>    COL1A;
		};
		typedef color1_t_<base + 0x64> color1_t;
		static color1_t COLOR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  セカンダリカラーレジスタ (COLOR2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct color2_t_ : public trw32_t<ofs> {
			typedef trw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>    COL2B;
			bits_rw_t<io_, bitpos::B8,  8>    COL2G;
			bits_rw_t<io_, bitpos::B16, 8>    COL2R;
			bits_rw_t<io_, bitpos::B24, 8>    COL2A;
		};
		typedef color2_t_<base + 0x68> color2_t;
		static color2_t COLOR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	パターンレジスタ (PATTERN)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct pattern_t_ : public trw32_t<ofs> {
			typedef trw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>    PATTERN;
		};
		typedef pattern_t_<base + 0x74> pattern_t;
		static pattern_t PATTERN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	リミッタ n 開始値レジスタ (LnSTART) (n = 1 ～ 6)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0x10> l1start_t;
		static l1start_t L1START;
		typedef trw32_t<base + 0x14> l2start_t;
		static l2start_t L2START;
		typedef trw32_t<base + 0x18> l3start_t;
		static l3start_t L3START;
		typedef trw32_t<base + 0x1C> l4start_t;
		static l4start_t L4START;
		typedef trw32_t<base + 0x20> l5start_t;
		static l5start_t L5START;
		typedef trw32_t<base + 0x24> l6start_t;
		static l6start_t L6START;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	リミッタ n X 軸インクリメントレジスタ (LnXADD) (n = 1 ～ 6)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0x28> l1xadd_t;
		static l1xadd_t L1XADD;
		typedef trw32_t<base + 0x2C> l2xadd_t;
		static l2xadd_t L2XADD;
		typedef trw32_t<base + 0x30> l3xadd_t;
		static l3xadd_t L3XADD;
		typedef trw32_t<base + 0x34> l4xadd_t;
		static l4xadd_t L4XADD;
		typedef trw32_t<base + 0x38> l5xadd_t;
		static l5xadd_t L5XADD;
		typedef trw32_t<base + 0x3C> l6xadd_t;
		static l6xadd_t L6XADD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	リミッタ n Y 軸インクリメントレジスタ (LnYADD) (n = 1 ～ 6)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0x40> l1yadd_t;
		static l1yadd_t L1YADD;
		typedef trw32_t<base + 0x44> l2yadd_t;
		static l2yadd_t L2YADD;
		typedef trw32_t<base + 0x48> l3yadd_t;
		static l3yadd_t L3YADD;
		typedef trw32_t<base + 0x4C> l4yadd_t;
		static l4yadd_t L4YADD;
		typedef trw32_t<base + 0x50> l5yadd_t;
		static l5yadd_t L5YADD;
		typedef trw32_t<base + 0x54> l6yadd_t;
		static l6yadd_t L6YADD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	リミッタ m バンド幅パラメータレジスタ (LmBAND) (m = 1, 2)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0x58> l1band_t;
		static l1band_t L1BAND;
		typedef trw32_t<base + 0x5C> l2band_t;
		static l2band_t L2BAND;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	テクスチャベースアドレスレジスタ (TEXORG)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0xBC> texorg_t;
		static texorg_t TEXORG;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	テクスチャラインテクセル数レジスタ (TEXPITCH)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0xB4> texpitch_t;
		static texpitch_t TEXPITCH;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	テクスチャマスクレジスタ (TEXMSK)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct texmsk_t_ : public trw32_t<ofs> {
			typedef trw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  11>  TEXUMASK;
			bits_rw_t<io_, bitpos::B11, 21>  TEXVMASK;
		};
		typedef texmsk_t_<base + 0xB8> texmsk_t;
		static texmsk_t TEXMSK;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	U リミッタ開始値レジスタ (LUST)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0x90> lust_t;
		static lust_t LUST;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	U リミッタ X 軸インクリメントレジスタ (LUXADD)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0x94> luxadd_t;
		static luxadd_t LUXADD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	U リミッタ Y 軸インクリメントレジスタ (LUYADD)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0x98> luyadd_t;
		static luyadd_t LUYADD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	V リミッタ開始値整数部レジスタ (LVSTI)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0x9C> lvsti_t;
		static lvsti_t LVSTI;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	V リミッタ開始値小数部レジスタ (LVSTF) @n
					※下位１６ビットのみが有効
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0xA0> lvstf_t;
		static lvstf_t LVSTF;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	V リミッタ X 軸インクリメント整数部レジスタ (LVXADDI)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0xA4> lvxaddi_t;
		static lvxaddi_t LVXADDI;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	V リミッタ Y 軸インクリメント整数部レジスタ (LVYADDI)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0xA8> lvyaddi_t;
		static lvyaddi_t LVYADDI;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	V リミッタインクリメント小数部レジスタ (LVYXADDF)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct lvyxaddf_t_ : public trw32_t<ofs> {
			typedef trw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  16>  LVYADDF;
			bits_rw_t<io_, bitpos::B16, 16>  LVXADDF;
		};
		typedef lvyxaddf_t_<base + 0xAC> lvyxaddf_t;
		static lvyxaddf_t LVYXADDF;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	CLUT 開始アドレスレジスタ (TEXCLADDR)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct texcladdr_t_ : public trw32_t<ofs> {
			typedef trw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>  CLADDR;
		};
		typedef texcladdr_t_<base + 0xDC> texcladdr_t;
		static texcladdr_t TEXCLADDR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	CLUT データレジスタ (TEXCLDATA)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0xE0> texcldata_t;
		static texcldata_t TEXCLDATA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	CLUT オフセットレジスタ (TEXCLOFST)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct texclofst_t_ : public trw32_t<ofs> {
			typedef trw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>  CLOFST;
		};
		typedef texclofst_t_<base + 0xE4> texclofst_t;
		static texclofst_t TEXCLOFST;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	クロマキーレジスタ (COLKEY)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct colkey_t_ : public trw32_t<ofs> {
			typedef trw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>  B;
			bits_rw_t<io_, bitpos::B8,  8>  G;
			bits_rw_t<io_, bitpos::B16, 8>  R;
		};
		typedef colkey_t_<base + 0xE8> colkey_t;
		static colkey_t COLKEY;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	バウンディングボックスサイズレジスタ (SIZE)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct size_t_ : public trw32_t<ofs> {
			typedef trw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  16>  X;
			bits_rw_t<io_, bitpos::B16, 16>  Y;
		};
		typedef size_t_<base + 0x78> size_t;
		static size_t SIZE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	フレームバッファピッチレジスタ (PITCH)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct pitch_t_ : public trw32_t<ofs> {
			typedef trw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  16>  PITCH;
			bits_rw_t<io_, bitpos::B16, 16>  SSD;
		};
		typedef pitch_t_<base + 0x7C> pitch_t;
		static pitch_t PITCH;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	フレームバッファベースアドレスレジスタ (ORIGIN)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0x80> origin_t;
		static origin_t ORIGIN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ディスプレイリスト開始アドレスレジスタ (DLISTST)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0xC8> dlistst_t;
		static dlistst_t DLISTST;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	パフォーマンスカウンタコントロールレジスタ (PERFTRG)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct perftrg_t_ : public trw32_t<ofs> {
			typedef trw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  16>  TRG1;
			bits_rw_t<io_, bitpos::B16, 16>  TRG2;
		};
		typedef perftrg_t_<base + 0xD4> perftrg_t;
		static perftrg_t PERFTRG;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	パフォーマンスカウンタ k (PERFCNTk) (k = 1, 2)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0xCC> perfcnt1_t;
		static perfcnt1_t PERFCNT1;
		typedef trw32_t<base + 0xD0> perfcnt2_t;
		static perfcnt2_t PERFCNT2;


		//-----------------------------------------------------------------//
		/*!
			@brief  ペリフェラル型を返す
			@return ペリフェラル型
		*/
		//-----------------------------------------------------------------//
		static peripheral get_peripheral() { return t; }


		//-----------------------------------------------------------------//
		/*!
			@brief  DRW2D 割り込みベクターを返す
			@return ベクター型
		*/
		//-----------------------------------------------------------------//
		static ICU::VECTOR_AL1 get_irq_vec() { return ICU::VECTOR_AL1::DRW_IRQ; }
	};

	typedef drw2d_t<0x000E3000, peripheral::DRW2D> DRW2D;

	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::control_t drw2d_t<base, t>::CONTROL;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::control2_t drw2d_t<base, t>::CONTROL2;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::irqctl_t drw2d_t<base, t>::IRQCTL;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::cachectl_t drw2d_t<base, t>::CACHECTL;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::status_t drw2d_t<base, t>::STATUS;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::hwver_t drw2d_t<base, t>::HWVER;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::color1_t drw2d_t<base, t>::COLOR1;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::color2_t drw2d_t<base, t>::COLOR2;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::pattern_t drw2d_t<base, t>::PATTERN;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::l1start_t drw2d_t<base, t>::L1START;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::l2start_t drw2d_t<base, t>::L2START;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::l3start_t drw2d_t<base, t>::L3START;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::l4start_t drw2d_t<base, t>::L4START;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::l5start_t drw2d_t<base, t>::L5START;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::l6start_t drw2d_t<base, t>::L6START;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::l1xadd_t drw2d_t<base, t>::L1XADD;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::l2xadd_t drw2d_t<base, t>::L2XADD;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::l3xadd_t drw2d_t<base, t>::L3XADD;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::l4xadd_t drw2d_t<base, t>::L4XADD;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::l5xadd_t drw2d_t<base, t>::L5XADD;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::l6xadd_t drw2d_t<base, t>::L6XADD;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::l1yadd_t drw2d_t<base, t>::L1YADD;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::l2yadd_t drw2d_t<base, t>::L2YADD;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::l3yadd_t drw2d_t<base, t>::L3YADD;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::l4yadd_t drw2d_t<base, t>::L4YADD;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::l5yadd_t drw2d_t<base, t>::L5YADD;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::l6yadd_t drw2d_t<base, t>::L6YADD;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::l1band_t drw2d_t<base, t>::L1BAND;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::l2band_t drw2d_t<base, t>::L2BAND;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::texorg_t drw2d_t<base, t>::TEXORG;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::texpitch_t drw2d_t<base, t>::TEXPITCH;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::texmsk_t drw2d_t<base, t>::TEXMSK;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::lust_t drw2d_t<base, t>::LUST;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::luxadd_t drw2d_t<base, t>::LUXADD;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::luyadd_t drw2d_t<base, t>::LUYADD;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::lvsti_t drw2d_t<base, t>::LVSTI;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::lvstf_t drw2d_t<base, t>::LVSTF;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::lvxaddi_t drw2d_t<base, t>::LVXADDI;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::lvyaddi_t drw2d_t<base, t>::LVYADDI;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::lvyxaddf_t drw2d_t<base, t>::LVYXADDF;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::texcladdr_t drw2d_t<base, t>::TEXCLADDR;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::texcldata_t drw2d_t<base, t>::TEXCLDATA;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::texclofst_t drw2d_t<base, t>::TEXCLOFST;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::colkey_t drw2d_t<base, t>::COLKEY;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::size_t drw2d_t<base, t>::SIZE;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::pitch_t drw2d_t<base, t>::PITCH;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::origin_t drw2d_t<base, t>::ORIGIN;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::dlistst_t drw2d_t<base, t>::DLISTST;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::perftrg_t drw2d_t<base, t>::PERFTRG;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::perfcnt1_t drw2d_t<base, t>::PERFCNT1;
	template <uint32_t base, peripheral t> typename drw2d_t<base, t>::perfcnt2_t drw2d_t<base, t>::PERFCNT2;
}
