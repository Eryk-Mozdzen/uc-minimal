#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htim11;

void NMI_Handler() {
	while(1);
}

void HardFault_Handler() {
	while(1);
}

void MemManage_Handler() {
	while(1);
}

void BusFault_Handler() {
	while(1);
}

void UsageFault_Handler() {
	while(1);
}

void DebugMon_Handler() {

}

void TIM1_TRG_COM_TIM11_IRQHandler() {
	HAL_TIM_IRQHandler(&htim11);
}
