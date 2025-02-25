
/* 
 *  Flash memory location and size
 */
__ROM_BASE = 0x08000000;
__ROM_SIZE = 0x00008000;    /* 32768 bytes */ 

/*
 *  Static RAM memory, location and size
 */
__RAM_BASE = 0x20000000;
__RAM_SIZE = 0x00001000;    /* 4096 bytes */

/*
 *  Definitions for the stack and the heap
 */
__STACK_SIZE = 0x00000400;  /* 1,024 bytes = 256 words, 512 half-words */
__HEAP_SIZE  = 0x00000C00;  /* 3,072 bytes = 768 words, 1,536 half-words */

/*
 *  Location and size of blocks of memory in the target.
 */
 MEMORY
{
  FLASH (rx)  : ORIGIN = __ROM_BASE, LENGTH = __ROM_SIZE
  SRAM  (rwx) : ORIGIN = __RAM_BASE, LENGTH = __RAM_SIZE
}

SECTIONS
{
  .text : 
  {
    KEEP(*(.vector_tbl))
    *(.text)
    *(.rodata)
    . = ALIGN(4);
    _etext = .;
  }> FLASH

  .data :
  {
    . = ALIGN(4);
    _sdata = .;
    *(.data)
    . = ALIGN(4);
    _edata = .;
  }> SRAM AT> FLASH

  .bss :
  {
    . = ALIGN(4);
    _sbss = .;
    *(.bss)
    . = ALIGN(4);
    _ebss = .;
  }> SRAM

}