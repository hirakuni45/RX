# -*- tab-width : 4 -*-
#=======================================================================
#   @file
#   @brief  RX microcontroller share Makefile
#   @author 平松邦仁 (hira@rvf-rc45.net)
#	@copyright	Copyright (C) 2021, 2024 Kunihito Hiramatsu @n
#				Released under the MIT license @n
#				https://github.com/hirakuni45/RX/blob/master/LICENSE
#=======================================================================
#  GNU-RX 8.3.0 202305 specific command line options:
#  --mbig-endian-data
#  --mlittle-endian-data [default]
#  --m32bit-doubles [default]
#  --m64bit-doubles
#  --muse-conventional-section-names
#  --muse-renesas-section-names [default]
#  --msmall-data-limit
#  --mrelax
#  --mpid
#  --mint-register=<value>
#  --mcpu=<rx100|rx200|rx230|rx600|rx610|rx64m|rx66T|rx71m|rx72T>
#  --misa=<v1|v2|v3>
#  --mno-allow-string-insns  --mgcc-abi
#  --mrx-abi [default]
#  -mtfu-version=      Specify RX TFU version.
#  -mtfu=              Enable the use of RX TFU instructions.
#=======================================================================

# System include path for each environment
ifeq ($(OS),Windows_NT)
SYSTEM := WIN
# C++.boost root
LOCAL_PATH  =   /c/boost_1_74_0
else
  UNAME := $(shell uname -s)
  ifeq ($(UNAME),Linux)
    SYSTEM := LINUX
    LOCAL_PATH = /usr/local/include
  endif
  ifeq ($(UNAME),Darwin)
    SYSTEM := OSX
    OSX_VER := $(shell sw_vers -productVersion | sed 's/^\([0-9]*.[0-9]*\).[0-9]*/\1/')
    LOCAL_PATH = /opt/local/include
  endif
endif

# Add default C++ source
ifeq ($(findstring common/stdapi.cpp,$(PSOURCES)),)
  PSOURCES += common/stdapi.cpp
endif

LIB_ROOT    =   ../../rxlib/lib

INC_SYS     =   ../../rxlib/include $(LOCAL_PATH)

# rx_prog erase command
PROG_ERASE = --erase
# rx_prog verify command
PROG_VERIFY = --verify
PROG_OPT =

ifeq ($(RX_DEF),SIG_RX110)
  RX_CPU = RX110
  RX_CHOOSE = -mcpu=rx100
  AS_OPT	+=	--defsym NO_FLOAT=1
  LDSCRIPT	= ../../RX110/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX111)
  RX_CPU = RX111
  RX_CHOOSE = -mcpu=rx100
  TFU_DEF	= -nofpu
  AS_OPT	+=	--defsym NO_FLOAT=1
  LDSCRIPT	= ../../RX111/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX113)
  RX_CPU = RX113
  RX_CHOOSE = -mcpu=rx100
  TFU_DEF	= -nofpu
  AS_OPT	+=	--defsym NO_FLOAT=1
  LDSCRIPT	= ../../RX113/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX13T)
  RX_CPU = RX13T
  RX_CHOOSE = -misa=v1
  LDSCRIPT	= ../../RX13T/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX130)
  RX_CPU = RX130
  RX_CHOOSE = -mcpu=rx100
  TFU_DEF	= -nofpu
  AS_OPT	+=	--defsym NO_FLOAT=1
  LDSCRIPT	= ../../RX130/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX140)
  RX_CPU = RX140
  RX_CHOOSE = -mcpu=rx140
  LDSCRIPT	= ../../RX140/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX210)
  RX_CPU = RX210
  RX_CHOOSE = -mcpu=rx200
  TFU_DEF	= -nofpu
  AS_OPT	+=	--defsym NO_FLOAT=1
  LDSCRIPT	= ../../RX210/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX220)
  RX_CPU = RX220
  RX_CHOOSE = -mcpu=rx200
  TFU_DEF	= -nofpu
  MCU_TARGET = -nofpu
  AS_OPT	+=	--defsym NO_FLOAT=1
  LDSCRIPT	= ../../RX220/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX230)
  RX_CPU = RX230
  RX_CHOOSE = -mcpu=rx230
  LDSCRIPT	= ../../RX231/$(DEVICE).ld
  PROG_OPT = --write-page-wait=30000 --erase-page-wait=10000
