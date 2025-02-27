/*
 * Routines to control gpio
 */
#include  "stm32f031x6.h"
//#include  "stm32f401xe.h"             // __FPU_PRESENT before core_cm4.h
//#include  "system_stm32f4xx.h"        // SystemCoreClock
//#include  "core_cm4.h"                // SysTick_Config
#include  "gpio.h"

/*
 *  Set the selected IO pin high
 */
void Set_Pin(void)
{
  uint32_t _t1;

  _t1 = GPIOB->ODR;
  _t1 |= GPIO_ODR_3;
  GPIOB->ODR = _t1;
} // Set_Pin

/*
 *  Reset the selected IO pin high
 */
void Reset_Pin(void)
{
  uint32_t _t1;

  _t1 = GPIOB->ODR;
  _t1 &= ~GPIO_ODR_3;
  GPIOB->ODR = _t1;
} // Reset_Pin

/*
 * 
 */
bool Is_Pin_Set(void)
{
  uint32_t _t1;

  _t1 = GPIOB->ODR;
  _t1 &= GPIO_ODR_3;

  return (_t1 == 0ul) ? false : true;
} // Is_Pin_Set

/*
 * PB3 is connected to LD3 (Green LED)
 */
void Gpio_PortB_Init(void)
{
  uint32_t _t1;

  // turn on the clock
  RCC->AHBENR |= RCC_AHBENR_GPIOBEN;


  // set PORT B3 to General purpose output mode
  _t1 = (uint32_t)GPIOB->MODER;
  _t1 |= ((uint32_t)GPIO_MODER_MODER3_0);
  GPIOB->MODER = _t1;

  // set PORT B3 to Output push-pull (reset state)
  _t1 = GPIOB->OTYPER;
  _t1 &= ~((uint32_t)GPIO_OTYPER_OT_3);
  GPIOB->OTYPER = _t1;

  // set PORT B3 to Low speed
  _t1 = GPIOB->OSPEEDR;
  _t1 &= ~((uint32_t)GPIO_OSPEEDR_OSPEEDR3);
  GPIOB->OSPEEDR = _t1;

  // set PORT B3 to No pull-up, pull-down
  _t1 = GPIOB->PUPDR;
  _t1 &= ~((uint32_t)GPIO_PUPDR_PUPDR3);
  GPIOB->PUPDR = _t1;
} // Gpio_PortB_Init

