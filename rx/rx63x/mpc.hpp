#pragma once
//=====================================================================//
/*!	@file
	@brief	RX63T グループ MPC 定義 @n
			Copyright 2013 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "../io_utils.hpp"

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
		typedef io8<0x0008c11f> pwpr_io;
		struct pwpr_t : public pwpr_io {
			using pwpr_io::operator =;
			using pwpr_io::operator ();
			using pwpr_io::operator |=;
			using pwpr_io::operator &=;

			bit_t<pwpr_io, 6> PFSWE;
			bit_t<pwpr_io, 7> B0WI;
		};
		static pwpr_t PWPR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  端子機能制御規定クラス X
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t base>
		struct pfsx_t : public io8<base> {
			typedef io8<base> io;
			using io::operator =;
			using io::operator ();
			using io::operator |=;
			using io::operator &=;

			bits_t<io, 0, 5>  PSEL;
			bit_t< io, 6>     ISEL;
		};


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


	};
	typedef mpc_t MPC;
}
