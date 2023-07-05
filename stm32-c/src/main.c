/*
    blink example for
    NUCLEO-F411RE development board
    led is connected to PA5
*/

#include "stm32f4xx.h"

int main() {

    // enable port A and set PA5 as output
    RCC->AHB1ENR |=RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER |=GPIO_MODER_MODER5_0;

    while(1) {
        // set PA5 and wait
        GPIOA->BSRR |=GPIO_BSRR_BS5;
        for(uint32_t i=0; i<1000000; ++i);

        // reset PA5 and wait
        GPIOA->BSRR |=GPIO_BSRR_BR5;
        for(uint32_t i=0; i<1000000; ++i);
    }
}
