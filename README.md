# Bare Metal Embedded Lectures

This summarizes the excellent YouTube series from Fastbit Embedded Brain Academy.

Some experience is assumed if you're reading this. There are a lot of details
that the YouTube series expands on that will not be developed here. This is
mostly notes for review.

## Lecture 1 - The Build Process

Bare metal embedded lecture-1: Build process<br>
https://www.youtube.com/watch?v=qWqlkCLmZoE&t=619s

- Overview of cross compilation toolchains.
- Installation of the GNU gcc toolchain
- Explanation of the preprocessing, compilation and linking stages of the build process

After the basic overview of the build process an example of the compilation 
process is demonstrated. Important points include how to tell the compiler

- Machine dependent options (e.g., -march, -mcpu, -mthumb, etc.)
- An example of how to generate an assembly only file using command line options

If you are familiar with embedded programming, in general, this section, while
very interesting can safely be skipped.

## Lecture 2 - Makefile and Analyzing Relocatable Object Files

Bare metal embedded lecture-2: Makefile and analyzing relocatable obj file<br>
https://www.youtube.com/watch?v=Bsq6P1B8JqI

- How to write makefiles (specifically for these examples)
- How to analyze object files

Note: the makefile for this project is slightly different than the one in the 
video.

### objdump

What follows are examples of how to use ***arm-none-eabi-objdump***. The online
man page can be found [here](https://man7.org/linux/man-pages/man1/objdump.1.html).

The main.c file, from which the following examples are based (i.e., main.o) 
is below. Note that this is not the same **main.c** that is presented in the 
videos.

~~~c
#include  <stdint.h>
#include  "main.h"

// .rodata section
const uint32_t  c32var    = 4096;
const uint16_t  c16var    = 1024;
const uint8_t   c8var     = 128;

// .data section
volatile uint32_t v32var  = 4095;
volatile uint16_t v16var  = 1023;
volatile uint8_t  v8var   = 127;

// .bss section
uint32_t  tick_count      = 0;

int main(void)
{

  v32var  = c32var;
  v16var  = c16var;
  v8var   = c8var;

  while(1)
  {
    ;
  }
	return 0;
} // main
~~~

1. Example of using **-h** to display the contents of the section headers.

~~~
$ arm-none-eabi-objdump -h bin/main.o

bin/main.o:     file format elf32-littlearm

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         0000002c  00000000  00000000  00000034  2**2
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, CODE
  1 .data         00000007  00000000  00000000  00000060  2**2
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          00000004  00000000  00000000  00000068  2**2
                  ALLOC
  3 .rodata       00000007  00000000  00000000  00000068  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  4 .comment      00000044  00000000  00000000  0000006f  2**0
                  CONTENTS, READONLY
  5 .ARM.attributes 0000002c  00000000  00000000  000000b3  2**0
                  CONTENTS, READONLY
~~~

Because the files are so simple, there are few data in either the data (.data) 
or uninitialized data (.bss) segments. The .text segment only has 396 bytes,
of which 192 bytes is the vector table.

**arm-none-eabi-objdump** can be used to disassemble specific object files or
the entire elf file. The latter gives more information about the variables
defined in the files.

The main.o file, edited for brevity.

~~~c
$ arm-none-eabi-objdump -d bin/main.o

bin/main.o:     file format elf32-littlearm


Disassembly of section .text:

00000000 <main>:
   0:	b580      	push	{r7, lr}
   2:	af00      	add	r7, sp, #0
   4:	2380      	movs	r3, #128	@ 0x80
   ...
~~~

The entire binary (*.elf), edited for brevity.

~~~c
$ arm-none-eabi-objdump -d bin/test.elf

bin/test.elf:     file format elf32-littlearm


Disassembly of section .text:

08000000 <vectors>:
 8000000:	00 10 00 20 f9 00 00 08 7d 01 00 08 7d 01 00 08     ... ....}...}...
	...

080000c0 <main>:
 80000c0:	b580      	push	{r7, lr}
 80000c2:	af00      	add	r7, sp, #0
 80000c4:	2380      	movs	r3, #128	@ 0x80
  ...
 80000e0:	20000000 	.word	0x20000000
 80000e4:	20000004 	.word	0x20000004
 80000e8:	20000006 	.word	0x20000006

080000ec <init_led>:
 80000ec:	b580      	push	{r7, lr}
 80000ee:	af00      	add	r7, sp, #0
 80000f0:	46c0      	nop			@ (mov r8, r8)
	...

