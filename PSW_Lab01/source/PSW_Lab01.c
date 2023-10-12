/*
 * Copyright 2016-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    PSW_Lab01.c
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

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
void delay(uint32_t milliseconds) {
    uint32_t delayTicks = milliseconds * (SystemCoreClock / 1000);
    for (uint32_t i = 0; i < delayTicks; i++) {
        __NOP();  // Wykonuje "no operation", czyli nic nie robi, tworząc opóźnienie.
    }
}

int main(void) {

	char c;
	bool led = 1;
    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    PRINTF("Start\r\n");

    while(1) {

    	if(GPIO_PinRead(BOARD_INITBUTTONSPINS_S1_GPIO,BOARD_INITBUTTONSPINS_S1_PORT,BOARD_INITBUTTONSPINS_S1_PIN) == 0)
    	{
    		led = !led;
    		GPIO_PinWrite(BOARD_INITLEDSPINS_LED_GREEN_GPIO, BOARD_INITLEDSPINS_LED_GREEN_PORT, BOARD_INITLEDSPINS_LED_GREEN_PIN, 1);
    		    	    GPIO_PinWrite(BOARD_INITLEDSPINS_LED_BLUE_GPIO, BOARD_INITLEDSPINS_LED_BLUE_PORT, BOARD_INITLEDSPINS_LED_BLUE_PIN, 1);
    		GPIO_PinWrite(BOARD_INITLEDSPINS_LED_RED_GPIO, BOARD_INITLEDSPINS_LED_RED_PORT, BOARD_INITLEDSPINS_LED_RED_PIN, led);
    		while(GPIO_PinRead(BOARD_INITBUTTONSPINS_S1_GPIO,BOARD_INITBUTTONSPINS_S1_PORT,BOARD_INITBUTTONSPINS_S1_PIN) == 0);
    		delay(30);
    	}
    	if(GPIO_PinRead(BOARD_INITBUTTONSPINS_S2_GPIO,BOARD_INITBUTTONSPINS_S2_PORT,BOARD_INITBUTTONSPINS_S2_PIN) == 0)
    	{
    	    led = !led;
    	    GPIO_PinWrite(BOARD_INITLEDSPINS_LED_RED_GPIO, BOARD_INITLEDSPINS_LED_RED_PORT, BOARD_INITLEDSPINS_LED_RED_PIN, 1);
    	    GPIO_PinWrite(BOARD_INITLEDSPINS_LED_BLUE_GPIO, BOARD_INITLEDSPINS_LED_BLUE_PORT, BOARD_INITLEDSPINS_LED_BLUE_PIN, 1);
    	    GPIO_PinWrite(BOARD_INITLEDSPINS_LED_GREEN_GPIO, BOARD_INITLEDSPINS_LED_GREEN_PORT, BOARD_INITLEDSPINS_LED_GREEN_PIN, led);
    	    while(GPIO_PinRead(BOARD_INITBUTTONSPINS_S2_GPIO,BOARD_INITBUTTONSPINS_S2_PORT,BOARD_INITBUTTONSPINS_S2_PIN) == 0);
    	    delay(30);
    	 }
    	if(GPIO_PinRead(BOARD_INITBUTTONSPINS_S3_GPIO,BOARD_INITBUTTONSPINS_S3_PORT,BOARD_INITBUTTONSPINS_S3_PIN) == 0)
    	{
    	    led = !led;
    	    GPIO_PinWrite(BOARD_INITLEDSPINS_LED_RED_GPIO, BOARD_INITLEDSPINS_LED_RED_PORT, BOARD_INITLEDSPINS_LED_RED_PIN, 1);
    	    GPIO_PinWrite(BOARD_INITLEDSPINS_LED_GREEN_GPIO, BOARD_INITLEDSPINS_LED_GREEN_PORT, BOARD_INITLEDSPINS_LED_GREEN_PIN, 1);
    	    GPIO_PinWrite(BOARD_INITLEDSPINS_LED_BLUE_GPIO, BOARD_INITLEDSPINS_LED_BLUE_PORT, BOARD_INITLEDSPINS_LED_BLUE_PIN, led);
    	    while(GPIO_PinRead(BOARD_INITBUTTONSPINS_S3_GPIO,BOARD_INITBUTTONSPINS_S3_PORT,BOARD_INITBUTTONSPINS_S3_PIN) == 0);
    	    delay(30);
    	}
    	/*
    	if(GPIO_PinRead(BOARD_INITBUTTONSPINS_S3_GPIO, BOARD_INITBUTTONSPINS_S3_PORT, BOARD_INITBUTTONSPINS_S3_PIN) == 0)
    	{
    		GPIO_PinWrite(BOARD_INITLEDSPINS_LED_RED_GPIO,BOARD_INITLEDSPINS_LED_RED_PORT, BOARD_INITLEDSPINS_LED_RED_PIN, 1);
    	}*/
    }
    return 0 ;
}
