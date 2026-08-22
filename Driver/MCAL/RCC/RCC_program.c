/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    RCC_program.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Hussam Ali
 *  Date    : 8/23/2026
 *  Vertion : 1.0
 *  Layer   : MCAL
 *  SWC     : RCC
 *
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"


/*==================================================================*/
/*                     RCC_voidInitSysClock                         */
/*==================================================================*/
void RCC_voidInitSysClock(void)
{

#if   RCC_u8_CLOCK_TYPE == RCC_CLOCK_HSI

    /* 1- شغّل المذبذب الداخلي */
    SET_BIT(RCC_CR, RCC_CR_HSION);

    /* 2- انتظر حتى يستقر */
    while (GET_BIT(RCC_CR, RCC_CR_HSIRDY) == 0);

    /* 3- اجعله مصدر ساعة النظام */
    RCC_CFGR &= ~(0b11UL << RCC_CFGR_SW);
    RCC_CFGR |=  ((u32)RCC_SW_HSI << RCC_CFGR_SW);


#elif RCC_u8_CLOCK_TYPE == RCC_CLOCK_HSE

    /* 1- شغّل الكرستالة الخارجية */
    SET_BIT(RCC_CR, RCC_CR_HSEON);

    /* 2- انتظر حتى تستقر
     *    ملاحظة : اذا لم تكن الكرستالة موجودة على البورد
     *    سيتوقف البرنامج هنا للأبد . هذا أول مكان تفحصه
     *    اذا تجمّد البرنامج عند الإقلاع .                    */
    while (GET_BIT(RCC_CR, RCC_CR_HSERDY) == 0);

    /* 3- اجعلها مصدر ساعة النظام */
    RCC_CFGR &= ~(0b11UL << RCC_CFGR_SW);
    RCC_CFGR |=  ((u32)RCC_SW_HSE << RCC_CFGR_SW);


#elif RCC_u8_CLOCK_TYPE == RCC_CLOCK_PLL

    /* 1- شغّل الكرستالة أولاً لأن الـ PLL سيأخذ منها */
    SET_BIT(RCC_CR, RCC_CR_HSEON);
    while (GET_BIT(RCC_CR, RCC_CR_HSERDY) == 0);

    /* 2- اطفئ الـ PLL قبل تغيير اعداداته ( لا يقبل التعديل وهو شغّال ) */
    CLR_BIT(RCC_CR, RCC_CR_PLLON);

    /* 3- مصدر الـ PLL = HSE بدون تقسيم */
    SET_BIT(RCC_CFGR, RCC_CFGR_PLLSRC);
    CLR_BIT(RCC_CFGR, RCC_CFGR_PLLXTPRE);

    /* 4- معامل الضرب */
    RCC_CFGR &= ~(0b1111UL << RCC_CFGR_PLLMUL);
    RCC_CFGR |=  ((u32)RCC_u8_PLL_MUL_VALUE << RCC_CFGR_PLLMUL);

    /* 5- الفلاش أبطأ من المعالج عند 72 ميغا
     *    Latency = 2  ضرورية فوق 48 ميغا
     *    بدونها : HardFault فوراً عند أول قراءة كود        */
    FLASH_ACR &= ~(0b111UL);
    FLASH_ACR |=  (0b010UL);

    /* 6- شغّل الـ PLL وانتظره */
    SET_BIT(RCC_CR, RCC_CR_PLLON);
    while (GET_BIT(RCC_CR, RCC_CR_PLLRDY) == 0);

    /* 7- اجعله مصدر ساعة النظام */
    RCC_CFGR &= ~(0b11UL << RCC_CFGR_SW);
    RCC_CFGR |=  ((u32)RCC_SW_PLL << RCC_CFGR_SW);

    /* 8- تأكد أن التبديل تمّ فعلاً */
    while (((RCC_CFGR >> RCC_CFGR_SWS) & 0b11UL) != RCC_SW_PLL);

#else
    #error "RCC_config.h : RCC_u8_CLOCK_TYPE غير صحيح"
#endif

}


/*==================================================================*/
/*                RCC_voidEnablePeripheralClock                     */
/*==================================================================*/
void RCC_voidEnablePeripheralClock(u8 Copy_u8BusID, u8 Copy_u8PerID)
{
    /* نفس شكل switch الذي استخدمناه في درايفر DIO على AVR */

    switch (Copy_u8BusID)
    {
    case AHB_BUS  :  SET_BIT(RCC_AHBENR  , Copy_u8PerID);  break;
    case APB1_BUS :  SET_BIT(RCC_APB1ENR , Copy_u8PerID);  break;
    case APB2_BUS :  SET_BIT(RCC_APB2ENR , Copy_u8PerID);  break;
    }
}


/*==================================================================*/
/*                RCC_voidDisablePeripheralClock                    */
/*==================================================================*/
void RCC_voidDisablePeripheralClock(u8 Copy_u8BusID, u8 Copy_u8PerID)
{
    switch (Copy_u8BusID)
    {
    case AHB_BUS  :  CLR_BIT(RCC_AHBENR  , Copy_u8PerID);  break;
    case APB1_BUS :  CLR_BIT(RCC_APB1ENR , Copy_u8PerID);  break;
    case APB2_BUS :  CLR_BIT(RCC_APB2ENR , Copy_u8PerID);  break;
    }
}
