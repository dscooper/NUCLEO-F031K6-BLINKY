/*
 *  TODO
 */
#include  <stdint.h>
#include  "stm32f031x6.h"
//#include  "stm32f401xe.h"             // __FPU_PRESENT before core_cm4.h
//#include  "system_stm32f4xx.h"        // SystemCoreClock
//#include  "core_cm4.h"                // SysTick_Config

// defined in main.c
extern volatile uint32_t systick_timeout_flag;

// This is the delay in milliseconds
static const uint32_t Delay = 500ul;  // OFF = 500ms, ON = 500ms

// counter variable, incremented every SystemCoreClock/Delay milliseconds
static volatile uint32_t systick_counter = 0ul;

// SysTick ISR
void SysTick_Handler(void)
{
  systick_counter++;
  
  if (systick_counter >= Delay)
  {
    systick_counter = 0ul;
    systick_timeout_flag ^= 1ul;
  }
}

// module initialization
void SysTick_Init(void)
{
  systick_counter = 0ul;
  SysTick_Config(SystemCoreClock/1000ul); // 1ms
}