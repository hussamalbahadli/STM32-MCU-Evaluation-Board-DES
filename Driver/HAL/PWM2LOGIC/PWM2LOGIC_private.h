/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    PWM2LOGIC_private.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Hussam Ali
 *  Date    : 8/23/2026
 *  Vertion : 1.0
 *  Layer   : HAL
 *  SWC     : PWM2LOGIC
 *
 */

#ifndef PWM2LOGIC_PRIVATE_H
#define PWM2LOGIC_PRIVATE_H

/* This layer never touches any register ― everything goes through GPIO and ICU.
 * That's why this file only contains internal things not relevant to the user.
 * It exists here to keep the same architecture shape in every driver.        */

#define PWM2LOGIC_SIGNAL_OK        0
#define PWM2LOGIC_SIGNAL_LOST      1

#endif /* PWM2LOGIC_PRIVATE_H */
