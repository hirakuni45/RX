/*
** Nofrendo (c) 1998-2000 Matthew Conte (matt@conte.com)
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of version 2 of the GNU Library General 
** Public License as published by the Free Software Foundation.
**
** This program is distributed in the hope that it will be useful, 
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
** Library General Public License for more details.  To obtain a 
** copy of the GNU Library General Public License, write to the Free 
** Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
** Any permitted reproduction of these routines, in whole or in part,
** must bear this legend.
**
**
** nes.c
**
** NES hardware related routines
** $Id: nes.c,v 1.2 2001/04/27 14:37:11 neil Exp $
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "nes6502.h"
#include "log.h"
#include "nes.h"
#include "nes_apu.h"
#include "nes_ppu.h"
#include "nes_rom.h"
#include "nes_mmc.h"

#define  NES_CLOCK_DIVIDER    12
// #define  NES_MASTER_CLOCK     21477272.727272727272
#define  NES_MASTER_CLOCK     (236250000 / 11)
#define  NES_SCANLINE_CYCLES  (1364.0 / NES_CLOCK_DIVIDER)
#define  NES_FIQ_PERIOD       (NES_MASTER_CLOCK / NES_CLOCK_DIVIDER / 60)

#define  NES_RAMSIZE          0x800

#define  NES_SKIP_LIMIT       (NES_REFRESH_RATE / 5)   /* 12 or 10, depending on PAL/NTSC */

static nes_t nes_;

nes_t *nes_getcontext(void)
{
   return &nes_;
}

/* find out if a file is ours */
int nes_isourfile(const char *filename)
{
   return rom_checkmagic(filename);
}

static uint8 ram_read(uint32 address)
{
   return nes_.cpu->mem_page[0][address & (NES_RAMSIZE - 1)];
}

static void ram_write(uint32 address, uint8 value)
{
   nes_.cpu->mem_page[0][address & (NES_RAMSIZE - 1)] = value;
}

static void write_protect(uint32 address, uint8 value)
{
   /* don't allow write to go through */
   UNUSED(address);
   UNUSED(value);
}

static uint8 read_protect(uint32 address)
{
   /* don't allow read to go through */
   UNUSED(address);

   return 0xFF;
}

#define  LAST_MEMORY_HANDLER  { -1, -1, NULL }
/* read/write handlers for standard NES */
static nes6502_memread default_readhandler[] =
{
   { 0x0800, 0x1FFF, ram_read },
   { 0x2000, 0x3FFF, ppu_read },
   { 0x4000, 0x4015, apu_read },
   { 0x4016, 0x4017, ppu_readhigh },
   LAST_MEMORY_HANDLER
};

static nes6502_memwrite default_writehandler[] =
{
   { 0x0800, 0x1FFF, ram_write },
   { 0x2000, 0x3FFF, ppu_write },
   { 0x4000, 0x4013, apu_write },
   { 0x4015, 0x4015, apu_write },
   { 0x4014, 0x4017, ppu_writehigh },
   LAST_MEMORY_HANDLER
};

