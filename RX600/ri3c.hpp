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


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	IBI 通知制御レジスタ (ICINCR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icincr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bit_rw_t <io_, bitpos::B0>      RHJRN;
			bit_rw_t <io_, bitpos::B1>      RCRRN;

			bit_rw_t <io_, bitpos::B3>      RTIRN;
		};
		typedef icincr_t<base + 0x58> ICINCR_;
		static  ICINCR_ ICINCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ターゲットモード制御レジスタ (ICTCR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct ictcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bit_rw_t <io_, bitpos::B16>     TA0DE;
		};
		typedef ictcr_t<base + 0x64> ICTCR_;
		static  ICTCR_ ICTCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	標準ビットレートレジスタ (ICSBR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icsbr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bits_rw_t<io_, bitpos::B0,  8>  ODLW;
			bits_rw_t<io_, bitpos::B8,  8>  ODHW;
			bits_rw_t<io_, bitpos::B16, 6>  PPLW;

			bits_rw_t<io_, bitpos::B24, 6>  PPHW;

			bit_rw_t <io_, bitpos::B31>     ODDBL;
		};
		typedef icsbr_t<base + 0x74> ICSBR_;
		static  ICSBR_ ICSBR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	拡張ビットレートレジスタ (ICEBR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icebr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bits_rw_t<io_, bitpos::B0,  8>  ODLW;
			bits_rw_t<io_, bitpos::B8,  8>  ODHW;
			bits_rw_t<io_, bitpos::B16, 6>  PPLW;

			bits_rw_t<io_, bitpos::B24, 6>  PPHW;
		};
		typedef icebr_t<base + 0x78> ICEBR_;
		static  ICEBR_ ICEBR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	バスフリー時間設定レジスタ (ICBFTR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icbftr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 9>   VAL;
		};
		typedef icbftr_t<base + 0x7C> ICBFTR_;
		static  ICBFTR_ ICBFTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	バス利用可能時間設定レジスタ (ICBATR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icbatr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 9>   VAL;
		};
		typedef icbatr_t<base + 0x80> ICBATR_;
		static  ICBATR_ ICBATR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	バスアイドル時間設定レジスタ (ICBITR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icbitr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 18>  VAL;
		};
		typedef icbitr_t<base + 0x84> ICBITR_;
		static  ICBITR_ ICBITR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	出力信号制御レジスタ (ICOCR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icocr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bit_rw_t <io_, bitpos::B0>      SDAO;
			bit_rw_t <io_, bitpos::B1>      SCLO;
			bit_rw_t <io_, bitpos::B2>      SOWP;
		};
		typedef icocr_t<base + 0x88> ICOCR_;
		static  ICOCR_ ICOCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイムアウト制御レジスタ (ICTOR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct ictor_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bits_rw_t<io_, bitpos::B0, 2>   TMOS;

			bit_rw_t <io_, bitpos::B4>      TMOL;
			bit_rw_t <io_, bitpos::B5>      TMOH;
			bits_rw_t<io_, bitpos::B6, 2>   TMOM;
		};
		typedef ictor_t<base + 0x90> ICTOR_;
		static  ICTOR_ ICTOR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	クロックストール制御レジスタ (ICSTCR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icstcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bits_rw_t<io_, bitpos::B0, 16>  STT;

			bit_rw_t <io_, bitpos::B28>     AASE;

			bit_rw_t <io_, bitpos::B30>     PBSE;
			bit_rw_t <io_, bitpos::B31>     APSE;
		};
		typedef icstcr_t<base + 0xB0> ICSTCR_;
		static  ICSTCR_ ICSTCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ターゲット送受信データ長レジスタ (ICTDLR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct ictdlr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bits_rw_t<io_, bitpos::B16, 16> DLGTH;
		};
		typedef ictdlr_t<base + 0xC0> ICTDLR_;
		static  ICTDLR_ ICTDLR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	コマンドキューレジスタ (ICCQR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x150> ICCQR_;
		static  ICCQR_ ICCQR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	レスポンスキューレジスタ (ICRQR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x154> ICRQR_;
		static  ICRQR_ ICRQR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	送受信データレジスタ (ICDR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x158> ICDR_;
		static  ICDR_ ICDR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	IBI キューレジスタ (ICIQR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x17C> ICIQR_;
		static  ICIQR_ ICIQR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	受信ステータスキューレジスタ (ICSQR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw32_t<base + 0x180> ICSQR_;
		static  ICSQR_ ICSQR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	キューバッファしきい値制御レジスタ (ICQBTCR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icqbtcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bits_rw_t<io_, bitpos::B0,  8>  CQTH;
			bits_rw_t<io_, bitpos::B8,  8>  RQTH;
			bits_rw_t<io_, bitpos::B16, 8>  IDSS;
			bits_rw_t<io_, bitpos::B24, 8>  IQTH;
		};
		typedef icqbtcr_t<base + 0x190> ICQBTCR_;
		static  ICQBTCR_ ICQBTCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	データバッファしきい値制御レジスタ (ICDBTCR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icdbtcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bits_rw_t<io_, bitpos::B0,  3>  TETH;

			bits_rw_t<io_, bitpos::B8,  3>  RFTH;

			bits_rw_t<io_, bitpos::B16, 3>  TSTH;

			bits_rw_t<io_, bitpos::B24, 3>  RSTH;
		};
		typedef icdbtcr_t<base + 0x194> ICDBTCR_;
		static  ICDBTCR_ ICDBTCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	受信ステータスキューしきい値制御レジスタ (ICSQTCR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icsqtcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bits_rw_t<io_, bitpos::B0, 8>   SQTH;
		};
		typedef icsqtcr_t<base + 0x1C0> ICSQTCR_;
		static  ICSQTCR_ ICSQTCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ステータスレジスタ 2 (ICSR2)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icsr2_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bit_rw_t <io_, bitpos::B0>      START;
			bit_rw_t <io_, bitpos::B1>      STOP;
			bit_rw_t <io_, bitpos::B2>      HDRXDF;

			bit_rw_t <io_, bitpos::B20>     TMOF;
		};
		typedef icsr2_t<base + 0x1D0> ICSR2_;
		static  ICSR2_ ICSR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ステータス検出許可レジスタ (ICSER)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icser_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bit_rw_t <io_, bitpos::B0>      STDE;
			bit_rw_t <io_, bitpos::B1>      SPDE;
			bit_rw_t <io_, bitpos::B2>      HDRXDE;

			bit_rw_t <io_, bitpos::B20>     TMOE;
		};
		typedef icser_t<base + 0x1D4> ICSER_;
		static  ICSER_ ICSER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ステータス割り込み許可レジスタ (ICSIER)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icsier_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bit_rw_t <io_, bitpos::B0>      STIE;
			bit_rw_t <io_, bitpos::B1>      SPIE;
			bit_rw_t <io_, bitpos::B2>      HDRXIE;

			bit_rw_t <io_, bitpos::B20>     TMOIE;
		};
		typedef icsier_t<base + 0x1D8> ICSIER_;
		static  ICSIER_ ICSIER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	通信ステータスレジスタ (ICCSR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct iccsr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bit_rw_t <io_, bitpos::B0>      TDRE;
			bit_rw_t <io_, bitpos::B1>      RDRF;
			bit_rw_t <io_, bitpos::B2>      IQEFF;
			bit_rw_t <io_, bitpos::B3>      CQEF;
			bit_rw_t <io_, bitpos::B4>      RQFF;
			bit_rw_t <io_, bitpos::B5>      DTAF;

			bit_rw_t <io_, bitpos::B9>      DTEF;

			bit_rw_t <io_, bitpos::B20>     SQFF;
		};
		typedef iccsr_t<base + 0x1E0> ICCSR_;
		static  ICCSR_ ICCSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	通信ステータス検出許可レジスタ (ICCSER)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct iccser_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bit_rw_t <io_, bitpos::B0>      TDE;
			bit_rw_t <io_, bitpos::B1>      RDE;
			bit_rw_t <io_, bitpos::B2>      IQEFDE;
			bit_rw_t <io_, bitpos::B3>      CQEDE;
			bit_rw_t <io_, bitpos::B4>      RQFDE;
			bit_rw_t <io_, bitpos::B5>      DTADE;

			bit_rw_t <io_, bitpos::B9>      DTEDE;

			bit_rw_t <io_, bitpos::B20>     SQFDE;
		};
		typedef iccser_t<base + 0x1E4> ICCSER_;
		static  ICCSER_ ICCSER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	通信ステータス割り込み許可レジスタ (ICCSIER)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct iccsier_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bit_rw_t <io_, bitpos::B0>      TIE;
			bit_rw_t <io_, bitpos::B1>      RIE;
			bit_rw_t <io_, bitpos::B2>      IQEFIE;
			bit_rw_t <io_, bitpos::B3>      CQEIE;
			bit_rw_t <io_, bitpos::B4>      RQFIE;
			bit_rw_t <io_, bitpos::B5>      DTAIE;

			bit_rw_t <io_, bitpos::B9>      DTEIE;

			bit_rw_t <io_, bitpos::B20>     SQFIE;
		};
		typedef iccsier_t<base + 0x1E8> ICCSIER_;
		static  ICCSIER_ ICCSIER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	バスステータスレジスタ (ICBSR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icbsr_t : public ro32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();
	
			bit_ro_t <in_, bitpos::B0>      BFREE;
			bit_ro_t <in_, bitpos::B1>      BVAL;
			bit_ro_t <in_, bitpos::B2>      BIDL;
		};
		typedef icbsr_t<base + 0x210> ICBSR_;
		static ICBSR_ ICBSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ターゲットデバイスアドレステーブルレジスタ (ICTDATR[m]) (m = 0 ～ 3)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct ictdatr_t : public rw32_index_t<ofs> {
			typedef rw32_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j <= 3) { io_::index = j * 8; } }

			bits_rw_t<io_, bitpos::B0,  7>  SADR;

			bit_rw_t <io_, bitpos::B12>     IBIPL;
			bit_rw_t <io_, bitpos::B13>     TIRRJ;
			bit_rw_t <io_, bitpos::B14>     CRRRJ;
			bit_rw_t <io_, bitpos::B15>     IBITSE;

			bits_rw_t<io_, bitpos::B16, 8>  DADR;

			bits_rw_t<io_, bitpos::B29, 2>  NACKRC;
			bit_rw_t <io_, bitpos::B31>     TYPE;

			ictdatr_t& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef ictdatr_t<base + 0x224> ICTDATR_;
		static  ICTDATR_ ICTDATR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	拡張ターゲットデバイスアドレステーブルレジスタ (ICEDATR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icedatr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bits_rw_t<io_, bitpos::B0,  7>  SADR;

			bits_rw_t<io_, bitpos::B16, 8>  DADR;

			bits_rw_t<io_, bitpos::B29, 2>  NACKRC;
			bit_rw_t <io_, bitpos::B31>     TYPE;
		};
		typedef icedatr_t<base + 0x2A0> ICEDATR_;
		static  ICEDATR_ ICEDATR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	デバイスアドレスレジスタ 0 (ICDAR0)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icear0_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bits_rw_t<io_, bitpos::B0, 10>  SADR;

			bit_rw_t <io_, bitpos::B12>     IBIPL;

			bits_rw_t<io_, bitpos::B16, 7>  DADR;
		};
		typedef icear0_t<base + 0x2B0> ICEAR0_;
		static  ICEAR0_ ICEAR0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ターゲットデバイス特性テーブルレジスタ (ICTDCTR[m]) (m = 0 ～ 3)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct ictdctr_t : public rw32_index_t<ofs> {
			typedef rw32_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j <= 3) { io_::index = j * 4; } }

			bit_rw_t <io_, bitpos::B8>      LIMIT;
			bit_rw_t <io_, bitpos::B9>      IBIRQC;
			bit_rw_t <io_, bitpos::B10>     IBIPL;
			bit_rw_t <io_, bitpos::B11>     OFLC;

			bits_rw_t<io_, bitpos::B14, 2>  ROLE;

			ictdctr_t& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		typedef ictdctr_t<base + 0x2D0> ICTDCTR_;
		static  ICTDCTR_ ICTDCTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	デバイス特性テーブルレジスタ (ICDCTR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icdctr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bits_rw_t<io_, bitpos::B0, 8>   DCR;
			bit_rw_t <io_, bitpos::B8>      LIMIT;
			bit_rw_t <io_, bitpos::B9>      IBIRQC;
			bit_rw_t <io_, bitpos::B10>     IBIPL;
			bit_rw_t <io_, bitpos::B11>     OFLC;

			bits_rw_t<io_, bitpos::B14, 2>  ROLE;
		};
		typedef icdctr_t<base + 0x320> ICDCTR_;
		static  ICDCTR_ ICDCTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	支給 ID 下位レジスタ (ICPIDLR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icpidlr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bits_rw_t<io_, bitpos::B0, 16>  VAL;
		};
		typedef icpidlr_t<base + 0x324> ICPIDLR_;
		static  ICPIDLR_ ICPIDLR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	支給 ID 上位レジスタ (ICPIDHR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icpidhr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bits_rw_t<io_, bitpos::B0, 16>  VAL;
		};
		typedef icpidhr_t<base + 0x328> ICPIDHR_;
		static  ICPIDHR_ ICPIDHR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	デバイスアドレスモニタレジスタ 0 (ICDAMR0)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icdamr0_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bits_rw_t<io_, bitpos::B16, 10> TADR;

			bit_rw_t <io_, bitpos::B30>     SAV;
			bit_rw_t <io_, bitpos::B31>     DAV;
		};
		typedef icdamr0_t<base + 0x330> ICDAMR0_;
		static  ICDAMR0_ ICDAMR0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ターゲットイベントレジスタ (ICTEVR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct ictevr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bit_rw_t <io_, bitpos::B0>      ENINT;
			bit_rw_t <io_, bitpos::B1>      ENCR;

			bit_rw_t <io_, bitpos::B3>      ENHJ;
		};
		typedef ictevr_t<base + 0x350> ICTEVR_;
		static  ICTEVR_ ICTEVR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	アクティビティステートレジスタ (ICASR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icasr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bit_rw_t <io_, bitpos::B0>      ENTAS0;
			bit_rw_t <io_, bitpos::B1>      ENTAS1;
			bit_rw_t <io_, bitpos::B2>      ENTAS2;
			bit_rw_t <io_, bitpos::B3>      ENTAS3;
		};
		typedef icasr_t<base + 0x354> ICASR_;
		static  ICASR_ ICASR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	最大ライト長レジスタ (ICMWLR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icmwlr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bits_rw_t<io_, bitpos::B0, 16>   NWL;
		};
		typedef icmwlr_t<base + 0x358> ICMWLR_;
		static  ICMWLR_ ICMWLR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	最大リード長レジスタ (ICMRLR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icmrlr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bits_rw_t<io_, bitpos::B0, 16>   MRL;
			bits_rw_t<io_, bitpos::B16, 8>   IBPL;
		};
		typedef icmrlr_t<base + 0x35C> ICMRLR_;
		static  ICMRLR_ ICMRLR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	テストモードレジスタ (ICTMR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct ictmr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bits_rw_t<io_, bitpos::B0, 8>    TM;
		};
		typedef ictmr_t<base + 0x360> ICTMR_;
		static  ICTMR_ ICTMR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	デバイスステータスレジスタ (ICDSR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icdsr_t : public rw32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bits_rw_t<io_, bitpos::B0, 4>    PNDINT;

			bit_ro_t <in_, bitpos::B5>       PERR;
			bits_rw_t<io_, bitpos::B6, 2>    CAS;
			bits_rw_t<io_, bitpos::B8, 8>    VRSV;
		};
		typedef icdsr_t<base + 0x364> ICDSR_;
		static  ICDSR_ ICDSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	最高ライト速度レジスタ (ICMWSR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icmwsr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bits_rw_t<io_, bitpos::B0, 3>    MSWDR;
		};
		typedef icmwsr_t<base + 0x368> ICMWSR_;
		static  ICMWSR_ ICMWSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	最高リード速度レジスタ (ICMRSR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icmrsr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bits_rw_t<io_, bitpos::B0, 3>    MSRDR;
			bits_rw_t<io_, bitpos::B3, 3>    TSCO;
		};
		typedef icmrsr_t<base + 0x36C> ICMRSR_;
		static  ICMRSR_ ICMRSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	最大リード応答時間レジスタ (ICMTTR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icmttr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bits_rw_t<io_, bitpos::B0, 24>   MRTT;

			bit_rw_t <io_, bitpos::B31>      MRTTE;
		};
		typedef icmttr_t<base + 0x370> ICMTTR_;
		static  ICMTTR_ ICMTTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	タイミングサポート情報レジスタ (ICTSIR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct ictsir_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bits_rw_t<io_, bitpos::B8,  8>   FREQ;
			bits_rw_t<io_, bitpos::B16, 8>   INAC;
		};
		typedef ictsir_t<base + 0x374> ICTSIR_;
		static  ICTSIR_ ICTSIR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	ビットカウントレジスタ (ICBCR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icbcr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bits_rw_t<io_, bitpos::B0, 5>    BC;
		};
		typedef icbcr_t<base + 0x380> ICBCR_;
		static  ICBCR_ ICBCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	キューバッファステータスレジスタ (ICQBSR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icqbsr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bits_rw_t<io_, bitpos::B0,  8>   CQFL;
			bits_rw_t<io_, bitpos::B8,  8>   RQFL;
			bits_rw_t<io_, bitpos::B16, 8>   IQFL;
			bits_rw_t<io_, bitpos::B24, 5>   ISC;
		};
		typedef icqbsr_t<base + 0x394> ICQBSR_;
		static  ICQBSR_ ICQBSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	データバッファステータスレジスタ (ICDBSR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icdbsr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bits_rw_t<io_, bitpos::B0, 8>    TBFL;
			bits_rw_t<io_, bitpos::B8, 8>    RBFL;
		};
		typedef icdbsr_t<base + 0x398> ICDBSR_;
		static  ICDBSR_ ICDBSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	受信ステータスキューステータスレジスタ (ICSQSR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icsqsr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;
	
			bits_rw_t<io_, bitpos::B0, 8>    SQFL;
		};
		typedef icsqsr_t<base + 0x3C0> ICSQSR_;
		static  ICSQSR_ ICSQSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	内部ステータスモニタレジスタ (ICIMR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icimr_t : public rw32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();
	
			bit_ro_t <in_, bitpos::B0>       SCLI;
			bit_ro_t <in_, bitpos::B1>       SDAI;
			bit_ro_t <in_, bitpos::B2>       SCLO;
			bit_ro_t <in_, bitpos::B3>       SDAO;
		};
		typedef icimr_t<base + 0x3CC> ICIMR_;
		static  ICIMR_ ICIMR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	コントローラエラーカウントレジスタ (ICCECR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct iccecr_t : public rw32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();
	
			bits_ro_t<in_, bitpos::B0, 8>    CE2C;
		};
		typedef iccecr_t<base + 0x3D0> ICCECR_;
		static  ICCECR_ ICCECR;
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
	template <uint32_t base> typename ri3c_core_t<base>::ICINCR_  ri3c_core_t<base>::ICINCR;
	template <uint32_t base> typename ri3c_core_t<base>::ICTCR_   ri3c_core_t<base>::ICTCR;
	template <uint32_t base> typename ri3c_core_t<base>::ICSBR_   ri3c_core_t<base>::ICSBR;
	template <uint32_t base> typename ri3c_core_t<base>::ICEBR_   ri3c_core_t<base>::ICEBR;
	template <uint32_t base> typename ri3c_core_t<base>::ICBFTR_  ri3c_core_t<base>::ICBFTR;
	template <uint32_t base> typename ri3c_core_t<base>::ICBATR_  ri3c_core_t<base>::ICBATR;
	template <uint32_t base> typename ri3c_core_t<base>::ICBITR_  ri3c_core_t<base>::ICBITR;
	template <uint32_t base> typename ri3c_core_t<base>::ICOCR_   ri3c_core_t<base>::ICOCR;
	template <uint32_t base> typename ri3c_core_t<base>::ICTOR_   ri3c_core_t<base>::ICTOR;
	template <uint32_t base> typename ri3c_core_t<base>::ICSTCR_  ri3c_core_t<base>::ICSTCR;
	template <uint32_t base> typename ri3c_core_t<base>::ICTDLR_  ri3c_core_t<base>::ICTDLR;
	template <uint32_t base> typename ri3c_core_t<base>::ICCQR_   ri3c_core_t<base>::ICCQR;
	template <uint32_t base> typename ri3c_core_t<base>::ICRQR_   ri3c_core_t<base>::ICRQR;
	template <uint32_t base> typename ri3c_core_t<base>::ICDR_    ri3c_core_t<base>::ICDR;
	template <uint32_t base> typename ri3c_core_t<base>::ICIQR_   ri3c_core_t<base>::ICIQR;
	template <uint32_t base> typename ri3c_core_t<base>::ICSQR_   ri3c_core_t<base>::ICSQR;
	template <uint32_t base> typename ri3c_core_t<base>::ICQBTCR_ ri3c_core_t<base>::ICQBTCR;
	template <uint32_t base> typename ri3c_core_t<base>::ICDBTCR_ ri3c_core_t<base>::ICDBTCR;
	template <uint32_t base> typename ri3c_core_t<base>::ICSQTCR_ ri3c_core_t<base>::ICSQTCR;
	template <uint32_t base> typename ri3c_core_t<base>::ICSR2_   ri3c_core_t<base>::ICSR2;
	template <uint32_t base> typename ri3c_core_t<base>::ICSER_   ri3c_core_t<base>::ICSER;
	template <uint32_t base> typename ri3c_core_t<base>::ICSIER_  ri3c_core_t<base>::ICSIER;
	template <uint32_t base> typename ri3c_core_t<base>::ICCSR_   ri3c_core_t<base>::ICCSR;
	template <uint32_t base> typename ri3c_core_t<base>::ICCSER_  ri3c_core_t<base>::ICCSER;
	template <uint32_t base> typename ri3c_core_t<base>::ICCSIER_ ri3c_core_t<base>::ICCSIER;
	template <uint32_t base> typename ri3c_core_t<base>::ICBSR_   ri3c_core_t<base>::ICBSR;
	template <uint32_t base> typename ri3c_core_t<base>::ICTDATR_ ri3c_core_t<base>::ICTDATR;
	template <uint32_t base> typename ri3c_core_t<base>::ICEDATR_ ri3c_core_t<base>::ICEDATR;
	template <uint32_t base> typename ri3c_core_t<base>::ICEAR0_  ri3c_core_t<base>::ICEAR0;
	template <uint32_t base> typename ri3c_core_t<base>::ICTDCTR_ ri3c_core_t<base>::ICTDCTR;
	template <uint32_t base> typename ri3c_core_t<base>::ICDCTR_  ri3c_core_t<base>::ICDCTR;
	template <uint32_t base> typename ri3c_core_t<base>::ICPIDLR_ ri3c_core_t<base>::ICPIDLR;
	template <uint32_t base> typename ri3c_core_t<base>::ICPIDHR_ ri3c_core_t<base>::ICPIDHR;
	template <uint32_t base> typename ri3c_core_t<base>::ICDAMR0_ ri3c_core_t<base>::ICDAMR0;
	template <uint32_t base> typename ri3c_core_t<base>::ICTEVR_  ri3c_core_t<base>::ICTEVR;
	template <uint32_t base> typename ri3c_core_t<base>::ICASR_   ri3c_core_t<base>::ICASR;
	template <uint32_t base> typename ri3c_core_t<base>::ICMWLR_  ri3c_core_t<base>::ICMWLR;
	template <uint32_t base> typename ri3c_core_t<base>::ICMRLR_  ri3c_core_t<base>::ICMRLR;
	template <uint32_t base> typename ri3c_core_t<base>::ICTMR_   ri3c_core_t<base>::ICTMR;
	template <uint32_t base> typename ri3c_core_t<base>::ICDSR_   ri3c_core_t<base>::ICDSR;
	template <uint32_t base> typename ri3c_core_t<base>::ICMWSR_  ri3c_core_t<base>::ICMWSR;
	template <uint32_t base> typename ri3c_core_t<base>::ICMRSR_  ri3c_core_t<base>::ICMRSR;
	template <uint32_t base> typename ri3c_core_t<base>::ICMTTR_  ri3c_core_t<base>::ICMTTR;
	template <uint32_t base> typename ri3c_core_t<base>::ICTSIR_  ri3c_core_t<base>::ICTSIR;
	template <uint32_t base> typename ri3c_core_t<base>::ICBCR_   ri3c_core_t<base>::ICBCR;
	template <uint32_t base> typename ri3c_core_t<base>::ICQBSR_  ri3c_core_t<base>::ICQBSR;
	template <uint32_t base> typename ri3c_core_t<base>::ICDBSR_  ri3c_core_t<base>::ICDBSR;
	template <uint32_t base> typename ri3c_core_t<base>::ICSQSR_  ri3c_core_t<base>::ICSQSR;
	template <uint32_t base> typename ri3c_core_t<base>::ICIMR_   ri3c_core_t<base>::ICIMR;
	template <uint32_t base> typename ri3c_core_t<base>::ICCECR_  ri3c_core_t<base>::ICCECR;


