/*
 * This file is part of the EasyLogger Library.
 *
 * Copyright (c) 2015, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: Portable interface for each platform.
 * Created on: 2015-04-28
 */
 
#include <elog.h>

/* FreeRTOS API */
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

static void async_output(void *arg);

SemaphoreHandle_t xSemaphore_port = NULL;
TaskHandle_t xHandle_port = NULL;

/**
 * EasyLogger port initialize
 *
 * @return result
 */
ElogErrCode elog_port_init(void) {
    ElogErrCode result = ELOG_NO_ERR;

    /* add your code here */
#ifdef ELOG_ASYNC_OUTPUT_ENABLE
    xSemaphore_port = xSemaphoreCreateCounting(1, 0);
    if (xSemaphore_port == NULL) {
        return ELOG_SEM_CREATE_FAIL;
    }

    BaseType_t ret = xTaskCreate(async_output, "log_output", 1024, NULL, 6, &xHandle_port);
    if (ret != pdPASS) {
        return ELOG_TASK_CREATE_FAIL;
    }
#endif
    return result;
}

/**
 * output log port interface
 *
 * @param log output of log
 * @param size log size
 */
void elog_port_output(const char *log, size_t size) {
    
    /* add your code here */
    printf("%.*s", size, log);
}

/**
 * output lock
 */
void elog_port_output_lock(void) {
    
    /* add your code here */
    xSemaphoreTake(xSemaphore_port,0xFFFFFFFF);
}

/**
 * output unlock
 */
void elog_port_output_unlock(void) {
    
    /* add your code here */
    xSemaphoreGive(xSemaphore_port);
}

/**
 * get current time interface
 *
 * @return current time
 */
const char *elog_port_get_time(void) {
    
    /* add your code here */
    static char cur_system_time[16] = {0};
    snprintf(cur_system_time, 16, "tick:%010d", xTaskGetTickCount());
    return cur_system_time;
}

/**
 * get current process name interface
 *
 * @return current process name
 */
const char *elog_port_get_p_info(void) {
    
    /* add your code here */
    return "";
}

/**
 * get current thread name interface
 *
 * @return current thread name
 */
const char *elog_port_get_t_info(void) {
    
    /* add your code here */
    return "";
}

#ifdef ELOG_ASYNC_OUTPUT_ENABLE
void elog_async_output_notice(void) {
    xSemaphoreGive(xSemaphore_port);
}

static void async_output(void *arg) {
    size_t get_log_size = 0;
    static char poll_get_buf[ELOG_LINE_BUF_SIZE - 4];

    while (true) {
        /* waiting log */
        xSemaphoreTake(xSemaphore_port, 0xFFFFFFFF);
        /* polling gets and outputs the log */
        while (true) {
#ifdef ELOG_ASYNC_LINE_OUTPUT
            get_log_size = elog_async_get_line_log(poll_get_buf, sizeof(poll_get_buf));
#else
            get_log_size = elog_async_get_log(poll_get_buf, sizeof(poll_get_buf));
#endif

            if (get_log_size) {
                elog_port_output(poll_get_buf, get_log_size);
            } else {
                break;
            }
        }
    }
}
#endif