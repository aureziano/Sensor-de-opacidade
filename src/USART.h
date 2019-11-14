/*
 * USART.h
 *
 *  Created on: 15 de jun de 2019
 *      Author: aureziano
 */

#ifndef USART_H_
#define USART_H_


#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "delay.h"

#define RX_TX_P	RCC_APB2Periph_GPIOB
#define RX_TX		GPIOB
#define TX			GPIO_Pin_10
#define RX			GPIO_Pin_11

void usart_init(void);
uint8_t Usart_Get(USART_TypeDef* USARTx);
void Usart_PutChar(USART_TypeDef* USARTx, uint8_t ch);
void Usart_PutString(USART_TypeDef* USARTx, uint8_t * str);
void Usart_PutNumber(USART_TypeDef* USARTx, uint32_t x);

#endif /* USART_H_ */
