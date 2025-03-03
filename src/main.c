/* -------------------------------------------------------------------------- */
/* file        main.c                                                         */
/* -------------------------------------------------------------------------- */
#include  <stdint.h>
#include  "stm32f031x6.h"
#include  "gpio.h"
#include  "systick.h"
#include  "main.h"

volatile uint32_t systick_timeout_flag = 0ul;

// -----------------------------------------------------------------------------
//  main
//
int main(void)
{
  /* This part of CMSIS-Core is not used in this simple example
   // Calculate the SystemCoreClock variable
   SystemCoreClockUpdate();
   */

  // Initialize the SysTick module
  SysTick_Init();

  // Initialize the IO port  
  Gpio_PortB_Init();

  do 
  {
    if (systick_timeout_flag)
    {
      if (Is_Pin_Set())
      {
        Reset_Pin();
      }
    }
    else
    {
      if (!Is_Pin_Set())
      {
        Set_Pin();
      }
    }
  }
  while(1);

  return 0; // never reached
} // main