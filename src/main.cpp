#include "stm32f10x.h"
#include "lcd.h"
#include "stdio.h"
#include "keypad.h"
#include "USART.h"

uint8_t key;
char yazi[16]=" ";
uint32_t sayi=1;
#define LEDVERDE	GPIO_Pin_9
#define LEDAZUL		GPIO_Pin_8
#define PORTALED	GPIOC

//#define BOTAO		GPIO_Pin_0
//#define PORTABOTAO	GPIOA


int main()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC,  ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;


	GPIO_InitStructure.GPIO_Pin = LEDAZUL | LEDVERDE ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORTALED, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = LEDAZUL | LEDVERDE ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORTALED, &GPIO_InitStructure);


//	GPIO_InitStructure.GPIO_Pin = BOTAO;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(PORTABOTAO, &GPIO_InitStructure);

	TIM_TimeBaseInitTypeDef TimerInitStructure;
	TimerInitStructure.TIM_Prescaler = 4000-1;
	TimerInitStructure.TIM_Period = 4000-1;
	TimerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TimerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TimerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TimerInitStructure);
	TIM_Cmd(TIM2, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	 lcd_init();
	 KeypadInit();
	 delay_init();
	 lcd_clear();

	 while(1)
	 {
		  lcd_clear();
		  lcd_line1();
		  lcd_print("VAMOS");
		  delay_ms(50);
		   //Get key pressed
		  key = KeypadGetKey();
			// Display pressed char to LCD
//		  if (key != KEYPAD_NO_PRESSED)
//		  {
//				lcd_line2();
//				lcd_putc(key);
//				delay_ms(250);
//		  }
		  switch(key)
		  {
		  	  case ('1'):
		  	  {
					lcd_line2();
					lcd_print("TESTE 1");
					delay_ms(250);
					Usart_PutChar(USART3,key);
					if (TIM_GetITStatus(TIM2, TIM_IT_Update))
					{
						TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
						if (GPIO_ReadOutputDataBit(PORTALED,LEDVERDE))
						{
							GPIO_ResetBits(PORTALED,LEDVERDE);
							lcd_clear();
							lcd_line2();
							lcd_print("CHATA");
							delay_ms(500);
							lcd_clear();
						}
					}
					break;
		  	  }

		  	case ('2'):
			  {
				lcd_line2();
				lcd_print("TESTE 2");
				GPIO_ResetBits(PORTALED,LEDVERDE);
				GPIO_SetBits(PORTALED,LEDAZUL);
				delay_ms(250);
				Usart_PutChar(USART3,key);
				break;
			  }

		  }

		  lcd_clear();

//		  if (GPIO_ReadInputDataBit(PORTABOTAO,BOTAO))
//		  {//diferente de um
//			  //sprintf(yazi,"%u",sayi);
//			  //sayi++;
//
//			  GPIO_ResetBits(PORTALED,LEDAZUL);
//			  if (TIM_GetITStatus(TIM2, TIM_IT_Update)) {
//					TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//					if (GPIO_ReadOutputDataBit(PORTALED,LEDVERDE)){
//						GPIO_ResetBits(PORTALED,LEDVERDE);
//						lcd_clear();
//						lcd_line2();
//						lcd_print("CHATA");
//						delay_ms(1000);
//						lcd_clear();
//					} else {
//						GPIO_SetBits(PORTALED,LEDVERDE);
//					}
//				}
//
//		  }
//		  else
//		  {
//				  lcd_clear();
//				  lcd_line2();
//				  lcd_print("LEGAL");
//				  delay_ms(1000);
//				  GPIO_SetBits(PORTALED,LEDAZUL);
//				  GPIO_ResetBits(PORTALED,LEDVERDE);
//
//		  }


	 }
}

void USART3_IRQHandler(void)
{
    uint8_t r;
    // RXNE handler
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
        r = Usart_Get(USART3);
        int i = 0;
        switch (r) {
        	case 'a':
        			GPIO_ResetBits(PORTALED, LEDVERDE);
        			GPIO_SetBits(PORTALED, LEDAZUL);
        			break;
			case 'v':
					GPIO_ResetBits(PORTALED, LEDAZUL);
					GPIO_SetBits(PORTALED, LEDVERDE);
					break;

            case '1':
					Usart_PutString(USART3,"Tempo = ");
					Usart_PutNumber(USART3,i);
					Usart_PutString(USART3," s\n\r");
					break;
        }
    }
}

