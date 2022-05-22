#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t init_counter_task(void);
TaskHandle_t get_counter_task(void);

#ifdef __cplusplus
}
#endif