/*
*/
#ifndef INC_HTTP_FILE_SERVER_H
#define INC_HTTP_FILE_SERVER_H
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "esp_event.h"
#include "esp_http_server.h"
#include "esp_log.h"
#include "esp_spiffs.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "cJSON.h"
#include "power_msg.h"



/* Time period between sending power updates */
static const TickType_t powerUpdatePeriod = pdMS_TO_TICKS(1000);

/*
 * @brief Parameter for http_file_server_task
 */
typedef struct http_file_server_task_parameters
{
  xQueueHandle xPowerQueue;
} http_file_server_task_parameters;

/*
 * @brief FreeRTOS task to launch web server for Sawppy web control panel over WiFI
 * @param pvParameters QueueHandle_t mailbox of joy_msg
 */
void http_file_server_task(void *pvParameters);

#endif // #ifndef INC_HTTP_FILE_SERVER_H
