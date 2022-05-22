#include "iot_button.h"
#include "esp_log.h"

button_handle_t left_button_handle;
button_handle_t right_button_handle;

button_config_t get_gpio_btn_config(int32_t gpio_number) {
    button_config_t res = {
        .type = BUTTON_TYPE_GPIO,
        .gpio_button_config = {
            .gpio_num = gpio_number,
            .active_level = 0,
        },
    };

    return res;
}

void left_button_single_click_cb(void* arg) {
    ESP_LOGI("btn", "Left button clicked!");
}

void right_button_single_click_cb(void* arg) {
    ESP_LOGI("btn", "Right button clicked!");
}

void init_buttons(int32_t left_gpio_pin, int32_t right_gpio_pin) {
    button_config_t left_button_config = get_gpio_btn_config(left_gpio_pin);
    left_button_handle = iot_button_create(&left_button_config);
    if (NULL == left_button_handle) {
        ESP_LOGE("btn", "Left button create failed");
    } else {
        iot_button_register_cb(left_button_handle, BUTTON_SINGLE_CLICK, left_button_single_click_cb);
    }

    button_config_t right_button_config = get_gpio_btn_config(right_gpio_pin);
    right_button_handle = iot_button_create(&right_button_config);
    if (NULL == right_button_handle) {
        ESP_LOGE("btn", "Right button create failed");
    } else {
        iot_button_register_cb(right_button_handle, BUTTON_SINGLE_CLICK, right_button_single_click_cb);
    }
}

button_handle_t get_left_button(void) {
    return left_button_handle;
}

button_handle_t get_right_button(void) {
    return right_button_handle;
}