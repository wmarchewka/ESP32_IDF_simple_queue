/*
 */
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
//#include "softap_start.h"
#include "volt_adc.h"
#include "new_udp_server.h"
#include "http_file_server.h"
#include "station_start.h"

void app_main()
{

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());

    // obtain handle to the queue we are going to use
    QueueHandle_t xPowerQueue = xQueueCreate(1, sizeof(power_msg));
    QueueHandle_t xUdpQueue = xQueueCreate(1, sizeof(udp_msg));

    /// @brief create task parameters to send to the task in this case just a queue
    http_file_server_task_parameters http_params = {
        .xPowerQueue = xPowerQueue,
    };

    ESP_ERROR_CHECK(esp_event_loop_create_default());

    udp_task_parameters udp_parameters = {
        .xUdpQueue = xUdpQueue,
    };

    // checl to see if the queue was actually created
    if (NULL == xPowerQueue)
    {
        printf("ERROR: Queue allocation failed.");
    }
    else
    {
        // create the task by naming the function, a name, a stack size?, parameters needed, and a priority,
       
        // xTaskCreate(softap_start_task, "softap_start_task", 1024 * 4, NULL, 20, NULL);
        xTaskCreate(station_start_task, "station_start_task", 1024 * 4, NULL, 20, NULL);
        // xTaskCreate(http_file_server_task, "http_file_server_task", 1024 * 4, &http_params, 19, NULL);
        // xTaskCreate(volt_adc_task, "volt_adc_task", 2048, xPowerQueue, 10, NULL);
        //xTaskCreate(udp_task, "udp task", 1024 * 8, &udp_parameters, 8, NULL);
        xTaskCreate(udp_server_task, "udp_server", 4096, (void *)AF_INET, 5, NULL);
    }
}
