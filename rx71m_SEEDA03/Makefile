#=======================================================================
#   @file
#   @brief  RX71M Makefile
#   @author 平松邦仁 (hira@rvf-rc45.net)
#	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
#				Released under the MIT license @n
#				https://github.com/hirakuni45/RX/blob/master/LICENSE
#=======================================================================
TARGET		=	seeda03_rx71m

# MCU (R5F564MLHDFB 144pin QFP)
DEVICE		=	R5F571ML

FATFS_VER	=	ff12b

# BUILD		=	release
BUILD		=	debug

BUILD_ID	=	$(shell date +%Y%m%d%H)

VPATH		=	../

ASOURCES	=	common/start.s \
				r_net/driver/cksum_rx_little.s

CSOURCES	=	common/ofs.c \
				common/init.c \
				common/vect.c \
				common/syscalls.c \
				$(FATFS_VER)/src/ff.c \
				$(FATFS_VER)/src/option/unicode.c \
				common/time.c \
				r_net/r_byteq_v1.30/r_byteq.c \
				r_net/driver/phy.c \
				r_net/driver/r_ether.c \
				r_net/driver/driver.c \
				r_net/T4_src/config_tcpudp.c \
				r_net/T4_src/ether.c \
				r_net/T4_src/ip.c \
				r_net/T4_src/udp.c \
				r_net/T4_src/tcp.c \
				r_net/T4_src/tcp_api.c \
				r_net/T4_src/r_dhcp_client.c

PSOURCES	=	rx64m_test/main.cpp \
				r_net/ethernet.cpp \
				common/stdapi.cpp

USER_LIBS	=	supc++ m

LDSCRIPT	=	../RX71M/$(DEVICE).ld

USER_DEFS	=	SIG_RX71M \
				F_ICLK=237500000 F_BCLK=118750000 \
				F_PCLKA=118750000 F_PCLKB=59375000 F_PCLKC=59375000 F_PCLKD=59375000 \
				F_FCLK=59375000 \
				B_ID=$(BUILD_ID) SEEDA \
				FAT_FS FAT_FS_NUM=3 \
				LOGGING_FS \
				TI_DP83822_

MCU_TARGET	=

INC_SYS		=

INC_APP		=	. ../ ../RX600 ../RX71M ../r_net ../rx64m_test

OPTIMIZE	=	-O3

AS_OPT		=	-mcpu=rx600 --defsym MEMWAIT=1

CP_OPT		=	-Wall -Werror \
				-Wno-unused-variable \
				-Wno-unused-function \
				-mcpu=rx600 \
				-fno-exceptions \
				-mlittle-endian-data

CC_OPT		=	-Wall -Werror \
				-Wno-unused-variable \
				-Wno-unused-function \
				-mcpu=rx600 \
				-fno-exceptions \
				-mlittle-endian-data

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

# AFLAGS        = -Wa,-adhlns=$(<:.s=.lst),-gstabs
AFLAGS		=	$(AS_OPT)
# AFLAGS        =	-Wa,-adhlns=$(<:.s=.lst)
# ALL_ASFLAGS    = -x assembler-with-cpp $(ASFLAGS) $(DEFS)
ALL_ASFLAGS    = $(AFLAGS) $(MCU_TARGET) $(DEFS)

ifeq ($(BUILD),debug)
#	CP_OPT += -g
#	CC_OPT += -g
	DEFS += -DDEBUG
endif

ifeq ($(BUILD),release)
	DEFS += -DNDEBUG
endif

CFLAGS		=	-std=gnu99 $(CC_OPT) $(OPTIMIZE) $(MCU_TARGET) $(DEFS)
PFLAGS		=	-std=c++14 $(CP_OPT) $(OPTIMIZE) $(MCU_TARGET) $(DEFS)
# override LDFLAGS	= $(MCU_TARGET) -nostartfiles -Wl,-Map,$(TARGET).map,-fdata-sections,-ffunction-sections,-falign-jumps,-fno-function-cse,-funit-at-a-time --select-lib=newlib -T $(LDSCRIPT)
# override LDFLAGS	= $(MCU_TARGET) -nostartfiles -Wl,-Map,$(TARGET).map,--cref,--gc-sections -T $(LDSCRIPT)

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
	*.[hc]pp Makefile ../common/*.[hc]pp ../common/*.[hcs] ../RX600/*.hpp \
	../RX64M/*.ld ../$(FATFS_VER)/* 

bin_zip:
	$(LK) $(LFLAGS) $(LIBS) $(OBJECTS) $(ICON_OBJ) $(LIBN) -mwindows -o $(TARGET) 
	rm -f $(subst .exe,,$(TARGET))_$(shell date +%Y%m%d%H)_bin.zip
	zip $(subst .exe,,$(TARGET))_$(shell date +%Y%m%d%H)_bin.zip *.exe *.dll res/*.*

run:
	rx_prog -P COM11 -d RX64M --progress --erase --write --verify $(TARGET).mot

doxygen:
	rm -rf seeda03_doc.zip
	rm -rf SEEDA03_DOC
	doxygen doxyfile
	zip -r seeda03_doc.zip SEEDA03_DOC

-include $(DEPENDS)
