/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    main.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Hussam Ali
 *  Date    : 8/23/2026
 *  Vertion : 1.0
 *  Layer   : APP
 *  SWC     : SOURCE MAIN
 *
 */

/*
 *  Example 01 : LED blink
 *  Wiring : LED on PB8  and  LED on PB9   ( with a 330 ohm resistor )
 *            button on PA0 to GND
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"

void APP_voidDelay(u32 Copy_u32Count);

int main(void)
{
    /* 1- system clock */
    RCC_voidInitSysClock();

    /* 2- port clocks ― without them nothing after this works */
    RCC_voidEnablePeripheralClock(APB2_BUS, GPIOA_RCC);
    RCC_voidEnablePeripheralClock(APB2_BUS, GPIOB_RCC);

    /* 3- pin configuration */
    GPIO_SetPinDirection(GPIOB, PIN8, OUTPUT_SPEED_2MHZ_PP);
    GPIO_SetPinDirection(GPIOB, PIN9, OUTPUT_SPEED_2MHZ_PP);
    GPIO_SetPinDirection(GPIOA, PIN0, INPUT_PULLUP_PULLDOWN);

    /* in pull up / pull down mode :  ODR = 1  selects pull up */
    GPIO_SetPinValue(GPIOA, PIN0, GPIO_HIGH);

    while (1)
    {
        /* button pressed  ->  the pin becomes 0 */
        if (GPIO_GetPinValue(GPIOA, PIN0) == GPIO_LOW)
        {
            GPIO_SetPinValue(GPIOB, PIN8, GPIO_HIGH);
            GPIO_SetPinValue(GPIOB, PIN9, GPIO_HIGH);
        }
        else
        {
            GPIO_TogglePinValue(GPIOB, PIN8);
            GPIO_TogglePinValue(GPIOB, PIN9);
            APP_voidDelay(200000);
        }
    }
}

/*
 *  Just a temporary delay for testing.
 *  volatile is essential: without it the compiler removes the whole loop at -O2
 *  ( and this is exactly the topic of LEC-9 )
 *  The correct alternative : the SysTick driver ― the next lesson.
 */
void APP_voidDelay(u32 Copy_u32Count)
{
    volatile u32 Local_u32Counter = 0;

    for (Local_u32Counter = 0; Local_u32Counter < Copy_u32Count; Local_u32Counter++)
    {
        /* nothing */
    }
}
