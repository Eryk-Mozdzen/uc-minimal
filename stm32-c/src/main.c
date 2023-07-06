#include "stm32f4xx.h"

int main() {

    RCC->AHB1ENR |=RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER |=GPIO_MODER_MODER5_0;

    while(1) {
        GPIOA->BSRR |=GPIO_BSRR_BS5;
        for(uint32_t i=0; i<1000000; ++i);

        GPIOA->BSRR |=GPIO_BSRR_BR5;
        for(uint32_t i=0; i<1000000; ++i);
    }
}
