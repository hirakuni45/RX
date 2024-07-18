#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ SCIm 定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "RX600/sci_base.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  SCIm クラス
		@param[in]	base	ベース・アドレス
		@param[in]	per		ペリフェラル型
		@param[in]	txi		送信割り込みベクター
		@param[in]	rxi		受信割り込みベクター
		@param[in]	ICUT	送信終了、受信エラー、割り込み型
		@param[in]	tei		送信終了割り込みベクター
		@param[in]	eri		受信エラー割り込みベクター
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <uint32_t base, peripheral per, ICU::VECTOR txi, ICU::VECTOR rxi,
		typename ICUT, ICUT tei, ICUT eri>
	struct scim_t : public sci_gj_t<base>, sci_fifo_t<base> {

		static constexpr auto PERIPHERAL = per;		///< ペリフェラル型
		static constexpr auto TXI		 = txi;		///< 受信割り込みベクター
		static constexpr auto RXI		 = rxi;		///< 送信割り込みベクター
		static constexpr auto TEI		 = tei;		///< 送信終了割り込みベクター
		static constexpr auto ERI		 = eri;		///< 受信エラー割り込みベクター
		static constexpr auto PCLK		 = clock_profile::PCLKA;	///< PCLK 周波数

		//ボーレート微調整
		static constexpr bool SEMR_BRME = true;		///< SEMR.BRME が利用可能な場合「true」
		// ボーレート倍速
		static constexpr bool SEMR_BGDM = true;		///< SEMR.BGDM  が利用可能な場合「true」
		// ノイズフィルタ
		static constexpr bool SEMR_NFEN = true;		///< SEMR.NFEN　が利用可能な場合「true」
		// 調歩同期基本クロックセレクト拡張
		static constexpr bool SEMR_ABCSE = false;	///< SEMR.ABCSE が利用可能な場合「true」
		// 受信データフル
		static constexpr bool SSR_RDRF   = true;	///< SSR.RDRF が利用可能な場合「true」
		// 簡易 I2C 機能の有無
		static constexpr bool I2C_SUB    = true;	///< 簡易 I2C が利用可能な場合「true」
		// 簡易 SPI 機能の有無
		static constexpr bool SPI_SUB    = true;	///< 簡易 SPI が利用可能な場合「true」
		// FIFO 機能の有無
		static constexpr bool FIFO_FUNC  = true;	///< FIFO バッファ機能が有効な場合「true」
	};

#if defined(SIG_RX660) || defined(SIG_RX671)
	typedef scim_t<0x000D'0040, peripheral::SCI10, ICU::VECTOR::TXI10, ICU::VECTOR::RXI10,
		ICU::GROUPAL0, ICU::GROUPAL0::TEI10, ICU::GROUPAL0::ERI10> SCI10;
	typedef scim_t<0x000D'0060, peripheral::SCI11, ICU::VECTOR::TXI11, ICU::VECTOR::RXI11,
		ICU::GROUPAL0, ICU::GROUPAL0::TEI11, ICU::GROUPAL0::ERI11> SCI11;
#endif
}
