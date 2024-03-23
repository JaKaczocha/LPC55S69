#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S69_cm33_core0.h"
#include "fsl_debug_console.h"
#include "oled.h"


uint16_t bouncing = 0;
char sbuff[32];
volatile uint16_t counter=0;
volatile uint8_t mode=1;

//bool g_pinState = false;
void SysTick_Handler(void)
{
	//GPIO_PinWrite(BOARD_INITLEDSPINS_LED_RED_GPIO, BOARD_INITLEDSPINS_LED_RED_PORT, BOARD_INITLEDSPINS_LED_RED_PIN, g_pinState^=true);
	bouncing = bouncing - 1 > 0 ? bouncing - 1 : 0;
}


void intEncSW(pint_pin_int_t pintr, uint32_t pmatch_status) {
	if(!bouncing) {
		mode = mode == 1 ? 10 : (mode == 10 ? 100 : 1);

	}

}
void intEncSIA(pint_pin_int_t pintr, uint32_t pmatch_status) {
	if(!bouncing) {
		if(!GPIO_PinRead(BOARD_INITENCPINS_SIB_GPIO, BOARD_INITENCPINS_SIB_PORT, BOARD_INITENCPINS_SIB_PIN)) {
				counter += mode;
			} else {
				counter -= mode;
			}
		bouncing = 15;

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
	SysTick_Config(SystemCoreClock / 100U);
	OLED_Init(FLEXCOMM1_PERIPHERAL);
	OLED_Puts(0, 0, "Encoder test");
	OLED_Refresh_Gram();
	while(1) {
			sprintf(sbuff,"Counter: %04d", counter);
			OLED_Puts(0, 2, sbuff);
			sprintf(sbuff,"Mode: %04d", mode);
			OLED_Puts(0, 3, sbuff);
			OLED_Refresh_Gram();


		}
	return 0 ;
}




