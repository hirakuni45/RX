#pragma once
//=====================================================================//
/*!	@file
	@brief	RX62N, RX621, RX63T グループ・CMT I/O 制御 @n
			Copyright 2013 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "cmt.hpp"
#include "rx63x/system.hpp"
#include "rx63x/icu.hpp"
#include "vect.h"

namespace device {

	extern void (*CMT_task[4])();
	extern volatile uint32_t CMT_counter[4];

	INTERRUPT_FUNC void task_CMT0();
	INTERRUPT_FUNC void task_CMT1();
	INTERRUPT_FUNC void task_CMT2();
	INTERRUPT_FUNC void task_CMT3();

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  CMT I/O クラス
		@param[in]	T	CMT クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class T>
	class cmt_io {

		T	cmt_;

		uint32_t	clock_;

		void sleep_() { }

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief  コンストラクター
		*/
		//-----------------------------------------------------------------//
		cmt_io() : clock_(0) { }


		//-----------------------------------------------------------------//
		/*!
			@brief  ベースクロックの設定
			@param[in]	clock	ベース周波数
		*/
		//-----------------------------------------------------------------//
		void set_clock(uint32_t clock) { clock_ = clock; }


		//-----------------------------------------------------------------//
		/*!
			@brief  初期化
			@param[in]	freq	タイマー周波数
			@param[in]	level	割り込みレベル
			@return レンジオーバーなら「false」を返す
		*/
		//-----------------------------------------------------------------//
		bool initialize(uint32_t freq, uint8_t level) const {
			if(freq == 0 || clock_ == 0) return false;

			uint32_t cmcor = clock_ / freq / 8;
			uint8_t cks = 0;
			while(cmcor > 65536) {
				cmcor >>= 2;
				++cks;
			}
			if(cks > 3 || cmcor == 0) {
				return false;
			}

			uint32_t chanel = cmt_.get_chanel();
			switch(chanel) {
			case 0:
				cmt_.CMSTR0.STR0 = 0;
				SYSTEM::MSTPCRA.MSTPA15 = 0;
				CMT_task[0] = 0;
				set_interrupt_task(task_CMT0, ICU::VECTOR::CMI0);
				ICU::IPR.CMI0 = level;
				ICU::IER.CMI0 = true;
				ICU::IR.CMI0 = 0;
				break;
			case 1:
				cmt_.CMSTR0.STR1 = 0;
				SYSTEM::MSTPCRA.MSTPA15 = 0;
				CMT_task[1] = 0;
				set_interrupt_task(task_CMT1, ICU::VECTOR::CMI1);
				ICU::IPR.CMI1 = level;
				ICU::IER.CMI1 = true;
				ICU::IR.CMI1 = 0;
				break;
			case 2:
				cmt_.CMSTR1.STR2 = 0;
				SYSTEM::MSTPCRA.MSTPA14 = 0;
				CMT_task[2] = 0;
				set_interrupt_task(task_CMT2, ICU::VECTOR::CMI2);
				ICU::IPR.CMI2 = level;
				ICU::IER.CMI2 = true;
				ICU::IR.CMI2 = 0;
				break;
			case 3:
				cmt_.CMSTR1.STR3 = 0;
				SYSTEM::MSTPCRA.MSTPA14 = 0;
				CMT_task[3] = 0;
				set_interrupt_task(task_CMT3, ICU::VECTOR::CMI3);
				ICU::IPR.CMI3 = level;
				ICU::IER.CMI3 = true;
				ICU::IR.CMI3 = 0;
				break;
			}

		    cmt_.CMCR = cmt_.CMCR.CMIE.b() | cmt_.CMCR.CKS.b(cks);
		    cmt_.CMCOR = cmcor - 1;

			switch(chanel) {
			case 0:
			    cmt_.CMSTR0.STR0 = 1;
				break;
			case 1:
			    cmt_.CMSTR0.STR1 = 1;
				break;
			case 2:
			    cmt_.CMSTR1.STR2 = 1;
				break;
			case 3:
			    cmt_.CMSTR1.STR3 = 1;
				break;
			}
			return true;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みタスクを設定
			@param[in]	task	設定タスク
		*/
		//-----------------------------------------------------------------//
		void set_task(void (*task)()) const {
			CMT_task[cmt_.get_chanel()] = task;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みと同期
		*/
		//-----------------------------------------------------------------//
		void sync() {
			volatile uint32_t cnt = CMT_counter[cmt_.get_chanel()];
			while(cnt == CMT_counter[cmt_.get_chanel()]) sleep_();
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  割り込みカウンターの値を取得
		*/
		//-----------------------------------------------------------------//
		uint32_t get_count() const {
			return CMT_counter[cmt_.get_chanel()];
		}


		//-----------------------------------------------------------------//
		/*!
			@brief  CMT カウンターの値を取得
		*/
		//-----------------------------------------------------------------//
		uint16_t get_cmt_count() const {
			return cmt_.CMCNT();
		}
	};
}
