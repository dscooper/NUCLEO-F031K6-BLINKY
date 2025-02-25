/* -----------------------------------------------------------------------------
 * startup_stm32f031k6.c
 */
#include  <stdint.h>
#include  "startup_stm32f031k6.h"
#include  "main.h"

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
void MemManage_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void) __attribute__((weak, alias("Default_Handler")));
//void WWDG_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void PVD_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void TAMPER_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void RTC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void FLASH_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void RCC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void EXTI0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void EXTI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void EXTI2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void EXTI3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void EXTI4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void DMA1_Channel1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void DMA1_Channel2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void DMA1_Channel3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void DMA1_Channel4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void DMA1_Channel5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void DMA1_Channel6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void DMA1_Channel7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void ADC1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void EXTI9_5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void TIM1_BRK_TIM15_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void TIM1_UP_TIM16_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void TIM1_TRG_COM_TIM17_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void TIM1_CC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void TIM2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void TIM3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void TIM4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void I2C1_EV_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void I2C1_ER_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void I2C2_EV_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void I2C2_ER_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void SPI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void SPI2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void USART1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void USART2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void USART3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void EXTI15_10_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void RTC_Alarm_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void CEC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void TIM6_DAC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
//void TIM7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));

uint32_t vectors[] __attribute__ ((section(".vector_tbl"))) = 
{
  (uint32_t)0x20002000,                                     /* 0x0000_0000    */
  (uint32_t)&Reset_Handler,                                 /* 0x0000_0004    */
  (uint32_t)&NMI_Handler,                                   /* 0x0000_0008    */
  (uint32_t)&HardFault_Handler,                             /* 0x0000_000C    */
  (uint32_t)&MemManage_Handler,                             /* 0x0000_0010    */
  (uint32_t)&BusFault_Handler,                              /* 0x0000_0014    */
  (uint32_t)&UsageFault_Handler,                            /* 0x0000_0018    */ 
  (uint32_t)0U,                                             /* 0x0000_001C    */
  (uint32_t)0U,                                             /* 0x0000_0020    */
  (uint32_t)0U,                                             /* 0x0000_0024    */
  (uint32_t)0U,                                             /* 0x0000_0028    */
  (uint32_t)&SVC_Handler,                                   /* 0x0000_002C    */
  (uint32_t)&DebugMon_Handler,                              /* 0x0000_0030    */
  (uint32_t)0U,                                             /* 0x0000_0034    */
  (uint32_t)&PendSV_Handler,                                /* 0x0000_0038    */
  (uint32_t)&SysTick_Handler,                               /* 0x0000_003C    */
//  (uint32_t)&WWDG_IRQHandler,                               /* 0x0000_0040    */
//  (uint32_t)&PVD_IRQHandler,                                /* 0x0000_0044    */
//  (uint32_t)&TAMPER_IRQHandler,                             /* 0x0000_0048    */
//  (uint32_t)&RTC_IRQHandler,                                /* 0x0000_004C    */
//  (uint32_t)&FLASH_IRQHandler,                              /* 0x0000_0050    */
//  (uint32_t)&RCC_IRQHandler,                                /* 0x0000_0054    */
//  (uint32_t)&EXTI0_IRQHandler,                              /* 0x0000_0058    */
//  (uint32_t)&EXTI1_IRQHandler,                              /* 0x0000_005C    */
//  (uint32_t)&EXTI2_IRQHandler,                              /* 0x0000_0060    */
//  (uint32_t)&EXTI3_IRQHandler,                              /* 0x0000_0064    */
//  (uint32_t)&EXTI4_IRQHandler,                              /* 0x0000_0068    */
//  (uint32_t)&DMA1_Channel1_IRQHandler,                      /* 0x0000_006C    */
//  (uint32_t)&DMA1_Channel2_IRQHandler,                      /* 0x0000_0070    */
//  (uint32_t)&DMA1_Channel3_IRQHandler,                      /* 0x0000_0074    */
//  (uint32_t)&DMA1_Channel4_IRQHandler,                      /* 0x0000_0078    */
//  (uint32_t)&DMA1_Channel5_IRQHandler,                      /* 0x0000_007C    */
//  (uint32_t)&DMA1_Channel6_IRQHandler,                      /* 0x0000_0080    */
//  (uint32_t)&DMA1_Channel7_IRQHandler,                      /* 0x0000_0084    */
//  (uint32_t)&ADC1_IRQHandler,                               /* 0x0000_0088    */
//  (uint32_t)0U,                                             /* 0x0000_008C    */
//  (uint32_t)0U,                                             /* 0x0000_0090    */
//  (uint32_t)0U,                                             /* 0x0000_0094    */
//  (uint32_t)0U,                                             /* 0x0000_0098    */
//  (uint32_t)&EXTI9_5_IRQHandler,                            /* 0x0000_009C    */
//  (uint32_t)&TIM1_BRK_TIM15_IRQHandler,                     /* 0x0000_00A0    */
//  (uint32_t)&TIM1_UP_TIM16_IRQHandler,                      /* 0x0000_00A4    */
//  (uint32_t)&TIM1_TRG_COM_TIM17_IRQHandler,                 /* 0x0000_00A8    */
//  (uint32_t)&TIM1_CC_IRQHandler,                            /* 0x0000_00AC    */
//  (uint32_t)&TIM2_IRQHandler,                               /* 0x0000_00B0    */
//  (uint32_t)&TIM3_IRQHandler,                               /* 0x0000_00B4    */
//  (uint32_t)&TIM4_IRQHandler,                               /* 0x0000_00B8    */
//  (uint32_t)&I2C1_EV_IRQHandler,                            /* 0x0000_00BC    */
//  (uint32_t)&I2C1_ER_IRQHandler,                            /* 0x0000_00C0    */
//  (uint32_t)&I2C2_EV_IRQHandler,                            /* 0x0000_00C4    */
//  (uint32_t)&I2C2_ER_IRQHandler,                            /* 0x0000_00C8    */
//  (uint32_t)&SPI1_IRQHandler,                               /* 0x0000_00CC    */
//  (uint32_t)&SPI2_IRQHandler,                               /* 0x0000_00D0    */
//  (uint32_t)&USART1_IRQHandler,                             /* 0x0000_00D4    */
//  (uint32_t)&USART2_IRQHandler,                             /* 0x0000_00D8    */
//  (uint32_t)&USART3_IRQHandler,                             /* 0x0000_00DC    */
//  (uint32_t)&EXTI15_10_IRQHandler,                          /* 0x0000_00E0    */
//  (uint32_t)&RTC_Alarm_IRQHandler,                          /* 0x0000_00E4    */
//  (uint32_t)&CEC_IRQHandler,                                /* 0x0000_00E8    */
//  (uint32_t)0U,                                             /* 0x0000_00EC    */
//  (uint32_t)0U,                                             /* 0x0000_00F0    */ 
//  (uint32_t)0U,                                             /* 0x0000_00F4    */ 
//  (uint32_t)0U,                                             /* 0x0000_00F8    */ 
//  (uint32_t)0U,                                             /* 0x0000_00FC    */ 
//  (uint32_t)0U,                                             /* 0x0000_0100    */ 
//  (uint32_t)0U,                                             /* 0x0000_0104    */ 
//  (uint32_t)0U,                                             /* 0x0000_0108    */ 
//  (uint32_t)0U,                                             /* 0x0000_010C    */ 
//  (uint32_t)0U,                                             /* 0x0000_0110    */ 
//  (uint32_t)0U,                                             /* 0x0000_0114    */ 
//  (uint32_t)&TIM6_DAC_IRQHandler,                           /* 0x0000_0118    */
//  (uint32_t)&TIM7_IRQHandler                                /* 0x0000_011C    */
};

#define VECTOR_TABLE_SIZE   sizeof(vectors)/sizeof(uint32_t)

// -----------------------------------------------------------------------------
//  Reset exception service routine
//
void Reset_Handler(void)
{
  // copy .data section to SRAM
  uint32_t size   = &_edata - &_sdata;
  uint8_t* p_dest = (uint8_t*)&_sdata;
  uint8_t* p_src  = (uint8_t*)&_etext;

  for (uint32_t i=0; i<size; i++)
  {
    *p_dest++ = *p_src++;
  }

  // initialize the .bss section
  size    = &_ebss - &_sbss;
  p_dest = (uint8_t*)&_sbss;

  for (uint32_t i=0; i<size; i++)
  {
    *p_dest++ = 0;
  }
 
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
