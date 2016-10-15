#pragma once
//=====================================================================//
/*!	@file
	@brief	RX63T グループ MPC 定義 @n
			Copyright 2013 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  マルチファンクションピンコントローラークラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct mpc_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  書き込みプロテクトレジスタ (PWPR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef rw8_t<0x0008c11f> pwpr_io;
		struct pwpr_t : public pwpr_io {
			using pwpr_io::operator =;
			using pwpr_io::operator ();
			using pwpr_io::operator |=;
			using pwpr_io::operator &=;

			bit_rw_t<pwpr_io, bitpos::B6> PFSWE;
			bit_rw_t<pwpr_io, bitpos::B7> B0WI;
		};
		static pwpr_t PWPR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  端子機能制御規定クラス X
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfsx_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bits_rw_t<io, bitpos::B0, 5>  PSEL;
			bit_rw_t< io, bitpos::B6>     ISEL;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  端子機能制御規定クラス Y
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfsy_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bit_rw_t<io, bitpos::B7>     ASEL;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  端子機能制御規定クラス Z
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfsz_t : public rw8_t<base> {
			typedef rw8_t<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bits_rw_t<io, bitpos::B0, 5>  PSEL;
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P0n 端子機能制御レジスタ (P0nPFS) (n=0..3)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsx_t<0x0008c140> P00PFS;
		static pfsx_t<0x0008c141> P01PFS;
		static pfsx_t<0x0008c142> P02PFS;
		static pfsx_t<0x0008c143> P03PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P1n 端子機能制御レジスタ (P1nPFS) (n=0..4)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsx_t<0x0008c148> P10PFS;
		static pfsx_t<0x0008c149> P11PFS;
		static pfsx_t<0x0008c14a> P12PFS;
		static pfsx_t<0x0008c14b> P13PFS;
		static pfsx_t<0x0008c14c> P14PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P2n 端子機能制御レジスタ (P2nPFS) (n=0..6)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsx_t<0x0008c150> P20PFS;
		static pfsx_t<0x0008c151> P21PFS;
		static pfsx_t<0x0008c152> P22PFS;
		static pfsx_t<0x0008c153> P23PFS;
		static pfsx_t<0x0008c154> P24PFS;
		static pfsx_t<0x0008c155> P25PFS;
		static pfsx_t<0x0008c156> P26PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P3n 端子機能制御レジスタ (P3nPFS) (n=0..5)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsx_t<0x0008c158> P30PFS;
		static pfsx_t<0x0008c159> P31PFS;
		static pfsx_t<0x0008c15a> P32PFS;
		static pfsx_t<0x0008c15b> P33PFS;
		static pfsx_t<0x0008c15c> P34PFS;
		static pfsx_t<0x0008c15d> P35PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P4n 端子機能制御レジスタ (P4nPFS) (n=0..7)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsy_t<0x0008c160> P40PFS;
		static pfsy_t<0x0008c161> P41PFS;
		static pfsy_t<0x0008c162> P42PFS;
		static pfsy_t<0x0008c163> P43PFS;
		static pfsy_t<0x0008c164> P44PFS;
		static pfsy_t<0x0008c165> P45PFS;
		static pfsy_t<0x0008c166> P46PFS;
		static pfsy_t<0x0008c167> P47PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P5n 端子機能制御レジスタ (P5nPFS) (n=0..7)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsy_t<0x0008c168> P50PFS;
		static pfsy_t<0x0008c169> P51PFS;
		static pfsy_t<0x0008c16a> P52PFS;
		static pfsy_t<0x0008c16b> P53PFS;
		static pfsy_t<0x0008c16c> P54PFS;
		static pfsy_t<0x0008c16d> P55PFS;
		static pfsy_t<0x0008c16e> P56PFS;
		static pfsy_t<0x0008c16f> P57PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P6n 端子機能制御レジスタ (P6nPFS) (n=0..5)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsy_t<0x0008c170> P60PFS;
		static pfsy_t<0x0008c171> P61PFS;
		static pfsy_t<0x0008c172> P62PFS;
		static pfsy_t<0x0008c173> P63PFS;
		static pfsy_t<0x0008c174> P64PFS;
		static pfsy_t<0x0008c175> P65PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P7n 端子機能制御レジスタ (P7nPFS) (n=0..6)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsx_t<0x0008c178> P70PFS;
		static pfsx_t<0x0008c179> P71PFS;
		static pfsx_t<0x0008c17a> P72PFS;
		static pfsx_t<0x0008c17b> P73PFS;
		static pfsx_t<0x0008c17c> P74PFS;
		static pfsx_t<0x0008c17d> P75PFS;
		static pfsx_t<0x0008c17e> P76PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P8n 端子機能制御レジスタ (P8nPFS) (n=0..2)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsx_t<0x0008c180> P80PFS;
		static pfsx_t<0x0008c181> P81PFS;
		static pfsx_t<0x0008c182> P82PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  P9n 端子機能制御レジスタ (P9nPFS) (n=0..6)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsx_t<0x0008c188> P90PFS;
		static pfsx_t<0x0008c189> P91PFS;
		static pfsx_t<0x0008c18a> P92PFS;
		static pfsx_t<0x0008c18b> P93PFS;
		static pfsx_t<0x0008c18c> P94PFS;
		static pfsx_t<0x0008c18d> P95PFS;
		static pfsx_t<0x0008c18e> P96PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PAn 端子機能制御レジスタ (PAnPFS) (n=0..6)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsz_t<0x0008c190> PA0PFS;
		static pfsz_t<0x0008c191> PA1PFS;
		static pfsz_t<0x0008c192> PA2PFS;
		static pfsz_t<0x0008c193> PA3PFS;
		static pfsz_t<0x0008c194> PA4PFS;
		static pfsz_t<0x0008c195> PA5PFS;
		static pfsz_t<0x0008c196> PA6PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PBn 端子機能制御レジスタ (PBnPFS) (n=0..7)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsx_t<0x0008c198> PB0PFS;
		static pfsx_t<0x0008c199> PB1PFS;
		static pfsx_t<0x0008c19a> PB2PFS;
		static pfsx_t<0x0008c19b> PB3PFS;
		static pfsx_t<0x0008c19c> PB4PFS;
		static pfsx_t<0x0008c19d> PB5PFS;
		static pfsx_t<0x0008c19e> PB6PFS;
		static pfsx_t<0x0008c19f> PB7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PCn 端子機能制御レジスタ (PCnPFS) (n=0..5)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsy_t<0x0008c1a0> PC0PFS;
		static pfsy_t<0x0008c1a1> PC1PFS;
		static pfsy_t<0x0008c1a2> PC2PFS;
		static pfsy_t<0x0008c1a3> PC3PFS;
		static pfsy_t<0x0008c1a4> PC4PFS;
		static pfsy_t<0x0008c1a5> PC5PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PDn 端子機能制御レジスタ (PDnPFS) (n=0..7)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsx_t<0x0008c1a8> PD0PFS;
		static pfsx_t<0x0008c1a9> PD1PFS;
		static pfsx_t<0x0008c1aa> PD2PFS;
		static pfsx_t<0x0008c1ab> PD3PFS;
		static pfsx_t<0x0008c1ac> PD4PFS;
		static pfsx_t<0x0008c1ad> PD5PFS;
		static pfsx_t<0x0008c1ae> PD6PFS;
		static pfsx_t<0x0008c1af> PD7PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PEn 端子機能制御レジスタ (PEnPFS) (n=0..5)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsx_t<0x0008c1b0> PE0PFS;
		static pfsx_t<0x0008c1b1> PE1PFS;
		static pfsx_t<0x0008c1b2> PE2PFS;
		static pfsx_t<0x0008c1b3> PE3PFS;
		static pfsx_t<0x0008c1b4> PE4PFS;
		static pfsx_t<0x0008c1b5> PE5PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PFn 端子機能制御レジスタ (PFnPFS) (n=2, 3)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsx_t<0x0008c1ba> PF2PFS;
		static pfsx_t<0x0008c1bb> PF3PFS;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  PGn 端子機能制御レジスタ (PGnPFS) (n=0..6)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static pfsx_t<0x0008c1c0> PG0PFS;
		static pfsx_t<0x0008c1c1> PG1PFS;
		static pfsx_t<0x0008c1c2> PG2PFS;
		static pfsx_t<0x0008c1c3> PG3PFS;
		static pfsx_t<0x0008c1c4> PG4PFS;
		static pfsx_t<0x0008c1c5> PG5PFS;
		static pfsx_t<0x0008c1c6> PG6PFS;





	};
	typedef mpc_t MPC;
}
