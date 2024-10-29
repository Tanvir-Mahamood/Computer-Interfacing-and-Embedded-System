// Change Blinking Rate on PC15 LED using SysTick Delay

#include "stm32f10x.h"
void systick_init(void);
void delay_ms(void);
void delay_t(unsigned long t);
void GPIO_config(void);


void systick_init(void) {
	SysTick->LOAD = 72000 - 1; 
	SysTick->VAL = 0; 
	SysTick->CTRL = 5; 
}
void delay_ms(void) {
	while (!(SysTick->CTRL & (1 << 16))); 
}
void delay_t(unsigned long t) {
	while (t--) { delay_ms();}
}


void GPIO_config(void) {
	RCC->APB2ENR |= (1 << 4);
	
	GPIOC->CRH &= ~(15UL << 28); 
	// MODE15[1:0] = 10 (Output mode, max speed 2 MHz)
	GPIOC->CRH |= (2UL << 28);
}
int main(void) {
	systick_init(); 
	GPIO_config();
	//unsigned long del = 2000;
	while (1) {
		for(uint32_t i=100; i<=1000; i+=100) {
			GPIOC->ODR = (1 << 15); 
			delay_t(i); // Delay for 500 ms
			GPIOC->ODR = (0 << 15); 
			delay_t(i); 
		}
		for(uint32_t i=1000; i>0; i-=100) {
			GPIOC->ODR = (1 << 15); 
			delay_t(i); // Delay for 500 ms
			GPIOC->ODR = (0 << 15); 
			delay_t(i); 
		}
	}
}

