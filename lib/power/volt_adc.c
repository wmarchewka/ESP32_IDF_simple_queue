/*
 */
#include "volt_adc.h"

static const char *TAG = "volt_adc";

void volt_adc_task(void *pvParameter)
{
  power_msg message;

  // Get queue to publish our data to.
  QueueHandle_t xPowerQueue;
  if (NULL == pvParameter)
  {
    ESP_LOGE(TAG, "Task parameter is null. Expected handle to power message queue.");
    vTaskDelete(NULL); // Delete self.
  }
  xPowerQueue = (QueueHandle_t)pvParameter;

  // Continuously read voltage and publish to queue
  while (true)
  {
    // ESP_LOGI(TAG, "Sending data to Power Queue");
    // message.voltage = 1;
    // message.timeStamp = xTaskGetTickCount();
    // xQueueOverwrite(xPowerQueue, &message);
    vTaskDelay(voltage_period);
  }
}
