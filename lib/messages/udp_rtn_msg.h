/*
 */
#ifndef INC_UDP_RTN_MSG_H
#define INC_UDP_RTN_MSG_H

#include "freertos/FreeRTOS.h"

//#define readBufSize 1024 * 16

typedef struct udp_rtn_msg
{
    TickType_t timeStamp;
    int value;
    char rx_buffer[128];
    char addr_str[128];
} udp_rtn_msg;

#endif // #ifndef INC_POWER_MSG_H
