# -*- tab-width : 4 -*-
#=======================================================================
#   @file
#   @brief  DRW2D Makefile
#   @author 平松邦仁 (hira@rvf-rc45.net)
#	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
#				Released under the MIT license @n
#				https://github.com/hirakuni45/RX/blob/master/LICENSE
#=======================================================================
TARGET		=	libdrw2d

BUILD		=	release

VPATH		=

ASOURCES	=

CSOURCES	=	src/rx/dave_base_rx.c \
				src/rx/dave_irq_rx.c \
				src/rx/dave_memory_rx.c \
				src/tes/dave_base.c \
				src/tes/dave_blit.c \
				src/tes/dave_box.c \
				src/tes/dave_circle.c \
				src/tes/dave_context.c \
				src/tes/dave_curve.c \
				src/tes/dave_dlist.c \
				src/tes/dave_driver.c \
				src/tes/dave_edge.c \
				src/tes/dave_errorcodes.c \
				src/tes/dave_gradient.c \
				src/tes/dave_hardware.c \
				src/tes/dave_line.c \
				src/tes/dave_math.c \
				src/tes/dave_memory.c \
				src/tes/dave_pattern.c \
				src/tes/dave_perfcount.c \
				src/tes/dave_polyline.c \
				src/tes/dave_quad.c \
				src/tes/dave_rbuffer.c \
				src/tes/dave_render.c \
				src/tes/dave_texture.c \
				src/tes/dave_triangle.c \
				src/tes/dave_utility.c \
				src/tes/dave_viewport.c \
				src/tes/dave_wedge.c

PSOURCES	=

USER_LIBS	=

LDSCRIPT	=

USER_DEFS	=

MCU_TARGET	=	

# for boost
INC_SYS		=

INC_APP		=	. inc/tes

LIB_ROOT	=

# rx-elf-gcc compiler version check
TARGET_ISA_TEXT := $(shell rx-elf-gcc --target-help | grep ISA)

ifeq ($(TARGET_ISA_TEXT), )
# gcc-7.5.0 current gcc source build
OPTIMIZE	=	-O3 -mcpu=rx600 
else # Renesas GNU-RX gcc
OPTIMIZE	=	-O3 -misa=v2
endif


CP_OPT		=	-Wall -Werror \
				-Wno-unused-variable \
				-Wno-unused-function \
				-Wno-unused-but-set-variable \
				-fno-exceptions

CC_OPT		=	-Wall -Werror \
				-Wno-unused-variable \
				-Wno-unused-function \
				-Wno-unused-but-set-variable \
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
AR2			=	rx-elf-ranlib
LD			=	rx-elf-ld
OBJCOPY		=	rx-elf-objcopy
OBJDUMP		=	rx-elf-objdump
SIZE		=	rx-elf-size

# AFLAGS        = -Wa,-adhlns=$(<:.s=.lst),-gstabs
# AFLAGS        =	-Wa,-adhlns=$(<:.s=.lst)
# ALL_ASFLAGS    = -x assembler-with-cpp $(ASFLAGS) $(DEFS)
ALL_ASFLAGS    = $(AFLAGS) $(MCU_TARGET) $(DEFS)

# Override is only needed by avr-lib build system.

CFLAGS		=	-std=gnu99 $(CC_OPT) $(OPTIMIZE) $(MCU_TARGET) $(DEFS)
PFLAGS		=	-std=c++14 $(CP_OPT) $(OPTIMIZE) $(MCU_TARGET) $(DEFS)
# override LDFLAGS	= $(MCU_TARGET) -nostartfiles -Wl,-Map,$(TARGET).map,-fdata-sections,-ffunction-sections,-falign-jumps,-fno-function-cse,-funit-at-a-time --select-lib=newlib -T $(LDSCRIPT)
# override LDFLAGS	= $(MCU_TARGET) -nostartfiles -Wl,-Map,$(TARGET).map,--cref,--gc-sections -T $(LDSCRIPT)
ARFLAGS = rc

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
.SUFFIXES : .hpp .s .h .c .cpp .d .o .a

all: $(BUILD) $(TARGET).a

$(TARGET).a: $(OBJECTS) Makefile
	$(AR) $(ARFLAGS) $@ $(OBJECTS)
	$(AR2) $@

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
	rm -rf $(BUILD) $(TARGET).a

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
	rx_prog -d RX64M --progress --erase --write --verify $(TARGET).mot

-include $(DEPENDS)
