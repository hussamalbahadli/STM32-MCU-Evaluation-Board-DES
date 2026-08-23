/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    RCC_program.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Hussam Ali
 *  Date    : 8/23/2026
 *  Vertion : 1.0
 *  Layer   : MCAL
 *  SWC     : RCC
 *
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"


/*==================================================================*/
/*                     RCC_voidInitSysClock                         */
/*==================================================================*/
void RCC_voidInitSysClock(void)
{

#if   RCC_u8_CLOCK_TYPE == RCC_CLOCK_HSI

    /* 1- start the internal oscillator */
    SET_BIT(RCC_CR, RCC_CR_HSION);

    /* 2- wait until it stabilizes */
    while (GET_BIT(RCC_CR, RCC_CR_HSIRDY) == 0);

    /* 3- make it the system clock source */
    RCC_CFGR &= ~(0b11UL << RCC_CFGR_SW);
    RCC_CFGR |=  ((u32)RCC_SW_HSI << RCC_CFGR_SW);


#elif RCC_u8_CLOCK_TYPE == RCC_CLOCK_HSE

    /* 1- start the external crystal */
    SET_BIT(RCC_CR, RCC_CR_HSEON);

    /* 2- wait until it stabilizes
     *    Note : if the crystal is not present on the board
     *    the program will hang here forever. This is the first place to check
     *    if the program freezes on boot.                    */
    while (GET_BIT(RCC_CR, RCC_CR_HSERDY) == 0);

    /* 3- make it the system clock source */
    RCC_CFGR &= ~(0b11UL << RCC_CFGR_SW);
    RCC_CFGR |=  ((u32)RCC_SW_HSE << RCC_CFGR_SW);


#elif RCC_u8_CLOCK_TYPE == RCC_CLOCK_PLL

    /* 1- start the crystal first because the PLL will take its input from it */
    SET_BIT(RCC_CR, RCC_CR_HSEON);
    while (GET_BIT(RCC_CR, RCC_CR_HSERDY) == 0);

    /* 2- turn off the PLL before changing its settings ( it doesn't accept changes while running ) */
    CLR_BIT(RCC_CR, RCC_CR_PLLON);

    /* 3- PLL source = HSE without division */
    SET_BIT(RCC_CFGR, RCC_CFGR_PLLSRC);
    CLR_BIT(RCC_CFGR, RCC_CFGR_PLLXTPRE);

    /* 4- multiplier factor */
    RCC_CFGR &= ~(0b1111UL << RCC_CFGR_PLLMUL);
    RCC_CFGR |=  ((u32)RCC_u8_PLL_MUL_VALUE << RCC_CFGR_PLLMUL);

    /* 5- flash is slower than the processor at 72 MHz
     *    Latency = 2  is required above 48 MHz
     *    without it : an immediate HardFault at the first code read        */
    FLASH_ACR &= ~(0b111UL);
    FLASH_ACR |=  (0b010UL);

    /* 6- start the PLL and wait for it */
    SET_BIT(RCC_CR, RCC_CR_PLLON);
    while (GET_BIT(RCC_CR, RCC_CR_PLLRDY) == 0);

    /* 7- make it the system clock source */
    RCC_CFGR &= ~(0b11UL << RCC_CFGR_SW);
    RCC_CFGR |=  ((u32)RCC_SW_PLL << RCC_CFGR_SW);

    /* 8- confirm the switch actually happened */
    while (((RCC_CFGR >> RCC_CFGR_SWS) & 0b11UL) != RCC_SW_PLL);

#else
    #error "RCC_config.h : RCC_u8_CLOCK_TYPE is invalid"
#endif

}


/*==================================================================*/
/*                RCC_voidEnablePeripheralClock                     */
/*==================================================================*/
void RCC_voidEnablePeripheralClock(u8 Copy_u8BusID, u8 Copy_u8PerID)
{
    /* The same switch style we used in the DIO driver on AVR */

    switch (Copy_u8BusID)
    {
    case AHB_BUS  :  SET_BIT(RCC_AHBENR  , Copy_u8PerID);  break;
    case APB1_BUS :  SET_BIT(RCC_APB1ENR , Copy_u8PerID);  break;
    case APB2_BUS :  SET_BIT(RCC_APB2ENR , Copy_u8PerID);  break;
    }
}


/*==================================================================*/
/*                RCC_voidDisablePeripheralClock                    */
/*==================================================================*/
void RCC_voidDisablePeripheralClock(u8 Copy_u8BusID, u8 Copy_u8PerID)
{
    switch (Copy_u8BusID)
    {
    case AHB_BUS  :  CLR_BIT(RCC_AHBENR  , Copy_u8PerID);  break;
    case APB1_BUS :  CLR_BIT(RCC_APB1ENR , Copy_u8PerID);  break;
    case APB2_BUS :  CLR_BIT(RCC_APB2ENR , Copy_u8PerID);  break;
    }
}