/* this big nasty boy sets up the address handlers that the CPU uses */
static void build_address_handlers_()
{
	int count, num_handlers = 0;

	const mapintf_t *intf = nes_.mmc->intf;

	memset(nes_.readhandler, 0, sizeof(nes_.readhandler));
	memset(nes_.writehandler, 0, sizeof(nes_.writehandler));

   for (count = 0; num_handlers < MAX_MEM_HANDLERS; count++, num_handlers++)
   {
      if (NULL == default_readhandler[count].read_func)
         break;

      memcpy(&nes_.readhandler[num_handlers], &default_readhandler[count],
             sizeof(nes6502_memread));
   }

   if (intf->sound_ext)
   {
      if (NULL != intf->sound_ext->mem_read)
      {
         for (count = 0; num_handlers < MAX_MEM_HANDLERS; count++, num_handlers++)
         {
            if (NULL == intf->sound_ext->mem_read[count].read_func)
               break;

            memcpy(&nes_.readhandler[num_handlers], &intf->sound_ext->mem_read[count],
                   sizeof(nes6502_memread));
         }
      }
   }

   if (NULL != intf->mem_read)
   {
      for (count = 0; num_handlers < MAX_MEM_HANDLERS; count++, num_handlers++)
      {
         if (NULL == intf->mem_read[count].read_func)
            break;

         memcpy(&nes_.readhandler[num_handlers], &intf->mem_read[count],
                sizeof(nes6502_memread));
      }
   }

   /* TODO: poof! numbers */
   nes_.readhandler[num_handlers].min_range = 0x4018;
   nes_.readhandler[num_handlers].max_range = 0x5FFF;
   nes_.readhandler[num_handlers].read_func = read_protect;
   num_handlers++;
   nes_.readhandler[num_handlers].min_range = -1;
   nes_.readhandler[num_handlers].max_range = -1;
   nes_.readhandler[num_handlers].read_func = NULL;
   num_handlers++;
   ASSERT(num_handlers <= MAX_MEM_HANDLERS);

   num_handlers = 0;

   for (count = 0; num_handlers < MAX_MEM_HANDLERS; count++, num_handlers++)
   {
      if (NULL == default_writehandler[count].write_func)
         break;

      memcpy(&nes_.writehandler[num_handlers], &default_writehandler[count],
             sizeof(nes6502_memwrite));
   }

   if (intf->sound_ext)
   {
      if (NULL != intf->sound_ext->mem_write)
      {
         for (count = 0; num_handlers < MAX_MEM_HANDLERS; count++, num_handlers++)
         {
            if (NULL == intf->sound_ext->mem_write[count].write_func)
               break;

            memcpy(&nes_.writehandler[num_handlers], &intf->sound_ext->mem_write[count],
                   sizeof(nes6502_memwrite));
         }
      }
   }

   if (NULL != intf->mem_write)
   {
      for (count = 0; num_handlers < MAX_MEM_HANDLERS; count++, num_handlers++)
      {
         if (NULL == intf->mem_write[count].write_func)
            break;

         memcpy(&nes_.writehandler[num_handlers], &intf->mem_write[count],
                sizeof(nes6502_memwrite));
      }
   }

   /* catch-all for bad writes */
   /* TODO: poof! numbers */
   nes_.writehandler[num_handlers].min_range = 0x4018;
   nes_.writehandler[num_handlers].max_range = 0x5FFF;
   nes_.writehandler[num_handlers].write_func = write_protect;
   num_handlers++;
   nes_.writehandler[num_handlers].min_range = 0x8000;
   nes_.writehandler[num_handlers].max_range = 0xFFFF;
   nes_.writehandler[num_handlers].write_func = write_protect;
   num_handlers++;
   nes_.writehandler[num_handlers].min_range = -1;
   nes_.writehandler[num_handlers].max_range = -1;
   nes_.writehandler[num_handlers].write_func = NULL;
   num_handlers++;
   ASSERT(num_handlers <= MAX_MEM_HANDLERS);
}

/* raise an IRQ */
void nes_irq(void)
{
#ifdef NOFRENDO_DEBUG
   if (nes_.scanline <= NES_SCREEN_HEIGHT)
      memset(nes_.vidbuf->line[nes_.scanline - 1], GUI_RED, NES_SCREEN_WIDTH);
#endif /* NOFRENDO_DEBUG */
   nes6502_irq();
}

static uint8 nes_clearfiq(void)
{
   if (nes_.fiq_occurred)
   {
      nes_.fiq_occurred = false;
      return 0x40;
   }

   return 0;
}

void nes_setfiq(uint8 value)
{
   nes_.fiq_state = value;
   nes_.fiq_cycles = (int) NES_FIQ_PERIOD;
}

static void nes_checkfiq(int cycles)
{
   nes_.fiq_cycles -= cycles;
   if (nes_.fiq_cycles <= 0)
   {
      nes_.fiq_cycles += (int) NES_FIQ_PERIOD;
      if (0 == (nes_.fiq_state & 0xC0))
      {
         nes_.fiq_occurred = true;
         nes6502_irq();
      }
   }
}