endif

ifeq ($(RX_DEF),SIG_RX231)
  RX_CPU = RX231
  RX_CHOOSE = -mcpu=rx230
  LDSCRIPT	= ../../RX231/$(DEVICE).ld
  PROG_OPT = --write-page-wait=30000 --erase-page-wait=10000
endif

ifeq ($(RX_DEF),SIG_RX23W)
  RX_CPU = RX23W
  RX_CHOOSE = -mcpu=rx230
  LDSCRIPT	= ../../RX23W/$(DEVICE).ld
#  PROG_OPT = --write-page-wait=15000 --erase-page-wait=5000
endif

ifeq ($(RX_DEF),SIG_RX23T)
  RX_CPU = RX23T
  RX_CHOOSE = -misa=v2
  LDSCRIPT	= ../../RX23T/$(DEVICE).ld
  PROG_OPT = --write-page-wait=10000 --erase-page-wait=5000
endif

ifeq ($(RX_DEF),SIG_RX24T)
  RX_CPU = RX24T
  RX_CHOOSE = -misa=v2
  LDSCRIPT	= ../../RX24T/$(DEVICE).ld
  PROG_OPT = --write-page-wait=10000 --erase-page-wait=5000
endif

ifeq ($(RX_DEF),SIG_RX24U)
  RX_CPU = RX24U
  RX_CHOOSE = -misa=v2
  LDSCRIPT	= ../../RX24U/$(DEVICE).ld
  PROG_OPT = --write-page-wait=10000 --erase-page-wait=5000
endif

ifeq ($(RX_DEF),SIG_RX260)
  RX_CPU = RX260
  RX_CHOOSE = -misa=v3
  LDSCRIPT	= ../../RX26x/$(DEVICE).ld
#  PROG_OPT = --write-page-wait=2500
endif

ifeq ($(RX_DEF),SIG_RX261)
  RX_CPU = RX261
  RX_CHOOSE = -misa=v3
  LDSCRIPT	= ../../RX26x/$(DEVICE).ld
#  PROG_OPT = --write-page-wait=2500
endif

ifeq ($(RX_DEF),SIG_RX26T)
  RX_CPU = RX26T
  RX_CHOOSE = -misa=v3
  # TFU_DEF	= -mtfu-version=v2 -mtfu=intrinsic,mathlib
  TFU_DEF	= -mtfu-version=v2 -mtfu=intrinsic
  LDSCRIPT	= ../../RX26T/$(DEVICE).ld
  PROG_OPT = --write-page-wait=2500
endif

ifeq ($(RX_DEF),SIG_RX63T)
  RX_CPU = RX63T
  RX_CHOOSE = -misa=v1
  LDSCRIPT	= ../../RX63T/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX63T_S)
