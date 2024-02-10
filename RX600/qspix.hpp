#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600 グループ・QSPIX 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  QSPIX 定義基底クラス
		@param[in]	eri		エラー割り込み
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <ICU::GROUPAL0 eri>
	struct qspix_t {

		static constexpr auto PERIPHERAL = peripheral::QSPIX;	///< ペリフェラル型
		static constexpr auto ERI = eri;	///< エラー割り込み
		static constexpr uint32_t PCLK = clock_profile::ICLK;	///< 内部クロック周波数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モードレジスタ 0 (SPMR0)
			@param[in]	adr	レジスター・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t adr>
		struct spmr0_t : public rw32_t<adr> {
			typedef rw32_t<adr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3>  RISEL;

			bits_rw_t<io_, bitpos::B4, 2>  SSE;

			bit_rw_t <io_, bitpos::B6>     PFE;

			bit_rw_t <io_, bitpos::B8>     CKMD;
			bit_rw_t <io_, bitpos::B9>     DODE;
	
			bit_rw_t <io_, bitpos::B15>    SRIS;
		};
		static inline spmr0_t<0x7400'0000> SPMR0;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  スレーブセレクト信号制御レジスタ (SPSSCR)
			@param[in]	adr	レジスター・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t adr>
		struct spsscr_t : public rw32_t<adr> {
			typedef rw32_t<adr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  SSHW;
			bit_rw_t <io_, bitpos::B4>     SSHLD;
			bit_rw_t <io_, bitpos::B5>     SSSU;
		};
		static inline spsscr_t<0x7400'0004> SPSSCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  動作クロック制御レジスタ (SPOCR)
			@param[in]	adr	レジスター・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t adr>
		struct spocr_t : public rw32_t<adr> {
			typedef rw32_t<adr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  DIV;
			bit_rw_t <io_, bitpos::B5>     DUTY;
		};
		static inline spocr_t<0x7400'0008> SPOCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  プリフェッチステータスレジスタ (SPPFSR)
			@param[in]	adr	レジスター・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t adr>
		struct sppfsr_t : public rw32_t<adr> {
			typedef rw32_t<adr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 5>  PBLVL;

			bit_rw_t <io_, bitpos::B6>     PBFUL;
			bit_rw_t <io_, bitpos::B7>     PFOSF;
		};
		static inline sppfsr_t<0x7400'000C> SPPFSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SPI データレジスタ (SPDR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<0x7400'0010> SPDR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モードレジスタ 1 (SPMR1)
			@param[in]	adr	レジスター・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t adr>
		struct spmr1_t : public rw32_t<adr> {
			typedef rw32_t<adr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B0>     AMOD;
		};
		static inline spmr1_t<0x7400'0014> SPMR1;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  SPI ステータスレジスタ (SPSR)
			@param[in]	adr	レジスター・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t adr>
		struct spsr_t : public rw32_t<adr> {
			typedef rw32_t<adr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_ro_t <io_, bitpos::B0>     BUSY;

			bit_rw_t <io_, bitpos::B7>     ROMAE;
		};
		static inline spsr_t<0x7400'0018> SPSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  独自リード命令設定レジスタ (SPRIR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<0x7400'0020> SPRIR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  アドレスモードレジスタ (SPAMR)
			@param[in]	adr	レジスター・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t adr>
		struct spamr_t : public rw32_t<adr> {
			typedef rw32_t<adr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  SIZE;

			bit_rw_t <io_, bitpos::B4>     I4AE;
		};
		static inline spamr_t<0x7400'0024> SPAMR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ダミーサイクル制御レジスタ (SPDCR)
			@param[in]	adr	レジスター・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t adr>
		struct spdcr_t : public rw32_t<adr> {
			typedef rw32_t<adr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 4>  DCYC;

			bit_rw_t <io_, bitpos::B6>     XIPS;
			bit_rw_t <io_, bitpos::B7>     XIPE;
			bits_rw_t<io_, bitpos::B8, 8>  MODE;
		};
		static inline spdcr_t<0x7400'0028> SPDCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  モードレジスタ 2 (SPMR2)
			@param[in]	adr	レジスター・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t adr>
		struct spmr2_t : public rw32_t<adr> {
			typedef rw32_t<adr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2>  IOMOD;
		};
		static inline spmr2_t<0x7400'0030> SPMR2;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  ポート制御レジスタ (SPPCR)
			@param[in]	adr	レジスター・アドレス
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t adr>
		struct sppcr_t : public rw32_t<adr> {
			typedef rw32_t<adr> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B2>     WP;
		};
		static inline sppcr_t<0x7400'0034> SPPCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  上位アドレスレジスタ (SPUAR)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<0x7400'0804> SPUAR;
	};
	typedef qspix_t<ICU::GROUPAL0::QERI> QSPIX;
}
