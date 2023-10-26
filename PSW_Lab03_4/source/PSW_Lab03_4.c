#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S69_cm33_core0.h"
#include "fsl_debug_console.h"
#include "oled.h"

char sbuff[32];

volatile uint8_t counter=0;
volatile bool mode=false;
volatile bool canEnter = true;

#define N 12

typedef struct{
char name[16];
uint8_t min;
uint8_t val;
uint8_t max;
}Menu_t;


volatile uint8_t first =0;
volatile uint8_t last =6;


Menu_t MenuItems[N]={
{"Value  1", 0, 0, 50},
{"Value  2", 0, 0, 50},
{"Value  3", 0, 0, 50},
{"Value  4", 0, 0, 50},
{"Value  5", 0, 0, 50},
{"Value  6", 0, 0, 50},
{"Value  7", 0, 0, 50},
{"Value  8", 0, 0, 50},
{"Value  9", 0, 0, 50},
{"Value 10", 0, 0, 50},
{"Value 11", 0, 0, 50},
{"Value 12", 0, 0, 50},
};
void cbENC_INTA(pint_pin_int_t pintr, uint32_t pmatch_status) {
	if(!canEnter) {
		return;
	}
	canEnter = false;
	if(GPIO_PinRead(BOARD_INITPMODPINS_ENC_B_GPIO, BOARD_INITPMODPINS_ENC_B_PORT, BOARD_INITPMODPINS_ENC_B_PIN)) {
		if(mode) {
			if(MenuItems[counter].val > MenuItems[counter].min)
				MenuItems[counter].val--;
		} else {
			if(counter>0)
				counter--;
			if(first > counter) {
				first--;
				last--;
			}
		}
	} else {
		if(mode) {
			if(MenuItems[counter].val < MenuItems[counter].max)
				MenuItems[counter].val++;
		} else {
			if(counter<N-1)
				counter++;
			if(counter >= last) {
				last++;
				first++;
			}
		}
	}
}
void cbENC_INTS(pint_pin_int_t pintr, uint32_t pmatch_status) {
	if(!canEnter) {
		return;
	}
	canEnter = false;
	mode=!mode;
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
	OLED_Puts(52, 0, "MENU");
	OLED_Draw_Line(0,10, 127,10);
	OLED_Refresh_Gram();
	while(1) {
		OLED_Puts(52, 0, "MENU");
		OLED_Draw_Line(0,10, 127,10);
		OLED_Refresh_Gram();


		for(int i=first; i < last;i++) {
			if(mode && i==counter)
				sprintf(sbuff, " %s [%03d] ", MenuItems[i].name, MenuItems[i].val);
			else
				sprintf(sbuff, " %s %03d   ", MenuItems[i].name, MenuItems[i].val);

			OLED_Puts(0, 2+i - first, sbuff);

		}
		OLED_Puts(0, 2+counter - first , ">");
		OLED_Refresh_Gram();

		canEnter = true;
	}
	return 0 ;
}
