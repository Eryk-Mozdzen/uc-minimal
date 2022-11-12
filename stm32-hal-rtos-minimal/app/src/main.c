#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if(htim->Instance==TIM11) {
		HAL_IncTick();
	}
}

void blink(void *param) {
    (void)param;

	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef led = {
		.Pin = GPIO_PIN_5,
		.Mode = GPIO_MODE_OUTPUT_PP,
		.Pull = GPIO_NOPULL,
		.Speed = GPIO_SPEED_FREQ_LOW
	};

	HAL_GPIO_Init(GPIOA, &led);

    while(1) {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
        vTaskDelay(1000);

        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
        vTaskDelay(1000);
    }
}

int main() {

	HAL_Init();
	
	RCC_OscInitTypeDef oscillator = {
		.OscillatorType = RCC_OSCILLATORTYPE_HSI,
		.HSIState = RCC_HSI_ON,
		.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT,
		.PLL.PLLState = RCC_PLL_ON,
		.PLL.PLLSource = RCC_PLLSOURCE_HSI,
		.PLL.PLLM = 8,
		.PLL.PLLN = 100,
		.PLL.PLLP = RCC_PLLP_DIV2,
		.PLL.PLLQ = 4
	};

	RCC_ClkInitTypeDef clock = {
		.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2,
		.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK,
		.AHBCLKDivider = RCC_SYSCLK_DIV1,
		.APB1CLKDivider = RCC_HCLK_DIV2,
		.APB2CLKDivider = RCC_HCLK_DIV1
	};

	HAL_RCC_OscConfig(&oscillator);
	HAL_RCC_ClockConfig(&clock, FLASH_LATENCY_2);

    xTaskCreate(blink, "blink", 1024, NULL, 4, NULL);

    vTaskStartScheduler();

    return 0;
}
