#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S69_cm33_core0.h"
#include "fsl_debug_console.h"
#include "lcd.h"
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
	while(1) {
		LCD_Clear(0b1111100000000000);
		LCD_GramRefresh();
		for(volatile int i=0;i<10000000;i++)
			;
		LCD_Clear(0b0000011111100000);
		LCD_GramRefresh();
		for(volatile int i=0;i<10000000;i++)
			;
		LCD_Clear(0b0000000000011111);
		LCD_GramRefresh();
		for(volatile int i=0;i<10000000;i++)
			;
	}
	return 0 ;
}
