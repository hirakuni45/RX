# -*- tab-width : 4 -*-
#=======================================================================
#   @file
#   @brief  RX72N Makefile
#   @author 平松邦仁 (hira@rvf-rc45.net)
#	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
#				Released under the MIT license @n
#				https://github.com/hirakuni45/RX/blob/master/LICENSE
#=======================================================================
TARGET		=	SYNTH_sample

ROOT		=	synth_sample

DEVICE		=	R5F572NN

RX_DEF		=	SIG_RX72N

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
				common/time.c

PSOURCES	=	$(ROOT)/main.cpp \
				graphics/font8x16.cpp \
				graphics/kfont16.cpp \
				graphics/color.cpp \
				common/stdapi.cpp \
				sound/synth/dx7note.cpp \
				sound/synth/env.cpp \
				sound/synth/exp2.cpp \
				sound/synth/fir.cpp \
				sound/synth/fm_core.cpp \
				sound/synth/fm_op_kernel.cpp \
				sound/synth/freqlut.cpp \
				sound/synth/lfo.cpp \
				sound/synth/log2.cpp \
				sound/synth/patch.cpp \
				sound/synth/pitchenv.cpp \
				sound/synth/resofilter.cpp \
				sound/synth/ringbuffer.cpp \
				sound/synth/sawtooth.cpp \
				sound/synth/sin.cpp \
				sound/synth/synth_unit.cpp \
				sound/smf/MD_MIDIFile.cpp \
				sound/smf/MD_MIDITrack.cpp \
				sound/smf/MD_MIDIHelper.cpp

USER_LIBS	=	supc++ m

USER_DEFS	=	FAT_FS FAT_FS_NUM=4

INC_APP		=	. ../ ../../ ../../sound/smf

AS_OPT		=

CP_OPT		=	-Wall -Werror \
				-Wno-unused-variable \
				-Wno-unused-function \
				-fno-exceptions

CC_OPT		=	-Wall -Werror \
				-Wno-unused-variable \
				-Wno-unused-function \
				-Wno-maybe-uninitialized \
				-Wno-unused-but-set-variable \
				-Wno-strict-aliasing \
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
