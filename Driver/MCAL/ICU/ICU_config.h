/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    ICU_config.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Hussam Ali
 *  Date    : 8/23/2026
 *  Vertion : 1.0
 *  Layer   : MCAL
 *  SWC     : ICU (Input Capture Unit)
 *
 */

#ifndef ICU_CONFIG_H
#define ICU_CONFIG_H

/*==================================================================*/
/*  Choose the timer ― each timer has a fixed pin that doesn't change */
/*                                                                  */
/*      ICU_TIMER2  ->  PA0                                         */
/*      ICU_TIMER3  ->  PA6                                         */
/*      ICU_TIMER4  ->  PB6                                         */
/*==================================================================*/

#define ICU_TIMER2      2
#define ICU_TIMER3      3
#define ICU_TIMER4      4

#define ICU_u8_TIMER_SELECT     ICU_TIMER2


/*==================================================================*/
/*  Clock frequency feeding the timer ( in Hertz )                  */
/*                                                                  */
/*  TIM2/3/4 are on the APB1 bus.                                    */
/*      if the system clock is HSI  ->  8000000                     */
/*      if you raised it to PLL 72 MHz ->  72000000                  */
/*                                                                  */
/*  A mistake here means every measurement is wrong by the same ratio. */
/*  If you read 9000 instead of 1000, the cause is this line, not the code. */
/*==================================================================*/
#define ICU_u32_TIMER_CLOCK_HZ      8000000UL

#endif /* ICU_CONFIG_H */
