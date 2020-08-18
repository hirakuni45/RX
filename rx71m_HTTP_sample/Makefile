# -*- tab-width : 4 -*-
#=======================================================================
#   @file
#   @brief  RX71M Makefile
#   @author 平松邦仁 (hira@rvf-rc45.net)
#	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
#				Released under the MIT license @n
#				https://github.com/hirakuni45/RX/blob/master/LICENSE
#=======================================================================
TARGET		=	http_sample

DEVICE		=	R5F571ML

ROOT_DEV	=	RX71M

FATFS_VER	=	ff14/source

OPTIMIZE	=	-O3

BUILD		=	release

VPATH		=	../

ASOURCES	=	common/start.s \
				r_net/driver/cksum_rx_little.s

CSOURCES	=	common/init.c \
				common/vect.c \
				common/syscalls.c \
				$(FATFS_VER)/ff.c \
				$(FATFS_VER)/ffsystem.c \
				$(FATFS_VER)/ffunicode.c \
				common/time.c \
                r_net/driver/phy.c \
                r_net/driver/r_ether.c \
                r_net/r_byteq_v1.30/r_byteq.c \
                r_net/driver/driver.c \
                r_net/T4_src/config_tcpudp.c \
                r_net/T4_src/ether.c \
                r_net/T4_src/ip.c \
                r_net/T4_src/udp.c \
                r_net/T4_src/tcp.c \
                r_net/T4_src/tcp_api.c \
                r_net/T4_src/r_dhcp_client.c \
				FreeRTOS/Source/portable/GCC/RX600v2/port.c \
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

LDSCRIPT	=	../$(ROOT_DEV)/$(DEVICE).ld

USER_DEFS	=	SIG_$(ROOT_DEV) \
				F_ICLK=240000000 \
				F_PCLKA=120000000 F_PCLKB=60000000 F_PCLKC=60000000 F_PCLKD=60000000 \
				F_FCLK=60000000 F_BCLK=120000000 \
				RTOS FAT_FS FAT_FS_NUM=4

AS_DEFS		=	--defsym MEMWAIT=1 --defsym NOT_USER=1
# CC_DEFS		=	-mcpu=rx600 -Wa,-mcpu=rxv2
CC_DEFS		=	-mcpu=rx71m
# CP_DEFS		=	-mcpu=rx600
CP_DEFS		=	-mcpu=rx71m

# Include path for each environment
ifeq ($(OS),Windows_NT)
SYSTEM := WIN
LOCAL_PATH  =   /mingw64
else
  UNAME := $(shell uname -s)
  ifeq ($(UNAME),Linux)
    SYSTEM := LINUX
    LOCAL_PATH = /usr/local
  endif
  ifeq ($(UNAME),Darwin)
    SYSTEM := OSX
    OSX_VER := $(shell sw_vers -productVersion | sed 's/^\([0-9]*.[0-9]*\).[0-9]*/\1/')
    LOCAL_PATH = /opt/local
  endif
endif

INC_SYS     =   $(LOCAL_PATH)/include

INC_APP		=	. ../ \
				../FreeRTOS/Source/include \
				../FreeRTOS/Source/portable/GCC/RX600v2 \
				../FreeRTOS_TCP \
				../FreeRTOS_TCP/include \
				../r_net

LIB_ROOT	=

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

SYSINCS		=	$(addprefix -I, $(INC_SYS))
APPINCS		=	$(addprefix -I, $(INC_APP))
AINCS		=	$(SYSINCS) $(APPINCS)
CINCS		=	$(SYSINCS) $(APPINCS)
PINCS		=	$(SYSINCS) $(APPINCS)
LIBINCS		=	$(addprefix -L, $(LIB_ROOT))
DEFS		=	$(addprefix -D, $(USER_DEFS))
LIBS		=	$(addprefix -l, $(USER_LIBS))

# You should not have to change anything below here.
AS			=	rx-elf-as
CC			=	rx-elf-gcc
CP			=	rx-elf-g++
AR			=	rx-elf-ar
LD			=	rx-elf-ld
OBJCOPY		=	rx-elf-objcopy
OBJDUMP		=	rx-elf-objdump
SIZE		=	rx-elf-size

# Override is only needed by avr-lib build system.

