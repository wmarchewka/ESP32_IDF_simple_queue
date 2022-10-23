#ifndef INC_UDPSERVER_H
#define INC_UDPSERVER_H


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
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

static const char *TAG = "udp_server";

/* Flags used in event group */
#define WIFI_CONNECTED_BIT BIT0

typedef struct udp_task_parameters
{
    xQueueHandle xUdpQueue;
} udp_task_parameters;

static void udp_server_task(void *pvParameters);

#endif