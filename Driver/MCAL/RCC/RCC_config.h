/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    RCC_config.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Hussam Ali
 *  Date    : 8/23/2026
 *  Vertion : 1.0
 *  Layer   : MCAL
 *  SWC     : RCC
 *
 */

#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H

/*==================================================================*/
/*  Choose the system clock source ― one option only                */
/*                                                                  */
/*      RCC_CLOCK_HSI   ->  Internal oscillator  8 MHz               */
/*                          No crystal needed. Simplest to start    */
/*                                                                  */
/*      RCC_CLOCK_HSE   ->  External crystal  8 MHz                 */
/*                          More accurate ― must be present on board*/
/*                                                                  */
/*      RCC_CLOCK_PLL   ->  HSE multiplied by 9  =  72 MHz           */
/*                          Highest speed. Also needs flash tuning  */
/*==================================================================*/

#define RCC_CLOCK_HSI     0
#define RCC_CLOCK_HSE     1
#define RCC_CLOCK_PLL     2

#define RCC_u8_CLOCK_TYPE     RCC_CLOCK_HSI


/*  Only used if we chose RCC_CLOCK_PLL
 *  The value 0b0111 means multiply by 9   ( 8 MHz * 9 = 72 MHz )
 *  Rule : multiplier = value + 2                                  */
#define RCC_u8_PLL_MUL_VALUE    0b0111


#endif /* RCC_CONFIG_H */
