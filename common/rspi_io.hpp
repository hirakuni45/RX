#pragma once
//=========================================================================//
/*!	@file
	@brief	RX グループ・RSPI I/O 制御
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2025 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"
#include "common/vect.h"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  RSPI 制御クラス
		@param[in]	RSPI		RSPI 定義クラス
		@param[in]	RSPI_ODR	RSPI ポート候補
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class RSPI, port_map::ORDER RSPI_ODR = port_map::ORDER::FIRST>
	class rspi_io {
	public:

		typedef RSPI value_type;	///< RSPI 型

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  データ、クロック位相タイプ型
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class PHASE : uint8_t {
			TYPE1,  ///< タイプ１ (MODE0): CPOL:0 CPHA:0
			TYPE2,  ///< タイプ２ (MODE1): CPOL:0 CPHA:1
			TYPE3,  ///< タイプ３ (MODE2): CPOL:1 CPHA:0
			TYPE4,  ///< タイプ４ (MODE3): CPOL:1 CPHA:1 (SD カードアクセス）
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

		uint32_t	speed_;
		uint8_t		level_;

		// 便宜上のスリープ
		void sleep_() { asm("nop"); }

		bool clock_div_(uint32_t speed, uint8_t& brdv, uint8_t& spbr) {
///			utils::format("PCLK: %d\n") % static_cast<uint32_t>(RSPI::PCLK);
			uint32_t br = static_cast<uint32_t>(RSPI::PCLK) / speed;
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
		rspi_io() noexcept : speed_(0), level_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  設定可能な最大速度を返す @n
					・RX24T: 20MHz @n
					・RX64M: 40MHz
			@return 最大速度
		*/
		//-----------------------------------------------------------------//
		uint32_t get_max_speed() const noexcept
		{
			// 最大クロックは、PCLK の 1/2
			uint32_t clk = RSPI::PCLK / 2;
#ifdef SEEDA
			while(clk > 20'000'000) {  // 20MHz
				clk >>= 1;
			}
#endif
			return clk;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  通信速度を設定して、CSI を有効にする
			@param[in]	speed	通信速度
			@param[in]	ctype	クロック位相タイプ
			@param[in]	dlen	データ長設定
			@param[in]	level	割り込みレベル、０の場合はポーリング
			@return エラー（速度設定範囲外）なら「false」
		*/
		//-----------------------------------------------------------------//
		bool start(uint32_t speed, PHASE ctype, DLEN dlen, uint8_t level = 0) noexcept
		{
			speed_ = speed;
			level_ = level;

			uint8_t brdv;
			uint8_t spbr;
			if(!clock_div_(speed, brdv, spbr)) {
				return false;
			}

			power_mgr::turn(RSPI::PERIPHERAL);

			port_map::turn(RSPI::PERIPHERAL, true, RSPI_ODR);

			// デバイスを不許可
			RSPI::SPCR = 0x00;

			// 設定
			RSPI::SPBR = spbr;

			RSPI::SPPCR = 0x00;	// Fixed idle value, disable loop-back
			RSPI::SPSCR = 0x00;	// disable sequence control
			RSPI::SPDCR = 0x20;	// SPLW=1 (long word access) 

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
			RSPI::SPCMD[0] = RSPI::SPCMD.BRDV.b(brdv)
				| RSPI::SPCMD.SPB.b(static_cast<uint8_t>(dlen))
				| RSPI::SPCMD.CPOL.b(cpol) | RSPI::SPCMD.CPHA.b(cpha);

			RSPI::SPCR.SPMS = 1;
			RSPI::SPCR.MSTR = 1;

			RSPI::SPCR.SPE = 1;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  ＳＤカード用設定を有効にする
			@param[in]	speed	通信速度
			@return エラー（速度設定範囲外）なら「false」
		*/
		//-----------------------------------------------------------------//
		bool start_sdc(uint32_t speed) noexcept
		{
			speed_ = speed;
			level_ = 0;

			uint8_t brdv;
			uint8_t spbr;
			if(!clock_div_(speed, brdv, spbr)) {
				return false;
			}

			power_mgr::turn(RSPI::PERIPHERAL);

			port_map::turn(RSPI::PERIPHERAL, true, RSPI_ODR);

			RSPI::SPCR = 0x00;
#if 0
			utils::format("RSPI Request Speed: %u [Hz]\n") % speed;
			utils::format("RSPI SPBR: %d\n") % static_cast<uint32_t>(spbr);
			utils::format("RSPI BRDV: %d\n") % static_cast<uint32_t>(brdv);
#endif
			RSPI::SPBR = spbr;

			RSPI::SPPCR = 0x00;	 // Fixed idle value, disable loop-back
			RSPI::SPSCR = 0x00;	 // sequence length: 1 

			if(RSPI::BYTE_ACCESS) {  // BYTE access
				RSPI::SPDCR = RSPI::SPDCR.SPBYT.b(1);
			}

			RSPI::SPND  = 0b011;  // 4 RSPCK + 2 PCLK
			RSPI::SPCMD[0] = RSPI::SPCMD.BRDV.b(brdv)
				| RSPI::SPCMD.SPB.b(static_cast<uint8_t>(DLEN::W8))
				| RSPI::SPCMD.CPHA.b(1) | RSPI::SPCMD.CPOL.b(1) | RSPI::SPCMD.SPNDEN.b(1);

			// RSPCK 自動停止有効
			RSPI::SPCR2 = RSPI::SPCR2.SCKASE.b(1);
			// 3 線式（SSLAx を使わない）、Master
			RSPI::SPCR = RSPI::SPCR.SPMS.b(1) | RSPI::SPCR.MSTR.b(1);

			RSPI::SPCR.SPE = 1;

			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	SSL ポートを有効にする
			@param[in]	odr		SSL ポート候補
			@param[in]	ssl		SSL ポート名
			@param[in]	ena		無効にする場合「false」
			@return エラーなら「false」
		*/
		//-----------------------------------------------------------------//
		bool enable_ssl(port_map_order::ORDER odr, port_map_order::RSPI ssl, bool ena = true) noexcept
		{
			switch(ssl) {
			case port_map_order::RSPI::SSL0:
				break;
			case port_map_order::RSPI::SSL1:
				break;
			case port_map_order::RSPI::SSL2:
				break;
			case port_map_order::RSPI::SSL3:
				break;
			default:
				return true;
			}

			return true;
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
			RSPI::SPDR.HH = data;
			uint32_t cnt = 0;
			while(RSPI::SPSR.SPRF() == 0) {
				++cnt;
				if(cnt > 40000) break;
			}
			auto val = RSPI::SPDR.HH();
			return val;
		}


		//----------------------------------------------------------------//
		/*!
			@brief	通信レジスタへ書き込み @n
					※通信幅は最大３２ビット（通信モード設定による）
			@param[in]	data	書き込みデータ
		*/
		//----------------------------------------------------------------//
		inline void xchg32_start(uint32_t data = 0) noexcept
		{
			RSPI::SPDR = static_cast<uint32_t>(data);
		}


		//----------------------------------------------------------------//
		/*!
			@brief	通信の同期とレジスタからの読み出し @n
					※通信幅は最大３２ビット（通信モード設定による）
			@return	読み出しデータ
		*/
		//----------------------------------------------------------------//
		inline uint32_t xchg32_sync() noexcept
		{
			while(RSPI::SPSR.SPRF() == 0) sleep_();
			return RSPI::SPDR();
		}


		//----------------------------------------------------------------//
		/*!
			@brief	リード・ライト
			@param[in]	data	書き込みデータ
			@return 読み出しデータ
		*/
		//----------------------------------------------------------------//
		inline uint32_t xchg32(uint32_t data = 0) noexcept
		{
			xchg32_start(data);
			return xchg32_sync();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアル送信
			@param[in]	src	送信ソース
			@param[in]	cnt	送信サイズ
		*/
		//-----------------------------------------------------------------//
		void send(const void* src, uint32_t size) noexcept
		{
			auto ptr = static_cast<const uint8_t*>(src);
			while(size > 0) {
				xchg(*ptr);
				++ptr;
				size--;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  シリアル受信
			@param[out]	dst	受信先
			@param[in]	cnt	受信サイズ
		*/
		//-----------------------------------------------------------------//
		void recv(void* dst, uint32_t size) noexcept
		{
			auto ptr = static_cast<uint8_t*>(dst);
			while(size > 0) {
				*ptr = xchg();
				++ptr;
				size--;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	RSPI の速度を取得
			@param[in]	real	「true」にした場合、内部で計算されたリアルな値
			@return 周期
		 */
		//-----------------------------------------------------------------//
		uint32_t get_speed(bool real = false) const noexcept
		{
			if(real) {
				static constexpr uint8_t n[4] = { 1, 2, 4, 8 };
				uint32_t spd = static_cast<uint32_t>(RSPI::PCLK)
						/ (2 * static_cast<uint32_t>(RSPI::SPBR() + 1) * static_cast<uint32_t>(n[RSPI::SPCMD[0].BRDV()]));
				return spd;
			} else {
				return speed_;
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
			RSPI::SPCR = 0x00;
			port_map::turn(RSPI::PERIPHERAL, false);
			if(power) power_mgr::turn(RSPI::PERIPHERAL, false);
		}
	};
}
