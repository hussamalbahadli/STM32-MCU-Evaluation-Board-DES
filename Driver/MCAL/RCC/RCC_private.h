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
/*  Registers only ― there is no logic at all in this file          */
/*  RCC Base Address = 0x40021000                                   */
/*  Reference : RM0008  Chapter 7                                    */
/*==================================================================*/

#define RCC_BASE_ADDRESS    0x40021000UL

/* The exact same way as AVR :  *((volatile u8*)0x3B)                */
/* The only difference : here u32 because ARM registers are 32-bit wide */

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

/* Flash register ― only needed at 72 MHz */
#define FLASH_ACR       *((volatile u32*)0x40022000UL)


/*------------------ RCC_CR register bits ------------------*/
#define RCC_CR_HSION        0
#define RCC_CR_HSIRDY       1
#define RCC_CR_HSEON       16
#define RCC_CR_HSERDY      17
#define RCC_CR_HSEBYP      18
#define RCC_CR_CSSON       19
#define RCC_CR_PLLON       24
#define RCC_CR_PLLRDY      25

/*------------------ RCC_CFGR register bits ----------------*/
#define RCC_CFGR_SW         0    /* 2 bit : system clock source        */
#define RCC_CFGR_SWS        2    /* 2 bit : actual source ( read only ) */
#define RCC_CFGR_PLLSRC    16    /* 0 = HSI/2   1 = HSE             */
#define RCC_CFGR_PLLXTPRE  17    /* 0 = HSE     1 = HSE/2           */
#define RCC_CFGR_PLLMUL    18    /* 4 bit : multiplier factor             */

/*------------------ SW / SWS values ---------------------*/
#define RCC_SW_HSI       0b00
#define RCC_SW_HSE       0b01
#define RCC_SW_PLL       0b10

#endif /* RCC_PRIVATE_H */
