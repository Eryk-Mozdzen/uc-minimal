#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

static void blink() {
	const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

	gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);

	while(1) {
		gpio_pin_set_dt(&led, 1);
		k_msleep(1000);

		gpio_pin_set_dt(&led, 0);
		k_msleep(1000);
	}
}

K_THREAD_DEFINE(blink_id, 1024, blink, NULL, NULL, NULL, 7, 0, 0);
