#
#	@note					This makefile assumes that there is a path to the to the 
#								toolchain 
#
TOOLPATH	=
TOOL			= $(TOOLPATH)arm-none-eabi-
CC 				= $(TOOL)gcc

BINDIR		= bin/
SRCDIR		=

CFLAGS		= -march=armv6-m 
CFLAGS 	 += -mcpu=cortex-m0 
CFLAGS 	 += -mthumb
CFLAGS   += -std=gnu11
CFLAGS   += -Wall
CFLAGS	 += -O0
CFLAGS	 += -g -ggdb

LFLAGS    = -nostdlib
LFLAGS   += -Tstm32f031k6.ld
LFLAGS   += -Wl,-Map,$(BINDIR)test.map 

SRCFILES  = main.c
SRCFILES += led.c
SRCFILES += startup_stm32f031k6.c

OBJFILES  = $(BINDIR)main.o
OBJFILES += $(BINDIR)led.o
OBJFILES += $(BINDIR)startup_stm32f031k6.o

TARGET		= test.elf

all: $(BINDIR) $(BINDIR)$(TARGET)

# Rule to create build directory
$(BINDIR) :
	mkdir -p $(BINDIR)

$(BINDIR)$(TARGET) : $(OBJFILES)
	$(CC) $(LFLAGS) $(OBJFILES) -o $(BINDIR)$(TARGET)

$(BINDIR)main.o	: main.c 
	$(CC) $(CFLAGS) -c $^ -o $@

$(BINDIR)led.o	: led.c 
	$(CC) $(CFLAGS) -c $^ -o $@

$(BINDIR)startup_stm32f031k6.o	: startup_stm32f031k6.c 
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONEY	: clean
clean 	:
	rm $(BINDIR)*.*

# arm-none-eabi-gcc -march=armv6-m -mcpu=cortex-m0 -mthumb -std=gnu17 -S main.c -o main.S