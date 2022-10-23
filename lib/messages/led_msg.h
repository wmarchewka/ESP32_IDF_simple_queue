#ifndef INC_LED_MSG_H
#define INC_LED_MSG_H

#include "freertos/FreeRTOS.h"

typedef struct led_msg
{
    TickType_t timeStamp;
    int state;
} led_msg;

#endif // #ifndef LED_MSG_H