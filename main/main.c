#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include "wifi.h"
#include "counter.h"
#include "ttgo_buttons.h"
#include "display.h"

#define GPIO_LEFT_BUTTON 0
#define GPIO_RIGHT_BUTTON 35

TaskHandle_t counter_task;
TaskHandle_t wifi_task;
TaskHandle_t display_task;


void app_main(void)
{
    init_buttons(GPIO_LEFT_BUTTON, GPIO_RIGHT_BUTTON);
    printf("Hello, World");

    counter_task = init_counter_task();
    wifi_task = init_wifi_task();
    display_task = init_display_task();
}