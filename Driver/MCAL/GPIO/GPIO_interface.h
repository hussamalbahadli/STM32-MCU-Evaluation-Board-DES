/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    GPIO_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Hussam Ali
 *  Date    : 8/23/2026
 *  Vertion : 1.0
 *  Layer   : MCAL
 *  SWC     : GPIO
 *
 */

#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H


/*==================================================================*/
/*                        Pin Values                                */
/*==================================================================*/
#define GPIO_HIGH     1
#define GPIO_LOW      0


/*==================================================================*/
/*                        Port Names                                */
/*==================================================================*/
#define GPIOA         0
#define GPIOB         1
#define GPIOC         2
#define GPIOD         3


/*==================================================================*/
/*                        Pin Numbers                               */
/*==================================================================*/
#define PIN0          0
#define PIN1          1
#define PIN2          2
#define PIN3          3
#define PIN4          4
#define PIN5          5
#define PIN6          6
#define PIN7          7
#define PIN8          8
#define PIN9          9
#define PIN10        10
#define PIN11        11
#define PIN12        12
#define PIN13        13
#define PIN14        14
#define PIN15        15


/*==================================================================*/
/*                        Pin Modes                                 */
/*                                                                  */
/*  كل بن يأخذ 4 بتات :        CNF[1:0]  MODE[1:0]                  */
/*  MODE = 00  ->  input                                            */
/*  MODE = 01  ->  output 10 MHz                                    */
/*  MODE = 10  ->  output  2 MHz                                    */
/*  MODE = 11  ->  output 50 MHz                                    */
/*==================================================================*/

/* ---------------------- Input ---------------------- */
#define INPUT_ANALOG              0b0000
#define INPUT_FLOATING            0b0100
#define INPUT_PULLUP_PULLDOWN     0b1000

/* الاسم القديم ــ مُبقى حتى لا تنكسر مشاريعك السابقة */
#define INPUT_ANLOG               INPUT_ANALOG

/* --------------- Output  10 MHz -------------------- */
#define OUTPUT_SPEED_10MHZ_PP     0b0001
#define OUTPUT_SPEED_10MHZ_OD     0b0101
#define OUTPUT_SPEED_10MHZ_AFPP   0b1001
#define OUTPUT_SPEED_10MHZ_AFOD   0b1101

/* --------------- Output   2 MHz -------------------- */
#define OUTPUT_SPEED_2MHZ_PP      0b0010
#define OUTPUT_SPEED_2MHZ_OD      0b0110
#define OUTPUT_SPEED_2MHZ_AFPP    0b1010
#define OUTPUT_SPEED_2MHZ_AFOD    0b1110

/* --------------- Output  50 MHz -------------------- */
#define OUTPUT_SPEED_50MHZ_PP     0b0011
#define OUTPUT_SPEED_50MHZ_OD     0b0111
#define OUTPUT_SPEED_50MHZ_AFPP   0b1011
#define OUTPUT_SPEED_50MHZ_AFOD   0b1111


/*==================================================================*/
/*                        Functions                                 */
/*==================================================================*/

/*
 * Brief      : يضبط وضع بن واحد
 * Parameters : Copy_u8PortID  --> GPIOA .. GPIOD
 *              Copy_u8PinID   --> PIN0 .. PIN15
 *              Copy_u8PinMode --> واحد من الـ modes أعلاه
 * Return     : void
 *
 * Hint       : لا تنسَ فتح ساعة البورت في RCC قبل هذه الدالة
 */
void GPIO_SetPinDirection(u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8PinMode);

/*
 * Brief      : يكتب 0 أو 1 على بن مخرج
 *              وفي وضع INPUT_PULLUP_PULLDOWN :
 *              1 = pull up   ,   0 = pull down
 */
void GPIO_SetPinValue(u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8PinValue);

/*
 * Brief      : يقرأ قيمة بن مدخل
 * Return     : GPIO_HIGH أو GPIO_LOW
 */
u8   GPIO_GetPinValue(u8 Copy_u8PortID, u8 Copy_u8PinID);

/*
 * Brief      : يعكس قيمة بن مخرج
 */
void GPIO_TogglePinValue(u8 Copy_u8PortID, u8 Copy_u8PinID);


/* ------------------------ Port level ------------------------ */

void GPIO_SetPortDirection(u8 Copy_u8PortID, u8 Copy_u8PortMode);
void GPIO_SetPortValue(u8 Copy_u8PortID, u16 Copy_u16PortValue);
u16  GPIO_GetPortValue(u8 Copy_u8PortID);
void GPIO_TogglePortValue(u8 Copy_u8PortID);


#endif /* GPIO_INTERFACE_H */
