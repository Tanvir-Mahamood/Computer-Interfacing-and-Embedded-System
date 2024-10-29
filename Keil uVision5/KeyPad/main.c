#include "stm32f10x.h"

void enable_clock(void);
void set_output_pins(void);
void set_input_pins(void);
void get_column(void);
void get_row(void);
void get_display(uint8_t n);

int row, col;
uint8_t key_map [4][3] =
{
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9},
    {0, 0, 0},
};

void enable_clock(void)
{
    RCC->APB2ENR |= 1UL<<2; // A
    RCC->APB2ENR |= 1UL<<3; // B
}

void set_output_pins(void)
{
// Set PA0, PA1, PA2, PA3 as output (R1, R2, R3, R4)
    GPIOA->CRL &= ~(15UL<<0); // Erase PA0 CNF and MODE
    GPIOA->CRL |= (3UL<<0); // Set PA0 as Output
    GPIOA->CRL &= ~(15UL<<4); // Erase PA1 CNF and MODE
    GPIOA->CRL |= (3UL<<4); // Set PA1 as Output
    GPIOA->CRL &= ~(15UL<<8); // Erase PA2 CNF and MODE
    GPIOA->CRL |= (3UL<<8); // Set PA2 as Output
    GPIOA->CRL &= ~(15UL<<12); // Erase PA3 CNF and MODE
    GPIOA->CRL |= (3UL<<12); // Set PA3 as Output

// B3, B4, B5, B6, for final output
    GPIOB->CRL &= ~(15UL<<12);
    GPIOB->CRL |= (3UL<<12);
    GPIOB->CRL &= ~(15UL<<16);
    GPIOB->CRL |= (3UL<<16);
    GPIOB->CRL &= ~(15UL<<20);
    GPIOB->CRL |= (3UL<<20);
    GPIOB->CRL &= ~(15UL<<24);
    GPIOB->CRL |= (3UL<<24);
}

void set_input_pins(void)
{
// Set PA4, PA5, PA6 as Input (C1, C2, C3)
    GPIOA->CRL &= ~(15UL<<16); // Erase PA4 CNF and MODE
    GPIOA->CRL |= (4UL<<16); // Set PA4 as Input
    GPIOA->CRL &= ~(15UL<<20); // Erase PA5 CNF and MODE
    GPIOA->CRL |= (4UL<<20); // Set PA5 as Input
    GPIOA->CRL &= ~(15UL<<24); // Erase PA6 CNF and MODE
    GPIOA->CRL |= (4UL<<24); // Set PA6 as Input
}

void get_column(void)
{
// Check whether PA4 is 0 or not
    if((GPIOA->IDR & 1UL<<4) == 0)
    {
        col = 0;
    }
// Check whether PA5 is 0 or not
    else if((GPIOA->IDR & 1UL<<5) == 0)
    {
        col = 1;
    }
// Check whether PA6 is 0 or not
    else if((GPIOA->IDR & 1UL<<6) == 0)
    {
        col = 2;
    }
// PA4, PA5, PA6 are all 1. No button pressed.
    else
    {
        col = -1;
    }
}

void get_row(void)
{
// Set PA0 as 0 and check if all columns are 1
    GPIOA->ODR &= ~(15UL<<0);
    GPIOA->ODR |= (14UL<<0);
    if((GPIOA->IDR & (7UL<<4)) != 112)
    {
        row = 0;
    }
// Set PA0 as 0 and check if all columns are 1
    GPIOA->ODR &= ~(15UL<<0);
    GPIOA->ODR |= (13UL<<0);
    if((GPIOA->IDR & (7UL<<4)) != 112)
    {
        row = 1;
    }
// Set PA0 as 0 and check if all columns are 1
    GPIOA->ODR &= ~(15UL<<0);
    GPIOA->ODR |= (11UL<<0);
    if((GPIOA->IDR & (7UL<<4)) != 112)
    {
        row = 2;
    }
// Set PA0 as 0 and check if all columns are 1
    GPIOA->ODR &= ~(15UL<<0);
    GPIOA->ODR |= (7UL<<0);
    if((GPIOA->IDR & (7UL<<4)) != 112)
    {
        row = 3;
    }
}


void get_display(uint8_t n)
{
  GPIOB->ODR &= ~(15UL<<3);  
	uint8_t led_mode, pos = 3;
    for(uint8_t i=0; i<4; i++)
    {
        led_mode = (n&1);
        n = (n>>1);
        if(led_mode)
        {
            GPIOB->ODR |= (1UL<<pos);
        }
        pos += 1;
    }
}

int main(void)
{
    enable_clock();
    set_output_pins();
    set_input_pins();

    while(1)
    {
        get_column();
        if (col == -1)
        {
            continue;
        }
        get_row();
        get_display(key_map[row][col]);
    }
}

