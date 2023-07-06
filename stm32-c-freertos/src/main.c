#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"

void blink(void *param) {

    RCC->AHB1ENR |=RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER |=GPIO_MODER_MODER5_0;

    while(1) {
        GPIOA->BSRR |=GPIO_BSRR_BS5;
        vTaskDelay(1000);

        GPIOA->BSRR |=GPIO_BSRR_BR5;
        vTaskDelay(1000);
    }
}

int main() {

    NVIC_SetPriorityGrouping(0);

    xTaskCreate(blink, "blink", 1024, NULL, 4, NULL);

    vTaskStartScheduler();
}
