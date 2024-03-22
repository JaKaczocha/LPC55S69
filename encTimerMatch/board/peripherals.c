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
 * PINT initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'PINT'
- type: 'pint'
- mode: 'match_mode'
- custom_name_enabled: 'false'
- type_id: 'pint_cf4a806bb2a6c1ffced58ae2ed7b43af'
- functional_group: 'BOARD_InitPeripherals_cm33_core0'
- peripheral: 'PINT'
- config_sets:
  - general:
    - match_rxev: 'false'
    - match_array:
      - 0:
        - use_slice: 'true'
        - match_slice_id: 'SLICE_0'
        - match_input_source: 'PINT.0'
        - match_configuration: 'kPINT_PatternMatchStickyFall'
        - match_endpoint_a: 'false'
        - callback_function: ''
        - enable_callback: 'false'
        - interrupt:
          - IRQn: 'PIN_INT0_IRQn'
          - enable_priority: 'false'
          - priority: '0'
      - 1:
        - use_slice: 'true'
        - match_slice_id: 'SLICE_1'
        - match_input_source: 'PINT.1'
        - match_configuration: 'kPINT_PatternMatchLow'
        - match_endpoint_a: 'true'
        - callback_function: 'encClockwise'
        - enable_callback: 'true'
        - interrupt:
          - IRQn: 'PIN_INT1_IRQn'
          - enable_priority: 'true'
          - priority: '0'
      - 2:
        - use_slice: 'true'
        - match_slice_id: 'SLICE_2'
        - match_input_source: 'PINT.0'
        - match_configuration: 'kPINT_PatternMatchStickyFall'
        - match_endpoint_a: 'false'
        - callback_function: ''
        - enable_callback: 'false'
        - interrupt:
          - IRQn: 'PIN_INT0_IRQn'
          - enable_priority: 'false'
          - priority: '0'
      - 3:
        - use_slice: 'true'
        - match_slice_id: 'SLICE_3'
        - match_input_source: 'PINT.1'
        - match_configuration: 'kPINT_PatternMatchHigh'
        - match_endpoint_a: 'true'
        - callback_function: 'encCounterClockwise'
        - enable_callback: 'true'
        - interrupt:
          - IRQn: 'PIN_INT3_IRQn'
          - enable_priority: 'true'
          - priority: '0'
      - 4:
        - use_slice: 'true'
        - match_slice_id: 'SLICE_4'
        - match_input_source: 'PINT.2'
        - match_configuration: 'kPINT_PatternMatchStickyFall'
        - match_endpoint_a: 'true'
        - callback_function: 'encPushButton'
        - enable_callback: 'true'
        - interrupt:
          - IRQn: 'PIN_INT4_IRQn'
          - enable_priority: 'true'
          - priority: '0'
      - 5:
        - use_slice: 'false'
        - match_slice_id: 'SLICE_5'
        - match_input_source: 'PINT.0'
        - match_configuration: 'kPINT_PatternMatchAlways'
        - match_endpoint_a: 'false'
        - callback_function: ''
        - enable_callback: 'false'
        - interrupt:
          - IRQn: 'PIN_INT0_IRQn'
          - enable_priority: 'false'
          - priority: '0'
      - 6:
        - use_slice: 'false'
        - match_slice_id: 'SLICE_6'
        - match_input_source: 'PINT.0'
        - match_configuration: 'kPINT_PatternMatchAlways'
        - match_endpoint_a: 'false'
        - callback_function: ''
        - enable_callback: 'false'
        - interrupt:
          - IRQn: 'PIN_INT0_IRQn'
          - enable_priority: 'false'
          - priority: '0'
      - 7:
        - use_slice: 'false'
        - match_slice_id: 'SLICE_7'
        - match_input_source: 'PINT.0'
        - match_configuration: 'kPINT_PatternMatchAlways'
        - callback_function: ''
        - enable_callback: 'false'
        - interrupt:
          - IRQn: 'PIN_INT0_IRQn'
          - enable_priority: 'false'
          - priority: '0'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
pint_pmatch_cfg_t PINT_SLICE_0_config = {
  .bs_src = kPINT_PatternMatchInp0Src,
  .bs_cfg = kPINT_PatternMatchStickyFall,
  .end_point = false,
  .callback = NULL
};
pint_pmatch_cfg_t PINT_SLICE_1_config = {
  .bs_src = kPINT_PatternMatchInp1Src,
  .bs_cfg = kPINT_PatternMatchLow,
  .end_point = true,
  .callback = encClockwise
};
pint_pmatch_cfg_t PINT_SLICE_2_config = {
  .bs_src = kPINT_PatternMatchInp0Src,
  .bs_cfg = kPINT_PatternMatchStickyFall,
  .end_point = false,
  .callback = NULL
};
pint_pmatch_cfg_t PINT_SLICE_3_config = {
  .bs_src = kPINT_PatternMatchInp1Src,
  .bs_cfg = kPINT_PatternMatchHigh,
  .end_point = true,
  .callback = encCounterClockwise
};
pint_pmatch_cfg_t PINT_SLICE_4_config = {
  .bs_src = kPINT_PatternMatchInp2Src,
  .bs_cfg = kPINT_PatternMatchStickyFall,
  .end_point = true,
  .callback = encPushButton
};

static void PINT_init(void) {
  /* PINT initiation  */
  PINT_Init(PINT_PERIPHERAL);
  /* Interrupt vector PIN_INT1_IRQn priority settings in the NVIC. */
  NVIC_SetPriority(PINT_PINT_1_IRQN, PINT_PINT_1_IRQ_PRIORITY);
  /* Interrupt vector PIN_INT3_IRQn priority settings in the NVIC. */
  NVIC_SetPriority(PINT_PINT_3_IRQN, PINT_PINT_3_IRQ_PRIORITY);
  /* Interrupt vector PIN_INT4_IRQn priority settings in the NVIC. */
  NVIC_SetPriority(PINT_PINT_4_IRQN, PINT_PINT_4_IRQ_PRIORITY);
  /* PINT SLICE_0 configuration  */
  PINT_PatternMatchConfig(PINT_PERIPHERAL, PINT_SLICE_0, &PINT_SLICE_0_config);
  /* PINT SLICE_1 configuration  */
  PINT_PatternMatchConfig(PINT_PERIPHERAL, PINT_SLICE_1, &PINT_SLICE_1_config);
  /* PINT SLICE_2 configuration  */
  PINT_PatternMatchConfig(PINT_PERIPHERAL, PINT_SLICE_2, &PINT_SLICE_2_config);
  /* PINT SLICE_3 configuration  */
  PINT_PatternMatchConfig(PINT_PERIPHERAL, PINT_SLICE_3, &PINT_SLICE_3_config);
  /* PINT SLICE_4 configuration  */
  PINT_PatternMatchConfig(PINT_PERIPHERAL, PINT_SLICE_4, &PINT_SLICE_4_config);
  /* Enable PINT SLICE_1 callback */
  PINT_EnableCallbackByIndex(PINT_PERIPHERAL, kPINT_PinInt1);
  /* Enable PINT SLICE_3 callback */
  PINT_EnableCallbackByIndex(PINT_PERIPHERAL, kPINT_PinInt3);
  /* Enable PINT SLICE_4 callback */
  PINT_EnableCallbackByIndex(PINT_PERIPHERAL, kPINT_PinInt4);
  /* Enable PINT match pattern mode  */
  PINT_PatternMatchEnable(PINT);
}

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
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals_cm33_core0(void)
{
  /* Initialize components */
  PINT_init();
  FLEXCOMM1_init();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
  BOARD_InitPeripherals_cm33_core0();
}
