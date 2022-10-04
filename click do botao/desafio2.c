/**
  ******************************************************************************
 	 * Projeto: microControlador
 	 * Placa: STM32F407VEx
 	 * Descrição: Ligando e desligando LED
 	 * Autor: Lucas Matheus
  ******************************************************************************
*/


#include "stm32f4xx.h"

#define K0 !(GPIOE->IDR & (1<<4))
#define K1 !(GPIOE->IDR & (1<<3))
#define LED_ON GPIOA->ODR &= ~(1<<6)
#define LED_OFF GPIOA->ODR |= (1<<6)

int main(void){
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;            //habilita o clock do GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;            //habilita o clock do GPIOE

    GPIOA->MODER |= (0b01 << 12);    //configura o pino PA6 como saída
    //GPIOA->MODER |= (0b01 << 14);    //configura o pino PA6 como saída
    GPIOE->MODER &= ~(0b11 << 6);    //configurando o pino PE3 como entrada
    GPIOE->PUPDR |= (0b01 << 6);    //liga o resistor de pull-up no pino PE3 (pra garanbir nível alto quando a chave estiver solta)
    GPIOE->MODER &= ~(0b11 << 8);    //configurando o pino PE4 como entrada
    GPIOE->PUPDR |= (0b01 << 8);    //liga o resistor de pull-up no pino PE4 (pra garanbir nível alto quando a chave estiver solta)


    //o LED em PA6 só deve acender ao pressionar primeiro K0 e depois K1
    while(1){
    	LED_OFF;

	if(!K0 && K1){
		LED_OFF;
		while(K1);
	}
	if(K0 && !K1){
		LED_OFF;
		while(K0){
			if(K1)
				LED_ON;
			else
				LED_OFF;
		}
	}
    }
}
