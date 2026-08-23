/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    main.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Hussam Ali
 *  Date    : 8/23/2026
 *  Vertion : 1.0
 *  Layer   : APP
 *  SWC     : Example 02 - PWM To Logic
 *
 *  Function : reads a PWM pulse coming from Ashura 1 and converts it to a logic level
 *
 *  Wiring :
 *      PA0  <--  PWM output from Ashura 1      ( PA0 tolerant up to 5V )
 *      PB0  -->  the device to be driven
 *      GND  <->  common ground  ( mandatory )
 *
 *      LED on PB1 blinks to confirm the program is alive
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "ICU_interface.h"
#include "PWM2LOGIC_interface.h"

int main(void)
{
    u32 Local_u32Blink = 0;

    /* 1- system clock */
    RCC_voidInitSysClock();

    /* 2- peripheral clocks:
     *      GPIOA and GPIOB on APB2
     *      TIM2 on APB1                     */
    RCC_voidEnablePeripheralClock(APB2_BUS, GPIOA_RCC);
    RCC_voidEnablePeripheralClock(APB2_BUS, GPIOB_RCC);
    RCC_voidEnablePeripheralClock(APB1_BUS, TIM2_RCC);

    /* 3- extra pin for blinking ― proves the program hasn't frozen */
    GPIO_SetPinDirection(GPIOB, PIN1, OUTPUT_SPEED_2MHZ_PP);

    /* 4- start the converter */
    PWM2LOGIC_voidInit();

    while (1)
    {
        /* all that's needed: one call in the loop */
        PWM2LOGIC_voidUpdate();

        /* slow blink to confirm the loop is running */
        Local_u32Blink++;
        if (Local_u32Blink >= 100000UL)
        {
            Local_u32Blink = 0;
            GPIO_TogglePinValue(GPIOB, PIN1);
        }
    }
}

/*
 *  Step-by-step verification
 *  --------------------------------------------------------------
 *  1. Pause the program with the debugger and open  Peripherals -> TIM2 :
 *         PSC = 7        ( at an 8 MHz clock )
 *         ARR = 0xFFFF
 *         CCR1 ~ 20000   ( servo period 20 ms )
 *         CCR2 ~ 1000 .. 2000   ( pulse width )
 *
 *  2. If CCR2 is approximately 9000 instead of 1000 :
 *         the cause is  ICU_u32_TIMER_CLOCK_HZ  in ICU_config.h
 *         ( the system clock became 72 MHz but the file still says 8 MHz )
 *
 *  3. If CCR2 = 0 always :
 *         - TIM2's clock is not enabled in RCC
 *         - or pin PA0 is not INPUT_FLOATING
 *         - or there is no common ground with Ashura 1
 *
 *  4. If the output flickers :
 *         increase  PWM2LOGIC_u8_AGREE_COUNT  from 3 to 5
 */
