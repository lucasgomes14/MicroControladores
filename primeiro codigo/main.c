/**
  ******************************************************************************

 	 * Projeto: microControlador
 	 * Placa: STM32F407VEx
 	 * Descrição: Ligando e desligando LED
 	 * Autor: Lucas Matheus
  ******************************************************************************
*/


#include "stm32f4xx.h"

void atraso(int delay){
	while(delay > 0) --delay;
}

int main(void){

	RCC -> AHB1ENR |= 1; // Liga o clock do GPIOA
	GPIOA -> MODER |= (0b01 << 12); // Configura o pino PA6 como saida

	while(1){

		GPIOA -> ODR |= (1 << 6); // Nível lógico alto no pino 6(desliga LED)
		atraso(1000000); // Aguarda um tempo

		GPIOA -> ODR &= ~(1 << 6); // Nível lógico baixo no pino 6(liga LED)
		atraso(1000000); // Aguarda um tempo
	}

}
