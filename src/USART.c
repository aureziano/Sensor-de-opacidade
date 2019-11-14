/*
 * USART.c
 *
 *  Created on: 15 de jun de 2019
 *      Author: aureziano
 */

#include <USART.h>

void usart_init(void)
{
		USART_InitTypeDef USART_InitStructure;
		USART_ClockInitTypeDef USART_ClockInitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,  ENABLE);
		GPIO_InitTypeDef GPIO_InitStructure;

		//Set USART1 Tx (PB.10) as AF push-pull
		GPIO_InitStructure.GPIO_Pin = TX;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(TX, &GPIO_InitStructure);

		//Set USART1 Rx (PB.11) as input floating
		GPIO_InitStructure.GPIO_Pin = RX;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		USART_ClockStructInit(&USART_ClockInitStructure);
		USART_ClockInit(USART3, &USART_ClockInitStructure);

		USART_InitStructure.USART_BaudRate = 9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No ;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

		USART_Init(USART3, &USART_InitStructure);
		USART_Cmd(USART3, ENABLE);
		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

		// Inicializa estrutura do vetor de interrupções
		NVIC_InitTypeDef NVIC_InitStruct;
		NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
		NVIC_Init(&NVIC_InitStruct);

		NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
		NVIC_Init(&NVIC_InitStruct);




}

uint8_t Usart_Get(USART_TypeDef* USARTx)
{
     while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET);
     return (uint8_t)USART_ReceiveData(USARTx);
}

void Usart_PutChar(USART_TypeDef* USARTx, uint8_t ch)
{
  while(!(USARTx->SR & USART_SR_TXE));
  USARTx->DR = ch;
}


void Usart_PutString(USART_TypeDef* USARTx, uint8_t * str)
{
  while(*str !=  0)
  {
    Usart_PutChar(USARTx, *str);
    str++;
  }
}


void Usart_PutNumber(USART_TypeDef* USARTx, uint32_t x)
{
  char value[10]; //a temp array to hold results of conversion
  int i = 0; //loop index

  do
  {
    value[i++] = (char)(x % 10) + '0'; //convert integer to character
    x /= 10;
  } while(x);

  while(i) //send data
  {
    Usart_PutChar(USARTx, value[--i]);
  }
}





