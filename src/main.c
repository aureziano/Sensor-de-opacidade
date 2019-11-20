#include "stm32f10x.h"
#include "lcd.h"
#include "stdio.h"
#include "keypad.h"
#include "string.h"
#include "stdlib.h"

int i; //contador opaco
int j; //contador nao opaco
#define LEDVERDE	GPIO_Pin_9 //Esteira
#define LEDAZUL		GPIO_Pin_8 //Aviso de nao opaco
#define PORTALED	GPIOC

#define SENSOR		GPIO_Pin_0 // sensor de opacidade
#define PORTABOTAO	GPIOA


int main()
{
	GPIO_InitTypeDef GPIO_InitStructure;//inicia configuração das GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC,  ENABLE);//ativa clock para GPIO Port C
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//Ativa o clock para a interrupção TIM2

	GPIO_InitStructure.GPIO_Pin = LEDAZUL | LEDVERDE ; //Configuração do Pino 8 e 9 para saída
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORTALED, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = SENSOR;//PIN 0 configurado como entrada(nesse caso botão no exemplo) na GPIO Port A
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;// Inserção flutuante
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORTABOTAO, &GPIO_InitStructure);

	TIM_TimeBaseInitTypeDef TimerInitStructure;
	TimerInitStructure.TIM_Prescaler = 4000-1; //Prescaler 72MHz/4000 = 18Khz => 18000 ciclos/sec
	TimerInitStructure.TIM_Period = 4000-1;
	TimerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TimerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TimerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TimerInitStructure);
	TIM_Cmd(TIM2, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	 lcd_init(); //iniciação do LCD
	 KeypadInit(); //Opção de utilização de um teclado matricial 4x3
	 delay_init();// iniciação da função dalay
	 lcd_clear(); //Limpa LCD
	 i=0; //contador de opacidade zerado
	 j=0; // contador de nao apacidade zerado
	 char result[20];

	 while(1)
	 {
		 GPIO_SetBits(PORTALED,LEDAZUL); // liga esteira
		 GPIO_ResetBits(PORTALED,LEDVERDE); // apaga led verde
		 GPIO_ResetBits(PORTABOTAO,SENSOR); // seta 0 para o sensor
		 lcd_clear();
		 lcd_line1(); //habilita linha 1 do LCD
//		  char result;
//		  if (i >= 10) {
//		      result = 'A' + i - 10;
//		  } else {
//		      result = '0' + i;
//		  }
		  itoa(i,result,10); // função que transforma int em string
		  lcd_print("CONTADOR:"); //printa na linha 1
		  lcd_line2(); //habilita linha 2
		  lcd_print(result); // printa na linha 2 o contador de opaco
		  delay_ms(50); // dalay de 50 ms

		  if (GPIO_ReadInputDataBit(PORTABOTAO,SENSOR)) //se o sensor encontra elemento não opaco
		  {

			  GPIO_ResetBits(PORTALED,LEDAZUL); //seta 0 no LED azul
			  if (TIM_GetITStatus(TIM2, TIM_IT_Update)) { //aciona o temporizador TIM2

					GPIO_SetBits(PORTALED,LEDVERDE);
					i = i + 1;
//					if (i >= 10) {
//						result = 'A' + i - 10;
//					} else {
//						result = '0' + i;
//					}
					itoa(i,result,10);
					lcd_line2();
					lcd_print(result);
					delay_ms(1000);
					//Como realizamos o trabalho necessário, evitamos que esta interrupção siga sendo avaliada por demais partes do CMSIS.
				    //Para isso só precisamos limpar o BIT de interrupção pendente de overflow.
					TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
				}

		  }
		  else
		  {
			  	  j = j + 1;
//			  	  if (j >= 10) {
//					result = 'A' + j - 10;
//				  } else {
//					result = '0' + j;
//				  }
			  	  itoa(j,result,10);
				  lcd_clear();
				  lcd_line1();
				  lcd_print("NAO OPACO:");
				  lcd_line2();
				  lcd_print(result);
				  delay_ms(3000);

		  }


	 }
}



