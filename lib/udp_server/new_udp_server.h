#ifndef INC_UDPNEWSERVER_H
#define INC_UDPNEWSERVER_H

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_http_server.h"

#include "nvs_flash.h"
#include <string.h>
#include <sys/param.h>

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

#include "udp_msg.h"

#define PORT 4444
#define CONFIG_EXAMPLE_IPV4

// Time to wait between taking voltage measurements
static const TickType_t udp_period = pdMS_TO_TICKS(1000);

/* Flags used in event group */
#define WIFI_CONNECTED_BIT BIT0

typedef struct udp_task_parameters
{
    xQueueHandle xUdpQueue;
} udp_task_parameters;

void udp_server_task(void *pvParameters);

#endif