AFLAGS		=	$(AS_OPT) $(AS_DEFS)
CFLAGS		=	-std=gnu99 $(CC_OPT) $(OPTIMIZE) $(CC_DEFS) $(DEFS)
PFLAGS		=	-std=c++17 $(CP_OPT) $(OPTIMIZE) $(CP_DEFS) $(DEFS)

override LDFLAGS = $(MCU_TARGET) -nostartfiles -Wl,-Map,$(TARGET).map -T $(LDSCRIPT)

OBJCOPY_OPT	=	--srec-forceS3 --srec-len 32

OBJECTS	=	$(addprefix $(BUILD)/,$(patsubst %.s,%.o,$(ASOURCES))) \
			$(addprefix $(BUILD)/,$(patsubst %.c,%.o,$(CSOURCES))) \
			$(addprefix $(BUILD)/,$(patsubst %.cpp,%.o,$(PSOURCES)))

DOBJECTS =	$(addprefix $(BUILD)/,$(patsubst %.c,%.o,$(CSOURCES))) \
			$(addprefix $(BUILD)/,$(patsubst %.cpp,%.o,$(PSOURCES)))

DEPENDS =   $(patsubst %.o,%.d, $(DOBJECTS))

.PHONY: all clean
.SUFFIXES :
.SUFFIXES : .rc .hpp .s .h .c .cpp .d .o

all: $(BUILD) $(TARGET).elf text

$(TARGET).elf: $(OBJECTS) $(LDSCRIPT) Makefile
	$(CC) $(LDFLAGS) $(LIBINCS) -o $@ $(OBJECTS) $(LIBS)
	$(SIZE) $@

$(BUILD)/%.o: %.s
	mkdir -p $(dir $@); \
	$(AS) -c $(AOPT) $(AFLAGS) $(AINCS) -o $@ $<

$(BUILD)/%.o : %.c
	mkdir -p $(dir $@); \
	$(CC) -c $(COPT) $(CFLAGS) $(CINCS) $(CCWARN) -o $@ $<

$(BUILD)/%.o : %.cpp
	mkdir -p $(dir $@); \
	$(CP) -c $(POPT) $(PFLAGS) $(PINCS) $(CPWARN) -o $@ $<

$(BUILD)/%.d: %.c
	mkdir -p $(dir $@); \
	$(CC) -MM -DDEPEND_ESCAPE $(COPT) $(CFLAGS) $(APPINCS) $< \
	| sed 's/$(notdir $*)\.o:/$(subst /,\/,$(patsubst %.d,%.o,$@) $@):/' > $@ ; \
	[ -s $@ ] || rm -f $@

$(BUILD)/%.d: %.cpp
	mkdir -p $(dir $@); \
	$(CP) -MM -DDEPEND_ESCAPE $(POPT) $(PFLAGS) $(APPINCS) $< \
	| sed 's/$(notdir $*)\.o:/$(subst /,\/,$(patsubst %.d,%.o,$@) $@):/' > $@ ; \
	[ -s $@ ] || rm -f $@

clean:
	rm -rf $(BUILD) $(TARGET).elf $(TARGET).mot $(TARGET).lst $(TARGET).map

clean_depend:
	rm -f $(DEPENDS)

lst:  $(TARGET).lst

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

# Rules for building the .text rom images

text: mot lst

bin: $(TARGET).bin
mot: $(TARGET).mot
lst: $(TARGET).lst

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

%.mot: %.elf
	$(OBJCOPY) $(OBJCOPY_OPT) -O srec $< $@

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@
#	$(OBJCOPY) -j .vects -j .text -j .data -O binary $< $@

tarball:
	tar cfvz $(subst .elf,,$(TARGET))_$(shell date +%Y%m%d%H).tgz \
	*.[hc]pp Makefile ../common/*/*.[hc]pp ../common/*/*.[hc]

bin_zip:
	$(LK) $(LFLAGS) $(LIBS) $(OBJECTS) $(ICON_OBJ) $(LIBN) -mwindows -o $(TARGET) 
	rm -f $(subst .exe,,$(TARGET))_$(shell date +%Y%m%d%H)_bin.zip
	zip $(subst .exe,,$(TARGET))_$(shell date +%Y%m%d%H)_bin.zip *.exe *.dll res/*.*

run:
	rx_prog -d $(ROOT_DEV) --progress --erase --write --verify $(TARGET).mot

-include $(DEPENDS)
