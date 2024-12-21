#pragma once
//=========================================================================//
/*!	@file
	@brief	Serial Communications Interface a / シリアルコミュニケーションインタフェース a
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX600/sci_base.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCIa class
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txi		送信割り込みベクター
		@param[in]	rxi		受信割り込みベクター
		@param[in]	tei		送信終了割り込みベクター
		@param[in]	eri		受信エラー割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txi, ICU::VECTOR rxi,
		ICU::VECTOR tei, ICU::VECTOR eri>
	struct scia_t : public sci_a_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TXI		 = txi;		///< 受信割り込みベクター
		static constexpr auto RXI		 = rxi;		///< 送信割り込みベクター
		static constexpr auto TEI		 = tei;		///< 送信終了割り込みベクター
		static constexpr auto ERI		 = eri;		///< 受信エラー割り込みベクター
		static constexpr auto PCLK		 = clock_profile::PCLK;	///< PCLK 周波数

		//ボーレート微調整
		static constexpr bool SEMR_BRME  = false;	///< SEMR.BRME が利用可能な場合「true」
		// ボーレート倍速
		static constexpr bool SEMR_BGDM  = false;	///< SEMR.BGDM  が利用可能な場合「true」
		// ノイズフィルタ
		static constexpr bool SEMR_NFEN  = false;	///< SEMR.NFEN　が利用可能な場合「true」
		// 調歩同期基本クロックセレクト拡張
		static constexpr bool SEMR_ABCSE = false;	///< SEMR.ABCSE が利用可能な場合「true」
		// 受信データフル
		static constexpr bool SSR_RDRF   = true;	///< SSR.RDRF が利用可能な場合「true」
		// 簡易 I2C 機能の有無
		static constexpr bool I2C_SUB    = false;	///< 簡易 I2C が利用可能な場合「true」
		// 簡易 SPI 機能の有無
		static constexpr bool SPI_SUB    = false;	///< 簡易 SPI が利用可能な場合「true」
		// FIFO 機能の有無
		static constexpr bool FIFO_FUNC  = false;	///< FIFO バッファ機能が有効な場合「true」
	};

#if defined(SIG_RX621) || defined(SIG_RX62N)
	typedef scia_t<0x0008'8240, peripheral::SCI0, ICU::VECTOR::TXI0, ICU::VECTOR::RXI0,
		ICU::VECTOR::TEI0, ICU::VECTOR::ERI0> SCI0;
	typedef scia_t<0x0008'8248, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1,
		ICU::VECTOR::TEI1, ICU::VECTOR::ERI1> SCI1;
	typedef scia_t<0x0008'8250, peripheral::SCI2, ICU::VECTOR::TXI2, ICU::VECTOR::RXI2,
		ICU::VECTOR::TEI2, ICU::VECTOR::ERI2> SCI2;
	typedef scia_t<0x0008'8258, peripheral::SCI3, ICU::VECTOR::TXI3, ICU::VECTOR::RXI3,
		ICU::VECTOR::TEI3, ICU::VECTOR::ERI3> SCI3;
	typedef scia_t<0x0008'8268, peripheral::SCI5, ICU::VECTOR::TXI5, ICU::VECTOR::RXI5,
		ICU::VECTOR::TEI5, ICU::VECTOR::ERI5> SCI5;
	typedef scia_t<0x0008'8270, peripheral::SCI6, ICU::VECTOR::TXI6, ICU::VECTOR::RXI6,
		ICU::VECTOR::TEI6, ICU::VECTOR::ERI6> SCI6;
#endif
}
