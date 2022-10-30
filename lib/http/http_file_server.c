/*
 */
#include "http_file_server.h"

static const char *TAG = "http file server";

void http_file_server_task(void *pvParameters)
{
  /* Mailbox (queue of 1 item) of power_msg */
  QueueHandle_t xPowerQueue;
  QueueHandle_t xUdpQueue;

  power_msg pwrMessage;
  udp_msg udpMessage;

  // Retrieve task parameters
  http_file_server_task_parameters *pTaskParameters = (http_file_server_task_parameters *)pvParameters;
  if (NULL == pTaskParameters || NULL == pTaskParameters->xPowerQueue || NULL == pTaskParameters->xPowerQueue)
  {
    ESP_LOGE(TAG, "Task parameters were missing, exiting.");
    vTaskDelete(NULL); // Delete self.
  }
  xPowerQueue = pTaskParameters->xPowerQueue;
  xUdpQueue = pTaskParameters->xUdpQueue;

  while (true)
    
  {
    // ESP_LOGI(TAG, "Waiting for data in Queues....");
    
    // if (pdTRUE == xQueuePeek(xPowerQueue, &pwrMessage, timeoutDelay))
    // {
    //   ESP_LOGI(TAG, "Received %lf from PowerQueu at %i", pwrMessage.voltage, pwrMessage.timeStamp);
    // }

    // if (xQueueReceive(xPowerQueue, &(pwrMessage), (TickType_t)10))
    // {
    //   ESP_LOGI(TAG, "Received %lf from PowerQueu at %i", pwrMessage.voltage, pwrMessage.timeStamp);
    // }

    // if (pdTRUE == xQueuePeek(xUdpQueue, &udpMessage, timeoutDelay))
    // {
    //   ESP_LOGI(TAG, "Received %s from %s at %i", udpMessage.rx_buffer, udpMessage.addr_str, udpMessage.timeStamp);
    // }

    if (xQueueReceive(xUdpQueue, &(udpMessage), portMAX_DELAY))
    {
      ESP_LOGI(TAG, "Received %s from %s at %i", udpMessage.rx_buffer, udpMessage.addr_str, udpMessage.timeStamp);
    }
    vTaskDelay(powerUpdatePeriod);
  }
}