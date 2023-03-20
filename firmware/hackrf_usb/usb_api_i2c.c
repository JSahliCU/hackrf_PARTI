#include "usb_api_i2c.h"
#include "usb_queue.h"

#include "hackrf_core.h"
#include "gpio.h"
#include "gpio_lpc.h"
#include "i2c_bus.h"
#include <libopencm3/lpc43xx/scu.h>

#include <stddef.h>
#include <sct.h>

pcf8575_driver_t solid_loop_gpio_expander = {
	.bus = &i2c0,
	.i2c_address = 0x40,
};

pcf8575_driver_t split_loop_gpio_expander = {
	.bus = &i2c0,
	.i2c_address = 0x4E,
};

/*
 * Write to one or more contiguous registers. data[0] should be the first
 * register number, one or more values follow.
 */
void pcf8575_write(
	pcf8575_driver_t* const drv,
	const uint8_t* const data,
	const size_t data_count)
{
	i2c_bus_transfer(drv->bus, drv->i2c_address, data, data_count, NULL, 0);
}

usb_request_status_t usb_vendor_request_set_i2c_split(
	usb_endpoint_t* const endpoint,
	const usb_transfer_stage_t stage){    
	if (stage == USB_TRANSFER_STAGE_SETUP) {
        pcf8575_write(&split_loop_gpio_expander, endpoint->setup.value, 2);
        usb_transfer_schedule_ack(endpoint->in);
	}
	return USB_REQUEST_STATUS_OK;
}

usb_request_status_t usb_vendor_request_set_i2c_solid(
	usb_endpoint_t* const endpoint,
	const usb_transfer_stage_t stage){    
	if (stage == USB_TRANSFER_STAGE_SETUP) {
        pcf8575_write(&solid_loop_gpio_expander, endpoint->setup.value, 2);
        usb_transfer_schedule_ack(endpoint->in);
	}
	return USB_REQUEST_STATUS_OK;
}

uint8_t usb_i2c_init(){
    // No need to implement or call 
    // since the i2c0 bus is configured for the Si5351C clock generators 
    return 0;
}