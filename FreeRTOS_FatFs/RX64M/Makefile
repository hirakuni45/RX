# -*- tab-width : 4 -*-
#=======================================================================
#   @file
#   @brief  RX64M Makefile
#   @author 平松邦仁 (hira@rvf-rc45.net)
#	@copyright	Copyright (C) 2019, 2023 Kunihito Hiramatsu @n
#				Released under the MIT license @n
#				https://github.com/hirakuni45/RX/blob/master/LICENSE
#=======================================================================
TARGET		=	rtos_fatfs_sample

DEVICE		=	R5F564MF

RX_DEF		=	SIG_RX64M

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
				FreeRTOS/Source/portable/GCC/RX600v2/port.c \
				FreeRTOS/Source/portable/MemMang/heap_3.c \
				FreeRTOS/Source/event_groups.c \
				FreeRTOS/Source/list.c \
				FreeRTOS/Source/queue.c \
				FreeRTOS/Source/stream_buffer.c \
				FreeRTOS/Source/tasks.c \
				FreeRTOS/Source/timers.c

PSOURCES	=	FreeRTOS_FatFs/main.cpp \
				common/stdapi.cpp

USER_LIBS	=	supc++ mad

USER_DEFS	=	RTOS FAT_FS FAT_FS_NUM=4

INC_APP		=	. ../ ../../ \
				../../FreeRTOS/Source/include \
				../../FreeRTOS/Source/portable/GCC/RX600v2

AS_OPT		=	--defsym NOT_USER=1

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
