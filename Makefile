# ==============================================================================
#	@file					Makefile
#	@date					2025-02-26	
#	@brief				Makefile for STM32F031K6
# ==============================================================================

#
#	@note					To enable debug mode, set the DEBUG variable to anything, else
#								leave it empty
#
DEBUG		= 1

#
#	@note					This makefile assumes that there is a path to the to the
#								toolchain
#
TOOLPATH	=
TOOL			= $(TOOLPATH)arm-none-eabi-
CC 				= $(TOOL)gcc
SIZE			= $(TOOL)size

BINDIR		= bin/
SRCDIR		= src/
INCDIR		= -Iinc/ -Iinc/cmsis/

DEFINES		= -DSTM32F031x6

CFLAGS		= -march=armv6-m
CFLAGS 	 += -mcpu=cortex-m0
CFLAGS 	 += -mthumb
CFLAGS   += -std=gnu11
CFLAGS   += -Wall
ifdef DEBUG
CFLAGS	 += -O0
CFLAGS	 += -g -ggdb
endif

LFLAGS    = -march=armv6-m -mcpu=cortex-m0 -mthumb
LFLAGS   += -nostdlib -lgcc
LFLAGS   += -Tstm32f031k6.ld
ifdef DEBUG
LFLAGS   += -Wl,-Map,$(BINDIR)test.map,--cref -Wl,--gc-sections
else
LFLAGS   += -Wl,--gc-sections
endif

SRCFILES  = main.c
SRCFILES += gpio.c
SRCFILES += systick.c
SRCFILES += system_stm32f0xx.c
SRCFILES += startup_stm32f031k6.c

OBJFILES  = $(BINDIR)main.o
OBJFILES += $(BINDIR)gpio.o
OBJFILES += $(BINDIR)systick.o
OBJFILES += $(BINDIR)system_stm32f0xx.o
OBJFILES += $(BINDIR)startup_stm32f031k6.o

TARGET		= test.elf

all: $(BINDIR) $(BINDIR)$(TARGET)

# Rule to create build directory
$(BINDIR) :
	mkdir -p $(BINDIR)

$(BINDIR)$(TARGET) : $(OBJFILES)
	$(CC) $(OBJFILES) $(LFLAGS) -o $@
	$(SIZE) $@

$(BINDIR)main.o	: $(SRCDIR)main.c
	$(CC) $(DEFINES) $(INCDIR) $(CFLAGS) -c $^ -o $@

$(BINDIR)gpio.o	: $(SRCDIR)gpio.c
	$(CC) $(DEFINES) $(INCDIR) $(CFLAGS) -c $^ -o $@

$(BINDIR)systick.o	: $(SRCDIR)systick.c
	$(CC) $(DEFINES) $(INCDIR) $(CFLAGS) -c $^ -o $@

$(BINDIR)system_stm32f0xx.o	: $(SRCDIR)system_stm32f0xx.c
	$(CC) $(DEFINES) $(INCDIR) $(CFLAGS) -c $^ -o $@

$(BINDIR)startup_stm32f031k6.o	: $(SRCDIR)startup_stm32f031k6.c
	$(CC) $(DEFINES) $(INCDIR) $(CFLAGS) -c $^ -o $@

.PHONEY	: clean
clean 	:
	rm $(BINDIR)*.*

# arm-none-eabi-gcc -march=armv6-m -mcpu=cortex-m0 -mthumb -std=gnu17 -S main.c -o main.S