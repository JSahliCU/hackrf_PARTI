#ifndef __USB_API_I2C_H__
#define __USB_API_I2C_H__

#include <usb_type.h>
#include <usb_request.h>

usb_request_status_t usb_vendor_request_set_i2c_split(
	usb_endpoint_t* const endpoint,
	const usb_transfer_stage_t stage);

usb_request_status_t usb_vendor_request_set_i2c_solid(
	usb_endpoint_t* const endpoint,
	const usb_transfer_stage_t stage);

typedef struct {
	i2c_bus_t* const bus;
	uint8_t i2c_address;
} pcf8575_driver_t;

uint8_t usb_i2c_init();

#endif /* end of include guard:__USB_API_I2C_H__ */