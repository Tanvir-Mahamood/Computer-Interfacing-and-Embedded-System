// Blinking LED on PC15 using SysTick Delay

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
	while (1) {
		GPIOC->ODR = (1 << 15); 
		delay_t(500); // Delay for 500 ms
		GPIOC->ODR = (0 << 15); 
		delay_t(500); 
	}
}


/*#include <stdint.h>
#define RCC_BASE 0x40021000
#define APB2ENR_OFFSET 0x18
#define GPIOA_BASE 0x40010800
#define GPIOA_CRL_OFFSET 0x00
#define GPIOA_ODR_OFFSET 0x0C
#define RCC_APB2ENR (*(volatile uint32_t *) (RCC_BASE+APB2ENR_OFFSET))
#define GPIOA_CRL (*(volatile uint32_t *) (GPIOA_BASE+GPIOA_CRL_OFFSET))
#define GPIOA_ODR (*(volatile uint32_t *) (GPIOA_BASE+GPIOA_ODR_OFFSET))
	
void GPIO_Clock_Enable(void);
void GPIO_Pin_Init(void);
void delay(int n);

void GPIO_Clock_Enable(void) {
	RCC_APB2ENR |= 1UL<<2; //0x0100
}
void GPIO_Pin_Init(void) {
	GPIOA_CRL &= ~(15UL<<20);
	GPIOA_CRL |= 3UL<<20; 
}

void delay(int n) {
	for(; n>0; n--) {
		for(int i=0; i<1000000; i++){ }
	}
}

int main(void) {
	GPIO_Clock_Enable();
	GPIO_Pin_Init();
	
	while(1) {
		GPIOA_ODR |= 1UL<<5;
		delay(10);
		GPIOA_ODR &= ~(1UL<<5);
		delay(10);
	}
}*/
