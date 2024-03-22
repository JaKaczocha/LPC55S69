#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S69_cm33_core0.h"
#include "fsl_debug_console.h"
#include "oled.h"
#define MENU_POS 7
volatile bool alarm=false;
char sbuff[32];
volatile uint8_t Mode=MENU_POS;
uint8_t Set=0;
const char Msg[2][10] = {
		{"[Cancel]"},
		{"[ OK ]"},
};
typedef struct {
	uint8_t cx0;
	uint8_t cy0;
	uint8_t cx1;
	uint8_t cy1;
	void *rtcs;
	uint8_t plen;
	uint16_t rtcmin;
	uint16_t rtcmax;
}set_datetime_t;
const set_datetime_t set_datetime[MENU_POS]={
		{ 0, 7, 12, 15, &RTC_dateTimeStruct.hour, 1, 0, 23},
		{18, 7, 30, 15, &RTC_dateTimeStruct.minute, 1, 0, 59},
		{36, 7, 48, 15, &RTC_dateTimeStruct.second, 1, 0, 59},
		{ 0, 23, 12, 31, &RTC_dateTimeStruct.day, 1, 1, 31},
		{18, 23, 30, 31, &RTC_dateTimeStruct.month, 1, 1, 12},
		{36, 23, 60, 31, &RTC_dateTimeStruct.year, 2, 1970, 2099},
		{ 0, 0, 0, 0, &Set, 1, 0, 1},
};
void RTC_IRQHANDLER() {
	if (RTC_GetStatusFlags(RTC) & kRTC_AlarmFlag) {
		alarm=true;
		/* Clear alarm flag */
		RTC_ClearStatusFlags(RTC, kRTC_AlarmFlag);
	}
}
void encClockwise(pint_pin_int_t pintr ,uint32_t pmatch_status) {
	if(Mode<MENU_POS) {
		if(GPIO_PinRead(BOARD_INITENCPINS_SIB_GPIO, BOARD_INITENCPINS_SIB_PORT, BOARD_INITENCPINS_SIB_PIN)) {
			if(set_datetime[Mode].plen==1) {
				if(*((uint8_t*)set_datetime[Mode].rtcs) > set_datetime[Mode].rtcmin) {
					(*((uint8_t*)set_datetime[Mode].rtcs))--;
				}
			}
			if(set_datetime[Mode].plen==2) {
				if(*((uint16_t*)set_datetime[Mode].rtcs) > set_datetime[Mode].rtcmin)
					(*((uint16_t*)set_datetime[Mode].rtcs))--;
			}
		} else {
			if(set_datetime[Mode].plen==1) {
				if(*((uint8_t*)set_datetime[Mode].rtcs) < set_datetime[Mode].rtcmax)
					(*((uint8_t*)set_datetime[Mode].rtcs))++;
			}
			if(set_datetime[Mode].plen==2) {
				if(*((uint16_t*)set_datetime[Mode].rtcs) < set_datetime[Mode].rtcmax)
					(*((uint16_t*)set_datetime[Mode].rtcs))++;
			}
		}
	}
}
void encSwitch(pint_pin_int_t pintr ,uint32_t pmatch_status) {
	Mode++;
	if(Mode>MENU_POS)
		Mode=0;
}
void Analog_Clock(uint8_t x, uint8_t y, uint8_t radius, rtc_datetime_t *datetime) {
	uint8_t radius_s=radius;
	uint8_t radius_m=radius*0.95;
	uint8_t radius_h=radius*0.5;
	uint8_t radius_p=radius-4;
	float h, m, s, p;
	s=(2*PI*datetime->second)/60.0;
	m=(2*PI*datetime->minute)/60.0;
	h=(2*PI*((datetime->hour % 12)+(datetime->minute/60.)))/12.0;
	OLED_Clear_Screen(0);
	for(int i=0; i<60;i++) {
		p=(2*PI*i)/60.0;
		if(i % 5) {
			OLED_Draw_Point(x+radius*sinf(p), y-radius*cosf(p), 1);
		} else {
			OLED_Draw_Line(x+radius_p*sinf(p), y-radius_p*cosf(p), x+radius*sinf(p), y-radius*cosf(p));
		}
	}
	OLED_Draw_Line(x,y, x+radius_s*sinf(s), y-radius_s*cosf(s));
	OLED_Draw_Line(x,y, x+radius_m*sinf(m), y-radius_m*cosf(m));
	OLED_Draw_Line(x,y, x+radius_h*sinf(h), y-radius_h*cosf(h));
}
void Digital_Clock(uint8_t x, uint8_t y, rtc_datetime_t *datetime, uint8_t mode) {
	sprintf(sbuff, "%02d:%02d.%02d", datetime->hour, datetime->minute, datetime->second);
	OLED_Puts(x+1, y+1, sbuff);
	sprintf(sbuff, "%02d-%02d-%02d", datetime->day, datetime->month, datetime->year);
	OLED_Puts(x+1, y+3, sbuff);
	if(mode<MENU_POS-1)
		OLED_Invert_Rect(x+set_datetime[mode].cx0, y+set_datetime[mode].cy0, x+set_datetime[mode].cx1,
				y+set_datetime[mode].cy1);
	if(mode==MENU_POS-1)
		OLED_Puts(x+1, y+7, (char*)Msg[Set]);
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
	/* Initialize OLED */
	OLED_Init(FLEXCOMM1_PERIPHERAL);
	while(1) {
		if(Mode==MENU_POS) {
			if(Set) {
				RTC_SetDatetime(RTC_PERIPHERAL, &RTC_dateTimeStruct);
				Set=0;
			}
			RTC_GetDatetime(RTC_PERIPHERAL, &RTC_dateTimeStruct);
		}
		Analog_Clock(96 , 32, 30 ,&RTC_dateTimeStruct);
		Digital_Clock(0 , 0, &RTC_dateTimeStruct, Mode);
		OLED_Refresh_Gram();
	}
	return 0 ;
}

