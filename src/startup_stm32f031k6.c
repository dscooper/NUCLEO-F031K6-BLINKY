/* -----------------------------------------------------------------------------
 * startup_stm32f031k6.c
 */
#include  <stdint.h>
#include  "startup_stm32f031k6.h"
#include  "system_stm32f0xx.h"
#include  "main.h"
#include  "systick.h"

/*
 *  For the STM32F031K6 microcontroller there are 4kB of SRAM
 */
#define   SRAM_START    0x20000000U
#define   SRAM_SIZE     (4 * 1024)    // 4 kB
#define   SRAM_END      ((SRAM_START + SRAM_SIZE))

/* 
 *  The top of the stack starts at the end of SRAM - it grows downward
 */
#define   STACK_START   SRAM_END

/*
 *  External declarations, from the linker script
 */
extern  uint32_t  _etext;
extern  uint32_t  _sdata;
extern  uint32_t  _edata;
extern  uint32_t  _sbss;
extern  uint32_t  _ebss;

/*
 *  aliased function place holders
 */
void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void) __attribute__((weak, alias("Default_Handler")));
void WWDG_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PVD_Handler(void) __attribute__((weak, alias("Default_Handler")));
void RTC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void FLASH_Handler(void) __attribute__((weak, alias("Default_Handler")));
void RCC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI0_1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI2_3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI4_15_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA_CH1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA_CH2_3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA_CH4_5_Handler(void) __attribute__((weak, alias("Default_Handler")));
void ADC_COMP_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_BRK_UP_TRG_COM_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_CC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM14_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM16_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM17_Handler(void) __attribute__((weak, alias("Default_Handler")));
void I2C1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SPI1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void USART1_Handler(void) __attribute__((weak, alias("Default_Handler")));

/*
 *  The vector table
 */
uint32_t vectors[] __attribute__ ((section(".vector_tbl"))) = 
{
  (uint32_t)SRAM_END,                                       /* 0x0000_0000    */
  (uint32_t)&Reset_Handler,                                 /* 0x0000_0004    */
  (uint32_t)&NMI_Handler,                                   /* 0x0000_0008    */
  (uint32_t)&HardFault_Handler,                             /* 0x0000_000C    */
  (uint32_t)0U,                                             /* 0x0000_0010    */
  (uint32_t)0U,                                             /* 0x0000_0014    */
  (uint32_t)0U,                                             /* 0x0000_0018    */ 
  (uint32_t)0U,                                             /* 0x0000_001C    */
  (uint32_t)0U,                                             /* 0x0000_0020    */
  (uint32_t)0U,                                             /* 0x0000_0024    */
  (uint32_t)0U,                                             /* 0x0000_0028    */
  (uint32_t)&SVC_Handler,                                   /* 0x0000_002C    */
  (uint32_t)0U,                                             /* 0x0000_0030    */
  (uint32_t)0U,                                             /* 0x0000_0034    */
  (uint32_t)&PendSV_Handler,                                /* 0x0000_0038    */
  (uint32_t)&SysTick_Handler,                               /* 0x0000_003C    */
  (uint32_t)&WWDG_Handler,                                  /* 0x0000_0040    */
  (uint32_t)&PVD_Handler,                                   /* 0x0000_0044    */
  (uint32_t)&RTC_Handler,                                   /* 0x0000_0048    */
  (uint32_t)&FLASH_Handler,                                 /* 0x0000_004C    */
  (uint32_t)&RCC_Handler,                                   /* 0x0000_0050    */
  (uint32_t)&EXTI0_1_Handler,                               /* 0x0000_0054    */
  (uint32_t)&EXTI2_3_Handler,                               /* 0x0000_0058    */
  (uint32_t)&EXTI4_15_Handler,                              /* 0x0000_005C    */
  (uint32_t)0,                                              /* 0x0000_0060    */
  (uint32_t)&DMA_CH1_Handler,                               /* 0x0000_0064    */
  (uint32_t)&DMA_CH2_3_Handler,                             /* 0x0000_0068    */
  (uint32_t)&DMA_CH4_5_Handler,                             /* 0x0000_006C    */
  (uint32_t)&ADC_COMP_Handler,                              /* 0x0000_0070    */
  (uint32_t)&TIM1_BRK_UP_TRG_COM_Handler,                   /* 0x0000_0074    */
  (uint32_t)&TIM1_CC_Handler,                               /* 0x0000_0078    */
  (uint32_t)&TIM2_Handler,                                  /* 0x0000_007C    */
  (uint32_t)&TIM3_Handler,                                  /* 0x0000_0080    */
  (uint32_t)0,                                              /* 0x0000_0084    */
  (uint32_t)0,                                              /* 0x0000_0088    */
  (uint32_t)&TIM14_Handler,                                 /* 0x0000_008C    */
  (uint32_t)0,                                              /* 0x0000_0090    */
  (uint32_t)&TIM16_Handler,                                 /* 0x0000_0094    */
  (uint32_t)&TIM17_Handler,                                 /* 0x0000_0098    */
  (uint32_t)&I2C1_Handler,                                  /* 0x0000_009C    */
  (uint32_t)0,                                              /* 0x0000_00A0    */
  (uint32_t)&SPI1_Handler,                                  /* 0x0000_00A4    */
  (uint32_t)0,                                              /* 0x0000_00A8    */
  (uint32_t)&USART1_Handler,                                /* 0x0000_00AC    */
  (uint32_t)0,                                              /* 0x0000_00B0    */
  (uint32_t)0,                                              /* 0x0000_00B4    */
  (uint32_t)0,                                              /* 0x0000_00B8    */
  (uint32_t)0,                                              /* 0x0000_00BC    */
};

#define VECTOR_TABLE_SIZE   sizeof(vectors)/sizeof(uint32_t)

// -----------------------------------------------------------------------------
//  Reset exception service routine
//
void Reset_Handler(void)
{
  // copy .data section to SRAM
  uint32_t size   = (uint32_t)&_edata - (uint32_t)&_sdata;
  uint8_t* p_dest = (uint8_t*)&_sdata;
  uint8_t* p_src  = (uint8_t*)&_etext;

  for (uint32_t i=0; i<size; i++)
  {
    *p_dest++ = *p_src++;
  }

  // initialize the .bss section
  size   = (uint32_t)&_ebss - (uint32_t)&_sbss;
  p_dest = (uint8_t*)&_sbss;

  for (uint32_t i=0; i<size; i++)
  {
    *p_dest++ = 0;
  }
 
  /* This part of CMSIS-Core is not used in this simple example
   // call the module initialization
   SystemInit(); // CMSIS system initialization
   */

  // call the main application
  main();
} // Reset_Handler

// -----------------------------------------------------------------------------
//  Default exception/interrupt service routine
//
void Default_Handler(void)
{
  while(1)
  {
    ;
  }
} // Default_Handler
