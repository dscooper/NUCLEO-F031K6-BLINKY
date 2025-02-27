/**
 * @file          gpio.h
 * @author        you@domain.com
 * @brief 
 * @version       0.1
 * @date          2025-02-026
 * 
 * @copyright     Copyright (c) 2025
 */
#if !defined(GPIO_H)
#define   GPIO_H
#include  <stdint.h>
#include  <stdbool.h>

/**
 * @brief         Set the selected IO pin high
 * @param pin     place holder, currently unused
 */
void Set_Pin(void);

/**
 * @brief         Reset the selected IO pin high
 * @param pin     place holder, currently unused
 */
void Reset_Pin(void);

/**
 * @brief         Initialize PORTAB     
 * 
 */
void Gpio_PortB_Init(void);

/**
 * @brief       Returns the state of the selected IO pin.
 * @return      <b>true</b> if the IO pin is set high, 
 *              <b>false</b> otherwise. 
 */
bool Is_Pin_Set(void);

#endif  // GPIO_H