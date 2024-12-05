# -*- tab-width : 4 -*-
#=======================================================================
#	RX24T Makefile
#   @author 平松邦仁 (hira@rvf-rc45.net)
#	@copyright	Copyright (C) 2018, 2024 Kunihito Hiramatsu @n
#				Released under the MIT license @n
#				https://github.com/hirakuni45/RX/blob/master/LICENSE
#=======================================================================
TARGET		=	adc_sample

DEVICE		=	R5F524TA

RX_DEF		=	SIG_RX24T

BUILD		=	release
# BUILD		=	debug

VPATH		=	../../

ASOURCES	=	common/start.s

CSOURCES	=	common/init.c \
				common/vect.c \
				common/syscalls.c

PSOURCES	=	ADC_sample/main.cpp

USER_LIBS	=	supc++

USER_DEFS   =

INC_APP		=	. ../ ../../

AS_OPT		=

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
