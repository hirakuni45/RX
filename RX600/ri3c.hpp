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




#if 0
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  I3C バスインタフェース (RI3C)
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txi		「送信データエンプティ」割り込みベクター
		@param[in]	rxi		「受信データフル」割り込みベクター
		@param[in]	eei		「通信エラー、通信イベント」割り込みベクター
		@param[in]	tei		「送信終了」割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per,
		ICU::VECTOR txi, ICU::VECTOR rxi, ICU::VECTOR eei, ICU::VECTOR tei>
	struct ri3c_t : ri3c_core_t<base> {
		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto TXI  = txi;		///< 受信割り込みベクター
		static constexpr auto RXI  = rxi;		///< 送信割り込みベクター
		static constexpr auto EEI  = eei;		///< 通信エラー、イベント割り込みベクター
		static constexpr auto TEI  = tei;		///< 送信終了割り込みベクター
		static constexpr auto PCLK = clock_profile::PCLKA;	///< クロック周波数
	};
//	template <uint32_t base, peripheral per, ICU::VECTOR txi, ICU::VECTOR rxi, ICU::VECTOR eei, ICU::VECTOR tei, uint32_t pclk>
//		typename riic_t<base, per, txi, rxi, eei, tei, pclk>::TMOCNTL_ riic_t<base, per, txi, rxi, eei, tei, pclk>::TMOCNTL;


#if defined(SIG_RX26T)
	typedef riica_t<0x000E'C000, peripheral::RI3C0, ICU::VECTOR::ICTXI0, ICU::VECTOR::ICRXI0,
		ICU::VECTOR, ICU::VECTOR::ICEEI0, ICU::VECTOR::ICTEI0, clock_profile::PCLKB> RIIC0;
#endif
#endif
}
