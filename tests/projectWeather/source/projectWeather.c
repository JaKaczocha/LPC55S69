/*
 * Copyright 2016-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    projectWeather.c
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
#include "fsl_i2c.h"
/* TODO: insert other definitions and declarations here. */

//#define LPS25HB_ADDR        0xBA
//#define LPS25HB_WHO_AM_I 		0x0F

#define BME280_ADDR 0xBA
#define BME280_ADDR_REG 0x0F

//#define BME280_ADDR 0x76
//#define BME280_ADDR_REG 0xD0
i2c_master_handle_t g_m_handle;
const uint8_t g_bme280_address = BME280_ADDR;

uint8_t g_accel_addr_found = 0x00;

volatile bool completionFlag = false;
volatile bool nakFlag        = false;

static void i2c_master_callback(I2C_Type *base, i2c_master_handle_t *handle,
		                        status_t status, void *userData)
{
    /* Signal transfer success when received success status. */
    if (status == kStatus_Success)
    {
        completionFlag = true;
    }
    /* Signal transfer success when received success status. */
    if ((status == kStatus_I2C_Nak) || (status == kStatus_I2C_Addr_Nak))
    {
        nakFlag = true;
    }
}


static bool I2C_ReadAccelWhoAmI(void)
{

    uint8_t who_am_i_reg          = BME280_ADDR_REG;
    uint8_t who_am_i_value        = 0x00;
    bool find_device              = false;

    FLEXCOMM4_transfer.slaveAddress   = BME280_ADDR;
    FLEXCOMM4_transfer.direction      = kI2C_Write;
    FLEXCOMM4_transfer.subaddress     = 0;
    FLEXCOMM4_transfer.subaddressSize = 0;
    FLEXCOMM4_transfer.data           = &who_am_i_reg;
    FLEXCOMM4_transfer.dataSize       = 1;
    FLEXCOMM4_transfer.flags          = kI2C_TransferNoStopFlag;

	I2C_MasterTransferNonBlocking(FLEXCOMM4_PERIPHERAL, &g_m_handle, &FLEXCOMM4_transfer);

	/*  wait for transfer completed. */
	while ((!nakFlag) && (!completionFlag))
	{
	}

	nakFlag = false;

	if (completionFlag == true)
	{
		completionFlag     = false;
		find_device        = true;
		g_accel_addr_found = FLEXCOMM4_transfer.slaveAddress;
	}


    if (find_device == true)
    {


    	FLEXCOMM4_transfer.direction      = kI2C_Read;
    	FLEXCOMM4_transfer.subaddress     = 0;
    	FLEXCOMM4_transfer.subaddressSize = 0;
    	FLEXCOMM4_transfer.data           = &who_am_i_value;
    	FLEXCOMM4_transfer.dataSize       = 1;
    	FLEXCOMM4_transfer.flags          = kI2C_TransferRepeatedStartFlag;

        I2C_MasterTransferNonBlocking(FLEXCOMM4_PERIPHERAL, &g_m_handle, &FLEXCOMM4_transfer);

        /*  wait for transfer completed. */
        while ((!nakFlag) && (!completionFlag))
        {
        }

        nakFlag = false;

        if (completionFlag == true)
        {
                PRINTF("Found a device, the WhoAmI value is 0x%x\r\n", who_am_i_value);
                PRINTF("The device address is 0x%x. \r\n", FLEXCOMM4_transfer.slaveAddress);

        }
        else
        {
            PRINTF("Not a successful i2c communication \r\n");
            return false;
        }
    }
    else
    {

        PRINTF("\r\n Do not find an accelerometer device ! \r\n");
        PRINTF("Found a device, the WhoAmI value is 0x%x\r\n", who_am_i_value);
        return false;
    }
    return true;
}

/*
 * @brief   Application entry point.
 */
int main(void) {

	bool isThereAccel;

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    PRINTF("\r\nI2C example -- Read BME280 sensor\r\n");

    I2C_MasterTransferCreateHandle(FLEXCOMM4_PERIPHERAL, &g_m_handle, \
    								i2c_master_callback, NULL);
    isThereAccel = I2C_ReadAccelWhoAmI();

    while(1) {
     }
    return 0 ;
}

