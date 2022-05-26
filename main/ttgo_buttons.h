#pragma once

#include "iot_button.h"

#ifdef __cplusplus
extern "C" {
#endif

void init_buttons(int32_t left_gpio_pin, int32_t right_gpio_pin);

button_handle_t get_left_button(void);
button_handle_t get_right_button(void);

#ifdef __cplusplus
}
#endif