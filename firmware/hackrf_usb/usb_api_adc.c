#include "usb_api_gpio.h"
#include "usb_queue.h"

#include "hackrf_core.h"
// #include "adc.h"
#include <libopencm3/lpc43xx/scu.h>

#include <stddef.h>
#include <sct.h>

usb_request_status_t usb_vendor_request_read_adc(
	usb_endpoint_t* const endpoint,
	const usb_transfer_stage_t stage){    
	if (stage == USB_TRANSFER_STAGE_SETUP) {
		if (endpoint->setup.index < MAX2837_NUM_REGS) {
			const uint16_t value =
				max283x_reg_read(&max283x, endpoint->setup.index);
			endpoint->buffer[0] = value & 0xff;
			endpoint->buffer[1] = value >> 8;
			usb_transfer_schedule_block(
				endpoint->in,
				&endpoint->buffer,
				2,
				NULL,
				NULL);
			usb_transfer_schedule_ack(endpoint->out);
			return USB_REQUEST_STATUS_OK;
		}
		return USB_REQUEST_STATUS_STALL;
	} else {
		return USB_REQUEST_STATUS_OK;
	}
}

uint8_t usb_adc_init(){

    //scu_pinmux(P4_1 or P4_3, SCU_ENAIO0);

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