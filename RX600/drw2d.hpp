#pragma once
//=====================================================================//
/*!	@file
	@brief	RX600 グループ DRW2D 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2020 Kunihito Hiramatsu @n
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
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct drw2d_t {

		static const auto PERIPHERAL = per;					///< ペリフェラル型
		static const auto IVEC = ICU::VECTOR_AL1::DRW_IRQ;	///< 割り込みベクター


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ジオメトリコントロールレジスタ (CONTROL)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct control_t : public trw32_t<ofs> {
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
		typedef control_t<base + 0x00> CONTROL_;
		static  CONTROL_ CONTROL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  サーフェスコントロールレジスタ (CONTROL2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct control2_t : public trw32_t<ofs> {
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
		typedef control2_t<base + 0x04> CONTROL2_;
		static  CONTROL2_ CONTROL2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  割り込みコントロールレジスタ (IRQCTL)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct irqctl_t : public trw32_t<ofs> {
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
		typedef irqctl_t<base + 0xC0> IRQCTL_;
		static  IRQCTL_ IRQCTL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  キャッシュコントロールレジスタ (CACHECTL)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct cachectl_t : public trw32_t<ofs> {
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
		typedef cachectl_t<base + 0xC4> CACHECTL_;
		static  CACHECTL_ CACHECTL;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ステータスレジスタ (STATUS)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct status_t : public ro32_t<ofs> {
			typedef ro32_t<ofs> io_;
			using io_::operator ();

			bit_ro_t <io_, bitpos::B0>      BSYENUM;
			bit_ro_t <io_, bitpos::B1>      BSYWR;
			bit_ro_t <io_, bitpos::B2>      CACHEDTY;
			bit_ro_t <io_, bitpos::B3>      DLSTACT;
			bit_ro_t <io_, bitpos::B4>      ENUIR;
			bit_ro_t <io_, bitpos::B5>      DLIR;
		};
		typedef status_t<base + 0x00> STATUS_;
		static  STATUS_ STATUS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ハードウェアバージョンレジスタ (HWVER)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct hwver_t : public ro32_t<ofs> {
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
		typedef hwver_t<base + 0x04> HWVER_;
		static  HWVER_ HWVER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ベースカラーレジスタ (COLOR1)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct color1_t : public trw32_t<ofs> {
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
		typedef color1_t<base + 0x64> COLOR1_;
		static  COLOR1_ COLOR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  セカンダリカラーレジスタ (COLOR2)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct color2_t : public trw32_t<ofs> {
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
		typedef color2_t<base + 0x68> COLOR2_;
		static  COLOR2_ COLOR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	パターンレジスタ (PATTERN)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct pattern_t : public trw32_t<ofs> {
			typedef trw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>    PATTERN;
		};
		typedef pattern_t<base + 0x74> PATTERN_;
		static  PATTERN_ PATTERN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	リミッタ n 開始値レジスタ (LnSTART) (n = 1 ～ 6)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0x10> L1START_;
		static  L1START_ L1START;
		typedef trw32_t<base + 0x14> L2START_;
		static  L2START_ L2START;
		typedef trw32_t<base + 0x18> L3START_;
		static  L3START_ L3START;
		typedef trw32_t<base + 0x1C> L4START_;
		static  L4START_ L4START;
		typedef trw32_t<base + 0x20> L5START_;
		static  L5START_ L5START;
		typedef trw32_t<base + 0x24> L6START_;
		static  L6START_ L6START;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	リミッタ n X 軸インクリメントレジスタ (LnXADD) (n = 1 ～ 6)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0x28> L1XADD_;
		static  L1XADD_ L1XADD;
		typedef trw32_t<base + 0x2C> L2XADD_;
		static  L2XADD_ L2XADD;
		typedef trw32_t<base + 0x30> L3XADD_;
		static  L3XADD_ L3XADD;
		typedef trw32_t<base + 0x34> L4XADD_;
		static  L4XADD_ L4XADD;
		typedef trw32_t<base + 0x38> L5XADD_;
		static  L5XADD_ L5XADD;
		typedef trw32_t<base + 0x3C> L6XADD_;
		static  L6XADD_ L6XADD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	リミッタ n Y 軸インクリメントレジスタ (LnYADD) (n = 1 ～ 6)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0x40> L1YADD_;
		static  L1YADD_ L1YADD;
		typedef trw32_t<base + 0x44> L2YADD_;
		static  L2YADD_ L2YADD;
		typedef trw32_t<base + 0x48> L3YADD_;
		static  L3YADD_ L3YADD;
		typedef trw32_t<base + 0x4C> L4YADD_;
		static  L4YADD_ L4YADD;
		typedef trw32_t<base + 0x50> L5YADD_;
		static  L5YADD_ L5YADD;
		typedef trw32_t<base + 0x54> L6YADD_;
		static  L6YADD_ L6YADD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	リミッタ m バンド幅パラメータレジスタ (LmBAND) (m = 1, 2)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0x58> L1BAND_;
		static  L1BAND_ L1BAND;
		typedef trw32_t<base + 0x5C> L2BAND_;
		static  L2BAND_ L2BAND;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	テクスチャベースアドレスレジスタ (TEXORG)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0xBC> TEXORG_;
		static  TEXORG_ TEXORG;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	テクスチャラインテクセル数レジスタ (TEXPITCH)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0xB4> TEXPITCH_;
		static  TEXPITCH_ TEXPITCH;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	テクスチャマスクレジスタ (TEXMSK)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct texmsk_t : public trw32_t<ofs> {
			typedef trw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  11>  TEXUMASK;
			bits_rw_t<io_, bitpos::B11, 21>  TEXVMASK;
		};
		typedef texmsk_t<base + 0xB8> TEXMSK_;
		static  TEXMSK_ TEXMSK;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	U リミッタ開始値レジスタ (LUST)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0x90> LUST_;
		static  LUST_ LUST;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	U リミッタ X 軸インクリメントレジスタ (LUXADD)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0x94> LUXADD_;
		static  LUXADD_ LUXADD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	U リミッタ Y 軸インクリメントレジスタ (LUYADD)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0x98> LUYADD_;
		static  LUYADD_ LUYADD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	V リミッタ開始値整数部レジスタ (LVSTI)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0x9C> LVSTI_;
		static  LVSTI_ LVSTI;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	V リミッタ開始値小数部レジスタ (LVSTF) @n
					※下位１６ビットのみが有効
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0xA0> LVSTF_;
		static  LVSTF_ LVSTF;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	V リミッタ X 軸インクリメント整数部レジスタ (LVXADDI)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0xA4> LVXADDI_;
		static  LVXADDI_ LVXADDI;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	V リミッタ Y 軸インクリメント整数部レジスタ (LVYADDI)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0xA8> LVYADDI_;
		static  LVYADDI_ LVYADDI;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	V リミッタインクリメント小数部レジスタ (LVYXADDF)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct lvyxaddf_t : public trw32_t<ofs> {
			typedef trw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  16>  LVYADDF;
			bits_rw_t<io_, bitpos::B16, 16>  LVXADDF;
		};
		typedef lvyxaddf_t<base + 0xAC> LVYXADDF_;
		static  LVYXADDF_ LVYXADDF;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	CLUT 開始アドレスレジスタ (TEXCLADDR)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct texcladdr_t : public trw32_t<ofs> {
			typedef trw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>  CLADDR;
		};
		typedef texcladdr_t<base + 0xDC> TEXCLADDR_;
		static  TEXCLADDR_ TEXCLADDR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	CLUT データレジスタ (TEXCLDATA)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0xE0> TEXCLDATA_;
		static  TEXCLDATA_ TEXCLDATA;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	CLUT オフセットレジスタ (TEXCLOFST)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct texclofst_t : public trw32_t<ofs> {
			typedef trw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>  CLOFST;
		};
		typedef texclofst_t<base + 0xE4> TEXCLOFST_;
		static  TEXCLOFST_ TEXCLOFST;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	クロマキーレジスタ (COLKEY)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct colkey_t : public trw32_t<ofs> {
			typedef trw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  8>  B;
			bits_rw_t<io_, bitpos::B8,  8>  G;
			bits_rw_t<io_, bitpos::B16, 8>  R;
		};
		typedef colkey_t<base + 0xE8> COLKEY_;
		static  COLKEY_ COLKEY;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	バウンディングボックスサイズレジスタ (SIZE)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct size_t : public trw32_t<ofs> {
			typedef trw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  16>  X;
			bits_rw_t<io_, bitpos::B16, 16>  Y;
		};
		typedef size_t<base + 0x78> SIZE_;
		static  SIZE_ SIZE;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	フレームバッファピッチレジスタ (PITCH)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct pitch_t : public trw32_t<ofs> {
			typedef trw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  16>  PITCH;
			bits_rw_t<io_, bitpos::B16, 16>  SSD;
		};
		typedef pitch_t<base + 0x7C> PITCH_;
		static  PITCH_ PITCH;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	フレームバッファベースアドレスレジスタ (ORIGIN)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0x80> ORIGIN_;
		static  ORIGIN_ ORIGIN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ディスプレイリスト開始アドレスレジスタ (DLISTST)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0xC8> DLISTST_;
		static  DLISTST_ DLISTST;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	パフォーマンスカウンタコントロールレジスタ (PERFTRG)
			@param[in]	ofs	オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct perftrg_t : public trw32_t<ofs> {
			typedef trw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  16>  TRG1;
			bits_rw_t<io_, bitpos::B16, 16>  TRG2;
		};
		typedef perftrg_t<base + 0xD4> PERFTRG_;
		static  PERFTRG_ PERFTRG;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	パフォーマンスカウンタ k (PERFCNTk) (k = 1, 2)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef trw32_t<base + 0xCC> PERFCNT1_;
		static  PERFCNT1_ PERFCNT1;
		typedef trw32_t<base + 0xD0> PERFCNT2_;
		static  PERFCNT2_ PERFCNT2;
	};
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::CONTROL_ drw2d_t<base, per>::CONTROL;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::CONTROL2_ drw2d_t<base, per>::CONTROL2;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::IRQCTL_ drw2d_t<base, per>::IRQCTL;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::CACHECTL_ drw2d_t<base, per>::CACHECTL;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::STATUS_ drw2d_t<base, per>::STATUS;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::HWVER_ drw2d_t<base, per>::HWVER;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::COLOR1_ drw2d_t<base, per>::COLOR1;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::COLOR2_ drw2d_t<base, per>::COLOR2;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::PATTERN_ drw2d_t<base, per>::PATTERN;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::L1START_ drw2d_t<base, per>::L1START;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::L2START_ drw2d_t<base, per>::L2START;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::L3START_ drw2d_t<base, per>::L3START;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::L4START_ drw2d_t<base, per>::L4START;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::L5START_ drw2d_t<base, per>::L5START;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::L6START_ drw2d_t<base, per>::L6START;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::L1XADD_ drw2d_t<base, per>::L1XADD;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::L2XADD_ drw2d_t<base, per>::L2XADD;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::L3XADD_ drw2d_t<base, per>::L3XADD;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::L4XADD_ drw2d_t<base, per>::L4XADD;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::L5XADD_ drw2d_t<base, per>::L5XADD;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::L6XADD_ drw2d_t<base, per>::L6XADD;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::L1YADD_ drw2d_t<base, per>::L1YADD;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::L2YADD_ drw2d_t<base, per>::L2YADD;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::L3YADD_ drw2d_t<base, per>::L3YADD;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::L4YADD_ drw2d_t<base, per>::L4YADD;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::L5YADD_ drw2d_t<base, per>::L5YADD;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::L6YADD_ drw2d_t<base, per>::L6YADD;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::L1BAND_ drw2d_t<base, per>::L1BAND;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::L2BAND_ drw2d_t<base, per>::L2BAND;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::TEXORG_ drw2d_t<base, per>::TEXORG;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::TEXPITCH_ drw2d_t<base, per>::TEXPITCH;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::TEXMSK_ drw2d_t<base, per>::TEXMSK;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::LUST_ drw2d_t<base, per>::LUST;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::LUXADD_ drw2d_t<base, per>::LUXADD;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::LUYADD_ drw2d_t<base, per>::LUYADD;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::LVSTI_ drw2d_t<base, per>::LVSTI;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::LVSTF_ drw2d_t<base, per>::LVSTF;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::LVXADDI_ drw2d_t<base, per>::LVXADDI;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::LVYADDI_ drw2d_t<base, per>::LVYADDI;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::LVYXADDF_ drw2d_t<base, per>::LVYXADDF;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::TEXCLADDR_ drw2d_t<base, per>::TEXCLADDR;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::TEXCLDATA_ drw2d_t<base, per>::TEXCLDATA;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::TEXCLOFST_ drw2d_t<base, per>::TEXCLOFST;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::COLKEY_ drw2d_t<base, per>::COLKEY;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::SIZE_ drw2d_t<base, per>::SIZE;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::PITCH_ drw2d_t<base, per>::PITCH;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::ORIGIN_ drw2d_t<base, per>::ORIGIN;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::DLISTST_ drw2d_t<base, per>::DLISTST;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::PERFTRG_ drw2d_t<base, per>::PERFTRG;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::PERFCNT1_ drw2d_t<base, per>::PERFCNT1;
	template <uint32_t base, peripheral per> typename drw2d_t<base, per>::PERFCNT2_ drw2d_t<base, per>::PERFCNT2;


	typedef drw2d_t<0x000E3000, peripheral::DRW2D> DRW2D;
}
