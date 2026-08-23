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
/*  Registers only ― there is no logic at all in this file          */
/*  Reference : RM0008  Chapter 9                                   */
/*                                                                  */
/*  Note : the exact same style as AVR                              */
/*      AVR    :  #define PORTA_Register  *((volatile u8 *)0x3B)    */
/*      STM32  :  #define GPIOA_ODR       *((volatile u32*)....)    */
/*  The only difference is u32 instead of u8 ― nothing more          */
/*==================================================================*/

#define GPIOA_BASE_ADDRESS      0x40010800UL
#define GPIOB_BASE_ADDRESS      0x40010C00UL
#define GPIOC_BASE_ADDRESS      0x40011000UL
#define GPIOD_BASE_ADDRESS      0x40011400UL

/* Offsets within each port */
#define GPIO_CRL_OFFSET     0x00      /* configures pins  0 .. 7   */
#define GPIO_CRH_OFFSET     0x04      /* configures pins  8 .. 15  */
#define GPIO_IDR_OFFSET     0x08      /* read  ( like PINx )   */
#define GPIO_ODR_OFFSET     0x0C      /* write  ( like PORTx )  */


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


/* Every pin reserves 4 bits in the config register */
#define GPIO_PIN_WIDTH      4
#define GPIO_MODE_MASK      0b1111UL

#endif /* GPIO_PRIVATE_H */
