#pragma once
//=========================================================================//
/*!	@file
	@brief	DMAC マネージャー @n
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include "common/renesas.hpp"
#include "common/intr_utils.hpp"
#include "common/vect.h"

/// RX24T には DMAC が無い為、エラーにする。
#ifdef SIG_RX24T
#  error "dmac_man.hpp not support for RX24T"
#endif

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  DMAC マネージャー・クラス
		@param[in]	DMAC	DMA コントローラー
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template<class DMAC, class TASK = utils::null_task>
	class dmac_man {
	public:

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief  タイプ
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class type : uint8_t {
		};


	private:
		static TASK	task_;

		uint32_t	src_;

		uint8_t		level_;


		static INTERRUPT_FUNC void dmac_task_() noexcept
		{
			task_();
		}


		void set_vector_(ICU::VECTOR vec) noexcept
		{
			if(level_) {
				set_interrupt_task(dmac_task_, static_cast<uint32_t>(vec));
			} else {
				set_interrupt_task(nullptr, static_cast<uint32_t>(vec));
			}
			icu_mgr::set_level(DMAC::get_peripheral(), level_);
		}

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		dmac_man() noexcept : src_(0), level_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	開始
			@param[in]	lvl		割り込みレベル
		 */
		//-----------------------------------------------------------------//
		void start(uint32_t lvl = 0) noexcept
		{
			level_ = lvl;

			power_cfg::turn(DMAC::get_peripheral());

			set_vector_(DMAC::get_vec());

			DMAST.DMST = 1;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	動作中か検査
			@return 動作中なら「true」
		 */
		//-----------------------------------------------------------------//
		bool probe() const noexcept {
			return DMAC::DMSTS.ACT();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	メモリー・コピー
			@param[in]	src		コピー元
			@param[in]	dst		コピー先
			@param[in]	len		コピー数（バイト）
			@return コピーが出来ない場合「false」
		 */
		//-----------------------------------------------------------------//
		bool fill(uint32_t src, void* dst, uint32_t len) noexcept
		{
			if(len == 0 || len >= 0x04000000) return false;

			src_ = src;


			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	コピー・メモリー
			@param[in]	src		コピー元
			@param[in]	dst		コピー先
			@param[in]	len		コピー数（バイト単位）@n
								※アドレスが 32 ビット単位の場合、最大 65535 x4 バイト
								※アドレスが 16 ビット単位の場合、最大 65535 x2 バイト
								※アドレスが 8  ビット単位の場合、最大 65535 x1 バイト
			@return コピーが出来ない場合「false」（パラメーターが異常）
		 */
		//-----------------------------------------------------------------//
		bool copy(const void* src, void* dst, uint32_t len) const noexcept
		{
			if(len == 0) return false;

			DMAC::DMCNT.DTE = 0;

			uint32_t src_adr = reinterpret_cast<uint32_t>(src);
			uint32_t dst_adr = reinterpret_cast<uint32_t>(dst);
			uint8_t sz = 0;
			if(len < 4) ;
			else if((src_adr & 3) == 0 && (dst_adr & 3) == 0 && (len & 3) == 0) {  // 32 bits DMA
				sz = 2;
				len >>= 2;
			} else if((src_adr & 1) == 0 && (dst_adr & 1) == 0 && (len & 1) == 0) {  // 16 bits DMA
				sz = 1;
				len >>= 1;
			}

			// 転送元 (+1)、転送先 (+1)
			DMAC::DMAMD = DMAC::DMAMD.DM.b(0b10) | DMAC::DMAMD.SM.b(0b10);

			DMAC::DMTMD = DMAC::DMTMD.DCTG.b(0b00) | DMAC::DMTMD.SZ.b(sz) |
						  DMAC::DMTMD.DTS.b(0b10) | DMAC::DMTMD.MD.b(0b00);

			DMAC::DMSAR = src_adr;
			DMAC::DMDAR = dst_adr;
			DMAC::DMCRA = len;

			DMAC::DMCNT.DTE = 1;

			// CLRS=0 の場合、１回の転送で終了
			DMAC::DMREQ = DMAC::DMREQ.SWREQ.b() | DMAC::DMREQ.CLRS.b();

			return true;
		}
	};
}
