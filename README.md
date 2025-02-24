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

### objdump

what follows are examples of how to use ***arm-none-eabi-objdump***. The online
man page can be found [here](https://man7.org/linux/man-pages/man1/objdump.1.html).

The main.c file, from which the following examples are based (i.e., main.o) 
is below.

~~~c
#include  "main.h"

int main(void)
{
  while(1);
  return 0;
} // main
~~~

1. example of using -h to display the contents of the section headers.

~~~
$ arm-none-eabi-objdump -h bin/main.o 

bin/main.o:     file format elf32-littlearm

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         00000006  00000000  00000000  00000034  2**1
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  1 .data         00000000  00000000  00000000  0000003a  2**0
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          00000000  00000000  00000000  0000003a  2**0
                  ALLOC
  3 .comment      00000044  00000000  00000000  0000003a  2**0
                  CONTENTS, READONLY
  4 .ARM.attributes 0000002d  00000000  00000000  0000007e  2**0
                  CONTENTS, READONLY
~~~

Because the file is so simple, there are no data in either the data (.data) or
uninitialized data (.bss) segments their length is 0. The text segment only has
6 bytes. This can be seen using the **-d** flag to disassemble the object file.

~~~c
$ arm-none-eabi-objdump -d bin/main.o 

bin/main.o:     file format elf32-littlearm


Disassembly of section .text:

00000000 <main>:
   0:	b480      	push	{r7}
   2:	af00      	add	r7, sp, #0
   4:	e7fe      	b.n	4 <main+0x4>
~~~

Note that the **.comment** and **.ARM.attributes** sections do not contain
executable code or program data, they hold version control information. These
sections are added by the compiler.

The sections can be examined by using the **-s** flag. This flag is used to 
display the full contents of sections, often used in combination with **-j** to 
request specific sections. 

~~~c
$ arm-none-eabi-objdump -s -j .comment bin/main.o 

bin/main.o:     file format elf32-littlearm

Contents of section .comment:
 0000 00474343 3a202847 4e552054 6f6f6c73  .GCC: (GNU Tools
 0010 20666f72 2053544d 33322031 322e332e   for STM32 12.3.
 0020 72656c31 2e323032 34303932 362d3137  rel1.20240926-17
 0030 31352920 31322e33 2e312032 30323330  15) 12.3.1 20230
 0040 36323600                             626.            
~~~

~~~c
$ arm-none-eabi-objdump -s -j .ARM.attributes bin/main.o 

bin/main.o:     file format elf32-littlearm

Contents of section .ARM.attributes:
 0000 412c0000 00616561 62690001 22000000  A,...aeabi.."...
 0010 05372d4d 00060a07 4d090212 04140115  .7-M....M.......
 0020 01170318 0119011a 011e0622 01        ...........".   
~~~

## Writing MCU startup file from scratch

Bare metal embedded lecture-3: Writing MCU startup file from scratch<br>
https://www.youtube.com/watch?v=2Hm8eEHsgls&t=69s

This lecture gets into the meat and potatoes of bare metal programming on ARM
microprocessors with an excellent explanation of the start up file.

This file, usually written in assembly, is supplied by the microprocessor 
vendor. One does not have to create them from scratch. However it is instructive
to see how it's done and, more importantly, why.

It is necessary to understand that the startup code is responsible for setting 
up the runtime environment for the main code. This can include hardware 
initialization such as the clock tree and floating point unit, if the processor
has one. More importantly, the startup code is responsible for the initialization
of the stack, variables that are assigned values, static constructors and
anything that is expected to be initialized before **main()** is called.








<!-- The older stuff ------------------------------------------------------- -->

## Ignore everything below this line

ELF file analyzers:
- arm-none-eabi-objdump
- arm-none-eabi-readelf
- arm-none-eabi-nm


Create a minimal C source file. This is an example file from https://en.wikipedia.org/wiki/Nm_(Unix).

~~~c
int global_var;
int global_var_init = 26;

static int static_var;
static int static_var_init = 25;

static int static_function()
{
  return 0;
}

int global_function(int p)
{
  static int local_static_var;
  static int local_static_var_init=5;

  local_static_var = p;

  return local_static_var_init + local_static_var;
}

int main(void)
{
  global_var = 1;
  static_var = 2;

  return 0;
}
~~~

Compile the source file with the appropriate compiler, including the appropriate
compiler flags.

In this case that would be the ARM gcc compiler supplied by ST.

~~~
arm-none-eabi-gcc -march=armv7-m -mcpu=cortex-m3 -mthumb -c main.c -o main.o
~~~

Consult the document ***Using the GNU Compiler Collection***[^1] for the
flags to use. In this case, because the target microprocessor is a 
STM32F100R8, we use:

<table>
  <tr>
    <td>-march=armv7-m</td>
    <td><i>specifies the name of the target ARM architecture</i></td>
  </tr>
  <tr>
    <td>-mcpu=cortex-m3</td>
    <td><i>specifies the name of the target ARM processor</i></td>
  </tr>
  <tr>
    <td>-mthumb</td>
    <td><i>generate code that executes in the Thumb state</i></td>
  </tr>
</table>

This will create the relocatable object file `main.o`.

This, of course, does nothing because it has not been linked with the necessary
startup code. Still we can use some of the binary utilities tools to look at the code generated.

For this we can use:

- `nm` lists the *symbols* from object files
- `objdump` displays information about one or more object files
- `readelf` displays information about one or more ELF format object files

The next example is displaying the symbols using `nm`.

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

## main.o ELF 

~~~c
00000000: 7f45 4c46 0101 0100 0000 0000 0000 0000  .ELF............
00000010: 0100 2800 0100 0000 0000 0000 0000 0000  ..(.............
00000020: 9401 0000 0000 0005 3400 0000 0000 2800  ........4.....(.
00000030: 0900 0800 80b4 00af fee7 0047 4343 3a20  ...........GCC: 
00000040: 2847 4e55 2054 6f6f 6c73 2066 6f72 2053  (GNU Tools for S
00000050: 544d 3332 2031 322e 332e 7265 6c31 2e32  TM32 12.3.rel1.2
00000060: 3032 3430 3932 362d 3137 3135 2920 3132  0240926-1715) 12
00000070: 2e33 2e31 2032 3032 3330 3632 3600 412c  .3.1 20230626.A,
00000080: 0000 0061 6561 6269 0001 2200 0000 0537  ...aeabi.."....7
00000090: 2d4d 0006 0a07 4d09 0212 0414 0115 0117  -M....M.........
000000a0: 0318 0119 011a 011e 0622 0100 0000 0000  ........."......
000000b0: 0000 0000 0000 0000 0000 0000 0100 0000  ................
000000c0: 0000 0000 0000 0000 0400 f1ff 0000 0000  ................
000000d0: 0000 0000 0000 0000 0300 0100 0000 0000  ................
000000e0: 0000 0000 0000 0000 0300 0200 0000 0000  ................
000000f0: 0000 0000 0000 0000 0300 0300 0800 0000  ................
00000100: 0000 0000 0000 0000 0000 0100 0000 0000  ................
00000110: 0000 0000 0000 0000 0300 0400 0000 0000  ................
00000120: 0000 0000 0000 0000 0300 0500 0b00 0000  ................
00000130: 0100 0000 0600 0000 1200 0100 006d 6169  .............mai
00000140: 6e2e 6300 2474 006d 6169 6e00 002e 7379  n.c.$t.main...sy
00000150: 6d74 6162 002e 7374 7274 6162 002e 7368  mtab..strtab..sh
00000160: 7374 7274 6162 002e 7465 7874 002e 6461  strtab..text..da
00000170: 7461 002e 6273 7300 2e63 6f6d 6d65 6e74  ta..bss..comment
00000180: 002e 4152 4d2e 6174 7472 6962 7574 6573  ..ARM.attributes
00000190: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000001a0: 0000 0000 0000 0000 0000 0000 0000 0000  ................
000001b0: 0000 0000 0000 0000 0000 0000 1b00 0000  ................
000001c0: 0100 0000 0600 0000 0000 0000 3400 0000  ............4...
000001d0: 0600 0000 0000 0000 0000 0000 0200 0000  ................
000001e0: 0000 0000 2100 0000 0100 0000 0300 0000  ....!...........
000001f0: 0000 0000 3a00 0000 0000 0000 0000 0000  ....:...........
00000200: 0000 0000 0100 0000 0000 0000 2700 0000  ............'...
00000210: 0800 0000 0300 0000 0000 0000 3a00 0000  ............:...
00000220: 0000 0000 0000 0000 0000 0000 0100 0000  ................
00000230: 0000 0000 2c00 0000 0100 0000 3000 0000  ....,.......0...
00000240: 0000 0000 3a00 0000 4400 0000 0000 0000  ....:...D.......
00000250: 0000 0000 0100 0000 0100 0000 3500 0000  ............5...
00000260: 0300 0070 0000 0000 0000 0000 7e00 0000  ...p........~...
00000270: 2d00 0000 0000 0000 0000 0000 0100 0000  -...............
00000280: 0000 0000 0100 0000 0200 0000 0000 0000  ................
00000290: 0000 0000 ac00 0000 9000 0000 0700 0000  ................
000002a0: 0800 0000 0400 0000 1000 0000 0900 0000  ................
000002b0: 0300 0000 0000 0000 0000 0000 3c01 0000  ............<...
000002c0: 1000 0000 0000 0000 0000 0000 0100 0000  ................
000002d0: 0000 0000 1100 0000 0300 0000 0000 0000  ................
000002e0: 0000 0000 4c01 0000 4500 0000 0000 0000  ....L...E.......
000002f0: 0000 0000 0100 0000 0000 0000 0a         .............
~~~

<!-- Appendix -------------------------------------------------------------- -->
[^1]: https://gcc.gnu.org/onlinedocs/