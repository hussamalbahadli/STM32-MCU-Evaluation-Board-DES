/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    PWM2LOGIC_program.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Hussam Ali
 *  Date    : 8/23/2026
 *  Vertion : 1.0
 *  Layer   : HAL
 *  SWC     : PWM2LOGIC
 *
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "ICU_interface.h"

#include "PWM2LOGIC_interface.h"
#include "PWM2LOGIC_config.h"
#include "PWM2LOGIC_private.h"


/* متغيّرات داخلية ــ تحتفظ بقيمتها بين الاستدعاءات */
static u8  PWM2LOGIC_u8State     = PWM2LOGIC_STATE_LOW;
static u16 PWM2LOGIC_u16LastPulse = 0;
static u8  PWM2LOGIC_u8Agree      = 0;
static u8  PWM2LOGIC_u8Candidate  = PWM2LOGIC_STATE_LOW;


/*==================================================================*/
/*                   دالة داخلية : اكتب على الخرج                   */
/*                                                                  */
/*  في وضع Push-Pull  :  1 -> 3.3 فولت                              */
/*  في وضع Open-Drain :  البن يسحب للأرض عند 0 ، ويُترك حراً عند 1  */
/*                       فترفعه المقاومة الخارجية إلى 5 فولت .      */
/*  في الحالتين نكتب نفس القيمة ــ الاختلاف في نوع البن فقط .       */
/*==================================================================*/
static void PWM2LOGIC_voidWriteOutput(u8 Copy_u8Level)
{
    GPIO_SetPinValue(PWM2LOGIC_u8_OUT_PORT, PWM2LOGIC_u8_OUT_PIN, Copy_u8Level);
}


/*==================================================================*/
/*                      PWM2LOGIC_voidInit                          */
/*==================================================================*/
void PWM2LOGIC_voidInit(void)
{
    /* 1- بن الدخل : مدخل حر ــ المؤقّت هو من يقرأه */
    GPIO_SetPinDirection(PWM2LOGIC_u8_IN_PORT, PWM2LOGIC_u8_IN_PIN, INPUT_FLOATING);

    /* 2- بن الخرج حسب النوع المختار */
#if   PWM2LOGIC_u8_OUT_TYPE == PWM2LOGIC_OUT_PUSH_PULL_3V3
    GPIO_SetPinDirection(PWM2LOGIC_u8_OUT_PORT, PWM2LOGIC_u8_OUT_PIN, OUTPUT_SPEED_2MHZ_PP);
#elif PWM2LOGIC_u8_OUT_TYPE == PWM2LOGIC_OUT_OPEN_DRAIN_5V
    GPIO_SetPinDirection(PWM2LOGIC_u8_OUT_PORT, PWM2LOGIC_u8_OUT_PIN, OUTPUT_SPEED_2MHZ_OD);
#else
    #error "PWM2LOGIC_config.h : PWM2LOGIC_u8_OUT_TYPE غير صحيح"
#endif

    /* 3- ابدأ من الحالة الآمنة */
    PWM2LOGIC_u8State = PWM2LOGIC_STATE_LOW;
    PWM2LOGIC_voidWriteOutput(PWM2LOGIC_STATE_LOW);

    /* 4- شغّل وحدة الالتقاط */
    ICU_voidInit();
}


/*==================================================================*/
/*                     PWM2LOGIC_voidUpdate                         */
/*==================================================================*/
void PWM2LOGIC_voidUpdate(void)
{
    u16 Local_u16Pulse = 0;
    u8  Local_u8New    = PWM2LOGIC_u8State;   /* الافتراض : لا تغيير */

    /* --- 1 : هل الإشارة موجودة أصلاً ؟ --- */
    if (ICU_u8IsSignalLost() == 1)
    {
        PWM2LOGIC_u8State    = PWM2LOGIC_STATE_LOW;   /* failsafe */
        PWM2LOGIC_u8Agree    = 0;
        PWM2LOGIC_u16LastPulse = 0;
        PWM2LOGIC_voidWriteOutput(PWM2LOGIC_STATE_LOW);
        return;
    }

    /* --- 2 : اقرأ عرض النبضة --- */
    Local_u16Pulse = ICU_u16GetPulseWidth();

    /* --- 3 : تجاهل القراءات غير المعقولة --- */
    if ((Local_u16Pulse < PWM2LOGIC_u16_MIN_VALID_US) ||
        (Local_u16Pulse > PWM2LOGIC_u16_MAX_VALID_US))
    {
        return;                                /* ضوضاء ــ لا تفعل شيئاً */
    }

    PWM2LOGIC_u16LastPulse = Local_u16Pulse;

    /* --- 4 : قرّر الحالة المرشّحة --- */
    if (Local_u16Pulse <= PWM2LOGIC_u16_LOW_THRESHOLD_US)
    {
        Local_u8New = PWM2LOGIC_STATE_LOW;
    }
    else if (Local_u16Pulse >= PWM2LOGIC_u16_HIGH_THRESHOLD_US)
    {
        Local_u8New = PWM2LOGIC_STATE_HIGH;
    }
    else
    {
        /* المنطقة الميتة : ابقَ على الحالة السابقة
         * هذا ما يمنع الخرج من الرفرفة اذا وقف الذراع في المنتصف */
        PWM2LOGIC_u8Agree = 0;
        return;
    }

    /* --- 5 : مرشّح : اطلب عدة قراءات متّفقة قبل التبديل --- */
    if (Local_u8New == PWM2LOGIC_u8State)
    {
        PWM2LOGIC_u8Agree = 0;                 /* لا تغيير مطلوب */
        return;
    }

    if (Local_u8New == PWM2LOGIC_u8Candidate)
    {
        PWM2LOGIC_u8Agree++;
    }
    else
    {
        PWM2LOGIC_u8Candidate = Local_u8New;
        PWM2LOGIC_u8Agree     = 1;
    }

    if (PWM2LOGIC_u8Agree >= PWM2LOGIC_u8_AGREE_COUNT)
    {
        PWM2LOGIC_u8State = Local_u8New;
        PWM2LOGIC_u8Agree = 0;
        PWM2LOGIC_voidWriteOutput(PWM2LOGIC_u8State);
    }
}


/*==================================================================*/
u8 PWM2LOGIC_u8GetState(void)
{
    return PWM2LOGIC_u8State;
}

u16 PWM2LOGIC_u16GetLastPulse(void)
{
    return PWM2LOGIC_u16LastPulse;
}
