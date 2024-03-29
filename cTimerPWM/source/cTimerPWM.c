#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S69_cm33_core0.h"
#include "fsl_debug_console.h"

uint8_t pwmDuty=0;

void cbTimerMatch(uint32_t flags) {
	CTIMER_UpdatePwmDutycycle(CTIMER2_PERIPHERAL,
			CTIMER2_PWM_PERIOD_CH,
			CTIMER2_PWM_1_CHANNEL,
			100-pwmDuty);
	pwmDuty++;
	if(pwmDuty>100)
		pwmDuty=0;
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
	while(1) {
	}
	return 0 ;
}