void nes_nmi(void)
{
   nes6502_nmi();
}

static void nes_renderframe(bool draw_flag)
{
	int elapsed_cycles;
	const mapintf_t *mapintf = nes_.mmc->intf;
	int in_vblank = 0;

	while(262 != nes_.scanline) {
		ppu_scanline(nes_.vidbuf, nes_.scanline, draw_flag);

		if(241 == nes_.scanline) {
			/* 7-9 cycle delay between when VINT flag goes up and NMI is taken */
			elapsed_cycles = nes6502_execute(7);
			nes_.scanline_cycles -= elapsed_cycles;
			nes_checkfiq(elapsed_cycles);

			ppu_checknmi();

			if(mapintf->vblank) {
				mapintf->vblank();
			}
			in_vblank = 1;
		} 

		if(mapintf->hblank) {
			mapintf->hblank(in_vblank);
		}

		nes_.scanline_cycles += (float) NES_SCANLINE_CYCLES;
		elapsed_cycles = nes6502_execute((int) nes_.scanline_cycles);
		nes_.scanline_cycles -= (float) elapsed_cycles;
		nes_checkfiq(elapsed_cycles);

		ppu_endscanline(nes_.scanline);
		nes_.scanline++;
	}
	nes_.scanline = 0;
}


void nes_emulate(int frames)
{
	if(nes_.pause) return;

	nes_.scanline_cycles = 0;
	nes_.fiq_cycles = (int) NES_FIQ_PERIOD;

	if(frames != 0) {
		while(frames > 0) {
			if(frames == 1) {
				nes_renderframe(true);
			} else {
				nes_renderframe(false);
			}
			--frames;
		}
	}
}

static void mem_trash(uint8 *buffer, int length)
{
   int i;

   for (i = 0; i < length; i++)
      buffer[i] = (uint8) rand();
}

/* Reset NES hardware */
void nes_reset(int reset_type)
{
   if (HARD_RESET == reset_type)
   {
      memset(nes_.cpu->mem_page[0], 0, NES_RAMSIZE);
      if (nes_.rominfo->vram)
         mem_trash(nes_.rominfo->vram, 0x2000 * nes_.rominfo->vram_banks);
   }

   apu_reset();
   ppu_reset(reset_type);
   mmc_reset();
   nes6502_reset();

   nes_.scanline = 241;
}

void nes_destroy(void)
{
	rom_free(nes_.rominfo);
	apu_destroy();
	bmp_destroy(nes_.vidbuf);
	if(nes_.cpu != NULL) {
		free(nes_.cpu->mem_page[0]);
	}
}

void nes_poweroff(void)
{
   nes_.poweroff = true;
}

void nes_pause(int enable)
{
	if(enable) nes_.pause = true;
	else nes_.pause = false;
}

/* insert a cart into the NES */
int nes_insertcart(const char *filename)
{
	/* rom file */
	nes_.rominfo = rom_load(filename);
	if(NULL == nes_.rominfo) {
		return -1;
	}

	/* map cart's SRAM to CPU $6000-$7FFF */
	if(nes_.rominfo->sram) {
		nes_.cpu->mem_page[6] = nes_.rominfo->sram;
		nes_.cpu->mem_page[7] = nes_.rominfo->sram + 0x1000;
	}

	/* mapper */
	mmc_create(nes_.rominfo);
	nes_.mmc = mmc_getcontext();

	/* if there's VRAM, let the PPU know */
	if (NULL != nes_.rominfo->vram) {
		ppu_getcontext()->vram_present = true;
	}

	apu_setext(nes_.mmc->intf->sound_ext);
   
	build_address_handlers_();

	nes6502_setup_page();

	nes_reset(HARD_RESET);
	return 0;
}

