#pragma once
//=====================================================================//
/*!	@file
	@brief	USB Host Mass Strage Class
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/renesas.hpp"

namespace device {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  HMSC
		@param[in]	USB_IO	USB 制御クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class USB_IO>
	class usb_hmsc {

		USB_IO&		usb_;


	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		usb_hmsc(USB_IO& usb) : usb_(usb) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  開始
			@return 正常なら「true」
		*/
		//-----------------------------------------------------------------//
		bool start() noexcept
		{






			return true;
		}

#if 0
		//-----------------------------------------------------------------//
		/*!
			@brief  廃棄（割り込みを停止して、ユニットを停止）
		*/
		//-----------------------------------------------------------------//
		void destroy() noexcept
		{
		    CMT::CMCR.CMIE = 0;
			CMT::enable(false);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みと同期
		*/
		//-----------------------------------------------------------------//
		void sync() const noexcept
		{
			if(level_ > 0) {
				volatile uint32_t cnt = counter_;
				while(cnt == counter_) sleep_();
			} else {
				auto ref = CMT::CMCNT();
				while(ref <= CMT::CMCNT()) sleep_();
				task_();
				++counter_;
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みカウンターの値を設定
			@param[in]	n	割り込みカウンターの値
		*/
		//-----------------------------------------------------------------//
		static void set_counter(uint32_t n) noexcept { counter_ = n; }


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みカウンターの値を取得
			@return 割り込みカウンターの値
		*/
		//-----------------------------------------------------------------//
		static uint32_t get_counter() noexcept { return counter_; }


		//-----------------------------------------------------------------//
		/*!
			@brief  CMCNT レジスターの値を取得
			@return CMCNT レジスター
		*/
		//-----------------------------------------------------------------//
		uint16_t get_cmt_count() const noexcept { return CMT::CMCNT(); }


		//-----------------------------------------------------------------//
		/*!
			@brief  CMCOR レジスターの値を取得
			@return CMCOR レジスター
		*/
		//-----------------------------------------------------------------//
		uint16_t get_cmp_count() const noexcept { return CMT::CMCOR(); }


		//-----------------------------------------------------------------//
		/*!
			@brief  TASK クラスの参照
			@return TASK クラス
		*/
		//-----------------------------------------------------------------//
		static TASK& at_task() noexcept { return task_; }
#endif
	};

//	template <class CMT, class TASK> volatile uint32_t cmt_io<CMT, TASK>::counter_ = 0;
//	template <class CMT, class TASK> TASK cmt_io<CMT, TASK>::task_;
}
