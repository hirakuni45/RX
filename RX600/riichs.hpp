#pragma once
//=============================================================================//
/*!	@file
	@brief	ハイスピード I2C バスインタフェース (RIICHS) @n
			RX671
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RIICHS コア 定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<uint32_t base>
	struct riichs_core_t {

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

			bit_rw_t<io_, bitpos::B31> ICE;
		};
		static inline iccr_t<base + 0x14> ICCR;


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

			bit_rw_t<io_, bitpos::B1>  MRST;

			bit_rw_t<io_, bitpos::B16> ISRST;
		};
		static inline icrcr_t<base + 0x20> ICRCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  動作モードモニタレジスタ (ICMMR)
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

			bit_rw_t<io_, bitpos::B2>  MST;

			bit_rw_t<io_, bitpos::B4>  TRS;

			bit_rw_t<io_, bitpos::B7>  MSWP;
		};
		static inline icmmr_t<base + 0x24> ICMMR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ファンクション許可レジスタ (ICFER)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icfer_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  MALE;
			bit_rw_t<io_, bitpos::B1>  NALE;
			bit_rw_t<io_, bitpos::B2>  SALE;

			bit_rw_t<io_, bitpos::B8>  SCLE;

			bit_rw_t<io_, bitpos::B12> SMBS;

			bit_rw_t<io_, bitpos::B14> FMPE;
			bit_rw_t<io_, bitpos::B15> HSME;
		};
		static inline icfer_t<base + 0x60> ICFER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  スレーブモード制御レジスタ (ICSCR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icscr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  GCAE;

			bit_rw_t<io_, bitpos::B5>  HSMCE;
			bit_rw_t<io_, bitpos::B6>  DIDE;

			bit_rw_t<io_, bitpos::B15> HOAE;
			bit_rw_t<io_, bitpos::B16> SAR0E;
			bit_rw_t<io_, bitpos::B17> SAR1E;
			bit_rw_t<io_, bitpos::B18> SAR2E;
		};
		static inline icscr_t<base + 0x64> ICSCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  基準クロック制御レジスタ (ICRCCR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icrccr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  CKS;
		};
		static inline icrccr_t<base + 0x70> ICRCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  F/S モードビットレートレジスタ (ICFBR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icfbr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  LOW;
			bits_rw_t<io_, bitpos::B8, 8>  HIGH;

			bit_rw_t <io_, bitpos::B31>    DBL;
		};
		static inline icfbr_t<base + 0x74> ICFBR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  Hs モードビットレートレジスタ (ICHBR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct ichbr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 8>  LOW;
			bits_rw_t<io_, bitpos::B8, 8>  HIGH;
		};
		static inline ichbr_t<base + 0x78> ICHBR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バスフリー時間設定レジスタ (ICBFTR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x7C> ICBFTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  出力信号制御レジスタ (ICOCR)
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

			bit_rw_t <io_, bitpos::B0>     SDAO;
			bit_rw_t <io_, bitpos::B1>     SCLO;
			bit_rw_t <io_, bitpos::B2>     SOWP;

			bit_rw_t <io_, bitpos::B4>     CLO;

			bits_rw_t<io_, bitpos::B8, 3>  SDDL;

			bit_rw_t <io_, bitpos::B15>    DLCS;
		};
		static inline icocr_t<base + 0x88> ICOCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  入力信号制御レジスタ (ICICR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icicr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  NF;
			bit_rw_t <io_, bitpos::B4>     NFE;
		};
		static inline icicr_t<base + 0x8C> ICICR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイムアウト制御レジスタ (ICTOR)
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

			bits_rw_t<io_, bitpos::B0, 2>  TMOS;

			bit_rw_t <io_, bitpos::B4>     TMOL;
			bit_rw_t <io_, bitpos::B5>     TMOH;
			bits_rw_t<io_, bitpos::B6, 2>  TMOM;
		};
		static inline ictor_t<base + 0x90> ICTOR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アクノリッジビット制御レジスタ (ICACKR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icackr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     ACKBR;
			bit_rw_t <io_, bitpos::B1>     ACKBT;
			bit_rw_t <io_, bitpos::B2>     ACKWP;
		};
		static inline icackr_t<base + 0xA0> ICACKR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  クロックストレッチ制御レジスタ (ICCSCR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct iccscr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     WAITAE;
			bit_rw_t <io_, bitpos::B1>     WAITRE;
		};
		static inline iccscr_t<base + 0xA4> ICCSCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  コンディション生成要求レジスタ (ICCGR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct iccgr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     ST;
			bit_rw_t <io_, bitpos::B1>     RS;
			bit_rw_t <io_, bitpos::B2>     SP;
		};
		static inline iccgr_t<base + 0x140> ICCGR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  送受信データレジスタ (ICDR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x158> ICDR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ステータスレジスタ 2 (ICSR2)
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

			bit_rw_t <io_, bitpos::B0>     START;
			bit_rw_t <io_, bitpos::B1>     STOP;

			bit_rw_t <io_, bitpos::B4>     NACKF;

			bit_rw_t <io_, bitpos::B8>     TEND;

			bit_rw_t <io_, bitpos::B16>    AL;

			bit_rw_t <io_, bitpos::B20>    TMOF;
		};
		static inline icsr2_t<base + 0x1D0> ICSR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ステータス検出許可レジスタ (ICSER)
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

			bit_rw_t <io_, bitpos::B0>     STDE;
			bit_rw_t <io_, bitpos::B1>     SPDE;

			bit_rw_t <io_, bitpos::B4>     NAKDE;

			bit_rw_t <io_, bitpos::B8>     TEDE;

			bit_rw_t <io_, bitpos::B16>    ALE;

			bit_rw_t <io_, bitpos::B20>    TMOE;
		};
		static inline icser_t<base + 0x1D4> ICSER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ステータス割り込み許可レジスタ (ICSIER)
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

			bit_rw_t <io_, bitpos::B0>     STIE;
			bit_rw_t <io_, bitpos::B1>     SPIE;

			bit_rw_t <io_, bitpos::B4>     NAKIE;

			bit_rw_t <io_, bitpos::B8>     TEIE;

			bit_rw_t <io_, bitpos::B16>    ALIE;

			bit_rw_t <io_, bitpos::B20>    TMOIE;
		};
		static inline icsier_t<base + 0x1D8> ICSIER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  通信ステータスレジスタ (ICCSR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct iccsr_t : public ro32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B0>     TDRE;
			bit_ro_t <in_, bitpos::B1>     RDRF;
		};
		static inline iccsr_t<base + 0x1E0> ICCSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  通信ステータス検出許可レジスタ (ICCSER)
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

			bit_rw_t <io_, bitpos::B0>     TDE;
			bit_rw_t <io_, bitpos::B1>     RDE;
		};
		static inline iccser_t<base + 0x1E4> ICCSER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  通信ステータス割り込み許可レジスタ (ICCSIER)
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

			bit_rw_t <io_, bitpos::B0>     TIE;
			bit_rw_t <io_, bitpos::B1>     RIE;
		};
		static inline iccsier_t<base + 0x1E8> ICCSIER;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バスステータスレジスタ (ICBSR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icbsr_t : public ro32_t<ofs> {
			typedef ro32_t<ofs> in_;
			using in_::operator ();

			bit_ro_t <in_, bitpos::B0>     BFREE;
		};
		static inline icbsr_t<base + 0x210> ICBSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  スレーブモードステータスレジスタ (ICSSR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icssr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     GCA;

			bit_rw_t <io_, bitpos::B5>     HSMC;
			bit_rw_t <io_, bitpos::B6>     DID;

			bit_rw_t <io_, bitpos::B15>    HOA;
			bit_rw_t <io_, bitpos::B16>    AAS0;
			bit_rw_t <io_, bitpos::B17>    AAS1;
			bit_rw_t <io_, bitpos::B18>    AAS2;
		};
		static inline icssr_t<base + 0x214> ICSSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  スレーブアドレスレジスタ y (SARy) (y = 0 ～ 2)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct sarn_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 10> SVA;
			bit_rw_t <io_, bitpos::B10>    FS;
		};
		static inline sarn_t<base + 0x2B0> SAR0;
		static inline sarn_t<base + 0x2B4> SAR1;
		static inline sarn_t<base + 0x2B8> SAR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  スレーブアドレスモニタレジスタ y (SAMRy) (y = 0 ～ 2)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct samrn_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B16, 10> SVA;

			bit_rw_t <io_, bitpos::B27>     FS;

			bit_rw_t <io_, bitpos::B30>     SAV;
		};
		static inline samrn_t<base + 0x330> SAMR0;
		static inline samrn_t<base + 0x334> SAMR1;
		static inline samrn_t<base + 0x338> SAMR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ビットカウントレジスタ (ICBCR)
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

			bits_rw_t<io_, bitpos::B0, 5> BC;
		};
		static inline icbcr_t<base + 0x380> ICBCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  内部ステータスモニタレジスタ (ICIMR)
			@param[in]	ofs		レジスタ・アドレス・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct icimr_t : public rw32_t<ofs> {
			typedef rw32_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>  SCLI;
			bit_rw_t <io_, bitpos::B1>  SDAI;
			bit_rw_t <io_, bitpos::B2>  SCLO;
			bit_rw_t <io_, bitpos::B3>  SDAO;
		};
		static inline icimr_t<base + 0x3CC> ICIMR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RIICHS ハイスピード・バスインタフェース 定義
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	rxi		受信データフル・割り込みベクター
		@param[in]	txi		送信データエンプティ・割り込みベクター
		@param[in]	INT		割り込みベクター型
		@param[in]	tei		送信終了割り込み・ベクター
		@param[in]	eei		通信エラー、通信イベント割り込み・ベクター
		@param[in]	pclk	クロック元
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per,
		ICU::VECTOR rxi, ICU::VECTOR txi, typename INT, INT tei, INT eei, uint32_t pclk>
	struct riichs_t : riichs_core_t<base> {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto RXI  = rxi;		///< 受信データフル・ベクター 
		static constexpr auto TXI  = txi;		///< 送信データエンプティ・ベクター
		static constexpr auto TEI  = tei;		///< 送信終了割り込み・ベクター
		static constexpr auto EEI  = eei;		///< 通信エラー、通信イベント割り込み・ベクター
		static constexpr auto PCLK = pclk;		///< クロック周波数
	};

#if defined(SIG_RX671)
	typedef riichs_t<0x000E'C000, peripheral::RIICHS0, ICU::VECTOR::ICHSRXI, ICU::VECTOR::ICHSTXI,
		ICU::GROUPAL1, ICU::GROUPAL1::TEI, ICU::GROUPAL1::EEI, clock_profile::PCLKA> RIICHS0;
#endif
}
