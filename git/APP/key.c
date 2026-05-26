#include "head.h"

uint8_t key1_staty;
uint8_t key2_staty;
uint8_t key3_staty;
uint8_t key1_last_staty;
uint8_t key2_last_staty;
uint8_t key3_last_staty;
uint32_t key_time;

void key_staty(void)
{
	if(HAL_GetTick()-key_time > 20)
	{
		key1_staty = HAL_GPIO_ReadPin(key1_GPIO_Port,key1_Pin);
		key2_staty = HAL_GPIO_ReadPin(key2_GPIO_Port,key2_Pin);
		key3_staty = HAL_GPIO_ReadPin(key3_GPIO_Port,key3_Pin);
		key_time = HAL_GetTick();
		if(!key1_staty&key1_last_staty)
		{
			show = (oled_show_t)((show + 1)%3);
		}
		if(!key2_staty&key2_last_staty)
		{
			if(show == limit_show_hum)
			{
				max_hum+=1;
				if(max_hum>100)
				{
					max_hum=100;
				}
			}
			if(show == limit_show_temp)
			{
				max_temp+=1;
				if(max_temp>100)
				{
					max_temp=100;
				}
			}
		}
		if(!key3_staty&key3_last_staty)
		{
			if(show == limit_show_hum)
			{
				max_hum-=1;
				if(max_hum<10)
				{
					max_hum=10;
				}
			}
			if(show == limit_show_temp)
			{
				max_temp+=1;
				if(max_temp>100)
				{
					max_temp=100;
				}
			}
		}
		key1_last_staty = key1_staty;
		key2_last_staty = key2_staty;
		key3_last_staty = key3_staty;
	}
}
