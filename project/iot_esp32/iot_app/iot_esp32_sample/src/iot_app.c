/**
 * @file iot_app.c
 * @author 
 * @brief 
 * @version 0.1
 * @date 2020-04-04
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <stdio.h>

#include "elog.h"
#include "esp_spi_flash.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

/**
 * @brief 
 * 
 */
void iot_user_main(void)
{
    printf("iot_esp %s_V%s\r\n",APP_BIN_NAME, USER_SW_VER);
    printf("iot_esp compiled at %s %s\r\n", __DATE__, __TIME__);
}
