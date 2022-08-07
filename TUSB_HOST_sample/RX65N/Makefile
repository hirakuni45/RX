# -*- tab-width : 4 -*-
#=======================================================================
#   @file
#   @brief  RX65N Makefile
#   @author 平松邦仁 (hira@rvf-rc45.net)
#	@copyright	Copyright (C) 2020, 2021 Kunihito Hiramatsu @n
#				Released under the MIT license @n
#				https://github.com/hirakuni45/RX/blob/master/LICENSE
#=======================================================================
TARGET		=	tusb_host_sample

DEVICE		=	R5F565NE

RX_DEF		=	SIG_RX65N

BUILD		=	release
# BUILD		=	debug

VPATH		=	../../

ASOURCES	=	common/start.s

CSOURCES	=	common/init.c \
				common/vect.c \
				common/syscalls.c \
				tinyusb/src/tusb.c \
				tinyusb/src/common/tusb_fifo.c \
				tinyusb/src/device/usbd.c \
				tinyusb/src/device/usbd_control.c \
				tinyusb/src/class/audio/audio_device.c \
				tinyusb/src/class/cdc/cdc_device.c \
				tinyusb/src/class/dfu/dfu_device.c \
				tinyusb/src/class/dfu/dfu_rt_device.c \
				tinyusb/src/class/hid/hid_device.c \
				tinyusb/src/class/midi/midi_device.c \
				tinyusb/src/class/msc/msc_device.c \
				tinyusb/src/class/net/ecm_rndis_device.c \
				tinyusb/src/class/net/ncm_device.c \
				tinyusb/src/class/usbtmc/usbtmc_device.c \
				tinyusb/src/class/video/video_device.c \
				tinyusb/src/class/vendor/vendor_device.c \
				tinyusb/src/class/cdc/cdc_host.c \
				tinyusb/src/class/hid/hid_host.c \
				tinyusb/src/class/msc/msc_host.c \
				tinyusb/src/host/hub.c \
				tinyusb/src/host/usbh.c \
				tinyusb/src/portable/ohci/ohci.c \
				tinyusb/src/portable/renesas/usba/hcd_usba.c

PSOURCES	=	TUSB_HOST_sample/main.cpp

USER_LIBS	=

USER_DEFS	=	CFG_TUSB_MCU=OPT_MCU_RX65X

INC_APP		=	. ../ ../../ ../../tinyusb/src

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