# 64/48 pin package
  RX_CPU = RX63T
  RX_CHOOSE = -misa=v1
  LDSCRIPT	= ../../RX63T/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX621)
  RX_CPU = RX621
  RX_CHOOSE = -misa=v1
  LDSCRIPT	= ../../RX62x/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX62N)
  RX_CPU = RX62N
  RX_CHOOSE = -misa=v1
  LDSCRIPT	= ../../RX62x/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX631)
  RX_CPU = RX631
  RX_CHOOSE = -misa=v1
  LDSCRIPT	= ../../RX63x/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX63N)
  RX_CPU = RX63N
  RX_CHOOSE = -misa=v1
  LDSCRIPT	= ../../RX63x/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX64M)
  RX_CPU = RX64M
  RX_CHOOSE = -mcpu=rx64m
  LDSCRIPT	= ../../RX64M/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX71M)
  RX_CPU = RX71M
  AS_OPT	+=	--defsym MEMWAIT=1
  RX_CHOOSE = -mcpu=rx71m
  LDSCRIPT	= ../../RX71M/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX65N)
  RX_CPU = RX65N
  LIB_ROOT += ../../RX600/drw2d
  INC_APP +=  ../../RX600/drw2d/inc/tes
  USER_LIBS += drw2d
  RX_CHOOSE = -misa=v2
  LDSCRIPT	= ../../RX65x/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX66N)
  RX_CPU = RX66N
  LIB_ROOT += ../../RX600/drw2d
  INC_APP +=  ../../RX600/drw2d/inc/tes
  USER_LIBS += drw2d
  RX_CHOOSE = -misa=v3
  # TFU_DEF	= -mtfu-version=v1 -mtfu=intrinsic,mathlib
  TFU_DEF	= -mtfu-version=v1 -mtfu=intrinsic
  LDSCRIPT	= ../../RX66N/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX660)
  RX_CPU = RX660
  RX_CHOOSE = -misa=v3
# TFU_DEF	= -mtfu-version=v1 -mtfu=intrinsic,mathlib
  TFU_DEF	= -mtfu-version=v1 -mtfu=intrinsic
  LDSCRIPT	= ../../RX660/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX671)
  RX_CPU = RX671
  RX_CHOOSE = -misa=v3
# TFU_DEF	= -mtfu-version=v1 -mtfu=intrinsic,mathlib
  TFU_DEF	= -mtfu-version=v1 -mtfu=intrinsic
  LDSCRIPT	= ../../RX671/$(DEVICE).ld
endif

# The RX66T cpu does not support the 'SAVE' and 'RSTR' instructions.
ifeq ($(RX_DEF),SIG_RX66T)
  RX_CPU = RX66T
  RX_CHOOSE = -mcpu=rx66T
  LDSCRIPT	= ../../RX66T/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX72T)
  RX_CPU = RX72T
  RX_CHOOSE = -mcpu=rx72T
  # TFU_DEF	= -mtfu-version=v1 -mtfu=intrinsic,mathlib
  TFU_DEF	= -mtfu-version=v1 -mtfu=intrinsic
  LDSCRIPT	= ../../RX72T/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX72N)
  RX_CPU = RX72N
  LIB_ROOT += ../../RX600/drw2d
  INC_APP +=  ../../RX600/drw2d/inc/tes
  USER_LIBS += drw2d
  RX_CHOOSE = -misa=v3
  # TFU_DEF	= -mtfu-version=v1 -mtfu=intrinsic,mathlib
  TFU_DEF	= -mtfu-version=v1 -mtfu=intrinsic
  LDSCRIPT	= ../../RX72N/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX72M)
  RX_CPU = RX72M
  LIB_ROOT += ../../RX600/drw2d
  INC_APP +=  ../../RX600/drw2d/inc/tes
  USER_LIBS += drw2d
  RX_CHOOSE = -misa=v3
  # TFU_DEF	= -mtfu-version=v1 -mtfu=intrinsic,mathlib
  TFU_DEF	= -mtfu-version=v1 -mtfu=intrinsic
  LDSCRIPT	= ../../RX72M/$(DEVICE).ld
endif

# Renesas GNU-RX gcc compiler version check
TARGET_ISA_TEXT := $(shell rx-elf-gcc --target-help | grep ISA)

# Renesas GNU-RX (8.3.0) compiler 
ifeq ($(TARGET_ISA_TEXT),)
  # for plain gcc-7.5.0 current gcc source build
  AS_DEFS	+=	-mcpu=rx600
  CC_DEFS	+=	-mcpu=rx600 -Wa,-mcpu=rxv2
  CP_DEFS	+=	-mcpu=rx600
else # Renesas GNU-RX gcc-8.3.0
  AS_DEFS	+=	$(RX_CHOOSE)
  CC_DEFS	+=	$(RX_CHOOSE) $(TFU_DEF)
  CP_DEFS	+=	$(RX_CHOOSE) $(TFU_DEF)
