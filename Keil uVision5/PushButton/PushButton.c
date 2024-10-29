// Detecting button press at PC15 and controlling LED connected to PB0.

#include "stm32f10x.h" // Device header
void setup(void);
uint8_t debounce(uint8_t last);
void systick_init(void);
void delay_ms(void);
void delay_t(unsigned long t);


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


void setup(void) { 
	RCC->APB2ENR |= (1<<3); 
	RCC->APB2ENR |= (1<<4); 
	
	GPIOB->CRL &= ~(15UL<<0);
	GPIOB->CRL |= 3UL<<0;

	GPIOC->CRH &= ~(15UL<<28);
	GPIOC->CRH |= 4UL<<28;
}
uint8_t debounce(uint8_t last) {
	uint8_t current = (GPIOC->IDR & (1<<15)) ? 1 : 0;
	if (last != current) {
		delay_t(50); // 50ms delay
		current = (GPIOC->IDR & (1<<15)) ? 1 : 0;
	}
	return current;
}
int main() {
	uint8_t lastButton = 0;
	uint8_t currentButton = 0;
	uint8_t ledOn = 0;
	systick_init();
	setup();
	while (1) {
		currentButton = debounce(lastButton);
		if (lastButton == 0 && currentButton == 1) {
			ledOn = !ledOn;
		}
		lastButton = currentButton;
		if (ledOn) {
			GPIOB->ODR |= (1UL<<0);
		} 
		else {
			GPIOB->ODR &= ~(1UL<<0);
		}
	}
}
