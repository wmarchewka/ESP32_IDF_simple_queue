/*
 */
#include "udp_server.h"

/* Handle for our HTTPD instance */
static httpd_handle_t server_handle;

/* Waiting for certain WiFi events before continuing */
static EventGroupHandle_t s_wifi_event_group;

static void wifi_connected_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);
void wait_for_wifi_ready();

void udp_task(void *pvParameter)
{
    udp_msg message;

    // Get queue to publish our data to.
    QueueHandle_t xUdpQueue;

    udp_task_parameters *pTaskParameters = (udp_task_parameters *)pvParameter;
    if (NULL == pTaskParameters ||
        NULL == pTaskParameters->xUdpQueue)
    {
        ESP_LOGE(TAG, "UDP Task parameters were missing, exiting.");
        vTaskDelete(NULL); // Delete self.
    }

    xUdpQueue = pTaskParameters->xUdpQueue;

    wait_for_wifi_ready();

    // Continuously read udp and publish to queue
    while (true)
    {
        ESP_LOGI(TAG, "UDP Sending to Queue");
        message.value = 44;
        message.timeStamp = xTaskGetTickCount();
        xQueueOverwrite(xUdpQueue, &message);
        vTaskDelay(udp_period);
    }
}

/*
 * @brief When WiFi is connected, sets event group bits to unblock code waiting for WiFi.
 */
static void wifi_connected_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        ESP_LOGI(TAG, "Received IP address in station mode");
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STACONNECTED)
    {
        // Unsure if WIFI_EVENT_AP_STACONNECTED is the best event to use
        ESP_LOGI(TAG, "Client connected in access point mode");
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

void wait_for_wifi_ready()
{
    // Used by WiFi event handler to signal we can continue
    s_wifi_event_group = xEventGroupCreate();

    // Register for WiFi event
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP, &wifi_connected_handler, NULL, &instance_got_ip));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        WIFI_EVENT_AP_STACONNECTED, &wifi_connected_handler, NULL, &instance_got_ip));

    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group, WIFI_CONNECTED_BIT, pdFALSE, pdFALSE, portMAX_DELAY);
    assert(bits == WIFI_CONNECTED_BIT); // We only have one bit today.

    // Once we're connected to WiFi, no longer need to listen to WiFi event
    ESP_ERROR_CHECK(esp_event_handler_instance_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, instance_got_ip));
    ESP_ERROR_CHECK(esp_event_handler_instance_unregister(WIFI_EVENT, WIFI_EVENT_AP_STACONNECTED, instance_got_ip));
    vEventGroupDelete(s_wifi_event_group);
}