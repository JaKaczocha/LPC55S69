#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S69_cm33_core0.h"
#include "fsl_debug_console.h"
#define LEDS 8
#define GET_BIT(k, n) (k & (1 << (n)))
#define SET_BIT(k, n) (k |= (1 << (n)))
#define CLR_BIT(k, n) (k &= ~(1 << (n)))
#define CODE_0 0b10000
#define CODE_1 0b11100
uint32_t colors[LEDS] = {
		// GRB
		0x00ff00, //red
		0x80ff00, //orange
		0xffff00, //yellow
		0xff8000, //chartreuse
		0xff0000, //green
		0xff0080, //spring green
		0x00ff00, //red
		0x8000ff, //dodger blue

};
void Neopixels_Send(SPI_Type *base, uint32_t n, uint32_t *value) {
	uint16_t LED_data=0;
	uint32_t configFlags=0U;
	/* ignore RX */
	configFlags |= (1<< 22);
	for(int j=0; j<n; j++) {
		for(int i=23;i>=0;i--) {
			LED_data = GET_BIT(value[j], i) ? CODE_1 : CODE_0;
			while(!(SPI_GetStatusFlags(base) & kSPI_TxNotFullFlag))
				;
			SPI_WriteData(base, LED_data, configFlags);
		}
	}
	// Reset >= 50 us
	LED_data=0;
	for(int j=0; j<60; j++) {
		while(!(SPI_GetStatusFlags(base) & kSPI_TxNotFullFlag))
			;
		SPI_WriteData(base, LED_data, configFlags);
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
	while(1) {
		Neopixels_Send(FLEXCOMM3_PERIPHERAL, LEDS, colors);
	}
	return 0 ;
}
