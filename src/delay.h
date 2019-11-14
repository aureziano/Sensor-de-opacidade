/*
 * delay.h
 *
 *  Created on: 8 de jun de 2019
 *      Author: aureziano
 */

#ifndef DELAY_H_
#define DELAY_H_
#include "stm32f10x.h"                  // Device header


// Function prototypes
void delay_init(void);
void delay_ms(uint32_t ms);
void delaysleep_ms(uint32_t ms);


#endif /* DELAY_H_ */
