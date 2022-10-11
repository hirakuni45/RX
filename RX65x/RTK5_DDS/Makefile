# -*- tab-width : 4 -*-
#=======================================================================
#   @file
#   @brief  RX65N Makefile
#   @author 平松邦仁 (hira@rvf-rc45.net)
#	@copyright	Copyright (C) 2020, 2022 Kunihito Hiramatsu @n
#				Released under the MIT license @n
#				https://github.com/hirakuni45/RX/blob/master/LICENSE
#=======================================================================
TARGET		=	dds_sample

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
				common/time.c

PSOURCES	=	main.cpp \
				common/stdapi.cpp

USER_LIBS	=	supc++ drw2d

USER_DEFS	=	FAT_FS FAT_FS_NUM=2

INC_APP		=	. ../ ../../

AS_OPT		=

CP_OPT		=	-Wall -Werror \
				-Wno-unused-variable \
				-Wno-unused-function \
				-fno-exceptions

CC_OPT		=	-Wall -Werror \
				-Wno-unused-variable \
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
