/*
 * keypad.h
 *
 *  Created on: 8 de jun de 2019
 *      Author: aureziano
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

/** Includes ---------------------------------------------------------------- */
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "delay.h"

// GPIO pin definitions for keypad columns (must on the same GPIO)
#define KEYPAD_RCC_GPIO_COL		RCC_APB2Periph_GPIOA
#define KEYPAD_GPIO_COL				GPIOA
#define KEYPAD_PIN_COL0				GPIO_Pin_7
#define KEYPAD_PIN_COL1				GPIO_Pin_6
#define KEYPAD_PIN_COL2				GPIO_Pin_5
//#define KEYPAD_PIN_COL3				GPIO_Pin_4
// GPIO pin definitions for keypad rows (must on the same GPIO)
#define KEYPAD_RCC_GPIO_ROW		RCC_APB2Periph_GPIOA
#define KEYPAD_GPIO_ROW				GPIOA
#define KEYPAD_PIN_ROW0				GPIO_Pin_4
#define KEYPAD_PIN_ROW1				GPIO_Pin_3
#define KEYPAD_PIN_ROW2				GPIO_Pin_2
#define KEYPAD_PIN_ROW3				GPIO_Pin_1
// Return value for no key pressed
#define KEYPAD_NO_PRESSED			0xFF

/** Public function prototypes ---------------------------------------------- */
void KeypadInit(void);
uint8_t KeypadGetKey(void);

//
//#define ROW_1_PA               GPIO_Pin_12 //((uint16_t)0x1000) //GPIO_Pin_12
//#define ROW_2_PA               GPIO_Pin_11 //((uint16_t)0x0800) //GPIO_Pin_11
//#define ROW_3_PB               GPIO_Pin_10 //((uint16_t)0x1000) //GPIO_Pin_12
//#define ROW_4_PB               GPIO_Pin_9 //((uint16_t)0x0800) //GPIO_Pin_11
//
//#define COLUMN_1_PB             GPIO_Pin_13//((uint16_t)0x8000) //GPIO_Pin_15
//#define COLUMN_2_PB             GPIO_Pin_14//((uint16_t)0x4000) //GPIO_Pin_14
//#define COLUMN_3_PB             GPIO_Pin_15//((uint16_t)0x2000) //GPIO_Pin_13
//
////#define PIN_1					((uint16_t)0x0400) //GPIO_Pin_10
////#define PIN_2					((uint16_t)0x0200) //GPIO_Pin_9
////#define PIN_3					((uint16_t)0x0020) //GPIO_Pin_5
////#define PIN_4					((uint16_t)0x0100) //GPIO_Pin_8
//
////#define PIN_a					((uint16_t)0x0020)
////#define PIN_b					((uint16_t)0x0040)
////#define PIN_c					((uint16_t)0x0080)
////#define PIN_d					((uint16_t)0x0040)
////#define PIN_e					((uint16_t)0x0080)
////#define PIN_f					((uint16_t)0x0200)
////#define PIN_g					((uint16_t)0x0100)
////#define PIN_dp					((uint16_t)0x0400)
//
//#define RECEIVE_BUFFER_LEN 		128
//#define SEND_BUFFER_LEN 		256
//#define TIME_BUFFER_LEN			4
//#define SECONDS_BUFFER_LEN 		2
//#define MIN_BUTTON_PRESSED		150
//
//char receiveBuffer[RECEIVE_BUFFER_LEN];
//short receiveBufferTail;
//short receiveBufferCount;
//
//char sendBuffer[SEND_BUFFER_LEN];
//short sendBufferTail;
//short sendBufferCount;
//
//short cmdStart;
//short cmdEnd;
//short cmdRange;
//
//char timeBuffer[TIME_BUFFER_LEN];
//char secondsBuffer[SECONDS_BUFFER_LEN];
//short timeBufferTail;
//
//short allowSet;
//short timeIsCorrect;
//short allTimeHasBeenSet;
//
//int TenMiliSeconds;
//
//char transmitChar;
//
//short buttonsBuffer[3][4];
//short clockStarted;

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
