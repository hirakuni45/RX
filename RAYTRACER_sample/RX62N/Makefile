# -*- tab-width : 4 -*-
#=======================================================================
#	RX62N Makefile
#   @author 平松邦仁 (hira@rvf-rc45.net)
#	@copyright	Copyright (C) 2022 Kunihito Hiramatsu @n
#				Released under the MIT license @n
#				https://github.com/hirakuni45/RX/blob/master/LICENSE
#=======================================================================
TARGET		=	raytracer_sample

# BlueBoard-RX62N_100pin
#DEVICE		=	R5F562N8
# FRK-RX62N (CQ出版)
DEVICE		=	R5F562N7
USER_DEFS	=	CQ_FRK

RX_DEF		=	SIG_RX62N

BUILD		=	release
# BUILD		=	debug

VPATH		=	../../

ASOURCES	=	common/start.s

CSOURCES	=	common/init.c \
				common/vect.c \
				common/syscalls.c

PSOURCES	=	RAYTRACER_sample/main.cpp

USER_LIBS	=	m

USER_DEFS   +=

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
