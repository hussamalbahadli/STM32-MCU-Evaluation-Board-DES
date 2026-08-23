/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    ICU_program.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Hussam Ali
 *  Date    : 8/23/2026
 *  Vertion : 1.0
 *  Layer   : MCAL
 *  SWC     : ICU (Input Capture Unit)
 *
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ICU_interface.h"
#include "ICU_config.h"
#include "ICU_private.h"


/*==================================================================*/
/*                          ICU_voidInit                            */
/*                                                                  */
/*  The whole idea in one line :                                    */
/*  we make a single pin feed two capture channels at the same time.*/
/*                                                                  */
/*      rising edge  ->  channel 1 captures  and  resets the counter */
/*      falling edge  ->  channel 2 captures                        */
/*                                                                  */
/*  So we get :                                                     */
/*      CCR1 = length of the full period                            */
/*      CCR2 = pulse width                                          */
/*                                                                  */
/*  and we set the PSC so that each tick = 1 microsecond,           */
/*  which makes CCR2 the width in microseconds directly, no math needed. */
/*==================================================================*/
void ICU_voidInit(void)
{
    /* 1- turn off the counter before changing its settings */
    CLR_BIT(ICU_CR1, ICU_CR1_CEN);

    /* 2- prescaler : we want a single tick = 1 microsecond
     *    required frequency = 1 million ticks/second
     *    PSC = ( timer clock / 1000000 ) - 1
     *    example : 8 MHz -> PSC = 7          */
    ICU_PSC = (ICU_u32_TIMER_CLOCK_HZ / 1000000UL) - 1UL;

    /* 3- max counter value = 65.535 ms window
     *    the servo signal's period is 20 ms, so the window is enough,
     *    and any gap longer than that raises the overflow flag.        */
    ICU_ARR = ICU_ARR_MAX;

    /* 4- channel 1 reads from TI1 directly */
    ICU_CCMR1 &= ~(0b11UL   << ICU_CCMR1_CC1S);
    ICU_CCMR1 |=  ((u32)ICU_CC1S_TI1 << ICU_CCMR1_CC1S);

    /* 5- channel 2 reads from the same TI1 but inverted */
    ICU_CCMR1 &= ~(0b11UL   << ICU_CCMR1_CC2S);
    ICU_CCMR1 |=  ((u32)ICU_CC2S_TI1 << ICU_CCMR1_CC2S);

    /* 6- noise filter on both channels
     *    ignores any pulse shorter than 8 ticks ― necessary with an RC receiver */
    ICU_CCMR1 &= ~(0b1111UL << ICU_CCMR1_IC1F);
    ICU_CCMR1 |=  ((u32)ICU_FILTER_8 << ICU_CCMR1_IC1F);
    ICU_CCMR1 &= ~(0b1111UL << ICU_CCMR1_IC2F);
    ICU_CCMR1 |=  ((u32)ICU_FILTER_8 << ICU_CCMR1_IC2F);

    /* 7- channel 1 on the rising edge, channel 2 on the falling edge */
    CLR_BIT(ICU_CCER, ICU_CCER_CC1P);      /* 0 = rising */
    SET_BIT(ICU_CCER, ICU_CCER_CC2P);      /* 1 = falling */

    /* 8- enable both channels */
    SET_BIT(ICU_CCER, ICU_CCER_CC1E);
    SET_BIT(ICU_CCER, ICU_CCER_CC2E);

    /* 9- Reset mode : every rising edge resets the counter
     *    and this is why the measurement is accurate without interrupts */
    ICU_SMCR &= ~(0b111UL << ICU_SMCR_TS);
    ICU_SMCR |=  ((u32)ICU_TS_TI1FP1 << ICU_SMCR_TS);
    ICU_SMCR &= ~(0b111UL << ICU_SMCR_SMS);
    ICU_SMCR |=  ((u32)ICU_SMS_RESET << ICU_SMCR_SMS);

    /*10- URS = 1  ―  very important :
     *    in Reset mode every pulse resets the counter, and the reset itself
     *    raises the UIF flag if we leave URS = 0. Then the code thinks
     *    the signal is lost 50 times a second.
     *    with URS = 1, UIF is only raised on a real overflow.   */
    SET_BIT(ICU_CR1, ICU_CR1_URS);

    /*11- actually load PSC and ARR */
    SET_BIT(ICU_EGR, ICU_EGR_UG);

    /*12- clear the flags then start the counter */
    ICU_SR = 0;
    SET_BIT(ICU_CR1, ICU_CR1_CEN);
}


/*==================================================================*/
/*                     ICU_u16GetPulseWidth                         */
/*==================================================================*/
u16 ICU_u16GetPulseWidth(void)
{
    return (u16)ICU_CCR2;
}


/*==================================================================*/
/*                       ICU_u16GetPeriod                           */
/*==================================================================*/
u16 ICU_u16GetPeriod(void)
{
    return (u16)ICU_CCR1;
}


/*==================================================================*/
/*                     ICU_u8IsSignalLost                           */
/*                                                                  */
/*  If the counter overflows it means 65 ms passed with no rising edge. */
/*  We read the flag then clear it to be ready for next time.       */
/*==================================================================*/
u8 ICU_u8IsSignalLost(void)
{
    u8 Local_u8Lost = 0;

    if (GET_BIT(ICU_SR, ICU_SR_UIF) == 1)
    {
        Local_u8Lost = 1;
        CLR_BIT(ICU_SR, ICU_SR_UIF);   /* clear the flag */
    }

    return Local_u8Lost;
}
