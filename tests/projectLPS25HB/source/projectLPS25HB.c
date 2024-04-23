/*
 * Copyright 2016-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    projectLPS25HB.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S69_cm33_core0.h"
#include "fsl_debug_console.h"

/* TODO: insert other include files here. */
#include "lpc25hb.h"
/* TODO: insert other definitions and declarations here. */

#include "lcd.h"

char sbuff[30];
volatile float temp = 0.0;
volatile float press = 0.0;


volatile uint32_t g_systickCounter;
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
/*
 * @brief   Application entry point.
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

	LCD_Init(FLEXCOMM3_PERIPHERAL);

	PRINTF("Hello World1\r\n");
	lps25hb_init();
	delay_ms(500);

	PRINTF("Hello World2\r\n");

	while(1) {


		delay_ms(1000);
	}
	return 0 ;
}
