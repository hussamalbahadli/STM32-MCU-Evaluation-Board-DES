/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    RCC_private.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Hussam Ali
 *  Date    : 8/23/2026
 *  Vertion : 1.0
 *  Layer   : MCAL
 *  SWC     : RCC
 *
 */

#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

/*==================================================================*/
/*  السجلات فقط ــ لا يوجد أي منطق في هذا الملف                     */
/*  RCC Base Address = 0x40021000                                   */
/*  المرجع : RM0008  Chapter 7                                      */
/*==================================================================*/

#define RCC_BASE_ADDRESS    0x40021000UL

/* بنفس طريقة AVR بالضبط :  *((volatile u8*)0x3B)                   */
/* الفرق الوحيد : هنا u32 لأن سجلات ARM بعرض 32 بت                  */

#define RCC_CR          *((volatile u32*)(RCC_BASE_ADDRESS + 0x00))
#define RCC_CFGR        *((volatile u32*)(RCC_BASE_ADDRESS + 0x04))
#define RCC_CIR         *((volatile u32*)(RCC_BASE_ADDRESS + 0x08))
#define RCC_APB2RSTR    *((volatile u32*)(RCC_BASE_ADDRESS + 0x0C))
#define RCC_APB1RSTR    *((volatile u32*)(RCC_BASE_ADDRESS + 0x10))
#define RCC_AHBENR      *((volatile u32*)(RCC_BASE_ADDRESS + 0x14))
#define RCC_APB2ENR     *((volatile u32*)(RCC_BASE_ADDRESS + 0x18))
#define RCC_APB1ENR     *((volatile u32*)(RCC_BASE_ADDRESS + 0x1C))
#define RCC_BDCR        *((volatile u32*)(RCC_BASE_ADDRESS + 0x20))
#define RCC_CSR         *((volatile u32*)(RCC_BASE_ADDRESS + 0x24))

/* سجل الفلاش ــ نحتاجه فقط عند 72 ميغا */
#define FLASH_ACR       *((volatile u32*)0x40022000UL)


/*------------------ بتات سجل RCC_CR ------------------*/
#define RCC_CR_HSION        0
#define RCC_CR_HSIRDY       1
#define RCC_CR_HSEON       16
#define RCC_CR_HSERDY      17
#define RCC_CR_HSEBYP      18
#define RCC_CR_CSSON       19
#define RCC_CR_PLLON       24
#define RCC_CR_PLLRDY      25

/*------------------ بتات سجل RCC_CFGR ----------------*/
#define RCC_CFGR_SW         0    /* 2 bit : مصدر ساعة النظام        */
#define RCC_CFGR_SWS        2    /* 2 bit : المصدر الفعلي ( قراءة ) */
#define RCC_CFGR_PLLSRC    16    /* 0 = HSI/2   1 = HSE             */
#define RCC_CFGR_PLLXTPRE  17    /* 0 = HSE     1 = HSE/2           */
#define RCC_CFGR_PLLMUL    18    /* 4 bit : معامل الضرب             */

/*------------------ قيم SW / SWS ---------------------*/
#define RCC_SW_HSI       0b00
#define RCC_SW_HSE       0b01
#define RCC_SW_PLL       0b10

#endif /* RCC_PRIVATE_H */