080000f8 <Reset_Handler>:
 80000f8:	b580      	push	{r7, lr}
 80000fa:	b086      	sub	sp, #24
 80000fc:	af00      	add	r7, sp, #0
  ...
 8000168:	20000008 	.word	0x20000008
 800016c:	20000000 	.word	0x20000000
 8000170:	0800018c 	.word	0x0800018c
 8000174:	2000000c 	.word	0x2000000c
 8000178:	20000008 	.word	0x20000008

0800017c <Default_Handler>:
 800017c:	b580      	push	{r7, lr}
 800017e:	af00      	add	r7, sp, #0
 8000180:	46c0      	nop			@ (mov r8, r8)
 8000182:	e7fd      	b.n	8000180 <Default_Handler+0x4>

08000184 <c32var>:
 8000184:	1000 0000                                   ....

08000188 <c16var>:
 8000188:	0400                                        ..

0800018a <c8var>:
 800018a:	0080                                        ..
~~~

Note that the **.comment** and **.ARM.attributes** sections do not contain
executable code or program data, they hold version control information. These
sections are added by the compiler, as are others.

The sections can be examined by using the **-s** flag. This flag is used to 
display the full contents of sections, often used in combination with **-j** to 
request specific sections. 

~~~c
$ arm-none-eabi-objdump -s -j .comment bin/test.elf 

bin/main.o:     file format elf32-littlearm

Contents of section .comment:
 0000 00474343 3a202847 4e552054 6f6f6c73  .GCC: (GNU Tools
 0010 20666f72 2053544d 33322031 322e332e   for STM32 12.3.
 0020 72656c31 2e323032 34303932 362d3137  rel1.20240926-17
 0030 31352920 31322e33 2e312032 30323330  15) 12.3.1 20230
 0040 36323600                             626.            
~~~

~~~c
$ arm-none-eabi-objdump -s -j .ARM.attributes bin/test.elf

bin/main.o:     file format elf32-littlearm

Contents of section .ARM.attributes:
 0000 412c0000 00616561 62690001 22000000  A,...aeabi.."...
 0010 05372d4d 00060a07 4d090212 04140115  .7-M....M.......
 0020 01170318 0119011a 011e0622 01        ...........".   
~~~

## Lecture 3 - Writing MCU startup file from scratch

Bare metal embedded lecture-3: Writing MCU startup file from scratch<br>
https://www.youtube.com/watch?v=2Hm8eEHsgls&t=69s

This lecture gets into the meat and potatoes of bare metal programming on ARM
microcontrollers with an excellent explanation of the start up file.

This file, usually written in assembly, is supplied by the microcontroller 
vendor. One does not have to create them from scratch. However it is instructive
to see how it's done and, more importantly, why.

It is necessary to understand that the startup code is responsible for setting 
up the runtime environment for the main code. This can include hardware 
initialization such as the clock tree and floating point unit, if the processor
has one. More importantly, the startup code is responsible for the initialization
of the stack, variables that are assigned values, static constructors and
anything that is expected to be initialized before **main()** is called.

This project differs from the Fastbit Academy code in that a STM32F031K6
microcontroller is used here. The examples are developed on the STM32 Nucleo-32
development board[^1]. That development board has the following features:

- STM32F031K6T6B microcontroller with 
  - 32 KB Flash memory 
  - 4 KB RAM in 64-pin LQFP
  - ARM Cortex-M0 (ARMv6-M)
- Memory Map
  - Flash:
      0x08000000 - 0x08007FFF  (32768 bytes)
  - SRAM:
      0x20000000 - 0x20000FFF  (4096 bytes)

Refer to the STM32F0x1 Reference Manual (RM0091) for more information.

### Interrupts and Exceptions

There are 22 maskable interrupts on the SMR32F031K6. It is important to note
that the reference manual lists all 32 in the chapter on interrupts but that is
for the other devices in the STM32F0xx family. This does not include the first
16 exceptions that are set aside for the ARM architecture.

The available interrupts can be figured out by looking at the appropriate data
sheet block diagram and see what is implemented. One could also just get the
startup file for the device and copy that.

The **STM32CubeF0 CMSIS Device MCU Component** files, of which 
**startup_stm32f031x6.s** is one, are available on GitHub [^2].

The important takeaways from this lecture are:

