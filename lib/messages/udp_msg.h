/*
 */
#ifndef INC_UDP_MSG_H
#define INC_UDP_MSG_H

#include "freertos/FreeRTOS.h"

//#define readBufSize 1024 * 16

typedef struct udp_msg
{
  TickType_t timeStamp;
  int value;
  char rx_buffer[128];
  char addr_str[128];
} udp_msg;

#endif // #ifndef INC_POWER_MSG_H
