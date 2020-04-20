# -*- tab-width : 4 -*-
#=======================================================================
#   @file
#   @brief  RX65N Makefile
#   @author 平松邦仁 (hira@rvf-rc45.net)
#	@copyright	Copyright (C) 2020 Kunihito Hiramatsu @n
#				Released under the MIT license @n
#				https://github.com/hirakuni45/RX/blob/master/LICENSE
#=======================================================================
TARGET		=	nesemu

ROOT		=	NESEMU_sample

DEVICE		=	R5F565NE

ROOT_DEV	=	RX65N
ROOT_DEV_	=	RX65x

FATFS_VER	=	ff13c/source

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
				$(ROOT)/emu/log.c \
				$(ROOT)/emu/bitmap.c \
				$(ROOT)/emu/cpu/nes6502.c \
				$(ROOT)/emu/nes/mmclist.c \
				$(ROOT)/emu/nes/nes.c \
				$(ROOT)/emu/nes/nes_mmc.c \
				$(ROOT)/emu/nes/nes_pal.c \
				$(ROOT)/emu/nes/nes_ppu.c \
				$(ROOT)/emu/nes/nes_rom.c \
				$(ROOT)/emu/nes/nesinput.c \
				$(ROOT)/emu/nes/nesstate.c \
				$(ROOT)/emu/sndhrdw/fds_snd.c \
				$(ROOT)/emu/sndhrdw/mmc5_snd.c \
				$(ROOT)/emu/sndhrdw/nes_apu.c \
				$(ROOT)/emu/sndhrdw/vrcvisnd.c \
				$(ROOT)/emu/mappers/map000.c \
				$(ROOT)/emu/mappers/map001.c \
				$(ROOT)/emu/mappers/map002.c \
				$(ROOT)/emu/mappers/map003.c \
				$(ROOT)/emu/mappers/map004.c \
				$(ROOT)/emu/mappers/map005.c \
				$(ROOT)/emu/mappers/map007.c \
				$(ROOT)/emu/mappers/map008.c \
				$(ROOT)/emu/mappers/map009.c \
				$(ROOT)/emu/mappers/map011.c \
				$(ROOT)/emu/mappers/map015.c \
				$(ROOT)/emu/mappers/map016.c \
				$(ROOT)/emu/mappers/map018.c \
				$(ROOT)/emu/mappers/map019.c \
				$(ROOT)/emu/mappers/map024.c \
				$(ROOT)/emu/mappers/map032.c \
				$(ROOT)/emu/mappers/map033.c \
				$(ROOT)/emu/mappers/map034.c \
				$(ROOT)/emu/mappers/map040.c \
				$(ROOT)/emu/mappers/map041.c \
				$(ROOT)/emu/mappers/map042.c \
				$(ROOT)/emu/mappers/map046.c \
				$(ROOT)/emu/mappers/map050.c \
				$(ROOT)/emu/mappers/map064.c \
				$(ROOT)/emu/mappers/map065.c \
				$(ROOT)/emu/mappers/map066.c \
				$(ROOT)/emu/mappers/map070.c \
				$(ROOT)/emu/mappers/map073.c \
				$(ROOT)/emu/mappers/map075.c \
				$(ROOT)/emu/mappers/map078.c \
				$(ROOT)/emu/mappers/map079.c \
				$(ROOT)/emu/mappers/map085.c \
				$(ROOT)/emu/mappers/map087.c \
				$(ROOT)/emu/mappers/map093.c \
				$(ROOT)/emu/mappers/map094.c \
				$(ROOT)/emu/mappers/map099.c \
				$(ROOT)/emu/mappers/map160.c \
				$(ROOT)/emu/mappers/map229.c \
				$(ROOT)/emu/mappers/map231.c \
				$(ROOT)/emu/mappers/mapvrc.c \
				$(ROOT)/emu/libsnss/libsnss.c

PSOURCES	=	$(ROOT)/main.cpp \
				RX65x/icu_mgr.cpp \
				graphics/font8x16.cpp \
				graphics/kfont16.cpp \
				graphics/color.cpp \
				common/stdapi.cpp

USER_LIBS	=	m supc++

LDSCRIPT	=	../../$(ROOT_DEV_)/$(DEVICE).ld

USER_DEFS	=	SIG_$(ROOT_DEV) \
				F_ICLK=120000000 \
				F_PCLKA=120000000 F_PCLKB=60000000 F_PCLKC=60000000 F_PCLKD=60000000 \
				F_FCLK=60000000 F_BCLK=120000000 \
				FAT_FS FAT_FS_NUM=4

AS_DEFS		=
CC_DEFS		=	-mcpu=rx600 -Wa,-mcpu=rxv2
CP_DEFS		=	-mcpu=rx600

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

INC_APP		=	. ../ ../../ ../../RX600/drw2d/inc/tes \
				../emu ../emu/cpu ../emu/nes ../emu/mappers ../emu/sndhrdw ../emu/libsnss

CP_OPT		=	-Wall -Werror \
				-Wno-unused-variable \
				-Wno-unused-function \
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
