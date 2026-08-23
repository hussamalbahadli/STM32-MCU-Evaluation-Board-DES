/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    GPIO_config.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Hussam Ali
 *  Date    : 8/23/2026
 *  Vertion : 1.0
 *  Layer   : MCAL
 *  SWC     : GPIO
 *
 */

#ifndef GPIO_CONFIG_H
#define GPIO_CONFIG_H

/*==================================================================*/
/*  How many ports does the chip you're using have?                 */
/*                                                                  */
/*      STM32F103C8  ( Blue Pill )  ->  GPIOC                       */
/*      STM32F103RB                 ->  GPIOD                       */
/*                                                                  */
/*  This define is for documentation only in this simplified version*/
/*  Calling a non-existent port doesn't raise an error ― it writes  */
/*  to an empty address.                                            */
/*==================================================================*/

#define GPIO_LAST_PORT      GPIOD

#endif /* GPIO_CONFIG_H */
