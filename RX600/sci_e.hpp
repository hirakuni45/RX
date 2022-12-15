#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ SCIe 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX600/sci_base.hpp"

namespace device {

#if defined(SIG_RX220)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCIe クラス
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
	struct scie_t : public sci_ce_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TXI		 = txi;		///< 受信割り込みベクター
		static constexpr auto RXI		 = rxi;		///< 送信割り込みベクター
		static constexpr auto TEI		 = tei;		///< 送信終了割り込みベクター
		static constexpr auto ERI		 = eri;		///< 受信エラー割り込みベクター
		static constexpr auto PCLK		 = clock_profile::PCLKB;	///< PCLK 周波数

		//ボーレート微調整
		static constexpr bool SEMR_BRME  = false;	///< SEMR.BRME が利用可能な場合「true」
		// ボーレート倍速
		static constexpr bool SEMR_BGDM  = false;	///< SEMR.BGDM  が利用可能な場合「true」
		// ノイズフィルタ
		static constexpr bool SEMR_NFEN  = true;	///< SEMR.NFEN　が利用可能な場合「true」
		// 調歩同期基本クロックセレクト拡張
		static constexpr bool SEMR_ABCSE = false;	///< SEMR.ABCSE が利用可能な場合「true」
		// 受信データフル
		static constexpr bool SSR_RDRF   = false;	///< SSR.RDRF が利用可能な場合「true」
		// 簡易 I2C 機能の有無
		static constexpr bool I2C_SUB    = true;	///< 簡易 I2C が利用可能な場合「true」
		// 簡易 SPI 機能の有無
		static constexpr bool SPI_SUB    = true;	///< 簡易 SPI が利用可能な場合「true」
	};

	typedef scie_t<0x0008'A020, peripheral::SCI1, ICU::VECTOR::TXI1, ICU::VECTOR::RXI1,
		ICU::VECTOR::TEI1, ICU::VECTOR::ERI1> SCI1;
	typedef scie_t<0x0008'A0A0, peripheral::SCI5, ICU::VECTOR::TXI5, ICU::VECTOR::RXI5,
		ICU::VECTOR::TEI5, ICU::VECTOR::ERI5> SCI5;
	typedef scie_t<0x0008'A0C0, peripheral::SCI6, ICU::VECTOR::TXI6, ICU::VECTOR::RXI6,
		ICU::VECTOR::TEI6, ICU::VECTOR::ERI6> SCI6;
	typedef scie_t<0x0008'A120, peripheral::SCI9, ICU::VECTOR::TXI9, ICU::VECTOR::RXI9,
		ICU::VECTOR::TEI9, ICU::VECTOR::ERI9> SCI9;
#endif
}
