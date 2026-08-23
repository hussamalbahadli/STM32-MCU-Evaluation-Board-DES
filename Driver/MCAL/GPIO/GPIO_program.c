/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    GPIO_program.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Hussam Ali
 *  Date    : 8/23/2026
 *  Vertion : 1.0
 *  Layer   : MCAL
 *  SWC     : GPIO
 *
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"


/*==================================================================*/
/*                    GPIO_SetPinDirection                          */
/*                                                                  */
/*  The whole idea is two lines :                                   */
/*      1- clear the old four bits    ( clear )                     */
/*      2- set the new four bits      ( set   )                     */
/*  It's the exact same bit masking we used in LEC-4 .               */
/*==================================================================*/
void GPIO_SetPinDirection(u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8PinMode)
{
    u8 Local_u8Shift = 0;

    /* pins 0..7 are in register CRL, and pins 8..15 in register CRH */
    if (Copy_u8PinID <= PIN7)
    {
        Local_u8Shift = Copy_u8PinID * GPIO_PIN_WIDTH;
    }
    else
    {
        Local_u8Shift = (Copy_u8PinID - 8) * GPIO_PIN_WIDTH;
    }

    switch (Copy_u8PortID)
    {
    case GPIOA :
        if (Copy_u8PinID <= PIN7)
        {
            GPIOA_CRL &= ~(GPIO_MODE_MASK << Local_u8Shift);
            GPIOA_CRL |=  ((u32)Copy_u8PinMode << Local_u8Shift);
        }
        else
        {
            GPIOA_CRH &= ~(GPIO_MODE_MASK << Local_u8Shift);
            GPIOA_CRH |=  ((u32)Copy_u8PinMode << Local_u8Shift);
        }
        break;

    case GPIOB :
        if (Copy_u8PinID <= PIN7)
        {
            GPIOB_CRL &= ~(GPIO_MODE_MASK << Local_u8Shift);
            GPIOB_CRL |=  ((u32)Copy_u8PinMode << Local_u8Shift);
        }
        else
        {
            GPIOB_CRH &= ~(GPIO_MODE_MASK << Local_u8Shift);
            GPIOB_CRH |=  ((u32)Copy_u8PinMode << Local_u8Shift);
        }
        break;

    case GPIOC :
        if (Copy_u8PinID <= PIN7)
        {
            GPIOC_CRL &= ~(GPIO_MODE_MASK << Local_u8Shift);
            GPIOC_CRL |=  ((u32)Copy_u8PinMode << Local_u8Shift);
        }
        else
        {
            GPIOC_CRH &= ~(GPIO_MODE_MASK << Local_u8Shift);
            GPIOC_CRH |=  ((u32)Copy_u8PinMode << Local_u8Shift);
        }
        break;

    case GPIOD :
        if (Copy_u8PinID <= PIN7)
        {
            GPIOD_CRL &= ~(GPIO_MODE_MASK << Local_u8Shift);
            GPIOD_CRL |=  ((u32)Copy_u8PinMode << Local_u8Shift);
        }
        else
        {
            GPIOD_CRH &= ~(GPIO_MODE_MASK << Local_u8Shift);
            GPIOD_CRH |=  ((u32)Copy_u8PinMode << Local_u8Shift);
        }
        break;
    }
}


/*==================================================================*/
/*                      GPIO_SetPinValue                            */
/*                                                                  */
/*  ODR in STM32  =  PORTx in AVR                                   */
/*==================================================================*/
void GPIO_SetPinValue(u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8PinValue)
{
    if (Copy_u8PinValue == GPIO_HIGH)
    {
        switch (Copy_u8PortID)
        {
        case GPIOA :  SET_BIT(GPIOA_ODR, Copy_u8PinID);  break;
        case GPIOB :  SET_BIT(GPIOB_ODR, Copy_u8PinID);  break;
        case GPIOC :  SET_BIT(GPIOC_ODR, Copy_u8PinID);  break;
        case GPIOD :  SET_BIT(GPIOD_ODR, Copy_u8PinID);  break;
        }
    }
    else
    {
        switch (Copy_u8PortID)
        {
        case GPIOA :  CLR_BIT(GPIOA_ODR, Copy_u8PinID);  break;
        case GPIOB :  CLR_BIT(GPIOB_ODR, Copy_u8PinID);  break;
        case GPIOC :  CLR_BIT(GPIOC_ODR, Copy_u8PinID);  break;
        case GPIOD :  CLR_BIT(GPIOD_ODR, Copy_u8PinID);  break;
        }
    }
}


