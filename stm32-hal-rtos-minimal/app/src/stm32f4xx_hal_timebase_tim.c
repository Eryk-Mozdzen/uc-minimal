#include "stm32f4xx_hal.h"

TIM_HandleTypeDef htim11;

HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority) {
	
	HAL_NVIC_SetPriority(TIM1_TRG_COM_TIM11_IRQn, TickPriority ,0);
	HAL_NVIC_EnableIRQ(TIM1_TRG_COM_TIM11_IRQn);

	__HAL_RCC_TIM11_CLK_ENABLE();

	RCC_ClkInitTypeDef clkconfig;
	uint32_t pFLatency;
	HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);
	
	const uint32_t uwTimclock = HAL_RCC_GetPCLK2Freq();
	const uint32_t uwPrescalerValue = (uwTimclock/1000000) - 1;

	htim11.Instance = TIM11;
	htim11.Init.Period = 999;
	htim11.Init.Prescaler = uwPrescalerValue;
	htim11.Init.ClockDivision = 0;
	htim11.Init.CounterMode = TIM_COUNTERMODE_UP;

	if(HAL_TIM_Base_Init(&htim11)!=HAL_OK)
		return HAL_ERROR;

	return HAL_TIM_Base_Start_IT(&htim11);
}
