#include "stm32f4xx_hal.h"
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

void vApplicationTickHook() {
	HAL_IncTick();
}

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize) {
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];

    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

void clock_init() {
	RCC_OscInitTypeDef oscillator = {0};
	oscillator.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	oscillator.HSIState = RCC_HSI_ON;
	oscillator.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	oscillator.PLL.PLLState = RCC_PLL_ON;
	oscillator.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	oscillator.PLL.PLLM = 8;
	oscillator.PLL.PLLN = 100;
	oscillator.PLL.PLLP = 2;
	oscillator.PLL.PLLQ = 4;
	HAL_RCC_OscConfig(&oscillator);

	RCC_ClkInitTypeDef clock = {0};
	clock.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	clock.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	clock.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clock.APB1CLKDivider = RCC_HCLK_DIV2;
	clock.APB2CLKDivider = RCC_HCLK_DIV1;
	HAL_RCC_ClockConfig(&clock, FLASH_LATENCY_2);
}

void blink(void *param) {
    (void)param;

    // PA5
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef led = {0};
	led.Pin = GPIO_PIN_5;
	led.Mode = GPIO_MODE_OUTPUT_PP;
	led.Pull = GPIO_NOPULL;
	led.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &led);

    while(1) {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
        vTaskDelay(1000);
        
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
        vTaskDelay(1000);
    }
}

int main() {

    clock_init();
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    xTaskCreate(blink, "blink", 1024, NULL, 4, NULL);

    vTaskStartScheduler();

    return 0;
}