/* -------------------------------------------------------------------------- */
/* file        main.c                                                         */
/* -------------------------------------------------------------------------- */
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

// -----------------------------------------------------------------------------
//  main
//
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