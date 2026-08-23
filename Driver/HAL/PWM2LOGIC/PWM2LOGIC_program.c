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


/* internal variables ― keep their value between calls */
static u8  PWM2LOGIC_u8State     = PWM2LOGIC_STATE_LOW;
static u16 PWM2LOGIC_u16LastPulse = 0;
static u8  PWM2LOGIC_u8Agree      = 0;
static u8  PWM2LOGIC_u8Candidate  = PWM2LOGIC_STATE_LOW;


/*==================================================================*/
/*                   internal function : write to the output        */
/*                                                                  */
/*  In Push-Pull mode  :  1 -> 3.3V                                 */
/*  In Open-Drain mode :  the pin pulls to ground at 0, and is left floating at 1 */
/*                       so the external resistor pulls it up to 5V. */
/*  In both cases we write the same value ― the difference is only in the pin type. */
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
    /* 1- input pin : floating input ― the timer is what reads it */
    GPIO_SetPinDirection(PWM2LOGIC_u8_IN_PORT, PWM2LOGIC_u8_IN_PIN, INPUT_FLOATING);

    /* 2- output pin according to the chosen type */
#if   PWM2LOGIC_u8_OUT_TYPE == PWM2LOGIC_OUT_PUSH_PULL_3V3
    GPIO_SetPinDirection(PWM2LOGIC_u8_OUT_PORT, PWM2LOGIC_u8_OUT_PIN, OUTPUT_SPEED_2MHZ_PP);
#elif PWM2LOGIC_u8_OUT_TYPE == PWM2LOGIC_OUT_OPEN_DRAIN_5V
    GPIO_SetPinDirection(PWM2LOGIC_u8_OUT_PORT, PWM2LOGIC_u8_OUT_PIN, OUTPUT_SPEED_2MHZ_OD);
#else
    #error "PWM2LOGIC_config.h : PWM2LOGIC_u8_OUT_TYPE is invalid"
#endif

    /* 3- start from the safe state */
    PWM2LOGIC_u8State = PWM2LOGIC_STATE_LOW;
    PWM2LOGIC_voidWriteOutput(PWM2LOGIC_STATE_LOW);

    /* 4- start the capture unit */
    ICU_voidInit();
}


/*==================================================================*/
/*                     PWM2LOGIC_voidUpdate                         */
/*==================================================================*/
void PWM2LOGIC_voidUpdate(void)
{
    u16 Local_u16Pulse = 0;
    u8  Local_u8New    = PWM2LOGIC_u8State;   /* default : no change */

    /* --- 1 : is the signal present at all ? --- */
    if (ICU_u8IsSignalLost() == 1)
    {
        PWM2LOGIC_u8State    = PWM2LOGIC_STATE_LOW;   /* failsafe */
        PWM2LOGIC_u8Agree    = 0;
        PWM2LOGIC_u16LastPulse = 0;
        PWM2LOGIC_voidWriteOutput(PWM2LOGIC_STATE_LOW);
        return;
    }

    /* --- 2 : read the pulse width --- */
    Local_u16Pulse = ICU_u16GetPulseWidth();

    /* --- 3 : ignore unreasonable readings --- */
    if ((Local_u16Pulse < PWM2LOGIC_u16_MIN_VALID_US) ||
        (Local_u16Pulse > PWM2LOGIC_u16_MAX_VALID_US))
    {
        return;                                /* noise ― do nothing */
    }

    PWM2LOGIC_u16LastPulse = Local_u16Pulse;

    /* --- 4 : decide the candidate state --- */
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
        /* dead zone : keep the previous state
         * this is what stops the output from flickering if the stick sits in the middle */
        PWM2LOGIC_u8Agree = 0;
        return;
    }

    /* --- 5 : filter : require several matching readings before switching --- */
    if (Local_u8New == PWM2LOGIC_u8State)
    {
        PWM2LOGIC_u8Agree = 0;                 /* no change needed */
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