/*==================================================================*/
/*                      GPIO_GetPinValue                            */
/*                                                                  */
/*  IDR in STM32  =  PINx in AVR                                    */
/*==================================================================*/
u8 GPIO_GetPinValue(u8 Copy_u8PortID, u8 Copy_u8PinID)
{
    u8 Local_u8Value = 0;

    switch (Copy_u8PortID)
    {
    case GPIOA :  Local_u8Value = (u8)GET_BIT(GPIOA_IDR, Copy_u8PinID);  break;
    case GPIOB :  Local_u8Value = (u8)GET_BIT(GPIOB_IDR, Copy_u8PinID);  break;
    case GPIOC :  Local_u8Value = (u8)GET_BIT(GPIOC_IDR, Copy_u8PinID);  break;
    case GPIOD :  Local_u8Value = (u8)GET_BIT(GPIOD_IDR, Copy_u8PinID);  break;
    }

    return Local_u8Value;
}


/*==================================================================*/
/*                     GPIO_TogglePinValue                          */
/*==================================================================*/
void GPIO_TogglePinValue(u8 Copy_u8PortID, u8 Copy_u8PinID)
{
    switch (Copy_u8PortID)
    {
    case GPIOA :  TOG_BIT(GPIOA_ODR, Copy_u8PinID);  break;
    case GPIOB :  TOG_BIT(GPIOB_ODR, Copy_u8PinID);  break;
    case GPIOC :  TOG_BIT(GPIOC_ODR, Copy_u8PinID);  break;
    case GPIOD :  TOG_BIT(GPIOD_ODR, Copy_u8PinID);  break;
    }
}


/*==================================================================*/
/*                    GPIO_SetPortDirection                         */
/*                                                                  */
/*  We repeat the same four bits eight times to fill CRL, and the same for CRH. */
/*==================================================================*/
void GPIO_SetPortDirection(u8 Copy_u8PortID, u8 Copy_u8PortMode)
{
    u32 Local_u32Pattern = 0;
    u8  Local_u8Counter  = 0;

    for (Local_u8Counter = 0; Local_u8Counter < 8; Local_u8Counter++)
    {
        Local_u32Pattern |= ((u32)Copy_u8PortMode << (Local_u8Counter * GPIO_PIN_WIDTH));
    }

    switch (Copy_u8PortID)
    {
    case GPIOA :  GPIOA_CRL = Local_u32Pattern;  GPIOA_CRH = Local_u32Pattern;  break;
    case GPIOB :  GPIOB_CRL = Local_u32Pattern;  GPIOB_CRH = Local_u32Pattern;  break;
    case GPIOC :  GPIOC_CRL = Local_u32Pattern;  GPIOC_CRH = Local_u32Pattern;  break;
    case GPIOD :  GPIOD_CRL = Local_u32Pattern;  GPIOD_CRH = Local_u32Pattern;  break;
    }
}


/*==================================================================*/
/*                      GPIO_SetPortValue                           */
/*==================================================================*/
void GPIO_SetPortValue(u8 Copy_u8PortID, u16 Copy_u16PortValue)
{
    switch (Copy_u8PortID)
    {
    case GPIOA :  GPIOA_ODR = (u32)Copy_u16PortValue;  break;
    case GPIOB :  GPIOB_ODR = (u32)Copy_u16PortValue;  break;
    case GPIOC :  GPIOC_ODR = (u32)Copy_u16PortValue;  break;
    case GPIOD :  GPIOD_ODR = (u32)Copy_u16PortValue;  break;
    }
}


/*==================================================================*/
/*                      GPIO_GetPortValue                           */
/*==================================================================*/
u16 GPIO_GetPortValue(u8 Copy_u8PortID)
{
    u16 Local_u16Value = 0;

    switch (Copy_u8PortID)
    {
    case GPIOA :  Local_u16Value = (u16)GPIOA_IDR;  break;
    case GPIOB :  Local_u16Value = (u16)GPIOB_IDR;  break;
    case GPIOC :  Local_u16Value = (u16)GPIOC_IDR;  break;
    case GPIOD :  Local_u16Value = (u16)GPIOD_IDR;  break;
    }

    return Local_u16Value;
}


/*==================================================================*/
/*                     GPIO_TogglePortValue                         */
/*==================================================================*/
void GPIO_TogglePortValue(u8 Copy_u8PortID)
{
    switch (Copy_u8PortID)
    {
    case GPIOA :  GPIOA_ODR ^= 0xFFFFUL;  break;
    case GPIOB :  GPIOB_ODR ^= 0xFFFFUL;  break;
    case GPIOC :  GPIOC_ODR ^= 0xFFFFUL;  break;
    case GPIOD :  GPIOD_ODR ^= 0xFFFFUL;  break;
    }
}
