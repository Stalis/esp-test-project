#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "st7789.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_system.h"
#include "font.h"

#define TAG "display"

TaskHandle_t display_task_handle;
TFT_t display_device;

void print_letter(TFT_t* dev, uint16_t x0, uint16_t y0, const uint16_t pixels[], uint16_t pixels_count, uint16_t color) {
    for (int i = 0; i < pixels_count; i++) {
        lcdDrawPixel(dev, x0 + pixels[2 * i], y0 + pixels[(2 * i) + 1], color);
    }
}

void display_task_fn(void* pvParam) {
	spi_master_init(&display_device, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO, CONFIG_BL_GPIO);
	lcdInit(&display_device, CONFIG_WIDTH, CONFIG_HEIGHT, CONFIG_OFFSETX, CONFIG_OFFSETY);

    lcdFillScreen(&display_device, RED);
    lcdDrawArrow(&display_device, (uint16_t)(135 / 2), 0, (uint16_t)(135 / 2), 240, 15, BLUE);

    print_letter(&display_device, 50, 50, letterXY_B, letterXY_B_len, GRAY);
    print_letter(&display_device, 60, 50, letterXY_A, letterXY_A_len, GRAY);
    print_letter(&display_device, 70, 50, letterXY_x, letterXY_x_len, GRAY);
    
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

