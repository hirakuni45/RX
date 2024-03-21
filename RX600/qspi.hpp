#pragma once
//=========================================================================//
/*!	@file
	@brief	RX600 グループ・QSPI 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/device.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  QSPI 定義基底クラス
		@param[in]	per		ペリフェラル型
		@param[in]	spri	受信バッファフル・割り込みベクター
		@param[in]	spti	送信バッファエンプティ・割り込みベクター
		@param[in]	ssli	QSSL ネゲート・割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR spri, ICU::VECTOR spti, ICU::GROUPBL0 ssli>
	struct qspi_t {

		static constexpr auto PERIPHERAL = per;	///< ペリフェラル型
		static constexpr auto SPRI = spri;		///< 受信バッファフル・割り込みベクター
		static constexpr auto SPTI = spti;		///< 送信バッファエンプティ・割り込みベクター
		static constexpr auto SSLI = ssli;		///< QSSL ネゲート・割り込みベクター
		static constexpr uint32_t PCLK = clock_profile::PCLKB;	///< PCLK 周波数

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI 制御レジスタ（SPCR）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B1> SPSSLIE;

			bit_rw_t<io_, bitpos::B3> MSTR;

			bit_rw_t<io_, bitpos::B5> SPTIE;
			bit_rw_t<io_, bitpos::B6> SPE;
			bit_rw_t<io_, bitpos::B7> SPRIE;
		};
		static inline spcr_t<base + 0x00> SPCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI スレーブセレクト極性レジスタ（SSLP）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct sslp_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0> SSLP;
		};
		static inline sslp_t<base + 0x01> SSLP;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI 端子制御レジスタ（SPPCR）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct sppcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B0>	SPLP;
			bit_rw_t<io_, bitpos::B1>	IO2FV;
			bit_rw_t<io_, bitpos::B2>	IO3FV;

			bit_rw_t<io_, bitpos::B4>	MOIFV;
			bit_rw_t<io_, bitpos::B5>	MOIFE;
		};
		static inline sppcr_t<base + 0x02> SPPCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI ステータスレジスタ（SPSR）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spsr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t<io_, bitpos::B4> SPSSLF;
			bit_rw_t<io_, bitpos::B5> SPTEF;
			bit_rw_t<io_, bitpos::B6> TREND;
			bit_rw_t<io_, bitpos::B7> SPRFF;
		};
		static inline spsr_t<base + 0x03> SPSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI データレジスタ（SPDR）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x04> SPDR32;
		static inline rw16_t<base + 0x04> SPDR16;
		static inline rw8_t<base + 0x04> SPDR8;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI シーケンス制御レジスタ（SPSCR）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spscr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> SPSC;
		};
		static inline spscr_t<base + 0x08> SPSCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI シーケンスステータスレジスタ（SPSSR）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spssr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 2> SPSS;
		};
		static inline spssr_t<base + 0x09> SPSSR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI ビットレートレジスタ（SPBR）
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw8_t<base + 0x0A> SPBR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI データ制御レジスタ（SPDCR）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spdcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bit_rw_t <io_, bitpos::B7>  TXDMY;
		};
		static inline spdcr_t<base + 0x0B> SPDCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI クロック遅延レジスタ（SPCKD）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spckd_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> SCKDL;
		};
		static inline spckd_t<base + 0x0C> SPCKD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI スレーブセレクトネゲート遅延レジスタ（SSLND）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct sslnd_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> SLNDL;
		};
		static inline sslnd_t<base + 0x0D> SSLND;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI 次アクセス遅延レジスタ（SPND）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spnd_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> SPNDL;
		};
		static inline spnd_t<base + 0x0E> SPND;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI コマンドレジスタ n（SPCMD[n]）（n = 0 ～ 3）
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spcmd_t : public rw16_index_t<ofs> {
			typedef rw16_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j < 4) { io_::index = j * 2; } }

			bit_rw_t <io_, bitpos::B0>    CPHA;
			bit_rw_t <io_, bitpos::B1>    CPOL;
			bits_rw_t<io_, bitpos::B2, 2> BRDV;
			bit_rw_t <io_, bitpos::B4>    SPRW;
			bits_rw_t<io_, bitpos::B5, 2> SPIMOD;
			bit_rw_t <io_, bitpos::B7>    SSLKP;
			bits_rw_t<io_, bitpos::B8, 4> SPB;
			bit_rw_t <io_, bitpos::B12>   LSBF;
			bit_rw_t <io_, bitpos::B13>   SPNDEN;
			bit_rw_t <io_, bitpos::B14>   SLNDEN;
			bit_rw_t <io_, bitpos::B15>   SCKDEN;

			spcmd_t& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline spcmd_t<base + 0x10> SPCMD;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI バッファ制御レジスタ (SPBFCR)
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spbfcr_t : public rw8_t<ofs> {
			typedef rw8_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 3> RXTRG;
			bit_rw_t <io_, bitpos::B3>    TXTRGEX;
			bits_rw_t<io_, bitpos::B4, 2> TXTRG;
			bit_rw_t <io_, bitpos::B6>    RXRST;
			bit_rw_t <io_, bitpos::B7>    TXRST;
		};
		static inline spbfcr_t<base + 0x18> SPBFCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI バッファデータカウントセットレジスタ (SPBDCR)
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spbdcr_t : public rw16_t<ofs> {
			typedef rw16_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			bits_rw_t<io_, bitpos::B0, 6> RXBC;

			bits_rw_t<io_, bitpos::B8, 6> TXBC;
		};
		static inline spbdcr_t<base + 0x1A> SPBDCR;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI 転送データ長倍数設定レジスタ n (SPBMULn) (n = 0 ～ 3)
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		static inline rw32_t<base + 0x1C> SPBMUL0;
		static inline rw32_t<base + 0x20> SPBMUL1;
		static inline rw32_t<base + 0x24> SPBMUL2;
		static inline rw32_t<base + 0x28> SPBMUL3;


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  QSPI 転送データ長倍数設定レジスタ n (SPBMUL[n]) (0 ～ 3)
			@param[in]	ofs	レジスター・オフセット
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		template <uint32_t ofs>
		struct spbmul_t : public rw32_index_t<ofs> {
			typedef rw32_index_t<ofs> io_;
			using io_::operator =;
			using io_::operator ();
			using io_::operator |=;
			using io_::operator &=;

			void set_index(uint32_t j) { if(j < 4) { io_::index = j * 4; } }

			spbmul_t& operator [] (uint32_t idx) {
				set_index(idx);
				return *this;
			}
		};
		static inline spbmul_t<0x1C> SPBMUL;
	};
	typedef qspi_t<0x0008'9E00, peripheral::QSPI, ICU::VECTOR::SPRI, ICU::VECTOR::SPTI,
		ICU::GROUPBL0::QSPSSLI>  QSPI;
}
