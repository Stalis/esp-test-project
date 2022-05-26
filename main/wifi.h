#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#ifdef __cplusplus
extern "C" {
#endif

TaskHandle_t init_wifi_task(void);
TaskHandle_t get_wifi_task(void);

#ifdef __cplusplus
}
#endif