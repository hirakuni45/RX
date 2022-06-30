# -*- tab-width : 4 -*-
#=======================================================================
#   @file
#   @brief  RX72N Makefile
#   @author 平松邦仁 (hira@rvf-rc45.net)
#	@copyright	Copyright (C) 2020, 2022 Kunihito Hiramatsu @n
#				Released under the MIT license @n
#				https://github.com/hirakuni45/RX/blob/master/LICENSE
#=======================================================================
TARGET		=	rtos_sample

DEVICE		=	R5F572NN

RX_DEF		=	SIG_RX72N

BUILD		=	release
# BUILD		=	debug

VPATH		=	../../

ASOURCES	=	common/start.s

CSOURCES	=	common/init.c \
				common/vect.c \
				common/syscalls.c \
                FreeRTOS/Source/portable/GCC/RX700v3_DPFPU/port.c \
                FreeRTOS/Source/portable/MemMang/heap_3.c \
                FreeRTOS/Source/croutine.c \
                FreeRTOS/Source/event_groups.c \
                FreeRTOS/Source/list.c \
                FreeRTOS/Source/queue.c \
                FreeRTOS/Source/stream_buffer.c \
                FreeRTOS/Source/tasks.c \
                FreeRTOS/Source/timers.c

PSOURCES	=	FreeRTOS/main.cpp

USER_LIBS	=

USER_DEFS	=	RTOS

INC_APP		=	. ../../ ../ \
				../../FreeRTOS/Source/include \
				../../FreeRTOS/Source/portable/GCC/RX700v3_DPFPU \
				../../RX600/drw2d/inc/tes

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
