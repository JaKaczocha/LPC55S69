#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S69_cm33_core0.h"
#include "fsl_debug_console.h"
bool g_pinState = false;
volatile uint32_t g_systickCounter;

#ifdef __cplusplus
extern "C" {
#endif

void SysTick_Handler(void)
{
if (g_systickCounter)
 g_systickCounter--;
}
void delay_ms(uint32_t n)
{
g_systickCounter = n;
while (g_systickCounter);
}

#ifdef __cplusplus
}
#endif
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
SysTick_Config(SystemCoreClock / 1000U);
while(1) {
GPIO_PinWrite(BOARD_INITLEDSPINS_LED_RED_GPIO,
 BOARD_INITLEDSPINS_LED_RED_PORT,
 BOARD_INITLEDSPINS_LED_RED_PIN,
 g_pinState ^= true);
delay_ms(500);
}
return 0 ;
}
