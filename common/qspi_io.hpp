#pragma once
//=====================================================================//
/*!	@file
	@brief	RX グループ・QSPI I/O 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/vect.h"

/// F_PCKx は速度パラメーター計算で必要で、設定が無いとエラーにします。
#if defined(SIG_RX24T)
#  error "qspi_io.hpp not support for RX24T"
#elif defined(SIG_RX64M) || defined(SIG_RX71M) || defined(SIG_RX65N)
#ifndef F_PCLKB
#  error "qspi_io.hpp requires F_PCLKB to be defined"
#else
#undef PCLK
#define PCLK F_PCLKB
#endif
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  QSPI 制御クラス
		@param[in]	QSPI	QSPI 定義クラス
		@param[in]	PSEL	ポート候補
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class QSPI, port_map::option PSEL = port_map::option::FIRST>
	class qspi_io {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  データ、クロック位相タイプ型
					TYPE1(MODE0): CPOL:0 CPHA:0 @n
					TYPE2(MODE1): CPOL:0 CPHA:1 @n
					TYPE3(MODE2): CPOL:1 CPHA:0 @n
					TYPE4(MODE3): CPOL:1 CPHA:1
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class PHASE : uint8_t {
			TYPE1,  ///< タイプ１
			TYPE2,  ///< タイプ２
			TYPE3,  ///< タイプ３
			TYPE4,  ///< タイプ４ (SD カードアクセス）
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  データ長型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class DLEN : uint8_t {
			W8  = 0b0111,	///< 8 Bits
			W9  = 0b1000,	///< 9 Bits
			W10 = 0b1001,	///< 10 Bits
			W11 = 0b1010,	///< 11 Bits
			W12 = 0b1011,	///< 12 Bits
			W13 = 0b1100,	///< 13 Bits
			W14 = 0b1101,	///< 14 Bits
			W15 = 0b1110,	///< 15 Bits
			W16 = 0b1111,	///< 16 Bits
			W20 = 0b0000,	///< 20 Bits
			W24 = 0b0001,	///< 24 Bits
			W32 = 0b0011,	///< 32 Bits
		};

	private:

		uint8_t	level_;


		// 便宜上のスリープ
		void sleep_() { asm("nop"); }


		bool clock_div_(uint32_t speed, uint8_t& brdv, uint8_t& spbr) {
///			utils::format("PCLK: %d\n") % static_cast<uint32_t>(PCLK);
			uint32_t br = static_cast<uint32_t>(PCLK) / speed;
			uint8_t dv = 0;
			while(br > 512) {
				br >>= 1;
				++dv;
				if(dv > 3) {
					brdv = 3;
					spbr = 255;
					return false;
				}
			}
			brdv = dv;
			if(br & 1) {
				br >>= 1;
				++br;
			} else {
				br >>= 1;
			}
			if(br) --br;
			spbr = br;
			return true;
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		qspi_io() noexcept : level_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  通信速度を設定して、CSI を有効にする
			@param[in]	speed	通信速度
			@param[in]	ctype	クロック位相タイプ
			@param[in]	dlen	データ長設定
			@param[in]	level	割り込みレベル（１～２）、０の場合はポーリング
			@return エラー（速度設定範囲外）なら「false」
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t speed, PHASE ctype, DLEN dlen, uint8_t level = 0) noexcept
		{
			level_ = level;

			// デバイスを不許可
			QSPI::SPCR = 0x00;

			// ポートを有効にする
			port_map::turn(QSPI::get_peripheral(), true, PSEL);

			bool f = true;
			uint8_t brdv;
			uint8_t spbr;
			if(!clock_div_(speed, brdv, spbr)) {
				f = false;
			}

			power_cfg::turn(QSPI::get_peripheral());

			// 設定
		    QSPI::SPBR = spbr;
			QSPI::SPPCR = 0x00;	// Fixed idle value, disable loop-back
			QSPI::SPSCR = 0x00;	// disable sequence control
			QSPI::SPDCR = 0x20;	// SPLW=1 (long word access) 
///			QSPI::SPCMD0 = RSPI::SPCMD0.LSBF.b() | RSPI::SPCMD0.BRDV.b(brdv) | RSPI::SPCMD0.SPB.b(0b0100);
			bool cpol = 0;
			bool cpha = 0;
			switch(ctype) {
			case PHASE::TYPE1:
				break;
			case PHASE::TYPE2:
				cpha = 1;
				break;
			case PHASE::TYPE3:
				cpol = 1;
				break;
			case PHASE::TYPE4:
				cpol = 1;
				cpha = 1;
				break;
			default:
				break;
			}
			QSPI::SPCMD0 = QSPI::SPCMD0.BRDV.b(brdv)
				| QSPI::SPCMD0.SPB.b(static_cast<uint8_t>(dlen))
				| QSPI::SPCMD0.CPOL.b(cpol) | QSPI::SPCMD0.CPHA.b(cpha);

			QSPI::SPCR.MSTR = 1;

			QSPI::SPCR.SPE = 1;

			return f;
		}


		//----------------------------------------------------------------//
		/*!
			@brief	リード・ライト
			@param[in]	data	書き込みデータ
			@return 読み出しデータ
		*/
		//----------------------------------------------------------------//
		uint8_t xchg(uint8_t data = 0xff) noexcept
		{
			QSPI::SPDR = static_cast<uint32_t>(data);
			while(QSPI::SPSR.SPRF() == 0) sleep_();
		    return QSPI::SPDR();
		}


		//----------------------------------------------------------------//
		/*!
			@brief	リード・ライト
			@param[in]	data	書き込みデータ
			@return 読み出しデータ
		*/
		//----------------------------------------------------------------//
		uint32_t xchg32(uint32_t data = 0) noexcept
		{
			QSPI::SPDR = static_cast<uint32_t>(data);
			while(QSPI::SPSR.SPRF() == 0) sleep_();
		    return QSPI::SPDR();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアル送信
			@param[in]	src	送信ソース
			@param[in]	cnt	送信サイズ
		*/
		//-----------------------------------------------------------------//
		void send(const uint8_t* src, uint16_t size) noexcept
		{
			auto end = src + size;
			while(src < end) {
				xchg(*src);
				++src;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアル受信
			@param[out]	dst	受信先
			@param[in]	cnt	受信サイズ
		*/
		//-----------------------------------------------------------------//
		void recv(uint8_t* dst, uint16_t size) noexcept
		{
			auto end = dst + size;
			while(dst < end) {
				*dst = xchg();
				++dst;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  RSPIを無効にして、パワーダウンする
			@param[in]	power パワーダウンをしない場合「false」
		*/
		//-----------------------------------------------------------------//
		void destroy(bool power = true) noexcept
		{
			QSPI::SPCR = 0x00;
			port_map::turn(QSPI::get_peripheral(), false);
			if(power) power_cfg::turn(QSPI::get_peripheral(), false);
		}
	};
}
