#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "st7789.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_system.h"

#define TAG "display"

TaskHandle_t display_task_handle;
TFT_t display_device;

void display_task_fn(void* pvParam) {
	spi_master_init(&display_device, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO, CONFIG_BL_GPIO);
	lcdInit(&display_device, CONFIG_WIDTH, CONFIG_HEIGHT, CONFIG_OFFSETX, CONFIG_OFFSETY);

    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

TaskHandle_t init_display_task(void) {
    if (xTaskCreate(display_task_fn, "display", 1024 * 4, NULL, 1, &display_task_handle) != pdPASS) {
        ESP_LOGE(TAG, "Error while creating wifi task");
    }

    return display_task_handle;
}

TaskHandle_t get_display_task(void) {
    return display_task_handle;
}

