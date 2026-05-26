#include "head.h"

uint8_t max_hum=50;
uint8_t max_temp=50;
oled_show_t show;
DHT11_Data_TypeDef DHT11_data;
char PUBLIS_BUF[256];

const char devPubTopic[] = "$sys/xX6gucP6ZM/Test1/thing/property/post";
const char *devSubTopic[] = {"$sys/xX6gucP6ZM/Test1/thing/property/set"};
unsigned char *dataPtr = NULL;
uint16_t TimeCount = 0;
uint8_t Alarm_flag = 0;

void JsonValue(void)
{
	uint8 Temp = DHT11_data.temp_int;
	uint8 Hum = DHT11_data.humi_int;
	
	memset(PUBLIS_BUF,0,sizeof(PUBLIS_BUF));
	sprintf(PUBLIS_BUF,"{\"id\":\"123\",\"params\":{\"temp\":{\"value\":%d},\"humidity\":{\"value\":%d} }}",
					Temp,Hum);	
}

void All_Init(void)
{
	OLED_Init();
	OLED_Clear();
	OLED_Clear();
	OLED_Printf(0,0,OLED_8X16,"WiFi start");
	OLED_Update();
	ESP8266_Init();
	while(OneNet_DevLink())
	{
		HAL_Delay(500);
	}
	OLED_Clear();
	OLED_Printf(0,0,OLED_8X16,"WiFi success");
	OLED_Update();
	HAL_Delay(3000);
	
	OneNet_Subscribe(devSubTopic,1);
}

void change(void)
{
	DHT11_ReadData(&DHT11_data);
	if(Alarm_flag)
	{
		if(DHT11_data.humi_int>max_hum || DHT11_data.temp_int>max_temp)
		{
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
		}
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
	}
	if(++TimeCount >= 100)
	{
		JsonValue();
		OneNet_Publish(devPubTopic, PUBLIS_BUF);
		ESP8266_Clear();
		TimeCount = 0;
	}
	dataPtr = ESP8266_GetIPD(2);
	if(dataPtr!=NULL)
	{
		OneNet_RevPro(dataPtr); 
	}
}

void LED_ON(void)
{
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
}
void LED_OFF(void)
{
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
}

void data_show(void)
{
	OLED_Clear();
	OLED_Printf(0,0,OLED_8X16,"temp=%d.%d",DHT11_data.temp_int,DHT11_data.temp_dec);
	OLED_Printf(0,16,OLED_8X16,"humi=%d",DHT11_data.humi_int,DHT11_data.humi_dec);
	OLED_Update();
}

void limit_hum_show(void)
{
	OLED_Clear();
	OLED_Printf(0,0,OLED_8X16,"max_hum=%d",max_hum);
	OLED_Update();
}

void limit_temp_show(void)
{
	OLED_Clear();
	OLED_Printf(0,0,OLED_8X16,"max_temp=%d",max_temp);
	OLED_Update();
}

void oled_show(void)
{
	switch(show)
	{
		case data_show_oled:
			data_show();
			break;
		case limit_show_hum:
			limit_hum_show();
			break;
		case limit_show_temp:
			limit_temp_show();
			break;
	}
}
