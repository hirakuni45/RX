#pragma once
//=====================================================================//
/*!	@file
	@brief	RX グループ・RSPI I/O 制御 @n
			Copyright 2016 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "common/renesas.hpp"
#include "common/vect.h"

/// F_PCKB は速度パラメーター計算で必要で、設定が無いとエラーにします。
#ifndef F_PCKB
#  error "sci_io.hpp requires F_PCKB to be defined"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RSPI 制御クラス
		@param[in]	RSPI	RSPI 定義クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class RSPI>
	class rspi_io {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  データ、クロック位相タイプ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class PHASE : uint8_t {
			TYPE1,  ///< タイプ１
			TYPE2,  ///< タイプ２
			TYPE3,  ///< タイプ３
			TYPE4,  ///< タイプ４ (SD カードアクセス）
		};

	private:
		uint8_t	level_;

		// 便宜上のスリープ
		void sleep_() { asm("nop"); }


		bool clock_div_(uint32_t speed, uint8_t& brdv, uint8_t& spbr) {
			uint32_t br = F_PCKB / 2 / speed;
			brdv = 0;
			while(br > 256) {
				br >>= 1;
				++brdv;
				if(brdv > 3) {
					brdv = 3;
					spbr = 255;
					return false;
				}
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
		rspi_io() : level_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  設定可能な最大速度を返す（通常、F_PCKB の半分）
		*/
		//-----------------------------------------------------------------//
		uint32_t get_max_speed() const { return F_PCKB / 2; }


		//-----------------------------------------------------------------//
		/*!
			@brief  通信速度を設定して、CSI を有効にする
			@param[in]	speed	通信速度
			@param[in]	dctype	データ、クロック位相タイプ
			@param[in]	level	割り込みレベル（１～２）、０の場合はポーリング
			@return エラー（速度設定範囲外）なら「false」
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t speed, PHASE dctype, uint8_t level = 0)
		{
			level_ = level;

			// ポートを有効にする
			port_map::turn(RSPI::get_peripheral());

			bool f = true;
			uint8_t brdv;
			uint8_t spbr;
			if(!clock_div_(speed, brdv, spbr)) {
				f = false;
			}

			power_cfg::turn(RSPI::get_peripheral());

			// デバイスを不許可
			RSPI::SPCR = 0x00;

			// 設定
		    RSPI::SPBR = spbr;

			RSPI::SPPCR = 0x00;	// Fixed idle value, disable loop-back
			RSPI::SPSCR = 0x00;	// disable sequence control
			RSPI::SPDCR = 0x20;	// SPLW=1 (long word access) 
///			RSPI::SPCMD0 = RSPI::SPCMD0.LSBF.b() | RSPI::SPCMD0.BRDV.b(brdv) | RSPI::SPCMD0.SPB.b(0b0100);
			RSPI::SPCMD0 = RSPI::SPCMD0.BRDV.b(brdv) | RSPI::SPCMD0.SPB.b(0b0111);

			RSPI::SPCR.SPMS = 1;
			RSPI::SPCR.MSTR = 1;

			RSPI::SPCR.SPE = 1;

			return f;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ＳＤカード用設定を有効にする
			@param[in]	speed	通信速度
			@return エラー（速度設定範囲外）なら「false」
		*/
		//-----------------------------------------------------------------//
		bool start_sdc(uint32_t speed)
		{
			level_ = 0;

			RSPI::SPCR = 0x00;			

			port_map::turn(RSPI::get_peripheral());

			bool f = true;
			uint8_t brdv;
			uint8_t spbr;
			if(!clock_div_(speed, brdv, spbr)) {
				f = false;
			}

			power_cfg::turn(RSPI::get_peripheral());

		    RSPI::SPBR = spbr;

			RSPI::SPPCR = 0x00;	// Fixed idle value, disable loop-back
			RSPI::SPSCR = 0x00;	// disable sequence control
			RSPI::SPDCR = 0x20;	// SPLW=1 (long word access) 
			RSPI::SPCMD0 = RSPI::SPCMD0.BRDV.b(brdv) | RSPI::SPCMD0.SPB.b(0b0111);

			RSPI::SPCR.SPMS = 1;
			RSPI::SPCR.MSTR = 1;

			RSPI::SPCR.SPE = 1;

			return f;
		}


		//----------------------------------------------------------------//
		/*!
			@brief	リード・ライト
			@param[in]	data	書き込みデータ
			@return 読み出しデータ
		*/
		//----------------------------------------------------------------//
		uint8_t xchg(uint8_t data = 0xff)
		{
//			RSPI::SPCR.SPTIE = 0;
//			RSPI::SPCR.SPRIE = 0;
			RSPI::SPDR = static_cast<uint32_t>(data);
			while(RSPI::SPSR.SPRF() == 0) sleep_();
		    return static_cast<uint8_t>(RSPI::SPDR());
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアル送信
			@param[in]	src	送信ソース
			@param[in]	cnt	送信サイズ
		*/
		//-----------------------------------------------------------------//
		void send(const uint8_t* src, uint16_t size)
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
		void recv(uint8_t* dst, uint16_t size)
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
		void destroy(bool power = true)
		{
			RSPI::SPCR = 0x00;
			port_map::turn(RSPI::get_peripheral(), false);
			if(power) power_cfg::turn(RSPI::get_peripheral(), false);
		}

	};
}
