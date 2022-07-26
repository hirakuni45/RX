# -*- tab-width : 4 -*-
#=======================================================================
#   @file
#   @brief  RX65N Makefile
#   @author 平松邦仁 (hira@rvf-rc45.net)
#	@copyright	Copyright (C) 2020, 2021 Kunihito Hiramatsu @n
#				Released under the MIT license @n
#				https://github.com/hirakuni45/RX/blob/master/LICENSE
#=======================================================================
TARGET		=	nesemu

ROOT		=	NESEMU_sample

DEVICE		=	R5F565NE

RX_DEF		=	SIG_RX65N

FATFS_VER	=	ff14/source

BUILD		=	release
# BUILD		=	debug

VPATH		=	../../

ASOURCES	=	common/start.s

CSOURCES	=	common/init.c \
				common/vect.c \
				common/syscalls.c \
				$(FATFS_VER)/ff.c \
				$(FATFS_VER)/ffsystem.c \
				$(FATFS_VER)/ffunicode.c \
				common/time.c \
				$(ROOT)/emu/log.c \
				$(ROOT)/emu/bitmap.c \
				$(ROOT)/emu/cpu/nes6502.c \
				$(ROOT)/emu/nes/mmclist.c \
				$(ROOT)/emu/nes/nes.c \
				$(ROOT)/emu/nes/nes_mmc.c \
				$(ROOT)/emu/nes/nes_pal.c \
				$(ROOT)/emu/nes/nes_ppu.c \
				$(ROOT)/emu/nes/nes_rom.c \
				$(ROOT)/emu/nes/nesinput.c \
				$(ROOT)/emu/nes/nesstate.c \
				$(ROOT)/emu/sndhrdw/fds_snd.c \
				$(ROOT)/emu/sndhrdw/mmc5_snd.c \
				$(ROOT)/emu/sndhrdw/nes_apu.c \
				$(ROOT)/emu/sndhrdw/vrcvisnd.c \
				$(ROOT)/emu/mappers/map000.c \
				$(ROOT)/emu/mappers/map001.c \
				$(ROOT)/emu/mappers/map002.c \
				$(ROOT)/emu/mappers/map003.c \
				$(ROOT)/emu/mappers/map004.c \
				$(ROOT)/emu/mappers/map005.c \
				$(ROOT)/emu/mappers/map007.c \
				$(ROOT)/emu/mappers/map008.c \
				$(ROOT)/emu/mappers/map009.c \
				$(ROOT)/emu/mappers/map011.c \
				$(ROOT)/emu/mappers/map015.c \
				$(ROOT)/emu/mappers/map016.c \
				$(ROOT)/emu/mappers/map018.c \
				$(ROOT)/emu/mappers/map019.c \
				$(ROOT)/emu/mappers/map024.c \
				$(ROOT)/emu/mappers/map032.c \
				$(ROOT)/emu/mappers/map033.c \
				$(ROOT)/emu/mappers/map034.c \
				$(ROOT)/emu/mappers/map040.c \
				$(ROOT)/emu/mappers/map041.c \
				$(ROOT)/emu/mappers/map042.c \
				$(ROOT)/emu/mappers/map046.c \
				$(ROOT)/emu/mappers/map050.c \
				$(ROOT)/emu/mappers/map064.c \
				$(ROOT)/emu/mappers/map065.c \
				$(ROOT)/emu/mappers/map066.c \
				$(ROOT)/emu/mappers/map070.c \
				$(ROOT)/emu/mappers/map073.c \
				$(ROOT)/emu/mappers/map075.c \
				$(ROOT)/emu/mappers/map078.c \
				$(ROOT)/emu/mappers/map079.c \
				$(ROOT)/emu/mappers/map085.c \
				$(ROOT)/emu/mappers/map087.c \
				$(ROOT)/emu/mappers/map093.c \
				$(ROOT)/emu/mappers/map094.c \
				$(ROOT)/emu/mappers/map099.c \
				$(ROOT)/emu/mappers/map160.c \
				$(ROOT)/emu/mappers/map229.c \
				$(ROOT)/emu/mappers/map231.c \
				$(ROOT)/emu/mappers/mapvrc.c \
				$(ROOT)/emu/libsnss/libsnss.c

PSOURCES	=	$(ROOT)/main.cpp \
				graphics/kfont16.cpp \
				common/stdapi.cpp

USER_LIBS	=	supc++ m

USER_DEFS	=	FAT_FS FAT_FS_NUM=4

INC_APP		=	. ../ ../../ \
				../emu ../emu/cpu ../emu/nes ../emu/mappers ../emu/sndhrdw ../emu/libsnss

AS_OPT		=

CP_OPT		=	-Wall -Werror \
				-Wno-unused-variable \
				-Wno-unused-function \
				-Wno-stringop-truncation \
				-fno-exceptions

CC_OPT		=	-Wall -Werror \
				-Wno-unused-variable \
				-Wno-unused-function \
				-Wno-maybe-uninitialized \
				-Wno-unused-but-set-variable \
				-Wno-strict-aliasing \
				-Wno-stringop-truncation \
				-fno-exceptions

ifeq ($(BUILD),debug)
    CC_OPT += -g -DDEBUG
    CP_OPT += -g -DDEBUG
	OPTIMIZE = -O0
endif

ifeq ($(BUILD),release)
    CC_OPT += -DNDEBUG
    CP_OPT += -DNDEBUG
	OPTIMIZE = -O3
endif

-include ../../common/makefile

-include $(DEPENDS)
