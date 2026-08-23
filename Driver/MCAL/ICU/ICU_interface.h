/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    ICU_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Hussam Ali
 *  Date    : 8/23/2026
 *  Vertion : 1.0
 *  Layer   : MCAL
 *  SWC     : ICU (Input Capture Unit)
 *
 */

#ifndef ICU_INTERFACE_H
#define ICU_INTERFACE_H

/*==================================================================*/
/*  ICU = Input Capture Unit                                        */
/*                                                                  */
/*  Measures the width of the incoming pulse in microseconds ― entirely in hardware. */
/*  No interrupts and no counting loops ― the timer runs on its own */
/*  and we read the result whenever we want.                       */
/*                                                                  */
/*  The pin used depends on the timer chosen in ICU_config.h :      */
/*      TIM2  ->  PA0                                               */
/*      TIM3  ->  PA6                                               */
/*      TIM4  ->  PB6                                               */
/*==================================================================*/

/*
 * Brief      : configures the timer in PWM Input mode
 * Parameters : void
 * Return     : void
 *
 * Hint       : enable the timer's clock and the port's clock in RCC before this function,
 *              and set the pin to INPUT_FLOATING.
 */
void ICU_voidInit(void);

/*
 * Brief      : pulse width ( the time the signal stayed high )
 * Return     : the value in microseconds  ―  a normal servo signal : 1000 .. 2000
 */
u16 ICU_u16GetPulseWidth(void);

/*
 * Brief      : length of the full period ( from one rising edge to the next )
 * Return     : the value in microseconds  ―  a normal servo signal : 20000
 */
u16 ICU_u16GetPeriod(void);

/*
 * Brief      : has the signal been lost ?
 * Return     : 1 if 65 ms passed with no rising edge at all
 *              0 if the signal is present
 */
u8 ICU_u8IsSignalLost(void);

#endif /* ICU_INTERFACE_H */
