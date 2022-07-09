#include <stdint.h>
#include "stm32f4xx.h"

void Clock_Init() {
    RCC->CR |=RCC_CR_HSION;
    while(!(RCC->CR & RCC_CR_HSIRDY));

    RCC->APB1ENR |=RCC_APB1ENR_PWREN;
    PWR->CR |=(3<<PWR_CR_VOS_Pos);
    FLASH->ACR |=FLASH_ACR_LATENCY_3WS | FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN;

    RCC->CFGR |=RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_PPRE2_DIV1 | RCC_CFGR_HPRE_DIV1;
    
    RCC->PLLCFGR &=~(0x03F<<RCC_PLLCFGR_PLLM_Pos);
    RCC->PLLCFGR &=~(0x1FF<<RCC_PLLCFGR_PLLN_Pos);
    RCC->PLLCFGR &=~(0x003<<RCC_PLLCFGR_PLLP_Pos);
    RCC->PLLCFGR &=~(0x00F<<RCC_PLLCFGR_PLLQ_Pos);
    RCC->PLLCFGR |=(8<<RCC_PLLCFGR_PLLM_Pos) | (100<<RCC_PLLCFGR_PLLN_Pos) | (0<<RCC_PLLCFGR_PLLP_Pos) | (4<<RCC_PLLCFGR_PLLQ_Pos) | RCC_PLLCFGR_PLLSRC_HSI;

    RCC->CR |=RCC_CR_PLLON;
    while(!(RCC->CR & RCC_CR_PLLRDY));

    RCC->CFGR |=RCC_CFGR_SW_PLL;
    while((RCC->CFGR & RCC_CFGR_SW)!=RCC_CFGR_SW_PLL);
}

int main() {
    
    NVIC_SetPriorityGrouping(0);
    Clock_Init();

    // PA5
    RCC->AHB1ENR |=RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |=GPIO_MODER_MODER5_0;

    while(1) {
        GPIOA->BSRR |=GPIO_BSRR_BS5;
        for(uint32_t i=0; i<1000000; i++);
        
        GPIOA->BSRR |=GPIO_BSRR_BR5;
        for(uint32_t i=0; i<1000000; i++);
    }

    return 0;
}