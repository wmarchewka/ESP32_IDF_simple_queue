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
#include "string.h"
#include "nvs_flash.h"
#include <sys/param.h>

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

#include "udp_msg.h"
#include "udp_rtn_msg.h"

char rx_buffer[128];
char addr_str[128];

int addr_family = AF_INET;
int ip_protocol = 0;
struct sockaddr_in6 dest_addr;
int sock;

struct sockaddr_storage source_addr; // Large enough for both IPv4 or IPv6
socklen_t socklen = sizeof(source_addr);

udp_msg message;
udp_rtn_msg return_message;

// Get queue to publish our data to.
QueueHandle_t xUdpQueue;
QueueHandle_t xUdpReturnQueue;

#define PORT 1234
#define CONFIG_EXAMPLE_IPV4

/* Handle for our HTTPD instance */
static httpd_handle_t server_handle;

// Time to wait between taking voltage measurements
static const TickType_t udp_period = pdMS_TO_TICKS(1000);

/* Flags used in event group */
#define WIFI_CONNECTED_BIT BIT0

typedef struct udp_task_parameters
{
    xQueueHandle xUdpQueue;
} udp_task_parameters;

void wait_for_wifi_ready();
void udp_server_task(void *pvParameters);
void send_data();

#endif