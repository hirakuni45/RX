# -*- tab-width : 4 -*-
#=======================================================================
#	RX220 Makefile
#   @author 平松邦仁 (hira@rvf-rc45.net)
#	@copyright	Copyright (C) 2022, 2023 Kunihito Hiramatsu @n
#				Released under the MIT license @n
#				https://github.com/hirakuni45/RX/blob/master/LICENSE
#=======================================================================
TARGET		=	rtos_sample

DEVICE		=	R5F52206

RX_DEF		=	SIG_RX220

BUILD		=	release
# BUILD		=	debug

VPATH		=	../../

ASOURCES	=	common/start.s

CSOURCES	=	common/init.c \
				common/vect.c \
				common/syscalls.c \
				FreeRTOS/Source/portable/GCC/RX200/port.c \
				FreeRTOS/Source/portable/MemMang/heap_1.c \
				FreeRTOS/Source/event_groups.c \
				FreeRTOS/Source/list.c \
				FreeRTOS/Source/queue.c \
				FreeRTOS/Source/stream_buffer.c \
				FreeRTOS/Source/tasks.c \
				FreeRTOS/Source/timers.c

PSOURCES	=	FreeRTOS/main.cpp

USER_LIBS	=

USER_DEFS   +=	RTOS RTOS_HEAP_SIZE=10

INC_APP		=	. ../ ../../ \
				../../FreeRTOS/Source/include \
				../../FreeRTOS/Source/portable/GCC/RX200

AS_OPT		=	--defsym NOT_USER=1

CP_OPT		=	-Wall -Werror \
				-Wno-unused-variable \
				-Wno-unused-function \
				-fno-exceptions

CC_OPT		=	-Wall -Werror \
				-Wno-implicit-function-declaration \
				-Wno-unused-function \
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
