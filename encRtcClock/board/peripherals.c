/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v14.0
processor: LPC55S69
package_id: LPC55S69JBD100
mcu_data: ksdk2_0
processor_version: 15.0.1
board: LPCXpresso55S69
functionalGroups:
- name: BOARD_InitPeripherals_cm33_core0
  UUID: 61d0725d-b300-49cb-9c66-b5edfbf8ffc1
  called_from_default_init: true
  selectedCore: cm33_core0
- name: BOARD_InitPeripherals_cm33_core1
  UUID: e2041cd4-ebb6-45a5-807f-e0c2dc047d48
  selectedCore: cm33_core1
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'system'
- type_id: 'system'
- global_system_definitions:
  - user_definitions: ''
  - user_includes: ''
  - global_init: ''
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'uart_cmsis_common'
- type_id: 'uart_cmsis_common_9cb8e302497aa696fdbb5a4fd622c2a8'
- global_USART_CMSIS_common:
  - quick_selection: 'default'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'gpio_adapter_common'
- type_id: 'gpio_adapter_common_57579b9ac814fe26bf95df0a384c36b6'
- global_gpio_adapter_common:
  - quick_selection: 'default'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "peripherals.h"

/***********************************************************************************************************************
 * BOARD_InitPeripherals_cm33_core0 functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * NVIC initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'NVIC'
- type: 'nvic'
- mode: 'general'
- custom_name_enabled: 'false'
- type_id: 'nvic_57b5eef3774cc60acaede6f5b8bddc67'
- functional_group: 'BOARD_InitPeripherals_cm33_core0'
- peripheral: 'NVIC'
- config_sets:
  - nvic:
    - interrupt_table:
      - 0: []
      - 1: []
      - 2: []
    - interrupts: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/* Empty initialization function (commented out)
static void NVIC_init(void) {
} */

/***********************************************************************************************************************
 * FLEXCOMM1 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'FLEXCOMM1'
- type: 'flexcomm_i2c'
- mode: 'I2C_Polling'
- custom_name_enabled: 'false'
- type_id: 'flexcomm_i2c_c8597948f61bd571ab263ea4330b9dd6'
- functional_group: 'BOARD_InitPeripherals_cm33_core0'
- peripheral: 'FLEXCOMM1'
- config_sets:
  - fsl_i2c:
    - i2c_mode: 'kI2C_Master'
    - clockSource: 'FXCOMFunctionClock'
    - clockSourceFreq: 'ClocksTool_DefaultInit'
    - i2c_master_config:
      - enableMaster: 'true'
      - baudRate_Bps: '1000000'
      - enableTimeout: 'false'
      - timeout_Ms: '35'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const i2c_master_config_t FLEXCOMM1_config = {
  .enableMaster = true,
  .baudRate_Bps = 1000000UL,
  .enableTimeout = false,
  .timeout_Ms = 35U
};

static void FLEXCOMM1_init(void) {
  /* Initialization function */
  I2C_MasterInit(FLEXCOMM1_PERIPHERAL, &FLEXCOMM1_config, FLEXCOMM1_CLOCK_SOURCE);
}

