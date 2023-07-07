#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

static void blink(void *param) {

	gpio_config_t led = {
		.pin_bit_mask = GPIO_Pin_2,
		.mode = GPIO_MODE_OUTPUT,
		.pull_up_en = GPIO_PULLUP_DISABLE,
		.pull_down_en = GPIO_PULLDOWN_DISABLE,
		.intr_type = GPIO_INTR_DISABLE
	};

	gpio_config(&led);

	while(1) {
		gpio_set_level(GPIO_NUM_2, 1);
		vTaskDelay(100);

		gpio_set_level(GPIO_NUM_2, 0);
		vTaskDelay(100);
	}
}

void app_main() {

	xTaskCreate(blink, "blink", 3000, NULL, 5, NULL);
}
