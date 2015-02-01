/*
	Description: flash the board leds approximately every second
*/

#include "stm32f10x.h"                  // Device header
//B1: Push button B1 labeled USER is connected to the I/O PA0 of STM32F100RBT6B
//		and can be used as WAKE-UP, this button has a external 10k pulldown resistor
//LD3: Green LED LD3 labeled PC9 is connected to the I/O PC9 of STM32F100RBT6B.
//LD4: Blue LED LD4 labeled PC8 is connected to the I/O PC8 of STM32F100RBT6B.

#define FLASH_TIME 0x3FFFFF

void delay_ms(int delay_time);

int main(void){
	//Turn on PORTC peripherial
	RCC->APB2ENR|=(0x1<<4);//Bit 4 IOPCEN: I/O port C clock enable = 0x1 1:I/O port C clock enabled
	//Configure PORTC 
	GPIOC->CRH&=~((0xF<<4)//clean CNF9[1:0] and MODE9[1:0]
								|(0xF<<0));//clean CNF8[1:0]  and MODE8[1:0]
	GPIOC->CRH|=((0x0<<6)//7:6 CNF9[1:0] Port x configuration = 0x0: General purpose output push-pull
			|(0x1<<4)//5:4 MODE9[1:0] Port x mode bits = 0x1: Output mode, max speed 10 MHz.
			|(0x0<<2)//3:2 CNF8[1:0] Port x configuration = 0x0: General purpose output push-pull
			|(0x1<<0));//1:0 MODE8[1:0]  Port x mode bits = 0x1: Output mode, max speed 10 MHz.
	while(1){
		GPIOC->BSRR=((0x1<<9)|(0x1<<8));//Turn on pins PC9 and PC8
		delay_ms(FLASH_TIME);
		GPIOC->BSRR=((0x1<<(8+16))|(0x1<<(9+16)));//Turn off pins PC9 and PC8
		delay_ms(FLASH_TIME);
	}
}

void delay_ms(int delay_time){
	for (int i=0; i<delay_time; i++);
}
