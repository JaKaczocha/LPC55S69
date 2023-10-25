#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S69_cm33_core0.h"
#include "fsl_debug_console.h"
#include "oled.h"
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
OLED_Draw_Bitmap(LogoKI);
OLED_Refresh_Gram();
while(1) {
}
return 0 ;
}
