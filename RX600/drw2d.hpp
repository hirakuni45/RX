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
		static control_t<base + 0x00> CONTROL;


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
		static control2_t<base + 0x04> CONTROL2;


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
		static irqctl_t<base + 0xC0> IRQCTL;


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
		static cachectl_t<base + 0xC4> CACHECTL;


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
		static status_t<base + 0x00> STATUS;


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
		static hwver_t<base + 0x04> HWVER;


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
		static color1_t<base + 0x64> COLOR1;


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
		static color2_t<base + 0x68> COLOR2;


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
		static pattern_t<base + 0x74> PATTERN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	リミッタ n 開始値レジスタ (LnSTART) (n = 1 ～ 6)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static trw32_t<base + 0x10> L1START;
		static trw32_t<base + 0x14> L2START;
		static trw32_t<base + 0x18> L3START;
		static trw32_t<base + 0x1C> L4START;
		static trw32_t<base + 0x20> L5START;
		static trw32_t<base + 0x24> L6START;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	リミッタ n X 軸インクリメントレジスタ (LnXADD) (n = 1 ～ 6)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static trw32_t<base + 0x28> L1XADD;
		static trw32_t<base + 0x2C> L2XADD;
		static trw32_t<base + 0x30> L3XADD;
		static trw32_t<base + 0x34> L4XADD;
		static trw32_t<base + 0x38> L5XADD;
		static trw32_t<base + 0x3C> L6XADD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	リミッタ n Y 軸インクリメントレジスタ (LnYADD) (n = 1 ～ 6)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static trw32_t<base + 0x40> L1YADD;
		static trw32_t<base + 0x44> L2YADD;
		static trw32_t<base + 0x48> L3YADD;
		static trw32_t<base + 0x4C> L4YADD;
		static trw32_t<base + 0x50> L5YADD;
		static trw32_t<base + 0x54> L6YADD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	リミッタ m バンド幅パラメータレジスタ (LmBAND) (m = 1, 2)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static trw32_t<base + 0x58> L1BAND;
		static trw32_t<base + 0x5C> L2BAND;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	テクスチャベースアドレスレジスタ (TEXORG)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static trw32_t<base + 0xBC> TEXORG;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	テクスチャラインテクセル数レジスタ (TEXPITCH)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static trw32_t<base + 0xB4> TEXPITCH;


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
		static texmsk_t<base + 0xB8> TEXMSK;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	U リミッタ開始値レジスタ (LUST)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static trw32_t<base + 0x90> LUST;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	U リミッタ X 軸インクリメントレジスタ (LUXADD)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static trw32_t<base + 0x94> LUXADD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	U リミッタ Y 軸インクリメントレジスタ (LUYADD)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static trw32_t<base + 0x98> LUYADD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	V リミッタ開始値整数部レジスタ (LVSTI)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static trw32_t<base + 0x9C> LVSTI;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	V リミッタ開始値小数部レジスタ (LVSTF) @n
					※下位１６ビットのみが有効
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static trw32_t<base + 0xA0> LVSTF;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	V リミッタ X 軸インクリメント整数部レジスタ (LVXADDI)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static trw32_t<base + 0xA4> LVXADDI;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	V リミッタ Y 軸インクリメント整数部レジスタ (LVYADDI)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static trw32_t<base + 0xA8> LVYADDI;


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
		static lvyxaddf_t<base + 0xAC> LVYXADDF;


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
		static texcladdr_t<base + 0xDC> TEXCLADDR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	CLUT データレジスタ (TEXCLDATA)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static trw32_t<base + 0xE0> TEXCLDATA;


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
		static texclofst_t<base + 0xE4> TEXCLOFST;


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
		static colkey_t<base + 0xE8> COLKEY;


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
		static size_t<base + 0x78> SIZE;


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
		static pitch_t<base + 0x7C> PITCH;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	フレームバッファベースアドレスレジスタ (ORIGIN)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static trw32_t<base + 0x80> ORIGIN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ディスプレイリスト開始アドレスレジスタ (DLISTST)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static trw32_t<base + 0xC8> DLISTST;


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
		static perftrg_t<base + 0xD4> PERFTRG;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	パフォーマンスカウンタ k (PERFCNTk) (k = 1, 2)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static trw32_t<base + 0xCC> PERFCNT1;
		static trw32_t<base + 0xD0> PERFCNT2;
	};

	typedef drw2d_t<0x000E3000, peripheral::DRW2D> DRW2D;
}