1. Creating a function table (array) with an array member for each exception
   and interrupt handler address.
   - The array will be 'decorated' with an attribute that allows us to place the
     array in the executable code section.
   - 'reserved' interrupts in the vector table documentation need to be 
     represented in the array by 0. The table layout must match the vector
     table documentation. The (relative) addressing must be the same.
   - For ARM Cortex-M devices, the first array member is the address of the top
     of the stack. Initially this can be hardcoded but later a symbolic
     address can be created by the linker script.
2. Because not every interrupt handler will need to be implemented a 'dummy'
   function is created for those handlers.
   - Most all of the exception and interrupt handlers will be aliased to this
     dummy function. Because the prototypes are attributed with 'weak' they
     can be replaced later with our own handlers without changing the vector
     table declaration.
3. The **Reset_Handler**, the exception called at reset, needs to be implemented.
   It will be responsible for initializing the microcontroller (clocks, etc),
   .data and .bss segments in RAM.
4. The **Dummy_Handler** needs to be implemented and can contain nothing more 
   than an endless loop or more sophisticated error handling code.

A brief example the the vector table follows. Note the use of attributes.

~~~c
// handler prototypes
void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
...

// vector table
uint32_t vectors[] __attribute__ ((section(".vector_tbl"))) = 
{
  (uint32_t)0x20002000,                                     /* 0x0000_0000    */
  (uint32_t)&Reset_Handler,                                 /* 0x0000_0004    */
  (uint32_t)&NMI_Handler,                                   /* 0x0000_0008    */
...
~~~

## Lecture 4 - Writing linker scripts and section placement

Bare metal embedded lecture-4: Writing linker scripts and section placement<br>
https://www.youtube.com/watch?v=B7oKdUvRhQQ&t=33s


## Lecture 5 - Linking and analyzing memory map file

Bare metal embedded lecture-5: Linking and analyzing memory map file
https://www.youtube.com/watch?v=5aafG5mjZ_Y



<!-- GitHub ---------------------------------------------------------------- -->
git clone https://github.com/STMicroelectronics/cmsis-device-f0.git

<!-- The older stuff ------------------------------------------------------- -->

~~~
$ /opt/st/stm32cubeclt_1.17.0/GNU-tools-for-STM32/bin/arm-none-eabi-nm -f sysv main.o


Symbols from main.o:

Name                      Value   Class  Type         Size     Line  Section

global_function         |0000000e|   T  |        FUNC|0000002a|     |.text
global_var              |00000000|   B  |      OBJECT|00000004|     |.bss
global_var_init         |00000000|   D  |      OBJECT|00000004|     |.data
local_static_var.1      |00000008|   b  |      NOTYPE|00000004|     |.bss
local_static_var_init.0 |00000008|   d  |      OBJECT|00000004|     |.data
main                    |00000038|   T  |        FUNC|00000024|     |.text
static_function         |00000000|   t  |        FUNC|0000000e|     |.text
static_var              |00000004|   b  |      NOTYPE|00000004|     |.bss
static_var_init         |00000004|   d  |      OBJECT|00000004|     |.data
~~~

The symbol table can also be displayed using `objdump`.

~~~
$ /opt/st/stm32cubeclt_1.17.0/GNU-tools-for-STM32/bin/arm-none-eabi-objdump -t main.o 

main.o:     file format elf32-littlearm

SYMBOL TABLE:
00000000 l    df *ABS*	00000000 main.c
00000000 l    d  .text	00000000 .text
00000000 l    d  .data	00000000 .data
00000000 l    d  .bss   00000000 .bss
00000004 l       .bss   00000004 static_var
00000004 l     O .data	00000004 static_var_init
00000000 l     F .text	0000000e static_function
00000008 l       .bss   00000004 local_static_var.1
00000008 l     O .data	00000004 local_static_var_init.0
00000000 l    d  .comment 00000000 .comment
00000000 l    d  .ARM.attributes	00000000 .ARM.attributes
00000000 g     O .bss   00000004 global_var
00000000 g     O .data	00000004 global_var_init
0000000e g     F .text	0000002a global_function
00000038 g     F .text	00000024 main
~~~



<!-- main.o ELF output ----------------------------------------------------- -->


<!-- Appendix -------------------------------------------------------------- -->
[^1]: https://www.st.com/en/evaluation-tools/nucleo-f031k6.html
[^2]: https://github.com/STMicroelectronics/cmsis-device-f0/
