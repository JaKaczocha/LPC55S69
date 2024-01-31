#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S69_cm33_core0.h"
#include "fsl_debug_console.h"
#include "lcd.h"
#include "fsl_power.h"
char sbuff[32];
lpadc_conv_result_t g_LpadcResultConfigStruct;
volatile uint16_t joyAxisX=0, joyAxisY=0;
volatile bool joySw=false;
int32_t coursorX=0, coursorY=0;
volatile bool ready=false;
/* ADC0_IRQn interrupt handler */
void ADC0_IRQHANDLER(void) {
	LPADC_GetConvResult(ADC0, &g_LpadcResultConfigStruct, 0U);
	joyAxisX=g_LpadcResultConfigStruct.convValue;
	LPADC_GetConvResult(ADC0, &g_LpadcResultConfigStruct, 0U);
	joyAxisY=g_LpadcResultConfigStruct.convValue;
	joySw = !GPIO_PinRead(BOARD_INITADCPINS_SW_GPIO, BOARD_INITADCPINS_SW_PORT, BOARD_INITADCPINS_SW_PIN);
	ready = true;
}
void setCursor(uint16_t x, uint16_t y, uint16_t size, uint16_t color) {
	int16_t a, b;
	a=x-size;
	b=x+size;
	if(a<0) {
		a=0;
	}
	LCD_Draw_Line(a, y, b, y, color);
	a=y-size;
	b=y+size;
	if(a<0) {
		a=0;
	}
	LCD_Draw_Line(x, a, x, b, color);
}
/*
 * @brief Application entry point.
 */
int main(void) {
	/* Disable LDOGPADC power down */
	POWER_DisablePD(kPDRUNCFG_PD_LDOGPADC);
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
		if(ready) {
			coursorX=joyAxisX/409;
			coursorY=LCD_HEIGHT-(joyAxisY/511);
			if(coursorX >= LCD_WIDTH){
				coursorX = LCD_WIDTH-1;
			}
			if(coursorY >= LCD_HEIGHT){
				coursorY = LCD_HEIGHT-1;
			}
			LCD_Clear(0x0000);
			sprintf(sbuff, "X:%3d Y:%3d S: %d", coursorX, coursorY, joySw);
			LCD_Puts(10, 5, sbuff, 0x07FF);
			setCursor(coursorX, coursorY, 10, 0xF800);
			if(joySw) {
				LCD_Draw_Circle(coursorX, coursorY, 10, 0xFF80);
			}
			LCD_GramRefresh();
			ready = false;
		}
	}
	return 0 ;
}
