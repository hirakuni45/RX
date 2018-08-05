#pragma once
//=====================================================================//
/*! @file
    @brief  A/D 変換、キャプチャー制御クラス
    @author 平松邦仁 (hira@rvf-rc45.net)
    @copyright  Copyright (C) 2018 Kunihito Hiramatsu @n
                Released under the MIT license @n
                https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

namespace utils {

	class capture {

//		volatile uint32_t   wpos_;

		/// DMAC 終了割り込み
		class dmac_term_task {
		public:
			void operator() () {
//				device::DMAC0::DMCNT.DTE = 1;  // DMA を再スタート
//				wpos_ = 0;
			}
		};

		typedef device::dmac_mgr<device::DMAC0, dmac_term_task> DMAC_MGR;
		DMAC_MGR    dmac_mgr_;

		class tpu_task {
		public:
			void operator() () {
//				uint32_t tmp = wpos_;
//				++wpos_;
//				if((tmp ^ wpos_) & 64) {
//					sound_out_.service(64);
//				}
			}
		};

		typedef device::tpu_io<device::TPU0, tpu_task> TPU0;
		TPU0        tpu0_;

		

	public:

		void start(uint32_t freq) noexcept
		{
			uint8_t intr_level = 5;
			if(!tpu0_.start(freq, intr_level)) {
				utils::format("TPU0 start error...\n");
			}

#if 0
			{  // DMAC マネージャー開始
				uint8_t intr_level = 4;
				auto ret = dmac_mgr_.start(tpu0_.get_intr_vec(), DMAC_MGR::trans_type::SP_DN_32,
					reinterpret_cast<uint32_t>(sound_out_.get_wave()),
					DAC::DADR0.address(),
					sound_out_.size(), intr_level);
				if(!ret) {
					utils::format("DMAC Not start...\n");
				}
			}
#endif
		}
	};
}