endif

SYSINCS		=	$(addprefix -I, $(INC_SYS))
APPINCS		=	$(addprefix -I, $(INC_APP))
AINCS		=	$(SYSINCS) $(APPINCS)
CINCS		=	$(SYSINCS) $(APPINCS)
PINCS		=	$(SYSINCS) $(APPINCS)
LIBINCS		=	$(addprefix -L, $(LIB_ROOT))
DEFS		=	$(addprefix -D, $(USER_DEFS))
DEFS	   +=	$(addprefix -D, $(RX_DEF))
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

AFLAGS		=	$(AS_OPT) $(AS_DEFS)
CFLAGS		=	-std=gnu99 $(CC_OPT) $(OPTIMIZE) $(CC_DEFS) $(DEFS)
PFLAGS		=	-std=c++17 $(CP_OPT) $(OPTIMIZE) $(CP_DEFS) $(DEFS)
FLAGS		= $(AS_OPT)$(AS_DEFS)$(CC_OPT)$(CP_OPT)$(OPTIMIZE)$(CC_DEFS)$(CP_DEFS)$(DEFS)

# FLAGS_CMP := $(shell cat $(TARGET).opt)

override LDFLAGS = $(MCU_TARGET) -nostartfiles -Wl,-Map,$(TARGET).map -T $(LDSCRIPT)

OBJCOPY_OPT	=	--srec-forceS3 --srec-len 32

OBJECTS	=	$(addprefix $(BUILD)/,$(patsubst %.s,%.o,$(ASOURCES))) \
			$(addprefix $(BUILD)/,$(patsubst %.c,%.o,$(CSOURCES))) \
			$(addprefix $(BUILD)/,$(patsubst %.cpp,%.o,$(PSOURCES)))

DOBJECTS =	$(addprefix $(BUILD)/,$(patsubst %.c,%.o,$(CSOURCES))) \
			$(addprefix $(BUILD)/,$(patsubst %.cpp,%.o,$(PSOURCES)))

DEPENDS =   $(patsubst %.o,%.d, $(DOBJECTS))

# all, clean: optional make command
.PHONY: all clean clean_depend run text
.SUFFIXES :
.SUFFIXES : .hpp .s .h .c .cpp .d .o

all: $(BUILD) $(TARGET).elf text

$(TARGET).elf: $(OBJECTS) $(LDSCRIPT) Makefile ../../common/makefile
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

$(BUILD)/%.d: %.c Makefile ../../common/makefile
	mkdir -p $(dir $@); \
	$(CC) -MM -DDEPEND_ESCAPE $(COPT) $(CFLAGS) $(APPINCS) $< \
	| sed 's/$(notdir $*)\.o:/$(subst /,\/,$(patsubst %.d,%.o,$@) $@):/' > $@ ; \
	[ -s $@ ] || rm -f $@

$(BUILD)/%.d: %.cpp Makefile ../../common/makefile
	mkdir -p $(dir $@); \
	$(CP) -MM -DDEPEND_ESCAPE $(POPT) $(PFLAGS) $(APPINCS) $< \
	| sed 's/$(notdir $*)\.o:/$(subst /,\/,$(patsubst %.d,%.o,$@) $@):/' > $@ ; \
	[ -s $@ ] || rm -f $@

clean:
	rm -rf $(BUILD) $(TARGET).elf $(TARGET).mot $(TARGET).lst $(TARGET).map

clean_depend:
	rm -f $(DEPENDS)

lst: $(TARGET).lst

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

# Rules for building the .text rom images

text: mot lst

lst: $(TARGET).lst
mot: $(TARGET).mot
bin: $(TARGET).bin

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

%.mot: %.elf
	$(OBJCOPY) $(OBJCOPY_OPT) -O srec $< $@

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

# Serial Flash write 
run:
	$(MAKE)
	rx_prog -d $(RX_CPU) $(PROG_OPT) --progress $(PROG_ERASE) --write $(PROG_VERIFY) $(TARGET).mot
