#pragma once
//=====================================================================//
/*!	@file
	@brief	RX64M グループ・バス定義 @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/io_utils.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  バス定義基底クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct bus_t {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CSn 制御レジスタ（CSnCR）（n = 0 ～ 7）
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
			bits_rw_t<io_, bitpos::B4, 2>  BSIZE;
			bit_rw_t <io_, bitpos::B8>     EMODE;
			bit_rw_t <io_, bitpos::B12>    MPXEN;
		};
		static csncr_t<0x00083802> CS0CR;
		static csncr_t<0x00083812> CS1CR;
		static csncr_t<0x00083822> CS2CR;
		static csncr_t<0x00083832> CS3CR;
		static csncr_t<0x00083842> CS4CR;
		static csncr_t<0x00083852> CS5CR;
		static csncr_t<0x00083862> CS6CR;
		static csncr_t<0x00083872> CS7CR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  CSn リカバリサイクル設定レジスタ（CSnREC）（n = 0 ～ 7）
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
		static csncr_t<0x0008380A> CS0REC;
		static csncr_t<0x0008381A> CS1REC;
		static csncr_t<0x0008382A> CS2REC;
		static csncr_t<0x0008383A> CS3REC;
		static csncr_t<0x0008384A> CS4REC;
		static csncr_t<0x0008385A> CS5REC;
		static csncr_t<0x0008386A> CS6REC;
		static csncr_t<0x0008387A> CS7REC;







	};
	
	typedef bus_t BUS;

}
