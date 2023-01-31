#include "usb_api_gpio.h"
#include "usb_queue.h"

#include "hackrf_core.h"
#include "gpio.h"
#include "gpio_lpc.h"
#include "i2c_bus.h"
#include <libopencm3/lpc43xx/scu.h>

#include <stddef.h>
#include <sct.h>

static struct gpio_t gpio_pins[] = {
    GPIO(3, 8),  // u1ctrl   IO2
    GPIO(3, 14), // u3ctrl0  IO3
    GPIO(3, 15), // u3ctrl1  IO4
    GPIO(3, 12), // u2ctrl0  IO5
    GPIO(3, 13)  // u2ctrl1  IO6
};

usb_request_status_t usb_vendor_request_set_gpio(
	usb_endpoint_t* const endpoint,
	const usb_transfer_stage_t stage){    
	if (stage == USB_TRANSFER_STAGE_SETUP) {

        if (endpoint->setup.index < 5){
            gpio_write(&gpio_pins[endpoint->setup.index], endpoint->setup.value);
        } // Register value
        usb_transfer_schedule_ack(endpoint->in);
	}
	return USB_REQUEST_STATUS_OK;
}

uint8_t usb_gpio_init(){

	scu_pinmux(SCU_PINMUX_GPIO3_8, SCU_GPIO_FAST | SCU_CONF_FUNCTION0);
	scu_pinmux(SCU_PINMUX_GPIO3_12, SCU_GPIO_FAST | SCU_CONF_FUNCTION0);
	scu_pinmux(SCU_PINMUX_GPIO3_13, SCU_GPIO_FAST | SCU_CONF_FUNCTION0);
	scu_pinmux(SCU_PINMUX_GPIO3_14, SCU_GPIO_FAST | SCU_CONF_FUNCTION0);
	scu_pinmux(SCU_PINMUX_GPIO3_15, SCU_GPIO_FAST | SCU_CONF_FUNCTION0);

    uint8_t i = 0;

    // clear the settings of the pins
	for (i = 0; i < 5; i++) {
		gpio_output(&gpio_pins[i]);
		gpio_write(&gpio_pins[i], 0);
	}

    return 0;
}