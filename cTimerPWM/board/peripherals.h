/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PERIPHERALS_H_
#define _PERIPHERALS_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "fsl_common.h"
#include "fsl_ctimer.h"
#include "fsl_clock.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/
/* Definitions for BOARD_InitPeripherals_cm33_core0 functional group */
/* Definition of peripheral ID */
#define CTIMER2_PERIPHERAL CTIMER2
/* Timer tick frequency in Hz (input frequency of the timer) */
#define CTIMER2_TICK_FREQ 10000UL
/* Timer tick period in ns (input period of the timer) */
#define CTIMER2_TICK_PERIOD 100000UL
/* Definition of PWM period channel. */
#define CTIMER2_PWM_PERIOD_CH kCTIMER_Match_3
/* Definition of PWM period */
#define CTIMER2_PWM_PERIOD 99
/* Definition of channel 1 ID */
#define CTIMER2_PWM_1_CHANNEL kCTIMER_Match_1
/* Definition of channel 1 duty */
#define CTIMER2_PWM_1_DUTY 50
/* CTIMER2 interrupt vector ID (number). */
#define CTIMER2_TIMER_IRQN CTIMER2_IRQn
/* CTIMER2 interrupt vector priority. */
#define CTIMER2_TIMER_IRQ_PRIORITY 0

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
extern const ctimer_config_t CTIMER2_config;

/***********************************************************************************************************************
 * Callback functions
 **********************************************************************************************************************/
  /* Single callback function declaration */
extern void cbTimerMatch(uint32_t flags);
extern ctimer_callback_t CTIMER2_callback[];

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/

void BOARD_InitPeripherals_cm33_core0(void);

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void);

#if defined(__cplusplus)
}
#endif

#endif /* _PERIPHERALS_H_ */
