#pragma once
//=============================================================================//
/*!	@file
	@brief	RX600 グループ・バス定義 @n
			RX24T/RX24U (CSx レジスタ 0 ～ 3, SDRAM 制御無し) @n
			RX26T (CSx レジスタ 0 ～ 3, SDRAM 制御無し) @n
			RX62N/RX621 @n
			RX63N/RX631 @n
			RX64M/RX71M @n
			RX65N/RX651 @n
			RX66N @n
			RX671 @n
			RX72M/RX72N @n
			RX66T/RX72T (CSx レジスタ 0 ～ 3, SDRAM 制御無し)
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=============================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  バス定義基底クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct bus_base_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CSn 制御レジスタ（CSnCR）（n = 0 ～ 3）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct csncr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     EXENB;

			bits_rw_t<io_, bitpos::B4, 2>  BSIZE;  // CS0CR の初期値が異なる

			bit_rw_t <io_, bitpos::B8>     EMODE;

			bit_rw_t <io_, bitpos::B12>    MPXEN;
		};
		static inline csncr_t<0x0008'3802> CS0CR;
		static inline csncr_t<0x0008'3812> CS1CR;
		static inline csncr_t<0x0008'3822> CS2CR;
		static inline csncr_t<0x0008'3832> CS3CR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CSn リカバリサイクル設定レジスタ（CSnREC）（n = 0 ～ 7）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct csnrec_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4> PRCV;

			bits_rw_t<io_, bitpos::B8, 4> WRCV;
		};
		static inline csncr_t<0x0008'380A> CS0REC;
		static inline csncr_t<0x0008'381A> CS1REC;
		static inline csncr_t<0x0008'382A> CS2REC;
		static inline csncr_t<0x0008'383A> CS3REC;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CS リカバリサイクル挿入許可レジスタ（CSRECEN）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct csrecen_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  RCVEN0;
			bit_rw_t<io_, bitpos::B1>  RCVEN1;
			bit_rw_t<io_, bitpos::B2>  RCVEN2;
			bit_rw_t<io_, bitpos::B3>  RCVEN3;
			bit_rw_t<io_, bitpos::B4>  RCVEN4;
			bit_rw_t<io_, bitpos::B5>  RCVEN5;
			bit_rw_t<io_, bitpos::B6>  RCVEN6;
			bit_rw_t<io_, bitpos::B7>  RCVEN7;
			bit_rw_t<io_, bitpos::B8>  RCVENM0;
			bit_rw_t<io_, bitpos::B9>  RCVENM1;
			bit_rw_t<io_, bitpos::B10> RCVENM2;
			bit_rw_t<io_, bitpos::B11> RCVENM3;
			bit_rw_t<io_, bitpos::B12> RCVENM4;
			bit_rw_t<io_, bitpos::B13> RCVENM5;
			bit_rw_t<io_, bitpos::B14> RCVENM6;
			bit_rw_t<io_, bitpos::B15> RCVENM7;
		};
		static inline csrecen_t<0x0008'3880> CSRECEN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CSn モードレジスタ（CSnMOD）（n = 0 ～ 3）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct csnmod_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>  WRMOD;

			bit_rw_t<io_, bitpos::B3>  EWENB;

			bit_rw_t<io_, bitpos::B8>  PRENB;
			bit_rw_t<io_, bitpos::B9>  PWENB;

			bit_rw_t<io_, bitpos::B15> PRMOD;
		};
		static inline csnmod_t<0x0008'3002> CS0MOD;
		static inline csnmod_t<0x0008'3012> CS1MOD;
		static inline csnmod_t<0x0008'3022> CS2MOD;
		static inline csnmod_t<0x0008'3032> CS3MOD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CSn ウェイト制御レジスタ 1（CSnWCR1）（n = 0 ～ 3）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct csnwcr1_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  CSPWWAIT;

			bits_rw_t<io_, bitpos::B8, 3>  CSPRWAIT;

			bits_rw_t<io_, bitpos::B16, 5> CSWWAIT;

			bits_rw_t<io_, bitpos::B24, 5> CSRWWAIT;
		};
		static inline csnwcr1_t<0x0008'3004> CS0WCR1;
		static inline csnwcr1_t<0x0008'3014> CS1WCR1;
		static inline csnwcr1_t<0x0008'3024> CS2WCR1;
		static inline csnwcr1_t<0x0008'3034> CS3WCR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CSn ウェイト制御レジスタ 2（CSnWCR2）（n = 0 ～ 3）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct csnwcr2_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  3> CSROFF;

			bits_rw_t<io_, bitpos::B4,  3> CSWOFF;

			bits_rw_t<io_, bitpos::B8,  3> WDOFF;

			bits_rw_t<io_, bitpos::B12, 2> AWAIT;

			bits_rw_t<io_, bitpos::B16, 3> RDON;

			bits_rw_t<io_, bitpos::B20, 3> WRON;

			bits_rw_t<io_, bitpos::B24, 3> WDON;

			bits_rw_t<io_, bitpos::B28, 3> CSON;
		};
		static inline csnwcr2_t<0x0008'3008> CS0WCR2;
		static inline csnwcr2_t<0x0008'3018> CS1WCR2;
		static inline csnwcr2_t<0x0008'3028> CS2WCR2;
		static inline csnwcr2_t<0x0008'3038> CS3WCR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CS 空間クラス（CSn）（n = 0 ～ 3）
			@param[in]	base	レジスタ・ベース・アドレス
			@param[in]	org		CS 空間開始アドレス
			@param[in]	end		CS 空間終了アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base, uint32_t org, uint32_t end>
		struct cs_t {

			static constexpr auto ORG = org;			///< CS 空間開始アドレス
			static constexpr auto END = end;			///< CS 空間終了アドレス
			static constexpr auto LEN = end - org + 1;	///< CS 空間長さ


			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			/*!
				@brief  CS 制御レジスタ
				@param[in]	base	レジスタ・ベース・アドレス
			*/
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			static inline csncr_t<base + 0x0802>  CSCR;


			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			/*!
				@brief  CS リカバリサイクル設定レジスタ
				@param[in]	base	レジスタ・ベース・アドレス
			*/
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			static inline csnrec_t<base + 0x080A> CSREC;			


			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			/*!
				@brief  CS セパレートバスリカバリサイクル挿入許可
				@param[in]	ena		不許可なら「false」
			*/
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			static void enable_sep_CSREC(bool ena = true) {
				if(ena) CSRECEN |= 1 << ((base & 0x70) >> 4);
				else CSRECEN &= ~(1 << ((base & 0x70) >> 4));
			}


			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			/*!
				@brief  CS マルチプレックスバスリカバリサイクル挿入許可
				@param[in]	ena		不許可なら「false」
			*/
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			static void enable_mux_CSREC(bool ena = true) {
				if(ena) CSRECEN |= 0x80 << ((base & 0x70) >> 4);
				else CSRECEN &= ~(0x80 << ((base & 0x70) >> 4));
			}


			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			/*!
				@brief  CS モードレジスタ
				@param[in]	base	レジスタ・ベース・アドレス
			*/
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			static inline csnmod_t<base + 0x0002> CSMOD;


			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			/*!
				@brief  CS ウェイト制御レジスタ 1
				@param[in]	base	レジスタ・ベース・アドレス
			*/
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			static inline csnwcr1_t<base + 0x0004> CSWCR1;


			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			/*!
				@brief  CS ウェイト制御レジスタ 2
				@param[in]	base	レジスタ・ベース・アドレス
			*/
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
			static inline csnwcr1_t<base + 0x0008> CSWCR2;
		};
		static inline cs_t<0x0008'3000, 0xFF00'0000, 0xFFFF'FFFF> CS0;
		static inline cs_t<0x0008'3010, 0x0700'0000, 0x07FF'FFFF> CS1;
		static inline cs_t<0x0008'3020, 0x0600'0000, 0x06FF'FFFF> CS2;
		static inline cs_t<0x0008'3030, 0x0500'0000, 0x05FF'FFFF> CS3;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バスエラーステータスクリアレジスタ（BERCLR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct berclr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> STSCLR;
		};
		static inline berclr_t<0x0008'1300> BERCLR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バスエラー監視許可レジスタ（BEREN）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct beren_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> IGAEN;
			bit_rw_t<io_, bitpos::B1> TOEN;
		};
		static inline beren_t<0x0008'1304> BEREN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バスエラーステータスレジスタ 1（BERSR1）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct bersr1_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    IA;
			bit_rw_t <io_, bitpos::B1>    TO;

			bits_rw_t<io_, bitpos::B4, 3> MST;
		};
		static inline bersr1_t<0x0008'1308> BERSR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バスエラーステータスレジスタ 2（BERSR2）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct bersr2_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B3, 13> ADDR;
		};
		static inline bersr2_t<0x0008'130A> BERSR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  バスプライオリティ制御レジスタ（BUSPRI）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct buspri_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  2> BPRA;
			bits_rw_t<io_, bitpos::B2,  2> BPRO;
			bits_rw_t<io_, bitpos::B4,  2> BPIB;
			bits_rw_t<io_, bitpos::B6,  2> BPGB;
			bits_rw_t<io_, bitpos::B8,  2> BPHB;
			bits_rw_t<io_, bitpos::B10, 2> BPFB;
			bits_rw_t<io_, bitpos::B12, 2> BPEB;
		};
		static inline buspri_t<0x0008'1310> BUSPRI;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  バス定義 SDRAM クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct bus_sdram_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDC 制御レジスタ（SDCCR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdccr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>    EXENB;

			bits_rw_t<io_, bitpos::B4, 2> BSIZE;
		};
		static inline sdccr_t<0x0008'3C00> SDCCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDC モードレジスタ（SDCMOD）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdcmod_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0> EMODE;
		};
		static inline sdcmod_t<0x0008'3C01> SDCMOD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM アクセスモードレジスタ（SDAMOD）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdamod_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0> BE;
		};
		static inline sdamod_t<0x0008'3C02> SDAMOD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM セルフリフレッシュ制御レジスタ（SDSELF）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdself_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0> SFEN;
		};
		static inline sdself_t<0x0008'3C10> SDSELF;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM リフレッシュ制御レジスタ（SDRFCR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdrfcr_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t <io_, bitpos::B0,  12> RFC;
			bits_rw_t <io_, bitpos::B12, 4>  REFW;
		};
		static inline sdrfcr_t<0x0008'3C14> SDRFCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM オートリフレッシュ制御レジスタ（SDRFEN）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdrfen_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0> RFEN;
		};
		static inline sdrfen_t<0x0008'3C16> SDRFEN;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM 初期化シーケンス制御レジスタ（SDICR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdicr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0> INIRQ;
		};
		static inline sdicr_t<0x0008'3C20> SDICR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM 初期化レジスタ（SDIR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdir_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t <io_, bitpos::B0, 4> ARFI;
			bits_rw_t <io_, bitpos::B4, 4> ARFC;
			bits_rw_t <io_, bitpos::B8, 3> PRC;
		};
		static inline sdir_t<0x0008'3C24> SDIR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM アドレスレジスタ（SDADR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdadr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t <io_, bitpos::B0, 2> MXC;
		};
		static inline sdadr_t<0x0008'3C40> SDADR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM タイミングレジスタ（SDTR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdtr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  3> CL;

			bit_rw_t <io_, bitpos::B8>     WR;
			bits_rw_t<io_, bitpos::B9,  3> RP;
			bits_rw_t<io_, bitpos::B12, 2> RCD;

			bits_rw_t<io_, bitpos::B16, 3> RAS;
		};
		static inline sdtr_t<0x0008'3C44> SDTR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM モードレジスタ（SDMOD）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdmod_t : public rw16_t<base> {
			typedef rw16_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 15> MR;
		};
		static inline sdmod_t<0x0008'3C48> SDMOD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SDRAM ステータスレジスタ（SDSR）
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct sdsr_t : public rw8_t<base> {
			typedef rw8_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> MRSST;

			bit_rw_t<io_, bitpos::B3> INIST;
			bit_rw_t<io_, bitpos::B4> SRFST;
		};
		static inline sdsr_t<0x0008'3C50> SDSR;
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  バス定義クラス（ALL）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct bus_all_t : public bus_base_t, bus_sdram_t {

	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  バス定義クラス（ALL+Ex）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct bus_allex_t : public bus_base_t, bus_sdram_t {

		//---------------------------------------------------------------------//
		/*!
			@brief  CSn 制御レジスタ（CSnCR）（n = 4 ～ 7）
		*/
		//---------------------------------------------------------------------//
		static inline csncr_t<0x0008'3842> CS4CR;
		static inline csncr_t<0x0008'3852> CS5CR;
		static inline csncr_t<0x0008'3862> CS6CR;
		static inline csncr_t<0x0008'3872> CS7CR;


		//---------------------------------------------------------------------//
		/*!
			@brief  CSn リカバリサイクル設定レジスタ（CSnREC）（n = 4 ～ 7）
		*/
		//---------------------------------------------------------------------//
		static inline csncr_t<0x0008'384A> CS4REC;
		static inline csncr_t<0x0008'385A> CS5REC;
		static inline csncr_t<0x0008'386A> CS6REC;
		static inline csncr_t<0x0008'387A> CS7REC;


		//---------------------------------------------------------------------//
		/*!
			@brief  CSn モードレジスタ（CSnMOD）（n = 4 ～ 7）
		*/
		//---------------------------------------------------------------------//
		static inline csnmod_t<0x0008'3042> CS4MOD;
		static inline csnmod_t<0x0008'3052> CS5MOD;
		static inline csnmod_t<0x0008'3062> CS6MOD;
		static inline csnmod_t<0x0008'3072> CS7MOD;


		//---------------------------------------------------------------------//
		/*!
			@brief  CSn ウェイト制御レジスタ 1（CSnWCR1）（n = 4 ～ 7）
		*/
		//---------------------------------------------------------------------//
		static inline csnwcr1_t<0x0008'3044> CS4WCR1;
		static inline csnwcr1_t<0x0008'3054> CS5WCR1;
		static inline csnwcr1_t<0x0008'3064> CS6WCR1;
		static inline csnwcr1_t<0x0008'3074> CS7WCR1;


		//---------------------------------------------------------------------//
		/*!
			@brief  CSn ウェイト制御レジスタ 2（CSnWCR2）（n = 4 ～ 7）
		*/
		//---------------------------------------------------------------------//
		static inline csnwcr2_t<0x0008'3048> CS4WCR2;
		static inline csnwcr2_t<0x0008'3058> CS5WCR2;
		static inline csnwcr2_t<0x0008'3068> CS6WCR2;
		static inline csnwcr2_t<0x0008'3078> CS7WCR2;


		//---------------------------------------------------------------------//
		/*!
			@brief  CS 空間クラス（CSn）（n = 4 ～ 7）
		*/
		//---------------------------------------------------------------------//
		static inline cs_t<0x0008'3040, 0x0400'0000, 0x04FF'FFFF> CS4;
		static inline cs_t<0x0008'3050, 0x0300'0000, 0x03FF'FFFF> CS5;
		static inline cs_t<0x0008'3060, 0x0200'0000, 0x02FF'FFFF> CS6;
		static inline cs_t<0x0008'3070, 0x0100'0000, 0x01FF'FFFF> CS7;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  拡張バスマスタ優先度制御レジスタ (EBMAPCR) @n
					※ GLCDC 関係に関連したレジスタ
			@param[in]	base	ベース・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template<uint32_t base>
		struct ebmapcr_t : public rw32_t<base> {
			typedef rw32_t<base> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0,  3>  PR1SEL;

			bits_rw_t<io_, bitpos::B4,  3>  PR2SEL;

			bits_rw_t<io_, bitpos::B8,  3>  PR3SEL;

			bits_rw_t<io_, bitpos::B12, 3>  PR4SEL;

			bits_rw_t<io_, bitpos::B16, 3>  PR5SEL;
#if defined(SIG_RX65N)
			bit_rw_t <io_, bitpos::B29>     RPSTOP;
#endif
			bit_rw_t <io_, bitpos::B31>     PRERR;
		};
		static inline ebmapcr_t<0x000C'5800> EBMAPCR;
	};

#if defined(SIG_RX62N) || defined(SIG_RX621) || defined(SIG_RX63N) || defined(SIG_RX631) || defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX671)
	typedef bus_all_t BUS;
#elif defined(SIG_RX65N) || defined(SIG_RX651) || defined(SIG_RX66N) || defined(SIG_RX72N) || defined(SIG_RX72M)
	typedef bus_allex_t BUS;
#elif defined(SIG_RX24T) || defined(SIG_RX24U) || defined(SIG_RX26T) || defined(SIG_RX66T) || defined(SIG_RX72T)
	typedef bus_base_t BUS;
#endif
}
