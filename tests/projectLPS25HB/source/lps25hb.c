#include "lpc25hb.h"
#include "fsl_i2c.h"

#include "fsl_debug_console.h"


#define LPS25HB_ADDR            0xBA

#define LPS25HB_WHO_AM_I       0x0F
#define LPS25HB_CTRL_REG1      0x20
#define LPS25HB_CTRL_REG2      0x21
#define LPS25HB_CTRL_REG3      0x22
#define LPS25HB_CTRL_REG4      0x23
#define LPS25HB_PRESS_OUT_XL   0x28
#define LPS25HB_PRESS_OUT_L    0x29
#define LPS25HB_PRESS_OUT_H    0x2A
#define LPS25HB_TEMP_OUT_L     0x2B
#define LPS25HB_TEMP_OUT_H     0x2C

#define TIMEOUT_MS             100

uint8_t LPS25HB_Read_Byte(uint8_t reg_address) {
    uint8_t data;

    if (kStatus_Success == I2C_MasterStart(I2C1_BASE, LPS25HB_ADDR , kI2C_Write)) {
        I2C_MasterWriteBlocking(I2C1_BASE, &reg_address, 1, kI2C_TransferDefaultFlag);
        I2C_MasterRepeatedStart(I2C1_BASE, LPS25HB_ADDR , kI2C_Read);
        I2C_MasterReadBlocking(I2C1_BASE, &data, 1, kI2C_TransferDefaultFlag);
        I2C_MasterStop(I2C1_BASE);
    }

    return data;
}

void LPS25HB_Write_Byte(uint8_t data, uint8_t reg_address) {
    uint8_t cmd_buff[2];
    cmd_buff[0] = reg_address;
    cmd_buff[1] = data;

    if (kStatus_Success == I2C_MasterStart(I2C1_BASE, LPS25HB_ADDR , kI2C_Write)) {
        I2C_MasterWriteBlocking(I2C1_BASE, &cmd_buff[0], 2, kI2C_TransferDefaultFlag);
        I2C_MasterStop(I2C1_BASE);
    }
}


status_t lps25hb_init(void)
{
    if (LPS25HB_Read_Byte(LPS25HB_WHO_AM_I) != 0xBD) {
    	PRINTF("WHO AM I KURWA");
    	return kStatus_Fail;
    }


    PRINTF("WHO AM I WOQW");

    return kStatus_Success ;
}


