#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

static void blink() {
	
	const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

	if(!device_is_ready(led.port))
		return;

	if(gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE)<0)
		return;

	while(1) {

		if(gpio_pin_toggle_dt(&led)<0)
			return;

		k_msleep(100);
	}
}

K_THREAD_DEFINE(blink_id, 1024, blink, NULL, NULL, NULL, 7, 0, 0);

void main() {

}
