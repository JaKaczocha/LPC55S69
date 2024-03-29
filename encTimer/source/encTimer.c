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

void  detectedSIA(pint_pin_int_t pintr, uint32_t pmatch_status) {
	if(GPIO_PinRead(BOARD_INITPMODPINS_SIB_GPIO, BOARD_INITPMODPINS_SIB_PORT, BOARD_INITPMODPINS_SIB_PIN))
		counter--;
	else
		counter++;
}
void detectedSW(pint_pin_int_t pintr, uint32_t pmatch_status) {
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
	OLED_Puts(0, 0, "Encoder test");
	OLED_Refresh_Gram();
	while(1) {
		sprintf(sbuff,"Counter: %03d", counter);
		OLED_Puts(0, 2, sbuff);
		sprintf(sbuff,"Mode: %d", mode);
		OLED_Puts(0, 3, sbuff);
		OLED_Refresh_Gram();
	}
	return 0 ;
}