/***********************************************************************************************************************
 * RTC initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'RTC'
- type: 'lpc_rtc'
- mode: 'general'
- custom_name_enabled: 'false'
- type_id: 'lpc_rtc_5b94d23b38d98ad150d835147973adbf'
- functional_group: 'BOARD_InitPeripherals_cm33_core0'
- peripheral: 'RTC'
- config_sets:
  - fsl_rtc:
    - rtc_config:
      - setDateTime: 'true'
      - rtc_datetime:
        - year: '2024'
        - month: '3'
        - day: '22'
        - hour: '20'
        - minute: '40'
        - second: '0'
      - setAlarmTime: 'true'
      - alarm_datetime:
        - year: '2024'
        - month: '3'
        - day: '22'
        - hour: '20'
        - minute: '40'
        - second: '15'
      - setWakeup: 'false'
      - alarm_wake_up_enable: 'false'
      - wake_up_enable: 'false'
      - subseconds: 'false'
      - start: 'true'
    - rtc_interrupt:
      - interrupt_vectors:
        - enable_irq: 'true'
        - interrupt:
          - IRQn: 'RTC_IRQn'
          - enable_interrrupt: 'enabled'
          - enable_priority: 'false'
          - priority: '0'
          - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
rtc_datetime_t RTC_dateTimeStruct = {
  .year = 2024U,
  .month = 3U,
  .day = 22U,
  .hour = 20U,
  .minute = 40U,
  .second = 0U
};
rtc_datetime_t RTC_alarmDateTimeStruct = {
  .year = 2024U,
  .month = 3U,
  .day = 22U,
  .hour = 20U,
  .minute = 40U,
  .second = 15U
};

static void RTC_init(void) {
  /* RTC initialization */
  RTC_Init(RTC_PERIPHERAL);
  /* Stop RTC timer */
  RTC_StopTimer(RTC_PERIPHERAL);
  /* Date and time initialization */
  RTC_SetDatetime(RTC_PERIPHERAL, &RTC_dateTimeStruct);
  /* Alarm initialization */
  RTC_SetAlarm(RTC_PERIPHERAL, &RTC_alarmDateTimeStruct);
  /* Enable sub-second counter */
  RTC_EnableSubsecCounter(RTC_PERIPHERAL, false);
  /* Enable interrupt RTC_IRQn request in the NVIC. */
  EnableIRQ(RTC_IRQN);
  /* Start RTC timer */
  RTC_StartTimer(RTC_PERIPHERAL);
}

/***********************************************************************************************************************
 * PINT initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'PINT'
- type: 'pint'
- mode: 'interrupt_mode'
- custom_name_enabled: 'false'
- type_id: 'pint_cf4a806bb2a6c1ffced58ae2ed7b43af'
- functional_group: 'BOARD_InitPeripherals_cm33_core0'
- peripheral: 'PINT'
- config_sets:
  - general:
    - interrupt_array:
      - 0:
        - interrupt_id: 'INT_0'
        - interrupt_selection: 'PINT.0'
        - interrupt_type: 'kPINT_PinIntEnableFallEdge'
        - callback_function: 'encClockwise'
        - enable_callback: 'true'
        - interrupt:
          - IRQn: 'PIN_INT0_IRQn'
          - enable_priority: 'true'
          - priority: '0'
      - 1:
        - interrupt_id: 'INT_1'
        - interrupt_selection: 'PINT.2'
        - interrupt_type: 'kPINT_PinIntEnableFallEdge'
        - callback_function: 'encSwitch'
        - enable_callback: 'true'
        - interrupt:
          - IRQn: 'PIN_INT2_IRQn'
          - enable_priority: 'true'
          - priority: '0'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

static void PINT_init(void) {
  /* PINT initiation  */
  PINT_Init(PINT_PERIPHERAL);
  /* Interrupt vector PIN_INT0_IRQn priority settings in the NVIC. */
  NVIC_SetPriority(PINT_PINT_0_IRQN, PINT_PINT_0_IRQ_PRIORITY);
  /* Interrupt vector PIN_INT2_IRQn priority settings in the NVIC. */
  NVIC_SetPriority(PINT_PINT_2_IRQN, PINT_PINT_2_IRQ_PRIORITY);
  /* PINT PINT.0 configuration */
  PINT_PinInterruptConfig(PINT_PERIPHERAL, PINT_INT_0, kPINT_PinIntEnableFallEdge, encClockwise);
  /* PINT PINT.2 configuration */
  PINT_PinInterruptConfig(PINT_PERIPHERAL, PINT_INT_1, kPINT_PinIntEnableFallEdge, encSwitch);
  /* Enable PINT PINT.0 callback */
  PINT_EnableCallbackByIndex(PINT_PERIPHERAL, kPINT_PinInt0);
  /* Enable PINT PINT.2 callback */
  PINT_EnableCallbackByIndex(PINT_PERIPHERAL, kPINT_PinInt2);
}

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals_cm33_core0(void)
{
  /* Initialize components */
  FLEXCOMM1_init();
  RTC_init();
  PINT_init();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
  BOARD_InitPeripherals_cm33_core0();
}
