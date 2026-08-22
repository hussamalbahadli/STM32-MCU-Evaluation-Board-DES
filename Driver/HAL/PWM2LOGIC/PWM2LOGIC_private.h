/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    PWM2LOGIC_private.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Hussam Ali
 *  Date    : 8/23/2026
 *  Vertion : 1.0
 *  Layer   : HAL
 *  SWC     : PWM2LOGIC
 *
 */

#ifndef PWM2LOGIC_PRIVATE_H
#define PWM2LOGIC_PRIVATE_H

/* هذه الطبقة لا تلمس أي سجل ــ كل شيء يمرّ عبر GPIO و ICU .
 * لذلك هذا الملف يحوي فقط أشياء داخلية لا تخصّ المستخدم .
 * وجوده هنا للحفاظ على شكل المعمارية نفسه في كل درايفر .        */

#define PWM2LOGIC_SIGNAL_OK        0
#define PWM2LOGIC_SIGNAL_LOST      1

#endif /* PWM2LOGIC_PRIVATE_H */
