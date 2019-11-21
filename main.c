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
#define OBJ		GPIO_Pin_1 // passagem de objeto
#define ESTEIRA		GPIO_Pin_2 // passagem de objeto
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

	GPIO_InitStructure.GPIO_Pin = ESTEIRA ; //PIN 2 PORT A - ligar um relé
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORTABOTAO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = OBJ;//PIN 1 PORT A - objeto entrou na esteira
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;// Inserção flutuante
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORTABOTAO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = SENSOR;//PIN 0 configurado como entrada(nesse caso botão no exemplo) na GPIO Port A
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;// Inserção flutuante
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORTABOTAO, &GPIO_InitStructure);

	TIM_TimeBaseInitTypeDef TimerInitStructure;
	//Configura o divisor do timer para 1000 ciclos por segundo.
	//O clock do sistema roda a 72Mhz, logo:
	//72000000 / 720000 = 1000 ciclos/seg
	TimerInitStructure.TIM_Prescaler = SystemCoreClock/100 -1;
	TimerInitStructure.TIM_Period = 4000-1;//Contamos até 1000 (0..999), assim temos 1000 contagens por segundo. Com isso teremos um overflow por segundo.
	TimerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//contador conta de 0 até 999, de forma crescente
	TimerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//Não queremos nenhum divisor de clock, o calculo é com os 72Mhz.
	TimerInitStructure.TIM_RepetitionCounter = 0;//Zerando tudo.
	TIM_TimeBaseInit(TIM2, &TimerInitStructure);
	TIM_Cmd(TIM2, ENABLE);//Ligando o timer
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);//Habilitando a atualização do bit de interrupção para o overflow.

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
					itoa(i,result,10);
					lcd_line2();
					lcd_print(result);
//					delay_ms(1000);
					//Como realizamos o trabalho necessário, evitamos que esta interrupção siga sendo avaliada por demais partes do CMSIS.
				    //Para isso só precisamos limpar o BIT de interrupção pendente de overflow.
					TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
				}

		  }
		  else
		  {
			  if (TIM_GetITStatus(TIM2, TIM_IT_Update))
			  {
				  j = j + 1;
				  itoa(j,result,10);
				  lcd_clear();
				  lcd_line1();
				  lcd_print("NAO OPACO:");
				  lcd_line2();
				  lcd_print(result);
//				  delay_ms(3000);
				  TIM_ClearITPendingBit(TIM2,TIM_IT_Update);

			  }


		  }


	 }
}



