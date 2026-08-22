/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    RCC_config.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Hussam Ali
 *  Date    : 8/23/2026
 *  Vertion : 1.0
 *  Layer   : MCAL
 *  SWC     : RCC
 *
 */

#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H

/*==================================================================*/
/*  اختر مصدر ساعة النظام ــ خيار واحد فقط                          */
/*                                                                  */
/*      RCC_CLOCK_HSI   ->  المذبذب الداخلي  8 MHz                  */
/*                          لا يحتاج كرستالة . الأبسط للبداية       */
/*                                                                  */
/*      RCC_CLOCK_HSE   ->  الكرستالة الخارجية  8 MHz               */
/*                          أدق ــ يجب أن تكون موجودة على البورد    */
/*                                                                  */
/*      RCC_CLOCK_PLL   ->  HSE مضروبة في 9  =  72 MHz              */
/*                          أعلى سرعة . تحتاج ضبط الفلاش أيضاً      */
/*==================================================================*/

#define RCC_CLOCK_HSI     0
#define RCC_CLOCK_HSE     1
#define RCC_CLOCK_PLL     2

#define RCC_u8_CLOCK_TYPE     RCC_CLOCK_HSI


/*  تُستخدم فقط اذا اخترنا RCC_CLOCK_PLL
 *  القيمة 0b0111 تعني الضرب في 9   ( 8 MHz * 9 = 72 MHz )
 *  القاعدة : المعامل = القيمة + 2                                  */
#define RCC_u8_PLL_MUL_VALUE    0b0111


#endif /* RCC_CONFIG_H */
