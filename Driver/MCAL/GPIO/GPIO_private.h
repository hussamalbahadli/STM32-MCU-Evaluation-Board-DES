/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    GPIO_private.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Hussam Ali
 *  Date    : 8/23/2026
 *  Vertion : 1.0
 *  Layer   : MCAL
 *  SWC     : GPIO
 *
 */

#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

/*==================================================================*/
/*  السجلات فقط ــ لا يوجد أي منطق في هذا الملف                     */
/*  المرجع : RM0008  Chapter 9                                      */
/*                                                                  */
/*  لاحظ : نفس اسلوب AVR بالضبط                                     */
/*      AVR    :  #define PORTA_Register  *((volatile u8 *)0x3B)    */
/*      STM32  :  #define GPIOA_ODR       *((volatile u32*)....)    */
/*  الفرق الوحيد هو u32 بدل u8 ــ لا اكثر                           */
/*==================================================================*/

#define GPIOA_BASE_ADDRESS      0x40010800UL
#define GPIOB_BASE_ADDRESS      0x40010C00UL
#define GPIOC_BASE_ADDRESS      0x40011000UL
#define GPIOD_BASE_ADDRESS      0x40011400UL

/* الإزاحات داخل كل بورت */
#define GPIO_CRL_OFFSET     0x00      /* ضبط البنّات  0 .. 7   */
#define GPIO_CRH_OFFSET     0x04      /* ضبط البنّات  8 .. 15  */
#define GPIO_IDR_OFFSET     0x08      /* قراءة  ( مثل PINx )   */
#define GPIO_ODR_OFFSET     0x0C      /* كتابة  ( مثل PORTx )  */


/*------------------------ GPIOA ------------------------*/
#define GPIOA_CRL   *((volatile u32*)(GPIOA_BASE_ADDRESS + GPIO_CRL_OFFSET))
#define GPIOA_CRH   *((volatile u32*)(GPIOA_BASE_ADDRESS + GPIO_CRH_OFFSET))
#define GPIOA_IDR   *((volatile u32*)(GPIOA_BASE_ADDRESS + GPIO_IDR_OFFSET))
#define GPIOA_ODR   *((volatile u32*)(GPIOA_BASE_ADDRESS + GPIO_ODR_OFFSET))

/*------------------------ GPIOB ------------------------*/
#define GPIOB_CRL   *((volatile u32*)(GPIOB_BASE_ADDRESS + GPIO_CRL_OFFSET))
#define GPIOB_CRH   *((volatile u32*)(GPIOB_BASE_ADDRESS + GPIO_CRH_OFFSET))
#define GPIOB_IDR   *((volatile u32*)(GPIOB_BASE_ADDRESS + GPIO_IDR_OFFSET))
#define GPIOB_ODR   *((volatile u32*)(GPIOB_BASE_ADDRESS + GPIO_ODR_OFFSET))

/*------------------------ GPIOC ------------------------*/
#define GPIOC_CRL   *((volatile u32*)(GPIOC_BASE_ADDRESS + GPIO_CRL_OFFSET))
#define GPIOC_CRH   *((volatile u32*)(GPIOC_BASE_ADDRESS + GPIO_CRH_OFFSET))
#define GPIOC_IDR   *((volatile u32*)(GPIOC_BASE_ADDRESS + GPIO_IDR_OFFSET))
#define GPIOC_ODR   *((volatile u32*)(GPIOC_BASE_ADDRESS + GPIO_ODR_OFFSET))

/*------------------------ GPIOD ------------------------*/
#define GPIOD_CRL   *((volatile u32*)(GPIOD_BASE_ADDRESS + GPIO_CRL_OFFSET))
#define GPIOD_CRH   *((volatile u32*)(GPIOD_BASE_ADDRESS + GPIO_CRH_OFFSET))
#define GPIOD_IDR   *((volatile u32*)(GPIOD_BASE_ADDRESS + GPIO_IDR_OFFSET))
#define GPIOD_ODR   *((volatile u32*)(GPIOD_BASE_ADDRESS + GPIO_ODR_OFFSET))


/* كل بن يحجز 4 بتات في سجل الضبط */
#define GPIO_PIN_WIDTH      4
#define GPIO_MODE_MASK      0b1111UL

#endif /* GPIO_PRIVATE_H */
