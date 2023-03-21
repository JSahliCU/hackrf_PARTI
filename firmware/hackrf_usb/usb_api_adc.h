#ifndef __USB_API_ADC_H__
#define __USB_API_ADC_H__

#include <usb_type.h>
#include <usb_request.h>

usb_request_status_t usb_vendor_request_read_adc(
	usb_endpoint_t* const endpoint,
	const usb_transfer_stage_t stage);

uint8_t usb_adc_init();

#endif /* end of include guard:__USB_API_ADC_H__ */