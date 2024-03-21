#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ・QSPI I/O 制御 @n
			RX64M/RX71M @n
			RX65N/RX651 @n
			RX72N/RX72M
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"
#include "common/vect.h"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  QSPI ベース・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct qspi_base {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  通信幅型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class WIDTH : uint8_t {
			SINGLE,		///< シングル (全二重: IO0, IO1)
			DUAL,		///< デュアル (半二重: IO0, IO1)
			QUAD,		///< クアッド (半二重: IO0 ～ IO3)
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  データ、クロック位相タイプ型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class PHASE : uint8_t {
			MODE0,  ///< モード０、CPOL:0 CPHA:0
			MODE1,  ///< モード１、CPOL:0 CPHA:1
			MODE2,  ///< モード２、CPOL:1 CPHA:0
			MODE3,  ///< モード３、CPOL:1 CPHA:1
		};


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  データ長型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class DLEN : uint8_t {
			W8, 	///< 8 bits
			W16,	///< 16 bits
			W32,	///< 32 bits
		};
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  QSPI 制御クラス
		@param[in]	QSPI	QSPI 定義クラス
		@param[in]	BUSW	バス幅の指定（省略すると「QUAD」）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class QSPI, qspi_base::WIDTH BUSW = qspi_base::WIDTH::QUAD>
	class qspi_io : public qspi_base {

		const device::port_map_order::qspi_port_t&	group_;

		ICU::LEVEL	level_;

		DLEN	dlen_;

		// 便宜上のスリープ
		void sleep_() { asm("nop"); }


		bool clock_div_(uint32_t speed, uint8_t& brdv, uint8_t& spbr) noexcept
		{
			auto br = static_cast<uint32_t>(QSPI::PCLK) / speed;
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
			@param[in] group	ポート・グループ
		*/
		//-----------------------------------------------------------------//
		explicit qspi_io(const device::port_map_order::qspi_port_t& group) noexcept :
			group_(group), level_(ICU::LEVEL::NONE), dlen_(DLEN::W8)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief  通信速度を設定して、CSI を有効にする
			@param[in]	speed	通信速度
			@param[in]	phase	クロック位相タイプ
			@param[in]	dlen	データ長設定
			@param[in]	level	割り込みレベル、NONE の場合はポーリング
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t speed, PHASE phase, DLEN dlen, ICU::LEVEL level = ICU::LEVEL::NONE) noexcept
		{
			uint8_t brdv;
			uint8_t spbr;
			if(!clock_div_(speed, brdv, spbr)) {
				return false;
			}

			// 電源を有効にする
			power_mgr::turn(QSPI::PERIPHERAL);

			// ポートを有効にする
			port_map_qspi::turn(group_, true);

			level_ = level;
			dlen_ = dlen;

			// デバイスを不許可
//			QSPI::SPCR = 0x00;

			// 設定
		    QSPI::SPBR = spbr;
			QSPI::SPPCR = 0x00;	// Fixed idle value, disable loop-back
			QSPI::SPSCR = 0x00;	// disable sequence control
			QSPI::SPDCR = 0x20;	// SPLW=1 (long word access) 
///			QSPI::SPCMD0 = RSPI::SPCMD0.LSBF.b() | RSPI::SPCMD0.BRDV.b(brdv) | RSPI::SPCMD0.SPB.b(0b0100);
			bool cpol = static_cast<uint8_t>(phase) & 1;
			bool cpha = (static_cast<uint8_t>(phase) >> 1) & 1;

			QSPI::SPCMD[0] = QSPI::SPCMD[0].BRDV.b(brdv)
				| QSPI::SPCMD[0].SPB.b(static_cast<uint8_t>(dlen))
				| QSPI::SPCMD[0].CPOL.b(cpol) | QSPI::SPCMD[0].CPHA.b(cpha);

			QSPI::SPCR.MSTR = 1;

			QSPI::SPCR.SPE = 1;

			return true;
		}


		//----------------------------------------------------------------//
		/*!
			@brief	SSL を許可
			@param[in]	ena		SSL の値
		*/
		//----------------------------------------------------------------//
		void enable_ssl(bool ena = true) noexcept
		{
//			QSPI::SPCMD[0].
		}


		//----------------------------------------------------------------//
		/*!
			@brief	送信
			@param[in]	data	送信データ
		*/
		//----------------------------------------------------------------//
		void send(uint32_t data) noexcept
		{
			while(QSPI::SPSR.SPTEF() != 0) sleep_();

			switch(dlen_) {
			case DLEN::W8:
				QSPI::SPDR8 = data;
				break;
			case DLEN::W16:
				QSPI::SPDR16 = data;
				break;
			case DLEN::W32:
				QSPI::SPDR32 = data;
				break;
			}
		}


		//----------------------------------------------------------------//
		/*!
			@brief	受信
			@return 受信データ
		*/
		//----------------------------------------------------------------//
		uint32_t recv() noexcept
		{
			while(QSPI::SPSR.SPRFF() != 0) sleep_();

			switch(dlen_) {
			case DLEN::W8:
				return QSPI::SPDR8();
			case DLEN::W16:
				return QSPI::SPDR16();
			case DLEN::W32:
				return QSPI::SPDR32();
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  連続送信
			@param[in]	src	送信ソース
			@param[in]	cnt	送信サイズ（バイト）
			@return 転送サイズを返す（バイト）
		*/
		//-----------------------------------------------------------------//
		uint32_t send(const void* src, uint32_t size) noexcept
		{
			auto ptr = static_cast<const uint8_t*>(src);
			auto end = ptr + size;
			while(ptr < end) {
				uint32_t d = *ptr++;
				send(d);
			}
			return size;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  連続受信
			@param[out]	dst	受信先
			@param[in]	cnt	受信サイズ
		*/
		//-----------------------------------------------------------------//
		void recv(void* dst, uint32_t size) noexcept
		{
			auto ptr = static_cast<uint8_t*>(dst);
			auto end = ptr + size;
			while(ptr < end) {
				*ptr++ = recv();
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
			port_map::turn(QSPI::PERIPHERAL, false);
			if(power) power_mgr::turn(QSPI::PERIPHERAL, false);
		}
	};
}
