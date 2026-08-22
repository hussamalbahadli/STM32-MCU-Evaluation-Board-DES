/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    main.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Hussam Ali
 *  Date    : 8/23/2026
 *  Vertion : 1.0
 *  Layer   : APP
 *  SWC     : Example 02 - PWM To Logic
 *
 *  الوظيفة : يقرأ نبضة PWM قادمة من Ashura 1 ويحوّلها إلى مستوى لوجك
 *
 *  التوصيل :
 *      PA0  <--  مخرج PWM من Ashura 1      ( PA0 متحمّل لـ 5 فولت )
 *      PB0  -->  الجهاز المطلوب تشغيله
 *      GND  <->  أرضي مشترك  ( إلزامي )
 *
 *      LED على PB1 يومض ليؤكّد أن البرنامج حي
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

    /* 1- ساعة النظام */
    RCC_voidInitSysClock();

    /* 2- السواعد :
     *      GPIOA و GPIOB على APB2
     *      TIM2 على APB1                     */
    RCC_voidEnablePeripheralClock(APB2_BUS, GPIOA_RCC);
    RCC_voidEnablePeripheralClock(APB2_BUS, GPIOB_RCC);
    RCC_voidEnablePeripheralClock(APB1_BUS, TIM2_RCC);

    /* 3- بن اضافي للوميض ــ يثبت أن البرنامج لم يتجمّد */
    GPIO_SetPinDirection(GPIOB, PIN1, OUTPUT_SPEED_2MHZ_PP);

    /* 4- شغّل المحوّل */
    PWM2LOGIC_voidInit();

    while (1)
    {
        /* كل ما يلزم : نداء واحد في الحلقة */
        PWM2LOGIC_voidUpdate();

        /* وميض بطيء للتأكّد أن الحلقة تدور */
        Local_u32Blink++;
        if (Local_u32Blink >= 100000UL)
        {
            Local_u32Blink = 0;
            GPIO_TogglePinValue(GPIOB, PIN1);
        }
    }
}

/*
 *  التحقّق خطوة بخطوة
 *  --------------------------------------------------------------
 *  1. اوقف البرنامج بالـ debugger وافتح  Peripherals -> TIM2 :
 *         PSC = 7        ( عند ساعة 8 ميغا )
 *         ARR = 0xFFFF
 *         CCR1 ~ 20000   ( دورة السيرفو 20 ملي ثانية )
 *         CCR2 ~ 1000 .. 2000   ( عرض النبضة )
 *
 *  2. اذا كانت CCR2 تساوي تقريباً 9000 بدل 1000 :
 *         السبب هو  ICU_u32_TIMER_CLOCK_HZ  في ICU_config.h
 *         ( ساعة النظام صارت 72 ميغا والملف ما زال يقول 8 ميغا )
 *
 *  3. اذا كانت CCR2 = 0 دائماً :
 *         - ساعة TIM2 غير مفتوحة في RCC
 *         - أو البن PA0 ليس INPUT_FLOATING
 *         - أو لا يوجد أرضي مشترك مع Ashura 1
 *
 *  4. اذا كان الخرج يرفرف :
 *         زد  PWM2LOGIC_u8_AGREE_COUNT  من 3 إلى 5
 */
