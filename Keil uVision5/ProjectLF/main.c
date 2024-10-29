/*
Pressing a button in PA0 will increase blinking rate.
Pressing a button in PA1 will decrease blinking rate.
Design the system.
*/

#include "stm32f10x.h" 
void systick_init(void);
void delay_ms(void);
void delay_t(unsigned long t);

void GPIO_Config(void);
void EXTI_Config(void);
void NVIC_Config(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);

int del = 1000;
int rat = 500;

void systick_init(void) {
	SysTick->LOAD = 72000 - 1; // Set reload register for 1 ms
	SysTick->VAL = 0; // Clear current value register
	SysTick->CTRL = 5; // Enable SysTick with processor clock
}
void delay_ms(void) {
	while (!(SysTick->CTRL & (1 << 16))); // Wait for COUNTFLAG to be 1
}
void delay_t(unsigned long t) {
	while (t--) { delay_ms();}
}

void GPIO_Config(void) {
	// Enable clock for GPIOA and AFIO
	RCC->APB2ENR |= (1UL<<2) | (1UL<<0); 
	
	// Configure PA0 as input floating
	GPIOA->CRL &= ~(15UL<<0); 
	GPIOA->CRL |= (4UL<<0);
	// Configure PA1 as input floating
	GPIOA->CRL &= ~(15UL<<4); 
	GPIOA->CRL |= (4UL<<4);
	
	// Configure PA2 as output push-pull
	GPIOA->CRL &= ~(15UL<<8); // Clear mode and configuration bits for PC15
	GPIOA->CRL |= (3UL<<8); // Set mode to 50 MHz output push-pull
}

void EXTI_Config(void) {
	// Configure EXTI line 0 to be triggered by PA0
	AFIO->EXTICR[0] &= ~(15UL<<0); // Clear EXTI0 bits
	AFIO->EXTICR[0] |= (0UL<<0); // Set EXTI0 to PA0
	
	AFIO->EXTICR[0] &= ~(15UL<<4); // Clear EXTI1 bits
	AFIO->EXTICR[0] |= (0UL<<4); // Set EXTI0 to PA1
	
	// Configure EXTI0 line to trigger on rising edge
	EXTI->IMR |= (1UL<<0); // Unmask EXTI0
	EXTI->RTSR |= (1UL<<0); // Trigger on rising edge
	EXTI->FTSR |= (1UL<<0); // Trigger on falling edge
	
	// Configure EXTI1 line to trigger on rising edge
	EXTI->IMR |= (1UL<<1); // Unmask EXTI0
	EXTI->RTSR |= (1UL<<1); // Trigger on rising edge
	EXTI->FTSR |= (1UL<<1); // Trigger on falling edge
}

void NVIC_Config(void) {
	NVIC_EnableIRQ(EXTI0_IRQn); // Enable EXTI0 interrupt in NVIC
	NVIC_EnableIRQ(EXTI1_IRQn); // Enable EXTI1 interrupt in NVIC
}

void EXTI0_IRQHandler(void) {
	if (EXTI->PR & (1UL<<0)) { // Check if EXTI0 interrupt pending
		EXTI->PR |= (1UL<<0); // Clear the interrupt pending bit
		if (GPIOA->IDR & (1UL<<0)) {
			if(del >= 500) del -= rat;
			//del = 500;
		}
	}
}

void EXTI1_IRQHandler(void) {
	if (EXTI->PR & (1UL<<1)) { // Check if EXTI1 interrupt pending
		EXTI->PR |= (1UL<<1); // Clear the interrupt pending bit
		if (GPIOA->IDR & (1UL<<1)) {
			del += rat;
			//del = 2000;
		}
	}
}

int main(void) {
	systick_init(); 
	GPIO_Config();
	EXTI_Config();
	NVIC_Config();
	while(1)
	{
		GPIOA->ODR = (1UL << 2); 
		delay_t(del);
		GPIOA->ODR = (0UL << 15); 
		delay_t(del); 
	}
}
