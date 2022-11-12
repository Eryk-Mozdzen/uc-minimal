#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"

void vApplicationMallocFailedHook() {
    taskDISABLE_INTERRUPTS();
    while(1);
}

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName) {
	(void)pcTaskName;
	(void)pxTask;

	taskDISABLE_INTERRUPTS();
	while(1);
}

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize) {
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];

    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

void clock_init() {
    RCC->CR |=RCC_CR_HSION;
    while(!(RCC->CR & RCC_CR_HSIRDY));

    RCC->APB1ENR |=RCC_APB1ENR_PWREN;
    PWR->CR |=(3<<PWR_CR_VOS_Pos);
    FLASH->ACR |=FLASH_ACR_LATENCY_3WS | FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN;

    RCC->CFGR |=RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_PPRE2_DIV1 | RCC_CFGR_HPRE_DIV1;
    
    RCC->PLLCFGR &=~RCC_PLLCFGR_PLLM_Msk;
    RCC->PLLCFGR &=~RCC_PLLCFGR_PLLN_Msk;
    RCC->PLLCFGR &=~RCC_PLLCFGR_PLLP_Msk;
    RCC->PLLCFGR &=~RCC_PLLCFGR_PLLQ_Msk;
    RCC->PLLCFGR |=(8<<RCC_PLLCFGR_PLLM_Pos) | (100<<RCC_PLLCFGR_PLLN_Pos) | (0<<RCC_PLLCFGR_PLLP_Pos) | (4<<RCC_PLLCFGR_PLLQ_Pos) | RCC_PLLCFGR_PLLSRC_HSI;

    RCC->CR |=RCC_CR_PLLON;
    while(!(RCC->CR & RCC_CR_PLLRDY));

    RCC->CFGR |=RCC_CFGR_SW_PLL;
    while((RCC->CFGR & RCC_CFGR_SW)!=RCC_CFGR_SW_PLL);
}

void blink(void *param) {
    (void)param;

    // PA5
    RCC->AHB1ENR |=RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |=(1<<GPIO_MODER_MODER5_Pos);

    while(1) {
        GPIOA->BSRR |=GPIO_BSRR_BS5;
        vTaskDelay(1000);
        
        GPIOA->BSRR |=GPIO_BSRR_BR5;
        vTaskDelay(1000);
    }
}

int main() {

    clock_init();
    NVIC_SetPriorityGrouping(0);

    xTaskCreate(blink, "blink", 1024, NULL, 4, NULL);

    vTaskStartScheduler();

    return 0;
}