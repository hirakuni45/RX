# -*- tab-width : 4 -*-
#=======================================================================
#   @file
#   @brief  RX71M Makefile
#   @author 平松邦仁 (hira@rvf-rc45.net)
#	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
#				Released under the MIT license @n
#				https://github.com/hirakuni45/RX/blob/master/LICENSE
#=======================================================================
TARGET		=	lcd_sample

DEVICE		=	R5F571ML

RX_DEF		=	SIG_RX71M

BUILD		=	release

VPATH		=	../../

ASOURCES	=	common/start.s

CSOURCES	=	common/init.c \
				common/vect.c \
				common/syscalls.c

PSOURCES	=	main.cpp

USER_LIBS	=	m

USER_DEFS	=

INC_APP		=	. ../../

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