#if defined(SIG_RX26T)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  I3C バスインタフェース (RI3C)
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per>
	struct ri3c_t : ri3c_core_t<base> {
		static constexpr auto PERIPHERAL = per;				///< ペリフェラル型
		static constexpr auto TXI   = ICU::VECTOR::TXI;		///< 送信データエンプティ・割り込みベクター
		static constexpr auto RXI   = ICU::VECTOR::RXI;		///< 受信データフル・割り込みベクター
		static constexpr auto IBII  = ICU::VECTOR::IBII;	///< IBI キューエンプティ／フル・割り込みベクター
		static constexpr auto CMDI  = ICU::VECTOR::CMDI;	///< コマンドキューエンプティ・割り込みベクター
		static constexpr auto RESPI = ICU::VECTOR::RESPI;	///< レスポンスキューフル・割り込みベクター
		static constexpr auto RCVI  = ICU::VECTOR::RCVI;	///< 受信ステータスキューフル・割り込みベクター
		static constexpr auto EEI   = ICU::GROUPAL1::EEI;	///< 通信エラー/通信イベント・割り込みベクター
		static constexpr auto PCLK = clock_profile::PCLKA;	///< クロック周波数
	};
	typedef ri3c_t<0x000E'C000, peripheral::RI3C0> RI3C0;
#endif
}
