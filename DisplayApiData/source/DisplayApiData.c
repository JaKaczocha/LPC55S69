#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S69_cm33_core0.h"
#include "fsl_debug_console.h"
#include "wlan_mwm.h"
#include "cJSON.h"
#include "lcd.h"
#include "back.h"
#include "wicons.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*-----------------------------------------------------------------------------
AP_SECURITY_MODE:
0 - Open
1 - WEP (Open mode)
2 - WEP (Shared mode)
3 - WPA-PSK
4 - WPA2-PSK
9 - WPA3-SAE
 ----------------------------------------------------------------------------*/
#define AP_SSID "Orange_Sw"
#define AP_PASSPHRASE ""
#define AP_SECURITY_MODE "4"
/*---------------------------------------------------------------------------*/
#define STR_BUFFER_LEN 128
#define CDE_BUFFER_LEN 64

/*******************************************************************************
 * Variables
 ******************************************************************************/
char g_bufferRX[RXD_BUFFER_LEN]={0}; // HTTP RX Buffer
char g_bufferTX[TXD_BUFFER_LEN]={0}; // HTTP TX Buffer
char g_sbuffer[STR_BUFFER_LEN]; // Text Buffer
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#ifndef MSEC_TO_TICK
#define MSEC_TO_TICK(msec) ((uint32_t)(msec) * (uint32_t)configTICK_RATE_HZ / 1000uL)
#endif
/*******************************************************************************
 * Code
 ******************************************************************************/
