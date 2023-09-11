# -*- tab-width : 4 -*-
#=======================================================================
#   @file
#   @brief  RX71M Makefile
#   @author 平松邦仁 (hira@rvf-rc45.net)
#	@copyright	Copyright (C) 2019, 2022 Kunihito Hiramatsu @n
#				Released under the MIT license @n
#				https://github.com/hirakuni45/RX/blob/master/LICENSE
#=======================================================================
TARGET		=	http_sample

DEVICE		=	R5F571ML

RX_DEF		=	SIG_RX71M

FATFS_VER	=	ff14/source

BUILD		=	release
# BUILD		=	debug

VPATH		=	../../

ASOURCES	=	common/start.s \
				r_net/driver/cksum_rx_little.s

CSOURCES	=	common/init.c \
				common/vect.c \
				common/syscalls.c \
				$(FATFS_VER)/ff.c \
				$(FATFS_VER)/ffsystem.c \
				$(FATFS_VER)/ffunicode.c \
				common/time.c \
                r_net/r_byteq_v1.30/r_byteq.c \
                r_net/driver/phy.c \
                r_net/driver/r_ether.c \
                r_net/driver/driver.c \
				r_net/T4_src/r_dhcp_client.c \
                r_net/T4_src/config_tcpudp.c \
                r_net/T4_src/ether.c \
                r_net/T4_src/ip.c \
                r_net/T4_src/udp.c \
                r_net/T4_src/tcp.c \
                r_net/T4_src/tcp_api.c

#                r_net/T4_src/tcp2.c

#				FreeRTOS/Source/portable/GCC/RX600v2/port.c \
				FreeRTOS/Source/portable/MemMang/heap_4.c \
				FreeRTOS/Source/croutine.c \
				FreeRTOS/Source/event_groups.c \
				FreeRTOS/Source/list.c \
				FreeRTOS/Source/queue.c \
				FreeRTOS/Source/stream_buffer.c \
				FreeRTOS/Source/tasks.c \
				FreeRTOS/Source/timers.c

#				FreeRTOS_TCP/source/FreeRTOS_ARP.c \
				FreeRTOS_TCP/source/FreeRTOS_DHCP.c \
				FreeRTOS_TCP/source/FreeRTOS_DNS.c \
				FreeRTOS_TCP/source/FreeRTOS_IP.c \
				FreeRTOS_TCP/source/FreeRTOS_Sockets.c \
				FreeRTOS_TCP/source/FreeRTOS_Stream_Buffer.c \
				FreeRTOS_TCP/source/FreeRTOS_TCP_IP.c \
				FreeRTOS_TCP/source/FreeRTOS_TCP_WIN.c \
				FreeRTOS_TCP/source/FreeRTOS_UDP_IP.c

PSOURCES	=	main.cpp \
				r_net/ethernet.cpp \
				common/stdapi.cpp

USER_LIBS	=	supc++

# USER_DEFS	=	RTOS FAT_FS FAT_FS_NUM=4
USER_DEFS	=	FAT_FS FAT_FS_NUM=4

INC_APP		=	. ../../ \
				../../FreeRTOS/Source/include \
				../../FreeRTOS/Source/portable/GCC/RX600v2 \
				../../FreeRTOS_TCP \
				../../FreeRTOS_TCP/include \
				../../r_net

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
				-fno-exceptions

#				-Wno-strict-aliasing

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
