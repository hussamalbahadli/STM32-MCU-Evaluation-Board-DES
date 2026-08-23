/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    PWM2LOGIC_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Hussam Ali
 *  Date    : 8/23/2026
 *  Vertion : 1.0
 *  Layer   : HAL
 *  SWC     : PWM2LOGIC
 *
 */

#ifndef PWM2LOGIC_INTERFACE_H
#define PWM2LOGIC_INTERFACE_H

/*==================================================================*/
/*  Converts a PWM pulse from an RC receiver or flight controller   */
/*  into a simple logic level  ( 0 or 1 )                           */
/*                                                                  */
/*      pulse width  <=  800 us   ->  output 0                      */
/*      pulse width  >= 1900 us   ->  output 1                      */
/*      between the two           ->  stays as-is                  */
/*      no signal                 ->  output 0  ( failsafe )        */
/*==================================================================*/

#define PWM2LOGIC_STATE_LOW     0
#define PWM2LOGIC_STATE_HIGH    1

/*
 * Brief      : configures the input pin and output pin and starts the ICU
 * Hint       : enable RCC clocks in main before calling it
 */
void PWM2LOGIC_voidInit(void);

/*
 * Brief      : reads the pulse and updates the output
 *              called continuously inside the main loop
 */
void PWM2LOGIC_voidUpdate(void);

/*
 * Brief      : the current state of the output
 * Return     : PWM2LOGIC_STATE_LOW  or  PWM2LOGIC_STATE_HIGH
 */
u8 PWM2LOGIC_u8GetState(void);

/*
 * Brief      : the last pulse width read ― for debugging only
 * Return     : in microseconds
 */
u16 PWM2LOGIC_u16GetLastPulse(void);

#endif /* PWM2LOGIC_INTERFACE_H */
