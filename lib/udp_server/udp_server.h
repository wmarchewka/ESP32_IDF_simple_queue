/*
 */
#ifndef INC_UDP_H
#define INC_UDP_H

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"
#include "freertos/task.h"

#include "esp_event.h"
#include "esp_http_server.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_err.h"

#include "udp_msg.h"

// Time to wait between taking voltage measurements
static const TickType_t udp_period = pdMS_TO_TICKS(1000);

static const char *TAG = "udp";

/* Flags used in event group */
#define WIFI_CONNECTED_BIT BIT0

void udp_task(void *pvParameter);

typedef struct udp_task_parameters
{
    xQueueHandle xUdpQueue;
} udp_task_parameters;

#endif //#ifndef INC_VOLT_ADC_H