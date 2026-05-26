#ifndef __CLEAR_PACK_H
#define __CLEAR_PACK_H

typedef enum
{
	data_show_oled = 0,
	limit_show_hum,
	limit_show_temp,
}oled_show_t;


void change(void);
void All_Init(void);
void oled_show(void);
void LED_OFF(void);
void LED_ON(void);

#endif
