/*
 */
#include "http_file_server.h"

static const char *TAG = "http file server";

void http_file_server_task(void *pvParameters)
{
  /* Mailbox (queue of 1 item) of power_msg */
  QueueHandle_t xPowerQueue;
  power_msg message;

  // Retrieve task parameters
  http_file_server_task_parameters *pTaskParameters = (http_file_server_task_parameters *)pvParameters;
  if (NULL == pTaskParameters ||
      NULL == pTaskParameters->xPowerQueue)
  {
    ESP_LOGE(TAG, "Task parameters were missing, exiting.");
    vTaskDelete(NULL); // Delete self.
  }
  xPowerQueue = pTaskParameters->xPowerQueue;

  while (true)
  {
    // ESP_ERROR_CHECK(send_power_update(xPowerQueue));
    ESP_LOGI(TAG, "File server task");
    if (pdTRUE == xQueuePeek(xPowerQueue, &message, portMAX_DELAY))
    {
      ESP_LOGI(TAG, "Message %lf", message.voltage);
      vTaskDelay(powerUpdatePeriod);
      ESP_LOGI(TAG, "Got data!!!");
    }
  }
}
