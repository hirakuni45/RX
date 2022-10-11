# -*- tab-width : 4 -*-
#=======================================================================
#   @file
#   @brief  RX64M Makefile
#   @author 平松邦仁 (hira@rvf-rc45.net)
#	@copyright	Copyright (C) 2020, 2022 Kunihito Hiramatsu @n
#				Released under the MIT license @n
#				https://github.com/hirakuni45/RX/blob/master/LICENSE
#=======================================================================
TARGET		=	efo_sample

DEVICE		=	R5F564MF

RX_DEF		=	SIG_RX64M

BUILD		=	release
# BUILD		=	debug

BUILD_ID	=	$(shell date +%Y%m%d%H)

VPATH		=	../../

ASOURCES	=	common/start.s

CSOURCES	=	common/init.c \
				common/vect.c \
				common/syscalls.c

PSOURCES	=	main.cpp \
				common/stdapi.cpp

USER_LIBS	=	supc++ m

# USER_DEFS	=	SIG_RX64M \
#				F_ICLK=118750000 \
#				F_PCLKA=118750000 F_PCLKB=59375000 F_PCLKC=59375000 F_PCLKD=59375000 \
#				F_FCLK=59375000 F_BCLK=118750000 \		

USER_DEFS	=	B_ID=$(BUILD_ID) EFO_CLOCK_DEF

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
