/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    BIT_MATH.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Hussam Ali
 *  Date    : 8/23/2026
 *  Vertion : 1.0
 *  Layer   : LIB
 *  SWC     : -
 *
 */

#ifndef BIT_MATH_H
#define BIT_MATH_H

/* نفس الماكرو الذي أخذناه في AVR بالضبط ــ لا شيء جديد هنا */

#define SET_BIT(reg,bit)    ((reg) |=  (1UL << (bit)))
#define CLR_BIT(reg,bit)    ((reg) &= ~(1UL << (bit)))
#define TOG_BIT(reg,bit)    ((reg) ^=  (1UL << (bit)))
#define GET_BIT(reg,bit)    (((reg) >> (bit)) & 1UL)

#endif /* BIT_MATH_H */
