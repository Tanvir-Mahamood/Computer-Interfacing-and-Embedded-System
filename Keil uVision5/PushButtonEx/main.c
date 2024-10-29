// PA7 int and input, PB15 Output
#include"stm32f10x.h"
void EnClock(void);
void EnPin(void);
void EXTI_Config(void);
void NVIC_Config(void);
void NVIC_Config(void);
void EXTI9_5_IRQHandler(void);

void EnClock(void){
RCC->APB2ENR |= (1UL<<2) | (1UL<<3) | (1UL<<0);
}

void EnPin(void){
GPIOA->CRL &= ~(15UL<<28);
GPIOA->CRL |= 4UL<<28;
	
GPIOB->CRH &= ~(15UL<<28);
GPIOB->CRH |= 3UL<<28;
}

void EXTI_Config(void){
AFIO->EXTICR[1] &= ~(15UL<<12);
AFIO->EXTICR[1] |= 0<<12;

EXTI->IMR  |= 1UL<<7;
EXTI->RTSR |= 1UL<<7;
EXTI->FTSR |= 1UL<<7;
}

void NVIC_Config(void){
NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void EXTI9_5_IRQHandler(void){
if(EXTI->PR & 1UL<<7) 
		EXTI->PR |= 1UL<<7;

if(GPIOA->IDR & 1UL<<7)
	GPIOB->ODR |= 1UL<<15;
else 
	GPIOB->ODR &= 0UL<<15;

}

int main(){
EnClock();
EnPin();
EXTI_Config();
NVIC_Config();
while(1);

}


