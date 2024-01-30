# -*- tab-width : 4 -*-
#=======================================================================
#   @file
#   @brief  RX71M Makefile
#   @author 平松邦仁 (hira@rvf-rc45.net)
#	@copyright	Copyright (C) 2020, 2023 Kunihito Hiramatsu @n
#				Released under the MIT license @n
#				https://github.com/hirakuni45/RX/blob/master/LICENSE
#=======================================================================
TARGET		=	rtos_tcp_sample

DEVICE		=	R5F571ML

RX_DEF		=	SIG_RX71M

BUILD		=	release
# BUILD		=	debug

VPATH		=	../../

ASOURCES	=	common/start.s

CSOURCES	=	common/init.c \
				common/vect.c \
				common/syscalls.c \
				FreeRTOS/Source/portable/GCC/RX600v2/port.c \
				FreeRTOS/Source/portable/MemMang/heap_3.c \
				FreeRTOS/Source/event_groups.c \
				FreeRTOS/Source/list.c \
				FreeRTOS/Source/queue.c \
				FreeRTOS/Source/stream_buffer.c \
				FreeRTOS/Source/tasks.c \
				FreeRTOS/Source/timers.c

#				FreeRTOS_TCP/source/FreeRTOS_ARP.c \
				FreeRTOS_TCP/source/FreeRTOS_DHCP.c \
				FreeRTOS_TCP/source/FreeRTOS_DNS.c \
				FreeRTOS_TCP/source/FreeRTOS_DNS_Cache.c \
				FreeRTOS_TCP/source/FreeRTOS_DNS_Callback.c \
				FreeRTOS_TCP/source/FreeRTOS_DNS_Networking.c \
				FreeRTOS_TCP/source/FreeRTOS_DNS_Parser.c \
				FreeRTOS_TCP/source/FreeRTOS_ICMP.c \
				FreeRTOS_TCP/source/FreeRTOS_IP.c \
				FreeRTOS_TCP/source/FreeRTOS_IP_Timers.c \
				FreeRTOS_TCP/source/FreeRTOS_IP_Utils.c \
				FreeRTOS_TCP/source/FreeRTOS_Sockets.c \
				FreeRTOS_TCP/source/FreeRTOS_Stream_Buffer.c \
				FreeRTOS_TCP/source/FreeRTOS_TCP_IP.c \
				FreeRTOS_TCP/source/FreeRTOS_TCP_Reception.c \
				FreeRTOS_TCP/source/FreeRTOS_TCP_State_Handling.c \
				FreeRTOS_TCP/source/FreeRTOS_TCP_Transmission.c \
				FreeRTOS_TCP/source/FreeRTOS_TCP_Utils.c \
				FreeRTOS_TCP/source/FreeRTOS_TCP_WIN.c \
				FreeRTOS_TCP/source/FreeRTOS_Tiny_TCP.c \
				FreeRTOS_TCP/source/FreeRTOS_UDP_IP.c \
				FreeRTOS_TCP/source/portable/BufferManagement/BufferAllocation_2.c \
				FreeRTOS_TCP/source/portable/NetworkInterface/RX/ether_callback.c \
				FreeRTOS_TCP/source/portable/NetworkInterface/RX/NetworkInterface.c \
				FreeRTOS_TCP/r_ether_rx/src/phy/phy.c \
				FreeRTOS_TCP/r_ether_rx/src/r_ether_rx.c

PSOURCES	=	FreeRTOS_TCP/main.cpp

USER_LIBS	=

USER_DEFS	=	RTOS

INC_APP		=	. ../ ../../ \
				../../FreeRTOS/Source/include \
				../../FreeRTOS/Source/portable/GCC/RX600v2 \
				../../FreeRTOS_TCP/r_ether_rx \
				../../FreeRTOS_TCP/source/portable/Compiler/GCC \
				../../FreeRTOS_TCP/source/include

# RTOS を使う場合指定
AS_OPT		=	--defsym NOT_USER=1

CC_OPT		=	-Wall -Werror \
				-Wno-implicit-function-declaration \
				-Wno-unused-function \
				-Wno-unused-variable \
				-Wno-unused-but-set-variable \
				-fno-exceptions

CP_OPT		=	-Wall -Werror \
				-Wno-unused-variable \
				-Wno-unused-function \
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
