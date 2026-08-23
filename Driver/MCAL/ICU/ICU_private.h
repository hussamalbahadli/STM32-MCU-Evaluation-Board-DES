/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    ICU_private.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Hussam Ali
 *  Date    : 8/23/2026
 *  Vertion : 1.0
 *  Layer   : MCAL
 *  SWC     : ICU (Input Capture Unit)
 *
 */

#ifndef ICU_PRIVATE_H
#define ICU_PRIVATE_H

/*==================================================================*/
/*  Registers only ― Reference : RM0008  Chapter 15 (TIM2..TIM5)     */
/*  The exact same style as GPIO_private.h                          */
/*==================================================================*/

#define TIM2_BASE_ADDRESS       0x40000000UL
#define TIM3_BASE_ADDRESS       0x40000400UL
#define TIM4_BASE_ADDRESS       0x40000800UL

/* We select the base address according to what's set in ICU_config.h */
#if   ICU_u8_TIMER_SELECT == ICU_TIMER2
    #define ICU_BASE_ADDRESS    TIM2_BASE_ADDRESS
#elif ICU_u8_TIMER_SELECT == ICU_TIMER3
    #define ICU_BASE_ADDRESS    TIM3_BASE_ADDRESS
#elif ICU_u8_TIMER_SELECT == ICU_TIMER4
    #define ICU_BASE_ADDRESS    TIM4_BASE_ADDRESS
#else
    #error "ICU_config.h : ICU_u8_TIMER_SELECT is invalid"
#endif


#define ICU_CR1     *((volatile u32*)(ICU_BASE_ADDRESS + 0x00))
#define ICU_SMCR    *((volatile u32*)(ICU_BASE_ADDRESS + 0x08))
#define ICU_SR      *((volatile u32*)(ICU_BASE_ADDRESS + 0x10))
#define ICU_EGR     *((volatile u32*)(ICU_BASE_ADDRESS + 0x14))
#define ICU_CCMR1   *((volatile u32*)(ICU_BASE_ADDRESS + 0x18))
#define ICU_CCER    *((volatile u32*)(ICU_BASE_ADDRESS + 0x20))
#define ICU_CNT     *((volatile u32*)(ICU_BASE_ADDRESS + 0x24))
#define ICU_PSC     *((volatile u32*)(ICU_BASE_ADDRESS + 0x28))
#define ICU_ARR     *((volatile u32*)(ICU_BASE_ADDRESS + 0x2C))
#define ICU_CCR1    *((volatile u32*)(ICU_BASE_ADDRESS + 0x34))
#define ICU_CCR2    *((volatile u32*)(ICU_BASE_ADDRESS + 0x38))


/*----------------- CR1 bits -----------------*/
#define ICU_CR1_CEN         0     /* enable the counter            */
#define ICU_CR1_URS         2     /* update event source           */

/*----------------- SR bits ------------------*/
#define ICU_SR_UIF          0     /* counter overflow flag         */
#define ICU_SR_CC1IF        1     /* capture on channel 1          */
#define ICU_SR_CC2IF        2     /* capture on channel 2          */

/*----------------- EGR bits -----------------*/
#define ICU_EGR_UG          0     /* generate an update event manually */

/*----------------- CCMR1 fields ---------------*/
#define ICU_CCMR1_CC1S      0     /* two bits : channel 1 input selection */
#define ICU_CCMR1_IC1F      4     /* four bits : channel 1 filter  */
#define ICU_CCMR1_CC2S      8     /* two bits : channel 2 input selection */
#define ICU_CCMR1_IC2F     12     /* four bits : channel 2 filter  */

/*----------------- CCER bits ----------------*/
#define ICU_CCER_CC1E       0     /* enable channel 1 capture      */
#define ICU_CCER_CC1P       1     /* 0 = rising edge                */
#define ICU_CCER_CC2E       4     /* enable channel 2 capture      */
#define ICU_CCER_CC2P       5     /* 1 = falling edge                */

/*----------------- SMCR fields ----------------*/
#define ICU_SMCR_SMS        0     /* three bits : slave mode        */
#define ICU_SMCR_TS         4     /* three bits : trigger source    */

/*----------------- ready-made values ----------------*/
#define ICU_CC1S_TI1     0b01     /* IC1 reads from TI1  ( direct )   */
#define ICU_CC2S_TI1     0b10     /* IC2 reads from TI1  ( inverted ) */
#define ICU_FILTER_8     0b0011   /* ignores pulses shorter than 8 ticks */
#define ICU_TS_TI1FP1    0b101    /* trigger = rising edge of TI1 */
#define ICU_SMS_RESET    0b100    /* Reset mode : the trigger resets the counter */

#define ICU_ARR_MAX      0xFFFFUL

#endif /* ICU_PRIVATE_H */
