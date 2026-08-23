/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    PWM2LOGIC_config.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Hussam Ali
 *  Date    : 8/23/2026
 *  Vertion : 1.0
 *  Layer   : HAL
 *  SWC     : PWM2LOGIC
 *
 */

#ifndef PWM2LOGIC_CONFIG_H
#define PWM2LOGIC_CONFIG_H

/*==================================================================*/
/*                        Input pin                                 */
/*  Must match the timer chosen in ICU_config.h :                   */
/*      TIM2 -> PA0    TIM3 -> PA6    TIM4 -> PB6                   */
/*==================================================================*/
#define PWM2LOGIC_u8_IN_PORT        GPIOA
#define PWM2LOGIC_u8_IN_PIN         PIN0


/*==================================================================*/
/*                        Output pin                                 */
/*==================================================================*/
#define PWM2LOGIC_u8_OUT_PORT       GPIOB
#define PWM2LOGIC_u8_OUT_PIN        PIN0


/*==================================================================*/
/*                      Output type                                  */
/*                                                                  */
/*  PWM2LOGIC_OUT_PUSH_PULL_3V3                                     */
/*      Direct 0 / 3.3V output. No external component needed.       */
/*                                                                  */
/*  PWM2LOGIC_OUT_OPEN_DRAIN_5V                                     */
/*      The pin only pulls to 0V, and needs a 4.7k resistor         */
/*      from the pin to +5V. The result is a true 0 / 5V output.    */
/*      Note : the logic is electrically inverted ― the code handles it. */
/*==================================================================*/
#define PWM2LOGIC_OUT_PUSH_PULL_3V3     0
#define PWM2LOGIC_OUT_OPEN_DRAIN_5V     1

#define PWM2LOGIC_u8_OUT_TYPE       PWM2LOGIC_OUT_PUSH_PULL_3V3


/*==================================================================*/
/*                        Thresholds                                 */
/*==================================================================*/
#define PWM2LOGIC_u16_LOW_THRESHOLD_US       800U
#define PWM2LOGIC_u16_HIGH_THRESHOLD_US     1900U

/* Any reading outside this range is considered noise and ignored */
#define PWM2LOGIC_u16_MIN_VALID_US           500U
#define PWM2LOGIC_u16_MAX_VALID_US          2500U

/* How many consecutive matching readings do we require before changing the output ?
 * 1 = instant switch       3 = good noise resistance ( recommended ) */
#define PWM2LOGIC_u8_AGREE_COUNT               3U

#endif /* PWM2LOGIC_CONFIG_H */
