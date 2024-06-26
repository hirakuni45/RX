# -*- tab-width : 4 -*-
#=======================================================================
#   @file
#   @brief  RX prog Makefile
#   @author 平松邦仁 (hira@rvf-rc45.net)
#	@copyright	Copyright (C) 2018 Kunihito Hiramatsu @n
#				Released under the MIT license @n
#				https://github.com/hirakuni45/RX/blob/master/LICENSE
#=======================================================================
TARGET		=	rx_prog

#ICON_RC		=	icon.rc

# 'debug' or 'release'
BUILD		=	release

VPATH		=

CSOURCES	=
PSOURCES	=	main.cpp \
				file_io.cpp \
				string_utils.cpp \
				sjis_utf16.cpp

# Include path for each environment
ifeq ($(OS),Windows_NT)
SYSTEM := WIN
# LOCAL_PATH  =   /mingw64
LOCAL_PATH  =   /c/boost_1_74_0
CMD_EXT = exe
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
CMD_EXT =
endif

STDLIBS		=
OPTLIBS		=
INC_SYS     =   $(LOCAL_PATH)
INC_LIB		=

PINC_APP	=
CINC_APP	=
LIBDIR		=

INC_S	=	$(addprefix -isystem , $(INC_SYS))
INC_L	=	$(addprefix -isystem , $(INC_LIB))
INC_P	=	$(addprefix -I, $(PINC_APP))
INC_C	=	$(addprefix -I, $(CINC_APP))
CINCS	=	$(INC_S) $(INC_L) $(INC_C)
PINCS	=	$(INC_S) $(INC_L) $(INC_P)
LIBS	=	$(addprefix -L, $(LIBDIR))
LIBN	=	$(addprefix -l, $(STDLIBS))
LIBN	+=	$(addprefix -l, $(OPTLIBS))

#
# Compiler, Linker Options, Resource_compiler
#
CP	=	g++
CC	=	gcc
LK	=	g++
RC	=

POPT	=	-O2 -std=gnu++17
COPT	=	-O2
LOPT	=

PFLAGS	=	-DHAVE_STDINT_H
CFLAGS	=

ifeq ($(BUILD),debug)
	POPT += -g
	COPT += -g
	PFLAGS += -DDEBUG
	CFLAGS += -DDEBUG
endif

ifeq ($(BUILD),release)
	PFLAGS += -DNDEBUG
	CFLAGS += -DNDEBUG
endif

# 	-static-libgcc -static-libstdc++
LFLAGS =

# -Wuninitialized -Wunused -Werror -Wshadow
CCWARN	=	-Wimplicit -Wreturn-type -Wswitch \
			-Wformat
CPWARN	=	-Wall -Werror \
			-Wno-unused-function

OBJECTS	=	$(addprefix $(BUILD)/,$(patsubst %.cpp,%.o,$(PSOURCES))) \
			$(addprefix $(BUILD)/,$(patsubst %.c,%.o,$(CSOURCES)))
DEPENDS =   $(patsubst %.o,%.d, $(OBJECTS))

ifdef ICON_RC
	ICON_OBJ =	$(addprefix $(BUILD)/,$(patsubst %.rc,%.o,$(ICON_RC)))
endif

.PHONY: all clean
.SUFFIXES :
.SUFFIXES : .rc .hpp .h .c .cpp .o

all: $(BUILD) $(TARGET)

$(TARGET): $(OBJECTS) $(ICON_OBJ) Makefile
	$(LK) $(LFLAGS) $(LIBS) $(OBJECTS) $(ICON_OBJ) $(LIBN) -o $(TARGET)

$(BUILD)/%.o : %.c
	mkdir -p $(dir $@); \
	$(CC) -c $(COPT) $(CFLAGS) $(CINCS) $(CCWARN) -o $@ $<

$(BUILD)/%.o : %.cpp
	mkdir -p $(dir $@); \
	$(CP) -c $(POPT) $(PFLAGS) $(PINCS) $(CPWARN) -o $@ $<

$(ICON_OBJ): $(ICON_RC)
	$(RC) -i $< -o $@

$(BUILD)/%.d : %.c
	mkdir -p $(dir $@); \
	$(CC) -MM -DDEPEND_ESCAPE $(COPT) $(CFLAGS) $(CINCS) $< \
	| sed 's/$(notdir $*)\.o:/$(subst /,\/,$(patsubst %.d,%.o,$@) $@):/' > $@ ; \
	[ -s $@ ] || rm -f $@

$(BUILD)/%.d : %.cpp
	mkdir -p $(dir $@); \
	$(CP) -MM -DDEPEND_ESCAPE $(POPT) $(PFLAGS) $(PINCS) $< \
	| sed 's/$(notdir $*)\.o:/$(subst /,\/,$(patsubst %.d,%.o,$@) $@):/' > $@ ; \
	[ -s $@ ] || rm -f $@

run:
	./$(TARGET) -d RX64M -P COM11 --verbose --progress --erase --write --verify uart_sample.mot

run_verify:
	./$(TARGET) -d RX64M -P COM11 --verbose --progress --verify uart_sample.mot

clean:
	rm -rf $(BUILD) $(TARGET)

clean_depend:
	rm -f $(DEPENDS)

dllname:
	objdump -p $(TARGET) | grep "DLL Name"

tarball:
	tar cfvz $(subst .exe,,$(TARGET))_$(shell date +%Y%m%d%H).tgz \
	*.[hc]pp Makefile

bin_zip:
	$(LK) $(LFLAGS) $(LIBS) $(OBJECTS) $(ICON_OBJ) $(LIBN) -mwindows -o $(TARGET) 
	rm -f $(subst .exe,,$(TARGET))_$(shell date +%Y%m%d%H)_bin.zip
	zip $(subst .exe,,$(TARGET))_$(shell date +%Y%m%d%H)_bin.zip *.exe *.dll

install:
	mkdir -p /usr/local/bin
	cp $(TARGET).$(CMD_EXT) /usr/local/bin/.
	cp $(TARGET).conf /usr/local/bin/.

-include $(DEPENDS)
