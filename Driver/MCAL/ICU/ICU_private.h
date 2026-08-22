/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    ICU_private.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Hussam Ali
 *  Date    : 8/23/2026
 *  Vertion : 1.0
 *  Layer   : MCAL
 *  SWC     : ICU (Input Capture Unit)
 *
 */

#ifndef ICU_PRIVATE_H
#define ICU_PRIVATE_H

/*==================================================================*/
/*  السجلات فقط ــ المرجع : RM0008  Chapter 15 (TIM2..TIM5)         */
/*  نفس اسلوب GPIO_private.h بالضبط                                 */
/*==================================================================*/

#define TIM2_BASE_ADDRESS       0x40000000UL
#define TIM3_BASE_ADDRESS       0x40000400UL
#define TIM4_BASE_ADDRESS       0x40000800UL

/* نختار عنوان القاعدة حسب ما هو مكتوب في ICU_config.h */
#if   ICU_u8_TIMER_SELECT == ICU_TIMER2
    #define ICU_BASE_ADDRESS    TIM2_BASE_ADDRESS
#elif ICU_u8_TIMER_SELECT == ICU_TIMER3
    #define ICU_BASE_ADDRESS    TIM3_BASE_ADDRESS
#elif ICU_u8_TIMER_SELECT == ICU_TIMER4
    #define ICU_BASE_ADDRESS    TIM4_BASE_ADDRESS
#else
    #error "ICU_config.h : ICU_u8_TIMER_SELECT غير صحيح"
#endif


#define ICU_CR1     *((volatile u32*)(ICU_BASE_ADDRESS + 0x00))
#define ICU_SMCR    *((volatile u32*)(ICU_BASE_ADDRESS + 0x08))
#define ICU_SR      *((volatile u32*)(ICU_BASE_ADDRESS + 0x10))
#define ICU_EGR     *((volatile u32*)(ICU_BASE_ADDRESS + 0x14))
#define ICU_CCMR1   *((volatile u32*)(ICU_BASE_ADDRESS + 0x18))
#define ICU_CCER    *((volatile u32*)(ICU_BASE_ADDRESS + 0x20))
#define ICU_CNT     *((volatile u32*)(ICU_BASE_ADDRESS + 0x24))
#define ICU_PSC     *((volatile u32*)(ICU_BASE_ADDRESS + 0x28))
#define ICU_ARR     *((volatile u32*)(ICU_BASE_ADDRESS + 0x2C))
#define ICU_CCR1    *((volatile u32*)(ICU_BASE_ADDRESS + 0x34))
#define ICU_CCR2    *((volatile u32*)(ICU_BASE_ADDRESS + 0x38))


/*----------------- بتات CR1 -----------------*/
#define ICU_CR1_CEN         0     /* شغّل العدّاد                  */
#define ICU_CR1_URS         2     /* مصدر حدث التحديث             */

/*----------------- بتات SR ------------------*/
#define ICU_SR_UIF          0     /* علم فيضان العدّاد            */
#define ICU_SR_CC1IF        1     /* التقاط على القناة 1          */
#define ICU_SR_CC2IF        2     /* التقاط على القناة 2          */

/*----------------- بتات EGR -----------------*/
#define ICU_EGR_UG          0     /* توليد حدث تحديث يدوياً       */

/*----------------- حقول CCMR1 ---------------*/
#define ICU_CCMR1_CC1S      0     /* بتّان : اختيار مدخل القناة 1 */
#define ICU_CCMR1_IC1F      4     /* أربع بتات : مرشّح القناة 1   */
#define ICU_CCMR1_CC2S      8     /* بتّان : اختيار مدخل القناة 2 */
#define ICU_CCMR1_IC2F     12     /* أربع بتات : مرشّح القناة 2   */

/*----------------- بتات CCER ----------------*/
#define ICU_CCER_CC1E       0     /* تفعيل التقاط القناة 1        */
#define ICU_CCER_CC1P       1     /* 0 = حافة صاعدة               */
#define ICU_CCER_CC2E       4     /* تفعيل التقاط القناة 2        */
#define ICU_CCER_CC2P       5     /* 1 = حافة نازلة               */

/*----------------- حقول SMCR ----------------*/
#define ICU_SMCR_SMS        0     /* ثلاث بتات : وضع الـ slave    */
#define ICU_SMCR_TS         4     /* ثلاث بتات : مصدر الزناد      */

/*----------------- قيم جاهزة ----------------*/
#define ICU_CC1S_TI1     0b01     /* IC1 يقرأ من TI1  ( مباشر )   */
#define ICU_CC2S_TI1     0b10     /* IC2 يقرأ من TI1  ( معكوس )   */
#define ICU_FILTER_8     0b0011   /* يتجاهل النبضات الأقصر من 8 تكّات */
#define ICU_TS_TI1FP1    0b101    /* الزناد = الحافة الصاعدة لـ TI1 */
#define ICU_SMS_RESET    0b100    /* وضع Reset : الزناد يصفّر العدّاد */

#define ICU_ARR_MAX      0xFFFFUL

#endif /* ICU_PRIVATE_H */
