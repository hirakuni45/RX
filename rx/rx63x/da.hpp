#pragma once
//=====================================================================//
/*!	@file
	@brief	RX63x グループ D/A コンバーター定義 @n
			Copyright 2013 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  D/A コンバーター定義
		@param[in]	base	ベース・アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base>
	struct da_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  D/A データレジスタ０ (DADR0)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		io16<base + 0x00>	DADR0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  D/A データレジスタ１ (DADR1)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		io16<base + 0x02>	DADR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  D/A コントロールレジスタ (DACR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io8<base + 0x04> dacr_io;
		struct dacr_t : public dacr_io {
			using dacr_io::operator =;
			using dacr_io::operator ();
			using dacr_io::operator |=;
			using dacr_io::operator &=;

			bit_t<dacr_io, 5>	DAE;
			bit_t<dacr_io, 6>	DAOE0;
			bit_t<dacr_io, 7>	DAOE1;
		};
		static dacr_t	DACR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  DADRm フォーマット選択レジスタ (DADPR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io8<base + 0x05> dadpr_io;
		struct dadpr_t : public dadpr_io {
			using dadpr_io::operator =;
			using dadpr_io::operator ();
			using dadpr_io::operator |=;
			using dadpr_io::operator &=;

			bit<dadpr_io, 7>	DPSEL;
		};
		static dadpr_t	DADPR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  D/A A/D 同期スタート制御レジスタ (DAADSCR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		typedef io8<base + 0x06> daadscr_io;
		struct daadscr_t : public daadscr_io {
			using daadscr_io::operator =;
			using daadscr_io::operator ();
			using daadscr_io::operator |=;
			using daadscr_io::operator &=;

			bit<daadscr_io, 7>	DAADS;
		};
		static daadscr_t	DAADSCR;
	};
	typedef da_t<0x000880c0> DA;
}