/* Initialize NES CPU, hardware, etc. */
int nes_create(int sample_rate, int sample_bits)
{
	int i;
	memset(&nes_, 0, sizeof(nes_t));

	/* bitmap */
	/* 8 pixel overdraw */
	nes_.vidbuf = bmp_create(NES_SCREEN_WIDTH, NES_SCREEN_HEIGHT, 8);
	if(NULL == nes_.vidbuf) {
		goto _fail;
	}

	nes_.autoframeskip = true;

	/* cpu */
	nes6502_init();
	nes_.cpu = nes6502_getcontext();
   
	/* allocate 2kB RAM */
	nes_.cpu->mem_page[0] = malloc(NES_RAMSIZE);
	if (NULL == nes_.cpu->mem_page[0])
		goto _fail;

	/* point all pages at NULL for now */
	for (i = 1; i < NES6502_NUMBANKS; i++)
		nes_.cpu->mem_page[i] = NULL;

	nes_.cpu->read_handler  = nes_.readhandler;
	nes_.cpu->write_handler = nes_.writehandler;

	// apu
	apu_create(0, sample_rate, NES_REFRESH_RATE, sample_bits);
	nes_.apu = apu_getcontext();

	/* set the IRQ routines */
	nes_.apu->irq_callback = nes_irq;
	nes_.apu->irqclear_callback = nes_clearfiq;

	/* ppu */
	ppu_create();
	nes_.ppu = ppu_getcontext();

	nes_.poweroff = false;
	nes_.pause = false;

	return 0;

_fail:
	nes_destroy();
	return -1;
}

