#
#	@note					This makefile assumes that there is a path to the to the 
#								toolchain 
#
TOOLPATH	=
TOOL			= $(TOOLPATH)arm-none-eabi-
CC 				= $(TOOL)gcc

BINDIR		= bin/
SRCDIR		=

CFLAGS		= -march=armv7-m 
CFLAGS 	 += -mcpu=cortex-m3 
CFLAGS 	 += -mthumb
CFLAGS   += -std=gnu17

#SRCFILES  = main.c
#SRCFILES += led.c
#
#OBJFILES 	= $(BINDIR)main.o
#OBJFILES += $(BINDIR)led.o

all: $(BINDIR) $(OBJFILES)

# Rule to create build directory
$(BINDIR) :
	mkdir -p $(BINDIR)

$(BINDIR)%o : $(SRCDIR)%c
	$(CC) $(CFLAGS) -c $^ -o $@

#$(BINDIR)main.o	: main.c 
#	$(CC) $(CFLAGS) -c $^ -o $@

#$(BINDIR)led.o	: led.c 
#	$(CC) $(CFLAGS) -c $^ -o $@

.PHONEY	: clean
clean 	:
	rm $(BINDIR)*.*

# arm-none-eabi-gcc -march=armv7-m -mcpu=cortex-m3 -mthumb -std=gnu17 -S main.c -o main.S