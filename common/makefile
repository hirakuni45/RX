# -*- tab-width : 4 -*-
#=======================================================================
#   @file
#   @brief  RX microcontroller share Makefile
#   @author 平松邦仁 (hira@rvf-rc45.net)
#	@copyright	Copyright (C) 2021 Kunihito Hiramatsu @n
#				Released under the MIT license @n
#				https://github.com/hirakuni45/RX/blob/master/LICENSE
#=======================================================================

# System include path for each environment
ifeq ($(OS),Windows_NT)
SYSTEM := WIN
# C++.boost root
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

LIB_ROOT    =   ../../rxlib/lib

INC_SYS     =   ../../rxlib/include $(LOCAL_PATH)/include

PROG_VERIFY = --verify

ifeq ($(RX_DEF),SIG_RX24T)
  RX_CPU = RX24T
  RX_OPT = v2
  LDSCRIPT	=	../../RX24T/$(DEVICE).ld
  PROG_VERIFY =
endif

ifeq ($(RX_DEF),SIG_RX64M)
  RX_CPU = RX64M
  RX_OPT = v2
  LDSCRIPT	=	../../RX64M/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX71M)
  AS_OPT	+=	--defsym MEMWAIT=1
  RX_CPU = RX71M
  RX_OPT = v2
  LDSCRIPT	=	../../RX71M/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX65N)
  LIB_ROOT += ../../RX600/drw2d
  INC_APP +=  ../../RX600/drw2d/inc/tes
  USER_LIBS += drw2d
  RX_CPU = RX65N
  RX_OPT = v2
  LDSCRIPT	=	../../RX65x/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX66T)
  RX_CPU = RX66T
  RX_OPT = v3
  LDSCRIPT	=	../../RX66T/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX72T)
  RX_CPU = RX72T
  RX_OPT = v3
  LDSCRIPT	=	../../RX72T/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX72N)
  LIB_ROOT += ../../RX600/drw2d
  INC_APP +=  ../../RX600/drw2d/inc/tes 
  USER_LIBS += drw2d
  RX_CPU = RX72N
  RX_OPT = v3
  LDSCRIPT	=	../../RX72N/$(DEVICE).ld
endif

ifeq ($(RX_DEF),SIG_RX72M)
  LIB_ROOT += ../../RX600/drw2d
  INC_APP +=  ../../RX600/drw2d/inc/tes
  USER_LIBS += drw2d
  RX_CPU = RX72M
  RX_OPT = v3
  LDSCRIPT	=	../../RX72M/$(DEVICE).ld
endif

# Renesas GNU-RX gcc compiler version check
TARGET_ISA_TEXT := $(shell rx-elf-gcc --target-help | grep ISA)

# Renesas GNU-RX (8.3.0) compiler 
ifeq ($(TARGET_ISA_TEXT),)
  # for gcc-7.5.0 current gcc source build
  AS_DEFS		=	-mcpu=rx600
  CC_DEFS		=	-mcpu=rx600 -Wa,-mcpu=rxv2
  CP_DEFS		=	-mcpu=rx600
else # Renesas GNU-RX gcc 8.3.0
  AS_DEFS		=	-misa=$(RX_OPT)
  CC_DEFS		=	-misa=$(RX_OPT)
  CP_DEFS		=	-misa=$(RX_OPT)
endif

SYSINCS		=	$(addprefix -I, $(INC_SYS))
APPINCS		=	$(addprefix -I, $(INC_APP))
AINCS		=	$(SYSINCS) $(APPINCS)
CINCS		=	$(SYSINCS) $(APPINCS)
PINCS		=	$(SYSINCS) $(APPINCS)
LIBINCS		=	$(addprefix -L, $(LIB_ROOT))
DEFS		=	$(addprefix -D, $(USER_DEFS))
DEFS	  +=	$(addprefix -D, $(RX_DEF))
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
FLAGS		= $(AS_OPT) $(AS_DEFS) $(CC_OPT) $(CP_OPT) $(OPTIMIZE) $(CC_DEFS) $(CP_DEFS) $(DEFS)

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

# $(TARGET).opt: $(TARGET).elf
#ifeq ($(FLAGS),$(FLAGS_CMP))
#	@echo "eq..."
#else
#	@echo $(FLAGS) > $(TARGET).opt
#	@echo "not eq..."
#	@echo $(FLAGS)
#	@echo $(FLAGS_CMP)
#endif

# Serial Flash write 
run:
	$(MAKE)
	rx_prog -d $(RX_CPU) --progress --erase --write $(PROG_VERIFY) $(TARGET).mot