/*
** $Log: nes.c,v $
** Revision 1.2  2001/04/27 14:37:11  neil
** wheeee
**
** Revision 1.1.1.1  2001/04/27 07:03:54  neil
** initial
**
** Revision 1.18  2000/11/29 12:58:23  matt
** timing/fiq fixes
**
** Revision 1.17  2000/11/27 19:36:15  matt
** more timing fixes
**
** Revision 1.16  2000/11/26 16:13:13  matt
** slight fix (?) to nes_fiq
**
** Revision 1.15  2000/11/26 15:51:13  matt
** frame IRQ emulation
**
** Revision 1.14  2000/11/25 20:30:39  matt
** scanline emulation simplifications/timing fixes
**
** Revision 1.13  2000/11/25 01:53:42  matt
** bool stinks sometimes
**
** Revision 1.12  2000/11/21 13:28:40  matt
** take care to zero allocated mem
**
** Revision 1.11  2000/11/20 13:23:32  matt
** nofrendo.c now handles timer
**
** Revision 1.10  2000/11/09 14:07:27  matt
** state load fixed, state save mostly fixed
**
** Revision 1.9  2000/11/05 22:19:37  matt
** pause buglet fixed
**
** Revision 1.8  2000/11/05 06:27:09  matt
** thinlib spawns changes
**
** Revision 1.7  2000/10/29 14:36:45  matt
** nes_clearframeirq is static
**
** Revision 1.6  2000/10/28 15:20:41  matt
** irq callbacks in nes_apu
**
** Revision 1.5  2000/10/27 12:55:58  matt
** nes6502 now uses 4kB banks across the boards
**
** Revision 1.4  2000/10/25 13:44:02  matt
** no more silly define names
**
** Revision 1.3  2000/10/25 01:23:08  matt
** basic system autodetection
**
** Revision 1.2  2000/10/25 00:23:16  matt
** makefiles updated for new directory structure
**
** Revision 1.1  2000/10/24 12:20:28  matt
** changed directory structure
**
** Revision 1.50  2000/10/23 17:51:09  matt
** adding fds support
**
** Revision 1.49  2000/10/23 15:53:08  matt
** better system handling
**
** Revision 1.48  2000/10/22 20:02:29  matt
** autoframeskip bugfix
**
** Revision 1.47  2000/10/22 19:16:15  matt
** more sane timer ISR / autoframeskip
**
** Revision 1.46  2000/10/21 19:26:59  matt
** many more cleanups
**
** Revision 1.45  2000/10/17 12:00:56  matt
** selectable apu base frequency
**
** Revision 1.44  2000/10/10 13:58:14  matt
** stroustrup squeezing his way in the door
**
** Revision 1.43  2000/10/10 13:05:30  matt
** Mr. Clean makes a guest appearance
**
** Revision 1.42  2000/10/08 17:53:37  matt
** minor accuracy changes
**
** Revision 1.41  2000/09/18 02:09:12  matt
** -pedantic is your friend
**
** Revision 1.40  2000/09/15 13:38:39  matt
** changes for optimized apu core
**
** Revision 1.39  2000/09/15 04:58:07  matt
** simplifying and optimizing APU core
**
** Revision 1.38  2000/09/08 11:57:29  matt
** no more nes_fiq
**
** Revision 1.37  2000/08/31 02:39:01  matt
** moved dos stuff in here (temp)
**
** Revision 1.36  2000/08/16 02:51:55  matt
** random cleanups
**
** Revision 1.35  2000/08/11 02:43:50  matt
** moved frame irq stuff out of APU into here
**
** Revision 1.34  2000/08/11 01:42:43  matt
** change to OSD sound info interface
**
** Revision 1.33  2000/07/31 04:27:59  matt
** one million cleanups
**
** Revision 1.32  2000/07/30 04:32:32  matt
** emulation of the NES frame IRQ
**
** Revision 1.31  2000/07/27 04:07:14  matt
** cleaned up the neighborhood lawns
**
** Revision 1.30  2000/07/27 03:59:52  neil
** pausing tweaks, during fullscreen toggles
**
** Revision 1.29  2000/07/27 03:19:22  matt
** just a little cleaner, that's all
**
** Revision 1.28  2000/07/27 02:55:23  matt
** nes_emulate went through detox
**
** Revision 1.27  2000/07/27 02:49:18  matt
** cleaner flow in nes_emulate
**
** Revision 1.26  2000/07/27 01:17:09  matt
** nes_insertrom -> nes_insertcart
**
** Revision 1.25  2000/07/26 21:36:14  neil
** Big honkin' change -- see the mailing list
**
** Revision 1.24  2000/07/25 02:25:53  matt
** safer xxx_destroy calls
**
** Revision 1.23  2000/07/24 04:32:40  matt
** autoframeskip bugfix
**
** Revision 1.22  2000/07/23 15:13:48  matt
** apu API change, autoframeskip part of nes_t struct
**
** Revision 1.21  2000/07/21 02:44:41  matt
** merged osd_getinput and osd_gethostinput
**
** Revision 1.20  2000/07/17 05:12:55  matt
** nes_ppu.c is no longer a scary place to be-- cleaner & faster
**
** Revision 1.19  2000/07/17 01:52:28  matt
** made sure last line of all source files is a newline
**
** Revision 1.18  2000/07/15 23:51:23  matt
** hack for certain filthy NES titles
**
** Revision 1.17  2000/07/11 04:31:54  matt
** less magic number nastiness for screen dimensions
**
** Revision 1.16  2000/07/11 02:38:25  matt
** encapsulated memory address handlers into nes/nsf
**
** Revision 1.15  2000/07/10 13:50:49  matt
** added function nes_irq()
**
** Revision 1.14  2000/07/10 05:27:55  matt
** cleaned up mapper-specific callbacks
**
** Revision 1.13  2000/07/09 03:43:26  matt
** minor changes to gui handling
**
** Revision 1.12  2000/07/06 16:42:23  matt
** updated for new video driver
**
** Revision 1.11  2000/07/05 19:57:36  neil
** __GNUC -> __DJGPP in nes.c
**
** Revision 1.10  2000/07/05 12:23:03  matt
** removed unnecessary references
**
** Revision 1.9  2000/07/04 23:12:34  matt
** memory protection handlers
**
** Revision 1.8  2000/07/04 04:58:29  matt
** dynamic memory range handlers
**
** Revision 1.7  2000/06/26 04:58:51  matt
** minor bugfix
**
** Revision 1.6  2000/06/20 20:42:12  matt
** fixed some NULL pointer problems
**
** Revision 1.5  2000/06/09 15:12:26  matt
** initial revision
**
*/
