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
 *  مثال 01 : وميض LED
 *  التوصيل : LED على PB8  و  LED على PB9   ( مع مقاومة 330 اوم )
 *            زر على PA0 الى GND
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"

void APP_voidDelay(u32 Copy_u32Count);

int main(void)
{
    /* 1- ساعة النظام */
    RCC_voidInitSysClock();

    /* 2- ساعة البورتات ــ بدونها لا يعمل أي شيء بعدها */
    RCC_voidEnablePeripheralClock(APB2_BUS, GPIOA_RCC);
    RCC_voidEnablePeripheralClock(APB2_BUS, GPIOB_RCC);

    /* 3- ضبط البنّات */
    GPIO_SetPinDirection(GPIOB, PIN8, OUTPUT_SPEED_2MHZ_PP);
    GPIO_SetPinDirection(GPIOB, PIN9, OUTPUT_SPEED_2MHZ_PP);
    GPIO_SetPinDirection(GPIOA, PIN0, INPUT_PULLUP_PULLDOWN);

    /* في وضع pull up / pull down :  ODR = 1  تختار pull up */
    GPIO_SetPinValue(GPIOA, PIN0, GPIO_HIGH);

    while (1)
    {
        /* الزر مضغوط  ->  الطرف يصير 0 */
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
 *  تأخير مؤقت فقط للتجربة .
 *  volatile ضرورية : بدونها يحذف المترجم الحلقة كاملة عند -O2
 *  ( وهذا بالضبط موضوع LEC-9 )
 *  البديل الصحيح : درايفر SysTick ــ وهو الدرس القادم .
 */
void APP_voidDelay(u32 Copy_u32Count)
{
    volatile u32 Local_u32Counter = 0;

    for (Local_u32Counter = 0; Local_u32Counter < Copy_u32Count; Local_u32Counter++)
    {
        /* لا شيء */
    }
}
