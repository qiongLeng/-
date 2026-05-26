#ifndef __HEAD_H
#define __HEAD_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <ctype.h>

#include "main.h"
#include "gpio.h"
#include "tim.h"
#include "usart.h"
#include "mydelay.h"

#include "OLED.h"
#include "key.h"
#include "DHT11.h"
#include "clear_pack.h"

#include "cJSON.h"
#include "Common.h"
#include "esp8266.h"
#include "MqttKit.h"
#include "onenet.h"

#define USART_DEBUG		 &huart1

extern uint8_t max_hum,max_temp;
extern oled_show_t show;
extern uint8_t Alarm_flag;

extern unsigned char esp8266_buf[512];
extern unsigned short esp8266_cnt,esp8266_cntPre;

#endif
