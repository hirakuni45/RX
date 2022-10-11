# -*- tab-width : 4 -*-
#=======================================================================
#   @file
#   @brief  RX65N Makefile
#   @author 平松邦仁 (hira@rvf-rc45.net)
#	@copyright	Copyright (C) 2020, 2022 Kunihito Hiramatsu @n
#				Released under the MIT license @n
#				https://github.com/hirakuni45/RX/blob/master/LICENSE
#=======================================================================
TARGET		=	usb_sample

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
				r_usb/basic/src/driver/r_usb_cdataio.c \
				r_usb/basic/src/driver/r_usb_clibusbip.c \
				r_usb/basic/src/driver/r_usb_cstd_rtos.c \
				r_usb/basic/src/driver/r_usb_hbc.c \
				r_usb/basic/src/driver/r_usb_hcontrolrw.c \
				r_usb/basic/src/driver/r_usb_hdriver.c \
				r_usb/basic/src/driver/r_usb_hhubsys.c \
				r_usb/basic/src/driver/r_usb_hintfifo.c \
				r_usb/basic/src/driver/r_usb_hinthandler_usbip0.c \
				r_usb/basic/src/driver/r_usb_hinthandler_usbip1.c \
				r_usb/basic/src/driver/r_usb_hlibusbip.c \
				r_usb/basic/src/driver/r_usb_hmanager.c \
				r_usb/basic/src/driver/r_usb_hscheduler.c \
				r_usb/basic/src/driver/r_usb_hsignal.c \
				r_usb/basic/src/driver/r_usb_hstdfunction.c \
				r_usb/basic/src/driver/r_usb_pbc.c \
				r_usb/basic/src/driver/r_usb_pcontrolrw.c \
				r_usb/basic/src/driver/r_usb_pdriver.c \
				r_usb/basic/src/driver/r_usb_pintfifo.c \
				r_usb/basic/src/driver/r_usb_pinthandler_usbip0.c \
				r_usb/basic/src/driver/r_usb_plibusbip.c \
				r_usb/basic/src/driver/r_usb_psignal.c \
				r_usb/basic/src/driver/r_usb_pstdfunction.c \
				r_usb/basic/src/driver/r_usb_pstdrequest.c \
				r_usb/basic/src/driver/r_usb_usbif_api.c \
				r_usb/basic/src/hw/r_usb_rx_mcu.c \
				r_usb/basic/src/hw/r_usb_creg_abs.c \
				r_usb/basic/src/hw/r_usb_dma.c \
				r_usb/basic/src/hw/r_usb_hostelectrical.c \
				r_usb/basic/src/hw/r_usb_preg_abs.c \
				r_usb/basic/src/hw/r_usb_hreg_abs.c \
				r_usb/basic/src/hw/r_usb_creg_access.c \
				r_usb/basic/src/hw/r_usb_hreg_access.c \
				r_usb/basic/src/hw/r_usb_preg_access.c \
				r_usb/hmsc/src/r_usb_hmsc_api.c \
				r_usb/hmsc/src/r_usb_hmsc_driver.c \
				r_usb/hmsc/src/r_usb_hstorage_driver.c \
				r_usb/hhid/src/r_usb_hhid_driver.c \
				r_usb/hhid/src/r_usb_hhid_api.c

PSOURCES	=	main.cpp \
				common/stdapi.cpp

USER_LIBS	=	supc++

USER_DEFS	=	FAT_FS FAT_FS_NUM=16

INC_APP		=	. ../ ../../ \
				../../r_usb/basic ../../r_usb/basic/src/hw/inc ../../r_usb/basic/src/driver/inc \
				../../r_usb/hmsc ../../r_usb/hmsc/src/inc \
				../../r_usb/hhid ../../r_usb/hhid/src/inc

AS_OPT		=

CC_OPT		=	-Wall -Werror \
				-Wno-unused-variable -Wno-uninitialized \
				-Wno-unused-function \
				-Wno-maybe-uninitialized \
				-Wno-unused-but-set-variable \
				-Wno-strict-aliasing \
				-Wno-sizeof-pointer-memaccess \
				-Wno-array-bounds \
				-Wno-stringop-truncation \
				-fno-exceptions

CP_OPT		=	-Wall -Werror \
				-Wno-unused-variable \
				-Wno-unused-function \
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
