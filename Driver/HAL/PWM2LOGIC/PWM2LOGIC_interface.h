/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    PWM2LOGIC_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Hussam Ali
 *  Date    : 8/23/2026
 *  Vertion : 1.0
 *  Layer   : HAL
 *  SWC     : PWM2LOGIC
 *
 */

#ifndef PWM2LOGIC_INTERFACE_H
#define PWM2LOGIC_INTERFACE_H

/*==================================================================*/
/*  يحوّل نبضة PWM من مستقبل RC أو من متحكّم طيران                  */
/*  إلى مستوى لوجك بسيط  ( 0 أو 1 )                                 */
/*                                                                  */
/*      عرض النبضة  <=  800 us   ->  الخرج 0                        */
/*      عرض النبضة  >= 1900 us   ->  الخرج 1                        */
/*      بين الاثنين               ->  يبقى على حاله                 */
/*      لا اشارة                  ->  الخرج 0  ( failsafe )         */
/*==================================================================*/

#define PWM2LOGIC_STATE_LOW     0
#define PWM2LOGIC_STATE_HIGH    1

/*
 * Brief      : يهيّئ بن الدخل وبن الخرج ويشغّل الـ ICU
 * Hint       : افتح سواعد RCC في main قبل استدعائها
 */
void PWM2LOGIC_voidInit(void);

/*
 * Brief      : يقرأ النبضة ويحدّث الخرج
 *              تُنادى باستمرار داخل الحلقة الرئيسية
 */
void PWM2LOGIC_voidUpdate(void);

/*
 * Brief      : الحالة الحالية للخرج
 * Return     : PWM2LOGIC_STATE_LOW  أو  PWM2LOGIC_STATE_HIGH
 */
u8 PWM2LOGIC_u8GetState(void);

/*
 * Brief      : آخر عرض نبضة تمّت قراءته ــ للتصحيح فقط
 * Return     : بالميكروثانية
 */
u16 PWM2LOGIC_u16GetLastPulse(void);

#endif /* PWM2LOGIC_INTERFACE_H */
