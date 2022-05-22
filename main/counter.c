#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

TaskHandle_t counter_task_handler;

void counter_task_fn(void* pvParam) {
    int8_t counter = 0;

    for (;;) {
        if (counter >= INT8_MAX) {
            counter = -1;
        }
        ESP_LOGI("counter", "value = %d", counter++);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

TaskHandle_t init_counter_task(void) {
    if (xTaskCreate(counter_task_fn, "counter", 1024 * 2, NULL, 1, &counter_task_handler) != pdPASS) {
        ESP_LOGE("task", "Error while creating counter task");
    }

    return counter_task_handler;
}

TaskHandle_t get_counter_task(void) {
    return counter_task_handler;
}