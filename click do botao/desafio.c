/**
  ******************************************************************************

 	 * Projeto: microControlador
 	 * Placa: STM32F407VEx
 	 * Descrição: Ligando e desligando LED quando aperta o botão
 	 * Autor: Lucas Matheus
  ******************************************************************************
*/


#include "stm32f4xx.h"

int main(void){

	// RCC -> AHB1ENR |= 1; 					// Liga o clock do GPIOA
	// RCC -> AHB1ENR |= (1 << 4); 				// Liga o clock do GPIOE
	RCC -> AHB1ENR |= 0b10001;					// Habilitando os clocks do GPIOA e GPIOE

	GPIOA -> MODER |= (0b01 << 12); 			// Configura o pino PA6 como saida
	GPIOA -> MODER |= (0b01 << 14); 			// Configura o pino PA7 como saida

												// quando o K0 é pressionado, PE4 está no nivel logico low
												// quando o K0 não está pressionado, PE4 está em float
												// então precisa deixar o pino em nivel lógico high quando não tiver pressionado.

	// configurando PE3 e PE4 com entradas
	GPIOE -> MODER &= ~(0b11 << 6);				// configura o PE3 como entrada
	GPIOE -> MODER &= ~(0b11 << 8);				// configura o PE4 como entrada

	// configurando para deixar o pino de
	// nivel logico high quando clicar
	GPIOE -> PUPDR |= (0b01 << 6);				// habilita o registrador de pull-up(para mudar de nivel logico floar para high)
	GPIOE -> PUPDR |= (0b01 << 8);				// habilita o registrador de pull-up(para mudar de nivel logico floar para high)

	while(1){

		int k0 = (GPIOE -> IDR & (1 << 4));		// lendo o botão K0
		int k1 = (GPIOE -> IDR & (1 << 3));		// lendo o botão K1

		// teste de logica K0 e K1
		if(k0 || k1){
			GPIOA -> ODR |= (1 << 6);			// desliga LED PA6
			GPIOA -> ODR |= (1 << 7);			// desliga LED PA7
		}
		else{
			if(k0 != 1 && k1 != 1){
				GPIOA -> ODR &= ~(1 << 6);			// desliga LED PA6
				GPIOA -> ODR &= ~(1 << 7);			// desliga LED PA7
			}
		}
	}
}