void main_task(void *pvParameters) {
	int ret;
	/* Initialize Serial MWM */
	PRINTF("Initializing...\r\n");
	ret = mwm_init();
	if (ret < 0) {
		PRINTF("Could not initialize Serial MWM, error: %d\r\n", ret);
		while (1)
			;
	}
	ret = wlan_get_state();
	if (ret == MWM_INITIALIZED) {
		PRINTF("Starting WLAN...\r\n");
		ret = mwm_wlan_start();
		if (ret < 0) {
			PRINTF("Could not start WLAN subsystem, error: %d\r\n", ret);
			while (1)
				;
		}
	}
	wlan_config(AP_SSID, AP_PASSPHRASE , AP_SECURITY_MODE);
	while(wlan_get_state()!= MWM_CONNECTED);
	wlan_state();
	LCD_Clear(0x0841);
	sprintf(g_sbuffer, "WiFi: %s", AP_SSID);
	LCD_Puts(10, 30, g_sbuffer, 0xFF00);
	LCD_GramRefresh();
	vTaskDelay(MSEC_TO_TICK(1000));
	char codebuffer[CDE_BUFFER_LEN]={0};
	char *contentData=NULL;
	int recvLen=0;
	int contLen=0;
	while (1) {
		http_GET("api.openweathermap.org/data/2.5/weather?q=Tarnow,pl&APPID=3ce14de5d95e35375360a2c19bea0404", g_bufferRX);
		contentData=g_bufferRX;
		recvLen=strlen(g_bufferRX);
		http_head_parser(g_bufferRX, codebuffer, "Content-Length:");
		contLen=atoi(codebuffer);
		contentData=g_bufferRX+(recvLen-contLen);
		http_head_parser(g_bufferRX, codebuffer, "Date: ");
		codebuffer[22]='\0';
		cJSON *root = cJSON_Parse(contentData);
		cJSON *windMain;
		cJSON *valuesMain;
		cJSON *weatherMain;
		cJSON *weatherItem;
		char *icon;
		char *desc;
		char *city;
		int temp;
		int humidity;
		int pressure;
		double windSpeed;
		int windDeg;
		if(root==NULL){
			PRINTF("JSON PARSING FAILURE\r\n");
		} else {
			weatherMain = cJSON_GetObjectItem(root, "weather");
			int n = cJSON_GetArraySize(weatherMain);
			for (int i = 0; i < n; i++) {
				weatherItem = cJSON_GetArrayItem(weatherMain, i);
				icon = cJSON_GetObjectItem(weatherItem, "icon")->valuestring;
				desc = cJSON_GetObjectItem(weatherItem, "description")->valuestring;
			}
			valuesMain = cJSON_GetObjectItem(root, "main");
			temp = cJSON_GetObjectItem(valuesMain, "temp")->valueint-273;
			humidity = cJSON_GetObjectItem(valuesMain, "humidity")->valueint;
			pressure = cJSON_GetObjectItem(valuesMain, "pressure")->valueint;
			windMain = cJSON_GetObjectItem(root, "wind");
			windSpeed = cJSON_GetObjectItem(windMain, "speed")->valuedouble;
			windDeg = cJSON_GetObjectItem(windMain, "deg")->valueint;
			city = cJSON_GetObjectItem(root, "name")->valuestring;
			LCD_Set_Bitmap((uint16_t*)back_160x128);
			LCD_Puts(10, 60, codebuffer, 0x0FFF);
			if(!strcmp(icon, "01d"))
				LCD_Set_Icon(96, 0, 64, 48, (uint16_t*)wi_1d_64x48);
			else if(!strcmp(icon, "02d"))
				LCD_Set_Icon(96, 0, 64, 48, (uint16_t*)wi_2d_64x48);
			else if(!strcmp(icon, "03d"))
				LCD_Set_Icon(96, 0, 64, 48, (uint16_t*)wi_3d_64x48);
			else if(!strcmp(icon, "04d"))
				LCD_Set_Icon(96, 0, 64, 48, (uint16_t*)wi_4_64x48);
			else if(!strcmp(icon, "09d"))
				LCD_Set_Icon(96, 0, 64, 48, (uint16_t*)wi_9_64x48);
			else if(!strcmp(icon, "10d"))
				LCD_Set_Icon(96, 0, 64, 48, (uint16_t*)wi_10d_64x48);
			else if(!strcmp(icon, "11d"))
				LCD_Set_Icon(96, 0, 64, 48, (uint16_t*)wi_11_64x48);
			else if(!strcmp(icon, "13d"))
				LCD_Set_Icon(96, 0, 64, 48, (uint16_t*)wi_13_64x48);
			else if(!strcmp(icon, "50d"))
				LCD_Set_Icon(96, 0, 64, 48, (uint16_t*)wi_50_64x48);
			else if(!strcmp(icon, "01n"))
				LCD_Set_Icon(96, 0, 64, 48, (uint16_t*)wi_1n_64x48);
			else if(!strcmp(icon, "02n"))
				LCD_Set_Icon(96, 0, 64, 48, (uint16_t*)wi_2n_64x48);
			else if(!strcmp(icon, "03n"))
				LCD_Set_Icon(96, 0, 64, 48, (uint16_t*)wi_3n_64x48);
			else if(!strcmp(icon, "04n"))
				LCD_Set_Icon(96, 0, 64, 48, (uint16_t*)wi_4_64x48);
			else if(!strcmp(icon, "09n"))
				LCD_Set_Icon(96, 0, 64, 48, (uint16_t*)wi_9_64x48);
			else if(!strcmp(icon, "10n"))
				LCD_Set_Icon(96, 0, 64, 48, (uint16_t*)wi_10n_64x48);
			else if(!strcmp(icon, "11n"))
				LCD_Set_Icon(96, 0, 64, 48, (uint16_t*)wi_11_64x48);
			else if(!strcmp(icon, "13n"))
				LCD_Set_Icon(96, 0, 64, 48, (uint16_t*)wi_13_64x48);
			else if(!strcmp(icon, "50n"))
				LCD_Set_Icon(96, 0, 64, 48, (uint16_t*)wi_50_64x48);
			LCD_Puts(10, 1, city, 0xFFFF);
			LCD_7seg( 0, 10, temp, 3, 0xFFFF);
			LCD_Puts(10, 43, desc, 0xFFFF);
			sprintf(g_sbuffer,"Humid: %d %%", humidity);
			LCD_Puts(10, 90, g_sbuffer, 0xFFFF);
			sprintf(g_sbuffer,"Press: %d hPa", pressure);
			LCD_Puts(10, 100, g_sbuffer, 0xFFFF);
			sprintf(g_sbuffer,"Wind: %.2f m/s (%d)", windSpeed, windDeg);
			LCD_Puts(10, 110, g_sbuffer, 0xFFFF);
			LCD_GramRefresh();
			cJSON_Delete(root);
		}
		vTaskDelay(MSEC_TO_TICK(5000));
	}
}
/*
 * @brief Application entry point.
 */
int main(void) {
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
#endif
	LCD_Init(FLEXCOMM3_PERIPHERAL);
	LCD_Clear(0x0841);
	LCD_Puts(10, 30, "Connecting to WiFi...", 0xFF00);
	LCD_GramRefresh();
	if (xTaskCreate(main_task, "main_task", 350, NULL, MAIN_TASK_PRIORITY, NULL) != pdPASS) {
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}
	vTaskStartScheduler();
	while(1) {
	}
	return 0 ;
}
