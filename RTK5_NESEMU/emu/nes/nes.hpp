#pragma once
//=====================================================================//
/*!	@file
	@brief	ＮＥＳクラス @n
			Copyright 2017 Kunihito Hiramatsu
	@author	平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include "bitmap.h"

#include "nes_apu.h"
#include "nes_mmc.h"
#include "nes_ppu.h"
#include "nes_rom.h"
#include "nes6502.h"

namespace emu {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ＮＥＳクラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	struct nes {

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
#if 0
#ifndef NES_VISIBLE_HEIGHT
#define  NES_VISIBLE_HEIGHT   224
#endif /* !NES_VISIBLE_HEIGHT */
#define  NES_SCREEN_WIDTH     256
#define  NES_SCREEN_HEIGHT    240

/* NTSC = 60Hz, PAL = 50Hz */
#ifdef PAL
#define  NES_REFRESH_RATE     50
#else /* !PAL */
#define  NES_REFRESH_RATE     60
#endif /* !PAL */

#define  NES_CLOCK_DIVIDER    12
// #define  NES_MASTER_CLOCK     21477272.727272727272
#define  NES_MASTER_CLOCK     (236250000 / 11)
#define  NES_SCANLINE_CYCLES  (1364.0 / NES_CLOCK_DIVIDER)
#define  NES_FIQ_PERIOD       (NES_MASTER_CLOCK / NES_CLOCK_DIVIDER / 60)

#define  NES_SKIP_LIMIT       (NES_REFRESH_RATE / 5)   /* 12 or 10, depending on PAL/NTSC */

#endif



	private:
		static const int MAX_MEM_HANDLERS = 32;
		static const int NES_RAMSIZE = 0x800;

		nes6502_context*	cpu_;
		nes6502_memread		readhandler_[MAX_MEM_HANDLERS];
		nes6502_memwrite	writehandler_[MAX_MEM_HANDLERS];

		ppu_t*	ppu_;
		apu_t*	apu_;
		mmc_t*	mmc_;
		rominfo_t*	rominfo_;

		bitmap_t*	vidbuf_;

		bool	fiq_occurred_;
		uint8	fiq_state_;
		int		fiq_cycles_;

		int		scanline_;

		float	scanline_cycles_;
		bool	autoframeskip_;

		bool	poweroff_;
		bool	pause_;


		void mem_trash_(uint8_t* buffer, int length) {
			for(int i = 0; i < length; i++) {
				buffer[i] = static_cast<uint8>(rand());
			}
		}

	public:
		//-------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		*/
		//-------------------------------------------------------------//
		nes() { }


		//-------------------------------------------------------------//
		/*!
			@brief	
		*/
		//-------------------------------------------------------------//
		int isourfile(const char *filename)
		{
//			return rom_checkmagic_(filename);
			return 0;
		}


		int insertcart(const char *filename)
		{

			return 0;
		}


		void setfiq(uint8 state)
		{
		}


		void nmi()
		{
		}


		void irq()
		{
		}


		void emulate(int frame)
		{
		}


		void reset(bool hard_reset)
		{
			if(hard_reset) {
				memset(cpu_->mem_page[0], 0, NES_RAMSIZE);
				if(rominfo_->vram) {
					mem_trash_(rominfo_->vram, 0x2000 * rominfo_->vram_banks);
				}
			}
			apu_reset();
   			ppu_reset(hard_reset == true ? 1 : 0);
   			mmc_reset();
   			nes6502_reset();

			scanline_ = 241;
		}


		void poweroff()
		{
			poweroff_ = true;
		}


		void togglepause()
		{
			pause_ = !pause_;
		}
	};
}
