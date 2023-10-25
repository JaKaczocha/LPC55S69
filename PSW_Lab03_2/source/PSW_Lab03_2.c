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
#define N 6

typedef struct{
    char name[16];
    uint8_t min;
    uint8_t val;
    uint8_t max;
}Menu_t;

Menu_t MenuItems[N]={
    {"Value 1", 0, 0, 10},
    {"Value 2", 0, 0, 20},
    {"Value 3", 0, 0, 10},
    {"Value 4", 0, 0, 50},
    {"Value 5", 0, 0, 10},
    {"Value 6", 0, 0, 30},
};

void cbENC_INTA(pint_pin_int_t pintr, uint32_t pmatch_status) {
    volatile uint32_t delay = 10000;
    uint8_t pinB_state_1, pinB_state_2;

    pinB_state_1 = GPIO_PinRead(BOARD_INITPMODPINS_ENC_B_GPIO, BOARD_INITPMODPINS_ENC_B_PORT, BOARD_INITPMODPINS_ENC_B_PIN);
    while(delay--); // Opóźnienie
    pinB_state_2 = GPIO_PinRead(BOARD_INITPMODPINS_ENC_B_GPIO, BOARD_INITPMODPINS_ENC_B_PORT, BOARD_INITPMODPINS_ENC_B_PIN);

    if(pinB_state_1 == pinB_state_2) { // Jeśli stan pinu B nie zmienił się po opóźnieniu
        if(pinB_state_1) {
            if(mode) {
                if(MenuItems[counter].val > MenuItems[counter].min)
                    MenuItems[counter].val--;
            } else {
                if(counter>0)
                    counter--;
            }
        } else {
            if(mode) {
                if(MenuItems[counter].val < MenuItems[counter].max)
                    MenuItems[counter].val++;
            } else {
                if(counter<N-1)
                    counter++;
            }
        }
    }
}

void cbENC_INTS(pint_pin_int_t pintr, uint32_t pmatch_status) {
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
    OLED_Puts(52, 0, "MENU");
    OLED_Draw_Line(0,10, 127,10);
    OLED_Refresh_Gram();

    while(1) {
        for(int i=0; i<N;i++) {
            if(mode && i==counter)
                sprintf(sbuff, " %s [%03d] ", MenuItems[i].name, MenuItems[i].val);
            else
                sprintf(sbuff, " %s %03d ", MenuItems[i].name, MenuItems[i].val);
            OLED_Puts(0, 2+i, sbuff);
        }
        OLED_Puts(0, 2+counter, ">");
        OLED_Refresh_Gram();
    }

    return 0 ;
}

