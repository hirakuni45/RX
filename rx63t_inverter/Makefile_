#=======================================================================#
#																		#
#	RX Makefile R5F563T6EDFM (64K Flash, 8K Ram)				        #
#																		#
#=======================================================================#
TARGET		=	inverter

ASOURCES	=	start.s

CSOURCES	=	vect.c \
				init.c

PSOURCES	=	main.cpp \
				../rx/cmt_io.cpp \
				../rx/sci_io.cpp \
				../rx/gpt_io.cpp \
				inv_monitor.cpp


USER_LIBS	=	stdc++

LDSCRIPT	=	rx63t_single_chip.ld

USER_DEFS	=	F_PCKA=96000000 F_PCKB=48000000

# 	-mcpu=rx610
MCU_TARGET	=

INC_SYS		=	/usr/boost_1_53_0
INC_ROOT	=	. ..
LIB_ROOT	=

#OPTIMIZE	=	-O0
#OPTIMIZE	=	-O1
OPTIMIZE	=	-O2

CPP_OPT		=	-Wno-pmf-conversions

# -fno-exceptions
CC_OPT		=	-Wall \
				-fno-exceptions
#				-fdata-sections -ffunction-sections -falign-jumps -funit-at-a-time
#				-fdata-sections -ffunction-sections -falign-jumps -fno-function-cse -funit-at-a-time
# DEBUG_OPT	=	-Wall

INCS		=	$(addprefix -I, $(INC_ROOT))
INC_DEP		=	$(addprefix -I, $(INC_ROOT))
LIBINCS		=	$(addprefix -L, $(LIB_ROOT))
DEFS		=	$(addprefix -D, $(USER_DEFS))
LIBS		=	$(addprefix -l, $(USER_LIBS))

# You should not have to change anything below here.

CC			=	rx-elf-gcc
CPP			=	rx-elf-g++
AR			=	rx-elf-ar
LD			=	rx-elf-ld
OBJCOPY		=	rx-elf-objcopy
OBJDUMP		=	rx-elf-objdump

# ASFLAGS        = -Wa,-adhlns=$(<:.s=.lst),-gstabs
ASFLAGS        =	-Wa,-adhlns=$(<:.s=.lst)
# ALL_ASFLAGS    = -x assembler-with-cpp $(ASFLAGS) $(DEFS)
ALL_ASFLAGS    = $(ASFLAGS) $(MCU_TARGET) $(DEFS)

# Override is only needed by avr-lib build system.

CFLAGS		=	-std=gnu99 $(CC_OPT) $(OPTIMIZE) $(MCU_TARGET) $(DEFS)
PFLAGS		=	-std=c++0x $(CPP_OPT) $(OPTIMIZE) $(MCU_TARGET) $(DEFS)
# override LDFLAGS	= $(MCU_TARGET) -nostartfiles -Wl,-Map,$(TARGET).map,-fdata-sections,-ffunction-sections,-falign-jumps,-fno-function-cse,-funit-at-a-time --select-lib=newlib -T $(LDSCRIPT)
# override LDFLAGS	= $(MCU_TARGET) -nostartfiles -Wl,-Map,$(TARGET).map,--cref,--gc-sections -T $(LDSCRIPT)

override LDFLAGS	= $(MCU_TARGET) -nostartfiles -Wl,-Map,$(TARGET).map -T $(LDSCRIPT)

OBJCOPY_OPT	=	--srec-forceS3 --srec-len 32

OBJECTS		=	$(ASOURCES:.s=.o) $(CSOURCES:.c=.o) $(PSOURCES:.cpp=.o)
DEPENDS =   $(CSOURCES:.c=.d) $(PSOURCES:.cpp=.d) 

# all: $(TARGET).elf lst text
# all: $(TARGET).elf $(LDSCRIPT) Makefile lst text
all: $(TARGET).elf $(LDSCRIPT) Makefile lst text

$(TARGET).elf: $(OBJECTS) $(LDSCRIPT) Makefile
	$(CC) $(LDFLAGS) $(LIBINCS) -o $@ $(OBJECTS) $(LIBS)

%.o: %.cpp
	$(CPP) $(PFLAGS) $(INCS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

%.o: %.s
	$(CC) -c $(ALL_ASFLAGS) $< -o $@

%.d: %.c %.h
	echo '$*.o: \' > $@
	$(CC) -MM $(COPT) $(CFLAGS) $(INCS) $(CCWARN) $< | \
	sed 's/.*://' >> $@

%.d: %.cpp %.hpp
	echo '$*.o: \' > $@
	$(CPP) -MM $(POPT) $(PFLAGS) $(INCS) $(CPWARN) $< | \
	sed 's/.*://' >> $@

clean:
	rm -rf $(DEPENDS)
	rm -rf $(OBJECTS) $(TARGET).elf
	rm -rf *.lst *.map $(EXTRA_CLEAN_FILES)

lst:  $(TARGET).lst

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

# Rules for building the .text rom images

text: mot bin

bin: $(TARGET).bin
mot: $(TARGET).mot

%.mot: %.elf
	$(OBJCOPY) $(OBJCOPY_OPT) -O srec $< $@

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@
#	$(OBJCOPY) -j .vects -j .text -j .data -O binary $< $@

tarball:
	chmod 644 ../fatfs/src/*.[hc] \
		../fatfs/src/option/*.c \
		../fatfs/rx621/*.[hc]pp \
		../rx62x/*.[hc]pp \
		*.s *.[hc] *.[hc]pp *.ld Makefile
	rm -f $(TARGET)_src.tgz
	tar cfvz $(TARGET)_src.tgz \
		../fatfs/src/*.[hc] \
		../fatfs/src/option/*.c \
		../fatfs/rx621/*.[hc]pp \
		../rx62x/*.[hc]pp \
		../rx621_sd/*.s ../rx621_sd/*.[hc] ../rx621_sd/*.[hc]pp \
		../rx621_sd/*.ld ../rx621_sd/Makefile
	chmod 444 $(TARGET)_src.tgz

clean_depend:
	rm -f $(DEPENDS)

-include $(DEPENDS)
