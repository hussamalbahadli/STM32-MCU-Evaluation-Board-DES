/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    RCC_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Hussam Ali
 *  Date    : 8/23/2026
 *  Vertion : 1.0
 *  Layer   : MCAL
 *  SWC     : RCC
 *
 */

#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H


/*==================================================================*/
/*                          Bus Names                               */
/*==================================================================*/
#define AHB_BUS       0
#define APB1_BUS      1
#define APB2_BUS      2


/*==================================================================*/
/*        Peripheral Numbers  =  bit number inside the ENR          */
/*==================================================================*/

/* --------- AHB peripherals  (RCC_AHBENR) --------- */
#define DMA1_RCC      0
#define DMA2_RCC      1
#define SRAM_RCC      2
#define FLITF_RCC     4
#define CRC_RCC       6

/* --------- APB1 peripherals (RCC_APB1ENR) -------- */
#define TIM2_RCC      0
#define TIM3_RCC      1
#define TIM4_RCC      2
#define WWDG_RCC     11
#define SPI2_RCC     14
#define USART2_RCC   17
#define USART3_RCC   18
#define I2C1_RCC     21
#define I2C2_RCC     22
#define CAN_RCC      25
#define PWR_RCC      28

/* --------- APB2 peripherals (RCC_APB2ENR) -------- */
#define AFIO_RCC      0
#define GPIOA_RCC     2
#define GPIOB_RCC     3
#define GPIOC_RCC     4
#define GPIOD_RCC     5
#define ADC1_RCC      9
#define ADC2_RCC     10
#define TIM1_RCC     11
#define SPI1_RCC     12
#define USART1_RCC   14


/*==================================================================*/
/*                          Functions                               */
/*==================================================================*/

/*
 * Brief      : sets the system clock source according to what we chose in RCC_config.h
 * Parameters : void
 * Return     : void
 */
void RCC_voidInitSysClock(void);

/*
 * Brief      : enables the clock of a single peripheral
 * Parameters : Copy_u8BusID  --> AHB_BUS , APB1_BUS , APB2_BUS
 *              Copy_u8PerID  --> bit number from the list above
 * Return     : void
 *
 * Hint       : any register of a peripheral whose clock is gated off always reads zero
 *              and writes have no effect on it at all.
 */
void RCC_voidEnablePeripheralClock(u8 Copy_u8BusID, u8 Copy_u8PerID);

/*
 * Brief      : disables the clock of a single peripheral ( to save power )
 */
void RCC_voidDisablePeripheralClock(u8 Copy_u8BusID, u8 Copy_u8PerID);


#endif /* RCC_INTERFACE_H */
