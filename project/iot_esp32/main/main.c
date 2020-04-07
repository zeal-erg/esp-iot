/**
 * @file main.c
 * @author 
 * @brief 
 * @version 0.1
 * @date 2020-04-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <stdio.h>

#include "esp_spi_flash.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include "elog.h"

#include "esp_log.h"

/**
 * @brief iot_app_init_thread
 * 
 * @param param 
 */
static void iot_app_init_thread(void *param)
{
    extern void iot_user_main(void); 
    iot_user_main();

    /* Kill init thread after all init tasks done */
    vTaskDelete(NULL);
}

/**
 * @brief iot_app_init_entry
 * 
 */
void iot_app_init_entry(void)
{
    if(xTaskCreate(iot_app_init_thread,"iot_app_init", 4096, NULL, tskIDLE_PRIORITY + 3, NULL) != pdPASS)
        printf("\n\r%s xTaskCreate(iot_app_init_thread) failed", __FUNCTION__);
}

/**
 * @brief elog_user_assert_hook
 * 
 * @param ex 
 * @param func 
 * @param line 
 */
static void elog_user_assert_hook(const char* ex, const char* func, size_t line) {
#ifdef ELOG_ASYNC_OUTPUT_ENABLE
    /* disable async output */
    elog_async_enabled(false);
#endif

    /* disable logger output lock */
    elog_output_lock_enabled(false);
    /* disable flash plugin lock */
    // elog_flash_lock_enabled(false);
    /* output logger assert information */
    elog_a("elog", "(%s) has assert failed at %s:%ld.\n", ex, func, line);
    /* write all buffered log to flash */
    // elog_flash_flush();
    while (1);
}

/**
 * @brief 
 * 
 */
void app_main(void) {
    #if 1
    /* easylogger init */
    if (elog_init() == ELOG_NO_ERR) {
        /* set enabled format */
        elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL & ~ELOG_FMT_P_INFO);
        elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
        elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
        elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
        elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL & ~(ELOG_FMT_FUNC | ELOG_FMT_P_INFO));
        elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL & ~(ELOG_FMT_FUNC | ELOG_FMT_P_INFO));
        /* set EasyLogger assert hook */
        elog_assert_set_hook(elog_user_assert_hook);
        /* initialize EasyLogger Flash plugin */
        // elog_flash_init();
        /* start EasyLogger */
        elog_start();
    }
    #endif
    printf("Hello world!\n");

    /* Print chip information */
    esp_chip_info_t chip_info;
    
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU cores, WiFi%s%s, ",
           CONFIG_IDF_TARGET,
           chip_info.cores,
           (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Free heap: %d\n", esp_get_free_heap_size());

    ESP_LOGE("iot-esp", "iot_app_init_entry");
    iot_app_init_entry();

    // printf("Restarting now.\n");
    // fflush(stdout);
    //esp_restart();
}
